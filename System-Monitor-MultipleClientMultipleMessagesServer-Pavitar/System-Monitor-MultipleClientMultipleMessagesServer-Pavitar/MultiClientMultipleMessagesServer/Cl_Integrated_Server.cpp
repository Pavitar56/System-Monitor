
#include<thread>
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#include <fstream>
#include "database.h"
#include<unordered_map>

#define DatabaseName "FinalDb"
#define TableName "FinalTable"

#define SettingsFileName "ConfigurationSettings.json"

#define SHUTDOWN -1
#define SUCCESS 0


#pragma comment (lib, "ws2_32.lib")

void main()
{

	Database db;             //Object of class database is created to handle all the database related queries
	db.dbConnect();              //connecting to database

	db.createDb(DatabaseName);           //creating the database if it does not exists already
	db.useDb(DatabaseName);                 //using the database created
	db.createTable(TableName);          //creating table in database if it does not exists already


	ConfigrationSettings Settings;        //class to read and get neccessary information from ConfigrationFile(present at source code only)

	int ErrorCode = Settings.read(SettingsFileName);

	if (ErrorCode == SHUTDOWN)
	{
		return;
	}

	string ipAddress = Settings.IP_getter();			// IP Address of the server

	if (ipAddress == "")                 //checking if ip was there in config file
	{
		return;
	}

	long long int port = Settings.Port_getter();						// Listening port # on the server

	if (port == SHUTDOWN)                      // checking if port number was there in config file
	{
		return;
	}

	// Initialze winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	// To ensure successful initialization of WinSock
	try
	{
		int wsOk = WSAStartup(ver, &wsData);
		if (wsOk != 0)
		{
			throw 101;
		}
	}
	catch (...)
	{
		cerr << "Cannot Initialize winsock.Quitting... " << endl;
		return;
	}

	// Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);


	// To ensure successful creation of socket 
	try
	{
		if (listening == INVALID_SOCKET)
		{
			throw 102;
		}
	}
	catch (...)
	{
		cerr << "Cannot create socket. Quitting..." << endl;
		return;
	}

	// Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
	//hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton .... 

	// Binding the IP address and port to a socket and ensure that binding is successful.
	try
	{
		int binded = bind(listening, (sockaddr*)&hint, sizeof(hint));
		if (binded != 0)
		{
			throw 103;
		}
	}
	catch (...)
	{
		cerr << "Could not Bind IP Address and Port to Socket. Quitting..." << endl;
		return;

	}

	// Telling Winsock the socket is for listening 
	//To ensure that the socket has been successfully set for listening.    
	try
	{
		int set_listen = listen(listening, SOMAXCONN);
		if (set_listen == SOCKET_ERROR)
		{
			throw 104;
		}
	}
	catch (...)
	{
		cerr << "Unable to set master socket to listening mode." << endl;
	}



	// Create the master file descriptor set and zero it
	fd_set master;
	FD_ZERO(&master);

	// Add our first socket that we're interested in interacting with; the listening socket!
	// It's important that this socket is added for our server or else we won't 'hear' incoming
	// connections 
	FD_SET(listening, &master);

	// this will be changed by the \quit command 
	bool running = true;//stopping server condtion handler /quit stops the server

	unordered_map<string, SOCKET> All_Clients;    //map with keys as client name and values as socket number associated with it
	unordered_map<SOCKET, string> All_Sockets;  //map with keys as socket number and values as client name associated with it


	std::thread loop([&]()                           //1 single thread to handle all the multiple clients
		{

			while (running)
			{
				// Make a copy of the master file descriptor set, this is SUPER important because
				// the call to select() is _DESTRUCTIVE_. The copy only contains the sockets that
				// are accepting inbound connection requests OR messages. 

				// E.g. You have a server and it's master file descriptor set contains 5 items;
				// the listening socket and four clients. When you pass this set into select(), 
				// only the sockets that are interacting with the server are returned. Let's say
				// only one client is sending a message at that time. The contents of 'copy' will
				// be one socket. You will have LOST all the other sockets.

				// SO MAKE A COPY OF THE MASTER LIST TO PASS INTO select() !!!

				fd_set copy = master;

				// See who's talking to us
				int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

				// Loop through all the current connections / potential connect
				
				try
				{
					if (socketCount == SOCKET_ERROR)
					{
						throw 107;
					}
					else
					{
						for (int i = 0; i < socketCount; i++)
						{
							// Makes things easy for us doing this assignment
							SOCKET sock = copy.fd_array[i];


							try
							{
								if (sock == INVALID_SOCKET)
								{
									throw 102;
								}
							}
							catch (...)
							{
								cerr << "Cannot create socket. Quitting..." << endl;
								return;
							}

							// Is it an inbound communication?
							if (sock == listening)
							{
								// Accepting a new connection
								try
								{
									SOCKET client = accept(listening, nullptr, nullptr);
									if (client == INVALID_SOCKET)
									{
										throw 105;
									}
									else
									{
										// Add the new connection to the list of connected clients
										FD_SET(client, &master);
										db.InsertConnectionMessage(TableName, "New Connection added!.");   //updating database
									}
								}
								catch (...)
								{
									db.InsertConnectionMessage(TableName, "Connection failed!.");

								}

							}
							else // It's an inbound message
							{
								char buf[4096];
								ZeroMemory(buf, 4096);

								try
								{
									// Receive message
									int bytesIn = recv(sock, buf, 4096, 0);
									if (bytesIn <= 0)
									{
										// Drop the client
										closesocket(sock);
										FD_CLR(sock, &master);
										throw 106;
									}
									else
									{
										// Check to see if it's a command. \quit kills the connection
										//cout << buf[0] << endl;
										if (buf[0] == '\\')
										{
											// Is the command quit? 
											string cmd = string(buf, bytesIn);            
											if (cmd == "\\quit")       // if client sends \quit then server disconnects that client
											{

												string disconnectStatus = "You are now disconnected";
												try
												{
													int sent = send(sock, disconnectStatus.c_str(), disconnectStatus.size() + 1, 0);  //send disconnection message back to client
													if (sent > 0)
													{
														db.InsertConnectionMessage(TableName, "A Connection with client name "+ All_Sockets[sock].substr(1)
																								+ " was disconnected!."); //updating database saying client name is disconnected

														string ClientName = All_Sockets[sock];
														All_Clients.erase(ClientName);      //removing from list of connected clients and sockets
														All_Sockets.erase(sock);			

														closesocket(sock);
														FD_CLR(sock, &master);         //clearing from master socket in case of \quit by client
													}
													else
													{
														throw 108;
													}
												}
												catch (...)
												{
													cerr << "Unable to send disconnection message to client " + All_Sockets[sock].substr(1) << endl;
												}

											}
											else             //it means it is a username 
											{
												string username(buf);
												//cout << username << endl;
												if (All_Clients.find(username) == All_Clients.end())   //check if username already exists or not
												{
													//cout << username << endl;
													string NoNamError = "Sucessfully Connected!";
													send(sock, NoNamError.c_str(), NoNamError.size() + 1, 0);
													All_Clients[username] = sock;         //adding to list of connected clients and sockets
													All_Sockets[sock] = username;
												}
												else
												{
													string SameNameError = "Error username Already exists";
													send(sock, SameNameError.c_str(), SameNameError.size() + 1, 0);
												}

											}

											// Unknown command
											continue;
										}


										// Send message to other clients, and definiately NOT the listening socket
										string s = "";
										for (int i = 0; i < bytesIn; i++)       //converting char array to string to add it to json
										{
											s = s + buf[i];
										}
										//cout << s << endl;
										std::ofstream o("pretty2.json");     //creating json with recieved data from cleint
										o << s << std::endl;

										db.InsertIntoDb(TableName, s, sock);      //updating all the data recieved from client into database(s contains all the client data recieved)        

												
										ostringstream ss;
										ss << "SOCKET #" << sock << ": " << buf << "\r\n";  //making data recieved ready to be echoed back
										string strOut = ss.str();
										cout << "SOCKET #" << sock << endl;
										try            //echoing data recieved from client back to client
										{
											int sent = send(sock, strOut.c_str(), strOut.size() + 1, 0);
											if (sent <= 0)                    //exception if not echoed
											{
												throw 109;
											}

										}
										catch (...)
										{
											cerr << "Unable to Echo message back to client \\" +All_Sockets[sock].substr(1) << endl;
										}
												
									}
								}
								catch (...)              //this catches the abrupt disconnection from client and removes it from master socket as client 
								{                           //is no longer connected to server
									string ClientName = "";                
									if (All_Sockets.find(sock) != All_Sockets.end())
									{
										ClientName = All_Sockets[sock];
										All_Clients.erase(ClientName);      //removing from list of connected clients and sockets
										All_Sockets.erase(sock);
									}

									cerr << "Unable to receive data.Client name " + ClientName.substr(1) + " disconnected abruptly" << endl;

									db.InsertConnectionMessage(TableName, "A Connection with client name " + ClientName.substr(1)   //updating database
																	+ " was disconnected!.");
									// Drop the client
									try
									{
										int check = closesocket(sock);              //closing everything related to this client
										if (check == SOCKET_ERROR)
										{
											throw 110;
										}
									}
									catch (...)
									{
										cerr << "Unable to close socket but it is now removed from master socket.Client name "+ ClientName.substr(1)
															+ " disconnected abruptly" << endl;
									}
									FD_CLR(sock, &master);   //removing abruptly disconnected cleint from master socket too
								}
							}
						}
					}
				}
				catch (...)
				{
					cerr << "Unable to number of socket handles that are ready." << endl; //what here
				}
			}

	});

		loop.detach();       //detached thread so that control is back to main function for quit command of server

		string ShutDownServer = "";
		while (true)
		{
			getline(cin, ShutDownServer);                      //if admin enters quit server closed and shuts down
			if (ShutDownServer == "\\quit")
			{
				running = false;
				//cout << "bye" << endl;
				break;
			}
		}
		


	// Remove the listening socket from the master file descriptor set and close it
	// to prevent anyone else trying to connect.
		FD_CLR(listening, &master);
		try
		{
			int check = closesocket(listening);
			if (check == SOCKET_ERROR)
			{
				throw 110;
			}
		}
		catch (...)
		{
			cerr << "Unable to close listening socket." << endl;
		}

	// Message to let users know what's happening.
	string msg = "$ Server is shutting down. Goodbye\r\n";

	while (master.fd_count > 0)          //loop to let users know that server is shutting down so that they can quit 
	{
		while (master.fd_count > 0)
		{
			// Get the socket number
			SOCKET sock = master.fd_array[0];
			try
			{
				if (sock == INVALID_SOCKET)
				{
					throw 102;
				}
			}
			catch (...)
			{
				cerr << "Cannot create cleaning socket. Quitting..." << endl;
				return;
			}

			// Send the goodbye message
			try
			{
				int sent_bytes = send(sock, msg.c_str(), msg.size() + 1, 0);
				if (sent_bytes <= 0)
				{
					throw 109;
				}

			}
			catch (...)
			{
				cerr << "Unable to Echo server shutdown message back to client." << endl;
			}


			// Remove it from the master set and close the socket
			FD_CLR(sock, &master);
			try
			{
				int check = closesocket(sock);
				if (check == SOCKET_ERROR)
				{
					throw 110;
				}
			}
			catch (...)
			{
				cerr << "Unable to close master socket." << endl;
			}

		}
	}

	// Cleanup winsock
	WSACleanup();
	cout << "All resources freed" << endl;
	system("pause");
}
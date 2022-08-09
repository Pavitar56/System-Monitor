
#define TimeInterval 5000

#define SHUTDOWN -1
#define SUCCESS 0

#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include "SystemInfoHeader.h"
#include "json.hpp"
#pragma comment(lib, "ws2_32.lib")

using namespace std;
using json = nlohmann::json;

//this is the function that runs periodically to send data to server if send successfull it returns SUCCESS value 
//otherwise  SHUTDOWN value and stops sending the data further
int updater(SOCKET sock,string ClientName)
{
	string s = "";


	SystemInfo_JsonWriter(ClientName);                  //creates json of system information gathered
	json client_info;						//json object
	std::ifstream i("pretty.json");
	i >> client_info;
	s = client_info.dump(4);			//converts into string (4 - retains indentation/readability)
	char buf[4096];

	if (s.size() > 0)
	{
		//Sending data and ensuring it is sent successfully
		try
		{
			int sendResult = send(sock, s.c_str(), s.size() + 1, 0);
			if (sendResult == SOCKET_ERROR)
			{
				throw 107;
			}
			else
			{
				//Waiting for response
				ZeroMemory(buf, 4096);
				try
				{
					int bytesReceived = recv(sock, buf, 4096, 0);
					if (bytesReceived <= 0)
					{
						throw 106;
					}
					else
					{
						//Echoing response to console
						cout << "SERVER>" << string(buf, 0, bytesReceived) << endl;
					}
				}
				catch (...)
				{
					cerr << "Server has shut down u can now disconnect by \\quit" << endl;
					return SHUTDOWN;
				}
			}
		}
		catch (...)
		{
			cerr << "Server has shut down u can now disconnect by \\quit" << endl;    //if data was not sent means connection was lost
			return SHUTDOWN;
		}
	}
	return SUCCESS;
}

int main()
{
	string ipAddress = "127.0.0.1";			// IP Address of the server
	int port = 54000;						// Listening port # on the server

	// Initializing WinSock and ensuring it is successful
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	try
	{
		int wsResult = WSAStartup(ver, &data);
		if (wsResult != 0)
		{
			throw 101;
		}
	}
	catch (...)
	{
		cerr << "Cannot Initialize winsock. Quitting..." << endl;
		return 0;
	}


	// Create socket and ensure socket creation is sucessful
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	try
	{
		if (sock == INVALID_SOCKET)
		{
			throw 102;
		}

	}
	catch (...)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		try
		{
			int clean = WSACleanup();
			if (clean == SOCKET_ERROR)
			{
				throw 110;
			}
		}
		catch (...)
		{
			cerr << "Unable to release and clean up engaged resources." << endl;
		}
		return 0;
	}


	// Filling in a sock_addr structure object
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Initiating connection to server 
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	try
	{
		if (connResult == SOCKET_ERROR)
		{
			throw 108;
		}
	}
	catch (...)
	{
		cerr << "Cannot connect to server." << endl;
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
			cerr << "Unable to close socket." << endl;
		}

		try
		{
			int clean = WSACleanup();
			if (clean == SOCKET_ERROR)
			{
				throw 110;
			}
		}
		catch (...)
		{
			cerr << "Unable to release and clean up engaged resources." << endl;
		}
		return 0;
	}



	// Do-while loop to send and receive data
	char buf[4096];
	string userInput="";        //string to get user name from user(client) at runtime

	bool running = true;

	//this loop asks for username from user then sends it to server and continues to ask 
	//untill the username provided is not in the map of connected clients in server 

	while (running)
	{
		cout << "Enter Name or quit by typing \\quit>";
		getline(cin, userInput);

		if (userInput == "\\quit")          //quit and close program if user wants to cancel authentication
		{
			closesocket(sock);
			WSACleanup();
			cout << "All resources freed" << endl;
			return 0;
		}

		string temp = "\\" + userInput;   // ading / to username so that it is read as command to server specifying that data sent is userna,e
		//cout << temp << endl;
		int sendResult = send(sock, temp.c_str(), temp.size()+1, 0);

		if (sendResult != SOCKET_ERROR)
		{
			//Wait for response
			char buf[4096];
			ZeroMemory(buf, 4096);
			int bytesReceived = recv(sock, buf, 4096, 0);
			if (bytesReceived > 0)
			{
				//Echo response to console
				cout << "SERVER>" << string(buf, 0, bytesReceived) << endl;
				if (buf[0] == 'S')      //this checks if server allowed user to send data or not 'S' successfull connectiona nd username is unique too 
				{
					running = false;   //breaks the loop so that it does not asks for user name again as connected
				}
			}
		}
		else
		{
			cout << "Unable to send Client Name to Server.Server is Disconnected" << endl;   //this means server is shut downed
			return 0;
		}

	}


	if (userInput == "\\quit")
	{
		closesocket(sock);
		WSACleanup();
		return 0;
	}

	string ClientName = userInput;

	CallBackTimer Periodic(sock, ClientName);         //object of class CallBacktimer with socket and client name created
	Periodic.start(TimeInterval, updater);  //starts a single thread to send the system information fetched periodically over a time interval specified
															//updater is the function that is to be called periodically
	//above thread is detached to inside class sp control is back to main
	do 
	{
		
		getline(cin, userInput);        //command for user to quit /disconnect from server

		if (userInput == "\\quit")
		{
			int sendResult = send(sock, userInput.c_str(), userInput.size() , 0);
			if (sendResult != SOCKET_ERROR)
			{
				//Wait for response
				char buf[4096];
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived > 0)
				{
					//Echo response to console
					cout << "SERVER>" << string(buf, 0, bytesReceived) << endl;

				}
				else
				{
					cout << "Connection Lost.Server Disconnected" << endl;
					break;
				}
			}
			else
			{
				cout << "Server was shut down.Exited safely!" << endl;
				break;
			}

		}
		
	
	} while (userInput != "\\quit");
		
	//if user enters \quit connection gets disconnected above do-while loop breaks and now we clean all the reources provided


	// Gracefully close down everything
	// Closing the socket
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
		cerr << "Unable to close socket." << endl;
	}

	//Releasing engaged resources
	try
	{
		int clean = WSACleanup();
		if (clean == SOCKET_ERROR)
		{
			throw 110;
		}
		cout << "Cleaned all resources" << endl;
	}
	catch (...)
	{
		cerr << "Unable to release and clean up engaged resources." << endl;
	}
	

	//system("pause");

	return 0;
}
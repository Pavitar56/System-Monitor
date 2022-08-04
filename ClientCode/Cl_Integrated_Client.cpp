#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include "SystemInfoHeader.h"
#include "json.hpp"
#pragma comment(lib, "ws2_32.lib")

using namespace std;
using json = nlohmann::json;


void updater(SOCKET sock,string ClientName)
{
	string s = "";


	SystemInfo_JsonWriter(ClientName);
	json client_info;				//json object
	std::ifstream i("pretty.json");	//
	i >> client_info;
	s = client_info.dump(4);		//converts into string (4 - retains indentation/readability)
	char buf[4096];
	if (s.size() > 0)
	{
		//Send the text
		int sendResult = send(sock, s.c_str(), s.size() + 1, 0);
		if (sendResult != SOCKET_ERROR)
		{
			//Wait for response
			ZeroMemory(buf, 4096);
			int bytesReceived = recv(sock, buf, 4096, 0);
			if (bytesReceived > 0)
			{
				//Echo response to console
				cout << "SERVER>" << string(buf, 0, bytesReceived) << endl;

			}
		}
	}

}

int main()
{
	string ipAddress = "127.0.0.1";			// IP Address of the server
	int port = 54000;						// Listening port # on the server

	// Initialize WinSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return 0;
	}

	// Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return 0;
	}
	/*
	else
	{
		string temp = "yo";
		int sendResult = send(sock, temp.c_str(), temp.size() + 1, 0);
		if (sendResult != SOCKET_ERROR)
		{
			// Wait for response
			char buf2[4096];
			ZeroMemory(buf2, 4096);
			int bytesReceived = recv(sock, buf2, 4096, 0);
			if (bytesReceived > 0)
			{
				// Echo response to console
				cout << "SERVER> " << string(buf2, 0, bytesReceived) << endl;
			}
		}
	}
	*/
	// Do-while loop to send and receive data
	char buf[4096];
	string userInput="1234";

	do
	{
		// Prompt the user for some text
		/*
		char wel[4096];
		ZeroMemory(wel, 4096);
		int welcome = recv(sock, wel, 4096, 0);
		if (welcome != SOCKET_ERROR)
		{
			cout << wel << endl;
		}
		*/
		/*
		cout << "> ";
		getline(cin, userInput);

		if (userInput.size() > 0)		// Make sure the user has typed in something
		{
			// Send the text



			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				// Wait for response
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived > 0)
				{
					// Echo response to console
					cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
				}
			}
		}
		*/
		cout << ">";
		getline(cin, userInput);
		/*
		int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
		if (sendResult == SOCKET_ERROR)
		{
			cout << "Unable to send client name" << endl;
			return 0;
		}
		*/

		string temp = userInput;

		CallBackTimer Periodic(sock, temp);
		Periodic.start(20000, updater);
		while (true);
		/*while (true)
		{

			string s = "";


			//SystemInfo_JsonWriter();
			json client_info;				//json object
			std::ifstream i("pretty.json");	//
			i >> client_info;
			s = client_info.dump(4);		//converts into string (4 - retains indentation/readability)

			if (s.size() > 0)
			{
				//Send the text
				int sendResult = send(sock, s.c_str(), s.size() + 1, 0);
				if (sendResult != SOCKET_ERROR)
				{
					//Wait for response
					ZeroMemory(buf, 4096);
					int bytesReceived = recv(sock, buf, 4096, 0);
					if (bytesReceived > 0)
					{
						//Echo response to console
						cout << "SERVER>" << string(buf, 0, bytesReceived) << endl;

					}
				}
			}
		}
		*/

		//	} while (userInput.size() > 0);
	} while (false);

	while (true);
	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();
	return 0;
}
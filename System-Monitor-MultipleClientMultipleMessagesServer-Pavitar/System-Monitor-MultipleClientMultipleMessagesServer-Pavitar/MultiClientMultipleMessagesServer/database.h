#pragma once

#include<iostream>
#include<stdio.h>
#include<mysql.h>
#include<string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"
#include<stdio.h>
#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>

using namespace std;
using namespace rapidjson;

//info related to dabase connected

#define HOST "localhost"
#define USER "root"
#define PASS "Pavi@_8156"
#define PORT 3306


#define SHUTDOWN -1
#define SUCCESS 0

//database calss
class Database 
{
	MYSQL* connection;               //connection to mysql

public:

	void dbConnect();
	void createDb(string);
	void useDb(string);
	void createTable(string);
	void InsertIntoDb(string,string, SOCKET);
	void InsertConnectionMessage(string, string);
};


// class to read Configuration setting from file and give neccessary info
class ConfigrationSettings
{

private:
    string Filename;
    string Path;
    Document data;

public:

    int read(string Filename)
    {
        this->Filename = Filename;
        this->Path = Filename;

        try
        {
            std::ifstream f(this->Filename);

            if (f.fail())          //CHECKS IF FILE EXISTS OR NOT
            {
                throw SHUTDOWN;
            }

            IStreamWrapper isw(f);  //make it ready for rapidjson to read

            (this->data).ParseStream(isw);
            cout << "Successfully read config file" << endl;
            return SUCCESS;
        }
        catch (...)
        {
            cout << "Unable to find and parse Configuration file" << endl;
            return SHUTDOWN;
        }
    }

    string IP_getter()
    {
        try
        {
            return data["ip"].GetString();
        }
        catch (...)
        {
            cout << "Unable to find ip in Configuration file" << endl;
            return "";
        }
    }

    long long int Port_getter()
    {
        try
        {
            return data["port"].GetInt();
        }
        catch (...)
        {
            cout << "Unable to find port number in Configuration file" << endl;
            return SHUTDOWN;
        }
    }

    long long int TimeInterval_getter()
    {
        try
        {
            return data["TimeInterval"].GetInt();
        }
        catch (...)
        {
            cout << "Unable to find TimeInterval in Configuration file" << endl;
            return SHUTDOWN;
        }

    }

};
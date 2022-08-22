#pragma once
#pragma comment(lib,"pdh.lib")
#pragma comment(lib,"ws2_32.lib")

#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include<iostream>
#include <Pdh.h>
#include <PdhMsg.h>
#include<cwchar>
#include<string>
#include<vector>
#include <atlstr.h>
#include<fstream>
#include<ctime>
#include<winsock.h>
#include"json.hpp"
#include<cstdint>

using namespace std;
using json = nlohmann::json;


// these are all the functions needed to get System information

void DateTime(json&);
void GetSystemName(json&);
void MemoryUsage(json&);
__int64 Filetime2Int64(const FILETIME*);
__int64 CompareFileTime2(FILETIME, FILETIME);
void GetCpuUsePercentage(json&);
void DiskInfo(json&);
void SystemIdleTime(json&);
void SystemInfo_JsonWriter(string);


#include <functional>
#include <chrono>
#include <future>
#include <cstdio>
#define SHUTDOWN -1
#define SUCCESS 0

//this class takes care of periodic function when to start when to stop ,over how mych interval to call everything
class CallBackTimer
{
public:
    CallBackTimer(SOCKET s,string Name)   //constructor
        :_execute(false)
    {
        sock = s;
        ClientName = Name;
    }

    ~CallBackTimer() {
        if (_execute.load(std::memory_order_acquire)) {
            stop();
        };
    }

    void stop()
    {
        _execute.store(false, std::memory_order_release);
        if (_thd.joinable())
            _thd.join();
    }

    void start(int interval, std::function<int(SOCKET,string)> func)
    {
        if (_execute.load(std::memory_order_acquire)) 
        {
            stop();
        };
        _execute.store(true, std::memory_order_release);
        _thd = std::thread([this, interval, func]()
            {
                while (_execute.load(std::memory_order_acquire))
                {
                    int code=func(sock, ClientName);                   //updater function sends the stop code only if serer is shut down to stop the thread
                    if (code == SHUTDOWN)
                    {
                        _execute.store(false, std::memory_order_release);;
                    }
                    
                    std::this_thread::sleep_for(
                        std::chrono::milliseconds(interval));
                    
                    //cout << is_running() << endl;
                }
            });
        _thd.detach();
    }

    bool is_running() const noexcept {
       // cout << _execute.load(std::memory_order_acquire) << endl;
        //cout << _thd.joinable() << endl;
        return (_execute.load(std::memory_order_acquire) &&
            _thd.joinable());
    }

private:
    std::atomic<bool> _execute;  //created it atomic so that 2 threads cant access it at the same time
    std::thread _thd;
    SOCKET sock;
    string ClientName;
};


// class to read Configuration setting from file and give neccessary info
class ConfigrationSettings
{

    private:
        string Filename;
        string Path;
        json data;

    public:

         int read(string Filename)
         {
            this->Filename = Filename;
            this->Path = Filename;

            try
            {
                std::ifstream f(this->Filename);
                this->data = json::parse(f);
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
                return data["ip"];
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
                return data["port"];
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
                return data["TimeInterval"];;
            }
            catch (...)
            {
                cout << "Unable to find TimeInterval in Configuration file" << endl;
                return SHUTDOWN;
            }

        }

};

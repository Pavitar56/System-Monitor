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



class CallBackTimer
{
public:
    CallBackTimer(SOCKET s,string Name)
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

    void start(int interval, std::function<void(SOCKET,string)> func)
    {
        if (_execute.load(std::memory_order_acquire)) {
            stop();
        };
        _execute.store(true, std::memory_order_release);
        _thd = std::thread([this, interval, func]()
            {
                while (_execute.load(std::memory_order_acquire)) {
                    func(sock, ClientName);
                    std::this_thread::sleep_for(
                        std::chrono::milliseconds(interval));
                    //cout << is_running() << endl;
                }
            });
       // _thd.join();
    }

    bool is_running() const noexcept {
       // cout << _execute.load(std::memory_order_acquire) << endl;
        //cout << _thd.joinable() << endl;
        return (_execute.load(std::memory_order_acquire) &&
            _thd.joinable());
    }

private:
    std::atomic<bool> _execute;
    std::thread _thd;
    SOCKET sock;
    string ClientName;
};

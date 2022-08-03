#include"SystemInfoHeader.h"

/*

    Date and time

*/
void DateTime(json& SystemInfo)
{
    time_t now = time(0);
    const char* dt = ctime(&now);

    cout << "Todays Date is " << dt << endl;
    SystemInfo["Date and Time"] = dt;


    return;

}

/*

    System Name

*/
void GetSystemName(json& SystemInfo)
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    char name[MAX_PATH];
    int8_t temp = gethostname(name, MAX_PATH);   ///0=success else failure 
    cout << temp << endl;
    if (temp == 0)
    {
        cout << name << endl;

        //adding to json
        SystemInfo["System Name"] = name;
    }
    else
    {
        cout << WSAGetLastError() << endl;
    }

    WSACleanup();
    return;
}

/*

    Memory Usage

*/
void MemoryUsage(json& SystemInfo)
{
    MEMORYSTATUSEX mem = { 0 };

    mem.dwLength = sizeof(mem);

    int8_t Error_Checker = GlobalMemoryStatusEx(&mem);

    if (Error_Checker == 0) //0 means failure
    {     
        cout << "Failed to memory status " << GetLastError();
        return;
    }

    cout << "Memory in use:" << mem.dwMemoryLoad << "%" << endl;
    cout << "Total physical memory: " << mem.ullTotalPhys / 1024 << endl;
    cout << "Free physical memory: " << mem.ullAvailPhys / 1024 << endl;

    //adding to json

    SystemInfo["RamInfo"]["Total(in KB)"] = mem.ullTotalPhys / 1024;
    SystemInfo["RamInfo"]["Free(in KB)"] = mem.ullAvailPhys / 1024;
    SystemInfo["RamInfo"]["Usage(in %)"] = mem.dwMemoryLoad;

    return;

}

/*

    CPU Usage

*/
__int64 Filetime2Int64(const FILETIME* ftime)
{
    LARGE_INTEGER li;
    li.LowPart = ftime->dwLowDateTime;
    li.HighPart = ftime->dwHighDateTime;
    return li.QuadPart;
}

__int64 CompareFileTime2(FILETIME preTime, FILETIME nowTime)
{
    return Filetime2Int64(&nowTime) - Filetime2Int64(&preTime);
}


void GetCpuUsePercentage(json& SystemInfo)
{
    FILETIME preIdleTime;
    FILETIME preKernelTime;
    FILETIME preUserTime;
    GetSystemTimes(&preIdleTime, &preKernelTime, &preUserTime);

    Sleep(1000);

    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;
    GetSystemTimes(&idleTime, &kernelTime, &userTime);

    int64_t idle = CompareFileTime2(preIdleTime, idleTime);
    int64_t kernel = CompareFileTime2(preKernelTime, kernelTime);
    int64_t user = CompareFileTime2(preUserTime, userTime);

    if (kernel + user == 0)
        return;
    //(total time-idle time)/total time = time occupied by cpu is the usage rate 
    float Cpu_Usage = float(100.0 * (kernel + user - idle) / (kernel + user));

    cout << Cpu_Usage << endl;

    //adding to json
    SystemInfo["Cpu_Usage(in%)"] = Cpu_Usage;

    return;
}

/*

    HDD Utilization

*/

void DiskInfo(json& SystemInfo)
{

    // getting total disks/drives available in system

    vector<wchar_t*> All_Drives;
    wchar_t LogicalDrives[MAX_PATH] = { 0 };
    DWORD Total_Drives = GetLogicalDriveStringsW(MAX_PATH, LogicalDrives);

    if (Total_Drives == 0)
    {
        wprintf(L"Failed to get drive names %ld", GetLastError());
        return;
    }

    if (Total_Drives > 0 && Total_Drives <= MAX_PATH)
    {

        wchar_t* SingleDrive = LogicalDrives;
        int32_t i = 0;                                //counter for drives
        while (*SingleDrive)
        {
            wprintf(L"%ls\n", SingleDrive);
            All_Drives.push_back(SingleDrive);

            //adding to json

            wstring temp(SingleDrive);
            string str(temp.begin(), temp.end());
            // cout << typeid(str).name() << endl;
            SystemInfo["DiskInfo"]["TotalDrives"][i++] = str;

            SingleDrive += wcslen(SingleDrive) + 1;
        }
        SystemInfo["Total_Num_Of_Drives"] = i;
    }
    else
    {
        cout << "Number of drives are greater than available size of buffer variable" << endl;
    }


    //Extracting info of each disk/drive available on system
    uint64_t TotalDiskSpace=0, TotalDiskFreeSpace=0;
    vector<wchar_t*>::iterator iter = All_Drives.begin();

    for (iter; iter != All_Drives.end(); iter++)
    {
        uint64_t freeCall,
            total,
            free;

        int32_t CurrentDriveInfo = GetDiskFreeSpaceExW(*iter, (PULARGE_INTEGER)&freeCall,
            (PULARGE_INTEGER)&total, (PULARGE_INTEGER)&free);

        if (CurrentDriveInfo == 0)
        {

            wprintf(L"Failed to get free disk space %ld", GetLastError());
            return;
        }

        wprintf(L"Available space to caller: %I64u MB\n", freeCall / (1024 * 1024));
        wprintf(L"Total space: %I64u MB\n", total / (1024 * 1024));
        wprintf(L"Free space on drive: %I64u MB\n", free / (1024 * 1024));

        wstring temp(*iter);
        string CurrentDriveName(temp.begin(), temp.end());

        //adding to json

        SystemInfo["DiskInfo"][CurrentDriveName]["Total Space(in MB)"] = total / (1024 * 1024);
        SystemInfo["DiskInfo"][CurrentDriveName]["Free Space(in MB)"] = free / (1024 * 1024);

        TotalDiskSpace = TotalDiskSpace + ( total / ( 1024 * 1024 ) );
        TotalDiskFreeSpace = TotalDiskFreeSpace + ( free / (1024 *1024 ) );
        //cout << to_string(freeCall / (1024 * 1024)) << endl;

    }
    SystemInfo["TotalDiskSpace(in MB)"] = TotalDiskSpace;
    SystemInfo["TotalDiskFreeSpace(in MB)"] = TotalDiskFreeSpace;
}

void SystemIdleTime(json& SystemInfo)
{
    LASTINPUTINFO plii;     //plii.dwTime gives the timestamp date of last input
    plii.cbSize = sizeof(LASTINPUTINFO);
    plii.dwTime = 0;

    /*

        GetTickCount64() :-This return value is the number of milliseconds
                        that have elapsed since the system was started
     */

    if (GetLastInputInfo(&plii) != 0)
    {
        uint64_t IdleTime_In_ms = GetTickCount64() - plii.dwTime;

        cout << "Last activity  : " << IdleTime_In_ms << " (ms)" << endl;

        //adding to json
        SystemInfo["System Idle Window(in sec)"] = IdleTime_In_ms / 1000;  //converting to sec
    }
    else 
    {
        cout << "GetLastInputInfo ERROR" << endl;
    }

    cout << GetTickCount64() << " " << plii.dwTime << endl;

}


/*

Json writer
call this function only in main to produce json file with neccesaary details

*/
void SystemInfo_JsonWriter(void)
{
    json SystemInfo;


    DateTime(SystemInfo);
    GetSystemName(SystemInfo);
    MemoryUsage(SystemInfo);
    GetCpuUsePercentage(SystemInfo);

    DiskInfo(SystemInfo);
    SystemIdleTime(SystemInfo);


    std::ofstream o("pretty.json");
    o << std::setw(4) << SystemInfo << std::endl;



    return;
}
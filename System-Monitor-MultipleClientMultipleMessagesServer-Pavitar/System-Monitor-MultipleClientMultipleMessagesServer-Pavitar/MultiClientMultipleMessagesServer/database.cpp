#include"database.h"


using namespace std;

using namespace rapidjson;

int qstate;                  //keeps a track wheather query is succesfully executed or not



void Database::dbConnect()
{

    connection = mysql_init(0);

    connection = mysql_real_connect(connection, HOST, USER, PASS, NULL, PORT, NULL, 0);  //connecting to database with correct user pass(can be changed in database.h)
    
    try
    {
        if (connection)
        {
            puts("Successful connection to database");
        }
        else
        {
            throw 100;
        }

    }
    catch (...)
    {
        puts("Connection to database has failed");
    }
}



void Database::createDb(string dbName)        //creating database
{
    string query = "CREATE DATABASE IF NOT EXISTS " + dbName + ";";

    const char* q = query.c_str();

    qstate = mysql_query(connection, q);
    try
    {
        if (!qstate)
        {
            cout << "Database has been created successfully if it did not exist." << endl;
        }
        else
        {
            throw 101;
        }
    }
    catch (...)
    {
        cout << "Query Database creation failed:" << mysql_error(connection) << endl;
    }
}

void Database::useDb(string dbName)        //using the database whose name is provided
{
    string query = "use " + dbName + ";";

    const char* q = query.c_str();

    qstate = mysql_query(connection, q);
    try
    {
        if (!qstate)
        {
            cout << "Using " + dbName << endl;

        }
        else
        {
            throw 102;
        }
    }
    catch (...)
    {
        cout << "Query using db failed:" << mysql_error(connection) << endl;
    }

}



void Database::createTable(string tableName)  //creating table with column names
{

    string query = "CREATE TABLE IF NOT EXISTS " + tableName +
        " ( id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,SocketNumber varchar(32) , MachineName varchar(32) , System_Name varchar(32), TotalRam varchar(32) , FreeRam varchar(32) , RamUsage varchar(32) , System_Idle_Window varchar(32), Date_and_Time varchar(32) , Cpu_Usage varchar(32) , TotalDiskSpace varchar(32) , FreeDiskSpace varchar(32) , ErrorMessage TEXT ) ";

    const char* q = query.c_str();

    qstate = mysql_query(connection, q);

    try
    {
        if (!qstate)
        {
            cout << "Table has been created successfully if not existed" << endl;
        }
        else
        {
            throw 103;
        }
    }
    catch (...)
    {
        cout << "Query Table creation failed:" << mysql_error(connection) << endl;
    }
}

void Database::InsertConnectionMessage(string tableName, string ErrorMessage)      //updater specifically for ErrorMessage colum only
{
    string query = "INSERT INTO " + tableName + " (ErrorMessage) VALUES ( \"" + ErrorMessage + "\"" + ")";

    const char* q = query.c_str();

    qstate = mysql_query(connection, q);

    try
    {
        if (!qstate)
        {
            cout << ErrorMessage << endl;
        }
        else
        {
            throw 104;
        }
    }
    catch (...)
    {
        cout << "Query New Connection failed:" << mysql_error(connection) << endl;
    }
}


void Database::InsertIntoDb(string tableName, string inputString, SOCKET sock) //inserting all the data into db 
{

    const char* json = inputString.c_str();
    Document d;
    d.Parse(json);                                  //parsing data string to json object for easier acces of all elements in data


    //converting all the json object elements in string
    string systemName = d["System Name"].GetString();

    int t = d["RamInfo"]["Free(in KB)"].GetInt();
    string ramFreeSpace = to_string(t);


    float cpuUsageStr = d["Cpu_Usage(in%)"].GetFloat();
    string cpuUsage = to_string(cpuUsageStr);


    string dateAndTime = d["Date and Time"].GetString();


    int ramTotal = d["RamInfo"]["Total(in KB)"].GetInt();
    string totalram = to_string(ramTotal);


    int ramUsage = d["RamInfo"]["Usage(in %)"].GetFloat();
    string testString = to_string(ramUsage);

    int b = d["System Idle Window(in sec)"].GetFloat();
    string systemIdleWindow = to_string(b);

    string MachineName = d["MachineName"].GetString();

    int freeDisk = d["TotalDiskFreeSpace(in MB)"].GetInt();
    string freeDiskSpace = to_string(freeDisk);

    int totalDisk = d["TotalDiskSpace(in MB)"].GetInt();
    string totalDiskSpace = to_string(totalDisk);

    ostringstream ss;
    ss << sock;
    string strOut = ss.str();

    //insert query
    string query = "INSERT into " + tableName + " (SocketNumber , MachineName , System_Name , TotalRam , FreeRam , RamUsage , System_Idle_Window , Date_and_Time , Cpu_Usage , TotalDiskSpace , FreeDiskSpace  ) VALUES ( \"" + strOut + "\"," + "\"" + MachineName + "\"," + "\"" + systemName + "\"," + "\"" + totalram + "\"" + ",\"" + ramFreeSpace + "\"," + "\"" + testString + "\"," + "\"" + systemIdleWindow + "\"," + "\"" + dateAndTime + "\"," + "\"" + cpuUsage + "\"," + "\"" + totalDiskSpace + "\"," + "\"" + freeDiskSpace + "\"" + ");";

    const char* q = query.c_str();
    qstate = mysql_query(connection, q);  //executing insert query

    try
    {
        if (!qstate)
        {
            string ErrorMessage = "Data added successfully for " + MachineName;
            string query = "UPDATE " + tableName + " SET ErrorMessage =\"" + ErrorMessage + "\"" + " where id = (SELECT last_insert_id());";

            const char* q = query.c_str();
            qstate = mysql_query(connection, q);

            try
            {
                if (!qstate)
                {
                    cout << "Data added successfully for " + MachineName << endl;
                }
                else
                {
                    throw 106;
                }

            }
            catch (...)
            {
                cout << "Query data additon failed for " + MachineName + ":" << mysql_error(connection) << endl;
            }
        }
        else
        {
            throw 105;
        }

    }
    catch (...)
    {
        string ErrorMessage = "Data additon failed for " + MachineName;
        string query = "UPDATE " + tableName + " SET ErrorMessage=\"" + ErrorMessage + "\"" + " where id =(SELECT last_insert_id());";

        const char* q = query.c_str();
        qstate = mysql_query(connection, q);

        try
        {
            if (!qstate)
            {
                cout << "Data additon failed for " + MachineName << endl;
            }

        }
        catch (...)
        {
            cout << "Query data additon failed for " + MachineName + ":" << mysql_error(connection) << endl;
        }
    }

}
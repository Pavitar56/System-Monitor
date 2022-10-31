
## System Monitor
A central monitoring system built using basic client-server model to collect system information from multiple nodes over a network. The server side receives the data from the client periodically.

#### The server is directly connected to the database, the GUI is also connected to database.


### This system information is sent periodically to a server to update about its state with following parameters: 
* Id
* Socket Number
* User Name
* System Name
* Total RAM
* Free RAM
* RAM usage
* System idle window
* Date and time
* CPU usage
* Total Disk Space
* Free Disk Space
* Error Message

### Pre-Requisites to run the server and successfully connect to the database.

1. Download and install MySQL Installer ​

2. Using MySQL Installer install: ​

     a. MySQL Community Server 8.0 ​

     b. MySQL Connector/C++ version 8.0 ​

3. Update the relevant include and lib directories in Visual Studio Community ​

    1. Go to Project Properties -> C/C++ -> General -> Additional Include Directories and update​

         a. C:\Program Files\MySQL\Connector C++ 8.0\include\jdbc\cppconn ​

         b. C:\Program Files\MySQL\MySQL Server 8.0\include ​

    2. Go to Project Properties -> Linker -> General -> Additional Library Directories and update​

        a. C:\Program Files\MySQL\Connector C++ 8.0\lib64\vs14 ​

        b. C:\Program Files\MySQL\MySQL Server 8.0\lib ​

    3. Go to Project Properties > Linker > Input > Additional Dependencies and update​

        a. mysqlcppconn.lib ​

        b. libmysql.lib​

4. Code, build, run ​

   a. Copy libmysql.dll from C:\Program Files\MySQL\MySQL Server 8.0\lib to the executable directory ​

   b. Copy libcrypto-1_1-x64.dll and libssl-1_1-x64.dll from C:\Program Files\MySQL\MySQL Server 8.0\bin 
      to the server executable directory.
      

### Steps to start the Server:
1. Start the SystemMonitor.exe , and enter the credentials.

![Input](https://user-images.githubusercontent.com/68504084/184081125-f2dccf4f-eb2d-4466-a708-5f6ffe5e6d3d.JPG)

2. Start the server by clicking the "start Server" button. 

![MicrosoftTeams-image (1)](https://user-images.githubusercontent.com/77383378/183707866-622efab3-8766-46ff-bf37-50491500945d.png)

2. Start the ClientCode.exe.
3. Enter the user Name into the cmd.

![Input](https://user-images.githubusercontent.com/68504084/183834011-963fe748-66a3-45f3-bc07-593b090fe58b.JPG)

4. Select the appropriate data / action to be performed from the GUI , to display the data.

![Input](https://user-images.githubusercontent.com/68504084/183834009-7a55e4de-96e7-4c19-bbeb-b7898a0e746f.JPG)
![Input](https://user-images.githubusercontent.com/68504084/183834003-4c66a3c6-b5c6-4694-95ff-8cad42dd69e9.JPG)

5. Click the "Stop the server" button to stop the server or type "\quit" in terminal to stop the client from sending data to the server.


#### The server receives the data from the client every 20 seconds(can be changed to any seconds by chaning "TimeInterval" macro in ClientCode) in JSON format , which then is inserted in the MySQL database using appropriate query.
#### The client can stop sending the data by typing "\quit" in console and the server can be stopped by clicking the "Stop the server" button or by typing \quit in server console.

#### Also note that in order to run Server from UI itself u need to change ServerApplicationPath macro in UI to path where u have saved ServerApplication otherwise start server from console itself.


# Server Side

## System Monitor
A central monitoring system built using basic client-server model to collect system information from multiple nodes over a network. The server side receives tge data from the client periodically.


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

#### Make sure all the pre requisites are done ( refer the integerated readme).
     
### Steps to start the Server:
1. First start the server.exe , if the server is started without any errors then a "Successfully connected to the database" message will be shown in the terminal.
2. After successful connection , start the client.exe.
3. The server can be started from the UI too.
4. The client is connected to the server and sends the data periodically .
5. The server is connected to the database , and the UI is connected to the database too.



#### The server receives the data from the client every 20 seconds in JSON format , which then is inserted in the MySQL database using appropriate query.
#### The client can stop sending the data by typing "\quit" and the server can be stopped by clicking the "Stop the server" button.



### PROJECT CONTRIBUTORS:-
#### System Interaction and UI Team
* Pavitar Goyal
#### Socket Programming Team
* Esha Sali
* Ishika Bhatt
#### Database Team
* Nizamuddin Syed

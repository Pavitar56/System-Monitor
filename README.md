# Client Side

## System Monitor
A central monitoring system built using basic client-server model to collect system information from multiple nodes over a network. The client side basically sends the data of the node periodically to the server .

### The data fetched by the client and sent to the server are as follows :
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

### Steps to open the client:
1. First make sure the server is running , if not , start the server ( refer the server Readme to start the server ).
2. Start the Client.exe
3. Insert / type the User name as desired but the user should only enter unique user name inorder to connect to the server , if it doesn't he has to enter it again.. 
4. The client will start sending the data of the client periodically to the server .
5. If there is any error it will be displayed accordingly.
6. To quit / stop the client ( stop the client from sending data to the server ) just type  "\quit "

#### Multiple instances of client can be started , if the user enters a pre-existing username/clientID that is active , user will not be able to connect and send data.(has to try another unique username).
#### The client in our case sends the above mentioned data every 20 seconds to the server once connected and after inserting the unique User Name.
#### The client must insert unique name inorder to get started (the name inserted must not be present among the online client ).

### PROJECT CONTRIBUTORS:-
#### System Interaction and UI Team
* Pavitar Goyal
#### Socket Programming Team
* Esha Sali
* Ishika Bhatt
#### Database Team
* Nizamuddin Syed

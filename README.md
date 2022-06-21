
# Chat Room Server

The implementation of the Chat Room Server is written in CPlusPlus language.
The implementaion is done using sockets and multi-threading.
The Chat Room Server works on Linux based Operating System.



## Deployment of the Server

Since we have implemented the Chat Room server in CPlusPlus language and hence the installation of
g++ becomes a prerequisite. 
In order to install gcc compiler -

On windows - run the following command-

```bash
  sudo apt install gcc
```
On mac if you have homebrew preinstalled then run the following command -

```bash
  brew install gcc
```
And in this way we can insatll gcc on our system.

Now, In order to deploy the Chat Room Server, first we have to compile the server.cpp and 
client.cpp files by commands:

```bash
  g++ -lpthread -o server server.cpp
  g++ -lpthread -o client client.cpp
```
This will create two executable object files for server.cpp and client.cpp which are named (server and client respectively).

After compiling the files, we run the server by the executing the executable file 'server' by the following command:

```bash
./server
```

After that, clients can join the server by executing the following command:

```bash
./client
```


## Internal Working 

The chat server conists of the server side and the client side which can consist of multiple clients which are connected to each other
through sockets. The port to which both the server sockets and client sockets connect has been pre-set to 10000.  


### Server

- The server side is designed to control how a client interacts with server as well as with the other clients. For that, primarily we need functions in order to add as well as remove the clients from the queue as we can have multiple clients. 

- I have used a broadcast_message function , whos function is to send the message of a client to all other clients and the server. 

- Since we have used multi threading in the server, hence it became necessary to use mutex locks during the addition and removal of the clients from the list. 

- On runnning the server, intially the socket is created and after the bind socket and listen functions are executed the server is opened for client processes to join. 

- When any client attempts to join the server a new thread is created and the client is added to the queue of active users.

- Further, when a valid name is entered, the client becomes eligible to interact in the chat room. 

- Then, all the messages of the client are sent with the broadcast_message function to other clients and the server until the client sends the message exit.

- On doing so, the client is removed from the server.

### Client

- The client side primarily controls the sending and recieving of the messages.

- It consists of two functions handler_send and handler_recieve. 

- When the server is active, on running the client and entering a valid name, the socket is created.
 
- After connecting to the socket, the name is sent to the server and the client is ready to interact with the server and all other clients as well as the server recieve a message that the client has joined the chat room.

- Whenever a message is sent by any other client, the name of the sending client along with the message is diplayed on the client's terminal.
 
- If the client writes a message and unless the message is not "exit" the message is broadcasted to all the users. 

- On writing exit, the client is removed from the server and all the other clients and the server recieve a message for the same.

## Video Demo

https://user-images.githubusercontent.com/83119859/174869957-945ae990-18c7-419b-99cf-581de7c39a46.mp4

## Learnings

- In the course of this project, I have learned the working of sockets and connecting as well as sending data between different sockets. 

- I have also understood how threads work as well as the concept of multi-threading and mutex locks which have been implemented through POSIX threads in the chat server.

## Additional Tasks
 
- I have used Threads for sending and recieving messages.

- From the basics of socket programming model using multi-threading, the implementation of a real time chat server has been done.

- The concept of Mutex/locks have been used while adding and removing any client from the list of active users , basically this addition and removal is done from the chat room for proper synchronization.
  
- Use of a keyword ("#exit") to remove a client from the server.

- The joining and leaving of clients is color coded.

## References

- https://www.geeksforgeeks.org/socket-programming-cc/
- https://dzone.com/articles/parallel-tcpip-socket-server-with-multi-threading 
- https://www.geeksforgeeks.org/multithreading-c-2/

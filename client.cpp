#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <signal.h>
#include <mutex>

#define NUM_COLORS 6
#define MAX_LEN 200

using namespace std;

bool signal_for_exit=false;

thread thr_send, thr_receive;
int client_socket;
string def_col="\033[0m";
string colors[]={"\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m"};


void send_message(int client_socket);
void receive_message(int client_socket);
void handler_ctrl_c(int signal);
string color(int color_code);
int Text_erasing(int value);


int main()
{
	if((client_socket=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket: ");
		exit(-1);
	}

	struct sockaddr_in client;
	client.sin_family=AF_INET;
	client.sin_port=htons(10000); // Port no. of server
	client.sin_addr.s_addr=INADDR_ANY;
	bzero(&client.sin_zero,0);

	if((connect(client_socket,(struct sockaddr *)&client,sizeof(struct sockaddr_in)))==-1)
	{
		perror("connect: ");
		exit(-1);
	}
	
	signal(SIGINT, handler_ctrl_c);
	char name[MAX_LEN];
	
	cout<<"Enter your name : ";
	
	cin.getline(name,MAX_LEN);
	send(client_socket,name,sizeof(name),0);

	cout << colors[NUM_COLORS-1]<<"\n\t|| ----------- WELCOME TO THE CHAT ROOM ----------- ||\n"<<def_col;

	thread t1(send_message, client_socket);
	thread t2(receive_message, client_socket);

	thr_send=move(t1);
	thr_receive=move(t2);

	if(thr_send.joinable()){
		thr_send.join();
	}
	if(thr_receive.joinable()){
		thr_receive.join();
	 }
	return 0;
}


// The function for sending the message to everyone 
void send_message(int client_socket)
{
	while(1)
	{
		cout<<colors[1]<<"You : "<<def_col;
		
		char str[MAX_LEN];
		cin.getline(str,MAX_LEN);
		send(client_socket,str,sizeof(str),0);
		
		if(strcmp(str,"#exit")==0)
		{
            		signal_for_exit=true;
			thr_receive.detach();	
			close(client_socket);
			return;
		}	
	}		
}

// The function for receiving the message to client
void receive_message(int client_socket)
{
	while(1)
	{
		if(signal_for_exit){
			return;
		}
			
		char name[MAX_LEN], str[MAX_LEN];
		int color_code;
		int bytes_received=recv(client_socket,name,sizeof(name),0);
		
		if(bytes_received<=0){
			continue;
		}
			
		recv(client_socket,&color_code,sizeof(color_code),0);
		recv(client_socket,str,sizeof(str),0);
		
		Text_erasing(6);
		
		if(strcmp(name,"#NULL")!=0){
			cout<<color(color_code)<<name<<" : "<<def_col<<str<<endl;
		}
			
		else{
			cout<<color(color_code)<<str<<endl;
		}
		cout<<colors[1]<<"You : "<<def_col;
		fflush(stdout);
	}
}

// The Handler for "Ctrl + C"
void handler_ctrl_c(int signal) 
{
	char str[MAX_LEN]="#exit";
	send(client_socket,str,sizeof(str),0);
        signal_for_exit=true;
	thr_send.detach();
	thr_receive.detach();
	close(client_socket);
	exit(signal);
}


// The function to erase the text from terminal
int Text_erasing(int value)
{
	char back_space=8;
	for(int i=0; i<value; i++)
	{
		cout<<back_space;
	}
	return 0;	
}

// The color code
string color(int color_code)
{
	return colors[color_code%NUM_COLORS];
}

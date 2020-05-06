#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<string.h>
#include<iterator>
#include<map>
using namespace std;

map <int,std::string> processes;

class server{
public:
  int s,status,lstatus,astatus,clilen,port;
  struct sockaddr_in address,clientaddr;
  void create(int id){
    port=8000+id;
    address.sin_family=AF_INET;
    address.sin_port=htons(port);
    address.sin_addr.s_addr=INADDR_ANY;
    s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(s>0)
      printf("socket created successfully");
    status=bind(s,(struct sockaddr*)&address,64 );
    if(status>=0)
      printf("\nBind Successful\n");
    lstatus=listen(s,10);
    clilen=sizeof(clientaddr);
    if (lstatus>-1)
      printf("listening");
    astatus=accept(s,(struct sockaddr*)&clientaddr,(socklen_t*)&clilen);
    if(astatus>-1)
      cout<<"\nPort "<<port<<" says Accept Successful\n";
    else{
      printf("Unsuccessful\n");
    }

  }
};
class client{
public:
  int status,s,port;
  struct sockaddr_in address,clientaddr;
  void create(int id){
    port=8000+id;
    address.sin_family=AF_INET;
    address.sin_port=htons(port);
    address.sin_addr.s_addr=INADDR_ANY;
    s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(s>0)
    printf("socket created successfully");
    status = connect(s,(struct sockaddr*)&address, 64);
    //printf("%d",status);
    if(status>-1){
      printf("\nConnection Successful\n");
    }

    processes[id]= "p_name";
  }
};
class message{
public:
  int message_id,forward=0,source_id,destination_id;

  void message_read(int s_id,int d_id,int p_id){
    destination_id=d_id;
    source_id=s_id;
    message_id=p_id;
  }

  void message_print(){
    cout<<"\nThe Source Process is "<<source_id<<processes[source_id]<<"\nThe destination process is "<<destination_id<<processes[destination_id]<<"\nThe message_id is "<<message_id<<"\n\n";
  }
  void message_send(int astatus){
    //cout<<source_id
    send(astatus, &source_id, sizeof(int), 0);
    if(source_id!=0 && destination_id!=0){
      forward=1;
    }
    else{
      forward=0;
    }
    send(astatus, &destination_id, sizeof(int), 0);
    send(astatus, &message_id, sizeof(int), 0);
    send(astatus,&forward,sizeof(int),0);
  }
  void message_recv(int s){
    //cout<<"hi1\n";
    //char temp[100];
    // char source[100];
    recv(s,&source_id,sizeof(int),0);
    // cout<<source;
    //source_id=atoi((char*)source_id);
    //cout<<"hi2\n"<<source;
    // char destination[100];
    recv(s,&destination_id,sizeof(int),0);
    // destination_id=atoi(destination);
    //cout<<"hi3\n";
    // char temp[100];
    recv(s,&message_id,sizeof(int),0);
    // cout<<temp<<"hi\n";
    // message_id=atoi(temp);
    //cout<<"hi4\n";
    recv(s,&forward,sizeof(int),0);
  }
};

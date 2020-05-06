#include<arpa/inet.h>
#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include "basics.cpp"
#include<iterator>
using namespace std;



int main()
{
  processes.insert(pair<int,std::string>(0, "Kernel"));
  message sendmessage,recmes;
  server s[100];
  s[1].create(1);
  sendmessage.message_read(0,s[1].port-8000,404);
  sendmessage.message_send(s[1].astatus);
  s[2].create(2);
  sendmessage.message_read(0,s[1].port-8000,414);
  sendmessage.message_send(s[2].astatus);
  recmes.message_recv(s[1].astatus);
  if (recmes.forward==1){
    cout<<"forwarding "<<recmes.destination_id;
    recmes.message_send(s[recmes.destination_id].astatus);
  }
  else
  recmes.message_print();
  return(0);
}

#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<iterator>
#include<arpa/inet.h>
#include<unistd.h>
#include "basics.cpp"
using namespace std;
char p_id[100]="process1";
int main()
{
  message sendmsg,revmes;
  client p;
  p.create(2);
  revmes.message_recv(p.s);
  revmes.message_print();
  revmes.message_recv(p.s);
  revmes.message_print();
  //do{fgets(sendmsg,20,stdin);
  //int len=strlen(sendmsg);
  //sendmsg[len-1]='\0';
  //send(s,sendmsg,20,0);
  //recv(s,revmes,100,0);
  //revmes.message_print();
  int cstatus=close(p.s);
  return(0);

}

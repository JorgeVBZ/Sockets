#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  char *host, **names, **addrs;
  struct hostent *hostinfo;

  //Set the host to the argument supplied with the getname call, or by default to the user’s machine
  if(argc == 1) 
  {
    char myname[256];
    gethostname(myname, 255);
    host = myname;
  }
  else
    host = argv[1];

  //Call gethostbyname and report an error if no information is found
  hostinfo = gethostbyname(host);

  if(!hostinfo)
  {
    fprintf(stderr, "cannot get info for host: %s\n", host);
    exit(1);
  }

  //Display the hostname and any aliases that it may have
  printf("results for host %s:\n", host);
  printf("Name: %s\n", hostinfo -> h_name);
  printf("Aliases:");
  names = hostinfo -> h_aliases;
  while(*names) 
  {
    printf("%s", *names);
    names++;
  }
  printf("\n");

  //Warn and exit if the host in question isn’t an IP host
  if(hostinfo -> h_addrtype != AF_INET) 
  {
    fprintf(stderr, "not an IP host!\n");
    exit(1);
  }
  //Otherwise display the IP adress(es)
  addrs = hostinfo -> h_addr_list;
  while(*addrs) 
  {
    printf("%s", inet_ntoa(*(struct in_addr *)*addrs));
    addrs++;
  }
  printf("\n");
  exit(0);

  /*Alternatively, you could use the function gethostbyaddr to determine which host has a given IP address.
    You might use this in a server to find out where the client is calling from.*/

}

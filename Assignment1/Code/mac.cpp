#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <stdio.h>
  
int main() {
  struct ifreq ifr;
  int s;
  if ((s = socket(AF_INET, SOCK_STREAM,0)) < 0) {
    perror("socket");
    return -1;
  }
  
  strcpy(ifr.ifr_name, "eno1");
  if (ioctl(s, SIOCGIFHWADDR, &ifr) < 0) {
    perror("ioctl");
    return -1;
  }
  
  unsigned char *hwaddr = (unsigned char *)ifr.ifr_hwaddr.sa_data;
  printf("%02X:%02X:%02X:%02X:%02X:%02X\n", hwaddr[0], hwaddr[1], hwaddr[2],
                                          hwaddr[3], hwaddr[4], hwaddr[5]);
  close(s);
  
  return 0;
}

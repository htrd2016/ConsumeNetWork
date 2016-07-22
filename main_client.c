#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char ** argv)
{
  char server_ip[64];
  int server_port;
  size_t buffer_size;
  int sock = 0;
  char *buffer;

  struct sockaddr_in addr;
  if(argc<4)
  {
    printf("use age<path><server ip><server port><buffer size>\n");
    return -1;
  }

  strcpy(server_ip, argv[1]);
  server_port = atoi(argv[2]);
  buffer_size = strtoull(argv[3], 0, 10);

  memset(&addr , 0, sizeof(struct sockaddr));
  printf("%s %d %ld\n", server_ip, server_port, buffer_size);

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock<=0)
  {
    printf("error:%s\n", strerror(errno));
    return -1;
  }
  
  addr.sin_family = AF_INET;
  addr.sin_port = htons(server_port);
  addr.sin_addr.s_addr = inet_addr(server_ip);
  if(connect(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) <0)
  {
    printf("%s\n", strerror(errno));
    close(sock);
    return -1;
  }  

  buffer = calloc(buffer_size, 1);
  for(;;)
  {
    if(0>=send(sock, buffer, buffer_size, 0))
    {
      printf("%s\n", strerror(errno));
      free(buffer);
      return -1;
    }
  }
  free(buffer);
  return 0;
}

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

int main(int argc, char *argv[])
{
  int listen_port;
  size_t buffer_size;
  char *buffer;
  int sock;
  struct sockaddr_in addr;
  int client_sock;
  unsigned int len = sizeof(addr);

  size_t recv_len = 0;

  if(argc<3)
  {
    printf("use age<path><port to listen><buffer size>\n");
    return -1;
  }

  listen_port = atoi(argv[1]);
  buffer_size = strtoull(argv[2], 0, 10);
  sock = socket(PF_INET, SOCK_STREAM, 0);
  if(sock<=0)
  {
    printf("%s\n", strerror(errno));
    return -1;
  }

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(listen_port);  

  if(bind(sock, (struct sockaddr*)&addr, sizeof(addr))<0)
  {
    printf("%s\n", strerror(errno));
    close(sock);
    return -1;
  }

  if(listen(sock, 1)<0)
  {
    printf("%s\n", strerror(errno));
    close(sock);
    return -1;
  }

  buffer = calloc(buffer_size, 1);
  for(;;)
  {
    client_sock = accept(sock, (struct sockaddr*)&addr, &len);
    printf("new connection ...\n");
    if(client_sock<=0)
    {
      printf("%s\n", strerror(errno));
      close(sock);
      free(buffer);
      return -1;
    }
    for(;;)
    {
      if((recv_len=recv(client_sock, buffer, buffer_size, 0))<=0)
      {
        printf("%s\n", strerror(errno));
        close(client_sock);
        break;
      }

      printf("recv:%ld\n", recv_len);
    }
  }

  close(client_sock);
  close(sock);
  free(buffer);
  return 0;
}

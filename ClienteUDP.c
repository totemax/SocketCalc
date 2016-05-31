#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sockaddr_in dirServ;

int port;

int sk, rec;

int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error al invocar el programa. Formato llamada server [port]. Ej: cliente 7777.\n");
        exit(1);
    } else {
        port = atoi(argv[1]);
        printf("Se a enviar en puerto %d\n", port);
    }

    sk=socket (AF_INET, SOCK_DGRAM,0);
    

    exit(0);
}

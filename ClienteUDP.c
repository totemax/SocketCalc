#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sockaddr_in dirServ;

char mensajeEnv[3];
char mensajeRec[2];

int port;

int sk, rec;

int main (int argc, char *argv[]) {
    if (argc < 5) {
        printf("Error al invocar el programa. Formato llamada client [port] [operacion] [operando1] [operando2]. Ej: cliente 7777 + 5 2.\n");
        printf("Nota: El parámetro multiplicación '*' se deberá enviar con el caracter backslash delante '\\'\n");
        exit(1);
    } else {
        port = atoi(argv[4]);
        printf("Se va a enviar en puerto %d\n", port);
        mensajeEnv[0] = *argv[1];
        mensajeEnv[1] = *argv[2];
        mensajeEnv[2] = *argv[3];
    }

    sk=socket (AF_INET, SOCK_DGRAM,0);
    dirServ.sin_family= AF_INET;
    dirServ.sin_addr.s_addr= inet_addr ("127.0.0.1");
    dirServ.sin_port= htons(port);

    sendto(sk,mensajeEnv,strlen(mensajeEnv),0,(struct sockaddr*)&dirServ,sizeof(dirServ));

    int tam= sizeof(dirServ);

    rec= recvfrom(sk,mensajeRec,sizeof(mensajeRec), 0, (struct sockaddr*)&dirServ, (unsigned*) &tam);
    mensajeRec[rec] = '\0';
    printf("resultado: %s\n", mensajeRec);

    exit(0);
}

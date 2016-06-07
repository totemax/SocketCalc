#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char mensajeRec[3];
char mensajeEnv[2];

struct sockaddr_in dirMia;
struct sockaddr_in dirCli;

int rec, result;
int port;
int sk;
int i, componente;
int operando1, operando2, resultado_operacion;

int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error al invocar el programa. Formato llamada server [port]. Ej: server 7777.\n");
        exit(1);
    } else {
        port = atoi(argv[1]);
    }
    sk = socket(AF_INET, SOCK_DGRAM, 0);
    dirMia.sin_family = AF_INET;
    dirMia.sin_addr.s_addr = inet_addr("127.0.0.1");
    dirMia.sin_port = htons(port);
    result = bind(sk, (struct sockaddr*)&dirMia, sizeof(dirMia));
    if (result < 0) {
        printf("Error al crear el socket en el puerto %d\n", port);
        exit(1);
    }else{
        printf("Escuchando en puerto %d\n", port);
    }

    while (result >= 0) {
        bzero(&dirCli,sizeof(dirCli));
        int tam = sizeof(dirCli);
        recvfrom(sk, mensajeRec, sizeof(mensajeRec), 0, (struct sockaddr*)&dirCli, (unsigned*)&tam);
        printf("Mensaje %s\n", mensajeRec);
        operando1 = mensajeRec[1] - '0';
        operando2 = mensajeRec[2] - '0';
        switch(mensajeRec[0]) {
            case '+':
                resultado_operacion = operando1+operando2;
                break;
            case '-':
                resultado_operacion = operando1-operando2;
                break;
            case '/':
                resultado_operacion = operando1/operando2;
                break;
            case '*':
                resultado_operacion = operando1*operando2;
                break;
        }
        printf("Resultado: %d\n", resultado_operacion);
        mensajeEnv[0] = resultado_operacion/10 + '0';
        mensajeEnv[1] = resultado_operacion%10 + '0';
        result = sendto(sk,mensajeEnv,strlen(mensajeEnv),0,(struct sockaddr*)&dirCli,sizeof(dirCli));
    }
    exit(0);
}

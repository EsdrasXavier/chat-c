#include "constants.h"
#include <arpa/inet.h> //inet_addr
#include <stdio.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <unistd.h> // close

int main(int argc, char *argv[]) {
  int socketDesc;
  struct sockaddr_in server;
  char message[MSG_BUFFER], serverReply[MSG_BUFFER];

  socketDesc = socket(AF_INET, SOCK_STREAM, 0);

  if (socketDesc == -1) {
    printf("Impossível criar socket.\n");
  }

  server.sin_addr.s_addr = inet_addr(ADDRESS);
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);

  if (connect(socketDesc, (struct sockaddr *)&server, sizeof(server)) < 0) {
    printf("Erro ao criar conexão.\n");
    return 1;
  }

  printf("Conectado ao endereço: %s:%i\n", ADDRESS, PORT);

  while (strcmp(message, QUIT) != 0) {
    int ch, n = 0;
    bzero(message, sizeof(message));
    printf("Digite uma mensagem: ");

    while ((ch = getchar()) != '\n' && n < MSG_BUFFER) {
      message[n] = ch;
      n++;
    }

    if (send(socketDesc, message, strlen(message), 0) < 0) {
      printf("Erro ao enviar\n");
      return 1;
    }

    printf("Dados enviados.\n");

    /* recebe dados do servidor */
    if (recv(socketDesc, serverReply, MSG_BUFFER, 0) < 0) {
      printf("Falha ao receber resposta do servidor.\n");
      return 1;
    }

    printf("Resposta recebida.\n");
    printf("\n%s\n", serverReply);

    bzero(serverReply, sizeof(serverReply));
  }

  close(socketDesc);

  return 0;
}
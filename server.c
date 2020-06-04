#include "constants.h"
#include "server_log.h"
#include <arpa/inet.h> //inet_addr
#include <stdio.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <unistd.h> //write
#define atoa(x) #x
int main(int argc, char *argv[]) {
  int socketDesc, newSocket, c, length;
  struct sockaddr_in server, client;
  char *message, *str, clientReply[MSG_BUFFER];

  socketDesc = socket(AF_INET, SOCK_STREAM, 0);
  if (socketDesc == -1) {
    logMessage("Não foi possível criar servidor.");
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(PORT);

  if (bind(socketDesc, (struct sockaddr *)&server, sizeof(server)) < 0) {
    logMessage("Erro ao criar bind.");
  }

  length = snprintf(NULL, 0, "%d", PORT);
  str = malloc(length + 1);

  snprintf(str, length + 1, "%d", PORT);
  logMessage(concat("Bind feito na porta: ", str));
  free(str);

  listen(socketDesc, 3);

  logMessage("Esperando por conexões...");
  c = sizeof(struct sockaddr_in);

  while ((newSocket = accept(socketDesc, (struct sockaddr *)&client,
                             (socklen_t *)&c))) {
    logMessage("Conexão aceita");

    char *client_ip = inet_ntoa(client.sin_addr);
    int client_port = ntohs(client.sin_port);
    logMessage("Conexão aceita");

    length = snprintf(NULL, 0, "%d", client_port);
    str = malloc(length + 1);
    snprintf(str, length + 1, "%d", client_port);

    logMessage(concat("Conexão aceita do client: ",
                      concat(client_ip, concat(":", str))));
    free(str);

    do {
      bzero(clientReply, sizeof(clientReply));

      if (recv(newSocket, clientReply, MSG_BUFFER, 0) < 0) {
        logMessage("Falha ao receber dados");
        return 1;
      }

      logMessage("Resposta recebida");
      logMessage(concat("Recebido: ", clientReply));

      message = concat("Mensagem recebida com sucesso! Para sair digite:\n- ", QUIT);
      write(newSocket, message, strlen(message));
    } while (strcmp(clientReply, QUIT) != 0);

    write(newSocket, message, strlen(message));
  }

  if (newSocket < 0) {
    logMessage("Erro ao aceitar socket");
    return 1;
  }

  return 0;
}
#include "server_log.h"
#include <stdio.h>

void logMessage(char *data) { printf("%s %s.\n", SERVER_NAME, data); }

char *concat(const char *s1, const char *s2) {
  char *result =
      malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
  // in real code you would check for errors in malloc here
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}
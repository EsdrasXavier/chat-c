#ifndef SERVER_LOG
#define SERVER_LOG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_NAME "[Servidor] "

void logMessage(char *data);

char *concat(const char *s1, const char *s2);
#endif
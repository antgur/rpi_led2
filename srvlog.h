
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>

#define LOG_PATH "/var/log"
#define FILE_NAME "pvz"
#define MAX_MESSAGE_LENGHT 256

int srvlog(char *st);
//

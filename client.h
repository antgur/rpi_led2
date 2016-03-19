#include <pigpio.h>
#include <stdio.h>
#include <string.h>
#include "srvlog.h"

void sighandler(int sig);
int siusts(int sockClient, char *ss, int code);
int siusti(int sockClient, int code);
int childWork(int sockClient, char *ip);
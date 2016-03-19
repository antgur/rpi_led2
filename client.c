#include "client.h"
void sighandler(int sig) { }

int siusts(int sockClient, char* ss, int code)
{
    int n, snt;
    char bu[256];
    n = strlen(ss);
    if ((snt = send(sockClient, ss, n, 0)) == -1)
    {
	sprintf(bu,"Siuntimas neivyko -> %d",sockClient);
	srvlog(bu);
	perror("Siuntimas neivyko ");
	return -2;
    }
    if (code == -1) 
    {
	sprintf(bu,"GPIO busy -> %d",sockClient);
	srvlog(bu);
	perror("GPIO uzimtas ");
    }
    return 0;
}

int siusti(int sockClient,int code) 
{
    int n;
    if (code == -1)
    {
	if ((n = siusts(sockClient, "GPIO uzimtas\r\n",code)) == -2)
	{
	    return -2;
	}
    } else if (code == 0)
    {
	if ((n = siusts(sockClient, "OK\r\n", code)) == -2)
	{
	    return -2;
	}
    } else    {    }
    return 0;
}

int childWork(int sockClient, char *ip)
{
    char ss[80];
    double start;
    int st;
    if ((st = ipcr_init()) < 0) 
    {
	siusti(sockClient, -2);
	sprintf(ss,"IPC init error (-2). Client IP: %s -> %d",ip, sockClient);
	srvlog(ss);
	return -2;
    }
    sprintf(ss,"New client IP: %s -> %d",ip, sockClient);
    srvlog(ss);
    ipcr_set(5,0);
    if (gpioInitialise() < 0)
    {
	siusti(sockClient, -1);
	sprintf(ss,"Error (-1) client IP: %s -> %d",ip, sockClient);
	srvlog(ss);
	ipcr_destroy();
	return -1;
    }
    ipcr_set(1,0);
    gpioSetMode(19, PI_OUTPUT);
    start = time_time();
    while ((time_time() - start) < 10.0)
    {
      gpioWrite(19, 1); /* on */
      time_sleep(ipcr_get(0)/10.0);
//      time_sleep(0.1);
      gpioWrite(19, 0); /* off */
//      time_sleep(0.1);
      time_sleep(ipcr_get(0)/10.0);
    }
    gpioTerminate();
    if ((st = ipcr_destroy()) < 0) 
    {
	siusti(sockClient, -3);
	sprintf(ss,"IPC destroy error (-2). Client IP: %s -> %d",ip, sockClient);
	srvlog(ss);
	return -3;
    }
    siusti(sockClient,0);
    sprintf(ss,"Finished, client IP: %s -> %d",ip, sockClient);
    srvlog(ss);
    return 0;
}

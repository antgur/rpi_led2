#if !defined(IPCR_H)
#define IPCR_H

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>

#define KEY_PATH        "/etc/hostname"
#define KEY_SYMB1       'y'
#define KEY_SYMB2       'r'
#define MAX_IPC_LENGHT 2048

struct GpioData
{
  int da[MAX_IPC_LENGHT];
};

  key_t keyshm;
  key_t keysem;

  int shmid;

  struct GpioData *mm;

  // kuria atminti arba prie jos prisijungia
  // grazina:
  //  -1 ivykus klaidai
  //  1 pasisekimo atveju
  int ipcr_init();
  //uzpilu IPC konstantomis
  int ipcr_fill();
  //dedu eilini paketa i IPC
  int ipcr_set(int data, int nr);
  //istraukiu nurodyta paketa is IPC
  int ipcr_get(int nr);
  //pasalinu atminti
  int ipcr_destroy();

#endif
// SERVERIO klaidu kodai
// -1:

// KLIENTO klaidu kodai
// -1: Direktorijos sukurimo LOG failui klaida

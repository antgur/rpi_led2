#include "ipcr.h"

int ipcr_init()
{
  keyshm = ftok(KEY_PATH, KEY_SYMB2); //OTF
  if(keyshm == -1) return -1;

  // atminties sukurimas
  shmid = shmget(keyshm, sizeof(struct GpioData), (0644 | IPC_CREAT | IPC_EXCL));
  if(shmid == -1) // gal but registruoja
  {
    if(errno == EEXIST)  // atmintis egzistuoja
    {
      shmid = shmget(keyshm, sizeof(struct GpioData), 0644);
      if(shmid == -1)
        return -1;
     mm = (struct GpioData *)shmat(shmid, (void *)0, 0);
     if(mm == (struct GpioData *)(-1))
       return -1;
     return 1;
    }
    else
      return -1;
  }
  else
  {
    mm = (struct GpioData *)shmat(shmid, (void *)0, 0);
    if(mm == (struct GpioData *)(-1))
      return -1;
    memset((void *)mm, 0, sizeof(struct GpioData));
    return 1;
  }
  return 1;
}

int ipcr_fill()
{
  int i;
  for (i=0; i < MAX_IPC_LENGHT; i++) mm->da[i] = 0;
  return 1;
}

int ipcr_set(int da, int nr)
{
  mm->da[nr] = da;
  return 1;
}

int ipcr_get(int nr)
{
  return mm->da[nr];
}

int ipcr_destroy()
{
  int rez;

  rez = shmctl(shmid,IPC_RMID,0);

  return rez;
}


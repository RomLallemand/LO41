//main.c

/*#include "client.c"*/
#include "ascenseur.c"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <unistd.h>


void main(){
  genererAscenseur(1); 
}

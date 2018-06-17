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


int main(int argc,char* argv[]){
  if (argc-1 != 1) {
    fprintf(stderr,"Appel : %s <nombre ascenseurs souhaités>\n",argv[1]);
    return 1;
  }
  int nbA=atoi(argv[1]);




  genererAscenseur(nbA);

  while(1){} // sinon on ne voit pas l'affichage de l'ascenseur

  return 1;
}

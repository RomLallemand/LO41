//main.c
#include "structure.c"
#include "client.c"
#include "ascenseur.c"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <unistd.h>
#include <pthread.h>



void traitantSIGINT(int num) {


  if (num!=SIGINT)
    perror("Pb sur SigInt...");

  msgctl(msgid,IPC_RMID,0);
	signal(SIGINT,SIG_DFL);
	raise(SIGINT);
  }

int main(int argc,char* argv[]){

  srand(time(NULL));
  for(int i =0 ;i<=24; i++){
    listeEtageDest[i]=0;
    listeEtageDehors[i]=0;
  }

  key_t key;
  char *path = "/tmp";

  if (argc-1 != 1) {
    fprintf(stderr,"Appel : %s <nombre clients souhaités>\n",argv[1]);
    return 1;
  }
  int nbC=atoi(argv[1]);

  if ((key = ftok(path, 'A')) == -1) {
		perror("Erreur de creation de la clé \n");
		exit(1);
	}

	if ((msgid = msgget(key, IPC_CREAT | IPC_EXCL| 0600)) == -1) {
		perror("Erreur de creation de la file\n");
		exit(1);
	}
  signal(SIGINT,traitantSIGINT);
  //printf("MSGID DANS MAIN : %d\n",msgid);
  generateClient(2,nbC,0);//,msgid);
  genererAscenseur(1);//,msgid);

  while(1){} // sinon on ne voit pas l'affichage de l'ascenseur

  //destruction de la file message
  msgctl(msgid,IPC_RMID,0);


  return 1;
}

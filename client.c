//client.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <unistd.h>

typedef struct {
	int type;
	int etage;
} MessageEtageDemande;

struct Client{
	int numClient;
	int etageDepart;
	int etageArrive;
}

void generateClient(int scenario, int nombre, int typeRandom){

	switch(scenario){
		case 1://
		break;
		default://case completement aléatoire on prend en compte nombre et typeRandom
		break;
	}
}

//fonction client

int choixAscenseur(){
	
}

void appelAscenseur(int numAscenseur){
	int msgid;
	key_t key;

	MessageEtageDemande msg;
	msg.type=2;
	msg.etage=num;

	if ((key = ftok(NULL, 'A')) == -1) {
		perror("Erreur de creation de la clé \n");
		exit(1);
	}

	if ((msgid = msgget(key, 0750 | IPC_CREAT | IPC_EXCL)) == -1) {
		perror("Erreur de creation de la file\n");
		exit(1);
	}

	if (msgsnd(msgid, &msg, sizeof(MessageEtage) - 4,0) == -1) {
	  perror("Erreur d'envoi requete \n");
		exit(1);
	}
}

//la fonction qui permet de sortir de l'ascenseur et est appelé quand l'ascenseur fait si=ont broadcast
void sortirAscenseur(){}

// pour le thread

void * client(void * args){}

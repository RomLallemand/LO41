//client.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <unistd.h>

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

int choixAscenseur(){}

void appelAscenseur(int numAscenseur){}

//la fonction qui permet de sortir de l'ascenseur et est appelé quand l'ascenseur fait si=ont broadcast
void sortirAscenseur(){}

// pour le thread

void * client(void * args){}

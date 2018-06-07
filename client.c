//client.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <unistd.h>

int numClient;
int etageDepart;
int etageArrive;

void generateClient(int scenario, int nombre, int typeRandom){

	switch(scenario){
		case 1://
		break;
		default://case completement aléatoire on prend en compte nombre et typeRandom
		break;
	}
}

//fonction client

int choixAssenceur(){}
void appelAssenceur(int numAssenceur){}

// pour le thread
void * client(void * args){}

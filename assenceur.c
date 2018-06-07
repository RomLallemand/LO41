//assenceur.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <unistd.h>

int numAssenceur;
int etat;// 0: en attente 1: en fonction 2: en panne
int etageActuel;//0 à 24
int capacitee;



//genere les assenceurs avec les semaphores et mutex
void genererAssenceur(int nombre){
	
	
}

//fonctions des assenceurs



void appelerReaparateur(){}

void signalArriveeEtage(){}



//la fonction assenceur qui sera lancée pour créer un thread
void * assenceur(void * args){


}

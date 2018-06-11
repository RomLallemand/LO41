//ascenseur.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <unistd.h>


struct Ascenseur{
	int numAssenceur;
	int etat;// 0: en attente 1: monte 2: descend 3: en panne
	int etageActuel;//0 à 24
	int capacitee;
	int queueEtageAppel[100];
	int liste_etage_arrive[100];
};


//genere les assenceurs avec les semaphores et mutex
void genererAscenseur(int nombre){


}

//fonctions des ascenseurs



void appelerReaparateur(){}

//lorsque l'ascenseur arrive il "broadcast" je suis à étage X et les clients qui veulent sortir le font et broadcast pour les clients qui attendent sur le palier
void signalArriveeEtage(){}

void voyage(){
//while true
	//si non plein
		//si appel on va chercher client            priorise queueEtageAppel

			//si sur chemin on a des etages demandées pour sortir par les clients à l'interieur de l'ascenseur on fait un arret

			//si pas appel (personne appel de dehors) mais client a bord on les ammene a destination


	//si plein

		//dépose 1 client de liste_etage_demandee

	//sinon attente a etage actuel

//fin while

}


//la fonction ascenseur qui sera lancée pour créer un thread
void * ascenseur(void * args){


}

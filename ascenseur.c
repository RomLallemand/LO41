//ascenseur.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <unistd.h>


typedef struct MessageEtage{
	int type;
	int etage;
} MessageEtage;

typedef struct {
	int numAscenseur;
	int etat;// 0: en attente 1: monte 2: descend 3: en panne
	int etageActuel;//0 à 24
	int capacite;
	int queueEtageAppel[100];
	int liste_etage_arrive[100];
} Ascenseur;

//la fonction ascenseur qui sera lancée pour créer un thread
void * ascenseur(void * args){
	Ascenseur *ascenseur=(Ascenseur *) args;
	voyage(ascenseur);
}


//genere les assenceurs avec les semaphores et mutex
void genererAscenseur(int nombre){
	int i;
	Ascenseur* ascenseurs;
	ascenseurs=malloc(nombre*sizeof(Ascenseur));
	for(i=0;i<nombre;i++){
		ascenseurs[i].numAscenseur=i;
		ascenseurs[i].etat=0;
		ascenseurs[i].etageActuel=0;
		ascenseurs[i].capacite=10;
		//ascenseurs[i].queueEtageAppel=NULL;
		//ascenseurs[i].liste_etage_arrive=NULL;
	}
	pthread_t thr[nombre];
	for(i=0;i<nombre;i++){
		if(pthread_create(&thr[i],NULL,ascenseur, &ascenseurs[i]))
			perror("Erreur création threads ascenseurs");
	}

	while(1){
		fprintf(stderr,"dans genererAscenseur\n");
	}

}

//fonctions des ascenseurs



void appelerReparateur(Ascenseur* ascenseur){
}

//lorsque l'ascenseur arrive il "broadcast" je suis à étage X et les clients qui veulent sortir le font et broadcast pour les clients qui attendent sur le palier
void signalArriveeEtage(int num){
	int msgid;
	key_t key;

	MessageEtage msg;
	msg.type=1;
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

void voyage(Ascenseur *ascenseur){
//while true
	//si non plein
		//si appel on va chercher client            priorise queueEtageAppel

			//si sur chemin on a des etages demandées pour sortir par les clients à l'interieur de l'ascenseur on fait un arret

			//si pas appel (personne appel de dehors) mais client a bord on les ammene a destination


	//si plein

		//dépose 1 client de liste_etage_demandee

	//sinon attente a etage actuel

//fin while

	while(1){
		fprintf(stderr,"ascenseur n°%d voyage\n", ascenseur->numAscenseur);
	}
}

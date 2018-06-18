//ascenseur.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <unistd.h>
#include "Queue.c"
#include <pthread.h>


#define CAPACITE 10


typedef struct {
	int numAscenseur;
	int etat;// 0: en attente 1: monte 2: descend 3: en panne
	int etageActuel;//0 à 24
	int capacite;
	/*int queueEtageAppel[100];*/
	Queue *queueEtageAppel;
	int nbDemandes;
	int liste_etage_arrive[CAPACITE];
	int msgid;
} Ascenseur;






void genererAscenseur(int,int);
void* ascenseur(void*);
void appelerReparateur(Ascenseur*);
void signalArriveeEtage(Ascenseur*);
void voyage(Ascenseur*);






//la fonction ascenseur qui sera lancée pour créer un thread
void * ascenseur(void * args){
	Ascenseur *ascenseur=(Ascenseur *) args;
	voyage(ascenseur);
}


//genere les ascenseurs avec les semaphores et mutex
void genererAscenseur(int nombre,int msgid){
	int i,j;
	Ascenseur* ascenseurs;
	ascenseurs=malloc(nombre*sizeof(Ascenseur));
	for(i=0;i<nombre;i++){
		ascenseurs[i].numAscenseur=i+1;
		ascenseurs[i].etat=0;
		ascenseurs[i].etageActuel=0;
		ascenseurs[i].nbDemandes=0;
		ascenseurs[i].capacite=CAPACITE;
		ascenseurs[i].queueEtageAppel=createQueue(100);
		ascenseurs[i].msgid=msgid;
		int j;
		/*for(j=0;j<100;j++)
			ascenseurs[i].queueEtageAppel[j]=0;*/
		for(j=0;j<CAPACITE;j++)
			ascenseurs[i].liste_etage_arrive[j]=0;

	}
	pthread_t thr[nombre];
	for(i=0;i<nombre;i++){
		if(pthread_create(&thr[i],NULL,ascenseur, &ascenseurs[i]))
			perror("Erreur création threads ascenseurs");
	}
	//for(i=0;i<nombre;i++){
	//	if(pthread_join(&thr[i],NULL))
	//		perror("Erreur lors du join des threads ascenseurs");
	//1}

	free(ascenseurs);
}

//fonctions des ascenseurs

void verifMessage(Ascenseur *ascenseur){
	printf("dans rcv\n");
	//en recupère qu'un seul
	int i =0;
	while(i <CAPACITE){
		MessageEtageDemande rep;
		if(msgrcv(ascenseur->msgid, &rep, sizeof(MessageEtageDemande) - 4, 2, IPC_NOWAIT)==-1){
			perror("Erreur réception requete \n");

		}else{
			ascenseur->nbDemandes++;
			Enqueue(ascenseur->queueEtageAppel,rep.etageAppuiBtn);
		}
		usleep(1000);
		i++;
	}


}

void appelerReparateur(Ascenseur* ascenseur){
}

//lorsque l'ascenseur arrive il "broadcast" je suis à étage X et les clients qui veulent sortir le font et broadcast pour les clients qui attendent sur le palier
void signalArriveeEtage(Ascenseur * ascenseur){

	MessageEtage msg;
	msg.type=1;
	msg.etage=ascenseur->etageActuel;


	if (msgsnd(ascenseur->msgid, &msg, sizeof(MessageEtage) - 4,0) == -1) {
	  perror("Erreur d'envoi requete \n");
		exit(1);
	}

}



void voyage(Ascenseur *ascenseur){ // IL FAUDRAIT PEUT ETRE SOCCUPER DE RECEVOIR LES DEMANDES A CHAQUE ITERATION DU WHILE ?
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

		if(ascenseur->nbDemandes < CAPACITE){ // => si pas plein, suit la queue étages demandés
			verifMessage(ascenseur);
			while(ascenseur->nbDemandes==0){
				//fprintf(stderr,"Ascenseur n°%d en attente à l'étage %d | %d/%d\n",ascenseur->numAscenseur,ascenseur->etageActuel,ascenseur->nbDemandes,CAPACITE);

			}
			int allerA=front(ascenseur->queueEtageAppel);
			Dequeue(ascenseur->queueEtageAppel);
		}
		else if(ascenseur->nbDemandes == CAPACITE){ // => si plein, dépose au premier étage demandé
			int allerA=front(ascenseur->queueEtageAppel);
			Dequeue(ascenseur->queueEtageAppel);

			while(ascenseur->etageActuel!=allerA){
				if(ascenseur->etageActuel<allerA){
					ascenseur->etageActuel++;
				}
				else if(ascenseur->etageActuel>allerA){
					ascenseur->etageActuel--;
				}
				usleep(1000);
			}

			verifMessage(ascenseur);
			signalArriveeEtage(ascenseur); // => fera sortir les gens qui veulent sortir, puis rentrer ceux qui attendent à cet étage
		}

	}
}



void test(Ascenseur *ascenseur){
	Enqueue(ascenseur->queueEtageAppel,0);
	Enqueue(ascenseur->queueEtageAppel,3);
	Dequeue(ascenseur->queueEtageAppel);
	while(1){
		//fprintf(stderr,"ascenseur n°%d voyage\n", ascenseur->numAscenseur);
		fprintf(stderr,"ascenseur n°%d voyage, front queueEtageAppel=%d\n", ascenseur->numAscenseur,front(ascenseur->queueEtageAppel));
	}
}

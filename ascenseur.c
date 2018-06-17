//ascenseur.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <unistd.h>
#include "Queue.c";
#define CAPACITE 10

typedef struct {
	int type;
	int etage;
} MessageEtage;

typedef struct {
	int numAscenseur;
	int etat;// 0: en attente 1: monte 2: descend 3: en panne
	int etageActuel;//0 à 24
	int capacite;
	/*int queueEtageAppel[100];*/
	Queue *queueEtageAppel;
	int nbDemandes;
	int liste_etage_arrive[CAPACITE];
} Ascenseur;







void genererAscenseur(int);
void* ascenseur(void*);
void appelerReparateur(Ascenseur*);
void signalArriveeEtage(int);
void voyage(Ascenseur*);






//la fonction ascenseur qui sera lancée pour créer un thread
void * ascenseur(void * args){
	Ascenseur *ascenseur=(Ascenseur *) args;
	voyage(ascenseur);
}


//genere les ascenseurs avec les semaphores et mutex
void genererAscenseur(int nombre){
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
}

//fonctions des ascenseurs



void appelerReparateur(Ascenseur* ascenseur){
}

//lorsque l'ascenseur arrive il "broadcast" je suis à étage X et les clients qui veulent sortir le font et broadcast pour les clients qui attendent sur le palier
void signalArriveeEtage(int numEtage){
	int msgid;
	key_t key;

	MessageEtage msg;
	msg.type=1;
	msg.etage=numEtage;

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

void voyage(Ascenseur *ascenseur){ // IL FAUDRAIT PEUT ETRE SOCCUPER DE RECEVOIR LES DEMANDES A CHAQUE ITERATION DU WHILE ?
	printf("ici");
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
			while(ascenseur->nbDemandes==0){
				fprintf(stderr,"Ascenseur n°%d en attente à l'étage %d | %d/%d\n",ascenseur->numAscenseur,ascenseur->etageActuel,ascenseur->nbDemandes,CAPACITE);
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

			signalArriveeEtage(ascenseur->etageActuel); // => fera sortir les gens qui veulent sortir, puis rentrer ceux qui attendent à cet étage
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

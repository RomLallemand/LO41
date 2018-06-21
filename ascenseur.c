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
#include <errno.h>

#define CAPACITE 10


typedef struct {
	int numAscenseur;
	int etat;// 0: en attente 1: monte 2: descend 3: en panne
	int etageActuel;//0 à 24
	int capacite;
	int nbClientDansAscenseur;
	/*int queueEtageAppel[100];*/
	Queue *queueEtageAppel;
	int nbDemandes;
	int liste_etage_arrive[CAPACITE];
	int msgid;
} Ascenseur;






void genererAscenseur(int);//,int);
void* ascenseur(void*);
void appelerReparateur(Ascenseur*);
void signalArriveeEtage(Ascenseur*);
void voyage(Ascenseur*);
void test(Ascenseur*);
void enterClient(Ascenseur*);
void sortirClient(Ascenseur*);
int chercheUneDestination(int);






//la fonction ascenseur qui sera lancée pour créer un thread
void * ascenseur(void * args){
	Ascenseur *ascenseur=(Ascenseur *) args;
	voyage(ascenseur);
	//test(ascenseur);
}


//genere les ascenseurs avec les semaphores et mutex
void genererAscenseur(int nombre){//,int msgid){
	int i,j;
	Ascenseur* ascenseurs;
	ascenseurs=malloc(nombre*sizeof(Ascenseur));
	//Ascenseur ascenseurs[nombre];
	for(i=0;i<nombre;i++){
		ascenseurs[i].numAscenseur=i;
		ascenseurs[i].etat=0;
		ascenseurs[i].etageActuel=0;
		ascenseurs[i].nbDemandes=0;
		ascenseurs[i].capacite=CAPACITE;
		ascenseurs[i].queueEtageAppel=createQueue(100);
		ascenseurs[i].msgid=msgid;
		ascenseurs[i].nbClientDansAscenseur=0;
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

	//free(ascenseurs);
}

//fonctions des ascenseurs

void verifMessage(Ascenseur *ascenseur){

	//printf("dans rcv\n");

	int i =0;

	while(i <CAPACITE){
		MessageEtageDemande rep;
		pthread_mutex_lock(&mutexMessage);
		int m=msgrcv(msgid, &rep, sizeof(MessageEtageDemande) - sizeof(long), 2, IPC_NOWAIT);
		pthread_mutex_unlock(&mutexMessage);
		if(m==-1){
			//perror("Erreur réception requete \n");

		}else{
			printf("res: %ld, %d, %d\n",rep.type,rep.etageDemande,rep.etageAppuiBtn);
			ascenseur->nbDemandes++;
			Enqueue(ascenseur->queueEtageAppel,rep.etageAppuiBtn);
			//printf("remplir\n");

		}
		i++;
		usleep(1000);
	}

}

void appelerReparateur(Ascenseur* ascenseur){
}

//lorsque l'ascenseur arrive il "broadcast" je suis à étage X et les clients qui veulent sortir le font et broadcast pour les clients qui attendent sur le palier
void signalArriveeEtage(Ascenseur * ascenseur){
	pthread_mutex_lock(&mutexMessage);
	MessageEtage msg;
	msg.type=1;
	msg.etage=ascenseur->etageActuel;


	if (msgsnd(ascenseur->msgid, &msg, sizeof(MessageEtage) - 4,0) == -1) {
	  perror("Erreur d'envoi requete \n");
		exit(1);
	}
	pthread_mutex_unlock(&mutexMessage);
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
		printf("Ascenseur arrive à l'étage %d\n",ascenseur->etageActuel);
		printf("Ascenseur: nbClientDansAscenseur %d\n",ascenseur->nbClientDansAscenseur);

		printf("demandes %d:\n",ascenseur->nbDemandes);
		int allerA;
		verifMessage(ascenseur);
		//printf("ascenseur->queueEtageAppel->size %d\n",ascenseur->queueEtageAppel->size );


		if(ascenseur->queueEtageAppel->size !=0){
			allerA=front(ascenseur->queueEtageAppel);

			//printf("dest: %d\n",allerA);
			if(ascenseur->etageActuel==allerA){
				Dequeue(ascenseur->queueEtageAppel);
				ascenseur->nbDemandes--;
			}



		}else{
			allerA=chercheUneDestination(ascenseur->etageActuel);
		}//fin if pour la gestion de la Queue
		printf("destination courante %d\n",allerA);
		//on previent les clients en dormance pour qu'ils sortent si c'est leur étage
		sortirClient(ascenseur);

		//faire entrer les clients
		enterClient(ascenseur);


		//deplacement
		if(ascenseur->nbClientDansAscenseur!= 0 && ascenseur->nbDemandes!=0){
			printf("Ascenseur départ\n");
		}
		
		if(ascenseur->etageActuel<allerA){
			ascenseur->etageActuel++;
			printf("Ascenseur monte\n");

		}
		else if(ascenseur->etageActuel>allerA){
			ascenseur->etageActuel--;
			printf("Ascenseur descend\n");

		}
		pthread_mutex_lock(&mutexVariableGlobale);
		printf("Client arrivés à destination %d\n",clientArriverDest);
		pthread_mutex_unlock(&mutexVariableGlobale);
		printf("--------------------------------------------\n");
		usleep(1000000);
	}//fin du while(1)
}//fin de la fonction



void test(Ascenseur *ascenseur){
	Enqueue(ascenseur->queueEtageAppel,0);
	Enqueue(ascenseur->queueEtageAppel,3);
	Dequeue(ascenseur->queueEtageAppel);
	while(1){
		fprintf(stderr,"ascenseur %d -> msgid %d\n",ascenseur->numAscenseur, ascenseur->msgid);
		//fprintf(stderr,"ascenseur n°%d voyage, front queueEtageAppel=%d\n", ascenseur->numAscenseur,front(ascenseur->queueEtageAppel));
	}
}

int chercheUneDestination(int etageActuel){
	for(int i=etageActuel;i<25;i++){
		//listeEtageDest[i]
		if(getListeEtageDest(i)!=0){
			return i;
		}
	}
	for(int i=etageActuel;i>=0;i--){
		//listeEtageDest[i]
		if(getListeEtageDest(i)!=0){
			return i;
		}
	}
	return etageActuel;
}

void enterClient(Ascenseur *ascenseur){
	//pthread_mutex_lock(&mutexVariableGlobale);
	//listeEtageDehors[ascenseur->etageActuel]
	while(ascenseur->nbClientDansAscenseur<CAPACITE && getListeEtageDehors(ascenseur->etageActuel)!=0){
		if(getListeEtageDehors(ascenseur->etageActuel)==1){
			printf("Fait entrer le client\n");
		}
		else if(getListeEtageDehors(ascenseur->etageActuel)!=0){
			printf("Fait entrer les clients\n");
		}
		switch(ascenseur->etageActuel){
			case 0:	pthread_cond_signal(&dormirAttenteAscenseur0);
				break;
			case 1:
				pthread_cond_signal(&dormirAttenteAscenseur1);
				break;
			case 2:
				pthread_cond_signal(&dormirAttenteAscenseur2);
				break;
			case 3:
				pthread_cond_signal(&dormirAttenteAscenseur3);
				break;
			case 4:
				pthread_cond_signal(&dormirAttenteAscenseur4);
				break;
			case 5:
				pthread_cond_signal(&dormirAttenteAscenseur5);
				break;
			case 6:
				pthread_cond_signal(&dormirAttenteAscenseur6);
				break;
			case 7:
				pthread_cond_signal(&dormirAttenteAscenseur7);
				break;
			case 8:
				pthread_cond_signal(&dormirAttenteAscenseur8);
				break;
			case 9:
				pthread_cond_signal(&dormirAttenteAscenseur9);
				break;
			case 10:
				pthread_cond_signal(&dormirAttenteAscenseur10);
				break;
			case 11:
				pthread_cond_signal(&dormirAttenteAscenseur11);
				break;
			case 12:
				pthread_cond_signal(&dormirAttenteAscenseur12);
				break;
			case 13:
				pthread_cond_signal(&dormirAttenteAscenseur13);
				break;
			case 14:
				pthread_cond_signal(&dormirAttenteAscenseur14);
				break;
			case 15:
				pthread_cond_signal(&dormirAttenteAscenseur15);
				break;
			case 16:
				pthread_cond_signal(&dormirAttenteAscenseur16);
				break;
			case 17:
				pthread_cond_signal(&dormirAttenteAscenseur17);
				break;
			case 18:
				pthread_cond_signal(&dormirAttenteAscenseur18);
				break;
			case 19:
				pthread_cond_signal(&dormirAttenteAscenseur19);
				break;
			case 20:
				pthread_cond_signal(&dormirAttenteAscenseur20);
				break;
			case 21:
				pthread_cond_signal(&dormirAttenteAscenseur21);
				break;
			case 22:
				pthread_cond_signal(&dormirAttenteAscenseur22);
				break;
			case 23:
				pthread_cond_signal(&dormirAttenteAscenseur23);
				break;
			case 24:
				pthread_cond_signal(&dormirAttenteAscenseur24);
				break;
			default:
				
				break;
		}//fin switch
		pthread_mutex_unlock(&mutexAttente);
		
		pthread_cond_wait(&condAscenseur,&ascenseur_mutex);

		ascenseur->nbClientDansAscenseur++;
		
	}//fin entrer client
	//pthread_mutex_unlock(&mutexVariableGlobale);

}
void sortirClient(Ascenseur* ascenseur){

	//libere mutex
	//condition est mise a true
	//pthread_mutex_lock(&mutexVariableGlobale);
	//listeEtageDest[ascenseur->etageActuel]
	while(getListeEtageDest(ascenseur->etageActuel)>0){
		printf("Fait sortir les clients\n");
		switch(ascenseur->etageActuel){
			case 0:
				pthread_cond_signal(&dormirDansAscenseur0);
				break;
			case 1:
				pthread_cond_signal(&dormirDansAscenseur1);
				break;
			case 2:
				pthread_cond_signal(&dormirDansAscenseur2);
				break;
			case 3:
				pthread_cond_signal(&dormirDansAscenseur3);
				break;
			case 4:
				pthread_cond_signal(&dormirDansAscenseur4);
				break;
			case 5:
				pthread_cond_signal(&dormirDansAscenseur5);
				break;
			case 6:
				pthread_cond_signal(&dormirDansAscenseur6);
				break;
			case 7:
				pthread_cond_signal(&dormirDansAscenseur7);
				break;
			case 8:
				pthread_cond_signal(&dormirDansAscenseur8);
				break;
			case 9:
				pthread_cond_signal(&dormirDansAscenseur9);
				break;
			case 10:
				pthread_cond_signal(&dormirDansAscenseur10);
				break;
			case 11:
				pthread_cond_signal(&dormirDansAscenseur11);
				break;
			case 12:
				pthread_cond_signal(&dormirDansAscenseur12);
				break;
			case 13:
				pthread_cond_signal(&dormirDansAscenseur13);
				break;
			case 14:
				pthread_cond_signal(&dormirDansAscenseur14);
				break;
			case 15:
				pthread_cond_signal(&dormirDansAscenseur15);
				break;
			case 16:
				pthread_cond_signal(&dormirDansAscenseur16);
				break;
			case 17:
				pthread_cond_signal(&dormirDansAscenseur17);
				break;
			case 18:
				pthread_cond_signal(&dormirDansAscenseur18);
				break;
			case 19:
				pthread_cond_signal(&dormirDansAscenseur19);
				break;
			case 20:
				pthread_cond_signal(&dormirDansAscenseur20);
				break;
			case 21:
				pthread_cond_signal(&dormirDansAscenseur21);
				break;
			case 22:
				pthread_cond_signal(&dormirDansAscenseur22);
				break;
			case 23:
				pthread_cond_signal(&dormirDansAscenseur23);
				break;
			case 24:
				pthread_cond_signal(&dormirDansAscenseur24);
				break;
			default:

				break;
		}//fin switch
		pthread_mutex_unlock(&mutexAttenteDansAscenseur);
		pthread_cond_wait(&condAscenseur,&ascenseur_mutex);
		ascenseur->nbClientDansAscenseur--;
	}
	//fin sorties clients
	//pthread_mutex_lock(&mutexVariableGlobale);
}

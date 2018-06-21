//client.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>


typedef struct {
	int numClient;
	int etageDepart;
	int etageArrive;
	int _msgid_;
	int heureArrivee;
} Client;





//fonction client

int choixAscenseur(){

}

/*
Fonction quand un client appelle l'ascenseur. Un message de type 2est envoyé à l'ascenseur avec l'etage actuel et voulu du client.
*/
void appelAscenseur(Client* c){
	pthread_mutex_lock(&mutexMessage);
	//printf("dans appel\n");

	MessageEtageDemande msg;
	msg.type=2;
	msg.etageDemande=c->etageArrive;
	msg.etageAppuiBtn=c->etageDepart;
	//printf("msg: %ld, %d, %d,\n",msg.type,msg.etageDemande,msg.etageAppuiBtn);
	//printf("Client appui sur bouton à l'étage %d pour aller au %d\n",msg.etageAppuiBtn,msg.etageDemande);
	if (msgsnd(msgid, &msg, sizeof(MessageEtageDemande) - sizeof(long),0) == -1) {
	  perror("Erreur d'envoi requete. \n");
		exit(1);
	}
	pthread_mutex_unlock(&mutexMessage);
}

//la fonction qui permet de sortir de l'ascenseur et est appelé quand l'ascenseur fait sont broadcast
void sortirAscenseur(){}





/*
Fonction pour les threads clients de la gestion d'un client de l'appel de l'ascenseur à la descente de la cabine.
*/
void * client(void * args){
	Client *client=(Client *) args;
	//printf("MSGID *CLIENT(args) : %d\n",client->_msgid_); // urgent PB de pointeur
	usleep(client->heureArrivee*1000000);
	appelAscenseur(client);
	//dort mutex + cond
	printf("		Client attend ascenseur à étage %d\n",client->etageDepart);
	pthread_mutex_lock(&mutexVariableGlobale);
	listeEtageDehors[client->etageDepart]++;
	pthread_mutex_unlock(&mutexVariableGlobale);
	switch(client->etageDepart){
		case 0:	pthread_cond_wait(&dormirAttenteAscenseur0,&mutexAttente);
			break;
		case 1:
			pthread_cond_wait(&dormirAttenteAscenseur1,&mutexAttente);
			break;
		case 2:
			pthread_cond_wait(&dormirAttenteAscenseur2,&mutexAttente);
			break;
		case 3:
			pthread_cond_wait(&dormirAttenteAscenseur3,&mutexAttente);
			break;
		case 4:
			pthread_cond_wait(&dormirAttenteAscenseur4,&mutexAttente);
			break;
		case 5:
			pthread_cond_wait(&dormirAttenteAscenseur5,&mutexAttente);
			break;
		case 6:
			pthread_cond_wait(&dormirAttenteAscenseur6,&mutexAttente);
			break;
		case 7:
			pthread_cond_wait(&dormirAttenteAscenseur7,&mutexAttente);
			break;
		case 8:
			pthread_cond_wait(&dormirAttenteAscenseur8,&mutexAttente);
			break;
		case 9:
			pthread_cond_wait(&dormirAttenteAscenseur9,&mutexAttente);
			break;
		case 10:
			pthread_cond_wait(&dormirAttenteAscenseur10,&mutexAttente);
			break;
		case 11:
			pthread_cond_wait(&dormirAttenteAscenseur11,&mutexAttente);
			break;
		case 12:
			pthread_cond_wait(&dormirAttenteAscenseur12,&mutexAttente);
			break;
		case 13:
			pthread_cond_wait(&dormirAttenteAscenseur13,&mutexAttente);
			break;
		case 14:
			pthread_cond_wait(&dormirAttenteAscenseur14,&mutexAttente);
			break;
		case 15:
			pthread_cond_wait(&dormirAttenteAscenseur15,&mutexAttente);
			break;
		case 16:
			pthread_cond_wait(&dormirAttenteAscenseur16,&mutexAttente);
			break;
		case 17:
			pthread_cond_wait(&dormirAttenteAscenseur17,&mutexAttente);
			break;
		case 18:
			pthread_cond_wait(&dormirAttenteAscenseur18,&mutexAttente);
			break;
		case 19:
			pthread_cond_wait(&dormirAttenteAscenseur19,&mutexAttente);
			break;
		case 20:
			pthread_cond_wait(&dormirAttenteAscenseur20,&mutexAttente);
			break;
		case 21:
			pthread_cond_wait(&dormirAttenteAscenseur21,&mutexAttente);
			break;
		case 22:
			pthread_cond_wait(&dormirAttenteAscenseur22,&mutexAttente);
			break;
		case 23:
			pthread_cond_wait(&dormirAttenteAscenseur23,&mutexAttente);
			break;
		case 24:
			pthread_cond_wait(&dormirAttenteAscenseur24,&mutexAttente);
			break;
		default:
			perror("erreur d attente a un etage\n");
			break;
	}
	//il est réveillé
	//entre dans ascenseur
	printf("		Entre dans ascenseur\n");
	pthread_mutex_lock(&mutexVariableGlobale);
	listeEtageDest[client->etageArrive]++;
	listeEtageDehors[client->etageDepart]--;
	pthread_mutex_unlock(&mutexVariableGlobale);
	pthread_cond_signal(&condAscenseur);
	pthread_mutex_unlock(&ascenseur_mutex);
	//pthread_mutex_lock(&mutexAttente);


	//dort dans l'ascenseur
	printf("		Client dort dans ascenseur\n");
	switch(client->etageArrive){
		case 0:	pthread_cond_wait(&dormirDansAscenseur0,&mutexAttenteDansAscenseur);
			break;
		case 1:
			pthread_cond_wait(&dormirDansAscenseur1,&mutexAttenteDansAscenseur);
			break;
		case 2:
			pthread_cond_wait(&dormirDansAscenseur2,&mutexAttenteDansAscenseur);
			break;
		case 3:
			pthread_cond_wait(&dormirDansAscenseur3,&mutexAttenteDansAscenseur);
			break;
		case 4:
			pthread_cond_wait(&dormirDansAscenseur4,&mutexAttenteDansAscenseur);
			break;
		case 5:
			pthread_cond_wait(&dormirDansAscenseur5,&mutexAttenteDansAscenseur);
			break;
		case 6:
			pthread_cond_wait(&dormirDansAscenseur6,&mutexAttenteDansAscenseur);
			break;
		case 7:
			pthread_cond_wait(&dormirDansAscenseur7,&mutexAttenteDansAscenseur);
			break;
		case 8:
			pthread_cond_wait(&dormirDansAscenseur8,&mutexAttenteDansAscenseur);
			break;
		case 9:
			pthread_cond_wait(&dormirDansAscenseur9,&mutexAttenteDansAscenseur);
			break;
		case 10:
			pthread_cond_wait(&dormirDansAscenseur10,&mutexAttenteDansAscenseur);
			break;
		case 11:
			pthread_cond_wait(&dormirDansAscenseur11,&mutexAttenteDansAscenseur);
			break;
		case 12:
			pthread_cond_wait(&dormirDansAscenseur12,&mutexAttenteDansAscenseur);
			break;
		case 13:
			pthread_cond_wait(&dormirDansAscenseur13,&mutexAttenteDansAscenseur);
			break;
		case 14:
			pthread_cond_wait(&dormirDansAscenseur14,&mutexAttenteDansAscenseur);
			break;
		case 15:
			pthread_cond_wait(&dormirDansAscenseur15,&mutexAttenteDansAscenseur);
			break;
		case 16:
			pthread_cond_wait(&dormirDansAscenseur16,&mutexAttenteDansAscenseur);
			break;
		case 17:
			pthread_cond_wait(&dormirDansAscenseur17,&mutexAttenteDansAscenseur);
			break;
		case 18:
			pthread_cond_wait(&dormirDansAscenseur18,&mutexAttenteDansAscenseur);
			break;
		case 19:
			pthread_cond_wait(&dormirDansAscenseur19,&mutexAttenteDansAscenseur);
			break;
		case 20:
			pthread_cond_wait(&dormirDansAscenseur20,&mutexAttenteDansAscenseur);
			break;
		case 21:
			pthread_cond_wait(&dormirDansAscenseur21,&mutexAttenteDansAscenseur);
			break;
		case 22:
			pthread_cond_wait(&dormirDansAscenseur22,&mutexAttenteDansAscenseur);
			break;
		case 23:
			pthread_cond_wait(&dormirDansAscenseur23,&mutexAttenteDansAscenseur);
			break;
		case 24:
			pthread_cond_wait(&dormirDansAscenseur24,&mutexAttenteDansAscenseur);
			break;
		default:
			perror("erreur d attente dans l ascenseur\n");
			break;
	}

	//il est réveillé
	//sortirAscenseur();
	printf("		Sort de ascenseur\n");
	pthread_mutex_lock(&mutexVariableGlobale);

	listeEtageDest[client->etageArrive]--;
	clientArriverDest++;
	pthread_mutex_unlock(&mutexVariableGlobale);
	pthread_cond_signal(&condAscenseur);
	pthread_mutex_unlock(&ascenseur_mutex);
	//pthread_mutex_lock(&mutexAttenteDansAscenseur);
	//usleep(10000000);
}

/*
Fonction qui génère n clients sous forme de threads. La fonction
*/
void generateClient(int scenario, int nombre, int typeRandom){//, int msgid_){
	switch(scenario){
		case 1:
				{
					Client* clients;
					clients=malloc(nombre*sizeof(Client));
					for(int i=0;i<nombre;i++){
						clients[i].numClient=i+1;
						clients[i].etageDepart=0;
						clients[i].etageArrive=2;
						clients[i]._msgid_=msgid;
						clients[i].heureArrivee=0;
					}
					pthread_t thr[nombre];
					for(int i=0;i<nombre;i++){
						if(pthread_create(&thr[i],NULL,client, &clients[i]))
							perror("Erreur création threads clients");
					}
					//for(int i=0;i<nombre;i++){
					//	if(pthread_join(&thr[i],NULL))
					//		perror("Erreur lors du join des threads client");
					//}

					//free(clients);
				}
				break;
		case 2:
				{
					Client* clients;
					clients=malloc(nombre*sizeof(Client));
					for(int i=0;i<nombre;i++){
						clients[i].numClient=i+1;
						int x=rand()%24;
						clients[i].etageDepart=x;
						int t=rand()%24;
						while(t==x){
							t=rand()%24;						
						}
						clients[i].etageArrive=t;
						clients[i]._msgid_=msgid;
						clients[i].heureArrivee=0;
					}
					pthread_t thr[nombre];
					for(int i=0;i<nombre;i++){
						if(pthread_create(&thr[i],NULL,client, &clients[i]))
							perror("Erreur création threads clients");
					}

				}
				break;
		case 3:
				{
					Client* clients;
					clients=malloc(nombre*sizeof(Client));
					for(int i=0;i<nombre;i++){
						clients[i].numClient=i+1;
						int x=rand()%24;
						clients[i].etageDepart=x;
						int t=rand()%24;
						while(t==x){
							t=rand()%24;						
						}
						clients[i].etageArrive=t;
						clients[i]._msgid_=msgid;
						clients[i].heureArrivee=rand()%15;
					}
					pthread_t thr[nombre];
					for(int i=0;i<nombre;i++){
						if(pthread_create(&thr[i],NULL,client, &clients[i]))
							perror("Erreur création threads clients");
					}

				}
				break;
		default://case completement aléatoire on prend en compte nombre et typeRandom
				break;
	}
}

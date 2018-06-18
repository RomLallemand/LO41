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


typedef struct {
	int numClient;
	int etageDepart;
	int etageArrive;
	int _msgid_;
} Client;





//fonction client

int choixAscenseur(){

}

void appelAscenseur(Client* c){
printf("dans appel\n");

	MessageEtageDemande msg;
	msg.type=2;
	msg.etageDemande=c->etageArrive;
	msg.etageAppuiBtn=c->etageDepart;

	if (msgsnd(c->_msgid_, &msg, sizeof(MessageEtageDemande) - sizeof(long),0) == -1) {
	  perror("Erreur d'envoi requete. \n");
		exit(1);
	}
}

//la fonction qui permet de sortir de l'ascenseur et est appelé quand l'ascenseur fait sont broadcast
void sortirAscenseur(){}





// pour le thread

void * client(void * args){
	Client *client=(Client *) args;
	printf("MSGID *CLIENT(args) : %d\n",client->etageArrive); // urgent PB de pointeur
	appelAscenseur(client);
	//dort
	//il est réveillé
	//entre dans ascenseur
	//dort
	usleep(10000000);
	//il est réveillé
	sortirAscenseur();

}


void generateClient(int scenario, int nombre, int typeRandom, int msgid_){
printf("MSGID GENERATECLT : %d\n",msgid_);


	switch(scenario){
		case 1:
				{
					Client* clients;
					clients=malloc(nombre*sizeof(Client));
					for(int i=0;i<nombre;i++){
						clients[i].numClient=i+1;
						clients[i].etageDepart=0;
						clients[i].etageArrive=2;
						clients[i]._msgid_=msgid_;
					}
					printf("MSGID GENERATECLT  test : %d\n",(&clients[0])->_msgid_); //OK bon msgid
					pthread_t thr[nombre];
					for(int i=0;i<nombre;i++){
						if(pthread_create(&thr[i],NULL,client, &clients[i]))
							perror("Erreur création threads clients");
					}
					//for(int i=0;i<nombre;i++){
					//	if(pthread_join(&thr[i],NULL))
					//		perror("Erreur lors du join des threads client");
					//}

					free(clients);
				}
				break;
		default://case completement aléatoire on prend en compte nombre et typeRandom
				break;
	}
}

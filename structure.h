#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SKEY   (key_t) IPC_PRIVATE
#define SEMPERM 0600

int msgid;

pthread_mutex_t mutexAttenteDansAscenseur=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexAttente=PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t mutexMessage=PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t attendreDansAscenseur,message;
pthread_cond_t dormirAttenteAscenseur0,
dormirAttenteAscenseur1,
dormirAttenteAscenseur2,
dormirAttenteAscenseur3,
dormirAttenteAscenseur4,
dormirAttenteAscenseur5,
dormirAttenteAscenseur6,
dormirAttenteAscenseur7,
dormirAttenteAscenseur8,
dormirAttenteAscenseur9,
dormirAttenteAscenseur10,
dormirAttenteAscenseur11,
dormirAttenteAscenseur12,
dormirAttenteAscenseur13,
dormirAttenteAscenseur14,
dormirAttenteAscenseur15,
dormirAttenteAscenseur16,
dormirAttenteAscenseur17,
dormirAttenteAscenseur18,
dormirAttenteAscenseur19,
dormirAttenteAscenseur20,
dormirAttenteAscenseur21,
dormirAttenteAscenseur22,
dormirAttenteAscenseur23,
dormirAttenteAscenseur24;

pthread_cond_t dormirDansAscenseur0,
dormirDansAscenseur1,
dormirDansAscenseur2,
dormirDansAscenseur3,
dormirDansAscenseur4,
dormirDansAscenseur5,
dormirDansAscenseur6,
dormirDansAscenseur7,
dormirDansAscenseur8,
dormirDansAscenseur9,
dormirDansAscenseur10,
dormirDansAscenseur11,
dormirDansAscenseur12,
dormirDansAscenseur13,
dormirDansAscenseur14,
dormirDansAscenseur15,
dormirDansAscenseur16,
dormirDansAscenseur17,
dormirDansAscenseur18,
dormirDansAscenseur19,
dormirDansAscenseur20,
dormirDansAscenseur21,
dormirDansAscenseur22,
dormirDansAscenseur23,
dormirDansAscenseur24;

pthread_mutex_t ascenseur;

pthread_cond_t condAscenseur;



typedef struct {
	long type;
	int etageDemande;
	int etageAppuiBtn;
} MessageEtageDemande;

typedef struct {
	long type;
	int etage;
} MessageEtage;

int shmid ;
shmid = shmget(IPC_PRIVATE, 25*sizeof(int), 0666);

int *listeEtageDest=malloc(25*sizeof(int));

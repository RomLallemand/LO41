#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SKEY   (key_t) IPC_PRIVATE
#define SEMPERM 0600

int msgid;

pthread_mutex_t mutexAttenteDansAscenseur=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexAttente=PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t mutexVariableGlobale=PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t mutexMessage=PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t attendreDansAscenseur=PTHREAD_COND_INITIALIZER;
pthread_cond_t message=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur0=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur1=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur2=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur3=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur4=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur5=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur6=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur7=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur8=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur9=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur10=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur11=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur12=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur13=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur14=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur15=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur16=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur17=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur18=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur19=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur20=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur21=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur22=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur23=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirAttenteAscenseur24=PTHREAD_COND_INITIALIZER;

pthread_cond_t dormirDansAscenseur0=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur1=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur2=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur3=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur4=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur5=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur6=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur7=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur8=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur9=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur10=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur11=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur12=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur13=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur14=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur15=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur16=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur17=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur18=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur19=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur20=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur21=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur22=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur23=PTHREAD_COND_INITIALIZER;
pthread_cond_t dormirDansAscenseur24=PTHREAD_COND_INITIALIZER;



pthread_mutex_t ascenseur_mutex=PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t condAscenseur=PTHREAD_COND_INITIALIZER;

typedef struct {
	long type;
	int etageDemande;
	int etageAppuiBtn;
} MessageEtageDemande;

typedef struct {
	long type;
	int etage;
} MessageEtage;

int listeEtageDest[25];
int listeEtageDehors[25];
int clientArriverDest=0;

int getListeEtageDest(int etage){
	int res;
	pthread_mutex_lock(&mutexVariableGlobale);
	res=listeEtageDest[etage];
	pthread_mutex_unlock(&mutexVariableGlobale);
	return res;
}
int getListeEtageDehors(int etage){
	int res;
	pthread_mutex_lock(&mutexVariableGlobale);
	res=listeEtageDehors[etage];
	pthread_mutex_unlock(&mutexVariableGlobale);
	return res;
}

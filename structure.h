#include <pthread.h>

int msgid;

pthread_mutex_t mutexAttenteDansAscenseur=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexAttente=PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t mutexMessage=PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t attendreDansAscenseur,message;



typedef struct {
	long type;
	int etageDemande;
	int etageAppuiBtn;
} MessageEtageDemande;

typedef struct {
	long type;
	int etage;
} MessageEtage;

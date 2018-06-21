
//recuère le mutex
		if(ascenseur->nbDemandes < CAPACITE){ // => si pas plein, suit la queue étages demandés

			while(ascenseur->nbDemandes==0){
				//fprintf(stderr,"Ascenseur n°%d en attente à l'étage %d | %d/%d\n",ascenseur->numAscenseur,ascenseur->etageActuel,ascenseur->nbDemandes,CAPACITE);

			}

			if(ascenseur->queueEtageAppel->size !=0){

				allerA=front(ascenseur->queueEtageAppel);
				Dequeue(ascenseur->queueEtageAppel);
			}




		}
		else if(ascenseur->nbDemandes == CAPACITE){ // => si plein, dépose au premier étage demandé
			if(ascenseur->queueEtageAppel->size !=0){
				allerA=front(ascenseur->queueEtageAppel);
				Dequeue(ascenseur->queueEtageAppel);
			}

			if(ascenseur->etageActuel!=allerA){
				if(ascenseur->etageActuel<allerA){
					ascenseur->etageActuel++;
				}
				else if(ascenseur->etageActuel>allerA){
					ascenseur->etageActuel--;
				}

			}
			verifMessage(ascenseur);

		}

//on change d'étage
		if(ascenseur->etageActuel!=allerA){
			if(ascenseur->etageActuel<allerA){
				ascenseur->etageActuel++;
			}
			else if(ascenseur->etageActuel>allerA){
				ascenseur->etageActuel--;
			}

		}























		////////////////////////////////////////////////////////











		void test(Ascenseur *ascenseur){
			Enqueue(ascenseur->queueEtageAppel,0);
			Enqueue(ascenseur->queueEtageAppel,3);
			Dequeue(ascenseur->queueEtageAppel);
			while(1){
				fprintf(stderr,"ascenseur %d -> msgid %d\n",ascenseur->numAscenseur, ascenseur->msgid);
				//fprintf(stderr,"ascenseur n°%d voyage, front queueEtageAppel=%d\n", ascenseur->numAscenseur,front(ascenseur->queueEtageAppel));
			}
		}

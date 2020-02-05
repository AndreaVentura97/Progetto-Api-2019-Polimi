#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 50


typedef struct mandante {
	char nome [N];
	struct mandante *Next;
} mand;

typedef mand* ListaMand;

typedef struct relazione {
	char nomeRelazione [N];
	ListaMand listaMand;
	int count;
	struct relazione *Next;
} rel;

typedef rel* ListaRel;

typedef struct maggiorRiceventi {
	char nome [N];
	struct maggiorRiceventi *Next;
} mr;

typedef mr* ListaMr;

typedef struct report {
	char identificativo [N];
	ListaMr listaMr;
	int num;
	struct report *Next;
} rep;

typedef rep* ListaReport;

typedef struct entity {
  char nome [N];
  ListaRel listaRel;
  struct entity *Next;
} ent;

typedef ent* ListaEnt;

ListaReport listaReport;


ListaEnt AggiungiEnt (char name [], ListaEnt lista);

ListaEnt AggiungiRelazioneAEntity (char mandante [], char ricevente [], char relazione[], ListaEnt lista);

ListaEnt RestituisciNodoDalNome (char nomeIdentificativo [], ListaEnt lis1);

void StampaRelazioniPerOgniEnt (ListaEnt lista);

ListaReport inserisciRelazioneInOrdine (char relazione [], ListaEnt lista);

ListaRel AggiungiRelazione (char relazione [], ListaRel listaRel, char mandante [], char ricevente []);


int verificaPresenzaEnt (char nomeInserito[], ListaEnt listaDaVerificare);

int verificaPresenzaRel (ListaRel listaRel, char relazione [], char mandante [], char ricevente []);

int verificaReport (char relazione []);

ListaMand AggiungiMandante (ListaMand listaM, char nome []);

ListaMand cancellaMandante2 (ListaMand lista, char nome []);

ListaRel cancellaMandante1 (ListaRel lista, char nome []);

ListaEnt cancellaEnt2 (ListaEnt lista, char nome []);

ListaEnt cancellaEnt (ListaEnt lista, char nome []);

void StampaMandanti (ListaEnt lista); 

ListaEnt cancellaRelazione (char mandante [], char ricevente [], char relazione [], ListaEnt lista);

void costruisciReport (ListaEnt lista);

int contieneRelazione(char relazione []);

ListaReport inserisciReport2 (char relazione [], int num, char maggiorRicevente [], ListaReport l);

ListaMr inserisciRicevente (ListaMr l, char maggiorRicevente []);

void stampaReport ();

void stampaReport2 (ListaMr a);

void inserisciRelazioneMax (ListaEnt listaEnt);

ListaReport aggiornaMax (char relazione [], ListaEnt lista);

ListaReport inserisciRelazioneInOrdine (char relazione [], char ricevente []);

ListaReport aggiornaMaggiorRiceventi (ListaEnt lista);

ListaMr inserisciNomeInOrdine (ListaMr lista,char nome []);

int esiste (ListaEnt lista, char nome []);

int contieneMr (ListaMr lis, char n []);



void aggiornaMaggiorRiceventi2 (ListaReport lis, ListaEnt lista);

int contieneMandante (ListaMand l, char mandante[]);

ListaReport updateReportAddrel (char relazione [], ListaRel listaRel, char ricevente []);










int main (){
	ListaEnt listaEnt= NULL;
	listaReport = NULL;
	char s0 [N];
	char s1 [N];
	char s2 [N];
	char s3 [N];
	int flag = 0;
	while (flag == 0){
		scanf ("%s", &s0);
		if (strcmp(s0,"end")==0){
			break;
		}
		if (strcmp(s0, "addent")==0){
			scanf ("%s", &s1);
			listaEnt = AggiungiEnt (s1, listaEnt);
		}
		if (strcmp(s0, "addrel")==0){
			scanf ("%s", &s1);
			scanf ("%s", &s2);
			scanf ("%s", &s3);
			listaEnt = AggiungiRelazioneAEntity (s1,s2,s3, listaEnt);
		}
		if (strcmp(s0,"stampa")==0){
			StampaRelazioniPerOgniEnt (listaEnt);
		}
		if (strcmp(s0, "report")==0){
			//inserisciRelazioneMax(listaEnt);
			//aggiornaMaggiorRiceventi(listaEnt); 
			if (listaReport==NULL){
				printf("none\n");
			}
			else {
				stampaReport ();
			}
		
		}
		if (strcmp(s0,"delent")==0){
			scanf ("%s", &s1);
			listaEnt = cancellaEnt (listaEnt,s1);
			
		}
		if (strcmp(s0,"delrel")==0){
			scanf ("%s", &s1);
			scanf ("%s", &s2);
			scanf ("%s", &s3);
			listaEnt = cancellaRelazione (s1,s2,s3,listaEnt);
		}
	}
	
	return 0;
}

ListaEnt AggiungiEnt (char name [], ListaEnt lista){
	ListaEnt listaTemp;
	if (lista == NULL){
      	if (verificaPresenzaEnt(name,lista)==0){
      		listaTemp = (ListaEnt) malloc(sizeof(ent));
      		listaTemp -> listaRel = NULL;
      		strcpy (listaTemp->nome, name);
      		listaTemp->Next = NULL;
      		return listaTemp;
	  	}	
      
    }
    else {
    	if (verificaPresenzaEnt(name,lista)==0){
    		lista->Next = AggiungiEnt(name, lista->Next);
      		return lista;
		}
		return lista;
    }
}

	
int verificaPresenzaEnt (char nomeInserito [], ListaEnt listaDaVerificare){
	ListaEnt lis = listaDaVerificare;
	while (lis != NULL){
		if (strcmp(lis->nome,nomeInserito)==0){
			return 1;
		}
		lis = lis ->Next;
	}
	return 0;
}




ListaRel AggiungiRelazione (char relazione [], ListaRel listaRel, char mandante [], char ricevente []){
	ListaRel temp = listaRel;
	if (verificaPresenzaRel(listaRel, relazione,mandante,ricevente)==0){
		if (listaRel == NULL){
		temp = (ListaRel) malloc(sizeof(rel));
      	strcpy (temp->nomeRelazione, relazione);
      	temp->count=1;
      	temp->listaMand = NULL;
      	temp->listaMand = AggiungiMandante (temp->listaMand,mandante);
      	updateReportAddrel (relazione, temp, ricevente);
      	temp->Next = NULL;
      	return temp;
		}
		else {
		listaRel->Next = AggiungiRelazione(relazione, listaRel->Next, mandante,ricevente);
      	return listaRel;
		}	
	
	}
	return listaRel;
		
}


ListaReport updateReportAddrel (char relazione [], ListaRel listaRel, char ricevente []) {
		ListaReport p = listaReport;
		ListaRel q = listaRel;
		
		if (p==NULL){
			listaReport = inserisciRelazioneInOrdine(relazione,ricevente);
			
			return listaReport;
		}
		if (verificaReport(relazione)==0){
			listaReport = inserisciRelazioneInOrdine(relazione,ricevente);
			return listaReport;
		}
		while (p!=NULL){
			if (strcmp(relazione, p->identificativo)==0){
				if (q->count==p->num){
					p->listaMr = inserisciNomeInOrdine(p->listaMr, ricevente);
				}
				else if (q->count > p->num){
					p->listaMr = NULL;
					p->listaMr = inserisciNomeInOrdine(p->listaMr, ricevente);
					p->num = q->count;
				}
					
			}
			p = p->Next;
		}
		return listaReport;
	}
	
	





ListaMand AggiungiMandante (ListaMand listaM, char nome []){
	ListaMand temp = listaM;
	if (listaM==NULL){
		temp = (ListaMand) malloc (sizeof(mand));
		strcpy(temp->nome,nome);
		temp->Next=NULL;
		return temp;
	}
	else {
		listaM->Next = AggiungiMandante (listaM->Next,nome);
		return listaM;
	}
	return listaM;
}




ListaEnt AggiungiRelazioneAEntity (char mandante [], char ricevente [], char relazione[], ListaEnt lista){
	if (esiste(lista,ricevente)==0 || esiste(lista, mandante)==0){
		return lista;
	}
	ListaEnt lis = RestituisciNodoDalNome (ricevente, lista);
	lis->listaRel= AggiungiRelazione (relazione, lis->listaRel, mandante, ricevente);
	
	return lista;
	
}

int esiste (ListaEnt lista, char nome []){
	ListaEnt p = lista;
	while (p!=NULL){
		if (strcmp(p->nome,nome)==0){
			return 1;
		}
		p = p->Next;
	}
	return 0;
}

int verificaPresenzaRel (ListaRel listaRel, char relazione [], char mandante [], char ricevente []){
	ListaRel p = listaRel;
	while (p!=NULL){
		if (contieneMandante(p->listaMand,mandante)==1 && strcmp(p->nomeRelazione,relazione)==0){
			return 1;
		}
		if (strcmp(p->nomeRelazione,relazione)==0){
			p->count = p->count + 1;
			p->listaMand = AggiungiMandante (p->listaMand,mandante);
			updateReportAddrel (relazione, p, ricevente);
			return 1;
		}
		p = p->Next;
	}
	return 0;
}

int contieneMandante (ListaMand l, char mandante[]){
	ListaMand s = l;
	while (s!=NULL){
		if (strcmp(s->nome,mandante)==0){
			return 1;
		}
		s = s->Next;
	}
	return 0;
}

ListaEnt RestituisciNodoDalNome (char nomeIdentificativo [], ListaEnt lis1){
	ListaEnt temp = lis1;
	while (temp!=NULL){
		if (strcmp (nomeIdentificativo, temp->nome)==0){
			return temp;
		}
		temp = temp->Next;
	}
	return NULL;
}

void StampaRelazioniPerOgniEnt (ListaEnt lista){
	ListaEnt lis = lista;
	while (lis != NULL){
		printf ("nome membro -> %s \t", lis->nome);
		ListaRel lis2 = lis->listaRel;
		while (lis2 != NULL){
			printf ("relazione -> %s (%d)\t", lis2->nomeRelazione, lis2->count);
			lis2 = lis2->Next;
			
		}
		printf ("\n");
		lis = lis->Next;
	}
}
	
int verificaReport (char relazione []){
	ListaReport temp = listaReport;
	while (temp!=NULL){
		if (strcmp(relazione,temp->identificativo)==0){
			return 1;
		}
		temp=temp->Next;
	}
	return 0;
}

ListaEnt cancellaEnt (ListaEnt lista, char nome []){
	ListaEnt lis = lista;
	while (lis!=NULL){
		lis->listaRel = cancellaMandante1 (lis->listaRel,nome);
		lis = lis->Next;
	}
	lista = cancellaEnt2 (lista, nome);
	return lista;
}
	
	
	
ListaEnt cancellaEnt2 (ListaEnt lista, char nome []){
	ListaEnt p = lista;
	while (p!=NULL){
		if (strcmp(p->nome,nome)==0){
			p = p->Next;
			free(lista);
			return p;
		}
		else {
			lista->Next = cancellaEnt2 (lista->Next,nome);
			return lista;
			}
			
		}
		return lista;
}
	
	
ListaRel cancellaMandante1 (ListaRel lista, char nome []){
	ListaRel lis = lista;
	while (lis!=NULL){
		ListaMand cis = lis->listaMand;
		while (cis!=NULL){
			if (strcmp(cis->nome,nome)==0){
				lis->count = lis->count - 1;
				}
				
			cis = cis->Next;
		}
		lis->listaMand = cancellaMandante2(lis->listaMand,nome);
		if (lis->count < 0){
			lis->count==0 ;
		}
		else {
			lis = lis->Next;
		}
	}
	return lista;
}
	
	
	
	
	
	ListaMand cancellaMandante2 (ListaMand lista, char nome []){
		ListaMand p = lista;
		while (p!=NULL){
			if (strcmp(p->nome,nome)==0){
				p = p->Next;
				free(lista);
				return p;
			}
			else {
				lista->Next = cancellaMandante2 (lista->Next,nome);
				return lista;
			}
		}
		return lista;
	}
	
	
	ListaEnt cancellaRelazione (char mandante [], char ricevente[], char relazione [], ListaEnt lista){
		ListaEnt lis = lista;
		
		while (lis!=NULL){
			
			if (strcmp(lis->nome,ricevente)==0){
				
				ListaRel cis = lis->listaRel;
				while (cis!=NULL){
					
					if (strcmp(cis->nomeRelazione,relazione)==0){
						
						if (contieneMandante(cis->listaMand,mandante)==1){
							
							cis->listaMand = cancellaMandante2 (cis->listaMand,mandante);
							cis->count = cis->count - 1;
							
							
							if (cis->count < 0){
								cis->count == 0;
							}
						}
					}
					cis = cis->Next;
				}
			}
			lis = lis->Next;
		}
		return lista;
	}
	
	
	
	
	
	int contieneRelazione(char relazione []){
		ListaReport c = listaReport;
		while (c!=NULL){
			if (strcmp(c->identificativo,relazione)==0){
				return 1;
			}
			
			c = c->Next;
		}
		return 0;
	}
	
	
	
	
    
    
	
	
	void stampaReport (){
		ListaReport a = listaReport;
		while (a!=NULL){
			printf("%s ", a->identificativo);
			stampaReport2(a->listaMr);
			printf("%d; ", a->num);
			
			a = a->Next;
		}
		printf("\n");
	}
	
	void stampaReport2 (ListaMr a){
		ListaMr b = a;
		while (b!=NULL){
			printf ("%s ", b->nome);
			b = b->Next;
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	int max (char relazione [], ListaEnt lista){
		ListaEnt p = lista;
		int q = 0;
		while (p!=NULL){
			ListaRel p1 = p->listaRel;
			while (p1!=NULL){
				if (strcmp(p1->nomeRelazione,relazione)==0 && p1->count>q){
				q = p1->count;
				}	
			p1 = p1->Next;
			}
		
		p = p->Next;
		
		}
		return q;
	}
	
	void inserisciRelazioneMax (ListaEnt listaEnt){
		listaReport = NULL;
		ListaEnt lis = listaEnt;
		while (lis!=NULL){
			ListaRel cis = lis->listaRel;
			while (cis!=NULL){
				if (contieneRelazione(cis->nomeRelazione)==0){
					//listaReport = inserisciRelazioneInOrdine(cis->nomeRelazione,listaEnt);
					
				}
				else {
					listaReport = aggiornaMax(cis->nomeRelazione,listaEnt);
					
					}
				
				cis = cis->Next;
			}
			lis = lis->Next;
		}
	}
		
	
	
	ListaReport aggiornaMax (char relazione [], ListaEnt lista){
		ListaReport a = listaReport;
		while (a!=NULL){
			if (strcmp(a->identificativo,relazione)==0){
				a->num = max(relazione,lista);
			}
			a = a->Next;
		}
		return listaReport;
	}
	
	
	
	ListaReport inserisciRelazioneInOrdine (char relazione [], char ricevente []){
		ListaReport p,corr,prec;
		prec = NULL;
		corr = listaReport;
		while (corr!=NULL && strcmp(relazione,corr->identificativo)>0){
			prec = corr;
			corr = corr->Next;
		}
		p = (ListaReport)malloc (sizeof(rep));
		p->num = 1;
		p->listaMr = NULL;
		strcpy(p->identificativo,relazione);
		
		p->listaMr = inserisciNomeInOrdine (p->listaMr, ricevente);
		
		p->Next = corr;
		if (prec!=NULL){
			prec->Next = p;
			return listaReport;
		}
		else {
			return p;
		}
		
	}
	



	

	


	int contieneMr (ListaMr lis, char n []){
		ListaMr p = lis;
		while (lis!=NULL){
			if (strcmp(p->nome,n)==0){
				
				return 1;
			}
			lis = lis->Next;
		}
	
		return 0;
	}


	
	ListaMr inserisciNomeInOrdine (ListaMr lista,char n []){
		ListaMr p,corr,prec;
		prec = NULL;
		corr = lista;
		
		while (corr!=NULL && strcmp(n,corr->nome)>0){
			prec = corr;
			
			corr = corr->Next;
		}
		
		p = (ListaMr)malloc (sizeof(mr));
		strcpy(p->nome,n);
		
		p->Next = corr;
		if (prec!=NULL){
			prec->Next = p;
			return lista;
		}
		else {
			return p;
		}
	}
	

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 50

typedef struct mandante {
	char nome [N];
	struct mandante *padre;
	struct mandante *left;
	struct mandante *right;
} mand;

typedef mand* TreeMand;

typedef struct relazione {
	char nomeRelazione [N];
	TreeMand treeMand;
	int count;
	struct relazione *Next;
} rel;

typedef rel* ListaRel;


typedef struct entity {
  char nome [N];
  ListaRel listaRel;
  struct entity *padre;
  struct entity *left;
  struct entity *right;
} ent;

typedef ent* ListaEnt;

typedef struct maggiorRiceventi {
	char nome [N];
	struct maggiorRiceventi* padre;
	struct maggiorRiceventi* left;
	struct maggiorRiceventi* right;
} mr;

typedef mr* TreeMr;

typedef struct report {
	char id [N];
	int max;
	struct report *Next;
}rep;

typedef rep* ListaRep;

ListaRep listaRep;

ListaEnt addent (ListaEnt lista, char nome []);

void stampaEnt (ListaEnt lista);

void stampaRel(ListaRel lista);

TreeMand AggiungiMandante(TreeMand tree, char nome []);

ListaEnt addrel (ListaEnt listaEnt, char relazione [], char ricevente [], char mandante[]);

ListaRel AggiungiRelazione (char relazione [], ListaRel listaRel, char mandante []);

ListaEnt RestituisciNodoDalNome(char ricevente [], ListaEnt lista);

int contieneMandante (TreeMand tree, char mandante []);

int verificaPresenzaRel(ListaRel listaRel, char relazione[] , char mandante[]);

int contieneEnt (ListaEnt lista, char nome []);

void costruisciReport (ListaEnt listaEnt);

ListaRep inserisciInOrdine (ListaRel lista);

void stampaReport (ListaEnt lista);

void stampaReportBis (ListaEnt lista, char id [], int num);

int verificaRep (ListaRel lista);







int main (){
	ListaEnt listaEnt= NULL;
	listaRep = NULL;
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
			listaEnt = addent(listaEnt,s1);
		}
		if (strcmp(s0, "stampa")==0){
			stampaEnt(listaEnt);
			
		}
		if (strcmp(s0, "addrel")==0){
			scanf ("%s", &s1);
			scanf ("%s", &s2);
			scanf ("%s", &s3);
			listaEnt = addrel(listaEnt,s3,s2,s1);
		}
		if (strcmp(s0, "report")==0){
			costruisciReport (listaEnt);
			stampaReport(listaEnt);
		}
		
		
		}
	
	return 0;
}


ListaEnt addent (ListaEnt listaEnt, char nome []){
	if (contieneEnt(listaEnt,nome)==1){
		return listaEnt;
	}
	ListaEnt listaAgg = (ListaEnt) malloc(sizeof(ent));
	strcpy(listaAgg->nome,nome);
	listaAgg->padre = NULL;
	listaAgg->listaRel = NULL;
	listaAgg->left = NULL;
	listaAgg->right = NULL;
	ListaEnt y = NULL;
	ListaEnt x = listaEnt;
	while (x!=NULL){
		y = x;
		if (strcmp(nome,listaEnt->nome)<0){
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	listaAgg->padre = y;
	if (y==NULL){
		listaEnt = listaAgg;
	}
	else if (strcmp(listaAgg->nome, y->nome)<0){
		y->left = listaAgg;
	}
	else {
		y->right = listaAgg;
	}
	return listaEnt;
}

int contieneEnt (ListaEnt lista, char nome []){
	ListaEnt p = lista;
	if (p==NULL){
		return 0;
	}
	if (strcmp(nome,p->nome)==0){
		return 1;
	}
	if (strcmp(nome, p->nome)<0){
		return contieneEnt (p->left, nome);
	}
	else {
		return contieneEnt(p->right, nome);
	}
}

void stampaEnt (ListaEnt lista){
	ListaEnt a = lista;
	if (a!=NULL){
		stampaEnt(a->left);
		printf("%s\n", a->nome);
		stampaRel(a->listaRel);
		stampaEnt(a->right);
	}
		
}

void stampaRel(ListaRel lista){
	ListaRel b = lista;
	while (b!=NULL){
		printf("%s (%d)", b->nomeRelazione, b->count);
		b = b->Next;
	}
	printf("\n");
}

ListaEnt addrel (ListaEnt listaEnt, char relazione [], char ricevente [], char mandante[]){
	if (contieneEnt(listaEnt,ricevente)==0 || contieneEnt(listaEnt, mandante)==0){
		return listaEnt;
	}
	ListaEnt lis = RestituisciNodoDalNome (ricevente, listaEnt);
	lis->listaRel = AggiungiRelazione(relazione,lis->listaRel,mandante);
	return listaEnt;
	
}

ListaRel AggiungiRelazione (char relazione [], ListaRel listaRel, char mandante []){
	ListaRel temp = listaRel;
	if (verificaPresenzaRel(listaRel, relazione,mandante)==0 ){
		if (listaRel == NULL){
		temp = (ListaRel) malloc(sizeof(rel));
      	strcpy (temp->nomeRelazione, relazione);
      	temp->count=1;
      	temp->treeMand = NULL;
      	temp->treeMand = AggiungiMandante (temp->treeMand,mandante);
      	temp->Next = NULL;
      	return temp;
		}
		else {
		listaRel->Next = AggiungiRelazione(relazione, listaRel->Next, mandante);
      	return listaRel;
		}	
	
	}
	return listaRel;
		
}

int verificaPresenzaRel(ListaRel listaRel, char relazione[] , char mandante[]){
	ListaRel p = listaRel;
	while (p!=NULL){
		if (contieneMandante(p->treeMand,mandante)==1 && strcmp(p->nomeRelazione,relazione)==0){
			return 1;
		}
		if (strcmp(p->nomeRelazione,relazione)==0){
			p->count = p->count + 1;
			p->treeMand = AggiungiMandante (p->treeMand,mandante);
			return 1;
		}
		p = p->Next;
	}
	return 0;
}

int contieneMandante (TreeMand tree, char mandante []){
	TreeMand p = tree;
	if (p==NULL){
		return 0;
	}
	if (strcmp(mandante,p->nome)==0){
		return 1;
	}
	if (strcmp(mandante, p->nome)<0){
		return contieneMandante(p->left, mandante);
	}
	else {
		return contieneMandante(p->right, mandante);
	}
}

TreeMand AggiungiMandante(TreeMand tree, char nome []){
	TreeMand a = (TreeMand)malloc(sizeof(mand));
	strcpy(a->nome,nome);
	a->padre = NULL;
	a->left = NULL;
	a->right = NULL;
	TreeMand y = NULL;
	TreeMand x = tree;
	while (x!=NULL){
		y = x;
		if (strcmp(nome,x->nome)<0){
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	a->padre = y;
	if (y==NULL){
		tree = a;
	}
	else if (strcmp(a->nome, y->nome)<0){
		y->left = a;
	}
	else {
		y->right = a;
	}
	return tree;
}

ListaEnt RestituisciNodoDalNome(char ricevente [], ListaEnt lista){
	ListaEnt p = lista;
	if (p==NULL || strcmp(ricevente,p->nome)==0){
		return p;
	}
	if (strcmp(ricevente, p->nome)<0){
		return RestituisciNodoDalNome(ricevente, p->left);
	}
	else {
		return RestituisciNodoDalNome(ricevente, p->right);
	}
	
}

void costruisciReport (ListaEnt listaEnt){
	ListaEnt lis = listaEnt;
	if (lis!=NULL){
		costruisciReport (lis->left);
		ListaRel bis = lis->listaRel;
		while (bis!=NULL){
			if (verificaRep(bis)==0) {
				listaRep = inserisciInOrdine (bis);
			}
			bis = bis->Next;	
			
		}
		costruisciReport (lis->right);
	}
}

int verificaRep (ListaRel lista){
	ListaRep a = listaRep;
	while (a!=NULL){
		if (strcmp(a->id,lista->nomeRelazione)==0){
			if (a->max<lista->count){
				a->max = lista->count;
			}
			return 1;
		}
		a = a->Next;
	}
	return 0;
}
	
	
	
	



ListaRep inserisciInOrdine (ListaRel lista){
	ListaRep punt,puntCor,puntPrec;
	puntPrec = NULL;
	puntCor = listaRep;
	
	while (puntCor!=NULL && lista->nomeRelazione>puntCor->id ){
		puntPrec = puntCor;
		puntCor = puntCor->Next;
	}
	punt = (ListaRep) malloc (sizeof(rep));
	strcpy(punt->id,lista->nomeRelazione);
	
	punt->max = lista->count;
	punt->Next = puntCor;
	if (puntPrec!=NULL){
		puntPrec->Next = punt;
		//printf("ritorna listaRep %s", listaRep->id);
		return listaRep;
	}
	else 
		//printf("ritorna punt %s", punt->id);
		return punt;

}

void stampaReport (ListaEnt lista){
	
	ListaRep a = listaRep;
	if (a==NULL){
		printf("none");
	}
	while (a!=NULL){
		printf("%s ", a->id);
		stampaReportBis(lista,a->id,a->max);
		printf ("%d", a->max);
		printf("; ");
		a = a->Next;
	}
	printf("\n");
}

void stampaReportBis (ListaEnt lista, char id [], int num){
	ListaEnt lis = lista;
	
	ListaRel bis = lis->listaRel;
	if (lis!=NULL){
		
		if (lis->left!=NULL){
			stampaReportBis (lis->left, id, num);
		}
		
		
		while (bis!=NULL){
			if(strcmp(bis->nomeRelazione,id)==0 && num==bis->count){
			printf("%s ", lis->nome);
			}
			bis = bis->Next;
		}
		
		
		
		if (lis->right!=NULL){
			stampaReportBis(lis->right,id, num);
		}
	}
}












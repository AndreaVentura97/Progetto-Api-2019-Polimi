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

ListaEnt globalEnt;

TreeMand globalTree;

ListaEnt addent (ListaEnt lista, char nome []);

void stampaEnt (ListaEnt lista);

void stampaRel(ListaRel lista);

void stampaMand (TreeMand tree);

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

ListaRel cancellaRelazione(ListaRel lista, char nomeRelazione[]);

void cancellaMandante (TreeMand tree, char mandante []);

TreeMand treeMinimum (TreeMand x);

TreeMand treeSuccessor (TreeMand x);



void delrel(ListaEnt lista, char mandante [], char ricevente [], char relazione[]);

void delent(ListaEnt listaEnt, char nome[]);

ListaEnt treeMinimum2 (ListaEnt x);

ListaEnt treeSuccessor2 (ListaEnt x);

TreeMand cerca2(TreeMand a, char k[]);

ListaEnt cerca(ListaEnt a, char k[]);

void aggiornaStruttura (ListaEnt lista, char ricevente []);

void eliminaRelazioni (ListaEnt lista, char ricevente []);

void svuotaMandanti (TreeMand tree);

void svuotaAlbero(ListaEnt lista);





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
            globalEnt=listaEnt;
        }
        if (strcmp(s0, "stampa")==0){
            listaEnt=globalEnt;
            stampaEnt(listaEnt);

        }
        if (strcmp(s0, "addrel")==0){
            scanf ("%s", &s1);
            scanf ("%s", &s2);
            scanf ("%s", &s3);
            listaEnt = addrel(listaEnt,s3,s2,s1);
            globalEnt=listaEnt;
        }
        if (strcmp(s0, "report")==0){
            listaRep=NULL;
            costruisciReport (listaEnt);
            stampaReport(listaEnt);
        }
        if (strcmp(s0, "delrel")==0){
            scanf ("%s", &s1);
            scanf ("%s", &s2);
            scanf ("%s", &s3);
            delrel(listaEnt, s1, s2,s3);
            globalEnt=listaEnt;

        }
        if (strcmp(s0,"prova")==0){
            //svuotaMandanti(listaEnt->listaRel->treeMand);

            svuotaAlbero(globalEnt);


            //listaEnt->listaRel->treeMand = cancellaMandante(listaEnt->listaRel->treeMand,"c");
        }

        if (strcmp(s0,"delent")==0){
            scanf("%s", &s1);
            listaEnt=globalEnt;
            if (contieneEnt(listaEnt,s1)==1) {
                delent(listaEnt, s1);
                listaEnt=globalEnt;
                eliminaRelazioni(listaEnt,s1);
                //aggiornaStruttura(listaEnt, s1);
                listaEnt=globalEnt;


            }
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
        if (strcmp(nome,x->nome)<0){
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
        if (a->listaRel!=NULL) stampaMand (a->listaRel->treeMand);
        stampaEnt(a->right);
    }

}

void stampaMand (TreeMand tree){

    TreeMand p = tree;
    if (p!=NULL){
        if(p->left!=NULL) stampaMand(p->left);
        printf("\t%s", p->nome);
        printf("\n");
        if (p->right!=NULL) stampaMand(p->right);
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
        if (strcmp(a->nome,x->nome)<0){
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
    if(lista->count==0){
        return 1;
    }
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

    while (puntCor!=NULL && strcmp(lista->nomeRelazione,puntCor->id)>0){
        puntPrec = puntCor;
        puntCor = puntCor->Next;
    }
    punt = (ListaRep) malloc (sizeof(rep));
    strcpy(punt->id,lista->nomeRelazione);

    punt->max = lista->count;
    punt->Next = puntCor;
    if (puntPrec!=NULL){
        puntPrec->Next = punt;

        return listaRep;
    }
    else

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


void delrel(ListaEnt lista, char mandante [], char ricevente [], char relazione[]){

    ListaEnt lis = lista;


    if (lis!=NULL){
        ListaRel bis = lis->listaRel;
        if (lis->left!=NULL) delrel(lis->left,mandante,ricevente,relazione);

        while (bis!=NULL){
            if (strcmp(bis->nomeRelazione, relazione)==0){

                if (strcmp(lis->nome, ricevente) == 0){
                    if (contieneMandante(bis->treeMand, mandante) == 1){
                        bis->count = bis->count - 1;

                        if (bis->count>=0) {
                            globalTree=bis->treeMand;
                            //bis->treeMand = cancellaMandante(bis->treeMand, mandante);
                            cancellaMandante(globalTree, mandante);
                            bis->treeMand=globalTree;
                        }

                        if (bis->count < 0) {
                            //lis->listaRel = cancellaRelazione(lis->listaRel, bis->nomeRelazione);
                            bis->count = 0;

                        }
                    }
                }
            }
            bis = bis->Next;
        }






        if (lis->right!=NULL) delrel(lis->right,mandante,ricevente,relazione);

    }

}


ListaRel cancellaRelazione(ListaRel lista, char nomeRelazione[]){
    ListaRel p = lista;
    while (p!=NULL){
        if (strcmp(p->nomeRelazione,nomeRelazione)==0){
            p = p->Next;
            free(lista);
            return p;
        }
        else {
            lista->Next = cancellaRelazione (lista->Next,nomeRelazione);
            return lista;
        }
    }
    return lista;

}

TreeMand cerca2(TreeMand a, char k[]){
    TreeMand x = a;
    if (x==NULL || strcmp(k,x->nome)==0){
        return x;
    }
    if (strcmp(k,x->nome)<0){
        return cerca2(x->left,k);
    }
    else
    {
        return cerca2(x->right,k);
    }
}

void cancellaMandante (TreeMand tree, char mandante []){

    TreeMand z = cerca2(tree,mandante);

    TreeMand y;
    TreeMand x;

    if (z->left==NULL || z->right==NULL){
        y = z;

    }
    else {
        y = treeSuccessor(z);
    }


    if (y->left!=NULL){
        x = y->left;


    }
    else {
        x = y->right;

    }
    if (x!=NULL){
        x->padre = y->padre;


    }
    if (y->padre==NULL){
        globalTree = x;

    }
    else if (y == y->padre->left){
        y->padre->left = x;

    }
    else {
        y->padre->right = x;


    }
    if (y!=z){
        strcpy(z->nome,y->nome);

    }


}

TreeMand treeSuccessor (TreeMand x){
    if (x->right!=NULL){
        return treeMinimum (x->right);
    }
    TreeMand y = x->padre;
    while (y!=NULL && x == y->right){
        x=y;
        y = y->padre;
    }
    return y;
}

ListaEnt treeSuccessor2 (ListaEnt x){
    if (x->right!=NULL){
        return treeMinimum2 (x->right);
    }
    ListaEnt y = x->padre;
    while (y!=NULL && x == y->right){
        x=y;
        y = y->padre;
    }
    return y;
}

TreeMand treeMinimum (TreeMand x){
    while (x->left!=NULL){
        x = x->left;
    }
    return x;
}

ListaEnt treeMinimum2 (ListaEnt x){
    while (x->left!=NULL){
        x = x->left;
    }
    return x;
}

ListaEnt cerca(ListaEnt a, char k[]){
    ListaEnt x = a;
    if (x==NULL || strcmp(k,x->nome)==0){
        return x;
    }
    if (strcmp(k,x->nome)<0){
        return cerca(x->left,k);
    }
    else return cerca(x->right,k);
}

void delent(ListaEnt listaEnt, char nome[]){

    ListaEnt z = cerca(globalEnt,nome);
    //z->listaRel=NULL;
    ListaEnt y;
    ListaEnt x;
    if (z->left==NULL || z->right==NULL){
        y = z;

    }
    else {
        y = treeSuccessor2(z);

    }
    if (y->left!=NULL){
        x = y->left;

    }
    else {
        x = y->right;
    }
    if (x!=NULL){
        x->padre = y->padre;

    }
    if (y->padre==NULL){
        globalEnt = x;

    }
    else if (y== y->padre->left){
        y->padre->left = x;

    }
    else {
        y->padre->right = x;

    }
    if (y!=z){
        strcpy(z->nome,y->nome);
        
    }

}

void aggiornaStruttura (ListaEnt lista, char ricevente []){
    ListaEnt lis = lista;
    if (lis!=NULL){
        if (lis->left!=NULL){
            aggiornaStruttura(lis->left,ricevente);
        }
        if(strcmp(ricevente,lis->nome)!=0) {
            ListaRel bis = lis->listaRel;
            while (bis != NULL) {
                if (contieneMandante(bis->treeMand, ricevente) == 1) {
                    //delrel(lis,ricevente,lis->nome,bis->nomeRelazione);
                    globalTree = bis->treeMand;
                    //bis->treeMand = cancellaMandante(bis->treeMand,ricevente);
                    cancellaMandante(globalTree, ricevente);
                    bis->treeMand = globalTree;
                    bis->count = bis->count - 1;
                    if (bis->count < 0) {
                        //bis = cancellaRelazione(bis,bis->nomeRelazione);
                        bis->count = 0;
                    }
                }
                bis = bis->Next;
            }
        }
        else {
            delent(globalEnt,ricevente);
        }
        if (lis->right!=NULL){
            aggiornaStruttura(lis->right,ricevente);
        }
    }
}

void eliminaRelazioni (ListaEnt lista, char ricevente []){
    ListaEnt lis = lista;
    if (lis!=NULL){
        if (lis->left!=NULL) {
            eliminaRelazioni(lis->left,ricevente);
        }
        if (strcmp(lis->nome,ricevente)==0){
            ListaRel bis = lis->listaRel;
            while (bis!=NULL){
                globalTree=bis->treeMand;
                svuotaMandanti(globalTree);
                bis->treeMand=globalTree;
                //cancellaRelazione(bis,bis->nomeRelazione);

                bis = bis->Next;
            }
        }
        if (lis->right!=NULL) {
            eliminaRelazioni(lis->right,ricevente);
        }
    }
}

void svuotaMandanti (TreeMand tree){

    if (tree!=NULL){
        if (tree->left!=NULL){
            svuotaMandanti(tree->left);
        }
        cancellaMandante(tree,tree->nome);
        if (tree->right!=NULL){
            svuotaMandanti(tree->right);
        }
    }
}

void svuotaAlbero(ListaEnt lista){

    if (lista!=NULL){
        if (lista->left!=NULL){
            svuotaAlbero(lista->left);
        }
        delent(lista,lista->nome);
        if (lista->right!=NULL){
            svuotaAlbero(lista->right);
        }
    }
}

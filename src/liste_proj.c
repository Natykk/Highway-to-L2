#include <stdlib.h>
#include <../head/liste_proj.h>

void init_liste_proj(void){
//Cree la liste constitue du seul drapeau
    drapeau = malloc(sizeof(t_element));
    drapeau->pred = drapeau;
    drapeau->succ = drapeau;
    ec = drapeau;
}

int liste_vide(void){
    return (drapeau->succ == drapeau);
}

int hors_liste(void){
    return (ec == drapeau);
}

void en_tete(void){
    if(!liste_vide())
        ec = drapeau->succ;
}

void en_queue(void){
    if(!liste_vide())
        ec = drapeau->pred;
}

void precedent(void){
    if(!liste_vide())
        ec = ec->pred;
}

void suivant(void){
    if(!liste_vide())
        ec = ec->succ;
}

void valeur_elt(projectile_t ** proj){
    if(!liste_vide())
        (*proj) = ec->proj;
}

void modif_elt(projectile_t * proj){
    if(!hors_liste())
        ec->proj = proj;
}

void oter_elt(void){
    t_element * old;

    if(!hors_liste()){
        old = ec;
        ec->pred->succ = ec->succ;
        ec->succ->pred = ec->pred;
        ec=ec->pred;
        old->proj = NULL;
        free(old);
    }

}

void ajout_droit(projectile_t * proj){
    t_element * nouv;

    if(!hors_liste() || liste_vide()){
        nouv = malloc(sizeof(t_element));
        nouv->proj=proj;
        //Chainage nouv
        nouv->pred=ec;
        nouv->succ=ec->succ;
        //Chainage autour
        ec->succ->pred = nouv;
        ec->succ = nouv;
        
        ec=nouv;
    }
}

void ajout_gauche(projectile_t * proj){
    t_element * nouv;

    if(!hors_liste() || liste_vide()){
        nouv = malloc(sizeof(t_element));
        nouv->proj=proj;
        //Chainage nouv
        nouv->succ=ec;
        nouv->pred=ec->pred;
        //Chainage autour
        ec->pred->succ = nouv;
        ec->pred = nouv;
        
        ec=nouv;
    }
}
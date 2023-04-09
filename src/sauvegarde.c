#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/sha.h>
#include <unistd.h>

#include "../head/sauvegarde.h"
#include "../head/arbre.h"
#include "../head/inventaire.h"



#define BLOCK_SIZE 16

#define SHA256_DIGEST_LENGTH 32

int sha256_file(const char *path, char *hash) {
    FILE *file;
    SHA256_CTX sha256_ctx;
    unsigned char buffer[BUFSIZ];
    int bytesRead;
    unsigned char sha256_hash[SHA256_DIGEST_LENGTH];
    int i;

    // ouvre le fichier
    file = fopen(path, "rb");
    if (!file) {
        return -1;
    }

    // Initialise le hash
    SHA256_Init(&sha256_ctx);

    // Calcule le hash du fichier avec des morceau de 521 octets 
    while ((bytesRead = fread(buffer, 1, BUFSIZ, file)) > 0) {
        SHA256_Update(&sha256_ctx, buffer, bytesRead);
    }

    // Finalise le hash et le convertit en chaîne de caractère hexadécimale
    SHA256_Final(sha256_hash, &sha256_ctx);
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash[i * 2], "%02x", sha256_hash[i]);
    }

    // Ferme le fichier
    fclose(file);

    return 0;
}


int de_chiffre_fichier_AES(const char *clef, const char *fichier_entree, const char *fichier_sortie,int mode) {
    AES_KEY cle;
    unsigned char iv[BLOCK_SIZE], buffer[BLOCK_SIZE], dechiffr[BLOCK_SIZE];
    int bytes_lus, bytes_ecrits;
    FILE *fichier_entree_ptr, *fichier_sortie_ptr;

    // Initialisation de la clé et du vecteur d'initialisation
    if(mode==AES_DECRYPT){
        if (AES_set_decrypt_key((const unsigned char*)clef, 128, &cle) < 0) {
            return -1;
        }
    }
    if(mode==AES_ENCRYPT){
        if (AES_set_encrypt_key((const unsigned char*)clef, 128, &cle) < 0) {
        return -1;
        }
    }
    memset(iv, 0, BLOCK_SIZE);

    // Ouverture des fichiers d'entrée et de sortie
    fichier_entree_ptr = fopen(fichier_entree, "rb");
    if (fichier_entree_ptr == NULL) {
        return -1;
    }
    fichier_sortie_ptr = fopen(fichier_sortie, "wb");
    if (fichier_sortie_ptr == NULL) {
        fclose(fichier_entree_ptr);
        return -1;
    }

    // Lecture et déchiffrement des blocs de données
    while ((bytes_lus = fread(buffer, 1, BLOCK_SIZE, fichier_entree_ptr)) > 0) {
        if(mode==AES_ENCRYPT){
            AES_cbc_encrypt(buffer, dechiffr, bytes_lus, &cle, iv,AES_ENCRYPT);
        }
        if(mode==AES_DECRYPT){
            AES_cbc_encrypt(buffer, dechiffr, bytes_lus, &cle, iv,AES_DECRYPT);
        }
        bytes_ecrits = fwrite(dechiffr, 1, bytes_lus, fichier_sortie_ptr);
        if (bytes_ecrits != bytes_lus) {
            fclose(fichier_entree_ptr);
            fclose(fichier_sortie_ptr);
            return -1;
        }
    }
    // Fermeture des fichiers
    fclose(fichier_entree_ptr);
    fclose(fichier_sortie_ptr);

    return 0;
}
/**
 * \fn int one_next_cpt_unlock(t_competence *competence)
 * @brief Renvoie l'indice de la première compétence suivante qui n'est pas acquise
 * @param competence une compétence
 * @return l'indice de la première compétence suivante qui n'est pas acquise
*/
int one_next_cpt_unlock(t_competence *competence)
{
    int i;
    for (i = 0; i < competence->nb_suiv; i++)
    {
        if (competence->suivantes[i]->competence_acquise == acquis)
        {
            return i;
        }
    }
    return -1;
}
/**
 * \fn int cpt_aquise(FILE *sauv, t_arbre *arbre)
 * @brief Sauvegarde les compétences acquises dans le fichier sauvegarde.txt
 * @param sauv le fichier sauvegarde.txt
 * @param arbre l'arbre de compétences
 * @return 1 si la sauvegarde s'est bien déroulée, 0 sinon
*/
int cpt_aquise(FILE *sauv, t_arbre *arbre)
{
    int ind = -1;
    t_competence *cpt_actuelle = arbre->competence[0];
    if (cpt_actuelle->competence_acquise != non_acquis)
    {
        do
        {
            fprintf(sauv, "%s\n", cpt_actuelle->nom);
            if ((ind = one_next_cpt_unlock(cpt_actuelle)) > -1)
            {
                cpt_actuelle = cpt_actuelle->suivantes[ind];
            }
        } while (cpt_actuelle->competence_acquise != non_acquis && ind > -1);
    }
    fprintf(sauv, "END_OF_CPT\n");
    return 1;
}

int sauvegarde(entite_t *personnage, int num_etage,unsigned char *key){
    if (personnage != NULL)
    {
        FILE * f_sauv = NULL;
        f_sauv = fopen("../sauv/sauvegarde.txt", "w");
        if(f_sauv == NULL){
            printf("pb de création\n");
            return 0;
        }
        if (personnage->nom != NULL && strcmp(personnage->nom, "")){
            fprintf(f_sauv, "%s\n", personnage->nom);
        }
        else
        {
            fprintf(f_sauv, "None\n");
        }
        
        /* Classe du personnage */
        if (personnage->arbre == NULL)
        {
            fprintf(f_sauv, "%d\n", AUCUNE_CLASSE);
        }
        else if (personnage->arbre->classe == ASSASSIN)
        {
            fprintf(f_sauv, "%d\n", ASSASSIN);
        }
        else if (personnage->arbre->classe == GUERRIER)
        {
            fprintf(f_sauv, "%d\n", GUERRIER);
        }
        else if (personnage->arbre->classe == MAGE)
        {
            fprintf(f_sauv, "%d\n", MAGE);
        }
        else if (personnage->arbre->classe == ARCHER)
        {
            fprintf(f_sauv, "%d\n", ARCHER);
        }

        /* Compétences acquises */
        if(personnage->arbre != NULL){
            cpt_aquise(f_sauv, personnage->arbre);
        }
        else{
            fprintf(f_sauv, "None\n");
        }

        /* Numéro de l'étage */
        fprintf(f_sauv, "%d\n", num_etage);

        /* Inventaire du personnage */

        for (int i = 0; i < NB_OBJET; i++)
        {
            fprintf(f_sauv, "%d\n", personnage->inventaire->nb[i]);
        }
        
        fclose(f_sauv);
        de_chiffre_fichier_AES(key,"../sauv/sauvegarde.txt","../sauv/sauvegarde_crypt.data",AES_ENCRYPT);

        FILE* file = fopen("../sauv/sauvegarde.txt", "w");
        fclose(file);

        
        char hash[(SHA256_DIGEST_LENGTH*2) + 1];
    if (sha256_file("../sauv/sauvegarde_crypt.data", hash) != 0) {
        printf("Erreur dans le calcul du hash \n");
        return 1;
    }
    
        FILE* f_hash = fopen("../sauv/sauvegarde.hash", "w");
        if(f_hash == NULL){
            printf("pb fichier hash\n");
            return 0;
        }
        fprintf(f_hash, "%s\n", hash);
        fclose(f_hash);

       
    }
    else
    {
        printf("Le personnage n'a pas été initialisé : impossible de sauvegarder\n");
        return 0;
    }
    return 1;
}


/**
 * \fn int appliquer(entite_t *personnage, t_competence *competence)
 * @brief Applique les effets d'une compétence sur un personnage
 * @param personnage le personnage
 * @param competence la compétence
 * @return 1 si l'application s'est bien déroulée, 0 sinon
*/
int appliquer(entite_t *personnage, t_competence *competence)
{
    personnage->degats *= competence->buff.buff_degat;
    personnage->vie *= competence->buff.buff_vie;
    personnage->vitesse_att *= competence->buff.buff_vit_att;
    personnage->vitesse_depl *= competence->buff.buff_vit_depl;
    personnage->perim_detect += competence->buff.perim_detect - 1;
    return 1;
}
/**
 * \fn int chargement(entite_t **personnage)
 * @brief Charge les données d'une sauvegarde dans un personnage
 * @param personnage le personnage
 * @return 1 si le chargement s'est bien déroulé, 0 sinon
*/

int chargement(entite_t **personnage, unsigned char *key)
{
    de_chiffre_fichier_AES(key,"../sauv/sauvegarde_crypt.data","../sauv/sauvegarde.txt",AES_DECRYPT);
    FILE *f_sauv = fopen("../sauv/sauvegarde.txt", "r");
    if (f_sauv)
    {
        /* Nom personnage */
        fscanf(f_sauv, "%s", (*personnage)->nom);

        /* Classe du personnage */
        int classe;
        fscanf(f_sauv, "%d", &classe);
        switch (classe){
            case ARCHER:
                init_arbre(&(*personnage)->arbre, cpt_archer, classe);
                break;
            case ASSASSIN:
                init_arbre(&(*personnage)->arbre, cpt_assassin, classe);
                break;
            case GUERRIER:
                init_arbre(&(*personnage)->arbre, cpt_guerrier, classe);
                break;
            case MAGE:
                init_arbre(&(*personnage)->arbre, cpt_mage, classe);
                break;
            default: 
                (*personnage)->arbre = NULL;
                break;
        }

        /* Nom des compétences */
        char c;
        char *nom_cpt = malloc(sizeof(char) * 50);

        fscanf(f_sauv, "%c", &c);
        fgets(nom_cpt, 50, f_sauv);
        nom_cpt[strlen(nom_cpt) - 1] = '\0';
    
        if(strcmp(nom_cpt, "None") && classe != AUCUN){
            t_competence *racine = (*personnage)->arbre->competence[0];
            while (strcmp(nom_cpt, "None") && strcmp(nom_cpt, "END_OF_CPT"))
            {
                if (!strcmp(nom_cpt, racine->nom))
                {
                    racine->competence_acquise = acquis;
                    appliquer(*personnage, racine);
                    fgets(nom_cpt, 50, f_sauv);
                    nom_cpt[strlen(nom_cpt) - 1] = '\0';
                    for (int i = 0; i < racine->nb_suiv; i++)
                    {
                        if (!strcmp(racine->suivantes[i]->nom, nom_cpt))
                        {
                            racine = racine->suivantes[i];
                        }
                    }
                }
            }
        }
        else{
            (*personnage)->arbre = NULL;
        }
        free(nom_cpt);
        nom_cpt = NULL;

        /* numéro de l'étage sauvegardé */
        int num_etage;
        fscanf(f_sauv, "%d", &num_etage);
        
        /* complémentation de l'inventaire */
        for (int i = 0; i < NB_OBJET; i++)
        {
            fscanf(f_sauv, "%d", &(*personnage)->inventaire->nb[i]);
        }
        FILE* file = fopen("../sauv/sauvegarde.txt", "w");
        fclose(file);

        return num_etage;
    }
    else
    {
        printf("Erreur : impossible d'ouvrir le fichier de sauvegarde\n");
        return -1;
    }
}

/*
int main(){
    t_arbre * mage;
    init_arbre(&mage, cpt_mage, MAGE);
    entite_t * personnage;
    personnage = creer_personnage(personnage);
    personnage = init_inventaire_personnage(personnage);
    //afficher_entite(personnage);

    int rang;
    rang=acces_obj("Grimoire");
    if(rang>-1){
        personnage->inventaire->nb[rang] = 30;
        
    }

    rang=acces_obj("Or");
    if(rang>-1){
        personnage->inventaire->nb[rang] = 50;
        
    }

    rang=acces_obj("Green Goo");
    if(rang>-1){
        personnage->inventaire->nb[rang] = 20;
        
    }

    rang=acces_obj("Grey Goo");
    if(rang>-1){
        personnage->inventaire->nb[rang] = 30;
        
    }

    rang=acces_obj("Griffe");
    if(rang>-1){
        personnage->inventaire->nb[rang] = 20;
        
    }

    rang=acces_obj("Red Goo");
    if(rang>-1){
        personnage->inventaire->nb[rang] = 20;
        
    }

    rang=acces_obj("Tetes");
    if(rang>-1){
        personnage->inventaire->nb[rang] = 20;
        
    }

    afficher_inventaire(personnage);
    competence_debloquer(personnage, mage->competence[0], mage);
    competence_debloquer(personnage, mage->competence[1], mage);
    competence_debloquer(personnage, mage->competence[3], mage);
    competence_debloquer(personnage, mage->competence[5], mage);
    competence_debloquer(personnage, mage->competence[9], mage);
    sauvegarde(personnage, 2,"0123456789abcdef","01234567890123456");
    //printf("--/\\-SAUVEGARDE---/\\-\n");
    detruire_arbre(&personnage->arbre);
    detruire_entitee(&personnage);
    
    personnage = creer_personnage(personnage);
    personnage = init_inventaire_personnage(personnage);

    chargement(&personnage,"0123456789abcdef","01234567890123456");
    //printf("--/\\-CHARGEMENT-/\\---\n");
    afficher_entite(personnage);
    //printf("----AFFICHAGE TERMINER----\n");
    //aff_classe(personnage->arbre);
    //afficher_inventaire(personnage);
    detruire_arbre(&personnage->arbre);
    detruire_entitee(&personnage);
}
*/
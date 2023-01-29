#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mapStruct.h"

/**
 * @file mapStruct.c
 * @brief Fichier contenant les fonctions de gestion de la map
 * @version 1.0
 * @date 28/01/2023
 */


/**
 * \fn void affichier_num_salle(t_etage * etage)
 * \brief Fonction d'affichage des numéros de salle
 * \return affichage des numéros de salle
 */

void affichier_num_salle(t_etage * etage){
    int i, j;
    for(i=0; i<DIM_ETAGE; i++){
        for(j=0; j<DIM_ETAGE; j++){
            printf("%3d", etage->etage[i][j].num_salle);
        }
        printf("\n");
    }
    printf("\n\n");
}


/**
 * \fn void afficher_salle(t_salle salle)
 *  \param salle la salle à afficher
 * \brief Fonction d'affichage d'une salle
 */
void afficher_salle(t_salle salle){
    int i, j;
    for(i=0; i<DIM_SALLE; i++){
        for(j=0; j<DIM_SALLE; j++){
            switch(salle.dim[i][j]){
                case VIDE : printf(" "); break;
                case PORTE : printf("P"); break;
                case MUR : printf("*"); break;
            }
        }
        printf("\n");
    }
}


/**
 * \fn void afficher_salle_etage(t_etage * etage)
 * \param etage l'étage à afficher
 * \brief Fonction d'affichage des salles d'un étage
 */

void afficher_salle_etage(t_etage * etage){
    int i, j;
    for(i=0; i<DIM_ETAGE; i++){
        for(j=0; j<DIM_ETAGE; j++){
            printf("Salle n°%d (%d/%d) :\n", etage->etage[i][j].num_salle, i, j);
            if(etage->etage[i][j].num_salle==-1){
                printf("Aucune salle à afficher\n\n");
            }
            else{
                afficher_salle(etage->etage[i][j]);
            printf("\n\n");
            }
        }
    }
    
}


/**
 * \fn void afficher_etage(t_etage * etage)
 * \param etage l'étage à afficher
 * \brief Fonction d'affichage d'un étage
 */
void afficher_etage(t_etage * etage){
    int i, j;
    for(i=0; i<DIM_ETAGE; i++){
        for(j=0; j<DIM_ETAGE; j++){
            if(etage->etage[i][j].num_salle==SALLE_UNUSED){
                printf(" *");
            }
            else if(etage->etage[i][j].statut==COMMON){
                printf(" O");
            }
            else if(etage->etage[i][j].statut==START){
                printf(" D");
            }
            else if(etage->etage[i][j].statut==EXIT){
                printf(" A");
            }
        }
        printf("\n");
    }
    printf("\n\n");
    

    afficher_salle_etage(etage);
    affichier_num_salle(etage);
}



/**
 * \fn int salle_disponible(int x, int y, t_salle etage[DIM_ETAGE][DIM_ETAGE])
 * \param x coordonnée x de la salle
 * \param y coordonnée y de la salle
 * \param etage l'étage à vérifier
 * \brief Fonction de vérification de la disponibilité d'une salle
 */
int salle_disponible(int x, int y, t_salle etage[DIM_ETAGE][DIM_ETAGE]){
    if(x>=0 && x<DIM_ETAGE && y>=0 && y<DIM_ETAGE){
        if(etage[x][y].num_salle==SALLE_UNUSED){
            return 1;
        }
        else{
            return -1;
        }
    }
    else{
        return 0;
    }
}


/** 
 * \fn t_pos trouverSalle(int num_salle, t_etage * etage)
 * \param num_salle le numéro de la salle à trouver
 * \param etage l'étage dans lequel chercher
 * \brief Fonction de recherche d'une salle dans un étage
 * \return la position de la salle dans l'étage
*/
t_pos trouverSalle(int num_salle, t_etage * etage){
    int i, j;
    t_pos pos_salle={-1,-1};
    for(i=0; i<DIM_ETAGE; i++){
        for(j=0; j<DIM_ETAGE; j++){
            if(etage->etage[i][j].num_salle==num_salle){
                pos_salle.x=i;
                pos_salle.y=j;
                return pos_salle;
            }
        }
    }
    return pos_salle;
}
/**
 * \fn int nb_lieu_libre(int x, int y, t_salle etage[DIM_ETAGE][DIM_ETAGE])
 * \param x coordonnée x de la salle
 * \param y coordonnée y de la salle
 * \param etage l'étage à vérifier
 * \brief Fonction de vérification du nombre d'endroit libre autour d'une salle
 */
int nb_lieu_libre(int x, int y, t_salle etage[DIM_ETAGE][DIM_ETAGE]){
    int cpt=0;
    if(etage[x+1][y].num_salle==SALLE_UNUSED) cpt++;
    if(etage[x-1][y].num_salle==SALLE_UNUSED) cpt++;
    if(etage[x][y-1].num_salle==SALLE_UNUSED) cpt++;
    if(etage[x][y+1].num_salle==SALLE_UNUSED) cpt++;

    return cpt;
}

/**
 * \fn int nbVoisin(int x, int y, t_etage * etage)
 * \param x coordonnée x de la salle
 * \param y coordonnée y de la salle
 * \param etage l'étage à vérifier
 * \brief Fonction de vérification du nombre de salle autour d'une salle
 * \return le nombre de salle autour de la salle
*/

int nbVoisin(int x, int y, t_etage * etage){
    int cpt=0;
    if(etage->etage[x+1][y].num_salle!=-1) cpt++;
    if(etage->etage[x-1][y].num_salle!=-1) cpt++;
    if(etage->etage[x][y+1].num_salle!=-1) cpt++;
    if(etage->etage[x][y-1].num_salle!=-1) cpt++;

    return cpt;
}


/**
 * \fn int genererSalle(int x_salle, int y_salle, t_etage * etage)
 * \param x_salle coordonnée x de la salle
 * \param y_salle coordonnée y de la salle
 * \param etage l'étage dans lequel sont générer les salles
 * \brief La fonction sert à générer une salle aléatoirement dans un étage en spécifiant les coordonnées x et y. Elle modifie les données de l'étage en ajoutant une nouvelle salle aux coordonnées spécifiées, avec un nombre de murs, de portes et d'espaces vides aléatoires.
 * \return 1 si la génération s'est bien passée, 0 sinon
*/
int genererSalle(int x_salle, int y_salle, t_etage * etage){
    int i, j;
    for(i=0; i<DIM_SALLE; i++){
        for(j=0; j<DIM_SALLE; j++){
            if(j==0 || i==0 || i==DIM_SALLE-1 || j==DIM_SALLE-1){
                etage->etage[x_salle][y_salle].dim[i][j]=MUR;
            }
            else{
                etage->etage[x_salle][y_salle].dim[i][j]=VIDE;
            }
        }
    }

    int cpt_porte=0;
    printf("Gestion des portes :\n");
    if(etage->etage[x_salle][y_salle].statut==EXIT){
        etage->etage[x_salle][y_salle].nb_porte=1;
        if(salle_disponible(x_salle-1, y_salle, etage->etage)==-1 && etage->etage[x_salle-1][y_salle].num_salle == etage->etage[x_salle][y_salle].num_salle-1){
            etage->etage[x_salle][y_salle].dim[0][DIM_SALLE/2-1]=PORTE;
            cpt_porte++;
        }
        if(salle_disponible(x_salle+1, y_salle, etage->etage)==-1 && etage->etage[x_salle+1][y_salle].num_salle == etage->etage[x_salle][y_salle].num_salle-1){
            etage->etage[x_salle][y_salle].dim[DIM_SALLE-1][DIM_SALLE/2-1]=PORTE;
            cpt_porte++;
        }
        if(salle_disponible(x_salle, y_salle-1, etage->etage)==-1 && etage->etage[x_salle][y_salle-1].num_salle == etage->etage[x_salle][y_salle].num_salle-1){
            etage->etage[x_salle][y_salle].dim[DIM_SALLE/2-1][0]=PORTE;
            cpt_porte++;
        }
        if(salle_disponible(x_salle, y_salle+1, etage->etage)==-1 && etage->etage[x_salle][y_salle+1].num_salle == etage->etage[x_salle][y_salle].num_salle-1){
            etage->etage[x_salle][y_salle].dim[DIM_SALLE/2-1][DIM_SALLE-1]=PORTE;
            cpt_porte++;
        }
    }
    else{
        etage->etage[x_salle][y_salle].nb_porte=nbVoisin(x_salle,y_salle,etage);
        if(salle_disponible(x_salle-1, y_salle, etage->etage)==-1 && etage->etage[x_salle-1][y_salle].num_salle!=SALLE_UNUSED && cpt_porte<etage->etage[x_salle][y_salle].nb_porte){
            if(etage->etage[x_salle-1][y_salle].statut==EXIT){
                if(etage->etage[x_salle-1][y_salle].num_salle-1 == etage->etage[x_salle][y_salle].num_salle){
                    etage->etage[x_salle][y_salle].dim[0][DIM_SALLE/2-1]=PORTE;
                    cpt_porte++;
                }
            }
            else{
                etage->etage[x_salle][y_salle].dim[0][DIM_SALLE/2-1]=PORTE;
                cpt_porte++;
            }
        }
        if(salle_disponible(x_salle+1, y_salle, etage->etage)==-1 && etage->etage[x_salle+1][y_salle].num_salle!=SALLE_UNUSED && cpt_porte<etage->etage[x_salle][y_salle].nb_porte){
            if(etage->etage[x_salle+1][y_salle].statut==EXIT){
                if(etage->etage[x_salle+1][y_salle].num_salle-1 == etage->etage[x_salle][y_salle].num_salle){
                    etage->etage[x_salle][y_salle].dim[DIM_SALLE-1][DIM_SALLE/2-1]=PORTE;
                    cpt_porte++;
                }
            }
            else{
                etage->etage[x_salle][y_salle].dim[DIM_SALLE-1][DIM_SALLE/2-1]=PORTE;
                cpt_porte++;
            }
        }
        if(salle_disponible(x_salle, y_salle-1, etage->etage)==-1 && etage->etage[x_salle][y_salle-1].num_salle!=SALLE_UNUSED && cpt_porte<etage->etage[x_salle][y_salle].nb_porte){
            if(etage->etage[x_salle][y_salle-1].statut==EXIT){
                if(etage->etage[x_salle][y_salle-1].num_salle-1 == etage->etage[x_salle][y_salle].num_salle){
                    etage->etage[x_salle][y_salle].dim[DIM_SALLE/2-1][0]=PORTE;
                    cpt_porte++;
                }
            }
            else{
                etage->etage[x_salle][y_salle].dim[DIM_SALLE/2-1][0]=PORTE;
                cpt_porte++;
            }
        }
        if(salle_disponible(x_salle, y_salle+1, etage->etage)==-1 && etage->etage[x_salle][y_salle+1].num_salle!=SALLE_UNUSED && cpt_porte<etage->etage[x_salle][y_salle].nb_porte){
            if(etage->etage[x_salle][y_salle+1].statut==EXIT){
                if(etage->etage[x_salle][y_salle+1].num_salle-1 == etage->etage[x_salle][y_salle].num_salle){
                    etage->etage[x_salle][y_salle].dim[DIM_SALLE/2-1][DIM_SALLE-1]=PORTE;
                    cpt_porte++;
                }
            }
            else{
                etage->etage[x_salle][y_salle].dim[DIM_SALLE/2-1][DIM_SALLE-1]=PORTE;
                cpt_porte++;
            }
            
        }
    }

    return OK;
}



/**
 * \fn int genererEtage(t_etage * etage)
 * \brief Fonction de création d'un étage  
 * \param etage pointeur sur l'étage à créer
 * \return 0 si la map a bien été créée sinon renvoie 100
*/
int genererEtage(t_etage * etage){
    srand(time(NULL));
    int i, j;
    for(i=0; i<DIM_ETAGE; i++){
        for(j=0; j<DIM_ETAGE; j++){
            etage->etage[i][j].num_salle=SALLE_UNUSED;
        }
    }

    int x=rand()%DIM_ETAGE;
    int y=rand()%DIM_ETAGE;
    int i_salle = 1;
    int i_new;
    etage->etage[x][y].num_salle=i_salle;
    etage->etage[x][y].statut=START;
    int exit_attribue=0;
    int new_salle_trouve=0;

    while (i_salle++<etage->nb_salle){
        int prev_x = x;
        int prev_y = y;
        do{
            int choix_direction_salle = rand()%4;
            if(choix_direction_salle==0 && salle_disponible(x+1,y,etage->etage)==1){
                etage->etage[++x][y].num_salle=i_salle;
            }
            else if(choix_direction_salle==1 && salle_disponible(x-1,y,etage->etage)==1){
                etage->etage[--x][y].num_salle=i_salle;
            }
            else if(choix_direction_salle==2 && salle_disponible(x,y+1,etage->etage)==1){
                etage->etage[x][++y].num_salle=i_salle;
            }
            else if(choix_direction_salle==3 && salle_disponible(x,y-1,etage->etage)==1){
                etage->etage[x][--y].num_salle=i_salle;
            }
            else if(!salle_disponible(x,y-1,etage->etage) && !salle_disponible(x,y+1,etage->etage) && !salle_disponible(x-1,y,etage->etage) && !salle_disponible(x+1,y,etage->etage)){
                etage->etage[prev_x][prev_y].statut=EXIT;
                exit_attribue=1;
                new_salle_trouve=0;
                t_pos pos_salle;
                i_new=1;

                while(!new_salle_trouve){
                    t_pos new_pos=trouverSalle(i_new, etage);
                    x=new_pos.x;
                    y=new_pos.y;
                    
                    if(nb_lieu_libre(x,y,etage->etage)>1){
                        new_salle_trouve=1;
                    }
                    else{
                        i_new++;
                    }
                }

                choix_direction_salle = rand()%4;
                if(choix_direction_salle==0 && salle_disponible(x+1,y,etage->etage)==1){
                    etage->etage[++x][y].num_salle=i_salle;
                }
                else if(choix_direction_salle==1 && salle_disponible(x-1,y,etage->etage)==1){
                    etage->etage[--x][y].num_salle=i_salle;
                }
                else if(choix_direction_salle==2 && salle_disponible(x,y+1,etage->etage)==1){
                    etage->etage[x][++y].num_salle=i_salle;
                }
                else if(choix_direction_salle==3 && salle_disponible(x,y-1,etage->etage)==1){
                    etage->etage[x][--y].num_salle=i_salle;
                }

            }
        }while(x == prev_x && y == prev_y);

        if(i_salle<=etage->nb_salle && etage->etage[x][y].statut!=START){
                etage->etage[x][y].statut=COMMON;
            }
        if(i_salle==etage->nb_salle && exit_attribue==0){
            etage->etage[x][y].statut=EXIT;
        }
    }

    for(i=0; i<DIM_ETAGE; i++){
        for(j=0; j<DIM_ETAGE; j++){
            if(etage->etage[i][j].num_salle>0){
                genererSalle(i,j,etage);
            }
        }
    }
    return OK;
}

/**
 * \fn int genererNiv(t_niv * niveau)
 * \brief Fonction de création d'un niveau
 * \param niveau pointeur sur le niveau à créer
 * \return 0 si la map a bien été créée sinon renvoie 100
 * 
*/
int genererNiv(t_niv * niveau){
    srand(time( NULL ));
    niveau->etages[0].nb_salle = rand()%4+8;
    genererEtage(&niveau->etages[0]);

    afficher_etage(&niveau->etages[0]);

    return OK;
}
/**
 * \fn int detruireNiv(t_niv ** niveau)
 * \brief Fonction de destruction d'un niveau
 * \param niveau pointeur sur le niveau à détruire
 * \return 0 si la map a bien été détruite
*/
int detruireNiv(t_niv ** niveau){
    free(*niveau);
    (*niveau)=NULL;

    return OK;
}

/**
 * \fn int main()
 * \brief Fonction principale qui malloc un niveau et le détruit
 * 
*/
int main(){
    t_niv * niveau = malloc(sizeof(t_niv));;
    genererNiv(niveau);
    detruireNiv(&niveau);
}

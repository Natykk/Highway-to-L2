#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../head/entite.h"
#include "../head/mapStruct.h"
#include "../head/inventaire.h"

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


void afficher_num_salle(t_etage * etage){
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
            if(salle.dim[i][j]>=10 && salle.dim[i][j]<=21){
                printf("M");
            }
            else{
                switch(salle.dim[i][j]){
                    case VIDE : printf(" "); break;
                    case PORTE : printf("|"); break;
                    case MUR : printf("*"); break;
                    case OBSTACLE : printf("+"); break;
                    default: break;
                }
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
    
    //afficher_salle_etage(etage);
    afficher_num_salle(etage);
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
    if(x+1>=0 && x+1<DIM_ETAGE && etage[x+1][y].num_salle==SALLE_UNUSED) cpt++;
    if(x-1>=0 && x-1<DIM_ETAGE && etage[x-1][y].num_salle==SALLE_UNUSED) cpt++;
    if(y-1>=0 && y-1<DIM_ETAGE && etage[x][y-1].num_salle==SALLE_UNUSED) cpt++;
    if(y+1>=0 && y+1<DIM_ETAGE && etage[x][y+1].num_salle==SALLE_UNUSED) cpt++;

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
    if(x+1>=0 && x+1<DIM_ETAGE && etage->etage[x+1][y].num_salle!=SALLE_UNUSED) cpt++;
    if(x-1>=0 && x-1<DIM_ETAGE && etage->etage[x-1][y].num_salle!=SALLE_UNUSED) cpt++;
    if(y+1>=0 && y+1<DIM_ETAGE && etage->etage[x][y+1].num_salle!=SALLE_UNUSED) cpt++;
    if(y-1>=0 && y-1<DIM_ETAGE && etage->etage[x][y-1].num_salle!=SALLE_UNUSED) cpt++;

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
    if(etage->etage[x_salle][y_salle].statut==EXIT){
        etage->etage[x_salle][y_salle].nb_porte=1;
        if(salle_disponible(x_salle-1, y_salle, etage->etage)==-1 && etage->etage[x_salle-1][y_salle].num_salle == etage->etage[x_salle][y_salle].num_salle-1){
            etage->etage[x_salle][y_salle].dim[0][DIM_SALLE/2]=PORTE;
            cpt_porte++;
        }
        if(salle_disponible(x_salle+1, y_salle, etage->etage)==-1 && etage->etage[x_salle+1][y_salle].num_salle == etage->etage[x_salle][y_salle].num_salle-1){
            etage->etage[x_salle][y_salle].dim[DIM_SALLE-1][DIM_SALLE/2]=PORTE;
            cpt_porte++;
        }
        if(salle_disponible(x_salle, y_salle-1, etage->etage)==-1 && etage->etage[x_salle][y_salle-1].num_salle == etage->etage[x_salle][y_salle].num_salle-1){
            etage->etage[x_salle][y_salle].dim[DIM_SALLE/2][0]=PORTE;
            cpt_porte++;
        }
        if(salle_disponible(x_salle, y_salle+1, etage->etage)==-1 && etage->etage[x_salle][y_salle+1].num_salle == etage->etage[x_salle][y_salle].num_salle-1){
            etage->etage[x_salle][y_salle].dim[DIM_SALLE/2][DIM_SALLE-1]=PORTE;
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

    int nbObstacle=rand()% 9 + 3;        //génère entre 3 et 12 obstacles
    int nbObstplace=0;
    int x_obst, y_obst;
    while(nbObstplace<nbObstacle){
        do{
            x_obst=rand()%(DIM_SALLE-4)+2;
            y_obst=rand()%(DIM_SALLE-4)+2;
        }while(etage->etage[x_salle][y_salle].dim[x_obst][y_obst]!=VIDE);
        etage->etage[x_salle][y_salle].dim[x_obst][y_obst]=OBSTACLE;
        nbObstplace++;
    }

    
    int nbMob=rand()%4+1;  //génère entre 1 et 5 mobs
    int num_mob;
    etage->etage[x_salle][y_salle].nb_mobs=nbMob;
    int nbMobplace=0;
    int x_mob, y_mob;
    while(nbMobplace<nbMob){
            num_mob=rand()%4 + NumEtage*4; // Prend un mob au hasard dans le tableau de mob suivant l'etage
            printf("%s\n",tab_mob[num_mob].nom);
           etage->etage[x_salle][y_salle].mob[nbMobplace]=creer_monstre(etage->etage[x_salle][y_salle].mob[nbMobplace],tab_mob[num_mob].nom); // Créer le mob       

        do{
            x_mob=rand()%(DIM_SALLE-4)+2; // Genere une position au hasard dans la salle
            y_mob=rand()%(DIM_SALLE-4)+2;
            
            etage->etage[x_salle][y_salle].mob[nbMobplace]->x=x_mob; // Place le mob dans la salle
            etage->etage[x_salle][y_salle].mob[nbMobplace]->y=y_mob;
        }while(etage->etage[x_salle][y_salle].dim[x_mob][y_mob]!=VIDE);
        //afficher_entite(etage->etage[x_salle][y_salle].mob[nbMobplace]);
        etage->etage[x_salle][y_salle].mob[nbMobplace]->persoOuMob=1;
        etage->etage[x_salle][y_salle].mob[nbMobplace]=init_inventaire_monstre(etage->etage[x_salle][y_salle].mob[nbMobplace]);
        etage->etage[x_salle][y_salle].dim[x_mob][y_mob]=nbMobplace+10;
        init_inventaire_monstre(etage->etage[x_salle][y_salle].mob[nbMobplace]);
        nbMobplace++;
    }

    return OK;
}

/**
 * \fn int etageConforme(t_etage * etage)
 * \brief Fonction vérifiant si l'étage possède autant de salles que etage->nb_salle et verifie la numerotation des chaque pièce.
 * \param etage pointeur sur l'étage à vérifier
 * \return 0 si l'étage n'est pas complet ou si il manque des salles (ex : 3-4-6-7), sinon si tout va bien retourne 1
*/
int etageConforme(t_etage * etage){
    int i=1;
    t_pos salle1 = trouverSalle(i++,etage);
    while(i<etage->nb_salle){
        if(salle1.y+1>=0 && salle1.y+1<DIM_ETAGE && etage->etage[salle1.x][salle1.y+1].num_salle==i+1){
            salle1.y++;
        }
        else if(salle1.y-1>=0 && salle1.y-1<DIM_ETAGE && etage->etage[salle1.x][salle1.y-1].num_salle==i+1){
            salle1.y--;
        }
        else if(salle1.x+1>=0 && salle1.x+1<DIM_ETAGE && etage->etage[salle1.x+1][salle1.y].num_salle==i+1){
            salle1.x++;
        }
        else if(salle1.x-1>=0 && salle1.x-1<DIM_ETAGE && etage->etage[salle1.x-1][salle1.y].num_salle==i+1){
            salle1.x--;   
        }
        i++;
    }
    if(i==etage->nb_salle){
        return 1;
    }
    else{
        return 0;
    }
}


/**
 * \fn int genererEtage(t_etage * etage)
 * \brief La fonction commence par initialiser un tableau pour représenter l'étage et mettre toutes les pièces de l'étage dans un état inutilisé. Ensuite, elle choisit aléatoirement une pièce de départ et, à l'aide d'une boucle while, elle ajoute des pièces à l'étage une par une. La boucle while continue jusqu'à ce que toutes les pièces aient été ajoutées. La fonction utilise un générateur de nombres aléatoires pour déterminer l'emplacement de chaque nouvelle pièce, et vérifie s'il existe des pièces inutilisées adjacentes à la pièce actuelle. Si c'est le cas, elle ajoute la nouvelle pièce à l'étage et met à jour la pièce actuelle en fonction de la nouvelle pièce. S'il n'y a pas de pièces inutilisées adjacentes à la pièce actuelle, il marque la pièce actuelle comme étant la pièce de sortie, trouve une nouvelle pièce de départ et continue à ajouter des pièces à partir de cette nouvelle pièce de départ.  
 * \param etage pointeur sur l'étage à créer
 * \return 0 si la map a bien été créée sinon renvoie 100
*/
int genererEtage(t_etage * etage){
    int i, j;
    for(i=0; i<DIM_ETAGE; i++){
        for(j=0; j<DIM_ETAGE; j++){
            etage->etage[i][j].num_salle=SALLE_UNUSED;
        }
    }

    int x=rand()%DIM_ETAGE;
    int y=rand()%DIM_ETAGE;
    int i_salle = 1;
    etage->etage[x][y].num_salle=i_salle++;
    etage->etage[x][y].statut=START;
    
    int i_new;
    int exit_attribue=0;
    int new_salle_trouve=0;
    int prev_x;
    int prev_y;
    int choix_direction_salle;

    while (i_salle<=etage->nb_salle){
        prev_x = x;
        prev_y = y;
        if(salle_disponible(x,y-1,etage->etage)!=1 && salle_disponible(x,y+1,etage->etage)!=1 && salle_disponible(x-1,y,etage->etage)!=1 && salle_disponible(x+1,y,etage->etage)!=1){
            if(exit_attribue==0){
                etage->etage[prev_x][prev_y].statut=EXIT;
                exit_attribue=1;
            }
            new_salle_trouve=0;
            i_new=1;
            

            while(!new_salle_trouve){
                t_pos new_pos=trouverSalle(i_new, etage);
                x=new_pos.x;
                y=new_pos.y;
                prev_x=x;
                prev_y=y;
                
                if(nb_lieu_libre(x,y,etage->etage)>1){
                    new_salle_trouve=1;
                }
                else{
                    i_new++;
                }
            }
        }

        do{
            choix_direction_salle = rand()%4;
            //printf("Choix direction : %d\n", choix_direction_salle);
            //printf("A ce moment, i_salle = %d\n", i_salle);
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
        }while(x == prev_x && y == prev_y);

        if(i_salle<=etage->nb_salle && i_salle>1){
                etage->etage[x][y].statut=COMMON;
            }
        if(i_salle==etage->nb_salle && exit_attribue==0){
            etage->etage[x][y].statut=EXIT;
        }
        i_salle++;
    }

    for(i=0; i<DIM_ETAGE; i++){
        for(j=0; j<DIM_ETAGE; j++){
            if(etage->etage[i][j].num_salle>0){
                genererSalle(i,j,etage);
            }
        }
    }

    etage->boss=0;
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
    niveau->etages[1].nb_salle = rand()%4+8;
    niveau->etages[2].nb_salle = rand()%4+8;
    NumEtage=0;
    do{
        genererEtage(&niveau->etages[0]);
        NumEtage++;
    }while(!etageConforme(&niveau->etages[0]));
    do{
        genererEtage(&niveau->etages[1]);
        NumEtage++;
    }while(!etageConforme(&niveau->etages[1]));
    do{
        genererEtage(&niveau->etages[2]);
    }while(!etageConforme(&niveau->etages[2]));

    return OK;
}

/**
 * \fn int detruireNiv(t_niv ** niveau)
 * \brief Fonction de destruction d'un niveau
 * \param niveau pointeur sur le niveau à détruire
 * \return 0 si la map a bien été détruite
*/
int detruireNiv(t_niv ** niveau){
    //detruire_entitees(&(*niveau)->etages[0].etage[0][0].mob[0]);
    free(*niveau);
    (*niveau)=NULL;

    return OK;
}

/**
 * \fn int main()
 * \brief Fonction principale qui génère un niveau et le détruit.
 * 
*/
/*
int main(){
    int i, j;
    srand(time(NULL));
    t_etage * etage = malloc(sizeof(t_etage));
    //for(int gen=0; gen<10; gen++){
    etage->nb_salle = 10;
    genererEtage(etage);
    afficher_etage(etage);
    afficher_salle_etage(etage);
    //}

    free(etage);
    etage=NULL;
}
*/
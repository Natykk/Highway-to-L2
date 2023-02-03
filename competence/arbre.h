#include "competence.h"
#define MAX_CPT 4


typedef enum{Assassin, Guerrier, Mage, Archer} t_classe;

typedef struct arbre{
    t_competence competence[MAX_CPT];
    t_buff buff_stat_total;
} t_arbre;



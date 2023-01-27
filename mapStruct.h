typedef enum {COMMON, START, EXIT} t_statut;

#define SALLE_UNUSED -1
#define DIM_ETAGE 5
#define DIM_SALLE 20
#define DIM_SALLE_BOSS 30

typedef struct salle {
    int nb_mobs;
    int num_salle;
    int salle[DIM_SALLE][DIM_SALLE];
    t_statut statut;
} t_salle;

typedef struct etage {
    int nb_salle;
    t_salle etage[DIM_ETAGE][DIM_ETAGE];
} t_etage;

typedef struct niveau {
    t_etage etages[3];      //3 étages par niveau
} t_niv;

/* Erreurs */
#define OK 0
#define ERR_CREA_MAP 100
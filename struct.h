#ifndef STRUCT
#define STRUCT

#define NB_ACTS 5
#define NB_ENTITIES 2
#define NB_MB_MAN 6

typedef struct s_entity entity;

extern entity entities[NB_ENTITIES];

enum coor {X = 0, Y, Z, ANGLE};
enum lateralite {GAUCHE = 0, DROITE};
enum action {STOP = 0, IDLE, RUN, WALK, SEAT};
enum bodyPart {TETE = 0, TRONC, BRAS_DROIT, BRAS_GAUCHE, JAMBE_DROITE, JAMBE_GAUCHE};

struct s_entity
{
	int color[3];
	int pos[3];
	float rotat[4];
	float amplitude[NB_ACTS];
	float med[NB_ACTS];
	float angle_Ini[NB_ACTS];
	int listeDessin;
	entity *compo;
};

#endif

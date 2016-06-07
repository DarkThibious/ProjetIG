#ifndef  INIT_INC
#define  INIT_INC

#include <GL/gl.h>           
#include <GL/glu.h>         
#include <GL/glut.h>    

#include <stdio.h>      
#include <stdlib.h>     
#include <stdbool.h>
#include <math.h>
#include <tiffio.h>     /* Sam Leffler's libtiff library. */
#include "formes.h"
#include "struct.h"

#define PI 3.1415926535898

#define position_Ini_X 0.0
#define position_Ini_Y 0.0

#define    windowWidth 300
#define    windowHeight 300

#define RED   0.5
#define GREEN 0.5
#define BLUE  0.5
#define ALPHA 1

#define TETE_R 1.5

#define TRONC_R 2.5
#define TRONC_H 7.0
#define TRONC_SCL_Y 0.75

#define BRAS_R 0.5
#define BRAS_H 4.5

#define PAUME_R 0.35
#define PAUME_H 0.5

#define DOIGT_R 0.1
#define DOIGT_H 0.5

#define CUISSE_R TRONC_R/2.0
#define CUISSE_H 5.0

#define MOLLET_R1 CUISSE_R - 0.5
#define MOLLET_R2 MOLLET_R1 - 0.5

#define CHAPEAU_R1 2.0
#define CHAPEAU_H1 0.5
#define CHAPEAU_R2 1.5
#define CHAPEAU_H2 3.0 

#define PAPILLON_H TRONC_H-0.5

enum lateralite {GAUCHE = 0, DROITE};
enum action {WALK = 0, RUN, SEAT, STOP, IDLE};

static GLfloat light_position0[];
static GLfloat light_position1[];

static GLfloat ambient_light0[];
static GLfloat diffuse_light0[];
static GLfloat specular_light0[];

static GLfloat ambient_light1[];
static GLfloat diffuse_light1[];
static GLfloat specular_light1[];

static GLfloat mat_specular[];
static GLfloat mat_ambientanddiffuse[];
static GLfloat mat_shininess[];

extern int Mon_Repere;

extern entity homme;
extern entity chaise;

/* des parties du corps */
extern int Ma_Tete;
extern int Mon_Tronc;
extern int Mon_Bras;
extern int Mon_AvantBras;
extern int Ma_Cuisse;
extern int Mon_Mollet;
extern int Ma_Paume;
extern int Mon_Pouce;
extern int Mon_Doigt;
extern int Mon_Epaule;
extern int Mon_Coude;
extern int Mon_Genou;
extern int Mon_Bassin;

/* des accessoires */
extern int Mon_Chapeau;
extern int Mon_Papillon;

/* des formes */
extern int My_Triangle;
extern int My_Base;
extern int My_Pyramide;

extern float angle_Bras[2];
extern float angle_AvantBras[2];
extern float angle_Cuisse[2];
extern float angle_Mollet[2];

extern float angle_Bras_Ini[2];
extern float angle_AvantBras_Ini[2];
extern float angle_Cuisse_Ini[2];
extern float angle_Mollet_Ini[2];

extern float amplitude_Bras;
extern float amplitude_AvantBras;
extern float amplitude_Cuisse;
extern float amplitude_Mollet;
extern float med_Bras;
extern float med_AvantBras;
extern float med_Cuisse;
extern float med_Mollet;

extern float angle_Bras_Ini_R[2];
extern float angle_AvantBras_Ini_R[2];
extern float angle_Cuisse_Ini_R[2];
extern float angle_Mollet_Ini_R[2];

extern float amplitude_Bras_R;
extern float amplitude_AvantBras_R;
extern float amplitude_Cuisse_R;
extern float amplitude_Mollet_R;
extern float med_Bras_R;
extern float med_AvantBras_R;
extern float med_Cuisse_R;
extern float med_Mollet_R;

GLvoid initGL();
void init_scene();
void init_angles();
void Faire_Composantes();
void Dessine_Repere();

void make_triangle();
void make_base();
void make_Pyramide();
void make_Chaise();
void make_square();
void make_cube();

#endif

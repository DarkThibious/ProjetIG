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

#define PI 3.1415926535898

#define position_Ini -60.0

#define    windowWidth 300
#define    windowHeight 300

#define RED   0.5
#define GREEN 0.5
#define BLUE  0.5
#define ALPHA 1

enum lateralite {Gauche = 0, Droit};

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

GLvoid initGL();
void init_scene();
void init_angles();
void Faire_Composantes();
void Dessine_Repere();

void make_triangle();
void make_base();
void make_Pyramide();

#endif

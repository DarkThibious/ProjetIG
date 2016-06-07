#include "init.h"

static GLfloat light_position0[] = {15.0, 15.0, 15.0, 0.0};
static GLfloat light_position1[] = {15.0, 15.0, -15.0, 0.0};

static GLfloat ambient_light0[] = {0.0, 0.0, 0.0, 0.0};
static GLfloat diffuse_light0[] = {0.7, 0.7, 0.7, 1.0};
static GLfloat specular_light0[] = {0.1, 0.1, 0.1, 0.1};

static GLfloat ambient_light1[] = {0.50, 0.50, 0.50, 1.0};
static GLfloat diffuse_light1[] = {0.5, 1.0, 1.0, 1.0};
static GLfloat specular_light1[] = {0.5, 1.0, 1.0, 1.0};

static GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
static GLfloat mat_ambientanddiffuse[] = {0.4, 0.4, 0.0, 1.0};
static GLfloat mat_shininess[] = {20.0};

int  Mon_Repere;

entity homme;

int Mon_Tronc;
int Ma_Tete;
int Mon_Bras;
int Mon_AvantBras;
int Ma_Cuisse;
int Mon_Mollet;
int Ma_Paume;
int Mon_Doigt;
int Mon_Pouce;
int Mon_Epaule;
int Mon_Coude;
int Mon_Genou;
int Mon_Bassin;

int Mon_Chapeau;
int Mon_Papillon;

int My_Triangle;
int My_Base;
int My_Pyramide;

float angle_Bras[2];
float angle_AvantBras[2];
float angle_Cuisse[2];
float angle_Mollet[2];

float angle_Bras_Ini[2] = {-30.0, 15.0};
float angle_AvantBras_Ini[2] = {0.0, 15.0};
float angle_Cuisse_Ini[2] = {20.0, -20.0};
float angle_Mollet_Ini[2] = {0.0, -20.0};

float amplitude_Bras;
float amplitude_AvantBras;
float amplitude_Cuisse;
float amplitude_Mollet;
float med_Bras;
float med_AvantBras;
float med_Cuisse;
float med_Mollet;

float angle_Bras_Ini_R[2] = {-35.0, 45.0};
float angle_AvantBras_Ini_R[2] = {90.0, 85.0};
float angle_Cuisse_Ini_R[2] = {45.0, -30.0};
float angle_Mollet_Ini_R[2] = {-5.0, -45.0};

float amplitude_Bras_R;
float amplitude_AvantBras_R;
float amplitude_Cuisse_R;
float amplitude_Mollet_R;
float med_Bras_R;
float med_AvantBras_R;
float med_Cuisse_R;
float med_Mollet_R;

// initialisation du fond de la fenêtre graphique : GRIS //noir opaque
GLvoid initGL() 
{
	// initialisation de l´éclairement

	// définition de deux source lumineuses
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light0);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light1);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

	// activation de l´éclairement
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// propriétés matérielles des objets
	// glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambientanddiffuse);
	// glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	// glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);

	// initialisation du fond
	glClearColor(RED, GREEN, BLUE, ALPHA);        
	// z-buffer
	glEnable(GL_DEPTH_TEST);
}

void init_scene()
{
	// initialise des display lists des composantes cylindriques du corps
	Faire_Composantes();

	amplitude_Bras = .5 * (angle_Bras_Ini[DROITE] - angle_Bras_Ini[GAUCHE]);
	amplitude_AvantBras = .5 * (angle_AvantBras_Ini[DROITE] - angle_AvantBras_Ini[GAUCHE]);
	amplitude_Cuisse = .5 * (angle_Cuisse_Ini[DROITE] - angle_Cuisse_Ini[GAUCHE]);
	amplitude_Mollet = .5 * (angle_Mollet_Ini[DROITE] - angle_Mollet_Ini[GAUCHE]);
	med_Bras = .5 * (angle_Bras_Ini[DROITE] + angle_Bras_Ini[GAUCHE]);
	med_AvantBras = .5 * (angle_AvantBras_Ini[DROITE] + angle_AvantBras_Ini[GAUCHE]);
	med_Cuisse = .5 * (angle_Cuisse_Ini[DROITE] + angle_Cuisse_Ini[GAUCHE]);
	med_Mollet = .5 * (angle_Mollet_Ini[DROITE] + angle_Mollet_Ini[GAUCHE]);

	amplitude_Bras_R = .5 * (angle_Bras_Ini_R[DROITE] - angle_Bras_Ini_R[GAUCHE]);
	amplitude_AvantBras_R = .5 * (angle_AvantBras_Ini_R[DROITE] - angle_AvantBras_Ini_R[GAUCHE]);
	amplitude_Cuisse_R = .5 * (angle_Cuisse_Ini_R[DROITE] - angle_Cuisse_Ini_R[GAUCHE]);
	amplitude_Mollet_R = .5 * (angle_Mollet_Ini_R[DROITE] - angle_Mollet_Ini_R[GAUCHE]);
	med_Bras_R = .5 * (angle_Bras_Ini_R[DROITE] + angle_Bras_Ini_R[GAUCHE]);
	med_AvantBras_R = .5 * (angle_AvantBras_Ini_R[DROITE] + angle_AvantBras_Ini_R[GAUCHE]);
	med_Cuisse_R = .5 * (angle_Cuisse_Ini_R[DROITE] + angle_Cuisse_Ini_R[GAUCHE]);
	med_Mollet_R = .5 * (angle_Mollet_Ini_R[DROITE] + angle_Mollet_Ini_R[GAUCHE]);
}

void initHomme()
{
	entity *e;

	homme.color[R] = 1.0;
	homme.color[G] = 1.0;
	homme.color[B] = 1.0;
	homme.pos[X] = position_Ini_X;
	homme.pos[Y] = position_Ini_Y;
	homme.pos[Z] = CUISSE_H*2-TRONC_R/10-0.05;
	homme.rotat[X] = 0;
	homme.rotat[Y] = 0;
	homme.rotat[Z] = 0;
	homme.rotat[ANGLE] = 0;
	homme.angle_Ini[MIN] = 0;
	homme.angle_Ini[MAX] = 0;
	homme.listeDessin = Mon_Tronc;
	homme.nbCompo = 6; // tete + brasGD + jambeGD + papillon
	homme.compo = malloc(sizeof(entity)*homme.nbCompo);

	homme.compo[TETE].color[R] = 1.0;
	homme.compo[TETE].color[G] = 1.0;
	homme.compo[TETE].color[B] = 0.0;
	homme.compo[TETE].pos[X] = 0;
	homme.compo[TETE].pos[Y] = 0;
	homme.compo[TETE].pos[Z] = TRONC_H+TETE_R;
	homme.compo[TETE].rotat[X] = 0;
	homme.compo[TETE].rotat[Y] = 0;
	homme.compo[TETE].rotat[Z] = 0;
	homme.compo[TETE].rotat[ANGLE] = 0;
	homme.compo[TETE].angle_Ini[MIN] = 0;
	homme.compo[TETE].angle_Ini[MAX] = 0;
	homme.compo[TETE].listeDessin = Ma_Tete;
	homme.compo[TETE].nbCompo = 1; // Chapeau
	homme.compo[TETE].compo = malloc(sizeof(entity));

	// Chapeau
	homme.compo[TETE].compo->color[R] = 1.0;
	homme.compo[TETE].compo->color[G] = 1.0;
	homme.compo[TETE].compo->color[B] = 1.0;
	homme.compo[TETE].compo->pos[X] = 0;
	homme.compo[TETE].compo->pos[Y] = 0;
	homme.compo[TETE].compo->pos[Z] = (2/3)*TETE_R;
	homme.compo[TETE].compo->rotat[X] = 0;
	homme.compo[TETE].compo->rotat[Y] = 0;
	homme.compo[TETE].compo->rotat[Z] = 0;
	homme.compo[TETE].compo->rotat[ANGLE] = 0;
	homme.compo[TETE].compo->angle_Ini[MIN] = 0;
	homme.compo[TETE].compo->angle_Ini[MAX] = 0;
	homme.compo[TETE].compo->listeDessin = Mon_Chapeau;
	homme.compo[TETE].compo->nbCompo = 0;
	homme.compo[TETE].compo->compo = NULL; 

	homme.compo[EPAULE_DROITE].color[R] = 0.0;
	homme.compo[EPAULE_DROITE].color[G] = 0.0;
	homme.compo[EPAULE_DROITE].color[B] = 1.0;
	homme.compo[EPAULE_DROITE].pos[X] = TRONC_R+BRAS_R;
	homme.compo[EPAULE_DROITE].pos[Y] = 0;
	homme.compo[EPAULE_DROITE].pos[Z] = TRONC_H-BRAS_R;
	homme.compo[EPAULE_DROITE].rotat[X] = 1;
	homme.compo[EPAULE_DROITE].rotat[Y] = 0;
	homme.compo[EPAULE_DROITE].rotat[Z] = 0;
	homme.compo[EPAULE_DROITE].rotat[ANGLE] = 0;
	homme.compo[EPAULE_DROITE].angle_Ini[MIN] = 0;
	homme.compo[EPAULE_DROITE].angle_Ini[MAX] = 0;
	homme.compo[EPAULE_DROITE].listeDessin = Mon_Epaule;
	homme.compo[EPAULE_DROITE].nbCompo = 1;// Bras droit
	homme.compo[EPAULE_DROITE].compo = malloc(sizeof(entity));
	
	// Bras droit
	homme.compo[EPAULE_DROITE].compo->color[R] = 0.0;
	homme.compo[EPAULE_DROITE].compo->color[G] = 0.0;
	homme.compo[EPAULE_DROITE].compo->color[B] = 1.0;
	homme.compo[EPAULE_DROITE].compo->pos[X] = 0;
	homme.compo[EPAULE_DROITE].compo->pos[Y] = 0;
	homme.compo[EPAULE_DROITE].compo->pos[Z] = 0;
	homme.compo[EPAULE_DROITE].compo->rotat[X] = 1;
	homme.compo[EPAULE_DROITE].compo->rotat[Y] = 0;
	homme.compo[EPAULE_DROITE].compo->rotat[Z] = 0;
	homme.compo[EPAULE_DROITE].compo->rotat[ANGLE] = 0;
	homme.compo[EPAULE_DROITE].compo->angle_Ini[MIN] = 0;
	homme.compo[EPAULE_DROITE].compo->angle_Ini[MAX] = 0;
	homme.compo[EPAULE_DROITE].compo->listeDessin = Mon_Bras;
	homme.compo[EPAULE_DROITE].compo->nbCompo = 1; // Coude
	homme.compo[EPAULE_DROITE].compo->compo = malloc(sizeof(entity));

	// Coude
	e = homme.compo[EPAULE_DROITE].compo->compo;
	e->color[R] = -1;
	e->color[G] = -1;
	e->color[B] = -1;
	e->pos[X] = 0;
	e->pos[Y] = 0;
	e->pos[Z] = -(BRAS_H+BRAS_R/2);
	e->rotat[X] = 1;
	e->rotat[Y] = 0;
	e->rotat[Z] = 0;
	e->rotat[ANGLE] = 0;
	e->angle_Ini[MIN] = 0;
	e->angle_Ini[MAX] = 0;
	e->listeDessin = Mon_Coude;
	e->nbCompo = 1; // Avant-Bras
	e->compo = malloc(sizeof(entity));
	
	// Avant-Bras
	e = e->compo;
	e->color[R] = -1;
	e->color[G] = -1;
	e->color[B] = -1;
	e->pos[X] = 0;
	e->pos[Y] = 0;
	e->pos[Z] = 0;
	e->rotat[X] = 0;
	e->rotat[Y] = 0;
	e->rotat[Z] = 0;
	e->rotat[ANGLE] = 0;
	e->angle_Ini[MIN] = 0;
	e->angle_Ini[MAX] = 0;
	e->listeDessin = Mon_Coude;
	e->nbCompo = 1; // Avant-Bras
	e->compo = malloc(sizeof(entity));

}

void Faire_Composantes() 
{
	GLUquadricObj* GLAPIENTRY qobj;

	// attribution des indentificateurs de display lists
	Ma_Tete =  glGenLists(14);
	Mon_Tronc = Ma_Tete + 1;
	Mon_Bras = Ma_Tete + 2;
	Mon_AvantBras = Ma_Tete + 3;
	Ma_Cuisse = Ma_Tete + 4;
	Mon_Mollet = Ma_Tete + 5;
	Mon_Chapeau = Ma_Tete + 6;
	Mon_Papillon = Ma_Tete + 7;
	Ma_Paume = Ma_Tete + 8;
	Mon_Doigt = Ma_Tete + 9;
	Mon_Epaule = Ma_Tete + 10;
	Mon_Coude = Ma_Tete + 11;
	Mon_Genou = Ma_Tete + 12;
	Mon_Bassin = Ma_Tete + 13;
	
	make_base();
	make_triangle();
	make_Pyramide();

	make_square();
	make_cube();
	make_Chaise();

	glNewList(Ma_Tete,GL_COMPILE);	
	{
		glutSolidSphere(TETE_R,20,20);	
	}
	glEndList();

	// allocation d´une description de quadrique
	qobj = gluNewQuadric();
	// la quadrique est pleine 
	gluQuadricDrawStyle(qobj, GLU_FILL); 
	// les ombrages, s´il y en a, sont doux
	gluQuadricNormals(qobj, GLU_SMOOTH);

	glNewList(Mon_Tronc, GL_COMPILE);
	{ 
		glPushMatrix();
		{
			glScalef(1,TRONC_SCL_Y,1);
			gluDisk(qobj, 0.0, TRONC_R, 20, 20);
			gluCylinder(qobj, TRONC_R, TRONC_R, TRONC_H, 20, 20);
			glTranslatef(0, 0, TRONC_H);
			gluDisk(qobj, 0.0, TRONC_R, 20, 20);
		}
		glPopMatrix();
	}
	glEndList();
	
	glNewList(Mon_Bras, GL_COMPILE);
	{
		glPushMatrix();
		{
			glRotatef(180,1,0,0);
			gluDisk(qobj, 0.0, BRAS_R, 20, 20);
			gluCylinder(qobj, BRAS_R, BRAS_R, BRAS_H, 20, 20);
			glTranslatef(0, 0, BRAS_H);
			gluDisk(qobj, 0.0, BRAS_R, 20, 20);
		}
		glPopMatrix();
	}
	glEndList();
	
	glNewList(Mon_Epaule, GL_COMPILE);
	{
		glutSolidSphere(BRAS_R, 20, 20);	
	}
	glEndList();
	
	glNewList(Mon_AvantBras, GL_COMPILE);
	{
		glPushMatrix();
		{
			glRotatef(180,1,0,0);
			gluDisk(qobj, 0.0, BRAS_R, 20, 20);
			gluCylinder(qobj, BRAS_R, BRAS_R/2, BRAS_H, 20, 20); 
			glTranslatef(0, 0, BRAS_H);
			gluDisk(qobj, 0.0, BRAS_R/2, 20, 20);
		}
		glPopMatrix();
	}
	glEndList();
	
	glNewList(Mon_Coude, GL_COMPILE);
	{
		glutSolidSphere(BRAS_R,20,20);	
	}
	glEndList();

	glNewList(Ma_Cuisse, GL_COMPILE);
	{
		glPushMatrix();
		{
			gluDisk(qobj, 0.0, CUISSE_R, 20, 20);
			gluCylinder(qobj, CUISSE_R, MOLLET_R1, CUISSE_H, 20, 20);
			glTranslatef(0, 0, CUISSE_H);
			gluDisk(qobj, 0.0, MOLLET_R1, 20, 20);
		}
		glPopMatrix();
	}
	glEndList();
	
	glNewList(Mon_Genou, GL_COMPILE);
	{
		glutSolidSphere(MOLLET_R1, 20, 20);	
	}
	glEndList();
	
	glNewList(Mon_Mollet, GL_COMPILE);
	{
		glPushMatrix();
		{
			gluDisk(qobj, 0.0, MOLLET_R1, 20, 20);
			gluCylinder(qobj, MOLLET_R1, MOLLET_R2, CUISSE_H, 20, 20);
			glTranslatef(0, 0, CUISSE_H);
			gluDisk(qobj, 0.0, MOLLET_R2, 20, 20);
		}
		glPopMatrix();
	}
	glEndList();
	
	glNewList(Mon_Chapeau, GL_COMPILE);
	{
		glPushMatrix();
		{
			gluDisk(qobj, 0.0, CHAPEAU_R1, 20, 20);
			gluCylinder(qobj, CHAPEAU_R1, CHAPEAU_R1, CHAPEAU_H1, 20, 20);
			glTranslatef(0, 0, CHAPEAU_H1);
			gluDisk(qobj, CHAPEAU_R2, CHAPEAU_R1, 20, 20);
		}
		glPopMatrix();
		gluCylinder(qobj, CHAPEAU_R2, CHAPEAU_R2, CHAPEAU_H2, 20, 20);
		glPushMatrix();
		{
			glTranslatef(0, 0, CHAPEAU_H2);
			gluDisk(qobj, 0.0, CHAPEAU_R2, 20, 20);
		}
		glPopMatrix();
	}
	glEndList();
	
	glNewList(Ma_Paume, GL_COMPILE);
	{
		gluDisk(qobj, 0.0, PAUME_R, 20, 20);
		gluCylinder(qobj, PAUME_R, PAUME_R, PAUME_H, 20, 20);
		glPushMatrix();
		{
			glTranslatef(0, 0, PAUME_H);
			gluDisk(qobj, 0.0, PAUME_R, 20, 20);
		}
		glPopMatrix();
	}
	glEndList();
	
	glNewList(Mon_Doigt, GL_COMPILE);
	{
		glPushMatrix();
		{
			glRotatef(180,1,0,0);
			gluDisk(qobj, 0.0, DOIGT_R, 20, 20);
			gluCylinder(qobj, DOIGT_R, DOIGT_R/2, DOIGT_H, 20, 20);
			glTranslatef(0, 0, DOIGT_H);
			gluDisk(qobj, 0.0, DOIGT_R/2, 20, 20);
		}
		glPopMatrix();
	}
	glEndList();

	glNewList(Mon_Bassin, GL_COMPILE);
	{
		glPushMatrix();
		{
			glScalef(1, TRONC_SCL_Y, 0.5);
			glutSolidSphere(TRONC_R, 20, 20);
		}
		glPopMatrix();
	}
	glEndList();

	glNewList(Mon_Papillon, GL_COMPILE);
	{
		glPushMatrix();
		{
			glRotatef(90, 0, 1, 0);
			glScalef(0.75,0.1,2);
			glCallList(My_Pyramide);
			glTranslatef(0,0,1.25);
			glRotatef(180,0,1,0);
			glCallList(My_Pyramide);
		}
		glPopMatrix();
	}
	glEndList();
}

void Dessine_Repere() 
{
	glNewList(Mon_Repere, GL_COMPILE);
	{
		glBegin(GL_LINES);
		{
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(-30 , 0 , 0);
			glVertex3f(30 , 0 , 0);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(0 , -30 , 0);
			glVertex3f(0 , 30 , 0);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(0 , 0 , -30);
			glVertex3f(0 , 0 , 30);
		}
		glEnd();
		glPointSize( 10.0 );
		glBegin(GL_POINTS);
		{
			glColor3f(1.0, 1.0, 1.0);
			glVertex3f(10.0 , 0 , 0);
		}
		glEnd();
		glBegin(GL_POINTS);
		{
			glColor3f(1.0, 1.0, 1.0);
			glVertex3f(0 , 10.0 , 0);
		}
		glEnd();
		glBegin(GL_POINTS);
		{
			glColor3f(1.0, 1.0, 1.0);
			glVertex3f(0 , 0.0 , 10.0);
		}
		glEnd();
	}
	glEndList();
}

void make_triangle()
{
	My_Triangle = glGenLists(1);
	glNewList(My_Triangle, GL_COMPILE);
	{
		glBegin(GL_TRIANGLES);
		{
			glVertex3f(0,0,1);
			glVertex3f(1,1,0);
			glVertex3f(1,-1,0);
		}
		glEnd();
	}
	glEndList();
}

void make_base()
{
	My_Base = glGenLists(1);
	glNewList(My_Base, GL_COMPILE);
	{
		glBegin(GL_QUADS);
		{
			glVertex3f(1,-1,0);
			glVertex3f(1,1,0);
			glVertex3f(-1,1,0);
			glVertex3f(-1,-1,0);
		}
		glEnd();
	}	
	glEndList();
}

void make_Pyramide()
{
	My_Pyramide = glGenLists(1);
	glNewList(My_Pyramide, GL_COMPILE);
	{
		glCallList(My_Triangle);

		glPushMatrix();
		{
			glRotatef(90, 0, 0, 1);
			glCallList(My_Triangle);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glRotatef(180, 0, 0, 1);
			glCallList(My_Triangle);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glRotatef(270, 0, 0, 1);
			glCallList(My_Triangle);
		}
		glPopMatrix();

		glCallList(My_Base);
	}
	glEndList();
}

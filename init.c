#include "init.h"

static GLfloat light_position0[] = { 15.0 , 15.0 , 15.0 , 0.0 };
static GLfloat light_position1[] = { 15.0 , 15.0 , -15.0 , 0.0 };

static GLfloat ambient_light0[] = { 0.0 , 0.0 , 0.0 , 0.0 };
static GLfloat diffuse_light0[] = { 0.7 , 0.7 , 0.7 , 1.0 };
static GLfloat specular_light0[] = { 0.1 , 0.1 , 0.1 , 0.1 };

static GLfloat ambient_light1[] = { 0.50 , 0.50 , 0.50 , 1.0 };
static GLfloat diffuse_light1[] = { 0.5 , 1.0 , 1.0 , 1.0 };
static GLfloat specular_light1[] = { 0.5 , 1.0 , 1.0 , 1.0 };

static GLfloat mat_specular[] = { 1.0 , 1.0 , 1.0 , 1.0 };
static GLfloat mat_ambientanddiffuse[] = { 0.4, 0.4 , 0.0 , 1.0 };
static GLfloat mat_shininess[] = { 20.0};

int  Mon_Repere;

int  Ma_Tete;
int  Mon_Tronc;
int  Mon_Bras;
int  Mon_AvantBras;
int  Ma_Cuisse;
int  Mon_Mollet;
int  Mon_Chapeau;

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

// initialisation du fond de la fenêtre graphique : noir opaque
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
	glShadeModel( GL_SMOOTH );
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

	amplitude_Bras = .5 * (angle_Bras_Ini[Droit] - angle_Bras_Ini[Gauche]);
	amplitude_AvantBras = .5 * (angle_AvantBras_Ini[Droit] - angle_AvantBras_Ini[Gauche]);
	amplitude_Cuisse = .5 * (angle_Cuisse_Ini[Droit] - angle_Cuisse_Ini[Gauche]);
	amplitude_Mollet = .5 * (angle_Mollet_Ini[Droit] - angle_Mollet_Ini[Gauche]);
	med_Bras = .5 * (angle_Bras_Ini[Droit] + angle_Bras_Ini[Gauche]);
	med_AvantBras = .5 * (angle_AvantBras_Ini[Droit] + angle_AvantBras_Ini[Gauche]);
	med_Cuisse = .5 * (angle_Cuisse_Ini[Droit] + angle_Cuisse_Ini[Gauche]);
	med_Mollet = .5 * (angle_Mollet_Ini[Droit] + angle_Mollet_Ini[Gauche]);
}

void Faire_Composantes() 
{
	GLUquadricObj* GLAPIENTRY qobj;

	// attribution des indentificateurs de display lists
	Ma_Tete =  glGenLists(6);
	Mon_Tronc = Ma_Tete + 1;
	Mon_Bras = Ma_Tete + 2;
	Mon_AvantBras = Ma_Tete + 3;
	Ma_Cuisse = Ma_Tete + 4;
	Mon_Mollet = Ma_Tete + 5;
	Mon_Chapeau = Ma_Tete + 6;

	glNewList(Ma_Tete,GL_COMPILE);	
	{
		glutSolidSphere(1.5,20,20);	
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
		gluCylinder(qobj, 2.5, 2.5, 7.0, 20, 20);
	}
	glEndList();
	glNewList(Mon_Bras, GL_COMPILE);
	{
		gluCylinder(qobj, 0.5, 0.5, 5.0, 20, 20);
	}
	glEndList();
	glNewList(Mon_AvantBras, GL_COMPILE);
	{
		gluCylinder(qobj, 0.5, 0.25, 5.0, 20, 20);
	}
	glEndList();
	glNewList(Ma_Cuisse, GL_COMPILE);
	{
		gluCylinder(qobj, 1.25, 0.75, 5.0, 20, 20);
	}
	glEndList();
	glNewList(Mon_Mollet, GL_COMPILE);
	{
		gluCylinder(qobj, 0.75, 0.25, 5.0, 20, 20);
	}
	glEndList();
	glNewList(Mon_Chapeau, GL_COMPILE);
	{
		gluCylinder(qobj, 2, 2, 0.5, 20, 20);
		gluCylinder(qobj, 1.5, 1.5, 3.0, 20, 20);
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
			glVertex3f(-10 , 0 , 0);
			glVertex3f(10 , 0 , 0);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(0 , -10 , 0);
			glVertex3f(0 , 10 , 0);
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
	}
	glEndList();
}

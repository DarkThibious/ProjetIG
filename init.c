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

int Ma_Robe;
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

	amplitude_Bras = .5 * (angle_Bras_Ini[Droit] - angle_Bras_Ini[Gauche]);
	amplitude_AvantBras = .5 * (angle_AvantBras_Ini[Droit] - angle_AvantBras_Ini[Gauche]);
	amplitude_Cuisse = .5 * (angle_Cuisse_Ini[Droit] - angle_Cuisse_Ini[Gauche]);
	amplitude_Mollet = .5 * (angle_Mollet_Ini[Droit] - angle_Mollet_Ini[Gauche]);
	med_Bras = .5 * (angle_Bras_Ini[Droit] + angle_Bras_Ini[Gauche]);
	med_AvantBras = .5 * (angle_AvantBras_Ini[Droit] + angle_AvantBras_Ini[Gauche]);
	med_Cuisse = .5 * (angle_Cuisse_Ini[Droit] + angle_Cuisse_Ini[Gauche]);
	med_Mollet = .5 * (angle_Mollet_Ini[Droit] + angle_Mollet_Ini[Gauche]);

	amplitude_Bras_R = .5 * (angle_Bras_Ini_R[Droit] - angle_Bras_Ini_R[Gauche]);
	amplitude_AvantBras_R = .5 * (angle_AvantBras_Ini_R[Droit] - angle_AvantBras_Ini_R[Gauche]);
	amplitude_Cuisse_R = .5 * (angle_Cuisse_Ini_R[Droit] - angle_Cuisse_Ini_R[Gauche]);
	amplitude_Mollet_R = .5 * (angle_Mollet_Ini_R[Droit] - angle_Mollet_Ini_R[Gauche]);
	med_Bras_R = .5 * (angle_Bras_Ini_R[Droit] + angle_Bras_Ini_R[Gauche]);
	med_AvantBras_R = .5 * (angle_AvantBras_Ini_R[Droit] + angle_AvantBras_Ini_R[Gauche]);
	med_Cuisse_R = .5 * (angle_Cuisse_Ini_R[Droit] + angle_Cuisse_Ini_R[Gauche]);
	med_Mollet_R = .5 * (angle_Mollet_Ini_R[Droit] + angle_Mollet_Ini_R[Gauche]);
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
	Ma_Robe = Ma_Tete + 13;
	
	make_base();
	make_triangle();
	make_Pyramide();

	glNewList(Ma_Tete,GL_COMPILE);	
	{
		glScalef(1, 1, 1.5);
		glutSolidSphere(1,20,20);	
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
		// Partie supérieure du buste
		glPushMatrix();
		{
			glTranslatef(0, 0, 3.5);
			glScalef(1, 0.65, 1);
			gluDisk(qobj, 0.0, 1.5, 20, 20);
			gluCylinder(qobj, 1.5, 2.5, 3.5, 20, 20);
			glTranslatef(0, 0, 3.5);
			gluDisk(qobj, 0.0, 2.5, 20, 20);
		}
		glPopMatrix();
		
		// Partie inférieure du buste		
		glPushMatrix();
		{		
			glScalef(1, 0.65, 1);
			gluDisk(qobj, 0.0, 1.5, 20, 20);
			gluCylinder(qobj, 2.5, 1.5, 3.5, 20, 20);
			gluDisk(qobj, 0.0, 2.5, 20, 20);
		}
		glPopMatrix();
	}
	glEndList();
	
	glNewList(Mon_Bras, GL_COMPILE);
	{
		glPushMatrix();
		{
			gluDisk(qobj, 0.0, 0.5, 20, 20);
			gluCylinder(qobj, 0.5, 0.5, 4.5, 20, 20);
			glTranslatef(0, 0, 4.5);
			gluDisk(qobj, 0.0, 0.5, 20, 20);
		}
		glPopMatrix();
	}
	glEndList();
	
		glNewList(Mon_Epaule, GL_COMPILE);
	{
		glutSolidSphere(0.5,20,20);	
	}
	glEndList();
	
	glNewList(Mon_AvantBras, GL_COMPILE);
	{
		gluDisk(qobj, 0.0, 0.5, 20, 20);
		gluCylinder(qobj, 0.5, 0.25, 4.5, 20, 20); 
		glPushMatrix();
		{
			glTranslatef(0, 0, 4.5);
			gluDisk(qobj, 0.0, 0.25, 20, 20);
		}
		glPopMatrix();
	}
	glEndList();
	
	glNewList(Mon_Coude, GL_COMPILE);
	{
		glutSolidSphere(0.5,20,20);	
	}
	glEndList();

	
	glNewList(Ma_Cuisse, GL_COMPILE);
	{
		gluDisk(qobj, 0.0, 1.25, 20, 20);
		gluCylinder(qobj, 1.25, 0.75, 5.0, 20, 20);
		glPushMatrix();
		{
			glTranslatef(0, 0, 5);
			gluDisk(qobj, 0.0, 0.75, 20, 20);
		}
		glPopMatrix();
	}
	glEndList();
	
	glNewList(Mon_Genou, GL_COMPILE);
	{
		glutSolidSphere(0.75,20,20);	
	}
	glEndList();
	
	glNewList(Mon_Mollet, GL_COMPILE);
	{
		gluDisk(qobj, 0.0, 0.75, 20, 20);
		gluCylinder(qobj, 0.75, 0.25, 5.0, 20, 20);
		glPushMatrix();
		{
			glTranslatef(0, 0, 5);
			gluDisk(qobj, 0.0, 0.25, 20, 20);
		}
		glPopMatrix();
	}
	glEndList();
	
	glNewList(Mon_Chapeau, GL_COMPILE);
	{
		gluDisk(qobj, 0.0, 2, 20, 20);
		gluCylinder(qobj, 2, 2, 0.5, 20, 20);
		glPushMatrix();
		{
			glTranslatef(0, 0, 0.5);
			gluDisk(qobj, 1.5, 2, 20, 20);
		}
		glPopMatrix();
		gluCylinder(qobj, 1.5, 1.5, 3.0, 20, 20);
		glPushMatrix();
		{
			glTranslatef(0, 0, 3);
			gluDisk(qobj, 0.0, 1.5, 20, 20);
		}
		glPopMatrix();
	}
	glEndList();
	
	glNewList(Ma_Paume, GL_COMPILE);
	{
		gluDisk(qobj, 0.0, 0.35, 20, 20);
		gluCylinder(qobj, 0.35, 0.35, 0.5, 20, 20);
		glPushMatrix();
		{
			glTranslatef(0, 0, 0.5);
			gluDisk(qobj, 0.0, 0.35, 20, 20);
		}
		glPopMatrix();
	}
	glEndList();
	
	glNewList(Mon_Doigt, GL_COMPILE);
	{
		gluDisk(qobj, 0.0, 0.1, 20, 20);
		gluCylinder(qobj, 0.1, 0.05, 0.5, 20, 20);
		glPushMatrix();
		{
			glTranslatef(0, 0, 0.5);
			gluDisk(qobj, 0.0, 0.05, 20, 20);
		}
		glPopMatrix();
	}
	glEndList();
	
	glNewList(Mon_Papillon, GL_COMPILE);
	{
		glPushMatrix();
		{
			glCallList(My_Pyramide);
			glTranslatef(0,0,1.25);
			glRotatef(180,0,1,0);
			glCallList(My_Pyramide);
		}
	glPopMatrix();
	}
	glEndList();
	
	glNewList(Ma_Robe, GL_COMPILE);
	{
		glPushMatrix();
		{
			//glScalef(1, 0.65, 1);
			//gluDisk(qobj, 0.0, 1.5, 20, 20);
			gluCylinder(qobj, 3, 1.51, 7, 20, 20); //4 2.5

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

#include "disp.h"

// fonction de call-back pour l´affichage dans la fenêtre
GLvoid window_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	render_scene();

	// trace la scène graphique qui vient juste d'être définie
	glFlush();
}

// fonction de call-back pour le redimensionnement de la fenêtre

GLvoid window_reshape(GLsizei width, GLsizei height)
{  
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -20, 20, -1000, 1000);
	// glFrustum(-20, 20, -20, 20, 10, 1000);
	// glScalef(10, 10, 10);

	// toutes les transformations suivantes s´appliquent au modèle de vue 
	glMatrixMode(GL_MODELVIEW);
}

void render_scene()
{
	Dessine_Repere();
	// rotation de 90 degres autour de Ox pour mettre l'axe Oz 
	// vertical comme sur la figure
	glRotatef(-90, 1, 0, 0);

	// rotation de 160 degres autour de l'axe Oz pour faire
	// avancer l'avatar vers le spectateur
	glRotatef(-160, 0, 0, 1);

	// rotation de 25 degres autour de la bissectrice de $Oy$ pour
	// voir la figure en perspective
	//glRotatef(25, 0, 1, 0);

	// déplacement horizontal selon l´axe Oy pour donner 
	// une impression de déplacement horizontal accompagnant
	// la marche
	//glTranslatef( 0, position, 0);

	// tracé du tronc, aucune transformation n´est
	// requise
	glColor3f(1.0, 1.0, 1.0);
	glCallList(Mon_Tronc);

	// tracé de la tête avec une translation positive
	// selon Oz pour la placer au-dessus du tronc
	// les appels à glPushMatrix et glPopMatrix servent 
	// à sauvegarder et restaurer le contexte graphique
	// ********* A FAIRE **************
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	{
		glTranslatef(0, 0, 8.5);
		glCallList(Ma_Tete);
	}
	glPopMatrix();

	// tracé de la cuisse droite avec une translation vers
	// la droite et une rotation de 180° autour de Ox
	// pour l´orienter vers le bas
	// ********* A FAIRE **************
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	{
		glRotatef(180,1,0,0);
		glTranslatef(1.25, 0, 0);
		glRotatef(angle_Cuisse[Droit],1,0,0);
		glCallList(Ma_Cuisse);

		// pour tracer le mollet, on reste dans le même
		// contexte graphique et on translate de
		// +5 selon Oz afin de mettre le repère au niveau
		// du genou
		// ********* A FAIRE **************
		glPushMatrix();
		{
			glColor3f(1.0, 0.25, 0.25);
			glTranslatef(0, 0, 5);
			glRotatef(angle_Mollet[Droit],1,0,0);
			glCallList(Mon_Mollet);
		}
		glPopMatrix();
	}
	glPopMatrix();

	// cuisse et mollet gauches
	// seule la translation initiale change
	// ********* A FAIRE **************
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	{
		glRotatef(180,1,0,0);
		glTranslatef(-1.25, 0, 0);
		glRotatef(angle_Cuisse[Gauche],1,0,0);
		glCallList(Ma_Cuisse);
		glColor3f(1.0, 0.25, 0.25);
		glTranslatef(0, 0, 5);
		glRotatef(angle_Mollet[Gauche],1,0,0);
		glCallList(Mon_Mollet);
	}
	glPopMatrix();

	// tracé du bras droit avec une translation vers
	// la droite et vers le haut composée avec une 
	// rotation de 180° autour de Ox pour l´orienter
	// vers le bas
	// ********* A FAIRE **************
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	{	
		glTranslatef(3.25, 0, 7);
		glRotatef(180,1,0,0);
		glRotatef(angle_Bras[Droit],1,0,0);
		glCallList(Mon_Bras);

		// pour tracer l´avant-bras, on reste dans le même
		// contexte graphique et on translate de
		// +5 selon Oz afin de mettre le repère au niveau
		// du coude
		// ********* A FAIRE **************
		glPushMatrix();
		{
			glColor3f(0.25, 0.25, 1.0);
			glTranslatef(0, 0, 5);
			glRotatef(angle_AvantBras[Droit],1,0,0);
			glCallList(Mon_AvantBras);
		}
		glPopMatrix();
	}
	glPopMatrix();

	// bras et avant-bras gauches
	// seule la translation initiale change
	// ********* A FAIRE **************
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	{
		glTranslatef(-3.25, 0, 7);
		glRotatef(180,1,0,0);
		glRotatef(angle_Bras[Gauche],1,0,0);
		glCallList(Mon_Bras);
		glPushMatrix();
		{
			glColor3f(0.25, 0.25, 1.0);
			glTranslatef(0, 0, 5);
			glRotatef(angle_AvantBras[Gauche],1,0,0);
			glCallList(Mon_AvantBras);
		}
		glPopMatrix();
	}
	glPopMatrix();

	//dessin du chapeau
	glColor3f(1, 0, 1);
	glPushMatrix();
	{
		glTranslatef(0, 0, 9.5);
		glCallList(Mon_Chapeau);
	}
	glPopMatrix();

	// permutation des buffers lorsque le tracé est achevé
	glutSwapBuffers();
}

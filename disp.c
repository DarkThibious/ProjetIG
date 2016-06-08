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
	//glFrustum(-20, 20, -20, 20, 10, 1000);
	// glScalef(10, 10, 10);

	// toutes les transformations suivantes s´appliquent au modèle de vue 
	glMatrixMode(GL_MODELVIEW);
}

void render_scene()
{
	// rotation de 90 degres autour de Ox pour mettre l'axe Oz 
	// vertical comme sur la figure
	glRotatef(-90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);

	// rotation de 160 degres autour de l'axe Oz pour faire
	// avancer l'avatar vers le spectateur
	//glRotatef(-160, 0, 0, 1);

	// rotation de 25 degres autour de la bissectrice de $Oy$ pour
	// voir la figure en perspective
	//glRotatef(25, 0, 1, 0);

	glRotatef(angleVisZ, 0 , 0, 1);
	glRotatef(angleVisX, 1 , 0, 0);

	glTranslatef(0,0,-10);

	Dessine_Repere();

	drawEntity(chaise);
	drawEntity(homme);
	//dessin_bonhomme();
	glColor3f(0.5,1,0.5);
	glPushMatrix();
	{
	//	glTranslatef(0,50,0);
		glRotatef(180,0,0,1);
		glScalef(1.3,1.3,1.75);
	//	glCallList(Ma_Chaise);
	}
	glPopMatrix();

	// permutation des buffers lorsque le tracé est achevé
	glutSwapBuffers();
}

void dessin_bonhomme()
{
	glPushMatrix();
	{
		glTranslatef(position_X, position_Y, CUISSE_H*2-TRONC_R/10-0.05);
		//glScalef(1+position/500,1+position/500, 1+position/500);
		if(doing == RUN || (doing == STOP && prevDoing == RUN))
		{
			glRotatef(-10, 1, 0, 0);
		}
		// tracé du tronc, aucune transformation n´est
		// requise
		glColor3f(1.0, 1.0, 1.0);
		glCallList(Mon_Tronc);

		// tracé de la tête avec une translation positive
		// selon Oz pour la placer au-dessus du tronc
		// les appels à glPushMatrix et glPopMatrix servent 
		// à sauvegarder et restaurer le contexte graphique
		glColor3f(1.0, 1.0, 0.0);
		glPushMatrix();
		{
			glTranslatef(0, 0, TRONC_H+TETE_R);
			glCallList(Ma_Tete);
		}
		glPopMatrix();

		// tracé de la cuisse droite avec une translation vers
		// la droite et une rotation de 180° autour de Ox
		// pour l´orienter vers le bas

		glColor3f(1.0, 0.0, 0.0);
		glCallList(Mon_Bassin);
		glPushMatrix();
		{
			glRotatef(angle_Cuisse[DROITE],1,0,0);
			glTranslatef(CUISSE_R-0.1, 0, -TRONC_R/10-0.05);
			glCallList(Ma_Cuisse);

			// pour tracer le mollet, on reste dans le même
			// contexte graphique et on translate de
			// +5 selon Oz afin de mettre le repère au niveau
			// du genou
			glPushMatrix();
			{
				glColor3f(1.0, 0.25, 0.25);
				glTranslatef(0, 0, -CUISSE_H);
				glRotatef(angle_Mollet[DROITE],1,0,0);
				glCallList(Mon_Genou);
				glCallList(Mon_Mollet);
			}
			glPopMatrix();
		}
		glPopMatrix();

		// cuisse et mollet gauches
		// seule la translation initiale change
		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		{
			glRotatef(angle_Cuisse[GAUCHE],1,0,0);
			glTranslatef(-(CUISSE_R-0.1), 0, -TRONC_R/10-0.05);
			glCallList(Ma_Cuisse);
			glColor3f(1.0, 0.25, 0.25);
			glTranslatef(0, 0, -CUISSE_H);
			glRotatef(angle_Mollet[GAUCHE],1,0,0);
			glCallList(Mon_Genou);
			glCallList(Mon_Mollet);
		}
		glPopMatrix();

		// tracé du bras droit avec une translation vers
		// la droite et vers le haut composée avec une 
		// rotation de 180° autour de Ox pour l´orienter
		// vers le bas
		glColor3f(0.0, 0.0, 1.0);
		glPushMatrix();
		{	
			glTranslatef(TRONC_R+BRAS_R, 0, TRONC_H-BRAS_R);
			glRotatef(angle_Bras[DROITE],1,0,0);
			glCallList(Mon_Epaule);
			glCallList(Mon_Bras);

			// pour tracer l´avant-bras, on reste dans le même
			// contexte graphique et on translate de
			// +5 selon Oz afin de mettre le repère au niveau
			// du coude
			glPushMatrix();
			{
				glColor3f(0.25, 0.25, 1.0);
				glTranslatef(0, 0, -(BRAS_H+BRAS_R/2));
				glRotatef(angle_AvantBras[DROITE],1,0,0);
				glCallList(Mon_Coude);
				glCallList(Mon_AvantBras);
				glPushMatrix();
				{
					glTranslatef(0, 0, -(BRAS_H+BRAS_R/2));
					glTranslatef(-PAUME_H/2, 0, 0);
					glRotatef(180, 1, 1, 0);
					glColor3f(0.5, 0.5, 1.0);
					glCallList(Ma_Paume);
					glPushMatrix();
					{
						glRotatef(90, 1, 0, 0);
						glPushMatrix();
						{
							glRotatef(-100, 0, 1, 0);
							glTranslatef(0, PAUME_H/2, -PAUME_R);
							glCallList(Mon_Doigt);
						}
						glPopMatrix();
						glPushMatrix();
						{
							glRotatef(-155, 0, 1, 0);
							glTranslatef(0, PAUME_H/2, -PAUME_R);
							glCallList(Mon_Doigt);
						}
						glPopMatrix();
						glPushMatrix();
						{
							glRotatef(-180, 0, 1, 0);
							glTranslatef(0, PAUME_H/2, -PAUME_R);
							glCallList(Mon_Doigt);
						}
						glPopMatrix();
						glPushMatrix();
						{
							glRotatef(-205, 0, 1, 0);
							glTranslatef(0, PAUME_H/2, -PAUME_R);
							glCallList(Mon_Doigt);
						}
						glPopMatrix();
						glPushMatrix();
						{
							glRotatef(-230, 0, 1, 0);
							glTranslatef(0, PAUME_H/2, -PAUME_R);
							glCallList(Mon_Doigt);
						}
						glPopMatrix();
					}
					glPopMatrix();

				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();

		// bras et avant-bras gauches
		// seule la translation initiale change
		glColor3f(0.0, 0.0, 1.0);
		glPushMatrix();
		{
			glTranslatef(-(TRONC_R+BRAS_R), 0, TRONC_H-BRAS_R);
			glRotatef(angle_Bras[GAUCHE],1,0,0);
			glCallList(Mon_Epaule);
			glCallList(Mon_Bras);
			glPushMatrix();
			{
				glColor3f(0.25, 0.25, 1.0);
				glTranslatef(0, 0, -(BRAS_H+BRAS_R/2));
				glRotatef(angle_AvantBras[GAUCHE],1,0,0);
				glCallList(Mon_Coude);
				glCallList(Mon_AvantBras);
				glPushMatrix();
				{
					glTranslatef(0, 0,-(BRAS_H+BRAS_R/2));
					glTranslatef(0.25, 0, 0);
					glRotatef(90, 1, 0, 0);
					glRotatef(-90, 0, 1, 0);
					glColor3f(0.5, 0.5, 1.0);
					glCallList(Ma_Paume);
					glPushMatrix();
					{
						glRotatef(90, 1, 0, 0);
						glPushMatrix();
						{
							glRotatef(125, 0, 1, 0);
							glTranslatef(0, PAUME_H/2, -PAUME_R);
							glCallList(Mon_Doigt);
						}
						glPopMatrix();
						glPushMatrix();
						{
							glRotatef(165, 0, 1, 0);
							glTranslatef(0, PAUME_H/2, -PAUME_R);
							glCallList(Mon_Doigt);
						}
						glPopMatrix();
						glPushMatrix();
						{
							glRotatef(180, 0, 1, 0);
							glTranslatef(0, PAUME_H/2, -PAUME_R);
							glCallList(Mon_Doigt);
						}
						glPopMatrix();
						glPushMatrix();
						{
							glRotatef(195, 0, 1, 0);
							glTranslatef(0, PAUME_H/2, -PAUME_R);
							glCallList(Mon_Doigt);
						}
						glPopMatrix();
						glPushMatrix();
						{
							glRotatef(210, 0, 1, 0);
							glTranslatef(0, PAUME_H/2, -PAUME_R);
							glCallList(Mon_Doigt);
						}
						glPopMatrix();
					}
					glPopMatrix();
				}
				glPopMatrix();
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

		//dessin du noeud papillon
		glColor3f(0, 0, 0); 
		{
			glTranslatef(-1.25, TRONC_R*TRONC_SCL_Y, PAPILLON_H);
			glCallList(Mon_Papillon);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawEntity(entity e)
{
	printf("%d\n", e.listeDessin);
	int i;
	if(e.color[R] != -1.0 && e.color[G] != -1.0 && e.color[B] != -1.0)
	{
		glColor3f(e.color[R], e.color[G], e.color[B]);
	}
	glPushMatrix();	
	{
		glTranslatef(e.pos[X], e.pos[Y], e.pos[Z]);
		glRotatef(e.rotat[ANGLE], e.rotat[X], e.rotat[Y], e.rotat[Z]);
		glCallList(e.listeDessin);
		for(i=0;i<e.nbCompo;i++)
		{
			if(e.color[R] != -1.0 && e.color[G] != -1.0 && e.color[B] != -1.0)
			{
				glColor3f(e.color[R], e.color[G], e.color[B]);
			}
			drawEntity(e.compo[i]);
		}
	}
	glPopMatrix();
}

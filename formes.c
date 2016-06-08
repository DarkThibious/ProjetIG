#include "formes.h"

int Ma_Chaise;
int My_Cube;
int My_Square;

void make_Chaise()
{
	Ma_Chaise = glGenLists(1);
	glNewList(Ma_Chaise, GL_COMPILE);
	{
		glPushMatrix();
		{
			glScalef(1.3,1.3,1.75);
			glTranslatef(-2,+0.75-5.5/2,1.5);
			glPushMatrix();
			{
				glScalef(1.5,1.5,3);
				glCallList(My_Cube);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(4,0,0);
				glScalef(1.5,1.5,3);
				glCallList(My_Cube);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0,4,0);
				glScalef(1.5,1.5,3);
				glCallList(My_Cube);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(4,4,0);
				glScalef(1.5,1.5,3);
				glCallList(My_Cube);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(2,2,2);
				glScalef(5.5,5.5,1);
				glCallList(My_Cube);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0,-0.5,4.25);
				glRotatef(15,1,0,0);
				glScalef(1.5,1.5,4);
				glCallList(My_Cube);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(4,-0.5,4.25);
				glRotatef(15,1,0,0);
				glScalef(1.5,1.5,4);
				glCallList(My_Cube);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(2,-0.5,4.25);
				glRotatef(15,1,0,0);
				glScalef(4,1.5,1);
				glCallList(My_Cube);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glEndList();
}

void make_square() 
{
	My_Square = glGenLists(1);
	glNewList(My_Square, GL_COMPILE);
	{
		glBegin(GL_POLYGON);
		{
			glVertex3f(0, 0, 0);
			glVertex3f(1, 0, 0);
			glVertex3f(1, 1, 0);
			glVertex3f(0, 1, 0);
		}
		glEnd();
	}
	glEndList();
}

void make_cube() 
{
	My_Cube = glGenLists(1);
	glNewList(My_Cube, GL_COMPILE);
	{
		glTranslatef(-0.5, -0.5, 0.5);
		glCallList(My_Square);
		glPushMatrix();
		{
			glTranslatef(0, 0, -1);
			glCallList(My_Square);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glRotatef(90, 0, 1, 0);
			glCallList(My_Square);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(1, 0, 0);
			glRotatef(90, 0, 1, 0);
			glCallList(My_Square);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glRotatef(-90, 1, 0, 0);
			glCallList(My_Square);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0, 1, 0);
			glRotatef(-90, 1, 0, 0);
			glCallList(My_Square);
		}
		glPopMatrix();
	}
	glEndList();
}

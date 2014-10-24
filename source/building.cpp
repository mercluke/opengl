#include "building.h"

void building (int segments)
{
	//Cylinder for base of clock tower
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, TEX_STEEL);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE);
		glRotated(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(0.0f, 7.5f, -5.0f);
		glColor3f(0.655f, 0.655f, 0.706f);
			GLUquadric* quad = gluNewQuadric();
			gluQuadricTexture(quad, true);
			gluCylinder(quad, 2.5, 2.5, 8.0, segments, segments);			               
		glEnd();
		glPopMatrix();
	//conical cylinder for roof of clock tower
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, TEX_GLASS);
		glPushMatrix();
		glColor3f(1.0,1.0,1.0);
		glRotated(-90.0, 1.0, 0.0, 0.0);
			glTranslatef(0.0f, 7.5f, 3.0f);
			gluQuadricTexture(quad, true);
			gluCylinder(quad, 2.5, 0, 2.0, segments, segments);
			glEnd();
		glDisable(GL_TEXTURE_2D);
		free(quad);
		glPopMatrix();
}
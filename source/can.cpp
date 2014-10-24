#include "can.h"

void can(int segments)
{

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glBindTexture(GL_TEXTURE_2D, TEX_CAN);
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glRotatef(-90,1.0f,0.0f,0.0f);
			glPushMatrix();
			glTranslatef(20.0f, -2.0f, -5.0f);
			glColor3f(1.0f,1.0f,1.0f);

			GLUquadric* quad = gluNewQuadric();
			gluQuadricTexture(quad, true);
			gluCylinder(quad, 1.0, 1.0, 3.0, segments, segments);
			glDisable(GL_TEXTURE_2D);
			glPushMatrix();
				glTranslated(0.0, 0.0, 3.0);
				gluDisk(quad, 0.0, 1.0, segments, segments);
			glPopMatrix();
			glPushMatrix();
				glRotated(180.0, 1.0, 0.0, 0.0);
				gluDisk(quad, 0.0, 1.0, segments, segments);
			glPopMatrix();
			free(quad);
			
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();

	glPopMatrix();
}
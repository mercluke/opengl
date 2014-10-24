#include "clock.h"

void clock(GLfloat hour, GLfloat minute, int segments)
{
	glPushMatrix();
		glTranslatef(0,0,0.1);

		/**Begin clockface**/
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -5.0f);
		glColor3f(1.0f, 1.0f, 1.0f); 
	    glBegin( GL_TRIANGLE_FAN );
	    glNormal3f(0.0, 0.0f, 1.0f);
	        glVertex2f(0, 0);
	        for( int i = 0; i <= segments; i++ ) {
	        	//draw circle with maths, more detail == more points
	            GLfloat v = TAU*(float)i/(float)segments;
	            glVertex2f(sin(v), cos(v));
	        }
	    glEnd();
		glLoadIdentity();
	    glPopMatrix();
	    /**End clockface**/
		



	    glPushMatrix();
			glTranslatef(0,0,0.1);
			/**Begin minute hand**/
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, -5.0f);
				glRotatef(-(360.0/60)*minute,0.0f,0.0f,1.0f);	
				glColor3f(1.0f,0.0f,0.0f);
				glBegin( GL_QUADS );
				glNormal3f(0.0, 0.0f, 1.0f);                  	
				glVertex3f( -0.05f, 0.0f, 0.0f);          
				glVertex3f( -0.025f, 1.0f, 0.0f);          
				glVertex3f( 0.025f, 1.0f, 0.0f);          
				glVertex3f( 0.05f, 0.0f, 0.0f);          
				glVertex3f( 0.0f, 0.0f, 0.0f);          
			glEnd();
			glLoadIdentity();
			glPopMatrix();
			/**End minute hand**/

			/**Begin hour hand**/
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, -5.0f);
				glRotatef(-(360.0/12)*(hour+(minute/60)),0.0f,0.0f,1.0f);
				glColor3f(0.0f,0.0f,0.2f);
				glBegin( GL_QUADS );
				glNormal3f(0.0, 0.0f, 1.0f);           
				glVertex3f( -0.05f, 0.0f, 0.0f);       
				glVertex3f( -0.025f, 0.6f, 0.0f);     
				glVertex3f( 0.025f, 0.6f, 0.0f); 
				glVertex3f( 0.05f, 0.0f, 0.0f);      
				glVertex3f( 0.0f, 0.0f, 0.0f);       
			glEnd();
			glLoadIdentity();
			glPopMatrix();
			/**End hour hand**/

		glPopMatrix();

	glPopMatrix();
}

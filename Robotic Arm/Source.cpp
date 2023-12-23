/*
 * Copyright (c) 1993-1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

 /*
  * robot.c
  * This program shows how to composite modeling transformations
  * to draw translated and rotated hierarchical models.
  * Interaction:  pressing the s and e keys (shoulder and elbow)
  * alters the rotation of the robot arm.
  */
//Name:Tarek Mohamed Rashad
//Sec: 1
//BN: 43

#include <stdlib.h>
#include <GL/glut.h>

static int shoulder = 0, elbow = 0, ThumbBase = 0, ThumbUp = 0, IndexBase = 0, IndexUp = 0;
static int MiddleBase = 0, MiddleUp = 0, RingBase = 0, RingUp = 0, LittleBase = 0, LittleUp = 0;
int moving, startx, starty;


GLfloat angle = 0.0;   // in degrees 
GLfloat angle2 = 0.0;   // in degrees 


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(angle2, 1.0, 0.0, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glTranslatef(-1.0, 0.0, 0.0);
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.6, 1.0);
	glutWireCube(1.0);
	glPopMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.6, 1.0);
	glutWireCube(1.0);
	glPopMatrix();

	//Draw Thumb flang 1 
	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)ThumbBase, 0.0, 0.0, 1.0);
	glTranslatef(0.15, 0.25, 0.45);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();

	//Draw Thumb flang 2 
	glTranslatef(0.15, 0.0, 0.0);
	glRotatef((GLfloat)ThumbUp, 0.0, 0.0, 1.0);
	glTranslatef(0.15, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
	
	//Draw Index flang 1 
	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)IndexBase, 0.0, 0.0, 1.0);
	glTranslatef(0.15, -0.25, 0.45);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();


	//Draw Index flang 2 
	glTranslatef(0.15, 0.0, 0.0);
	glRotatef((GLfloat)IndexUp, 0.0, 0.0, 1.0);
	glTranslatef(0.15, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();

	
	//Draw Middle flang 1 
	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)MiddleBase, 0.0, 0.0, 1.0);
	glTranslatef(0.15, -0.25, 0.15);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	

	//Draw Middle flang 2 
	glTranslatef(0.15, 0.0, 0.0);
	glRotatef((GLfloat)MiddleUp, 0.0, 0.0, 1.0);
	glTranslatef(0.15, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();

	//Draw Ring flang 1 
	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)RingBase, 0.0, 0.0, 1.0);
	glTranslatef(0.15, -0.25, -0.15);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();

	//Draw Ring flang 2 
    glTranslatef(0.15, 0.0, 0.0);
	glRotatef((GLfloat)RingUp, 0.0, 0.0, 1.0);
	glTranslatef(0.15, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();

	
	//Draw Little flang 1 
	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)LittleBase, 0.0, 0.0, 1.0);
	glTranslatef(0.15, -0.25, -0.45);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();

	
	//Draw Little flang 2 
	glTranslatef(0.15, 0.0, 0.0);
	glRotatef((GLfloat)LittleUp, 0.0, 0.0, 1.0);
	glTranslatef(0.15, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
	
	
	glPopMatrix();
	glutSwapBuffers();   
} 

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(85.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's': if (shoulder == 90) { break; }
		shoulder = (shoulder + 5) % 360;
		glutPostRedisplay();
		break;
	case 'S':if (shoulder == -180) { break; }
		shoulder = (shoulder - 5) % 360;
		glutPostRedisplay();
		break;
	case 'e': if (elbow == 120) { break; }
		elbow = (elbow + 5) % 360;
		glutPostRedisplay();
		break;
	case 'E': if (elbow == 0) { break; }
		elbow = (elbow - 5) % 360;
		glutPostRedisplay();
		break;
	case 'z': if (ThumbBase == 0) { break; }
		ThumbBase = (ThumbBase + 5) % 360;
		glutPostRedisplay();
		break;
	case 'Z': if (ThumbBase == 0) { break; }
		ThumbBase = (ThumbBase - 5) % 360;
		glutPostRedisplay();
		break;
	case 'x': if (IndexBase == 0) { break; }
		IndexBase = (IndexBase + 5) % 360;
		glutPostRedisplay();
		break;
	case 'X': if (IndexBase == 0) { break; }
		IndexBase = (IndexBase - 5) % 360;
		glutPostRedisplay();
		break;
	case 'c': if (MiddleBase == 0) { break; }
		MiddleBase = (MiddleBase + 5) % 360;
		glutPostRedisplay();
		break;
	case 'C': if (MiddleBase == 0) { break; }
		MiddleBase = (MiddleBase - 5) % 360;
		glutPostRedisplay();
		break;
	case 'v': if (RingBase == 0) { break; }
		RingBase = (RingBase + 5) % 360;
		glutPostRedisplay();
		break;
	case 'V': if (RingBase == 0) { break; }
		RingBase = (RingBase - 5) % 360;
		glutPostRedisplay();
		break;
	case 'b': if (LittleBase == 0) { break; }
		LittleBase = (LittleBase + 5) % 360;
		glutPostRedisplay();
		break;
	case 'B': if (LittleBase == 0) { break; }
		LittleBase = (LittleBase - 5) % 360;
		glutPostRedisplay();
		break;
	case 'f': if (ThumbUp == 0) { break; }
		ThumbUp = (ThumbUp + 5) % 360;
		glutPostRedisplay();
		break;
	case 'F': if (ThumbUp == -65) { break; }
		ThumbUp = (ThumbUp - 5) % 360;
		glutPostRedisplay();
		break;
	case 'g': if (IndexUp == 90) { break; }
		IndexUp = (IndexUp + 5) % 360;
		glutPostRedisplay();
		break;
	case 'G': if (IndexUp == 0) { break; }
		IndexUp = (IndexUp - 5) % 360;
		glutPostRedisplay();
		break;
	case 'h': if (MiddleUp == 90) { break; }
		MiddleUp = (MiddleUp + 5) % 360;
		glutPostRedisplay();
		break;
	case 'H': if (MiddleUp == 0) { break; }
		MiddleUp = (MiddleUp - 5) % 360;
		glutPostRedisplay();
		break;
	case 'j': if (RingUp == 90) { break; }
		RingUp = (RingUp + 5) % 360;
		glutPostRedisplay();
		break;
	case 'J': if (RingUp == 0) { break; }
		RingUp = (RingUp - 5) % 360;
		glutPostRedisplay();
		break;
	case 'k': if (LittleUp == 90) { break; }
		LittleUp = (LittleUp + 5) % 360;
		glutPostRedisplay();
		break;
	case 'K': if (LittleUp == 0) { break; }
		LittleUp = (LittleUp - 5) % 360;
		glutPostRedisplay();
		break;

	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

static void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			moving = 1;
			startx = x;
			starty = y;
		}
		if (state == GLUT_UP) {
			moving = 0;
		}
	}
}


static void motion(int x, int y)
{
	if (moving) {
		angle = angle + (x - startx);
		angle2 = angle2 + (y - starty);
		startx = x;
		starty = y;
		glutPostRedisplay();
	}
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}



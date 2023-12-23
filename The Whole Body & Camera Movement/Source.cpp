#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>


#define PI 3.14

double eye[] = { 0.0, 0.0, 5.0 };
double center[] = { 0.0, 0.0, 0.0 };
double up[] = { 0.0, 1.0, 0.0 };

static int elbow = 0, RThumbUp = 0, RfingerUp = 0;
static int Body = 0, Head = 0, LFemur = 0, LTibia = 0, RFemur = 0, RTibia = 0, LThumbUp = 0, LfingerUp = 0;
static int shoulder1 = 0, shoulder2 = 0, shoulder3 = 0, RFemur2 = 0, LFemur2 = 0;
int moving, startx, starty;


GLfloat angle = 0.0;   // in degrees 
GLfloat angle2 = 0.0;   // in degrees 

static double zoomFactor = 1.0;	//Zooming in/out 
static double zoomFactor2 = 1.0;





void rotatePoint(double a[], double theta, double p[])
{

	double temp[3];
	temp[0] = p[0];
	temp[1] = p[1];
	temp[2] = p[2];

	temp[0] = -a[2] * p[1] + a[1] * p[2];
	temp[1] = a[2] * p[0] - a[0] * p[2];
	temp[2] = -a[1] * p[0] + a[0] * p[1];

	temp[0] *= sin(theta);
	temp[1] *= sin(theta);
	temp[2] *= sin(theta);

	temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
	temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
	temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

	temp[0] += cos(theta) * p[0];
	temp[1] += cos(theta) * p[1];
	temp[2] += cos(theta) * p[2];

	p[0] = temp[0];
	p[1] = temp[1];
	p[2] = temp[2];
}

void crossProduct(double a[], double b[], double c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])      //Unit Vector
{
	double norm;
	norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	norm = sqrt(norm);
	a[0] /= norm;
	a[1] /= norm;
	a[2] /= norm;
}

// Rotation about vertical direction
void lookRight()
{
	rotatePoint(up, PI / 8, eye);
}

void lookLeft()
{
	rotatePoint(up, -PI / 8, eye);

}

// Rotation about horizontal direction

void lookUp()
{
	double horizontal[3];
	double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
	crossProduct(up, look, horizontal);
	normalize(horizontal);
	rotatePoint(horizontal, PI / 8, eye);
	rotatePoint(horizontal, PI / 8, up);
}

void lookDown()
{
	double horizontal[3];
	double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
	crossProduct(up, look, horizontal);
	normalize(horizontal);
	rotatePoint(horizontal, -PI / 8, eye);
	rotatePoint(horizontal, -PI / 8, up);

}

// Forward and Backward
void moveForward()
{
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];
	float speed = 0.1;
	eye[0] += direction[0] * speed;
	eye[1] += direction[1] * speed;
	eye[2] += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[1] += direction[1] * speed;
	center[2] += direction[2] * speed;
}

void moveBackward()
{
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];
	float speed = 0.1;
	eye[0] -= direction[0] * speed;
	eye[1] -= direction[1] * speed;
	eye[2] -= direction[2] * speed;

	center[0] -= direction[0] * speed;
	center[1] -= direction[1] * speed;
	center[2] -= direction[2] * speed;
}

void init(void)
{
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60.0,
		1.0,
		1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void reset()
{
	double e[] = { 0.0, 0.0, 5.0 };
	double c[] = { 0.0, 0.0, 0.0 };
	double u[] = { 0.0, 1.0, 0.0 };
	for (int i = 0; i < 3; i++)
	{
		eye[i] = e[i];
		center[i] = c[i];
		up[i] = u[i];
	}
}


void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		lookLeft();
		break;
	case GLUT_KEY_RIGHT:
		lookRight();
		break;
	case GLUT_KEY_UP:
		lookUp();
		break;
	case GLUT_KEY_DOWN:
		lookDown();
		break;
	}
	glutPostRedisplay();
}




void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		up[0], up[1], up[2]);
	glClear(GL_COLOR_BUFFER_BIT);

	//Body
	glPushMatrix();
	glRotatef(angle2, 1.0, 0.0, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glTranslatef(-0.75, 0.0, 0.0);
	glRotatef((GLfloat)Body, 0.0, 0.0, 1.0);
	glTranslatef(0.75, 0.0, 0.0);
	glPushMatrix();
	glScalef(1.5, 3.0, 0.6);
	glutWireCube(1.0);
	glPopMatrix();

	//head
	glPushMatrix();
	glTranslatef(0.0, 2.25, 0.0);
	glPushMatrix();
	glutWireSphere(0.5, 10.0, 10.0);
	glPopMatrix();
	glPopMatrix();

	//Rshoulder and Relbow
	glPushMatrix();
	glTranslatef(1.0, 1.25, 0.0);
	glRotatef((GLfloat)shoulder1, 0.0, 0.0, 1.0);
	glRotatef((GLfloat)shoulder2, 0.0, 1.0, 0.0);
	glRotatef((GLfloat)shoulder3, 1.0, 0.0, 0.0);
	glTranslatef(0.5, 0.0, 0.0);
	glPushMatrix();
	glScalef(1.0, 0.5, 0.2);
	glutWireCube(1.0);
	glPopMatrix();
	glTranslatef(0.5, 0.0, 0.0);
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
	glTranslatef(0.5, 0.0, 0.0);
	glPushMatrix();
	glScalef(1.0, 0.5, 0.2);
	glutWireCube(1.0);
	glPopMatrix();


	//Right fingers 
	//Draw Thumb  
	glPushMatrix();
	glTranslatef(0.5, 0.225, -0.075);
	glTranslatef(0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.05, 0.05);
	glutWireCube(1);
	glPopMatrix();
	glTranslatef(0.1, 0.0, 0.0);
	glRotatef((GLfloat)RThumbUp, 0.0, 1.0, 0.0);
	glTranslatef(0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.05, 0.05);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();


	//Draw Index 
	glPushMatrix();
	glTranslatef(0.5, 0.225, 0.075);
	glTranslatef(0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.05, 0.05);
	glutWireCube(1);
	glPopMatrix();
	glTranslatef(0.1, 0.0, 0.0);
	glRotatef((GLfloat)RfingerUp, 0.0, 1.0, 0.0);
	glTranslatef(0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.05, 0.05);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();


	//Draw Middle 
	glPushMatrix();
	glTranslatef(0.5, 0.075, 0.075);
	glTranslatef(0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.05, 0.05);
	glutWireCube(1);
	glPopMatrix();
	glTranslatef(0.1, 0.0, 0.0);
	glRotatef((GLfloat)RfingerUp, 0.0, 1.0, 0.0);
	glTranslatef(0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.05, 0.05);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();

	//Draw Ring 
	glPushMatrix();
	glTranslatef(0.5, -0.075, 0.075);
	glTranslatef(0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.05, 0.05);
	glutWireCube(1);
	glPopMatrix();
	glTranslatef(0.1, 0.0, 0.0);
	glRotatef((GLfloat)RfingerUp, 0.0, 1.0, 0.0);
	glTranslatef(0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.05, 0.05);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();


	//Draw Little  
	glPushMatrix();
	glTranslatef(0.5, -0.225, 0.075);
	glTranslatef(0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.05, 0.05);
	glutWireCube(1);
	glPopMatrix();
	glTranslatef(0.1, 0.0, 0.0);
	glRotatef((GLfloat)RfingerUp, 0.0, 1.0, 0.0);
	glTranslatef(0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.05, 0.05);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	//Lshoulder and Lelbow
	glPushMatrix();
	glTranslatef(-1.0, 1.25, 0.0);
	glRotatef(-(GLfloat)shoulder1, 0.0, 0.0, 1.0);
	glRotatef(-(GLfloat)shoulder2, 0.0, 1.0, 0.0);
	glRotatef((GLfloat)shoulder3, 1.0, 0.0, 0.0);
	glTranslatef(-0.5, 0.0, 0.0);
	glPushMatrix();
	glScalef(-1.0, 0.5, 0.2);
	glutWireCube(1.0);
	glPopMatrix();
	glTranslatef(-0.5, 0.0, 0.0);
	glRotatef((GLfloat)elbow, 0.0, 0.0, -1.0);
	glTranslatef(-0.5, 0.0, 0.0);
	glPushMatrix();
	glScalef(1.0, 0.5, 0.2);
	glutWireCube(1.0);
	glPopMatrix();


	//Left fingers 
	//Draw Thumb  
	glPushMatrix();
	glTranslatef(-0.5, 0.225, -0.075);
	glTranslatef(-0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.05, 0.05);
	glutWireCube(1);
	glPopMatrix();
	glTranslatef(-0.1, 0.0, 0.0);
	glRotatef((GLfloat)LThumbUp, 0.0, -1.0, 0.0);
	glTranslatef(-0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.05, 0.05);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();


	//Draw Index 
	glPushMatrix();
	glTranslatef(-0.5, 0.225, 0.075);
	glTranslatef(-0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.05, 0.05);
	glutWireCube(1);
	glPopMatrix();
	glTranslatef(-0.1, 0.0, 0.0);
	glRotatef((GLfloat)LfingerUp, 0.0, -1.0, 0.0);
	glTranslatef(-0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.05, 0.05);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();


	//Draw Middle 
	glPushMatrix();
	glTranslatef(-0.5, 0.075, 0.075);
	glTranslatef(-0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.05, 0.05);
	glutWireCube(1);
	glPopMatrix();
	glTranslatef(-0.1, 0.0, 0.0);
	glRotatef((GLfloat)LfingerUp, 0.0, -1.0, 0.0);
	glTranslatef(-0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.05, 0.05);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();

	//Draw Ring 
	glPushMatrix();
	glTranslatef(-0.5, -0.075, 0.075);
	glTranslatef(-0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.05, 0.05);
	glutWireCube(1);
	glPopMatrix();
	glTranslatef(-0.1, 0.0, 0.0);
	glRotatef((GLfloat)LfingerUp, 0.0, -1.0, 0.0);
	glTranslatef(-0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.05, 0.05);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();


	//Draw Little  
	glPushMatrix();
	glTranslatef(-0.5, -0.225, 0.075);
	glTranslatef(-0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.05, 0.05);
	glutWireCube(1);
	glPopMatrix();
	glTranslatef(-0.1, 0.0, 0.0);
	glRotatef((GLfloat)LfingerUp, 0.0, -1.0, 0.0);
	glTranslatef(-0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.05, 0.05);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	//left femur
	glPushMatrix();
	glTranslatef(-0.5, -1.0, 0.0);
	glRotatef((GLfloat)LFemur, 0.0, 0.0, -1.0);
	glRotatef((GLfloat)LFemur2, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -1.25, 0.0);
	glPushMatrix();
	glScalef(0.5, 1.5, 0.6);
	glutWireCube(1.0);
	glPopMatrix();
	//left tibia 
	glTranslatef(0.0, -0.75, 0.0);
	glRotatef((GLfloat)LTibia, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.75, 0.0);
	glPushMatrix();
	glScalef(0.5, 1.5, 0.6);
	glutWireCube(1.0);
	glPopMatrix();

	//left feet 
	glTranslatef(0.0, -0.75, 0.0);
	glPushMatrix();
	glScalef(0.5, 0.5, 1.5);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();

	//Right femur
	glPushMatrix();
	glTranslatef(0.5, -1.0, 0.0);
	glRotatef((GLfloat)RFemur, 0.0, 0.0, -1.0);
	glRotatef((GLfloat)RFemur2, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -1.25, 0.0);
	glPushMatrix();
	glScalef(0.5, 1.5, 0.6);
	glutWireCube(1.0);
	glPopMatrix();
	//Right tibia 
	glTranslatef(0.0, -0.75, 0.0);
	glRotatef((GLfloat)RTibia, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.75, 0.0);
	glPushMatrix();
	glScalef(0.5, 1.5, 0.6);
	glutWireCube(1.0);
	glPopMatrix();

	//Right feet 
	glTranslatef(0.0, -0.75, 0.0);
	glPushMatrix();
	glScalef(0.5, 0.5, 1.5);
	glutSolidCube(1.0);
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

	case 'q':
		moveForward();
		glutPostRedisplay();

		break;
	case 'Q':
		moveBackward();
		glutPostRedisplay();
		break;

	case 's':
		if (shoulder1 <= 110)
		{
			shoulder1 = (shoulder1 + 5) % 360;
			glutPostRedisplay();
		};
		break;
	case 'S':
		if (shoulder1 >= -120)
		{
			shoulder1 = (shoulder1 - 5) % 360;
			glutPostRedisplay();
		};
		break;

	case 'd':
		if (shoulder2 <= 110)
		{
			shoulder2 = (shoulder2 + 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'D':
		if (shoulder2 >= -30)
		{
			shoulder2 = (shoulder2 - 5) % 360;
			glutPostRedisplay();
		}
		break;

	case 'r':
		if (shoulder3 <= 180)
		{
			shoulder3 = (shoulder3 + 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'R':
		if (shoulder3 >= 0)
		{
			shoulder3 = (shoulder3 - 5) % 360;
			glutPostRedisplay();
		}
		break;

	case 'e': if (elbow == 120) { break; }
			  elbow = (elbow + 5) % 360;
			  glutPostRedisplay();
			  break;
	case 'E': if (elbow == 0) { break; }
			  elbow = (elbow - 5) % 360;
			  glutPostRedisplay();
			  break;

	case 'f': if (RThumbUp == 0) { break; }
			  RThumbUp = (RThumbUp + 5) % 360;
			  glutPostRedisplay();
			  break;
	case 'F': if (RThumbUp == -65) { break; }
			  RThumbUp = (RThumbUp - 5) % 360;
			  glutPostRedisplay();
			  break;

	case 'z': if (RfingerUp == 90) { break; }
			  RfingerUp = (RfingerUp + 5) % 360;
			  glutPostRedisplay();
			  break;
	case 'Z': if (RfingerUp == 0) { break; }
			  RfingerUp = (RfingerUp - 5) % 360;
			  glutPostRedisplay();
			  break;

	case 'g': if (LThumbUp == 0) { break; }
			  LThumbUp = (LThumbUp + 5) % 360;
			  glutPostRedisplay();
			  break;
	case 'G': if (LThumbUp == -65) { break; }
			  LThumbUp = (LThumbUp - 5) % 360;
			  glutPostRedisplay();
			  break;

	case 'x': if (LfingerUp == 90) { break; }
			  LfingerUp = (LfingerUp + 5) % 360;
			  glutPostRedisplay();
			  break;
	case 'X': if (LfingerUp == 0) { break; }
			  LfingerUp = (LfingerUp - 5) % 360;
			  glutPostRedisplay();
			  break;

	case 'h':
		if (RFemur < 15)
		{
			RFemur = (RFemur + 5) % 360;
			glutPostRedisplay();
		};
		break;
	case 'H':
		if (RFemur > -75)
		{
			RFemur = (RFemur - 5) % 360;
			glutPostRedisplay();
		};
		break;

	case 'y':
		if (RFemur2 < 90)
		{
			RFemur2 = (RFemur2 + 5) % 360;
			glutPostRedisplay();
		};
		break;
	case 'Y':
		if (RFemur2 > -45)
		{
			RFemur2 = (RFemur2 - 5) % 360;
			glutPostRedisplay();
		};
		break;

	case 'u':
		if (RTibia < 0)
		{
			RTibia = (RTibia + 5) % 360;
			glutPostRedisplay();
		};
		break;
	case 'U':
		if (RTibia > -75)
		{
			RTibia = (RTibia - 5) % 360;
			glutPostRedisplay();
		};
		break;

	case 'a':
		if (LFemur > -15)
		{
			LFemur = (LFemur - 5) % 360;
			glutPostRedisplay();
		};
		break;
	case 'A':
		if (LFemur < 75)
		{
			LFemur = (LFemur + 5) % 360;
			glutPostRedisplay();
		};
		break;

	case 'o':
		if (LFemur2 < 90)
		{
			LFemur2 = (LFemur2 + 5) % 360;
			glutPostRedisplay();
		};
		break;
	case 'O':
		if (LFemur2 > -45)
		{
			LFemur2 = (LFemur2 - 5) % 360;
			glutPostRedisplay();
		};
		break;

	case 'w':
		if (LTibia < 0)
		{
			LTibia = (LTibia + 5) % 360;
			glutPostRedisplay();
		};
		break;
	case 'W':
		if (LTibia > -75)
		{
			LTibia = (LTibia - 5) % 360;
			glutPostRedisplay();
		};
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Task 2");
	init();
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}
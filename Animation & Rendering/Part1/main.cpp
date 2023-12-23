#include <GL/glut.h>
#include "imageloader.h"
#include "glm.h"
#include <iostream> 
#include <math.h>
static int shoulderlz = -75, shoulderrz = 75, elbow = 0, fingerBase = 0, fingerUp = 0,
            finger2Base = 0, finger2Up, finger3Base , finger3Up, finger4Base, finger4Up,
            finger5Base, finger5Up, shoulderlx, shoulderrx,
            fingerBase2, fingerUp2, finger2Base2, finger2Up2, finger3Base2, finger3Up2,
            finger4Base2, finger4Up2, finger5Base2, finger5Up2,
            body, elbow2, legx, legz, legx2, legz2, knee, knee2, ankle, ankle2, elbowx, elbowx2;
double elevation;
double z=-9;
static int ball;
static int elbowr,elbowl;
double eye[] = { 0, 0, 10 };
double center[] = { 0, 0, 1 };
double up[] = { 0, 1, 0 };
double normal_ax[] = {1, 0, 0};
double course[] = {0, 0, 0}; 
int limit, limit2;
static float theta = 3*M_PI /180;
float step = 0.1;
void crossProduct(double a[], double b[], double c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}
void normalize(double a[])
{
	double norm;
	norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	norm = sqrt(norm);
	a[0] /= norm;
	a[1] /= norm;
	a[2] /= norm;
}
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

	temp[0] += (1 - cos(theta))*(a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
	temp[1] += (1 - cos(theta))*(a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
	temp[2] += (1 - cos(theta))*(a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

	temp[0] += cos(theta)*p[0];
	temp[1] += cos(theta)*p[1];
	temp[2] += cos(theta)*p[2];

	p[0] = temp[0];
	p[1] = temp[1];
	p[2] = temp[2];

}
void Left()
{
	// implement camera rotation arround vertical window screen axis to the left
	// used by mouse and left arrow
	if(limit >= -30)
	{
		rotatePoint(up, -theta, eye);
		limit--;
	}
}

void Right()
{
	// implement camera rotation arround vertical window screen axis to the right
	// used by mouse and right arrow
	if(limit <= 30){
		rotatePoint(up, theta, eye);
		limit++;
	}
}

void Up()
{
	// implement camera rotation arround horizontal window screen axis +ve
	// used by up arrow
	if(limit2 <= 27)
	{
		crossProduct(eye , up, normal_ax);
		normalize(normal_ax);
		rotatePoint(normal_ax, theta, eye);
		limit2++;
	}
}

void Down()
{	
	// implement camera rotation arround horizontal window screen axis 
	// used by down arrow
	if(limit2 >= -27)
	{
		crossProduct(up , eye, normal_ax);
		normalize(normal_ax);
		rotatePoint(normal_ax, theta, eye);
		limit2--;
	}
}
void set_direc(double a[], double b[], double c[])
{
	c[0] = a[0] - b[0];
	c[1] = a[1] - b[1];
	c[2] = a[2] - b[2];
}
void moveForward()
{
	set_direc(center, eye, course);
	eye[0] += course[0] * step;
	eye[1] += course[1] * step;
	eye[2] += course[2] * step;

	center[0] += course[0] * step;
	center[1] += course[1] * step;
	center[2] += course[2] * step;
}

void moveBack()
{
	set_direc(center, eye, course);
	eye[0] -= course[0] * step;
	eye[1] -= course[1] * step;
	eye[2] -= course[2] * step;

	center[0] -= course[0] * step;
	center[1] -= course[1] * step;
	center[2] -= course[2] * step;
}
void keyboard2(unsigned char key, int x, int y)
{
	// List all youe keyboard keys from assignment two her for body movement
	switch (key)
	{
        case 'x':
        body = (body + 5);
        glutPostRedisplay();
        break;
        case 'X':
        body = (body - 5);
        glutPostRedisplay();
        break;
        case 'A':
        if(shoulderlx > - 10){
        shoulderlx = (shoulderlx - 5);
        shoulderrx = (shoulderrx + 5);
        glutPostRedisplay();}
        break;
        case 'a':
        if(shoulderlx < 160){
        shoulderlx = (shoulderlx + 5);
        shoulderrx = (shoulderrx - 5);
        std::cout<<shoulderlx<<std::endl;
        glutPostRedisplay();}
        break;
        case 's':
        if(shoulderlz > -175){
        shoulderlz = (shoulderlz - 5);
        shoulderrz = (shoulderrz + 5);
        std::cout<<shoulderlz<<std::endl;
        glutPostRedisplay();}
        break;
        case 'S':
        if(shoulderlz < 30){
        shoulderlz = (shoulderlz + 5);
        shoulderrz = (shoulderrz - 5);
        std::cout<<shoulderlz<<std::endl;
        glutPostRedisplay();}
        break;
        case 'e':
        if(elbow < 145){
        elbow = (elbow + 5);
        elbow2 = (elbow2 - 5);
        glutPostRedisplay();}
        break;
        case 'E':
        if(elbow > 0){
        elbow = (elbow - 5);
        elbow2 = (elbow2 + 5);
        glutPostRedisplay();}
        break;
        
        case 'g':
        if(fingerUp >  -90){
        fingerUp = (fingerUp - 5);
        finger2Up = (finger2Up - 5);
        finger3Up = (finger3Up - 5);
        finger4Up = (finger4Up - 5);
        fingerUp2 = (fingerUp2 + 5);
        finger2Up2 = (finger2Up2 + 5);
        finger3Up2 = (finger3Up2 + 5);
        finger4Up2 = (finger4Up2 + 5);
        glutPostRedisplay();}
        if(finger5Up < 90 ){
        finger5Up = (finger5Up + 5);
        finger5Up2 = (finger5Up2 - 5);
        glutPostRedisplay();}
        break;
        case 'G':
        if(fingerUp < 0){
        fingerUp = (fingerUp + 5);
        finger2Up = (finger2Up + 5);
        finger3Up = (finger3Up + 5);
        finger4Up = (finger4Up + 5);
        fingerUp2 = (fingerUp2 - 5);
        finger2Up2 = (finger2Up2 - 5);
        finger3Up2 = (finger3Up2 - 5);
        finger4Up2 = (finger4Up2 - 5);
        glutPostRedisplay();}
        if(finger5Up > 0){
        finger5Up = (finger5Up - 5);
        finger5Up2 = (finger5Up2 + 5);
        glutPostRedisplay();}
        break;
        case 't':
        if(legx < 50){
            legx = (legx + 5);
            glutPostRedisplay();}
            break;
        case 'T':
        if(legx > -90){
            legx = (legx - 5);
        glutPostRedisplay();}
        break;
        case 'y':
        if(legx2 < 50){
            legx2 = (legx2 + 5);
            glutPostRedisplay();}
            break;
        case 'Y':
        if(legx2 > -90){
            legx2 = (legx2 - 5);
        glutPostRedisplay();}
        break;
        case 'u':
        if(legz2 > -75){
        legz2 = (legz2 - 5);
        glutPostRedisplay();}
        break;
        case 'U':
        if(legz2 < 0){
            legz2 = (legz2 + 5) %360;
            glutPostRedisplay();}
        break;
        case 'i':
        if(legz < 75){
        legz = (legz + 5);
        glutPostRedisplay();}
        break;
        case 'I':
        if(legz > 0){
            legz = (legz - 5) %360;
            glutPostRedisplay();}
        break;
        case 'h':
        if(knee < 110){
            knee = (knee + 5 );
            glutPostRedisplay();}
        break;
        case 'H':
        if(knee > 0){
        knee = (knee - 5);
        glutPostRedisplay();}
        break;
        case 'j':
        if(knee2 < 110){
            knee2 = (knee2 + 5 );
            glutPostRedisplay();}
        break;
        case 'J':
        if(knee2 > 0){
        knee2 = (knee2 - 5);
        glutPostRedisplay();}
        break;
        case 'q':
        if(elbowx > -90){
        elbowx = elbowx - 5;
        elbowx2 = elbowx2 - 5;
        glutPostRedisplay();}
        break;
        case 'Q':
        if(elbowx < 90){
        elbowx = elbowx + 5;
        elbowx2 = elbowx2 + 5;
        std::cout<<elbowx<<std::endl;
        glutPostRedisplay();}
        break;
        case 'f':
            moveForward();
            glutPostRedisplay();
            break;
        case 'b':
            moveBack();
            glutPostRedisplay();
            break;
        default:
            break;
    }
}



GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */
double XX=1.06,YY=3.77,ZZ=-0.02;
GLMmodel* pmodel;
int s=2;

//This function drawmodel1() takes the objects path to display them.

void drawmodel1( char* name)
{
	
	pmodel = glmReadOBJ(name);
	if (!pmodel) exit(0);
	glmUnitize(pmodel);
	glmFacetNormals(pmodel);
	glmVertexNormals(pmodel, 90.0);
	glmScale(pmodel, .15);

	glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);
}

void robot() {
  
  glPushMatrix();
  glTranslatef(0.0, elevation, z);
  glRotatef(angle2, 1.0, 0.0, 0.0);
  glRotatef(angle, 0.0, 1.0, 0.0);
  glRotatef ((GLfloat) body, 0.0, 1.0, 0.0);
  glPushMatrix();
  glScalef(1.5, 2.5, 0.5);
  glutWireCube(1.0);
  glPopMatrix();

  //LEFT ARM:
  glPushMatrix();

  //SHOULDER
  glTranslatef(0.85, 1.1, 0.0);
  glRotatef ((GLfloat) shoulderlz, 0.0, 0.0, 1.0);
  glRotatef ((GLfloat) shoulderlx, 0.0, -1.0, 0.0);
  //glRotatef ((GLfloat) shou, 0.0, -1.0, 0.0);
  glRotatef((GLfloat) elbowx, 1.0, 0.0, 0.0);
  glTranslatef(0.5, 0.0, 0.0);
  glPushMatrix();
  glScalef(1.0, 0.3, 0.5);
  glutWireCube(1.0);
  glPopMatrix();

  //ELBOW
  glTranslatef (0.5 , 0.0 , 0.0);
  glRotatef ((GLfloat) elbow, 0.0, -1.0, 0.0);
  //glRotatef((GLfloat) elbowx, 1.0, 0.0, 0.0);
  glTranslatef (0.5, 0.0, 0.0);
  glPushMatrix();
  glScalef (1.0, 0.3, 0.5);
  //glColor3f(1, 0.5, 0.2);
  glutWireCube (1.0);
  glPopMatrix();
  glPushMatrix();

  //Draw finger flang 1 
  glTranslatef(0.5, 0.1, 0.075);
  glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
  glTranslatef(0.075, 0.0, 0.0);
  glPushMatrix();
  glScalef(0.15, 0.05, 0.05);
  // glColor3f(0.2, 0.4, 0.8);
  glutWireCube(1);
  glPopMatrix();
  //Draw finger flang 1 
  glTranslatef(0.075, 0.0, 0.0);
  glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
  glTranslatef(0.075, 0.0, 0.0);
  glPushMatrix();
  glScalef(0.15, 0.05, 0.05);
  glutWireCube(1);
  glPopMatrix();
  glPopMatrix();
  glPushMatrix();
  //Draw finger flang 2 
  glTranslatef(0.5, 0.1, 0.2);
  glRotatef((GLfloat)finger2Base, 0.0, 0.0, 1.0);
  glTranslatef(0.075, 0.0, 0.0);
  glPushMatrix();
  glScalef(0.15, 0.05, 0.05);
  // glColor3f(0.2, 0.4, 0.8);
  glutWireCube(1);
  glPopMatrix();
  //Draw finger flang 2 
  glTranslatef(0.075, 0.0, 0.0);
  glRotatef((GLfloat)finger2Up, 0.0, 0.0, 1.0);
  glTranslatef(0.075, 0.0, 0.0);
  glPushMatrix();
  glScalef(0.15, 0.05, 0.05);
  glutWireCube(1);
  glPopMatrix();
  glPopMatrix();
  glPushMatrix();
  //Draw finger flang 3 
  glTranslatef(0.5, 0.1, -0.2);
  glRotatef((GLfloat)finger3Base, 0.0, 0.0, 1.0);
  glTranslatef(0.075, 0.0, 0.0);
  glPushMatrix();
  glScalef(0.15, 0.05, 0.05);
  // glColor3f(0.2, 0.4, 0.8);
  glutWireCube(1);
  glPopMatrix();
  //Draw finger flang 3 
  glTranslatef(0.075, 0.0, 0.0);
  glRotatef((GLfloat)finger3Up, 0.0, 0.0, 1.0);
  glTranslatef(0.075, 0.0, 0.0);
  glPushMatrix();
  glScalef(0.15, 0.05, 0.05);
  glutWireCube(1);
  glPopMatrix();
  glPopMatrix();
  glPushMatrix();
  //Draw finger flang 4 
  glTranslatef(0.5, 0.1, -0.075);
  glRotatef((GLfloat)finger4Base, 0.0, 0.0, 1.0);
  glTranslatef(0.075, 0.0, 0.0);
  glPushMatrix();
  glScalef(0.15, 0.05, 0.05);
  // glColor3f(0.2, 0.4, 0.8);
  glutWireCube(1);
  glPopMatrix();
  //Draw finger flang 4 
  glTranslatef(0.075, 0.0, 0.0);
  glRotatef((GLfloat)finger4Up, 0.0, 0.0, 1.0);
  glTranslatef(0.075, 0.0, 0.0);
  glPushMatrix();
  glScalef(0.15, 0.05, 0.05);
  glutWireCube(1);
  glPopMatrix();
  glPopMatrix();
  glPushMatrix();
  //Draw finger flang 5 
  glTranslatef(0.5, -0.1, 0.125);
  glRotatef((GLfloat)finger5Base, 0.0, 0.0, 1.0);
  glTranslatef(0.075, 0.0, 0.0);
  glPushMatrix();
  glScalef(0.15, 0.05, 0.05);
  // glColor3f(0.2, 0.4, 0.8);
  glutWireCube(1);
  glPopMatrix();
  //Draw finger flang 5 
  glTranslatef(0.075, 0.0, 0.0);
  glRotatef((GLfloat)finger5Up, 0.0, 0.0, 1.0);
  glTranslatef(0.075, 0.0, 0.0);
  glPushMatrix();
  glScalef(0.15, 0.05, 0.05);
  glutWireCube(1);
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();




  //RIGHT ARM:
  glPushMatrix();

  //SHOULDER
  glTranslatef(-0.85, 1.1, 0.0);
  glRotatef ((GLfloat) shoulderrz, 0.0, 0.0, 1.0);
  glRotatef((GLfloat) shoulderrx, 0.0, -1.0, 0.0);
  glRotatef((GLfloat) elbowx2, 1.0, 0.0, 0.0);
  glTranslatef(-0.5, 0.0, 0.0);
  glPushMatrix();
  glScalef(1.0, 0.3, 0.5);
  glutWireCube(1.0);
  glPopMatrix();

  //ELBOW
  glTranslatef (-0.5 , 0.0 , 0.0);
  glRotatef ((GLfloat) elbow2, 0.0, -1.0, 0.0);
  //glRotatef((GLfloat) elbowx2, 1.0, 0.0, 0.0);
  glTranslatef (-0.5, 0.0, 0.0);
  glPushMatrix();
  glScalef (1.0, 0.3, 0.5);
  //glColor3f(1, 0.5, 0.2);
  glutWireCube (1.0);
  glPopMatrix();
  glPushMatrix();

  //Draw finger flang 1 
  glTranslatef(-0.5, 0.1, 0.075);
  glRotatef((GLfloat)fingerBase2, 0.0, 0.0, 1.0);
  glTranslatef(-0.075, 0.0, 0.0);
  glPushMatrix();
  glScalef(0.15, 0.05, 0.05);
  // glColor3f(0.2, 0.4, 0.8);
  glutWireCube(1);
  glPopMatrix();
  //Draw finger flang 1 
  glTranslatef(-0.075, 0.0, 0.0);
  glRotatef((GLfloat)fingerUp2, 0.0, 0.0, 1.0);
  glTranslatef(-0.075, 0.0, 0.0);
  glPushMatrix();
  glScalef(0.15, 0.05, 0.05);
  glutWireCube(1);
  glPopMatrix();
  glPopMatrix();
  glPushMatrix();
  //Draw finger flang 2 
  glTranslatef(-0.5, 0.1, 0.2);
  glRotatef((GLfloat)finger2Base2, 0.0, 0.0, 1.0);
  glTranslatef(-0.075, 0.0, 0.0);
  glPushMatrix();
  glScalef(0.15, 0.05, 0.05);
  // glColor3f(0.2, 0.4, 0.8);
  glutWireCube(1);
  glPopMatrix();
  //Draw finger flang 2 
  glTranslatef(-0.075, 0.0, 0.0);
  glRotatef((GLfloat)finger2Up2, 0.0, 0.0, 1.0);
  glTranslatef(-0.075, 0.0, 0.0);
  glPushMatrix();
  glScalef(0.15, 0.05, 0.05);
  glutWireCube(1);
  glPopMatrix();
  glPopMatrix();
  glPushMatrix();
  //Draw finger flang 3 
  glTranslatef(-0.5, 0.1, -0.2);
  glRotatef((GLfloat)finger3Base2, 0.0, 0.0, 1.0);
  glTranslatef(-0.075, 0.0, 0.0);
  glPushMatrix();
  glScalef(0.15, 0.05, 0.05);
  // glColor3f(0.2, 0.4, 0.8);
  glutWireCube(1);
  glPopMatrix();
  //Draw finger flang 3 
  glTranslatef(-0.075, 0.0, 0.0);
  glRotatef((GLfloat)finger3Up2, 0.0, 0.0, 1.0);
  glTranslatef(-0.075, 0.0, 0.0);
  glPushMatrix();
  glScalef(0.15, 0.05, 0.05);
  glutWireCube(1);
  glPopMatrix();
  glPopMatrix();
  glPushMatrix();
  //Draw finger flang 4 
  glTranslatef(-0.5, 0.1, -0.075);
  glRotatef((GLfloat)finger4Base2, 0.0, 0.0, 1.0);
  glTranslatef(-0.075, 0.0, 0.0);
  glPushMatrix();
  glScalef(0.15, 0.05, 0.05);
  // glColor3f(0.2, 0.4, 0.8);
  glutWireCube(1);
  glPopMatrix();
  //Draw finger flang 4 
  glTranslatef(-0.075, 0.0, 0.0);
  glRotatef((GLfloat)finger4Up2, 0.0, 0.0, 1.0);
  glTranslatef(-0.075, 0.0, 0.0);
  glPushMatrix();
  glScalef(0.15, 0.05, 0.05);
  glutWireCube(1);
  glPopMatrix();
  glPopMatrix();
  glPushMatrix();
  //Draw finger flang 5 
  glTranslatef(-0.5, -0.1, 0.125);
  glRotatef((GLfloat)finger5Base2, 0.0, 0.0, 1.0);
  glTranslatef(-0.075, 0.0, 0.0);
  glPushMatrix();
  glScalef(0.15, 0.05, 0.05);
  // glColor3f(0.2, 0.4, 0.8);
  glutWireCube(1);
  glPopMatrix();
  //Draw finger flang 5 
  glTranslatef(-0.075, 0.0, 0.0);
  glRotatef((GLfloat)finger5Up2, 0.0, 0.0, 1.0);
  glTranslatef(-0.075, 0.0, 0.0);
  glPushMatrix();
  glScalef(0.15, 0.05, 0.05);
  glutWireCube(1);
  glPopMatrix();
  
  glPopMatrix();

  glPushMatrix();
   //glRotatef((GLfloat) ball, 0.0, -1.0, 0.0);
   glTranslatef(-0.5, -0.5, -0.5);	
   
	glScalef(s,s,s);	
   drawmodel1("objects/soccerball.obj");		
	glPopMatrix();
  glPopMatrix();

  


  //LEFT LEG:
  glPushMatrix();

  //LEG
  glTranslatef(0.5, -1.35, 0.0);
  glRotatef((GLfloat) legx, 1.0, 0.0, 0.0);
  glRotatef((GLfloat) legz, 0.0, 0.0, 1.0);
  glTranslatef(0.0, -0.5, 0.0);
  glPushMatrix();
  glScalef(0.5, 1, 0.5);
  glutWireCube(1.0);
  glPopMatrix();

  //KNEE
  glTranslatef(0.0, -0.5, 0.0);
  glRotatef((GLfloat) knee, 1.0, 0.0, 0.0);
  glTranslatef(0.0, -0.5, 0.0);
  glPushMatrix();
  glScalef(0.5, 1.0, 0.5);
  glutWireCube(1.0);
  glPopMatrix();

  //ANKLE
  glTranslatef(0.0, -0.5, 0.0);
  glRotatef((GLfloat) ankle, 1.0, 0.0, 0.0);
  glTranslatef(0.0, -0.1, 0.25);
  glPushMatrix();
  glScalef(0.5, 0.2, 1.0);
  glutWireCube(1.0);
  glPopMatrix();
  glPopMatrix();



  //RIGHT LEG:
  glPushMatrix();

  //LEG
  glTranslatef(-0.5, -1.35, 0.0);
  glRotatef((GLfloat) legx2, 1.0, 0.0, 0.0);
  glRotatef((GLfloat) legz2, 0.0, 0.0, 1.0);
  glTranslatef(0.0, -0.5, 0.0);
  glPushMatrix();
  glScalef(0.5, 1, 0.5);
  glutWireCube(1.0);
  glPopMatrix();

  //KNEE
  glTranslatef(0.0, -0.5, 0.0);
  glRotatef((GLfloat) knee2, 1.0, 0.0, 0.0);
  glTranslatef(0.0, -0.5, 0.0);
  glPushMatrix();
  glScalef(0.5, 1.0, 0.5);
  glutWireCube(1.0);
  glPopMatrix();

  //ANKLE
  glTranslatef(0.0, -0.5, 0.0);
  glRotatef((GLfloat) ankle2, 1.0, 0.0, 0.0);
  glTranslatef(0.0, -0.1, 0.25);
  glPushMatrix();
  glScalef(0.5, 0.2, 1.0);
  glutWireCube(1.0);
  glPopMatrix();
  glPopMatrix();


  //HEAD:
  glPushMatrix();
  glTranslatef(0.0, 1.6, 0.0);
  glutWireSphere(0.35, 16, 16);
  glPopMatrix();

  glPopMatrix();
}

int moving, startx, starty;
int flage=0;
int flage2=0;
int s2=2;

int windowWidth = 1024;
int windowHeight = 768;
float aspect = float(windowWidth) / float(windowHeight);
Image* image;
float VRot =0.0;
// RGBA
GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat light_diffuse[] = { 0.5, 0.5, 0.5,1.0 };
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0 };
// x , y, z, w
GLfloat light_position[] = {5.5,5.0, 2.0, 1.0 };
GLfloat lightPos1[] = {-0.5,-5.0,-2.0, 1.0 };
// Material Properties
GLfloat mat_amb_diff[] = {0.643, 0.753, 0.934, 1.0 };
GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat shininess[] = {100.0 };  
//left teapot specular
GLfloat teapotl_diff[] = { 0.0,0.0, 1.0, 1.0 };
GLfloat teapotl_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat teapotl_shininess[] = {10.0 };  
//middle teapot diffuse
GLfloat teapotm_diff[] = { 1.0, 0, 0.0, 1.0 };
GLfloat teapotm_specular[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat teapotm_shininess[] = {1.0 };  
//right teapot glosy
GLfloat teapotr_diff[] = { 1.0, .0, 0.0, 1.0 };
GLfloat teapotr_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat teapotr_shininess[] = {1000.0 };  
//cube
GLfloat cube_diff[] = {1.0,0.0, 0.0, 1.0 };
GLfloat cube_specular[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat cube_shininess[] = {10.0 }; 

//This function loadTexture() take the image data and maps it to the texture generated and returns the texture id.
GLuint loadTexture(Image* image) {
      GLuint textureId;
      glGenTextures(1, &textureId); //Make room for our texture
      glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
      //Map the image to the texture
      glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                               0,                            //0 for now
                               GL_RGB,                       //Format OpenGL uses for image
                               image->width, image->height,  //Width and height
                               0,                            //The border of the image
                               GL_RGB, //GL_RGB, because pixels are stored in RGB format
                               GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                                                 //as unsigned numbers
                               image->pixels);               //The actual pixel data
      return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture

//Initializes 3D rendering
//This function loads the image data and adjusts the lightning of the room.

void initRendering() {
   if (!image) {
		image = loadBMP("data/floor.bmp");
   if (!image) exit(0);
	}
   _textureId = loadTexture(image);
   delete image;
   // Turn on the power
   glEnable(GL_LIGHTING);
   // Flip light switch
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);
   // assign light parameters
   glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
   glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
   glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
   // Material Properties         
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
   GLfloat lightColor1[] = {1.0f, 1.0f,  1.0f, 1.0f };
   glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
   glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor1);
   glEnable(GL_NORMALIZE);
   //Enable smooth shading
   glShadeModel(GL_SMOOTH);
   // Enable Depth buffer
   glEnable(GL_DEPTH_TEST);
}

void init(void)
{
   glMatrixMode(GL_PROJECTION);
	gluPerspective(60.0, aspect, 1.0, 60.0);
}

//By calling the loadTexture() function, it takes the texture id to draw the room floor and walls and puts the textures on them.

void floorTexture()
{
   //floortextureId
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
   
   glBindTexture(GL_TEXTURE_2D, loadTexture(loadBMP("data/floor5.bmp")));
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   //glBindTexture(GL_TEXTURE_2D, loadTexture(loadBMP("data/floor3.bmp")));
   glBegin(GL_QUADS);      
	glNormal3f(0.0,-1.0,0.0);
	glTexCoord2f(0.0f, 0.0f);
   glVertex3f(-10,10,10);
   glTexCoord2f(5.0f,  0.0f);
   glVertex3f(10,10,10);
   glTexCoord2f(5.0f,  20.0f);
   glVertex3f(10,10,-10);
   glTexCoord2f(0.0f, 20.0f);
   glVertex3f(-10,10,-10);
   glEnd();

   glBegin(GL_QUADS);      
	glNormal3f(0.0,0.0,-1.0);
	glTexCoord2f(0.0f, 0.0f);
   glVertex3f(10,10,-10);
   glTexCoord2f(5.0f,  0.0f);
   glVertex3f(10,-3.35,-10);
   glTexCoord2f(5.0f,  20.0f);
   glVertex3f(-10,-3.35,-10);
   glTexCoord2f(0.0f, 20.0f);
   glVertex3f(-10,10,-10);
   glEnd();

   glBegin(GL_QUADS);       
	glNormal3f(-1.0,0.0,0.0);
	glTexCoord2f(0.0f, 0.0f);
   glVertex3f(10,-3.35,10);
   glTexCoord2f(5.0f,  0.0f);
   glVertex3f(10,10,10);
   glTexCoord2f(5.0f,  20.0f);
   glVertex3f(10,10,-10);
   glTexCoord2f(0.0f, 20.0f);
   glVertex3f(10,-3.35,-10);
   glEnd();

   glBegin(GL_QUADS);       
	glNormal3f(-1.0,0.0,0.0);
	glTexCoord2f(0.0f, 0.0f);
   glVertex3f(-10,-3.35,10);
   glTexCoord2f(5.0f,  0.0f);
   glVertex3f(-10,10,10);
   glTexCoord2f(5.0f,  20.0f);
   glVertex3f(-10,10,-10);
   glTexCoord2f(0.0f, 20.0f);
   glVertex3f(-10,-3.35,-10);
   glEnd();

   glBindTexture(GL_TEXTURE_2D, _textureId);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   glBegin(GL_QUADS);      
	glNormal3f(0.0,-1.0,0.0);
	glTexCoord2f(0.0f, 0.0f);
   glVertex3f(-10,-3.35,10);
   glTexCoord2f(5.0f,  0.0f);
   glVertex3f(10,-3.35,10);
   glTexCoord2f(5.0f,  20.0f);
   glVertex3f(10,-3.35,-10);
   glTexCoord2f(0.0f, 20.0f);
   glVertex3f(-10,-3.35,-10);
   glEnd();
	glDisable(GL_TEXTURE_2D);
   glPopMatrix();

}


//In this function we adjust the objects locations in the room and calls the robot function to display it.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_FLAT);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
   glPushMatrix();
   glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glPopMatrix();
   //materials properties
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glPushMatrix();
	glTranslatef(0, 0, -1);
   floorTexture();

   glPushMatrix();

   glPushMatrix();
   glTranslatef(3.1, -0.1, 4.2);
   glRotatef(-90,1,0,0); 
   glRotatef(-90,0,0,1); 
   glScalef(20,20,20);
   drawmodel1("objects/10488_basketball_goal_L3.obj");	
	glPopMatrix();
	
   

   glPushMatrix();
   glTranslatef(-12, -2, -15);	
	glScalef(20,20,20);	
   drawmodel1("objects/flowers.obj");		
	glPopMatrix();

   glPopMatrix();
   
  
   robot();
   glPopMatrix();
   if (flage)
   {s=0;
   glPushMatrix();
            glRotatef((GLfloat) ball, 1.0, 0.0, -1.0);
            glTranslatef(XX, YY, ZZ);	
            
            glScalef(s2,s2,s2);	
            drawmodel1("objects/soccerball.obj");		
            glPopMatrix();
             
            
   }

   if (flage2)
   {s=0;
   glPushMatrix();
            
            glTranslatef(2, -2, 3);	
            
            glScalef(2,2,2);	
            drawmodel1("objects/soccerball.obj");		
            glPopMatrix();
            
            
   }
	glutSwapBuffers();
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
	int xx = x-startx;
	int yy = y-starty;
    if(xx > 3){Left();}
	else if(xx < -3){Right();}
	if(yy > 3){Up();}
	else if(yy < -3){Down();}
    startx = x;
    starty = y;
    glutPostRedisplay();
  }
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT: Left(); break;
	case GLUT_KEY_RIGHT: Right(); break;
	case GLUT_KEY_UP:    Up(); break;
	case GLUT_KEY_DOWN:  Down(); break;
	}
	glutPostRedisplay();
}

//This function screen_menu helps us to change the floor texture we click on the right mouse button

void screen_menu(int value)
{
	switch (value) {
	case 1:
		image = loadBMP("data/floor.bmp");
		break;
	case 2:
		image = loadBMP("data/floor2.bmp");
		break;
	case 4:
		image = loadBMP("data/floor4.bmp");
		break;
	case 5:
		image = loadBMP("data/floor3.bmp");
		break;
   case 6:
		image = loadBMP("data/floor6.bmp");
		break;
	case 7:
		image = loadBMP("data/floor7.bmp");
		break;
	}
	if (!image) exit(0);
   initRendering();
	glutPostRedisplay();
}
int state = 0;
int step_j = 1;
int statez = 1;
int state3=0;

//This function makes the 2nd animation in which the robot throw the basketball in the basketball hoop by pressing "z" key.

void timerica(int)
{  
   body = 45;
   switch (state)
   {  
      case 0:
      {
         if(legx > -60)
         {
            legx -= step_j;
            legx2 -= step_j;
            knee += step_j;
            knee2 += step_j;
            shoulderlx += step_j;
            shoulderrx -= step_j;
            elbow += 2*step_j;
            elbow2 -= 2*step_j;
            if(legx < -15)
               elevation -= 0.01;
         }
         else
            state = 1;
      }break;
      case 1:
      {
         if(legx < -15)
         {
            legx += step_j;
            legx2 += step_j;
            knee -= step_j;
            knee2 -= step_j;
            shoulderlx += step_j;
            shoulderrx -= step_j;
            elevation += 0.03;
         }
         else
            state = 2;
      }break;
      case 2:
      {
         if(legx < 0)
         {
            legx += step_j;
            legx2 += step_j;
            knee -= step_j;
            knee2 -= step_j;
            shoulderlx += step_j;
            shoulderrx -= step_j;
            elbow -= 4*step_j;
            elbow2 += 4*step_j;
            elevation += 0.03;
         }
         else
          {
            state = 3;
          }
      }break;
      case 3:
      {
         if(elevation > 0.025)
         {
            elevation -= 0.025;
            if(ball < 44)
            ball+=4;
            else if(YY>0){
               YY -= 0.7;
               XX += 0.3;
               ZZ += 0.3;}
            flage=1;
            if(elbow > 0)
            {
               elbow -= step_j;
               elbow2 += step_j;
               
            }
            if(shoulderlx > 0)
            {
               shoulderlx -= step_j;
               shoulderrx += step_j; 
            }
         }
         else
            state = 4;
      }
      case 4:
      {
         if(elbow > 0)
         {
            elbow -= step_j;
            elbow2 += step_j;
            
         }
         if(shoulderlx > 0)
         {
            shoulderlx -= step_j;
            shoulderrx += step_j; 
         }
         if (elbow == 0 && shoulderlx == 0)
         {
            state = 5;
            elevation = 0;
         }
      }
   }
   glutPostRedisplay();
   
   if(state == 5)
      state = 0;
   else
      glutTimerFunc(5, timerica, 0);
   
}

//This function makes the 1st animation in which the robot moves along the room.
void timer(int)
{
    
    
    if (z <0)
       { z+=0.1;
         
         
         
         
       
        switch(statez)
        {
        case 1:
               
               legx+=5;
               legx2-=5;
               if (legx >45)
                 statez =-1;
            
            break;
    
        case -1:
               
               legx-=5;
               legx2+=5;
               
               if (legx<-45)

                  statez=1;
            break;
    
        
         }
        glutTimerFunc(1000/60, timer ,0);
        
       }
       
    
    else
    {  
       legx=0;
       legx2=0;
       
       
       
    }
    
   glutPostRedisplay();
   
}

//This fuction makes the 3rd animation in which the robot waves his hand and displays a message by pressing "v" key.
void timer3(int)
{
   glutTimerFunc(1000/60, timer3 ,0);
   glutPostRedisplay();
   body=0;
   s=0;
   s2=0;
   flage2=1;
   switch (state3)
   {
      case 0:
         {
            if(shoulderlx < 155)
               {shoulderlx = (shoulderlx + 5);
                shoulderrx = (shoulderrx - 5);
               }
            if(elbowx < 85){
               elbowx = elbowx + 5;
               elbowx2 = elbowx2 + 5;
               }

            if(shoulderlz > -90){
             shoulderlz = (shoulderlz - 5);
             shoulderrz = (shoulderrz + 5);
            }
            if (shoulderlx==155 && elbowx==85 && shoulderlz==-90)
                state3=1;
         }
         break;

      case 1:
         {  
            if(shoulderlz < -75){
             shoulderlz = (shoulderlz + 5);
             shoulderrz = (shoulderrz - 5);
            }
            else
               state3=2;
         }
         break;
      case 2:
         {
            if(shoulderlz > -140){
             shoulderlz = (shoulderlz - 5);
             shoulderrz = (shoulderrz + 5);
            }
            else
              state3=1;
         }
         break;
      default:
         break;
   }
       
       
    
}
void keyboard(unsigned char key, int x, int y)
{
   keyboard2(key, x, y);
   switch (key)
   {
   case 'z':
      state = 0;
      glutTimerFunc(5, timerica, 0);
      break;
   case 'Z':
      break;
   case 'v':
      glutTimerFunc(1000/60, timer3 ,0);
      glutPostRedisplay();
      break;
   case 'V':
      YY+=0.1;
      glutPostRedisplay();
      break;
   case 'm':
      ZZ+=0.1;
      glutPostRedisplay();
      break;
   case 'M':
      std::cout<<XX<<std::endl;
      std::cout<<YY<<std::endl;
      std::cout<<ZZ<<std::endl;
      break;
   }
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
   
	glutCreateWindow("ROOM");
	initRendering();
	init();
	glutDisplayFunc(display);
   glutCreateMenu(screen_menu);
	glutAddMenuEntry("         Floor1         ", 1);
	glutAddMenuEntry("         Floor2", 2);
	glutAddMenuEntry("         Floor3", 4);
	glutAddMenuEntry("         Floor4", 5);
   glutAddMenuEntry("         Floor5", 6);
	glutAddMenuEntry("         Floor6", 7);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
   glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   glutMotionFunc(motion);
   glutTimerFunc(1000/60, timer ,0);
	glutMainLoop();
	return 0;
}
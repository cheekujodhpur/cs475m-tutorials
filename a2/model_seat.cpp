#include <GL/glut.h>
#include <math.h>
#include<iostream>

using namespace std;

struct Vec {
  double x, y, z; Vec(double x_=0, double y_=0, double z_=0){ x=x_; y=y_; z=z_; } Vec operator+(const Vec &b) const { return Vec(x+b.x,y+b.y,z+b.z); }
  Vec operator-(const Vec &b) const { return Vec(x-b.x,y-b.y,z-b.z); }
  Vec operator*(double b) const { return Vec(x*b,y*b,z*b); } Vec mult(const Vec &b) const { return Vec(x*b.x,y*b.y,z*b.z); }
  Vec& norm(){ return *this = *this * (1/sqrt(x*x+y*y+z*z)); }
  double dot(const Vec &b) const { return x*b.x+y*b.y+z*b.z; } // cross:
  Vec operator%(Vec&b){return Vec(y*b.z-z*b.y,z*b.x-x*b.z,x*b.y-y*b.x);}
};

void drawCylinder(double height, double radius, Vec trans, Vec rot){
    int numMajor = 100;
    int numMinor = 100;

  double majorStep = height / numMajor;
  double minorStep = 2.0 * M_PI / numMinor;
  int i, j;

  glPushMatrix();

  glTranslatef(trans.x, trans.y, trans.z);
  glRotatef(rot.x, 1.0, 0.0, 0.0);
  glRotatef(rot.y, 0.0, 1.0, 0.0);
  glRotatef(rot.z, 0.0, 0.0, 1.0);

  for (i = 0; i < numMajor; ++i) {
      GLfloat z0 = 0.5 * height - i * majorStep;
      GLfloat z1 = z0 - majorStep;

      glBegin(GL_TRIANGLE_STRIP);
      for (j = 0; j <= numMinor; ++j) {
          double a = j * minorStep;
          GLfloat x = radius * cos(a);
          GLfloat y = radius * sin(a);
          glVertex3f(x, y, z0);
          glColor3f(0.0,0.1,0.8);
          glVertex3f(x, y, z1);
          glColor3f(0.0,0.1,0.8);
      }
      glEnd();
  }
  glPopMatrix();
}

void drawTorus(double width, double radius, Vec trans, Vec rot){
  int num = 100;

  double Step = 2.0 * M_PI / num;
  int i, j;

  glPushMatrix();

  glTranslatef(trans.x, trans.y, trans.z);
  glRotatef(rot.x, 1.0, 0.0, 0.0);
  glRotatef(rot.y, 0.0, 1.0, 0.0);
  glRotatef(rot.z, 0.0, 0.0, 1.0);

  for (i = 0; i < num; ++i) {
        double theta = i*Step;

      glBegin(GL_TRIANGLE_STRIP);
      for (j = 0; j <= num; ++j) {
          double phi = j * Step;
          glVertex3f((radius-width*sin(phi))*cos(theta),(radius-width*sin(phi))*sin(theta), width*cos(phi));
          glColor3f(0.8,0.1,0.8);
          glVertex3f((radius-width*sin(phi))*cos(theta+Step),(radius-width*sin(phi))*sin(theta+Step), width*cos(phi));
          glColor3f(0.8,0.1,0.8);
      }
      glEnd();
  }
  glPopMatrix();
}

struct Seat{
    double th, bh; //top height, bottom height
    double tw, bw; //top width, bottom width
    double d; //thickness
    Seat(double th_, double bh_, double tw_, double bw_, double d_):th(th_),bh(bh_),tw(tw_),bw(bw_),d(d_){}
    void drawTop(){
      glBegin(GL_TRIANGLE_STRIP);
      glVertex3f(d,bw,0.0);
      glColor3f(1.0,1.0,1.0);

      glVertex3f(d,tw,th);
      glColor3f(1.0,1.0,1.0);

      glVertex3f(d,bw,-bh);
      glColor3f(1.0,1.0,1.0);
      
      glVertex3f(d,-tw,th);
      glColor3f(1.0,1.0,1.0);
      
      glVertex3f(d,-bw,-bh);
      glColor3f(1.0,1.0,1.0);

      glVertex3f(d,-bw,0.0);
      glColor3f(1.0,1.0,1.0);

      glEnd();
    }
    void drawBottom(){
      glBegin(GL_TRIANGLE_STRIP);
      glVertex3f(-d,bw,0.0);
      glColor3f(1.0,1.0,1.0);

      glVertex3f(-d,tw,th);
      glColor3f(1.0,1.0,1.0);

      glVertex3f(-d,bw,-bh);
      glColor3f(1.0,1.0,1.0);
      
      glVertex3f(-d,-tw,th);
      glColor3f(1.0,1.0,1.0);
      
      glVertex3f(-d,-bw,-bh);
      glColor3f(1.0,1.0,1.0);

      glVertex3f(-d,-bw,0.0);
      glColor3f(1.0,1.0,1.0);

      glEnd();
    }
    void drawSides(){
      glBegin(GL_TRIANGLE_STRIP);

      glVertex3f(d,bw,0.0);
      glColor3f(1.0,1.0,1.0);

      glVertex3f(-d,bw,0.0);
      glColor3f(1.0,1.0,1.0);

      glVertex3f(d,bw,-bh);
      glColor3f(1.0,1.0,1.0);

      glVertex3f(-d,bw,-bh);
      glColor3f(1.0,1.0,1.0);

      glVertex3f(d,-bw,-bh);
      glColor3f(1.0,1.0,1.0);

      glVertex3f(-d,-bw,-bh);
      glColor3f(1.0,1.0,1.0);

      glVertex3f(d,-bw,0.0);
      glColor3f(1.0,1.0,1.0);

      glVertex3f(-d,-bw,0.0);
      glColor3f(1.0,1.0,1.0);

      glVertex3f(d,-tw,th);
      glColor3f(1.0,1.0,1.0);

      glVertex3f(-d,-tw,th);
      glColor3f(1.0,1.0,1.0);

      glVertex3f(d,tw,th);
      glColor3f(1.0,1.0,1.0);

      glVertex3f(-d,tw,th);
      glColor3f(1.0,1.0,1.0);

      glVertex3f(d,bw,0.0);
      glColor3f(1.0,1.0,1.0);

      glEnd();
    }
    void draw(){
        glPushMatrix();
        drawTop();
        drawBottom();
        drawSides();
        glPopMatrix();
    }
};

Vec supremo(0.0,0.0,0.0);
Vec eye(9.0 ,0.0, 0.0);
Vec up(0.0, 0.0, 1.0);

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity(); 
  gluLookAt(eye.x, eye.y, eye.z,  // eye is at (0,0,8)
  0.0, 0.0, 0.0,      // center is at (0,0,0)
  up.x, up.y, up.z);      // up is in positive Y direction

  Seat seat(2.0,4.0,0.5,1.5,0.5);
  seat.draw();
  glPushMatrix();
  glRotatef(-75,0.0,1.0,0.0);
  glTranslatef(-0.7,0.0,2.7);
  drawCylinder(5.0,0.5,Vec(0.0,0.0,0.0),Vec(0.0,0.0,0.0));
  glPopMatrix();

  glutSwapBuffers();
}

//Our function for processing ASCII keys
void processNormalKeys(unsigned char key, int x, int y) {
  switch(key) {
    case 'w':
      supremo.z += 0.05;
      break;
    case 's':
      supremo.z -= 0.05;
      break;
    case 'a':
      supremo.y -= 0.05;
      break;
    case 'd':
      supremo.y += 0.05;
      break;
    case 'q':
      supremo.x += 0.05;
      break;
    case 'e':
      supremo.x -= 0.05;
      break;
    case 'p':
    cout << supremo.x << " " << supremo.y << " " << supremo.z << endl; 
    break;
    case 'v': 
    if(eye.x==0){ 
        eye.x = 9.0; 
        eye.y = 0.0; 
        eye.z = 0.0; 
        up.x = 0.0; 
        up.y = 0.0; 
        up.z = 1.0; } 
    else if(eye.x==9.0){ 
        eye.x = 0.0; 
        eye.z = 9.0; 
        up.x = -1.0; 
        up.z = 0.0; } 
    break; 
    case 'k': 
    if(eye.x==0){ 
        eye.x = 9.0; 
        eye.z = 0.0; 
        eye.y = 0.0; 
        up.x = 0.0; 
        up.y = 0.0; 
        up.z = 1.0; } 
    else if(eye.x=9.0){ 
        eye.y = 9.0; 
        eye.x = 0.0; } 
    break;
  }
  if (key == 27)
  exit(0);

  glutPostRedisplay();
}

void processSpecialKeys(int key, int x, int y) {
  switch(key) {
  }
  //Redraw
  glutPostRedisplay();
}

void init(void)
{
  // Use depth buffering for hidden surface elimination.
  glEnable(GL_DEPTH_TEST);
  // Setup the view of the cube.
  glMatrixMode(GL_PROJECTION);
  //gluPerspective(field of view in degree, aspect ratio, Z near, Z far);
  gluPerspective(80.0, 1.0, 1.0, 20.0);

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(9.0, 0.0, 0.0,  // eye is at (0,0,8)
  0.0, 0.0, 0.0,      // center is at (0,0,0)
  0.0, 0.0, 1.0);      // up is in positive Y direction
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(700,700);
  glutCreateWindow("Assignment 2");
  glutDisplayFunc(display);
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(processSpecialKeys);
  init();
  glutMainLoop();
  return 0;
}

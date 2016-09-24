#include <GL/glut.h>
#include <math.h>
#include<iostream>

using namespace std;

struct Vec {
  double x, y, z; Vec(double x_=0, double y_=0, double z_=0){ x=x_; y=y_; z=z_; } Vec operator+(const Vec &b) const { return Vec(x+b.x,y+b.y,z+b.z); }
  Vec operator-(const Vec &b) const { return Vec(x-b.x,y-b.y,z-b.z); }
  Vec operator*(double b) const { return Vec(x*b,y*b,z*b); }
  Vec mult(const Vec &b) const { return Vec(x*b.x,y*b.y,z*b.z); }
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

Vec supremo(0.0,0.0,0.0);

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawCylinder(3.2, 0.2, Vec(0.0, 0.5, 0.0), Vec(-15.0, 0.0, 0.0));
  drawCylinder(4.5, 0.15, Vec(0.0, -1.9, -0.3), Vec(60.0, 0.0, 0.0));
  drawCylinder(4.5, 0.15, Vec(0.0,-1.55, 1.15) , Vec(85.0, 0.0, 0.0));
  drawCylinder(4.5, 0.15, supremo, Vec(85.0, 0.0, 0.0));

  glutSwapBuffers();
}

void processSpecialKeys(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_LEFT :
    supremo.y -= 0.05;
    break;
    case GLUT_KEY_RIGHT :
    supremo.y += 0.05;
    break;
    case GLUT_KEY_UP :
    supremo.z += 0.05;
    break;
    case GLUT_KEY_DOWN :
    supremo.z -= 0.05;
    break;
    case GLUT_KEY_PAGE_UP:
    cout << supremo.x << " " << supremo.y << " " << supremo.z << endl; 
    break;
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
  glutSpecialFunc(processSpecialKeys);
  init();
  glutMainLoop();
  return 0;
}

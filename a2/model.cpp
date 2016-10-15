#include <math.h>
#include<iostream>
#include "functions.hpp"

using namespace std;

// Texture numbers
GLuint woodenTexture;
GLuint wheelTexture;
GLuint wallTexture;
GLuint roofTexture;
GLuint paintTexture;
GLuint frameTexture;

//lights
bool roomLights = true;
bool headLights = false;

//for debugging
Vec supremo(0.0,0.0,0.0);
Vec eye(9.0 ,0.0, 0.0);
Vec up(0.0, 0.0, 1.0);
Vec lookat(0.0,0.0,0.0);

//back wheel angle parameter
double theta = 0;
//front wheel angle parameter
double phi = 0;
//front handle angle parameter
double theta2 = 0;
//pedal angle paramter
double phi2 = 30;

double fcrot=0;
double fctrax=0;
double fctray=0;

int cameraMode = 0;

double ln_axle = 9.05;

void update_params(float delta_phi2, float theta2)
{
    theta += 1.5 * delta_phi2 * (180.0/M_PI);
    float bw = 2.8725 * delta_phi2;
    float fw = (bw-ln_axle)*cos(theta2*(M_PI/180.0)) + sqrt(ln_axle*ln_axle + bw*(2*ln_axle-bw)*sin(theta2*(M_PI/180.0)*sin(theta2*(M_PI/180.0))));
    phi += (fw*180.0)/(1.28*M_PI);
    float rotation = atan2(bw*sin(theta2*(M_PI/180.0)), ln_axle +  bw*cos(theta2*(M_PI/180.0)));
    fcrot = (180/M_PI)*(angleSum(((M_PI/180)*fcrot),rotation));
    fctrax += bw*sin(theta2*(M_PI/180.0))*cos(fcrot*(M_PI/180.0))+bw*cos(theta2*(M_PI/180.0))*sin(fcrot*(M_PI/180.0)); 
    fctray -= bw*cos(theta2*(M_PI/180.0))*cos(fcrot*(M_PI/180.0))+bw*sin(theta2*(M_PI/180.0))*sin(fcrot*(M_PI/180.0));
    if (cameraMode == 1 || cameraMode == 2) {
    	eye.x+=bw*sin(theta2*(M_PI/180.0))*cos(fcrot*(M_PI/180.0))+bw*cos(theta2*(M_PI/180.0))*sin(fcrot*(M_PI/180.0));
	eye.y-= bw*cos(theta2*(M_PI/180.0))*cos(fcrot*(M_PI/180.0))+bw*sin(theta2*(M_PI/180.0))*sin(fcrot*(M_PI/180.0));
	lookat.x+=bw*sin(theta2*(M_PI/180.0))*cos(fcrot*(M_PI/180.0))+bw*cos(theta2*(M_PI/180.0))*sin(fcrot*(M_PI/180.0)); 
	lookat.y-= bw*cos(theta2*(M_PI/180.0))*cos(fcrot*(M_PI/180.0))+bw*sin(theta2*(M_PI/180.0))*sin(fcrot*(M_PI/180.0));
    }
}
/*inline double bw(double x){
    return 1.915*theta(x)*(M_PI/180.0);
}
inline double fw(double x){
    return ((bw(x)-ln_axle)*cos(theta2*(M_PI/180.0)) + sqrt(ln_axle*ln_axle + bw(x)*(2*ln_axle-bw(x))*sin(theta2*(M_PI/180.0))*sin(theta2*(M_PI/180.0))));
}
inline double phi(double x){
    return fw(x)/1.28;
}
inline double fcrot(double x){
    asin(fw(x)*cos(theta2*(M_PI/180.0))/ln_axle);
}
inline double fctrax(double x){
    return fw(x)*cos(theta2*(M_PI/180.0)) - ds_front*sin(fcrot(x));
}
inline double fctray(double x){
    return bw(x);
}
*/
//seat paramter
double seat_height = 2.35;

void drawCycle(GLuint frameTexture){
  float colorBlue[] = { 0.0f, 0.0f, 1.0f, 1.0f };
  //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorBlue);

  drawFrame(frameTexture);
    // draw back wheel
    glPushMatrix();
    glTranslatef(0,4.25,-1.5);
    glRotatef(theta,1.0,0.0,0.0);
    drawWheel(wheelTexture);
    glPopMatrix();

    // draw seat
    glPushMatrix();
    glRotatef(90,1.0,0.0,0.0);
    glRotatef(90,0.0,0.0,1.0);

    glRotatef(15,0.0,1.0,0.0);
    glTranslatef(seat_height,0.0,0.0);
    glRotatef(-15,0.0,1.0,0.0);

    drawSeat();
    glPopMatrix();

    //draw handle
    glPushMatrix();
    glTranslatef(0.0,-3.9,1.15);
    glRotatef(-17.0, 1.0, 0.0, 0.0);
    glRotatef(theta2, 0.0, 0.0, 1.0);
    drawHandle(phi,wheelTexture,frameTexture);
    glPopMatrix();

    //draw pedals
    glPushMatrix();
    glTranslatef(0.0,0.15,-1.30);
    glRotatef(90,0.0,1.0,0.0);
    glRotatef(phi2,0.0,0.0,1.0);
    drawPedals(phi2);
    glPopMatrix();
    
    //draw chain
    glPushMatrix();
    glRotatef(90,1.0,0.0,0.0);
    drawCylinder(4.114,0.03, Vec(0.148,-0.94,-2.2), Vec(-6,2.165,27.324), Vec(0,0,0));
    drawCylinder(4.114,0.03, Vec(0.148,-1.85,-2.2), Vec(1,2.165,-27.324), Vec(0,0,0));
    glPopMatrix();

}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity(); 
  gluLookAt(eye.x, eye.y, eye.z,  // eye is at (0,0,8)
  lookat.x,lookat.y,lookat.z,      // center is at (0,0,0)
  up.x, up.y, up.z);      // up is in positive Y direction

  //draw the room
  float colorWhite[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorWhite);

  glPushMatrix();
    glTranslatef(0.0, 0.0, 1.55);
    drawRoom(woodenTexture, wallTexture,roofTexture,paintTexture, roomLights);
  glPopMatrix();

  //draw the cycle
  glPushMatrix();
    glTranslatef(fctrax,fctray,0);
    glRotatef(fcrot,0.0,0.0,1.0);
    drawCycle(frameTexture);
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
    case '3':
    if(eye.y==6.0){
        cameraMode = 0;
	eye.x = 9.0;
        eye.y = 0.0;
	eye.z = 0.0;
        up.x = 0.0;
	up.y = 0.0;
        up.z = 1.0;
    }
    else if(eye.x==9.0){
        cameraMode = 3;
	eye.x = 0.0;
	eye.y = 6.0;
        eye.z = 12.0;
        up.x = 0.0;
	up.y = 0.3;
        up.z = 1.0;
    }
    break;
    case '2':
    if(eye.z==6.0){
        cameraMode = 0;
	eye.x = 9.0;
        eye.y = 0.0;
	eye.z = 0.0;
        lookat.x = 0.0;
	lookat.y = 0.0;
	lookat.z = 0.0;
        up.x = 0.0;
	up.y = 0.0;
        up.z = 1.0;
    }
    else if(eye.x==9.0){
        cameraMode = 1;
	eye.x = 0.0+fctrax;
	eye.y = 6.0+fctray;
        eye.z = 6.5;
	up.y = -1.0;
        lookat.x = 0.0+fctrax;
	lookat.y = 1.0+fctray;
	lookat.z = 0.3;
    }
    break;
    
    case '1':
    if(eye.z==6.0){
        cameraMode = 0;
	eye.x = 9.0;
        eye.y = 0.0;
	eye.z = 0.0;
        lookat.x = 0.0;
	lookat.y = 0.0;
	lookat.z = 0.0;
        up.x = 0.0;
	up.y = 0.0;
        up.z = 1.0;
    }
    else if(eye.x==9.0){
        cameraMode = 1;
	eye.x = 0.0+fctrax;
	eye.y = 0.0+fctray;
        eye.z = 6.0;
	up.y = -2.0;
        lookat.x = 0.0+fctrax;
	lookat.y = -1.0+fctray;
	lookat.z = 1.0;
    }
    break;

    //seat height
    case 'H':
        if(headLights){
            glDisable(GL_LIGHT2);
            headLights = !headLights; 
        }
        else{
            glEnable(GL_LIGHT2);
            headLights = !headLights;
        }
        break;

    //pedal angle
    case 'x':
        phi2 -= 2.5;
        update_params(-2.5*M_PI/180,theta2);
        break;
    case 'X':
        phi2 += 2.5;
        update_params(+2.5*M_PI/180,theta2);
        break;

    //light
    case 'L':
       if(roomLights){
           glDisable(GL_LIGHT1);
           roomLights = !roomLights; 
       }
       else{
           glEnable(GL_LIGHT1);
           roomLights = !roomLights;
       }
       break;
  }
  if (key == 27)
  exit(0);

//	float position1[] = { supremo.x, supremo.y, supremo.z, 1.0f };	
// glLightfv(GL_LIGHT1, GL_POSITION, position1);
  glutPostRedisplay();
}

void processSpecialKeys(int key, int x, int y) {
  switch(key) {
      case GLUT_KEY_PAGE_UP:
 //         theta += 0.5;
          break;
      case GLUT_KEY_PAGE_DOWN:
 //         theta -= 0.5;
          break;
      case GLUT_KEY_DOWN:
            phi2 -= 2.5;
            update_params(-2.5*M_PI/180,theta2);
          break;
      case GLUT_KEY_UP:
            phi2 += 2.5;
            update_params(+2.5*M_PI/180,theta2);
          break;
      case GLUT_KEY_LEFT:
          theta2 += 0.5;
          break;
      case GLUT_KEY_RIGHT:
          theta2 -= 0.5;
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
  gluPerspective(80.0, 1.0, 1.0, 30.0);

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(9.0, 0.0, 0.0,  // eye is at (0,0,8)
  0.0, 0.0, 0.0,      // center is at (0,0,0)
  0.0, 0.0, 1.0);      // up is in positive Y direction

	glShadeModel(GL_SMOOTH);

	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	
	// Enable light and set up 2 light sources (GL_LIGHT0 and GL_LIGHT1)
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// We're setting up two light sources. One of them is located
	// on the left side of the model (x = -1.5f) and emits white light. The
	// second light source is located on the right side of the model (x = 1.5f)
	// emitting red light.

	// GL_LIGHT0: the white light emitting light source
	// Create light components for GL_LIGHT0
	float ambientLight0[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float diffuseLight0[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	float specularLight0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float position0[] = { -1.5f, 1.0f, -4.0f, 1.0f };	
	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight0);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);

	// GL_LIGHT1: the fixture on wall
	// Create light components for GL_LIGHT1
	float ambientLight1[] = { 0.8f, 0.8f, 1.0f, 1.0f };
	float diffuseLight1[] = { 0.8f, 0.8f, 1.0f, 1.0f };
	float specularLight1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float position1[] = { -9.96f,0.0f,7.225f,1.0f };	
	// Assign created components to GL_LIGHT1
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);
	glLightfv(GL_LIGHT1, GL_POSITION, position1);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.005);

	// GL_LIGHT1: the red light emitting light source
	// Create light components for GL_LIGHT1
	float ambientLight2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float diffuseLight2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float specularLight2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position2[] = {0.0f,0.0f,0.0f,1.0f};
    GLfloat hldir[] = {0.0f,-1.0f,0.0f};
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, hldir);
	// Assign created components to GL_LIGHT1
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularLight2);
	glLightfv(GL_LIGHT2, GL_POSITION, position2);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 15.0);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.01);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
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

   //load all textures
   int texw,texh;
   woodenTexture = LoadTexture("wooden.bmp", texw, texh);
   wheelTexture = LoadTexture("wheel.bmp", texw, texh);
   wallTexture = LoadTexture("wall.bmp", texw, texh);
   roofTexture = LoadTexture("roof.bmp", texw, texh);
   paintTexture = LoadTexture("painting.bmp", texw, texh);
   frameTexture = LoadTexture("frame.bmp" , texw, texh);

  init();
  glutMainLoop();
  return 0;
}

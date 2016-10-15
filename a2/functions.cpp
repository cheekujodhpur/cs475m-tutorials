#include "functions.hpp"
#include <stdio.h>

void Seat::drawTop(){
      glBegin(GL_TRIANGLE_STRIP);

      glVertex3f(d,bw,0.0);
      glVertex3f(d,tw,th);
      glVertex3f(d,bw,-bh);
      glVertex3f(d,-tw,th);
      glVertex3f(d,-bw,-bh);
      glVertex3f(d,-bw,0.0);

      glEnd();
    }
void Seat::drawBottom(){
      glBegin(GL_TRIANGLE_STRIP);

      glVertex3f(-d,bw,0.0);
      glVertex3f(-d,tw,th);
      glVertex3f(-d,bw,-bh);
      glVertex3f(-d,-tw,th);
      glVertex3f(-d,-bw,-bh);
      glVertex3f(-d,-bw,0.0);

      glEnd();
    }
void Seat::drawSides(){
      glBegin(GL_TRIANGLE_STRIP);

      glVertex3f(d,bw,0.0);
      glVertex3f(-d,bw,0.0);
      glVertex3f(d,bw,-bh);
      glVertex3f(-d,bw,-bh);
      glVertex3f(d,-bw,-bh);
      glVertex3f(-d,-bw,-bh);
      glVertex3f(d,-bw,0.0);
      glVertex3f(-d,-bw,0.0);
      glVertex3f(d,-tw,th);
      glVertex3f(-d,-tw,th);
      glVertex3f(d,tw,th);
      glVertex3f(-d,tw,th);
      glVertex3f(d,bw,0.0);

      glEnd();
    }
void Seat::draw(){
        glColor3f(1.0,1.0,1.0);

        glPushMatrix();
        drawTop();
        drawBottom();
        drawSides();
        glPopMatrix();
    }


// cylinder drawing
void drawCylinder(double height, double radius, Vec trans, Vec rot, Vec color){
    int numMajor = 100;
    int numMinor = 100;

  double majorStep = height / numMajor;
  double minorStep = 2.0 * M_PI / numMinor;
  int i, j;

  glColor3f(color.x,color.y,color.z);

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
          glVertex3f(x, y, z1);
      }
      glEnd();
  }
  glPopMatrix();
}

//gear drawing(solid cylinder)
void drawDisk(double height, double radius,double tooth_width, double tooth_height, Vec trans, Vec rot, Vec color){
    int numMajor = 100;
    int numMinor = 100;

  double majorStep = height / numMajor;
  double minorStep = 2.0 * M_PI / numMinor;
  int i, j;

  glColor3f(color.x,color.y,color.z);

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
          glVertex3f(x, y, z1);
      }
      glEnd();
  }
      for (j=0; j<= numMinor; ++j) {
          double a = j * minorStep ;
          double next_a = ( j + 1 ) * minorStep;
          glBegin(GL_TRIANGLE_STRIP);
          glVertex3f(0,0,height/2);
          glVertex3f(radius*cos(a),radius*sin(a),height/2);
          glVertex3f(radius*cos(next_a),radius*sin(next_a),height/2);
          glEnd();
          glBegin(GL_TRIANGLE_STRIP);
          glVertex3f(0,0,-height/2);
          glVertex3f(radius*cos(a),radius*sin(a),-height/2);
          glVertex3f(radius*cos(a),radius*sin(a),-height/2);
     }
     for (j=0; j<=15; ++j){
          double a = j * 2.0 * M_PI / 15;
          double b = tooth_width / radius;
          glBegin(GL_TRIANGLE_STRIP);
          glVertex3f(radius*cos(a-b),radius*sin(a-b),height/2);
          glVertex3f(radius*cos(a+b),radius*sin(a+b),height/2);
          glVertex3f((radius+tooth_height)*cos(a),(radius+tooth_height)*sin(a),0);
          glVertex3f(radius*cos(a+b),radius*sin(a+b),-height/2);
          glVertex3f(radius*cos(a-b),radius*sin(a-b),-height/2);
          glVertex3f((radius+tooth_height)*cos(a),(radius+tooth_height)*sin(a),0);
          glVertex3f(radius*cos(a-b),radius*sin(a-b),height/2);
          glEnd();
  }
  glPopMatrix();
}

//torus drawing
void drawTorus(double width, double radius, Vec trans, Vec rot, Vec color, double total=2.0*M_PI){
  int num = 100;

  double Step = total / num;
  double smallStep = 2.0*M_PI / num;
  int i, j;

  glColor3f(color.x,color.y,color.z); 

  glPushMatrix();

  glTranslatef(trans.x, trans.y, trans.z);
  glRotatef(rot.x, 1.0, 0.0, 0.0);
  glRotatef(rot.y, 0.0, 1.0, 0.0);
  glRotatef(rot.z, 0.0, 0.0, 1.0);

  for (i = 0; i < num; ++i) {
        double theta = i*Step;

      glBegin(GL_TRIANGLE_STRIP);
      for (j = 0; j <= num; ++j) {
          double phi = j * smallStep;
          glVertex3f((radius-width*sin(phi))*cos(theta),(radius-width*sin(phi))*sin(theta), width*cos(phi));
          glVertex3f((radius-width*sin(phi))*cos(theta+Step),(radius-width*sin(phi))*sin(theta+Step), width*cos(phi)); 
      } 
      glEnd();
  }
  glPopMatrix();
}

//torus drawing
void drawTorusTexture(double width, double radius, Vec trans, Vec rot, Vec color, GLuint texture, double total=2.0*M_PI){
  int num = 100;

  double Step = total / num;
  double smallStep = 2.0*M_PI / num;
  int i, j;

  glColor3f(color.x,color.y,color.z); 

  glPushMatrix();

  glTranslatef(trans.x, trans.y, trans.z);
  glRotatef(rot.x, 1.0, 0.0, 0.0);
  glRotatef(rot.y, 0.0, 1.0, 0.0);
  glRotatef(rot.z, 0.0, 0.0, 1.0);

  for (i = 0; i < num; ++i) {
        double theta = i*Step;

          glEnable(GL_TEXTURE_2D);
          glBindTexture(GL_TEXTURE_2D, texture);
      glBegin(GL_TRIANGLE_STRIP);
      for (j = 0; j <= num; ++j) {
          double phi = j * smallStep;
          glTexCoord2d((double)i/num, (double)j/num);
          glVertex3f((radius-width*sin(phi))*cos(theta),(radius-width*sin(phi))*sin(theta), width*cos(phi));
          glTexCoord2d((double)(i+1)/num, (double)j/num);
          glVertex3f((radius-width*sin(phi))*cos(theta+Step),(radius-width*sin(phi))*sin(theta+Step), width*cos(phi)); 
      } 
      glEnd();
          glBindTexture(GL_TEXTURE_2D, 0);
          glDisable(GL_TEXTURE_2D);
  }
  glPopMatrix();
}

//drawing wheel
void drawWheel(GLuint texture){
  drawTorusTexture(0.08,1.875, Vec(0.0,0.0, 0.0), Vec(0.0,90,0.0), Vec(0.1,0.1,0.1),texture);
  drawTorus(0.075,1.7, Vec(0.0,0.0, 0.0), Vec(0.0,90,0.0), Vec(0.7,0.7,0.7));
  drawCylinder(0.28, 0.1, Vec(0.0,0.0,0.0), Vec(0.0, 90.0, 0.0), Vec(0.7,0.0,0.0));
  //Back gear disk
  drawDisk(0.05, 0.3,0.06,0.1, Vec(0.08,0.0,0.0), Vec(0.0, 90.0, 0.0), Vec(1,1,1));
  
  for(int x=0;x<10;x++){
    glPushMatrix();
    glRotatef(36*x,1.0,0.0,0.0);
    drawCylinder(1.65, 0.02, Vec(0.02,0.825,0.0), Vec(90.0,5.2, 0.0), Vec(0.7,0.7,0.7));
    glPopMatrix();
    glPushMatrix();
    glRotatef(36*x+18,1.0,0.0,0.0);
    drawCylinder(1.65, 0.02, Vec(-0.02,0.825,0.0), Vec(90.0, -5.2, 0.0), Vec(0.7,0.7,0.7));
    glPopMatrix();	
  }	
}

void drawFrontWheel(GLuint texture){
  drawTorusTexture(0.2,1.18, Vec(0.0,0.0, 0.0), Vec(0.0,90,0.0), Vec(0.1,0.1,0.1),texture);
  drawTorus(0.17,1.1, Vec(0.0,0.0, 0.0), Vec(0.0,90,0.0), Vec(0.7,0.7,0.7));
  drawCylinder(0.64, 0.15, Vec(0.0,0.0,0.0), Vec(0.0, 90.0, 0.0), Vec(0.7,0.0,0.0));
  for(int x=0;x<10;x++){
    glPushMatrix();
    glRotatef(36*x,1.0,0.0,0.0);
    drawCylinder(1.05, 0.02, Vec(0.15,0.625,0.0), Vec(90.0,9.2, 0.0), Vec(0.7,0.7,0.7));
    glPopMatrix();
    glPushMatrix();
    glRotatef(36*x+18,1.0,0.0,0.0);
    drawCylinder(1.05, 0.02, Vec(-0.15,0.625,0.0), Vec(90.0, -9.2, 0.0), Vec(0.7,0.7,0.7));
    glPopMatrix();	
  }	
}

void drawFrame(){
  //big rod
  drawCylinder(3.2, 0.2, Vec(0.0, 0.5, 0.0), Vec(-15.0, 0.0, 0.0),Vec(0.0,0.1,0.85));
  //middle top rod
  drawCylinder(4.5, 0.15, Vec(0.0, -1.9, -0.3), Vec(60.0, 0.0, 0.0),Vec(0.0,0.1,0.85));
  //middle bottom rod
  drawCylinder(4.5, 0.15, Vec(0.0,-1.55, 1.15) , Vec(85.0, 0.0, 0.0),Vec(0.0,0.1,0.85));
  //front rod
  drawCylinder(1.7, 0.2, Vec(0.0, -3.95, 1.0), Vec(-17.0, 0.0, 0.0),Vec(0.0,0.1,0.85));

  //back top rods
  drawCylinder(1.1, 0.11, Vec(-0.15,1.2,1.1) , Vec(50.0, 15.0, 0.0),Vec(0.0,0.1,0.85));
  drawCylinder(1.1, 0.11, Vec(0.15,1.2,1.1) , Vec(50.0, -15.0, 0.0),Vec(0.0,0.1,0.85));
  drawCylinder(3.7, 0.11, Vec(-0.25,2.95,-0.35), Vec(50.0, 0.0, 0.0),Vec(0.0,0.1,0.85));
  drawCylinder(3.7, 0.11, Vec(0.25,2.95,-0.35), Vec(50.0, 0.0, 0.0),Vec(0.0,0.1,0.85));

  //back bottom rods
  drawCylinder(1.1, 0.11, Vec(-0.15,0.65,-1.5) , Vec(90.0, 15.0, 0.0),Vec(0.0,0.1,0.85));
  drawCylinder(1.1, 0.11, Vec(0.15,0.65,-1.5) , Vec(90.0, -15.0, 0.0),Vec(0.0,0.1,0.85));
  drawCylinder(3.3, 0.11, Vec(0.25, 2.75, -1.5), Vec(90.0, 0.0, 0.0),Vec(0.0,0.1,0.85));
  drawCylinder(3.3, 0.11, Vec(-0.25, 2.75, -1.5), Vec(90.0, 0.0, 0.0),Vec(0.0,0.1,0.85));
}

void drawSeat(){
  Seat seat(0.66,1.5,0.25,0.75,0.15);
  seat.draw();
  glPushMatrix();
  glRotatef(-75,0.0,1.0,0.0);
  glTranslatef(-0.5,0.0,.7);
  drawCylinder(1.5,0.18,Vec(0.0,0.0,0.0),Vec(0.0,0.0,0.0),Vec(0.0,0.85,0.1));
  glPopMatrix();
}

void drawHandle(double phi,GLuint texture){
    glPushMatrix();
    drawCylinder(3.0,0.18, Vec(0.0,0.0,0.0), Vec(0.0,0.0,0.0), Vec(0.5,0.2,0.7));
        //draw headlight
        glPushMatrix();
        GLfloat hlpos[] = {0.0f,-1.0f,0.0f,1.0f};
        GLfloat hldir[] = {0.0f,-1.0f,-0.1f};
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, hldir);
        glLightfv(GL_LIGHT2, GL_POSITION, hlpos);
        drawCylinder(0.4,0.35, Vec(0.0,-0.3,0.0), Vec(107.0,0.0,0.0), Vec(0.0,0.1,0.85));
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0,0.0,-1.5);
        drawTorus(0.18,0.5, Vec(0.0,0.0, -0.5), Vec(90.0,0,0.0), Vec(0.7,0.0,0.0),M_PI);
            glPushMatrix();
            drawCylinder(1.3, 0.175, Vec(0.5,0.00,-1.15), Vec(0.0, 0.0, 0.0),Vec(0.0,0.1,0.85));
            drawCylinder(1.3, 0.175, Vec(-0.5,0.00,-1.15), Vec(0.0, 0.0, 0.0),Vec(0.0,0.1,0.85));
                glPushMatrix();
                glTranslatef(0.0,0.0,-1.65);
                glRotatef(phi,1.0,0.0,0.0);
                drawFrontWheel(texture);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        //drawing hand handle
        glPushMatrix();
            glTranslatef(0.0,0.5,1.5); 
            glRotatef(90,0.0,1.0,0.0);
            glRotatef(180.0,0.0,0.0,1.0);
            glPushMatrix();
            drawTorus(0.18,0.5, Vec(0.0,0.0, 0.0), Vec(00.0,0,0.0), Vec(0.7,0.0,0.0),M_PI/2);
            drawCylinder(0.8,0.18, Vec(0.5,-0.4,0.0), Vec(90.0,0.0,0.0), Vec(0.5,0.2,0.7));
            //draw hand hand handle
                glPushMatrix();
                    glTranslatef(0.5,-0.8,0.0);
                    glRotatef(90,0.0,0.0,1.0);
                    drawCylinder(3.6,0.18, Vec(0.0,0.0,0.0), Vec(0.0,0.0,0.0), Vec(0.7,0.0,0.7));
                    drawCylinder(0.8,0.20, Vec(0.0,0.0,1.4), Vec(0.0,0.0,0.0), Vec(0.7,0.7,0.7));
                    drawCylinder(0.8,0.20, Vec(0.0,0.0,-1.4), Vec(0.0,0.0,0.0), Vec(0.7,0.7,0.7));
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void drawBox(double a, double b, double c, Vec color)
{
    glColor3f(color.x, color.y, color.z);

    glBegin(GL_TRIANGLE_STRIP);

        glVertex3f(a,b,c);
        glVertex3f(a,b,-c);
        glVertex3f(a,-b,c);
        glVertex3f(a,-b,-c);
        glVertex3f(-a,-b,c);
        glVertex3f(-a,-b,-c);
        glVertex3f(-a,b,c);
        glVertex3f(-a,b,-c);

    glEnd();
    glBegin(GL_TRIANGLE_STRIP);

        glVertex3f(a,-b,c);
        glVertex3f(-a,-b,c);
        glVertex3f(a,b,c);
        glVertex3f(-a,b,c);
        glVertex3f(a,b,-c);
        glVertex3f(-a,b,-c);
        glVertex3f(a,-b,-c);
        glVertex3f(-a,-b,-c);

    glEnd();
}

void drawPedals(double phi2){
        //front gear disk
	glPushMatrix();
        drawDisk(0.1, 0.5,0.07,0.1, Vec(0.0,0.0,0.21), Vec(0.0, 0.0, 0.0), Vec(1,1,1));
	glPopMatrix();

    drawCylinder(1.6,0.18, Vec(0.0,0.0,0.0), Vec(0.0,0.0,0.0), Vec(0.0,0.1,0.7));
       
        //pedal rods
        glPushMatrix();
        glTranslatef(0.0,0.0,-0.8);
        glRotatef(60,0.0,1.0,0.0);
        glTranslatef(0.0,0.0,-0.4);
        drawCylinder(1.0,0.13, Vec(0.0,0.0,0.0), Vec(0.0,0.0,0.0), Vec(0.7,0.0,0.1));
            //pedal shafts
            glPushMatrix();
            glTranslatef(0.0,0.0,-0.5);
            glRotatef(-60,0.0,1.0,0.0);
            glTranslatef(0.0,0.0,-0.3);
            glRotatef(-phi2,0.0,0.0,1.0);
            drawBox(0.1,0.25,0.45,Vec(1.0,1.0,1.0));
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0,0.0,0.8);
        glRotatef(60,0.0,1.0,0.0);
        glTranslatef(0.0,0.0,0.4);
        drawCylinder(1.0,0.13, Vec(0.0,0.0,0.0), Vec(0.0,0.0,0.0), Vec(0.7,0.0,0.1));
            //pedal shafts
            glPushMatrix();
            glTranslatef(0.0,0.0,0.5);
            glRotatef(-60,0.0,1.0,0.0);
            glTranslatef(0.0,0.0,0.3);
            glRotatef(-phi2,0.0,0.0,1.0);
            drawBox(0.1,0.25,0.45,Vec(1.0,1.0,1.0));
            glPopMatrix();
        glPopMatrix();
}

void drawRoom(GLuint texture, GLuint texture1, GLuint texture2, GLuint texture3, bool roomLights){
    glColor3f(0.5,0.5,0.5);
    float colorWhite[] = { 1.0f, 0.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorWhite);

        double a = 10;
        double b = 10;
        double c = 5;

        int num = 100;
        float istep = a/num;
        float jstep = b/num;
        float kstep = c/num;
        float tistep = 1/(2.0*num);
        float tjstep = 1/(2.0*num);
        float tkstep = 1/(2.0*num);

    //drawFloor
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
        for(int j = -num;j<num+1;j++){
            glBegin(GL_TRIANGLE_STRIP);
            for(int i = -num;i<=num;i++){
                glTexCoord2f(0.5+tistep*i,0.5+tjstep*j);
                glVertex3f(istep*i, jstep*j, -5);

                glTexCoord2f(0.5+tistep*i,0.5+tjstep*(j+1));
                glVertex3f(istep*(i), jstep*(j+1), -5);
            }
            glEnd();
        }
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    //draw walls
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture1);

        for(int i = -num;i<num+1;i++){
            glBegin(GL_TRIANGLE_STRIP);
            for(int k = -num;k<=2*num;k++){
                glTexCoord2f(0.5+tjstep*i,0.66*(0.5+tkstep*k));
                glVertex3f(istep*i, -b, kstep*k);

                glTexCoord2f(0.5+tjstep*(i+1),0.66*(0.5+tkstep*(k)));
                glVertex3f(istep*(i+1), -b, kstep*k);
            }
            glEnd();
        }
        for(int j = -num;j<num+1;j++){
            glBegin(GL_TRIANGLE_STRIP);
            for(int k = -num;k<=2*num;k++){
                glTexCoord2f(0.66*(0.5+tkstep*k),0.5+tjstep*j);
                glVertex3f(a, jstep*j, kstep*k);

                glTexCoord2f(0.66*(0.5+tkstep*k),0.5+tjstep*(j+1));
                glVertex3f(a, jstep*(j+1), kstep*k);
            }
            glEnd();
        }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(0.0,1.0);
        glVertex3f(a,-b,2*c);
        glTexCoord2d(0.0,0.0);
        glVertex3f(-a,-b,2*c);
        glTexCoord2d(1.0,1.0);
        glVertex3f(a,b,2*c);
        glTexCoord2d(1.0,0.0);
        glVertex3f(-a,b,2*c);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture1);

        for(int j = -num;j<num+1;j++){
            glBegin(GL_TRIANGLE_STRIP);
            for(int k = -num;k<=2*num;k++){
                glTexCoord2f(0.66*(0.5+tkstep*k),0.5+tjstep*j);
                glVertex3f(-a, jstep*j, kstep*k);

                glTexCoord2f(0.66*(0.5+tkstep*k),0.5+tjstep*(j+1));
                glVertex3f(-a, jstep*(j+1), kstep*k);
            }
            glEnd();
        }

        for(int i = -num;i<num+1;i++){
            glBegin(GL_TRIANGLE_STRIP);
            for(int k = -num;k<=2*num;k++){
                glTexCoord2f(0.5+tjstep*i,0.66*(0.5+tkstep*k));
                glVertex3f(istep*i, b, kstep*k);

                glTexCoord2f(0.5+tjstep*(i+1),0.66*(0.5+tkstep*(k)));
                glVertex3f(istep*(i+1), b, kstep*k);
            }
            glEnd();
        }

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glColor3f(0.2,0.2,0.2);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(-a+0.01,b/2,-c/2+1.5);
        glVertex3f(-a+0.01,-b/2,-c/2+1.5);
        glVertex3f(-a+0.01,b/2,c+1.5);
        glVertex3f(-a+0.01,-b/2,c+1.5);
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture3);

    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(1.0,0.0);
        glVertex3f(-a+0.02,b/2-0.3,-c/2+1.8);
        glTexCoord2d(0.0,0.0);
        glVertex3f(-a+0.02,-b/2+0.3,-c/2+1.8);
        glTexCoord2d(1.0,1.0);
        glVertex3f(-a+0.02,b/2-0.3,c+1.2);
        glTexCoord2d(0.0,1.0);
        glVertex3f(-a+0.02,-b/2+0.3,c+1.2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);


    GLfloat colSpec[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat noSpec[] = {0.0f, 0.0f, 0.0f, 1.0f};
    if(roomLights)
        glMaterialfv(GL_FRONT, GL_EMISSION, colSpec);
    else
        glMaterialfv(GL_FRONT, GL_EMISSION, noSpec);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(-a+0.03,1.5,c+2.5);
        glVertex3f(-a+0.03,-1.5,c+2.5);
        glVertex3f(-a+0.03,1.5,c+2.0);
        glVertex3f(-a+0.03,-1.5,c+2.0);
    glEnd();
    glMaterialfv(GL_FRONT, GL_EMISSION, noSpec);
}

GLuint LoadTexture(const char* filename, int &w, int &h){
    GLuint texture;
    unsigned char header[54]; //54 byte header of BMP
    int pos;
    unsigned int size; //w*h*3

    unsigned char* data; //Data in RGB Format
    FILE *file;

    file = fopen(filename, "rb");
    if(file==NULL) return 0; //if file is empty
    if(fread(header, 1, 54, file)!=54){
        printf("incorrect BMP file\n");
        return 0;
    }

    //read metadata
    pos = *(int*)&(header[0x0A]);
    size = *(int*)&(header[0x22]);
    w = *(int*)&(header[0x12]);
    h = *(int*)&(header[0x16]);

    //just in case metadata is missing
    if(size == 0)
        size = w*h*3;
    if(pos == 0)
        pos = 54;

    data = new unsigned char[size];

    fread(data, size, 1, file); //read the file
    fclose(file);
    ////////////////////////////////
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);

    free(data);
    return texture; //return the texture id
}

GLfloat angleSum(GLfloat a, GLfloat b)
{
  a += b;
  if (a < 0) return a+2*M_PI;
  else if (a > 2*M_PI) return a-2*M_PI;
  else return a;
}


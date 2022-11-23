#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h>
#include <gl/gl.h>
#include <math.h>

void display();
void reshape(int,int);
void timer(int);

float bottomCarXPostition = 150;
float topCarXposition = 100;

//Change Color for clearing
void init(){
    //
    glClearColor(0.85,0.85,0.85,1);
}



int main(int argc,char **argv){

glutInit(&argc,argv);
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //DOUBLE BUFFER MODE

glutInitWindowPosition(200,0);
glutInitWindowSize(1200,800);
glutCreateWindow("Window 1");
glutSetWindowTitle("Omar Elmanzalawy: 20100221 / Shady Zewil: 20101064");

//CallBack Methods
glutDisplayFunc(display);
glutReshapeFunc(reshape);
//Calls Function timer every 1 second
glutTimerFunc(1000,timer,0);

init();

glutMainLoop();

}

void wheel(int x,int y)
{
   float th;
   glBegin(GL_POLYGON);
   glColor3f(0,0,0);
   //circle
   for(int i=0;i<360;i++)
   {
       th=i*(3.1416/180);
       glVertex2f(x+20*cos(th),y+20*sin(th));
   }

   glEnd();

}

void road(){
glLoadIdentity();
glLineWidth(10);
glBegin(GL_LINES);
glColor3f(1,1,1);

// Max Y: 200 , MIN: 100
//Top Line
glVertex2f(0,300);
glVertex2f(700,300);

//Bottom Line
glBegin(GL_LINES);
glVertex2f(0,20);
glVertex2f(700,20);

glEnd();

glColor3f(0.3,0.3,0.3);
glRectd(700,25,0,295);

}

void car()
{
   //Bottom Part
   glLoadIdentity();
   glBegin(GL_POLYGON);
   glColor3f(1,1,1);
   glVertex2f(topCarXposition,100);
   glVertex2f(topCarXposition,160);
   glVertex2f(topCarXposition+350,160);
   glVertex2f(topCarXposition+350,100);

   //Top Part
   glBegin(GL_POLYGON);
   glVertex2f(bottomCarXPostition,160);
   glVertex2f(bottomCarXPostition+50,200);
   glVertex2f(bottomCarXPostition+250,200);
   glVertex2f(bottomCarXPostition+300,160);


   glEnd();

   wheel(topCarXposition+100,100);
   wheel(topCarXposition+280,100);

}

float angle = 120;
//TODO: MAKE ROTATING SUN
void sun(int x,int y){
    glBegin(GL_POLYGON);
    glColor3f(1,1,0);

   for(int i=0;i<360;i++)
   {

       double th=i*(3.1416/180);
       glVertex2f(x+65*cos(th),y+65*sin(th));
   }
   glEnd();


}

void background(){
    //SKY
    glColor3f(0,0.8,1);
    glRectd(700,305,0,700);
    //SEA
    glBegin(GL_POLYGON);
        glColor3f(.8,.89,1);
        glVertex2i(0,150);

        glColor3f(.8,.89,1);
        glVertex2i(700,150);

        glColor3f(.2,.58,1);
        glVertex2i(700,350);

        glColor3f(.2,.58,1);
        glVertex2i(0,350);
    glEnd();
}

void tree(int x,int y){
    //Wood Part
 glBegin(GL_POLYGON);
        glVertex2i(x,y);
        glVertex2i(x+6,y);
        glVertex2i(x+6,y+105);
        glVertex2i(72,y+105);
    glEnd();

    //Leaves Part
    glColor3f(.1,0.5,0.1);
    glBegin(GL_POLYGON);
        glVertex2i(x+3,y+150);
        glVertex2i(x+28,y+90);
        glVertex2i(x-22,y+90);

    glEnd();
    glBegin(GL_POLYGON);
        glVertex2i(x+3,y+120);
        glVertex2i(x+28,y+60);
        glVertex2i(x-22,y+60);

    glEnd();
    glBegin(GL_POLYGON);
        glVertex2i(x+3,y+100);
        glVertex2i(x+28,y+40);
        glVertex2i(x-22,y+40);

    glEnd();


}

//In order for animation to work, display function has to be called multiple times
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    //Drawing Goes Here
    background();
    sun(85,620);
    road();
    tree(72,300);
    car();
    //Display Drawing
    glFlush();

    glutSwapBuffers(); //Swaps between front and back buffer
}

//Called When window is reshaped (minimized maximized, etc....)
void reshape(int w,int h){

//Setting Viewport
glViewport(0,0,w,h);

//Setting Projection

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0,700,0,700);
glMatrixMode(GL_MODELVIEW);

}

void timer(int){

//Calls Display function
glutPostRedisplay();
//Function will call itself 60 times every 1 second (60fps)
glutTimerFunc(1000/60,timer,0);

topCarXposition -= 1.5;
bottomCarXPostition -= 1.5;
angle +=0.5;
if(angle >= 360){ angle = 0;}

//Checks if car is out of bounds
if(topCarXposition<-370){
    topCarXposition = 700;
    bottomCarXPostition = 750;
}

}

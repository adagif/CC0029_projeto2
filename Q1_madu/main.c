#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <GL/gl.h>

void lighting(){

    float position[4] = {2.0f, 2.0f, 2.0f, 1.0f};
    float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


}

int init(){

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 1.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

    lighting();
}

void display(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glutSolidSphere(1.5, 40, 40);
    glFlush();
}

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200,0);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Exemplo 1 - iluminacao");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;


}





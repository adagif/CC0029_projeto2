#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <GL/gl.h>

GLfloat x = 0;
GLfloat velocidade = 0.05;

void girar(){

    x = x + velocidade;
    if(x>360){
        x = 0;
    }
    glutPostRedisplay();

}
void lighting(){

    float position[4] = {0.0f, 1.0f, 0.0f, 1.0f};
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
    gluLookAt(0.0, 0.0, 2.0,
              0.0, 0.0, 0.0,
              1.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

    lighting();
}

void display(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     
    glMatrixMode(GL_MODELVIEW);
    
    //desenha tábua da mesa
    glPushMatrix();
        glLoadIdentity();
        glRotatef(x, 0, 1, 0);
        glScalef(1, 0.25, 1);
        glutSolidCube(1.0f);
       

    glPopMatrix();
    
   //desenha esfera 
   glPushMatrix();
        glLoadIdentity();
        glRotatef(x, 0, 1, 0);
        glTranslatef(0.15, 0.37, 0.0);
        glutSolidSphere(0.25, 40, 40);
    glPopMatrix();
/* 
    //desenha bule
    glPushMatrix();
    glTranslatef(0.5, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glutSolidTeapot(0.5f);
    glutSwapBuffers();
    glPopMatrix();
    //desenha rosquinha
    glPushMatrix();
    glTranslatef(0.5, -1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0); // Define a cor do torus (azul)
    glutSolidTorus(0.1, 0.3, 40, 40); // Desenha o torus em arame
    glPopMatrix();


   

    glFlush();*/
    glutSwapBuffers();
}

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200,0);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Exemplo 1 - iluminacao");


    init();
    glutDisplayFunc(display);
    glutIdleFunc(girar);
    glutMainLoop();
    
    return 0;


}





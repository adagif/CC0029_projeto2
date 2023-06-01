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

    float position[4] = {2.0f, 2.0f, 2.0f, 1.0f};
    float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.06f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.01f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01f);

    float global_ambient[4] = {0.95f, 0.95f, 0.95f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
        

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

}

int init(){

    glClearColor(0.7f, 0.7f, 0.7f, 0.7f);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 2.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

    lighting();
}

void display(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     

    float ka[4] = {0.1f, 0.18725f,0.1745f, 1.0f};
    float kd[4] = {0.396f, 0.74151f, 0.69102f, 1.0f};
    float ks[4] = {0.297254f,0.30829f, 0.306678f, 1.0f};
    float ns = 0.8f * 128.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);

    glMatrixMode(GL_MODELVIEW);
    
    //desenha tábua da mesa
    glPushMatrix();
    
        glLoadIdentity();
        glRotatef(x, 0, 1, 0);
        glScalef(2, 0.25, 1);
        glutSolidCube(1.0f);
       

    glPopMatrix();
    
   //desenha esfera 
   glPushMatrix();
        glLoadIdentity();
        glRotatef(x, 0, 1, 0);
        glTranslatef(0.75, 0.27, 0.0);
        glutSolidSphere(0.15, 40, 40);
    glPopMatrix();
 
    //desenha bule
    glPushMatrix();
        glLoadIdentity();
        glRotatef(x, 0, 1, 0);
        glTranslatef(-0.60, 0.39, 0.0);
        glutSolidTeapot(0.40f);
    glPopMatrix();
    
    //desenha rosquinha
    glPushMatrix();
        glLoadIdentity();
        glRotatef(x, 0, 1, 0);
        glTranslatef(0.30, 0.30, 0.0);
        glutSolidTorus(0.05, 0.15, 40, 40);
    glPopMatrix();

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





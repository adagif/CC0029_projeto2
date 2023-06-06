#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <GL/gl.h>

typedef struct{
    float ka[4];
    float kd[4];
    float ks[4];
    float ns;
}Material;

Material yellow_rubber = {{0.05f, 0.05f, 0.0f, 1.0f},
                 {0.5f, 0.5f, 0.4f, 1.0f},
                 {0.7f, 0.7f, 0.4f, 1.0f},
                   0.5f * 50.0f };

Material Ruby = {{0.1745f, 0.05175f, 0.05175f, 1.0f},
                 {0.61424f, 0.04136f, 0.04136f, 1.0f},
                 {0.727811f, 0.626959f, 0.626959f, 1.0f},
                  0.2f * 128.0f};

Material Turquoise = {{0.1f, 0.18725f,0.1745f, 1.0f},
                 {0.396f, 0.74151f, 0.69102f, 1.0f},
                 {0.297254f,0.30829f, 0.306678f, 1.0f},
                 0.8f * 128.0f};
Material White_plastic = {{0.0f, 0.0f,0.0f, 1.0f},
                 {0.55f, 0.55f, 0.55f, 1.0f},
                 {0.7f,0.7f, 0.7f, 1.0f},
                 0.5f * 50.0f};
Material gold = {{0.24725f, 0.1995f,0.0745f, 1.0f},
                 {0.75164f, 0.60648f, 0.22648f, 1.0f},
                 {0.628281f,0.555802f,0.366065f, 1.0f},
                 0.4f * 50.0f};


GLfloat x = 0;

void timer(int extra){
    glutPostRedisplay();
    glutTimerFunc(15, timer, 0);
}

void update(){
    x = x + 1;
}
void lighting(){

    float position[4] = {2.0f, 6.0f, 2.0f, 1.0f};
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
    lighting();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 2.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -20.0, 20.0);

}

void updateMaterial(Material material){
    glMaterialfv(GL_FRONT, GL_AMBIENT, material.ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material.kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material.ks);
    glMaterialf(GL_FRONT, GL_SHININESS, material.ns);
}

void display(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
    glMatrixMode(GL_MODELVIEW);
    update();
    
    //superfície
    glPushMatrix();
        updateMaterial(White_plastic);
        glLoadIdentity();
        glRotatef(x, 0, 1, 0);
        glScalef(2, 0.25, 1);
        glutSolidCube(1.0f);
    glPopMatrix();

   //desenha esfera 
   glPushMatrix();
        updateMaterial(Ruby);
        glLoadIdentity();
        glRotatef(x, 0, 1, 0);
        glTranslatef(0.75, 0.27, 0.0);
        glutSolidSphere(0.15, 40, 40);
    glPopMatrix();
 
    //desenha bule
    glPushMatrix();
        updateMaterial(Turquoise);
        glLoadIdentity();
        glRotatef(x, 0, 1, 0);
        glTranslatef(-0.60, 0.39, 0.0);
        glutSolidTeapot(0.40f);
    glPopMatrix();
    
    //desenha rosquinha
    glPushMatrix();
        updateMaterial(gold);
        glLoadIdentity();
        glRotatef(x, 0, 1, 0);
        glTranslatef(0.30, 0.30, 0.0);
        glutSolidTorus(0.05, 0.15, 40, 40);
    glPopMatrix();

    //desenha parede
    glPushMatrix();
        updateMaterial(yellow_rubber);
        glLoadIdentity();
        glRotatef(x, 0, 1, 0);
        glScalef(4.0, 6.0, -0.1);
        glTranslatef(-0.002, -0.01, 5.0);
        glutSolidCube(0.5f);
    glPopMatrix();
    glutSwapBuffers();

}

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200,0);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Projeto CG 2 - Questao 1");


    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    
    return 0;


}





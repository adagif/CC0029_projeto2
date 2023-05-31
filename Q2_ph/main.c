#include <windows.h>
#include <GL/freeglut.h>

float alpha = 0, delta = 1;
boolean keyStates[256];

void lighting(){
    float position[4] = {6.0f, 3.0f, 6.0f, 1.0f};
    float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float black[4] = {0.05f, 0.05f, 0.05f, 1.0f};
    
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
    glOrtho(-4.0, 4.0, -4.0, 4.0, -4.0, 4.0);

    lighting();
}

void update(){
    alpha = alpha + 1;
    if(keyStates[GLUT_KEY_UP] == TRUE){
        delta = delta * 1.01f;
    }
    if(keyStates[GLUT_KEY_DOWN] == TRUE){
        delta = delta * (1/1.01f);
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float ka[4] = {0.1745f, 0.05175f, 0.05175f, 1.0f};
    float kd[4] = {0.61424f, 0.04136f, 0.04136f, 1.0f};
    float ks[4] = {0.727811f, 0.626959f, 0.626959f, 1.0f};
    float ns = 0.2f * 128.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);

    glMatrixMode(GL_MODELVIEW);

    update();

    glLoadIdentity();
    glRotatef(alpha, 0, 1, 0);
    glutSolidTeapot(1.5f);

    glutSwapBuffers();
}

void keyPressed_special (int key, int x, int y){
    keyStates[key] = TRUE;
}

void keyUp_special (int key, int x, int y){
    keyStates[key] = FALSE;
}

void timer(int extra){
    glutPostRedisplay();
    glutTimerFunc(15, timer, 0);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200, 0);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Projeto CG 2 - Questão 2");

    init();

    glutSpecialUpFunc(keyUp_special);
    glutSpecialFunc(keyPressed_special);
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
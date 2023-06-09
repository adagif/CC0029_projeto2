#include <windows.h>
#include <math.h>
#include <GL/freeglut.h>
#include <stdio.h>

typedef struct{
    float ka[4];
    float kd[4];
    float ks[4];
    float ns;
}Material;

Material Ruby = {{0.1745f, 0.05175f, 0.05175f, 1.0f},
                 {0.61424f, 0.04136f, 0.04136f, 1.0f},
                 {0.727811f, 0.626959f, 0.626959f, 1.0f},
                  0.2f * 128.0f};

float width = 800, height = 800;
float alpha = 0, delta = 1;
boolean keyStates[256];
float position[4] = {5.0f, 4.0f, 5.0f, 1.0f};
float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float black[4] = {0.05f, 0.05f, 0.05f, 1.0f};
float global_ambient[4] = {0.95f, 0.95f, 0.95f, 1.0f};

void lighting(){
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.06f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.01f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01f);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

int init(){
    glClearColor(0.8f, 0.8f, 0.8f, 0.8f);
    glEnable(GL_DEPTH_TEST);
    lighting();
}

void update(){
    alpha++;
    if(keyStates[GLUT_KEY_UP] == TRUE) delta = delta * 1.01f;
    if(keyStates[GLUT_KEY_DOWN] == TRUE) delta = delta * (1/1.01f);
}

void desenha(){
    glMatrixMode(GL_MODELVIEW);
    glRotatef(alpha, 0, 1, 0);
    glutSolidTeapot(1.5f);
}

void desenhaPlano(){
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    glRecti(398, 0, 402, 800);
    glRecti(0, 398, 800, 402);
}

void updateMaterial(Material material){
    glMaterialfv(GL_FRONT, GL_AMBIENT, material.ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material.kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material.ks);
    glMaterialf(GL_FRONT, GL_SHININESS, material.ns);
}

void RenderString(float x, float y, void *font, const char* string){  
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);
    glutBitmapString(font, string);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    updateMaterial(Ruby);
    update();

    glMatrixMode(GL_MODELVIEW);
    glViewport(0, height/2, width/2, height/2);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 2.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0/delta, 3.0/delta, -3.0/delta, 3.0/delta, -10.0, 100.0); 
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    desenha();
    
    glViewport(width/2, height/2, width/2, height/2);
    glLoadIdentity();
    gluLookAt(2.0, 0.0, 0.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0/delta, 3.0/delta, -3.0/delta, 3.0/delta, -10.0, 100.0);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    desenha();
    
    glViewport(0, 0, width/2, height/2);
    glLoadIdentity();
    gluLookAt(0.0, 2.0, 0.0,
              0.0, 0.0, 0.0,
              0.0, 0.0, -1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0/delta, 3.0/delta, -3.0/delta, 3.0/delta, -10.0, 100.0); 
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    desenha();

    glViewport(width/2, 0, width/2, height/2);
    glLoadIdentity();
    gluLookAt(3.0, 2.5, 6.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(atan(tan(50.0 * 3.14159 / 360.0) / delta) * 360.0 / 3.14159, 1, 0.1, 100.0);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    desenha();
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 800);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
    glClear(GL_DEPTH_BUFFER_BIT);
    desenhaPlano();
    RenderString(355.0f, 420.0f, GLUT_BITMAP_TIMES_ROMAN_24, "XY");
    RenderString(760.0f, 420.0f, GLUT_BITMAP_TIMES_ROMAN_24, "YZ");
    RenderString(355.0f, 20.0f, GLUT_BITMAP_TIMES_ROMAN_24, "XZ");
    RenderString(680.0f, 20.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Perspectiva");
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glutSwapBuffers();
}

void keyPressed_special(int key, int x, int y){
    keyStates[key] = TRUE;
}

void keyUp_special(int key, int x, int y){
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
    glutInitWindowSize(width, height);
    glutCreateWindow("Projeto CG 2 - Questao 2");

    init();

    glutSpecialUpFunc(keyUp_special);
    glutSpecialFunc(keyPressed_special);
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
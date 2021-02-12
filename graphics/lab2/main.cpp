#include <GL/glut.h>
#include <iostream>

GLfloat angle = 0.0;

GLfloat squareOffsetX = 0.0;
GLfloat squareOffsetY = 0.0;

void rotate() {
    angle += 2.0;
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    glTranslatef(0.25, 0.25, 0.0);
    glRotatef(angle,0.0,0.0,1.0);
    glTranslatef(-0.25, -0.25, 0.0);

    glBegin(GL_POLYGON);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(0, 0, 0.0);
    glVertex3f(0.5, 0, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
    glVertex3f(0, 0.5, 0.0);
    glEnd();

    glPopMatrix();

    glPushMatrix();

    glTranslatef(squareOffsetX, squareOffsetY, 0.0);

    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0,1.0);
    glVertex3f(-0.75, -0.75, 0.0);
    glVertex3f(-0.5, -0.75, 0.0);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(-0.75, -0.5, 0.0);
    glEnd();

    glPushMatrix();

    glutSwapBuffers();
}

void keyHandler(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
        case 'w':
            squareOffsetY += 0.01;
            glutPostRedisplay();
            break;
        case 's':
            squareOffsetY -= 0.01;
            glutPostRedisplay();
            break;
        case 'a':
            squareOffsetX -= 0.01;
            glutPostRedisplay();
            break;
        case 'd':
            squareOffsetX += 0.01;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

void mouseHandler(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) glutIdleFunc(rotate);
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN) glutIdleFunc(nullptr);
            break;
        default:
            break;
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab 2");

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutDisplayFunc(display);

    glutKeyboardFunc(keyHandler);
    glutMouseFunc(mouseHandler);

    glutMainLoop();

    return 0;
}

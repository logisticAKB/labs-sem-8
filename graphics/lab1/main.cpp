#include <GL/glut.h>

GLfloat width = 1024;
GLfloat height = 768;

void onReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    double aspect = (double)w / h;
//glOrtho() определяет координатную систему .
    glOrtho(-2.0 * aspect, 2.0 * aspect, -2.0, 2.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

//    glPushMatrix();

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.25, 0.25, 0.0); // bottom left
    glVertex3f(0.75, 0.25, 0.0); // bottom right
    glVertex3f(0.75, 0.75, 0.0); // top right
    glVertex3f(0.25, 0.75, 0.0); // top left
    glEnd();

//    glPopMatrix();

    glutSwapBuffers();
}

void keyHandler(unsigned char key, int x, int y) {
    if (key == 27) exit(0);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab 1");

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutDisplayFunc(display);

    glutKeyboardFunc(keyHandler);
    glutReshapeFunc(onReshape);

    glutMainLoop();

    return 0;
}

#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.25, 0.25, 0.0); // bottom left
    glVertex3f(0.75, 0.25, 0.0); // bottom right
    glVertex3f(0.75, 0.75, 0.0); // top right
    glVertex3f(0.25, 0.75, 0.0); // top left
    glEnd();

    glFlush();
}

void keyHandler(unsigned char key, int x, int y) {
    if (key == 27) exit(0);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab 1");

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutDisplayFunc(display);

    glutKeyboardFunc(keyHandler);

    glutMainLoop();

    return 0;
}

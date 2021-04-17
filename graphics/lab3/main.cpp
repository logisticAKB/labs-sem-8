#include <GL/glut.h>
#include <iostream>
#include <cmath>

GLfloat eyeX = 0.0f;
GLfloat eyeY = 0.0f;
GLfloat eyeZ = -8.0f;

GLfloat r = eyeZ * -1.0f;

GLfloat speed = 40.0f;

void glInit() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Nice perspective corrections
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.0f);
    gluLookAt(eyeX, eyeY, eyeZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f);
//    glTranslatef(0.0f, 0.0f, 7.0f);

    glBegin(GL_QUADS);

    // Top face (y = 1.0f)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f( 1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f,  1.0f);
    glVertex3f( 1.0f, 1.0f,  1.0f);

    // Bottom face (y = -1.0f)
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);

    // Front face  (z = 1.0f)
    glVertex3f( 1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, 1.0f);

    // Back face (z = -1.0f)
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);

    // Left face (x = -1.0f)
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);

    // Right face (x = 1.0f)
    glVertex3f(1.0f,  1.0f, -1.0f);
    glVertex3f(1.0f,  1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height) {
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);

//    glOrtho(-2.0 * aspect, 2.0 * aspect, -2.0, 2.0, 0.1f, 100.0f);

}

void keyHandler(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
        case 'w':
            eyeY += 0.01 * speed;
            if (eyeY > r) eyeY -= r;
            if (std::abs(std::abs(eyeY) - r) < 0.0001) {
                eyeZ = 0.0f;
            } else {
                eyeZ = std::sqrt(r*r - eyeY*eyeY);
            }
            break;
        case 's':
            eyeY -= 0.01 * speed;
            if (eyeY < -r) eyeY += r;
            if (std::abs(std::abs(eyeY) - r) < 0.0001) {
                eyeZ = 0.0f;
            } else {
                eyeZ = std::sqrt(r*r - eyeY*eyeY);
            }
            break;
        case 'a':
            eyeX -= 0.01 * speed;
            if (eyeX < -r) eyeX += r;
            if (std::abs(std::abs(eyeX) - r) < 0.0001) {
                eyeZ = 0.0f;
            } else {
                eyeZ = std::sqrt(r*r - eyeX*eyeX);
            }
            break;
        case 'd':
            eyeX += 0.01 * speed;
            if (eyeX > r) eyeX -= r;
            if (std::abs(std::abs(eyeX) - r) < 0.0001) {
                eyeZ = 0.0f;
            } else {
                eyeZ = std::sqrt(r*r - eyeX*eyeX);
            }
//            std::cout << eyeX << std::endl;
//            std::cout << eyeZ << std::endl;
            break;
        default:
            break;

    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab 3");

    glInit();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyHandler);

    glutMainLoop();

    return 0;
}

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>

void Draw();

int getRandomValue() {
    return (rand() % (500 - 100 + 1)) + 100; // Generates a number between 100 and 500
}

int main(int argc, char **argv) {
    // OpenGL Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("2D Transformation (Translation)");
    glClearColor(1.0, 1.0, 1.0, 0);
    glColor3f(0, 0, 0);
    gluOrtho2D(0, 640, 0, 480);
    glutDisplayFunc(Draw);
    glutMainLoop();

    return 0;
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glVertex2d(200, 200);
    glColor3f(1, 7, 0);
    for(int i = 0; i < 100000; i++ ){
        glVertex2d(getRandomValue(), getRandomValue());
    }
    glEnd();
    glFlush();
}



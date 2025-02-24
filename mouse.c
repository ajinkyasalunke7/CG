
#include <GL/glut.h>
#include <stdio.h>

// Window dimensions
int windowWidth = 800, windowHeight = 600;

// Function to handle mouse click events
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Convert screen coordinates to OpenGL coordinates
        float xPos = (float)x / windowWidth * 2.0f - 1.0f;
        float yPos = 1.0f - (float)y / windowHeight * 2.0f;

        printf("Mouse clicked at screen coordinates (%d, %d)\n", x, y);
        printf("Converted to OpenGL coordinates (%f, %f)\n", xPos, yPos);
    }
}

// Function to handle window resizing
void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Function to render the scene (empty in this example)
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Mouse Click Example");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseClick);

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glutMainLoop();
    return 0;
}

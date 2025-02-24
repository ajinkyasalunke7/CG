/*******************************************************
 * File: dda.c
 * Author: Ajinkya V. Salunke
 * Date: 2025-01-17
 * Description: This program is to draw DDA Line from mouse clicks
 * Version: 1.0
 * License: MIT License
 *
 * Change Log:
 * 2025-01-17 - Initial version of the program.
 *******************************************************/

#include <stdio.h>
#include <GL/glut.h>
#include <unistd.h>

// Global variable declaration
int x1, ya, x2, y2, flag = 0;
int windowWidth = 640, windowHeight = 480;

// Function declaration
void Draw();
int Round(float num);
void DdaLine(int x1, int ya, int x2, int y2);
void mouseClick(int button, int state, int x, int y);

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Mouse click DDA");
    glClearColor(1.0, 1.0, 1.0, 0);
    glColor3f(0.0, 0.0, 0.0);
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glutMouseFunc(mouseClick);
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}

void Draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    DdaLine(x1, ya, x2, y2);
    glEnd();
    glFlush();
}

void DdaLine(int x1, int ya, int x2, int y2){
    int dx = x2 - x1;
    int dy = y2 - ya;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float Xinc = dx / (float)(steps);
    float Yinc = dy / (float)(steps);

    float x = x1;
    float y = ya;

    glVertex2d(x, y);

    for(int i = 0; i < steps; i++){
        x += Xinc;
        y += Yinc;
        glVertex2d(Round(x), Round(y));
    }
}

int Round(float num){
    return (int)(num);
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if(flag == 0) {
            x1 = x;
            ya = windowHeight - y;
            flag = 1;
            printf("%d, %d\n", x1, ya);
        } else {
            x2 = x;
            y2 = windowHeight - y;
            printf("%d, %d\n", x2, y2);
            flag = 0;
            glutPostRedisplay();
        }
    }
}

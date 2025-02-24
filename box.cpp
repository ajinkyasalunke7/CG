#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stack>

int xa, ya, xb, yb;

struct Point {
    int x, y;
};

void Bline(int xa, int ya, int xb, int yb) {
    int dx, dy, d;
    int c, r, f;

    dx = xb - xa;
    dy = yb - ya;

    glBegin(GL_POINTS);
    if (abs(dx) > abs(dy)) {
        d = 2 * abs(dy) - abs(dx);

        if (dx > 0) {
            c = xa;
            r = ya;
            f = xb;
        } else {
            c = xb;
            r = yb;
            f = xa;
        }

        while (c <= f) {
            glVertex2d(c, r);

            if (d < 0) {
                c = c + 1;
                d = d + 2 * abs(dy);
            } else {
                c = c + 1;
                if ((dx > 0 && dy > 0) || (dx < 0 && dy < 0)) {
                    r = r + 1;
                } else {
                    r = r - 1;
                }
                d = d + 2 * abs(dy) - 2 * abs(dx);
            }
        }
    } else {
        d = 2 * abs(dx) - abs(dy);

        if (dy > 0) {
            c = xa;
            r = ya;
            f = yb;
        } else {
            c = xb;
            r = yb;
            f = ya;
        }

        while (r <= f) {
            glVertex2d(c, r);

            if (d < 0) {
                r = r + 1;
                d = d + 2 * abs(dx);
            } else {
                r = r + 1;
                if ((dx > 0 && dy > 0) || (dx < 0 && dy < 0)) {
                    c = c + 1;
                } else {
                    c = c - 1;
                }
                d = d + 2 * abs(dx) - 2 * abs(dy);
            }
        }
    }
    glEnd();
    glFlush();
}

void delay(float ms) {
    clock_t goal = ms + clock();
    while (goal > clock());
}

void BoundaryFillFunc(int x, int y, float fillColor[], float boundaryColor[]) {
    std::stack<Point> pixelStack;
    pixelStack.push({x, y});

    float currentColor[3];

    while (!pixelStack.empty()) {
        Point p = pixelStack.top();
        pixelStack.pop();

        glReadPixels(p.x, p.y, 1, 1, GL_RGB, GL_FLOAT, currentColor);

        // Check if the current pixel is neither boundary nor already filled
        if ((fabs(currentColor[0] - boundaryColor[0]) > 0.01 ||
             fabs(currentColor[1] - boundaryColor[1]) > 0.01 ||
             fabs(currentColor[2] - boundaryColor[2]) > 0.01) &&
            (fabs(currentColor[0] - fillColor[0]) > 0.01 ||
             fabs(currentColor[1] - fillColor[1]) > 0.01 ||
             fabs(currentColor[2] - fillColor[2]) > 0.01)) {

            glColor3f(fillColor[0], fillColor[1], fillColor[2]);
            glBegin(GL_POINTS);
            glVertex2d(p.x, p.y);
            glEnd();
            glFlush();

            // Push neighboring pixels onto the stack
            pixelStack.push({p.x + 1, p.y}); // Right
            pixelStack.push({p.x - 1, p.y}); // Left
            pixelStack.push({p.x, p.y + 1}); // Up
            pixelStack.push({p.x, p.y - 1}); // Down
        }
    }
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a square using Bresenham's Line Algorithm
    glColor3f(0, 1, 0); // Green for boundary
    Bline(100, 100, 100, 300);
    Bline(100, 100, 300, 100);
    Bline(100, 300, 300, 300);
    Bline(300, 300, 300, 100);

    // Boundary Fill Algorithm
    float boundaryColor[] = {0, 1, 0};  // Green boundary
    float fillColor[] = {0, 0, 1};      // Blue fill color
    BoundaryFillFunc(150, 150, fillColor, boundaryColor);
}

int main(int argc, char **argv) {
    xa = 100;
    ya = 100;
    xb = 300;
    yb = 300;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 560);
    glutCreateWindow("Boundary Fill Algorithm");

    glClearColor(1.0, 1.0, 1.0, 0); 
    glColor3f(0, 1, 0); 
    gluOrtho2D(0, 640, 0, 560); 

    glutDisplayFunc(Draw);
    glutMainLoop();

    return 0;
}

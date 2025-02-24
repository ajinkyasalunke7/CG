#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int xa = 100, ya = 100, xb = 500, yb = 500;

void Bline(int xa, int ya, int xb, int yb)
{
    int dx, dy, d;
    int c, r, f;

    dx = abs(xb - xa);
    dy = abs(yb - ya);

    int sx = (xb >= xa) ? 1 : -1; // Step for x
    int sy = (yb >= ya) ? 1 : -1; // Step for y

    if (dx > dy)
    {
        d = 2 * dy - dx;
        c = xa;
        r = ya;
        f = xb;

        while (c != f)
        {
            glVertex2d(c, r);
            if (d < 0)
            {
                d += 2 * dy;
            }
            else
            {
                r += sy;
                d += 2 * (dy - dx);
            }
            c += sx;
        }
    }
    else
    {
        d = 2 * dx - dy;
        c = ya;
        r = xa;
        f = yb;

        while (c != f)
        {
            glVertex2d(r, c);
            if (d < 0)
            {
                d += 2 * dx;
            }
            else
            {
                r += sx;
                d += 2 * (dx - dy);
            }
            c += sy;
        }
    }
}

void DrawChessboard(int num_of_boxes)
{
    int yinc = (yb - ya) / num_of_boxes;
    int xinc = (xb - xa) / num_of_boxes;

    for (int i = 0; i <= num_of_boxes; i++)
    {
        Bline(xa, ya + i * yinc, xb, ya + i * yinc); // Horizontal lines
        Bline(xa + i * xinc, ya, xa + i * xinc, yb); // Vertical lines
    }
}

void BoundaryFillFunc(int x, int y, float fillColor[], float boundaryColor[])
{
    float currentColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, currentColor);

    // Floating-point tolerance
    float epsilon = 0.01f;
    
    // Check if the current pixel is neither boundary nor already filled
    if ((fabs(currentColor[0] - boundaryColor[0]) > epsilon ||
         fabs(currentColor[1] - boundaryColor[1]) > epsilon ||
         fabs(currentColor[2] - boundaryColor[2]) > epsilon) &&
        (fabs(currentColor[0] - fillColor[0]) > epsilon ||
         fabs(currentColor[1] - fillColor[1]) > epsilon ||
         fabs(currentColor[2] - fillColor[2]) > epsilon))
    {
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);
        glBegin(GL_POINTS);
        glVertex2d(x, y);
        glEnd();
        glutSwapBuffers();

        // Recursive calls in 4 directions
        BoundaryFillFunc(x + 1, y, fillColor, boundaryColor); // Right
        BoundaryFillFunc(x - 1, y, fillColor, boundaryColor); // Left
        BoundaryFillFunc(x, y + 1, fillColor, boundaryColor); // Up
        BoundaryFillFunc(x, y - 1, fillColor, boundaryColor); // Down
    }
}

void Draw()
{
    float color[3] = {1, 0, 0};       // Red fill color
    float boundaryColor[3] = {0, 0, 0}; // Black boundary color

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    DrawChessboard(8); // Draw the chessboard
    glEnd();
    glutSwapBuffers();

    BoundaryFillFunc(200, 200, color, boundaryColor);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Use Double Buffer
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 560);
    glutCreateWindow("Chessboard and Boundary Fill");

    glClearColor(1.0, 1.0, 1.0, 0); // White Background
    glColor3f(0, 0, 0);             // Black for chessboard
    gluOrtho2D(0, 640, 0, 560);

    glutDisplayFunc(Draw);
    glutMainLoop();

    return 0;
}

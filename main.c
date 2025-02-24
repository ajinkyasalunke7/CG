#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>

void Draw();
void BresLine(int x1, int y1, int x2, int y2);
void PrintMatrix(int given_array[3][3], int range);

int input[3][3]; // Matrix to hold points in homogeneous coordinates
int translation_matrix[3][3]; // Translation matrix
int transformed[3][3]; // Output matrix after translation
int tx, ty;

int main(int argc, char **argv) {

    // Perform translation
    for (int i = 0; i < 3; i++) {
        transformed[0][i] = input[0][i] + tx; // x' = x + tx
        transformed[1][i] = input[1][i] + ty; // y' = y + ty
        transformed[2][i] = 1;
    }

    // OpenGL Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 650);
    glutCreateWindow("2D Transformation (Translation)");
    glClearColor(1.0, 1.0, 1.0, 0);
    glColor3f(0, 0, 0);
    gluOrtho2D(0, 640, 0, 580);
    glutDisplayFunc(Draw);
    glutMainLoop();

    return 0;
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);

    // Draw Axes
    BresLine(100,100,200,400); // X-axis
    BresLine(100, 100, 400, 100); // Y-axis
    BresLine(200, 400, 500, 400); // Y-axis
    BresLine(500, 400, 400, 100);

    glColor3f(0, 1, 0);
        
    BresLine(100 + 50 , 100 + 50, 200 + 50 , 400 + 50); 
    BresLine(100 + 50 , 100 + 50, 400 + 50 , 100 + 50);
    BresLine(200 + 50 , 400 + 50, 500 + 50 , 400 + 50); 
    BresLine(500 + 50 , 400 + 50, 400 + 50 , 100 + 50);
    

    glEnd();
    glFlush();
}

void BresLine(int xa, int ya, int xb, int yb) {
    int dx = abs(xb - xa);
    int dy = abs(yb - ya);
    int sx = (xa < xb) ? 1 : -1;
    int sy = (ya < yb) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        glVertex2d(xa, ya);

        if (xa == xb && ya == yb) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            xa += sx;
        }
        if (e2 < dx) {
            err += dx;
            ya += sy;
        }
    }
}

void PrintMatrix(int given_array[3][3], int range) {
    for (int i = 0; i < range; i++) {
        for (int j = 0; j < range; j++) {
            printf("%d ", given_array[i][j]);
        }
        printf("\n");
    }
}

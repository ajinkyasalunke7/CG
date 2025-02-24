#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h> // For abs()
#include <windows.h>

void Draw();
void BresLine(int x1, int y1, int x2, int y2);
void PrintMatrix(int given_array[3][3], int range);

void delay(int n) {
    usleep(n * 1000); // Converts n milliseconds to microseconds
}

/*
bool checkColor(float b[3], float f[3]){
    for(int =  0; i < 3; i++){
        if(b[i] != f[i]){
            return true;
        }2
    }
    return false;
}
*/

void BoundaryFill(int x, int y, float bcol[3], float fcol[3]) {
    float current_color[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, current_color);

    // Check if the pixel is not already filled and not a boundary
    if ((current_color[0] != fcol[0] || current_color[1] != fcol[1] || current_color[2] != fcol[2]) &&
        (current_color[0] != bcol[0] || current_color[1] != bcol[1] || current_color[2] != bcol[2])) {

        glBegin(GL_POINTS);
        glColor3f(fcol[0], fcol[1], fcol[2]);
        glVertex2i(x, y);
        printf("%d, %d", x, y);
        glEnd();
        glFlush(); // Ensure pixel is drawn

        //delay(3); // Small delay for visualization

        // Recursive calls for 4-connected pixels
        BoundaryFill(x + 1, y, bcol, fcol);
        BoundaryFill(x - 1, y, bcol, fcol);
        BoundaryFill(x, y + 1, bcol, fcol);
        BoundaryFill(x, y - 1, bcol, fcol);
    }
}

int output_mat[3][3] = {{150, 450, 300}, {150, 150, 300}, {1, 1, 1}};
int color[3];

int main(int argc, char **argv) {
    printf("Enter color to fill (RGB values between 0 and 255):\n");
    for (int i = 0; i < 3; i++) {
        printf("Enter color[%d]: ", i);
        scanf("%d", &color[i]);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Bresenham Line Drawing");

    glClearColor(1.0, 1.0, 1.0, 0); // White background
    glColor3f(0, 0, 0); // Black for boundary
    gluOrtho2D(0, 640, 480, 0); // Set coordinate system

    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < 3; i++) {
        int next = (i + 1) % 3;
        BresLine(output_mat[0][i], output_mat[1][i], output_mat[0][next], output_mat[1][next]);
    }

    float boundaryColor[3] = {0.0f, 0.0f, 0.0f};
    float fillColor[3] = {(float)color[0] / 255.0f, (float)color[1] / 255.0f, (float)color[2] / 255.0f}; // User input fill color

    BoundaryFill(200, 200, boundaryColor, fillColor);
    glFlush();
}

void BresLine(int xa, int ya, int xb, int yb) {
    int dx = abs(xb - xa), dy = abs(yb - ya);
    int sx = (xa < xb) ? 1 : -1;
    int sy = (ya < yb) ? 1 : -1;
    int err = dx - dy;

    glBegin(GL_POINTS);
    while (1) {
        glVertex2i(xa, ya);
        if (xa == xb && ya == yb) break;

        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; xa += sx; }
        if (e2 < dx) { err += dx; ya += sy; }
    }
    glEnd();
}

void PrintMatrix(int given_array[3][3], int range) {
    printf("Matrix Coordinates:\n");
    for (int i = 0; i < range; i++) {
        for (int j = 0; j < range; j++) {
            printf("%d ", given_array[i][j]);
        }
        printf("\n");
    }
}

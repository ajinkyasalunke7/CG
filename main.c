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
    printf("Enter elements for matrix A (3x3) representing points in homogeneous coordinates:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 2) {
                input[2][j] = 1; // Homogeneous coordinate always 1
            } else {
                printf("Enter element A[%d][%d]: ", i, j);
                scanf("%d", &input[i][j]);
            }
        }
    }

    printf("Enter translation factor of X: ");
    scanf("%d", &tx);
    printf("Enter translation factor of Y: ");
    scanf("%d", &ty);

    // Initialize translation matrix
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            translation_matrix[i][j] = (i == j) ? 1 : 0;
        }
    }
    translation_matrix[0][2] = tx;
    translation_matrix[1][2] = ty;

    // Perform translation
    for (int i = 0; i < 3; i++) {
        transformed[0][i] = input[0][i] + tx; // x' = x + tx
        transformed[1][i] = input[1][i] + ty; // y' = y + ty
        transformed[2][i] = 1; // Homogeneous coordinate remains 1
    }

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

    // Draw Axes
    BresLine(0, 240, 640, 240); // X-axis
    BresLine(320, 0, 320, 480); // Y-axis

    // Print Matrices
    printf("Original Points:\n");
    PrintMatrix(input, 3);
    printf("Translation Matrix:\n");
    PrintMatrix(translation_matrix, 3);
    printf("Transformed Points:\n");
    PrintMatrix(transformed, 3);

    // Draw Original Triangle
    glColor3f(0, 0, 0); // Black color
    for (int i = 0; i < 3; i++) {
        int next = (i + 1) % 3;
        BresLine(input[0][i], input[1][i], input[0][next], input[1][next]);
    }

    // Draw Translated Triangle
    glColor3f(1, 0, 0); // Red color for transformed shape
    for (int i = 0; i < 3; i++) {
        int next = (i + 1) % 3;
        BresLine(transformed[0][i], transformed[1][i], transformed[0][next], transformed[1][next]);
    }

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

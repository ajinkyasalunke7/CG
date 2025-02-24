#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>

void Draw();
void BresLine(int x1, int y1, int x2, int y2);
void PrintMatrix(int given_array[3][3], int range);

int tx, ty;
int input[3][3] = {
    {150, 450, 300}, 
    {150, 150, 300}, 
    {1, 1, 1}
};
int translation_matrix[3][3];
// int translation_matrix[3][3] = {
//     {1, 0, 100},  // Move 100 units in x-direction
//     {0, 1, 50},   // Move 50 units in y-direction
//     {0, 0, 1}
// };
int transformed[3][3];

int main(int argc, char **argv) {
    printf("Enter translation factor of X: ");
   scanf("%d", & tx);
   printf("Enter translation factor of Y: ");
   scanf("%d", & ty);
      for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
         if (i == j) {
            translation_matrix[i][j] = 1;
         } else {
            translation_matrix[i][j] = 0;
         }
      }
   }
   translation_matrix[0][2] = tx;
   translation_matrix[1][2] = ty;
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

    // Print Original Points
    printf("Before Translation:\n");
    PrintMatrix(input, 3);

    // Apply Translation
    for (int i = 0; i < 3; i++) {
        transformed[0][i] = input[0][i] + translation_matrix[0][2]; // x' = x + tx
        transformed[1][i] = input[1][i] + translation_matrix[1][2]; // y' = y + ty
        transformed[2][i] = 1; // Homogeneous coordinate remains 1
    }

    // Print Translated Points
    // printf("After Translation:\n");
    // PrintMatrix(input 3);
    // PrintMatrix(translation_matrix, 3);

    PrintMatrix(transformed, 3);

    // Draw Original Triangle
    for (int i = 0; i < 3; i++) {
        int next = (i + 1) % 3;
        BresLine(input[0][i], input[1][i], input[0][next], input[1][next]);
    }

    // Draw Translated Triangle
    glColor3f(1, 0, 0); // Change color to red
    for (int i = 0; i < 3; i++) {
        int next = (i + 1) % 3;
        printf("%d %d %d %d",transformed[0][i], transformed[1][i],transformed[0][next],transformed[1][next]);
        BresLine(transformed[0][i], transformed[1][i], transformed[0][next], transformed[1][next]);
    }

    glEnd();
    glFlush();
}

void BresLine(int xa, int ya, int xb, int yb) {
    int dx = xb - xa, dy = yb - ya, d;
    int x = xa, y = ya;
    int step_x = (dx > 0) ? 1 : -1;
    int step_y = (dy > 0) ? 1 : -1;
    
    dx = abs(dx);
    dy = abs(dy);

    if (dx > dy) {
        d = 2 * dy - dx;
        for (int i = 0; i < dx; i++) {
            glVertex2d(x, y);
            if (d >= 0) {
                y += step_y;
                d -= 2 * dx;
            }
            x += step_x;
            d += 2 * dy;
        }
    } else {
        d = 2 * dx - dy;
        for (int i = 0; i < dy; i++) {
            glVertex2d(x, y);
            if (d >= 0) {
                x += step_x;
                d -= 2 * dy;
            }
            y += step_y;
            d += 2 * dx;
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

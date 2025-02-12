#include <GL/freeglut_std.h>

#include <GL/gl.h>

#include <stdio.h>

#include <GL/glut.h>

void Draw();
void BresLine(int x1, int y1, int x2, int y2);
void PrintMatrix(int given_array[3][3], int range);

int input[3][3];

int main(int argc, char ** argv) {
   glutInit( & argc, argv);
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

    int input[3][3] = {
      {
         100,
         300,
         200
      },
      {
         100,
         300,
         200
      },
      {
         1,
         1,
         1
      }
   };

    PrintMatrix(input, 3);
    glColor3f(1, 0, 0);
     glColor3f(1, 0, 0); // Change color to red
    for (int i = 0; i < 3; i++) {
        int next = (i + 1) % 3;
        printf("%d %d %d %d",input[0][i], input[1][i],input[0][next],input[1][next]);
        BresLine(input[0][i], input[1][i],input[0][next],input[1][next]);
    }

   glEnd();
   glFlush();
}

void BresLine(int xa, int ya, int xb, int yb) {
   int dx, dy, d;
   int c, r, f;

   dx = xb - xa;
   dy = yb - ya;

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

      while (f > c) {
         if (d < 0) {
            c = c + 1;
            d = d + 2 * abs(dy);
         } else {
            c = c + 1;

            if (dx > 0 && dy > 0 || dx < 0 && dy < 0) {
               r = r + 1;
            } else {
               r = r - 1;
            }
            d = d + 2 * abs(dy) - 2 * abs(dx);
         }
         glVertex2d(c, r);

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

      while (f > r) {
         if (d < 0) {
            r = r + 1;
            d = d + 2 * abs(dx);
         } else {
            r = r + 1;

            if (dx > 0 && dy > 0 || dx < 0 && dy < 0) {
               c = c + 1;
            } else {
               c = c - 1;
            }
            d = d + 2 * abs(dx) - 2 * abs(dy);
         }
         glVertex2d(c, r);

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
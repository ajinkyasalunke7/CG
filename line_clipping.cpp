#include <iostream>

#include <GL/glut.h>

using namespace std;

int xa, ya, xb, yb, Xmin, Ymin, Xmax, Ymax;
// int xa = 15, ya = 100;
// int xb = 75, yb = 330;
// int Xmin = 10, Ymin = 30;
// int Xmax = 200, Ymax = 300;

// int xa = 245, ya = 320;    
// int xb = 180, yb = 150;  
// int Xmin = 50, Ymin = 60, Xmax = 600, Ymax = 450;

int result_arr_1[2];
int result_arr_2[2];

float m;

void BresLine(int xa, int ya, int xb, int yb) {
	int dx = abs(xb - xa);
	int dy = abs(yb - ya);
	int sx = (xa < xb) ? 1 : -1;
	int sy = (ya < yb) ? 1 : -1;
	int err = dx - dy;

	while (1) {
	  glVertex2d(xa, ya);

	  if (xa == xb && ya == yb)
		 break;
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

void PrintArray(int arr[], int len) {
	cout << "\n";
	for (int i = 0; i < len; i++) {
	  cout << arr[i] << " ";
	}
}
void getOutCode(int arr[], int x, int y, int Xmin, int Ymin, int Xmax, int Ymax) {
	for (int i = 0; i < 4; i++)
	  arr[i] = 0;

	if (x < Xmin)
	  arr[3] = 1;
	if (x > Xmax)
	  arr[2] = 1;
	if (y < Ymin)
	  arr[1] = 1;
	if (y > Ymax)
	  arr[0] = 1;
}

void drawWindow(int xmin, int ymin, int xmax, int ymax) {
	BresLine(xmin, ymin, xmax, ymin);
	BresLine(xmin, ymax, xmax, ymax);
	BresLine(xmin, ymin, xmin, ymax);
	BresLine(xmax, ymin, xmax, ymax);
}

void getXY(int arr[], int x, int y, float m, int Xmin, int Ymin, int Xmax, int Ymax, int result_arr[]) {
	int new_x = x, new_y = y; 
	
	if (arr[0] == 1) { 
		new_y = Ymax;
		new_x = x + (Ymax - y) / m;
	} 
	else if (arr[1] == 1) {
		new_y = Ymin;
		new_x = x + (Ymin - y) / m;
	} 
	else if (arr[2] == 1) { 
		new_x = Xmax;
		new_y = y + m * (Xmax - x);
	} 
	else if (arr[3] == 1) {
		new_x = Xmin;
		new_y = y + m * (Xmin - x);
	}

	result_arr[0] = new_x;
	result_arr[1] = new_y;
}

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	BresLine(xa, ya, xb, yb);
	drawWindow(Xmin, Ymin, Xmax, Ymax);

//    BresLine(0, 240, 640, 240); // X-axis
//    BresLine(320, 0, 320, 480); // Y-axis
	
	glColor3f(0, 0, 1);
	cout << "(" << result_arr_1[0] << ", " <<  result_arr_1[1] << ")" << "(" << result_arr_2[0]<< ", " << result_arr_2[1] << ")";
	BresLine(result_arr_1[0], result_arr_1[1], result_arr_2[0], result_arr_2[1]);

	// BresLine(10, 10, 10, 470);
	// BresLine(10, 10, 630, 10);
	// BresLine(630, 10, 630, 470);
	// BresLine(10, 470, 630, 470);

	glEnd();
	glFlush();
}
int main(int argc, char ** argv) {
	int x1, y1;

	cout << "\nEnter xa, ya: ";
	cin >> xa >> ya;
	cout << "\nEnter xb, yb: ";
	cin >> xb >> yb;

	cout << "\nEnter Xmin, Ymin: ";
	cin >> Xmin >> Ymin;
	cout << "\nEnter Xmax, Ymax: ";
	cin >> Xmax >> Ymax;


	m = (float)(yb - ya) / (float)(xb - xa);
	// cout << m;
	int A[4], B[4];
	getOutCode(A, xa, ya, Xmin, Ymin, Xmax, Ymax);
	getOutCode(B, xb, yb, Xmin, Ymin, Xmax, Ymax);

	int flag = 0;
	for (int i = 0; i < 4; i++) {
	  if (A[i] == 1 || B[i] == 1) {
		 flag = 1;
		 break;
	  }
	}
	if (flag == 1) {
	  cout << "\nRejected or Partially accepted!";

	  int flag = 0;
	  for (int i = 0; i < 4; i++) {
		 if (A[i] && B[i]) {
			flag = 1;
		 }
	  }
	  if (flag == 1) {
		 cout << "\nCompletely rejected";
	  } else {
		 cout << "\nPartially accepted";
		 
		 getXY(A, xa, ya, m, Xmin, Ymin, Xmax, Ymax, result_arr_1);
		 getXY(B, xb, yb, m, Xmin, Ymin, Xmax, Ymax, result_arr_2);
		//  BresLine()
	  }
	} else {
	  cout << "Completely inside!";
	  getXY(A, xa, ya, m, Xmin, Ymin, Xmax, Ymax, result_arr_1);
	  getXY(B, xb, yb, m, Xmin, Ymin, Xmax, Ymax, result_arr_2);
	}

	// OpenGL Initialization
	glutInit( & argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1020, 720);
	glutCreateWindow("Line Clipping");
	glClearColor(1.0, 1.0, 1.0, 0);
	glColor3f(0, 0, 0);
	gluOrtho2D(0, 1020, 0, 720);
	glutDisplayFunc(Draw);
	glutMainLoop();

	return 0;
}
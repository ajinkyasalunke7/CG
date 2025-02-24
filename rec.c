#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

int x1, ya, x2, y2;

void Draw();
int Round(int num);
void DdaLine(int x1, int ya, int x2, int y2);

int main(int argc, char **argv){
	printf("Enter starting co-ordinate: ");
	scanf("%d %d", &x1, &ya);
	printf("Enter ending co-ordinate: ");
	scanf("%d %d", &x2, &y2);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(640, 480);
	glutCreateWindow("________Window_______");
	glClearColor(1.0, 1.0, 1.0, 0);
	glColor3f(0.0, 0.0, 0.0);
	gluOrtho2D(0, 640, 0, 480);
	glutDisplayFunc(Draw);
	glutMainLoop();
	return 0;
}

void Draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	for(int i = 0; i < 4; i++){
	DdaLine(x1, y2, x2, y2);
	DdaLine(x1, y2, x1, ya);
	DdaLine(x1, ya, x2, ya);
	DdaLine(x2, ya, x2, y2);
	}
	glEnd();	
	glFlush();
}

void DdaLine(int x1, int ya, int x2, int y2){
	int dx = x2 - x1;
	int dy = y2 - ya;
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	
	float Xinc = dx / (float)(steps);
	float Yinc = dy / (float)(steps);
	
	int x = x1;
	int y = ya;
	
	glVertex2d(x, y);
	
	for(int i = 0; i < steps; i++){
		x += Xinc;
		y += Yinc;
		glVertex2d(Round(x), Round(y));
	}

}

int Round(int num){
	return (int)(num);
}



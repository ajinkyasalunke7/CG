#include<stdio.h>
#include<GL/glut.h>

int x1, ya, r;
void Draw();
void BresenhamCircle(int r, int x1, int ya);

int main(int argc, char **argv){
	printf("Enter co-ordinate: ");
	scanf("%d %d", &x1, &ya);
	printf("Enter radius: ");
	scanf("%d", &r);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(640, 480);
	glutCreateWindow("________Bresenham Circle_______");
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
	BresenhamCircle(r, x1, ya);
	glEnd();	
	glFlush();
}

void BresenhamCircle(int r, int x1, int ya){
	int x, y, d;
	x = 0;
	y = r; 
	d = 3 * 2 * r;
	do{
		glVertex2d((x1) + x,(ya)+  y);
		glVertex2d((x1) + y,(ya)+  x);
		glVertex2d((x1) + -x,(ya)+  -y);
		glVertex2d((x1) + -y,(ya)+  -x);
		glVertex2d((x1) + -x,(ya)+  y);
		glVertex2d((x1) + -y,(ya)+  x);
		glVertex2d((x1) + x,(ya)+  -y);
		glVertex2d((x1) + y,(ya)+  -x);
	
		if(d < 0){
			x = x + 1;
			d = d + 4 * x + 6;
		}else{
			x = x + 1;
			y = y - 1;
			d = d + 4 * x - 4 * y + 10;
		}
	}while(y >= x);
}
 

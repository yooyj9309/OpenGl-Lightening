// Prog23.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include <math.h>
#include <gl/glut.h>

GLfloat vertices[][3] = { { -1.0,-1.0,-1.0 },{ 1.0,-1.0,-1.0 },{ 1.0,1.0,-1.0 },{ -1.0,1.0,-1.0 },
{ -1.0,-1.0, 1.0 },{ 1.0,-1.0, 1.0 },{ 1.0,1.0, 1.0 },{ -1.0,1.0, 1.0 } };
typedef struct {
	GLfloat pos[4];	// position
	GLfloat amb[4];	// ambient
	GLfloat dif[4];	// diffuse
	GLfloat spe[4];	// specular
} Light;

typedef struct {
	GLfloat amb[4];	// ambient
	GLfloat dif[4];	// diffuse
	GLfloat spe[4];	// specular
	GLfloat shi;    // shininess
} Material;

Light light = {
	{ 3.0, 3.0, 3.0, 1.0 },	// position
	{ 1.0, 1.0, 1.0, 1.0 }, // ambient
	{ 1.0, 1.0, 1.0, 1.0 }, // diffuse
	{ 1.0, 1.0, 1.0, 1.0 }, // specular
};

Material mat0 = {
	{ 0.2, 0.2, 0.2, 1.0 }, // ambient
	{ 1.0, 1.0, 1.0, 1.0 }, // diffuse
	{ 1.0, 1.0, 1.0, 1.0 }, // specular
	{ 100.0 }, // shininess
};

Material mat1 = {
	{ 0.2, 0.0, 0.0, 1.0 }, // ambient
	{ 1.0, 0.0, 0.0, 1.0 }, // diffuse
	{ 1.0, 0.0, 0.0, 1.0 }, // specular
	{ 300.0 }, // shininess
};

Material mat2 = {
	{ 0.0, 0.2, 0.0, 1.0 }, // ambient
	{ 0.0, 1.0, 0.0, 1.0 }, // diffuse
	{ 0.0, 1.0, 0.0, 1.0 }, // specular
	{ 100.0 }, // shininess
};

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.5, 0.5, 0.5);
	glOrtho(-5.0, 5.0, -5.0, 5.0, -10.0, 10.0);
	gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_POSITION, light.pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light.amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.spe);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void normal(GLfloat *n)
{
	GLfloat x = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
	if (x > 0.0) for (int i = 0; i<3; i++) n[i] /= x;
}

void polygon(int a, int b, int c, int d)
{
	GLfloat nor[3];

	nor[0] = (vertices[a][0] + vertices[b][0] + vertices[c][0] + vertices[d][0]);
	nor[1] = (vertices[a][1] + vertices[b][1] + vertices[c][1] + vertices[d][1]);
	nor[2] = (vertices[a][2] + vertices[b][2] + vertices[c][2] + vertices[d][2]);
	normal(nor);

	glBegin(GL_POLYGON);
	glNormal3fv(nor);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();
}

void cube()
{
	polygon(0, 3, 2, 1);
	polygon(2, 3, 7, 6);
	polygon(0, 4, 7, 3);
	polygon(1, 2, 6, 5);
	polygon(4, 5, 6, 7);
	polygon(0, 1, 5, 4);
}

void spin_cube()
{
	glutPostRedisplay();
}

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'x') light.pos[0] -= 0.1;
	if (key == 'X') light.pos[0] += 0.1;
	if (key == 'y') light.pos[1] -= 0.1;
	if (key == 'Y') light.pos[1] += 0.1;
	if (key == 'z') light.pos[2] -= 0.1;
	if (key == 'Z') light.pos[2] += 0.1;

	if (key == 'a') { for (int i = 0; i<3; i++) light.amb[i] -= 0.1; }
	if (key == 'A') { for (int i = 0; i<3; i++) light.amb[i] += 0.1; }
	if (key == 'd') { for (int i = 0; i<3; i++) light.dif[i] -= 0.1; }
	if (key == 'D') { for (int i = 0; i<3; i++) light.dif[i] += 0.1; }
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat0.amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat0.dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat0.spe);
	glMaterialf(GL_FRONT, GL_SHININESS, mat0.shi);
	cube();

	//glLoadIdentity();
	glTranslatef(-3.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat1.amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat1.dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat1.spe);
	glMaterialf(GL_FRONT, GL_SHININESS, mat1.shi);
	cube();

	glLoadIdentity();
	glTranslatef(+3.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat2.amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat2.dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat2.spe);
	glMaterialf(GL_FRONT, GL_SHININESS, mat2.shi);
	cube();

	glLoadIdentity();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat0.amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat0.dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat0.spe);
	glMaterialf(GL_FRONT, GL_SHININESS, mat0.shi);
	glTranslatef(light.pos[0], light.pos[1], light.pos[2]);
	glutSolidSphere(0.2, 10, 10);

	glLightfv(GL_LIGHT0, GL_POSITION, light.pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light.amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.dif);

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog24: multiple materials");
	glutIdleFunc(spin_cube);
	glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}

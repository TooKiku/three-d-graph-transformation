#include <gl/glut.h>
#include<stdio.h>
#include <math.h>

int press;

//正方体每个顶点的坐标
float vertex_list[8][3] = {
	-1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	-1.0,  1.0, -1.0,
	1.0,  1.0, -1.0,
	-1.0, -1.0,  1.0,
	1.0, -1.0,  1.0,
	-1.0,  1.0,  1.0,
	1.0,  1.0,  1.0
};
float normal_list[8][3] = {
	-1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	-1.0,  1.0, -1.0,
	1.0,  1.0, -1.0,
	-1.0, -1.0,  1.0,
	1.0, -1.0,  1.0,
	-1.0,  1.0,  1.0,
	1.0,  1.0,  1.0
};
// 正方体每个顶点的颜色
float color[][3] = {
		1.0,1.0,0.0,
		0.0, 1.0, 0.0,
		0.0,1.0,1.0,
		1.0,1.0,1.0,
		1.0,0.0,1.0,
		0.0,0.0,1.0,
		0.0,0.0,0.0,
		1.0,0.0,0.0
};
//正方体每面的个顶点的序号
GLint index_list[][4] = {
	0, 2, 3, 1,
	0, 4, 6, 2,
	0, 1, 5, 4,
	4, 5, 7, 6,
	1, 3, 7, 5,
	2, 6, 7, 3,
};
void Rotate(double angle, int check)
{
	double rad = angle * 3.1415926 / 180;
	float temp[8][3] = {};
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = vertex_list[i][j];
		}
	// 绕X轴旋转
	if (check == 1)
	{
		for (int i = 0; i < 8; i++)
		{
			vertex_list[i][1] = cos(rad) * temp[i][1] - sin(rad) * temp[i][2];
			vertex_list[i][2] = sin(rad) * temp[i][1] + cos(rad) * temp[i][2];
		}
	}
	// 绕Y轴旋转
	if (check == 2)
	{
		for (int i = 0; i < 8; i++)
		{
			vertex_list[i][0] = cos(rad) * temp[i][0] + sin(rad) * temp[i][2];
			vertex_list[i][2] = -sin(rad) * temp[i][0] + cos(rad) * temp[i][2];
		}
	}
	// 绕Z轴旋转
	if (check == 3)
	{
		for (int i = 0; i < 8; i++)
		{
			vertex_list[i][0] = cos(rad) * temp[i][0] - sin(rad) * temp[i][1];
			vertex_list[i][1] = sin(rad) * temp[i][0] + cos(rad) * temp[i][1];
		}
	}
}
void Translate(double distance, int check)
{
	float temp[8][3] = {};
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = vertex_list[i][j];
		}
	// 绕X轴平移
	if (check == 1)
	{
		for (int i = 0; i < 8; i++)
		{
			vertex_list[i][0] = temp[i][0] + distance;
		}
	}
	// 绕Y轴平移
	if (check == 2)
	{
		for (int i = 0; i < 8; i++)
		{
			vertex_list[i][1] = temp[i][1] + distance;
		}
	}
	// 绕Z轴平移
	if (check == 3)
	{
		for (int i = 0; i < 8; i++)
		{
			vertex_list[i][2] = temp[i][2] + distance;
		}
	}
}
void Scale(double size)
{
	float temp[8][3] = {};
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = vertex_list[i][j];
		}
	// 缩放
	for (int i = 0; i < 8; i++)
	{
		vertex_list[i][0] = temp[i][0] * size;
		vertex_list[i][1] = temp[i][1] * size;
		vertex_list[i][2] = temp[i][2] * size;
	}
}

//画立方体
void Cube()
{
	glBegin(GL_QUADS);
	glTranslatef(2, 2, 2);//起始点的位置
	for (int i = 0; i < 6; ++i)         // 有六个面，循环六次
		for (int j = 0; j < 4; ++j)     // 每个面有四个顶点，循环四次
		{
			glColor3f(color[index_list[i][j]][0], color[index_list[i][j]][1], color[index_list[i][j]][2]);
			glVertex3fv(vertex_list[index_list[i][j]]);//绘制顶点

		}
	glEnd();
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//绘制立方体
	glTranslatef(-2, -2, -12);//平移
	if (press == 1)
		Rotate(0.05, 1);
	if (press == 2)
		Rotate(0.05, 2);
	if (press == 3)
		Rotate(0.05, 3);
	if (press == 4)
		Translate(-0.001, 1);
	if (press == 5)
		Translate(0.001, 1);
	if (press == 6)
		Translate(0.001, 2);
	if (press == 7)
		Translate(-0.001, 2);
	if (press == 8)
		Translate(0.001, 3);
	if (press == 9)
		Translate(-0.001, 3);
	if (press == 10)
		Scale(1.0001);
	if (press == 11)
		Scale(0.9999);
	if (press == 12)
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 3; j++)
			{
				vertex_list[i][j] = normal_list[i][j];
			}
	//Translate(-0.001, 1);
	Cube();
	glEnable(GL_DEPTH_TEST);
	glutSwapBuffers();//交换缓冲区
}
void reshape(int w, int h) {

	// 防止高度为0
	if (h == 0)
		h = 1;
	float ratio = 1.0 * w / h;

	// 单位化投影矩阵。
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 设置视口大小为整个窗口大小
	glViewport(0, 0, w, h);

	// 设置正确的投影矩阵
	gluPerspective(45, ratio, 1, 1000);
	//下面是设置模型视图矩阵
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//设置观测点
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -12.0, 0.0f, 1.0f, 0.0f);
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':
	case 'X':
		press = 1;
		printf("绕X轴旋转\n");
		break;
	case 'y':
	case 'Y':
		press = 2;
		printf("绕Y轴旋转\n");
		break;
	case 'z':
	case 'Z':
		press = 3;
		printf("绕Z轴旋转\n");
		break;
	case 'l':
	case 'L':
		press = 4;
		printf("左移\n");
		break;
	case 'r':
	case 'R':
		press = 5;
		printf("右移\n");
		break;
	case 'u':
	case 'U':
		press = 6;
		printf("上移\n");
		break;
	case 'd':
	case 'D':
		press = 7;
		printf("下移\n");
		break;
	case 'f':
	case 'F':
		press = 8;
		printf("前移\n");
		break;
	case 'b':
	case 'B':
		press = 9;
		printf("后移\n");
		break;
	case 'a':
	case 'A':
		press = 10;
		printf("放大\n");
		break;
	case 's':
	case 'S':
		press = 11;
		printf("缩小\n");
		break;
	case 'm':
	case 'M':
		press = 12;
		printf("恢复\n");
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("三维图形变换");
	glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboard);
	glutReshapeFunc(reshape); //指定窗口形状变化时的回调函数
	glutIdleFunc(display); //指定程序空闲时调用函数
	glutMainLoop();
	return 0;
}


#define _CRT_SECURE_NO_WARNINGS      

#include <stdio.h>      
#include <string.h>      
#include<time.h>    
#include <stdlib.h>    
#include"test.h"      
#include"fluid.h"

# define  white  1.0 ,  1.0  ,  1.0   // 对颜色的宏定义
# define  green  0.0 ,  0.502,  0.0
# define  red    0.8 ,  0.0  ,  0.0
# define  gray   0.502, 0.502,0.502
# define  hgray  0.117, 0.180,0.227
# define  blue   0.0  , 0.0  ,  1.0
# define  pi  3.14159265
# define  gold   1.0,215.0/255.0,0.0
# define  hgreen 0.0,100.0/255.0,0.0
# define  brown  210.0/255.0, 105.0/255.0,  30.0/255.0
# define  nbrown 128.0/255.0, 64.0/255.0, 64.0/255.0
# define  men   244.0/255.0 ,164.0/255.0 , 96.0/255.0
# define  menba   139.0/255.0 ,69.0/255.0,19.0/255.0
# define water 141.0/255.0, 193.0/255.0, 241.0/255.0
# define orange 255.0/255.0, 128.0/255.0, 0.0/255.0
# define sunshine 255.0/255.0, 210.0/255.0, 166.0/255.0

//纹理缓冲区  
GLuint texture[13];

//视区      
float whRatio;
int wHeight = 0;
int wWidth = 0;
//流体
Fluid *f;

//视点      
float center[] = { 27, 10, 0 };
float eye[] = { 27, -50, 50 };

double fang[8][3];             // 定义长方体的8个顶点
// 定义constract函数  当给定长方体的最里面的点时，
// 计算其余的7个顶点 并赋值给fang

void drawScene()
{
	static int count = 0;
	count++;
	if (count > 1000) {
		count = 0;
		f->Evaluate();
	}
	f->draw();
}

void updateView(int height, int width)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);//设置矩阵模式为投影       
	glLoadIdentity();   //初始化矩阵为单位矩阵          
	whRatio = (GLfloat)width / (GLfloat)height;  //设置显示比例     
	gluPerspective(45.0f, whRatio, 1.0f, 150.0f); //透视投影        
	//glFrustum(-3, 3, -3, 3, 3,100);      
	glMatrixMode(GL_MODELVIEW);  //设置矩阵模式为模型    
}

void reshape(int width, int height)
{
	if (height == 0)      //如果高度为0          
	{
		height = 1;   //让高度为1（避免出现分母为0的现象）          
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth); //更新视角          
}


void idle()
{
	glutPostRedisplay();
}


void init()
{
	srand(unsigned(time(NULL)));
	glEnable(GL_DEPTH_TEST);//开启深度测试       

	glEnable(GL_LIGHTING);  //开启光照模式       

	//	Fluid(long n, long m, float d, float t, float c, float mu);

	glGenTextures(1, texture);
	loadTex(0, "D://code//VS code//动态测试//water.bmp", texture);
	/*
	n = 10
	m = 10
	d = 1
	t = 1
	c = 0.5
	u = 0
	*/
	f = new Fluid(10, 10, 5, 2, 0.5, 0, texture[0]);
}

void constract(double x, double y, double z, double x1, double y1, double z1){ //长方体
	fang[0][0] = x;
	fang[0][1] = y;
	fang[0][2] = z;        //  第0个点

	fang[1][0] = x;
	fang[1][1] = y;
	fang[1][2] = z + z1;     //  第一个点

	fang[2][0] = x + x1;
	fang[2][1] = y;
	fang[2][2] = z + z1;     //  第二个点

	fang[3][0] = x + x1;
	fang[3][1] = y;
	fang[3][2] = z;        //  第三个点
	for (int i = 0; i<4; i++){  // for()循环来完成其余的四个点
		for (int j = 0; j<3; j++){
			if (j == 1)
				fang[i + 4][j] = fang[i][j] + y1;
			else
				fang[i + 4][j] = fang[i][j];
		}
	}
}

void build(){
	glBegin(GL_POLYGON);
	//glColor3f(red);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(fang[0][0], fang[0][1], fang[0][2]);
	glVertex3f(fang[1][0], fang[1][1], fang[1][2]);
	glVertex3f(fang[2][0], fang[2][1], fang[2][2]);
	glVertex3f(fang[3][0], fang[3][1], fang[3][2]);
	glEnd();   //     下底

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(fang[1][0], fang[1][1], fang[1][2]);
	glVertex3f(fang[0][0], fang[0][1], fang[0][2]);
	glVertex3f(fang[4][0], fang[4][1], fang[4][2]);
	glVertex3f(fang[5][0], fang[5][1], fang[5][2]);
	glEnd();   //     左面

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(fang[7][0], fang[7][1], fang[7][2]);
	glVertex3f(fang[6][0], fang[6][1], fang[6][2]);
	glVertex3f(fang[2][0], fang[2][1], fang[2][2]);
	glVertex3f(fang[3][0], fang[3][1], fang[3][2]);
	glEnd();   //     右面

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(fang[5][0], fang[5][1], fang[5][2]);
	glVertex3f(fang[6][0], fang[6][1], fang[6][2]);
	glVertex3f(fang[2][0], fang[2][1], fang[2][2]);
	glVertex3f(fang[1][0], fang[1][1], fang[1][2]);
	glEnd();   //     前面

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(fang[0][0], fang[0][1], fang[0][2]);
	glVertex3f(fang[3][0], fang[3][1], fang[3][2]);
	glVertex3f(fang[7][0], fang[7][1], fang[7][2]);
	glVertex3f(fang[4][0], fang[4][1], fang[4][2]);
	glEnd();   //     后面

	glBegin(GL_POLYGON);
	//glColor3f(red);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(fang[4][0], fang[4][1], fang[4][2]);
	glVertex3f(fang[7][0], fang[7][1], fang[7][2]);
	glVertex3f(fang[6][0], fang[6][1], fang[6][2]);
	glVertex3f(fang[5][0], fang[5][1], fang[5][2]);
	glEnd();   //     上面
}

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除颜色和深度缓存        
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();   //初始化矩阵为单位矩阵          
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);                // 场景（0，0，0)，Y轴向上      
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	// 启用光照计算    
	glEnable(GL_LIGHTING);
	// 指定环境光强度（RGBA）    
	GLfloat ambientLight[] = { 2.0f, 2.0f, 2.0f, 1.0f };

	// 设置光照模型，将ambientLight所指定的RGBA强度值应用到环境光    
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	// 启用颜色追踪    
	glEnable(GL_COLOR_MATERIAL);
	// 设置多边形正面的环境光和散射光材料属性，追踪glColor    
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);




	drawScene();//绘制场景 	
	//
	//////****************************增加地面底板（颜色为 绿色）********
	//glBegin(GL_POLYGON);
	//constract(-200, 0, -200, 1100, 10, 800);
	//glColor3f(green);
	//build();

	//////****************************增加大地层********
	//glBegin(GL_POLYGON);
	//constract(-200, -5, -200, 1100, 1, 900);
	//glColor3f(nbrown);
	//build();      
	glutSwapBuffers();//交换缓冲区      
}

int main(int argc, char *argv[])
{

	glutInit(&argc, argv);//对glut的初始化             
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	//初始化显示模式:RGB颜色模型，深度测试，双缓冲               
	glutInitWindowSize(500, 500);//设置窗口大小             
	int windowHandle = glutCreateWindow("Simple GLUT App");//设置窗口标题               
	glutDisplayFunc(redraw); //注册绘制回调函数             
	glutReshapeFunc(reshape);   //注册重绘回调函数             

	glutIdleFunc(idle);//注册全局回调函数：空闲时调用           

	init();
	glutMainLoop();  // glut事件处理循环           
	return 0;
}
#include "stdlib.h"
#include <GL/glut.h>
#include<iostream>
using std::cout;
#define _USE_MATH_DEFINES // for C++
#include <math.h>
GLfloat w = 1100;
GLfloat h = 1100;
double rotate_x = 0.0;
double rotate_y = 0.0;
double rotate_z = 0.0;

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

double fang[8][3];             // 定义长方体的8个顶点
// 定义constract函数  当给定长方体的最里面的点时，
// 计算其余的7个顶点 并赋值给fang

double san[8][3];              // 定义地面为梯形的长方体

//定义两个纹理对象编号
GLuint texGround;
GLuint texPoor;
GLuint texFloor;
GLuint texRoof;

#define BMP_Header_Length 54  //图像数据在内存块中的偏移量
static GLfloat angle = 0.0f;   //旋转角度
//材质参数
GLfloat matiral_specular[4] = { 0.00, 0.00, 0.00, 1.00 };  //材质参数：镜面反射，所得到的光的强度（颜色）
GLfloat matiral_emission[4] = { 0.00, 0.00, 0.00, 1.00 };  //材质本身就微微的向外发射光线
const GLfloat matiral_shininess = 11.00;
//设置材质


GLfloat sca[3] = { 1.5, 1.5, 1.5 };
GLfloat tra[3] = { -300, 0, -470 };


GLfloat AngleX;
GLfloat AngleY;


GLfloat bx = 0; //泳池中气球的移动坐标
GLfloat by = 0;
GLfloat bz = 0;

void setMetiral(GLfloat matiral_diffuse_ambient[4])
{
	//glMaterialfv(GL_FRONT,GL_AMBIENT,matiral_ambient); //光线照射到该材质上,经过多次反射遗留在整个光照环境中的强度（颜色）
	//glMaterialfv(GL_FRONT,GL_DIFFUSE,matiral_diffuse); //光线照射到该材质上,漫反射，所得到的光的强度（颜色）
	//设置颜色
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matiral_diffuse_ambient); //设置相同值更逼真
	//设置参数
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matiral_specular);  //镜面反射，所得到的光的强度（颜色）
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matiral_emission);  //材质本身就微微的向外发射光线，以至于眼睛感觉到它有这样的颜色 
	glMaterialf(GL_FRONT_AND_BACK, matiral_shininess, 0);   //“镜面指数”（0~128） 该值越小，材质越粗糙，点光源发射的光线照射到上面，也可以产生较大的亮点。该值越大，表示材质越类似于镜面，光源照射到上面后，产生较小的亮点。

}

//void drawSphere(double r, int lats, int longs, double x, double y, double z) {  //圆
//	int i, j;
//	for (i = 0; i <= lats; i++) {
//		double lat0 = pi * (-0.5 + (double)(i - 1) / lats);   // M_PI
//		double z0 = sin(lat0);
//		double zr0 = cos(lat0);
//
//		double lat1 = pi * (-0.5 + (double)i / lats);
//		double z1 = sin(lat1);
//		double zr1 = cos(lat1);
//
//		glBegin(GL_QUAD_STRIP);
//		glScaled(100, 100, 100);
//		for (j = 0; j <= longs; j++) {
//			double lng = 2 * pi * (double)(j - 1) / longs;
//			double x = cos(lng);
//			double y = sin(lng);
//			glNormal3f(x * zr0, y * zr0, z0);
//			glVertex3f(zr0, zr0, z0);
//			glNormal3f(x * zr1, y * zr1, z1);
//			glVertex3f(zr1, zr1, z1);
//		}
//		glEnd();
//	}
//}

void cons(double x, double y, double z, double x1, double y1, double z1){  //梯形
	san[0][0] = x;
	san[0][1] = y;
	san[0][2] = z;     //  第0个点

	san[1][0] = x;
	san[1][1] = y;
	san[1][2] = z + z1;   //  第1个点

	san[4][0] = x;
	san[4][1] = y + y1;
	san[4][2] = z;     //  第4个点

	san[5][0] = x;
	san[5][1] = y + y1;
	san[5][2] = z + z1 / 2;      //  第5个点
	for (int i = 0; i<3; i++){
		if (i == 0){
			san[3][i] = san[0][i] + x1;
			san[2][i] = san[1][i] + x1;
			san[6][i] = san[4][i] + x1;
			san[7][i] = san[5][i] + x1;
		}
		else{
			san[3][i] = san[0][i];
			san[2][i] = san[1][i];
			san[6][i] = san[4][i];
			san[7][i] = san[5][i];
		}
	}
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

void build2(){
	glBegin(GL_POLYGON);
	//glColor3f(red);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(san[0][0], san[0][1], san[0][2]);
	glVertex3f(san[1][0], san[1][1], san[1][2]);
	glVertex3f(san[2][0], san[2][1], san[2][2]);
	glVertex3f(san[3][0], san[3][1], san[3][2]);
	glEnd();   //     下底

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(san[1][0], san[1][1], san[1][2]);
	glVertex3f(san[0][0], san[0][1], san[0][2]);
	glVertex3f(san[4][0], san[4][1], san[4][2]);
	glVertex3f(san[5][0], san[5][1], san[5][2]);
	glEnd();   //     左面

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(san[7][0], san[7][1], san[7][2]);
	glVertex3f(san[6][0], san[6][1], san[6][2]);
	glVertex3f(san[3][0], san[3][1], san[3][2]);
	glVertex3f(san[2][0], san[2][1], san[2][2]);
	glEnd();   //     右面

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(san[5][0], san[5][1], san[5][2]);
	glVertex3f(san[6][0], san[6][1], san[6][2]);
	glVertex3f(san[2][0], san[2][1], san[2][2]);
	glVertex3f(san[1][0], san[1][1], san[1][2]);	
	glEnd();   //     前面

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(san[0][0], san[0][1], san[0][2]);
	glVertex3f(san[3][0], san[3][1], san[3][2]);
	glVertex3f(san[7][0], san[7][1], san[7][2]);
	glVertex3f(san[4][0], san[4][1], san[4][2]);
	glEnd();   //     后面

	glBegin(GL_POLYGON);
	//glColor3f(red);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(san[4][0], san[4][1], san[4][2]);
	glVertex3f(san[7][0], san[7][1], san[7][2]);
	glVertex3f(san[6][0], san[6][1], san[6][2]);
	glVertex3f(san[5][0], san[5][1], san[5][2]);
	glEnd();   //     上面
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

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();          //增加M矩阵
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_z, 0.0, 0.0, 1.0);
	//glScalef(1.5, 1.5, 1.5);
	//glTranslatef(-470, 0, -470);


	glScalef(sca[0], sca[1], sca[2]);
	glTranslatef(tra[0], tra[1], tra[2]);


	////****************************增加地面底板（颜色为 绿色）********
	glBegin(GL_POLYGON);
	constract(-200, 0, -200, 1100, 10, 800);
	glColor3f(green);
	build();

	////****************************增加大地层********
	glBegin(GL_POLYGON);
	constract(-200, -5, -200, 1100, 1, 900);
	glColor3f(nbrown);
	build();

	//****************************增加小路（颜色  深灰色）***************************
	glBegin(GL_POLYGON);
	constract(-200, 0, 600, 1100, 10, 100);
	glColor3f(gray);
	build();

	//纹理设置地面
	//texGround = load_texture("ground-water.bmp");
	//设置材质
	GLfloat matiral_diffused[4] = { 0.20, 0.32, 0.80, 1.00 };
	setMetiral(matiral_diffused);
	
	glEnable(GL_TEXTURE_2D);    //草地纹理
	glBindTexture(GL_TEXTURE_2D, texGround);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-200, 11, -200);
	glTexCoord2f(0.0f, 5.0f); glVertex3f(-200, 11, 600);
	glTexCoord2f(5.0f, 5.0f); glVertex3f(900, 11, 600);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(900, 11, -200);
	glEnd();
	glDisable(GL_TEXTURE_2D);


	////****************************增加车库底板（颜色  深灰色）****************
	//glBegin(GL_POLYGON);
	//constract(330, 20, 250, 140, 1, 250);
	//glColor3f(gray);
	//build();
	//****************************增加斑马线（颜色为 白色）********
	for (int i = 0; i<11; i++){
		glBegin(GL_POLYGON);
		constract(i * 100-200, 10, 600 + 45, 40, 1, 10);
		glColor3f(white);
		build();
	}
	//****************************增加栅栏基座（颜色为 白色）********
	glBegin(GL_POLYGON);
	constract(10, 10, 10, 20, 20, 480);
	glColor3f(white);
	build();       //    对应于A点
	constract(30, 10, 10, 650, 20, 20);
	glColor3f(white);
	build();       //    对应于B点
	constract(680, 10, 10, 20, 20, 480);
	glColor3f(white);
	build();       //    对应于C点
	constract(30, 10, 470, 100, 20, 20);
	glColor3f(white);
	build();       //    对应于D点
	constract(230, 10, 470, 450, 20, 20);
	glColor3f(white);
	build();       //    对应于F点
	//****************************增加栅栏柱子（颜色为 白色）********
	glBegin(GL_POLYGON);
	constract(10, 10, 10, 20, 50, 20);
	glColor3f(white);
	build();       //    对应于A点
	glBegin(GL_POLYGON);
	constract(680, 10, 10, 20, 50, 20);
	glColor3f(white);
	build();       //    对应于C点
	glBegin(GL_POLYGON);
	constract(230, 10, 470, 20, 50, 20);
	glColor3f(white);
	build();       //    对应于F点
	glBegin(GL_POLYGON);
	constract(10, 10, 470, 20, 50, 20);
	glColor3f(white);
	build();       //    对应于E点
	glBegin(GL_POLYGON);
	constract(680, 10, 470, 20, 50, 20);
	glColor3f(white);
	build();       //    对应于G点
	glBegin(GL_POLYGON);
	//constract(310, 10, 470, 20, 50, 20);
	//glColor3f(white);
	//build();       //    对应于H点
	glBegin(GL_POLYGON);
	constract(110, 10, 470, 20, 50, 20);
	glColor3f(white);
	build();       //    对应于I点
	//****************************增加栅栏********
	glColor3f(nbrown);
	for (int i = 35; i<470; i += 25)
	{
		constract(15, 20, i, 6, 30, 6);
		build();         //左边竖条
	}
	for (int i = 35; i<470; i += 25)
	{
		constract(685, 20, i, 6, 30, 6);
		build();          // 右边竖条
	}
	for (int i = 35; i<680; i += 25)
	{
		constract(i, 20, 15, 6, 30, 6);
		build();          // 上边横条
	}
	for (int i = 35; i<110; i += 25)
	{
		constract(i, 20, 480, 6, 30, 6);
		build();          // 下边横条1
	}
	for (int i = 235; i<680; i += 25)
	{
		constract(i, 20, 480, 6, 30, 6);
		build();          // 下边横条2
	}

	//****************************增加泳池********
	glColor3f(water);
	constract(490, 10, 75, 150, 5, 350);
	build();	

	glColor3f(white);
	constract(490, 10, 75, 8, 12, 350);
	build();     //左墙壁
	glColor3f(white);
	constract(632, 10, 75, 8, 12, 350);
	build();     //右墙壁
	glColor3f(white);
	constract(498, 10, 75, 134, 12, 8);
	build();     //上墙壁
	glColor3f(white);
	constract(498, 10, 417, 134, 12, 8);
	build();     //下墙壁1

	glEnable(GL_TEXTURE_2D);   //泳池纹理
	glBindTexture(GL_TEXTURE_2D, texPoor);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(490, 16, 75);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(490, 16, 425);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(640, 16, 425);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(640, 16, 75);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	////****************************增加车库墙（颜色为 白色）********
	//glColor3f(white);
	//constract(320, 10, 250, 10, 100, 220);
	//build();
	//constract(460, 10, 250, 10, 100, 220);
	//build();
	////****************************增加车库顶棚（颜色为 深灰色）********
	//glColor3f(hgray);
	//constract(320, 110, 250, 150, 10, 220);
	//build();
	//****************************增加卧室和客厅的墙壁（颜色为 白色）********
	glColor3f(white);
	constract(50, 10, 50, 12, 150, 197);
	build();     //左墙壁
	glColor3f(white);
	constract(438, 10, 50, 12, 150, 197);
	build();     //右墙壁
	glColor3f(white);
	constract(62, 10, 50, 376, 150, 12);
	build();     //上墙壁
	
	glColor3f(white);
	constract(62, 10, 235, 376, 35, 12);
	build();     //下墙壁1
	glColor3f(white);
	constract(62, 45, 235, 50, 65, 12);
	build();     //下墙壁2
	glColor3f(white);
	constract(200, 45, 235, 238, 65, 12);
	build();     //下墙壁3
	glColor3f(white);
	constract(62, 110, 235, 376, 50, 12);
	build();     //下墙壁4

	//****************************增加房内地板********
	glEnable(GL_TEXTURE_2D);   
	glBindTexture(GL_TEXTURE_2D, texFloor);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(62, 15, 62);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(62, 15, 235);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(438, 15, 235);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(438, 15, 62);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//****************************增加卧室和客厅的玻璃（颜色为 白色）********
	glColor4f(blue, 0.35);
	constract(62 + 50, 45, 235, 88, 65, 12);
	build();

	////****************************增加房顶 （颜色 红色）************
	glColor3f(red);
	cons(50, 160, 148.5, 400, 27, 110);
	build2();
	cons(50, 187, 148.5, 400, 27, 90);
	//cons(50, 187, 140, 400, 27, 90);
	build2();
	cons(50, 214, 148.5, 400, 27, 70);
	build2();
	cons(50, 241, 148.5, 400, 15, 50);
	build2();
	glColor3f(red);
	cons(50, 160, 148.5, 400, 27, -110);
	build2();
	cons(50, 187, 148.5, 400, 27, -90);
	build2();
	cons(50, 214, 148.5, 400, 27, -70);
	build2();
	cons(50, 241, 148.5, 400, 15, -50);
	build2();
	//************************************* 门*************
	glColor3f(men);
	constract(230, 10, 250, 50, 100, 5);
	build();              //门面
	glColor3f(menba);
	constract(235, 60, 255, 5, 5, 5);
	build();              //门把手
	//**************************************小路*************
	for (int i = 0; i<6; i++)
	{
		glColor3f(brown);
		constract(235 - i * 15, 10, 250 + i * 40, 40, 2, 20);
		build();
	}
	////**************************************太阳*************
	glColor3f(gold);
	glTranslatef(700, 400, 300);
	glutSolidSphere(35.0, 20, 20);
	glTranslatef(-700, -400, -300);

	//**************************************树干*************
	glColor3f(brown);
	constract(60, 10, 390, 15, 70, 15);
	build();
	//**************************************树叶*************
	glColor3f(hgreen);
	glTranslatef(60, 70, 400);
	glutSolidSphere(25.0, 20, 20);  //球1

	glTranslatef(20, 0, 0);
	glutSolidSphere(25.0, 20, 20);  //球2

	glTranslatef(-10, 0, -10);
	glutSolidSphere(25.0, 20, 20);  //球3

	glTranslatef(0, 0, 20);
	glutSolidSphere(25.0, 20, 20);  //球4

	glTranslatef(0, 10, -10);
	glutSolidSphere(25.0, 20, 20);  //球4
	glTranslatef(-70, -80, -400);

	//glPushMatrix();
	//{
	//	glRotatef(AngleX, 1.0f, 0.0f, 0.0f);
	//	glRotated(AngleY, 0.0f, 1.0f, 0.0f);
	//	glScalef(sca[0], sca[1], sca[2]);
	//	glTranslatef(tra[0], tra[1], tra[2]);
	//	//glutWireSphere(36, 25, 25);	
	//	glColor3f(gold);

	//	glutSolidSphere(35.0, 20, 20);

	//	//glColor3f(red);
	//	//glutWireCone(25, 20, 30, 30);
	//}
	//glPopMatrix();

	//**************************************气球*************
	//glColor3f(orange);
	glColor4f(orange, 0.8);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glTranslatef(565 - bx, 25 - by, 250 - bz);
	glutSolidSphere(15, 20, 20);
	glTranslatef(-565, -25, -250);

	glFlush();  // 刷新
	glutSwapBuffers();//还要加上swapbuffer函数
}

GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };
//GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.5 };;//光源位置
GLfloat light_position[] = { 1.0,1.0,0,0};;//光源位置
GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };

void init(void)
{
	//glTranslatef(700, 400, 0);
	//glutSolidSphere(35.0, 20, 20);
	//glTranslatef(-700, -400, 0);

	GLfloat sun_direction[] = { 700.0, 400.0, 100.0, 1.0 };
	GLfloat sun_intensity[] = { sunshine, 1.0 };
	GLfloat ambient_intensity[] = { 0.5, 0.5, 0.5, 1.0 };

	glEnable(GL_LIGHTING);              // Set up ambient light.环境光
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);
	//glLightModelfv(GL_AMBIENT, ambient_intensity);


	glEnable(GL_LIGHT0);                // Set up sunlight.漫反射
	glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_intensity);

	glEnable(GL_COLOR_MATERIAL);        // Configure glColor().
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	cout << "The OpenGL version is: " << glGetString(GL_VERSION) << "\n";
	cout << glGetString(GL_VENDOR) << "\n";
	glLineWidth(5);
	glClearColor(0.0, 0.0, 0.0, 0.0);      //定义背景颜色-->  black

	glEnable(GL_BLEND); // 打开混合
	glDisable(GL_DEPTH_TEST); // 关闭深度测试
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); // 基于源象素alpha通道值的半透明混合函数
	glEnable(GL_DEPTH_TEST); //打开深度测试

	glMatrixMode(GL_PROJECTION);     // 貌似和视角有关的定义 places the camera at (0,0,0) and faces it along(0,0,-1).
	glOrtho(-w, w, -h, h, -w, w); // specify clipping volume
}


int flag = 1;
void timerFunction(int value)
{
	if (flag == 1){
		by = by + 4;
		flag++;
	}
	else if (flag == 2){
		by = by - 4;
		flag--;
	}
	else{
		cout << "Wrong!\n";
	}
	glutPostRedisplay();
	glutTimerFunc(1000, timerFunction, 1);
}

void specialkeys(int key, int x, int y){   //键盘相应函数
	
	//气球移动
	if (key == GLUT_KEY_F1)
		bx -= 1;
	else if (key == GLUT_KEY_F2)
		bx += 1;
	else if (key == GLUT_KEY_F3)
		bz += 1;
	else if (key == GLUT_KEY_F4)
		bz -= 1;

	//旋转
	if (key == GLUT_KEY_RIGHT)
		rotate_y -= 1;
	else if (key == GLUT_KEY_LEFT)
		rotate_y += 1;
	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 1;
	else if (key == GLUT_KEY_UP)
		rotate_x += 1;
	
	//场景放缩
	if (key == GLUT_KEY_F7){  
		for (int i = 0; i < 3; i++)
			sca[i] = sca[i] + 0.1;
	}
	else if (key == GLUT_KEY_F8){ 
		for (int i = 0; i < 3; i++)
			sca[i] = sca[i] - 0.1;
	}
	glutPostRedisplay();
}

// 函数power_of_two用于判断一个整数是不是2的整数次幂
int power_of_two(int n)
{
	if (n <= 0)
		return 0;
	return (n & (n - 1)) == 0;
}

/* 函数load_texture
* 读取一个BMP文件作为纹理
* 如果失败，返回0，如果成功，返回纹理编号
*/
GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID = 0, texture_ID = 0;
	FILE *pFile;
	errno_t err;                                   

	// 打开文件，如果失败，返回
	if ((err = fopen_s(&pFile, file_name, "rb")) != 0)    
	{
		printf("无法打开此文件\n");            //如果打不开，就输出打不开
		exit(0);                               //终止程序
	}

	// 读取文件中图象的宽度和高度
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// 计算每行像素所占字节数，并根据此数据计算总像素字节数
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// 根据总像素字节数分配内存
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	// 读取像素数据
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 对就旧版本的兼容，如果图象的宽度和高度不是的整数次方，则需要进行缩放
	// 若图像宽高超过了OpenGL规定的最大值，也缩放
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if (!power_of_two(width)
			|| !power_of_two(height)
			|| width > max
			|| height > max)
		{
			const GLint new_width = 256;
			const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			// 计算每行需要的字节数和总字节数
			new_line_bytes = new_width * 3;
			while (new_line_bytes % 4 != 0)
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			// 分配内存
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if (new_pixels == 0)
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			// 进行像素缩放
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	// 分配一个新的纹理编号
	glGenTextures(1, &texture_ID);
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 绑定新的纹理，载入纹理并设置纹理参数
	// 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
	GLint lastTextureID = last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, lastTextureID);  //恢复之前的纹理绑定
	free(pixels);
	return texture_ID;
}

int main(int argc, char** argv)    //  main函数 增加键盘事件
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("The House");
	init();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);    // 启用纹理
	//"D://code//VS code//ConsoleApplication1-v4.0//grass.bmp"
	texGround = load_texture("grass.bmp");  //加载纹理
	texPoor = load_texture("swimmingpoor3.bmp");
	texFloor = load_texture("floor.bmp");

	//texRoof = load_texture("D://code//VS code//ConsoleApplication1-v2.0//floor.bmp"); 
	glutDisplayFunc(display);
	//glutMotionFunc(myMouseMotion); //调用鼠标移动函数
	glutSpecialFunc(specialkeys);  //调用键盘控制函数	
	glutTimerFunc(1000, timerFunction, 1);    //注册定时器
	glutMainLoop();
	system("pause");
	return 0;
}


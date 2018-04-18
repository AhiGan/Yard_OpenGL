#pragma once
#include "Vector2D.h"  


class Fluid
{
private:

	long            width; //宽
	long            height; //高

	Vector3D        *buffer[2]; //缓冲区
	long            renderBuffer;  //当前渲染的缓冲区

	//Vector3D        *normal; //法线
	//Vector3D        *tangent; //切线

	int             *indices[3]; //索引
	float       *texcoords[3][2]; //纹理坐标
	float           k1, k2, k3; //多项式系数

	int texture;
public:

	//n:网格宽 m：网格高 d：网格点之间的距离
	//t:时间 c：波速 mu：阻力系数

	Fluid(long n, long m, float d, float t, float c, float mu, int tex);
	~Fluid();

	void Evaluate(void);
	void draw();
};
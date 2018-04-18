# Yard_OpenGL
# 使用OpenGL函数库实现的一个三维庭院

> 源代码参考自：[《OpenGL 房子》](https://blog.csdn.net/xws117/article/details/42342345)

## 实验要求
绘制一个具有真实感的三维场景，其中至少含有2个三维物体，具有光照、纹理效果，可实现交互式的场景漫游，可以使用WebGL、OpenGL或其他函数库，要求独立完成从建模、变换、光照、面绘制算法、纹理映射的全部过程。

## 实验报告
### 1 使用手册
1.	该程序在Visual Studio + OpenGL的平台上模拟了一个三维立体场景中的庭院，场景中包括草地、树木、房屋、泳池、小球、栅栏、小路、马路和太阳等对象。
2.	场景观测视角旋转：键盘↑/↓/←/→分别对应控制视角上移、下移、左移和右移。
3.	场景缩放：键盘F7/F8分别对应控制场景放大和缩小。
4.	小球运动：泳池中小球会随着水波自动沉浮，并且可以通过键盘F1/F2/F3/F4分别控制小球向前、向后、向左、向右游动
![Image Text](https://github.com/AhiGan/Img_Folder/blob/master/Yard_OpenGL_1.png)
![Image Text](https://github.com/AhiGan/Img_Folder/blob/master/Yard_OpenGL_2.png)
### 2 设计思路
1.	建模。对三维立体场景以及场景中的各对象进行模型建立，包括光照和面绘制。设置了环境光和平行光两种光照类型，面绘制则采用了两种绘制方式，单层绘制负责圆形的绘制，两层层级绘制则用于其他图形的绘制。
2.	纹理绘制。实现场景中的草地、泳池和房内地板的纹理映射。
3.	交互控制。实现键盘对场景的各类交互控制。
4.	动态纹理绘制。实现泳池的水的动态水波和小球的动态沉浮，考虑使用基于网格绘制的方法，通过物理模拟（各种波动方程）来计算网格点位置，达到动态效果。

### 3 实现
1.	建模
1) 首先，简单地调用OpenGL的初始化函数，实现应用程序的初始化工作。之后，建立窗口的位置，定义窗口的宽度和高度，指定窗口的显示模式。在init函数中对光照和视角进行了初始化，注册了绘图函数display负责三维场景中所有对象的绘制。
![Image Text](https://github.com/AhiGan/Img_Folder/blob/master/Yard_OpenGL_3.png)
2) 面绘制中两层层级绘制方式，上层设置了constract函数和cons函数分别根据输入的坐标参数对长方体和梯形的顶点数组进行赋值，再由下层build2函数和build函数分别根据顶点坐标进行面绘制。
![Image Text](https://github.com/AhiGan/Img_Folder/blob/master/Yard_OpenGL_4png)
![Image Text](https://github.com/AhiGan/Img_Folder/blob/master/Yard_OpenGL_5.png)
3) 场景中各对象的实现只需调用上层constract函数和cons函数或glutSolidSphere函数即可。
![Image Text](https://github.com/AhiGan/Img_Folder/blob/master/Yard_OpenGL_6.png)
![Image Text](https://github.com/AhiGan/Img_Folder/blob/master/Yard_OpenGL_7.png)
![Image Text](https://github.com/AhiGan/Img_Folder/blob/master/Yard_OpenGL_8.png)
2.	纹理绘制
首先对纹理对象进行了定义，在纹理绑定函数中读取纹理绘制所需的bmp图片。之后进行启动纹理、绑定纹理、关闭纹理三步骤。
![Image Text](https://github.com/AhiGan/Img_Folder/blob/master/Yard_OpenGL_9.png)
![Image Text](https://github.com/AhiGan/Img_Folder/blob/master/Yard_OpenGL_10.png)
![Image Text](https://github.com/AhiGan/Img_Folder/blob/master/Yard_OpenGL_11.png)
![Image Text](https://github.com/AhiGan/Img_Folder/blob/master/Yard_OpenGL_12.png)
3.	交互控制
键盘的交互控制通过specialkeys函数实现，函数参数为键盘按下的键key。F1/F2/F3/F4控制泳池中小球的移动，该移动通过改变小球坐标的偏移量bx、bz实现。方向键上下左右控制三维场景的观测视角，该旋转通过改变场景轴旋转变量rotate_x、rotate_y实现。F7/F8控制三维场景的放大和缩小，该放缩通过修改放缩数组sca[3]实现。
![Image Text](https://github.com/AhiGan/Img_Folder/blob/master/Yard_OpenGL_13.png)
4.	动态纹理绘制。
这一部分在设计中是计划绘制出泳池中水涌动带动小球沉浮的场景。了解了真实的水面模拟在绘制方面有四种实现方式，分别是：贴图置换、基于网格绘制，通过物理模拟（各种波动方程）来计算网格点位置，达到动态效果、动态的凹凸纹理映射、使用粒子系统模拟水面；渲染则包括反射和折射效果的实现、高光（亮斑）的添加、半透明等方面。在这次实验中曾尝试基于网格绘制实现动态水面模拟，很遗憾这部分代码最终没有调试成功，因而最终只能通过定时器的方式实现小球的自动沉浮。
![Image Text](https://github.com/AhiGan/Img_Folder/blob/master/Yard_OpenGL_14.png)
![Image Text](https://github.com/AhiGan/Img_Folder/blob/master/Yard_OpenGL_15.png)

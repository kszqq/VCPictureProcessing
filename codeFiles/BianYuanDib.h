#pragma once
class BianYuanDib:public CObject
{
private:
	CDib *dib;
	/*经过平滑后的图像变模糊的根本原因是受到了平均或积分运算，因此可以对其进行逆运算（如微分运算），就可以使图像变得清晰。
	用差分运算时图像的第一行或者第一列经常无法求得，可以用旁边的值近似代替。
	边缘锐化这里的算子和都是0，而平滑是1.
	*/
public:
	void GetDib(CDib *dib);
	void ZongXiang();//进行纵向微分，用差分代替微分，f（i,j)-f(i,j-1)，实际上等于（f（i,j)-f(i,j-1)）/1
	void HengXiang();//进行横向微分，(f(i,j)-f(i-1,j))/1
	void ShuangXiang();//双向微分，sqrt(pow(f(i,j)-f(i-1,j),2)+pow(f（i,j)-f(i,j-1),2))
	void MenXianRuiHua(byte t);//门限锐化，门限阈值判断基本上不破坏内部，又能增强边缘亮度
	void GuDingRuiHua();//固定锐化,反正都是测试函数，就不写那么完善了，给边缘一个固定的灰度值
	//可以给边缘固定一个值，也可以给背景固定一个值，这里是边缘
	void ErZhiRuiHua();//二值锐化，用一个阈值，梯度大于就255，小于就0
	/*
	边缘沿边缘走向变化平缓，沿垂直边缘方向变换剧烈，从这个意义上说，提取边缘的算法就是检出符合边缘特性的边缘像素的数学算子。
	书上的0度、90度、135度边缘算子等，将所有模板用于像素上输出值最大的点就是改点的边缘方向；如果所有方向都接近0就说明没有边缘；如果所有方向输出值都接近相等，则改点没有可靠的边缘方向。
	由于我们不能预知边缘的方向，所以要用不具备空间方向性的算子和具有旋转不变的线性微分算子。
	卷积可以简单的看成一个加权求和的过程，模板矩阵叫做卷积核，卷积核中各元素叫卷积系数，卷积行、列必须是奇数，大多数是3x3的；图像的边缘要么忽略，要么复制旁边像素
	*/
	void Robert();//罗伯特算子边缘检测，对噪声敏感，边缘定位准；利用两个对角进行差分，形状是X，旋转也是一样的，具有旋转不变性
	LPBYTE Templat(int temph,int tempw,int tempx,int tempy,float main,float* fpArray);//最后一个是模板系数
	//Sobel算子,水平+垂直=十字形的，或者X行的旋转都是不变的，具有旋转不变性
	//
	void Sobel();//Sobel算子,效果会亮很多，具有一定的噪声抑制能力，用于提取边缘,下面减上面，左边减右边，这里只是实现了水平和垂直，取水平或者竖直中像素值较大的，并没有按照前面理论说的要取微分
	void Prewitt();//跟Sobel一样，只是算子的权重不一样,输出水平和垂直边缘检测中的最大值
	void Krisch();//8个算子，代表8个有向方向，从指向正上，顺时针旋转，8个方向输出较大值。
	/*边缘处图像一阶偏导数取得最大值，二阶偏导数会通过零点（由正到负或者由负到正）。
	旋转前后的偏导数的平方和具有旋转不变性，看看书就会动。
	高斯拉普拉斯将高斯滤波器和拉普拉斯锐化滤波器结合起来，先平滑噪声，再进行边缘检测，对孤立点敏感。本来是一个3x3的滤波，这里采用的是5x5的
	*/
	void Guasslaplacian();//高斯拉普拉斯算子，
};
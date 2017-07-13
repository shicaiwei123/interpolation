
#ifndef  INTERPOLATION_H
#define  INTERPOLATION_H
#include"ebox.h"
class Interpolation
{
public:
	//构造函数，传入样本点参数：恒做坐标首地址，数组长度
	Interpolation(float *x, float *y, int n);
	//更改样本点参数：恒做坐标首地址，数组长度
	void setSamplePoint(float *x, float *y, int n);
	//用二分查找查找输入x的区间下限
	float *search(float x);
	//纯虚函数，获取插值后任意坐标下的值
	virtual float getY(float x) = 0;
	//获取measureY
	int geyMeasureY(void);
private:
	float *xaxis;
	float *yaxis;
	int length;
	int measureY;    //用来确定插值点对应的y值

};


class LinearInterpolation :public Interpolation
{
public:
	LinearInterpolation(float *x, float *y, int n);
	float getY(float x);

private:
	float *xaxis;
	float *yaxis;
	int length;
};



class QuadraticInterpolation :public Interpolation
{
public:
	//构造函数
	QuadraticInterpolation(float *x, float *y, int n);
	//具体基类纯虚函数
	float getY(float x);

private:
	float *xaxis;
	float *yaxis;
	int length;

};




#endif
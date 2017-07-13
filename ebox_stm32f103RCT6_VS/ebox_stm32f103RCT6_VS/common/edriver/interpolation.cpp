#include "interpolation.h"
Interpolation::Interpolation(float *x, float *y, int n)
{
	this->xaxis = x;
	this->yaxis = y;
	this->length = n;
	measureY = 0;
}

void Interpolation::setSamplePoint(float *x, float *y, int n)
{
	this->xaxis = x;
	this->yaxis = y;
	this->length = n;
}

float *Interpolation::search(float x)
{
	float *x1 = xaxis;
	float *y1 = yaxis;
	//	float *x2 = x+4;          对数组指针做加法 等同于数组标号上直接相加
	int low = 0, high = length - 1;
	int mid = 0;
	while (1)
	{
		if (x <*(xaxis))  //如果x比最小值小
		{
			measureY = 1;
			return xaxis + 1;
		}

		else if (x>*(xaxis + length - 1)) //如果x比最大值大
		{
			measureY = length-1;
			return xaxis + length - 1;
		}

		else
		{
			mid = (low + high) / 2;
			if (*(xaxis + mid) > x)
			{
				high = mid - 1;
				if (*(xaxis + high) < x)
				{
					measureY = mid;
					return xaxis + mid;
					break;
				}
			}
			else if (*(xaxis + mid) < x)
			{
				low = mid + 1;
				if (*(xaxis + low) > x)
				{
					measureY = low;
					return xaxis + low;
					break;
				}
			}
			else
			{
				measureY = mid + 1;
				return xaxis + mid + 1;

			}
		}
		
	}


}

int Interpolation::geyMeasureY(void)
{
	return measureY;
}



LinearInterpolation::LinearInterpolation(float *x, float *y, int n) :Interpolation(x, y, n)
{
	this->xaxis = x;
	this->yaxis = y;
	this->length = n;
}

float LinearInterpolation::getY(float x)
{
	float *x1 = xaxis;
	float *y1 = yaxis;
	float y2, y3;
	float x2, x3;
	float k;
	float y;
	int j = 0;
	//while ( *(++x1)<x)
	//{
	//	j++;
	//	y1++;
	//}
	x1 = search(x);
	j = geyMeasureY();
	y1 = y1 + j;
	x3 = *x1--; x2 = *x1;
	y3 = *y1--; y2 = *y1;
	k = (y3 - y2) / (x3 - x2);
	y = y2 + k*(x - x2);
	return y;
}



QuadraticInterpolation::QuadraticInterpolation(float *x, float *y, int n) :Interpolation(x, y, n)
{
	this->xaxis = x;
	this->yaxis = y;
	this->length = n;
}

float QuadraticInterpolation::getY(float x)
{
	float *x1 = xaxis;
	float *y1 = yaxis;
	float arrY[3];
	float arrX[3];
	float y;
	int j = 0; //小于X的数最大横坐标标号
			   //找到x区间
			   //while (*(++x1) < x)
			   //{
			   //	j++;
			   //	y1++;
			   //}
	x1 = search(x);
	j = geyMeasureY();
	y1 = y1 + j;
	if (j < length - 2)//x在区间范围内,且下一个数不是边界
	{
		arrX[2] = *(++x1);
		arrX[1] = *(--x1);
		arrX[0] = *(--x1);
		arrY[2] = *(++y1);
		arrY[1] = *(--y1);
		arrY[0] = *(--y1);
	}
	else if (j >= length - 2) //x在区间范围内,且下一个数是上界或就是上界
	{
		arrX[2] = *(x1--);
		arrX[1] = *(x1--);
		arrX[0] = *(x1);
		arrY[2] = *(y1--);
		arrY[1] = *(y1--);
		arrY[0] = *(y1);
	}
	//百度例程
	//for (int k = 0; k < 3; k++)
	//{
	//	double t = 1;
	//	for (int j = 0; j < 3; j++)
	//	{
	//		if (k != j)
	//		{
	//			t = t*((x - arrX[j]) / (arrX[k] - arrX[j]));
	//		}
	//	}
	//	y = y + arrY[k] * t;
	//}
	//定义式
	float l0 = (x - arrX[1])*(x - arrX[2]) / ((arrX[0] - arrX[1])*(arrX[0] - arrX[2]));
	float l1 = (x - arrX[0])*(x - arrX[2]) / ((arrX[1] - arrX[0])*(arrX[1] - arrX[2]));
	float l2 = (x - arrX[0])*(x - arrX[1]) / ((arrX[2] - arrX[0])*(arrX[2] - arrX[1]));
	y = arrY[0] * l0 + arrY[1] * l1 + arrY[2] * l2;
	return y;
}

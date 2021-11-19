#include "stdafx.h"
#include "LagrangeInterpolator.h"

double LagrangeInterpolator::GetValue(double* ArrayX, double* ArrayY, double x, int n)
{
	double y = 0.0;

	for (int i = 0; i < n; i++)
	{
		y += ArrayY[i] * l(i, ArrayX, x, n);
	}

	return y;
}

double LagrangeInterpolator::l(int index, double* ArrayX, double x, int n)
{
	double l = 1;
	for (int i = 0; i < n; i++)
	{
		if (i != index)
		{
			l *= (x - ArrayX[i]) / (ArrayX[index] - ArrayX[i]);
		}
	}
	return l;
}
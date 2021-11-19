#pragma once
class LagrangeInterpolator
{
public:
	double GetValue(double* ArrayX, double* ArrayY, double x, int n);
private:
	double l(int index, double* ArrayX, double x, int n);
};


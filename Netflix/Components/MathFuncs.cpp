#include "MathFuncs.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double standardDeviation(vector<double> list)
{
	return sqrt(covariance(list, list));
}

double covariance(vector<double> first, vector<double> second)
{
	double meanFirst = mean(first), meanSecond = mean(second), sum = 0;
	for (int i = 0; i < first.size(); i++)
	{
		sum += (first[i] - meanFirst) * (second[i] - meanSecond);
	}
	return sum / (first.size() - 1);
}

double mean(vector<double> list)
{
	double sum = 0;
	for (int i = 0; i < list.size(); i++)
	{
		sum += list[i];
	}
	return sum / list.size();
}
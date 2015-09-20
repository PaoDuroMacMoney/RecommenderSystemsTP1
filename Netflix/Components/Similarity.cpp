#include "Similarity.h"
#include "MathFuncs.h"
#include <vector>
#include <cmath>

using namespace std;

static double Pearson(vector<double> first, vector<double> second)
{
	return covariance(first, second) / (standardDeviation(first) * standardDeviation(second));
}

static double Cosine(vector<double> first, vector<double> second)
{
	double firstSquared, secondSquared, product = 0 ;

	for (unsigned int i = 0; i < first.size(); i++) 
	{
		product += first[i] * second[i];
		firstSquared += first[i] * first[i];
		secondSquared += second[i] * second[i];		
	}
	return product / (sqrt(firstSquared) * sqrt(secondSquared));
}


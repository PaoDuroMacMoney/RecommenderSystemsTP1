#include "ColaborativeUserBasedSolver.h"
#include <iostream>
#include <algorithm>   
#include <math.h>
#include <sstream>

ColaborativeUserBasedSolver::ColaborativeUserBasedSolver(data_input * input, Parameters * params)
	: ColaborativeSolver(input, params)
{
}

string ColaborativeUserBasedSolver::chooseMainDimension(string userId, string itemId)
{
	return userId;
}

string ColaborativeUserBasedSolver::chooseAuxDimension(string userId, string itemId)
{
	return itemId;
}

vector<data_node*> * ColaborativeUserBasedSolver::getMainDimensionFunc(string dimensionId)
{
	return &input->userInfo[dimensionId]->ratedList;
}

vector<data_node*> * ColaborativeUserBasedSolver::getAuxDimensionFunc(string dimensionId)
{
	return &input->itemInfo[dimensionId]->ratedList;
}

bool ColaborativeUserBasedSolver::sortBeforeSolveFunc(data_node i, data_node j)
{
	return i.userId < j.userId;
}

ColaborativeUserBasedParameters::ColaborativeUserBasedParameters(int neighboorsAmount, float accuracyThresholdValue)
	:ColaborativeParameters(neighboorsAmount, accuracyThresholdValue)
{
}

string ColaborativeUserBasedParameters::getAlgorithmName()
{
	return "UserBased";
}

#pragma once
#include "Solver.h"
#include "Util.h"

class CrossValidation
{
public :
	CrossValidation(int folds, data_input * input, ISolver * solver);
	
	float run();
private:
	int folds;
	data_input * originalInput;
	ISolver * currentSolver;
	bool compareFunc(int i, int j);
};
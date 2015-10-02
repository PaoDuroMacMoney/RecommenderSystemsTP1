// Netflix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Components\Util.h"
#include "..\Components\Solver.h"
#include "..\Components\ColaborativeUserBasedSolver.h"
#include "..\Components\CrossValidation.h"
#include <iostream>
using namespace std;


int main()
{
	data_input * input = read_input("ratings.csv");
	data_input * target = read_input("targets.csv", true);
	
	ColaborativeUserBasedParameters * params = new ColaborativeUserBasedParameters(20);
	ISolver * solver = new ColaborativeUserBasedSolver(input, params);

	//solver->solve(target);

	float iterationRmse;
	float bestIterationRmse = FLT_MAX;
	int bestNeighboorhoodSelection = 0;
	for (int i = 15; i < 30; i++)
	{
		iterationRmse = crossValidation(5, input, *solver);
		params->update(i);
		if (iterationRmse < bestIterationRmse)
		{
			bestIterationRmse = iterationRmse;
			bestNeighboorhoodSelection = i;
		}
		std::cout << "rmse = " << iterationRmse << " for " << i << " neighboors" << std::endl;
	}

	std::cout << "best neighboorhood selection = " << bestNeighboorhoodSelection << std::endl;
	solver->solve(target);
	return 0;
}


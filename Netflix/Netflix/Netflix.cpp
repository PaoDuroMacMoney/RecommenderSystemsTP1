// Netflix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Components\Util.h"
#include "..\Components\Solver.h"
#include "..\Components\ColaborativeItemBasedSolver.h"
#include "..\Components\ColaborativeUserBasedSolver.h"
#include "..\Components\CrossValidation.h"
#include <iostream>
using namespace std;


int main()
{
	data_input * input = read_input("ratings.csv");
	data_input * target = read_input("targets.csv", true);

	ColaborativeItemBasedParameters * params = new ColaborativeItemBasedParameters(33, 0);
	ColaborativeItemBasedSolver * solver = new ColaborativeItemBasedSolver(input, params);
	CrossValidation * crossValidation = new CrossValidation(5, input, solver);

	/*ColaborativeUserBasedParameters * params = new ColaborativeUserBasedParameters(33, 1);
	ColaborativeUserBasedSolver * solver = new ColaborativeUserBasedSolver(input, params);
	CrossValidation * crossValidation = new CrossValidation(5, input, solver);
	*/

	crossValidation->run();
	//for (int i = 1; i <= 40; i++)
	//{
	//	params->update(i, 1);
	//	crossValidation->run();
	//}
	getchar();
	//solver->solve(target);
	return 0;
}


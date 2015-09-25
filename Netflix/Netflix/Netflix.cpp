// Netflix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Components\Util.h"
#include "..\Components\Solver.h"
#include "..\Components\ColaborativeUserBasedSolver.h"
#include <iostream>
using namespace std;


int main()
{
	data_input * input = read_input("ratings.csv");
	data_input * target = read_input("targets.csv", true);

	ISolver * solver = new ColaborativeUserBasedSolver(input);
	solver->solve(target);
	return 0;
}


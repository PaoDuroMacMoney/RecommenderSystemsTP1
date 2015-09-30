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
	data_input * input = read_input("ratings.csv", 336672);
	//data_input * target = read_input("targets.csv", 77276, true);
	data_input * target = read_input("targets.csv", 0, true);

	ISolver * solver = new ColaborativeUserBasedSolver(input);
	solver->solve(target);
	return 0;
}


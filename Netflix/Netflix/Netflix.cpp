// Netflix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Components\Util.h"
#include "..\Components\Solver.h"

#include <iostream>
using namespace std;


int main()
{
	data_input * input = read_input("ratings.csv");
	data_input * target = read_input("targets.csv", true);

	UserAveragesSolver * solver = new UserAveragesSolver();
	solver->solve(input, target);
	return 0;
}


#pragma once
#include "Solver.h"
class ColaborativeUserBasedSolver : public GenericSolver
{
public:
	ColaborativeUserBasedSolver(data_input * input);
	virtual float predict(string targetUser, string targetItem) override;
};


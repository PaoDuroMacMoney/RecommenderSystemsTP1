#pragma once

#include "Util.h"
class ISolver
{
public:
	virtual ~ISolver();
	virtual float predict(data_input * input, string targetUser, string targetItem) = 0;
	virtual void solve(data_input * input, data_input * target, vector<int> selectedIndexes = vector<int>(0)) = 0;
};

class GenericSolver : ISolver
{
	virtual void solve(data_input * input, data_input * target, vector<int> selectedIndexes = vector<int>(0)) override;
};


#pragma once

#include "Util.h"
class ISolver
{
public:
	virtual float predict(data_input * input, string targetUser, string targetItem) = 0;
	virtual void solve(data_input * input, data_input * target, vector<int> selectedIndexes = vector<int>(0)) = 0;
};

class GenericSolver : public ISolver
{
public:
	virtual void solve(data_input * input, data_input * target, vector<int> selectedIndexes = vector<int>(0)) override;
};

class ConstantOutputSolver : public GenericSolver
{
public:
	ConstantOutputSolver();
	virtual float predict(data_input * input, string targetUser, string targetItem) override;
};

class UserAveragesSolver : public GenericSolver
{
public:
	UserAveragesSolver();
	virtual float predict(data_input * input, string targetUser, string targetItem) override;
};

#pragma once

#include "Util.h"
class ISolver
{
public:
	virtual float predict(string targetUser, string targetItem) = 0;
	virtual void solve( data_input * target, vector<int> selectedIndexes = vector<int>(0)) = 0;
};

class GenericSolver : public ISolver
{
public:
	GenericSolver(data_input * input);
	virtual void solve(data_input * target, vector<int> selectedIndexes = vector<int>(0)) override;
protected:
	data_input * input;
};

class ConstantOutputSolver : public GenericSolver
{
public:
	ConstantOutputSolver(data_input * input);
	virtual float predict(string targetUser, string targetItem) override;
};

class UserAveragesSolver : public GenericSolver
{
public:
	UserAveragesSolver(data_input * input);
	virtual float predict(string targetUser, string targetItem) override;
};
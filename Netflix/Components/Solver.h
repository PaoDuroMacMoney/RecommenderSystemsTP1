#pragma once

#include "Util.h"
class Parameters{};

class ISolver
{
public:
	virtual float predict(string targetUser, string targetItem) = 0;
	virtual void solve(data_input * target) = 0;
	virtual void updateInput(data_input * newInput) = 0;
	virtual void beforePredict() = 0;
};

class GenericSolver : public ISolver
{
public:
	GenericSolver(data_input * input, Parameters * parameters = new Parameters);
	virtual void solve(data_input * target) override;	
	virtual void beforePredict() override;
	void updateInput(data_input * newInput) override;
protected:
	data_input * input;
	Parameters * parameters;
	float getBlindGuess(string targetUser, string targetItem);
private:
	int predicted = 0;
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
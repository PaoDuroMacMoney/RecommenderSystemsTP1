#pragma once

#include "Util.h"
class Parameters
{
public:
	virtual string getAlgorithmName() = 0;
	virtual string print();
};

class DummyParameters:public Parameters
{
public:
	virtual string getAlgorithmName() override { return ""; };
	virtual string print() override { return ""; };
};

class ISolver
{
public:
	virtual float predict(string targetUser, string targetItem) = 0;
	virtual void solve(data_input * target) = 0;
	virtual void updateInput(data_input * newInput) = 0;
	virtual void beforePredict() = 0;
	virtual void afterPredict() = 0;
	virtual string printParams() = 0;
	virtual bool compareFunc(data_input * input, int i, int j) = 0;
};

class GenericSolver : public ISolver
{
public:
	GenericSolver(data_input * input, Parameters * parameters = new DummyParameters);
	virtual void solve(data_input * target) override;	
	virtual void beforePredict() override;
	virtual void afterPredict() override;
	virtual string printParams();
	void updateInput(data_input * newInput) override;
	virtual bool compareFunc(data_input * input, int i, int j) override;
	virtual bool sortBeforeSolveFunc(data_node i, data_node j) = 0;
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
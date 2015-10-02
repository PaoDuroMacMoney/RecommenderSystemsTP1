#pragma once
#include "Solver.h"
#include <unordered_map>

class ColaborativeUserBasedParameters : public Parameters
{
public:
	ColaborativeUserBasedParameters(int neighboorsAmount, bool userMaxMinLimit);
	void update(int neighboorsAmount, bool userMaxMinLimit);
public:
	bool limitByUserMaxMin = false;
	int neighboors = 0;
};

class ColaborativeUserBasedSolver : public GenericSolver
{
private:
	string lastUser = "";
	unordered_map<string, neighboor *> * neighboors = new unordered_map<string, neighboor *>;
public:
	ColaborativeUserBasedParameters * getParams();
	virtual void beforePredict() override;
	ColaborativeUserBasedSolver(data_input * input, Parameters * params);
	vector<neighboor *> getUserNeighboors(data_input * input,string userId, string itemId);
	void updateNeighboorhood(unordered_map<string, neighboor *> * neighboors,string neighboorId,float targetRating,float neighboorRate, string ratedItemId);
	virtual float predict(string targetUser, string targetItem) override;
};

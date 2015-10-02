#pragma once
#include "Solver.h"
#include <unordered_map>
class ColaborativeUserBasedSolver : public GenericSolver
{
private:
	string lastUser = "";
	unordered_map<string, neighboor *> * neighboors = new unordered_map<string, neighboor *>;
public:
	virtual void beforePredict() override;
	ColaborativeUserBasedSolver(data_input * input, Parameters * params);
	vector<neighboor *> getUserNeighboors(data_input * input,string userId, string itemId);
	void updateNeighboorhood(unordered_map<string, neighboor *> * neighboors,string neighboorId,float targetRating,float neighboorRate, string ratedItemId);
	virtual float predict(string targetUser, string targetItem) override;
};

class ColaborativeUserBasedParameters : public Parameters
{
public:
	ColaborativeUserBasedParameters(int neighboorsAmount);
	void update(int neighboorsAmount);	
private:
	int neighboors = 0;
};
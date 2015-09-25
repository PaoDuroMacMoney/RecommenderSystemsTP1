#pragma once
#include "Solver.h"
class ColaborativeUserBasedSolver : public GenericSolver
{
public:
	ColaborativeUserBasedSolver(data_input * input);
	vector<neighboor *> getUserNeighboors(data_input * input,string userId, string itemId);
	void updateNeighboorhood(unordered_map<string, neighboor *> * neighboors,string neighboorId,float targetRating,float neighboorRate);
	virtual float predict(string targetUser, string targetItem) override;
};


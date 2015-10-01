#pragma once
#include "Solver.h"
#include <unordered_map>
class ColaborativeUserBasedSolver : public GenericSolver
{
private:
	string lastUser = "";
	unordered_map<string, neighboor *> * neighboors = new unordered_map<string, neighboor *>;
public:
	ColaborativeUserBasedSolver(data_input * input);
	vector<neighboor *> getUserNeighboors(data_input * input,string userId, string itemId);
	void updateNeighboorhood(unordered_map<string, neighboor *> * neighboors,string neighboorId,float targetRating,float neighboorRate, string ratedItemId);
	virtual float predict(string targetUser, string targetItem) override;
};


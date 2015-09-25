#include "ColaborativeUserBasedSolver.h"
#include <iostream>


ColaborativeUserBasedSolver::ColaborativeUserBasedSolver(data_input * input) : GenericSolver(input) 
{
	input->normalizeUsers();
}

float ColaborativeUserBasedSolver::predict(string targetUser, string targetItem)
{
	vector<neighboor> neighboors = input->getNeighboorsForItem(targetUser, targetItem);
	float score = 0, normalizeFactor = 0;
	for (unsigned  int i = 0; i < neighboors.size(); i++)
	{
		neighboor item = neighboors[i];
		score += item.similarity * item.value;
		normalizeFactor += item.similarity;
	}
	score = score / normalizeFactor;

	return input->userInfo[targetUser]->denormalize(score);
}

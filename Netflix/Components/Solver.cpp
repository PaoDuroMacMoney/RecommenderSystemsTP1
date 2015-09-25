#include "Solver.h"
#include <fstream>
#include <iostream>

GenericSolver::GenericSolver(data_input * inputPtr)
{
	input = inputPtr;
}

void GenericSolver::solve( data_input * target, vector<int> selectedIndexes)
{
	std::ofstream fout("submission.csv");
	fout << "UserId:ItemId,Prediction"<< std::endl;

	for (int i = 0; i < target->length; i++)
	{
		data_node node = target->data[i];
		node.value = predict(node.userId, node.itemId);
		fout << node.userId <<":"<< node.itemId<< ","<< node.value << std::endl;
	}
	fout.close();
}

ConstantOutputSolver::ConstantOutputSolver(data_input * input) : GenericSolver(input){}

float ConstantOutputSolver::predict(string targetUser, string targetItem)
{
	return 5.5f;
}

UserAveragesSolver::UserAveragesSolver(data_input * input) : GenericSolver(input) {}

float UserAveragesSolver::predict( string targetUser, string targetItem)
{
	auto userIterator = input->userInfo.find(targetUser);
	if (userIterator == input->userInfo.end())
	{
		//o usuário não tem notas, o chute escolhido será a média do item
		auto itemIterator = input->userInfo.find(targetUser);
		if (itemIterator == input->userInfo.end())
		{
			//não tem nem o usuário nem o item no treino, o chute será a média geral
			return input->generalAverage;
		}
		return itemIterator->second->getAverage();
	}
	return userIterator->second->getAverage();
}

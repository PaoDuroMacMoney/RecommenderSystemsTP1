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
		std::cout << ++predicted << " Usu�rio: " << node.userId << ", Item: " << node.itemId << ", predi��o: " << node.value << std::endl;
		fout << node.userId <<":"<< node.itemId<< ","<< node.value << std::endl;
	}
	fout.close();
}

float GenericSolver::getBlindGuess(string targetUser, string targetItem)
{
	auto userIterator = input->userInfo.find(targetUser);
	auto itemIterator = input->itemInfo.find(targetItem);
	if (userIterator == input->userInfo.end())
	{
		//o usu�rio n�o tem notas, o chute escolhido ser� a m�dia do item		
		if (itemIterator == input->itemInfo.end())
		{
			//n�o tem nem o usu�rio nem o item no treino, o chute ser� a m�dia geral
			return input->generalAverage;
		}
		return itemIterator->second->getAverage();
	}
	if (itemIterator == input->itemInfo.end())
	{
		return userIterator->second->getAverage();
	}
	return 0.0f;
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
		//o usu�rio n�o tem notas, o chute escolhido ser� a m�dia do item
		auto itemIterator = input->userInfo.find(targetUser);
		if (itemIterator == input->userInfo.end())
		{
			//n�o tem nem o usu�rio nem o item no treino, o chute ser� a m�dia geral
			return input->generalAverage;
		}
		return itemIterator->second->getAverage();
	}
	return userIterator->second->getAverage();
}

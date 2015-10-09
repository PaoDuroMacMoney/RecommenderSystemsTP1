#include "Solver.h"
#include <fstream>
#include <iostream>
#include <algorithm>   
#include <functional>

GenericSolver::GenericSolver(data_input * inputPtr, Parameters * parametersPtr)
{
	input = inputPtr;	
	parameters = parametersPtr;
}


bool GenericSolver::compareFunc(data_input * input, int i, int j)
{
	return sortBeforeSolveFunc(input->data[i], input->data[j]);
}

void GenericSolver::solve( data_input * target)
{
	std::ofstream fout("submission.csv");
	fout << "UserId:ItemId,Prediction"<< std::endl;
	beforePredict();
	vector<data_node> sortedNodes;

	for (int i = 0; i < target->length; i++)
	{
		sortedNodes.push_back(target->data[i]);
	}
	std::sort(sortedNodes.begin(), sortedNodes.end(), std::bind(&GenericSolver::sortBeforeSolveFunc, this,
		std::placeholders::_1, std::placeholders::_2));

	for (int i = 0; i < sortedNodes.size(); i++)
	{
		data_node node = sortedNodes[i];
		node.value = predict(node.userId, node.itemId);
		//std::cout << ++predicted << " User: " << node.userId << ", Item: " << node.itemId << ", prediction: " << node.value << std::endl;
		if(++predicted % 1000 == 0)
			std::cout << predicted << " predictions done" << std::endl;
		fout << node.userId <<":"<< node.itemId<< ","<< node.value << std::endl;
	}
	fout.close();

	afterPredict();
}

void GenericSolver::beforePredict() {}
void GenericSolver::afterPredict() {}

string GenericSolver::printParams()
{
	return parameters->print();
}

void GenericSolver::updateInput(data_input * newInput)
{
	input = newInput;
}

float GenericSolver::getBlindGuess(string targetUser, string targetItem)
{
	auto userIterator = input->userInfo.find(targetUser);
	auto itemIterator = input->itemInfo.find(targetItem);
	if (userIterator == input->userInfo.end())
	{
		//o usuário não tem notas, o chute escolhido será a média do item		
		if (itemIterator == input->itemInfo.end())
		{
			//não tem nem o usuário nem o item no treino, o chute será a média geral
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

string Parameters::print()
{
	return "";
}

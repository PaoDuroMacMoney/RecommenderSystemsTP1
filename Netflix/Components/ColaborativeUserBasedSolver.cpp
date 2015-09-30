#include "ColaborativeUserBasedSolver.h"
#include <iostream>
#include <algorithm>    // std::min
#include <math.h>


ColaborativeUserBasedSolver::ColaborativeUserBasedSolver(data_input * input) : GenericSolver(input) 
{
	input->normalizeUsers();
}

vector<neighboor *> ColaborativeUserBasedSolver::getUserNeighboors(data_input * input, string targetUser, string targetItem)
{
	vector<data_node*>* ratedItemsForUser = &input->userInfo[targetUser]->ratedList;
	if (input->userInfo[targetUser]->neighboors == nullptr)
	{
		unordered_map<string, neighboor *> * neighboors = new unordered_map<string, neighboor *>;
		for (unsigned int i = 0; i < ratedItemsForUser->size(); i++)
		{
			//como já está tudo normalizado o cálculo da similaridade de pearson pode ser simplificado, todos
			//os termos de média serão 0, e fica equivalente com o cosseno.
			float targetRating = (*ratedItemsForUser)[i]->value;
			string ratedItemId = (*ratedItemsForUser)[i]->itemId;
			for (unsigned int j = 0; j < input->itemInfo[ratedItemId]->ratedList.size(); j++)
			{
				string neighboorId = input->itemInfo[ratedItemId]->ratedList[j]->userId;
				float neighboorRate = input->itemInfo[ratedItemId]->ratedList[j]->value;
				if (neighboorId != targetUser && neighboorRate != 0 && targetRating !=0)
				{
					updateNeighboorhood(neighboors, neighboorId, targetRating, neighboorRate);
				}
			}
		}
		input->userInfo[targetUser]->neighboors = neighboors;
		for (auto iterator = input->userInfo[targetUser]->neighboors->begin();
			iterator != input->userInfo[targetUser]->neighboors->end(); iterator++)
		{
			neighboor * neighboor = iterator->second;
			neighboor->similarity = neighboor->numeratorTemp / (sqrt(neighboor->denominatorTemp1)*sqrt(neighboor->denominatorTemp2));
			float cost = std::min(neighboor->commonRates / 50, 1.0f);
			neighboor->similarity *= cost;
		}
	}
	vector<neighboor *> result;
	for (auto iterator = input->userInfo[targetUser]->neighboors->begin(); iterator != input->userInfo[targetUser]->neighboors->end(); iterator++)
	{
		neighboor * neighboor = iterator->second;
		float targetItemNeighboorRate = input->getItemRate(neighboor->neighboorId,targetItem);
		if (targetItemNeighboorRate != FLT_MIN)
		{
			neighboor->value = targetItemNeighboorRate;
			result.push_back(neighboor);
		}
	}
	return result;
}

void ColaborativeUserBasedSolver::updateNeighboorhood(unordered_map<string, neighboor *>* neighboors, 
	string neighboorId, float targetRating, float neighboorRate)
{
	neighboor * neighboorToUpdate;
	auto iterator = neighboors->find(neighboorId);
	if (iterator == neighboors->end())
	{
		neighboorToUpdate = new neighboor;
		neighboorToUpdate->neighboorId = neighboorId;
		neighboors->insert(pair<string, neighboor *>(neighboorId, neighboorToUpdate));
	}
	else
	{
		neighboorToUpdate = iterator->second;
	}

	neighboorToUpdate->numeratorTemp += (targetRating*neighboorRate);
	neighboorToUpdate->denominatorTemp1 += (targetRating*targetRating);
	neighboorToUpdate->denominatorTemp2 += (neighboorRate*neighboorRate);

	neighboorToUpdate->commonRates++;
}

float ColaborativeUserBasedSolver::predict(string targetUser, string targetItem)
{
	float blindGuess = getBlindGuess(targetUser, targetItem);
	if (blindGuess != 0) 
	{
		//o usuário não tem avaliações chute será a média para o item, 
		//caso o item não tenha avaliações o chute será a média global.
		return blindGuess;
	}
	vector<neighboor*> neighboors = getUserNeighboors(input, targetUser, targetItem);
	if (neighboors.size() == 0)
	{
		//item não tem avaliações, ou itens que o usuário avaliou não têm vizinhança, 
		//o chute será a média do usuário
		return input->userInfo[targetUser]->getAverage();
	}
	double score = 0, normalizeFactor = 0;
	for (unsigned  int i = 0; i < neighboors.size(); i++)
	{
		neighboor * item = neighboors[i];
		score += item->similarity * item->value;
		normalizeFactor += std::abs(item->similarity);
	}
	score = score / normalizeFactor;

	float result = input->userInfo[targetUser]->denormalize(score);
	float userAverage = input->userInfo[targetUser]->getAverage();
	float userStdDeviation = input->userInfo[targetUser]->getStdDeviation();
	float prediction = std::min(10.0f, std::max(1.0f, result));	
	return prediction;
}

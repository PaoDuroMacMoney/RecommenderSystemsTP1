#include "Solver.h"
#include <fstream>

void GenericSolver::solve(data_input * input, data_input * target, vector<int> selectedIndexes)
{
	input->userItem = new Matrix(input->users, input->items);

	int userIndex, itemIndex;
	for (int i = 0; i < input->length; i++)
	{
		data_node node = input->data[i];
		userIndex = input->userIndex[node.userId];
		itemIndex = input->itemIndex[node.itemId];
		(* input->userItem)(userIndex, itemIndex) = node.value;
	}

	std::ofstream fout("submission.csv");
	fout << "UserId:ItemId,Prediction"<< std::endl;

	for (int i = 0; i < target->length; i++)
	{
		data_node node = target->data[i];
		node.value = predict(input, node.userId, node.itemId);
		fout << node.userId <<":"<< node.itemId<< ","<< node.value << std::endl;
	}
	fout.close();
}

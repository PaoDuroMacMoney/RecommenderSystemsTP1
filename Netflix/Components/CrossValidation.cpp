#include "CrossValidation.h"
#include "Util.h"
#include "MathFuncs.h"
#include "Solver.h"
#include <iostream>

#include <algorithm>
#include <cmath>

using namespace std;

bool compareUsers(int i, int j) 
{ 
	return g_originalInput->data[i].userId < g_originalInput->data[j].userId;
}

float crossValidation(int folds, data_input * input, ISolver &solver)
{
	g_originalInput = input;
	int inputLength = input->length;

	//create shuffled positions array
	vector<int> shuffled(inputLength);
	for (int i = 0; i < inputLength; i++)
		shuffled[i] = i;
	random_shuffle(shuffled.begin(), shuffled.end());

	//iterate folders
	double totalError = 0;
	int foldInstances = inputLength / folds;
	for (int fold = 0; fold < folds; fold++)
	{
		std::cout << "Calculating folder " << fold << std::endl;
		int begin = fold*foldInstances;
		int end = min(begin + foldInstances, inputLength);

		//separate data outside folder for training, and on folder for validation
		vector<int> allButFolder;
		vector<int> folder;
		for (int i = 0; i < inputLength; i++)
			if(i >= begin && i < end)
				folder.push_back(shuffled[i]);
			else
				allButFolder.push_back(shuffled[i]);
		std::sort(folder.begin(), folder.end(), compareUsers);

		data_input * crossValidationInput = select_input(input, &allButFolder);
		solver.updateInput(crossValidationInput);
		solver.beforePredict();
		double iterationError = 0;

		int contador = 0;
		for (unsigned int ii = 0; ii < folder.size(); ii++)
		{
			if (++contador % 1000 == 0)
				std::cout << contador << " predictions done" << std::endl;
			int index = folder[ii];
			float realValue = input->data[index].value;			
			string userId = input->data[index].userId;
			string itemId = input->data[index].itemId;

			float predictedValue = solver.predict(userId, itemId);

			iterationError += rmse(realValue, predictedValue);
		}
		totalError += iterationError;
		std::cout << "folder " << fold <<" error = "<< iterationError << std::endl;
	}
	return totalError / inputLength;
}
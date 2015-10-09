#include "CrossValidation.h"
#include "Util.h"
#include "Solver.h"
#include <iostream>

#include <algorithm>
#include <cmath>
#include <functional>

using namespace std;

bool CrossValidation::compareFunc(int i, int j)
{ 
	return currentSolver->compareFunc(originalInput, i, j);
}

float CrossValidation::run()
{
	int inputLength = originalInput->length;

	//create shuffled positions array
	vector<int> shuffled(inputLength);
	for (int i = 0; i < inputLength; i++)
		shuffled[i] = i;
	random_shuffle(shuffled.begin(), shuffled.end());

	//iterate folders
	float totalError = 0;
	int foldInstances = inputLength / folds;
	for (int fold = 0; fold < folds; fold++)
	{
		std::cout << "Calculating folder " << fold << std::endl;
		int begin = fold*foldInstances;
		int end = min(begin + foldInstances, inputLength);

		//separate data outside folder for training, and on folder for validation
		vector<int> allButFolder(0);
		vector<int> folder(0);
		for (int i = 0; i < inputLength; i++)
			if(i >= begin && i < end)
				folder.push_back(shuffled[i]);
			else
				allButFolder.push_back(shuffled[i]);
		std::sort(folder.begin(), folder.end(), std::bind(&CrossValidation::compareFunc,this,
			std::placeholders::_1,std::placeholders::_2));

		data_input * crossValidationInput = select_input(originalInput, &allButFolder);
		currentSolver->updateInput(crossValidationInput);
		currentSolver->beforePredict();
		float iterationError = 0;

		int index;
		float realValue, predictedValue, diff;
		string userId, itemId;
		for (unsigned int ii = 0; ii < folder.size(); ii++)
		{
			//if (ii % 1000 == 0)
			//	std::cout << ii << " predictions done" << std::endl;
			index = folder[ii];
			realValue = originalInput->data[index].value;
			userId = originalInput->data[index].userId;
			itemId = originalInput->data[index].itemId;

			predictedValue = currentSolver->predict(userId, itemId);
			diff = realValue - predictedValue;
			iterationError += diff * diff;
		}
		float rmse = std::sqrt(iterationError / (float)folder.size());
		totalError += rmse;
		currentSolver->afterPredict();
		std::cout << "folder " << fold <<" error = "<< rmse << std::endl;
	}
	float result = totalError / folds;
	std::cout << "RMSE = " << result << " for " << currentSolver->printParams() << std::endl;
	std::cout << std::endl;
	return result;
}

CrossValidation::CrossValidation(int folders, data_input * input,ISolver * solver)
{
	folds = folders;
	originalInput = input;
	currentSolver = solver;
}


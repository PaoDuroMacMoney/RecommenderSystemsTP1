#include "CrossValidation.h"
#include "Util.h"
#include "MathFuncs.h"

#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

double crossValidation(int folds, data_input * input, float(*predictFunc) (data_input *, vector<int>, int, int))
{
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

		double iterationError = 0;
		for (int ii = begin; ii < end; ii++)
		{
			int index = shuffled[ii];
			float realValue = input->value[index];
			
			int user = input->data[index].user;
			int item = input->data[index].item;

			float predictedValue = (*predictFunc)(input, allButFolder, user, item);

			iterationError += rmse(realValue, predictedValue);
		}
		totalError += iterationError;
	}
	return totalError / inputLength;
}
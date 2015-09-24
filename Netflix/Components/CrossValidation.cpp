#include "CrossValidation.h"
#include "Util.h"
#include "MathFuncs.h"

#include <algorithm>
#include <cmath>

using namespace std;

double crossValidation(int folds, data_input * input, float(*predictFunc) (data_input *, string, string, vector<int>))
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
		for (int i = 0; i < inputLength; i++)
			if(!(i >= begin && i < end))
				allButFolder.push_back(shuffled[i]);

		double iterationError = 0;
		for (int ii = begin; ii < end; ii++)
		{
			int index = shuffled[ii];
			float realValue = input->data[index].value;			
			string userId = input->data[index].userId;
			string itemId = input->data[index].itemId;

			float predictedValue = (*predictFunc)(input, userId, itemId, allButFolder);

			iterationError += rmse(realValue, predictedValue);
		}
		totalError += iterationError;
	}
	return totalError / inputLength;
}
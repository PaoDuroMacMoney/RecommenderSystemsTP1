#include "CrossValidation.h"
#include "Util.h"

#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

double cross_validation(int folds, data_input * prob)
{
	vector<int> order(prob->length);
	for (int i = 0; i < prob->length; i++)
		order[i] = i;
	random_shuffle(order.begin(), order.end());

	double loss = 0;
	int nr_instance_per_fold = prob->length / folds;
	for (int fold = 0; fold < folds; fold++)
	{
		int begin = fold*nr_instance_per_fold;
		int end = min(begin + nr_instance_per_fold, prob->length);

		vector<int> order1;
		for (int i = 0; i < begin; i++)
			order1.push_back(order[i]);
		for (int i = end; i < prob->length; i++)
			order1.push_back(order[i]);

		data_model * model = train(prob, order1);

		double loss1 = 0;
		for (int ii = begin; ii < end; ii++)
		{
			int i = order[ii];

			double y = prob->Y[i];

			data_node *begin = &prob->X[prob->P[i]];

			data_node *end = &prob->X[prob->P[i + 1]];

			double y_bar = predict(begin, end, model);

			loss1 -= y == 1 ? log(y_bar) : log(1 - y_bar);
		}
		loss += loss1;
	}
	return loss / prob-> length;
}
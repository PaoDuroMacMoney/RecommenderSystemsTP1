#pragma once

double crossValidation(int folds, data_input * input, float(*predictFunc)(data_input *, vector<int>, int, int));

#pragma once
#include "Solver.h"
#include "Util.h"

double crossValidation(int folds, data_input * input, ISolver &solver);

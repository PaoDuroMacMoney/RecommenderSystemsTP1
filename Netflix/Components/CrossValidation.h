#pragma once
#include "Solver.h"
#include "Util.h"

static data_input * g_originalInput;

float crossValidation(int folds, data_input * input, ISolver &solver);
bool compareUsers(int i, int j);
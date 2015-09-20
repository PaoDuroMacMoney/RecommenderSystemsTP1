#include "Util.h"
#include <algorithm>
#include <string>

using namespace std;

int const MAX_LINE_SIZE = 100000;

data_input * read_input(char const *path)
{
	if (strlen(path) == 0)
		return nullptr;

	FILE * file;
	fopen_s(&file, path, "r");

	data_input * input = new data_input;
	input->length = 0;
	input->n = 0;
	input->m = 0;
	input->X = nullptr;
	input->P = nullptr;
	input->Y = nullptr;

	char line[MAX_LINE_SIZE];

	long nnz = 0;
	for (; fgets(line, MAX_LINE_SIZE, file) != nullptr; input->length++)
	{
		strtok(line, " \t");
		for (; ; nnz++)
		{
			char *ptr = strtok(nullptr, " \t");
			if (ptr == nullptr || *ptr == '\n')
				break;
		}
	}
	rewind(file);

	input->X = new data_node[nnz];
	input->P = new long long[input->length + 1];
	input->Y = new float[input->length];

	long long p = 0;
	input->P[0] = 0;
	for (int i = 0; fgets(line, MAX_LINE_SIZE, file) != nullptr; i++)
	{
		char *y_char = strtok(line, " \t");
		float y = (atoi(y_char)>0) ? 1.0f : -1.0f;
		input->Y[i] = y;

		for (; ; p++)
		{
			char *field_char = strtok(nullptr, ":");
			char *idx_char = strtok(nullptr, ":");
			char *value_char = strtok(nullptr, " \t");
			if (field_char == nullptr || *field_char == '\n')
				break;

			int field = atoi(field_char);
			int idx = atoi(idx_char);
			float value = atof(value_char);

			input->m = max(input->m, field + 1);
			input->n = max(input->n, idx + 1);

			input->X[p].field = field;
			input->X[p].index = idx;
			input->X[p].value = value;
		}
		input->P[i + 1] = p;
	}

	fclose(file);

	return input;
}

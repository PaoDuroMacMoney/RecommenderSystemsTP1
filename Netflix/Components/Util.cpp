#include "Util.h"
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

int const MAX_LINE_SIZE = 100000;

data_input * read_input(char const *path)
{
	data_input * input = new data_input;

	input->length = 0;

	string line;
	ifstream myfile(path);

	while (getline(myfile, line))
		input->length++;
	input->length--; //remove header from count

	input->data = new data_node[input->length];
	input->value = new float[input->length];

	ifstream infile(path);

	//input format: u0026762:i2171847,6,1362062307
	char u = 'u', i = 'i', comma = ',', dblPoint = ':';
	int user, item, value, timestamp;

	string header;
	getline(infile, header);//ignore header

	int index = 0;
	while (infile >> u >> user>> dblPoint >> i >> item >> comma >> value >> comma >> timestamp)
	{
		data_node * node = new data_node;
		node->user = user;
		node->item = item;
		node->timestamp = timestamp;
		input->data[index] = *node;

		input->value[index] = value;
		index++;
	}

	return input;
}

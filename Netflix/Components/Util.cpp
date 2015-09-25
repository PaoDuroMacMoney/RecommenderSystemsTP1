#include "Util.h"
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream> 

data_input * read_input(char const *path, bool isTarget)
{
	data_input * input = new data_input;

	input->isTarget = isTarget;
	input->length = 0;

	string line;
	ifstream myfile(path);

	std::cout << "Counting lines" << endl;

	while (getline(myfile, line))
		input->length++;
	input->length--; //remove header from count

	std::cout << input->length << " lines" << endl;

	input->data = new data_node[input->length];

	ifstream infile(path);

	string header;
	getline(infile, header);//ignore header

	std::cout << "Loading data to memory" << endl;

	while (infile >> *input){}
	input->generalAverage = input->generalAverage / input->length;

	std::cout << "Loaded..." << endl;
	return input;
}

std::istream & operator>>(std::istream & stream, data_input & input)
{
	if (input.isTarget)
	{
		readAsTarget(stream, input);
	}
	else
	{
		readAsInput(stream, input);
	}
	
	return stream;
}

void readAsInput(std::istream & stream, data_input & input)
{
	//input format: u0026762:i2171847,6,1362062307
	std::string line;
	string userId, itemId, timestamp, value;
	if (std::getline(stream, line))
	{
		std::stringstream iss(line);

		if (std::getline(iss, userId, ':') &&
			std::getline(iss, itemId, ',') &&
			std::getline(iss, value, ',') &&
			std::getline(iss, timestamp, '\n'))
		{
			data_node * node = new data_node;
			node->userId = userId;
			node->itemId = itemId;
			node->value = stof(value);
			node->timestamp = stoi(timestamp);

			loadMap(&input.userInfo, node->userId, input.insertIndex, &input);
			loadMap(&input.itemInfo, node->itemId, input.insertIndex, &input);

			input.generalAverage += node->value;
			input.data[input.insertIndex] = *node;
			input.insertIndex++;
		}
		else
		{
			stream.setstate(std::ios::failbit);
		}
	}
}

void loadMap(unordered_map<string, data_info *> * map, string key, int index, data_input * parent)
{
	auto iterator = map->find(key);
	data_info * info;
	if (iterator == map->end())
	{
		info = new data_info();
		info->parent = parent;
		map->insert(pair<string, data_info *>(key, info));		
	}
	else
	{
		info = iterator->second;
	}
	
	info->indexes.push_back(index);
	info->count++;
}

void readAsTarget(std::istream & stream, data_input & input)
{
	//target format: u0000039:i0060196
	std::string line;
	string userId, itemId;
	if (std::getline(stream, line))
	{
		std::stringstream iss(line);

		if (std::getline(iss, userId, ':') &&
			std::getline(iss, itemId, '\n'))
		{
			data_node * node = new data_node;
			node->userId = userId;
			node->itemId = itemId;
			node->value = 0;
			node->timestamp = 0;

			input.data[input.insertIndex] = *node;
			input.insertIndex++;
		}
		else
		{
			stream.setstate(std::ios::failbit);
		}
	}
}

float data_info::getAverage()
{
	if (average == 0)
	{
		float sum = 0;
		int valueIndex;
		for (int i = 0; i < count; i++)
		{
			valueIndex = indexes[i];
			sum += ((data_input *)parent)->data[valueIndex].value;
		}
		average = sum / count;
	}
	return average;
}

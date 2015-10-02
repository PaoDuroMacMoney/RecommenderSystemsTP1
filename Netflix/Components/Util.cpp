#include "Util.h"
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream> 

data_input * select_input(data_input * completeInput, vector<int> * allButFolder)
{
	data_input * filteredInput = new data_input;
	filteredInput->length = allButFolder->size();
	filteredInput->data = new data_node[filteredInput->length];

	for (unsigned int i = 0; i < allButFolder->size(); i++)
	{
		int selectedIndex = allButFolder->at(i);
		data_node * itemToAdd = &completeInput->data[selectedIndex];

		filteredInput->generalAverage += itemToAdd->value;
		filteredInput->data[i] = * itemToAdd;

		loadMap(&filteredInput->userInfo, itemToAdd->userId, itemToAdd);
		loadMap(&filteredInput->itemInfo, itemToAdd->itemId, itemToAdd);		
	}
	filteredInput->generalAverage = filteredInput->generalAverage / filteredInput->length;
	return filteredInput;
}

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

			loadMap(&input.userInfo, node->userId, node);
			loadMap(&input.itemInfo, node->itemId, node);

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

void loadMap(unordered_map<string, data_info *> * map, string key, data_node * node)
{
	auto iterator = map->find(key);
	data_info * info;
	if (iterator == map->end())
	{
		info = new data_info();
		map->insert(pair<string, data_info *>(key, info));		
	}
	else
	{
		info = iterator->second;
	}
	info->updateMaxMin(node->value);
	info->ratedList.push_back(node);
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
		for (int i = 0; i < count; i++)
		{
			sum += ratedList[i]->value;
		}
		average = sum / count;
	}
	return average;
}

void data_info::normalize()
{
	average = getAverage();
	std_deviation = getStdDeviation();

	for (int i = 0; i < count; i++)
	{
		ratedList[i]->value -= average;
		if (std_deviation != 0)
		{
			ratedList[i]->value /= std_deviation;
		}
	}
}

void data_info::denormalize()
{
	average = getAverage();
	std_deviation = getStdDeviation();

	for (int i = 0; i < count; i++)
	{		
		if (std_deviation != 0)
		{
			ratedList[i]->value *= std_deviation;
		}
		ratedList[i]->value += average;
	}
	resetValues();
}

void data_info::updateMaxMin(float value)
{
	if (value < min)
	{
		min = value;
	}
	if (value > max)
	{
		max = value;
	}
}

float data_info::denormalize(float score)
{
	if (std_deviation == 0)
		return average;
	float result = score * std_deviation + average;
	return result;
}

float data_info::getStdDeviation()
{
	if (count == 1)
		return 0;
	if (std_deviation == -1)
	{
		float sum = 0, mean = getAverage(), deviation;
		for (int i = 0; i < count; i++)
		{
			deviation = ratedList[i]->value - mean;
			sum += deviation * deviation;
		}
		std_deviation = sqrt(sum / (count - 1));
	}
	return std_deviation;
}

float data_info::getMax()
{
	return max;
}

float data_info::getMin()
{
	return min;
}

void data_info::resetValues()
{
	average = 0;
	std_deviation = 0;
	max = 1;
	min = 10;
}

void data_input::denormalizeUsers()
{
	for (auto iterator = itemInfo.begin(); iterator != itemInfo.end(); iterator++)
	{
		iterator->second->resetValues();
	}
	for (auto iterator = userInfo.begin(); iterator != userInfo.end(); iterator++)
	{
		iterator->second->denormalize();
	}
}

void data_input::normalizeUsers()
{	
	for (auto iterator = itemInfo.begin(); iterator != itemInfo.end(); iterator++)
	{
		iterator->second->getAverage();
		iterator->second->getStdDeviation();
	}
	for (auto iterator = userInfo.begin(); iterator != userInfo.end(); iterator++)
	{
		iterator->second->normalize();
	}
}


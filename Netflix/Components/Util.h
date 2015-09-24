#pragma once
#include <unordered_map>
#include <string>
#include "Matrix.h"

using namespace std;
struct data_node
{
	string userId;
	string itemId;
	int timestamp;
	float value;
};

class data_input
{
	friend std::istream & operator>>(std::istream & stream, data_input & input);

public:

	unordered_map <string, int> userIndex;
	unordered_map <string, int> itemIndex;
	int users;
	int items;
	int length;
	data_node * data;
	bool isTarget;
	int insertIndex;
	Matrix * userItem;
};

data_input * read_input(char const * path, bool isTarget = false);

void loadMap(unordered_map<string, int>* map, int * count, string key);
void readAsTarget(std::istream & stream, data_input & input);
void readAsInput(std::istream & stream, data_input & input);


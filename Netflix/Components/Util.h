#pragma once
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

struct data_node
{
	string userId;
	string itemId;
	int timestamp;
	float value;
};

class data_info
{
public:
	vector<int> indexes;
	int variance;
	int count;
	float getAverage();
	void * parent;
private:
	float average;
};

class data_input
{
	friend std::istream & operator>>(std::istream & stream, data_input & input);

public:

	unordered_map <string, data_info *> userInfo;
	unordered_map <string, data_info *> itemInfo;
	int length;
	data_node * data;
	bool isTarget;
	int insertIndex;
	float generalAverage;
};

data_input * read_input(char const * path, bool isTarget = false);

void loadMap(unordered_map<string, data_info *> * map, string key, int index, data_input * parent);
void readAsTarget(std::istream & stream, data_input & input);
void readAsInput(std::istream & stream, data_input & input);


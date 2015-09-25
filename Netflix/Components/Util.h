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

struct neighboor
{
	float similarity;
	float value;
};

class data_info
{
public:
	float getAverage();
	void normalize();
	float denormalize(float score);

	vector<int> indexes;
	int count;	
	void * parent;
private:
	float getStdDeviation();
	float average;
	float std_deviation=-1;
};

class data_input
{
	friend std::istream & operator>>(std::istream & stream, data_input & input);

public:
	void normalizeUsers();
	vector<neighboor> getNeighboorsForItem(string userId,string itemId);
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


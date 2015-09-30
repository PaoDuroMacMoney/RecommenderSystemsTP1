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
	string neighboorId;
	double numeratorTemp =0;
	double denominatorTemp1 =0;
	double denominatorTemp2 =0;
	double similarity =0;
	float value =0;
	float commonRates =0;
};

class data_info
{
public:
	float getAverage();
	float getStdDeviation();
	void normalize();
	float denormalize(float score);
	int count =0;	
	vector<data_node*> ratedList;
	unordered_map<string, neighboor *> * neighboors = nullptr;
private:		
	float average = 0;
	float std_deviation=-1;
};

class data_input
{
	friend std::istream & operator>>(std::istream & stream, data_input & input);

public:
	void normalizeUsers();	
	float getItemRate(string userId, string itemId);
	unordered_map <string, data_info *> userInfo;
	unordered_map <string, data_info *> itemInfo;
	int length;
	data_node * data;
	bool isTarget;
	int insertIndex;
	float generalAverage =0;
};

data_input * read_input(char const * path,int size = 0, bool isTarget = false, vector<int> * selection = (vector<int> *)nullptr);

void loadMap(unordered_map<string, data_info *> * map, string key, data_node * node);
void readAsTarget(std::istream & stream, data_input & input);
void readAsInput(std::istream & stream, data_input & input);


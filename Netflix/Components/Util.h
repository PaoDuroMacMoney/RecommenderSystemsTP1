#pragma once
struct data_node
{
	int user;
	int item;
	int timestamp;
};

struct data_input
{
	int length;
	data_node * data;
	float * value;
};

data_input * read_input(char const * path);

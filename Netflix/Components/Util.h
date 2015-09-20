#pragma once
struct data_node
{
	int field;
	int index;
	float value;
};

struct data_input
{
	int length;
	int n;
	int m;
	data_node * X;
	float * Y;
	long long *P;
};

struct data_model
{
	/*int n;
	int m;
	int k;
	float *W;
	bool normalization;*/
};


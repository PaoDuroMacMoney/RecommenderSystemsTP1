#pragma once
#include <vector>
class Matrix
{
public:
	Matrix(size_t rows, size_t cols);
	float& operator()(size_t i, size_t j);
	float operator()(size_t i, size_t j) const;

private:
	size_t mRows;
	size_t mCols;
	std::vector<float> mData;
};


#include "Matrix.h"
#include <vector>


Matrix::Matrix(size_t rows, size_t cols)
	: mRows(rows),
	mCols(cols),
	mData(rows * cols)
{
}

float& Matrix::operator()(size_t i, size_t j)
{
	return mData[i * mCols + j];
}

float Matrix::operator()(size_t i, size_t j) const
{
	return mData[i * mCols + j];
}

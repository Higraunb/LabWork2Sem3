#include "TVector.h"
#include "TDenseMatrix.h"
#include "TTriangleMatrix.h"

int main()
{
	TDenseMatrix<int> matrixA = { {1, 2}, {3, 4} };
	TDenseMatrix<int> matrixB = { {5, 6}, {7, 8} };
	cout << matrixA + matrixB;
	return 0;
}
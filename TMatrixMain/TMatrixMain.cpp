#include "TVector.h"
#include "TDenseRectangularMatrix.h"
#include "TTriangleMatrix.h"

int main()
{
	TTriangleMatrix<int> a{ {-1},{2,3} }, d{ {2}, {3, 4} }, c(-1, -2);
	cout << c;
	return 0;
}
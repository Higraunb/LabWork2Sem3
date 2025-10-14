#include "TVector.h"
#include "TDenseMatrix.h"
#include "TTriangleMatrix.h"
#include "TSparseMatrix.h"

int main()
{
	TSparseMatrix<int> a{ {1, 2, 3, 0},
												{2, 3, 3, 4},
												{2, 3, 4, 1},
												{0, 2, 1, 6} };
	TSparseMatrix<int> c{ {2, 2, 3, 0},
												{2, 3, 3, 4},
												{2, 3, 4, 1},
												{0, 2, 1, 4} };
	TSparseMatrix<int> d = c * a;
	operator <<(std::cout,d);
	return 0;
}
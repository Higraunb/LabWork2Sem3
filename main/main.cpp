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
	//cout << a;
	//cout << "\n";
	//cout << a[0][2];
	return 0;
}
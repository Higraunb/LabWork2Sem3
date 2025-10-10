#include "TVector.h"
template <class T>
class TBended
{
public:
	TBended();
	TBended(int len);
	TBended(const TBended&);
	TBended(TBended&&);
	~TBended();

private:
	TVector<TVector<T>> data;
	size_t row;
	size_t column;
};
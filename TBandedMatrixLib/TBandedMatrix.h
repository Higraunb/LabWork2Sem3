#include "TVector.h"
template <class T>
class TBendedMatirx
{
public:
	TBendedMatirx();
	TBendedMatirx(const size_t dim_, const size_t width_);
	TBendedMatirx(const TBendedMatirx& other);
	TBendedMatirx(const size_t dim_, const size_t width_, const T& other);
	TBendedx(TBendedMatirx&& other);
	TBendedMatirx(std::initializer_list<initializer_list<T>> init_list);

	size_t GetRow();
	size_t GetWidth();
	TVector<T> GetData();


	void SetDim(const size_t dim_);
	void SetWidth(const size_t width_);

	TVector<T> begin() noexcept;
	const TVector<T> cbegin() const noexcept;

	TVector<T> end() noexcept;
	const TVector<T> cend() const noexcept;

	bool empty() const noexcept;
	bool full() const noexcept;
	void Clear() noexcept;

	Row<T> operator[](size_t row_index);

	TBendedMatirx<T>& operator = (const TBendedMatirx<T>& other);
	TBendedMatirx<T>& operator = (TBendedMatirx<T>&& other) noexcept;
	TBendedMatirx<T> operator + (const TBendedMatirx<T>& other);
	TBendedMatirx<T> operator - (const TBendedMatirx<T>& other);
	TBendedMatirx<T> operator * (TBendedMatirx<T>& other);

	bool operator==(const TBendedMatirx<T>& other);
	bool operator!=(const TBendedMatirx<T>& other);

	template<class O>
	friend ostream& operator << (ostream& out, TBendedMatirx<O>& other);
	template<class O>
	friend istream& operator >> (istream& input, TBendedMatirx<O>& other);
private:
	struct data
	{
		size_t row;
		size_t column;
		T elem;
	};
};
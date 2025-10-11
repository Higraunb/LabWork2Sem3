#include "TVector.h"
#include <initializer_list>
using namespace std;
template <class T>
class TTriangleMatrix
{
public:

	TTriangleMatrix();
	TTriangleMatrix(const size_t dim_);
	TTriangleMatrix(const TTriangleMatrix& other);
	TTriangleMatrix(size_t dim_, const T& other);
	TTriangleMatrix(TTriangleMatrix&& other);
	TTriangleMatrix(std::initializer_list<initializer_list<T>> init_list);

	size_t GetDim();
	TVector<T> GetData();

	void SetDim(const size_t dim_);

	T* begin() noexcept;
	const T* begin() const noexcept;
	const T* cbegin() const noexcept;

	T* end() noexcept;
	const T* end() const noexcept;
	const T* cend() const noexcept;

	bool empty() const noexcept;
	bool full() const noexcept;
	void Clear() noexcept;

	Row<T> operator[](size_t row_index);
	const Row<T> operator[](size_t row_index) const;

	TTriangleMatrix& operator = (const TTriangleMatrix<T>& other);
	TTriangleMatrix& operator = (TTriangleMatrix <T>&& other) noexcept;
	TTriangleMatrix<T> operator + (const TTriangleMatrix<T>& other);
	TTriangleMatrix<T> operator - (const TTriangleMatrix<T>& other);
	TTriangleMatrix<T> operator * (TTriangleMatrix<T>& other);

	bool operator==(const TTriangleMatrix<T>& other);
	bool operator!=(const TTriangleMatrix<T>& other);

	template<class O>
	friend ostream& operator << (ostream& out, TTriangleMatrix<O>& other);
	template<class O>
	friend istream& operator >> (istream& input, TTriangleMatrix<O>& other);
private:
	size_t dim;
	TVector<T> data;
};

template<class T>
TTriangleMatrix<T>::TTriangleMatrix(): data()
{
	dim = 0;
}

template<class T>
TTriangleMatrix<T>::TTriangleMatrix(const size_t dim_)
{
	dim = dim_;
	data.SetSize(dim * (dim + 1) / 2);
}

template<class T>
TTriangleMatrix<T>::TTriangleMatrix(const TTriangleMatrix& other): data(other.data)
{
	dim = other.data.GetSize();
}

template<class T>
TTriangleMatrix<T>::TTriangleMatrix(size_t dim_, const T& other): data(dim_*(dim_ + 1) / 2)
{
	dim = dim_;
}

template<class T>
TTriangleMatrix<T>::TTriangleMatrix(TTriangleMatrix&& other)
{
	data = std::move(other.data);
	dim = other.dim;
	other.dim = 0;
}

template<class T>
TTriangleMatrix<T>::TTriangleMatrix(std::initializer_list<initializer_list<T>> init_list)
{
	dim = init_list.size();

	if (dim == 0) return;

	size_t row_index = 0;
	for (const auto& row_list : init_list)
	{
		size_t element_count = 0;
		for (const auto& element : row_list)
		{
			element_count++;
			(void)element;
		}

		if (element_count != row_index + 1)
			throw invalid_argument("Invalid triangular matrix dimensions");
		row_index++;
	}

	data.SetSize(dim * (dim + 1) / 2);

	size_t data_index = 0;
	for (const auto& row_list : init_list)
		for (const T& value : row_list) data[data_index++] = value;
}

template<class T>
inline size_t TTriangleMatrix<T>::GetDim()
{
	return dim;
}

template<class T>
inline TVector<T> TTriangleMatrix<T>::GetData()
{
	return data;
}

template<class T>
inline void TTriangleMatrix<T>::SetDim(const size_t dim_)
{
	dim = dim_;
}

template<class T>
inline T* TTriangleMatrix<T>::begin() noexcept
{
	return data;
}

template<class T>
inline const T* TTriangleMatrix<T>::begin() const noexcept
{
	return data;
}

template<class T>
inline const T* TTriangleMatrix<T>::cbegin() const noexcept
{
	return data;
}

template<class T>
inline T* TTriangleMatrix<T>::end() noexcept
{
	return data + (dim * (dim + 1) / 2);
}

template<class T>
inline const T* TTriangleMatrix<T>::end() const noexcept
{
	return data + (dim * (dim + 1) / 2);
}

template<class T>
inline const T* TTriangleMatrix<T>::cend() const noexcept
{
	return data + (dim * (dim + 1) / 2);
}

template<class T>
inline bool TTriangleMatrix<T>::empty() const noexcept
{
	return data.empty();
}

template<class T>
inline bool TTriangleMatrix<T>::full() const noexcept
{
	return data.full();
}

template<class T>
inline void TTriangleMatrix<T>::Clear() noexcept
{
	for (size_t i = 0; i < data.GetSize(); i++)
		data[i] = 0;
}

template<class T>
inline Row<T> TTriangleMatrix<T>::operator[](size_t row_index)
{
	return Row<T>();
}

template<class T>
inline const Row<T> TTriangleMatrix<T>::operator[](size_t row_index) const
{
	return Row<T>();
}

template<class T>
inline TTriangleMatrix<T>& TTriangleMatrix<T>::operator=(const TTriangleMatrix<T>& other)
{
	data = other.data;
	dim = other.data.GetSize();
	return *this;
}

template<class T>
inline TTriangleMatrix<T>& TTriangleMatrix<T>::operator=(TTriangleMatrix<T>&& other) noexcept
{
	data = other.data;
	dim = other.GetDim();
	other.data = T();
	other.dim = 0;
	return *this;
}

template<class T>
inline TTriangleMatrix<T> TTriangleMatrix<T>::operator+(const TTriangleMatrix<T>& other)
{
	if (data.GetSize() != other.data.GetSize())
		throw invalid_argument("Error matrix size not equals");
	TTriangleMatrix<T> res(data.GetSize());
	for (size_t i = 0; i < data.GetSize(); i++)
	{
		res[i] = data[i] + other.data[i];
	}
	return res;
}

template<class T>
inline TTriangleMatrix<T> TTriangleMatrix<T>::operator-(const TTriangleMatrix<T>& other)
{
	if (data.GetSize() != other.data.GetSize())
		throw invalid_argument("Error matrix size not equals");
	TTriangleMatrix<T> res(data.GetSize());
	for (size_t i = 0; i < data.GetSize(); i++)
	{
		res[i] = data[i] - other.data[i];
	}
	return res;;
}

template<class T>
inline TTriangleMatrix<T> TTriangleMatrix<T>::operator*(TTriangleMatrix<T>& other)
{
	if (dim != other.dim)
		throw invalid_argument("Error matrix size not equals");
	TTriangleMatrix<T> res(dim);
	for (size_t i = 0; i < dim; i++)
	{
		for (size_t j = 0; j <= i; j++)
		{
			T sum = T();
			for (size_t k = j; k <= i; k++)
				sum += data[(i * (i + 1) / 2) + k] * other.data[(k * (k + 1) / 2) + j];
			res.data[(i * (i + 1) / 2) + j] = sum;
		}
	}
	return res;
}

template<class T>
inline bool TTriangleMatrix<T>::operator==(const TTriangleMatrix<T>& other)
{
	return data == other.data;
}

template<class T>
inline bool TTriangleMatrix<T>::operator!=(const TTriangleMatrix<T>& other)
{
	return data != other.data;
}

template<class O>
inline ostream& operator<<(ostream& out, TTriangleMatrix<O>& other)
{
	for (size_t i = 0; i < other.GetDim(); i++)
	{
		for (size_t j = 0; j <= i; j++)
		{
			out << other.data[i + j] << "  ";
		}
		out << "\n";
	}
	return out;
}

template<class O>
inline istream& operator>>(istream& input, TTriangleMatrix<O>& other)
{
	for (size_t i = 0; i < other.GetDim(); i++)
	{
		for (size_t j = 0; j <= i; j++)
		{
			cout << "[" << i << "]" << "[" << j << "] : ";
			input >> other.data[i + j];
			cout << "\n";
		}
	}
	return input;
}

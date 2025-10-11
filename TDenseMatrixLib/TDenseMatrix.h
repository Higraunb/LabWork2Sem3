#include "TVector.h"
#include <initializer_list>
using namespace std;
template <class T>
class TDenseMatrix
{
public:

	TDenseMatrix();
	TDenseMatrix(const size_t row_, const size_t column_);
	TDenseMatrix(const TDenseMatrix& other);
	TDenseMatrix(size_t column_, size_t row_, const T& other);
	TDenseMatrix(TDenseMatrix&& other);
	TDenseMatrix(std::initializer_list<initializer_list<T>> init_list);

	size_t GetRow();
	size_t GetColumn();
	TVector<T> GetData();

	void SetRow(const size_t row_);
	void SetColumn(const size_t column_);

	//TVector<T> begin() noexcept;
	//const TVector<T> begin() const noexcept;
	//const TVector<T> cbegin() const noexcept;

	//TVector<T> end() noexcept;
	//const TVector<T> end() const noexcept;
	//const TVector<T> cend() const noexcept;

	bool empty() const noexcept;
	bool full() const noexcept;
	void Clear() noexcept;

	void push_back(const T& elem);
	void push_front(const T& elem);

	void pop_back();
	void pop_front();
	
	Row<T> operator[](size_t row_index);
	ConstRow<T> operator[](size_t row_index) const;
	
	TDenseMatrix& operator = (const TDenseMatrix<T>& other);
	TDenseMatrix& operator = (TDenseMatrix <T>&& other) noexcept;
	TDenseMatrix<T> operator + (const TDenseMatrix<T>& other);
	TDenseMatrix<T> operator - (const TDenseMatrix<T>& other);
	TDenseMatrix<T> operator * (const TDenseMatrix<T>& other);

	bool operator==(const TDenseMatrix<T>& other);
	bool operator!=(const TDenseMatrix<T>& other);

	template<class O>
	friend ostream& operator << (ostream& out, TDenseMatrix<O>& other);
	template<class O>
	friend istream& operator >> (istream& input, TDenseMatrix<O>& other);
private:
	size_t row;
	size_t column;
	TVector<T> data;
};


template<class T>
inline TDenseMatrix<T>::TDenseMatrix()
{
	row = 0;
	column = 0;
	data = T();
}

template<class T>
inline TDenseMatrix<T>::TDenseMatrix(const size_t row_, const size_t column_)
{
	row = row_;
	column = column_;
	data.SetCapacity(row_ * column_);
}

template<class T>
inline TDenseMatrix<T>::TDenseMatrix(size_t column_, size_t row_, const T& other) : data(row * column, other)
{
	row = row_;
	column = column_;
}

template<class T>
inline TDenseMatrix<T>::TDenseMatrix(const TDenseMatrix& other): data(other.data)
{
	row = other.row;
	column = other.column;
}

template<class T>
inline TDenseMatrix<T>::TDenseMatrix(TDenseMatrix&& other): data(other.data)
{
		row = other.row;
		column = other.column;
		other.row = 0;
		other.column = 0;
}

template<class T>
inline TDenseMatrix<T>::TDenseMatrix(initializer_list<initializer_list<T>> init_list)
{
	if (init_list.size() == 0)
	{
		row = 0;
		column = 0;
		data = T();
		return;
	}

	row = init_list.size();
	const initializer_list<T>& first_row = *(init_list.begin());
	column = first_row.size();

	for (const initializer_list<T>& rows : init_list) {
		if (rows.size() != column) {
			throw invalid_argument("Different row dimensions");
		}
	}

	data.SetSize(row * column);
	size_t index = 0;
	for (const std::initializer_list<T>& rows : init_list)
	{
		for (const auto& element : rows)
		{
			data[index++] = element;
		}
	}
}


template<class T>
inline size_t TDenseMatrix<T>::GetRow()
{
	return row;
}

template<class T>
inline size_t TDenseMatrix<T>::GetColumn()
{
	return column;
}

template<class T>
inline TVector<T> TDenseMatrix<T>::GetData()
{
	return data;
}

template<class T>
inline void TDenseMatrix<T>::SetRow(const size_t row_)
{
	if (row_ != row)
	{
		row = row_;
		data.SetCapacity(row * column);
	}
}

template<class T>
inline void TDenseMatrix<T>::SetColumn(const size_t column_)
{
	if (column_ != column)
	{
		column = column_;
		data.SetCapacity(row * column);
	}
}

//template<class T>
//inline TVector<T> TDenseMatrix<T>::begin() noexcept
//{
//	return data;
//}
//
//template<class T>
//inline const TVector<T> TDenseMatrix<T>::begin() const noexcept
//{
//	return data;
//}
//
//template<class T>
//inline const TVector<T> TDenseMatrix<T>::cbegin() const noexcept
//{
//	return data;
//}
//
//template<class T>
//inline TVector<T> TDenseMatrix<T>::end() noexcept
//{
//	return  data + data.GetSize();
//}
//
//template<class T>
//inline const TVector<T> TDenseMatrix<T>::end() const noexcept
//{
//	return data + data.GetSize();
//}
//
//template<class T>
//inline const TVector<T> TDenseMatrix<T>::cend() const noexcept
//{
//	return data + data.GetSize();
//}

template<class T>
inline bool TDenseMatrix<T>::empty() const noexcept
{
	return data.empty();
}

template<class T>
inline bool TDenseMatrix<T>::full() const noexcept
{
	return data.full();
}

template<class T>
inline void TDenseMatrix<T>::Clear() noexcept
{
	for (size_t i = 0; i < data.GetSize(); i++)
		data[i] = 0;
}

template<class T>
inline void TDenseMatrix<T>::push_back(const T& elem)
{
	if (data.GetSize() >= column * row)
		row++;
	data.push_back(elem);
}

template<class T>
inline void TDenseMatrix<T>::push_front(const T& elem)
{
	if (data.GetSize() >= column * row)
		row++;
	data.push_front(elem);
}

template<class T>
inline void TDenseMatrix<T>::pop_back()
{
	if (data.GetSize() <= column * row)
		row++;
	data.pop_back();
}

template<class T>
inline void TDenseMatrix<T>::pop_front()
{
	if (data.GetSize() <= column * row)
		row++;
	data.pop_front();
}

template<class T>
inline Row<T> TDenseMatrix<T>::operator[](size_t row_index)
{
	if (row_index >= row)
		throw invalid_argument("Error");
	Row<T> row;
	for (size_t i = 0; i < column; ++i)
		row.row_data.push_back(&data[row_index * column + i]);
	return row;
}

template<class T>
inline ConstRow<T> TDenseMatrix<T>::operator[](size_t row_index) const
{
	if (row_index >= row)
		throw invalid_argument("Error");
	ConstRow<T> row;
	for (size_t i = 0; i < column; ++i) 
		row.row_data.push_back(& data[row_index * column + i]);
	return row;
}

template<class T>
inline TDenseMatrix<T>& TDenseMatrix<T>::operator=(const TDenseMatrix<T>& other)
{
	if (this != &other)
	{
		if (!data.empty()) 
			data.Clear();
		column = other.column;
		row = other.row;
		if (row * column)
		{
			data.SetSize(row * column);
			for (auto i = 0; i < row * column; i++) 
				data[i] = other.data[i];
		}
		else data = T();
	}
	return *this;
}

template<class T>
inline TDenseMatrix<T>& TDenseMatrix<T>::operator=(TDenseMatrix<T>&& other) noexcept
{
	if (!data.empty()) 
		data.Clear();
	data = other.data;
	row = other.row;
	column = other.column;
	other.data = T();
	other.row = 0;
	other.column = 0;
	return *this;
}

template<class T>
inline TDenseMatrix<T> TDenseMatrix<T>::operator+(const TDenseMatrix<T>& other)
{
	if ((column == other.column) && (row == other.row))
	{
		TDenseMatrix<T> res(row, column);
		for (size_t i = 0; i < other.data.GetSize(); i++)
			res.data.push_back(data[i] + other.data[i]);
		return res;
	}
	else
		throw invalid_argument("Error");
}

template<class T>
inline TDenseMatrix<T> TDenseMatrix<T>::operator-(const TDenseMatrix<T>& other)
{
	if ((column == other.column) && (row == other.row))
	{
		TDenseMatrix<T> res(row, column);
		for (size_t i = 0; i < other.data.GetSize(); i++)
			res.data.push_back(data[i] - other.data[i]);
		return res;
	}
	else
		throw invalid_argument("Error");
}

template<class T>
inline TDenseMatrix<T> TDenseMatrix<T>::operator*(const TDenseMatrix<T>& other)
{
	if (column == other.row)
	{
		TDenseMatrix<T> res(row, other.column);
		for (int i = 0; i < res.row; ++i)
		{
			for (int j = 0; j < res.column; ++j)
			{
				T sum = 0;
				for (int k = 0; k < column; ++k)
					sum += data[i * column + k] * other.data[k * other.column + j];
				res.push_back(sum);
			}
		}
		return res;
	}
	else
		throw invalid_argument("Error size matrixs not equals");
}

template<class T>
inline bool TDenseMatrix<T>::operator==(const TDenseMatrix<T>& other)
{
	return data == other.data;
}

template<class T>
inline bool TDenseMatrix<T>::operator!=(const TDenseMatrix<T>& other)
{
	return data != other.data;
}

template<class O>
ostream& operator<<(ostream& out, TDenseMatrix<O>& other)
{
	for (size_t i = 0; i < other.data.GetSize(); i++)
	{
		out << other.data[i];
		if (i % other.GetColumn())
		{
			out << "\n";
		}
	}
	return out;
}

template<class O>
inline istream& operator>>(istream& input, TDenseMatrix<O>& other)
{
	size_t row;
	size_t column;
	input >> row;
	if (row < 0)
		throw invalid_argument("Error row < 0");
	input >> column;
	if (column < 0)
		throw invalid_argument("Error column < 0");
	other.SetColumn(column);
	other.SetRow(row);
	for (size_t i = 0; i < other.GetColumn(); i++)
	{
		for (size_t j = 0; j < other.GetRow(); j++)
		{

			cout << "["<< i << "]" << "[" << j << "]";
			input >> other.data[i + j];
		}
	}
}

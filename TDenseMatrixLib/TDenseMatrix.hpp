#pragma once
#include "TDenseMatrix.h"
#include "TVector.h"

template<class T>
inline TDenseMatrix<T>::TDenseMatrix()
{
	row = 0;
	column = 0;
	data = TVector<T>();
}

template<class T>
inline TDenseMatrix<T>::TDenseMatrix(const size_t row_, const size_t column_)
{
	row = row_;
	column = column_;
	data.SetSize(row_ * column_);
}

template<class T>
inline TDenseMatrix<T>::TDenseMatrix(size_t column_, size_t row_, const T& other) : data(row_* column_, other)
{
	row = row_;
	column = column_;
}

template<class T>
inline TDenseMatrix<T>::TDenseMatrix(const TDenseMatrix<T>& other) : data(other.data)
{
	row = other.row;
	column = other.column;
}

template<class T>
inline TDenseMatrix<T>::TDenseMatrix(TDenseMatrix<T>&& other) : data(other.data)
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
		data = TVector<T>();
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
inline TDenseMatrix<T>::TDenseMatrix(const string& filename)
{
	std::ifstream file(filename.c_str());

	if (!file.is_open()) 
		throw ("Cannot open file ");

	if (file.is_open())
	{

		size_t file_rows{}, file_columns{};
		file >> file_rows >> file_columns;
		if (file_rows == 0 || file_columns == 0) {
			throw ("Invalid matrix dimensions in file");
		}
		row = file_rows;
		column = file_columns;
		data.SetSize(row * column);
		for (size_t i = 0; i < row; ++i) {
			for (size_t j = 0; j < column; ++j)
				file >> data[i * column + j];
		}
		file.close();
	}
}


template<class T>
inline void TDenseMatrix<T>::SaveToFile(const string& filename)
{
	ofstream file(filename.c_str());
	if (file.is_open())
	{
		file
			<< row << '\n'
			<< column << '\n';
		for (auto i = 0; i < row; ++i)
		{
			for (auto j = 0; j < column; ++j) file << data[i * column + j] << ' ';
			file << '\n';
		}
	}
	file.close();
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
		data.SetSize(row * column);
	}
}

template<class T>
inline void TDenseMatrix<T>::SetColumn(const size_t column_)
{
	if (column_ != column)
	{
		column = column_;
		data.SetSize(row * column);
	}
}

template<class T>
inline T* TDenseMatrix<T>::begin() noexcept
{
	return data.begin();
}

template<class T>
inline const T* TDenseMatrix<T>::cbegin() const noexcept
{
	return data.cbegin();
}

template<class T>
inline T* TDenseMatrix<T>::end() noexcept
{
	return data.end();
}

template<class T>
inline const T* TDenseMatrix<T>::cend() const noexcept
{
	return data.cend();
}

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
		data[i] = T();
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
	if (data.GetSize() > 0) 
	{
		data.pop_back();
		if (data.GetSize() < column * row)
			row--;
	}
}

template<class T>
inline void TDenseMatrix<T>::pop_front()
{
	if (data.GetSize() > 0) 
	{
		data.pop_front();
		if (data.GetSize() < column * row)
			row--;
	}
}

template<class T>
inline Row<T> TDenseMatrix<T>::operator[](size_t row_index)
{
	if (row_index >= row)
		throw invalid_argument("Error");
	Row<T> row_;
	for (size_t i = 0; i < column; ++i)
		row_.row_data.push_back(&data[row_index * column + i]);
	return row_;
}

template<class T>
inline ConstRow<T> TDenseMatrix<T>::operator[](size_t row_index) const
{
	if (row_index >= row)
		throw invalid_argument("Error");
	ConstRow<T> row_;
	for (size_t i = 0; i < column; ++i)
		row_.row_data.push_back(&data[row_index * column + i]);
	return row_;
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
		else data = TVector<T>();
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
	other.data = TVector<T>();
	other.row = 0;
	other.column = 0;
	return *this;
}

template<class T>
inline TDenseMatrix<T> TDenseMatrix<T>::operator+(const TDenseMatrix<T>& other)
{
	if (column != other.column || row != other.row)
		throw invalid_argument("Matrix dimensions don't match");

	TDenseMatrix<T> res(row, column);
	res.data.SetSize(row * column);
	for (size_t i = 0; i < row * column; i++)
		res.data[i] = data[i] + other.data[i];
	return res;
}

template<class T>
inline TDenseMatrix<T> TDenseMatrix<T>::operator-(const TDenseMatrix<T>& other)
{
	if (column != other.column || row != other.row)
		throw invalid_argument("Matrix dimensions don't match");

	TDenseMatrix<T> res(row, column);
	res.data.SetSize(row * column);
	for (size_t i = 0; i < row * column; i++)
		res.data[i] = data[i] - other.data[i];
	return res;
}

template<class T>
inline TDenseMatrix<T> TDenseMatrix<T>::operator*(const TDenseMatrix<T>& other)
{
	if (column == other.row)
	{
		TDenseMatrix<T> res(row, other.column);
		res.data.SetSize(row * other.column);
		for (size_t i = 0; i < res.row; ++i)
		{
			for (size_t j = 0; j < res.column; ++j)
			{
				T sum = 0;
				for (int k = 0; k < column; ++k)
					sum += data[i * column + k] * other.data[k * other.column + j];
				res.data[i * other.column + j] = sum;
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
	for (size_t i = 0; i < other.GetRow(); i++)
	{
		for (size_t j = 0; j < other.GetColumn(); j++)
		{
			out << other.data[i * other.GetColumn() + j];
			if (j < other.GetColumn() - 1)
				out << " ";
		}
		out << "\n";
	}
	return out;
}

template<class O>
inline istream& operator>>(istream& input, TDenseMatrix<O>& other)
{
	size_t row;
	size_t column;
	input >> row;
	other.SetColumn(column);
	other.SetRow(row);
	for (size_t i = 0; i < other.GetRow(); i++)
	{
		for (size_t j = 0; j < other.GetColumn(); j++)
		{
			input >> other.data[i * other.GetColumn() + j];
		}
	}
	return input;
}

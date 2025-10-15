#pragma once
#include "TVector.h"
#include <fstream>
template <class T>
class TSparseMatrix
{
public:

	TSparseMatrix();
	TSparseMatrix(const size_t dim_, const size_t width_);
	TSparseMatrix(const TSparseMatrix<T>& other);
	TSparseMatrix(const size_t dim_, const size_t width_, const T& other);
	TSparseMatrix(TSparseMatrix<T>&& other);
	TSparseMatrix(std::initializer_list<initializer_list<T>> init_list);
	TSparseMatrix<T>(const string& filename);
	void SaveToFile(const string& filename);

	size_t GetDim();
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

	TSparseMatrix<T>& operator = (const TSparseMatrix<T>& other);
	TSparseMatrix<T>& operator = (TSparseMatrix <T>&& other) noexcept;
	TSparseMatrix<T> operator + (const TSparseMatrix<T>& other);
	TSparseMatrix<T> operator - (const TSparseMatrix<T>& other);
	TSparseMatrix<T> operator * (TSparseMatrix<T>& other);

	bool operator==(const TSparseMatrix<T>& other);
	bool operator!=(const TSparseMatrix<T>& other);

	template<class O>
	friend ostream& operator << (ostream& out, TSparseMatrix<O>& other);
	template<class O>
	friend istream& operator >> (istream& input, TSparseMatrix<O>& other);
private:
	size_t dim;
	size_t width;
	TVector<T> data;
};

template<class T>
inline TSparseMatrix<T>::TSparseMatrix()
{
	dim = 0;
	width = 0;
	data = T();
}

template<class T>
inline TSparseMatrix<T>::TSparseMatrix(const size_t dim_, const size_t width_)
{
	dim = dim_;
	width = width_;
	size_t sum = 0;
	for (size_t i = 0; i < width; i++)
		sum += dim - i;
	data.SetSize(sum);
}

template<class T>
inline TSparseMatrix<T>::TSparseMatrix(const TSparseMatrix<T>& other): data(other.data)
{
	dim = other.dim;
	width = other.width;
}

template<class T>
inline TSparseMatrix<T>::TSparseMatrix(const size_t dim_, const size_t width_, const T& other)
{
	dim = dim_;
	width = width_;
	size_t sum = 0;
	for (size_t i = 0; i < width; i++)
		sum += dim - i;
	data = TVector<T>(sum, other);
}

template<class T>
inline TSparseMatrix<T>::TSparseMatrix(TSparseMatrix<T>&& other): data(other.data)
{
	dim = other.dim;
	width = other.width;
	other.dim = 0;
	other.width = 0;
}

template<class T>
inline TSparseMatrix<T>::TSparseMatrix(std::initializer_list<initializer_list<T>> init_list)
{
	dim = init_list.size();
	if (dim == 0) {
		this->dim = 0;
		this->width = 0;
		return;
	}

	width = 0;
	for (const auto& row : init_list) {
		size_t row_nonzero = 0;
		for (const auto& elem : row) {
			if (elem != T(0)) row_nonzero++;
		}
		width = std::max(width, row_nonzero);
	}

	size_t total_size = 0;
	for (size_t i = 0; i < width; i++)
		total_size += dim - i;
	data = TVector<T>(total_size, T(0));

	size_t row_idx = 0;
	for (const auto& row_list : init_list)
	{
		size_t col_idx = 0;
		Row<T> row_proxy = (*this)[row_idx];
		for (const auto& elem : row_list) 
		{
			if (elem != T(0) && col_idx < dim)
			{
				try
				{
					row_proxy[col_idx] = elem;
				}
				catch (const std::invalid_argument&){}
			}
			col_idx++;
		}
		row_idx++;
	}
}
template<class T>
inline TSparseMatrix<T>::TSparseMatrix(const string& filename)
{
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open())
		throw std::runtime_error("Cannot open file for reading: " + filename);

	// Читаем размерности
	file.read(reinterpret_cast<char*>(&dim), sizeof(size_t));
	file.read(reinterpret_cast<char*>(&width), sizeof(size_t));

	// Читаем размер данных
	size_t data_size;
	file.read(reinterpret_cast<char*>(&data_size), sizeof(size_t));

	// Инициализируем вектор данных
	data = TVector<T>(data_size);

	// Читаем данные
	for (size_t i = 0; i < data_size; ++i)
	{
		T value;
		file.read(reinterpret_cast<char*>(&value), sizeof(T));
		data.push_back(value);
	}

	file.close();
}
template<class T>
inline size_t TSparseMatrix<T>::GetDim()
{
	return dim;
}

template<class T>
inline size_t TSparseMatrix<T>::GetWidth()
{
	return width;
}

template<class T>
inline TVector<T> TSparseMatrix<T>::GetData()
{
	return data;
}

template<class T>
inline void TSparseMatrix<T>::SetDim(const size_t dim_)
{
	if (dim != dim_)
	{
		dim = dim_;
		size_t sum = 0;
		for (size_t i = 0; i < width; i++)
			sum += dim - i;
		data.SetSize(sum);
	}
}

template<class T>
inline void TSparseMatrix<T>::SetWidth(const size_t width_)
{
	if (width != width_)
	{
		width = width_;
		size_t sum = 0;
		for (size_t i = 0; i < width; i++)
			sum += dim - i;
		data.SetSize(sum);
	}
}
template<class T>
inline TVector<T> TSparseMatrix<T>::begin() noexcept
{
	return data;
}

template<class T>
inline const TVector<T> TSparseMatrix<T>::cbegin() const noexcept
{
	return data;
}

template<class T>
inline TVector<T> TSparseMatrix<T>::end() noexcept
{
	return data + data.GetSize();
}

template<class T>
inline const TVector<T> TSparseMatrix<T>::cend() const noexcept
{
	return data + data.GetSize();
}

template<class T>
inline bool TSparseMatrix<T>::empty() const noexcept
{
	return data.empty();
}

template<class T>
inline bool TSparseMatrix<T>::full() const noexcept
{
	return data.full();
}

template<class T>
inline void TSparseMatrix<T>::Clear() noexcept
{
	for (size_t i = 0; i < data.GetSize(); i++)
		data[i] = 0;
}

template<class T>
inline Row<T> TSparseMatrix<T>::operator[](size_t row_index)
{
	if (row_index >= dim)
		throw std::out_of_range("Row index out of range");

	Row<T> row_proxy;
	row_proxy.row_data = TVector<T*>(dim, nullptr);

	// Вычисляем начальный индекс для текущей строки в data
	size_t data_start = 0;
	for (size_t diag = 0; diag < width; diag++) {
		// Для каждой диагонали вычисляем, попадает ли текущая строка в её диапазон
		size_t diag_length = dim - diag;

		// Главная диагональ (diag = 0)
		if (diag == 0) 
		{
			if (row_index < diag_length)
				row_proxy.row_data[row_index] = &data[data_start + row_index];
		}
		// Верхние диагонали (diag > 0)
		else 
		{
			// Элементы справа от главной диагонали
			size_t col = row_index + diag;
			if (col < dim)
				row_proxy.row_data[col] = &data[data_start + row_index];

			// Элементы слева от главной диагонали (симметричные)
			if (diag <= row_index) {
				size_t symmetric_col = row_index - diag;
				row_proxy.row_data[symmetric_col] = &data[data_start + row_index - diag];
			}
		}

		data_start += diag_length;
	}

	return row_proxy;
}

template<class T>
inline TSparseMatrix<T>& TSparseMatrix<T>::operator=(const TSparseMatrix<T>& other)
{
	// мне кажеться можно переделать чтобы тут был if(other.data != nullptr)
	data = other.data;
	dim = other.dim;
	width = other.width;
	return *this;
}

template<class T>
inline TSparseMatrix<T>& TSparseMatrix<T>::operator=(TSparseMatrix<T>&& other) noexcept
{
	data = other.data;
	dim = other.dim;
	width = other.width;
	other.dim = 0;
	other.width = 0;
	other.data = TVector<T>();
	return *this;
}

template<class T>
inline TSparseMatrix<T> TSparseMatrix<T>::operator+(const TSparseMatrix<T>& other)
{
	if (dim != other.dim)
		throw invalid_argument("Error matrix size not equals");
	TSparseMatrix<T> res(dim, width);
	res.data.SetSize(0);
	for (size_t i = 0; i < data.GetSize(); i++)
	{
		res.data.push_back(data[i] + other.data[i]);
	}
	return res;
}

template<class T>
inline TSparseMatrix<T> TSparseMatrix<T>::operator-(const TSparseMatrix<T>& other)
{
	if (dim != other.dim)
		throw invalid_argument("Error matrix size not equals");
	TSparseMatrix<T> res(dim, width);
	res.data.SetSize(0);
	for (size_t i = 0; i < data.GetSize(); i++)
	{
		res.data.push_back(data[i] - other.data[i]);
	}
	return res;
}

template<class T>
TSparseMatrix<T> TSparseMatrix<T>::operator*(TSparseMatrix<T>& other)
{
	if (dim != other.dim) {
		throw std::invalid_argument("Matrix dimensions must match for multiplication");
	}

	size_t res_width = std::min(dim, width + other.width - 1);
	TSparseMatrix<T> result(dim, res_width);
	result.data.SetSize(result.data.GetCapacity());
	for (size_t i = 0; i < dim; i++) {
		for (size_t j = i; j < std::min(dim, i + res_width); j++) {
			T sum = T(0);

			size_t k_start = std::max(
				(i >= width) ? i - width + 1 : 0,
				(j >= other.width) ? j - other.width + 1 : 0
			);
			size_t k_end = std::min(
				std::min(i + width, j + other.width),
				dim
			);
			for (size_t k = k_start; k < k_end; k++) {
				T a_ik = (*this)[i][k];
				T b_kj = other[k][j];
				sum += a_ik * b_kj;
			}
			if (sum != T(0)) {
				result[i][j] = sum;
			}
		}
	}

	return result;
}

template<class T>
inline void TSparseMatrix<T>::SaveToFile(const string& filename)
{
	std::ofstream file(filename, std::ios::binary);
	if (!file.is_open())
		throw std::runtime_error("Cannot open file for writing: " + filename);

	// Сохраняем размерности
	file.write(reinterpret_cast<const char*>(&dim), sizeof(size_t));
	file.write(reinterpret_cast<const char*>(&width), sizeof(size_t));

	// Сохраняем размер данных
	size_t data_size = data.GetSize();
	file.write(reinterpret_cast<const char*>(&data_size), sizeof(size_t));

	// Сохраняем данные
	for (size_t i = 0; i < data_size; ++i)
	{
		file.write(reinterpret_cast<const char*>(&data[i]), sizeof(T));
	}

	file.close();
}


template<class T>
inline bool TSparseMatrix<T>::operator==(const TSparseMatrix<T>& other)
{
	return data == other.data;
}

template<class T>
inline bool TSparseMatrix<T>::operator!=(const TSparseMatrix<T>& other)
{
	return data != other.data;
}

template<class O>
inline ostream& operator<<(ostream& out, TSparseMatrix<O>& other)
{
	size_t sum = other.dim, j = 1;
	for (size_t i = 0; i < other.GetData().GetSize(); i++)
	{
		if (i == sum)
		{
			sum += other.dim - j;
			j++;
			out << "\n";
		}
		out << other.data[i] << " ";
	}
	return out;
}

template<class O>
inline istream& operator>>(istream& input, TSparseMatrix<O>& other)
{
	return input;
}

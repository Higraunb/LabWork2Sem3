#pragma once
#include "TVector.h"
#include "TDenseMatrix.h"
#include "TBandedMatrix.h"
#include <map>

template<class T>
inline TBandedMatrix<T>::TBandedMatrix()
{
	row_elem_count = TVector<size_t>();
	column_index = TVector<size_t>();
	data = TVector<T>();
	dim = 0;
}

template<class T>
inline TBandedMatrix<T>::TBandedMatrix(TDenseMatrix<T>& other)
{
	if ((other.GetData().empty() != true) && (other.GetColumn() == other.GetRow()))
	{
		dim = other.GetColumn();
		size_t elem_count = 0;
		for (size_t i = 0; i < other.GetRow(); i++)
		{
			for (size_t j = 0; j < other.GetColumn(); j++)
			{
				if (other[i][j] != 0)
				{
					data.push_back(other[i][j]);
					column_index.push_back(j);
					elem_count++;
				}
			}
			row_elem_count.push_back(elem_count);
			elem_count = 0;
		}
	}
	else
		throw invalid_argument("Error size other matrix = 0");
}

template<class T>
inline TBandedMatrix<T>::TBandedMatrix(const TBandedMatrix<T>& other) : data(other.data),
row_elem_count(other.row_elem_count), column_index(other.column_index)
{
	dim = other.dim;
}

template<class T>
inline TBandedMatrix<T>::TBandedMatrix(TBandedMatrix<T>&& other) : data(other.data),
row_elem_count(other.row_elem_count), column_index(other.column_index)
{
	dim = other.dim;
	other.data = TVector<T>();
	other.row_elem_count = TVector<size_t>();
	other.column_index = TVector<size_t>();
	other.dim = 0;
}

template<typename T>
inline TBandedMatrix<T>::TBandedMatrix(initializer_list<initializer_list<T>> init_list)
{
	dim = init_list.size();

	TVector<T> temp_data;
	TVector<size_t> temp_col_indices;
	row_elem_count = TVector<size_t>(dim, 0);

	size_t row_idx = 0;
	for (const auto& row : init_list)
	{
		if (row.size() > dim)
			throw invalid_argument("Row length exceeds matrix dimension");

		size_t col_idx = 0;
		for (const auto& element : row)
		{
			if (element != T(0))
			{
				temp_data.push_back(element);
				temp_col_indices.push_back(col_idx);
				row_elem_count[row_idx]++;
			}
			col_idx++;
		}
		row_idx++;
	}
	data = std::move(temp_data);
	column_index = std::move(temp_col_indices);
}

template<class T>
inline size_t TBandedMatrix<T>::GetDim()
{
	return dim;
}

template<class T>
inline TVector<size_t> TBandedMatrix<T>::GetRowElemCount()
{
	return row_elem_count;
}

template<class T>
inline TVector<size_t> TBandedMatrix<T>::GetColumnIndex()
{
	return column_index;
}
template<class T>
inline TVector<T> TBandedMatrix<T>::GetData()
{
	return data;
}

template<class T>
inline void TBandedMatrix<T>::SetDim(const size_t dim_)
{
	dim = dim_;
}

template<class T>
inline TVector<T> TBandedMatrix<T>::begin() noexcept
{
	return data;
}

template<class T>
inline const TVector<T> TBandedMatrix<T>::cbegin() const noexcept
{
	return data;
}

template<class T>
inline TVector<T> TBandedMatrix<T>::end() noexcept
{
	return data + data.GetSize();
}

template<class T>
inline const TVector<T> TBandedMatrix<T>::cend() const noexcept
{
	return data + data.GetSize();
}

template<class T>
inline bool TBandedMatrix<T>::empty() const noexcept
{
	return data.empty();
}

template<class T>
inline bool TBandedMatrix<T>::full() const noexcept
{
	return data.full();
}

template<class T>
inline void TBandedMatrix<T>::Clear() noexcept
{
	data = TVector<T>();
	row_elem_count = TVector<size_t>();
	column_index = TVector<size_t>();
  dim = 0;
}

template<class T>
inline TVectorProcs<T> TBandedMatrix<T>::operator[](size_t row_index)
{
	if (row_index >= dim)
		throw std::invalid_argument("Row index out of bounds");
	return TVectorProcs<T>(*this, row_index);
}


template<typename T>
T TBandedMatrix<T>::get(size_t row, size_t col) const 
{
  if (row >= dim || col >= dim) {
    throw std::invalid_argument("Indices out of bounds");
  }

  // Находим диапазон элементов для данной строки
  size_t start = 0;
  for (size_t i = 0; i < row; i++) {
    start += row_elem_count[i];
  }
  size_t end = start + row_elem_count[row];

  // Ищем элемент в найденном диапазоне
  for (size_t i = start; i < end; i++) {
    if (column_index[i] == col) {
      return data[i];
    }
  }

  return T(0); // Элемент не найден
}

template<typename T>
void TBandedMatrix<T>::set(size_t row, size_t col, const T& value) {
  if (row >= dim || col >= dim) {
    throw std::invalid_argument("Indices out of bounds");
  }

  // Находим позицию для вставки/обновления
  size_t start = 0;
  for (size_t i = 0; i < row; i++) {
    start += row_elem_count[i];
  }
  size_t end = start + row_elem_count[row];

  // Ищем существующий элемент
  for (size_t i = start; i < end; i++) {
    if (column_index[i] == col) {
      if (value == T(0)) {
        // Удаляем элемент
        removeElement(i, row);
      }
      else {
        // Обновляем значение
        data[i] = value;
      }
      return;
    }
  }

  // Элемент не найден - добавляем новый (если не нулевой)
  if (value != T(0)) {
    insertElement(start, row, col, value);
  }
}

template<typename T>
void TBandedMatrix<T>::removeElement(size_t pos, size_t row) {
  // Удаляем элемент из массивов
  data.erase(data.begin() + pos);
  column_index.erase(column_index.begin() + pos);

  // Уменьшаем счетчик элементов в строке
  row_elem_count[row]--;

  // Обновляем счетчики для последующих строк
  for (size_t i = row + 1; i < dim; i++) {
    // Смещаем начало строк (в row_elem_count это неявно хранится)
    // Вам может понадобиться отдельный массив row_ptrs для эффективности
  }
}

template<typename T>
void TBandedMatrix<T>::insertElement(size_t pos, size_t row, size_t col, const T& value) {
  // Вставляем элемент
  data.insert(data.begin() + pos, value);
  column_index.insert(column_index.begin() + pos, col);

  // Увеличиваем счетчик элементов в строке
  row_elem_count[row]++;
}
template<class T>
inline TBandedMatrix<T>& TBandedMatrix<T>::operator=(const TBandedMatrix<T>& other)
{
	data = other.data;
	row_elem_count = other.row_elem_count;
	column_index = other.column_index;
  dim = other.dim;
	return *this;
}

template<class T>
inline TBandedMatrix<T>& TBandedMatrix<T>::operator=(TBandedMatrix<T>&& other) noexcept
{
	data = other.data;
	row_elem_count = other.row_elem_count;
	column_index = other.column_index;
	dim = other.dim;
	other.data = TVector<T>();
	other.row_elem_count = TVector<size_t>();
	other.column_index = TVector<size_t>();
	other.dim = 0;
	return *this;
}

template<class T>
inline TBandedMatrix<T> TBandedMatrix<T>::operator+(const TBandedMatrix<T>& other)
{
  if (dim != other.dim)
    throw std::invalid_argument("Matrix dimensions must match for addition");

  TBandedMatrix<T> result;
  result.dim = dim;
  result.row_elem_count = TVector<size_t>(dim, 0);

  // Проходим по всем строкам
  for (size_t i = 0; i < dim; ++i)
  {
    // Используем map для хранения всех ненулевых элементов строки
    map<size_t, T> row_elements;

    // Добавляем элементы из первой матрицы
    size_t start1 = 0;
    for (size_t r = 0; r < i; ++r)
      start1 += row_elem_count[r];

    for (size_t j = 0; j < row_elem_count[i]; ++j)
    {
      size_t col = column_index[start1 + j];
      row_elements[col] = data[start1 + j];
    }

    // Добавляем элементы из второй матрицы
    size_t start2 = 0;
    for (size_t r = 0; r < i; ++r)
      start2 += other.row_elem_count[r];

    for (size_t j = 0; j < other.row_elem_count[i]; ++j)
    {
      size_t col = other.column_index[start2 + j];
      row_elements[col] += other.data[start2 + j];
    }

    // Добавляем ненулевые элементы в результат
    for (const auto& pair : row_elements)
    {
      if (pair.second != T(0))
      {
        result.data.push_back(pair.second);
        result.column_index.push_back(pair.first);
        result.row_elem_count[i]++;
      }
    }
  }

  return result;
}
template<class T>
inline TBandedMatrix<T> TBandedMatrix<T>::operator-(const TBandedMatrix<T>& other)
{
  if (dim != other.dim)
    throw std::invalid_argument("Matrix dimensions must match for subtraction");

  TBandedMatrix<T> result;
  result.dim = dim;
  result.row_elem_count = TVector<size_t>(dim, 0);

  // Проходим по всем строкам
  for (size_t i = 0; i < dim; ++i)
  {
    // Используем map для хранения всех ненулевых элементов строки
    std::map<size_t, T> row_elements;

    // Добавляем элементы из первой матрицы
    size_t start1 = 0;
    for (size_t r = 0; r < i; ++r)
      start1 += row_elem_count[r];

    for (size_t j = 0; j < row_elem_count[i]; ++j)
    {
      size_t col = column_index[start1 + j];
      row_elements[col] = data[start1 + j];
    }

    // Вычитаем элементы из второй матрицы
    size_t start2 = 0;
    for (size_t r = 0; r < i; ++r)
      start2 += other.row_elem_count[r];

    for (size_t j = 0; j < other.row_elem_count[i]; ++j)
    {
      size_t col = other.column_index[start2 + j];
      row_elements[col] -= other.data[start2 + j];
    }

    // Добавляем ненулевые элементы в результат
    for (const auto& pair : row_elements)
    {
      if (pair.second != T(0))
      {
        result.data.push_back(pair.second);
        result.column_index.push_back(pair.first);
        result.row_elem_count[i]++;
      }
    }
  }

  return result;
}

template<class T>
inline TBandedMatrix<T> TBandedMatrix<T>::operator*(const TBandedMatrix<T>& other)
{
  if (dim != other.dim)
    throw std::invalid_argument("Matrix dimensions must match for multiplication");

  TBandedMatrix<T> result;
  result.dim = dim;
  result.row_elem_count = TVector<size_t>(dim, 0);

  // Проходим по всем строкам первой матрицы
  for (size_t i = 0; i < dim; ++i)
  {
    std::map<size_t, T> row_elements;

    // Получаем начало строки i в первой матрице
    size_t start_i = 0;
    for (size_t r = 0; r < i; ++r)
      start_i += row_elem_count[r];

    // Проходим по всем ненулевым элементам строки i
    for (size_t idx = 0; idx < row_elem_count[i]; ++idx)
    {
      size_t k = column_index[start_i + idx];  // Индекс столбца
      T val_ik = data[start_i + idx];           // Значение A[i][k]

      // Находим начало строки k во второй матрице
      size_t start_k = 0;
      for (size_t r = 0; r < k; ++r)
        start_k += other.row_elem_count[r];

      // Умножаем на все элементы строки k второй матрицы
      for (size_t idx2 = 0; idx2 < other.row_elem_count[k]; ++idx2)
      {
        size_t j = other.column_index[start_k + idx2];  // Индекс столбца
        T val_kj = other.data[start_k + idx2];          // Значение B[k][j]

        row_elements[j] += val_ik * val_kj;
      }
    }

    // Добавляем ненулевые результаты в матрицу
    for (const auto& pair : row_elements)
    {
      if (pair.second != T(0))
      {
        result.data.push_back(pair.second);
        result.column_index.push_back(pair.first);
        result.row_elem_count[i]++;
      }
    }
  }

  return result;
}

template<class T>
inline bool TBandedMatrix<T>::operator==(const TBandedMatrix<T>& other)
{
	return (data == other.data && row_elem_count == other.row_elem_count
		&& column_index == other.column_index);
}

template<class T>
inline bool TBandedMatrix<T>::operator!=(const TBandedMatrix<T>& other)
{
	return !(*this == other);
}

template<class O>
inline ostream& operator<<(ostream& out, TBandedMatrix<O>& other)
{
	// TODO: вставьте здесь оператор return
}

template<class O>
inline istream& operator>>(istream& input, TBandedMatrix<O>& other)
{
	// TODO: вставьте здесь оператор return
}

#pragma once
#include "TBandedMatrix.h"
#include "TVector.h"
#include <string>

template<class O>
std::ostream& operator<<(std::ostream& out, TVector<O>& other) {
	out << other.GetSize();
	for (size_t i = 0; i < other.GetSize(); ++i) {
		out << " " << other[i];
	}
	return out;
}

template<class T>
void TVector<T>::insert(size_t pos, const T& value)
{
	if (pos > size) {
		throw std::out_of_range("Insert position out of range");
	}

	// Если массив полный, увеличиваем емкость
	if (size == capacity) {
		size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
		T* new_data = new T[new_capacity];

		// Копируем элементы до позиции вставки
		for (size_t i = 0; i < pos; ++i) {
			new_data[i] = std::move(data[i]);
		}

		// Вставляем новый элемент
		new_data[pos] = value;

		// Копируем остальные элементы
		for (size_t i = pos; i < size; ++i) {
			new_data[i + 1] = std::move(data[i]);
		}

		// Заменяем старый массив новым
		delete[] data;
		data = new_data;
		capacity = new_capacity;
	}
	else {
		// Сдвигаем элементы вправо, начиная с конца
		for (size_t i = size; i > pos; --i) {
			data[i] = std::move(data[i - 1]);
		}
		data[pos] = value;
	}

	++size;
}

template<class T>
void TVector<T>::insert(T* pos, const T& value)
{
	if (pos < data || pos > data + size) {
		throw std::out_of_range("Insert position out of range");
	}

	size_t index = pos - data;
	insert(index, value);
}

template<class T>
void TVector<T>::erase(size_t pos)
{
	if (pos >= size) {
		throw std::out_of_range("Erase position out of range");
	}

	// Сдвигаем элементы влево, начиная с позиции после удаляемой
	for (size_t i = pos; i < size - 1; ++i) {
		data[i] = std::move(data[i + 1]);
	}

	// Очищаем последний элемент
	if (size > 0) {
		data[size - 1] = T();
	}

	--size;
}

template<class T>
void TVector<T>::erase(T* pos)
{
	if (pos < data || pos >= data + size) {
		throw std::out_of_range("Erase position out of range");
	}

	size_t index = pos - data;
	erase(index);
}

template<class O>
std::istream& operator>>(std::istream& inp, TVector<O>& other) {
	other.Clear();

	size_t size;
	inp >> size;

	if (!inp || size > 1000)
	{
		inp.setstate(std::ios::failbit);
		return inp;
	}

	for (size_t i = 0; i < size; ++i) {
		O value;
		inp >> value;
		if (!inp) break;
		other.push_back(value);
	}

	return inp;
}


template<class T>
inline TVector<T>::TVector()
{
	data = nullptr;
	capacity = 0;
	size = 0;
}

template<class T>
inline TVector<T>::TVector(size_t len)
{
	if (len > 0)
	{
		capacity = len;
		size = 0;
		data = new T[capacity]{};
	}
	else if (len == 0)
	{
		capacity = 0;
		size = 0;
		data = nullptr;
	}
	else
		throw std::invalid_argument("len < 0");
}

template<class T>
inline TVector<T>::TVector(const size_t len, const T elem)
{
	if (len == 0)
	{
		capacity = 0;
		size = 0;
		data = nullptr;
	}
	else
	{
		capacity = len;
		size = len;
		data = new T[capacity];
		for (size_t i = 0; i < size; ++i)
			data[i] = elem;
	}
}

template<class T>
inline TVector<T>::TVector(const TVector<T>& other)
{
	if (other.capacity != 0)
	{
		data = nullptr;
		capacity = other.capacity;
		size = other.size;
		if (size > capacity)
			capacity = size;
		data = new T[capacity];
		for (size_t i = 0; i < size; i++)
			data[i] = other.data[i];
	}
	else
	{
		capacity = 0;
		size = 0;
		data = nullptr;
	}
}

template<class T>
inline TVector<T>::TVector(std::initializer_list<T> init) : data(nullptr), capacity(0), size(0) {
	if (init.size() > 0) {
		size = init.size();
		capacity = init.size();
		data = new T[capacity];
		size_t i = 0;
		for (const auto& item : init) {
			data[i++] = item;
		}
	}
}

template<class T>
inline TVector<T>::TVector(TVector<T>&& other) noexcept
{
	if (other.capacity != 0)
	{
		capacity = other.capacity;
		size = other.size;
		data = other.data;
		other.capacity = 0;
		other.size = 0;
		other.data = nullptr;
	}
	else
	{
		capacity = 0;
		size = 0;
		data = nullptr;
		other.capacity = 0;
		other.size = 0;
		other.data = nullptr;
	}
}

template<class T>
inline TVector<T>::~TVector()
{
	delete[] data;
}

template<class T>
inline size_t TVector<T>::GetSize() const noexcept
{
	return size;
}

template<class T>
inline size_t TVector<T>::GetCapacity() const noexcept
{
	return capacity;
}

template<class T>
inline T* TVector<T>::GetData() const noexcept
{
	return data;
}

template<class T>
inline void TVector<T>::SetSize(const size_t size_)
{
	if (size_ != size)
	{
		if (size_ <= capacity)
		{
			size = size_;
		}
		else
		{
			T* tmp = nullptr;
			if (size > 0)
			{
				tmp = new T[size];
				for (size_t i = 0; i < size; i++)
					tmp[i] = std::move(data[i]);
			}
			delete[] data;
			capacity = size_;
			data = new T[capacity];
			if (size > 0 && tmp != nullptr)
			{
				for (size_t i = 0; i < size; i++)
					data[i] = std::move(tmp[i]);
				delete[] tmp;
			}
			size = size_;
		}
	}
}

template<class T>
inline void TVector<T>::SetCapacity(const size_t capacity_)
{
	if (capacity_ <= capacity)
	{
		capacity = capacity_;
		if (capacity < size)
			size = capacity;
	}
	else
	{
		if (size == 0)
		{
			delete[] data;
			capacity = capacity_;
			data = new T[capacity]{};
		}
		else
		{
			T* tmp = new T[size]{};
			for (size_t i = 0; i < size; i++)
				tmp[i] = data[i];
			delete[] data;
			capacity = capacity_;
			if (capacity < size)
				size = capacity;
			data = new T[capacity]{};
			for (size_t i = 0; i < size; i++)
				data[i] = tmp[i];
			delete[] tmp;
		}
	}
}

template<class T>
inline void TVector<T>::SetData(const T* data_)
{
	if (data_ != nullptr)
	{
		if (data_.size() > capacity)
		{
			delete[] data;
			capacity = data_.size();
			data = new T[capacity]{};
			for (size_t i = 0; i < capacity; i++)
				data[i] = data_[i];
		}
		else
		{
			for (size_t i = 0; i < size; i++)
				data[i] = 0;
			for (size_t i = 0; i < data_.size(); i++)
				data[i] = data_[i];
		}
	}
}

template<class T>
inline T* TVector<T>::begin() noexcept
{
	return data;
}

template<class T>
inline const T* TVector<T>::begin() const noexcept
{
	return data;
}

template<class T>
inline const T* TVector<T>::cbegin() const noexcept
{
	return data;
}

template<class T>
inline T* TVector<T>::end() noexcept
{
	return data + size;
}

template<class T>
inline const T* TVector<T>::end() const noexcept
{
	return data + size;
}

template<class T>
inline const T* TVector<T>::cend() const noexcept
{
	return data + size;
}

template<class T>
inline bool TVector<T>::empty() const noexcept
{
	return size == 0;
}

template<class T>
inline bool TVector<T>::full() const noexcept
{
	return size == capacity;
}

template<class T>
inline void TVector<T>::Clear() noexcept
{
	size = 0;
	delete[] data;
	data = nullptr;
}

template<class T>
inline void TVector<T>::push_back(const T& elem)
{
	if (capacity == 0)
	{
		size++;
		capacity++;
		data = new T[capacity]{ elem };
	}
	else if (size != capacity)
		data[size++] = elem;
	else
	{
		size_t capacity_ = capacity * 2;
		T* data_ = new T[size]{};
		for (size_t i = 0; i < size; i++)
			data_[i] = data[i];
		delete[] data;
		data = new T[capacity_]{};
		for (size_t i = 0; i < size; i++)
			data[i] = data_[i];
		data[size] = elem;
		size++;
		capacity = capacity_;
		delete[] data_;
	}
}

template<class T>
inline void TVector<T>::push_front(const T& elem)
{
	push_back(elem);
	for (size_t i = size - 1; i > 0; --i)
		data[i] = data[i - 1];
	data[0] = elem;
}

template<class T>
inline void TVector<T>::pop_back()
{
	if (size > 0)
	{
		data[size - 1] = 0;
		size--;
	}
	else
		throw std::invalid_argument("size == 0");
}

template<class T>
inline void TVector<T>::pop_front()
{
	if (size > 0)
	{
		for (size_t i = 1; i < size; i++)
			data[i - 1] = data[i];
		size--;
	}
	else
		throw std::invalid_argument("size == 0");
}

template<class T>
inline TVector<T>& TVector<T>::operator = (const TVector<T>& other)
{
	if (*this == other)
		return *this;
	if (other.capacity != 0)
	{
		delete[] data;
		capacity = other.capacity;
		size = other.size;
		data = new T[capacity];
		for (size_t i = 0; i < size; i++)
			data[i] = other.data[i];
	}
	else
	{
		capacity = 0;
		size = 0;
		data = nullptr;
	}
	return *this;
}

template<class T>
inline TVector<T>& TVector<T>::operator=(TVector<T>&& other) noexcept
{
	if (*this == other)
		return *this;
	if (other.capacity != 0)
	{
		delete[] data;
		capacity = other.capacity;
		size = other.size;
		data = other.data;
		other.capacity = 0;
		other.size = 0;
		other.data = nullptr;
	}
	else
	{
		capacity = 0;
		size = 0;
		data = nullptr;
		other.capacity = 0;
		other.size = 0;
		other.data = nullptr;
	}
	return *this;
}

template<class T>
inline TVector<T>& TVector<T>::operator=(std::initializer_list<T> init)
{
	if (init.size() == 0)
	{
		capacity = 0;
		size = 0;
		data = nullptr;
	}
	else
	{
		delete[] data;
		size = init.size();
		capacity = init.size();
		data = new T[capacity];
		const T* src = init.begin();
		T* dest = data;
		const T* end = init.end();
		while (src != end)
			*dest++ = *src++;
	}
	return *this;
}

template<class T>
inline bool TVector<T>::operator==(const TVector<T>& other)
{
	if (size != other.size)
		return false;
	else
	{
		for (size_t i = 0; i < size; ++i)
			if (data[i] != other.data[i])
				return false;
	}
	return true;
}

template<class T>
inline bool TVector<T>::operator!=(const TVector<T>& other)
{
	return !(*this == other);
}

template<class T>
inline T& TVector<T>::operator[](size_t pos)
{
	return data[pos];
}

template<class T>
inline const T& TVector<T>::operator[](size_t pos) const
{
	return data[pos];
}

template<class T>
inline TVector<T> TVector<T>::operator+(const TVector<T>& other) const
{
	if (other.capacity != 0)
	{
		TVector<T> res(capacity + other.capacity);
		for (size_t i = 0; i < size; i++)
			res.push_back(data[i]);
		for (size_t i = 0; i < other.size; i++)
			res.push_back(other.data[i]);
		return res;
	}
	return *this;
}

template<class T>
class Row {
public:
	TVector<T*> row_data;
	T& operator[](size_t col)
	{
		if (col >= row_data.GetSize())
			throw invalid_argument("Error");
		return *row_data[col];
	}

	const T& operator[](size_t col) const
	{
		if (col >= row_data.GetSize())
			throw invalid_argument("Error");
		return *row_data[col];
	}
};

template<class T>
class ConstRow {
public:
	TVector<const T*> row_data;

	const T& operator[](size_t col) const
	{
		if (col >= row_data.GetSize())
			throw invalid_argument("Error");
		return *row_data[col];
	}
};


template<class T>
class TVectorProcs 
{
private:
	TBandedMatrix<T>& matrix; 
	size_t row_index;   
public:
	TVectorProcs(TBandedMatrix<T>& mat, size_t row) : matrix(mat), row_index(row) {}

	class ElementProxy {
	private:
		TBandedMatrix<T>& matrix;
		size_t row;
		size_t col;

	public:
		ElementProxy(TBandedMatrix<T>& m, size_t r, size_t c)
			: matrix(m), row(r), col(c) {}

		// Оператор присваивания - устанавливает значение
		ElementProxy& operator=(const T& value) {
			matrix.set(row, col, value);
			return *this;
		}

		// Оператор приведения к T - получает значение
		operator T() const {
			return matrix.get(row, col);
		}

		// Оператор +=, -= и другие можно добавить при необходимости
		ElementProxy& operator+=(const T& value) {
			T current = matrix.get(row, col);
			matrix.set(row, col, current + value);
			return *this;
		}
	};

	// Оператор [] возвращает прокси-объект
	ElementProxy operator[](size_t col) {
		if (col >= matrix.GetDim())
			throw std::invalid_argument("Column index out of bounds");
		return ElementProxy(matrix, row_index, col);
	}

};

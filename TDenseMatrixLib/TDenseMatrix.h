#pragma once
#include <initializer_list>
#include <stdexcept>
#include <iostream>
using namespace std;

template <class T> class TVector;
template <class T> class Row;
template <class T> class ConstRow;

template <class T>
class TDenseMatrix
{
public:

	TDenseMatrix();
	TDenseMatrix(const size_t row_, const size_t column_);
	TDenseMatrix(const TDenseMatrix<T>& other);
	TDenseMatrix(size_t column_, size_t row_, const T& other);
	TDenseMatrix(TDenseMatrix<T>&& other);
	TDenseMatrix(std::initializer_list<initializer_list<T>> init_list);

	size_t GetRow();
	size_t GetColumn();
	TVector<T> GetData();

	void SetRow(const size_t row_);
	void SetColumn(const size_t column_);

	T* begin() noexcept;
	const T* cbegin() const noexcept;

	T* end() noexcept;
	const T* cend() const noexcept;

	bool empty() const noexcept;
	bool full() const noexcept;
	void Clear() noexcept;

	void push_back(const T& elem);
	void push_front(const T& elem);

	void pop_back();
	void pop_front();
	
	Row<T> operator[](size_t row_index);
	ConstRow<T> operator[](size_t row_index) const;
	
	TDenseMatrix<T>& operator = (const TDenseMatrix<T>& other);
	TDenseMatrix<T>& operator = (TDenseMatrix <T>&& other) noexcept;
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
#include "TDenseMatrix.hpp"
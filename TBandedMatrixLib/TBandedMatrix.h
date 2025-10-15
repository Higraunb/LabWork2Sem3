#pragma once
#include <initializer_list>
#include <stdexcept>
#include <iostream>
using namespace std;

template <class T> class TDenseMatrix;
template <class T> class TVector;
template <class T> class TVectorProcs;

template <class T>
class TBandedMatrix
{
public:
	TBandedMatrix();
	TBandedMatrix(TDenseMatrix<T>& other);
	TBandedMatrix(const TBandedMatrix<T>& other);
	TBandedMatrix(TBandedMatrix<T>&& other);
	TBandedMatrix(initializer_list<initializer_list<T>> init_list);
	void set(size_t row, size_t col, const T& value);
	T get(size_t row, size_t col) const;
	void removeElement(size_t pos, size_t row);
	void insertElement(size_t pos, size_t row, size_t col, const T& value);
	size_t GetDim();
	TVector<size_t> GetRowElemCount();
	TVector<size_t> GetColumnIndex();
	TVector<T> GetData();

	void SetDim(const size_t dim_);

	TVector<T> begin() noexcept;
	const TVector<T> cbegin() const noexcept;

	TVector<T> end() noexcept;
	const TVector<T> cend() const noexcept;

	bool empty() const noexcept;
	bool full() const noexcept;
	void Clear() noexcept;

	TVectorProcs<T> operator[](size_t row_index);

	TBandedMatrix<T>& operator = (const TBandedMatrix<T>& other);
	TBandedMatrix<T>& operator = (TBandedMatrix<T>&& other) noexcept;
	TBandedMatrix<T> operator + (const TBandedMatrix<T>& other);
	TBandedMatrix<T> operator - (const TBandedMatrix<T>& other);
	TBandedMatrix<T> operator * (const TBandedMatrix<T>& other);

	bool operator==(const TBandedMatrix<T>& other);
	bool operator!=(const TBandedMatrix<T>& other);

	template<class O>
	friend ostream& operator << (ostream& out, TBandedMatrix<O>& other);
	template<class O>
	friend istream& operator >> (istream& input, TBandedMatrix<O>& other);
private:
	TVector<size_t> row_elem_count;
	TVector<size_t> column_index;
	TVector<T> data;
	size_t dim;
};
#include "TBandedMatrix.hpp"
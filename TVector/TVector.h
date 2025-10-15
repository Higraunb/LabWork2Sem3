#pragma once
#include <initializer_list>
#include <stdexcept>
#include <iostream>

using namespace std;

template <class T> class TBandedMatrix;
template <class T> class TDenseMatrix;

template <class T>
class TVector
{
public:
	TVector();
	TVector(size_t len);
	TVector(const size_t len, const T elem);
	TVector(const TVector<T> &other);
	TVector(std::initializer_list<T> init);
	TVector(TVector<T>&& other) noexcept;
	~TVector();
	
	size_t GetSize() const noexcept;
	size_t GetCapacity() const noexcept;
	T* GetData() const noexcept;
	
	void SetSize(const size_t size_);
	void SetCapacity(const size_t capacity_);
	void SetData(const T* data_);

	T* begin() noexcept;
	const T* begin() const noexcept;
	const T* cbegin() const noexcept;

	T* end() noexcept;
	const T* end() const noexcept;
	const T* cend() const noexcept;

	bool empty() const noexcept;
	bool full() const noexcept;
	void Clear() noexcept;
	
	void push_back(const T& elem);
	void push_front(const T& elem);

	void insert(size_t pos, const T& value);
	void erase(size_t pos);

	void insert(T* pos, const T& value);
	void erase(T* pos);

	void pop_back();
	void pop_front();
	
	TVector<T>& operator=(const TVector<T>& other);
	TVector<T>& operator=(TVector<T>&& other) noexcept;
	TVector<T>& operator=(std::initializer_list<T> init);
	T& operator[](size_t pos);
	const T& operator[](size_t pos) const;

	bool operator == (const TVector<T>& other);
	bool operator != (const TVector<T>& other);
	TVector<T> operator + (const TVector<T>& other) const;

	template<class O>
	friend std::istream& operator>>(std::istream& inp, TVector<O>& other);

	template<class O>
	friend std::ostream& operator<<(std::ostream& out, TVector<O>& other);

private:
	T* data;
	size_t capacity;
	size_t size;
};

#include "TVector.hpp"
// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>
#include <exception>
#include <utility>

using namespace std;

constexpr size_t MAX_VECTOR_SIZE = 100000000;
constexpr size_t MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
	ValType* pVector = nullptr;
	size_t Size = 0;       // размер вектора
public:
	TVector() = default;
	TVector(size_t sz);
	TVector(const TVector& v);                // конструктор копирования
	TVector(TVector&& other) noexcept;

	~TVector();


	size_t GetSize() const noexcept { return Size; } // размер вектора
	[[deprecated]] size_t GetStartIndex() { return 0; } // индекс первого элемента
	
	ValType& operator[](size_t pos);             // доступ
	const ValType& operator[](size_t pos) const;

	bool operator==(const TVector& v) const;  // сравнение
	bool operator!=(const TVector& v) const;  // сравнение

	TVector& operator=(const TVector& v);     // присваивание
	TVector& operator=(TVector&& other) noexcept;

	// скалярные операции
	TVector&  operator+=(const ValType& val);   // прибавить скаляр
	TVector&  operator-=(const ValType& val);   // вычесть скаляр
	TVector&  operator*=(const ValType& val);   // умножить на скаляр
	
	TVector  operator+(const ValType& val);   // прибавить скаляр
	TVector  operator-(const ValType& val);   // вычесть скаляр
	TVector  operator*(const ValType& val);   // умножить на скаляр

	// векторные операции
	TVector&  operator+=(const TVector& v);     // сложение
	TVector&  operator-=(const TVector& v);     // вычитание

	TVector  operator+(const TVector& v);     // сложение
	TVector  operator-(const TVector& v);     // вычитание
	ValType  operator*(const TVector& v);     // скалярное произведение

	// ввод-вывод
	friend istream& operator>>(istream& in, TVector& v)
	{
		for (int i = 0; i < v.Size; i++)
			in >> v.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TVector& v)
	{
		for (int i = 0; i < v.Size; i++)
			out << v.pVector[i] << ' ';
		return out;
	}

	template <typename U>
	friend struct _vector_reference;

private:
	size_t _check_size(size_t sz)
	{
		if (sz > MAX_VECTOR_SIZE) {
			throw std::exception("vector too long");
		}

		return sz;
	}

};


template <typename T>
TVector<T>::TVector(size_t sz)
	: pVector(new T[_check_size(sz)]{})
	, Size(sz)
{}


template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType>& other)
	: pVector(new ValType[other.Size]{})
	, Size(other.Size)
{
	for (size_t i = 0; i < this->Size; i++)
	{
		this->pVector[i] = other.pVector[i];
	}
} 

template <typename T>
TVector<T>::TVector(TVector<T>&& other) noexcept
	: pVector(other.pVector)
	, Size(other.Size)
{
	other.pVector = nullptr;
	other.Size = 0;
}

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[] this->pVector;
} 

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](size_t pos)
{
	if (pos >= this->Size) {
		throw std::range_error("out of vector");
	}

	return this->pVector[pos];
}

template <class ValType> // доступ
const ValType& TVector<ValType>::operator[](size_t pos) const
{
	return const_cast<TVector<T>&>(*this)[pos];
}

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector& v) const
{
	if (this == &v) return true;
	if (this->Size != v.Size) return false;

	for (size_t i = 0; i < this->Size; i++)
	{
		if (this->pVector[i] != v.pVector[i]) {
			return false;
		}
	}

	return true;
} 

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector& v) const
{
	return !(*this == v);
}


template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
	if (this == &v) return *this;

	this->~TVector();
	new (this) TVector<ValType>(v);

	return *this;
} 

template <typename T>
TVector<T>& TVector<T>::operator=(TVector&& other) noexcept
{
	if (this == &other) return *this;

	this->~TVector();
	new (this) TVector<T>(std::move(other));

	return *this;
}

template <typename T>
TVector<T>& TVector<T>::operator+=(const T& right)
{
	for (size_t i = 0; i < this->Size; i++)
	{
		this->pVector[i] += right;
	}

	return *this;
}

template <typename T>
TVector<T>& TVector<T>::operator-=(const T& right)
{
	for (size_t i = 0; i < this->Size; i++)
	{
		this->pVector[i] -= right;
	}

	return *this;
}

template <typename T>
TVector<T>& TVector<T>::operator*=(const T& right)
{
	for (size_t i = 0; i < this->Size; i++)
	{
		this->pVector[i] *= right;
	}

	return *this;
}

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
	auto tmp(*this);
	tmp += val;

	return tmp;
} 

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
	auto tmp(*this);
	tmp -= val;

	return tmp;
} 

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
	auto tmp(*this);
	tmp *= val;

	return tmp;
}



template <typename T>
TVector<T>& TVector<T>::operator+=(const TVector<T>& right)
{
	if (this->Size != right.Size)
	{
		throw std::logic_error("different size of vectors");
	}

	for (size_t i = 0; i < this->Size; i++)
	{
		this->pVector[i] += right.pVector[i];
	}

	return *this;
}

template <typename T>
TVector<T>& TVector<T>::operator-=(const TVector<T>& right)
{
	if (this->Size != right.Size)
	{
		throw std::logic_error("different size of vectors");
	}

	for (size_t i = 0; i < this->Size; i++)
	{
		this->pVector[i] -= right.pVector[i];
	}

	return *this;
}


template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v)
{
	auto tmp(*this);
	tmp += v;

	return tmp;
}

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v)
{
	auto tmp(*this);
	tmp -= v;

	return tmp;
} 

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
	if (this->Size != v.Size)
	{
		throw std::logic_error("different size of vectors");
	}

	ValType ans{};
	for (size_t i = 0; i < this->Size; i++)
	{
		ans += this->pVector[i] * v.pVector[i];
	}
	
	return ans;
} 


template <typename T>
struct _vector_reference
{
	_vector_reference(const TVector<T>& ptr, size_t si)
		: data(ptr)
		, start_index(si)
	{}

	T& operator[](size_t i)
	{
		if (i < start_index || i >= data.GetSize() + start_index) {
			throw std::range_error("out of matrix row");
		}

		return const_cast<T&>(data.pVector[i - start_index]);
	}

	const T& operator[](size_t i) const
	{
		return const_cast<_vector_reference&>(*this)[i];
	}

private:
	const TVector<T>& data;
	size_t start_index;
};

// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
private:
	using base = TVector<TVector<ValType>>;

public:
	TMatrix() = default;
	TMatrix(size_t sz);

	TMatrix(const TMatrix& mt) = default;                    // копирование
	TMatrix(TMatrix&&) = default;

	TMatrix& operator=(const TMatrix&) = default;
	TMatrix& operator=(TMatrix&&) = default;

	TMatrix(const TVector<TVector<ValType> >& mt); // преобразование типа
	
	//bool operator==(const TMatrix& mt) const;      // сравнение
	//bool operator!=(const TMatrix& mt) const;      // сравнение
	//TMatrix& operator= (const TMatrix& mt);        // присваивание
	TMatrix  operator+ (const TMatrix& mt);        // сложение
	TMatrix  operator- (const TMatrix& mt);        // вычитание

	_vector_reference<ValType> operator[](size_t i)
	{
		return _vector_reference<ValType>(this->pVector[i], i);
	}
	const _vector_reference<ValType> operator[](size_t i) const
	{
		return const_cast<TMatrix&>(*this)[i];
	}
	
	

	// ввод / вывод
	friend istream& operator>>(istream& in, TMatrix& mt)
	{
		for (int i = 0; i < mt.Size; i++)
			in >> mt.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TMatrix& mt)
	{
		for (int i = 0; i < mt.Size; i++)
			out << mt.pVector[i] << endl;
		return out;
	}

private:
	size_t _check_size(size_t sz)
	{
		if (sz > MAX_MATRIX_SIZE) {
			throw std::exception("vector too long");
		}

		return sz;
	}
};

template <class ValType>
TMatrix<ValType>::TMatrix(size_t sz) : TVector<TVector<ValType>>(_check_size(sz))
{
	for (size_t i = 0; i < sz; i++)
	{
		this->pVector[i] = TVector<ValType>(sz - i);
	}
}

//template <class ValType> // конструктор копирования
//TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) :
//	TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) :
	TVector<TVector<ValType> >(mt) {}

//template <class ValType> // сравнение
//bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
//{
//} /*-------------------------------------------------------------------------*/

//template <class ValType> // сравнение
//bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
//{
//} /*-------------------------------------------------------------------------*/
//
//template <class ValType> // присваивание
//TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
//{
//} /*-------------------------------------------------------------------------*/
//
template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
	return this->base::operator+(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
	return this->base::operator-(mt);
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif

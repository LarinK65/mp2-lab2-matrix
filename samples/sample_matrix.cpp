// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_matrix.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (20.04.2015)
//
// Тестирование верхнетреугольной матрицы

#include <iostream>
#include "utmatrix.h"
#include <cstddef>
//---------------------------------------------------------------------------

int main()
{
	std::ios::sync_with_stdio(false);

	std::cout << "enter size of matrixs: ";
	std::cout.flush();

	std::size_t size;
	std::cin >> size;

	TMatrix<int> a(size), b(size);

	std::cout << "enter first matrix with lower null elements" << std::endl;
	for (std::size_t i = 0; i < size; i++)
	{
		for (std::size_t j = 0; j < i; j++)
		{
			std::cin >> a[i][i];
		}
		for (std::size_t j = i; j < size; j++)
		{
			std::cin >> a[i][j];
		}
	}

	std::cout << "enter second matrix with lower null elements" << std::endl;
	for (std::size_t i = 0; i < size; i++)
	{
		for (std::size_t j = 0; j < i; j++)
		{
			std::cin >> b[i][i];
		}
		for (std::size_t j = i; j < size; j++)
		{
			std::cin >> b[i][j];
		}
	}

	std::cout << "enter operation \'+\' or \'-\'";
	std::cout.flush();

	char op;
	cin >> op;

#pragma warning(disable:26493)

	auto tmp = (op == '+' ? a + b : (op == '-' ? a - b : *(decltype(a - b)*)0));

	if (op == '+') {
		std::cout << "A + B = {" << std::endl;
	}
	else {
		std::cout << "A - B = {" << std::endl;
	}

	for (std::size_t i = 0; i < size; i++)
	{
		for (std::size_t j = 0; j < i; j++)
		{
			cout << "0 ";
		}
		for (std::size_t j = i; j < size; j++)
		{
			std::cout << tmp[i][j] << ' ';
		}
		std::cout << '\n';
	}

	std::cout << '}' << std::endl;

	return 0;
}
//---------------------------------------------------------------------------

#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> m(5);
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = i; j < 5; j++)
		{
			m[i][j] = i + j;
		}
	}

	TMatrix<int> m_copy(m);

	ASSERT_TRUE(m == m_copy);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> m(5);
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = i; j < 5; j++)
		{
			m[i][j] = i + j;
		}
	}

	TMatrix<int> m_copy(m);
	m_copy[0][0] = 1000;

	ASSERT_TRUE(m[0][0] == 0);
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> m(5);

	ASSERT_TRUE(m.GetSize() == 5);
}

//TEST(TMatrix, can_set_and_get_element)
//{
//  ADD_FAILURE();
//}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> m(5);

	ASSERT_ANY_THROW(m[-342978][-438783] = 5);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> m(5);

	ASSERT_ANY_THROW(m[6][0] = 0);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> m(5);
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = i; j < 5; j++)
		{
			m[i][j] = i + j;
		}
	}
	
	m = m;

	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = i; j < 5; j++)
		{
			ASSERT_TRUE(m[i][j] == i + j);
		}
	}
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> m(5);
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = i; j < 5; j++)
		{
			m[i][j] = i + j;
		}
	}

	TMatrix<int> m_copy(5);
	m_copy = m;

	ASSERT_TRUE(m == m_copy);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> m(5);
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = i; j < 5; j++)
		{
			m[i][j] = i + j;
		}
	}

	TMatrix<int> m_copy(5);
	m_copy = m;

	ASSERT_TRUE(m == m_copy);
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> m(5);
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = i; j < 5; j++)
		{
			m[i][j] = i + j;
		}
	}

	TMatrix<int> m_copy(1);
	m_copy = m;

	ASSERT_TRUE(m == m_copy);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> m(5);
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = i; j < 5; j++)
		{
			m[i][j] = i + j;
		}
	}

	TMatrix<int> m_copy(5);
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = i; j < 5; j++)
		{
			m_copy[i][j] = i + j;
		}
	}

	ASSERT_TRUE(m == m_copy);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> m(5);
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = i; j < 5; j++)
		{
			m[i][j] = i + j;
		}
	}

	ASSERT_TRUE(m == m);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> m(5);
	TMatrix<int> m1(1);

	ASSERT_TRUE(m != m1);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> m(5);
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = i; j < 5; j++)
		{
			m[i][j] = i + j;
		}
	}

	TMatrix<int> m1(5);
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = i; j < 5; j++)
		{
			m1[i][j] = 1;
		}
	}
	m += m1;

	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = i; j < 5; j++)
		{
			ASSERT_TRUE(m[i][j] == i + j + 1);
		}
	}
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> m(5);
	TMatrix<int> m1(1);

	ASSERT_ANY_THROW(m + m1);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> m(5);
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = i; j < 5; j++)
		{
			m[i][j] = i + j;
		}
	}

	TMatrix<int> m1(5);
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = i; j < 5; j++)
		{
			m1[i][j] = 1;
		}
	}

	m -= m1;

	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = i; j < 5; j++)
		{
			ASSERT_TRUE(m[i][j] == i + j - 1);
		}
	}
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> m(5);
	TMatrix<int> m1(1);

	ASSERT_ANY_THROW(m - m1);
}


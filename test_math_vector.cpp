#include "test_math_vector.h"
#include "math_vector.h"
#include <cassert>
#include <complex>

void tests::math_vector::test_constructors()
{
	MathVector<float> a{};
	assert(a.GetDim() == 0);

	MathVector<int> b(2);
	assert(b.GetDim() == 2);
	assert(b.GetAxisProject(0) == 0);
	assert(b.GetAxisProject(1) == 0);

	int tmp[3] = { 1, 3, 2 };
	MathVector<int> c{ tmp, 3 };
	assert(c.GetDim() == 3);
	assert(c.GetAxisProject(0) == 1);
	assert(c.GetAxisProject(1) == 3);
	assert(c.GetAxisProject(2) == 2);
}

void tests::math_vector::test_get_set()
{
	MathVector<std::complex<int>> a{ 3 };
	assert(a.GetDim() == 3);
	std::complex<int> tmp1(1, 2);
	std::complex<int> tmp2(7, 2);
	std::complex<int> tmp3(4, 9);
	a.SetAxisProject(0, tmp1);
	a.SetAxisProject(1, tmp3);
	a.SetAxisProject(2, tmp2);
	assert(a.GetAxisProject(0) == tmp1);
	assert(a.GetAxisProject(1) == tmp3);
	assert(a.GetAxisProject(2) == tmp2);

	bool error = false;
	try
	{
		a.SetAxisProject(3, tmp1);
	}
	catch(std::exception& e)
	{
		error = true;
		assert(strcmp(e.what(), "MathVector SetAxisProject: "
			"ArraySequence Set: index out of range") == 0);
	}
	assert(error);

	error = false;
	try
	{
		a.GetAxisProject(3);
	}
	catch (std::exception& e)
	{
		error = true;
		assert(strcmp(e.what(), "MathVector GetAxisProject: "
			"ArraySequence Get: index out of range") == 0);
	}
	assert(error);
}

void tests::math_vector::test_sum()
{
	int tmp1[2] = { 1, 2 };
	int tmp2[3] = { 3, 4, 5};
	MathVector<int> a(tmp1, 2);
	MathVector<int> b(tmp2, 2);
	MathVector<int> c(tmp2, 3);
	MathVector<int> res1 = a.Sum(&b);
	assert(res1.GetDim() == 2);
	assert(res1.GetAxisProject(0) == tmp1[0] + tmp2[0]);
	assert(res1.GetAxisProject(1) == tmp1[1] + tmp2[1]);
	MathVector<int> res2 = a.Sum(&c);
	assert(res2.GetDim() == 3);
	assert(res2.GetAxisProject(0) == tmp1[0] + tmp2[0]);
	assert(res2.GetAxisProject(1) == tmp1[1] + tmp2[1]);
	assert(res2.GetAxisProject(2) == tmp2[2]);
}

void tests::math_vector::test_multiply()
{
	int tmp1[3] = { 3, 4, 5 };
	MathVector<int> a(tmp1, 3);
	MathVector<int> b{};
	a = a.Multiply(4);
	assert(a.GetDim() == 3);
	assert(a.GetAxisProject(0) == 12);
	assert(a.GetAxisProject(1) == 16);
	assert(a.GetAxisProject(2) == 20);
	b = b.Multiply(6);
	assert(b.GetDim() == 0);
}

void tests::math_vector::test_norm()
{
	MathVector<int> a{};
	bool error = false;
	try {
		a.Norm();
	}
	catch (std::exception& e)
	{
		error = true;
		assert(strcmp(e.what(), "MathVector Norm: dimension is 0") == 0);
	}
	assert(error);

	MathVector<int> b(3);
	b.SetAxisProject(0, 3);
	assert(b.Norm() == 3);
	b.SetAxisProject(1, 4);
	assert(b.Norm() == 5);
}

void tests::math_vector::test_scalar_product()
{
	MathVector<int> a{};
	MathVector<int> b{};

	bool error = false;
	try
	{
		a.ScalarProduct(&b);
	}
	catch (std::exception& e)
	{
		error = true;
		assert(strcmp(e.what(), "MathVector ScalarProduct:"
			" vectors dimension is 0") == 0);
	}
	assert(error);

	MathVector<int> c(2);
	c.SetAxisProject(0, 2);
	c.SetAxisProject(1, -10);

	error = false;
	try
	{
		a.ScalarProduct(&c);
	}
	catch (std::exception& e)
	{
		error = true;
		assert(strcmp(e.what(),
			"MathVector ScalarProduct: different dimensions") == 0);
	}
	assert(error);

	MathVector<int> d(2);
	d.SetAxisProject(0, 4);
	d.SetAxisProject(1, 2);
	assert(c.ScalarProduct(&d) == -12);
}

void tests::math_vector::test_all()
{
	tests::math_vector::test_constructors();
	tests::math_vector::test_get_set();
	tests::math_vector::test_sum();
	tests::math_vector::test_multiply();
	tests::math_vector::test_norm();
	tests::math_vector::test_scalar_product();
}
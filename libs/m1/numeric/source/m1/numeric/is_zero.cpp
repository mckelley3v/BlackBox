#include "m1/is_zero.hpp"
#include "m1/abs.hpp"

namespace m1
{
	bool is_zero(const int x)
	{
		return x == 0;
	}

	bool is_zero(const long int x)
	{
		return x == 0l;
	}

	bool is_zero(const float x)
	{
		const float default_tolerance = 0.00001f;
		return is_zero(x, default_tolerance);
	}

	bool is_zero(const double x)
	{
		const double default_tolerance = 0.00001;
		return is_zero(x, default_tolerance);
	}

	bool is_zero(const long double x)
	{
		const long double default_tolerance = 0.00001l;
		return is_zero(x, default_tolerance);
	}

	bool is_zero(const float x, const float tolerance)
	{
		return abs(x) <= tolerance;
	}

	bool is_zero(const double x, const double tolerance)
	{
		return abs(x) <= tolerance;
	}

	bool is_zero(const long double x, const long double tolerance)
	{
		return abs(x) <= tolerance;
	}
} // namespace m1

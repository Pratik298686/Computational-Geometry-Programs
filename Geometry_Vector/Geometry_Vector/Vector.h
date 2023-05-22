#ifndef _VECTOR_H
#define _VECTOR_H

#include <iostream>
#include <array>
#include "Core.h"

namespace GeomVector
{
#define DIM2 2
#define DIM3 3

#define X 0
#define Y 1
#define Z 2

	template<class coordinate_type, size_t dimension = DIM3>
	class Vector {

		static_assert(std::is_arithmetic_v<coordinate_type>, "Vector class can only store Integral or Floating Point values");
		static_assert(dimension >= DIM2, "Vector dimension atleast should be 2D");

		std::array<coordinate_type, dimension> coords{ 0 };

		template<class coordinate_type, size_t dimension>
		friend float dotProduct(const Vector<coordinate_type, dimension>&, const Vector<coordinate_type, dimension>&);

	public:
		Vector() {}

		Vector(std::array<coordinate_type, dimension> _coords) : coords(coords) {}

		Vector(coordinate_type _x, coordinate_type _y, coordinate_type _z) : coords({ _x, _y, _z }) {}

		Vector(coordinate_type _x, coordinate_type _y) : coords({ _x, _y }) {}

		// Equality check
		bool operator==(const Vector<coordinate_type, dimension>&) const;

		// Not equal
		bool operator!=(const Vector<coordinate_type, dimension>&) const;

		// Addition
		Vector<coordinate_type, dimension> operator+(const Vector<coordinate_type, dimension>&) const;

		// Substraction
		Vector<coordinate_type, dimension> operator-(const Vector<coordinate_type, dimension>&) const;

		// Multiplication
		Vector<coordinate_type, dimension> operator*(coordinate_type value);

		// Less Than Operator
		bool operator<(const Vector<coordinate_type, dimension>&) const;

		// Greater Than Operator
		bool operator>(const Vector<coordinate_type, dimension>&) const;

		// Indexing operator
		coordinate_type operator[](const unsigned int) const;

		// Update already assign vector
		void assign(int _index, coordinate_type value);

		double magnitude() const;

		void normalize();
	};

	typedef Vector<float, DIM2> vector2f;
	typedef Vector<float, DIM3> vector3f;

	template<class coordinate_type, size_t dimension>
	inline bool Vector<coordinate_type, dimension>::operator==(const Vector<coordinate_type, dimension>& _other) const
	{
		for (size_t i = 0; i < dimension; ++i)
		{
			if (isEqualD(coords[i], _other.coords[i]))
				return false;
		}
		return true;
	}

	template<class coordinate_type, size_t dimension>
	inline bool Vector<coordinate_type, dimension>::operator!=(const Vector<coordinate_type, dimension>& _other) const
	{
		return !(*this == _other);
	}

	template<class coordinate_type, size_t dimension>
	inline Vector<coordinate_type, dimension> Vector<coordinate_type, dimension>::operator+(const Vector<coordinate_type, dimension>& _other) const
	{
		std::array<coordinate_type, dimension> temp_array;

		for (size_t i = 0; i < dimension; ++i)
		{
			temp_array[i] = coords[i] + _other.coords[i];
		}

		return Vector<coordinate_type, dimension>(temp_array);
	}

	template<class coordinate_type, size_t dimension>
	inline Vector<coordinate_type, dimension> Vector<coordinate_type, dimension>::operator-(const Vector<coordinate_type, dimension>& _other) const
	{
		std::array<coordinate_type, dimension> temp_array;

		for (size_t i = 0; i < dimension; ++i)
		{
			temp_array[i] = coords[i] - _other.coords[i];
		}

		return Vector<coordinate_type, dimension>(temp_array);
	}

	template<class coordinate_type, size_t dimension>
	inline Vector<coordinate_type, dimension> Vector<coordinate_type, dimension>::operator*(coordinate_type value)
	{
		std::array<coordinate_type, dimension> temp_array;

		for (size_t i = 0; i < dimension; ++i)
		{
			temp_array[i] = coords[i] * value;
		}

		return Vector<coordinate_type, dimension>(temp_array);
	}

	template<class coordinate_type, size_t dimension>
	inline bool Vector<coordinate_type, dimension>::operator<(const Vector<coordinate_type, dimension>& _other) const
	{
		for (size_t i = 0; i < dimension; ++i)
		{
			if (this->coords[i] < _other.coords[i])
				return true;
			else if (this->coord[i] > _other.coords[i])
				return false;
		}
		return false;
	}

	template<class coordinate_type, size_t dimension>
	inline bool Vector<coordinate_type, dimension>::operator>(const Vector<coordinate_type, dimension>& _other) const
	{
		for (size_t i = 0; i < dimension; ++i)
		{
			if (this->coords[i] > _other.coords[i])
				return true;
			else if (this->coord[i] < _other.coords[i])
				return false;
		}
		return false;
	}

	template<class coordinate_type, size_t dimension>
	inline coordinate_type Vector<coordinate_type, dimension>::operator[](const unsigned int _index) const
	{
		if (_index >= coords.size())
		{
			std::cout << "Index Out Of Bound" << std::endl;
			return coordinate_type();
		}
		return coords[_index];
	}

	template<class coordinate_type, size_t dimension>
	inline void Vector<coordinate_type, dimension>::assign(int _index, coordinate_type value)
	{
		if (_index >= coords.size())
		{
			std::cout << "Index Out Of Bound" << std::endl;
		}

		coords[_index] = value;
	}


	template<class coordinate_type, size_t dimension>
	inline double Vector<coordinate_type, dimension>::magnitude() const
	{
		double value = 0.0;

		for (size_t i = 0; i < dimension; ++i)
		{
			value += pow(coords[i], 2.0);
		}

		return sqrt(value);
	}


	template<class coordinate_type, size_t dimension>
	inline void Vector<coordinate_type, dimension>::normalize()
	{
		auto mag = magnitude();

		for (size_t i = 0; i < dimension; ++i)
		{
			assign(i, coords[i] / mag);
		}
	}

	template<class coordinate_type, size_t dimension>
	float dotProduct(const Vector<coordinate_type, dimension>& v1, const Vector<coordinate_type, dimension>& v2)
	{
		if (v1.coords.size() != v2.coords.size())
			return FLT_MIN;

		float product = 0.0;

		for (size_t i = 0; i < dimension; ++i)
		{
			product += v1[i] * v2[i];
		}

		return product;
	}

	vector2f scalerProduct2D(float scalerValue, vector2f v2);

	float crossProduct2D(vector2f v1, vector2f v2);

	vector3f crossProduct3D(vector3f v1, vector3f v2);

	float scalerTripleProduct(vector3f v1, vector3f v2, vector3f v3);
}

#endif // !_VECTOR_H


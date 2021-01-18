#ifndef GMATH_HPP
#define GMATH_HPP
#include<cmath>
#include"vector.hpp"
#include"mat.h"
namespace agl
{
	const float pi = 3.141592653;
	template<typename T>
	agl::vector2<T> sqrt(const agl::vector2<T>& v)
	{
		return agl::vector2<float>(std::sqrt(v.x), std::sqrt(v.y));
	}

	template<typename T>
	agl::vector3<T> sqrt(const agl::vector3<T>& v)
	{
		return agl::vector3<float>(std::sqrt(v.x), std::sqrt(v.y), std::sqrt(v.z));
	}


	template<typename T>
	T dot(const agl::vector2<T>& v1, const agl::vector2<T>& v2)
	{
		return (v1.x * v2.x + v1.y * v2.y);
	}

	template<typename T>
	T dot(const agl::vector3<T>& v1, const agl::vector3<T>& v2)
	{
		return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
	}

	template<typename T>
	agl::vector2<T> sign(const agl::vector2<T>& v)
	{
		return (v.x>=0?1:-1,v.y>=0?1:-1);
	}

	template<typename T>
	agl::vector2<T> operator*(T n, const vector2<T>& v)
	{
		return agl::vector2<T>(n * v.x, n * v.y);
	}

	template<typename T>
	agl::vector2<T> operator*(const vector2<T>& u,const vector2<T>& v)
	{
		return agl::vector2<T>(u.x * v.x, u.y * v.y);
	}

	template<typename T>
	agl::vector3<T> operator*(T n, const vector3<T>& v)
	{
		return agl::vector3<T>(n * v.x, n * v.y, n * v.z);
	}

	template<typename T>
	agl::vector2<T> operator*(const mat2x2<T>& m, const vector2<T>& v)
	{
		return vector2<T>(m.x1 * v.x + m.x2 * v.y, m.y1 * v.x + m.y2 * v.y);
	}

	template<typename T>
	agl::mat2x2<T> operator*(const mat2x2<T>& m1, const mat2x2<T>& m2)
	{
		return mat2x2<T>(
			m1.x1 * m2.x1 + m1.x2 * m2.y1,
			m1.x1 * m2.x2 + m1.x2 * m2.y2,
			m1.y1 * m2.x1 + m1.y2 * m2.y1,
			m1.y1 * m2.x2 + m1.y2 * m2.y2
			);
	}

	template<typename T, template<typename> class V>
	V<T> operator*(const V<T>& v, T n)
	{
		return n * v;
	}

	template<typename T>
	agl::vector2<T> operator-(const vector2<T>& v1, const vector2<T>& v2)
	{
		return agl::vector2<T>(v1.x - v2.x, v1.y - v2.y);
	}

	template<typename T>
	agl::vector2<T> operator-(const vector2<T>& v)
	{
		return agl::vector2<T>(-v.x, -v.y);
	}

	template<typename T>
	agl::vector2<T> operator+(const vector2<T>& v1, const vector2<T>& v2)
	{
		return agl::vector2<T>(v1.x + v2.x, v1.y + v2.y);
	}

	template<typename T>
	agl::vector3<T> operator-(const vector3<T>& v1, const vector3<T>& v2)
	{
		return agl::vector3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	template<typename T>
	agl::vector2<T> operator+=(vector2<T>& v1, const vector2<T>& v2)
	{
		return (v1 = v1 + v2);
	}

	template<typename T, template<typename>class V>
	T length(const V<T>& v)
	{
		return std::sqrt(dot(v, v));
	}

	template<typename T>
	agl::vector3<T> cross(const agl::vector3<T>& v1, const agl::vector3<T>& v2)
	{
		return vector3<T>(v1.y * v2.z - v2.y * v1.z,
			v1.z * v2.x - v2.z * v1.x,
			v1.x * v2.y - v2.x * v1.y);
	}

	template<typename T>
	float cross(const agl::vector2<T>& v1, const agl::vector2<T>& v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}

	template<typename T>
	agl::vector2<T> cross(T s, const agl::vector2<T>& v)
	{
		return vector2<T>(-s * v.y, s * v.x);
	}

	template<typename T>
	agl::vector2<T> cross(const agl::vector2<T>& v, T s)
	{
		return vector2<T>(s * v.y, -s * v.x);
	}
	
	template<typename T, template<typename> class V>
	V<T> normalize(const V<T>& v)
	{
		return (1 / length(v)) * v;
	}

	template<typename T>
	agl::vector3<T> fabs(const agl::vector3<T>& v)
	{
		return vector3<T>(std::fabs(v.x), std::fabs(v.y), std::fabs(v.z));
	}

	template<typename T>
	agl::vector3<T> abs(const agl::vector3<T>& v)
	{
		return vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
	}

	template<typename T>
	agl::vector2<T> abs(const agl::vector2<T>& v)
	{
		return vector2<T>(std::abs(v.x), std::abs(v.y));
	}

	template<typename T>
	agl::mat2x2<T> abs(const agl::mat2x2<T>& m)
	{
		return mat2x2<T>(std::abs(m.x1), std::abs(m.y1), std::abs(m.x2), std::abs(m.y2));
	}
};
#endif // GMATH_HPP

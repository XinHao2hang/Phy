#pragma once
#include"vector.hpp"
#include<cmath>
#include"scoin.h"
namespace agl
{
	template<typename T>
	class mat2x2
	{
	public:
		T x1, y1, x2, y2;
		mat2x2() {}
		mat2x2(T angle)
		{
			//float c = Lcos(angle), s = Lsin(angle);
			float c = std::cos(angle), s = std::sin(angle);
			x1 = c; x2 = -s;
			y1 = s; y2 = c;
		}
		//列数据输入
		mat2x2(T a, T b, T c, T d) :x1(a), y1(b), x2(c), y2(d) {}
		//获取行列数据
		vector2<T> col(int index) { return (index == 0 ? vector2<T>(x1, y1) : vector2<T>(x2, y2)); }
		vector2<T> row(int index) { return (index == 0 ? vector2<T>(x1,x2): vector2<T>(y1, y2)); }
		mat2x2 Transpose() { return mat2x2(x1,x2,y1,y2); }
	};
};


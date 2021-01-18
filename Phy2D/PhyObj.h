#pragma once
#include"PhyAttr.h"
#include"Shapes.h"
enum ShapeType
{
	RECTANGLE,
	CIRCLE
};
using namespace agl;
namespace phy2d
{
	class PhyObj: public PhyAttr 
	{
	public:
		ShapeType type = RECTANGLE;
		virtual std::tuple<float, float, float, float> getMax() = 0;
	};
	class PhyRect :public PhyObj,public Rectangle
	{
	public:

		PhyRect() {}
		PhyRect(const vec2f _r, const vec2f& pos, float m) 
		{ 
			r  =_r; 
			position = pos; 
			mass = m; 
			if (m < FLT_MAX)
			{
				invMass = 1.0 / m;
				I = mass * (4.0f*r.x * r.x + 4.0f*r.y * r.y) / 12.0f;
				invI = 1.0f / I;
			}
			else
			{
				invMass = 0;
				I = FLT_MAX;
				invI = 0.0f;
			}
			type = RECTANGLE;
		}
		virtual std::tuple<float, float, float, float> getMax()
		{
			vec2f points[4];
			vec2f sign[4] = {vec2f(1,1),vec2f(-1,1),vec2f(1,-1),vec2f(-1,-1)};
			mat2f rot = mat2f(rotation * pi / 180.0);
			for (int i = 0; i < 4; i++)
				points[i] = rot * vec2f(r.x * sign[i].x, r.y * sign[i].y) + position;
			float max_x = points[0].x, min_x = points[0].x, max_y = points[0].y, min_y = points[0].y;
			for (int i = 0; i < 4; i++)
			{
				if (max_x < points[i].x)
					max_x = points[i].x;
				if (min_x > points[i].x)
					min_x = points[i].x;
				if (max_y < points[i].y)
					max_y = points[i].y;
				if (min_y > points[i].y)
					min_y = points[i].y;
			}
			return std::make_tuple(min_x, min_y, max_x, max_y);
		}
	};

	class PhyCircle :public PhyObj, public Circle
	{
	public:
		PhyCircle() {}
		PhyCircle(const float _r, const vec2f& pos, float m)
		{
			r = _r;
			position = pos;
			mass = m;
			if (m < FLT_MAX)
			{
				invMass = 1.0 / m;
				I = mass * r * r * 0.5f;
				invI = 1.0f / I;
			}
			else
			{
				invMass = 0;
				I = FLT_MAX;
				invI = 0.0f;
			}
			type = CIRCLE;
		}
		virtual std::tuple<float, float, float, float> getMax()
		{
			float min_x = position.x - r;
			float min_y = position.y - r;
			float max_x = position.x + r;
			float max_y = position.y + r;
			return std::make_tuple(min_x, min_y, max_x, max_y);
		}
		~PhyCircle() {}
	};
};

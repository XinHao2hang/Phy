#pragma once
#include"core.h"
class Shape
{
public:

};
class Rectangle :public Shape
{
public:
	//�洢���εĳ���
	agl::vec2f r;
};

class Circle :public Shape
{
public:
	float r;
};
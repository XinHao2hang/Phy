#pragma once
#include"core.h"
class Shape
{
public:

};
class Rectangle :public Shape
{
public:
	//´æ´¢¾ØÐÎµÄ³¤¿í
	agl::vec2f r;
};

class Circle :public Shape
{
public:
	float r;
};
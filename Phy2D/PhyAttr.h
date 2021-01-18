#pragma once
#include"core.h"
#include<iostream>
namespace phy2d
{
	class PhyAttr
	{
	public:
		PhyAttr()
		{
			velocity = agl::vec2f(0.0f);
			position = agl::vec2f(0.0f);
			force = agl::vec2f(0.0f);
		}
		agl::vec2f velocity;//速度
		agl::vec2f position;//位置
		float rotation = 0.0f;//旋转角度
		float angularVelocity = 0.0f;//角速度
		agl::vec2f force;//力
		float torque = 0.0f;//转矩
		float friction = 0.0f;//摩擦力
		float mass = 0.0f, invMass = 0.0f;//质量和逆
		float I = 0.0f, invI = 0.0f;//转动惯量和逆
		void addForce(const agl::vec2f& f) { force += f; }
		void applyForce(float time) { velocity += (force * time); force = agl::vec2f(0.0f); }
		//更新读取
		void applyVelocity(float time) 
		{ 
			position += velocity * time; 
			rotation += (angularVelocity * time)*(180.0f/3.1415936f);
		}
		//更新物体速度受力
		void update(const agl::vec2f&f,float time)
		{
			addForce(f);
			applyForce(time);
			applyVelocity(time);
			force = agl::vec2f(0.0f);
		}
		~PhyAttr() {}
	};
};
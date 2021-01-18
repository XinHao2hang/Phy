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
		agl::vec2f velocity;//�ٶ�
		agl::vec2f position;//λ��
		float rotation = 0.0f;//��ת�Ƕ�
		float angularVelocity = 0.0f;//���ٶ�
		agl::vec2f force;//��
		float torque = 0.0f;//ת��
		float friction = 0.0f;//Ħ����
		float mass = 0.0f, invMass = 0.0f;//��������
		float I = 0.0f, invI = 0.0f;//ת����������
		void addForce(const agl::vec2f& f) { force += f; }
		void applyForce(float time) { velocity += (force * time); force = agl::vec2f(0.0f); }
		//���¶�ȡ
		void applyVelocity(float time) 
		{ 
			position += velocity * time; 
			rotation += (angularVelocity * time)*(180.0f/3.1415936f);
		}
		//���������ٶ�����
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
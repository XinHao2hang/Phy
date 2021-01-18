#pragma once
#include<vector>
#include"PhyObj.h"
#include"core.h"
using namespace agl;
namespace phy2d
{
	class Impulse
	{
	public:
		//正面和侧面的动量
		float ImpulseNormal = 0;
		float ImpulseSide = 0;
		float friction = 0.1f;
	};
	//碰撞信息
	class Contact
	{
	public:
		Contact() {}
		Contact(vec2f pos,vec2f n,float s):position(pos),normal(n),separation(s) {}
		vec2f position;//碰撞点位置
		vec2f normal;//分离轴方向
		//agl::vec2f r1, r2;//半径//现场算
		float separation;//最小相交距离
		~Contact() {}
	};

	class Driver :public Impulse
	{
	public:
		Driver() {}
		Driver(PhyObj* _a, PhyObj* _b, std::vector<Contact>& _c) :a(_a), b(_b), contacts(_c) {}
		//不更新原有动量信息
		void overlap(const Driver & d)
		{
			contacts = d.contacts;
			a = d.a;
			b = d.b;
		}
		//碰撞信息列表
		std::vector<Contact> contacts;
		//碰撞物体
		PhyObj *a, *b;
		//运动执行函数
		void ApplyImpulse(float time)
		{
			//计算好必要的值
			//float M = (a->invMass + b->invMass);
			for (int i = 0; i < contacts.size(); i++)
			{
				vec2f r1 = contacts[i].position - a->position;
				vec2f r2 = contacts[i].position - b->position;
				float M = (a->invMass + b->invMass);
				float bias = -0.3 * (1 / time) * std::min(0.0f, (-abs(contacts[i].separation) + 0.01f));
				float rna = dot(r1, contacts[i].normal);
				float rnb = dot(r2, contacts[i].normal);
				M += (a->invI * (dot(r1, r1) - rna * rna) + b->invI * (dot(r2, r2) - rnb * rnb));
				if (M == 0)
					continue;
				M = 1.0 / M;

				//相对速度
				vec2f V = b->velocity + cross(b->angularVelocity, r2) - a->velocity - cross(a->angularVelocity, r1);
				//vec2f V = b->velocity - a->velocity;
				//计算动冲量
				float P = ((-dot(V, contacts[i].normal)+bias)*M);

				float P0 = ImpulseNormal;
				//这里做是是冲量的累加，如果累加结果小于0了就等于0
				ImpulseNormal = std::max(P0 + P, 0.0f);
				
				//还原出累加进去的冲量大小
				P = ImpulseNormal -  P0;

				//normal方向上的冲量
				vec2f normalP = P * contacts[i].normal;
				//计算物体运动速度
				a->velocity = a->velocity - a->invMass * normalP;
				b->velocity = b->velocity + b->invMass * normalP;

				a->angularVelocity -= a->invI * cross(r1, normalP);
				b->angularVelocity += b->invI * cross(r2, normalP);
				ImpulseNormal += P;

				//计算摩擦力
				//获取摩擦力方向
				vec2f tangentNormal = cross(contacts[i].normal,1.0f);
				//计算切线方向的冲量
				float trna = dot(r1, tangentNormal);
				float trnb = dot(r2, tangentNormal);
				M = (a->invMass + b->invMass);
				M += (a->invI * (dot(r1, r1) - trna * trna) + b->invI * (dot(r2, r2) - trnb * trnb));
				M = 1.0 / M;

				//计算相对速度
				V = b->velocity + cross(b->angularVelocity, r2) - a->velocity - cross(a->angularVelocity, r1);
				float tP = (-dot(V, tangentNormal) * M);
				
				//保存冲量
				float maxPt = friction * ImpulseNormal;
				float oldTangentImpulse = ImpulseSide;
				ImpulseSide = std::max( - maxPt, std::min(oldTangentImpulse + tP, maxPt));
				tP = ImpulseSide - oldTangentImpulse;
				
				vec2f tangentP = tP * tangentNormal;

				a->velocity = a->velocity - a->invMass * tangentP;
				b->velocity = b->velocity + b->invMass * tangentP;

				a->angularVelocity -= a->invI * cross(r1, tangentP);
				b->angularVelocity += b->invI * cross(r2, tangentP);		
			}
		}
	};
}

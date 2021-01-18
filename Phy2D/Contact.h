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
		//����Ͳ���Ķ���
		float ImpulseNormal = 0;
		float ImpulseSide = 0;
		float friction = 0.1f;
	};
	//��ײ��Ϣ
	class Contact
	{
	public:
		Contact() {}
		Contact(vec2f pos,vec2f n,float s):position(pos),normal(n),separation(s) {}
		vec2f position;//��ײ��λ��
		vec2f normal;//�����᷽��
		//agl::vec2f r1, r2;//�뾶//�ֳ���
		float separation;//��С�ཻ����
		~Contact() {}
	};

	class Driver :public Impulse
	{
	public:
		Driver() {}
		Driver(PhyObj* _a, PhyObj* _b, std::vector<Contact>& _c) :a(_a), b(_b), contacts(_c) {}
		//������ԭ�ж�����Ϣ
		void overlap(const Driver & d)
		{
			contacts = d.contacts;
			a = d.a;
			b = d.b;
		}
		//��ײ��Ϣ�б�
		std::vector<Contact> contacts;
		//��ײ����
		PhyObj *a, *b;
		//�˶�ִ�к���
		void ApplyImpulse(float time)
		{
			//����ñ�Ҫ��ֵ
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

				//����ٶ�
				vec2f V = b->velocity + cross(b->angularVelocity, r2) - a->velocity - cross(a->angularVelocity, r1);
				//vec2f V = b->velocity - a->velocity;
				//���㶯����
				float P = ((-dot(V, contacts[i].normal)+bias)*M);

				float P0 = ImpulseNormal;
				//���������ǳ������ۼӣ�����ۼӽ��С��0�˾͵���0
				ImpulseNormal = std::max(P0 + P, 0.0f);
				
				//��ԭ���ۼӽ�ȥ�ĳ�����С
				P = ImpulseNormal -  P0;

				//normal�����ϵĳ���
				vec2f normalP = P * contacts[i].normal;
				//���������˶��ٶ�
				a->velocity = a->velocity - a->invMass * normalP;
				b->velocity = b->velocity + b->invMass * normalP;

				a->angularVelocity -= a->invI * cross(r1, normalP);
				b->angularVelocity += b->invI * cross(r2, normalP);
				ImpulseNormal += P;

				//����Ħ����
				//��ȡĦ��������
				vec2f tangentNormal = cross(contacts[i].normal,1.0f);
				//�������߷���ĳ���
				float trna = dot(r1, tangentNormal);
				float trnb = dot(r2, tangentNormal);
				M = (a->invMass + b->invMass);
				M += (a->invI * (dot(r1, r1) - trna * trna) + b->invI * (dot(r2, r2) - trnb * trnb));
				M = 1.0 / M;

				//��������ٶ�
				V = b->velocity + cross(b->angularVelocity, r2) - a->velocity - cross(a->angularVelocity, r1);
				float tP = (-dot(V, tangentNormal) * M);
				
				//�������
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

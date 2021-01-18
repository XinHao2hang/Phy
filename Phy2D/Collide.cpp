#include "Collide.h"
#include"core.h"
#include<iostream>
#include<algorithm>
using std::max;
using std::make_tuple;
using std::get;
using std::tuple;
using std::vector;
using agl::vec2f;
using agl::mat2f;
#define X_AXIS 0
#define Y_AXIS 1
namespace phy2d
{
	float sign(float value)
	{
		if (value >= 0)return 1;
		else  return -1;
	}

	bool Collide(PhyObj* obj1, PhyObj* obj2, std::vector<Contact>& contacts)
	{
		if (obj1->type == RECTANGLE && obj2->type == RECTANGLE)
			return CollideRectRect(obj1, obj2, contacts);
		else if (obj1->type == RECTANGLE && obj2->type == CIRCLE)
			return CollideRectCircle(obj1, obj2, contacts,true);
		else if (obj1->type == CIRCLE && obj2->type == RECTANGLE)
			return CollideRectCircle(obj2, obj1, contacts,false);
		else if (obj1->type == CIRCLE && obj2->type == CIRCLE)
			return CollideCircleCircle(obj1,obj2,contacts);
		return true;
	}
	bool CollideRectRect(PhyObj* A, PhyObj* B, std::vector<Contact>& contacts)
	{
		//��ȡ����������Ϣ
		PhyRect* rectA = static_cast<PhyRect*>(A);
		PhyRect* rectB = static_cast<PhyRect*>(B);
		//��ȡ���ΰ뾶
		vec2f rA = rectA->r, rB = rectB->r;
		//��ȡ����λ��
		vec2f posA = rectA->position, posB = rectB->position;
		//����;������
		float theta = agl::pi / 180;
		mat2f rotA(rectA->rotation * theta), rotB(rectB->rotation * theta);
		mat2f rotAT = rotA.Transpose(), rotBT = rotB.Transpose();
		mat2f rotAB = rotBT * rotA, rotBA = rotAT * rotB;
		//��ȡ���������µ���������
		vec2f centerLine = (posB - posA), centerLineA = rotAT * centerLine, centerLineB = -(rotBT * centerLine);
		//�������ж���ײ
		vec2f satIntersectA = abs(centerLineA) - (rA + abs(rotAB) * rB);
		vec2f satIntersectB = abs(centerLineB) - (rB + abs(rotBA) * rA);

		if (satIntersectA.x > 0 || satIntersectA.y > 0 || satIntersectB.x > 0 || satIntersectB.y > 0) return false;
		vec2f AtoBDir = posB - posA;
		//��¼�ཻ������С����;���
		auto cmpfun = [](std::tuple<float, const vec2f&, int> a, decltype(a) b) {return get<0>(a) < get<0>(b); };
		std::tuple<float, vec2f, int> contact_info = max(
			max(make_tuple(satIntersectA.x, abs(rotA.col(0)), 0), make_tuple(satIntersectA.y, abs(rotA.col(1)), 0), cmpfun),
			max(make_tuple(satIntersectB.x, abs(rotB.col(0)), 1), make_tuple(satIntersectB.y, abs(rotB.col(1)), 1), cmpfun), cmpfun);

		get<1>(contact_info) = vec2f(sign(AtoBDir.x),sign(AtoBDir.y))*get<1>(contact_info);

		//���������������ཻʱ��ȡ�ĸ���,����ײ��ָ�������ΪA
		//�������A��λ�ƣ�A�İ뾶��B�İ뾶����A�����ķ��뷽�򣬴�B�����ķ��뷽��,��A��B�ı任����
		auto find_points = [](vec2f posOffset, vec2f rA, vec2f rB, vec2f axisA, vec2f axisB, mat2f rot, int axisDirection) {// yA = (1,normalFA),xA = (normalFA,1),B=(+-1,normalFB)

			vec2f pA = rot * vec2f(axisA.x * rA.x, axisA.y * rA.y) + posOffset;
			vec2f npA = pA - 2.0f * rot.col(axisDirection) * (axisDirection == X_AXIS ? rA.x : rA.y);

			vector<tuple<vec2f, int>> pts = (axisDirection == X_AXIS 
				? vector<tuple<vec2f, int>>{ make_tuple(vec2f(axisB.x * rB.x, axisB.y * rB.y), 1), make_tuple(vec2f(-axisB.x * rB.x, axisB.y * rB.y), 1), make_tuple(pA, -1), make_tuple(npA, -1) }
				: vector<tuple<vec2f, int>>{ make_tuple(vec2f(axisB.x * rB.x, -axisB.y * rB.y), 1), make_tuple(vec2f(axisB.x * rB.x, axisB.y * rB.y), 1), make_tuple(pA, -1), make_tuple(npA, -1) });
			
			std::sort(pts.begin(), pts.end(), [axisDirection](tuple<vec2f, int>& a, tuple<vec2f, int>& b) {return get<0>(a)[axisDirection] > get<0>(b)[axisDirection]; });
			
			return vector<tuple<vec2f, int>>{ pts[1], pts[2] };
		};

		auto getCollideInfo = [find_points](vec2f posOffset, vec2f rA, vec2f rB, vec2f normalFA, vec2f normalFB, vec2f pos, mat2f&rotB, mat2f&rotAB, float separation) {
			vector<tuple<vec2f, int>> points;
			//ȫ��ת����B�����¼���
			if (normalFB.x == 0)
				//ȫ���任��B�����¼���
				points = find_points(posOffset, rA, rB, vec2f(1, sign(normalFA.y)), vec2f(1, sign(normalFB.y)), rotAB, X_AXIS);
			else if (normalFB.y == 0)
				points = find_points(posOffset, rA, rB, vec2f(sign(normalFA.x), 1), vec2f(sign(normalFB.x), 1), rotAB, Y_AXIS);
			else
				points.push_back(make_tuple(agl::vec2f(sign(normalFB.x) * rB.x, sign(normalFB.y) * rB.y), 1));
			for (auto& p : points)
				get<0>(p) = (rotB * get<0>(p) + pos) + normalFA * (get<1>(p) * abs(separation));//���һ���Ƿ������
			return points;
		};
		//��ʱ��A��������Ϊ��,ȫ��ת����B�¼���
		vector<tuple<vec2f, int>> points = (get<2>(contact_info) == 0 
			? getCollideInfo(rotBT * (-centerLine), rA, rB, rotAT * (-get<1>(contact_info)), rotBT * (-get<1>(contact_info)), posB, rotB, rotAB, get<0>(contact_info))//A���B��λ�ƣ�A�뾶��B�뾶��Aָ��B�ķ�������(��A������)��Bָ��A�ķ������(��B������)
			: getCollideInfo(rotAT * (centerLine), rB, rA, rotBT * (get<1>(contact_info)), rotAT * (get<1>(contact_info)), posA, rotA, rotBA, get<0>(contact_info)));//��ת����A�¼���  //B���A��λ�ƣ�Bָ��A�ķ�������(��B������)��Aָ��B�ķ������(��A������)
		
		for (int i = 0; i < points.size(); i++)
			contacts.push_back(Contact(get<0>(points[i]), get<1>(contact_info), get<0>(contact_info)));
		//if(points.size() == 1)
		//	contacts.push_back(Contact(get<0>(points[0]), get<1>(contact_info), get<0>(contact_info)));
		//else 
		//	contacts.push_back(Contact(0.5f * (get<0>(points[0])+get<0>(points[1])), get<1>(contact_info), get<0>(contact_info)));

		return true;
	}
	bool CollideCircleCircle(PhyObj*A, PhyObj*B, std::vector<Contact>& contacts)
	{
		//��ȡ����������Ϣ
		PhyCircle* circleA = static_cast<PhyCircle*>(A);
		PhyCircle* circleB = static_cast<PhyCircle*>(B);
		float rA = circleA->r;
		float rB = circleB->r;
		vec2f distanceVector = (circleB->position - circleA->position);
		float distance = length(distanceVector);
		float R = rA + rB;
		if (distance > R)
			return false;
		//��ȡ�ཻ����
		float intersect = R - distance;
		vec2f n = normalize(distanceVector);
		contacts.push_back(Contact(circleA->position+n * (rA-intersect),n,intersect));
		return true;
	}
	bool CollideRectCircle(PhyObj*A, PhyObj*B, std::vector<Contact>& contacts,bool AisR)
	{
		PhyRect* rectA = static_cast<PhyRect*>(A);
		PhyCircle* circleB = static_cast<PhyCircle*>(B);
		vec2f rA = rectA->r;
		float rB = circleB->r;
		vec2f positionA = rectA->position;
		vec2f positionB = circleB->position;
		vec2f positionBtoACircle = positionB - positionA;
		float theta = agl::pi / 180;
		mat2f rotA(rectA->rotation * theta);
		vec2f distanceABS = abs(positionA - positionB);
		if ((positionBtoACircle.x >= -rA.x && positionBtoACircle.x <= rA.x) || (positionBtoACircle.y >= -rA.y && positionBtoACircle.y <= rA.y))
		{
			
			//��һ��С�ڱ�ʾ����ײ
			if (rB + rA.x < distanceABS.x || rB + rA.y < distanceABS.y)
				return false;
			float intersect = 0;
			vec2f n;
			if (rB + rA.x - distanceABS.x < rB + rA.y - distanceABS.y)
			{
				intersect = rB + rA.x - distanceABS.x;
				if (positionBtoACircle.x > 0)
					n = rotA * vec2f(1, 0);
				else
					n = rotA * vec2f(-1, 0);
			}
			else
			{
				intersect = rB + rA.y - distanceABS.y;
				if (positionBtoACircle.y > 0)
					n = rotA * vec2f(0, 1);
				else
					n = rotA * vec2f(0, -1);
			}
			if (!AisR)
			{
				n = -n;
				contacts.push_back(Contact(n * (rB - intersect) + positionB, n, intersect));
			}
			else
				contacts.push_back(Contact(-n * (rB - intersect) + positionB, n, intersect));
			return true;
		}
		else
		{
			
			float distance = length(distanceABS - rA);
			if (distance > rB)
				return false;
			float intersect = rB - distance;
			vec2f point = vec2f(sign(positionB.x) * rA.x, sign(positionB.y) * rA.y);
			vec2f n = normalize(positionB - point);
			if (!AisR) n = -n;
			contacts.push_back(Contact((rotA*point)+positionA, n, intersect));
			return true;
		}
		return false;
	}
};
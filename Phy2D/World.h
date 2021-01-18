#pragma once
#include<unordered_map>
#include<vector>
#include<mutex>
#include <condition_variable>
#include<thread>
#include"PhyObj.h"
#include"Contact.h"
using std::mutex;
using std::thread;
namespace phy2d
{
	struct HashFuc
	{
		std::size_t operator()(const std::pair<PhyObj*, PhyObj*>& key) const
		{
			return std::hash<size_t>()((int)key.first);
		}
	};
	struct BVHObj
	{
		PhyObj* object;
		float min_x, min_y;
		float max_x, max_y;
	};
	struct BVHNode
	{
		std::vector<BVHObj> objects;
		vec2f a, b;//���ο��������
	};
	//�Ƚ�����ָ�뷵��Key
	static std::pair<PhyObj*, PhyObj*> make_key(PhyObj* o1, PhyObj* o2)
	{
		if (o1 < o2)
			return std::make_pair(o1, o2);
		else
			return std::make_pair(o2, o1);
	}
	class World
	{
		//�洢����
		std::vector<BVHNode> collideBVHObjects;
		std::vector<BVHObj> bvhObjects;
		std::vector<PhyObj*> objects;
		//�洢��ײ��Ϣ
		std::unordered_map<std::pair<PhyObj*, PhyObj*>, Driver, HashFuc> collisions;
		//����topk
		int partitionx(int left, int right, int k);
		int partitiony(int left, int right, int k);
		void TopK(int left, int right, int k,bool XYflag);
		//BVH���ݹ鴴��
		void createBVH(int left,int right, std::vector<BVHObj> & bvhObjects);
		//�ж�AABB�ཻ
		bool BVHAABBIntersect(BVHNode& a, BVHNode& b);
		//������ײ�ͱ�����ײ��Ϣ
		void broadPhase(PhyObj* object1, PhyObj* object2);
	public:
		World() 
		{ 
			collisions.max_load_factor(0.7);
		}
		//��������
		void run(float time);
		//��������
		void push(PhyObj* object) { objects.push_back(object); }
		//����BVH
		void makeBVH();
	};
}


#include "World.h"
#include"Collide.h"
#include<algorithm>
#include<functional>
#include<thread>
using namespace phy2d;
using std::min;
using std::max;
int phy2d::World::partitionx(int left, int right, int k)
{
	auto m = bvhObjects[left];
	int i = left - 1, j = right + 1;
	while (i < j)
	{
		while (bvhObjects[++i].max_x < m.max_x);
		while (bvhObjects[--j].max_x > m.max_x);
		if (i < j) std::swap(bvhObjects[i], bvhObjects[j]);
	}
	return j;
}
int phy2d::World::partitiony(int left, int right, int k)
{
	auto m = bvhObjects[left];
	int i = left - 1, j = right + 1;
	while (i < j)
	{
		while (bvhObjects[++i].max_y < m.max_y);
		while (bvhObjects[--j].max_y > m.max_y);
		if (i < j) std::swap(bvhObjects[i], bvhObjects[j]);
	}
	return j;
}
void phy2d::World::TopK(int left, int right, int k, bool XYflag)
{
	if (left > right)
		return;
	if (left == right)
		return;
	//摆放元素
	int pos = 0;
	if (XYflag)
		pos = partitionx(left, right, k);
	else
		pos = partitiony(left, right, k);
	int kNum = pos - left + 1;
	if (kNum == k)
		return;
	else if (kNum > k)
		TopK(left, pos, k, XYflag);
	else
		TopK(pos + 1, right, k - kNum, XYflag);
}
void phy2d::World::createBVH(int left, int right, std::vector<BVHObj>& bvhObjects)
{
	static int deep = 0;
	BVHNode node;
	if (right - left + 1 <= 10)
	{
		//获取对应形状
		node.a.x = bvhObjects[left].min_x;
		node.a.y = bvhObjects[left].min_y;
		node.b.x = bvhObjects[left].max_x;
		node.b.y = bvhObjects[left].max_y;
		for (int i = left; i < right + 1; i++)
		{
			node.objects.push_back(bvhObjects[i]);
			//计算box
			node.a.x = min(node.a.x, bvhObjects[i].min_x);
			node.a.y = min(node.a.y, bvhObjects[i].min_y);
			node.b.x = max(node.b.x, bvhObjects[i].max_x);
			node.b.y = max(node.b.y, bvhObjects[i].max_y);
			/*if (node.a.x > bvhObjects[i].min_x)
				node.a.x = bvhObjects[i].min_x;
			if (node.a.y > bvhObjects[i].min_y)
				node.a.y = bvhObjects[i].min_y;
			if (node.b.x < bvhObjects[i].max_x)
				node.b.x = bvhObjects[i].max_x;
			if (node.b.y < bvhObjects[i].max_y)
				node.b.y = bvhObjects[i].max_y;*/
		}
		collideBVHObjects.push_back(node);
		return;
	}
	deep++;
	TopK(left, right, (right - left + 1) / 2, (node.b.x - node.a.x > node.b.y > node.a.y));
	int mid = (left + right) / 2;
	createBVH(left, mid - 1, bvhObjects);
	createBVH(mid, right, bvhObjects);
}
bool phy2d::World::BVHAABBIntersect(BVHNode& a, BVHNode& b)
{
	vec2f posa = vec2f((a.a.x + a.b.x) / 2, (a.a.y + a.b.y) / 2);
	vec2f posb = vec2f((b.a.x + b.b.x) / 2, (b.a.y + b.b.y) / 2);
	vec2f ar = vec2f((a.b.x - a.a.x) / 2, (a.b.y - a.a.y) / 2);
	vec2f br = vec2f((b.b.x - b.a.x) / 2, (b.b.y - b.a.y) / 2);
	if (abs(posa.x - posb.x) > ar.x + br.x || abs(posa.y - posb.y) > ar.y + br.y)
		return false;
	return true;
}
void phy2d::World::broadPhase(PhyObj* object1, PhyObj* object2)
{
	//生成一个key
	auto key = make_key(object1, object2);
	std::vector<Contact> contacts;
	if (Collide(object1, object2, contacts))
	{
		//std::cout << "collide" << std::endl;
		Driver driver(object1, object2, contacts);
		//查找当前两个物体是否还处于碰撞阶段
		if (collisions.find(key) == collisions.end())
		{
			//添加新的碰撞
			//std::cout << "add new" << std::endl;
			collisions[key] = driver;
		}
		else//已有了则更新碰撞信息
		{
			//std::cout << "overlap" << std::endl;
			collisions[key].overlap(driver);
		}
	}
	else
	{
		//std::cout << "erase" << std::endl;
		//如果有已经碰撞的此时首次分离，则删除之前的碰撞信息
		if (collisions.find(key) != collisions.end())
		{
			//std::cout << "erase" << std::endl;
			collisions.erase(key);
		}
	}
}

void phy2d::World::run(float time)
{
	makeBVH();
	//碰撞检测与生成
	//for (int i = 0; i < objects.size(); i++)
	//{
	//	for (int j = i + 1; j < objects.size(); j++)
	//	{
	//		broadPhase(objects[i], objects[j]);
	//	}
	//}

	for (int i = 0; i < collideBVHObjects.size(); i++)
	{
		//计算自身中的结果
		for (int m = 0; m < collideBVHObjects[i].objects.size(); m++)
			for (int n = m + 1; n < collideBVHObjects[i].objects.size(); n++)
				//碰撞计算
				broadPhase(collideBVHObjects[i].objects[m].object, collideBVHObjects[i].objects[n].object);

		for (int j = i + 1; j < collideBVHObjects.size(); j++)
			//判断两个AABB是否有相交
			//如果有
			if (BVHAABBIntersect(collideBVHObjects[i], collideBVHObjects[j]))
			{
				for (int m = 0; m < collideBVHObjects[i].objects.size(); m++)
					for (int n = 0; n < collideBVHObjects[j].objects.size(); n++)
						//碰撞计算
						broadPhase(collideBVHObjects[i].objects[m].object, collideBVHObjects[j].objects[n].object);
			}
	}
	//应用作用力
	for (auto object : objects)
	{
		if (object->invMass != 0)
		{
			//object->update(agl::vec2f(0.0f, -9.0f), time);
			object->addForce(agl::vec2f(0.0f, -10.0f));
			object->applyForce(time);
		}

	}
	//碰撞处理
	for (auto collision : collisions)
	{
		for (int i = 0; i < 10; i++)
			collision.second.ApplyImpulse(time);
	}
	for (auto object : objects)
		object->applyVelocity(time);
	bvhObjects.clear();
	collideBVHObjects.clear();
}

void phy2d::World::makeBVH()
{
	for (int i = 0; i < objects.size(); i++)
	{
		auto [min_x, min_y, max_x, max_y] = objects[i]->getMax();
		bvhObjects.push_back({ objects[i],min_x,min_y,max_x,max_y });
	}
	createBVH(0, bvhObjects.size() - 1, bvhObjects);
}
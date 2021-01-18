#pragma once
#include"PhyObj.h"
#include"Contact.h"
#include<vector>
namespace phy2d
{
	struct contact_info
	{
		contact_info(float _d, const agl::vec2f & v):d(_d),vec(v) {}
		float d;
		agl::vec2f vec;
	};
	bool Collide(PhyObj*, PhyObj*, std::vector<Contact>&contacts);
	bool CollideRectRect(PhyObj*, PhyObj*, std::vector<Contact>& contacts);
	bool CollideCircleCircle(PhyObj*, PhyObj*, std::vector<Contact>& contacts);
	bool CollideRectCircle(PhyObj*, PhyObj*, std::vector<Contact>& contacts,bool);
}

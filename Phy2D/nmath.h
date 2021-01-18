#pragma once
#include"scoin.h"
#include<cmath>
namespace agl
{
	static float sinl(float angle)
	{
		
		int tAngle = 0;
		if(angle >= 0)
			tAngle = (int)(angle * 10) % 3600;
		else
			tAngle = -((int)(std::abs(angle) * 10) % 3600)+3600;
		int iAngle = tAngle % 900;
		if (tAngle >= 0 && tAngle <= 900)
		{
			return sinList[iAngle];
		}
		else if (tAngle > 900 && tAngle <= 1800)
		{
			return sinList[900-iAngle];
		}
		else if (tAngle >1800 && tAngle <= 2700)
		{
			return -sinList[iAngle];
		}
		else
		{
			return -sinList[900-iAngle];
		}
	}
}

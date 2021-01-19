#pragma once
#include "const.h"
namespace toy {
	//�Ƕ�ת����
	float radians(float degrees)
	{
		return degrees * M_PIf / 180.0f;
	}
	//����ת�Ƕ�
	float degrees(float radians)
	{
		return radians * M_1_PIf * 180.0f;
	}
}
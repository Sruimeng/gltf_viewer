#pragma once

#include <iostream>
#include "vector.h"
namespace toy {
	class Euler
	{
	public:
		Euler();
		inline Euler(float3 Euler) { this->euler = Euler; };
	private:
		float3 euler;
		std::string order;
	};

	Euler::Euler()
	{
	}
}

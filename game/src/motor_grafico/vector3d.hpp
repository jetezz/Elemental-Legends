#pragma once
#include <irrlicht/irrlicht.h>


struct vector3d{
	vector3d(float x, float y, float z)
		:X(x), Y(y), Z(z)
	{}
	vector3d() = default;	
	irr::core::vector3df transformar();

float X=0;
float Y=0;
float Z=0;
};
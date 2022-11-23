#pragma once
#include "flecs.h"

#include <array>

struct Position
{
	Position() : x(), y(), z() {}
	Position(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
	Position(const std::array<float, 3>& arr) : x(arr[0]),
												y(arr[1]),
												z(arr[2]) {}
	float x, y, z;
};

struct Scale
{
	float s;
};

struct Velocity
{
	Velocity() : x(), y(), z() {}
	Velocity(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
	Velocity(const std::array<float, 3>& arr) : x(arr[0]),
												y(arr[1]),
												z(arr[2]) {}
	float x, y, z;
};

struct Gravity
{
	Gravity() : x(), y(), z() {}
	Gravity(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
	Gravity(const std::array<float, 3>& arr) : x(arr[0]),
											   y(arr[1]),
											   z(arr[2]) {}
	float x, y, z;
};

struct BouncePlane
{
	BouncePlane() : x(), y(), z(), w() {}
	BouncePlane(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}
	BouncePlane(const std::array<float, 4>& arr) : x(arr[0]),
												   y(arr[1]),
												   z(arr[2]),
												   w(arr[3]) {}
	float x, y, z, w;
};

struct DeathPlane
{
	float x, y, z, w;
};

struct Bounciness
{
	float val;
};

struct ShiverAmount
{
	float val;
};

struct FrictionAmount
{
	float val;
};

struct BoundingBox
{
	float x;
	float y;
	float z;
};

typedef float Speed;

void register_ecs_phys_systems(flecs::world& ecs);
#include "extra.h"
#include <iostream>
#include <string>
#include <sstream>
//#include <GLFW/glfw3.h>

namespace extra {

	void setVector3(float x, float y, float z, Vector3* ptr) {
		ptr->x = x;
		ptr->y = y;
		ptr->z = z;
	}

	struct Vector3 WorldToScreen(const struct Vector3 pos, struct viewMatrix matrix) {
		struct Vector3 out;
		float _x = matrix.matrix[0].x * pos.x + matrix.matrix[0].y * pos.y + matrix.matrix[0].z * pos.z + matrix.matrix[0].w;
		float _y = matrix.matrix[1].x * pos.x + matrix.matrix[1].y * pos.y + matrix.matrix[1].z * pos.z + matrix.matrix[1].w;
		out.z = matrix.matrix[2].x * pos.x + matrix.matrix[2].y * pos.y + matrix.matrix[2].z * pos.z + matrix.matrix[2].w;

		_x *= 1.f / out.z;
		_y *= 1.f / out.z;

		//int width = WBounds.right - WBounds.left;
		//int height = WBounds.bottom + WBounds.left;

		int width = 800;
		int height = 600;

		out.x = width * .5f;
		out.y = height * .5f;

		out.x += 0.5f * _x * width + 0.5f;
		out.y -= 0.5f * _y * height + 0.5f;

		return out;
	}

	Dog::Dog(std::string name, int8_t age) : name(name), age(age) {};

	void Dog::bark() const {
		std::cout << "woof" << std::endl;
	}

	std::string Dog::getName() const {
		return this->name;
	}

	int8_t Dog::getAge() const {
		return this->age;
	}

	void Dog::growOlder() {
		this->age++;
	}
}
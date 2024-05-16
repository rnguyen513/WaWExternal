#include "extra.h"
#include <iostream>
#include <string>
#include <sstream>

namespace extra {

	void setVector3(float x, float y, float z, Vector3* ptr) {
		ptr->x = x;
		ptr->y = y;
		ptr->z = z;
	}

	struct Vector3 WorldToScreen(const struct Vector3 pos, struct viewMatrix matrix) {
		struct Vector3 out;
		float _x = matrix.matrix[0] * pos.x + matrix.matrix[1] * pos.y + matrix.matrix[2] * pos.z + matrix.matrix[3];
		float _y = matrix.matrix[4] * pos.x + matrix.matrix[5] * pos.y + matrix.matrix[6] * pos.z + matrix.matrix[7];
		out.z = matrix.matrix[12] * pos.x + matrix.matrix[13] * pos.y + matrix.matrix[14] * pos.z + matrix.matrix[15];

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

	Vector2 WTS(const Vector3& pos, const viewMatrix_t& mtx) {
		float vectorHomogeneous[4] = { pos.x, pos.y, pos.z, 1.0f };

		float vectorClip[4] = { 0 };
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				vectorClip[i] += mtx.matrix[i][j] * vectorHomogeneous[j];
			}
		}

		float vectorNDC[3] = { 0 };
		for (int i = 0; i < 3; i++) {
			vectorNDC[i] = vectorClip[i] / vectorClip[3];
		}

		Vector2 screenVector;
		screenVector.x = (vectorNDC[0] + 1.0f) * 0.5f * 800;
		screenVector.y = (1.0f - vectorNDC[1]) * 0.5f * 600;

		return screenVector;
	}

	//bool WorldToScreen(struct originvec vect2, struct vec2D& vOut, float* flMatrix)
	//{
	//	vOut.x = flMatrix[0] * vect2.x + flMatrix[1] * vect2.y + flMatrix[2] * vect2.z + flMatrix[3];
	//	vOut.y = flMatrix[4] * vect2.x + flMatrix[5] * vect2.y + flMatrix[6] * vect2.z + flMatrix[7];
	//	std::cout << vOut.x << std::endl;

	//	float flTemp = flMatrix[12] * vect2.x + flMatrix[13] * vect2.y + flMatrix[14] * vect2.z + flMatrix[15];

	//	std::cout << flTemp << std::endl;

	//	if (flTemp < 0.01f)
	//		return false;

	//	float x = (float)res[0] / 2.f; // Your X resolution...
	//	float y = (float)res[1] / 2.f; // Your Y resolution...

	//	x += 0.5f * vOut.x * (float)res[0] + 0.5f;
	//	y -= 0.5f * vOut.y * (float)res[1] + 0.5f;

	//	vOut.x = x;
	//	vOut.y = y;

	//	return true;
	//}

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
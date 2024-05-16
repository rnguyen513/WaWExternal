#pragma once
#include <string>
#include <sstream>
#include <Windows.h>

namespace extra {
	struct Vector2 {
		float x, y;
	};

	struct Vector3 {
		float x, y, z;
		std::string toString() const {
			std::stringstream ss;
			ss << x << ", " << y << ", " << z;
			return ss.str();
		}
	};

	struct Vector4 {
		float x, y, z, w;
	};

	struct viewMatrix {
		float matrix[16];
	};

	struct viewMatrix_t {
		float matrix[4][4];
	};

	Vector2 WTS(const Vector3& pos, const viewMatrix_t& mtx);

	//struct Vector3 WorldToScreen(const struct Vector3 pos, struct viewMatrix matrix) {
	//	struct Vector3 out;
	//	float _x = matrix.matrix[0] * pos.x + matrix.matrix[1] * pos.y + matrix.matrix[2] * pos.z + matrix.matrix[3];
	//	float _y = matrix.matrix[4] * pos.x + matrix.matrix[5] * pos.y + matrix.matrix[6] * pos.z + matrix.matrix[7];
	//	out.z = matrix.matrix[12] * pos.x + matrix.matrix[13] * pos.y + matrix.matrix[14] * pos.z + matrix.matrix[15];

	//	_x *= 1.f / out.z;
	//	_y *= 1.f / out.z;

	//	int width = WBounds.right - WBounds.left;
	//	int height = WBounds.bottom + WBounds.left;

	//	out.x = width * .5f;
	//	out.y = height * .5f;

	//	out.x += 0.5f * _x * width + 0.5f;
	//	out.y -= 0.5f * _y * height + 0.5f;

	//	return out;
	//}

	struct Vector3 WorldToScreen(const struct Vector3 pos, struct viewMatrix matrix);

	void setVector3(float x, float y, float z, Vector3* ptr);

	class Dog {
	private:
		std::string name;
		int8_t age;

	public:
		Dog(std::string name, int8_t age);

		void bark() const;

		std::string getName() const;
		int8_t getAge() const;

		void growOlder();
	};

	struct ent {
		DWORD padding[6];
		Vector3 pos;
		DWORD padding2[105];
		int health;
	};
}
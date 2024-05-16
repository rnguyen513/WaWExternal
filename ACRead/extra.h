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

	bool WorldToScreen(Vector3 pos, Vector2& screen, float matrix[16], int windowWidth, int windowHeight);

	void setVector3(float x, float y, float z, Vector3* ptr);

	void DrawFilledRect(int x, int y, int w, int h, HDC hdc, HBRUSH brush);

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
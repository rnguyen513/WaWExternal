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

	bool WorldToScreen(Vector3 pos, Vector2& screen, float matrix[16], int windowWidth, int windowHeight)
	{
		Vector4 clipCoords;
		clipCoords.x = pos.x * matrix[0] + pos.y * matrix[1] + pos.z * matrix[2] + matrix[3];
		clipCoords.y = pos.x * matrix[4] + pos.y * matrix[5] + pos.z * matrix[6] + matrix[7];
		clipCoords.z = pos.x * matrix[8] + pos.y * matrix[9] + pos.z * matrix[10] + matrix[11];
		clipCoords.w = pos.x * matrix[12] + pos.y * matrix[13] + pos.z * matrix[14] + matrix[15];

		if (clipCoords.w < 0.1f) return false;

		Vector3 NDC;
		NDC.x = clipCoords.x / clipCoords.w; NDC.y = clipCoords.y / clipCoords.w; NDC.z = clipCoords.z / clipCoords.w;
		screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
		screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
		return true;
	}

	void DrawFilledRect(int x, int y, int w, int h, HDC hdc, HBRUSH brush) {
		RECT rect = { x, y, x + w, y + h };
		FillRect(hdc, &rect, brush);
		LineTo(hdc, x, y);
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
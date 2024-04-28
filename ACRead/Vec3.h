#pragma once

#include <string>
#include <iostream>

namespace extra {
	struct Vec3 {
		float x, y, z;
	};

	void setVec3(float x, float y, float z, Vec3* ptr) {
		ptr->x = x;
		ptr->y = y;
		ptr->z = z;
	}

	class Dog {
	private:
		string name;
		UINT8 age;
	public:

		Dog(string new_name, UINT8 new_age) : name(new_name), age(new_age) {};

		void bark() {
			std::cout << "woof";
		}

		string getName() return this.name;
		UINT8 getAge() return this.age;
	};
};
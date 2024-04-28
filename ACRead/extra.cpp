#include "extra.h"
#include <iostream>

namespace extra {
	void setVector3(float x, float y, float z, Vector3* ptr) {
		ptr->x = x;
		ptr->y = y;
		ptr->z = z;
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
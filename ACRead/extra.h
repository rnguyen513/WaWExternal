#pragma once
#include <string>

namespace extra {
	struct Vector3 {
		float x, y, z;
	};

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
}
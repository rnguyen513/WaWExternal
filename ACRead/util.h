#pragma once
#include <string>
#include <sstream>
#include <Windows.h>
#include "Memory.h"

namespace util {
	struct Vector2 {
		long x, y;
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

	bool WorldToScreen(Vector3 pos, Vector2* screen, float matrix[16], int windowWidth, int windowHeight);



	//drawing stuff
	void DrawFilledRect(int x, int y, int w, int h, HDC hdc, HBRUSH brush);
	void DrawBoundingBox(int x, int y, int w, int h, HDC hdc, HBRUSH brush);
	void DrawWithDoubleBuffering(HDC hdc, int width, int height, Memory::Mem memoryController, viewMatrix mtx, HPEN pen, HBRUSH brush);
	void DrawZombies(Memory::Mem memoryController, viewMatrix mtx, int w, int h, HPEN pen, HBRUSH brush, HDC hdc, bool drawlines, bool boxes);

	float Pythagorean2D(Vector2 a, Vector2 b);

	//zombie entity structure, so u only need to read the base address of zombie
	struct ent {
		DWORD padding[6];
		Vector3 pos;
		DWORD padding2[76];
		Vector3 head;
		DWORD padding3[26];
		int health;
		int maxHealth;
	};
}
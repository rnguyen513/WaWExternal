#include "util.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Memory.h"
#include "offests.h"

namespace util {

	bool WorldToScreen(Vector3 pos, Vector2* screen, float matrix[16], int windowWidth, int windowHeight)
	{
		Vector4 clipCoords;
		clipCoords.x = pos.x * matrix[0] + pos.y * matrix[1] + pos.z * matrix[2] + matrix[3];
		clipCoords.y = pos.x * matrix[4] + pos.y * matrix[5] + pos.z * matrix[6] + matrix[7];
		clipCoords.z = pos.x * matrix[8] + pos.y * matrix[9] + pos.z * matrix[10] + matrix[11];
		clipCoords.w = pos.x * matrix[12] + pos.y * matrix[13] + pos.z * matrix[14] + matrix[15];

		if (clipCoords.w < 0.1f) return false;

		Vector3 NDC;
		NDC.x = clipCoords.x / clipCoords.w; NDC.y = clipCoords.y / clipCoords.w; NDC.z = clipCoords.z / clipCoords.w;
		screen->x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
		screen->y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
		return true;
	}

	void DrawFilledRect(int x, int y, int w, int h, HDC hdc, HBRUSH brush) {
		RECT rect = { x, y, x + w, y + h };
		FillRect(hdc, &rect, brush);
	}

	void DrawBoundingBox(int x, int y, int w, int h, HDC hdc, HBRUSH brush) {
		DrawFilledRect(x, y, w, 2, hdc, brush); //bottom
		DrawFilledRect(x, y, 2, h, hdc, brush); // left
		DrawFilledRect(x, y+h, w, 2, hdc, brush); //top
		DrawFilledRect(x+w, y, 2, h, hdc, brush); //right
	}

	void DrawWithDoubleBuffering(HDC hdc, int width, int height, Memory::Mem memoryController, viewMatrix mtx, HPEN pen, HBRUSH brush, bool drawlines, bool boxes) {
		HDC bufferDC = CreateCompatibleDC(hdc);
		HBITMAP bufferBitmap = CreateCompatibleBitmap(hdc, width, height);
		SelectObject(bufferDC, bufferBitmap);

		HBRUSH _brush = CreateSolidBrush(RGB(0, 0, 0));
		RECT rect = { 0, 0, width, height };
		FillRect(bufferDC, &rect, _brush);
		DeleteObject(_brush);

		//draw zombies using new bufferDC
		DrawZombies(memoryController, mtx, width, height, pen, brush, hdc, drawlines, boxes);

		BitBlt(hdc, 0, 0, width, height, bufferDC, 0, 0, SRCCOPY);

		DeleteObject(bufferBitmap);
		DeleteDC(bufferDC);
	}

	void DrawZombies(Memory::Mem memoryController, viewMatrix mtx, int w, int h, HPEN pen, HBRUSH brush, HDC hdc, bool drawlines, bool boxes) {
		int zombieCount = 0;
		int zWidth = 0;
		int zHeight = 0;

		Vector2 closest = { 0,0 };
		POINT crosshair;
		GetCursorPos(&crosshair);
		for (int i = 0; i < 24; i++) {
			float distance = 0;
			ent zombie = memoryController.RPM<ent>(memoryController.RPM<uintptr_t>(memoryController.base_address + OFFSET_ENTITY_LIST + 0x88 * i));
			if (zombie.health > 0 && zombie.health < 50000 && zombie.health != 8304 && zombie.health != 1400) {
				zombieCount++;


				//WTS
				Vector2 zombieScreen;
				Vector2 headScreen;
				if (!WorldToScreen(zombie.pos, &zombieScreen, mtx.matrix, w, h) || !WorldToScreen(zombie.head, &headScreen, mtx.matrix, w, h)) continue;



				////get closest to crosshair FOR AIMBOT
				//distance = Pythagorean2D({crosshair.x, crosshair.y}, headScreen);
				//if (distance < Pythagorean2D({crosshair.x, crosshair.y}, closest)) {
				//	closest.x = headScreen.x;
				//	closest.y = headScreen.y;
				//	std::cout << "new closest: " << distance << std::endl;
				//}

				if (boxes) {
					//calculate zombie dimensions
					zHeight = headScreen.y - zombieScreen.y;
					zWidth = zHeight / 2.4;

					//DRAW BOX
					brush = CreateSolidBrush(RGB(255, 0, 0));
					SelectObject(hdc, brush);
					DrawBoundingBox(zombieScreen.x - zWidth / 2, zombieScreen.y, zWidth, zHeight, hdc, brush);
					DeleteObject(brush);

					//DRAW HEALTH
					brush = CreateSolidBrush(RGB(0, 155, 0));
					SelectObject(hdc, brush);
					DrawFilledRect(zombieScreen.x + zWidth * 0.5, zombieScreen.y, zWidth * 0.2, zHeight * zombie.health / zombie.maxHealth, hdc, brush);
					DeleteObject(brush);
				}

				//draw lines if toggled
				if (!drawlines) continue;
				pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
				SelectObject(hdc, pen);
				MoveToEx(hdc, w / 2, h - 40, nullptr);
				LineTo(hdc, (int)zombieScreen.x, (int)zombieScreen.y);
				DeleteObject(pen);


				////draw esp line
				//glLineWidth(2);
				//glBegin(GL_LINES);
				//glColor3f(1.0f, 1.0f, 1.0f);
				//glVertex2f(0, -1.0f);
				//glVertex2f(zombieScreen.x/width, zombieScreen.y/height);
				//glEnd();
			}
		}
		if (GetAsyncKeyState(VK_MENU)) {
			SetCursorPos(closest.x, closest.y);
		}
	}

	float Pythagorean2D(Vector2 a, Vector2 b) {
		return sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2));
	}
}
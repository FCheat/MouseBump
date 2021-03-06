﻿#include <Windows.h>

POINT PointDistance(POINT posA, POINT posB)
{
	return { posB.x - posA.x , posB.y - posA.y };
}

int main()
{
	RECT desktop;
	GetWindowRect(GetDesktopWindow(), &desktop);
	POINT ScreenSize = { desktop.right, desktop.bottom };
	POINT mousePointSave = { 0, 0 };

	for (;;)
	{
		POINT mousePointCurrent;
		if (!GetCursorPos(&mousePointCurrent))
			continue;

		if (mousePointCurrent.x != mousePointSave.x || mousePointCurrent.y != mousePointSave.y)
			if (mousePointCurrent.x > ScreenSize.x - 1 || mousePointCurrent.x < 1 || mousePointCurrent.y > ScreenSize.y - 2 || mousePointCurrent.y < 1)
			{
				POINT BounceForce = PointDistance(mousePointSave, mousePointCurrent);

				if (mousePointCurrent.x > ScreenSize.x - 1 || mousePointCurrent.x < 1)
					BounceForce.x *= rand() % 19 + 6;
				else
					BounceForce.y *= rand() % 12 + 2;

				POINT newMouse = { mousePointCurrent.x - BounceForce.x , mousePointCurrent.y - BounceForce.y };

				if (newMouse.x > ScreenSize.x)
					newMouse.x = ScreenSize.x - 3;
				else if (newMouse.x < 0)
					newMouse.x = 1;

				if (newMouse.y > ScreenSize.y)
					newMouse.y = ScreenSize.y - 3;
				else if (newMouse.y < 0)
					newMouse.y = 1;

				SetCursorPos(newMouse.x, newMouse.y);
				//mousePointCurrent = newMouse; //Optional, will give less bouncies but for more processing
			}

		mousePointSave = mousePointCurrent;
	}

    return 0;
}

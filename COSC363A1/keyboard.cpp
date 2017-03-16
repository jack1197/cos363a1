#include "common.h"
#include "keyboard.h"

namespace KbdController {
	const int max_keys = 20;
	unsigned char keys[max_keys];
	int specials[max_keys];
	unsigned char n_keys = 0;
	unsigned char n_specials = 0;
}

bool isSpecialDown(int key)
{
	for (int i = 0; i < KbdController::n_specials; i++)
	{
		if (key == KbdController::specials[i])
		{
			return 1;
		}
	}
	return 0;
}

bool isKeyDown(unsigned char key)
{
	for (int i = 0; i < KbdController::n_keys; i++)
	{
		if (key == KbdController::keys[i])
		{
			return 1;
		}
	}
	return 0;
}

void specialPressed(int key, int x, int y) {
	for (auto item : KbdController::specials)
	{
		if (item == key)
		{
			return;
		}
	}
	if (KbdController::n_specials >= KbdController::max_keys)
	{
		return;
	}
	KbdController::specials[KbdController::n_specials++] = key;
}

void specialReleased(int key, int x, int y)
{
	register int i = 0;
	for (; i < KbdController::n_specials; i++)
	{
		if (key == KbdController::specials[i])
		{
			break;
		}
	}
	if (i == KbdController::n_specials)
	{
		return;
	}
	memcpy(KbdController::specials + i, KbdController::specials + i + 1, sizeof(int)*(KbdController::n_specials - (i + 1)));
	KbdController::n_specials--;
}

void keyPressed(unsigned char key, int x, int y)
{
	for (auto item : KbdController::keys)
	{
		if (item == key)
		{
			return;
		}
	}
	if (KbdController::n_keys >= KbdController::max_keys)
	{
		return;
	}
	KbdController::keys[KbdController::n_keys++] = key;
}
void keyReleased(unsigned char key, int x, int y)
{
	register int i = 0;
	for (; i < KbdController::n_keys; i++)
	{
		if (key == KbdController::keys[i])
		{
			break;
		}
	}
	if (i == KbdController::n_keys)
	{
		return;
	}
	memcpy(KbdController::keys + i, KbdController::keys + i + 1, sizeof(unsigned char)*(KbdController::n_keys - (i + 1)));
	KbdController::n_keys--;
}
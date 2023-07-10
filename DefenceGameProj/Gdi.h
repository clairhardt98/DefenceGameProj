#pragma once
#include "framework.h"
#include <objidl.h>
#include <gdiplus.h>
#include <string>
#pragma comment(lib,"Gdiplus.lib")
using namespace Gdiplus;

class GDI
{
private:
	ULONG_PTR g_GdiToken;
public:
	void Gdi_Init();
	void Gdi_Draw(HDC hdc, int score);
	void Gdi_End();
};





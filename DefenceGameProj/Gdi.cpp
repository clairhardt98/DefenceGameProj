#include "Gdi.h"

void GDI::Gdi_Init()
{
	GdiplusStartupInput gpsi;
	GdiplusStartup(&g_GdiToken, &gpsi, NULL);
}

void GDI::Gdi_Draw(HDC hdc, int score)
{
	Graphics graphics(hdc);

	// : text
	SolidBrush brush(Color(255, 255, 255, 255));
	FontFamily fontFamily(L"Times New Roman");
	Font font(&fontFamily, 24, FontStyleRegular, UnitPixel);
	PointF pointf(10.0f, 5.0f);
	graphics.DrawString(L"Score: ", -1, &font, pointf, &brush);
	std::wstring text = std::to_wstring(score);
	PointF scorePoint(120.0f, 5.0f);
	graphics.DrawString(text.c_str(), -1, &font, scorePoint, NULL, &brush);
}

void GDI::Gdi_End()
{
	GdiplusShutdown(g_GdiToken);
}

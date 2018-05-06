#include "../GuiObjectPainter.h"

#include "../utils.h"

lycee::gui::GuiObjectPainter::GuiObjectPainter(HDC hdc)
	: hTargetDC(hdc)
{
	;
}

void lycee::gui::GuiObjectPainter::fillColor(COLORREF crNew, int width, int height) {
	HBRUSH hBrush = CreateSolidBrush(crNew);
	RECT rect = { 0, 0, width, height };
	int res = FillRect(hTargetDC, &rect, hBrush);
	DeleteObject(hBrush);
}

void lycee::gui::GuiObjectPainter::plotPoint(
	const POINT &center,
	int size,
	const COLORREF &crSurface,
	const COLORREF &crEdge
) {
	if (size <= 0) return;

	HBRUSH hOldBrush = (HBRUSH)SelectObject(hTargetDC, CreateSolidBrush(crSurface));
	HPEN hOldPen = (HPEN)SelectObject(hTargetDC, CreatePen(PS_SOLID, 1, crEdge));
	Ellipse(hTargetDC, center.x - size, center.y - size, center.x + size, center.y + size);
	DeleteObject(SelectObject(hTargetDC, hOldBrush));
	DeleteObject(SelectObject(hTargetDC, hOldPen));
}

void lycee::gui::GuiObjectPainter::drawBezier(
	const POINT *pts,
	int cpt,
	const COLORREF &crEdge
) {
	HPEN hOldPen = (HPEN)SelectObject(hTargetDC, CreatePen(PS_SOLID, 1, crEdge));
	PolyBezier(hTargetDC, pts, cpt);
	DeleteObject(SelectObject(hTargetDC, hOldPen));
}

void lycee::gui::GuiObjectPainter::drawLine(
	const POINT &start,
	const POINT &end,
	const COLORREF &crLine,
	const DWORD &dwStyle
) {
	HPEN hOldPen = (HPEN)SelectObject(hTargetDC, CreatePen(dwStyle, 1, crLine));
	MoveToEx(hTargetDC, start.x, start.y, NULL);
	LineTo(hTargetDC, end.x, end.y);

	DeleteObject(SelectObject(hTargetDC, hOldPen));
}


void lycee::gui::GuiObjectPainter::writeWeight(
	double w,
	const POINT &center,
	int textSize,
	const COLORREF &crText,
	const COLORREF &crBack
) {
	COLORREF crOldBkColor = SetBkColor(hTargetDC, crBack);
	HFONT hFont = CreateFont(
		textSize,
		0, 0, 0,
		FW_REGULAR,
		FALSE, FALSE, FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_MODERN,
		TEXT("Meiryo")
	);

	HFONT hOldFont = SelectFont(hTargetDC, hFont);


	lycee::lycee_string text = lycee::utils::Strings::fmt2str(TEXT("%.1f"), w);

	RECT calcRect = {0};
	DrawText(hTargetDC, text.c_str(), -1, &calcRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_CALCRECT);
	
	int width = calcRect.right - calcRect.left;
	int height = calcRect.bottom - calcRect.top;
	
	RECT textRect;
	textRect.left = center.x - width / 2;
	textRect.top = center.y - height / 2;
	textRect.right = textRect.left + width;
	textRect.bottom = textRect.top + height;

	DrawText(hTargetDC, text.c_str(), -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
	DeleteFont(SelectFont(hTargetDC, hOldFont));
	SetBkColor(hTargetDC, crOldBkColor);
}

POINT lycee::gui::GuiObjectPainter::getCentroidCoord(const POINT *ppt, int cpt) {
	long Gx = 0;
	long Gy = 0;
	for(int i=0 ; i<cpt ; i++) {
		Gx += ppt[i].x;
		Gy += ppt[i].y;
	}
	return make<POINT>(Gx / cpt, Gy / cpt);
}

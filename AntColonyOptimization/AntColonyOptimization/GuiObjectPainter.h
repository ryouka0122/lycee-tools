#ifndef __LYCEE__GUI_OBJECT_PAINTER__HEADER__
#define __LYCEE__GUI_OBJECT_PAINTER__HEADER__

#include "includes.h"

namespace lycee {

namespace gui {

	class GuiObjectPainter {
	public:
		explicit GuiObjectPainter(HDC hdc);

		void fillColor(COLORREF crNew, int width, int height);

		void plotPoint(const POINT &center, int size, const COLORREF &crSurface, const COLORREF &crEdge);
		void plotPoint(const POINT &center, int size, const COLORREF &crSurface) {
			plotPoint(center, size, crSurface, crSurface);
		}
		
		void drawBezier(const POINT *pts, int cpt, const COLORREF &crEdge);
		
		void drawLine(const POINT &start, const POINT &end, const COLORREF &crLine, const DWORD &dwStyle = PS_SOLID);

		void writeWeight(double w,
			const POINT &center,
			int textSize, const COLORREF &crText, const COLORREF &crBack);

		// ï°êîç¿ïWÇ©ÇÁèdêSÇãÅÇﬂÇÈîüêî
		POINT getCentroidCoord(const POINT *ppt, int cpt);

	private:
		HDC hTargetDC;
	};

}	// gui

}	// lycee
#endif	// __LYCEE__GUI_OBJECT_PAINTER__HEADER__

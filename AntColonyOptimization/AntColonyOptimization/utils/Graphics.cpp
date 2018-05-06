#include "../utils.h"

// ============================================================================
// 3次ベジエ曲線の長さの算出
// 参考文献：http://kone.vis.ne.jp/diary/diaryb06.html
//
long lycee::utils::Graphics::calcBezierArcLength(const POINT pts[4], int div) {
	// A = - p0 + 3p1 - 3p2 + p3
	// B =  3p0 - 6p1 + 3p2
	// C = -3p0 + 3p2

	long Ax = 0, Ay = 0, Bx = 0, By = 0, Cx = 0, Cy = 0;
	long ConstA[] = { -1,  3, -3, 1 };
	long ConstB[] = { 3, -6,  3, 0 };
	long ConstC[] = { -3,  3,  0, 0 };

	for (int i = 0; i < 4; i++) {
		Ax += ConstA[i] * pts[i].x;
		Ay += ConstA[i] * pts[i].y;
		Bx += ConstB[i] * pts[i].x;
		By += ConstB[i] * pts[i].y;
		Cx += ConstC[i] * pts[i].x;
		Cy += ConstC[i] * pts[i].y;
	}

	// (P'(t))^2 = 9A^2t^4 + 12ABt^3 + (6AC+4B^2)t^2 + 4BCt + C^2
	long
		Px[5] = {
		9 * Ax * Ax
		, 12 * Ax * Bx
		, 6 * Ax * Cx + 4 * Bx * Bx
		, 4 * Bx * Cx
		, Cx * Cx
	},
		Py[5] = {
		9 * Ay * Ay
		, 12 * Ay * By
		, 6 * Ay * Cy + 4 * By * By
		, 4 * By * Cy
		, Cy * Cy
	};

	double dx, dy, length = 0.0;
	for (int t = 0; t < div; t++) {
		dx = 0.0;
		dy = 0.0;
		for (int i = 0; i < 5; i++) {
			dx += pow((double)t / div, 4 - i) * Px[i];
			dy += pow((double)t / div, 4 - i) * Py[i];
		}
		length += sqrt(dx + dy) / div;
	}
	return (long)length;
}

// 点と点との距離を算出
double lycee::utils::Graphics::distPtAndPt(const POINT &a, const POINT &b) {
	POINT pt = { a.x - b.x, a.y - b.y };
	return abs(pt);
}

// ============================================================================
// 点と線分との距離を算出
// 参考：http://www.deqnotes.net/acmicpc/2d_geometry/lines
double lycee::utils::Graphics::distPtAndSegment(const POINT &p, const POINT &a, const POINT &b) {
	POINT ba = { b.x - a.x, b.y - a.y };
	POINT pa = { p.x - a.x, p.y - a.y };
	POINT ab = { a.x - b.x, a.y - b.y };
	POINT pb = { p.x - b.x, p.y - b.y };

	if (dot(ba, pa) == 0) return Graphics::abs(pa);
	if (dot(ab, pb) == 0) return Graphics::abs(pb);
	return ::abs(cross(ba, pa)) / Graphics::abs(ba);
}

long lycee::utils::Graphics::dot(const POINT &a, const POINT &b) {
	return (a.x* b.x + a.y*b.y);
}

long lycee::utils::Graphics::cross(const POINT &a, const POINT &b) {
	return (a.x* b.y - a.y*b.x);
}

double lycee::utils::Graphics::abs(const POINT &a) {
	return ::sqrt(a.x*a.x + a.y*a.y);
}


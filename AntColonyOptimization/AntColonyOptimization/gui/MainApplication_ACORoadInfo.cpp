#include "../MainApplication.h"

#include "../GuiObjectPainter.h"

// ---------------------------------------------------------------
//
// コンストラクタ
//
lycee::ACORoadInfo::ACORoadInfo(int s, int t, const POINT &ptS, const POINT &ptT) {
	nodeIndexS = s;
	nodeIndexT = t;

	// roadのベクトルと長さ
	long ax = ptT.x - ptS.x;
	long ay = ptT.y - ptS.y;
	double len = sqrt(ax*ax + ay * ay);

	// roadに対する法線ベクトル
	double nx = ay * DEFAULT_ANCHOR_POLE_LENGTH / len;
	double ny = -ax * DEFAULT_ANCHOR_POLE_LENGTH / len;

	// 各アンカーポイントの座標算出
	left[SINK].x = (long)(ptS.x + nx);
	left[SINK].y = (long)(ptS.y + ny);
	left[TERM].x = (long)(ptT.x + nx);
	left[TERM].y = (long)(ptT.y + ny);

	right[SINK].x = (long)(ptS.x - nx);
	right[SINK].y = (long)(ptS.y - ny);
	right[TERM].x = (long)(ptT.x - nx);
	right[TERM].y = (long)(ptT.y - ny);
}


bool lycee::ACORoadInfo::hitTestSegment(const std::deque<POINT> &nodeList, const POINT &pt, long size) {
	double dist = lycee::utils::Graphics::distPtAndSegment(pt,
		nodeList[this->nodeIndexS],
		nodeList[this->nodeIndexT]);
	return (dist <= size);
}

int lycee::ACORoadInfo::hitTestAnchor(const POINT &pt, int size) {
	for (int i = 0; i < 4; i++) {
		double dist = lycee::utils::Graphics::distPtAndPt(pt, this->get(i));
		if (dist <= size) {
			return i;
		}
	}
	return -1;
}

long lycee::ACORoadInfo::calcBezierLength(const std::deque<POINT> &nodeList, int dir) {
	POINT *trg = (dir==LEFT ? left : right);
	POINT pts[4] = {
		nodeList[this->nodeIndexS],
		trg[0],
		trg[1],
		nodeList[this->nodeIndexT],
	};
	return lycee::utils::Graphics::calcBezierArcLength(pts, lycee::consts::ACO_Consts::DEVIDE_SIZE);
}


void lycee::ACORoadInfo::paint(
	lycee::gui::GuiObjectPainter *painter,
	const std::deque<POINT> &nodeList,
	bool bPaintAnchor,
	bool bDrawWeight,
	double *weight
) {
	POINT bezier[4];
	POINT pts[2] = {
		nodeList[this->nodeIndexS],
		nodeList[this->nodeIndexT],
	};

	bezier[0] = pts[0];
	bezier[3] = pts[1];

	// セグメントの描画（灰色）
	painter->drawLine(pts[0], pts[1], lycee::consts::GRAY, PS_DASH);

	// アンカーの描画（オレンジ）
	if (bPaintAnchor) {
		for (int i = 0; i < 2; i++) {
			painter->drawLine(pts[i], this->left[i], lycee::consts::ORANGE);
			painter->plotPoint(this->left[i], lycee::consts::ANCHOR_POINT_SIZE, lycee::consts::ORANGE);

			painter->drawLine(pts[i], this->right[i], lycee::consts::ORANGE);
			painter->plotPoint(this->right[i], lycee::consts::ANCHOR_POINT_SIZE, lycee::consts::ORANGE);
		}
	}

	// ベジエの描画（青色）
	bezier[1] = this->left[0];
	bezier[2] = this->left[1];
	painter->drawBezier(bezier, 4, lycee::consts::BLUE);
	long bez1Len = lycee::utils::Graphics::calcBezierArcLength(bezier, lycee::consts::ACO_Consts::DEVIDE_SIZE);

	bezier[1] = this->right[0];
	bezier[2] = this->right[1];
	painter->drawBezier(bezier, 4, lycee::consts::BLUE);
	long bez2Len = lycee::utils::Graphics::calcBezierArcLength(bezier, lycee::consts::ACO_Consts::DEVIDE_SIZE);

	if (bDrawWeight) {
		painter->writeWeight(
			weight ? weight[0] : (100.0 * bez1Len / (bez1Len + bez2Len)),
			painter->getCentroidCoord(this->left, 2),
			lycee::consts::ACO_Consts::WEIGHT_FONT_SIZE,
			lycee::consts::Colors::BLACK,
			lycee::consts::Colors::WHITE
		);
		painter->writeWeight(
			weight ? weight[1] : (100.0 * bez2Len / (bez1Len + bez2Len)),
			painter->getCentroidCoord(this->right, 2),
			lycee::consts::ACO_Consts::WEIGHT_FONT_SIZE,
			lycee::consts::Colors::BLACK,
			lycee::consts::Colors::WHITE
		);
	}
}
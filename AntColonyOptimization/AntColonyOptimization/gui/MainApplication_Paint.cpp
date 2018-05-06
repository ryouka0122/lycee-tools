#include "../MainApplication.h"

void lycee::MainApplication::event_paint() {
	PAINTSTRUCT ps;
	if (HDC hdc = BeginPaint(hWnd, &ps)) {
		gui::GuiObjectPainter painter(hdc);
		painter.fillColor(lycee::consts::Colors::WHITE, CLIENT_WIDTH, CLIENT_HEIGHT);
		
		eventHandler->paint(&painter);
		/*
		for (unsigned int i = 0; i < roadInfoList.size(); i++) {
			auto info = &roadInfoList[i];
			paint_road(info, activeRoad == info, &painter);
		}
		paint_node(&painter);
		*/
		EndPaint(hWnd, &ps);
	}

	/* �_�u���o�b�t�@�����O�p
	gui::GuiObjectPainter painter(hBackScreenDC);
	painter.fillColor(lycee::consts::Colors::WHITE, CLIENT_WIDTH, CLIENT_HEIGHT);
	for (unsigned int i = 0; i < roadInfoList.size(); i++) {
		auto info = &roadInfoList[i];
		paint_road(info, activeRoad == info, &painter);
	}
	paint_node(&painter);

	if (HDC hdc = BeginPaint(hWnd, &ps)) {
		// �o�b�N����t�����g�Ƀf�[�^�]��
		BitBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, hBackScreenDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
	}*/
	return;
}


// ==========================================================================
// ACORoadInfo�̕`��
void lycee::MainApplication::paint_road(
	lycee::gui::GuiObjectPainter *painter,
	const lycee::ACORoadInfo *road,
	bool bPaintAnchor,
	bool bDrawWeight,
	double *weight
) {
	POINT bezier[4];
	POINT pts[2] = {
		nodeList[road->nodeIndexS],
		nodeList[road->nodeIndexT],
	};
	
	bezier[0] = pts[0];
	bezier[3] = pts[1];

	// �Z�O�����g�̕`��i�D�F�j
	painter->drawLine(pts[0], pts[1], lycee::consts::Colors::GRAY, PS_DASH);

	// �A���J�[�̕`��i�I�����W�j
	if (bPaintAnchor) {
		for (int i = 0; i < 2; i++) {
			painter->drawLine(pts[i], road->left[i], lycee::consts::Colors::ORANGE);
			painter->plotPoint(road->left[i], lycee::consts::ACO_Consts::ANCHOR_POINT_SIZE, lycee::consts::Colors::ORANGE);

			painter->drawLine(pts[i], road->right[i], lycee::consts::Colors::ORANGE);
			painter->plotPoint(road->right[i], lycee::consts::ACO_Consts::ANCHOR_POINT_SIZE, lycee::consts::Colors::ORANGE);
		}
	}

	// �x�W�G�̕`��i�F�j
	bezier[1] = road->left[0];
	bezier[2] = road->left[1];
	painter->drawBezier(bezier, 4, lycee::consts::Colors::BLUE);
	long bez1Len = lycee::utils::Graphics::calcBezierArcLength(bezier, lycee::consts::ACO_Consts::DEVIDE_SIZE);

	bezier[1] = road->right[0];
	bezier[2] = road->right[1];
	painter->drawBezier(bezier, 4, lycee::consts::Colors::BLUE);
	long bez2Len = lycee::utils::Graphics::calcBezierArcLength(bezier, lycee::consts::ACO_Consts::DEVIDE_SIZE);

	if (bDrawWeight) {
		painter->writeWeight(
			weight ? weight[0] : (100.0 * bez1Len / (bez1Len + bez2Len)),
			painter->getCentroidCoord(road->left, 2),
			lycee::consts::ACO_Consts::WEIGHT_FONT_SIZE,
			lycee::consts::Colors::BLACK,
			lycee::consts::Colors::WHITE
		);
		painter->writeWeight(
			weight ? weight[1] : (100.0 * bez2Len / (bez1Len + bez2Len)),
			painter->getCentroidCoord(road->right, 2),
			lycee::consts::ACO_Consts::WEIGHT_FONT_SIZE,
			lycee::consts::Colors::BLACK,
			lycee::consts::Colors::WHITE
		);
	}
}

// ==========================================================================
// �m�[�h�̕`��
void lycee::MainApplication::paint_node(
	lycee::gui::GuiObjectPainter *painter,
	bool bHitColor
) {
	int size = (int)nodeList.size();
	if (size == 0) return;

	COLORREF crActiveNode = lycee::consts::Colors::WHITE;
	if(bHitColor) switch (this->hitType) {
	case Grab:
		crActiveNode = lycee::consts::Colors::RED;
		break;
	case Hover:
		crActiveNode = lycee::consts::Colors::CYAN;
		break;
	}

	// �n�_�A�I�_�̕`��i�ԐF�j
	painter->plotPoint(
		nodeList[0],
		lycee::consts::ACO_Consts::SINK_POINT_SIZE,
		(bHitColor && 0==this->draggedPtIndex) ? crActiveNode : lycee::consts::WHITE,
		lycee::consts::BLACK);

	if (size == 1) {
		// 1�̎��́A�������Ȃ�
		return;
	}

	// ���p�_�̕`��i�Z�D�F�j
	int i = 1;
	while (i < size - 1) {
		painter->plotPoint(nodeList[i++],
			lycee::consts::ACO_Consts::ROAD_POINT_SIZE,
			(bHitColor && i == this->draggedPtIndex) ? crActiveNode : lycee::consts::DARK_GRAY);
	}

	// �n�_�A�I�_�̕`��i�F�j
	painter->plotPoint(nodeList[i],
		lycee::consts::ACO_Consts::TERM_POINT_SIZE,
		(bHitColor && i == this->draggedPtIndex) ? crActiveNode : lycee::consts::WHITE,
		lycee::consts::BLACK);

}


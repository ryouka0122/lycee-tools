#include "../MainApplication.h"

// �_�u���o�b�t�@�����O���p�t���O
//#define USE_DOUBLE_BUFFERING

void lycee::MainApplication::event_paint() {
	PAINTSTRUCT ps;

#if defined(USE_DOUBLE_BUFFERING)
	// �Ȃ����`��ł��Ȃ��iCompatible�ɂȂ��ĂȂ��H�j
	/* �_�u���o�b�t�@�����O�p */
	gui::GuiObjectPainter painter(hBackScreenDC);
	painter.fillColor(lycee::consts::Colors::WHITE, CLIENT_WIDTH, CLIENT_HEIGHT);
	eventHandler->paint(&painter);

	if (HDC hdc = BeginPaint(hWnd, &ps)) {
		// �o�b�N����t�����g�Ƀf�[�^�]��
		BitBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, hBackScreenDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
	}
#else
	if (HDC hdc = BeginPaint(hWnd, &ps)) {
		gui::GuiObjectPainter painter(hdc);
		painter.fillColor(lycee::consts::Colors::WHITE, CLIENT_WIDTH, CLIENT_HEIGHT);

		eventHandler->paint(&painter);
		EndPaint(hWnd, &ps);
	}
#endif

	return;
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
		painter->plotPoint(nodeList[++i],
			lycee::consts::ACO_Consts::ROAD_POINT_SIZE,
			(bHitColor && i == this->draggedPtIndex) ? crActiveNode : lycee::consts::DARK_GRAY);
	}

	// �n�_�A�I�_�̕`��i�F�j
	painter->plotPoint(nodeList[i],
		lycee::consts::ACO_Consts::TERM_POINT_SIZE,
		(bHitColor && i == this->draggedPtIndex) ? crActiveNode : lycee::consts::WHITE,
		lycee::consts::BLACK);

}


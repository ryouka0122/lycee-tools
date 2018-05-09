#include "../MainApplication.h"

#include "../aco.h"

// =========================================================================
// lycee::EventHandler
// =========================================================================
void lycee::EventHandler::reset() {

}

void lycee::EventHandler::down(const MouseInfo &info) {
	switch (info.key) {
	case MouseKey::MK_Right:
		clickedPt.x = info.clickX;
		clickedPt.y = info.clickY;
		app->showContextMenu(info.clickX, info.clickY);
		break;
	}
}

void lycee::EventHandler::up(const MouseInfo &info) {
	;
}

void lycee::EventHandler::move(const MouseInfo &info) {
	;
}

void lycee::EventHandler::leave() {

}

void lycee::EventHandler::paint(lycee::gui::GuiObjectPainter *painter) {
	// デフォルトは全表示
	for (unsigned int i = 0; i < app->roadInfoList.size(); ++i) {
		auto info = &app->roadInfoList[i];
		info->paint(painter, app->nodeList, /*bPaintAnchor=*/true, /*bDrawWeight=*/true);
		//app->paint_road(painter, info, /*bPaintAnchor=*/true, /*bDrawWeight=*/true);
	}
	app->paint_node(painter, /*bHitColor=*/false);
}

void lycee::EventHandler::keydown(UINT uKey) {
	;
}


// =========================================================================
// lycee::NodeEventHandler
// =========================================================================
void lycee::NodeEventHandler::reset() {
	app->hitType = lycee::HitType::NoHit;
}

void lycee::NodeEventHandler::down(const MouseInfo &info) {
	if(info.key != MouseKey::MK_Left) {
		lycee::EventHandler::down(info);
		return;
	}
	int index = hittestNode(info.clickX, info.clickY);
	if (index != -1) {
		app->draggedPtIndex = index;
		app->hitType = lycee::HitType::Grab;
		app->refresh();
	}
	return;
}

void lycee::NodeEventHandler::up(const MouseInfo &info) {
	app->hitType = lycee::HitType::NoHit;
	app->draggedPtIndex = -1;
	return;
}

void lycee::NodeEventHandler::move(const MouseInfo &info) {
	if (app->hitType == lycee::HitType::Grab) {
		app->nodeList[app->draggedPtIndex].x = info.clickX;
		app->nodeList[app->draggedPtIndex].y = info.clickY;
	}
	else {
		int index = hittestNode(info.clickX, info.clickY);
if (index != -1) {
	app->draggedPtIndex = index;
	app->hitType = lycee::HitType::Hover;
}
else {
	app->draggedPtIndex = -1;
	app->hitType = lycee::HitType::NoHit;
}
	}
	app->refresh();
	return;
}

void lycee::NodeEventHandler::leave() {
	app->draggedPtIndex = -1;
	app->hitType = lycee::HitType::NoHit;
}

void lycee::NodeEventHandler::paint(lycee::gui::GuiObjectPainter *painter) {
	// ノード操作中はアンカーは非表示
	for (unsigned int i = 0; i < app->roadInfoList.size(); ++i) {
		auto info = &app->roadInfoList[i];
		info->paint(painter, app->nodeList, /*bPaintAnchor=*/false, /*bDrawWeight=*/true);
		//app->paint_road(painter, info, /*bPaintAnchor=*/false, /*bDrawWeight=*/true);
	}
	// ノードのヒットテスト情報は反映させる
	app->paint_node(painter, /*bHitColor=*/true);
}


int lycee::NodeEventHandler::hittestNode(long x, long y) {
	POINT pt = { x, y };
	for (unsigned int i = 0; i < app->nodeList.size(); ++i) {
		if (lycee::utils::Graphics::distPtAndPt(pt, app->nodeList[i])
			< lycee::consts::ACO_Consts::HITTEST_SIZE) {
			return i;
		}
	}
	return -1;
}

// =========================================================================
// lycee::AnchorEventHandler
// =========================================================================
void lycee::AnchorEventHandler::reset() {
	app->activeRoad = NULL;
	app->hitType = lycee::HitType::NoHit;
}

void lycee::AnchorEventHandler::down(const MouseInfo &info) {
	if (info.key != MouseKey::MK_Left) {
		lycee::EventHandler::down(info);
		return;
	}
	POINT pt = {info.clickX, info.clickY};
	// ヒットテスト
	int index = hittestSegment(pt);
	if (-1 != index) {
		// ヒットしたセグメントをアクティベート
		app->activeRoad = &app->roadInfoList[index];
		app->hitType = lycee::HitType::NoHit;
	}else if (app->activeRoad) {
		// 選択中のセグメントがある時、アンカーのヒットテスト
		int index = app->activeRoad->hitTestAnchor(pt, lycee::consts::ACO_Consts::HITTEST_SIZE);
		if (-1 != index) {
			// アンカーポイントをつかむ状態にする
			app->draggedPtIndex = index;
			app->hitType = lycee::HitType::Grab;
			lycee::utils::Log::debug("[mouse down] index=%d\n", index);
		}
	}
	app->refresh();
	return;
}

void lycee::AnchorEventHandler::up(const MouseInfo &info) {
	app->hitType = lycee::HitType::NoHit;
	app->refresh();
	return;
}

void lycee::AnchorEventHandler::move(const MouseInfo &info) {
	POINT pt = { info.clickX , info.clickY };
	if (app->activeRoad) {
		// アクティベートされたセグメントがある場合
		if (app->hitType == lycee::HitType::Grab) {
			// さらにアンカーポイントをつかんでいる場合
			// アンカーポイントをカーソルの位置に移動
			app->activeRoad->get(app->draggedPtIndex) = pt;
		}
	}
	else {
		// ヒットテスト
		int index = hittestSegment(pt);
		if (-1 != index) {
			// ヒットしたセグメントをアクティベート
			app->activeRoad = &app->roadInfoList[index];
			app->hitType = lycee::HitType::Hover;
		}
		else {
			// ヒットなし
			app->activeRoad = NULL;
			app->hitType = lycee::HitType::NoHit;
		}
	}
	app->refresh();
}

void lycee::AnchorEventHandler::leave() {
	app->activeRoad = NULL;
	app->hitType = lycee::HitType::NoHit;
	app->refresh();
}

void lycee::AnchorEventHandler::paint(lycee::gui::GuiObjectPainter *painter) {
	// アンカー操作中はアクティベートされたセグメントのみアンカー表示
	for (unsigned int i = 0; i < app->roadInfoList.size(); ++i) {
		auto info = &app->roadInfoList[i];
		info->paint(painter, app->nodeList, /*bPaintAnchor=*/app->activeRoad == info, /*bDrawWeight=*/true);
		//app->paint_road(painter, info, /*bPaintAnchor=*/app->activeRoad==info, /*bDrawWeight=*/true);
	}
	// ノードのヒットテスト情報は反映させない
	app->paint_node(painter, /*bHitColor=*/false);
}


int lycee::AnchorEventHandler::hittestSegment(const POINT &pt) {
	for (unsigned int i = 0; i < app->roadInfoList.size(); ++i) {
		int n = app->roadInfoList[i].hitTestSegment(app->nodeList, pt, lycee::consts::ACO_Consts::HITTEST_SIZE);
		if(n!=-1) return i;
	}
	return -1;
}



// =========================================================================
// lycee::ACOMouseListener
// =========================================================================
void lycee::ACOEventHandler::reset() {
	// 各種変数の初期化
	if (pheromone[0]) delete[] pheromone[0];
	if (pheromone[1]) delete[] pheromone[1];

	size = app->roadInfoList.size();
	int *left = new int[size];
	int *right = new int[size];
	pheromone[0] = new double[size];
	pheromone[1] = new double[size];

	for (int i = 0; i < size; ++i) {
		// 左側の経路の長さ
		long leftLength = app->roadInfoList[i].calcBezierLength(app->nodeList, ACORoadInfo::LEFT);
		
		// 右側の経路の長さ
		long rightLength = app->roadInfoList[i].calcBezierLength(app->nodeList, ACORoadInfo::RIGHT);

		// 重みの設定
		if (leftLength == rightLength) {
			left[i] = 3;
			right[i] = 3;
		}
		else if (leftLength > rightLength) {
			left[i] = 5;
			right[i] = 1;
		}
		else {
			/* leftLength < rightLength */
			left[i] = 1;
			right[i] = 5;
		}
		//left[i] = 100 * leftLength / (leftLength + rightLength);
		//right[i] = 100 - left[i];
	}

	// ACOの生成
	lycee::aco::AntColonyOptimization aco(/*Q=*/3, /*rho=*/0.4, /*epsilon=*/0.15);
	
	// 経路上の重みの設定
	aco.setCost(left, right, size);

	// ACOの実行
	aco.optimize(/*ant=*/500);

	// 結果の取得
	aco.getPheromone(pheromone, size);

	// 後片付け
	delete[] left;
	delete[] right;
}

void lycee::ACOEventHandler::paint(gui::GuiObjectPainter *painter) {
	// ACO実行中は全表示
	double weight[2];
	for (unsigned int i = 0; i < app->roadInfoList.size(); ++i) {
		auto info = &app->roadInfoList[i];
		weight[0] = pheromone[0][i];
		weight[1] = pheromone[1][i];
		info->paint(painter, app->nodeList, /*bPaintAnchor=*/true, /*bDrawWeight=*/true, weight);
		//app->paint_road(painter, info, /*bPaintAnchor=*/true, /*bDrawWeight=*/true, weight);
	}
	app->paint_node(painter, /*bHitColor=*/false);
}

void lycee::ACOEventHandler::keydown(UINT uKey) {
	switch (uKey) {
	case VK_SPACE:
		this->reset();
		app->refresh();
		break;
	}
}

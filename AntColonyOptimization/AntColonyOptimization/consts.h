#ifndef __LYCEE__CONSTS__HEADER__
#define __LYCEE__CONSTS__HEADER__

#include "includes.h"

namespace lycee {

namespace consts {

	// ===========================================
	// デフォルトRGB値
	// 
	enum Colors {
		BLACK		= RGB(0X00, 0X00, 0X00),
		WHITE		= RGB(0XFF, 0XFF, 0XFF),

		RED			= RGB(0XFF, 0X00, 0X00),
		GREEN		= RGB(0X00, 0XFF, 0X00),
		BLUE		= RGB(0X00, 0X00, 0XFF),

		CYAN		= RGB(0X00, 0XFF, 0XFF),
		ORANGE		= RGB(0XFF, 0X7F, 0X00),

		LIGHT_GRAY	= RGB(0X92, 0X92, 0X92),
		DARK_GRAY	= RGB(0X64, 0X64, 0X64),
		GRAY		= RGB(0X7F, 0X7F, 0X7F),
	};


	// ===========================================
	// ACORoadInfo描画用定数
	// 
	enum ACO_Consts {
	/* 重み用フォントサイズ */		WEIGHT_FONT_SIZE = 20,
	/* 道のりのノードサイズ */		ROAD_POINT_SIZE = 5,
	/* 始点りのノードサイズ */		SINK_POINT_SIZE = 8,
	/* 終点のノードサイズ */		TERM_POINT_SIZE = 8,
	/* アンカーポイントサイズ */	ANCHOR_POINT_SIZE = 3,

	/* ノードの当たり判定サイズ */	HITTEST_SIZE = 3,
	/* Bezier曲線の長さ算出精度 */	DEVIDE_SIZE = 100,

	};

}	// consts

}	// lycee
#endif	// __LYCEE__CONSTS__HEADER__

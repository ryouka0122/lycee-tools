#ifndef __LYCEE__UTILS__HEADER__
#define __LYCEE__UTILS__HEADER__

#include "includes.h"

namespace lycee {

	template<typename T>
	inline T make(long x, long y);

	template<>
	inline POINT make<POINT>(long x, long y) {
		POINT pt = { x, y };
		return pt;
	}

	template<>
	inline SIZE make<SIZE>(long cx, long cy) {
		SIZE sz = { cx, cy };
		return sz;
	}

	inline POINT makePOINT(long x, long y) {
		POINT pt = { x, y };
		return pt;
	}

	inline SIZE makeSIZE(long cx, long cy) {
		SIZE sz = { cx, cy };
		return sz;
	}

	inline RECT makeRECT(POINT pt1, POINT pt2) {
		RECT rect = { 0 };
		if (pt1.x < pt2.x) {
			rect.left = pt1.x;
			rect.right = pt2.x;
		}
		else {
			rect.left = pt2.x;
			rect.right = pt1.x;
		}
		if (pt1.y < pt2.y) {
			rect.top = pt1.y;
			rect.bottom = pt2.y;
		}
		else {
			rect.top = pt2.y;
			rect.bottom = pt1.y;
		}
		return rect;
	}

namespace utils {

	struct Log {
		static void debug(const char *fmt, ...);
	};


	struct Resources {
		static lycee_string loadString(int nResourceId, int szString);

	};

	struct Strings {
		// フォーマット出力時の文字数を計算（マルチバイト版）
		static int calcTextLength(const char *fmt, ...);

		// フォーマット出力時の文字数を計算（ワイド文字版）
		static int calcTextLength(const wchar_t *fmt, ...);

		// フォーマット指定で文字列に変換する函数
		static lycee_string fmt2str(const lycee::lycee_char *fmt, ...);
	};

	struct Graphics {
		// 3次ベジエ曲線の長さの算出
		static long calcBezierArcLength(const POINT pts[4], int div);

		// 点と点との距離を算出
		static double distPtAndPt(const POINT &a, const POINT &b);

		// 点と線分との距離を算出
		static double distPtAndSegment(const POINT &p, const POINT &a, const POINT &b);

		// ベクトルの内積
		static long dot(const POINT &a, const POINT &b);

		// ベクトルの外積(クロス積)
		static long cross(const POINT &a, const POINT &b);

		// ベクトルの絶対値
		static double abs(const POINT &a);

	};

}	// utils

}	// lycee
#endif	// __LYCEE__UTILS__HEADER__

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
		// �t�H�[�}�b�g�o�͎��̕��������v�Z�i�}���`�o�C�g�Łj
		static int calcTextLength(const char *fmt, ...);

		// �t�H�[�}�b�g�o�͎��̕��������v�Z�i���C�h�����Łj
		static int calcTextLength(const wchar_t *fmt, ...);

		// �t�H�[�}�b�g�w��ŕ�����ɕϊ����锟��
		static lycee_string fmt2str(const lycee::lycee_char *fmt, ...);
	};

	struct Graphics {
		// 3���x�W�G�Ȑ��̒����̎Z�o
		static long calcBezierArcLength(const POINT pts[4], int div);

		// �_�Ɠ_�Ƃ̋������Z�o
		static double distPtAndPt(const POINT &a, const POINT &b);

		// �_�Ɛ����Ƃ̋������Z�o
		static double distPtAndSegment(const POINT &p, const POINT &a, const POINT &b);

		// �x�N�g���̓���
		static long dot(const POINT &a, const POINT &b);

		// �x�N�g���̊O��(�N���X��)
		static long cross(const POINT &a, const POINT &b);

		// �x�N�g���̐�Βl
		static double abs(const POINT &a);

	};

}	// utils

}	// lycee
#endif	// __LYCEE__UTILS__HEADER__

#ifndef __LYCEE__CONSTS__HEADER__
#define __LYCEE__CONSTS__HEADER__

#include "includes.h"

namespace lycee {

namespace consts {

	// ===========================================
	// �f�t�H���gRGB�l
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
	// ACORoadInfo�`��p�萔
	// 
	enum ACO_Consts {
	/* �d�ݗp�t�H���g�T�C�Y */		WEIGHT_FONT_SIZE = 20,
	/* ���̂�̃m�[�h�T�C�Y */		ROAD_POINT_SIZE = 5,
	/* �n�_��̃m�[�h�T�C�Y */		SINK_POINT_SIZE = 8,
	/* �I�_�̃m�[�h�T�C�Y */		TERM_POINT_SIZE = 8,
	/* �A���J�[�|�C���g�T�C�Y */	ANCHOR_POINT_SIZE = 3,

	/* �m�[�h�̓����蔻��T�C�Y */	HITTEST_SIZE = 3,
	/* Bezier�Ȑ��̒����Z�o���x */	DEVIDE_SIZE = 100,

	};

}	// consts

}	// lycee
#endif	// __LYCEE__CONSTS__HEADER__

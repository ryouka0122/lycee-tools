#ifndef __LYCEE__DEFINES__HEADER__
#define __LYCEE__DEFINES__HEADER__

#if defined(UNICODE) || defined(_UNICODE)
// �����R�[�h�FUNICODE�̂Ƃ�

#else
// �����R�[�h�F�}���`�o�C�g�����̎�

#endif

namespace lycee {
	typedef TCHAR lycee_char;
	typedef std::basic_string<TCHAR> lycee_string;
}	// lycee
#endif	// __LYCEE__DEFINES__HEADER__

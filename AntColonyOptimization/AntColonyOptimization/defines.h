#ifndef __LYCEE__DEFINES__HEADER__
#define __LYCEE__DEFINES__HEADER__

#if defined(UNICODE) || defined(_UNICODE)
// 文字コード：UNICODEのとき

#else
// 文字コード：マルチバイト文字の時

#endif

namespace lycee {
	typedef TCHAR lycee_char;
	typedef std::basic_string<TCHAR> lycee_string;
}	// lycee
#endif	// __LYCEE__DEFINES__HEADER__

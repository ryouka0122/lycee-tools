#include "../utils.h"

// éQçlÅFhttp://jumble-note.blogspot.jp/2012/09/c-vacopy.html
int lycee::utils::Strings::calcTextLength(const char *fmt, ...) {
	va_list args;
	int len;

	va_start(args, fmt);
	len = _vsnprintf(NULL, 0, fmt, args);
	va_end(args);
	return len;
}

int lycee::utils::Strings::calcTextLength(const wchar_t *fmt, ...) {
	va_list args;
	int len;
	va_start(args, fmt);
	len = _vsnwprintf(NULL, 0, fmt, args);
	va_end(args);
	return len;
}

lycee::lycee_string lycee::utils::Strings::fmt2str(const lycee::lycee_char *fmt, ...) {
	va_list args;
	int len;
	va_start(args, fmt);
#ifdef _UNICODE
	len = _vsnwprintf(NULL, 0, _TRUNCATE, fmt, args);
#else
	len = _vsnprintf(NULL, 0, fmt, args);
#endif
	va_end(args);

	lycee::lycee_char *buf = (lycee::lycee_char*)memset(new lycee::lycee_char[len+1], 0, (len+1)*sizeof(lycee::lycee_char));
	va_start(args, fmt);
#ifdef _UNICODE
	_vsnwprintf(buf, len, fmt, args);
#else
	_vsnprintf(buf, len, fmt, args);
#endif
	va_end(args);
	lycee::lycee_string result(buf);
	delete[] buf;
	return result;
}


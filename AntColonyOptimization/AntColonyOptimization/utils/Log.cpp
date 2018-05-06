#include "../utils.h"


void lycee::utils::Log::debug(const char *fmt, ...) {
#if defined(_DEBUG)
	// デバッグ時のみ有効
	va_list args;
	char *buf;
	int len;

	// バッファ長の計算
	va_start(args, fmt);
	len = _vsnprintf(NULL, 0, fmt, args);
	va_end(args);

	if (len > 0) {
		len += 1;	// EOS分
		buf = (char*)malloc(sizeof(char)*len);
		memset(buf, 0, sizeof(char)*len);
		
		// フォーマット処理
		va_start(args, fmt);
		vsnprintf(buf, len, fmt, args);
		va_end(args);

		// ログ出力
		OutputDebugStringA(buf);
		free(buf);
	}
#endif
	return;
}

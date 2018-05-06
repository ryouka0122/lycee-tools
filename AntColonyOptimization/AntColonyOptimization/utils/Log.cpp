#include "../utils.h"


void lycee::utils::Log::debug(const char *fmt, ...) {
#if defined(_DEBUG)
	// �f�o�b�O���̂ݗL��
	va_list args;
	char *buf;
	int len;

	// �o�b�t�@���̌v�Z
	va_start(args, fmt);
	len = _vsnprintf(NULL, 0, fmt, args);
	va_end(args);

	if (len > 0) {
		len += 1;	// EOS��
		buf = (char*)malloc(sizeof(char)*len);
		memset(buf, 0, sizeof(char)*len);
		
		// �t�H�[�}�b�g����
		va_start(args, fmt);
		vsnprintf(buf, len, fmt, args);
		va_end(args);

		// ���O�o��
		OutputDebugStringA(buf);
		free(buf);
	}
#endif
	return;
}

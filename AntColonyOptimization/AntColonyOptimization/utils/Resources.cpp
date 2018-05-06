#include "../utils.h"

lycee::lycee_string lycee::utils::Resources::loadString(int nResourceId, int szString) {
	lycee::lycee_char *buf = new lycee::lycee_char[szString];
	lycee::lycee_string strResource;
	if (0 < LoadString(GetModuleHandle(NULL), nResourceId, buf, szString)) {
		strResource.assign(buf);
	}
	delete buf;
	return strResource;
}
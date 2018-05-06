#include "../WindowProcedure.h"


lycee::CallableGuiObject::~CallableGuiObject()
{
	;
}


std::map<HWND, lycee::CallableGuiObject*> initializeMap() {
	return std::map<HWND, lycee::CallableGuiObject*>();
}

std::map<HWND, lycee::CallableGuiObject*> lycee::WindowProcedure::objectList = initializeMap();


void lycee::WindowProcedure::entry(lycee::CallableGuiObject *obj) {
	if (obj == NULL) return;
	HWND hWnd = obj->GetHWND();
	lycee::WindowProcedure::map_type::iterator iter = objectList.find(hWnd);
	if (iter == objectList.end()) {
		objectList.insert(std::make_pair(hWnd, obj));
	}
}

void lycee::WindowProcedure::release(lycee::CallableGuiObject *obj) {
	HWND hWnd = obj->GetHWND();
	lycee::WindowProcedure::map_type::iterator iter = objectList.find(hWnd);
	if (iter != objectList.end()) {
		objectList.erase(iter);
	}
}

LRESULT CALLBACK lycee::WindowProcedure::WndProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp) {
	lycee::WindowProcedure::map_type::iterator
		iter = objectList.find(hWnd);
	if (iter != objectList.end()) {
		return iter->second->Callback(uMsg, wp, lp);
	}
	return DefWindowProc(hWnd, uMsg, wp, lp);
}
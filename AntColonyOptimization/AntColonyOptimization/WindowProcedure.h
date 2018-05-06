#ifndef __LYCEE__WINDOW_PROCEDURE__HEADER__
#define __LYCEE__WINDOW_PROCEDURE__HEADER__

#include "includes.h"

namespace lycee {

	// ===============================================================
	// 
	// CallableGuiObject
	//
	class CallableGuiObject {
	public:
		virtual ~CallableGuiObject() = 0;

		// �����p���X�g�Ɏg�p����C���f�b�N�X
		virtual HWND GetHWND() = 0;

		// �R�[���o�b�N
		virtual LRESULT Callback(UINT uMsg, WPARAM wp, LPARAM lp) = 0;

	};

	// ===============================================================
	// 
	// WindowProcedure
	//
	class WindowProcedure {
	private:
		virtual ~WindowProcedure() = 0;
		WindowProcedure();
		WindowProcedure(const WindowProcedure &);
		WindowProcedure& operator =(const WindowProcedure &);

	public:
		typedef std::map<HWND, lycee::CallableGuiObject*> map_type;

		static void entry(CallableGuiObject *obj);

		static void release(CallableGuiObject *obj);

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);

	private:
		static std::map<HWND, CallableGuiObject*> objectList;
	};



}	// lycee
#endif	// __LYCEE__WINDOW_PROCEDURE__HEADER__

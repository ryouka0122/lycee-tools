#ifndef __LYCEE__MAIN_APPLICATION__HEADER__
#define __LYCEE__MAIN_APPLICATION__HEADER__

#include "includes.h"

#include "WindowProcedure.h"
#include "GuiObjectPainter.h"

#include "resource.h"
#include "consts.h"
#include "utils.h"


namespace lycee {
	// ============================
	// メインアプリケーション宣言
	// ============================
	class MainApplication;

	// ============================
	// AntColonyOptimization用構造体
	//
	struct ACORoadInfo {
		enum { SINK = 0, TERM = 1 };
		enum { LEFT = 0, RIGHT = 2 };
		enum { DEFAULT_ANCHOR_POLE_LENGTH = 50 };

		int nodeIndexS;
		int nodeIndexT;
		POINT left[2];
		POINT right[2];

		explicit ACORoadInfo(int s, int t, const POINT &ptS, const POINT &ptT);

		POINT& get(int i) {
			return (*this)[i];
		}

		const POINT& get(int i) const {
			return (*this)[i];
		}

		POINT& operator [](int n) {
			return (n < RIGHT) ? left[n] : right[n - RIGHT];
		}

		const POINT& operator [](int n) const {
			return (n < RIGHT) ? left[n] : right[n - RIGHT];
		}

		enum {NO_HIT=-1};
		bool hitTestSegment(const std::deque<POINT> &nodeList, const POINT &pt, long size);
		int hitTestAnchor(const POINT &pt, int size);

		long calcBezierLength(const std::deque<POINT> &nodeList, int dir);


		void paint(
			lycee::gui::GuiObjectPainter *painter,
			const std::deque<POINT> &nodeList,
			bool bPaintAnchor,
			bool bDrawWeight,
			double *weight
		);

		void paint(
			lycee::gui::GuiObjectPainter *painter,
			const std::deque<POINT> &nodeList,
			bool bPaintAnchor,
			bool bDrawWeight
		) {
			paint(painter, nodeList, bPaintAnchor, bDrawWeight, 0);
		}

	};


	enum { NO_DRAGGING = -1 };
	enum HitType {
		NoHit,	// どこにも当たってない
		Hover,	// カーソルが当たってる時
		Grab,	// つかんでいるとき
	};

	// ============================
	// マウスイベント用構造体
	//
	enum MouseKey {
		MK_None,	// 未定義
		MK_Left,	// 左ボタン
		MK_Right,	// 右ボタン
	};

	struct MouseInfo {
		MouseKey key;
		long clickX;
		long clickY;

		explicit MouseInfo(MouseKey _key, LPARAM lp)
			: key(_key)
			, clickX(GET_X_LPARAM(lp))
			, clickY(GET_Y_LPARAM(lp))
		{
			;
		}
	};

	// ============================
	// イベントハンドラ
	//
	class EventHandler {
	public:
		POINT clickedPt;
		MainApplication *app;
		explicit EventHandler(MainApplication *_app) : app(_app) { }

		virtual void reset();
		
		virtual void down(const MouseInfo &info);
		virtual void up(const MouseInfo &info);
		virtual void move(const MouseInfo &info);
		virtual void leave();

		virtual void paint(gui::GuiObjectPainter *painter);

		virtual void keydown(UINT wKey);
	};

	// ノード操作用ハンドラ
	class NodeEventHandler
		: public virtual EventHandler {
	public:
		explicit NodeEventHandler(MainApplication *_app)
			: EventHandler(_app) { }

		virtual void reset();
		virtual void down(const MouseInfo &info);
		virtual void up(const MouseInfo &info);
		virtual void move(const MouseInfo &info);
		virtual void leave();

		virtual void paint(gui::GuiObjectPainter *painter);
	private:
		int hittestNode(long x, long y);
	};

	// アンカー制御用ハンドラ
	class AnchorEventHandler
		: public virtual EventHandler {
	public:
		explicit AnchorEventHandler(MainApplication *_app)
			: EventHandler(_app) { }

		virtual void reset();
		virtual void down(const MouseInfo &info);
		virtual void up(const MouseInfo &info);
		virtual void move(const MouseInfo &info);
		virtual void leave();

		virtual void paint(gui::GuiObjectPainter *painter);
	private:
		int hittestSegment(const POINT &pt);
	};
	
	// ACO実行用ハンドラ
	class ACOEventHandler
		: public virtual EventHandler {
	public:
		explicit ACOEventHandler(MainApplication *_app)
			: EventHandler(_app), size(0) {
			pheromone[0] = 0;
			pheromone[1] = 0;
		}

		virtual void reset();
		/* 継承しない
		virtual void down(const MouseInfo &info);
		virtual void up(const MouseInfo &info);
		virtual void move(const MouseInfo &info);
		virtual void leave();
		*/
		virtual void paint(gui::GuiObjectPainter *painter);

		virtual void keydown(UINT uKey);
	private:
		int size;
		double* pheromone[2];
	};


	// ============================
	// メインアプリケーション
	//
	class MainApplication
		: public virtual CallableGuiObject
	{
		// ===============================================================
		// フレンドクラス
		friend class EventHandler;
		friend class NodeEventHandler;
		friend class AnchorEventHandler;
		friend class ACOEventHandler;


		// ===============================================================
		// 定数
		// using enum hack
		enum { CLIENT_WIDTH = 800, };
		enum { CLIENT_HEIGHT = 600, };

	// ===================================================================
	// コンストラクタ／デストラクタ
	public:
		virtual ~MainApplication();
	private:
		ATOM registerClass();

	public:
		MainApplication(HINSTANCE hInstance);

		virtual HWND GetHWND() {
			return this->hWnd;
		}

		virtual LRESULT Callback(UINT uMsg, WPARAM wp, LPARAM lp);

	private:
		lycee_string appName;
		lycee_string title;

		HINSTANCE hInstance;
		ATOM atom;
		HWND hWnd;
		HACCEL hAccelTable;

		HMENU hCxtBaseMenu;
		HMENU hContextMenu;

		HDC hBackScreenDC;
		HBITMAP hBackScreenBitmap;

		EventHandler *eventHandler;
		EventHandler *defaultEventHandler;
		NodeEventHandler *nodeEventHandler;
		AnchorEventHandler *anchorEventHandler;
		ACOEventHandler *acoEventHandler;

	// ===================================================================
	// 初期化／アプリ実行
	public:
		BOOL initialize();

		int run(int nCmdShow);

	private:
		// ============================
		//  モード
		// ============================
		enum OperationMode {
			WAIT,				// 待機
			NODE_DRAGGING,		// ノードドラッグ
			ANCHOR_DRAGGING,	// アンカードラッグ
			VIEW_ACO,			// ACO表示
		};
		OperationMode currentMode;

		// ============================
		// ノードリスト
		// ============================
		std::deque<POINT> nodeList;
		std::deque<ACORoadInfo> roadInfoList;

		ACORoadInfo *activeRoad;
		int draggedPtIndex;
		HitType hitType;

		// ===============================================================
		// イベント
	private:
		void refresh(BOOL bErase=FALSE);

		// ============================
		//  マウスイベント
		// ============================
	public:

	private:
		void showContextMenu(long x, long y);

		// ============================
		// 再描画
		// ============================
	public:
		void event_paint();

	private:
		// ノードの描画
		void paint_node(gui::GuiObjectPainter *painter,
			bool bHitColor);


		// ============================
		// メニューイベント
		// ============================
	public:
		void event_command(WORD menuId);

	private:
		void toggleMenu(WORD menuId);
		void add_node(const POINT &pt);

	};
	
}	// lycee
#endif	// __LYCEE__MAIN_APPLICATION__HEADER__

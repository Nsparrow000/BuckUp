//=========================================================================================================================
// DirectX_Sample [main.cpp]
// Author:satou syusuke
//=========================================================================================================================
#include "main.h"
#include "input.h"
#include <Windows.h>

//=========================================================================================================================
// マクロ定義
//=========================================================================================================================
#define CLASS_NAME "UISET"	// ウィンドウクラスの名前
#define WINDOW_NAME "UISET"		// ウィンドウの名前
#define WINDOW_COLOR_R	(0)		// ウィンドウの色(赤)
#define WINDOW_COLOR_G	(0)			// ウィンドウの色(緑)
#define WINDOW_COLOR_B	(0)			// ウィンドウの色(青)
#define WINDOW_COLOR_A	(0)			// ウィンドウの色(透明度)

//=========================================================================================================================
// プロトタイプ宣言
//=========================================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ウィンドウプロシージャ
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);							// 初期化処理
void Uninit(void);																	// 終了処理
void Update(void);																	// 更新処理
void Draw(void);																	// 描画処理
void DrawFPS(void);																	// 
void DrawTxT(void);

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3D9 g_pD3D = NULL;													// Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;										// Direct3Dデバイスへのポインタ(描画処理に必要)
LPD3DXFONT g_pFont = NULL;													// フォントへのポインタ
int g_nCountFPS;															// FPSカウンタ

//MODE g_mode;

//ModeStyle g_Style;
//=========================================================================================================================
// メイン関数
//=========================================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)
	};
	HWND hWnd;		// ウィンドウハンドル(識別子)
	MSG  msg;		// メッセージを格納する
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGTH };


	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);
	
	
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	

	// ウィンドウの生成
	hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right,
		rect.bottom,
		NULL,
		NULL,
		hInstance,
		NULL);

	// 初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	DWORD dwExecLastTime;	// 処理実行最終時刻
	DWORD dwFPSLastTime;	// FPS計測最終時刻
	DWORD dwCurrentTime;	// 現在時刻
	DWORD dwFrameCount;		// フレームカウント

	dwExecLastTime = timeGetTime();
	dwFPSLastTime = timeGetTime();
	dwCurrentTime = timeGetTime();
	dwFrameCount = 0;

	//メッセージループ
	while (1)
	{	// Windowsの処理
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// メッセージを取得しなかった場合 "0" を返す
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectXの処理
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5秒経過
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) > (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				Update();

				// 描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}

	// 終了処理
	Uninit();

	// ウィンドウクラスの登録解除
	UnregisterClass(
		CLASS_NAME,
		wcex.hInstance);

	return (int)msg.wParam;
	return 0;
}

//=========================================================================================================================
// ウィンドウプロシージャ
//=========================================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGTH };

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);	// WM_QUITメッセージを返す
		break;
	case WM_CLOSE:
		
			DestroyWindow(hWnd);	// WM_DESTROYメッセージを返すl
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			
			DestroyWindow(hWnd);	// WM_DESTROYメッセージを返す

			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=========================================================================================================================
// 初期化処理
//=========================================================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	// DIrect3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ディスプレイモードの取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;		// スクリーンの幅
	d3dpp.BackBufferHeight = SCREEN_HEIGTH;		// スクリーンの高さ
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	// Direct3Dデバイスの生成
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// カリングの設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンド(α値の合成)の設定
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);			// ソース(描画元)の合成方法の設定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// デスティネーション(描画先)の合成方法の設定

	// サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// 縮小時 補間
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// 拡大時 補間
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// U値 繰り返し
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// V値 繰り返し

	// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// α値の合成
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// α値の合成
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// α値の合成

	//テキスト処理
	D3DXCreateFont(g_pD3DDevice, 20, 0, 0, 0,//大きさ
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH, "Terminal", &g_pFont);


	// 入力の初期化
	InitKeyboard(hInstance, hWnd);

	InitUI();
	InitUISet();

	SetUISet(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGTH / 2, 0.0), 100, 50, 0);

	return S_OK; 

}

//=========================================================================================================================
// 終了処理
//=========================================================================================================================
void Uninit(void)
{

	UninitKeyboard();
	UninitUI();
	UninitUISet();

	// Direct3Dデバイスの開放
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの開放
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

}

//=========================================================================================================================
// 更新処理
//=========================================================================================================================
void Update(void)
{
	UpdateKeyboard();
	UpdateUISet();
	UpdateUI();
}

//=========================================================================================================================
// 描画処理
//=========================================================================================================================
void Draw(void)
{

	// バックバッファ&Zバッファのクリア(画面クリア)
	g_pD3DDevice->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(WINDOW_COLOR_R, WINDOW_COLOR_G, WINDOW_COLOR_B, WINDOW_COLOR_A),
		1.0f,
		0);

	// 描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		DrawUISet();
		DrawUI();
		

		DrawTxT();
		DrawFPS();

		// 描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

	
}

//=========================================================================================================================
// デバイスの取得
//=========================================================================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=========================================================================================================================
// FPSの描画
//=========================================================================================================================
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGTH };
	char aStr[256];

	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	// テキストの描画
	g_pFont->DrawText(
		NULL,
		&aStr[0],
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

void DrawTxT(void)
{
	UISet * pUISet = GetUISet();
	UIserect * pUISerect = GetUIserect();

	RECT rect = { 0, 25, SCREEN_WIDTH, SCREEN_HEIGTH };
	char aStr[400];

	int nNum = sprintf(&aStr[0], "セットする座標:(%.1f : %.1f)\n", pUISet->pos.x, pUISet->pos.y);
	nNum += sprintf(&aStr[nNum], "大きさ[幅：高さ]:(%.1f : %.1f : %.1f)\n", pUISet->fWidth, pUISet->fHight);
	nNum += sprintf(&aStr[nNum], "セットできるUIの総数:(%d)\n", pUISerect->TotalNumber);
	nNum += sprintf(&aStr[nNum], "セットするUI番号:(%d)\n", pUISerect->TotalNumber);
	nNum += sprintf(&aStr[nNum], "UI総設置数:(%d)\n\n", pUISerect->nSetNumber);
	nNum += sprintf(&aStr[nNum], "[WASD]:予定場所の移動\n");
	nNum += sprintf(&aStr[nNum], "[Q E]:幅の変更\n");
	nNum += sprintf(&aStr[nNum], "[Z C]:高さの変更\n");
	nNum += sprintf(&aStr[nNum], "[↑ ↓]:種類の変更\n");
	nNum += sprintf(&aStr[nNum], "[Enter]:セット\n\n");
	nNum += sprintf(&aStr[nNum], "[K]:設置したUIの削除\n");
	nNum += sprintf(&aStr[nNum], "[F9]:セットしたUIの書き出し\n");
	nNum += sprintf(&aStr[nNum], "書き出したファイルのパス[%s]\n",SAVEFILETEXT);
	nNum += sprintf(&aStr[nNum], "アルファ値 %f", pUISet->colorA);



	// テキストの描画
g_pFont->DrawText(
		NULL,
		&aStr[0],
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//void SetMode(MODE mode)
//{
//
//	g_mode = mode;
//}
//
//MODE GetMode(void)
//{
//	return g_mode;
//}


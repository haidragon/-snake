#include <windows.h>

#define MAP_TOTAL_WIDTH 1200	//总宽度，游戏区+信息区
#define MAP_TOTAL_HEIGHT 600	//界面高度
#define MAP_GAME_WIDTH 900		//游戏区宽度
#define MAP_GAME_HEIGHT 600		//游戏区高度
#define MAP_INFO_WIDTH 300		//信息区宽度
#define MAP_INFO_HEIGHT 600		//信息区高度

#define key_NULL 0
#define key_LEFT 37
#define key_UP 38
#define key_RIGHT 39
#define key_DOWN 40
#define key_Enter 13

#define NodeStyle_SnakeHead 1
#define NodeStyle_SnakeBody 2
#define NodeStyle_Food 3
#define NodeStyle_Stone 4

#define Pic_SnakeHead	"image/SnakeHead.bmp"
#define Pic_SnakeBody	"image/SnakeBody.bmp"
#define Pic_Food		"image/Food.bmp"
#define Pic_Stone		"image/Stone.bmp"
#define Pic_Start		"image/Start.bmp"
#define Pic_End			"image/End.bmp"

#define InitPosition_SnakeHead_X 450	//30整数倍
#define InitPosition_SnakeHead_Y 300	//

#define Count_Stone 15	//石头数量

extern HINSTANCE hInstance;		//应用进程句柄
extern HANDLE hConcoleOut;		//控制台窗口句柄
extern HWND hWndGame;			//游戏窗口句柄
extern HWND hWndWelcome;		//游戏欢迎界面窗口句柄
extern HWND hWndEnd;			//游戏结束界面窗口句柄
extern HWND hWndScore;			//游戏分数
extern TCHAR szAppName[];		//游戏名称

extern int g_nGameState;
extern int g_nFoodState;
extern int g_nStoneState;
extern int g_nWelcomState;
extern int g_nEndState;

extern int g_nDirect;
extern int g_nCreateMapTimes;
extern int g_nDrawMapTimes;

extern int g_nEatCount;
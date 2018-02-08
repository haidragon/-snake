#include <windows.h>

#define MAP_TOTAL_WIDTH 1200	//�ܿ�ȣ���Ϸ��+��Ϣ��
#define MAP_TOTAL_HEIGHT 600	//����߶�
#define MAP_GAME_WIDTH 900		//��Ϸ�����
#define MAP_GAME_HEIGHT 600		//��Ϸ���߶�
#define MAP_INFO_WIDTH 300		//��Ϣ�����
#define MAP_INFO_HEIGHT 600		//��Ϣ���߶�

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

#define InitPosition_SnakeHead_X 450	//30������
#define InitPosition_SnakeHead_Y 300	//

#define Count_Stone 15	//ʯͷ����

extern HINSTANCE hInstance;		//Ӧ�ý��̾��
extern HANDLE hConcoleOut;		//����̨���ھ��
extern HWND hWndGame;			//��Ϸ���ھ��
extern HWND hWndWelcome;		//��Ϸ��ӭ���洰�ھ��
extern HWND hWndEnd;			//��Ϸ�������洰�ھ��
extern HWND hWndScore;			//��Ϸ����
extern TCHAR szAppName[];		//��Ϸ����

extern int g_nGameState;
extern int g_nFoodState;
extern int g_nStoneState;
extern int g_nWelcomState;
extern int g_nEndState;

extern int g_nDirect;
extern int g_nCreateMapTimes;
extern int g_nDrawMapTimes;

extern int g_nEatCount;
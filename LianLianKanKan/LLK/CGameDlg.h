#pragma once
#include <GdiPlus.h>
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

#include "afxdialogex.h"
#include "CGameControl.h"



// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

	// 对话框数据
	//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALG };
	//#endif

protected:

	int timeCount;
	CDC m_dcMem;			//内存DC
	CDC m_dcElm;			//元素内存DC
	CDC m_dcMask;			//掩码内存DC
	CDC m_dcBG;				//背景DC
	CDC m_dcCache;		
	bool m_bPause;// 游戏暂停与否
	int m_anMap[MAX_ROW][MAX_COL];		//初始游戏地图4*4

	CPoint m_ptGameTop;		//起始点坐标
	CSize m_sizeElem;		//图片元素大小
	CRect m_rtGameRect;     //游戏区域的大小

	bool m_bFirstPoint;		//选中的图片是不是第一次选中的，TRUE   是，FALSE  否
	Vertex m_ptSelFirst;	//第一次选中的点(x表示列)
	Vertex m_ptSelSec;		//第二次选中的点

	CGameControl m_gameControl; //游戏控制类
	void DrawGameTime();
	bool m_bPlaying;
	void JudgeWin();
	//CPoint m_ptSelFirst;	//第一次选中的点
	//CPoint m_ptSelSec;		//第二次选中的点
protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void InitBackground();	//初始化背景
	void InitElement();		//初始化元素
	void UpdateWindow();		//
	void UpdateMap();
	void DrawTipFrame(int nRow, int nCol);		//绘制游戏提示框
	void DrawTipLine(Vertex avPath[MAX_ROW * MAX_COL], int nVexnum);    //绘制提示线

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();


	afx_msg void OnClickedButtonStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);		//鼠标点击事件

	afx_msg void OnClickedBtnMention();
	afx_msg void OnClickedBtnPlato();
	CProgressCtrl m_GameProgress;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnSet();
	afx_msg void OnBnClickedBtnPause();
	afx_msg void OnBnClickedBtnHelp();
};







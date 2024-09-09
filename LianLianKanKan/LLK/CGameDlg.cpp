// CGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CGameDlg.h"
#include "CHelpDialog.h"
#define GAMEWND_HEIGHT 600
#define GAMEWND_WIDTH 800

// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALG, pParent)
{
	//初始化起始点坐标
	m_ptGameTop.x = 50;
	m_ptGameTop.y = 50;

	//初始化图片元素大小
	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;

	//初始化游戏更新区域
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_COL;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_ROW;

	//初始化图标选中状态
	m_bFirstPoint = true;
	m_bPlaying = false;
	m_bPause = false;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_GameProgress);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnClickedButtonStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_MENTION, &CGameDlg::OnClickedBtnMention)
	ON_BN_CLICKED(IDC_BTN_PLATO, &CGameDlg::OnClickedBtnPlato)
	ON_BN_CLICKED(IDC_BTN_RANK, &CGameDlg::OnBnClickedBtnSet)
	ON_WM_TIMER()
	//ON_BN_CLICKED(IDC_BUTTON1, &CGameDlg::OnBnClickedButton1)
	
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CGameDlg::OnBnClickedBtnPause)
	ON_BN_CLICKED(IDC_BTN_HELP, &CGameDlg::OnBnClickedBtnHelp)
END_MESSAGE_MAP()




//初始化窗口背景和大小
void CGameDlg::InitBackground()
{	// TODO: 在此处添加实现代码.

	//加载BMP图片资源
	HANDLE Backbmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//获得当前对话框的视频内容
	CClientDC dc(this);

	//创建与视频内容兼容的内存DC
	m_dcBG.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcBG.SelectObject(Backbmp);

	//初始化内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);

	//绘制背景到内存DC中
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);




	//设置窗口大小
	UpdateWindow();
}


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//窗口标题
	this->SetWindowTextW(_T("欢乐连连看　基本模式"));

	//初始化背景
	InitBackground();

	//初始化元素
	InitElement();


	this->GetDlgItem(IDC_GAME_TIME)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_EDIT_TIME)->ShowWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}

//初始化元素
void CGameDlg::InitElement() {
	CClientDC dc(this);

	HANDLE Elmbmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_dcElm.CreateCompatibleDC(&dc);

	m_dcElm.SelectObject(Elmbmp);

	//掩码图加载
	HANDLE Maskbmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_dcMask.CreateCompatibleDC(&dc);

	m_dcMask.SelectObject(Maskbmp);


	// 加载游戏暂停BMP图片资源
	HANDLE hCache = ::LoadImage(NULL, _T("theme\\picture\\fruit_pause.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// 创建与视频内存兼容的内存DC
	m_dcCache.CreateCompatibleDC(&dc);

	// 将位图资源选入DC
	m_dcCache.SelectObject(hCache);
}

//开始游戏
void CGameDlg::OnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码

	m_gameControl.StartGame();

	//判断是否正在玩游戏
	m_bPlaying = true;
	this->GetDlgItem(IDC_BTN_START)->EnableWindow(false);
	
	timeCount = 300;

	//初始进度条
	m_GameProgress.SetRange(0, 300);//初始范围
	m_GameProgress.SetStep(-1);//初始步数值
	m_GameProgress.SetPos(300);//设置初始值
	//启动计时器
	this->SetTimer(1, 1000, NULL);
	//绘制当前秒数
	DrawGameTime();


	//更新地图
	UpdateMap();

	//更新窗口
	Invalidate(FALSE);
	// 设置进度条隐藏和剩余时间控件
	this->GetDlgItem(IDC_GAME_TIME)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_EDIT_TIME)->ShowWindow(TRUE);
}
void CGameDlg::DrawGameTime() {
	// 获取绘图设备的句柄
	CDC* pDC = GetDC();
	//// 创建GDI+绘图对象
	Graphics graphics(pDC->GetSafeHdc());
	// 设置绘制参数
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 24, FontStyleRegular, UnitPixel);
	SolidBrush brush(Color(2, 4, 8, 16)); // 黑色画刷

}


//调整窗口大小
void CGameDlg::UpdateWindow()
{

	// TODO: 在此处添加实现代码.

	//调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);		//获得窗口大小
	this->GetWindowRect(rtClient);	//获得客户区大小

	//标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Width() - rtClient.Width();

	//设置窗口大小
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);

	CenterWindow();
}


//更新地图
void CGameDlg::UpdateMap()
{
	// TODO: 在此处添加实现代码.

	//计算图片的顶点坐标与图片大小
	int nTop = m_ptGameTop.y;
	int nLeft = m_ptGameTop.x;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;

	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top,
		m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);

	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			//m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElm, 0, m_anMap[i][j] * nElemH, SRCCOPY);

			int nInfo = m_gameControl.GetElement(i, j);       //当前元素图片的数值
			if (nInfo == BLANK)  continue;


			//将背景与掩码相或，边保留，图像区域为1
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nInfo * nElemH, SRCPAINT);

			//将元素图片相与，边保留，图像区域为元素图片
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElm, 0, nInfo * nElemH, SRCAND);

		}
	}

}

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// TODO: 在此处添加实现代码.
	if (m_bPause){
		return;
	}

	if (m_bPlaying==false) {
		return;
	}
	//去掉小于0状态
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	//换算点击的坐标
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;//行号
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;

	//判断坐标的有效性
	if (nRow > MAX_ROW - 1 || nCol > MAX_COL - 1) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}


	//第一个点
	if (m_bFirstPoint) {
		//绘制提示框
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetFirstPoint(nRow, nCol);

	}
	//第二个点
	else {
		//绘制提示框
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetSecPoint(nRow, nCol);

		Vertex avPath[MAX_ROW * MAX_COL];     //获得路径   160为路径最长（不会到160条路径的）
		int nVexnum = 0;      //顶点个数

		//判断是否是相同图片	
		if (m_gameControl.Link(avPath, nVexnum)) {

			//画提示线
			DrawTipLine(avPath, nVexnum);

			//更新地图
			UpdateMap();
		}
		Sleep(200);    //延迟
		InvalidateRect(m_rtGameRect, FALSE); //局部矩形更新

		// 判断胜负
		JudgeWin();

	}
	m_bFirstPoint = !m_bFirstPoint; //赋反值

	CDialogEx::OnLButtonUp(nFlags, point);
}



//绘制矩形提示框
void CGameDlg::DrawTipFrame(int nRow, int nCol) {
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}



//绘制提示线
void CGameDlg::DrawTipLine(Vertex avPath[MAX_ROW * MAX_COL], int nVexnum)
{
	//获取DC
	CClientDC dc(this);

	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	//将画笔选入DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	dc.MoveTo(m_ptGameTop.x + avPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + avPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	//绘制连接线
	for (int i = 0; i < nVexnum - 1; i++)
	{

		dc.LineTo(m_ptGameTop.x + avPath[i + 1].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + avPath[i + 1].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}

	dc.SelectObject(pOldPen);
}

void CGameDlg::OnClickedBtnMention()
{
	// TODO: 在此添加控件通知处理程序代码
	// 如果没有进行游戏，则返回
	if (m_bPlaying == false)
	{
		return;
	}

	// 如果能够连通，绘制提示框和连接线并更新游戏地图
	Vertex avPath[MAX_VERTEX_NUM]; // 获得路径
	int nVexnum = 0;			   // 顶点个数

	if (m_gameControl.Help(avPath, nVexnum))
	{
		// 画第一个点的提示框
		DrawTipFrame(avPath[0].row, avPath[0].col);
		DrawTipFrame(avPath[nVexnum - 1].row, avPath[nVexnum - 1].col);

		// 画提示线
		DrawTipLine(avPath, nVexnum);

		// 为了使第二个提示框可以看到，暂停500ms后，再刷新页面
		Sleep(500);

		UpdateMap(); // 更新地图

		// 局部矩形更新
		InvalidateRect(m_rtGameRect, FALSE);
	}
}


void CGameDlg::OnClickedBtnPlato()
{
	// TODO: 在此添加控件通知处理程序代码
	// 调用ResertGraph()
	m_gameControl.Resert();

	// 更新地图，调用UpdateMap(),更新界面显示
	UpdateMap();

	// 通知界面重绘
	InvalidateRect(m_rtGameRect, FALSE); // 局部矩形更新
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 设置进度条位置之前，需要判断计时器编号是否为当前计时器
	if (nIDEvent == 1 && m_bPlaying)
	{
		// 游戏时间减一秒
		if (timeCount > 0)
		{
			timeCount--;
			CString str;
			str.Format(_T("%d"), timeCount);
			//SetDlgItemText(IDC_EDIT_TIME, str);
			
			CFont font;
			font.CreateFont(30, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
			GetDlgItem(IDC_EDIT_TIME)->SetFont(&font);

			// 设置文本居中显示
			GetDlgItem(IDC_EDIT_TIME)->SetWindowText(str);



			
			UpdateData(false);

			// 刷新进度条位置
			m_GameProgress.StepIt();
		}
	}

	// 判断胜负
	JudgeWin();
	CDialogEx::OnTimer(nIDEvent);
}

// 判断胜负
void CGameDlg::JudgeWin()
{
	// 游戏胜负判断
	BOOL bGameStatus = m_gameControl.IsWin(m_GameProgress.GetPos());

	// 判断是否继续游戏
	if (bGameStatus == GAME_PLAY)
	{
		return;
	}
	else
	{
		// 将游戏表示改为false
		m_bPlaying = false;

		// 关闭定时器
		KillTimer(PLAY_TIMER_ID);

		// 提示获胜
		CString strTitle;

		this->GetWindowTextW(strTitle);

		if (bGameStatus == GAME_SUCCESS)
		{
			MessageBox(_T("挑战成功!"), strTitle);
		}
		else if (bGameStatus == GAME_LOSE)
		{
			MessageBox(_T("超时失败！"), strTitle);
		}

		// 还原游戏按钮可点击
		this->GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
	}
}



void CGameDlg::OnBnClickedBtnSet()
{
	// TODO: 在此添加控件通知处理程序代码
	// 调用ResertGraph()
	m_gameControl.Resert();

	// 更新地图，调用UpdateMap(),更新界面显示
	UpdateMap();

	// 通知界面重绘
	InvalidateRect(m_rtGameRect, FALSE); // 局部矩形更新
}







void CGameDlg::OnBnClickedBtnPause()
{
	// TODO: 在此添加控件通知处理程序代码
	// 获得当前对话框的视频内容
	CClientDC dc(this);

	// 游戏未正在进行，直接返回
	if (m_bPlaying == false)
	{
		return;
	}

	// 如果游戏不是暂停状态
	if (m_bPause == false)
	{
		// 绘制背景到内存DC中
		m_dcMem.BitBlt(MAP_LEFT, MAP_TOP, 640, 500, &m_dcCache, 0, 0, SRCCOPY);

		GetDlgItem(IDC_BTN_RANK)->EnableWindow(false);
		GetDlgItem(IDC_BTN_MENTION)->EnableWindow(false);
		InvalidateRect(m_rtGameRect, false); // 更新界面
		this->GetDlgItem(IDC_BTN_PAUSE)->SetWindowTextW(_T("继续游戏"));
		KillTimer(PLAY_TIMER_ID);
	}

	// 如果游戏暂停
	if (m_bPause == true)
	{
		UpdateMap();
		GetDlgItem(IDC_BTN_RANK)->EnableWindow(1);
		GetDlgItem(IDC_BTN_MENTION)->EnableWindow(1);
		

		this->GetDlgItem(IDC_BTN_PAUSE)->SetWindowTextW(_T("暂停游戏"));
		InvalidateRect(m_rtGameRect, FALSE); // 局部矩形更新
		SetTimer(PLAY_TIMER_ID, 1000, NULL); // 重新启动计时器
	}
	m_bPause = !m_bPause;
}


void CGameDlg::OnBnClickedBtnHelp()
{
	// TODO: 在此添加控件通知处理程序代码
	CHelpDialog dlg;
	dlg.DoModal();
}

#include <iostream>
#include "pch.h"
#include "CGameControl.h"
using namespace std;
//int CGameControl::s_nRows = 10;
//int CGameControl::s_nCols = 16;
//int CGameControl::s_nPicNum = 10;
CGameControl::CGameControl()
{
}


CGameControl::~CGameControl()
{
}

//开始游戏函数
void CGameControl::StartGame(void)
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_graph);

}

//获得某行某列的图片编号函数
int CGameControl::GetElement(int nRow, int nCol)
{
	//return m_anMap[nRow][nCol];
	return m_graph.GetVertex(nRow * MAX_COL + nCol);
}

//设置第一个点函数
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;

}

//设置第二个点函数
void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;

}

//连接判断函数
bool CGameControl::Link(Vertex avPath[MAX_ROW * MAX_COL], int& nVexnum)
{

	//判断选中的点是否为同一个图片，若为同一个图片，则不能连通
	if (m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col)
	{
		return false;
	}

	//判断图片是否相同，如果不同则不能连通
	int	nInfo1 = m_graph.GetVertex(m_ptSelFirst.row * MAX_COL + m_ptSelFirst.col);
	int	nInfo2 = m_graph.GetVertex(m_ptSelSec.row * MAX_COL + m_ptSelSec.col);

	if (nInfo1 != nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
	{
		return false;
	}

	//判断是否可以连通
	CGameLogic gameLogic;
	if (gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec) == true)
	{
		//消子
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);


		//返回路径顶点
		nVexnum = gameLogic.GetVexPath(avPath);
		return true;
	}

	return false;
}


bool CGameControl::IsWin()
{
	// TODO: 在此处添加实现代码.
	CGameLogic logic;
	if (logic.IsBlank(m_graph) == true) {
		m_graph.ClearGraph(); //清理图结构！
		return true;
	}
	return false;
}


// 在地图中查找可以消除的一堆照片，返回连接路径和路径上的顶点数
bool CGameControl::Help(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum)
{
	CGameLogic logic;

	// 判断是否为空
	if (logic.IsBlank(m_graph) == true)
	{
		return false;
	}

	// 查找一条有效的提示路径
	if (logic.SearchValidPath(m_graph))
	{
		// 返回路径顶点
		nVexnum = logic.GetVexPath(avPath);
		return true;
	}
	return false;
}

// 判断是否获胜
BOOL CGameControl::IsWin(int nTime)
{
	// 定义逻辑处理类
	CGameLogic logic;

	// 判断游戏时间
	if (nTime <= 0)
	{
		// 清除图
		m_graph.ClearGraph();
		return GAME_LOSE;
	}

	// 判断是否图中所有点为空
	if (logic.IsBlank(m_graph) == true)
	{
		// 清除图
		m_graph.ClearGraph();
		return GAME_SUCCESS;
	}
	return GAME_PLAY;
}

// 实现重排
void CGameControl::Resert(void)
{
	// 重排图中顶点
	CGameLogic logic;
	logic.ResertGraph(m_graph);
}

#pragma once
#include"CGameLogic.h"
#include "CGraph.h"
#include "pch.h"
#include <afxwin.h>
class CGameControl
{
public:
	CGameControl();
	~CGameControl();
	CGraph m_graph;			//初始游戏地图
protected:
	
	Vertex m_ptSelFirst;	//第一次选中的点(x表示列)
	Vertex m_ptSelSec;		//第二次选中的点

public:
	//开始游戏函数
	void StartGame(void);
	void Resert(void);
	BOOL IsWin(int nTime);
	//获得某行某列的图片编号函数
	int GetElement(int nRow, int nCol);

	void SetFirstPoint(int nRow, int nCol);             //设置第一个点函数
	void SetSecPoint(int nRow, int nCol);               //设置第二个点函数
	bool Help(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum); // 在地图中查找可以消除的一堆照片，返回连接路径和路径上的顶点数



	bool Link(Vertex avPath[MAX_ROW * MAX_COL], int& nVexnum);          //连接判断函数

	//获胜
	bool IsWin();
};


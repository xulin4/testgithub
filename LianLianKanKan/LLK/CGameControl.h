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
	CGraph m_graph;			//��ʼ��Ϸ��ͼ
protected:
	
	Vertex m_ptSelFirst;	//��һ��ѡ�еĵ�(x��ʾ��)
	Vertex m_ptSelSec;		//�ڶ���ѡ�еĵ�

public:
	//��ʼ��Ϸ����
	void StartGame(void);
	void Resert(void);
	BOOL IsWin(int nTime);
	//���ĳ��ĳ�е�ͼƬ��ź���
	int GetElement(int nRow, int nCol);

	void SetFirstPoint(int nRow, int nCol);             //���õ�һ���㺯��
	void SetSecPoint(int nRow, int nCol);               //���õڶ����㺯��
	bool Help(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum); // �ڵ�ͼ�в��ҿ���������һ����Ƭ����������·����·���ϵĶ�����



	bool Link(Vertex avPath[MAX_ROW * MAX_COL], int& nVexnum);          //�����жϺ���

	//��ʤ
	bool IsWin();
};


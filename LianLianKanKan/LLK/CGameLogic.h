#pragma once
#include "global.h"
#include "CGraph.h"

class CGameLogic
{
public:
	CGameLogic(void); // ���캯��

protected:
	Vertex m_avPath[MAX_VERTEX_NUM]; // �����ڽ��������ж�ʱ�������Ķ���
	int m_anPath[MAX_VERTEX_NUM];	 // ������ͨ·���Ķ�������
	int m_nVexNum;					 // ������
	int m_nCorner;					 // ����·������m_anPath�еĹյ���

public:
	void InitMap(CGraph& g);
	void UpdateArc(CGraph& g, int nRow, int nCol); // �ж���Ϸ��ͼ��nRow�У�nCol�еĶ��������������ҵĶ����Ƿ��бߣ�����бߣ������ͼ�ṹ��������
	bool IsLink(CGraph& g, Vertex v1, Vertex v2);  // �ж϶���v1��v2�Ƿ���ͨ
	void Clear(CGraph& g, Vertex v1, Vertex v2);   // ��V1��v2��ͨʱ�����䶥���ֵ��Ϊ��
	bool SearchPath(CGraph& g, int nV0, int nV1);  // ������������������ж�V1��ͼg���Ƿ���ͨ
	bool IsExsit(int nVi);						   // �ж�����ΪnVi�Ķ����Ƿ񱣴浽��ͨ����m_anPath��
	bool IsCorner(void);						   // �ж�����·�������У��������������Ƿ񹹳�һ���յ�
	void PushVertex(int nV);
	void PopVertex();
	int GetVexPath(Vertex avPath[MAX_VERTEX_NUM]); // ͨ����������·��
	bool IsBlank(CGraph& g);					   // �ж�ͼg�����еĶ����Ƿ�Ϊ��
	bool SearchValidPath(CGraph& g);			   // ����һ�Կ���������ͼƬ
	void ResertGraph(CGraph& g);				   // ��ͼ�ṹg�ӵĶ���������ţ������¶���Ĺ�ϵ
};

#pragma once
#include "global.h"
// ͼ���ݽṹ��
class CGraph
{
public:
	CGraph();

	typedef int Vertices[MAX_VERTEX_NUM];					// �������������
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // �ߵ���������

protected:
	Vertices m_Vertices;   // ��������
	AdjMatrix m_AdjMatrix; // ��ϵ����

	int m_nVexnum; // ��������
	int m_nArcnum; // �ߵ�����

public:
	void InitGraph(void);						 // ��ʼ��ͼ�Ķ���͹�ϵ
	int AddVertex(int nInfo);					 // ������info���뵽����������
	void AddArc(int nV1Index, int nV2Index);	 // ���nV1Index��nV2Index�Ĺ�ϵ
	int GetVertex(int ninfo);					 // ��ȡ��i��������������ΪnIndex�Ķ���
	bool GetArc(int nV1Index, int nV2Index);	 // �����������Ļ���Ϣ
	void UpdateVertex(int nIndex, int Info);	 // ��ͼ����������������ΪnIndex�Ķ����ֵ����Ϊinfo
	int GetVexnum(void);						 // ��ȡ���������еĶ�����
	void ClearGraph();							 // ��ͼ�ж���ͱ߻�ԭΪ��ʼ״̬
	void ChangeVertex(int nIndex1, int nIndex2); // �����������λ��
};

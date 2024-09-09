#include "pch.h"
#include "CGraph.h"

// ���캯��
CGraph::CGraph()
{
	InitGraph(); // ��ʼ��ͼ
}

// ͼ�ṹ�ĳ�ʼ����-1��û��ͼƬ 0��û�й�ϵ
void CGraph::InitGraph()
{
	m_nArcnum = 0;
	m_nVexnum = 0;

	// ��ʼ��������ߵ���Ϣ
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		// ��ʼ������
		m_Vertices[i] = -1;

		for (int j = 0; j < MAX_VERTEX_NUM; j++)
		{
			// ��ʼ����
			m_AdjMatrix[i][j] = 0;
		}
	}
}

// ��Ӷ���
int CGraph::AddVertex(int nInfo)
{
	if (m_nVexnum > MAX_VERTEX_NUM)
	{
		return 0;
	}
	m_Vertices[m_nVexnum] = nInfo;
	m_nVexnum++;
	return m_nVexnum;
}

// ���������������ı�
void CGraph::AddArc(int nV1Index, int nV2Index)
{
	m_AdjMatrix[nV1Index][nV2Index] = true;
	m_AdjMatrix[nV2Index][nV1Index] = true;
}

// �����������Ӷ���������ȡ����Ӧ�Ķ���
int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

// �����������Ļ���Ϣ
bool CGraph::GetArc(int nV1Index, int nV2Index)
{
	return m_AdjMatrix[nV1Index][nV2Index];
}

// ��ȡ���������еĶ�����
int CGraph::GetVexnum(void)
{
	return m_nVexnum;
}

// ��ͼ����������������ΪnIndex�Ķ����ֵ����Ϊinfo
void CGraph::UpdateVertex(int nIndex, int nInfo)
{
	m_Vertices[nIndex] = nInfo;
}

// ��ͼ�ж���ͱ߻�ԭΪ��ʼ״̬
void CGraph::ClearGraph()
{
	InitGraph();
}

// �����������λ��
void CGraph::ChangeVertex(int nIndex1, int nIndex2)
{
	int Temp = m_Vertices[nIndex1];
	m_Vertices[nIndex1] = m_Vertices[nIndex2];
	m_Vertices[nIndex2] = Temp;
}
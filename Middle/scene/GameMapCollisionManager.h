#ifndef _MAP_COLLISION_MANAGER_H_
#define _MAP_COLLISION_MANAGER_H_

namespace	Orphigine
{
class	PhyWorld;
}
class	CMapCollisionManager
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	CMapCollisionManager(void);
	~CMapCollisionManager(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	/* �������������ļ��ж�ȡ���ݡ� �����������������ļ��� ����·���� */
	uint32	LoadCollisionTriInfoFromFile(const char *szFileName);

	/*
	 * ͨ������� ƽ��fx, fzλ�õõ��߶ȡ� ����1�� FLOAT fx ��Ϸ�߼����ꡣ ����2��
	 * FLOAT fz ��Ϸ�߼����ꡣ ����3�� FLOAT& fy ��Ϸ�߼����� ���صĸ߶ȡ� return�� 1
	 * �� �ɹ��� fy�����塣 0 �� ʧ�ܣ� fy�����壬 �����˴�����ײ���ݡ�
	 */
	BOOL	Get3DMapHeight(FLOAT fx, FLOAT fy, FLOAT fz, FLOAT &outY);

	BOOL	GetMapHeight(FLOAT fx, FLOAT fz, FLOAT &outY);

	/*
	 * ͨ������� ƽ��fx, fzλ�õõ��߶ȡ� ����1�� FLOAT fx ��Ϸ�߼����ꡣ ����2��
	 * FLOAT fz ��Ϸ�߼����ꡣ ����3�� FLOAT& fy ��Ϸ�߼����� ���صĸ߶ȡ� return�� 1
	 * �� �ɹ��� fy�����塣 0 �� ʧ�ܣ� fy�����壬 �����˴�����ײ���ݡ�
	 */
	BOOL	IsIntersection
			(
				FLOAT	fOrigx,
				FLOAT	fOrigy,
				FLOAT	fOrigz, /* ���ߵ�ԭ�㡣 */
				FLOAT	fDirx,
				FLOAT	fDiry,
				FLOAT	fDirz,	/* ���ߵķ��� */
				int32		ix,
				int32		iz,		/* ѡ�е�ͼ��λ�� */
				FLOAT	&fPosx,
				FLOAT	&fPosy,
				FLOAT	&fPosz	/* ���ؽ������������λ�á� */
			);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	Orphigine::PhyWorld * m_physicsWorld;
};

/* class */
#endif /* _MAP_COLLISION_MANAGER_H_ */

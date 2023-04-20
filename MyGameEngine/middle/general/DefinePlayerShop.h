#ifndef __GAMEDEFINE_PLAYERSHOP_H__
#define __GAMEDEFINE_PLAYERSHOP_H__

namespace	PLAYER_SHANGDIAN
{
enum STATUS_STALL
{
	STALL_INVALID	= 0,			/* �˹�̨��û�п��Ÿ����ʹ�� */
	STALL_CLOSE,				/* �˹�̨�Ѿ����� */
	STALL_OPEN,				/* �˹�̨�Ѿ����� */
};
}
#define MAX_DY_GROUP_PRICE_NUM		10	/* ��̬�̵�����Ʒ�۸��������� */
#define MAX_DY_PER_GROUP_GOODS_NUM	10	/* ��̬�̵�ÿ�鷷����Ʒ���� */

enum DY_PRICE_TYPE		/* ��̬�̵�۸����� */
{
	PRICE_GOLD	= 0,	/* ��Ϸ�� */
	PRICE_CREDIT,		/* ���� */
	PRICE_HONOR,		/* ���� */
	PRICE_GP,		/* �ﹱ */
	PRICE_ITEM,		/* ��Ʒ */

	PRICE_RMB,		/* ����� */
	PRICE_TYPE_NUM,
};
#endif /* __GAMEDEFINE_PLAYERSHOP_H__ */

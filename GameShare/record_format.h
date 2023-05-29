/*$T MapServer/Server/Base/record_format.h GC 1.140 10/10/09 10:07:21 */

/* record_format.h $v1.0 13407899 */
#ifndef _RECORD_FORMAT_H_
#define _RECORD_FORMAT_H_

/*
 * TOL: ;
 * ���1GUID����GUID��,��ɫ����,���ڵ�ͼsceneid,������ͣ�0���ף�1��̯��,����ǰ��������,���׺���������
 * ;
 * ��Ʒ1ID,��ƷGUID1,��Ʒ1�������,��Ʒ2ID,��ƷGUID2,��Ʒ2�������,��Ʒ3ID,��ƷGUID3,��Ʒ3�������,��Ʒ4ID,
 * ;
 * ��ƷGUID4,��Ʒ4�������,��Ʒ5ID,��ƷGUID5,��Ʒ5�������,��ƥID,��ƥGUID, ;
 * ���2GUID������GUID��,��ɫ����,���ڵ�ͼsceneid,������ͣ�0���ף�1��̯��,����ǰ��������,���׺���������
 * ;
 * ��Ʒ1ID,��ƷGUID1,��Ʒ1�������,��Ʒ2ID,��ƷGUID2,��Ʒ2�������,��Ʒ3ID,��ƷGUID3,��Ʒ3�������,��Ʒ4ID,
 * ;
 * ��ƷGUID4,��Ʒ4�������,��Ʒ5ID,��ƷGUID5,��Ʒ5�������,��ƥID,��ƥGUID ;
 * Trade ��ʽΪ, log����,
 * ���1��Ϣ,��Ʒ1��Ϣ,...��Ʒ5��Ϣ,pet��Ϣ,���2��Ϣ,��Ʒ1��Ϣ,...��Ʒ5��Ϣ,pet��Ϣ,
 * ;
 * IOL:GL��,Server��,��Ʒ���,��ɫGUID,�Է�GUID,��������,��󱳰�λ��,������, ;
 * ���NPC,XPOS,ZPOS,����̵��(��������֮����-1),�;öȣ���Ƕ�׸��� ;
 * ��������1������1��������������4������4 ;
 * MIL:��ɫGUID���������ͣ�������xλ��,zλ�ã������ţ�����ű��������־ ;
 * ����0������1������2������3������4������5������6������7�� ;
 * ��ɱ�־��������ɱ�־ֵ��ȫ����������������ȫ����������ֵ ;
 * MOL:�����ɫ�������ɫ���������ͣ�����������������xλ��,zλ�� ;
 * POL:�����ɫ�������ɫ���������ͣ�������xλ��,zλ�� ,������ ;
 * SOL:�����ɫ���������ͣ�������xλ��,zλ��,���ܱ�� ;
 * XOL:�����ɫ���������ͣ�������xλ��,zλ��,���ܱ�� ;
 * GPL:��ɫGUID����ɫ���֣��������淨��ţ��Ƿ���ӣ�������� ;
 * ��Ա1�ȼ�����Ա1ְҵ����Ա2�ȼ�����Ա2ְҵ����Ա3�ȼ��� ;
 * ��Ա3ְҵ����Ա4�ȼ�����Ա4ְҵ����Ա5�ȼ�����Ա5ְҵ����Ա6�ȼ�����Ա6ְҵ��
 */
static const char	*csRECORD_FORMAT_Quest = "MIL:%u,%d,%d,%.2f,%.2f,%d,%d,%d,%u,%u,%u,%u,%u,%u,%u,%u,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_Item = "%u,%u,%s,%s,%d,%u,%s,%d,%d,%d,%d,%d,%u,%u,%u,%u,%u,%.2f,%.2f,%d,%u,%d,%d,%d";
static const char	*csRECORD_FORMAT_Equip = "%u,%u,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_Money = "%u,%u,%s,%d,%d,%d,%d,%d,%.2f,%.2f,%u,%d,%d,%u,%u,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_Pet = "%u,%u,%d,%d,%.2f,%.2f,%u,%u,%d,%d,%d";
static const char	*csRECORD_FORMAT_Skill = "%u,%d,%d,%.2f,%.2f,%u,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_Ability = "%u,%d,%d,%.2f,%.2f,%u,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_GameWay = "%u,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_IllegalEnter = "%u,%s,%d,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_IB = "%u,%u,%s,%d,%d,%d,%d,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_Cheat = "%s,%u,%d,%u,%u,%f,%f,%u,%d,%d";
static const char	*csRECORD_FORMAT_Trade = "%u,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%u,%u,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%u,%d,%d";
static const char	*csRECORD_FORMAT_WorlShop = "%u,%u,%d,%d,%u,%d,%d,%d,%d,%d,%u,%u,%d,%d";
static const char	*csRECORD_FORMAT_ReturnToChild = "%d,%u,%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_PetSkillChange = "%u,%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_IBMoney = "%u,%s,%d,%u,%u,%u,%d,%u,%u,%u,%d,%d";
static const char	*csRECORD_FORMAT_IBCost = "%u,%s,%d,%u,%u,%u,%d,%u,%d,%d,%d";
static const char	*csRECORD_FORMAT_StockTrade = "%u,%u,%d,%d,%d,%d,%d,%u,%u,%d,%d";
static const char	*csRECORD_FORMAT_StockAcc = "%u,%d,%d,%d,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_Guild = "%d,%s,%d,%d,%d,%d,%d,%d,%d";
static const char	*csRECORD_FORMAT_ZhuanJing = "%u,%d,%d,%.2f,%.2f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

#endif /* _RECORD_FORMAT_H_??? */

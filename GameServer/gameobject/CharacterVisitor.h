/*$T MapServer/Server/Obj/Visitor/CharacterVisitor.h GC 1.140 10/10/07 10:07:35 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef CharacterVisitor_h__
#define CharacterVisitor_h__

#include "TypeDefine.h"

class	Character;
struct _INIT_OBJECT;

// ��ɫ������
class CharacterVisitor
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum VisitorType { CharacterVisitor_None, CharacterVisitor_MonsterAttr };

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	CharacterVisitor();
	virtual ~CharacterVisitor();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	// ����
	virtual CharacterVisitor::VisitorType	GetType() = 0;

	// ��ʼ��
	virtual void VisitInitMonster(Character *pChar)
	{
	};
};
#endif
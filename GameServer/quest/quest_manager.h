#pragma once

#include "share/TAB/TabDefine_Map_Quest.h"
struct NPC_QUEST;
struct _QUEST_DATA_t;
class Player;
class Character;
class GameMap;
class QuestManager: public GameSingleton<QuestManager>
{
public:
	QuestManager();
	virtual	~QuestManager();

	KHAN_RETURN_RESULT			Initialize();
	_QUEST_DATA_t* GetQuestData(int32_t questId);
	void OnNPCClicked(Player* pPlayer, MapID_t uSceneID, ObjID_t uNPCID, GUID_t uNPCGUID);
	BOOL IsQuestCompleted(const Player* const pPlayer, uint32 uIndexQuest);
    void ShowNpcQuestList(GameMap* pMap, int32* iQuestList, int32 iCount, ObjID_t selfId, ObjID_t targetId);
    //! �������״̬
    int32_t GetQuestState(Player* pPlayer, int32 iMissionID);
    //! ��ұ�����Ʒ�����仯��������
    void OnEvent_ItemChanged(Player* pPlayer, uint32 uItemDataID, int32 nChangeType);

    int32_t GetNeedItemNum(int32 iMissionID, Lua_State* L, int32 itemId);

    BOOL QuestCheckSubmit(Player* pPlayer, int32 iMissionID, ObjID_t targetId, int32 InstIndex);
    int32_t QuestComplate(Player* pPlayer, GameMap* pMap, int32 iMissionID, ObjID_t targetId, int32 selId);
    void QuestBonusNotItem(Player* pPlayer, GameMap* pMap, int32 iMissionID, ScriptID_t nScriptId);
    int32_t QuestBonusItem(Player* pPlayer, GameMap* pMap, int32 iMissionID, int32 selId);
    //! ��˷����仯��������
    void OnEvent_PetChanged(Player* pPlayer, uint32 uPetDataID);

    //! ��ͻ��˷���XCScriptCommand��Ϣ���ӱ���ȡ������Ϣ�����͡�
    void AddDispatchQuestInfo(Player* pPlayer, int32 iMissionID, ObjID_t targetId, int32 state);

    //! ���ɱ��������������
    void OnEvent_KillObject(Player* pPlayer, Character* pObj);

    int32 GetItemIdInItemBox(Lua_State* L, int32 gpType, Player* pPlayer, int32 itemId);

    typedef FixedFlag<MAX_CHAR_QUEST_DATA_NUM> FlagMD;
    const FlagMD& getFlagMDClientFilter()
    {
        return m_FlagMDClientFilter;
    }
private:
    //! �������������
    void LoadQuestList();

    //! �����������������
    void LoadDeliveryTable();

    //! ���ػ������������
    void LoadEscortTable();

    //! ����ʹ����Ʒ���������
    void LoadUseItemTable();

    //! ���ػ�ȡ��Ʒ���������
    void LoadQuestLootItemTable();

    //! ����ɱ�����������
    void LoadQuestKillMonsterTable();

    //! ���ؽ����������������
    void LoadQuestEnterAreaTable();

    void initFlagMDClientFilter();
private:
    //! ɱ�������
	__QUEST_KILLMONSTER m_QuestKillMonsterTable;
    //! ���������
	__QUEST_DELIVERY    m_QuestDeliveryTable;
    //! ���������
    __QUEST_HUSONG      m_QuestEscortTable;
    //! ʹ����Ʒ�����
    __QUEST_USEITEM     m_QuestUseItemTable;

    //! ��ȡ��Ʒ���������
	__QUEST_LOOKITEM    m_QuestLookItemTable;

    //! �������������
    __QUEST_ENTERAREA   m_QuestEnterAreaTable;

    FlagMD	m_FlagMDClientFilter;
};
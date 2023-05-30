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
    //! 获得任务状态
    int32_t GetQuestState(Player* pPlayer, int32 iMissionID);
    //! 玩家背包物品发生变化的任务处理
    void OnEvent_ItemChanged(Player* pPlayer, uint32 uItemDataID, int32 nChangeType);

    int32_t GetNeedItemNum(int32 iMissionID, Lua_State* L, int32 itemId);

    BOOL QuestCheckSubmit(Player* pPlayer, int32 iMissionID, ObjID_t targetId, int32 InstIndex);
    int32_t QuestComplate(Player* pPlayer, GameMap* pMap, int32 iMissionID, ObjID_t targetId, int32 selId);
    void QuestBonusNotItem(Player* pPlayer, GameMap* pMap, int32 iMissionID, ScriptID_t nScriptId);
    int32_t QuestBonusItem(Player* pPlayer, GameMap* pMap, int32 iMissionID, int32 selId);
    //! 骑乘发生变化的任务处理
    void OnEvent_PetChanged(Player* pPlayer, uint32 uPetDataID);

    //! 向客户端发送XCScriptCommand消息，从表格读取任务信息并发送。
    void AddDispatchQuestInfo(Player* pPlayer, int32 iMissionID, ObjID_t targetId, int32 state);

    //! 玩家杀死怪物后的任务处理
    void OnEvent_KillObject(Player* pPlayer, Character* pObj);

    int32 GetItemIdInItemBox(Lua_State* L, int32 gpType, Player* pPlayer, int32 itemId);

    typedef FixedFlag<MAX_CHAR_QUEST_DATA_NUM> FlagMD;
    const FlagMD& getFlagMDClientFilter()
    {
        return m_FlagMDClientFilter;
    }
private:
    //! 加载所有任务表
    void LoadQuestList();

    //! 加载送信类型任务表
    void LoadDeliveryTable();

    //! 加载护送类型任务表
    void LoadEscortTable();

    //! 加载使用物品类型任务表
    void LoadUseItemTable();

    //! 加载获取物品类型任务表
    void LoadQuestLootItemTable();

    //! 加载杀怪类型任务表
    void LoadQuestKillMonsterTable();

    //! 加载进入区域类型任务表
    void LoadQuestEnterAreaTable();

    void initFlagMDClientFilter();
private:
    //! 杀怪任务表
	__QUEST_KILLMONSTER m_QuestKillMonsterTable;
    //! 送信任务表
	__QUEST_DELIVERY    m_QuestDeliveryTable;
    //! 护送任务表
    __QUEST_HUSONG      m_QuestEscortTable;
    //! 使用物品任务表
    __QUEST_USEITEM     m_QuestUseItemTable;

    //! 获取物品类型任务表
	__QUEST_LOOKITEM    m_QuestLookItemTable;

    //! 进入区域任务表
    __QUEST_ENTERAREA   m_QuestEnterAreaTable;

    FlagMD	m_FlagMDClientFilter;
};
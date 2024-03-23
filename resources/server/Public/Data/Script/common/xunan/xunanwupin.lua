x300752_g_scriptId  = 300752
x300752_g_Impact1   = -1 --效果ID
x300752_g_Impact2   = -1 --不用

x300752_g_MissionId 	= -1			--任务ID
x300752_g_ItemId 		= 12030107		--藏宝图ID
x300752_g_ScriptId 		= 300752		--脚本ID

x300752_g_UseSceneID1	= 50			--使用物品场景
x300752_g_UseSceneID2	= 150			--使用物品场景
x300752_g_UseSceneID3	= 250			--使用物品场景
x300752_g_UseSceneID4	= 350			--使用物品场景
x300752_g_UsePosX		= 198			--使用物品位置
x300752_g_UsePosZ		= 46


x300752_g_CreateMonsterID	= 9560;		--创建出来的怪ID
x300752_g_MonsterPos	= {{x = 185, z = 49},
						   {x = 184, z = 57},
						   {x = 190, z = 63},
						   {x = 198, z = 64},
						   {x = 205, z = 63},
						   {x = 214, z = 49},
						   {x = 214, z = 36},
						   {x = 201, z = 30},
						   {x = 190, z = 31},
						   {x = 187, z = 41}}
						   
x300752_g_GiveItemID	= 12110206;		--给玩家的物品ID
x300752_g_GiveExp		= 1000;			--给玩家的经验
x300752_g_GiveScriptID	= 300330;		--藏宝图任务的脚本ID
x300752_g_GiveMissionID	= 8050;			--藏宝图任务的任务ID


--**********************************
--事件交互入口
--**********************************
function x300752_ProcEventEntry( sceneId, selfId, bagIndex )
--SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x300752_g_Impact1, 0); --特效
    local playerLevel = GetLevel( sceneId, selfId)
    if playerLevel < 20 then
        BeginQuestEvent( sceneId)
        AddQuestText( sceneId,"你的等级太低，还无法领悟藏宝图的奥秘" )
        EndQuestEvent( sceneId)
        DispatchQuestTips( sceneId, selfId)
        Msg2Player( sceneId, selfId, "你的等级太低，还无法领悟藏宝图的奥秘！", 8, 2)
        return 0;
    end

    --DelQuest(sceneId, selfId, x300752_g_GiveMissionID)
	local x,z = GetWorldPos( sceneId, selfId)
    local bHaveMission	= IsHaveQuestNM( sceneId, selfId, x300752_g_GiveMissionID)
    if( bHaveMission > 0) then
        BeginQuestEvent( sceneId)
        AddQuestText( sceneId,"你已经有藏宝图任务了，无法重复领取！" )
        EndQuestEvent( sceneId)
        DispatchQuestTips( sceneId, selfId)
        Msg2Player( sceneId, selfId, "你已经有藏宝图任务了，无法重复领取！", 8, 2)
        return 0;
    end

    if IsQuestFullNM( sceneId, selfId) == 1 then
        Msg2Player( sceneId, selfId, "任务已满，任务接受失败", 8, 3)
        return 0
    end

    if DelItemByIndexInBag( sceneId, selfId, bagIndex, 1) == 0 then
        Msg2Player( sceneId, selfId, "打开藏宝图发生异常，无法查看其奥秘", 8, 3)
        return 0
    end

    --给任务
    if CallScriptFunction( x300752_g_GiveScriptID, "OnForceAddMission", sceneId, selfId, -1, x300752_g_GiveMissionID ) > 0 then
        -- 删除背包里的藏宝图
        --DelItemByIndexInBag( sceneId, selfId, bagIndex, 1)
		
		x300752_UpdateTopList(sceneId, selfId)
    end
    -- BeginQuestEvent(sceneId)
    -- AddQuestText(sceneId,"恭喜，您获得了【寻龙任务】！您可以通过Q键查询任务信息！")
    -- EndQuestEvent(sceneId)
    -- DispatchQuestTips(sceneId,selfId)
    -- local Readme = "恭喜，您获得了【寻龙任务】！您可以通过Q键查询任务信息！"
    -- Msg2Player(sceneId,selfId,Readme,8,2)

    return 1;
end

function x300752_UpdateTopList(sceneId,selfId)

	local lastday = GetQuestData( sceneId, selfId, MD_BAOZANG_DAY[1], MD_BAOZANG_DAY[2], MD_BAOZANG_DAY[3] )
	local curCount = GetQuestData( sceneId, selfId, MD_BAOZANG_COUNT[1], MD_BAOZANG_COUNT[2], MD_BAOZANG_COUNT[3] )
	local curday = GetWeekFirstDay()
	if lastday ~= curday then
		curCount = 0
	end
	curCount = curCount + 1
	SetQuestData( sceneId, selfId, MD_BAOZANG_COUNT[1], MD_BAOZANG_COUNT[2], MD_BAOZANG_COUNT[3], curCount )
	SetQuestData( sceneId, selfId, MD_BAOZANG_DAY[1], MD_BAOZANG_DAY[2], MD_BAOZANG_DAY[3], curday )
	
	SendToplistKeyValue2GL(sceneId, selfId, BAOZANG_TOPLIST, curCount)
	
end

function x300752_IsSkillLikeScript( sceneId, selfId)
 
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x300752_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x300752_OnConditionCheck( sceneId, selfId )
	return 0
end

function x300752_OnDeplete( sceneId, selfId )
	if DepletingUsedItem(sceneId, selfId) == 1 then
		return 1;
	end
	return 0
end

function x300752_OnActivateOnce( sceneId, selfId )
end

function x300752_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end


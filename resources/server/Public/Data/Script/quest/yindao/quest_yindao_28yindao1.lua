--引导任务--完成征税，内政，狩猎 各一次

--MisDescBegin
x203787_g_ScriptId = 203787
--x203787_g_MissionIdPre ={67,69,70,71}
x203787_g_MissionId = 4257
x203787_g_LevelLess	= 28 
x203787_g_MissionIdNext = -1
x203787_g_Name	={}
x203787_g_ExtTarget={{type=20,n=1,target="完成一整轮@npc_28801"}}
x203787_g_MissionName="【个人】王国内务"
x203787_g_MissionInfo="\t你好，亲爱的朋友，王国中有不少官员正在寻求人手帮忙，你可以去@npc_126041那里看看，当你将他的一整轮任务都完成后，我会好好的奖励你。"  --任务描述
x203787_g_MissionTarget=""		
x203787_g_MissionCompleted="\t看来你已经对王国内务了如指掌了。\n\t记得每天都去他那里看看，一定会对你有不少帮助。"					--完成任务npc说话的话
x203787_g_ContinueInfo="别太心急，我为你准备了不少礼物，但是......你应该先完成一轮内政任务。"
x203787_g_MissionHelp =	""
x203787_g_DemandItem ={}
x203787_g_ExpBonus = 500000
x203787_g_BonusMoney1 =5000
x203787_g_BonusMoney2 =0
x203787_g_BonusMoney3 =0
x203787_g_BonusMoney4 =0
x203787_g_BonusMoney5 =0
x203787_g_BonusMoney6 =0
x203787_g_BonusItem	=	{}
x203787_g_BonusChoiceItem ={}
x203787_g_NpcGUID ={{ guid = 126002, name = "万事通"} }
--MisDescEnd
--**********************************
-- 征税完成标记
--x203787_g_MP_Tax        = 1
-- 狩猎完成标记
--x203787_g_MP_Hunt       = 2
-- 内政完成标记
x203787_g_MP_Neizheng   = 3
-- 最大等级
x203787_g_MaxLevel      = 40

function x203787_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    local level = GetLevel(sceneId, selfId)
	if level < x203787_g_LevelLess or level >= x203787_g_MaxLevel then
		return
	end

	if IsQuestHaveDone(sceneId, selfId, x203787_g_MissionId) > 0 then
		return 
	end

	if IsHaveQuest(sceneId,selfId, x203787_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x203787_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x203787_g_MissionId, state, -1 )
	end
end

function x203787_DispatchMissionInfo( sceneId, selfId, NPCId )
    if x203787_g_ExpBonus> 0 then
        AddQuestExpBonus(sceneId, x203787_g_ExpBonus )
    end
    if x203787_g_BonusMoney1 > 0 then
        AddQuestMoneyBonus1(sceneId, x203787_g_BonusMoney1 )
    end
    if x203787_g_BonusMoney2 > 0 then
        AddQuestMoneyBonus2(sceneId, x203787_g_BonusMoney2 )
    end
    if x203787_g_BonusMoney3 > 0 then
        AddQuestMoneyBonus3(sceneId, x203787_g_BonusMoney3 )
    end
    if x203787_g_BonusMoney4 > 0 then
        AddQuestMoneyBonus4(sceneId, x203787_g_BonusMoney4 )
    end
    if x203787_g_BonusMoney5 > 0 then
        AddQuestMoneyBonus5(sceneId, x203787_g_BonusMoney5 )
    end
    if x203787_g_BonusMoney6 > 0 then
        AddQuestMoneyBonus6(sceneId, x203787_g_BonusMoney6 )
    end
    for i, item in x203787_g_BonusItem do
        AddQuestItemBonus(sceneId, item.item, item.n)
    end
    for i, item in x203787_g_BonusChoiceItem do
        AddQuestRadioItemBonus(sceneId, item.item, item.n)
    end
end

function x203787_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203787_g_MissionId) > 0 then
		return
	end
	if IsHaveQuest(sceneId,selfId, x203787_g_MissionId) > 0 then
        if x203787_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x203787_g_MissionName)
            AddQuestText(sceneId,x203787_g_ContinueInfo)
            EndQuestEvent()
            DispatchQuestEventList(sceneId, selfId, NPCId, x203787_g_ScriptId, x203787_g_MissionId);
        else
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x203787_g_MissionName)
            AddQuestText(sceneId,x203787_g_MissionCompleted)
            AddQuestText(sceneId," ")
            x203787_DispatchMissionInfo( sceneId, selfId, NPCId )
            EndQuestEvent()
            DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203787_g_ScriptId, x203787_g_MissionId);
        end
    elseif x203787_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"#Y"..x203787_g_MissionName)
        AddQuestText(sceneId,x203787_g_MissionInfo)
        AddQuestText( sceneId,"#Y任务目标：")
        for i, item in x203787_g_ExtTarget do
            AddQuestText( sceneId,item.target)
        end 
        if x203787_g_MissionHelp ~= "" then
            AddQuestText(sceneId,"\n#G小提示:#W")
            AddQuestText(sceneId,x203787_g_MissionHelp )
        end
        x203787_DispatchMissionInfo( sceneId, selfId, NPCId )
        EndQuestEvent()
        DispatchQuestInfoNM(sceneId, selfId, NPCId, x203787_g_ScriptId, x203787_g_MissionId);
    end
end

function x203787_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

function x203787_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x203787_g_MissionId)
	if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
	    return 1
	else
	    return 0
	end
end

function x203787_OnYinDaoCompleted( sceneId, selfId, nMode)   
	if nMode==nil then
		return
	end

	if IsHaveQuestNM( sceneId, selfId, x203787_g_MissionId ) == 0 then
		return
	end

	local misIndex = GetQuestIndexByID(sceneId,selfId,x203787_g_MissionId)  

	local n1 = GetQuestParam( sceneId, selfId, misIndex, 0 )	
	--local n2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	--local n3 = GetQuestParam( sceneId, selfId, misIndex, 2 )                                                

    if nMode ==0 then --内政
   		SetQuestByIndex(sceneId,selfId,misIndex,0,1)

   	--	if n2==1 and n3==1 then
   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   		end
   --	elseif nMode==1 then --征税
   --		SetQuestByIndex(sceneId,selfId,misIndex,1,1)
   --		if n1==1 and n3==1 then
   --			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   --		end
   --	elseif nMode==2 then	-- 狩猎
   --		SetQuestByIndex(sceneId,selfId,misIndex,2,1)
   --		if n1==1 and n2==1 then
   --			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   --		end
   --	end
end

function x203787_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
    if IsQuestHaveDone(sceneId, selfId, x203787_g_MissionId) > 0 then
        return 
    end
    if IsQuestFullNM(sceneId,selfId)==1 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"可接任务数量已满")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 
    end

    --检查前置任务
    local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203787_g_MissionId  )
    if FrontMissiontId1 ~= -1 then
        if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
            return 0
        end
    end
    if FrontMissiontId2 ~= -1 then
        if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
            return 0
        end
    end
    if FrontMissiontId3 ~= -1 then
        if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
            return 0
        end
    end

    if x203787_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        local retmiss = AddQuest( sceneId, selfId, x203787_g_MissionId, x203787_g_ScriptId, 0, 0, 0, 1)
        if retmiss ==0 then
            Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
            return 0
        else
            local misIndex = GetQuestIndexByID(sceneId,selfId,x203787_g_MissionId)                                                  
            x203787_Msg2toplayer( sceneId, selfId,0)
            --SetQuestByIndex(sceneId,selfId,misIndex,x203787_g_MP_Tax,0)
            --SetQuestByIndex(sceneId,selfId,misIndex,x203787_g_MP_Hunt,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x203787_g_MP_Neizheng,0)
            x203787_ProcQuestLogRefresh( sceneId, selfId, x203787_g_MissionId)
        end
    end                                                                    
end

function x203787_ProcQuestAbandon(sceneId, selfId, MissionId)
    if IsHaveQuest(sceneId,selfId, x203787_g_MissionId) <= 0 then
        return 
    end
    DelQuest( sceneId, selfId, x203787_g_MissionId)
    x203787_Msg2toplayer( sceneId, selfId, 1)
end

function x203787_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203787_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
    end
    for j, item in x203787_g_BonusChoiceItem do
        if item.item == selectRadioId then
            AddItem( sceneId, item.item, item.n )
            break
        end
    end
    local ret = EndAddItem(sceneId,selfId)
    if ret <= 0 then
        if result == 1 then
            result = 0
        end
    end
	return result
end

function x203787_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203787_g_MissionId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"您没有这个任务！")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x203787_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"您没有达到完成条件！")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x203787_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"背包空间不足，请清理后再来！")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif DelQuest(sceneId, selfId, x203787_g_MissionId) > 0 then
        x203787_Msg2toplayer( sceneId, selfId,2)
        QuestCom(sceneId, selfId, x203787_g_MissionId)
        x203787_GetBonus( sceneId, selfId,NPCId)
        BeginAddItem(sceneId)
        for i, item in x203787_g_BonusItem do
            AddBindItem( sceneId, item.item, item.n )
        end
        for i, item in x203787_g_BonusChoiceItem do
            if item.item == selectRadioId then
                AddItem( sceneId, item.item, item.n )
            end
        end
        EndAddItem(sceneId,selfId)
       -- AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203787_g_MissionIdNext )	
end

function x203787_GetBonus( sceneId, selfId,NpcID)
	if x203787_g_ExpBonus > 0 then
		AddExp(sceneId, selfId, x203787_g_ExpBonus);
  	end
	if x203787_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203787_g_BonusMoney1)
	end
    if x203787_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203787_g_BonusMoney2)
    end
    if x203787_g_BonusMoney3 > 0 then
        AddMoney( sceneId, selfId, 3, x203787_g_BonusMoney3)
    end
    if x203787_g_BonusMoney4 > 0 then
        local nRongYu = GetRongYu( sceneId, selfId )
        nRongYu = nRongYu + x203787_g_BonusMoney4
        SetRongYu( sceneId, selfId, nRongYu )
    end
    if x203787_g_BonusMoney5 > 0 then
        local nShengWang = GetShengWang( sceneId, selfId)
        nShengWang = nShengWang + x203787_g_BonusMoney5
        SetShengWang( sceneId, selfId, nShengWang )
    end
    if x203787_g_BonusMoney6 > 0 then
        AddHonor(sceneId,selfId,x203787_g_BonusMoney6)
    end
end

function x203787_Msg2toplayer( sceneId, selfId,type)
    if type == 0 then
        Msg2Player(sceneId, selfId, "您接受了任务"..x203787_g_MissionName.."！", 0, 2)
        Msg2Player(sceneId, selfId, "您接受了任务"..x203787_g_MissionName.."！", 0, 3)
    elseif type == 1 then
        Msg2Player(sceneId, selfId, "您放弃了任务"..x203787_g_MissionName.."！", 0, 2)
        Msg2Player(sceneId, selfId, "您放弃了任务"..x203787_g_MissionName.."！", 0, 3)
    elseif type == 2 then
        Msg2Player(sceneId, selfId, "您完成了任务"..x203787_g_MissionName.."！", 0, 2)
        Msg2Player(sceneId, selfId, "您完成了任务"..x203787_g_MissionName.."！", 0, 3)
        if x203787_g_ExpBonus > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R经验"..x203787_g_ExpBonus.."#Y的奖励", 0, 2)
        end
        if x203787_g_BonusMoney1 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x203787_g_BonusMoney1.."文#Y的奖励", 0, 2)
        end
        if x203787_g_BonusMoney2 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R现银"..x203787_g_BonusMoney2.."文#Y的奖励", 0, 2)
        end
        if x203787_g_BonusMoney3 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x203787_g_BonusMoney3.."文#Y的奖励", 0, 2)
        end
        if x203787_g_BonusMoney4 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x203787_g_BonusMoney4.."#Y的奖励", 0, 2)
        end
        if x203787_g_BonusMoney5 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R声望"..x203787_g_BonusMoney5.."#Y的奖励", 0, 2)
        end
        if x203787_g_BonusMoney6 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x203787_g_BonusMoney6.."#Y的奖励", 0, 2)
        end
    end
end

function x203787_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end

function x203787_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203787_ProcTiming(sceneId, selfId, ScriptId, MissionId)
    CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
end

function x203787_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203787_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end

function x203787_LevelUp( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x203787_g_MissionId) < 1 then
        return
    end

    -- 完成狩猎
    local misIndex = GetQuestIndexByID( sceneId, selfId, x203787_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x203787_g_MP_Hunt, 1)
    x203787_ProcQuestLogRefresh( sceneId, selfId, x203787_g_MissionId)
end

function x203787_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
    local bFind  = 0
    for i ,item in x203787_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
    if IsHaveQuest(sceneId,selfId, x203787_g_MissionId) > 0 then
        local state = GetQuestStateNM(sceneId,selfId,npcId,x203787_g_MissionId)
        AddQuestTextNM( sceneId, selfId, npcId, x203787_g_MissionId, state, -1 )
    end
end

function x203787_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203787_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203787_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203787_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203787_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203787_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x203787_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
    --local tax = GetQuestParam( sceneId, selfId, misIndex, x203787_g_MP_Tax)
    --local hunt = GetQuestParam( sceneId, selfId, misIndex, x203787_g_MP_Hunt)
    local neizheng = GetQuestParam( sceneId, selfId, misIndex, x203787_g_MP_Neizheng)
    local strTarget = format( "任务已经完成，请回报@npc_%d", x203787_g_NpcGUID[1].guid)

    if neizheng == 1 then
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
    else
        --if tax == 0 then
        --    strTarget = "  #W完成一整轮@npc_82057(0/1)\n"
        --else
        --    strTarget = "  #G完成一整轮@npc_82057(1/1)\n"
        --end
        --if hunt == 0 then
        --    strTarget = strTarget.."  #W完成一整轮@npc_82058(0/1)\n"
        --else
        --    strTarget = strTarget.."  #G完成一整轮@npc_82058(1/1)\n"
        --end
        if neizheng == 0 then
            strTarget = "  #W完成一整轮@npc_28801(0/1)"
        else
            strTarget = strTarget.."  #G完成一整轮@npc_28801(1/1)"
        end
    end

	BeginQuestEvent( sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                             -- 标题
                                x203787_g_MissionName,          -- 任务名字
                                strTarget,
                                "",                             --任务NPC
                                "去找@npc_126041，完成他发布的一整轮任务。",
                                "\t你好，亲爱的朋友，王国中有不少官员正在寻求人手帮忙，你可以去@npc_126041那里看看，当你将他的一整轮任务都完成后，我会好好的奖励你。",
                                "@npc_126041的任务是非常简单，回报高额的。"
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

-- 完成一轮征税
--function x203787_FinishTax( sceneId, selfId)
--    if IsHaveQuest( sceneId, selfId, x203787_g_MissionId) <= 0 then
--        return
--    end
--
--    local misIndex = GetQuestIndexByID( sceneId, selfId, x203787_g_MissionId)
--    SetQuestByIndex( sceneId, selfId, misIndex, x203787_g_MP_Tax, 1)
--
--    x203787_ProcQuestLogRefresh( sceneId, selfId, x203787_g_MissionId)
--end

-- 完成一轮狩猎
--function x203787_FinishHunt( sceneId, selfId)
--    if IsHaveQuest( sceneId, selfId, x203787_g_MissionId) <= 0 then
--        return
--    end
--
--    local misIndex = GetQuestIndexByID( sceneId, selfId, x203787_g_MissionId)
--    SetQuestByIndex( sceneId, selfId, misIndex, x203787_g_MP_Hunt, 1)
--
--    x203787_ProcQuestLogRefresh( sceneId, selfId, x203787_g_MissionId)
--end

-- 完成一轮内政
function x203787_FinishNeizheng( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x203787_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x203787_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x203787_g_MP_Neizheng, 1)

    x203787_ProcQuestLogRefresh( sceneId, selfId, x203787_g_MissionId)
end

--引导任务--完成官府押运，守边各一次

--MisDescBegin
x256223_g_ScriptId = 256223
--x256223_g_MissionIdPre ={67,69,70,71}
x256223_g_MissionId = 3114
x256223_g_LevelLess	= 33
x256223_g_MissionIdNext = -1
x256223_g_Name	={}
x256223_g_ExtTarget={{type=20,n=1,target="在#G国运令#W发布后完成一次@npc_82063"},{type=20,n=1,target="到边塞完成@npc_82064"},}
x256223_g_MissionName="【个人】国家押运和国家守边"
x256223_g_MissionInfo="\t时隔数日，亲爱的朋友我们又见面了，现在你的威名在王城可谓家喻户晓。\n\t这次@npc_138588和@npc_129700邀请你去帮助他们，我看你就不要推辞了，不过要小心，这些任务是有危险的。"  --任务描述
x256223_g_MissionTarget=""		
x256223_g_MissionCompleted="\t呵呵，这次你为我们的王国立了大功，做功臣的感觉如何啊？\n\t记得每天都去他们那里看看，一定会对你有不少帮助。"					--完成任务npc说话的话
x256223_g_ContinueInfo="\t年轻人做事有些急躁是难免的，做事要戒骄戒躁不要半途而废。"
x256223_g_MissionHelp =	""
x256223_g_DemandItem ={}
x256223_g_BonusMoney1 =10000
x256223_g_BonusMoney2 =0
x256223_g_BonusMoney3 =0
x256223_g_BonusMoney4 =0
x256223_g_BonusMoney5 =21
x256223_g_BonusMoney6 =0
x256223_g_BonusItem	=	{}
x256223_g_BonusChoiceItem ={}
x256223_g_ExpBonus = 85000
x256223_g_NpcGUID ={{ guid = 138575, name = "万事通"} }
--MisDescEnd
--**********************************
-- 押运完成标记
x256223_g_MP_Yayun       = 1
-- 守边完成标记
x256223_g_MP_Shoubian       = 2
-- 内政完成标记
-- x256223_g_MP_Neizheng   = 3
-- 最大等级
x256223_g_MaxLevel      = 160

function x256223_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    local level = GetLevel(sceneId, selfId)
	if level < x256223_g_LevelLess or level >= x256223_g_MaxLevel then
		return
	end

	if IsQuestHaveDone(sceneId, selfId, x256223_g_MissionId) > 0 then
		return 
	end

	if IsHaveQuest(sceneId,selfId, x256223_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x256223_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x256223_g_MissionId, state, -1 )
	end
end

function x256223_DispatchMissionInfo( sceneId, selfId, NPCId )
    if x256223_g_ExpBonus> 0 then
        AddQuestExpBonus(sceneId, x256223_g_ExpBonus )
    end
    if x256223_g_BonusMoney1 > 0 then
        AddQuestMoneyBonus1(sceneId, x256223_g_BonusMoney1 )
    end
    if x256223_g_BonusMoney2 > 0 then
        AddQuestMoneyBonus2(sceneId, x256223_g_BonusMoney2 )
    end
    if x256223_g_BonusMoney3 > 0 then
        AddQuestMoneyBonus3(sceneId, x256223_g_BonusMoney3 )
    end
    if x256223_g_BonusMoney4 > 0 then
        AddQuestMoneyBonus4(sceneId, x256223_g_BonusMoney4 )
    end
    if x256223_g_BonusMoney5 > 0 then
        AddQuestMoneyBonus5(sceneId, x256223_g_BonusMoney5 )
    end
    if x256223_g_BonusMoney6 > 0 then
        AddQuestMoneyBonus6(sceneId, x256223_g_BonusMoney6 )
    end
    for i, item in x256223_g_BonusItem do
        AddQuestItemBonus(sceneId, item.item, item.n)
    end
    for i, item in x256223_g_BonusChoiceItem do
        AddQuestRadioItemBonus(sceneId, item.item, item.n)
    end
end

function x256223_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x256223_g_MissionId) > 0 then
		return
	end
	if IsHaveQuest(sceneId,selfId, x256223_g_MissionId) > 0 then
        if x256223_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x256223_g_MissionName)
            AddQuestText(sceneId,x256223_g_ContinueInfo)
            EndQuestEvent()
            DispatchQuestEventList(sceneId, selfId, NPCId, x256223_g_ScriptId, x256223_g_MissionId);
        else
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x256223_g_MissionName)
            AddQuestText(sceneId,x256223_g_MissionCompleted)
            AddQuestText(sceneId," ")
            x256223_DispatchMissionInfo( sceneId, selfId, NPCId )
            EndQuestEvent()
            DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256223_g_ScriptId, x256223_g_MissionId);
        end
    elseif x256223_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"#Y"..x256223_g_MissionName)
        AddQuestText(sceneId,x256223_g_MissionInfo)
        AddQuestText( sceneId,"#Y任务目标：")
        for i, item in x256223_g_ExtTarget do
            AddQuestText( sceneId,item.target)
        end 
        if x256223_g_MissionHelp ~= "" then
            AddQuestText(sceneId,"\n#G小提示:#W")
            AddQuestText(sceneId,x256223_g_MissionHelp )
        end
        x256223_DispatchMissionInfo( sceneId, selfId, NPCId )
        EndQuestEvent()
        DispatchQuestInfoNM(sceneId, selfId, NPCId, x256223_g_ScriptId, x256223_g_MissionId);
    end
end

function x256223_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

function x256223_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x256223_g_MissionId)
	if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
	    return 1
	else
	    return 0
	end
end

function x256223_OnYinDaoCompleted( sceneId, selfId, nMode)   
	if nMode==nil then
		return
	end

	if IsHaveQuestNM( sceneId, selfId, x256223_g_MissionId ) == 0 then
		return
	end

	local misIndex = GetQuestIndexByID(sceneId,selfId,x256223_g_MissionId)  

	local n1 = GetQuestParam( sceneId, selfId, misIndex, 0 )	
	local n2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	--local n3 = GetQuestParam( sceneId, selfId, misIndex, 2 )                                                

    if nMode ==0 then --押运
   		SetQuestByIndex(sceneId,selfId,misIndex,0,1)

   		if n2==1 and n3==1 then
   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   		end
   	elseif nMode==1 then --守边
   		SetQuestByIndex(sceneId,selfId,misIndex,1,1)
   		if n1==1 and n3==1 then
   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   		end
   --	elseif nMode==2 then	-- 狩猎
   	--	SetQuestByIndex(sceneId,selfId,misIndex,2,1)
   		--if n1==1 and n2==1 then
   		--	SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   	--	end
   	end
end

function x256223_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
    if IsQuestHaveDone(sceneId, selfId, x256223_g_MissionId) > 0 then
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
    local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256223_g_MissionId  )
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

    if x256223_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        local retmiss = AddQuest( sceneId, selfId, x256223_g_MissionId, x256223_g_ScriptId, 0, 0, 0, 1)
        if retmiss ==0 then
            Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
            return 0
        else
            local misIndex = GetQuestIndexByID(sceneId,selfId,x256223_g_MissionId)                                                  
            x256223_Msg2toplayer( sceneId, selfId,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256223_g_MP_Yayun,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256223_g_MP_Shoubian,0)
            --SetQuestByIndex(sceneId,selfId,misIndex,x256223_g_MP_Neizheng,0)
            x256223_ProcQuestLogRefresh( sceneId, selfId, x256223_g_MissionId)
        end
    end                                                                    
end

function x256223_ProcQuestAbandon(sceneId, selfId, MissionId)
    if IsHaveQuest(sceneId,selfId, x256223_g_MissionId) <= 0 then
        return 
    end
    DelQuest( sceneId, selfId, x256223_g_MissionId)
    x256223_Msg2toplayer( sceneId, selfId, 1)
end

function x256223_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x256223_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
    end
    for j, item in x256223_g_BonusChoiceItem do
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

function x256223_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256223_g_MissionId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"您没有这个任务！")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x256223_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"您没有达到完成条件！")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x256223_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"背包空间不足，请清理后再来！")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif DelQuest(sceneId, selfId, x256223_g_MissionId) > 0 then
        x256223_Msg2toplayer( sceneId, selfId,2)
        QuestCom(sceneId, selfId, x256223_g_MissionId)
        x256223_GetBonus( sceneId, selfId,NPCId)
        BeginAddItem(sceneId)
        for i, item in x256223_g_BonusItem do
            AddBindItem( sceneId, item.item, item.n )
        end
        for i, item in x256223_g_BonusChoiceItem do
            if item.item == selectRadioId then
                AddItem( sceneId, item.item, item.n )
            end
        end
        EndAddItem(sceneId,selfId)
       -- AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256223_g_MissionIdNext )	
end

function x256223_GetBonus( sceneId, selfId,NpcID)
	if x256223_g_ExpBonus > 0 then
		AddExp(sceneId, selfId, x256223_g_ExpBonus);
  	end
	if x256223_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256223_g_BonusMoney1)
	end
    if x256223_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256223_g_BonusMoney2)
    end
    if x256223_g_BonusMoney3 > 0 then
        AddMoney( sceneId, selfId, 3, x256223_g_BonusMoney3)
    end
    if x256223_g_BonusMoney4 > 0 then
        local nRongYu = GetRongYu( sceneId, selfId )
        nRongYu = nRongYu + x256223_g_BonusMoney4
        SetRongYu( sceneId, selfId, nRongYu )
    end
    if x256223_g_BonusMoney5 > 0 then
        local nShengWang = GetShengWang( sceneId, selfId)
        nShengWang = nShengWang + x256223_g_BonusMoney5
        SetShengWang( sceneId, selfId, nShengWang )
    end
    if x256223_g_BonusMoney6 > 0 then
        AddHonor(sceneId,selfId,x256223_g_BonusMoney6)
    end
end

function x256223_Msg2toplayer( sceneId, selfId,type)
    if type == 0 then
        Msg2Player(sceneId, selfId, "您接受了任务："..x256223_g_MissionName.."！", 0, 2)
        Msg2Player(sceneId, selfId, "您接受了任务："..x256223_g_MissionName.."！", 0, 3)
    elseif type == 1 then
        Msg2Player(sceneId, selfId, "您放弃了任务："..x256223_g_MissionName.."！", 0, 2)
        Msg2Player(sceneId, selfId, "您放弃了任务："..x256223_g_MissionName.."！", 0, 3)
    elseif type == 2 then
        Msg2Player(sceneId, selfId, "您完成了任务"..x256223_g_MissionName.."！", 0, 2)
        Msg2Player(sceneId, selfId, "您完成了任务"..x256223_g_MissionName.."！", 0, 3)
        if x256223_g_ExpBonus > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R经验"..x256223_g_ExpBonus.."#Y的奖励", 0, 2)
        end
        if x256223_g_BonusMoney1 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x256223_g_BonusMoney1.."文#Y的奖励", 0, 2)
        end
        if x256223_g_BonusMoney2 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R现银"..x256223_g_BonusMoney2.."文#Y的奖励", 0, 2)
        end
        if x256223_g_BonusMoney3 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x256223_g_BonusMoney3.."文#Y的奖励", 0, 2)
        end
        if x256223_g_BonusMoney4 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x256223_g_BonusMoney4.."#Y的奖励", 0, 2)
        end
        if x256223_g_BonusMoney5 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R声望"..x256223_g_BonusMoney5.."#Y的奖励", 0, 2)
        end
        if x256223_g_BonusMoney6 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x256223_g_BonusMoney6.."#Y的奖励", 0, 2)
        end
    end
end

function x256223_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end

function x256223_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256223_ProcTiming(sceneId, selfId, ScriptId, MissionId)
    CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
end

function x256223_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256223_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end

function x256223_LevelUp( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256223_g_MissionId) < 1 then
        return
    end

    -- 完成狩猎
     -- local misIndex = GetQuestIndexByID( sceneId, selfId, x256223_g_MissionId)
     -- SetQuestByIndex( sceneId, selfId, misIndex, x256223_g_MP_Shoubian, 1)
     -- x256223_ProcQuestLogRefresh( sceneId, selfId, x256223_g_MissionId)
end

function x256223_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
    local bFind  = 0
    for i ,item in x256223_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
    if IsHaveQuest(sceneId,selfId, x256223_g_MissionId) > 0 then
        local state = GetQuestStateNM(sceneId,selfId,npcId,x256223_g_MissionId)
        AddQuestTextNM( sceneId, selfId, npcId, x256223_g_MissionId, state, -1 )
    end
end

function x256223_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	--return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256223_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	--return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256223_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	--return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256223_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	--return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256223_OnProcOver( sceneId, selfId, targetId )
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256223_OpenCheck( sceneId, selfId, targetId )
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x256223_ProcQuestLogRefresh( sceneId, selfId, MissionId)

    if IsHaveQuest( sceneId, selfId, x256223_g_MissionId) <= 0 then
        return
    end
    
    local misIndex = GetQuestIndexByID( sceneId, selfId, x256223_g_MissionId)
    local Yayun= GetQuestParam( sceneId, selfId, misIndex, x256223_g_MP_Yayun)
    local Shoubian = GetQuestParam( sceneId, selfId, misIndex, x256223_g_MP_Shoubian)
    --local neizheng = GetQuestParam( sceneId, selfId, misIndex, x256223_g_MP_Neizheng)
    local strTarget = format( "任务已经完成，请回报@npc_%d", x256223_g_NpcGUID[1].guid)

    if Yayun== 1 and Shoubian == 1 then
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
    else
        if Yayun== 0 then
            strTarget = "  #W在国运令发布后完成一次@npc_82063(0/1)\n"
        else
            strTarget = "  #G在国运令发布后完成一次@npc_82063(1/1)\n"
        end
        if Shoubian == 0 then
            strTarget = strTarget.."  #W到边塞完成@npc_82064(0/1)\n"
        else
            strTarget = strTarget.."  #G到边塞完成@npc_82064(1/1)\n"
        end
       -- if neizheng == 0 then
      --      strTarget = strTarget.."  #W完成一整轮@npc_82056(0/1)\n"
       -- else
       --     strTarget = strTarget.."  #G完成一整轮@npc_82056(1/1)\n"
      --  end
    end

	BeginQuestEvent( sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                             -- 标题
                                x256223_g_MissionName,          -- 任务名字
                                strTarget,
                                "",                             --任务NPC
                                "去@npc_138588和@npc_129700处，完成他们发布的任务。",
                                "\t时隔数日，亲爱的朋友我们又见面了，现在你的威名在王城可谓家喻户晓。\n\t这次@npc_138588和@npc_129700邀请你去帮助他们，我看你就不要推辞了，不过要小心这些任务是有危险的。",
                                "@npc_138588和@npc_129700的任务都有些危险，注意安全。"
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

-- 完成一轮押运
function x256223_FinishYayun( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256223_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256223_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256223_g_MP_Yayun, 1)

    x256223_ProcQuestLogRefresh( sceneId, selfId, x256223_g_MissionId)
end

-- 完成一轮守边
function x256223_FinishShoubian( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256223_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256223_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256223_g_MP_Shoubian, 1)

    x256223_ProcQuestLogRefresh( sceneId, selfId, x256223_g_MissionId)
end

-- 完成一轮内政
-- function x256223_FinishNeizheng( sceneId, selfId)
--     if IsHaveQuest( sceneId, selfId, x256223_g_MissionId) <= 0 then
 --        return
--     end

--     local misIndex = GetQuestIndexByID( sceneId, selfId, x256223_g_MissionId)
 --    SetQuestByIndex( sceneId, selfId, misIndex, x256223_g_MP_Neizheng, 1)

 --    x256223_ProcQuestLogRefresh( sceneId, selfId, x256223_g_MissionId)
-- end

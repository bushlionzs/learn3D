--引导任务--完成赵王府斗戏，四大法王，生死财神，相国寺比武各一次

--MisDescBegin
x256225_g_ScriptId = 256225
--x256225_g_MissionIdPre ={67,69,70,71}
x256225_g_MissionId = 3112
x256225_g_LevelLess	= 40 
x256225_g_MissionIdNext = -1
x256225_g_Name	={}
x256225_g_ExtTarget={{type=20,n=1,target="完成一次@npc_28832"},{type=20,n=1,target="完成一次@npc_28833"},{type=20,n=1,target="完成一次@npc_28834"},{type=20,n=1,target="完成一次@npc_28835"},}
x256225_g_MissionName="【个人】大都的收获"
x256225_g_MissionInfo="\t大都是四方宾客汇聚之地，每天都有很多事发生。你可以去@npc_139084，@npc_139115，@npc_139083和@npc_139116他们那里看看，这些都是阔绰之人，帮他们做事收获必然丰厚。"  --任务描述
x256225_g_MissionTarget=""		
x256225_g_MissionCompleted="\t不错，不错，结识了这些能人义士将来必对你有所帮助。\n\t我没有骗你吧，他们的奖励我想你应该很满意，每天常去他们那里走走都会有收获的。"					--完成任务npc说话的话
x256225_g_ContinueInfo="\t别太心急，做事就要每一步迈的坚实，遇到挫折不要紧，努一把力就会完成的。"
x256225_g_MissionHelp =	""
x256225_g_DemandItem ={}
x256225_g_BonusMoney1 =8000
x256225_g_BonusMoney2 =0
x256225_g_BonusMoney3 =0
x256225_g_BonusMoney4 =0
x256225_g_BonusMoney5 =500
x256225_g_BonusMoney6 =0
x256225_g_BonusItem	=	{{item=11050002,n=3},{item=11000201,n=3},}
x256225_g_BonusChoiceItem ={}
x256225_g_ExpBonus = 30000
x256225_g_NpcGUID ={{ guid = 140417, name = "包打听"} }
--MisDescEnd
--**********************************
-- 征税完成标记
x256225_g_MP_douxi   = 1
-- 狩猎完成标记
x256225_g_MP_fawang  = 2
-- 内政完成标记
x256225_g_MP_caishen  = 3
-- 内政完成标记
x256225_g_MP_biwu   = 4
-- 最大等级
x256225_g_MaxLevel   = 160

function x256225_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    local level = GetLevel(sceneId, selfId)
	if level < x256225_g_LevelLess or level >= x256225_g_MaxLevel then
		return
	end

	if IsQuestHaveDone(sceneId, selfId, x256225_g_MissionId) > 0 then
		return 
	end

	if IsHaveQuest(sceneId,selfId, x256225_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x256225_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x256225_g_MissionId, state, -1 )
	end
end

function x256225_DispatchMissionInfo( sceneId, selfId, NPCId )
    if x256225_g_ExpBonus> 0 then
        AddQuestExpBonus(sceneId, x256225_g_ExpBonus )
    end
    if x256225_g_BonusMoney1 > 0 then
        AddQuestMoneyBonus1(sceneId, x256225_g_BonusMoney1 )
    end
    if x256225_g_BonusMoney2 > 0 then
        AddQuestMoneyBonus2(sceneId, x256225_g_BonusMoney2 )
    end
    if x256225_g_BonusMoney3 > 0 then
        AddQuestMoneyBonus3(sceneId, x256225_g_BonusMoney3 )
    end
    if x256225_g_BonusMoney4 > 0 then
        AddQuestMoneyBonus4(sceneId, x256225_g_BonusMoney4 )
    end
    if x256225_g_BonusMoney5 > 0 then
        AddQuestMoneyBonus5(sceneId, x256225_g_BonusMoney5 )
    end
    if x256225_g_BonusMoney6 > 0 then
        AddQuestMoneyBonus6(sceneId, x256225_g_BonusMoney6 )
    end
    for i, item in x256225_g_BonusItem do
        AddQuestItemBonus(sceneId, item.item, item.n)
    end
    for i, item in x256225_g_BonusChoiceItem do
        AddQuestRadioItemBonus(sceneId, item.item, item.n)
    end
end

function x256225_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x256225_g_MissionId) > 0 then
		return
	end
	if IsHaveQuest(sceneId,selfId, x256225_g_MissionId) > 0 then
        if x256225_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x256225_g_MissionName)
            AddQuestText(sceneId,x256225_g_ContinueInfo)
            EndQuestEvent()
            DispatchQuestEventList(sceneId, selfId, NPCId, x256225_g_ScriptId, x256225_g_MissionId);
        else
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x256225_g_MissionName)
            AddQuestText(sceneId,x256225_g_MissionCompleted)
            AddQuestText(sceneId," ")
            x256225_DispatchMissionInfo( sceneId, selfId, NPCId )
            EndQuestEvent()
            DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256225_g_ScriptId, x256225_g_MissionId);
        end
    elseif x256225_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"#Y"..x256225_g_MissionName)
        AddQuestText(sceneId,x256225_g_MissionInfo)
        AddQuestText( sceneId,"#Y任务目标：")
        for i, item in x256225_g_ExtTarget do
            AddQuestText( sceneId,item.target)
        end 
        if x256225_g_MissionHelp ~= "" then
            AddQuestText(sceneId,"\n#G小提示:#W")
            AddQuestText(sceneId,x256225_g_MissionHelp )
        end
        x256225_DispatchMissionInfo( sceneId, selfId, NPCId )
        EndQuestEvent()
        DispatchQuestInfoNM(sceneId, selfId, NPCId, x256225_g_ScriptId, x256225_g_MissionId);
    end
end

function x256225_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

function x256225_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x256225_g_MissionId)
	if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
	    return 1
	else
	    return 0
	end
end

function x256225_OnYinDaoCompleted( sceneId, selfId, nMode)   
	if nMode==nil then
		return
	end

	if IsHaveQuestNM( sceneId, selfId, x256225_g_MissionId ) == 0 then
		return
	end

	local misIndex = GetQuestIndexByID(sceneId,selfId,x256225_g_MissionId)  

	local n1 = GetQuestParam( sceneId, selfId, misIndex, 0 )	
	local n2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local n3 = GetQuestParam( sceneId, selfId, misIndex, 2 )
	local n4 = GetQuestParam( sceneId, selfId, misIndex, 3 )                                                

    if nMode ==0 then --内政
   		SetQuestByIndex(sceneId,selfId,misIndex,0,1)

   		if n2==1 and n3==1 and n4==1 then
   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   		end
   	elseif nMode==1 then --征税
   		SetQuestByIndex(sceneId,selfId,misIndex,1,1)
   		if n1==1 and n3==1 and n4==1 then
   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   		end
   	elseif nMode==2 then	-- 狩猎
   		SetQuestByIndex(sceneId,selfId,misIndex,2,1)
   		if n1==1 and n2==1 and n4==1 then
   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   		end
   	elseif nMode==3 then --征税
   		SetQuestByIndex(sceneId,selfId,misIndex,3,1)
   		if n1==1 and n2==1 and n3==1 then
   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   		end
   	end
end

function x256225_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
    if IsQuestHaveDone(sceneId, selfId, x256225_g_MissionId) > 0 then
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
    local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3	= GetFrontQuestIdNM( sceneId, selfId,x256225_g_MissionId  )
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


    if x256225_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        local retmiss = AddQuest( sceneId, selfId, x256225_g_MissionId, x256225_g_ScriptId, 0, 0, 0, 1)
        if retmiss ==0 then
            Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
            return 0
        else
            local misIndex = GetQuestIndexByID(sceneId,selfId,x256225_g_MissionId)                                                  
            x256225_Msg2toplayer( sceneId, selfId,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256225_g_MP_douxi,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256225_g_MP_fawang,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256225_g_MP_caishen,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256225_g_MP_biwu,0)
            x256225_ProcQuestLogRefresh( sceneId, selfId, x256225_g_MissionId)
        end
    end                                                                    
end

function x256225_ProcQuestAbandon(sceneId, selfId, MissionId)
    if IsHaveQuest(sceneId,selfId, x256225_g_MissionId) <= 0 then
        return 
    end
    DelQuest( sceneId, selfId, x256225_g_MissionId)
    x256225_Msg2toplayer( sceneId, selfId, 1)
end

function x256225_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x256225_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
    end
    for j, item in x256225_g_BonusChoiceItem do
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

function x256225_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256225_g_MissionId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"您没有这个任务！")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x256225_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"您没有达到完成条件！")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x256225_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"背包空间不足，请清理后再来！")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif DelQuest(sceneId, selfId, x256225_g_MissionId) > 0 then
        x256225_Msg2toplayer( sceneId, selfId,2)
        QuestCom(sceneId, selfId, x256225_g_MissionId)
        x256225_GetBonus( sceneId, selfId,NPCId)
        BeginAddItem(sceneId)
        for i, item in x256225_g_BonusItem do
            AddBindItem( sceneId, item.item, item.n )
        end
        for i, item in x256225_g_BonusChoiceItem do
            if item.item == selectRadioId then
                AddItem( sceneId, item.item, item.n )
            end
        end
        EndAddItem(sceneId,selfId)
        AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256225_g_MissionIdNext )	
end

function x256225_GetBonus( sceneId, selfId,NpcID)
	if x256225_g_ExpBonus > 0 then
		AddExp(sceneId, selfId, x256225_g_ExpBonus);
  	end
	if x256225_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256225_g_BonusMoney1)
	end
    if x256225_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256225_g_BonusMoney2)
    end
    if x256225_g_BonusMoney3 > 0 then
        AddMoney( sceneId, selfId, 3, x256225_g_BonusMoney3)
    end
    if x256225_g_BonusMoney4 > 0 then
        local nRongYu = GetRongYu( sceneId, selfId )
        nRongYu = nRongYu + x256225_g_BonusMoney4
        SetRongYu( sceneId, selfId, nRongYu )
    end
    if x256225_g_BonusMoney5 > 0 then
        local nShengWang = GetShengWang( sceneId, selfId)
        nShengWang = nShengWang + x256225_g_BonusMoney5
        SetShengWang( sceneId, selfId, nShengWang )
    end
    if x256225_g_BonusMoney6 > 0 then
        AddHonor(sceneId,selfId,x256225_g_BonusMoney6)
    end
end

function x256225_Msg2toplayer( sceneId, selfId,type)
    if type == 0 then
        Msg2Player(sceneId, selfId, "您接受了任务："..x256225_g_MissionName.."！", 0, 2)
        Msg2Player(sceneId, selfId, "您接受了任务："..x256225_g_MissionName.."！", 0, 3)
    elseif type == 1 then
        Msg2Player(sceneId, selfId, "您放弃了任务："..x256225_g_MissionName.."！", 0, 2)
        Msg2Player(sceneId, selfId, "您放弃了任务："..x256225_g_MissionName.."！", 0, 3)
    elseif type == 2 then
        Msg2Player(sceneId, selfId, "您完成了任务"..x256225_g_MissionName.."！", 0, 2)
        Msg2Player(sceneId, selfId, "您完成了任务"..x256225_g_MissionName.."！", 0, 3)
        if x256225_g_ExpBonus > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R经验"..x256225_g_ExpBonus.."#Y的奖励", 0, 2)
        end
        if x256225_g_BonusMoney1 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x256225_g_BonusMoney1.."文#Y的奖励", 0, 2)
        end
        if x256225_g_BonusMoney2 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R现银"..x256225_g_BonusMoney2.."文#Y的奖励", 0, 2)
        end
        if x256225_g_BonusMoney3 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x256225_g_BonusMoney3.."文#Y的奖励", 0, 2)
        end
        if x256225_g_BonusMoney4 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x256225_g_BonusMoney4.."#Y的奖励", 0, 2)
        end
        if x256225_g_BonusMoney5 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R声望"..x256225_g_BonusMoney5.."#Y的奖励", 0, 2)
        end
        if x256225_g_BonusMoney6 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x256225_g_BonusMoney6.."#Y的奖励", 0, 2)
        end
    end
end

function x256225_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end

function x256225_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256225_ProcTiming(sceneId, selfId, ScriptId, MissionId)
    CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
end

function x256225_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256225_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end

function x256225_LevelUp( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256225_g_MissionId) < 1 then
        return
    end

    -- 完成狩猎
    local misIndex = GetQuestIndexByID( sceneId, selfId, x256225_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256225_g_MP_fawang, 1)
    x256225_ProcQuestLogRefresh( sceneId, selfId, x256225_g_MissionId)
end

function x256225_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
    local bFind  = 0
    for i ,item in x256225_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
    if IsHaveQuest(sceneId,selfId, x256225_g_MissionId) > 0 then
        local state = GetQuestStateNM(sceneId,selfId,npcId,x256225_g_MissionId)
        AddQuestTextNM( sceneId, selfId, npcId, x256225_g_MissionId, state, -1 )
    end
end

function x256225_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	--return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256225_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	--return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256225_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	--return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256225_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	--return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256225_OnProcOver( sceneId, selfId, targetId )
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256225_OpenCheck( sceneId, selfId, targetId )
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x256225_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    if IsHaveQuest( sceneId, selfId, x256225_g_MissionId) <= 0 then
        return
    end
    
    local misIndex = GetQuestIndexByID( sceneId, selfId, x256225_g_MissionId)
    local douxi = GetQuestParam( sceneId, selfId, misIndex, x256225_g_MP_douxi)
    local fawang= GetQuestParam( sceneId, selfId, misIndex, x256225_g_MP_fawang)
    local caishen = GetQuestParam( sceneId, selfId, misIndex, x256225_g_MP_caishen)
    local biwu= GetQuestParam( sceneId, selfId, misIndex, x256225_g_MP_biwu)
    local strTarget = format( "任务已经完成，请回报@npc_%d", x256225_g_NpcGUID[1].guid)

    if douxi == 1 and fawang== 1 and caishen == 1 and biwu== 1 then
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
    else
        if douxi == 0 then
            strTarget = "  #W完成一次@npc_28832(0/1)\n"
        else
            strTarget = "  #G完成一次@npc_28832(1/1)\n"
        end
        if fawang== 0 then
            strTarget = strTarget.."  #W完成一次@npc_28833(0/1)\n"
        else
            strTarget = strTarget.."  #G完成一次@npc_28833(1/1)\n"
        end
        if caishen == 0 then
            strTarget = strTarget.."  #W完成一次@npc_28834(0/1)\n"
        else
            strTarget = strTarget.."  #G完成一次@npc_28834(1/1)\n"
        end
        if biwu== 0 then
            strTarget = strTarget.."  #W完成一次@npc_28835(0/1)"
        else
            strTarget = strTarget.."  #G完成一次@npc_28835(1/1)"
        end
    end

	BeginQuestEvent( sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                             -- 标题
                                x256225_g_MissionName,          -- 任务名字
                                strTarget,
                                "",                             --任务NPC
                                "去@npc_139084，@npc_139115，@npc_139083和@npc_139116处，完成的他们吩咐的事情。",
                                "\t大都是四方宾客汇聚之地，每天都有很多事发生。你可以去@npc_139084，@npc_139115，@npc_139083和@npc_139116他们那里看看，这些都是阔绰之人，帮他们做事收获必然丰厚。",
                                "@npc_139084，@npc_139115，@npc_139083和@npc_139116要你完成任务都是回报丰厚。"
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

-- 完成一轮征税
function x256225_Finishdouxi( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256225_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256225_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256225_g_MP_douxi, 1)

    x256225_ProcQuestLogRefresh( sceneId, selfId, x256225_g_MissionId)
end

-- 完成一轮狩猎
function x256225_Finishfawang( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256225_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256225_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256225_g_MP_fawang, 1)

    x256225_ProcQuestLogRefresh( sceneId, selfId, x256225_g_MissionId)
end

-- 完成一轮内政
function x256225_Finishcaishen( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256225_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256225_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256225_g_MP_caishen, 1)

    x256225_ProcQuestLogRefresh( sceneId, selfId, x256225_g_MissionId)
end
-- 完成一轮内政
function x256225_Finishbiwu( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256225_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256225_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256225_g_MP_biwu, 1)

    x256225_ProcQuestLogRefresh( sceneId, selfId, x256225_g_MissionId)
end
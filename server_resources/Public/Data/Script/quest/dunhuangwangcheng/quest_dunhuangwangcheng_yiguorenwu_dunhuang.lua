--引导任务--完成异国任务各一次

--MisDescBegin
x256271_g_ScriptId = 256271
x256271_g_MissionIdPre = 2627
x256271_g_MissionId = 2611
x256271_g_LevelLess	= 40
x256271_g_MissionIdNext = -1
x256271_g_Name	={}
x256271_g_ExtTarget={{type=20,n=1,target="@npc_28824"},{type=20,n=1,target="@npc_28825"},{type=20,n=1,target="@npc_28826"},{type=20,n=1,target="@npc_28827"},}
x256271_g_MissionName="【个人】国家使命"
x256271_g_MissionInfo="\t我等你很久了，到了你这样的修为的人，应该开始为国家尽一份力了。\n\t找到@npc_134502，@npc_134503，@npc_134504，@npc_134505完成他们所交代的任务，你会获得丰厚的奖励。"  --任务描述
x256271_g_MissionTarget=""		
x256271_g_MissionCompleted="\t这等为国效力的事，乃是我等臣民应尽之责。\n\t记得每天都去他们那里完成任务，臣民百姓会记得你，你的奖励也不会少。"					--完成任务npc说话的话
x256271_g_ContinueInfo="\t失败不可怕，可怕的是你自此丧失斗志。"
x256271_g_MissionHelp =	""
x256271_g_DemandItem ={}
x256271_g_ExpBonus = 55000
x256271_g_BonusMoney1 =5000
x256271_g_BonusMoney2 =0
x256271_g_BonusMoney3 =0
x256271_g_BonusMoney4 =0
x256271_g_BonusMoney5 =200
x256271_g_BonusMoney6 =0
x256271_g_BonusItem	=	{}
x256271_g_BonusChoiceItem ={}
x256271_g_NpcGUID ={{ guid = 134552, name = "狄岚枫"} }
--MisDescEnd
--**********************************
-- 异国刺杀完成标记
x256271_g_MP_cisha  = 1
-- 夺旗完成标记
x256271_g_MP_duoqi   = 2
-- 除奸完成标记
x256271_g_MP_chujian  = 3
-- 情报完成标记
x256271_g_MP_qingbao  = 4
-- 最大等级
x256271_g_MaxLevel   = 55

function x256271_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

    local level = GetLevel(sceneId, selfId)
	if level < x256271_g_LevelLess or level >= x256271_g_MaxLevel then
		return
	end

	if IsQuestHaveDone(sceneId, selfId, x256271_g_MissionId) > 0 then
		return 
	end
	
  if IsQuestHaveDone(sceneId, selfId, x256271_g_MissionIdPre)> 0 then 
	if IsHaveQuest(sceneId,selfId, x256271_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x256271_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x256271_g_MissionId, state, -1 )
	end
	end
end

function x256271_DispatchMissionInfo( sceneId, selfId, NPCId )
    if x256271_g_ExpBonus> 0 then
        AddQuestExpBonus(sceneId, x256271_g_ExpBonus )
    end
    if x256271_g_BonusMoney1 > 0 then
        AddQuestMoneyBonus1(sceneId, x256271_g_BonusMoney1 )
    end
    if x256271_g_BonusMoney2 > 0 then
        AddQuestMoneyBonus2(sceneId, x256271_g_BonusMoney2 )
    end
    if x256271_g_BonusMoney3 > 0 then
        AddQuestMoneyBonus3(sceneId, x256271_g_BonusMoney3 )
    end
    if x256271_g_BonusMoney4 > 0 then
        AddQuestMoneyBonus4(sceneId, x256271_g_BonusMoney4 )
    end
    if x256271_g_BonusMoney5 > 0 then
        AddQuestMoneyBonus5(sceneId, x256271_g_BonusMoney5 )
    end
    if x256271_g_BonusMoney6 > 0 then
        AddQuestMoneyBonus6(sceneId, x256271_g_BonusMoney6 )
    end
    for i, item in x256271_g_BonusItem do
        AddQuestItemBonus(sceneId, item.item, item.n)
    end
    for i, item in x256271_g_BonusChoiceItem do
       AddQuestRadioItemBonus(sceneId, item.item, item.n)
    end
end

function x256271_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x256271_g_MissionId) > 0 then
		return
	end
	if IsHaveQuest(sceneId,selfId, x256271_g_MissionId) > 0 then
        if x256271_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x256271_g_MissionName)
            AddQuestText(sceneId,x256271_g_ContinueInfo)
            EndQuestEvent()
            DispatchQuestEventList(sceneId, selfId, NPCId, x256271_g_ScriptId, x256271_g_MissionId);
        else
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x256271_g_MissionName)
            AddQuestText(sceneId,x256271_g_MissionCompleted)
            AddQuestText(sceneId," ")
            x256271_DispatchMissionInfo( sceneId, selfId, NPCId )
            EndQuestEvent()
            DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256271_g_ScriptId, x256271_g_MissionId);
        end
    elseif x256271_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"#Y"..x256271_g_MissionName)
        AddQuestText(sceneId,x256271_g_MissionInfo)
        AddQuestText( sceneId,"#Y任务目标：")
        AddQuestText( sceneId,"完成以下任务：")
        for i, item in x256271_g_ExtTarget do
            AddQuestText( sceneId,item.target)
        end 
        if x256271_g_MissionHelp ~= "" then
            AddQuestText(sceneId,"\n#G小提示:#W")
            AddQuestText(sceneId,x256271_g_MissionHelp )
        end
        x256271_DispatchMissionInfo( sceneId, selfId, NPCId )
        EndQuestEvent()
        DispatchQuestInfoNM(sceneId, selfId, NPCId, x256271_g_ScriptId, x256271_g_MissionId);
    end
end

function x256271_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

function x256271_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x256271_g_MissionId)
	if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
	    return 1
	else
	    return 0
	end
end

function x256271_OnYinDaoCompleted( sceneId, selfId, nMode)   
	if nMode==nil then
		return
	end

	if IsHaveQuestNM( sceneId, selfId, x256271_g_MissionId ) == 0 then
		return
	end

	local misIndex = GetQuestIndexByID(sceneId,selfId,x256271_g_MissionId)  

	local n1 = GetQuestParam( sceneId, selfId, misIndex, 0 )	
	local n2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local n3 = GetQuestParam( sceneId, selfId, misIndex, 2 )
	local n4 = GetQuestParam( sceneId, selfId, misIndex, 3 )                                                

    if nMode ==0 then 
   		SetQuestByIndex(sceneId,selfId,misIndex,0,1)

   		if n2==1 and n3==1 and n4==1 then
   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   		end
   	elseif nMode==1 then 
   		SetQuestByIndex(sceneId,selfId,misIndex,1,1)
   		if n1==1 and n3==1 and n4==1 then
   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   		end
   	elseif nMode==2 then	
   		SetQuestByIndex(sceneId,selfId,misIndex,2,1)
   		if n1==1 and n2==1 and n4==1 then
   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   		end
   	elseif nMode==3 then 
   		SetQuestByIndex(sceneId,selfId,misIndex,3,1)
   		if n1==1 and n2==1 and n3==1 then
   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   		end
   	end
end

function x256271_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
    if IsQuestHaveDone(sceneId, selfId, x256271_g_MissionId) > 0 then
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
    local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256271_g_MissionId  )
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


    if x256271_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        local retmiss = AddQuest( sceneId, selfId, x256271_g_MissionId, x256271_g_ScriptId, 0, 0, 0, 1)
        if retmiss ==0 then
            Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
            return 0
        else
            local misIndex = GetQuestIndexByID(sceneId,selfId,x256271_g_MissionId)                                                  
            x256271_Msg2toplayer( sceneId, selfId,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256271_g_MP_cisha,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256271_g_MP_duoqi,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256271_g_MP_chujian,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256271_g_MP_qingbao,0)
            x256271_ProcQuestLogRefresh( sceneId, selfId, x256271_g_MissionId)
        end
    end                                                                    
end

function x256271_ProcQuestAbandon(sceneId, selfId, MissionId)
    if IsHaveQuest(sceneId,selfId, x256271_g_MissionId) <= 0 then
        return 
    end
    DelQuest( sceneId, selfId, x256271_g_MissionId)
    x256271_Msg2toplayer( sceneId, selfId, 1)
end

function x256271_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x256271_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
    end
    for j, item in x256271_g_BonusChoiceItem do
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

function x256271_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256271_g_MissionId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"您没有这个任务！")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x256271_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"您没有达到完成条件！")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x256271_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"背包空间不足，请清理后再来！")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif DelQuest(sceneId, selfId, x256271_g_MissionId) > 0 then
        x256271_Msg2toplayer( sceneId, selfId,2)
        QuestCom(sceneId, selfId, x256271_g_MissionId)
        x256271_GetBonus( sceneId, selfId,NPCId)
        BeginAddItem(sceneId)
        for i, item in x256271_g_BonusItem do
            AddBindItem( sceneId, item.item, item.n )
        end
        for i, item in x256271_g_BonusChoiceItem do
            if item.item == selectRadioId then
                AddItem( sceneId, item.item, item.n )
            end
        end
        EndAddItem(sceneId,selfId)
       	--AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256271_g_MissionIdNext )	
end

function x256271_GetBonus( sceneId, selfId,NpcID)
	if x256271_g_ExpBonus > 0 then
		AddExp(sceneId, selfId, x256271_g_ExpBonus);
  	end
	if x256271_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256271_g_BonusMoney1)
	end
    if x256271_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256271_g_BonusMoney2)
    end
    if x256271_g_BonusMoney3 > 0 then
        AddMoney( sceneId, selfId, 3, x256271_g_BonusMoney3)
    end
    if x256271_g_BonusMoney4 > 0 then
        local nRongYu = GetRongYu( sceneId, selfId )
        nRongYu = nRongYu + x256271_g_BonusMoney4
        SetRongYu( sceneId, selfId, nRongYu )
    end
    if x256271_g_BonusMoney5 > 0 then
        local nShengWang = GetShengWang( sceneId, selfId)
        nShengWang = nShengWang + x256271_g_BonusMoney5
        SetShengWang( sceneId, selfId, nShengWang )
    end
    if x256271_g_BonusMoney6 > 0 then
        AddHonor(sceneId,selfId,x256271_g_BonusMoney6)
    end
end

function x256271_Msg2toplayer( sceneId, selfId,type)
    if type == 0 then
        Msg2Player(sceneId, selfId, "您接受了任务："..x256271_g_MissionName.."！", 0, 2)
        Msg2Player(sceneId, selfId, "您接受了任务："..x256271_g_MissionName.."！", 0, 3)
    elseif type == 1 then
        Msg2Player(sceneId, selfId, "您放弃了任务："..x256271_g_MissionName.."！", 0, 2)
        Msg2Player(sceneId, selfId, "您放弃了任务："..x256271_g_MissionName.."！", 0, 3)
    elseif type == 2 then
        Msg2Player(sceneId, selfId, "您完成了任务"..x256271_g_MissionName.."！", 0, 2)
        Msg2Player(sceneId, selfId, "您完成了任务"..x256271_g_MissionName.."！", 0, 3)      
        if x256271_g_ExpBonus > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R经验"..x256271_g_ExpBonus.."#Y的奖励", 0, 2)
        end
        if x256271_g_BonusMoney1 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x256271_g_BonusMoney1.."文#Y的奖励", 0, 2)
        end
        if x256271_g_BonusMoney2 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R现银"..x256271_g_BonusMoney2.."文#Y的奖励", 0, 2)
        end
        if x256271_g_BonusMoney3 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x256271_g_BonusMoney3.."文#Y的奖励", 0, 2)
        end
        if x256271_g_BonusMoney4 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x256271_g_BonusMoney4.."#Y的奖励", 0, 2)
        end
        if x256271_g_BonusMoney5 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R声望"..x256271_g_BonusMoney5.."#Y的奖励", 0, 2)
        end
        if x256271_g_BonusMoney6 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x256271_g_BonusMoney6.."#Y的奖励", 0, 2)
        end
    end
end

function x256271_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end

function x256271_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256271_ProcTiming(sceneId, selfId, ScriptId, MissionId)
    CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
end

function x256271_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256271_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end

function x256271_LevelUp( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256271_g_MissionId) < 1 then
        return
    end

    -- 完成狩猎
    local misIndex = GetQuestIndexByID( sceneId, selfId, x256271_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256271_g_MP_duoqi, 1)
    x256271_ProcQuestLogRefresh( sceneId, selfId, x256271_g_MissionId)
end

function x256271_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
    local bFind  = 0
    for i ,item in x256271_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
    if IsHaveQuest(sceneId,selfId, x256271_g_MissionId) > 0 then
        local state = GetQuestStateNM(sceneId,selfId,npcId,x256271_g_MissionId)
        AddQuestTextNM( sceneId, selfId, npcId, x256271_g_MissionId, state, -1 )
    end
end

function x256271_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256271_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256271_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256271_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256271_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256271_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x256271_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
    local cisha= GetQuestParam( sceneId, selfId, misIndex, x256271_g_MP_cisha)
    local duoqi = GetQuestParam( sceneId, selfId, misIndex, x256271_g_MP_duoqi)
    local chujian = GetQuestParam( sceneId, selfId, misIndex, x256271_g_MP_chujian)
    local qingbao= GetQuestParam( sceneId, selfId, misIndex, x256271_g_MP_qingbao)
    local strTarget = format( "回报@npc_%d", x256271_g_NpcGUID[1].guid)

    if cisha== 1 and duoqi == 1 and chujian == 1 and qingbao== 1 then
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
    else
        if cisha== 0 or duoqi == 0 or chujian == 0 or qingbao == 0 then
          strTarget = "  #W完成任务：\n"
        end
         if cisha== 0 then
            strTarget = strTarget.."  #W完成一次@npc_28827(0/1)\n"
        else
            strTarget = strTarget.."  #G完成一次@npc_28827(1/1)\n"
        end
        if duoqi == 0 then
            strTarget = strTarget.."  #W完成一次@npc_28824(0/1)\n"
        else
            strTarget = strTarget.."  #G完成一次@npc_28824(1/1)\n"
        end
        if chujian == 0 then
            strTarget = strTarget.."  #W完成一次@npc_28825(0/1)\n"
        else
            strTarget = strTarget.."  #G完成一次@npc_28825(1/1)\n"
        end
        if qingbao== 0 then
            strTarget = strTarget.."  #W完成一次@npc_28826(0/1)"
        else
            strTarget = strTarget.."  #G完成一次@npc_28826(1/1)"
        end
    end

	BeginQuestEvent( sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                             -- 标题
                                x256271_g_MissionName,          -- 任务名字
                                strTarget,
                                "",                             --任务NPC
                                "找到@npc_134502，@npc_134503，@npc_134504，@npc_134505完成他们所交代的任务。",
                                "\t我等你很久了，到了你这样的修为的人，应该开始为国家尽一份力了。\n\t找到@npc_134502，@npc_134503，@npc_134504，@npc_134505完成他们所交代的任务，你会获得丰厚的奖励。",
                                "异国任务都是回报高额的任务，但是要注意安全。"
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

-- 完成刺杀
function x256271_Finishcisha( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256271_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256271_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256271_g_MP_cisha, 1)

    x256271_ProcQuestLogRefresh( sceneId, selfId, x256271_g_MissionId)
end

-- 完成夺旗
function x256271_Finishduoqi( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256271_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256271_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256271_g_MP_duoqi, 1)

    x256271_ProcQuestLogRefresh( sceneId, selfId, x256271_g_MissionId)
end

-- 完成除奸
function x256271_Finishchujian( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256271_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256271_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256271_g_MP_chujian, 1)

    x256271_ProcQuestLogRefresh( sceneId, selfId, x256271_g_MissionId)
end
-- 完成情报
function x256271_Finishqingbao( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256271_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256271_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256271_g_MP_qingbao, 1)

    x256271_ProcQuestLogRefresh( sceneId, selfId, x256271_g_MissionId)
end
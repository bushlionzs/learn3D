--引导任务--完成帮会任务各一次

--MisDescBegin
x256266_g_ScriptId = 256266
x256266_g_MissionIdPre = 2614
x256266_g_MissionId = 2606
x256266_g_LevelLess	= 42
x256266_g_MissionIdNext = 4064
x256266_g_Name	={}
x256266_g_ExtTarget={{type=20,n=1,target="帮会神兽"},{type=20,n=1,target="帮会暗战"},{type=20,n=1,target="帮会图腾"},{type=20,n=1,target="帮会除魔"},}
x256266_g_MissionName="【个人】兴帮之功"
x256266_g_MissionInfo="\t你好，我亲爱的朋友，你如愿的加入了你所向往的帮会。\n\t为了让我们的帮会一天天的强大起来，帮中兄弟要齐心完成帮中的帮会神兽，帮会暗战，帮会图腾，帮会除魔任务，在完成后你会得到很丰厚的回报。"  --任务描述
x256266_g_MissionTarget=""			
x256266_g_MissionCompleted="\t帮中的兄弟对你的表现十分满意，希望你以后再接再厉。"					--完成任务npc说话的话
x256266_g_ContinueInfo="\t帮会任务，是需要和帮中兄弟合作完成的，你不要太心急。"
x256266_g_MissionHelp =	""
x256266_g_DemandItem ={}
x256266_g_BonusMoney1 =0
x256266_g_BonusMoney2 =0
x256266_g_BonusMoney3 =0
x256266_g_BonusMoney4 =0
x256266_g_BonusMoney5 =0
x256266_g_BonusMoney6 =0
x256266_g_BonusMoney8 =200
x256266_g_BonusItem	=	{}
x256266_g_BonusChoiceItem ={}
x256266_g_ExpBonus = 450000
x256266_g_NpcGUID ={{ guid = 129020, name = "帮会任务发布人"} }
--MisDescEnd
--**********************************
-- 帮会内政
--x256266_g_MP_nz   = 1
-- 帮会神兽
x256266_g_MP_hss   = 1
-- 帮会暗战
x256266_g_MP_anzhan  = 2
-- 收集丹木
x256266_g_MP_danmu  = 3
-- 仙人谷除妖
x256266_g_MP_chuyao   = 4
-- 最大等级
x256266_g_MaxLevel   = 160
function x256266_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if GetGuildID( sceneId, selfId ) == -1 then
		--不在帮会中
		return
	end
    local level = GetLevel(sceneId, selfId)
	if level < x256266_g_LevelLess or level >= x256266_g_MaxLevel then
		return
	end

	if IsQuestHaveDone(sceneId, selfId, x256266_g_MissionId) > 0 then
		return 
	end

  if IsQuestHaveDone(sceneId, selfId, x256266_g_MissionIdPre)> 0 then 	
	if IsHaveQuest(sceneId,selfId, x256266_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x256266_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x256266_g_MissionId, state, -1 )
	end
	end
end

function x256266_DispatchMissionInfo( sceneId, selfId, NPCId )
    if x256266_g_ExpBonus> 0 then
        AddQuestExpBonus(sceneId, x256266_g_ExpBonus )
    end
    if x256266_g_BonusMoney1 > 0 then
        AddQuestMoneyBonus1(sceneId, x256266_g_BonusMoney1 )
    end
    if x256266_g_BonusMoney2 > 0 then
        AddQuestMoneyBonus2(sceneId, x256266_g_BonusMoney2 )
    end
    if x256266_g_BonusMoney3 > 0 then
        AddQuestMoneyBonus3(sceneId, x256266_g_BonusMoney3 )
    end
    if x256266_g_BonusMoney4 > 0 then
        AddQuestMoneyBonus4(sceneId, x256266_g_BonusMoney4 )
    end
    if x256266_g_BonusMoney5 > 0 then
        AddQuestMoneyBonus5(sceneId, x256266_g_BonusMoney5 )
    end
    if x256266_g_BonusMoney6 > 0 then
        AddQuestMoneyBonus6(sceneId, x256266_g_BonusMoney6 )
    end
    if x256266_g_BonusMoney8 > 0 then
		AddQuestMoneyBonus8(sceneId, x256266_g_BonusMoney8 )
	end
    for i, item in x256266_g_BonusItem do
        AddQuestItemBonus(sceneId, item.item, item.n)
    end
    for i, item in x256266_g_BonusChoiceItem do
        AddQuestRadioItemBonus(sceneId, item.item, item.n)
    end
end

function x256266_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x256266_g_MissionId) > 0 then
		return
	end
	if IsHaveQuest(sceneId,selfId, x256266_g_MissionId) > 0 then
        if x256266_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x256266_g_MissionName)
            AddQuestText(sceneId,x256266_g_ContinueInfo)
            EndQuestEvent()
            DispatchQuestEventList(sceneId, selfId, NPCId, x256266_g_ScriptId, x256266_g_MissionId);
        else
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x256266_g_MissionName)
            AddQuestText(sceneId,x256266_g_MissionCompleted)
            AddQuestText(sceneId," ")
            x256266_DispatchMissionInfo( sceneId, selfId, NPCId )
            EndQuestEvent()
            DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256266_g_ScriptId, x256266_g_MissionId);
        end
    elseif x256266_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"#Y"..x256266_g_MissionName)
        AddQuestText(sceneId,x256266_g_MissionInfo)
        AddQuestText( sceneId,"#Y任务目标：")
        AddQuestText( sceneId,"找到@npc_129020完成:")
        for i, item in x256266_g_ExtTarget do
            AddQuestText( sceneId,item.target)
        end 
        if x256266_g_MissionHelp ~= "" then
            AddQuestText(sceneId,"\n#G小提示:#W")
            AddQuestText(sceneId,x256266_g_MissionHelp )
        end
        x256266_DispatchMissionInfo( sceneId, selfId, NPCId )
        EndQuestEvent()
        DispatchQuestInfoNM(sceneId, selfId, NPCId, x256266_g_ScriptId, x256266_g_MissionId);
    end
end

function x256266_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

function x256266_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x256266_g_MissionId)
	if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
	    return 1
	else
	    return 0
	end
end

--function x256266_OnYinDaoCompleted( sceneId, selfId, nMode)   
--	if nMode==nil then
--		return
--	end
--
--	if IsHaveQuestNM( sceneId, selfId, x256266_g_MissionId ) == 0 then
--		return
--	end
--
--	local misIndex = GetQuestIndexByID(sceneId,selfId,x256266_g_MissionId)  
--
--	--local n1 = GetQuestParam( sceneId, selfId, misIndex, 0 )	
--	local n2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
--	local n3 = GetQuestParam( sceneId, selfId, misIndex, 2 )
--	local n4 = GetQuestParam( sceneId, selfId, misIndex, 3 ) 
--	local n5 = GetQuestParam( sceneId, selfId, misIndex, 4 )                                                    
--
--   -- if nMode ==0 then --内政
--   		--SetQuestByIndex(sceneId,selfId,misIndex,0,1)
--
--   		--if n2==1 and n3==1 and n4==1 and n5==1 then
--   		--	SetQuestByIndex(sceneId,selfId,misIndex,7,1)
--   	--	end
--   	elseif nMode==1 then --征税
--   		SetQuestByIndex(sceneId,selfId,misIndex,1,1)
--   		if n3==1 and n4==1 and n5==1 then
--   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
--   		end
--   	elseif nMode==2 then	-- 狩猎
--   		SetQuestByIndex(sceneId,selfId,misIndex,2,1)
--   		if n2==1 and n4==1 and n5==1 then
--   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
--   		end
--   	elseif nMode==3 then --征税
--   		SetQuestByIndex(sceneId,selfId,misIndex,3,1)
--   		if n2==1 and n3==1 and n5==1 then
--   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
--   		end
--   	elseif nMode==4 then --征税
--   		SetQuestByIndex(sceneId,selfId,misIndex,4,1)
--   		if n2==1 and n3==1 and n4==1 then
--   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
--   		end
--   	end
--end

function x256266_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
    if IsQuestHaveDone(sceneId, selfId, x256266_g_MissionId) > 0 then
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
	  local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256266_g_MissionId  )
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

    if x256266_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        local retmiss = AddQuest( sceneId, selfId, x256266_g_MissionId, x256266_g_ScriptId, 0, 0, 0, 1)
        if retmiss ==0 then
            Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
            return 0
        else
            local misIndex = GetQuestIndexByID(sceneId,selfId,x256266_g_MissionId)                                                  
            x256266_Msg2toplayer( sceneId, selfId,0)
           -- SetQuestByIndex(sceneId,selfId,misIndex,x256266_g_MP_nz,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256266_g_MP_hss,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256266_g_MP_anzhan,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256266_g_MP_danmu,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256266_g_MP_chuyao,0)
            x256266_ProcQuestLogRefresh( sceneId, selfId, x256266_g_MissionId)
        end
    end                                                                    
end

function x256266_ProcQuestAbandon(sceneId, selfId, MissionId)
    if IsHaveQuest(sceneId,selfId, x256266_g_MissionId) <= 0 then
        return 
    end
    DelQuest( sceneId, selfId, x256266_g_MissionId)
    x256266_Msg2toplayer( sceneId, selfId, 1)
end

function x256266_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x256266_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
    end
    for j, item in x256266_g_BonusChoiceItem do
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

function x256266_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256266_g_MissionId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"您没有这个任务！")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x256266_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"您没有达到完成条件！")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x256266_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"背包空间不足，请清理后再来！")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif DelQuest(sceneId, selfId, x256266_g_MissionId) > 0 then
        x256266_Msg2toplayer( sceneId, selfId,2)
        QuestCom(sceneId, selfId, x256266_g_MissionId)
        x256266_GetBonus( sceneId, selfId,NPCId)
        BeginAddItem(sceneId)
        for i, item in x256266_g_BonusItem do
            AddBindItem( sceneId, item.item, item.n )
        end
        for i, item in x256266_g_BonusChoiceItem do
            if item.item == selectRadioId then
                AddItem( sceneId, item.item, item.n )
            end
        end
        EndAddItem(sceneId,selfId)
       	--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256266_g_MissionIdNext )	
end

function x256266_GetBonus( sceneId, selfId,NpcID)
	if x256266_g_ExpBonus > 0 then
		AddExp(sceneId, selfId, x256266_g_ExpBonus);
  	end
	if x256266_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256266_g_BonusMoney1)
	end
    if x256266_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256266_g_BonusMoney2)
    end
    if x256266_g_BonusMoney3 > 0 then
        AddMoney( sceneId, selfId, 3, x256266_g_BonusMoney3)
    end
    if x256266_g_BonusMoney4 > 0 then
        local nRongYu = GetRongYu( sceneId, selfId )
        nRongYu = nRongYu + x256266_g_BonusMoney4
        SetRongYu( sceneId, selfId, nRongYu )
    end
    if x256266_g_BonusMoney5 > 0 then
        local nShengWang = GetShengWang( sceneId, selfId)
        nShengWang = nShengWang + x256266_g_BonusMoney5
        SetShengWang( sceneId, selfId, nShengWang )
    end
    if x256266_g_BonusMoney6 > 0 then
        AddHonor(sceneId,selfId,x256266_g_BonusMoney6)
    end
    if x256266_g_BonusMoney8 > 0 then
		AddGuildUserPoint(sceneId,selfId,x256266_g_BonusMoney8)	--增加帮贡
		local BonusMoney8 = x256266_g_BonusMoney8
		local pointText = "#Y获得#R帮贡"..BonusMoney8.."点#Y的奖励"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, pointText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)			
  		Msg2Player(sceneId,selfId,pointText,8,2)
	end
end

function x256266_Msg2toplayer( sceneId, selfId,type)
    if type == 0 then
        Msg2Player(sceneId, selfId, "您接受了任务："..x256266_g_MissionName.."！", 0, 2)
        Msg2Player(sceneId, selfId, "您接受了任务："..x256266_g_MissionName.."！", 0, 3)
    elseif type == 1 then
        Msg2Player(sceneId, selfId, "您放弃了任务："..x256266_g_MissionName.."！", 0, 2)
        Msg2Player(sceneId, selfId, "您放弃了任务："..x256266_g_MissionName.."！", 0, 3)
    elseif type == 2 then
        Msg2Player(sceneId, selfId, "您完成了任务"..x256266_g_MissionName.."！", 0, 2)
        Msg2Player(sceneId, selfId, "您完成了任务"..x256266_g_MissionName.."！", 0, 3)      
        if x256266_g_ExpBonus > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R经验"..x256266_g_ExpBonus.."#Y的奖励", 0, 2)
        end
        if x256266_g_BonusMoney1 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x256266_g_BonusMoney1.."文#Y的奖励", 0, 2)
        end
        if x256266_g_BonusMoney2 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R现银"..x256266_g_BonusMoney2.."文#Y的奖励", 0, 2)
        end
        if x256266_g_BonusMoney3 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x256266_g_BonusMoney3.."文#Y的奖励", 0, 2)
        end
        if x256266_g_BonusMoney4 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x256266_g_BonusMoney4.."#Y的奖励", 0, 2)
        end
        if x256266_g_BonusMoney5 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R声望"..x256266_g_BonusMoney5.."#Y的奖励", 0, 2)
        end
        if x256266_g_BonusMoney6 > 0 then
            Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x256266_g_BonusMoney6.."#Y的奖励", 0, 2)
        end
    end
end

function x256266_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end

function x256266_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256266_ProcTiming(sceneId, selfId, ScriptId, MissionId)
    CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
end

function x256266_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256266_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end

--function x256266_LevelUp( sceneId, selfId)
--    if IsHaveQuest( sceneId, selfId, x256266_g_MissionId) < 1 then
--        return
--    end
--
--    -- 完成狩猎
--    local misIndex = GetQuestIndexByID( sceneId, selfId, x256266_g_MissionId)
--    SetQuestByIndex( sceneId, selfId, misIndex, x256266_g_MP_hss, 1)
--    x256266_ProcQuestLogRefresh( sceneId, selfId, x256266_g_MissionId)
--end

function x256266_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
    local bFind  = 0
    for i ,item in x256266_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
    if IsHaveQuest(sceneId,selfId, x256266_g_MissionId) > 0 then
        local state = GetQuestStateNM(sceneId,selfId,npcId,x256266_g_MissionId)
        AddQuestTextNM( sceneId, selfId, npcId, x256266_g_MissionId, state, -1 )
    end
end

function x256266_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256266_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256266_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256266_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256266_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256266_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x256266_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
    --local nz = GetQuestParam( sceneId, selfId, misIndex, x256266_g_MP_nz)
    local hss = GetQuestParam( sceneId, selfId, misIndex, x256266_g_MP_hss)
    local anzhan = GetQuestParam( sceneId, selfId, misIndex, x256266_g_MP_anzhan)
    local danmu= GetQuestParam( sceneId, selfId, misIndex, x256266_g_MP_danmu)
    local chuyao= GetQuestParam( sceneId, selfId, misIndex, x256266_g_MP_chuyao)
    local strTarget = format( "任务已经完成，请回报@npc_%d", x256266_g_NpcGUID[1].guid)

    if hss == 1 and anzhan == 1 and danmu== 1 and chuyao== 1 then
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
    else
        if hss== 0 or anzhan  == 0 or danmu == 0 or chuyao == 0 then      
           strTarget = "  #W找到@npc_129020完成:\n"
        end
        if hss == 0 then
       
            strTarget =strTarget.."  #W帮会神兽(0/1)\n"
        else
            strTarget =strTarget.."  #G帮会神兽(1/1)\n"
        end
        if anzhan == 0 then
            strTarget = strTarget.."  #W帮会暗战(0/1)\n"
        else
            strTarget = strTarget.."  #G帮会暗战(1/1)\n"
        end
        if danmu== 0 then
            strTarget = strTarget.."  #W帮会图腾(0/1)\n"
        else
            strTarget = strTarget.."  #G帮会图腾(1/1)\n"
        end
         if chuyao== 0 then
            strTarget = strTarget.."  #W帮会除魔(0/1)"
        else
            strTarget = strTarget.."  #G帮会除魔(1/1)"
        end
    end

	BeginQuestEvent( sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                             -- 标题
                                x256266_g_MissionName,          -- 任务名字
                                strTarget,
                                "",                             --任务NPC
                                "找到@npc_129020完成帮会神兽，帮会暗战，帮会图腾，帮会除魔",
                                "\t你好，我亲爱的朋友，你如愿的加入了你所向往的帮会。\n\t为了让我们的帮会一天天的强大起来，帮中兄弟要齐心完成帮中的帮会神兽，帮会暗战，帮会图腾，帮会除魔任务，在完成后你会得到很丰厚的回报。",
                                "@npc_129020的任务都是回报高额的任务，但是要注意安全。"
                                )
       	if x256266_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256266_g_ExpBonus )
		end
		if x256266_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256266_g_BonusMoney1 )
		end
		if x256266_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256266_g_BonusMoney2 )
		end
		if x256266_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256266_g_BonusMoney3 )
		end
		if x256266_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256266_g_BonusMoney4 )
		end
		if x256266_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256266_g_BonusMoney5 )
		end
		if x256266_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256266_g_BonusMoney6 )
		end
		if x256266_g_BonusMoney8 > 0 then
			AddQuestMoneyBonus8(sceneId, x256266_g_BonusMoney8 )
		end
		--if x256266_g_GuildExpBonus>0 then
		--	AddQuestGuildExpBonus(sceneId,x256266_g_GuildExpBonus)
		--end
		for i, item in x256266_g_BonusItem do
	   		AddQuestItemBonus(sceneId, item.item, item.n)
 		end
		for i, item in x256266_g_BonusChoiceItem do
    		AddQuestRadioItemBonus(sceneId, item.item, item.n)
  		end

	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

-- 完成内政
--function x256266_Finishnz( sceneId, selfId)
--    if IsHaveQuest( sceneId, selfId, x256266_g_MissionId) <= 0 then
--        return
--    end
--
--    local misIndex = GetQuestIndexByID( sceneId, selfId, x256266_g_MissionId)
--    SetQuestByIndex( sceneId, selfId, misIndex, x256266_g_MP_nz, 1)
--
--    x256266_ProcQuestLogRefresh( sceneId, selfId, x256266_g_MissionId)
--end

-- 完成帮会神兽
function x256266_Finishhss( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256266_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256266_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256266_g_MP_hss, 1)

    x256266_ProcQuestLogRefresh( sceneId, selfId, x256266_g_MissionId)
end

-- 完成暗战
function x256266_Finishanzhan( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256266_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256266_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256266_g_MP_anzhan, 1)

    x256266_ProcQuestLogRefresh( sceneId, selfId, x256266_g_MissionId)
end
-- 完成黑木
function x256266_Finishdanmu( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256266_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256266_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256266_g_MP_danmu, 1)

    x256266_ProcQuestLogRefresh( sceneId, selfId, x256266_g_MissionId)
end
-- 完成除妖
function x256266_Finishchuyao( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256266_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256266_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256266_g_MP_chuyao, 1)

    x256266_ProcQuestLogRefresh( sceneId, selfId, x256266_g_MissionId)
end

function x256266_LevelUp( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256266_g_MissionId) < 1 then
        return
    end

    -- 当等级大于65级时自动完成任务
    if   GetLevel(sceneId, selfId) >= 65 then
    local misIndex = GetQuestIndexByID( sceneId, selfId, x256266_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
    SetQuestByIndex( sceneId, selfId, misIndex, 1, 1)
    SetQuestByIndex( sceneId, selfId, misIndex, 2, 1)
    SetQuestByIndex( sceneId, selfId, misIndex, 3, 1)
    SetQuestByIndex( sceneId, selfId, misIndex, 4, 1)
    SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
    end
end 
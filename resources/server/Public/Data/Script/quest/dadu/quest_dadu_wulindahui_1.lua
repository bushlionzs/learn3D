--【主线】武林风波<二>

--MisDescBegin
x270004_g_ScriptId = 270004
x270004_g_MissionIdPre =3562
x270004_g_MissionId = 3568
x270004_g_LevelLess	= 	50 
x270004_g_MissionIdNext = 3569
x270004_g_Name	={}
x270004_g_ExtTarget={{type=20,n=1,target="消灭@npcsp_乞丐_136281得到物证"}}
x270004_g_MissionName="【主线】武林风波<二>"
x270004_g_MissionInfo="\t（风陵师太命弟子灭绝收了宝剑，回头对你说道）\n\t本门被派出办事的几名弟子确实很久未归，我也曾派人找遍了大都附近，都没有发现弟子的行踪。\n\t与丐帮的人械斗被杀？我们两派素来渊源深厚，在事情没有查清楚之前不能随便冤枉他们。\n\t有劳少侠到城南跑一趟，看看是否能从那几个乞丐那里找到什么线索。"  --任务描述
x270004_g_MissionTarget=""		
x270004_g_MissionCompleted="\t（风陵师太紧紧地攥着那条玉石项链，脸色涨红，好像极力地控制着自己，半晌，才说道）\n\t这……，这，想我峨眉开山鼻祖“小东邪”郭襄祖师与丐帮现任帮主都是精忠报国的郭大侠之后，两派的渊源极深，为何算计我门下弟子！此事贫尼定要找他问个明白！"					--完成任务npc说话的话
x270004_g_ContinueInfo="\t有消息了吗？"
x270004_g_MissionHelp =	""
x270004_g_DemandItem ={{id=13020312,num=1}}
x270004_g_BonusMoney1 =376
x270004_g_BonusMoney2 =0
x270004_g_BonusMoney3 =0
x270004_g_BonusMoney4 =0
x270004_g_BonusMoney5 =61
x270004_g_BonusMoney6 =0
x270004_g_BonusItem	=	{}
x270004_g_BonusChoiceItem ={}
x270004_g_ExpBonus = 145000
x270004_g_NpcGUID ={{ guid = 136281, name = "乞丐刘"},{ guid = 136282, name = "乞丐张"} }
--MisDescEnd
--**********************************

function x270004_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270004_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270004_g_MissionIdPre)> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x270004_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x270004_g_MissionId, state, -1 )
	end
end

function x270004_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270004_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270004_g_ExpBonus )
		end
		if x270004_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270004_g_BonusMoney1 )
		end
		if x270004_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270004_g_BonusMoney2 )
		end
		if x270004_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270004_g_BonusMoney3 )
		end
		if x270004_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270004_g_BonusMoney4 )
		end
		if x270004_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270004_g_BonusMoney5 )
		end
		if x270004_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270004_g_BonusMoney6 )
		end
		for i, item in x270004_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270004_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270004_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x270004_g_MissionId) > 0 then
		return 
	end
	if which == -1 then
		if IsHaveQuest(sceneId,selfId, x270004_g_MissionId) > 0 then
			if x270004_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270004_g_MissionName)
						AddQuestText(sceneId,x270004_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270004_g_ScriptId, x270004_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270004_g_MissionName)
						AddQuestText(sceneId,x270004_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270004_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270004_g_ScriptId, x270004_g_MissionId);
			end
		elseif x270004_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270004_g_MissionName)
			AddQuestText(sceneId,x270004_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x270004_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270004_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x270004_g_MissionHelp )
			end
			x270004_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270004_g_ScriptId, x270004_g_MissionId);
  	end
	else
			local liu = FindMonsterByGUID( sceneId,136281)
			local zhang = FindMonsterByGUID( sceneId,136282)
			if IsObjValid (sceneId,liu) == 1 then
			SetMonsterCamp(sceneId,liu,21)
			end
			if IsObjValid (sceneId,zhang) == 1 then
			SetMonsterCamp(sceneId,zhang,21)
			end
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"两个乞丐突然发狂，向你冲了过来！")
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId, x270004_g_ScriptId, x270004_g_MissionId);
	end
  
end
--**********************************

function x270004_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x270004_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x270004_CheckSubmit( sceneId, selfId, NPCId)
		if GetItemCount(sceneId,selfId,x270004_g_DemandItem[1].id) >= x270004_g_DemandItem[1].num then
				local misIndex = GetQuestIndexByID(sceneId,selfId,x270004_g_MissionId)
				SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    	SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	      return 1
	  else
	  		local misIndex = GetQuestIndexByID(sceneId,selfId,x270004_g_MissionId)
				SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	    	SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
	  return 0
end
--**********************************
function x270004_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270004_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270004_g_MissionId  )
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
		if x270004_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x270004_g_MissionId, x270004_g_ScriptId, 1, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x270004_Msg2toplayer( sceneId, selfId,0)
		  		end
	 	end                                                                    
	     
end
--**********************************

function x270004_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270004_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270004_g_MissionId)
	  x270004_Msg2toplayer( sceneId, selfId,1)
	  for i, item in x270004_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
		end
end
--**********************************
function x270004_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x270004_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270004_g_BonusChoiceItem do
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
--**********************************
function x270004_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270004_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270004_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270004_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270004_g_MissionId) > 0 then
				x270004_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270004_g_MissionId)
				x270004_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270004_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270004_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		for i, item in x270004_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
				end
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270004_g_MissionIdNext )	
end

function x270004_GetBonus( sceneId, selfId,NpcID)
	  if x270004_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270004_g_ExpBonus);
  	end
		if x270004_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270004_g_BonusMoney1 )
	  end
		if x270004_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270004_g_BonusMoney2 )
	  end
		if x270004_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270004_g_BonusMoney3 )
		end
		if x270004_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270004_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270004_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270004_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270004_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270004_g_BonusMoney6)
		end
end

function x270004_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x270004_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x270004_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x270004_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x270004_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x270004_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x270004_g_MissionName.."！", 0, 3)
				if x270004_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x270004_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x270004_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x270004_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x270004_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x270004_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x270004_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x270004_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x270004_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x270004_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x270004_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x270004_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x270004_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x270004_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x270004_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	if	objdataId ==3820 then
	 local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
            if humanObjId ~= -1 then
                if IsHaveQuest(sceneId,humanObjId, x270004_g_MissionId) > 0 then
                    if GetItemCount(sceneId,humanObjId,x270004_g_DemandItem[1].id) < x270004_g_DemandItem[1].num then
                                BeginAddItem(sceneId)
                                AddItem( sceneId, x270004_g_DemandItem[1].id, x270004_g_DemandItem[1].num )
                                local ret = EndAddItem(sceneId,humanObjId)
                                if ret > 0 then
                                    AddItemListToPlayer(sceneId,humanObjId)
                                    x270004_CheckSubmit( sceneId, humanObjId, 0)
                                    Msg2Player(sceneId, humanObjId, "得到了#G翡翠项链#Y   1/1", 0, 3)
                                else
                                    BeginQuestEvent(sceneId)
                                    AddQuestText(sceneId,"物品栏已满，无法得到任务物品！")
                                    EndQuestEvent(sceneId)
                                    DispatchQuestTips(sceneId,humanObjId)
                                end
                    end
                end
            end
		end
	end
end


function x270004_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x270004_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x270004_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x270004_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270004_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x270004_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x270004_g_MissionId) > 0 then
				AddQuestNumText(sceneId, x270004_g_MissionId, "你见过峨嵋派的女弟子吗？",0, 1)
		end
end

function x270004_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270004_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270004_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270004_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270004_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270004_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

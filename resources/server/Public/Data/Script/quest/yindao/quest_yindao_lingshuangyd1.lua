--领双引导

--MisDescBegin
x203751_g_ScriptId = 203751
x203751_g_MissionIdPre = 4241
x203751_g_MissionId = 4205
x203751_g_LevelLess	= 	20
x203751_g_MissionIdNext = 4383
x203751_g_Name	={}
x203751_g_ExtTarget={{type=20,n=1,target="找到@npc_126028学习@npc_59601时间"}}
x203751_g_MissionName="【个人】事半功倍"            
x203751_g_MissionInfo="\t在王城的每一个人都在努力地提升能力，在@npc_126028那里可以@npc_59601时间，赶快找到她寻求帮助！\n\t可以点击#G领双管理员#W打开领取经验时间栏，根据情况选择领取#G双倍经验时间#W"  --任务描述
x203751_g_MissionTarget=""		
x203751_g_MissionCompleted="\t那些想快速提高能力的人都会来找我，在我这里@npc_59601时间，完成任务过程事半功倍。"					--完成任务npc说话的话
x203751_g_ContinueInfo="\t我对没有能力的人不感兴趣！\n\t#G注：你可以点击梵贝领取双倍\n\t经验时间#W"
x203751_g_MissionHelp ="\t#G您可以在@npc_126028那里选择点击@npc_59601时间#W"
x203751_g_DemandItem ={}
x203751_g_ExpBonus = 30000
x203751_g_BonusMoney1 =176
x203751_g_BonusMoney2 =0
x203751_g_BonusMoney3 =0
x203751_g_BonusMoney4 =0
x203751_g_BonusMoney5 =21
x203751_g_BonusMoney6 =0
x203751_g_BonusItem	=	{}
x203751_g_BonusChoiceItem ={}
x203751_g_NpcGUID ={{ guid = 126028, name = "梵贝"} }
--MisDescEnd
--**********************************
x203751_g_MaxLevel   = 40

function x203751_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    local level = GetLevel(sceneId, selfId)
	if level < x203751_g_LevelLess or level >= x203751_g_MaxLevel then
		return
	end


	if IsQuestHaveDone(sceneId, selfId, x203751_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203751_g_MissionIdPre)> 0 then
		if IsHaveQuest(sceneId,selfId, x203751_g_MissionId) <= 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x203751_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x203751_g_MissionId, state, -1 )
		end
	end
end

function x203751_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203751_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203751_g_ExpBonus )
		end
		if x203751_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203751_g_BonusMoney1 )
		end
		if x203751_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203751_g_BonusMoney2 )
		end
		if x203751_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203751_g_BonusMoney3 )
		end
		if x203751_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203751_g_BonusMoney4 )
		end
		if x203751_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203751_g_BonusMoney5 )
		end
		if x203751_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203751_g_BonusMoney6 )
		end
		for i, item in x203751_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203751_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203751_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203751_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203751_g_MissionId) > 0 then
			if x203751_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203751_g_MissionName)
						AddQuestText(sceneId,x203751_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203751_g_ScriptId, x203751_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203751_g_MissionName)
						AddQuestText(sceneId,x203751_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203751_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203751_g_ScriptId, x203751_g_MissionId);
			end
  elseif x203751_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203751_g_MissionName)
			AddQuestText(sceneId,x203751_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x203751_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203751_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203751_g_MissionHelp )
			end
			x203751_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203751_g_ScriptId, x203751_g_MissionId);
  end
	
end
--**********************************

function x203751_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x203751_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x203751_CheckSubmit( sceneId, selfId, NPCId)
	local buff = 7511
	if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 then 
	        return 1
	end
	return 0
	
end
--**********************************
function x203751_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203751_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203751_g_MissionId  )
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
		if x203751_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203751_g_MissionId, x203751_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			  x203751_Msg2toplayer( sceneId, selfId,0)
		  				if x203751_CheckSubmit(sceneId, selfId, NPCId) > 0 then
									local misIndex = GetQuestIndexByID(sceneId,selfId,x203751_g_MissionId)                                                  
	    						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 41,0 )
	    				end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203751_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203751_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203751_g_MissionId)
	  x203751_Msg2toplayer( sceneId, selfId,1)
		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 41,0 )
end
--**********************************
function x203751_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203751_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203751_g_BonusChoiceItem do
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
function x203751_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203751_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203751_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203751_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203751_g_MissionId) > 0 then
				x203751_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203751_g_MissionId)
				x203751_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203751_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203751_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203751_g_MissionIdNext )	
end

function x203751_GetBonus( sceneId, selfId,NpcID)
	  if x203751_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203751_g_ExpBonus);
  	end
		if x203751_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203751_g_BonusMoney1 )
	  end
		if x203751_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203751_g_BonusMoney2 )
	  end
		if x203751_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203751_g_BonusMoney3 )
		end
		if x203751_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203751_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203751_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203751_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203751_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203751_g_BonusMoney6)
		end
end

function x203751_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务："..x203751_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务："..x203751_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务："..x203751_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务："..x203751_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203751_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203751_g_MissionName.."！", 0, 3)
				if x203751_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x203751_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x203751_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x203751_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x203751_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x203751_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x203751_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x203751_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x203751_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x203751_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x203751_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x203751_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x203751_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x203751_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x203751_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203751_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203751_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203751_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203751_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203751_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
  	local bFind  = 0
    for i ,item in x203751_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203751_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203751_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203751_g_MissionId, state, -1 )
				if x203751_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
				 CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 41,1 )
				end 
		end
end

function x203751_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203751_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203751_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203751_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203751_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203751_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
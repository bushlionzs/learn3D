--初识万事通

--MisDescBegin
x256242_g_ScriptId = 256242
x256242_g_MissionIdPre =3099
x256242_g_MissionId = 1530
x256242_g_LevelLess	= 	10
x256242_g_MissionIdNext = 1544
x256242_g_Name	={}
x256242_g_ExtTarget={{type=20,n=1,target="找到@npc_138575"}}
x256242_g_MissionName="【主线】初识万事通"
x256242_g_MissionInfo="\t王城内有一位万事通，他的身份非常神秘，据说合赞太子对他也是礼敬有加。\n\t刚刚来到王城的你，势必对王城还有些陌生，万事通对于整个王城了如指掌，如果你去找他，我想他会很乐意给你指点一二的。"  --任务描述
x256242_g_MissionTarget=""		
x256242_g_MissionCompleted="\t你好啊，年轻人#Y@myname#W，来找我寻求指导么？ "					--完成任务npc说话的话
x256242_g_ContinueInfo=""
x256242_g_MissionHelp =	""
x256242_g_DemandItem ={}
x256242_g_BonusMoney1 =200
x256242_g_BonusMoney2 =0
x256242_g_BonusMoney3 =0
x256242_g_BonusMoney4 =0
x256242_g_BonusMoney5 =0
x256242_g_BonusMoney6 =0
x256242_g_BonusItem	=	{}
x256242_g_BonusChoiceItem ={}
x256242_g_ExpBonus = 1400
x256242_g_NpcGUID ={{ guid = 138575, name = "万事通"} }
--MisDescEnd
--**********************************

function x256242_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x256242_g_MissionId) > 0 then
		return 
	end

				if IsQuestHaveDone(sceneId, selfId, x256242_g_MissionIdPre)> 0 then
						if IsHaveQuest(sceneId,selfId, x256242_g_MissionId) <= 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x256242_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x256242_g_MissionId, state, -1 )
						end
				end

end

function x256242_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256242_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256242_g_ExpBonus )
		end
		if x256242_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256242_g_BonusMoney1 )
		end
		if x256242_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256242_g_BonusMoney2 )
		end
		if x256242_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256242_g_BonusMoney3 )
		end
		if x256242_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256242_g_BonusMoney4 )
		end
		if x256242_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256242_g_BonusMoney5 )
		end
		if x256242_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256242_g_BonusMoney6 )
		end
		for i, item in x256242_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x256242_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x256242_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x256242_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256242_g_MissionId) > 0 then
			if x256242_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256242_g_MissionName)
						AddQuestText(sceneId,x256242_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x256242_g_ScriptId, x256242_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256242_g_MissionName)
						AddQuestText(sceneId,x256242_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x256242_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256242_g_ScriptId, x256242_g_MissionId);
			end
  elseif x256242_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x256242_g_MissionName)
			AddQuestText(sceneId,x256242_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x256242_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256242_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x256242_g_MissionHelp )
			end
			x256242_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256242_g_ScriptId, x256242_g_MissionId);
  end
	
end
--**********************************

function x256242_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x256242_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x256242_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256242_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256242_g_MissionId  )
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
		
		if x256242_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256242_g_MissionId, x256242_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x256242_Msg2toplayer( sceneId, selfId,0)
						--if x256242_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x256242_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,13,1 )
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x256242_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256242_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256242_g_MissionId)
	  x256242_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x256242_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x256242_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256242_g_BonusChoiceItem do
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
function x256242_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256242_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256242_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256242_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256242_g_MissionId) > 0 then
				x256242_Msg2toplayer( sceneId, selfId,2)
				CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,13,0)
				QuestCom(sceneId, selfId, x256242_g_MissionId)
				QuestCom(sceneId, selfId, 1536)
				x256242_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256242_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x256242_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256242_g_MissionIdNext )	
end

function x256242_GetBonus( sceneId, selfId,NpcID)
	  if x256242_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256242_g_ExpBonus);
  	end
		if x256242_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256242_g_BonusMoney1 )
	  end
		if x256242_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256242_g_BonusMoney2 )
	  end
		if x256242_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256242_g_BonusMoney3 )
		end
		if x256242_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256242_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256242_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256242_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256242_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256242_g_BonusMoney6)
		end
end

function x256242_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x256242_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x256242_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256242_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256242_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x256242_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x256242_g_MissionName.."！", 0, 3)
				if x256242_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x256242_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x256242_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x256242_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x256242_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x256242_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x256242_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x256242_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x256242_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x256242_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x256242_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x256242_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x256242_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x256242_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x256242_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256242_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256242_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256242_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256242_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x256242_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x256242_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256242_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256242_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x256242_g_MissionId, state, -1 )
		end
end

function x256242_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256242_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256242_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256242_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256242_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256242_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
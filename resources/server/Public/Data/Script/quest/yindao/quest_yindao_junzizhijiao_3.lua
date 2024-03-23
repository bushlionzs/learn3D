--询问状况

--MisDescBegin
x203824_g_ScriptId = 203824
x203824_g_MissionIdPre =2714
x203824_g_MissionId = 4049
x203824_g_LevelLess	= 35 
x203824_g_MissionIdNext = -1
x203824_g_Name	={}
x203824_g_ExtTarget={{type=20,n=1,target="添加一个好友，将好友度提升到10"}}
x203824_g_MissionName="【个人】君子之交"
x203824_g_MissionInfo="\t去寻找和你志趣相投，又能肝胆相照的一位好友吧。\n\t在组队完成任务过程中你可以邀请那些你喜欢的人为好友。在王国中可以成为好友的人数不胜数，一起组队完成#G“好友任务或打怪”#W将好友度提升得10。"	
x203824_g_MissionTarget=""		
x203824_g_MissionCompleted="\t恭喜你交到密友，看到你们在完成任务时的默契配合我很欣慰。"					--完成任务npc说话的话
x203824_g_ContinueInfo="\t邀请那些你喜欢的人为好友，一起组队完成#G“好友任务或打怪”#W将好友度提升得10。"	
x203824_g_MissionHelp ="一起组队完成#G“好友任务或打怪”#W可以将好友度提升得10。"
x203824_g_DemandItem ={}
x203824_g_ExpBonus = 1000000
x203824_g_BonusMoney1 =295
x203824_g_BonusMoney2 =0
x203824_g_BonusMoney3 =0
x203824_g_BonusMoney4 =0
x203824_g_BonusMoney5 =56
x203824_g_BonusMoney6 =0
x203824_g_BonusItem	={}
x203824_g_BonusChoiceItem ={}
x203824_g_NpcGUID ={{ guid = 132055, name = "朋尔多"} }
--MisDescEnd
--**********************************
-- 最大等级
x203824_g_MaxLevel      = 160

function x203824_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
		local level = GetLevel(sceneId, selfId)
	  if level < x203824_g_LevelLess or level >= x203824_g_MaxLevel then
		return
	end


	if IsQuestHaveDone(sceneId, selfId, x203824_g_MissionId) > 0 then
		return 
	end

	if IsHaveQuest(sceneId,selfId, x203824_g_MissionId) <= 0 then
		if IsQuestHaveDone(sceneId, selfId, x203824_g_MissionIdPre) > 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x203824_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x203824_g_MissionId, state, -1 )
		end
	end

end

function x203824_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203824_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203824_g_ExpBonus )
		end
		if x203824_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203824_g_BonusMoney1 )
		end
		if x203824_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203824_g_BonusMoney2 )
		end
		if x203824_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203824_g_BonusMoney3 )
		end
		if x203824_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203824_g_BonusMoney4 )
		end
		if x203824_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203824_g_BonusMoney5 )
		end
		if x203824_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203824_g_BonusMoney6 )
		end
		for i, item in x203824_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	 	end
		for i, item in x203824_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  	end
end
--**********************************

function x203824_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203824_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203824_g_MissionId) > 0 then
			if x203824_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x203824_g_MissionName)
				AddQuestText(sceneId,x203824_g_ContinueInfo)
				EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, NPCId, x203824_g_ScriptId, x203824_g_MissionId);
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x203824_g_MissionName)
				AddQuestText(sceneId,x203824_g_MissionCompleted)
				AddQuestText(sceneId," ")
				x203824_DispatchMissionInfo( sceneId, selfId, NPCId )
				EndQuestEvent()
				DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203824_g_ScriptId, x203824_g_MissionId);
			end
  elseif x203824_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  		AddQuestText(sceneId,"#Y"..x203824_g_MissionName)
			AddQuestText(sceneId,x203824_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x203824_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203824_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203824_g_MissionHelp )
			end
			x203824_DispatchMissionInfo( sceneId, selfId, NPCId )
	  		EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203824_g_ScriptId, x203824_g_MissionId);
  end
	
end
--**********************************

function x203824_ProcAcceptCheck(sceneId, selfId, NPCId)
		
	return 1
		

end
--**********************************
function x203824_CheckSubmit( sceneId, selfId, NPCId)                                                 
	if IsHaveFriend_FriendPointMoreThenPara(sceneId, selfId, 10) > 0 then
	   return 1
	end
	 
	return 0
	
end

--**********************************
function x203824_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203824_g_MissionId) > 0 then
				return 
		end
		if IsQuestFullNM(sceneId,selfId)==1 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"可接任务数量已满")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 
		end
		
		---检查前置任务
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203824_g_MissionId  )
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
		
		if x203824_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203824_g_MissionId, x203824_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203824_Msg2toplayer( sceneId, selfId,0)
					local friend = IsHaveFriend_FriendPointMoreThenPara(sceneId, selfId, 10)
					if  friend >= 1 then
						local misIndex = GetQuestIndexByID(sceneId,selfId,x203824_g_MissionId)                                                  
	    				SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    				SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203824_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203824_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203824_g_MissionId)
	  x203824_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x203824_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203824_g_BonusItem do
		AddBindItem( sceneId, item.item, item.n )
  end
  for j, item in x203824_g_BonusChoiceItem do
        if item.item == selectRadioId then
            AddBindItem( sceneId, item.item, item.n )
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
function x203824_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203824_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203824_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203824_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"背包空间不足，请清理后再来！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203824_g_MissionId) > 0 then
				x203824_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203824_g_MissionId)
				x203824_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203824_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x203824_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203824_g_MissionIdNext )	
end

function x203824_GetBonus( sceneId, selfId,NpcID)
	  if x203824_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203824_g_ExpBonus);
  	end
		if x203824_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203824_g_BonusMoney1 )
	  end
		if x203824_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203824_g_BonusMoney2 )
	  end
		if x203824_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203824_g_BonusMoney3 )
		end
		if x203824_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203824_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203824_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203824_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203824_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203824_g_BonusMoney6)
		end
end

function x203824_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203824_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203824_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203824_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203824_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203824_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203824_g_MissionName.."！", 0, 3)
				if x203824_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x203824_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x203824_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x203824_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x203824_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x203824_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x203824_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x203824_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x203824_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x203824_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x203824_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x203824_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x203824_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x203824_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x203824_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203824_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203824_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203824_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203824_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203824_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x203824_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203824_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203824_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203824_g_MissionId, state, -1 )
		end
end

function x203824_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203824_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203824_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203824_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203824_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203824_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
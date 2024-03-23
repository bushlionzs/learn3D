--【剧场】救出灾民

--MisDescBegin
x203317_g_ScriptId = 203317
x203317_g_MissionIdPre ={767,768}
x203317_g_MissionId = 769
x203317_g_LevelLess	= 84
x203317_g_MissionIdNext = -1
x203317_g_Name	={}
x203317_g_ExtTarget={{type=20,n=2,target="解救2名@npc_115520"}}
x203317_g_MissionName="【剧场】救出灾民"
x203317_g_MissionInfo="\t暴虐的札兰丁抓走了很多无辜的百姓，大汗常对我们说，欲取天下，先取民心。我一定要救出他们。"  --任务描述
x203317_g_MissionTarget=""		
x203317_g_MissionCompleted="\t看来还是有些可怜的百姓丧生于此！他们会得到长生天的祝福的！这些活下来的人都是你救的，他们一定会终身感谢你！"					--完成任务npc说话的话
x203317_g_ContinueInfo="\t这些都是无辜的百姓，一定要救他们出来！"
x203317_g_MissionHelp =	""
x203317_g_DemandItem ={}
x203317_g_ExpBonus = 626000
x203317_g_BonusMoney1 =840
x203317_g_BonusMoney2 =0
x203317_g_BonusMoney3 =0
x203317_g_BonusMoney4 =0
x203317_g_BonusMoney5 =96
x203317_g_BonusMoney6 =0
x203317_g_BonusItem	=	{}
x203317_g_BonusChoiceItem ={}
x203317_g_GroupPoint	={ {type=10,id =333,target = "装人麻袋"} }
--MisDescEnd
--**********************************

function x203317_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x203317_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203317_g_MissionIdPre[1])> 0 then
	   if IsQuestHaveDone(sceneId, selfId, x203317_g_MissionIdPre[2])> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x203317_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x203317_g_MissionId, state, -1 )
		 end
	end
end

function x203317_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203317_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203317_g_ExpBonus )
		end
		if x203317_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203317_g_BonusMoney1 )
		end
		if x203317_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203317_g_BonusMoney2 )
		end
		if x203317_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203317_g_BonusMoney3 )
		end
		if x203317_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203317_g_BonusMoney4 )
		end
		if x203317_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203317_g_BonusMoney5 )
		end
		if x203317_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203317_g_BonusMoney6 )
		end
		for i, item in x203317_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203317_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203317_ProcEventEntry(sceneId, selfId, NPCId, MissionId, which)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203317_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203317_g_MissionId) > 0 then
			if x203317_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203317_g_MissionName)
						AddQuestText(sceneId,x203317_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203317_g_ScriptId, x203317_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203317_g_MissionName)
						AddQuestText(sceneId,x203317_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203317_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203317_g_ScriptId, x203317_g_MissionId);
			end
  elseif x203317_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203317_g_MissionName)
			AddQuestText(sceneId,x203317_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x203317_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203317_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203317_g_MissionHelp )
			end
			x203317_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203317_g_ScriptId, x203317_g_MissionId);
  end
	
end
--**********************************

function x203317_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x203317_g_MissionIdPre[1])> 0 then
		   if IsQuestHaveDone(sceneId, selfId, x203317_g_MissionIdPre[2])> 0 then
					return 1
			 end
		end
		      return 0

end
--**********************************
function x203317_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x203317_g_MissionId)
			if GetQuestParam(sceneId,selfId,misIndex,0) >= 2 then
					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		return 1
	    end
	 		return 0
	
end
--**********************************
function x203317_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203317_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203317_g_MissionId  )
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
		if x203317_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203317_g_MissionId, x203317_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203317_Msg2toplayer( sceneId, selfId,0)
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203317_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203317_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203317_g_MissionId)
	  x203317_Msg2toplayer( sceneId, selfId,1)
	  for i, item in x203317_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
		end
			
end
--**********************************
function x203317_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203317_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203317_g_BonusChoiceItem do
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
function x203317_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203317_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203317_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203317_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203317_g_MissionId) > 0 then
				x203317_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203317_g_MissionId)
				x203317_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203317_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203317_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		for i, item in x203317_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
				end
    		--AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203317_g_MissionIdNext )	--自动弹出面板
end

function x203317_GetBonus( sceneId, selfId,NpcID)
	  if x203317_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203317_g_ExpBonus);
  	end
		if x203317_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203317_g_BonusMoney1 )
	  end
		if x203317_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203317_g_BonusMoney2 )
	  end
		if x203317_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203317_g_BonusMoney3 )
		end
		if x203317_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203317_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203317_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203317_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203317_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203317_g_BonusMoney6)
		end
end

function x203317_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203317_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203317_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203317_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203317_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203317_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203317_g_MissionName.."！", 0, 3)
				if x203317_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x203317_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x203317_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x203317_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x203317_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x203317_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x203317_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x203317_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x203317_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x203317_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x203317_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x203317_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x203317_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x203317_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x203317_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203317_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203317_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203317_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203317_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203317_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

function x203317_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203317_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203317_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203317_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203317_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203317_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x203317_Growpoint(sceneId,selfId,which)
		if IsHaveQuest(sceneId,selfId, x203317_g_MissionId) <= 0 then
				return 1
		end
		if which ==0 then
							return 0
		elseif which == 1 then
				if IsHaveQuest(sceneId,selfId, x203317_g_MissionId) > 0 then
                    local misIndex = GetQuestIndexByID(sceneId,selfId,x203317_g_MissionId)
										if GetQuestParam(sceneId,selfId,misIndex,0) < 2 then		                                     ---
												SetQuestByIndex(sceneId,selfId,misIndex,0,GetQuestParam(sceneId,selfId,misIndex,0)+1)
												Msg2Player(sceneId, selfId, format("无辜的百姓   %d/2", GetQuestParam(sceneId,selfId,misIndex,0)), 0, 3)
												x203317_CheckSubmit( sceneId, selfId)
										end
										local x,z =GetWorldPos(sceneId,selfId)
										local creatid =CreateMonster(sceneId, 933,x,z,3,1,-1,-1,20,4000,180,"无辜的百姓")
										SendSpecificImpactToUnit(sceneId, creatid, creatid, creatid, 8712, 0);
        end
    		return 1
    end
		
end
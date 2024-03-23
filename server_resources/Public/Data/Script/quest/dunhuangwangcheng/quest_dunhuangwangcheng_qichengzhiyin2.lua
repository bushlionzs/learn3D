--答题

--MisDescBegin
x256052_g_ScriptId = 256052
x256052_g_MissionIdPre =2816
x256052_g_MissionId = 2817
x256052_g_LevelLess	= 	30 
x256052_g_MissionIdNext = -1
x256052_g_Name	={}
x256052_g_ExtTarget={{type=20,n=2,target="回答@npc_137078的问题"}}
x256052_g_MissionName="【教学】骑乘的问题"
x256052_g_MissionInfo="\t我已经告诉你不少关于骑乘的知识了，不知道你是否已经记在了心里，我来问你几个问题吧。"  --任务描述
x256052_g_MissionTarget=""		
x256052_g_MissionCompleted="\t你做得很好，看来骑乘技能的知识你已经是烂熟于胸了。"					--完成任务npc说话的话
x256052_g_ContinueInfo=""
x256052_g_MissionHelp =	""
x256052_g_DemandItem ={}
x256052_g_BonusMoney1 =0
x256052_g_BonusMoney2 =0
x256052_g_BonusMoney3 =0
x256052_g_BonusMoney4 =0
x256052_g_BonusMoney5 =0
x256052_g_BonusMoney6 =0
x256052_g_BonusItem	=	{}
x256052_g_BonusChoiceItem ={}
x256052_g_ExpBonus = 3000
x256052_g_NpcGUID ={}
x256052_g_answer1 ={"冰霜盾","疾驰","清醒","全属"}
x256052_g_answer2 ={"2级反震","1级回春","2级回春","4级回春"}
x256052_g_question1 ={"\t下面哪个技能是被动技能？"}
x256052_g_question2 ={"\t你的骑乘如果要学习3级回春，那么它应该有什么技能？"}
--MisDescEnd
--**********************************

function x256052_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x256052_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x256052_g_MissionIdPre)> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x256052_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x256052_g_MissionId, state, -1 )
	end
end

function x256052_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256052_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256052_g_ExpBonus )
		end
		if x256052_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256052_g_BonusMoney1 )
		end
		if x256052_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256052_g_BonusMoney2 )
		end
		if x256052_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256052_g_BonusMoney3 )
		end
		if x256052_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256052_g_BonusMoney4 )
		end
		if x256052_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256052_g_BonusMoney5 )
		end
		if x256052_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256052_g_BonusMoney6 )
		end
		for i, item in x256052_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x256052_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x256052_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x256052_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256052_g_MissionId) > 0 then
	local zhiye =GetZhiye( sceneId, selfId)+1
	local misIndex = GetQuestIndexByID(sceneId,selfId,x256052_g_MissionId)
	local daan =0
			if x256052_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
					if which ==-1 then
						daan =2
						if GetQuestParam(sceneId,selfId,misIndex,0) ==0 then 
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"#Y"..x256052_g_MissionName)
							AddQuestText(sceneId,x256052_g_question1[1])
							for i, item in x256052_g_answer1 do
								AddQuestNumText(sceneId, MissionId, x256052_g_answer1[i],3,i)
							end 
							EndQuestEvent()
							DispatchQuestEventList(sceneId, selfId, NPCId, x256052_g_ScriptId, x256052_g_MissionId);
					  elseif GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"#Y"..x256052_g_MissionName)
							AddQuestText(sceneId,x256052_g_question2[1])
							for i, item in x256052_g_answer2 do
								AddQuestNumText(sceneId, MissionId, x256052_g_answer2[i],3,i+6)
							end 
							EndQuestEvent()
							DispatchQuestEventList(sceneId, selfId, NPCId, x256052_g_ScriptId, x256052_g_MissionId);
					  end
					elseif which > -1 then
						if which <7 then
							if which ==4 then
									daan =1
							end
						elseif which == 9 then
									daan =1
						elseif daan == 2 then
							daan = 0
						end
					end
					if daan ==0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"你答错了，请重新答！") 
						EndQuestEvent()
						DispatchQuestTips(sceneId, selfId)
					elseif daan ==1 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"恭喜你答对了！") 
						EndQuestEvent()
						DispatchQuestTips(sceneId, selfId)
						SetQuestByIndex(sceneId,selfId,misIndex,0,GetQuestParam(sceneId,selfId,misIndex,0)+1)
						x256052_ProcEventEntry(sceneId, selfId, NPCId, MissionId,-1)
					end
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256052_g_MissionName)
						AddQuestText(sceneId,x256052_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x256052_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256052_g_ScriptId, x256052_g_MissionId);
			end
  elseif x256052_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x256052_g_MissionName)
			AddQuestText(sceneId,x256052_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x256052_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256052_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x256052_g_MissionHelp )
			end
			x256052_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256052_g_ScriptId, x256052_g_MissionId);
  end
	
end
--**********************************

function x256052_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x256052_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x256052_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x256052_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) ==2 then
	        return 1
	  end
	  return 0
	
end
--**********************************
function x256052_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256052_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256052_g_MissionId  )
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
		
		
		if x256052_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256052_g_MissionId, x256052_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x256052_Msg2toplayer( sceneId, selfId,0)
						local misIndex = GetQuestIndexByID(sceneId,selfId,x256052_g_MissionId)                                                  
	    			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			if x256052_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								SetQuestByIndex(sceneId,selfId,misIndex,0,2)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x256052_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256052_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256052_g_MissionId)
	  x256052_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x256052_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x256052_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256052_g_BonusChoiceItem do
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
function x256052_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256052_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256052_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256052_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256052_g_MissionId) > 0 then
				x256052_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256052_g_MissionId)
				x256052_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256052_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x256052_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256052_g_MissionIdNext )	
end

function x256052_GetBonus( sceneId, selfId,NpcID)
	  if x256052_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256052_g_ExpBonus);
  	end
		if x256052_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256052_g_BonusMoney1 )
	  end
		if x256052_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256052_g_BonusMoney2 )
	  end
		if x256052_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256052_g_BonusMoney3 )
		end
		if x256052_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256052_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256052_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256052_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256052_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256052_g_BonusMoney6)
		end
end

function x256052_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x256052_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x256052_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256052_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256052_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x256052_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x256052_g_MissionName.."！", 0, 3)
				if x256052_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x256052_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x256052_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x256052_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x256052_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x256052_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x256052_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x256052_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x256052_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x256052_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x256052_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x256052_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x256052_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x256052_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x256052_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256052_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256052_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256052_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256052_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x256052_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	 
end

function x256052_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256052_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256052_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256052_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256052_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256052_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end






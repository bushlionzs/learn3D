--答题

--MisDescBegin
x203305_g_ScriptId = 203305
x203305_g_MissionIdPre =477
x203305_g_MissionId = 480
x203305_g_LevelLess	= 	45 
x203305_g_MissionIdNext = 481
x203305_g_Name	={}
x203305_g_ExtTarget={{type=20,n=2,target="解答@npc_110029的疑问"}}
x203305_g_MissionName="【剧场】回鹘公主的倾慕"
x203305_g_MissionInfo="\t本公主听说过很多大汗的传说，神往已久，可是传说中总有些不明之处，将军你和大汗并肩作战多年，一定对这些了解甚多，可否为我解答一番？"  --任务描述
x203305_g_MissionTarget=""		
x203305_g_MissionCompleted="\t原来是这样，看来大汗也并非是无情之人……"					--完成任务npc说话的话
x203305_g_ContinueInfo=""
x203305_g_MissionHelp =	""
x203305_g_DemandItem ={}
x203305_g_ExpBonus = 214000
x203305_g_BonusMoney1 =376
x203305_g_BonusMoney2 =0
x203305_g_BonusMoney3 =0
x203305_g_BonusMoney4 =0
x203305_g_BonusMoney5 =71
x203305_g_BonusMoney6 =0
x203305_g_BonusItem	=	{}
x203305_g_BonusChoiceItem ={}
x203305_g_NpcGUID ={}
x203305_g_answer1 ={"此事......不可明言","他们一直恩爱有加","大汗另有新欢"}
x203305_g_answer2 ={"大汗曾为此大病一场","大汗并不在意","大汗完全不知此事"}
x203305_g_question1 ={"\t听说大汗的第一位妻子孛儿贴曾被蔑里岂人抢走侮辱过，后来大汗救回她之后，他们之间感情如何？ "}
x203305_g_question2 ={"\t听说赫赫有名的木华黎将军，在金国凤翔府城下不幸遇伏身亡，大汗听闻此事后有何反应？"}
--MisDescEnd
--**********************************

function x203305_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x203305_g_MissionId) > 0 then
		return 
	end
    
	if IsQuestHaveDone(sceneId, selfId, x203305_g_MissionIdPre)> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x203305_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x203305_g_MissionId, state, -1 )
	end
end

function x203305_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203305_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203305_g_ExpBonus )
		end
		if x203305_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203305_g_BonusMoney1 )
		end
		if x203305_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203305_g_BonusMoney2 )
		end
		if x203305_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203305_g_BonusMoney3 )
		end
		if x203305_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203305_g_BonusMoney4 )
		end
		if x203305_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203305_g_BonusMoney5 )
		end
		if x203305_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203305_g_BonusMoney6 )
		end
		for i, item in x203305_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203305_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203305_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203305_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203305_g_MissionId) > 0 then
	local zhiye =GetZhiye( sceneId, selfId)+1
	local misIndex = GetQuestIndexByID(sceneId,selfId,x203305_g_MissionId)
	local daan =0
			if x203305_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
					if which ==-1 then
						daan =2
						if GetQuestParam(sceneId,selfId,misIndex,0) ==0 then 
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"#Y"..x203305_g_MissionName)
							AddQuestText(sceneId,x203305_g_question1[1])
							for i, item in x203305_g_answer1 do
								AddQuestNumText(sceneId, MissionId, x203305_g_answer1[i],3,i)
							end 
							EndQuestEvent()
							DispatchQuestEventList(sceneId, selfId, NPCId, x203305_g_ScriptId, x203305_g_MissionId);
					  elseif GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"#Y"..x203305_g_MissionName)
							AddQuestText(sceneId,x203305_g_question2[1])
							for i, item in x203305_g_answer2 do
								AddQuestNumText(sceneId, MissionId, x203305_g_answer2[i],3,i+6)
							end 
							EndQuestEvent()
							DispatchQuestEventList(sceneId, selfId, NPCId, x203305_g_ScriptId, x203305_g_MissionId);
					  end
					elseif which > -1 then
						if which <7 then
							if which ==2 then
									daan =1
							end
						elseif which == 7 then
									daan =1
						elseif daan == 2 then
							daan = 0
						end
					end
					if daan ==0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"原来你也不知道......") 
						EndQuestEvent()
						DispatchQuestTips(sceneId, selfId)
					elseif daan ==1 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"原来是这样，我明白了。") 
						EndQuestEvent()
						DispatchQuestTips(sceneId, selfId)
						SetQuestByIndex(sceneId,selfId,misIndex,0,GetQuestParam(sceneId,selfId,misIndex,0)+1)
--                        print(11111)
						x203305_ProcEventEntry(sceneId, selfId, NPCId, MissionId,-1)
					end
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203305_g_MissionName)
						AddQuestText(sceneId,x203305_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203305_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203305_g_ScriptId, x203305_g_MissionId);
			end
  elseif x203305_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203305_g_MissionName)
			AddQuestText(sceneId,x203305_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x203305_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203305_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203305_g_MissionHelp )
			end
			x203305_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203305_g_ScriptId, x203305_g_MissionId);
  end
	
end
--**********************************

function x203305_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x203305_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x203305_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x203305_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) ==2 then
	        return 1
	  end
	  return 0
	
end
--**********************************
function x203305_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203305_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203305_g_MissionId  )
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
		
		if x203305_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203305_g_MissionId, x203305_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			  x203305_ProcEventEntry(sceneId, selfId, NPCId, MissionId,-1)
		  				x203305_Msg2toplayer( sceneId, selfId,0)
							local misIndex = GetQuestIndexByID(sceneId,selfId,x203305_g_MissionId)                                                  
	    				SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    				if x203305_CheckSubmit(sceneId, selfId, NPCId) > 0 then
									SetQuestByIndex(sceneId,selfId,misIndex,0,2)
	    				end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203305_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203305_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203305_g_MissionId)
	  x203305_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x203305_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203305_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203305_g_BonusChoiceItem do
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
function x203305_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId)
	if IsHaveQuest(sceneId,selfId, x203305_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203305_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203305_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203305_g_MissionId) > 0 then
				x203305_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203305_g_MissionId)
				x203305_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203305_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203305_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203305_g_MissionIdNext )	
end

function x203305_GetBonus( sceneId, selfId,NpcID)
	  if x203305_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203305_g_ExpBonus);
  	end
		if x203305_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203305_g_BonusMoney1 )
	  end
		if x203305_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203305_g_BonusMoney2 )
	  end
		if x203305_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203305_g_BonusMoney3 )
		end
		if x203305_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203305_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203305_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203305_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203305_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203305_g_BonusMoney6)
		end
end

function x203305_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203305_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203305_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203305_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203305_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203305_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203305_g_MissionName.."！", 0, 3)
				if x203305_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x203305_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x203305_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x203305_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x203305_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x203305_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x203305_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x203305_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x203305_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x203305_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x203305_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x203305_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x203305_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x203305_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x203305_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203305_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203305_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203305_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203305_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203305_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	 
end

function x203305_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203305_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203305_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203305_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203305_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203305_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end






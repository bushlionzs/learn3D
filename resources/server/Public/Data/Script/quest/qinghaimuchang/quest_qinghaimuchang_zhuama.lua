--【新手】第一匹马

--MisDescBegin
x203589_g_ScriptId = 203589
x203589_g_MissionIdPre =3407
x203589_g_MissionId = 3408
x203589_g_LevelLess	= 	1 
x203589_g_MissionIdNext = 3409
x203589_g_Name	={}
x203589_g_ExtTarget={{type=20,n=1,target="抓到一匹@npc_131027"}}
x203589_g_MissionName="【新手】白鹿长老的考验"
x203589_g_MissionInfo="\t在成吉思汗的世界中，想要成为真正的英雄，一匹好马是你必不可少的伙伴。\n\t看见我身后的这些马了吧，你首先要学会的是如何驯服它们。现在，按我教给你的方法，去选择一匹来做为你第一个伙伴吧。"  --任务描述
x203589_g_MissionTarget="抓到一匹@npc_131027"		
x203589_g_MissionCompleted="\t牢记驯服它们的方法，或许今后你将会得到更多更好的坐骑。"					--完成任务npc说话的话
x203589_g_ContinueInfo="\t你驯服它了么？"
x203589_g_MissionHelp =	"#G将鼠标移动至#R马匹#G上，点击#R左键#G一下，耐心等待抓马读条完毕，系统会提示您捕捉#R成功#G，如果失败了，很可能是由于您和马的#R距离过远#G导致的，您只需要#R靠近马匹#G，重新抓一次即可。#W"
x203589_g_DemandItem ={}
x203589_g_ExpBonus = 310
x203589_g_BonusMoney1 =5
x203589_g_BonusMoney2 =0
x203589_g_BonusMoney3 =0
x203589_g_BonusMoney4 =0
x203589_g_BonusMoney5 =12
x203589_g_BonusMoney6 =0
x203589_g_BonusItem	=	{}
x203589_g_BonusChoiceItem ={}
x203589_g_NpcGUID = {}
--MisDescEnd
--**********************************

function x203589_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

	if IsQuestHaveDone(sceneId, selfId, x203589_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203589_g_MissionIdPre)> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x203589_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x203589_g_MissionId, state, -1 )
			
	end
end

function x203589_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203589_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203589_g_ExpBonus )
		end
		if x203589_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203589_g_BonusMoney1 )
		end
		if x203589_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203589_g_BonusMoney2 )
		end
		if x203589_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203589_g_BonusMoney3 )
		end
		if x203589_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203589_g_BonusMoney4 )
		end
		if x203589_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203589_g_BonusMoney5 )
		end
		if x203589_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203589_g_BonusMoney6 )
		end
		for i, item in x203589_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203589_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203589_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203589_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203589_g_MissionId) > 0 then
			if x203589_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203589_g_MissionName)
						AddQuestText(sceneId,x203589_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203589_g_ScriptId, x203589_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203589_g_MissionName)
						AddQuestText(sceneId,x203589_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203589_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203589_g_ScriptId, x203589_g_MissionId);
			end
  elseif x203589_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203589_g_MissionName)
			AddQuestText(sceneId,x203589_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")  
			for i, item in x203589_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203589_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203589_g_MissionHelp )
			end
			x203589_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
	  	 CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 )
	    
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203589_g_ScriptId, x203589_g_MissionId);
			
  end
	
end
--**********************************

function x203589_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x203589_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x203589_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x203589_g_MissionId )
	local petnum =GetHorseCount(sceneId,selfId)
	if petnum > 0 then
		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,20,0 )
	else 
		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
		SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	end
	if GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
	        return 1
	end
	return 0
end
--**********************************
function x203589_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203589_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203589_g_MissionId  )
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
		if x203589_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203589_g_MissionId, x203589_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203589_Msg2toplayer( sceneId, selfId,0)
		  			SetQuestEvent(sceneId, selfId, x203589_g_MissionId, 3 )
		  			 CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 20,1 )
						if x203589_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203589_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,1,1 )
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203589_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203589_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203589_g_MissionId)
	  x203589_Msg2toplayer( sceneId, selfId,1)
	  CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,1,0 )
			
end
--**********************************
function x203589_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203589_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203589_g_BonusChoiceItem do
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
function x203589_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203589_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203589_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203589_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203589_g_MissionId) > 0 then
				x203589_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203589_g_MissionId)
				x203589_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203589_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203589_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,1,0 )
   CallScriptFunction( 203590, "ProcEventEntry", sceneId, selfId, NPCId, x203589_g_MissionIdNext )	
end

function x203589_GetBonus( sceneId, selfId,NpcID)
	  if x203589_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203589_g_ExpBonus);
  	end
		if x203589_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203589_g_BonusMoney1 )
	  end
		if x203589_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203589_g_BonusMoney2 )
	  end
		if x203589_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203589_g_BonusMoney3 )
		end
		if x203589_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203589_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203589_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203589_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203589_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203589_g_BonusMoney6)
		end
end

function x203589_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203589_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203589_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203589_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203589_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203589_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203589_g_MissionName.."！", 0, 3)
				if x203589_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G经验"..x203589_g_ExpBonus.."#cffcf00的奖励", 0, 2)
  			end
				if x203589_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G银卡"..x203589_g_BonusMoney1.."文#cffcf00的奖励", 0, 2)
	  		end
				if x203589_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G现银"..x203589_g_BonusMoney2.."文#cffcf00的奖励", 0, 2)
	  		end
				if x203589_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G金卡"..x203589_g_BonusMoney3.."文#cffcf00的奖励", 0, 2)
				end
				if x203589_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G朝廷声望值"..x203589_g_BonusMoney4.."#cffcf00的奖励", 0, 2)
				end
				if x203589_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G声望"..x203589_g_BonusMoney5.."#cffcf00的奖励", 0, 2)
				end
				if x203589_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G荣誉"..x203589_g_BonusMoney6.."#cffcf00的奖励", 0, 2)
				end
		end
end

function x203589_ProcQuestHorseChanged(sceneId, selfId, horseId, MissionId)
	x203589_CheckSubmit( sceneId, selfId)
end

function x203589_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203589_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203589_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203589_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203589_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203589_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

function x203589_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203589_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203589_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203589_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203589_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203589_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

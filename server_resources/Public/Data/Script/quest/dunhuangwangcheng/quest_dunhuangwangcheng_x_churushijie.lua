--初入世界

--MisDescBegin
x256009_g_ScriptId = 256009
--x256009_g_MissionIdPre =2704
x256009_g_MissionId = 3000
x256009_g_LevelLess	= 	1 
x256009_g_MissionIdNext = 3001
x256009_g_Name	={}
x256009_g_ExtTarget={{type=20,n=1,target="找到@npc_138023"}}
x256009_g_MissionName="【新手】使团的偶遇"
x256009_g_MissionInfo="\t欢迎来到成吉思汗的世界，勇士#Y@myname#W。\n\t在你下山历练之前，请去和你身边的郭守谦谈一谈。"  --任务描述
x256009_g_MissionTarget=""		
x256009_g_MissionCompleted="\t#Y@myname#W你回来的刚好，我正有些重要的事情要告诉你。"					--完成任务npc说话的话
x256009_g_ContinueInfo=""
x256009_g_MissionHelp =	"您可以用鼠标#R左键#G点击郭守谦，和他对话。您可以点击键盘上的#RQ#G键，打开任务列表，选中你要完成的任务，点击#R任务目标#G中的蓝色字体来进行自动寻路。"
x256009_g_DemandItem ={}
x256009_g_BonusMoney1 =99999999
x256009_g_BonusMoney2 =99999999
x256009_g_BonusMoney3 =99999999
x256009_g_BonusMoney4 =99999999
x256009_g_BonusMoney5 =99999999
x256009_g_BonusMoney6 =99999999
x256009_g_BonusItem	=	{}
x256009_g_BonusChoiceItem ={}
x256009_g_ExpBonus = 5
x256009_g_NpcGUID = {}
--MisDescEnd
--**********************************

function x256009_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
  CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 )
	if IsQuestHaveDone(sceneId, selfId, x256009_g_MissionId) > 0 then
		return 
	end
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x256009_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x256009_g_MissionId, state, -1 )
	  CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 2,1 ) -- 第二个 1 打开界面 0 关闭界面 ? 
end

function x256009_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256009_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256009_g_ExpBonus )
		end
		if x256009_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256009_g_BonusMoney1 )
		end
		if x256009_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256009_g_BonusMoney2 )
		end
		if x256009_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256009_g_BonusMoney3 )
		end
		if x256009_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256009_g_BonusMoney4 )
		end
		if x256009_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256009_g_BonusMoney5 )
		end
		if x256009_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256009_g_BonusMoney6 )
		end
		for i, item in x256009_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x256009_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x256009_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x256009_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256009_g_MissionId) > 0 then
			if x256009_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256009_g_MissionName)
						AddQuestText(sceneId,x256009_g_MissionCompleted)
						EndQuestEvent()
						
						DispatchQuestEventList(sceneId, selfId, NPCId, x256009_g_ScriptId, x256009_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256009_g_MissionName)
						AddQuestText(sceneId,x256009_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x256009_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 2,0 ) -- 第二个 1 打开界面 0 关闭界面  
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 3,1 ) -- 第二个 1 打开界面 0 关闭界面  
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256009_g_ScriptId, x256009_g_MissionId);
			end
  elseif x256009_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x256009_g_MissionName)
			AddQuestText(sceneId,x256009_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")  
			for i, item in x256009_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256009_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x256009_g_MissionHelp )
			end
			x256009_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256009_g_ScriptId, x256009_g_MissionId);
  end
	
end
--**********************************

function x256009_ProcAcceptCheck(sceneId, selfId, NPCId)

					return 1

end
--**********************************
function x256009_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x256009_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256009_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256009_g_MissionId  )
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
		
		
		if x256009_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256009_g_MissionId, x256009_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x256009_Msg2toplayer( sceneId, selfId,0)
						if x256009_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x256009_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x256009_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256009_g_MissionId) > 0 then
				return 
		end
	  	BeginQuestEvent(sceneId)
		  AddQuestText(sceneId,"您无法放弃此任务！") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
			
end
--**********************************
function x256009_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x256009_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256009_g_BonusChoiceItem do
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
function x256009_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256009_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256009_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256009_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256009_g_MissionId) > 0 then
				x256009_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256009_g_MissionId)
				x256009_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256009_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x256009_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
   end
   CallScriptFunction(203419, "ProcEventEntry", sceneId, selfId, NPCId, x256009_g_MissionIdNext )	
end

function x256009_GetBonus( sceneId, selfId,NpcID)
	  if x256009_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256009_g_ExpBonus);
  	end
		if x256009_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256009_g_BonusMoney1 )
	  end
		if x256009_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256009_g_BonusMoney2 )
	  end
		if x256009_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256009_g_BonusMoney3 )
		end
		if x256009_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256009_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256009_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256009_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256009_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256009_g_BonusMoney6)
		end
end

function x256009_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x256009_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x256009_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256009_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256009_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x256009_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x256009_g_MissionName.."！", 0, 3)
				if x256009_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x256009_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x256009_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x256009_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x256009_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x256009_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x256009_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x256009_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x256009_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x256009_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x256009_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x256009_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x256009_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x256009_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x256009_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256009_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256009_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256009_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256009_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x256009_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x256009_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256009_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256009_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256009_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256009_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256009_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
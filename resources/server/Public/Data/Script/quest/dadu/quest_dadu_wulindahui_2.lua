--【主线】扑朔迷离<一>

--MisDescBegin
x270005_g_ScriptId = 270005
x270005_g_MissionIdPre =3563
x270005_g_MissionId = 3570
x270005_g_LevelLess	= 	50 
x270005_g_MissionIdNext = 3571
x270005_g_Name	={}
x270005_g_ExtTarget={{type=20,n=1,target="询问@npc_136253铁琴印的事"}}
x270005_g_MissionName="【主线】扑朔迷离<一>"
x270005_g_MissionInfo="\t(何足道拿起了“铁琴”仔细看了看说道)\n\t此物确实是我昆仑派信物，但多年前我已将此物送给了丐帮帮主郭破虏，他一直随身带着。而从伤痕上来看，很像是被丐帮的“落叶掌”和“打蛇八式”所伤。\n\t不过，以郭帮主的为人，也断然不会做出这种事，少侠不妨查探一下，看看郭帮主的信物还在不在。"  --任务描述
x270005_g_MissionTarget=""		
x270005_g_MissionCompleted="\t没了？！此物乃是峨眉开山祖师郭襄女侠所赠，郭帮主自得了此物后，一直随身携带，怎么可能随意丢弃？"					--完成任务npc说话的话
x270005_g_ContinueInfo="\t我怀疑有人嫁祸丐帮，因为我相信郭帮主是一个正直的人，不会来诬陷我。"
x270005_g_MissionHelp =	""
x270005_g_DemandItem ={}
x270005_g_BonusMoney1 =376
x270005_g_BonusMoney2 =0
x270005_g_BonusMoney3 =0
x270005_g_BonusMoney4 =0
x270005_g_BonusMoney5 =61
x270005_g_BonusMoney6 =0
x270005_g_BonusItem	=	{}
x270005_g_BonusChoiceItem ={}
x270005_g_ExpBonus = 145000
x270005_g_NpcGUID ={{ guid = 136253, name = "张真人"} }
--MisDescEnd
--**********************************

function x270005_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270005_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270005_g_MissionIdPre)> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x270005_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x270005_g_MissionId, state, -1 )
	end
end

function x270005_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270005_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270005_g_ExpBonus )
		end
		if x270005_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270005_g_BonusMoney1 )
		end
		if x270005_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270005_g_BonusMoney2 )
		end
		if x270005_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270005_g_BonusMoney3 )
		end
		if x270005_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270005_g_BonusMoney4 )
		end
		if x270005_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270005_g_BonusMoney5 )
		end
		if x270005_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270005_g_BonusMoney6 )
		end
		for i, item in x270005_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270005_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270005_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x270005_g_MissionId) > 0 then
		return 
	end
	if which == -1 then
		if IsHaveQuest(sceneId,selfId, x270005_g_MissionId) > 0 then
			if x270005_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270005_g_MissionName)
						AddQuestText(sceneId,x270005_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270005_g_ScriptId, x270005_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270005_g_MissionName)
						AddQuestText(sceneId,x270005_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270005_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270005_g_ScriptId, x270005_g_MissionId);
			end
		elseif x270005_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270005_g_MissionName)
			AddQuestText(sceneId,x270005_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x270005_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270005_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x270005_g_MissionHelp )
			end
			x270005_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270005_g_ScriptId, x270005_g_MissionId);
  	end
	else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t这个铁琴印我的确见过，上次武林大会上，何足道把它赠与了丐帮帮主郭破奴，此事是我亲眼所见。但是郭帮主性格随和，如此惨案不会是他所为。")
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId, x270005_g_ScriptId, x270005_g_MissionId);
			local misIndex = GetQuestIndexByID(sceneId,selfId,x270005_g_MissionId)
			SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	end
end
--**********************************

function x270005_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x270005_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x270005_CheckSubmit( sceneId, selfId, NPCId)
			local misIndex = GetQuestIndexByID(sceneId,selfId,x270005_g_MissionId)
			if GetQuestParam(sceneId,selfId,misIndex,0) == 1 then
					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		return 1
	    end
	 		return 0
end
--**********************************
function x270005_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270005_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270005_g_MissionId  )
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
		if x270005_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x270005_g_MissionId, x270005_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x270005_Msg2toplayer( sceneId, selfId,0)
		  		end
	 	end                                                                    
	     
end
--**********************************

function x270005_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270005_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270005_g_MissionId)
	  x270005_Msg2toplayer( sceneId, selfId,1)
	  for i, item in x270005_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
		end
end
--**********************************
function x270005_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x270005_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270005_g_BonusChoiceItem do
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
function x270005_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270005_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270005_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270005_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270005_g_MissionId) > 0 then
				x270005_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270005_g_MissionId)
				x270005_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270005_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270005_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270005_g_MissionIdNext )	
end

function x270005_GetBonus( sceneId, selfId,NpcID)
	  if x270005_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270005_g_ExpBonus);
  	end
		if x270005_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270005_g_BonusMoney1 )
	  end
		if x270005_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270005_g_BonusMoney2 )
	  end
		if x270005_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270005_g_BonusMoney3 )
		end
		if x270005_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270005_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270005_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270005_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270005_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270005_g_BonusMoney6)
		end
end

function x270005_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x270005_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x270005_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x270005_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x270005_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x270005_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x270005_g_MissionName.."！", 0, 3)
				if x270005_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x270005_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x270005_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x270005_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x270005_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x270005_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x270005_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x270005_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x270005_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x270005_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x270005_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x270005_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x270005_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x270005_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x270005_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x270005_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x270005_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x270005_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x270005_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270005_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x270005_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x270005_g_MissionId) > 0 then
				AddQuestNumText(sceneId, x270005_g_MissionId, "张真人您可知此物的主人？",0, 1)
		end
end

function x270005_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270005_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270005_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270005_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270005_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270005_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

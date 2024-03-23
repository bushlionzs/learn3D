--【主线】铲除元凶<一>

--MisDescBegin
x270007_g_ScriptId = 270007
x270007_g_MissionIdPre =3573
x270007_g_MissionId = 3574
x270007_g_LevelLess	= 	50 
x270007_g_MissionIdNext = -1
x270007_g_Name	={}
x270007_g_ExtTarget={{type=20,n=8,target="杀死假冒僧人的天魔教徒"}}
x270007_g_MissionName="【主线】铲除元凶<一>"
x270007_g_MissionInfo="\t天魔教的教主逃走了，但现在还有许多天魔教的人潜伏在寺中。要尽快找到并清除他们，避免更大的麻烦。我想这些假僧人应该不会佛经，你跟他们说“色即是空”，如果能接出下句，就说明他是真僧人。"  --任务描述
x270007_g_MissionTarget=""		
x270007_g_MissionCompleted="\t想不到短短时日武林中就会出现如此阴险的教派。"					--完成任务npc说话的话
x270007_g_ContinueInfo="\t说不出来的人立刻杀掉，不要犹豫。"
x270007_g_MissionHelp =	"此任务无自动寻路，请根据剧情来完成此任务"
x270007_g_DemandItem ={}
x270007_g_BonusMoney1 =376
x270007_g_BonusMoney2 =0
x270007_g_BonusMoney3 =0
x270007_g_BonusMoney4 =0
x270007_g_BonusMoney5 =61
x270007_g_BonusMoney6 =0
x270007_g_BonusItem	=	{}
x270007_g_BonusChoiceItem ={}
x270007_g_ExpBonus = 145000
x270007_g_NpcGUID ={{ guid = 136251, name = "相国寺僧人"},{ guid = 136252, name = "相国寺僧人"} }
--MisDescEnd
--**********************************

function x270007_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270007_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270007_g_MissionIdPre)> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x270007_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x270007_g_MissionId, state, -1 )
	end
end

function x270007_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270007_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270007_g_ExpBonus )
		end
		if x270007_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270007_g_BonusMoney1 )
		end
		if x270007_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270007_g_BonusMoney2 )
		end
		if x270007_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270007_g_BonusMoney3 )
		end
		if x270007_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270007_g_BonusMoney4 )
		end
		if x270007_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270007_g_BonusMoney5 )
		end
		if x270007_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270007_g_BonusMoney6 )
		end
		for i, item in x270007_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270007_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270007_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x270007_g_MissionId) > 0 then
		return 
	end
	if which == -1 then
		if IsHaveQuest(sceneId,selfId, x270007_g_MissionId) > 0 then
			if x270007_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270007_g_MissionName)
						AddQuestText(sceneId,x270007_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270007_g_ScriptId, x270007_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270007_g_MissionName)
						AddQuestText(sceneId,x270007_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270007_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270007_g_ScriptId, x270007_g_MissionId);
			end
		elseif x270007_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270007_g_MissionName)
			AddQuestText(sceneId,x270007_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x270007_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270007_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x270007_g_MissionHelp )
			end
			x270007_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270007_g_ScriptId, x270007_g_MissionId);
  	end
	elseif which == 1 then
			SetMonsterCamp(sceneId,NPCId,21)
			NpcTalk(sceneId, NPCId, "色你个大头鬼！色怎么会是空！", -1)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t和尚突然露出一副凶恶的嘴脸，向你冲来！")
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId, x270007_g_ScriptId, x270007_g_MissionId);
	elseif which == 2 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t回施主下句是“空即是色”")
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId, x270007_g_ScriptId, x270007_g_MissionId);
	end
  
end
--**********************************

function x270007_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x270007_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x270007_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x270007_g_MissionId)
			if GetQuestParam(sceneId,selfId,misIndex,0) >= 8 then
					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		return 1
	    end
	 		return 0
end
--**********************************
function x270007_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270007_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270007_g_MissionId  )
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
		if x270007_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x270007_g_MissionId, x270007_g_ScriptId, 1, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x270007_Msg2toplayer( sceneId, selfId,0)
		  		end
	 	end                                                                    
	     
end
--**********************************

function x270007_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270007_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270007_g_MissionId)
	  x270007_Msg2toplayer( sceneId, selfId,1)
	  for i, item in x270007_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
		end
end
--**********************************
function x270007_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x270007_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270007_g_BonusChoiceItem do
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
function x270007_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270007_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270007_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270007_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270007_g_MissionId) > 0 then
				x270007_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270007_g_MissionId)
				x270007_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270007_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270007_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		for i, item in x270007_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
				end
    		--AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270007_g_MissionIdNext )	
end

function x270007_GetBonus( sceneId, selfId,NpcID)
	  if x270007_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270007_g_ExpBonus);
  	end
		if x270007_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270007_g_BonusMoney1 )
	  end
		if x270007_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270007_g_BonusMoney2 )
	  end
		if x270007_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270007_g_BonusMoney3 )
		end
		if x270007_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270007_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270007_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270007_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270007_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270007_g_BonusMoney6)
		end
end

function x270007_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x270007_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x270007_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x270007_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x270007_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x270007_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x270007_g_MissionName.."！", 0, 3)
				if x270007_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x270007_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x270007_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x270007_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x270007_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x270007_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x270007_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x270007_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x270007_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x270007_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x270007_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x270007_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x270007_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x270007_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x270007_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	if	objdataId ==3801 then
	 local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
            if humanObjId ~= -1 then
                 if IsHaveQuest(sceneId,humanObjId, x270007_g_MissionId) > 0 then
                    local misIndex = GetQuestIndexByID(sceneId,humanObjId,x270007_g_MissionId)
										if GetQuestParam(sceneId,humanObjId,misIndex,0) < 8 then
												SetQuestByIndex(sceneId,humanObjId,misIndex,0,GetQuestParam(sceneId,humanObjId,misIndex,0)+1)
												Msg2Player(sceneId, humanObjId, format("杀死假冒僧人   %d/8", GetQuestParam(sceneId,humanObjId,misIndex,0)), 0, 3)
												x270007_CheckSubmit( sceneId, humanObjId)
										end
                end
            end
		end
	end
end


function x270007_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x270007_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x270007_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x270007_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270007_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x270007_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x270007_g_MissionId) > 0 then
				AddQuestNumText(sceneId, x270007_g_MissionId, "色即是空",0, 1)
		end
end

function x270007_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270007_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270007_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270007_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270007_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270007_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

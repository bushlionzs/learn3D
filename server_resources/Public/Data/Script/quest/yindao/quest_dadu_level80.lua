--询问状况

--MisDescBegin
x256302_g_ScriptId = 256302
x256302_g_MissionIdPre = -1
x256302_g_MissionId = 1603
x256302_g_LevelLess	= 	75 
x256302_g_MissionIdNext = -1
x256302_g_Name	={}
x256302_g_ExtTarget={{type=20,n=1,target="按任务攻略的指引升级到80级"}}
x256302_g_MissionName="【个人】目标：八十级"
x256302_g_MissionInfo="\t你好，亲爱的朋友，我这里有些你应该知道的事情：\n\t完成每周王城发布的#G军需武备#W任务，是迅速升级的一大捷径。\n\t每天#G02：00——02：20#W，#G06：00——06：20#W，#G10：00——10：20#W，#G14：00——14：20#W，#G18：00——18：20#W，#G22：00——22：20#W的其中一个时间，组队从#G外城#W进入70级圣山地宫，能在很短的时间内获得高额的经验\n\t每天@npc_139140会在大都进行仕官晋级考试，凡参与考试者都会获得大量经验。\n\t每天的#G10：30——11：00#W，#G12：30——13：00#W，#G14：30——15：00#W，#G16：30——17：00#W，#G18：30——19：00#W，#G21：30——22：00#W魔君札兰丁的部将都会出现在#G撒马尔罕#W，击杀他们会获得大量各种奖励。\n\t大都的@npc_139100、@npc_139129、@npc_139133他们会在每天晚上#G19：30——24：00#W发布任务，完成后就会获得高额的经验回报。\n\t越是深夜兴致越是高涨？不妨#G23：00#W之后去大都的@npc_139104的店里玩玩，轻松获得大量经验。"  --任务描述
x256302_g_MissionTarget=""		
x256302_g_MissionCompleted="\t八十级是一个不错的成就，但也是新的开始。\n\t我这里为你准备了一些小礼物，希望能对你的历程有所帮助。"					--完成任务npc说话的话
x256302_g_ContinueInfo="别太心急，我为你的八十级准备了不少礼物，但是......你应该先到八十级再来。"
x256302_g_MissionHelp =	""
x256302_g_DemandItem ={}
x256302_g_ExpBonus = 5000000
x256302_g_BonusMoney1 =0
x256302_g_BonusMoney2 =0
x256302_g_BonusMoney3 =0
x256302_g_BonusMoney4 =0
x256302_g_BonusMoney5 =0
x256302_g_BonusMoney6 =0
x256302_g_BonusItem	=	{{item=12030256,n=1},{item=11060003,n=1}}
x256302_g_BonusChoiceItem ={}
x256302_g_NpcGUID ={{ guid = 140417, name = "包打听"} }
--MisDescEnd
--**********************************
-- 最大等级
x256302_g_MaxLevel      = 100

function x256302_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
     local level = GetLevel(sceneId, selfId)
	   if level < x256302_g_LevelLess or level >= x256302_g_MaxLevel then
		return
	end


	if IsQuestHaveDone(sceneId, selfId, x256302_g_MissionId) > 0 then
		return 
	end

	if IsHaveQuest(sceneId,selfId, x256302_g_MissionId) <= 0 then
		--if IsQuestHaveDone(sceneId, selfId, x256302_g_MissionIdPre) > 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x256302_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x256302_g_MissionId, state, -1 )
		end
	--end

end

function x256302_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256302_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256302_g_ExpBonus )
		end
		if x256302_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256302_g_BonusMoney1 )
		end
		if x256302_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256302_g_BonusMoney2 )
		end
		if x256302_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256302_g_BonusMoney3 )
		end
		if x256302_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256302_g_BonusMoney4 )
		end
		if x256302_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256302_g_BonusMoney5 )
		end
		if x256302_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256302_g_BonusMoney6 )
		end
		for i, item in x256302_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	 	end
		for i, item in x256302_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  	end
end
--**********************************

function x256302_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x256302_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256302_g_MissionId) > 0 then
			if x256302_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x256302_g_MissionName)
				AddQuestText(sceneId,x256302_g_ContinueInfo)
				EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, NPCId, x256302_g_ScriptId, x256302_g_MissionId);
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x256302_g_MissionName)
				AddQuestText(sceneId,x256302_g_MissionCompleted)
				AddQuestText(sceneId," ")
				x256302_DispatchMissionInfo( sceneId, selfId, NPCId )
				EndQuestEvent()
				DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256302_g_ScriptId, x256302_g_MissionId);
			end
  elseif x256302_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  		AddQuestText(sceneId,"#Y"..x256302_g_MissionName)
			AddQuestText(sceneId,x256302_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x256302_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256302_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x256302_g_MissionHelp )
			end
			x256302_DispatchMissionInfo( sceneId, selfId, NPCId )
	  		EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256302_g_ScriptId, x256302_g_MissionId);
  end
	
end
--**********************************

function x256302_ProcAcceptCheck(sceneId, selfId, NPCId)
		
	return 1
		

end
--**********************************
function x256302_CheckSubmit( sceneId, selfId, NPCId)                                                 
	if GetLevel(sceneId, selfId)>= 80 then
	   return 1
	end
	 
	return 0
	
end

--**********************************
function x256302_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256302_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256302_g_MissionId  )
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
		
		if x256302_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256302_g_MissionId, x256302_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x256302_Msg2toplayer( sceneId, selfId,0)
					if GetLevel(sceneId, selfId) >= 80 then
						local misIndex = GetQuestIndexByID(sceneId,selfId,x256302_g_MissionId)                                                  
	    				SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    				SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x256302_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256302_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256302_g_MissionId)
	  x256302_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x256302_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x256302_g_BonusItem do
		AddBindItem( sceneId, item.item, item.n )
  end
  for j, item in x256302_g_BonusChoiceItem do
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
function x256302_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256302_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256302_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256302_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"背包空间不足，请清理后再来！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256302_g_MissionId) > 0 then
				x256302_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256302_g_MissionId)
				x256302_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256302_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x256302_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256302_g_MissionIdNext )	
end

function x256302_GetBonus( sceneId, selfId,NpcID)
	  if x256302_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256302_g_ExpBonus);
  	end
		if x256302_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256302_g_BonusMoney1 )
	  end
		if x256302_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256302_g_BonusMoney2 )
	  end
		if x256302_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256302_g_BonusMoney3 )
		end
		if x256302_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256302_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256302_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256302_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256302_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256302_g_BonusMoney6)
		end
end

function x256302_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x256302_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x256302_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256302_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256302_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x256302_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x256302_g_MissionName.."！", 0, 3)
				if x256302_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x256302_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x256302_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x256302_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x256302_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x256302_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x256302_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x256302_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x256302_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x256302_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x256302_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x256302_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x256302_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x256302_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x256302_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256302_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256302_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256302_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256302_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x256302_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x256302_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256302_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256302_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x256302_g_MissionId, state, -1 )
		end
end

function x256302_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256302_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256302_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256302_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256302_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256302_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
--【剧场】浪漫神箭

--MisDescBegin
x256100_g_ScriptId = 256100
x256100_g_MissionIdPre =17
x256100_g_MissionId = 18
x256100_g_MissionIdNext = {3644, 3645, 3646, 3647}
x256100_g_LevelLess	= 	10
x256100_g_Name	={}
x256100_g_ExtTarget={{type=20,n=1,target="将浪漫神箭交给@npc_101020，回到王城"}}
x256100_g_MissionName="【剧场】浪漫神箭"
x256100_g_MissionInfo="\t罕难河是铁木真童年和少年时期的成长之地，在这里铁木真遇到了札木合，木华黎等好兄弟，同时在这里，铁木真遇到了自己生命之初的爱情之花，孛儿贴。这是一个浪漫的时期，没有战争，没有血泪，一切都如同雨后的天空一般明亮。"  --任务描述
x256100_g_MissionTarget=""		
x256100_g_MissionCompleted="\t历史从不曾化为尘埃，它会一直烙印在人们的心中。"					--完成任务npc说话的话
x256100_g_ContinueInfo="\t传说铁木真的祖先，为了重返祖先故土，杀了七十头牤牛，制成七十个风匣，又祭了苍天，方才点燃烟火，终于将阻碍归途的大山化出一个山口来，这就是蒙古“化铁出山”的传说。"
x256100_g_MissionHelp =	""
x256100_g_ExpBonus = 10000
x256100_g_BonusMoney1 =352
x256100_g_BonusMoney2 =0
x256100_g_BonusMoney3 =0
x256100_g_BonusMoney4 =0
x256100_g_BonusMoney5 =100
x256100_g_BonusMoney6 =0
x256100_g_BonusItem	=	{}
x256100_g_BonusChoiceItem ={}
x256100_g_NpcGUID ={{ guid = 101020, name = "钥匙老人"}}
--MisDescEnd
--**********************************

function x256100_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDone(sceneId, selfId, x256100_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256100_g_MissionId) > 0 then
		return 
	end	
	if GetLevel(sceneId, selfId) >= x256100_g_LevelLess then
		if IsQuestHaveDone(sceneId, selfId, x256100_g_MissionIdPre)> 0 then
		if IsHaveQuest(sceneId,selfId, x256100_g_MissionId) <= 0 then
				local state = GetQuestStateNM(sceneId,selfId,NPCId,x256100_g_MissionId)
				AddQuestTextNM( sceneId, selfId, NPCId, x256100_g_MissionId, state, -1 )
		end
		end
	end
	
end

function x256100_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256100_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256100_g_ExpBonus )
		end
		if x256100_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256100_g_BonusMoney1 )
		end
		if x256100_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256100_g_BonusMoney2 )
		end
		if x256100_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256100_g_BonusMoney3 )
		end
		if x256100_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256100_g_BonusMoney4 )
		end
		if x256100_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256100_g_BonusMoney5 )
		end
		if x256100_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256100_g_BonusMoney6 )
		end
		for i, item in x256100_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x256100_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x256100_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x256100_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256100_g_MissionId) > 0 then
			if x256100_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256100_g_MissionName)
						AddQuestText(sceneId,x256100_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x256100_g_ScriptId, x256100_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256100_g_MissionName)
						AddQuestText(sceneId,x256100_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x256100_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256100_g_ScriptId, x256100_g_MissionId);
			end
  elseif x256100_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x256100_g_MissionName)
			AddQuestText(sceneId,x256100_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x256100_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256100_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x256100_g_MissionHelp )
			end
			x256100_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256100_g_ScriptId, x256100_g_MissionId);
  end
	
end
--**********************************

function x256100_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x256100_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x256100_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256100_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256100_g_MissionId  )
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
		
		
		if x256100_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256100_g_MissionId, x256100_g_ScriptId, 1, 0, 0, 1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x256100_Msg2toplayer( sceneId, selfId,0)		  			
		  			--x256100_ProcQuestItemChanged(sceneId, selfId, -1, MissionId)
						--if x256100_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x256100_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x256100_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256100_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256100_g_MissionId)
	  x256100_Msg2toplayer( sceneId, selfId,1)
end
--**********************************
function x256100_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x256100_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256100_g_BonusChoiceItem do
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
function x256100_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	local nCountry = GetCurCountry(sceneId, selfId)
	if IsHaveQuest(sceneId,selfId, x256100_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256100_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256100_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256100_g_MissionId) > 0 then
				x256100_Msg2toplayer( sceneId, selfId,2)
				DelItem( sceneId,selfId,13020011, 1 )
				QuestCom(sceneId, selfId, x256100_g_MissionId)     
				x256100_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256100_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x256100_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
				end
				--local country = GetCurCountry(sceneId, selfId)
				--if country == 0 then
				--		AddQuest( sceneId, selfId, 3644, -1, 1, 0, 0, 1)
				--elseif country == 1 then
				--		AddQuest( sceneId, selfId, 3645, -1, 1, 0, 0, 1)
				--elseif country == 2 then
				--		AddQuest( sceneId, selfId, 3646, -1, 1, 0, 0, 1)		
				--elseif country == 3 then
				--		AddQuest( sceneId, selfId, 3647, -1, 1, 0, 0, 1)
				--end
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256100_g_MissionIdNext[nCountry+1] )	
end

function x256100_GetBonus( sceneId, selfId,NpcID)
	  if x256100_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256100_g_ExpBonus);
  	end
		if x256100_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256100_g_BonusMoney1 )
	  end
		if x256100_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256100_g_BonusMoney2 )
	  end
		if x256100_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256100_g_BonusMoney3 )
		end
		if x256100_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256100_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256100_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256100_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256100_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256100_g_BonusMoney6)
		end
end

function x256100_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x256100_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x256100_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256100_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256100_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x256100_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x256100_g_MissionName.."！", 0, 3)
				if x256100_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x256100_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x256100_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x256100_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x256100_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x256100_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x256100_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x256100_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x256100_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x256100_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x256100_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x256100_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x256100_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x256100_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x256100_CheckSubmit( sceneId, selfId, NPCId)
				local misIndex = GetQuestIndexByID(sceneId,selfId,x256100_g_MissionId)  
				SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	        return 1

end

function x256100_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256100_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256100_OnTimer(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "OnTimer",sceneId, selfId, ScriptId, MissionId )
		
end

function x256100_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256100_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x256100_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256100_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256100_g_MissionId)        ---取得任务状态 ，根据状态添加按钮 AddQuestTextNM
				AddQuestTextNM( sceneId, selfId, npcId, x256100_g_MissionId, state, -1 )
		end
end

function x256100_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256100_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256100_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256100_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256100_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256100_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
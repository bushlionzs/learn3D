--小试牛刀

--MisDescBegin
x203435_g_ScriptId = 203435
x203435_g_MissionIdPre =3413
x203435_g_MissionId = 3414
x203435_g_LevelLess	= 	1 
x203435_g_MissionIdNext = 3498
x203435_g_DemandKill ={{id=11970,num=5}}
--x203435_g_Name	={"穆林","斡鲁斯" }
x203435_g_ExtTarget={{type=20,n=5,target="消灭5只@npc_131023"}}
x203435_g_MissionName="【新手】新兵训练！"
--x203435_g_MissionTalk={"武士的特点","技能的特色","如何能成为宗师"}
x203435_g_MissionInfo="\t现在，我们要开始一项针对新兵的训练！\n\t东南边有很多草原熊在游荡，你的任务，就是去干掉那些草原熊！\n\t在这之后，记得去王城右都尉金虎大人那里报到。他带领着王国的军队，就在王城的东门外。"  --任务描述
x203435_g_MissionTarget="消灭5只@npc_131023"		
x203435_g_MissionCompleted="\t新人？很好！铁家这几个小子，看人的眼光还不错。"
x203435_g_ContinueInfo="\t不要怯懦，这几只熊是难不倒你的。"
x203435_g_MissionHelp =	""
x203435_g_DemandItem ={}
x203435_g_ExpBonus = 2200
x203435_g_BonusMoney1 =5
x203435_g_BonusMoney2 =0
x203435_g_BonusMoney3 =0
x203435_g_BonusMoney4 =0
x203435_g_BonusMoney5 =12
x203435_g_BonusMoney6 =0
x203435_g_BonusItem	=	{}
x203435_g_BonusChoiceItem ={}
x203435_g_NpcGUID = {{ guid = 131037, name = "金虎"} }
--MisDescEnd

--**********************************

function x203435_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
   CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 ) 
	if IsQuestHaveDone(sceneId, selfId, x203435_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203435_g_MissionIdPre) > 0 then
				if IsHaveQuest(sceneId,selfId, x203435_g_MissionId) <= 0 then
						local state = GetQuestStateNM(sceneId,selfId,NPCId,x203435_g_MissionId)
						AddQuestTextNM( sceneId, selfId, NPCId, x203435_g_MissionId, state, -1 )
					 -- CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 5,1 )					 
				end
	end
end

function x203435_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203435_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203435_g_ExpBonus )
		end
		if x203435_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203435_g_BonusMoney1 )
		end
		if x203435_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203435_g_BonusMoney2 )
		end
		if x203435_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203435_g_BonusMoney3 )
		end
		if x203435_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203435_g_BonusMoney4 )
		end
		if x203435_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203435_g_BonusMoney5 )
		end
		if x203435_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203435_g_BonusMoney6 )
		end
		for i, item in x203435_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.id, item.num)
	  end
		for i, item in x203435_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

--任务入口函数

--**********************************

function x203435_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
   CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 )
	if IsQuestHaveDone(sceneId, selfId, x203435_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203435_g_MissionId) > 0 then
			if x203435_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203435_g_MissionName)
						AddQuestText(sceneId,x203435_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203435_g_ScriptId, x203435_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203435_g_MissionName)
						AddQuestText(sceneId,x203435_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203435_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203435_g_ScriptId, x203435_g_MissionId);
			end
  elseif x203435_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
    CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 5,0 )
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203435_g_MissionName)
			AddQuestText(sceneId,x203435_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：") 
			--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,1 )	
			for i, item in x203435_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203435_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203435_g_MissionHelp )
			end
			x203435_DispatchMissionInfo( sceneId, selfId, NPCId )
			EndQuestEvent()
		
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203435_g_ScriptId, x203435_g_MissionId);
  end
end
--*************************************************

--************************************************* 
function x203435_ProcAcceptCheck(sceneId, selfId, NPCId)
	if IsQuestHaveDone(sceneId, selfId, x203435_g_MissionId) > 0 then
		return 0
	elseif IsQuestHaveDone(sceneId, selfId, x203435_g_MissionIdPre) <= 0 then
		return 0
	end
	return 1
end
--**********************************杀怪
function x203435_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x203435_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,0) == x203435_g_DemandKill[1].num then
             
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 21,0 )
	    		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 17,0 )
	    		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,1 )
	        return 1
	end
	return 0
end
--**********************************杀怪
function x203435_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203435_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203435_g_MissionId  )
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
		if x203435_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203435_g_MissionId, x203435_g_ScriptId, 1, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203435_Msg2toplayer( sceneId, selfId,0)
		  			CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 17,1 )
						--if x203435_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203435_g_MissionId)       
								CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 21,1 )
                                           
	    					--SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			--end
		  		end
	 	end                                                                    
	     
end

--**********************************
function x203435_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203435_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203435_g_MissionId)
	  x203435_Msg2toplayer( sceneId, selfId,1)
	  CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 17,0 )
end
--**********************************
function x203435_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203435_g_BonusItem do
		AddItem( sceneId, item.id, item.num )
  end
  for j, item in x203435_g_BonusChoiceItem do
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
function x203435_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203435_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203435_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203435_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203435_g_MissionId) > 0 then
				x203435_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203435_g_MissionId)
				--QuestCom(sceneId, selfId, 3264)
				x203435_GetBonus( sceneId, selfId,NPCId)
				CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203435_g_MissionIdNext )	
				CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 )
				--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 17,1 ) 
   end
end

function x203435_GetBonus( sceneId, selfId,NpcID)
	  if x203435_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203435_g_ExpBonus);
  	end
		if x203435_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203435_g_BonusMoney1 )
	  end
		if x203435_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203435_g_BonusMoney2 )
	  end
		if x203435_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203435_g_BonusMoney3 )
		end
		if x203435_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203435_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203435_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203435_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203435_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203435_g_BonusMoney6)
		end
end

function x203435_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203435_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203435_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203435_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203435_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203435_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203435_g_MissionName.."！", 0, 3)
				if x203435_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G经验"..x203435_g_ExpBonus.."#cffcf00的奖励", 0, 2)
  			end
				if x203435_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G银卡"..x203435_g_BonusMoney1.."文#cffcf00的奖励", 0, 2)
	  		end
				if x203435_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G现银"..x203435_g_BonusMoney2.."文#cffcf00的奖励", 0, 2)
	  		end
				if x203435_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G金卡"..x203435_g_BonusMoney3.."文#cffcf00的奖励", 0, 2)
				end
				if x203435_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G朝廷声望值"..x203435_g_BonusMoney4.."#cffcf00的奖励", 0, 2)
				end
				if x203435_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G声望"..x203435_g_BonusMoney5.."#cffcf00的奖励", 0, 2)
				end
				if x203435_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G荣誉"..x203435_g_BonusMoney6.."#cffcf00的奖励", 0, 2)
				end
		end
end

function x203435_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
    local bFind  = 0
    for i ,item in x203435_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203435_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203435_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203435_g_MissionId, state, -1 )
		end
end

--**********************************杀怪

function x203435_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	if	objdataId ==x203435_g_DemandKill[1].id then
	 local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
            if humanObjId ~= -1 then
                 if IsHaveQuest(sceneId,humanObjId, x203435_g_MissionId) > 0 then
                    local misIndex = GetQuestIndexByID(sceneId,humanObjId,x203435_g_MissionId)
										if GetQuestParam(sceneId,humanObjId,misIndex,0) < 5 then
												SetQuestByIndex(sceneId,humanObjId,misIndex,0,GetQuestParam(sceneId,humanObjId,misIndex,0)+1)
												Msg2Player(sceneId, humanObjId, format("你击毙了草原棕熊 %d/5", GetQuestParam(sceneId,humanObjId,misIndex,0)), 0, 3)
												x203435_CheckSubmit( sceneId, humanObjId)
										end
                end
            end
		end
	end
end

--**********************************杀怪
function x203435_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203435_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203435_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203435_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203435_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203435_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203435_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203435_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203435_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203435_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
--小试牛刀

--MisDescBegin
x203642_g_ScriptId = 203642
x203642_g_MissionIdPre =3342
x203642_g_MissionId = 3304
x203642_g_LevelLess	= 	1 
x203642_g_MissionIdNext = 3310
x203642_g_DemandKill ={{id=11971,num=4}}
--x203642_g_Name	={"穆林","斡鲁斯" }
x203642_g_ExtTarget={{type=20,n=4,target="消灭4只@npc_128021"}}
x203642_g_MissionName="【新手】小试牛刀"
--x203642_g_MissionTalk={"武士的特点","技能的特色","如何能成为宗师"}
x203642_g_MissionInfo="\t我确实遇到了一些麻烦。\n\t你看见这周围的狼群了吗？如果放任下去，必然会成为猎场的一大危害，你可以帮我将它们除掉一些吗？"  --任务描述
x203642_g_MissionTarget="消灭4只@npc_128021"		
x203642_g_MissionCompleted="\t感谢你除掉了这些草原狼，在我来这里之前，我看见王国派出了征兵官正在西南方招收勇士，加入王国军队。\n\t以你的身手，应征入伍应该不是问题。"
x203642_g_ContinueInfo="\t几只草原狼应该不会难住你！"
x203642_g_MissionHelp =	"#G\t你可以点击任务寻路中的蓝色字找到怪物，再用鼠标左键点击怪物，就可以攻击并消灭它们。"
x203642_g_DemandItem ={}
x203642_g_ExpBonus = 139
x203642_g_BonusMoney1 =5
x203642_g_BonusMoney2 =0
x203642_g_BonusMoney3 =0
x203642_g_BonusMoney4 =0
x203642_g_BonusMoney5 =12
x203642_g_BonusMoney6 =0
x203642_g_BonusItem	=	{}
x203642_g_BonusChoiceItem ={}
x203642_g_NpcGUID = {{ guid = 128015, name = "木图"} }
--MisDescEnd

--**********************************

function x203642_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
   CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 ) 
	if IsQuestHaveDone(sceneId, selfId, x203642_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203642_g_MissionIdPre) > 0 then
				if IsHaveQuest(sceneId,selfId, x203642_g_MissionId) <= 0 then
						local state = GetQuestStateNM(sceneId,selfId,NPCId,x203642_g_MissionId)
						AddQuestTextNM( sceneId, selfId, NPCId, x203642_g_MissionId, state, -1 )
					 -- CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 5,1 )					 
				end
	end
end

function x203642_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203642_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203642_g_ExpBonus )
		end
		if x203642_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203642_g_BonusMoney1 )
		end
		if x203642_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203642_g_BonusMoney2 )
		end
		if x203642_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203642_g_BonusMoney3 )
		end
		if x203642_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203642_g_BonusMoney4 )
		end
		if x203642_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203642_g_BonusMoney5 )
		end
		if x203642_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203642_g_BonusMoney6 )
		end
		for i, item in x203642_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.id, item.num)
	  end
		for i, item in x203642_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

--任务入口函数

--**********************************

function x203642_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
   CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 )
	if IsQuestHaveDone(sceneId, selfId, x203642_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203642_g_MissionId) > 0 then
			if x203642_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203642_g_MissionName)
						AddQuestText(sceneId,x203642_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203642_g_ScriptId, x203642_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203642_g_MissionName)
						AddQuestText(sceneId,x203642_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203642_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203642_g_ScriptId, x203642_g_MissionId);
			end
  elseif x203642_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
    CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 5,0 )
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203642_g_MissionName)
			AddQuestText(sceneId,x203642_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：") 
			--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,1 )	
			for i, item in x203642_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203642_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203642_g_MissionHelp )
			end
			x203642_DispatchMissionInfo( sceneId, selfId, NPCId )
			EndQuestEvent()
		
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203642_g_ScriptId, x203642_g_MissionId);
  end
end
--*************************************************

--************************************************* 
function x203642_ProcAcceptCheck(sceneId, selfId, NPCId)
	if IsQuestHaveDone(sceneId, selfId, x203642_g_MissionId) > 0 then
		return 0
	elseif IsQuestHaveDone(sceneId, selfId, x203642_g_MissionIdPre) <= 0 then
		return 0
	end
	return 1
end
--**********************************杀怪
function x203642_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x203642_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,0) == x203642_g_DemandKill[1].num then
             
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 21,0 )
	    		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,1 )
	        return 1
	end
	return 0
end
--**********************************杀怪
function x203642_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203642_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203642_g_MissionId  )
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
		if x203642_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203642_g_MissionId, x203642_g_ScriptId, 1, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203642_Msg2toplayer( sceneId, selfId,0)
						--if x203642_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203642_g_MissionId)       
								CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 21,1 )
                                           
	    					--SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			--end
		  		end
	 	end                                                                    
	     
end

--**********************************
function x203642_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203642_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203642_g_MissionId)
	  x203642_Msg2toplayer( sceneId, selfId,1)
	  CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 )
	  
end
--**********************************
function x203642_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203642_g_BonusItem do
		AddItem( sceneId, item.id, item.num )
  end
  for j, item in x203642_g_BonusChoiceItem do
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
function x203642_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203642_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203642_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203642_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203642_g_MissionId) > 0 then
				x203642_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203642_g_MissionId)
				--QuestCom(sceneId, selfId, 3264)
				x203642_GetBonus( sceneId, selfId,NPCId)
				CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 )
				CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203642_g_MissionIdNext )	
				--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 17,1 ) 
   end
end

function x203642_GetBonus( sceneId, selfId,NpcID)
	  if x203642_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203642_g_ExpBonus);
  	end
		if x203642_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203642_g_BonusMoney1 )
	  end
		if x203642_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203642_g_BonusMoney2 )
	  end
		if x203642_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203642_g_BonusMoney3 )
		end
		if x203642_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203642_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203642_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203642_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203642_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203642_g_BonusMoney6)
		end
end

function x203642_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203642_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203642_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203642_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203642_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203642_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203642_g_MissionName.."！", 0, 3)
				if x203642_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G经验"..x203642_g_ExpBonus.."#cffcf00的奖励", 0, 2)
  			end
				if x203642_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G银卡"..x203642_g_BonusMoney1.."文#cffcf00的奖励", 0, 2)
	  		end
				if x203642_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G现银"..x203642_g_BonusMoney2.."文#cffcf00的奖励", 0, 2)
	  		end
				if x203642_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G金卡"..x203642_g_BonusMoney3.."文#cffcf00的奖励", 0, 2)
				end
				if x203642_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G朝廷声望值"..x203642_g_BonusMoney4.."#cffcf00的奖励", 0, 2)
				end
				if x203642_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G声望"..x203642_g_BonusMoney5.."#cffcf00的奖励", 0, 2)
				end
				if x203642_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G荣誉"..x203642_g_BonusMoney6.."#cffcf00的奖励", 0, 2)
				end
		end
end

function x203642_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
    local bFind  = 0
    for i ,item in x203642_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203642_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203642_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203642_g_MissionId, state, -1 )
		end
end

--**********************************杀怪

function x203642_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	if	objdataId ==x203642_g_DemandKill[1].id then
	 local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
            if humanObjId ~= -1 then
                 if IsHaveQuest(sceneId,humanObjId, x203642_g_MissionId) > 0 then
                    local misIndex = GetQuestIndexByID(sceneId,humanObjId,x203642_g_MissionId)
										if GetQuestParam(sceneId,humanObjId,misIndex,0) < 4 then
												SetQuestByIndex(sceneId,humanObjId,misIndex,0,GetQuestParam(sceneId,humanObjId,misIndex,0)+1)
												Msg2Player(sceneId, humanObjId, format("你击毙了草原狼 %d/4", GetQuestParam(sceneId,humanObjId,misIndex,0)), 0, 3)
												x203642_CheckSubmit( sceneId, humanObjId)
												if GetQuestParam(sceneId,selfId,misIndex,0) == x203642_g_DemandKill[1].num then	
														CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,1 )	
												end
										end
                end
            end
		end
	end
end

--**********************************杀怪
function x203642_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203642_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203642_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203642_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203642_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203642_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203642_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203642_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203642_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203642_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
--火枪习武

--MisDescBegin
x203568_g_ScriptId = 203568
x203568_g_MissionIdPre =3400
x203568_g_MissionId = 3420
x203568_g_LevelLess	= 	1 
x203568_g_MissionIdNext = 3441
--x203568_g_Name	={"穆林","斡鲁斯" }
x203568_g_ExtTarget={{type=20,n=3,target="向@npc_131001讨教职业发展"}}
x203568_g_MissionName="【新手】初识职业"
x203568_g_MissionTalk={"火枪的现状","火枪的特点","如何能成为宗师"}
x203568_g_MissionInfo="\t作为一个初入世界的新人，首先必须要对自己的职业有明确的认识。\n\t我的朋友智者哈达，年轻时游历世界，见多识广。他一定可以为你做出有关你的职业的指点。"  --任务描述
x203568_g_MissionTarget="向@npc_131001讨教职业发展"		
x203568_g_MissionCompleted="\t绝世武功并非朝夕而蹴，只有持之以恒的练习，才能成为一代宗师。"
x203568_g_ContinueInfo={"\t虽然火枪手是一个新兴的兵种，但是凭借着无以伦比的精准和穿透力，迅速活跃在各个国家中。",
												"\t火枪手拥有着最先进的武器装备，已经成为大元军队中一个不可或缺的职业。\n",
												"\t技能均为远程伤害技能，以单目标攻击技能为主，配有部分多目标技能。\n"}
x203568_g_MissionHelp =	"#G您可以用鼠标#R左键#G点击@npc_131001，和他对话。您可以点击键盘上的#RQ#G键，打开任务列表，选中你要完成的任务，点击#R任务目标#G中的蓝色字体来进行自动寻路。"
x203568_g_DemandItem ={}
x203568_g_ExpBonus = 23
x203568_g_BonusMoney1 =11
x203568_g_BonusMoney2 =0
x203568_g_BonusMoney3 =0
x203568_g_BonusMoney4 =0
x203568_g_BonusMoney5 =12
x203568_g_BonusMoney6 =0
x203568_g_BonusItem	=	{}
x203568_g_BonusChoiceItem ={}
x203568_g_NpcGUID = {{ guid = 131001, name = "长老"} }
--x203568_g_Skill	= {{id=406, level=1, pos=4},{id=409, level=1, pos=3}}
--MisDescEnd
--**********************************

function x203568_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
 CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 )
	if IsQuestHaveDone(sceneId, selfId, x203568_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203568_g_MissionIdPre) > 0 then
		if GetZhiye( sceneId, selfId)==3 then
				if IsHaveQuest(sceneId,selfId, x203568_g_MissionId) <= 0 then
						local state = GetQuestStateNM(sceneId,selfId,NPCId,x203568_g_MissionId)
						AddQuestTextNM( sceneId, selfId, NPCId, x203568_g_MissionId, state, -1 )
					 CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 5,1 )	
				end
		end
	end
end

function x203568_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203568_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203568_g_ExpBonus )
		end
		if x203568_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203568_g_BonusMoney1 )
		end
		if x203568_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203568_g_BonusMoney2 )
		end
		if x203568_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203568_g_BonusMoney3 )
		end
		if x203568_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203568_g_BonusMoney4 )
		end
		if x203568_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203568_g_BonusMoney5 )
		end
		if x203568_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203568_g_BonusMoney6 )
		end
		for i, item in x203568_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.id, item.num)
	  end
		for i, item in x203568_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

--任务入口函数

--**********************************

function x203568_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
   local misIndex = GetQuestIndexByID(sceneId,selfId,x203568_g_MissionId)
   CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 )
	if IsQuestHaveDone(sceneId, selfId, x203568_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203568_g_MissionId) > 0 then
			if x203568_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
					if which == -1 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203568_g_MissionName)
						AddQuestText(sceneId,x203568_g_ContinueInfo[1])
						AddQuestNumText(sceneId, MissionId, x203568_g_MissionTalk[1],0,0)
						EndQuestEvent()
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 16,1 )	
						DispatchQuestEventList(sceneId, selfId, NPCId, x203568_g_ScriptId, x203568_g_MissionId);
					elseif which ==0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203568_g_MissionName)
						AddQuestText(sceneId,x203568_g_ContinueInfo[2])
						AddQuestNumText(sceneId, MissionId, x203568_g_MissionTalk[2],1,1)
						EndQuestEvent()
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						DispatchQuestEventList(sceneId, selfId, NPCId, x203568_g_ScriptId, x203568_g_MissionId);
					elseif which ==1 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203568_g_MissionName)
						AddQuestText(sceneId,x203568_g_ContinueInfo[3])
						AddQuestNumText(sceneId, MissionId, x203568_g_MissionTalk[3],0,2)
						EndQuestEvent()
						SetQuestByIndex(sceneId,selfId,misIndex,0,2)
						DispatchQuestEventList(sceneId, selfId, NPCId, x203568_g_ScriptId, x203568_g_MissionId);
						local misIndex = GetQuestIndexByID(sceneId,selfId,x203568_g_MissionId)  
						SetQuestByIndex(sceneId,selfId,misIndex,1,1)                                                
	    			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
					end
			else
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 16,0)
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 3,1)
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203568_g_MissionName)
						AddQuestText(sceneId,x203568_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203568_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						SetQuestByIndex(sceneId,selfId,misIndex,0,3)
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203568_g_ScriptId, x203568_g_MissionId);
			end
  elseif x203568_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
    CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 5,0 )
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203568_g_MissionName)
			AddQuestText(sceneId,x203568_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
				CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,1 )	
			for i, item in x203568_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203568_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203568_g_MissionHelp )
			end
			x203568_DispatchMissionInfo( sceneId, selfId, NPCId )
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203568_g_ScriptId, x203568_g_MissionId);
			CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 4,1 )
  end
end
--**********************************
function x203568_ProcAcceptCheck(sceneId, selfId, NPCId)
	if IsQuestHaveDone(sceneId, selfId, x203568_g_MissionId) > 0 then
		return 0
	elseif IsQuestHaveDone(sceneId, selfId, x203568_g_MissionIdPre) <= 0 then
		return 0
	end
	return 1
end
--**********************************
function x203568_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x203568_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,1) == 1 then
	        return 1
	end
	return 0
end
--**********************************
function x203568_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203568_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203568_g_MissionId  )
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
		if x203568_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203568_g_MissionId, x203568_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203568_Msg2toplayer( sceneId, selfId,0)
						--if x203568_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203568_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 4,0 )
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************
function x203568_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203568_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203568_g_MissionId)
	  x203568_Msg2toplayer( sceneId, selfId,1)
end
--**********************************
function x203568_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203568_g_BonusItem do
		AddItem( sceneId, item.id, item.num )
  end
  for j, item in x203568_g_BonusChoiceItem do
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
function x203568_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203568_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203568_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203568_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203568_g_MissionId) > 0 then
				x203568_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203568_g_MissionId)
				QuestCom(sceneId, selfId, 3440)
				x203568_GetBonus( sceneId, selfId,NPCId)
				--if HaveSkill(sceneId, selfId,x203568_g_Skill[1].id)<=0 then
				--	AddSkillToPlayer(sceneId, selfId, x203568_g_Skill[1].id, x203568_g_Skill[1].level, x203568_g_Skill[1].pos)
				--end
				--if HaveSkill(sceneId, selfId,x203568_g_Skill[2].id)<=0 then
				--	AddSkillToPlayer(sceneId, selfId, x203568_g_Skill[2].id, x203568_g_Skill[2].level, x203568_g_Skill[2].pos)
				--end
				--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 17,1 ) 
				 CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 3,0)
				CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203568_g_MissionIdNext )	
   end
end

function x203568_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
    local bFind  = 0
    for i ,item in x203568_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203568_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203568_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203568_g_MissionId, 7, -1 )
		end
end

function x203568_GetBonus( sceneId, selfId,NpcID)
	  if x203568_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203568_g_ExpBonus);
  	end
		if x203568_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203568_g_BonusMoney1 )
	  end
		if x203568_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203568_g_BonusMoney2 )
	  end
		if x203568_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203568_g_BonusMoney3 )
		end
		if x203568_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203568_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203568_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203568_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203568_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203568_g_BonusMoney6)
		end
end

function x203568_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203568_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203568_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203568_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203568_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203568_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203568_g_MissionName.."！", 0, 3)
				if x203568_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G经验"..x203568_g_ExpBonus.."#cffcf00的奖励", 0, 2)
  			end
				if x203568_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G银卡"..x203568_g_BonusMoney1.."文#cffcf00的奖励", 0, 2)
	  		end
				if x203568_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G现银"..x203568_g_BonusMoney2.."文#cffcf00的奖励", 0, 2)
	  		end
				if x203568_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G金卡"..x203568_g_BonusMoney3.."文#cffcf00的奖励", 0, 2)
				end
				if x203568_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G朝廷声望值"..x203568_g_BonusMoney4.."#cffcf00的奖励", 0, 2)
				end
				if x203568_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G声望"..x203568_g_BonusMoney5.."#cffcf00的奖励", 0, 2)
				end
				if x203568_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G荣誉"..x203568_g_BonusMoney6.."#cffcf00的奖励", 0, 2)
				end
		end
end

--**********************************

function x203568_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end
--**********************************
function x203568_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203568_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203568_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203568_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203568_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203568_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203568_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203568_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203568_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203568_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
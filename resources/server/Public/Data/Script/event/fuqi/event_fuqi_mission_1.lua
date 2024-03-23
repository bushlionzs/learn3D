
--MisDescBegin
x300350_g_ScriptId = 300350
x300350_g_LevelLess = 40
--MisDescEnd

x300350_g_MissionId = SPOUSE_TASK[1]
x300350_g_FatherMissionId = SPOUSE_TASK[3]
x300350_g_FatherMissionName = "【夫妻任务】"
x300350_g_MissionName ="【夫妻任务】"
x300350_g_MissionItem = 13080009

function x300350_IsMissionComplete(sceneId, selfId, MissionId) 
  local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
  return GetQuestParam( sceneId, selfId, misIndex, 7 )
end
function x300350_SetMissionData(sceneId, selfId)
		SetQuestData(sceneId, selfId, MD_SPOUSE_MISSION_DATE[1][1], MD_SPOUSE_MISSION_DATE[1][2], MD_SPOUSE_MISSION_DATE[1][3], GetDayOfYear())
end

function x300350_SubmitFatherMissionCheck(sceneId, selfId, NPCId)
	local teamSize = GetTeamSize(sceneId, selfId)
	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	local week = GetWeek()
	local today = GetDayOfYear()
	if week ~=4 and week ~= 6 then
		return "很抱歉，只有周四、周六，才能进行本任务！"   
	end
	
	if HasTeam(sceneId, selfId) ~= 1 then
		return "很抱歉，您还未进行组队无法提交本任务。"
	end
	
	if (GetTeamSize(sceneId, selfId) < 2) then
		return "很抱歉，您所在的队伍中成员小于2人，无法提交本任务。";
	end
	
	if (GetTeamSize(sceneId, selfId) > 2) then
		return "很抱歉，您所在的队伍中成员大于2人，无法提交本任务。";
	end
	
	if IsInDist(sceneId, selfId, targetId, 10) ~= 1 then
		return "很抱歉，您与配偶不在有效的距离内，无法进行本任务。";
	end
	
	if IsSpouses(sceneId, selfId, targetId) ~= 1 then
		return "很抱歉，您所在的队伍中成员不是夫妻关系，无法提交本任务。";
	end		
	
	if GetSex(sceneId, selfId) == 0 then
		return "很抱歉，只有男性才能提交本任务。";
	end
	
	if IsHaveQuestNM( sceneId, selfId, x300350_g_FatherMissionId ) ~= 1 then
		return "您没有本任务，无法提交本任务。"
	end
	
	if IsHaveQuestNM( sceneId, targetId, x300350_g_FatherMissionId ) ~= 1 then
		return "您的配偶没有本任务，无法提交本任务。"
	end
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300350_g_FatherMissionId )
	if GetQuestParam( sceneId, selfId, misIndex, 1 )  <= 0 then
		return "您未完成本任务，无法提交本任务。"
	end
	
	local misIndex = GetQuestIndexByID( sceneId, targetId, x300350_g_FatherMissionId )
	if GetQuestParam( sceneId, targetId, misIndex, 1 ) <= 0 then
		return "您的配偶未完成本任务，无法提交本任务。"
	end
	
	return nil
end

--**********************************

--任务入口函数

--**********************************
function x300350_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )
	if IsHaveQuestNM( sceneId, selfId, x300350_g_FatherMissionId ) == 1 then
		
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300350_g_FatherMissionId )
		if GetQuestParam( sceneId, selfId, misIndex, 1 ) == 1 then
			local submitRetCode = x300350_SubmitFatherMissionCheck(sceneId, selfId, targetId)
			if submitRetCode ~= nil then
				Msg2Player(sceneId,selfId,submitRetCode,8,2)
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, submitRetCode);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return
				--BeginQuestEvent(sceneId)
				--AddQuestText(sceneId,submitRetCode)
				--EndQuestEvent()
				--DispatchQuestDemandInfo(sceneId, selfId, targetId, x300350_g_ScriptId, x300350_g_MissionId,0);
				--return
			end
			BeginQuestEvent(sceneId)
		--任务信息
			AddQuestText(sceneId,"")
			AddQuestText(sceneId,"")
	
			--任务目标
			AddQuestText(sceneId,"")
			AddQuestText(sceneId,"#Y【夫妻】心心相映#W#r\t恭喜您，出色的完成了【夫妻任务】，祝福您夫妻二人白头偕老，永不分离！这是给你们的奖励，请收下！#r")
	
			local level = GetLevel(sceneId, selfId)
			local ExpBonus = 1000 *0.4*level*10
			--if ExpBonus > 0 then
				AddQuestExpBonus(sceneId, ExpBonus);
			--end
			
			EndQuestEvent()
		  DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300350_g_ScriptId, x300350_g_MissionId);
		  return
		else
			local str = "任务还没有完成 您还需要加把劲啊 ..."
			Msg2Player(sceneId,selfId,str,8,2)
			return
			--BeginQuestEvent(sceneId)
			--AddQuestText(sceneId,str)
			--EndQuestEvent()
			--DispatchQuestDemandInfo(sceneId, selfId, targetId, x300350_g_ScriptId, x300350_g_MissionId,0);
			--return
		end
	end
	if IsHaveQuestNM( sceneId, targetId, x300350_g_MissionId ) ~= 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y【夫妻】爱情紫晶")
		AddQuestText(sceneId,"\t您好，每周的周四，周六您可以在我这里进行【夫妻任务】。【夫妻任务】一共由三个任务组成。您必须完成全部三个任务才能够获得奖励。#r\t在大都的东门附近，生长着一种紫色的水晶。#r\t据说得到紫水晶的情侣会受到爱的祝福。#r\t到达大都@npc_72044，采集5个紫水晶回来交给@npc_140002，他正在收集带有爱意的紫水晶，将紫水晶交给他，就可以得到他对你们爱的祝福。")
		local level = GetLevel(sceneId, selfId)
		local ExpBonus = 1000 *0.4*10* level
		AddQuestText(sceneId,"#Y奖励内容：#W#r经验值：" .. ExpBonus.."点")
		EndQuestEvent(sceneId)   
		DispatchQuestInfo(sceneId, selfId, targetId, x300350_g_MissionId, x300350_g_ScriptId)
	end
	
end

--**********************************

--列举事件

--**********************************
--5	非循环任务	未接	1
--6	非循环/循环任务	未完成	2
--7	非循环任务	已完成	3
function x300350_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	if IsMarried(sceneId, selfId) ~= 1 then
		return
	end
	local state = GetQuestStateNM(sceneId, selfId, targetId, x300350_g_MissionId)
	if IsHaveQuestNM( sceneId, selfId, x300350_g_MissionId ) == 1 then
		return
	end
	if IsHaveQuestNM( sceneId, selfId, SPOUSE_TASK[2] ) == 1 then
		return
	end
	
	if IsHaveQuestNM( sceneId, selfId, x300350_g_FatherMissionId ) == 1 then
		state = GetQuestStateNM(sceneId, selfId, targetId, x300350_g_FatherMissionId)
		AddQuestNumText(sceneId, MissionId, x300350_g_FatherMissionName, state, -1)
		return
	end
	AddQuestNumText(sceneId, MissionId, x300350_g_MissionName, state, -1)
	
end



--**********************************

--检测接受条件

--**********************************

function x300350_ProcAcceptCheck(sceneId, selfId, NPCId)

	--if HasTeam(sceneId, selfId) == 1 then
		return 1
	--end
end


--**********************************

--检测查看条件

--**********************************

function x300350_CheckPushList(sceneId, selfId, NPCId)
	return 1
end

function x300350_SendAcceptMissionMsg(sceneId, selfId, MissionId)
	local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
	local message = format("您接受了任务：【夫妻】爱情紫晶", MissionName);
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 4, 2);
end

function x300350_DoAccept( sceneId, selfId )

	local week = GetWeek()
	local today = GetDayOfYear()
	if week ~= 4 and week ~= 6 then
		return"很抱歉，只有周四、周六，才能进行本任务！"    
	end
	
	if 1 == IsQuestFullNM(sceneId, selfId) then
			return "很抱歉，您的任务已经满了，无法领取本任务。"
	end
	if HasTeam(sceneId, selfId) ~= 1 then
		return "很抱歉，您还未进行组队无法领取本任务。"
	end
	
	local teamSize = GetTeamSize(sceneId, selfId)
	
	if (GetTeamSize(sceneId, selfId) < 2) then
		return "很抱歉，您所在的队伍中成员小于2人，无法领取本任务。";
	end
	
	if (GetTeamSize(sceneId, selfId) > 2) then
		return "很抱歉，您所在的队伍中成员大于2人，无法领取本任务。";
	end

	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	if IsInDist(sceneId, selfId, targetId, 10) ~= 1 then
		return "很抱歉，您与配偶不在有效的距离内，无法进行本任务。";
	end
	
	if IsSpouses(sceneId, selfId, targetId) ~= 1 then
		return "很抱歉，您所在的队伍中成员不是夫妻关系，无法领取本任务。";
	end		
	
	if 1 == IsQuestFullNM(sceneId, targetId) then
			return "很抱歉，您配偶的任务已经满了，无法领取本任务。"
	end
	
	local completeDay = GetQuestData(sceneId, selfId, MD_SPOUSE_MISSION_DATE[1][1], MD_SPOUSE_MISSION_DATE[1][2],MD_SPOUSE_MISSION_DATE[1][3])
	if completeDay == today then
		return "很抱歉，您今天已经成功领取或完成过此任务！"
	end
	
	completeDay = GetQuestData(sceneId, targetId, MD_SPOUSE_MISSION_DATE[1][1], MD_SPOUSE_MISSION_DATE[1][2],MD_SPOUSE_MISSION_DATE[1][3])
	if completeDay == today then
		return "您的配偶领取了本任务，今天无法接取本任务。"
	end
	
	
	
	local bHaveMission = IsHaveQuest(sceneId, targetId, x300350_g_MissionId)
	if bHaveMission == 1 then
		return "您的配偶有本任务，无法接取本任务。"
	end
		
	if AddQuestNM( sceneId, selfId, x300350_g_MissionId ) ~= 1 then
		return "您添加任务失败，无法接取本任务。"
	end
	x300350_SetMissionData(sceneId, selfId)
	x300350_SendAcceptMissionMsg( sceneId, selfId, x300350_g_MissionId )
	
	if AddQuestNM( sceneId, targetId, x300350_g_MissionId ) ~= 1 then
		return "您的配偶添加任务失败，无法接取本任务。"
	end
	x300350_SetMissionData(sceneId, targetId)
	x300350_SendAcceptMissionMsg( sceneId, targetId, x300350_g_MissionId )
	
	return nil
end

--**********************************

--接受

--**********************************
function x300350_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	local str = x300350_DoAccept( sceneId, selfId )
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,8,2)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,str);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		
	end
	
end



--**********************************

--放弃

--**********************************

function x300350_ProcQuestAbandon(sceneId, selfId, MissionId)
	DelQuestNM( sceneId, selfId, MissionId )
	
	--local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
	local message = "您放弃了夫妻任务"
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 4, 2);
	
	x300350_SetMissionData(sceneId, selfId)
	
	--发可执行邮件给配偶
	local spouseGuid = GetSpouseGUID( sceneId, selfId )
	local spouseName = GetFriendName( sceneId, selfId, tonumber(spouseGuid) )
	SendScriptMail( sceneId, spouseName, MAIL_DELETE_MISSION, x300350_g_MissionId, 0, 0, selfId )
end



--**********************************

--检测是否可以提交

--**********************************

function x300350_CheckSubmit( sceneId, selfId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then
		return 0;
	end
	return 1
end


function x300350_CalculateEXP(level)
	local ExpBonus = 1000 *0.4*10* level
	if ExpBonus > 0 then
		return ExpBonus
	end
	return 0
end
--**********************************

--提交

--**********************************
function x300350_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	local retCode = x300350_SubmitFatherMissionCheck(sceneId, selfId, targetId)
	if retCode ~= nil then
		Msg2Player(sceneId,selfId,retCode,8,2)
		return
	end
	local spouseId = GetTeamSceneMember(sceneId, selfId, 0);
	local level = GetLevel(sceneId, selfId)
	local ExpBonus = x300350_CalculateEXP(level)
	local ret = x300350_IsMissionComplete( sceneId, selfId, x300350_g_FatherMissionId )
	if ret > 0 then
		AddExp(sceneId, selfId, ExpBonus);	
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "您完成了任务：【夫妻任务】");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "获得#R经验"..ExpBonus.."点#o的奖励");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		local Readme ="您完成了任务：【夫妻任务】#r获得#R经验"..ExpBonus.."点#o的奖励"
		Msg2Player(sceneId,selfId,Readme,8,2)
		DelQuestNM( sceneId, selfId, x300350_g_FatherMissionId )
		x300350_SetMissionData(sceneId, selfId)
	end

	local ret = x300350_IsMissionComplete( sceneId, spouseId, x300350_g_FatherMissionId )
	if ret > 0 then
		local level = GetLevel(sceneId, spouseId)
		local ExpBonus = x300350_CalculateEXP(level)
		AddExp(sceneId, spouseId, ExpBonus);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "您完成了任务：【夫妻任务】");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, spouseId);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "获得#R经验"..ExpBonus.."点#o的奖励");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, spouseId);
		local Readme ="您完成了任务：【夫妻任务】#r获得#R经验"..ExpBonus.."点#o的奖励"
		Msg2Player(sceneId,spouseId,Readme,8,2)
		DelQuestNM( sceneId, spouseId, x300350_g_FatherMissionId )
		x300350_SetMissionData(sceneId, spouseId)
	end
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x300350_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end



--**********************************

--进入区域事件

--**********************************

function x300350_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x300350_ProcTiming(sceneId, selfId )
	 
		
end

function x300350_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x300350_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId, nChangeType)
    
  if MissionId == nil or MissionId < 0 then
      return
  end
  
  if IsHaveQuestNM(sceneId,selfId,MissionId) <= 0 then
      return
  end
  
  if itemdataId ~= x300350_g_MissionItem then
  	return
  end
    
	local NeedNum, ObjIndex = GetQuestNeedItemNumNM( sceneId, selfId, MissionId, itemdataId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	
	if 1 == nChangeType then -- 删除任务物品
		local Num = GetItemCount( sceneId, selfId, itemdataId )
		SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )
		if Num < NeedNum then
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
		end
		x300350_RefreshItemNum( sceneId, selfId, MissionId)
		return
	end
	
	if NeedNum > 0 then
		local Num = GetItemCount( sceneId, selfId, itemdataId )
		if Num < NeedNum then --还没有完成任务
            if nChangeType == 0 then --删除物品，不提示
                BeginQuestEvent(sceneId)
                local strText = format("#Y获得物品#G#{_ITEM%d}#Y: %d/%d", itemdataId, Num, NeedNum )
                if strText == nil then
                    strText = "";
                end
                AddQuestText( sceneId, strText )
                EndQuestEvent( sceneId )
                DispatchQuestTips( sceneId, selfId )
            end
			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )         --by zheng
		elseif Num == NeedNum then
			--已经完成任务
            if nChangeType == 0 then --删除物品，不提示
                BeginQuestEvent(sceneId)
                local strText = format( "#Y已完成获得物品#G#{_ITEM%d}#Y: %d/%d", itemdataId, Num, NeedNum )
                if strText == nil then
                    strText = "";
                end
                AddQuestText( sceneId, strText )
                EndQuestEvent( sceneId )
                DispatchQuestTips( sceneId, selfId )
                SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
            end
			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )         --by zheng
		end
	x300350_RefreshItemNum( sceneId, selfId, MissionId)
	end
end
function x300350_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没有这个任务
		return
	end
	
end

function x300350_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x300350_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x300350_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x300350_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x300350_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x300350_RefreshItemNum( sceneId, selfId, MissionId)
	x300350_QuestLogRefresh( sceneId, selfId, MissionId)
end

function x300350_QuestLogRefresh( sceneId, selfId, MissionId)
	BeginQuestEvent(sceneId)
	local level = GetLevel(sceneId, selfId)
	local ExpBonus = 1000 *0.4*10* level
    if ExpBonus > 0 then
		AddQuestExpBonus(sceneId,  ExpBonus);
	end
		
	if MissionId == nil or MissionId < 0 then
        return
    end
    
    if IsHaveQuestNM(sceneId,selfId,MissionId) <= 0 then
        return
    end
    
	local NeedNum, ObjIndex = GetQuestNeedItemNumNM( sceneId, selfId, MissionId, x300350_g_MissionItem )
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local curNum = GetQuestParam(sceneId, selfId, misIndex, ObjIndex)
	local szTarget = "(" .. curNum .. "/" .. NeedNum .. ")"
	AddQuestLogCustomText( sceneId,
							"标题",						-- 标题
							"" .. x300350_g_MissionName,        -- 任务名字
							"  去@npc_72044采集@item_13080009，交给@npc_140002" .. szTarget,		--任务目标
							"@npc_140002",			--任务NPC
							"",               --任务攻略
							"\t在大都的东门附近，生长着一种紫色的水晶。#r\t据说得到紫水晶的情侣会受到爱的祝福。#r\t到达大都@npc_72044，采集5个紫水晶回来交给@npc_140002，他正在收集带有爱意的紫水晶，将紫水晶交给他，就可以得到他对您们爱的祝福。",	--任务描述
							"【夫妻任务】进行的整个过程中，您必须与配偶形影不离，否则您将不能领取或提交任务！"					--任务小提示
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
end

function x300350_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	x300350_QuestLogRefresh( sceneId, selfId, MissionId );
end

function x300350_CheckSubmitNPC( sceneId,selfId,idScript,idMission,npcGUID )
	if IsHaveQuestNM( sceneId, selfId, x300350_g_FatherMissionId ) == 0 then
		-- 如果没有这个任务
		return 0
	end
	for i, npcItem in SPOUSE_NPC do
		if npcItem == npcGUID then
			return 1
		end
	end
	return 0
end
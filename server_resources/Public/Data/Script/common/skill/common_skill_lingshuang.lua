--领取双倍经验

--MisDescBegin
x561002_g_ScriptId = 561002
x561002_g_MissionIdPre =-1
--x561002_g_MissionId = 
x561002_g_MissionKind = 8
x561002_g_LevelLess	= 	-1 
x561002_g_MissionIdNext = -1
x561002_g_Name	="" 
x561002_g_noDemandItem ={}
x561002_g_ExtTarget={}
x561002_g_MissionHelp =	""
x561002_g_MissionName1="【领取双倍时间说明】"
x561002_g_MissionName2="领取1小时双倍时间"
x561002_g_MissionName3="领取30分钟双倍时间"
x561002_g_MissionName4="本周剩余双倍时间"
x561002_g_MissionName5="领取2小时双倍时间"
x561002_g_MissionName6="领取4小时双倍时间"
x561002_g_MissionName7="冻结双倍时间"
x561002_g_MissionName8="解冻双倍时间"



x561002_g_MissionInfo="\t当你到达#R20级#W，你每周共有#G5个小时#W的双倍时间可以#G免费领取并使用#W。\n\t在双倍时间里，从怪物身上所获得的战斗经验将翻倍！\n\t您也可以冻结已领取的双倍时间以供下次使用。"  --任务描述
x561002_g_MissionTarget=""		                                                                                               
x561002_g_MissionCompleted1="你成功领取了1小时双倍经验"--完成任务npc说话的话
x561002_g_MissionCompleted2="你成功领取了2小时双倍经验"--完成任务npc说话的话
x561002_g_MissionCompleted3="你成功领取了4小时双倍经验"--完成任务npc说话的话
x561002_g_ContinueInfo1="\t你是否要领取#G1小时#W双倍经验？双倍经验的持续时间#R可以#W叠加。"
x561002_g_ContinueInfo2="\t你是否要领取#G2小时#W双倍经验？双倍经验的持续时间#R可以#W叠加。"
x561002_g_ContinueInfo3="\t您现在正在双倍经验时间里。"
x561002_g_ContinueInfo4="\t你是否要领取#G4小时#W双倍经验？双倍经验的持续时间#R可以#W叠加。"

x561002_g_ContinueInfo5="\t你要冻结双倍经验时间吗？冻结双倍经验时间可以使你的双倍经验不再随时间流逝。\n\t如果你希望重新获得这些冻结的双倍时间，可以使用#G解冻功能#W。\n\t注意，双倍时间最多可以冻结#R5小时#W！多余的双倍将会#R消失#W！"
x561002_g_ContinueInfo6="\t#Y您没有冻结双倍时间，无需解冻"
x561002_g_ContinueInfo7="\t#Y您的双倍时间已经解冻"

x561002_g_ErrorInfo1="你本周的双倍时间已经不足1小时，无法领取！"
x561002_g_ErrorInfo2="你本周的双倍时间已经不足2小时，无法领取！"
x561002_g_ErrorInfo3="你本周的双倍时间已经不足4小时，无法领取！"
x561002_g_BonusMoney1 =0
x561002_g_BonusMoney2 =0
x561002_g_BonusMoney3 =0
x561002_g_BonusItem	=	{}
x561002_g_BonusChoiceItem ={}
x561002_g_ExpBonus = 250
x561002_g_SkillHalfHour = 7510
x561002_g_SkillOneHour = 7511

x561002_g_maxtimes = 5 --最多领双次数（单位：1小时）
x561002_g_defualtdialog = "\t圣人曰：不舍昼夜。要想高人一等的话，必须勤奋加上正确的方法。"
x561002_g_otherdialog = "\n\t#Y本周您还可以领取#W#G%s小时#W#Y双倍经验#W"
x561002_g_errordialog = "\n\t#R本周剩余双倍时间为0小时，请通过购买双倍经验道具获得双倍经验#W"
x561002_g_fulldialog = "\n\t#Y本周您还可以领取#W#G%s小时#W#Y双倍经验#W"
x561002_g_jiedong = "\t你是否要解冻双倍经验时间？你现在冻结的双倍经验时间为：#G%d小时%d分钟#W。"
--MisDescEnd

function x561002_CheckDongShuang(sceneId, selfId, buffTimer)
	if buffTimer > 0 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"处于双倍冻结状态，无法领取") 
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
		return 0
	end
	return 1
end

--**********************************

--任务入口函数

--**********************************
function x561002_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本
	--检测列出条件
	local status1 = (IsHaveSpecificImpact(sceneId, selfId,x561002_g_SkillHalfHour))
	local status2 = (IsHaveSpecificImpact(sceneId, selfId,x561002_g_SkillOneHour))
	local level = GetLevel(sceneId,selfId)
	local buffTimer = x561002_GetRecordData( sceneId, selfId ) 

	if extid == 1 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x561002_g_MissionName1)
			AddQuestText(sceneId,x561002_g_MissionInfo)
		EndQuestEvent()
		x561002_SetSelected(sceneId, selfId, 1)
		DispatchQuestEventList(sceneId, selfId,targetId,x561002_g_ScriptId, x561002_g_MissionName1)

	elseif extid == 2 then -- 1小时
		if x561002_CheckDongShuang(sceneId, selfId, buffTimer) <= 0 then
			x561002_SetSelected(sceneId, selfId, 0)
			return
		end
		if level < 20 then
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"#Y"..x561002_g_MissionName2)
					AddQuestText(sceneId,"\t等级不足,无法领取双倍经验！")
				EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, targetId, x561002_g_ScriptId, x561002_g_MissionName2)
		elseif level >= 20 then
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x561002_g_MissionName2)
				AddQuestText(sceneId,x561002_g_ContinueInfo1)
			EndQuestEvent()
			DispatchQuestInfo(sceneId, selfId, targetId, x561002_g_ScriptId, -1)
			x561002_SetSelected(sceneId, selfId, 2)
		end

	elseif extid == 3 then -- 2小时
		if x561002_CheckDongShuang(sceneId, selfId, buffTimer) <= 0 then
			x561002_SetSelected(sceneId, selfId, 0)
			return
		end
		if level < 20 then
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x561002_g_MissionName5)
				AddQuestText(sceneId,"\t等级不足,无法领取双倍经验！")
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, targetId, x561002_g_ScriptId, x561002_g_MissionName5)
		elseif  level >= 20 then
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x561002_g_MissionName5)
				AddQuestText(sceneId,x561002_g_ContinueInfo2)
			EndQuestEvent()
			DispatchQuestInfo(sceneId, selfId, targetId, x561002_g_ScriptId, -1)
			x561002_SetSelected(sceneId, selfId, 3)
		end
	
	elseif extid == 4 then -- 4小时
		if x561002_CheckDongShuang(sceneId, selfId, buffTimer) <= 0 then
			x561002_SetSelected(sceneId, selfId, 0)
			return
		end
		if level < 20 then
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x561002_g_MissionName6)
				AddQuestText(sceneId,"\t等级不足,无法领取双倍经验！")
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, targetId, x561002_g_ScriptId, x561002_g_MissionName6)
		elseif  level >= 20 then
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x561002_g_MissionName6)
				AddQuestText(sceneId,x561002_g_ContinueInfo4)
			EndQuestEvent()
			DispatchQuestInfo(sceneId, selfId, targetId, x561002_g_ScriptId, -1)
			x561002_SetSelected(sceneId, selfId, 4)
		end
	
	elseif extid == 5 then
		if( IsHaveSpecificImpact( sceneId, selfId, x561002_g_SkillOneHour ) <= 0 ) then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "不处于双倍状态，无法冻双") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
			x561002_SetSelected(sceneId, selfId, 0)
			return
		else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x561002_g_MissionName7)
				AddQuestText(sceneId,x561002_g_ContinueInfo5)
			EndQuestEvent()
			DispatchQuestInfo(sceneId, selfId, targetId, x561002_g_ScriptId, -1)
			x561002_SetSelected(sceneId, selfId, 5)
		end
	elseif extid == 6 then
		local buffTimer = x561002_GetRecordData( sceneId, selfId ) 
		if buffTimer <= 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "不处于冻双状态，无法解冻") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
			x561002_SetSelected(sceneId, selfId, 0)
			return
		else
			local h = floor( buffTimer /60 )
			local m = mod(buffTimer,60)
			local strFmt = format( x561002_g_jiedong, h,m)
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x561002_g_MissionName8)
				AddQuestText(sceneId,strFmt)
			EndQuestEvent()
			DispatchQuestInfo(sceneId, selfId, targetId, x561002_g_ScriptId, -1)
			x561002_SetSelected(sceneId, selfId, 6)
		end
	end

end



--**********************************

--列举事件

--**********************************

function x561002_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	local level = GetLevel(sceneId,selfId)
	if level < 20 then
		AddQuestText(sceneId,x561002_g_defualtdialog)
		AddQuestNumText(sceneId, x561002_g_ScriptId, x561002_g_MissionName1,0,1)
		return
	end
		
	if GetSceneRelation(sceneId, selfId, sceneId) == 1 then
		local weekcount = x561002_GetWeekCount(sceneId, selfId)
		if weekcount >= x561002_g_maxtimes then
			AddQuestText(sceneId,x561002_g_defualtdialog)
			AddQuestText(sceneId,x561002_g_errordialog)
		else
			local str = format( x561002_g_otherdialog, (x561002_g_maxtimes-weekcount) )
			AddQuestText(sceneId,x561002_g_defualtdialog)
			AddQuestText(sceneId, str)
		end
		
		local strFmt
		local buffTimer = x561002_GetRecordData( sceneId, selfId ) 
		
		if buffTimer > 0 then
			local strDongShuang = "解冻双倍时间#G(%d小时%d分)"
			local h = floor( buffTimer /60 )
			local m = mod(buffTimer,60)
			strFmt = format( strDongShuang, h,m)
		else
			strFmt = "解冻双倍时间"
		end
		AddQuestNumText(sceneId, x561002_g_ScriptId, x561002_g_MissionName2,3,2)
		AddQuestNumText(sceneId, x561002_g_ScriptId, x561002_g_MissionName5,3,3)
		AddQuestNumText(sceneId, x561002_g_ScriptId, x561002_g_MissionName6,3,4)
		AddQuestNumText(sceneId, x561002_g_ScriptId, x561002_g_MissionName7,3,5)
		AddQuestNumText(sceneId, x561002_g_ScriptId, strFmt,3,6)
		AddQuestNumText(sceneId, x561002_g_ScriptId, x561002_g_MissionName1,0,1)
		
	else 
			return
	end
	
end



--**********************************

--检测接受条件

--**********************************

function x561002_ProcAcceptCheck(sceneId, selfId, NPCId)

	return 1
end


--**********************************

--检测查看条件

--**********************************

function x561002_CheckPushList(sceneId, selfId, NPCId)
	
end


function x561002_SendLingshangImpact(sceneId, selfId, currentContinuance)

	local lastContinuance = -1
	if( IsHaveSpecificImpact( sceneId, selfId, x561002_g_SkillOneHour ) > 0 ) then
		local ImpactContinuance = GetImpactContinuanceByDataIndex(sceneId, selfId, x561002_g_SkillOneHour) + currentContinuance
		lastContinuance = ImpactContinuance - GetImpactContinuanceElapsed(sceneId, selfId, x561002_g_SkillOneHour)

		if 2147483647 - lastContinuance < ImpactContinuance then
			ImpactContinuance = 2147483647 - lastContinuance
		end
	else
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x561002_g_SkillOneHour, 0);
		lastContinuance = currentContinuance
	end
	
	if lastContinuance >= 0 then
		SetImpactContinuanceByDataIndex( sceneId, selfId, x561002_g_SkillOneHour, lastContinuance )
		ResetImpactContinuanceElapsed(sceneId, selfId, x561002_g_SkillOneHour)
		RefreshImpactByDataIndex(sceneId, selfId, x561002_g_SkillOneHour)
	end
end


--**********************************

--接受

--**********************************

function x561002_ProcAccept( sceneId, selfId )

	local Flag = x561002_GetSelected(sceneId, selfId)
	local weekcount = x561002_GetWeekCount(sceneId, selfId)
	local HourToMilSec = 60*60*1000
	if Flag == 1 then
		x561002_SetSelected(sceneId, selfId, 0)
		if weekcount <= x561002_g_maxtimes then
		 	BeginQuestEvent(sceneId)
				AddQuestText(sceneId,x561002_g_MissionInfo) 
			EndQuestEvent()
		end
		
	elseif Flag == 2 then	--1小时
		x561002_SetSelected(sceneId, selfId, 0)

		local remantimes = x561002_g_maxtimes - weekcount
		if remantimes >= 1 then
		 	BeginQuestEvent(sceneId)
				x561002_SendLingshangImpact( sceneId, selfId, HourToMilSec )
				AddQuestText(sceneId, x561002_g_MissionCompleted1) 
				x561002_SetWeekCount(sceneId, selfId, weekcount + 1)
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
		else 
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,x561002_g_ErrorInfo1) 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
		end	
		
	elseif Flag == 3 then --2小时
		x561002_SetSelected(sceneId, selfId, 0)
		local remantimes = x561002_g_maxtimes - weekcount
		if remantimes >= 2 then
		 	BeginQuestEvent(sceneId)
				x561002_SendLingshangImpact( sceneId, selfId, HourToMilSec * 2 )
				AddQuestText(sceneId, x561002_g_MissionCompleted2) 
				x561002_SetWeekCount(sceneId, selfId, weekcount + 2)
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
		else 
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,x561002_g_ErrorInfo2) 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
		end
	elseif Flag == 4 then --4小时
		x561002_SetSelected(sceneId, selfId, 0)
		local remantimes = x561002_g_maxtimes - weekcount
		if remantimes >= 4 then
		 	BeginQuestEvent(sceneId)
				x561002_SendLingshangImpact( sceneId, selfId, HourToMilSec * 4 )
				AddQuestText(sceneId, x561002_g_MissionCompleted3) 
				x561002_SetWeekCount(sceneId, selfId, weekcount + 4)
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
		else 
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,x561002_g_ErrorInfo3) 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
		end

	elseif Flag == 5 then --冻双
		x561002_SetSelected(sceneId, selfId, 0)
		local buffTimer = x561002_GetRecordData( sceneId, selfId ) 

		local ImpactContinuance = GetImpactContinuanceByDataIndex(sceneId, selfId, x561002_g_SkillOneHour)
		local lastContinuance = ImpactContinuance - GetImpactContinuanceElapsed(sceneId, selfId, x561002_g_SkillOneHour)
		lastContinuance = lastContinuance * 0.001 / 60 --转换为分钟
		lastContinuance = lastContinuance + buffTimer
		if lastContinuance > 300 then 
			lastContinuance = 300
		end
		x561002_RecordData(sceneId, selfId, lastContinuance)
		CancelSpecificImpact( sceneId, selfId, x561002_g_SkillOneHour )

	elseif Flag == 6 then --解冻
		x561002_SetSelected(sceneId, selfId, 0)
		local ImpactContinuance = GetImpactContinuanceByDataIndex(sceneId, selfId, x561002_g_SkillOneHour)
		local lastContinuance = ImpactContinuance - GetImpactContinuanceElapsed(sceneId, selfId, x561002_g_SkillOneHour)
		local buffTimer = x561002_GetRecordData( sceneId, selfId )
		buffTimer = buffTimer * 60 * 1000
		buffTimer = buffTimer + lastContinuance
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x561002_g_SkillOneHour, 0);
		
		SetImpactContinuanceByDataIndex( sceneId, selfId, x561002_g_SkillOneHour, buffTimer )
		ResetImpactContinuanceElapsed(sceneId, selfId, x561002_g_SkillOneHour)
		RefreshImpactByDataIndex(sceneId, selfId, x561002_g_SkillOneHour)

		x561002_RecordData(sceneId, selfId, 0)

	end
end

function x561002_RecordData(sceneId, selfId,timer)
	SetQuestData(sceneId,selfId,MD_SKILL_LING_SHUANG[1],MD_SKILL_LING_SHUANG[2],MD_SKILL_LING_SHUANG[3],timer)
end

function x561002_GetRecordData(sceneId, selfId)
	local result = GetQuestData(sceneId, selfId, MD_SKILL_LING_SHUANG[1], MD_SKILL_LING_SHUANG[2],MD_SKILL_LING_SHUANG[3] )
	return result
end

--**********************************

--放弃

--**********************************

function x561002_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x561002_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--提交

--**********************************

function x561002_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x561002_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x561002_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x561002_ProcTiming(sceneId, selfId )
	 
		
end

function x561002_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x561002_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x561002_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x561002_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x561002_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x561002_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x561002_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x561002_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x561002_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

---------------------------------------------------------------------------------------------------
--取得当周已经领取的次数
---------------------------------------------------------------------------------------------------
function x561002_GetWeekCount(sceneId, selfId)
	local nowtime = GetCurrentTime() + 8 * 3600
	local thisweek = floor(nowtime / 86400) - 14249 --定位到2009年1月5日
	thisweek = floor(thisweek / 7)

	local lastweek = GetQuestData(sceneId, selfId, MD_DOUBLE_DATE[1], MD_DOUBLE_DATE[2],MD_DOUBLE_DATE[3] )

	if lastweek ~= thisweek then
		return 0
	end

	local weekcount = GetQuestData(sceneId, selfId, MD_DOUBLE_TIMES[1], MD_DOUBLE_TIMES[2],MD_DOUBLE_TIMES[3] )
	return weekcount
end

---------------------------------------------------------------------------------------------------
--设置当周已经领取的次数
---------------------------------------------------------------------------------------------------
function x561002_SetWeekCount(sceneId, selfId, count)
	local nowtime = GetCurrentTime() + 8 * 3600
	local thisweek = floor(nowtime / 86400) - 14249 --定位到2009年1月5日
	thisweek = floor(thisweek / 7)

	local lastweek = GetQuestData(sceneId, selfId, MD_DOUBLE_DATE[1], MD_DOUBLE_DATE[2],MD_DOUBLE_DATE[3] )

	if lastweek ~= thisweek then
		SetQuestData(sceneId, selfId, MD_DOUBLE_DATE[1], MD_DOUBLE_DATE[2], MD_DOUBLE_DATE[3], thisweek)
		SetQuestData(sceneId, selfId, MD_DOUBLE_TIMES[1], MD_DOUBLE_TIMES[2], MD_DOUBLE_TIMES[3], count)
	else
		SetQuestData(sceneId, selfId, MD_DOUBLE_TIMES[1], MD_DOUBLE_TIMES[2], MD_DOUBLE_TIMES[3], count)
	end

end

---------------------------------------------------------------------------------------------------
--得到玩家刚才选择的界面选项
---------------------------------------------------------------------------------------------------
function x561002_GetSelected(sceneId, selfId)
	local flag = GetQuestData(sceneId, selfId, MD_DOUBLE_TIMES_FLAG[1], MD_DOUBLE_TIMES_FLAG[2],MD_DOUBLE_TIMES_FLAG[3] )
	return flag
end

---------------------------------------------------------------------------------------------------
--设置玩家刚才选择的界面选项
---------------------------------------------------------------------------------------------------
function x561002_SetSelected(sceneId, selfId, flag)
	SetQuestData(sceneId, selfId, MD_DOUBLE_TIMES_FLAG[1], MD_DOUBLE_TIMES_FLAG[2], MD_DOUBLE_TIMES_FLAG[3], flag)
end

--��ȡ˫������

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
x561002_g_MissionName1="����ȡ˫��ʱ��˵����"
x561002_g_MissionName2="��ȡ1Сʱ˫��ʱ��"
x561002_g_MissionName3="��ȡ30����˫��ʱ��"
x561002_g_MissionName4="����ʣ��˫��ʱ��"
x561002_g_MissionName5="��ȡ2Сʱ˫��ʱ��"
x561002_g_MissionName6="��ȡ4Сʱ˫��ʱ��"
x561002_g_MissionName7="����˫��ʱ��"
x561002_g_MissionName8="�ⶳ˫��ʱ��"



x561002_g_MissionInfo="\t���㵽��#R20��#W����ÿ�ܹ���#G5��Сʱ#W��˫��ʱ�����#G�����ȡ��ʹ��#W��\n\t��˫��ʱ����ӹ�����������õ�ս�����齫������\n\t��Ҳ���Զ�������ȡ��˫��ʱ���Թ��´�ʹ�á�"  --��������
x561002_g_MissionTarget=""		                                                                                               
x561002_g_MissionCompleted1="��ɹ���ȡ��1Сʱ˫������"--�������npc˵���Ļ�
x561002_g_MissionCompleted2="��ɹ���ȡ��2Сʱ˫������"--�������npc˵���Ļ�
x561002_g_MissionCompleted3="��ɹ���ȡ��4Сʱ˫������"--�������npc˵���Ļ�
x561002_g_ContinueInfo1="\t���Ƿ�Ҫ��ȡ#G1Сʱ#W˫�����飿˫������ĳ���ʱ��#R����#W���ӡ�"
x561002_g_ContinueInfo2="\t���Ƿ�Ҫ��ȡ#G2Сʱ#W˫�����飿˫������ĳ���ʱ��#R����#W���ӡ�"
x561002_g_ContinueInfo3="\t����������˫������ʱ���"
x561002_g_ContinueInfo4="\t���Ƿ�Ҫ��ȡ#G4Сʱ#W˫�����飿˫������ĳ���ʱ��#R����#W���ӡ�"

x561002_g_ContinueInfo5="\t��Ҫ����˫������ʱ���𣿶���˫������ʱ�����ʹ���˫�����鲻����ʱ�����š�\n\t�����ϣ�����»����Щ�����˫��ʱ�䣬����ʹ��#G�ⶳ����#W��\n\tע�⣬˫��ʱ�������Զ���#R5Сʱ#W�������˫������#R��ʧ#W��"
x561002_g_ContinueInfo6="\t#Y��û�ж���˫��ʱ�䣬����ⶳ"
x561002_g_ContinueInfo7="\t#Y����˫��ʱ���Ѿ��ⶳ"

x561002_g_ErrorInfo1="�㱾�ܵ�˫��ʱ���Ѿ�����1Сʱ���޷���ȡ��"
x561002_g_ErrorInfo2="�㱾�ܵ�˫��ʱ���Ѿ�����2Сʱ���޷���ȡ��"
x561002_g_ErrorInfo3="�㱾�ܵ�˫��ʱ���Ѿ�����4Сʱ���޷���ȡ��"
x561002_g_BonusMoney1 =0
x561002_g_BonusMoney2 =0
x561002_g_BonusMoney3 =0
x561002_g_BonusItem	=	{}
x561002_g_BonusChoiceItem ={}
x561002_g_ExpBonus = 250
x561002_g_SkillHalfHour = 7510
x561002_g_SkillOneHour = 7511

x561002_g_maxtimes = 5 --�����˫��������λ��1Сʱ��
x561002_g_defualtdialog = "\tʥ��Ի��������ҹ��Ҫ�����һ�ȵĻ��������ڷܼ�����ȷ�ķ�����"
x561002_g_otherdialog = "\n\t#Y��������������ȡ#W#G%sСʱ#W#Y˫������#W"
x561002_g_errordialog = "\n\t#R����ʣ��˫��ʱ��Ϊ0Сʱ����ͨ������˫��������߻��˫������#W"
x561002_g_fulldialog = "\n\t#Y��������������ȡ#W#G%sСʱ#W#Y˫������#W"
x561002_g_jiedong = "\t���Ƿ�Ҫ�ⶳ˫������ʱ�䣿�����ڶ����˫������ʱ��Ϊ��#G%dСʱ%d����#W��"
--MisDescEnd

function x561002_CheckDongShuang(sceneId, selfId, buffTimer)
	if buffTimer > 0 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"����˫������״̬���޷���ȡ") 
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
		return 0
	end
	return 1
end

--**********************************

--������ں���

--**********************************
function x561002_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����
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

	elseif extid == 2 then -- 1Сʱ
		if x561002_CheckDongShuang(sceneId, selfId, buffTimer) <= 0 then
			x561002_SetSelected(sceneId, selfId, 0)
			return
		end
		if level < 20 then
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"#Y"..x561002_g_MissionName2)
					AddQuestText(sceneId,"\t�ȼ�����,�޷���ȡ˫�����飡")
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

	elseif extid == 3 then -- 2Сʱ
		if x561002_CheckDongShuang(sceneId, selfId, buffTimer) <= 0 then
			x561002_SetSelected(sceneId, selfId, 0)
			return
		end
		if level < 20 then
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x561002_g_MissionName5)
				AddQuestText(sceneId,"\t�ȼ�����,�޷���ȡ˫�����飡")
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
	
	elseif extid == 4 then -- 4Сʱ
		if x561002_CheckDongShuang(sceneId, selfId, buffTimer) <= 0 then
			x561002_SetSelected(sceneId, selfId, 0)
			return
		end
		if level < 20 then
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x561002_g_MissionName6)
				AddQuestText(sceneId,"\t�ȼ�����,�޷���ȡ˫�����飡")
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
			AddQuestText(sceneId, "������˫��״̬���޷���˫") 
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
			AddQuestText(sceneId, "�����ڶ�˫״̬���޷��ⶳ") 
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

--�о��¼�

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
			local strDongShuang = "�ⶳ˫��ʱ��#G(%dСʱ%d��)"
			local h = floor( buffTimer /60 )
			local m = mod(buffTimer,60)
			strFmt = format( strDongShuang, h,m)
		else
			strFmt = "�ⶳ˫��ʱ��"
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

--����������

--**********************************

function x561002_ProcAcceptCheck(sceneId, selfId, NPCId)

	return 1
end


--**********************************

--���鿴����

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

--����

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
		
	elseif Flag == 2 then	--1Сʱ
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
		
	elseif Flag == 3 then --2Сʱ
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
	elseif Flag == 4 then --4Сʱ
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

	elseif Flag == 5 then --��˫
		x561002_SetSelected(sceneId, selfId, 0)
		local buffTimer = x561002_GetRecordData( sceneId, selfId ) 

		local ImpactContinuance = GetImpactContinuanceByDataIndex(sceneId, selfId, x561002_g_SkillOneHour)
		local lastContinuance = ImpactContinuance - GetImpactContinuanceElapsed(sceneId, selfId, x561002_g_SkillOneHour)
		lastContinuance = lastContinuance * 0.001 / 60 --ת��Ϊ����
		lastContinuance = lastContinuance + buffTimer
		if lastContinuance > 300 then 
			lastContinuance = 300
		end
		x561002_RecordData(sceneId, selfId, lastContinuance)
		CancelSpecificImpact( sceneId, selfId, x561002_g_SkillOneHour )

	elseif Flag == 6 then --�ⶳ
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

--����

--**********************************

function x561002_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x561002_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x561002_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x561002_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x561002_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x561002_ProcTiming(sceneId, selfId )
	 
		
end

function x561002_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

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
--ȡ�õ����Ѿ���ȡ�Ĵ���
---------------------------------------------------------------------------------------------------
function x561002_GetWeekCount(sceneId, selfId)
	local nowtime = GetCurrentTime() + 8 * 3600
	local thisweek = floor(nowtime / 86400) - 14249 --��λ��2009��1��5��
	thisweek = floor(thisweek / 7)

	local lastweek = GetQuestData(sceneId, selfId, MD_DOUBLE_DATE[1], MD_DOUBLE_DATE[2],MD_DOUBLE_DATE[3] )

	if lastweek ~= thisweek then
		return 0
	end

	local weekcount = GetQuestData(sceneId, selfId, MD_DOUBLE_TIMES[1], MD_DOUBLE_TIMES[2],MD_DOUBLE_TIMES[3] )
	return weekcount
end

---------------------------------------------------------------------------------------------------
--���õ����Ѿ���ȡ�Ĵ���
---------------------------------------------------------------------------------------------------
function x561002_SetWeekCount(sceneId, selfId, count)
	local nowtime = GetCurrentTime() + 8 * 3600
	local thisweek = floor(nowtime / 86400) - 14249 --��λ��2009��1��5��
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
--�õ���Ҹղ�ѡ��Ľ���ѡ��
---------------------------------------------------------------------------------------------------
function x561002_GetSelected(sceneId, selfId)
	local flag = GetQuestData(sceneId, selfId, MD_DOUBLE_TIMES_FLAG[1], MD_DOUBLE_TIMES_FLAG[2],MD_DOUBLE_TIMES_FLAG[3] )
	return flag
end

---------------------------------------------------------------------------------------------------
--������Ҹղ�ѡ��Ľ���ѡ��
---------------------------------------------------------------------------------------------------
function x561002_SetSelected(sceneId, selfId, flag)
	SetQuestData(sceneId, selfId, MD_DOUBLE_TIMES_FLAG[1], MD_DOUBLE_TIMES_FLAG[2], MD_DOUBLE_TIMES_FLAG[3], flag)
end

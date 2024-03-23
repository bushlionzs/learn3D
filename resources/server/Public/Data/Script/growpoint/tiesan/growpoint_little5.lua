--������

x301425_g_GrowpointId = 708 		--��Ӧ������ID

x301425_g_MissionId = 7538
x301425_g_BuffList={7709,7710,7711}

x301425_g_StateBuff = {{{7610,7607},{7608,7605}}, {{7616,7613},{7614,7611}}, {{7622,7619},{7620,7617}}, {{7628,7625},{7626,7623}}}
-- �����г�buff
function x301425_SendStateBuff(sceneId, selfId)
	local country = GetCurCountry( sceneId, selfId )
	local sex = GetSex( sceneId, selfId )
	
	SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x301425_g_StateBuff[country+1][2][sex+1], 0)
end

function x301425_CancelStateBuff(sceneId, selfId)
	local country = GetCurCountry( sceneId, selfId )
	local sex = GetSex( sceneId, selfId )
	
	if IsHaveSpecificImpact( sceneId, selfId, x301425_g_StateBuff[country+1][2][sex+1] ) > 0 then
		CancelSpecificImpact(sceneId, selfId,x301425_g_StateBuff[country+1][2][sex+1])
	end
end

function x301425_RandBuff(sceneId, selfId)
	local kindIndex = random(1, 100)
	if kindIndex < 0 or kindIndex > 100 then
		kindIndex = 0
	end
	
	if kindIndex <= 60 then
		return x301425_g_BuffList[1]
	elseif kindIndex <= 80 then
		return x301425_g_BuffList[2]
	else
		return x301425_g_BuffList[3]
	end
end


--���ɺ�����ʼ************************************************************************
function 	x301425_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301425_g_GrowpointId, sceneId, 0, -1)
	SetGrowPointObjID(sceneId,x301425_g_GrowpointId,x, y,ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301425_OnOpen(sceneId,selfId,targetId)
		--PrintStr("x301425_OnOpen")
    return x301425_OnOpenItemBox(sceneId, selfId, targetId, x301425_g_GrowpointId, -1)	
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301425_OnRecycle(sceneId,selfId,targetId)
	return   x301425_OnGuildRecycle( sceneId, selfId, targetId, x301425_g_GrowpointId, -1 )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301425_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301425_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--**********************************************************************
--�ɼ�����
--��ItemBox
function x301425_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	
	if IsHaveQuestNM( sceneId, selfId, x301425_g_MissionId ) <= 0 then
		Msg2Player(sceneId,selfId,"��û�������塿�������������עϵͳ���档",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		return -31
	end
	    
	return 0
end

--����
function x301425_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )
	
	local buff = x301425_RandBuff(sceneId, selfId)
	
	if buff == 7709 then
		if IsHaveSpecificImpact( sceneId, selfId, 7710 ) > 0 then
			CancelSpecificImpact(sceneId, selfId,7710)
		end
		x301425_SendStateBuff(sceneId, selfId)
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, buff, 0)
		Msg2Player(sceneId,selfId,"���������ﳵ״̬�������ٶ�15�룡",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		return 1
	elseif buff == 7710 then
		if IsHaveSpecificImpact( sceneId, selfId, 7709 ) > 0 then
			CancelSpecificImpact(sceneId, selfId,7709)
		end
		x301425_CancelStateBuff(sceneId, selfId)
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, buff, 0)
		Msg2Player(sceneId,selfId,"�ܲ��ң������ƶ��ٶ�5�룡",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		return 1
	elseif buff == 7711 then
		if IsHaveSpecificImpact( sceneId, selfId, buff ) > 0 then
			CancelSpecificImpact(sceneId, selfId,buff)
		end
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, buff, 1000)
		Msg2Player(sceneId,selfId,"�ܲ��ң�ѣ��2�룡",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		return 1
	end
	return 0
end
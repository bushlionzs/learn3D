--������

x301431_g_GrowpointId = 710 		--��Ӧ������ID

x301431_g_MissionId = 7538
x301431_g_BuffList={7709,7710,7711,0}
x301431_g_SubmitNpc = 139102

--���ɺ�����ʼ************************************************************************
function 	x301431_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301431_g_GrowpointId, sceneId, 0, -1)
	SetGrowPointObjID(sceneId,x301431_g_GrowpointId,x, y,ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301431_OnOpen(sceneId,selfId,targetId)
		--PrintStr("x301431_OnOpen")
    return x301431_OnOpenItemBox(sceneId, selfId, targetId, x301431_g_GrowpointId, -1)	
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301431_OnRecycle(sceneId,selfId,targetId)
	return   x301431_OnGuildRecycle( sceneId, selfId, targetId, x301431_g_GrowpointId, -1 )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301431_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301431_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--**********************************************************************
--�ɼ�����
--��ItemBox
function x301431_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	
	if IsHaveQuestNM( sceneId, selfId, x301431_g_MissionId ) <= 0 then
		Msg2Player(sceneId,selfId,"��û�������塿�������������עϵͳ���档",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		return -31
	end
	    
	return 0
end

--����
function x301431_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )
	local x, z = GetWorldPos( sceneId, FindMonsterByGUID(sceneId, x301431_g_SubmitNpc))
	Msg2Player(sceneId,selfId,format("������������:%d,%d������", x, z),CHAT_TYPE_SELF,CHAT_LEFTDOWN)
	return 1

end
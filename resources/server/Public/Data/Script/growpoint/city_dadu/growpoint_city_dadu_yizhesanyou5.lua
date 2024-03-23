--������

x301093_g_GrowpointId = 327 --��Ӧ������ID
x301093_g_ItemIndex = 13810095 --��Ӧ�ռ���Ʒ��ID
x301093_g_MissionId = 300569


--���ɺ�����ʼ************************************************************************
function 	x301093_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301093_g_GrowpointId, sceneId, 0, x301093_g_ItemIndex)
    SetGrowPointObjID( sceneId, x301093_g_GrowpointId, x, y, ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301093_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301093_g_MissionId, "OnOpenItemBox", sceneId, selfId, targetId, x301093_g_GrowpointId, x301093_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301093_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301093_g_MissionId, "OnRecycle", sceneId, selfId, targetId, x301093_g_GrowpointId, x301093_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301093_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



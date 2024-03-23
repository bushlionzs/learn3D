--������

x301095_g_GrowpointId = 329 --��Ӧ������ID
x301095_g_ItemIndex = 13810101 --��Ӧ�ռ���Ʒ��ID
x301095_g_MissionId = 300569


--���ɺ�����ʼ************************************************************************
function 	x301095_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301095_g_GrowpointId, sceneId, 0, x301095_g_ItemIndex)
    SetGrowPointObjID( sceneId, x301095_g_GrowpointId, x, y, ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301095_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301095_g_MissionId, "OnOpenItemBox", sceneId, selfId, targetId, x301095_g_GrowpointId, x301095_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301095_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301095_g_MissionId, "OnRecycle", sceneId, selfId, targetId, x301095_g_GrowpointId, x301095_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301095_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



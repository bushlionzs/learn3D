--������

x301080_g_GrowpointId = 324 --��Ӧ������ID
x301080_g_ItemIndex = 13810102 --��Ӧ�ռ���Ʒ��ID
x301080_g_MissionId = 300569


--���ɺ�����ʼ************************************************************************
function 	x301080_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301080_g_GrowpointId, sceneId, 0, x301080_g_ItemIndex)
    SetGrowPointObjID( sceneId, x301080_g_GrowpointId, x, y, ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301080_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301080_g_MissionId, "OnOpenItemBox", sceneId, selfId, targetId, x301080_g_GrowpointId, x301080_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301080_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301080_g_MissionId, "OnRecycle", sceneId, selfId, targetId, x301080_g_GrowpointId, x301080_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301080_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



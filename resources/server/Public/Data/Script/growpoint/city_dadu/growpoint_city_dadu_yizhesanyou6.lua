--������

x301094_g_GrowpointId = 328 --��Ӧ������ID
x301094_g_ItemIndex = 13810098 --��Ӧ�ռ���Ʒ��ID
x301094_g_MissionId = 300569


--���ɺ�����ʼ************************************************************************
function 	x301094_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301094_g_GrowpointId, sceneId, 0, x301094_g_ItemIndex)
    SetGrowPointObjID( sceneId, x301094_g_GrowpointId, x, y, ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301094_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301094_g_MissionId, "OnOpenItemBox", sceneId, selfId, targetId, x301094_g_GrowpointId, x301094_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301094_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301094_g_MissionId, "OnRecycle", sceneId, selfId, targetId, x301094_g_GrowpointId, x301094_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301094_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



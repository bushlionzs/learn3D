--������

x301082_g_GrowpointId = 326 --��Ӧ������ID
x301082_g_ItemIndex = 13810092 --��Ӧ�ռ���Ʒ��ID
x301082_g_MissionId = 300569


--���ɺ�����ʼ************************************************************************
function 	x301082_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301082_g_GrowpointId, sceneId, 0, x301082_g_ItemIndex)
    SetGrowPointObjID( sceneId, x301082_g_GrowpointId, x, y, ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301082_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301082_g_MissionId, "OnOpenItemBox", sceneId, selfId, targetId, x301082_g_GrowpointId, x301082_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301082_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301082_g_MissionId, "OnRecycle", sceneId, selfId, targetId, x301082_g_GrowpointId, x301082_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301082_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



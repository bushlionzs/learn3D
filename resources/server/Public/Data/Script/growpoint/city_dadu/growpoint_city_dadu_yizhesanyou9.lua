--������

x301097_g_GrowpointId = 331 --��Ӧ������ID
x301097_g_ItemIndex = 13810107 --��Ӧ�ռ���Ʒ��ID
x301097_g_MissionId = 300569


--���ɺ�����ʼ************************************************************************
function 	x301097_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301097_g_GrowpointId, sceneId, 0, x301097_g_ItemIndex)
    SetGrowPointObjID( sceneId, x301097_g_GrowpointId, x, y, ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301097_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301097_g_MissionId, "OnOpenItemBox", sceneId, selfId, targetId, x301097_g_GrowpointId, x301097_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301097_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301097_g_MissionId, "OnRecycle", sceneId, selfId, targetId, x301097_g_GrowpointId, x301097_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301097_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



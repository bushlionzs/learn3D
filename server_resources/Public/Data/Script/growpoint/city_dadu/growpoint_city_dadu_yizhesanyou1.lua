--������

x301079_g_GrowpointId = 323 --��Ӧ������ID
x301079_g_ItemIndex = 13810084 --��Ӧ�ռ���Ʒ��ID
x301079_g_MissionId = 300569


--���ɺ�����ʼ************************************************************************
function 	x301079_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301079_g_GrowpointId, sceneId, 0, x301079_g_ItemIndex)
    SetGrowPointObjID( sceneId, x301079_g_GrowpointId, x, y, ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301079_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301079_g_MissionId, "OnOpenItemBox", sceneId, selfId, targetId, x301079_g_GrowpointId, x301079_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301079_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301079_g_MissionId, "OnRecycle", sceneId, selfId, targetId, x301079_g_GrowpointId, x301079_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301079_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



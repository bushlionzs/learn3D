--������

x301078_g_GrowpointId = 322 --��Ӧ������ID
x301078_g_ItemIndex = 13810100 --��Ӧ�ռ���Ʒ��ID
x301078_g_MissionId = 300569


--���ɺ�����ʼ************************************************************************
function 	x301078_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301078_g_GrowpointId, sceneId, 0, x301078_g_ItemIndex)
    SetGrowPointObjID( sceneId, x301078_g_GrowpointId, x, y, ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301078_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301078_g_MissionId, "OnOpenItemBox", sceneId, selfId, targetId, x301078_g_GrowpointId, x301078_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301078_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301078_g_MissionId, "OnRecycle", sceneId, selfId, targetId, x301078_g_GrowpointId, x301078_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301078_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



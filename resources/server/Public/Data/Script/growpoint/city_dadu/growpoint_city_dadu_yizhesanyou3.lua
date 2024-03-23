--������

x301081_g_GrowpointId = 325 --��Ӧ������ID
x301081_g_ItemIndex = 13810089 --��Ӧ�ռ���Ʒ��ID
x301081_g_MissionId = 300569


--���ɺ�����ʼ************************************************************************
function 	x301081_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301081_g_GrowpointId, sceneId, 0, x301081_g_ItemIndex)
    SetGrowPointObjID( sceneId, x301081_g_GrowpointId, x, y, ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301081_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301081_g_MissionId, "OnOpenItemBox", sceneId, selfId, targetId, x301081_g_GrowpointId, x301081_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301081_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301081_g_MissionId, "OnRecycle", sceneId, selfId, targetId, x301081_g_GrowpointId, x301081_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301081_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



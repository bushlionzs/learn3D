--������

x301044_g_GrowpointId = 189 --��Ӧ������ID
x301044_g_ItemIndex = 13810056 --��Ӧ�ռ���Ʒ��ID
x301044_g_MissionId = 300566


--���ɺ�����ʼ************************************************************************
function 	x301044_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301044_g_GrowpointId, sceneId, 0, x301044_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301044_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301044_g_MissionId, "OnOpenItemBox", sceneId, selfId, targetId, x301044_g_GrowpointId, x301044_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301044_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301044_g_MissionId, "OnRecycle", sceneId, selfId, targetId, x301044_g_GrowpointId, x301044_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301044_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



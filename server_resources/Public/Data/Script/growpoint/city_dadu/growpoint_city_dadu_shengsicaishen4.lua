--������

x301047_g_GrowpointId = 192 --��Ӧ������ID
x301047_g_ItemIndex = 13810059 --��Ӧ�ռ���Ʒ��ID
x301047_g_MissionId = 300566


--���ɺ�����ʼ************************************************************************
function 	x301047_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301047_g_GrowpointId, sceneId, 0, x301047_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301047_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301047_g_MissionId, "OnOpenItemBox", sceneId, selfId, targetId, x301047_g_GrowpointId, x301047_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301047_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301047_g_MissionId, "OnRecycle", sceneId, selfId, targetId, x301047_g_GrowpointId, x301047_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301047_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



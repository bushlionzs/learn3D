--������

x301004_g_GrowpointId = 5 --��Ӧ������ID
x301004_g_ItemIndex = 13020005 --��Ӧ�ռ���Ʒ��ID


--���ɺ�����ʼ************************************************************************
function 	x301004_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301004_g_GrowpointId, sceneId, 0, x301004_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301004_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox", sceneId, selfId, targetId, x301004_g_GrowpointId, x301004_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301004_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x301004_g_GrowpointId, x301004_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301004_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


--������

x301303_g_GrowpointId = 203 --��Ӧ������ID
x301303_g_ItemIndex = 13040003 --��Ӧ�ռ���Ʒ��ID


--���ɺ�����ʼ************************************************************************
function 	x301303_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301303_g_GrowpointId, sceneId, 0, x301303_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301303_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox", sceneId, selfId, targetId, x301303_g_GrowpointId, x301303_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301303_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x301303_g_GrowpointId, x301303_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301303_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


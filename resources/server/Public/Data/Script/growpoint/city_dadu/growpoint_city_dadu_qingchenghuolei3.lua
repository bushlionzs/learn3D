--������

x301086_g_GrowpointId = 211 --��Ӧ������ID
x301086_g_ItemIndex = -1 --��Ӧ�ռ���Ʒ��ID
x301086_g_TargetScriptId = 300576


--���ɺ�����ʼ************************************************************************
function 	x301086_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301086_g_GrowpointId, sceneId, 0, x301086_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301086_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301086_g_TargetScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301086_g_GrowpointId, x301086_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301086_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301086_g_TargetScriptId, "OnRecycle", sceneId, selfId, targetId, x301086_g_GrowpointId, x301086_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301086_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( x301086_g_TargetScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


--������

x301434_g_GrowpointId = 713 --��Ӧ������ID
x301434_g_ItemIndex = -1 --��Ӧ�ռ���Ʒ��ID
x301434_g_TargetScriptId = 310210


--���ɺ�����ʼ************************************************************************
function 	x301434_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301434_g_GrowpointId, sceneId, 0, x301434_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301434_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301434_g_TargetScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301434_g_GrowpointId, x301434_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301434_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301434_g_TargetScriptId, "OnRecycle", sceneId, selfId, targetId, x301434_g_GrowpointId, x301434_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301434_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( x301434_g_TargetScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


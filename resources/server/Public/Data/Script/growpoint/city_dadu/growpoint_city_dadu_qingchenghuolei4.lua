--������

x301087_g_GrowpointId = 212 --��Ӧ������ID
x301087_g_ItemIndex = -1 --��Ӧ�ռ���Ʒ��ID
x301087_g_TargetScriptId = 300576


--���ɺ�����ʼ************************************************************************
function 	x301087_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301087_g_GrowpointId, sceneId, 0, x301087_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301087_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301087_g_TargetScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301087_g_GrowpointId, x301087_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301087_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301087_g_TargetScriptId, "OnRecycle", sceneId, selfId, targetId, x301087_g_GrowpointId, x301087_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301087_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( x301087_g_TargetScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

--������

x301092_g_GrowpointId = 217 --��Ӧ������ID
x301092_g_ItemIndex = -1 --��Ӧ�ռ���Ʒ��ID
x301092_g_TargetScriptId = 300576


--���ɺ�����ʼ************************************************************************
function 	x301092_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301092_g_GrowpointId, sceneId, 0, x301092_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301092_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301092_g_TargetScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301092_g_GrowpointId, x301092_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301092_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301092_g_TargetScriptId, "OnRecycle", sceneId, selfId, targetId, x301092_g_GrowpointId, x301092_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301092_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( x301092_g_TargetScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


--������

x301091_g_GrowpointId = 216 --��Ӧ������ID
x301091_g_ItemIndex = -1 --��Ӧ�ռ���Ʒ��ID
x301091_g_TargetScriptId = 300576


--���ɺ�����ʼ************************************************************************
function 	x301091_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301091_g_GrowpointId, sceneId, 0, x301091_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301091_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301091_g_TargetScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301091_g_GrowpointId, x301091_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301091_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301091_g_TargetScriptId, "OnRecycle", sceneId, selfId, targetId, x301091_g_GrowpointId, x301091_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301091_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( x301091_g_TargetScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


--������

x301437_g_GrowpointId = 716 --��Ӧ������ID
x301437_g_ItemIndex = -1 --��Ӧ�ռ���Ʒ��ID
x301437_g_TargetScriptId = 310210


--���ɺ�����ʼ************************************************************************
function 	x301437_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301437_g_GrowpointId, sceneId, 0, x301437_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301437_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301437_g_TargetScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301437_g_GrowpointId, x301437_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301437_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301437_g_TargetScriptId, "OnRecycle", sceneId, selfId, targetId, x301437_g_GrowpointId, x301437_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301437_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( x301437_g_TargetScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


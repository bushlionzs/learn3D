--������

x301436_g_GrowpointId = 715 --��Ӧ������ID
x301436_g_ItemIndex = -1 --��Ӧ�ռ���Ʒ��ID
x301436_g_TargetScriptId = 310210


--���ɺ�����ʼ************************************************************************
function 	x301436_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301436_g_GrowpointId, sceneId, 0, x301436_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301436_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301436_g_TargetScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301436_g_GrowpointId, x301436_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301436_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301436_g_TargetScriptId, "OnRecycle", sceneId, selfId, targetId, x301436_g_GrowpointId, x301436_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301436_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( x301436_g_TargetScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


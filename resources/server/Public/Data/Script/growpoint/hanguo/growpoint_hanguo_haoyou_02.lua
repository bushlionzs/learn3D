--������

x302002_g_GrowpointId = 422 --��Ӧ������ID
x302002_g_ItemIndex = 13013702 --��Ӧ�ռ���Ʒ��ID


--���ɺ�����ʼ************************************************************************
function 	x302002_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x302002_g_GrowpointId, sceneId, 0, x302002_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x302002_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( 300782, "OnOpenItemBox", sceneId, selfId, targetId, x302002_g_GrowpointId, x302002_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x302002_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( 300782, "OnRecycle", sceneId, selfId, targetId, x302002_g_GrowpointId, x302002_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x302002_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( 300782, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



--������

x302004_g_GrowpointId = 424 --��Ӧ������ID
x302004_g_ItemIndex = 13013704 --��Ӧ�ռ���Ʒ��ID


--���ɺ�����ʼ************************************************************************
function 	x302004_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x302004_g_GrowpointId, sceneId, 0, x302004_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x302004_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( 300782, "OnOpenItemBox", sceneId, selfId, targetId, x302004_g_GrowpointId, x302004_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x302004_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( 300782, "OnRecycle", sceneId, selfId, targetId, x302004_g_GrowpointId, x302004_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x302004_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( 300782, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



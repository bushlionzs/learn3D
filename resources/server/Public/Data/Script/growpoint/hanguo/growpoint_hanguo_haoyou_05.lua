--������

x302005_g_GrowpointId = 425 --��Ӧ������ID
x302005_g_ItemIndex = 13013705 --��Ӧ�ռ���Ʒ��ID


--���ɺ�����ʼ************************************************************************
function 	x302005_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x302005_g_GrowpointId, sceneId, 0, x302005_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x302005_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( 300782, "OnOpenItemBox", sceneId, selfId, targetId, x302005_g_GrowpointId, x302005_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x302005_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( 300782, "OnRecycle", sceneId, selfId, targetId, x302005_g_GrowpointId, x302005_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x302005_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( 300782, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



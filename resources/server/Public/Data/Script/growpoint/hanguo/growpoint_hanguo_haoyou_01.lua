--������

x302001_g_GrowpointId = 421 --��Ӧ������ID
x302001_g_ItemIndex = 13013701 --��Ӧ�ռ���Ʒ��ID


--���ɺ�����ʼ************************************************************************
function 	x302001_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x302001_g_GrowpointId, sceneId, 0, x302001_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x302001_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( 300782, "OnOpenItemBox", sceneId, selfId, targetId, x302001_g_GrowpointId, x302001_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x302001_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( 300782, "OnRecycle", sceneId, selfId, targetId, x302001_g_GrowpointId, x302001_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x302001_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( 300782, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



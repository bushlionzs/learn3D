--������

x301452_g_GrowpointId = 800 --��Ӧ������ID
x301452_g_ItemIndex = 13010028 --��Ӧ�ռ���Ʒ��ID


--���ɺ�����ʼ************************************************************************
function 	x301452_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301452_g_GrowpointId, sceneId, 0, x301452_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301452_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox", sceneId, selfId, targetId, x301452_g_GrowpointId, x301452_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301452_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x301452_g_GrowpointId, x301452_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301452_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



--������

x301000_g_GrowpointId = 1 --��Ӧ������ID
x301000_g_ItemIndex = 13010029 --��Ӧ�ռ���Ʒ��ID


--���ɺ�����ʼ************************************************************************
function 	x301000_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301000_g_GrowpointId, sceneId, 0, x301000_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301000_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox", sceneId, selfId, targetId, x301000_g_GrowpointId, x301000_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301000_OnRecycle(sceneId,selfId,targetId)
	 CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x301000_g_GrowpointId, x301000_g_ItemIndex )
	 return 0        	
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301000_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@




--������

x301043_g_GrowpointId = 188 --��Ӧ������ID
x301043_g_ItemIndex = 13810055 --��Ӧ�ռ���Ʒ��ID
x301043_g_MissionId = 300566


--���ɺ�����ʼ************************************************************************
function 	x301043_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301043_g_GrowpointId, sceneId, 0, x301043_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301043_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301043_g_MissionId, "OnOpenItemBox", sceneId, selfId, targetId, x301043_g_GrowpointId, x301043_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301043_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301043_g_MissionId, "OnRecycle", sceneId, selfId, targetId, x301043_g_GrowpointId, x301043_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301043_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



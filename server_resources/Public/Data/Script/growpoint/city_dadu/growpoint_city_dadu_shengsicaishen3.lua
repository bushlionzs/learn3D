--������

x301046_g_GrowpointId = 191 --��Ӧ������ID
x301046_g_ItemIndex = 13810058 --��Ӧ�ռ���Ʒ��ID
x301046_g_MissionId = 300566


--���ɺ�����ʼ************************************************************************
function 	x301046_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301046_g_GrowpointId, sceneId, 0, x301046_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301046_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301046_g_MissionId, "OnOpenItemBox", sceneId, selfId, targetId, x301046_g_GrowpointId, x301046_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301046_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301046_g_MissionId, "OnRecycle", sceneId, selfId, targetId, x301046_g_GrowpointId, x301046_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301046_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



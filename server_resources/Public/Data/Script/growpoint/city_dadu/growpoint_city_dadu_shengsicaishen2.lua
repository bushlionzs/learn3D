--������

x301045_g_GrowpointId = 190 --��Ӧ������ID
x301045_g_ItemIndex = 13810057 --��Ӧ�ռ���Ʒ��ID
x301045_g_MissionId = 300566


--���ɺ�����ʼ************************************************************************
function 	x301045_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301045_g_GrowpointId, sceneId, 0, x301045_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301045_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301045_g_MissionId, "OnOpenItemBox", sceneId, selfId, targetId, x301045_g_GrowpointId, x301045_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301045_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301045_g_MissionId, "OnRecycle", sceneId, selfId, targetId, x301045_g_GrowpointId, x301045_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301045_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



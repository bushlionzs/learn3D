--������

x301061_g_GrowpointId = 61 --��Ӧ������ID
x301061_g_ItemIndex = 13011511 --��Ӧ�ռ���Ʒ��ID
x301061_g_FarScriptId = 300501


--���ɺ�����ʼ************************************************************************
function 	x301061_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301061_g_GrowpointId, sceneId, 0, x301061_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301061_OnOpen(sceneId,selfId,targetId)

	return CallScriptFunction( x301061_g_FarScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301061_g_GrowpointId, x301061_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301061_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301061_g_FarScriptId, "OnRecycle", sceneId, selfId, targetId, x301061_g_GrowpointId, x301061_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301061_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( x301061_g_FarScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301061_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

	--CallScriptFunction( x301061_g_FarScriptId, "OpenCheck", sceneId, selfId, targetId )
end

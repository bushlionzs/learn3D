--������

x301060_g_GrowpointId = 60 --��Ӧ������ID
x301060_g_ItemIndex = 13011510 --��Ӧ�ռ���Ʒ��ID
x301060_g_FarScriptId = 300501


--���ɺ�����ʼ************************************************************************
function 	x301060_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301060_g_GrowpointId, sceneId, 0, x301060_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301060_OnOpen(sceneId,selfId,targetId)

	return CallScriptFunction( x301060_g_FarScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301060_g_GrowpointId, x301060_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301060_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301060_g_FarScriptId, "OnRecycle", sceneId, selfId, targetId, x301060_g_GrowpointId, x301060_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301060_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( x301060_g_FarScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301060_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

	--CallScriptFunction( x301060_g_FarScriptId, "OpenCheck", sceneId, selfId, targetId )
end

--������

x300838_g_GrowpointId = 729 --��Ӧ������ID
x300838_g_ItemIndex = 13080024 --��Ӧ�ռ���Ʒ��ID
x300838_g_FarScriptId = 300615


--���ɺ�����ʼ************************************************************************
function 	x300838_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x300838_g_GrowpointId, sceneId, 0, x300838_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x300838_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x300838_g_FarScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x300838_g_GrowpointId, x300838_g_ItemIndex)
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x300838_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x300838_g_FarScriptId, "OnRecycle", sceneId, selfId, targetId, x300838_g_GrowpointId, x300838_g_ItemIndex)
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x300838_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( x300838_g_FarScriptId, "OnProcOver", sceneId, selfId, targetId)
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x300838_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( x300838_g_FarScriptId, "OpenCheck", sceneId, selfId, targetId)
end

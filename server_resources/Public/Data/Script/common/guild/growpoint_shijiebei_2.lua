--������

x300834_g_GrowpointId = 728 --��Ӧ������ID
x300834_g_ItemIndex = 13080024 --��Ӧ�ռ���Ʒ��ID
x300834_g_FarScriptId = 300615


--���ɺ�����ʼ************************************************************************
function 	x300834_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x300834_g_GrowpointId, sceneId, 0, x300834_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x300834_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x300834_g_FarScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x300834_g_GrowpointId, x300834_g_ItemIndex)
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x300834_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x300834_g_FarScriptId, "OnRecycle", sceneId, selfId, targetId, x300834_g_GrowpointId, x300834_g_ItemIndex)
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x300834_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( x300834_g_FarScriptId, "OnProcOver", sceneId, selfId, targetId)
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x300834_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( x300834_g_FarScriptId, "OpenCheck", sceneId, selfId, targetId)
end

--������

x300832_g_GrowpointId = 726 --��Ӧ������ID
x300832_g_ItemIndex = 13011510 --��Ӧ�ռ���Ʒ��ID
x300832_g_FarScriptId = 300615


--���ɺ�����ʼ************************************************************************
function 	x300832_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x300832_g_GrowpointId, sceneId, 0, x300832_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x300832_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x300832_g_FarScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x300832_g_GrowpointId, x300832_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x300832_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x300832_g_FarScriptId, "OnRecycle", sceneId, selfId, targetId, x300832_g_GrowpointId, x300832_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x300832_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( x300832_g_FarScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x300832_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( x300832_g_FarScriptId, "OpenCheck", sceneId, selfId, targetId )
end

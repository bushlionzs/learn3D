--������

x300833_g_GrowpointId = 727 --��Ӧ������ID
x300833_g_ItemIndex = 13011510 --��Ӧ�ռ���Ʒ��ID
x300833_g_FarScriptId = 300615


--���ɺ�����ʼ************************************************************************
function 	x300833_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x300833_g_GrowpointId, sceneId, 0, x300833_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x300833_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x300833_g_FarScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x300833_g_GrowpointId, x300833_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x300833_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x300833_g_FarScriptId, "OnRecycle", sceneId, selfId, targetId, x300833_g_GrowpointId, x300833_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x300833_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( x300833_g_FarScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x300833_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( x300833_g_FarScriptId, "OpenCheck", sceneId, selfId, targetId )
end

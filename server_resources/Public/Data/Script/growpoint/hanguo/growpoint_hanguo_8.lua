--������

x301057_g_GrowpointId = 57 --��Ӧ������ID
x301057_g_ItemIndex = 13011507 --��Ӧ�ռ���Ʒ��ID
x301057_g_FarScriptId = 300501


--���ɺ�����ʼ************************************************************************
function 	x301057_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301057_g_GrowpointId, sceneId, 0, x301057_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301057_OnOpen(sceneId,selfId,targetId)

	return CallScriptFunction( x301057_g_FarScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301057_g_GrowpointId, x301057_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301057_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301057_g_FarScriptId, "OnRecycle", sceneId, selfId, targetId, x301057_g_GrowpointId, x301057_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301057_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( x301057_g_FarScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301057_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

	--CallScriptFunction( x301057_g_FarScriptId, "OpenCheck", sceneId, selfId, targetId )
end

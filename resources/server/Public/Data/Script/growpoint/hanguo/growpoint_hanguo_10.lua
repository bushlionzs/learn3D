--������

x301059_g_GrowpointId = 59 --��Ӧ������ID
x301059_g_ItemIndex = 13011509 --��Ӧ�ռ���Ʒ��ID
x301059_g_FarScriptId = 300501


--���ɺ�����ʼ************************************************************************
function 	x301059_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301059_g_GrowpointId, sceneId, 0, x301059_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301059_OnOpen(sceneId,selfId,targetId)

	return CallScriptFunction( x301059_g_FarScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301059_g_GrowpointId, x301059_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301059_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301059_g_FarScriptId, "OnRecycle", sceneId, selfId, targetId, x301059_g_GrowpointId, x301059_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301059_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( x301059_g_FarScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301059_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

	--CallScriptFunction( x301059_g_FarScriptId, "OpenCheck", sceneId, selfId, targetId )
end

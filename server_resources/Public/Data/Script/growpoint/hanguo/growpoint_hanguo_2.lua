--������

x301051_g_GrowpointId = 51 --��Ӧ������ID
x301051_g_ItemIndex = 13011500 --��Ӧ�ռ���Ʒ��ID
x301051_g_FarScriptId = 300520

x301051_g_ScriptTable = {
    300520, 
    300511, 
    300512, 
    300513, 
}


--���ɺ�����ʼ************************************************************************
function 	x301051_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301051_g_GrowpointId, sceneId, 0, x301051_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301051_OnOpen(sceneId,selfId,targetId)

	return CallScriptFunction( x301051_g_ScriptTable[ GetCurCountry( sceneId, selfId) + 1], "OnOpenItemBox", sceneId, selfId, targetId, x301051_g_GrowpointId, x301051_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301051_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301051_g_ScriptTable[ GetCurCountry( sceneId, selfId) + 1], "OnRecycle", sceneId, selfId, targetId, x301051_g_GrowpointId, x301051_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301051_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( x301051_g_ScriptTable[ GetCurCountry( sceneId, selfId) + 1], "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301051_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

	--CallScriptFunction( x301051_g_FarScriptId, "OpenCheck", sceneId, selfId, targetId )
end

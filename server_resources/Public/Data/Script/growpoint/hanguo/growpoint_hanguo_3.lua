--������

x301052_g_GrowpointId = 52 --��Ӧ������ID
x301052_g_ItemIndex = 13011506 --��Ӧ�ռ���Ʒ��ID
x301052_g_FarScriptId = 300520

x301052_g_ScriptTable = {
    300520, 
    300511, 
    300512, 
    300513, 
}

--���ɺ�����ʼ************************************************************************
function 	x301052_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301052_g_GrowpointId, sceneId, 0, x301052_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301052_OnOpen(sceneId,selfId,targetId)

	return CallScriptFunction( x301052_g_ScriptTable[ GetCurCountry( sceneId, selfId) + 1], "OnOpenItemBox", sceneId, selfId, targetId, x301052_g_GrowpointId, x301052_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301052_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301052_g_ScriptTable[ GetCurCountry( sceneId, selfId) + 1], "OnRecycle", sceneId, selfId, targetId, x301052_g_GrowpointId, x301052_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301052_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( x301052_g_ScriptTable[ GetCurCountry( sceneId, selfId) + 1], "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301052_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

	--CallScriptFunction( x301052_g_FarScriptId, "OpenCheck", sceneId, selfId, targetId )
end

--������

x301056_g_GrowpointId = 56 --��Ӧ������ID
x301056_g_ItemIndex = 13011506 --��Ӧ�ռ���Ʒ��ID
x301056_g_ScriptTable = {
    300520, 
    300511, 
    300512, 
    300513, 
}

--���ɺ�����ʼ************************************************************************
function 	x301056_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301056_g_GrowpointId, sceneId, 0, x301056_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301056_OnOpen(sceneId,selfId,targetId)
    return CallScriptFunction( x301056_g_ScriptTable[ GetCurCountry( sceneId, selfId) + 1], "OnOpenItemBox", sceneId, selfId, targetId, x301056_g_GrowpointId, x301056_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301056_OnRecycle(sceneId,selfId,targetId)
    return CallScriptFunction( x301056_g_ScriptTable[ GetCurCountry( sceneId, selfId) + 1], "OnRecycle", sceneId, selfId, targetId, x301056_g_GrowpointId, x301056_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301056_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( x301056_g_FarScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301056_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

	--CallScriptFunction( x301056_g_FarScriptId, "OpenCheck", sceneId, selfId, targetId )
end

--������

x301055_g_GrowpointId = 55 --��Ӧ������ID
x301055_g_ItemIndex = 13011505 --��Ӧ�ռ���Ʒ��ID
x301055_g_ScriptTable = {
    300520, 
    300511, 
    300512, 
    300513, 
}

--���ɺ�����ʼ************************************************************************
function 	x301055_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301055_g_GrowpointId, sceneId, 0, x301055_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301055_OnOpen(sceneId,selfId,targetId)
    return CallScriptFunction( x301055_g_ScriptTable[ GetCurCountry( sceneId, selfId) + 1], "OnOpenItemBox", sceneId, selfId, targetId, x301055_g_GrowpointId, x301055_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301055_OnRecycle(sceneId,selfId,targetId)
    return CallScriptFunction( x301055_g_ScriptTable[ GetCurCountry( sceneId, selfId) + 1], "OnRecycle", sceneId, selfId, targetId, x301055_g_GrowpointId, x301055_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301055_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( x301055_g_FarScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301055_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

	--CallScriptFunction( x301055_g_FarScriptId, "OpenCheck", sceneId, selfId, targetId )
end

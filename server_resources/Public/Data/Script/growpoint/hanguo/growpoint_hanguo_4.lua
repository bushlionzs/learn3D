--������

x301053_g_GrowpointId = 53 --��Ӧ������ID
x301053_g_ItemIndex = 13011508 --��Ӧ�ռ���Ʒ��ID
x301053_g_FarScriptId = 300520

x301053_g_ScriptTable = {
    300520, 
    300511, 
    300512, 
    300513, 
}


--���ɺ�����ʼ************************************************************************
function 	x301053_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301053_g_GrowpointId, sceneId, 0, x301053_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301053_OnOpen(sceneId,selfId,targetId)

	return CallScriptFunction( x301053_g_ScriptTable[ GetCurCountry( sceneId, selfId) + 1], "OnOpenItemBox", sceneId, selfId, targetId, x301053_g_GrowpointId, x301053_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301053_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301053_g_ScriptTable[ GetCurCountry( sceneId, selfId) + 1], "OnRecycle", sceneId, selfId, targetId, x301053_g_GrowpointId, x301053_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301053_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( x301053_g_FarScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301053_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

	--CallScriptFunction( x301053_g_FarScriptId, "OpenCheck", sceneId, selfId, targetId )
end

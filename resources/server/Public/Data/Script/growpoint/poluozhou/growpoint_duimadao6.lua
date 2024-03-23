-- �ɼ���

x301443_g_GrowpointId = 722 --��Ӧ������ID
x301443_g_ItemIndex = 13070010 --��Ӧ�ռ���Ʒ��ID
x301443_g_ScriptId = 305015


--���ɺ�����ʼ************************************************************************
function 	x301443_OnCreate( sceneId, growPointType, x, y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301443_g_GrowpointId, sceneId, 0, x301443_g_ItemIndex)
    SetGrowPointObjID( sceneId, x301443_g_GrowpointId, x, y, ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301443_OnOpen( sceneId, selfId, targetId)
	return CallScriptFunction( x301443_g_ScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301443_g_GrowpointId, x301443_g_ItemIndex)
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301443_OnRecycle( sceneId, selfId, targetId)
	return CallScriptFunction( x301443_g_ScriptId, "OnRecycle", sceneId, selfId, targetId, x301443_g_GrowpointId, x301443_g_ItemIndex)
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301443_OnProcOver( sceneId, selfId, targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId)
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



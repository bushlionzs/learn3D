-- �ɼ���

x301444_g_GrowpointId = 723 --��Ӧ������ID
x301444_g_ItemIndex = 13070011 --��Ӧ�ռ���Ʒ��ID
x301444_g_ScriptId = 305015


--���ɺ�����ʼ************************************************************************
function 	x301444_OnCreate( sceneId, growPointType, x, y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301444_g_GrowpointId, sceneId, 0, x301444_g_ItemIndex)
    SetGrowPointObjID( sceneId, x301444_g_GrowpointId, x, y, ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301444_OnOpen( sceneId, selfId, targetId)
	return CallScriptFunction( x301444_g_ScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301444_g_GrowpointId, x301444_g_ItemIndex)
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301444_OnRecycle( sceneId, selfId, targetId)
	return CallScriptFunction( x301444_g_ScriptId, "OnRecycle", sceneId, selfId, targetId, x301444_g_GrowpointId, x301444_g_ItemIndex)
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301444_OnProcOver( sceneId, selfId, targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId)
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



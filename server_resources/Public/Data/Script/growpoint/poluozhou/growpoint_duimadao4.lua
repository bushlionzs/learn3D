-- �ɼ���

x301441_g_GrowpointId = 720 --��Ӧ������ID
x301441_g_ItemIndex = 13070010 --��Ӧ�ռ���Ʒ��ID
x301441_g_ScriptId = 305015


--���ɺ�����ʼ************************************************************************
function 	x301441_OnCreate( sceneId, growPointType, x, y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301441_g_GrowpointId, sceneId, 0, x301441_g_ItemIndex)
    SetGrowPointObjID( sceneId, x301441_g_GrowpointId, x, y, ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301441_OnOpen( sceneId, selfId, targetId)
	return CallScriptFunction( x301441_g_ScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301441_g_GrowpointId, x301441_g_ItemIndex)
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301441_OnRecycle( sceneId, selfId, targetId)
	return CallScriptFunction( x301441_g_ScriptId, "OnRecycle", sceneId, selfId, targetId, x301441_g_GrowpointId, x301441_g_ItemIndex)
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301441_OnProcOver( sceneId, selfId, targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId)
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



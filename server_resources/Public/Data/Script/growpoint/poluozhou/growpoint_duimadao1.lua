-- �ɼ���

x301438_g_GrowpointId = 717 --��Ӧ������ID
x301438_g_ItemIndex = 13070012 --��Ӧ�ռ���Ʒ��ID
x301438_g_ScriptId = 305015


--���ɺ�����ʼ************************************************************************
function 	x301438_OnCreate( sceneId, growPointType, x, y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301438_g_GrowpointId, sceneId, 0, x301438_g_ItemIndex)
    SetGrowPointObjID( sceneId, x301438_g_GrowpointId, x, y, ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301438_OnOpen( sceneId, selfId, targetId)
	return CallScriptFunction( x301438_g_ScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301438_g_GrowpointId, x301438_g_ItemIndex)
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301438_OnRecycle( sceneId, selfId, targetId)
	return CallScriptFunction( x301438_g_ScriptId, "OnRecycle", sceneId, selfId, targetId, x301438_g_GrowpointId, x301438_g_ItemIndex)
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301438_OnProcOver( sceneId, selfId, targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId)
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



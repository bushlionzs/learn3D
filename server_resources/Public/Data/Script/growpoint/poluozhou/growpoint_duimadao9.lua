-- �ɼ���

x301446_g_GrowpointId = 725 --��Ӧ������ID
x301446_g_ItemIndex = 13070011 --��Ӧ�ռ���Ʒ��ID
x301446_g_ScriptId = 305015


--���ɺ�����ʼ************************************************************************
function 	x301446_OnCreate( sceneId, growPointType, x, y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301446_g_GrowpointId, sceneId, 0, x301446_g_ItemIndex)
    SetGrowPointObjID( sceneId, x301446_g_GrowpointId, x, y, ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301446_OnOpen( sceneId, selfId, targetId)
	return CallScriptFunction( x301446_g_ScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301446_g_GrowpointId, x301446_g_ItemIndex)
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301446_OnRecycle( sceneId, selfId, targetId)
	return CallScriptFunction( x301446_g_ScriptId, "OnRecycle", sceneId, selfId, targetId, x301446_g_GrowpointId, x301446_g_ItemIndex)
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301446_OnProcOver( sceneId, selfId, targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId)
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



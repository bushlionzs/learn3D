-- �ɼ���

x301439_g_GrowpointId = 718 --��Ӧ������ID
x301439_g_ItemIndex = 13070012 --��Ӧ�ռ���Ʒ��ID
x301439_g_ScriptId = 305015


--���ɺ�����ʼ************************************************************************
function 	x301439_OnCreate( sceneId, growPointType, x, y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301439_g_GrowpointId, sceneId, 0, x301439_g_ItemIndex)
    SetGrowPointObjID( sceneId, x301439_g_GrowpointId, x, y, ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301439_OnOpen( sceneId, selfId, targetId)
	return CallScriptFunction( x301439_g_ScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301439_g_GrowpointId, x301439_g_ItemIndex)
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301439_OnRecycle( sceneId, selfId, targetId)
	return CallScriptFunction( x301439_g_ScriptId, "OnRecycle", sceneId, selfId, targetId, x301439_g_GrowpointId, x301439_g_ItemIndex)
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301439_OnProcOver( sceneId, selfId, targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId)
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



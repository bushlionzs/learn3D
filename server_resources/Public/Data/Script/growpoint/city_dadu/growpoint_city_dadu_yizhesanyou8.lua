--������

x301096_g_GrowpointId = 330 --��Ӧ������ID
x301096_g_ItemIndex = 13810104 --��Ӧ�ռ���Ʒ��ID
x301096_g_MissionId = 300569


--���ɺ�����ʼ************************************************************************
function 	x301096_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301096_g_GrowpointId, sceneId, 0, x301096_g_ItemIndex)
    SetGrowPointObjID( sceneId, x301096_g_GrowpointId, x, y, ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301096_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301096_g_MissionId, "OnOpenItemBox", sceneId, selfId, targetId, x301096_g_GrowpointId, x301096_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301096_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301096_g_MissionId, "OnRecycle", sceneId, selfId, targetId, x301096_g_GrowpointId, x301096_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301096_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



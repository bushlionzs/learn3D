--���ս�ػ��޻��ֲɼ���

x300644_g_ItemIndex = -1
x300644_g_GrowPointType = 114

--���ɺ�����ʼ************************************************************************
function x300644_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x300644_g_GrowPointType, sceneId, 0, x300644_g_ItemIndex)
    SetGrowPointObjID(sceneId,x300644_g_GrowPointType,x,y,ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function x300644_OnOpen(sceneId,selfId,targetId)
    return x300644_OnOpenItemBox(sceneId, selfId, targetId, x300644_g_GrowPointType, x300644_g_ItemIndex)
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function x300644_OnRecycle(sceneId,selfId,targetId)
	return x300644_OnGuildRecycle( sceneId, selfId, targetId, x300644_g_GrowPointType, x300644_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function x300644_OnProcOver(sceneId,selfId,targetId)	
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


function x300644_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
end


--**********************************************************************
--�ɼ�����
--��ItemBox
function x300644_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction(300643,"OnRecyleConvoyGrowPoint_Check",sceneId,selfId)
end

--����
function x300644_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )

	return CallScriptFunction(300643,"OnRecyleConvoyGrowPoint",sceneId,selfId)
end

--**********************************************************************


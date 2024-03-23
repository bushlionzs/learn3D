--DOORA

x300921_g_ItemIndex = -1

--���ɺ�����ʼ************************************************************************
function x300921_OnCreate(sceneId,growPointType,x,y)
	
	local typeGrowPoint = CallScriptFunction(300918,"GetDoorA",sceneId)
	
	local ItemBoxId = ItemBoxEnterScene(x, y, typeGrowPoint, sceneId, 0, x300921_g_ItemIndex)
    SetGrowPointObjID(sceneId,typeGrowPoint,x,y,ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function x300921_OnOpen(sceneId,selfId,targetId)
	
	local typeGrowPoint = CallScriptFunction(300918,"GetDoorA",sceneId)
    return x300921_OnOpenItemBox(sceneId, selfId, targetId, typeGrowPoint, x300921_g_ItemIndex)
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function x300921_OnRecycle(sceneId,selfId,targetId)
	local typeGrowPoint = CallScriptFunction(300918,"GetDoorA",sceneId)
	return x300921_OnGuildRecycle( sceneId, selfId, targetId, typeGrowPoint, x300921_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function x300921_OnProcOver(sceneId,selfId,targetId)	
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


function x300921_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
end


--**********************************************************************
--�ɼ�����
--��ItemBox
function x300921_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction(300918,"OnOpenDoorA_Check",sceneId,selfId)
end

--����
function x300921_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )

	return CallScriptFunction(300918,"OnOpenDoorA",sceneId,selfId)
end

--**********************************************************************


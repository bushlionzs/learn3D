--DOORB

x300922_g_ItemIndex = -1

--���ɺ�����ʼ************************************************************************
function x300922_OnCreate(sceneId,growPointType,x,y)
	
	local typeGrowPoint = CallScriptFunction(300918,"GetDoorB",sceneId)
	
	local ItemBoxId = ItemBoxEnterScene(x, y, typeGrowPoint, sceneId, 0, x300922_g_ItemIndex)
    SetGrowPointObjID(sceneId,typeGrowPoint,x,y,ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function x300922_OnOpen(sceneId,selfId,targetId)
	
	local typeGrowPoint = CallScriptFunction(300918,"GetDoorB",sceneId)
    return x300922_OnOpenItemBox(sceneId, selfId, targetId, typeGrowPoint, x300922_g_ItemIndex)
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function x300922_OnRecycle(sceneId,selfId,targetId)
	local typeGrowPoint = CallScriptFunction(300918,"GetDoorB",sceneId)
	return x300922_OnGuildRecycle( sceneId, selfId, targetId, typeGrowPoint, x300922_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function x300922_OnProcOver(sceneId,selfId,targetId)	
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


function x300922_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
end


--**********************************************************************
--�ɼ�����
--��ItemBox
function x300922_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction(300918,"OnOpenDoorB_Check",sceneId,selfId)
end

--����
function x300922_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )

	return CallScriptFunction(300918,"OnOpenDoorB",sceneId,selfId)
end

--**********************************************************************


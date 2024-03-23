--ħ����

x300669_g_GrowpointId = 114 		--��Ӧ������ID
x300669_g_Percentum = {num1=20,num2=40,num3=60,num4=80,num5=100,}           --�ٷֱ�
x300669_g_BufList = {buf1=7021,buf2=7022,buf3=1210,buf4=1210,}
x300669_g_ItemIndex = 12010001

--���ɺ�����ʼ************************************************************************
function 	x300669_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x300669_g_GrowpointId, sceneId, 0, x300669_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x300669_OnOpen(sceneId,selfId,targetId)
    return x300669_OnOpenItemBox(sceneId, selfId, targetId, x300669_g_GrowpointId, x300669_g_ItemIndex)
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x300669_OnRecycle(sceneId,selfId,targetId)
	return   x300669_OnGuildRecycle( sceneId, selfId, targetId, x300669_g_GrowpointId, x300669_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x300669_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x300669_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--**********************************************************************
--�ɼ�����
--��ItemBox
function x300669_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )

	local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
		return 1
	end

	return 0
end

--����
function x300669_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )

    x300669_CancelBuffer(sceneId,selfId)

	local num = random(1,40)

	if num<=x300669_g_Percentum.num1 then
     	SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId,x300669_g_BufList.buf1,0)
	elseif num<=x300669_g_Percentum.num2 then
     	SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId,x300669_g_BufList.buf2,0)
--	elseif num<=x300669_g_Percentum.num3 then
--     	SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId,x300669_g_BufList.buf3,0)
--	elseif num<=x300669_g_Percentum.num4 then
--     	SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId,x300669_g_BufList.buf4,0)
--	else
-- 		AddExp(sceneId, selfId,100)
	end

	return 1

end

function x300669_CancelBuffer( sceneId, selfId )

    local bHaveFlag = IsHaveSpecificImpact(sceneId, selfId,x300669_g_BufList.buf1 )
    if bHaveFlag > 0 then
        CancelSpecificImpact(sceneId,selfId,x300669_g_BufList.buf1 )
    end

    bHaveFlag = IsHaveSpecificImpact(sceneId, selfId,x300669_g_BufList.buf2 )
    if bHaveFlag > 0 then
        CancelSpecificImpact(sceneId,selfId,x300669_g_BufList.buf2 )
    end

    bHaveFlag = IsHaveSpecificImpact(sceneId, selfId,x300669_g_BufList.buf3 )
    if bHaveFlag > 0 then
        CancelSpecificImpact(sceneId,selfId,x300669_g_BufList.buf3 )
    end

    bHaveFlag = IsHaveSpecificImpact(sceneId, selfId,x300669_g_BufList.buf4 )
    if bHaveFlag > 0 then
        CancelSpecificImpact(sceneId,selfId,x300669_g_BufList.buf4 )
    end

end

--**********************************************************************


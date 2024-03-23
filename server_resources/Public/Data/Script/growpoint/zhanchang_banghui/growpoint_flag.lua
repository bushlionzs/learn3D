--����

x300666_g_ItemIndex = 12010001

--���ɺ�����ʼ************************************************************************
function 	x300666_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, LD_GUILD_BATTLE_FLAG_GROW_POINT, sceneId, 0, x300666_g_ItemIndex)
    SetGrowPointObjID(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,x,y,ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x300666_OnOpen(sceneId,selfId,targetId)
    return x300666_OnOpenItemBox(sceneId, selfId, targetId, LD_GUILD_BATTLE_FLAG_GROW_POINT, x300666_g_ItemIndex)
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x300666_OnRecycle(sceneId,selfId,targetId)
	return   x300666_OnGuildRecycle( sceneId, selfId, targetId, LD_GUILD_BATTLE_FLAG_GROW_POINT, x300666_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x300666_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x300666_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--**********************************************************************
--�ɼ�����
--��ItemBox
function x300666_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return 0
end

--����
function x300666_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )

    if CallScriptFunction(GUILDBATTLE_SCRIPTID,"CheckBattleState", sceneId) == 0 then
        return 0
    end

    ReCallHorse( sceneId, selfId )--ǿ������

 	SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId,LD_GUILD_BATTLE_DEC_SPEED_BUF,200)  --200����
 	SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId,LD_GUILD_BATTLE_INC_DEFENCE_BUF,200)--200����
 	--SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId,LD_GUILD_BATTLE_FLAG_BUF,0)

 	if GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_TIME) == -1 then
 	 	SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_TIME,60*10 )     --������Чʱ��5����
 	end

 	SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_OWNER,selfId )  --��¼��������
	--������������ʱ��
	SetGrowPointIntervalContainer(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,-1)

    CallScriptFunction( GUILDBATTLE_SCRIPTID,"UpdateSceneDataFlag",sceneId,7 )
    CallScriptFunction( 300669,"CancelBuffer",sceneId,selfId )

    local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
    local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

    local nGuildId = GetGuildID( sceneId,selfId )

    --������ս���е���Ӫ����
    local nFlag = -1
    if nGuildId == nGuildA then
        nFlag = 0
    elseif nGuildId == nGuildB then
        nFlag = 1
    end

    --������Ӧ��ʾ
    if nFlag == 0 then
        
        LuaThisScenceM2Wrold(sceneId,"������ȡ��ս��",2,1)
        LuaThisScenceM2Wrold(sceneId,"������ȡ��ս��",3,1)

    elseif nFlag == 1 then
        
        LuaThisScenceM2Wrold(sceneId,"�췽��ȡ��ս��",2,1)
        LuaThisScenceM2Wrold(sceneId,"�췽��ȡ��ս��",3,1)
    end

	return 1

end

--**********************************************************************


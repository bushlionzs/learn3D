--����1

x300662_g_GrowpointId = 106 		--��Ӧ������ID
x300662_g_ItemIndex = 12010001
x300662_g_BufIndex = 1210

--���ɺ�����ʼ************************************************************************
function 	x300662_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x300662_g_GrowpointId, sceneId, 0, x300662_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x300662_OnOpen(sceneId,selfId,targetId)
    return x300662_OnOpenItemBox(sceneId, selfId, targetId, x300662_g_GrowpointId, x300662_g_ItemIndex)
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x300662_OnRecycle(sceneId,selfId,targetId)
	return   x300662_OnGuildRecycle( sceneId, selfId, targetId, x300662_g_GrowpointId, x300662_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x300662_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x300662_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--**********************************************************************
--�ɼ�����
--��ItemBox
function x300662_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )

    
    local nResult = CallScriptFunction(GUILDBATTLE_SCRIPTID,"CheckBattleState", sceneId)
    if  nResult == 0 then
        return 1
    end

	local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
		return 1
	end

	--�õ����ֵ�ǰ���
	local guild = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN1_GUILD)
	if guild == GetGuildID(sceneId, selfId) then	--�Ǳ�������
		--�õ������������A��B��
        local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
        local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

        local flag = -1

        --������ս���е���Ӫ����
        if guild == nGuildA then
            flag = 0
        elseif guild == nGuildB then
            flag = 1
        end

	  	--�ж������Ƿ�����
    	local IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId,LD_GUILD_BATTLE_DEC_SPEED_BUF )
    	if IsHaveFlag == 0 then
    		--�������첻�ɽ�
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�������첻�ɽ���");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 1
		end

		if GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN2_GUILD) ~= guild and GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN3_GUILD) ~= guild then
  			--ռ���������ֲ��ܽ�
 			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "ռ���������ֲ��ܽ���");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 1
		end

		local FlagNum = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_FLAG_NUM+flag) + 1
        --if FlagNum < LD_GUILD_BATTLE_FLAG_COUNT then						--�������
        SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_A_FLAG_NUM+flag,FlagNum )
        --else
        --	SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_A_FLAG_NUM+flag,LD_GUILD_BATTLE_FLAG_COUNT )
        --end

        --��������10
        if flag == 0 then
            local Score = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_SOCRE) + 10
            SetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_SOCRE ,Score )
        end

        if flag == 1 then
            local Score = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_SOCRE) + 10
            SetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_SOCRE ,Score )
        end

        --���Ӽ�����1
        local nGetFlag = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_GETFLAG) + 1
        SetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_GETFLAG,nGetFlag) 

		--ɾ������BUF
	    CancelSpecificImpact(sceneId,selfId,LD_GUILD_BATTLE_DEC_SPEED_BUF )
	    CancelSpecificImpact(sceneId,selfId,LD_GUILD_BATTLE_INC_DEFENCE_BUF )
	    --CancelSpecificImpact(sceneId,owner,LD_GUILD_BATTLE_FLAG_BUF )
	    SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_OWNER,-1 )

		--if FlagNum < LD_GUILD_BATTLE_FLAG_COUNT then
			--��������λ�ú���������
			SetGrowPointPos(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,LD_GUILD_BATTLE_FLAG_X,LD_GUILD_BATTLE_FLAG_Y)
			SetGrowPointIntervalContainer(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,1000)
			SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_TIME,-1 )
            CallScriptFunction( GUILDBATTLE_SCRIPTID,"UpdateSceneDataFlag",sceneId,7 )
		--end

        --������Ӧ��ʾ
        if flag == 0 then
            
            LuaThisScenceM2Wrold(sceneId,"�����ɹ�������ս��",2,1)
            LuaThisScenceM2Wrold(sceneId,"�����ɹ�������ս��",3,1)

        elseif flag == 1 then
            
            LuaThisScenceM2Wrold(sceneId,"�췽�ɹ�������ս��",2,1)
            LuaThisScenceM2Wrold(sceneId,"�췽�ɹ�������ս��",3,1)
        end

		return 1
	else
        --�ж������Ƿ�����
    	local IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId,LD_GUILD_BATTLE_DEC_SPEED_BUF )
    	if IsHaveFlag == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�������첻�ɲɼ���");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 1
		end
    end

	return 0
end

--����
function x300662_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )
    
    local nResult = CallScriptFunction(GUILDBATTLE_SCRIPTID,"CheckBattleState", sceneId)
    if  nResult == 0 then
        return 0
    end

	SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_BARN1_GUILD,GetGuildID(sceneId, selfId) )

	--���豻ռ��ʱ��
	SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_BARN1_TIME,-1 )

    CallScriptFunction( GUILDBATTLE_SCRIPTID,"UpdateSceneDataFlag",sceneId,1 )

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
        
        LuaThisScenceM2Wrold(sceneId,"������ȡ������",2,1)
        LuaThisScenceM2Wrold(sceneId,"������ȡ������",3,1)

    elseif nFlag == 1 then
        
        LuaThisScenceM2Wrold(sceneId,"�췽��ȡ������",2,1)
        LuaThisScenceM2Wrold(sceneId,"�췽��ȡ������",3,1)
    end

	return 1

end

--**********************************************************************


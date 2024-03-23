--A���ֿ�

x300667_g_GrowpointId = 112 		--��Ӧ������ID
x300667_g_ItemIndex = 12010001
x300667_g_Flag = 0             		-- 0:A���ֿ�

--���ɺ�����ʼ************************************************************************
function 	x300667_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x300667_g_GrowpointId, sceneId, 0, x300667_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x300667_OnOpen(sceneId,selfId,targetId)
    return x300667_OnOpenItemBox(sceneId, selfId, targetId, x300667_g_GrowpointId, x300667_g_ItemIndex)
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x300667_OnRecycle(sceneId,selfId,targetId)
	return   x300667_OnGuildRecycle( sceneId, selfId, targetId, x300667_g_GrowpointId, x300667_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x300667_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x300667_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--**********************************************************************
function x300667_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )

    if CallScriptFunction(GUILDBATTLE_SCRIPTID,"CheckBattleState", sceneId) == 0 then
        return 1
    end

	local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
		return 1
	end

	--�õ������������A��B��
    --����A��Ӫ������Ч
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

	if nFlag ~= x300667_g_Flag then      --�з��ֿ⣺�����Դ洢
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�з��ֿ⣺�����Դ洢��");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1
	else
	  	--�ж������Ƿ�����
    	local IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId,LD_GUILD_BATTLE_DEC_SPEED_BUF )
    	if IsHaveFlag == 0 then
    		--�������첻�ɽ�
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�������첻�ɽ���");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 1
		else
			

            local FlagNum = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_FLAG_NUM+nFlag) + 1
			--if FlagNum < LD_GUILD_BATTLE_FLAG_COUNT then						--�������
            SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_A_FLAG_NUM+nFlag,FlagNum )
			--else
			--	SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_A_FLAG_NUM+flag,LD_GUILD_BATTLE_FLAG_COUNT )
			--end

            --��������10
            if nFlag == 0 then
                local Score = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_SOCRE) + 10
                SetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_SOCRE ,Score )
            end

            if nFlag == 1 then
	            local Score = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_SOCRE) + 10
                SetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_SOCRE ,Score )
            end

            --���Ӽ�����1
            local nGetFlag = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_GETFLAG) + 1
            SetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_GETFLAG,nGetFlag) 

			--ɾ������BUF
		    CancelSpecificImpact(sceneId,selfId,LD_GUILD_BATTLE_DEC_SPEED_BUF )
		    CancelSpecificImpact(sceneId,selfId,LD_GUILD_BATTLE_INC_DEFENCE_BUF )
		    --CancelSpecificImpact(sceneId,selfId,LD_GUILD_BATTLE_FLAG_BUF )
			SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_OWNER,-1 )

			--if FlagNum < LD_GUILD_BATTLE_FLAG_COUNT then
				--��������λ�ú���������
				SetGrowPointPos(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,LD_GUILD_BATTLE_FLAG_X,LD_GUILD_BATTLE_FLAG_Y)
				SetGrowPointIntervalContainer(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,1000)
				SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_TIME,-1 )
                CallScriptFunction( GUILDBATTLE_SCRIPTID,"UpdateSceneDataFlag",sceneId,7 )

			--end

            --������Ӧ��ʾ
            if nFlag == 0 then
                
                LuaThisScenceM2Wrold(sceneId,"�����ɹ�������ս��",2,1)
                LuaThisScenceM2Wrold(sceneId,"�����ɹ�������ս��",3,1)

            elseif nFlag == 1 then
                
                LuaThisScenceM2Wrold(sceneId,"�췽�ɹ�������ս��",2,1)
                LuaThisScenceM2Wrold(sceneId,"�췽�ɹ�������ս��",3,1)
            end
		end
		return 1
	end

	return 1
end

--����
function x300667_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )

    if CallScriptFunction(GUILDBATTLE_SCRIPTID,"CheckBattleState", sceneId) == 0 then
        return 0
    end

	return 1

end

--**********************************************************************


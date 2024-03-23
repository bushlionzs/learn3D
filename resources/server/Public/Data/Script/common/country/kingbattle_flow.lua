
x300813_g_scriptId                      = 300813
x300813_g_TotalBattleTime               = 60 * 20     	--ս������ʱ��1200��        19:00-19:20

--�淨����
x300813_g_SceneName                     = { {Name="zhanchang_guowangzhanchang/zhanchang_guowangzhanchang.scn",Script=300813} }

x300813_g_King_Signup                  = 2     --����
x300813_g_King_WaitBattle              = 3     --�����������ȴ�����ս��
x300813_g_King_BeginBattle             = 4     --��ʼ����ս��
x300813_g_King_EndBattle               = 5     --��������ս��

--�������
x300813_g_MaxScore                     = 49	            --��0��ʼ����
x300813_g_BonusTips                    = "#G�������#R%d#G�㾭��,#R%d#G���ṱ��,#R%d#G��ᾭ��!" --������ʾ
x300813_g_BonusTips1                   = "������˽���" --������ʾ


--���齱��
x300813_g_WinPrise                     = 1000*0.5*20              --��ʤ�����齱��ϵ����ֻ��ȼ��й�
x300813_g_LosePrise                    = 1000*0.1*20              --ʧ�ܷ����齱��ϵ����ֻ��ȼ��й�
x300813_g_DeucePrise                   = 1000*0.3*20              --սƽʱ���齱��ϵ����ֻ��ȼ��й�

--�ﹱ����
x300813_g_WinBangGong                  = 25

x300813_g_DeuceBangGong                = 20

--��ᾭ��
x300813_g_WinBangExp                   = 2
x300813_g_LoseBangExp                  = 2
x300813_g_DeuceBangExp                 = 2

x300813_g_Guild_Camp_A                 = 5
x300813_g_Guild_Camp_B                 = 6

x300813_g_Leader_Index                 = 5

x300813_g_Kick_Down                    = 8



----------------------------------------------------------------------------------------------
--����Ƿ��ǹ���ս��������������Ƿ���0���Ƿ���1
----------------------------------------------------------------------------------------------
function x300813_GetKingBattleSceneScript( sceneId )

    local name = GetBattleSceneName(sceneId)
    for i,item in x300813_g_SceneName do
        if name == item.Name then
            return item.Script
        end
    end

    return 0
end


----------------------------------------------------------------------------------------------
--�����
----------------------------------------------------------------------------------------------
function x300813_OnBattleStateEvent( sceneId, state  )

	--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --�������ݿ⿪��
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    --���Է�����
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --ս���Լ��Ŀ���
    if GetBattleSceneToggle( BATTLESCENE_TYPE_KINGBATTLE ) == 0 then
        return
    end


	local sceneType = GetSceneType(sceneId);
	if sceneType == 0 then --������������ͨ����

        if state == x300813_g_King_Signup then

            --���״̬�Ƿ��Ѿ��ù�
            local selfStatus = GetKingBattleStatus(sceneId)
            if selfStatus ~= STATE_KING_BATTLE_SIGNUP then
                
                --��¼��־
                local msg = format("KBL:STATE_KING_BATTLE_SIGNUP,SceneId=%d ",sceneId  )
                WriteLog(1,msg)

            end
            
            --��ʼ����
            SetKingBattleStatus(sceneId,STATE_KING_BATTLE_SIGNUP)
            
        elseif state == x300813_g_King_WaitBattle then

            --���״̬�Ƿ��Ѿ��ù�
            local selfStatus = GetKingBattleStatus(sceneId)
            if selfStatus ~= STATE_KING_BATTLE_SIGNUP_FINISH then
                
                --��¼��־
                local msg = format("KBL:STATE_KING_BATTLE_SIGNUP_FINISH,SceneId=%d ",sceneId )
                WriteLog(1,msg)

            end
            
            --��������
            SetKingBattleStatus(sceneId,STATE_KING_BATTLE_SIGNUP_FINISH)
            
        elseif state == x300813_g_King_BeginBattle then

            --���״̬�Ƿ��Ѿ��ù�
            local selfStatus = GetKingBattleStatus(sceneId)
            if selfStatus == STATE_KING_BATTLE_BATTLE then
                
                --��¼��־
                local msg = format("KBL:STATE_KING_BATTLE_BATTLE,SceneId=%d ",sceneId )
                WriteLog(1,msg)

            end
            
            --��ʼ����ս��
		    SetKingBattleStatus(sceneId,STATE_KING_BATTLE_BATTLE)
            SetKingBattleEnterSceneFlag( sceneId,1)

        elseif state == x300813_g_King_EndBattle then
            
            --����ս������
            SetKingBattleStatus(sceneId,STATE_KING_BATTLE_BATTLE_FINISH)

            --��¼��־
            local msg = format("KBL:STATE_KING_BATTLE_BATTLE_FINISH, SceneId=%d",sceneId )
            WriteLog(1,msg)

        end

	elseif sceneType == 2 then --���������ǹ���ս������
        
        --����Ƿ��ǹ���ս�������б���������������������ǣ��򲻴���
        local nScriptId = x300813_GetKingBattleSceneScript( sceneId )
        if  nScriptId == 0 then
            return
        end

        if state == x300813_g_King_Signup then

            --���״̬�Ƿ��Ѿ��ù�
            local selfStatus = GetKingBattleStatus(sceneId)
            if selfStatus ~= STATE_KING_BATTLE_READY then
                
                --��¼��־
                local msg = format("KBL:STATE_KING_BATTLE_SIGNUP,SceneId=%d,2 ",sceneId  )
                WriteLog(1,msg)

            end

            KingBattleAskInit( sceneId )                                               --��GLServerע��һ��
            SetKingBattleStatus(sceneId,STATE_KING_BATTLE_READY)                      --����״̬


            --���û�������
            SetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_SCRIPT,KINGBATTLE_FLOW_SCRIPT)

        elseif state == x300813_g_King_WaitBattle then

            --���״̬�Ƿ��Ѿ��ù�
            local selfStatus = GetKingBattleStatus(sceneId)
            if selfStatus ~= STATE_KING_BATTLE_SIGNUP_FINISH then
                
                --��¼��־
                local msg = format("KBL:STATE_KING_BATTLE_SIGNUP_FINISH,SceneId=%d,2",sceneId )
                WriteLog(1,msg)

            end

            --���û�������
            SetKingBattleStatus(sceneId,STATE_KING_BATTLE_SIGNUP_FINISH)
            SetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_SCRIPT,KINGBATTLE_FLOW_SCRIPT)

        elseif state == x300813_g_King_BeginBattle then

            --���״̬�Ƿ��Ѿ��ù�
            local selfStatus = GetKingBattleStatus(sceneId)
            if selfStatus ~= STATE_KING_BATTLE_BATTLE then
                
                --��¼��־
                local msg = format("KBL:STATE_KING_BATTLE_BATTLE,SceneId=%d,2",sceneId )
                WriteLog(1,msg)

            end

            --���û�������            
            SetKingBattleStatus(sceneId,STATE_KING_BATTLE_BATTLE)                     --���ÿ�ʼ����ս��
            SetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_SCRIPT,KINGBATTLE_FLOW_SCRIPT)
            SetKingBattleEnterSceneFlag( sceneId,1)

            x300813_OnBattleSceneReady( sceneId,( x300813_g_TotalBattleTime) )

        elseif state == x300813_g_King_EndBattle then

            local nState = GetKingBattleStatus( sceneId )
            if nState > STATE_KING_BATTLE_BATTLE or nState < STATE_KING_BATTLE_READY then
                
                --��¼��־
                local msg = format("KBL:STATE_KING_BATTLE_BATTLE_FINISH,Result:nState > STATE_KING_BATTLE_BATTLE or nState < STATE_KING_BATTLE_READY  SceneId=%d,state=%d,2",sceneId, nState )
                WriteLog(1,msg)

                --�����淨�Ľű��Ĳ�ͬ��������س�ʼ���ص�
                x300813_OnBattleSceneClose( sceneId )

                --��¼��־
                local msg = format("KBL:STATE_KING_BATTLE_BATTLE_FINISH, SceneId=%d,2",sceneId )
                WriteLog(1,msg)
                return
            end

            --����״̬�������
    		SetKingBattleStatus(sceneId,STATE_KING_BATTLE_BATTLE_FINISH)
            x300813_OnBattleSceneClose( sceneId )

            --��¼��־
            local msg = format("KBL:STATE_KING_BATTLE_BATTLE_FINISH, SceneId=%d,2",sceneId )
            WriteLog(1,msg)
        end
	end
end

----------------------------------------------------------------------------------------------
--����ս��������
----------------------------------------------------------------------------------------------
function x300813_ProcTiming( sceneId,uTime )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --����Ƿ��ǹ���ս�������б���������������������ǣ��򲻴���
    local nScriptId = x300813_GetKingBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end
       
    x300813_OnBattleSceneTimer( sceneId, uTime)
end


----------------------------------------------------------------------------------------------
--��ҽ����¼�
----------------------------------------------------------------------------------------------
function x300813_OnPlayerEnter( sceneId, playerId )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --����Ƿ��ǹ���ս�������б���������������������ǣ��򲻴���
    local nScriptId = x300813_GetKingBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    local status = GetKingBattleStatus( sceneId )
    if status ~= STATE_KING_BATTLE_BATTLE then
    
        --x300813_RestoreAllPlayerCamp( sceneId )
        --x300813_KingBattleKickAllPlayer(sceneId) --˳������������
        x300813_SetAllPlayerNeedKick( sceneId )
        --��¼��־
        local msg = format("KBL:x300813_OnBattlePlayerEnter Kick,Player,SceneId=%d,playerId=%d status=%d",sceneId,playerId,status )
        WriteLog(1,msg)
        return
    end


    --ȡ�ð��A�Ͱ��B
    local nGuildA = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_A_GUILD )
    local nGuildB = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_B_GUILD )

    local nGuildId = GetGuildID( sceneId,playerId )

    --������ս���е���Ӫ����
    local nSendCCamp = -1
    if nGuildId == nGuildA then
        nSendCCamp = 0
    elseif nGuildId == nGuildB then
        nSendCCamp = 1
    else
        SetPlayerRuntimeData( sceneId,playerId,RD_BATTLE_SCENE_KICK_DOWN ,x300813_g_Kick_Down) 
        --��¼��־
        local msg = format("KBL:x300813_OnBattlePlayerEnter Kick 2,Player,SceneId=%d,playerId=%d",sceneId,playerId )
        WriteLog(1,msg)
        return

    end

    --�������趨
    SetKingBattleDisable(sceneId, playerId, 0, nSendCCamp )

    local strGuildA = GetGuildName( nGuildA )
    local strGuildB = GetGuildName( nGuildB )

    SendKingBattleInfo( sceneId, playerId, strGuildA, strGuildB )

    --��ҽ���ս���������֮ǰ������
    SetPlayerRuntimeData(sceneId,playerId,RD_KING_BATTLE_BEKILLED,0)

    --������Ӫ
    
    if nGuildId == nGuildA then
        SetCurCamp(sceneId,playerId,x300813_g_Guild_Camp_A)
        SetPos(sceneId,playerId,50,204)

    elseif nGuildId == nGuildB then
        SetCurCamp(sceneId,playerId,x300813_g_Guild_Camp_B)
        SetPos(sceneId,playerId,206,48)
    end

    SetPlayerRuntimeData( sceneId,playerId,RD_BATTLE_SCENE_KICK_DOWN,-1)

    --�����ԭ�ȵĳ������б���
    local scenePre = GetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_SCENE_PRE ) - 1
    if scenePre >= 0 then
        
        local CurX = GetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_POSX_PRE)
        local CurZ = GetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_POSZ_PRE)

        SetPlayerBakSceneInfo(sceneId,playerId,scenePre,CurX,CurZ)

        SetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_SCENE_PRE,0)
        SetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_POSX_PRE,0)
        SetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_POSZ_PRE,0)

    end

end

----------------------------------------------------------------------------------------------
--����뿪�¼�
----------------------------------------------------------------------------------------------
function x300813_OnPlayerLeave( sceneId, playerId )
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --����Ƿ��ǹ���ս�������б���������������������ǣ��򲻴���
    local nScriptId = x300813_GetKingBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    local nCountryId = GetCurCountry(sceneId,playerId )
    SetCurCamp( sceneId,playerId,nCountryId )

    SetKingBattleDisable(sceneId, playerId,1,-1)
end

----------------------------------------------------------------------------------------------
--����˻�
----------------------------------------------------------------------------------------------
function x300813_OnPlayerLeaveGuild( sceneId,selfId )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --����Ƿ��ǹ���ս�������б���������������������ǣ��򲻴���
    local nScriptId = x300813_GetKingBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end
    
    x300813_KingBattleKickPlayer( sceneId,selfId )
    SetKingBattleDisable(sceneId, selfId,1,-1)

end

----------------------------------------------------------------------------------------------
--���ù���ս����������Ϣ
----------------------------------------------------------------------------------------------
function x300813_OnSetKingBattleMatchInfo( sceneId,nGuildA,nGuildB,nCountryId )
    
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return 
    end

    --����Ƿ��ǹ���ս�������б���������������������ǣ��򲻴���
    local nScriptId = x300813_GetKingBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    SetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_A_GUILD, nGuildA )
    SetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_B_GUILD, nGuildB )
    SetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_COUNTRYID, nCountryId )

    --debug
    local a = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_A_GUILD )
    local b = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_B_GUILD )
    local c = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_COUNTRYID )

    local msg = format( "KBL:KING_BATTLE_MATCHINFO:sceneId=%d,A=%d,B=%d,CountryId=%d", sceneId, a, b,c )
    WriteLog(1,msg)
end

----------------------------------------------------------------------------------------------
--�����������
----------------------------------------------------------------------------------------------
function x300813_OnPlayerNewConnectEnter( sceneId, selfId )
    
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return 
    end

    --����Ƿ��ǹ���ս�������б���������������������ǣ��򲻴���
    local nScriptId = x300813_GetKingBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    local BattleSceneFlag = GetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG)
    if BattleSceneFlag == 0 then

        --�����ߵ����,����Kick����ʱ��׼���ߵ�
        SetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN,x300813_g_Kick_Down)

        local name = GetName(sceneId,selfId)
        if name == nil then
            name = "ErrorName"
        end
        local msg = format( "KBL:x300813_OnPlayerNewConnectEnter 0,need kick,sceneId=%d,selfId=%d,name=%s", sceneId, selfId, name )
        WriteLog(1,msg)

    else

        --�ӱ�һ��������ת���������
        --ͬ������������,��ʱ��RD_BATTLESCENE_ENTER_FLAGֵĿǰ�޷���0��
        --ֻ��������뿪ս��������ʱ��������ǲ�ͬ��������Ŀ����������
        local name = GetName(sceneId,selfId)
        if name == nil then
            name = "ErrorName"
        end
        local msg = format( "KBL:x300813_OnPlayerNewConnectEnter 1,sceneId=%d,selfId=%d,name=%s", sceneId, selfId, name )
        WriteLog(1,msg)

        SetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG,0)

    end

    --x300813_KingBattleKickPlayer( sceneId,selfId )
end

----------------------------------------------------------------------------------------------
--�����������
----------------------------------------------------------------------------------------------
function x300813_OnPlayerDie( sceneId, selfId, killerId  )
    
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return 
    end

    --����Ƿ��ǹ���ս�������б���������������������ǣ��򲻴���
    local nScriptId = x300813_GetKingBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    --��¼��ɱ����
    local nBeKilled = GetPlayerRuntimeData(sceneId,selfId,RD_KING_BATTLE_BEKILLED ) + 1
    SetPlayerRuntimeData(sceneId,selfId,RD_KING_BATTLE_BEKILLED,nBeKilled)

    --�����ɱ����
    local ObjType = GetObjType(sceneId, killerId)

    --ɱ�������߲�������ң���ɱ��������6�����ڣ�����6�Σ�
    if IsPlayerStateNormal( sceneId,killerId ) == 1 and ObjType == 1 and nBeKilled <= 6 then

        AddGuildUserPoint(sceneId,killerId,10)

        local msg = "�������10��ﹱ"
        local name = GetName(sceneId,killerId )

        LuaScenceM2Player(sceneId, killerId, msg, name , 2,1)
    
    end

    --�������Σ�������ʾ
    if nBeKilled <= 6 then 

        local str = format("#G%s�ڹ���ս���б�ɱ��%d�Ρ�",GetName(sceneId,selfId ),nBeKilled )
        LuaThisScenceM2Wrold(sceneId,str,3,1)
        LuaThisScenceM2Wrold(sceneId,str,2,1)
    end

    --�����Σ�����ʾ
    if nBeKilled == 6 then

        local nCountryId = GetCurCountry( sceneId,selfId)

        local str = format("#G%s�ڹ���ս���У��������������������뿪ս����",GetName(sceneId,selfId ) )
        LuaAllScenceM2Country(sceneId,str,nCountryId,3,1)
        LuaAllScenceM2Country(sceneId,str,nCountryId,2,1)

        --RestoreHp(sceneId, selfId,100)
	    --RestoreRage(sceneId, selfId,100)
	    --ClearMutexState(sceneId, selfId, 6)
	    --SendReliveResult(sceneId, selfId,1)	

        --x300813_KingBattleKickPlayer( sceneId,selfId )

        --���뵹��ʱ��������ֹһֱ��ɱ�������˳�ս��
        local KickDown = GetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ) 
        if KickDown <= 0 or KickDown > 4 then
            SetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ,4) 
        end
    end

end

-------------------------------------------------------------------------------
--���״̬�Ƿ�����
-------------------------------------------------------------------------------
function x300813_CheckPlayerState( sceneId,selfId )
    

    local state
    local ErrorMsg

    state = IsPlayerStateNormal(sceneId,selfId )
    if state == 0 then
        ErrorMsg = "״̬�쳣"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_MENTALGAME )
    if state == 1 then
        ErrorMsg = "���ڴ���״̬�����ܽ���ս��"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_STALL )
    if state == 1 then
        ErrorMsg = "���ڰ�̯״̬�����ܽ���ս��"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_DIE )
    if state == 1 then
        ErrorMsg = "��������״̬�����ܽ���ս��"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_CRASHBOX )
    if state == 1 then
        ErrorMsg = "��������״̬�����ܽ���ս��"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_AUTOPLAY )
    if state == 1 then
        ErrorMsg = "���ڹһ�״̬�����ܽ���ս��"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_SUBTRAIN )
    if state == 1 then
        ErrorMsg = "���ڴ���״̬�����ܽ���ս��"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_BUS )
    if state == 1 then
        ErrorMsg = "����BUS״̬�����ܽ���ս��"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_PKMODE )
    if state == 1 then
        ErrorMsg = "PKֵ���߻��ڿ�ģʽ�����ܽ���ս��"
        return 1,ErrorMsg
    end

    return 0

end

-------------------------------------------------------------------------------
--����ս����ش��ͽű�
-------------------------------------------------------------------------------
function x300813_OnKingBattleChangeScene( sceneId,selfId,newSceneID,Flag )
    

    --����ڼ��������Ա�����
	if sceneId == PK_PUNISH_PRISON_SCENE_ID then
		BeginQuestEvent(sceneId)
		local strText = "�����ﻹ����ʵ,����,û�š�"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
	end

    local PosX = 100
    local PosZ = 100


    if sceneId == newSceneID then
        
        if Flag == 0 then
		    SetPos( sceneId , selfId , 50 , 204 )
        else
            SetPos( sceneId , selfId , 206,48 )
        end
	else
        
        --���״̬
        local state,msg = x300813_CheckPlayerState( sceneId,selfId )
        if state == 1 then
            
            BeginQuestEvent(sceneId)
            AddQuestText( sceneId, msg );
            EndQuestEvent(sceneId)
            DispatchQuestTips(sceneId,selfId)
            return
        end

        --��¼һ��RuntimeData
        local nCurX,nCurZ = GetWorldPos( sceneId,selfId )
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_SCENE_PRE,sceneId + 1)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSX_PRE,nCurX)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSZ_PRE,nCurZ)
        SetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG,1)

		NewWorld( sceneId , selfId , newSceneID , PosX , PosZ,300813 )
	end
end

function x300813_DoPlayerRelive( sceneId, selfId )
	
	if GetHp(sceneId,selfId) > 0 then
		return
	end
	
    RestoreHp(sceneId, selfId,0)
	RestoreRage(sceneId, selfId,100)
	ClearMutexState(sceneId, selfId, 6)
	SendReliveResult(sceneId, selfId,1)	

    --�������״̬
    RelivePlayerNM(sceneId,selfId,2)	
    SetPlayerMutexState(sceneId,selfId,PLAYER_STATE_DIE,0)
end

--����ս������
function x300813_OnPlayerRelive( sceneId, selfId )

    --����Ƿ��ǹ���ս��
    local nScriptId = x300813_GetKingBattleSceneScript( sceneId )
    if nScriptId == 0 then
        return
    end
    
    --������������Ƿ񳬹�6��
    local nBeKilled = GetPlayerRuntimeData(sceneId,selfId,RD_KING_BATTLE_BEKILLED )
    if nBeKilled >= 6 then
        
        --����һ�α���
        local KickDown = GetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ) 
        if KickDown <= 0 or KickDown > 4 then
            SetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ,4) 
        end
        
        return
    end
    
    --ִ�и������
    ClearRageRecoverTick(sceneId, selfId)
	RestoreHp(sceneId, selfId,100)
	RestoreRage(sceneId, selfId,100)
	ClearMutexState(sceneId, selfId, 6)
	SendReliveResult(sceneId, selfId,1)

	--�õ������������A��B��
    local nGuildId = GetGuildID( sceneId,selfId )
    local nGuildA = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_A_GUILD )
    local nGuildB = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_B_GUILD )

    if nGuildId == nGuildA then

        x300813_OnKingBattleChangeScene(sceneId,selfId,sceneId,0)
    else
        x300813_OnKingBattleChangeScene(sceneId,selfId,sceneId,1)
    end

end


----------------------------------------------------------------------------------------------
--���쳡����ʼ��
----------------------------------------------------------------------------------------------
function x300813_OnBattleSceneReady( sceneId,totalTime )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --��������س�ʼ��
    SetKingBattleSceneData_Param( sceneId,LD_KING_BATTLE_COUNT_DOWN_STATE,-1 )
    SetKingBattleSceneData_Param( sceneId,LD_KING_BATTLE_COUNT_DOWN_TIME,10 )

    --��������ʱ��
    --SetKingBattleSceneData_Timer( sceneId,1000 )
    SetKingBattleSceneData_Param( sceneId,LD_KING_BATTLE_COUNT_ITME,totalTime )

end

function x300813_OnBattleSceneClose( sceneId )

    if GetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_COUNT_DOWN_STATE) == 1 then
        return
    end

    local status = GetKingBattleStatus( sceneId )
	if status == STATE_KING_BATTLE_BATTLE_FINISH then
		x300813_BattleGenResult( sceneId,0 )
	end


end

----------------------------------------------------------------------------------------------
--����ս��������
----------------------------------------------------------------------------------------------
function x300813_OnBattleSceneTimer( sceneId,uTime )

    --��ؼ��
    ----------------------------------------------------------------------------------------------
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --�������Kick״̬
    x300813_UpdatePlayerKickState( sceneId )

    local BattleStatus = GetKingBattleStatus(sceneId)
    if BattleStatus ~= STATE_KING_BATTLE_BATTLE then
        return
    end

    --��ʱ
    ----------------------------------------------------------------------------------------------
    local nTime = GetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_COUNT_ITME ) - 1
    SetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_COUNT_ITME,nTime )

    --����ʱ����
    ----------------------------------------------------------------------------------------------
    if GetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_COUNT_DOWN_STATE) == 1 then

	    --����ʱ״̬
	    local time = GetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_COUNT_DOWN_TIME)
	    if time > 0 then

		    SetKingBattleSceneData_Param( sceneId,LD_KING_BATTLE_COUNT_DOWN_TIME,time-1 )

		    local str = format("#G����ս������,#R%d��#G��ս���Զ��ر�",time)

		    LuaThisScenceM2Guild(sceneId,str,GetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_A_GUILD),3,1)
		    LuaThisScenceM2Guild(sceneId,str,GetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_B_GUILD),3,1)

		else

		    --����ʱ����
	    	SetKingBattleSceneData_Param( sceneId,LD_KING_BATTLE_COUNT_DOWN_STATE,-1 )
            
            --�ߵ��������
            x300813_RestoreAllPlayerCamp( sceneId )
	    	x300813_KingBattleKickAllPlayer(sceneId)

		 	--ֹͣ����
			--SetKingBattleSceneData_Timer(sceneId,0)
			ClearKingBattleSceneData(sceneId)
            
            --��¼��־
            local msg = format("KBL:x300813_OnBattleSceneTimer KingBattleFinished,SceneId=%d,LeaveTime h= %d,m=%d",sceneId, floor(nTime/60),mod(nTime,60) )
            WriteLog(1,msg)

	    end

	    return

	end

    --����Ƿ����
    ----------------------------------------------------------------------------------------------
    if nTime < 18*60 then
        local bIsFinished = x300813_CheckIsFinished( sceneId)
        if bIsFinished == 1 then
            
            local status = GetKingBattleStatus( sceneId )
            if status == STATE_KING_BATTLE_BATTLE then

                x300813_BattleGenResult( sceneId,1 )
                return
            end

        end
    end
	

    --��ʱ��ʱ��ͬ��
    ----------------------------------------------------------------------------------------------
    --x300813_SyncBattleTimeToAllPlayer( sceneId, nTime )
    x300813_SyncGuildPower( sceneId )

    --С��ͼ����ʾ����
    x300813_UpdateSceneDataFlag( sceneId )

end


----------------------------------------------------------------------------------------------
--����Ƿ���Խ���
----------------------------------------------------------------------------------------------
function x300813_CheckIsFinished( sceneId )

    
    --�ռ���Ϣ
    local nGuildA = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_A_GUILD )
    local nGuildB = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_B_GUILD )

    local nGuildA_MemberCount = 0
    local nGuildB_MemberCount = 0


    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local nGuildId = GetGuildID( sceneId,objId )
            if nGuildId == nGuildA then
                nGuildA_MemberCount = nGuildA_MemberCount + 1
            elseif nGuildId == nGuildB then
                nGuildB_MemberCount = nGuildB_MemberCount + 1
            end
        end
    end

    if nGuildA_MemberCount == 0 and nGuildB_MemberCount == 0 then
        return 1
    end

    --һ�����ˣ�����Խ���
    if nGuildA_MemberCount == 0 and nGuildB_MemberCount > 0 then
        return 1
    end

    if nGuildB_MemberCount == 0 and nGuildA_MemberCount > 0 then
        return 1
    end

    return 0

end


----------------------------------------------------------------------------------------------
--�õ���ʤ����0ΪA����ʤ��1ΪB����ʤ��-1Ϊƽ��
----------------------------------------------------------------------------------------------
function x300813_GetWinner(sceneId)

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return -1
    end

    --�ռ���Ϣ
    local nGuildA = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_A_GUILD )
    local nGuildB = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_B_GUILD )

    local nGuildA_MemberCount = 0
    local nGuildB_MemberCount = 0

    local nGuildA_GuildIn = 0
    local nGuildB_GuildIn = 0

    local nGuildA_GuilderDie = 0
    local nGuildB_GuilderDie = 0

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local nGuildId = GetGuildID( sceneId,objId )
            if nGuildId == nGuildA then
                nGuildA_MemberCount = nGuildA_MemberCount + 1
            elseif nGuildId == nGuildB then
                nGuildB_MemberCount = nGuildB_MemberCount + 1
            end

            local pos = GetGuildOfficial(sceneId, objId)
	        if pos == x300813_g_Leader_Index then
                if nGuildId == nGuildA then
                    nGuildA_GuildIn = 1
                    nGuildA_GuilderDie = GetPlayerRuntimeData(sceneId,objId,RD_KING_BATTLE_BEKILLED )
                else
                    nGuildB_GuildIn = 1
                    nGuildB_GuilderDie = GetPlayerRuntimeData(sceneId,objId,RD_KING_BATTLE_BEKILLED )
                end
            end
        end
    end


    --ʤ���ж�

    --�����ж�ֻ��һ�������ڵ�Ӯ
    if nGuildA_GuildIn == 1 and nGuildB_GuildIn == 0 then
        return 0
    end

    if nGuildA_GuildIn == 0 and nGuildB_GuildIn == 1 then
        return 1
    end

    --�������ڻ��Ƕ����ڣ����ж��������Ӯ
    if nGuildA_MemberCount == 0 and nGuildB_MemberCount > 0 then
        return 1
    end

    if nGuildB_MemberCount == 0 and nGuildA_MemberCount > 0 then
        return 0
    end

    --���������0������Ϊ�˶��һ��Ӯ
    if nGuildA_MemberCount > 0 and nGuildB_MemberCount > 0 then
        if nGuildA_MemberCount > nGuildB_MemberCount then
            return 0
        elseif nGuildA_MemberCount < nGuildB_MemberCount then
            return 1
        else
            
            
            if nGuildA_GuildIn == 0 and nGuildB_GuildIn == 0 then
                --������ͬ�����������ڣ�����Ӯ
                return 1            
            elseif nGuildA_GuildIn == 1 and nGuildB_GuildIn == 0 then
                --������ͬ���������Ĵ���ΪӮ
                return 0
            elseif nGuildA_GuildIn == 0 and nGuildB_GuildIn == 1 then
                --������ͬ���������Ĵ���ΪӮ
                return 1
            else
                --������ͬ���������Ĵ���ΪӮ
                if nGuildA_GuilderDie > nGuildB_GuilderDie then
                    return 1

                elseif nGuildA_GuilderDie < nGuildB_GuilderDie then
                    return 0

                --������ͬ���������Ĵ�����ͬ��������Ӯ
                else
                    return 1
                end
            end
        end
    end

    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300813_BattleBonus( sceneId,selfId,battleResult )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

end

----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x300813_KingBattleBonus( sceneId ,battleResult )

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            x300813_BattleBonus( sceneId,objId,battleResult)
        end
    end
end


----------------------------------------------------------------------------------------------
--�ָ���Ӫ
----------------------------------------------------------------------------------------------
function x300813_RestorePlayerCamp( sceneId,selfId )
    local nCountryId = GetCurCountry( sceneId,selfId )
    SetCurCamp(sceneId,selfId,nCountryId )
end

----------------------------------------------------------------------------------------------
--�ָ���Ӫ
----------------------------------------------------------------------------------------------
function x300813_RestoreAllPlayerCamp( sceneId )

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local nCountryId = GetCurCountry( sceneId,objId )
            SetCurCamp(sceneId,objId,nCountryId )
        end
    end
end

----------------------------------------------------------------------------------------------
--���ɰ�ս���
----------------------------------------------------------------------------------------------
function x300813_BattleGenResult( sceneId, callerId  )
    
    local nGuildA = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_A_GUILD )
    local nGuildB = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_B_GUILD )

    local nCountryId = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_COUNTRYID )

    if nGuildA == nGuildB then
        return
    end

    local nWinner = x300813_GetWinner( sceneId )
    if nWinner == 0 then
        --��ս����ȡ

        local strGuildName = GetGuildName(nGuildA)
        local strGuildLeaderName = GetGuildLeaderName(nGuildA)
        
        local str = format("#G%s�����%s����ս����ʤ����%s�����˹����ı����� ",strGuildName,GetCountryName(nCountryId),strGuildLeaderName)
        LuaAllScenceM2Wrold(sceneId, str, 2, 1)
        LuaAllScenceM2Wrold(sceneId, str, 3, 1)

        SendKingBattleResultToGL( nCountryId,1,nGuildA,nGuildB)

    else
        --��������ȡ
        local strGuildName = GetGuildName(nGuildB)
        
        local str = format("#G%s����Ž�һ�µĶ�ס����ս��������%s�����ı�����  ",strGuildName,GetCountryName(nCountryId) )
        local nKingGuildID = GetCountryKingGuildIdNM( nCountryId )
        if nKingGuildID < 0 then
        	--û�й����Ĵ���
        	local strGuildLeaderName = GetGuildLeaderName(nGuildB)
        	str = format("#G%s�����%s����ս����ʤ����%s�����˹����ı����� ",strGuildName,GetCountryName(nCountryId),strGuildLeaderName)
        end
        LuaAllScenceM2Wrold(sceneId, str, 2, 1)
        LuaAllScenceM2Wrold(sceneId, str, 3, 1)

        SendKingBattleResultToGL( nCountryId,0,nGuildA,nGuildB)
    end

    --���뵹��ʱ״̬,�����õ���ʱ��
    SetKingBattleSceneData_Param( sceneId,LD_KING_BATTLE_COUNT_DOWN_STATE,1 )
    SetKingBattleSceneData_Param( sceneId,LD_KING_BATTLE_COUNT_DOWN_TIME,10 )

    local nTime = GetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_COUNT_ITME )
        
    --��¼��־
    local msg = format("KBL:x300813_BattleGenResult SceneId=%d,LeaveTime h= %d,m=%d,CallerId=%d nWinner=%d,GuildA=%d,name=%s,GuildB=%d,name=%s",sceneId, floor(nTime/60),mod(nTime,60), callerId,nWinner,nGuildA,GetGuildName(nGuildA),nGuildB,GetGuildName(nGuildB) )
    WriteLog(1,msg)

    SetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_A_GUILD,-1 )
    SetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_B_GUILD,-1 )

    x300813_SetAllPlayerNeedKick(sceneId)
    ClearKingBattleSceneData(sceneId)
    
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300813_KingBattleKickPlayer( sceneId,selfId )

    x300813_DoPlayerRelive( sceneId,selfId )

    x300813_RestorePlayerCamp( sceneId,selfId)

    --ֻҪ����뿪ս����������������÷�
    SetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG,0)

    --�������BakScene��Ϣ������BakScene��ϢΪ׼
    local nBakSceneId,x,z = GetPlayerBakSceneInfo(sceneId,selfId )
    if nBakSceneId >= 0 then
        NewWorld(sceneId,selfId,nBakSceneId,x,z,300813)
        return
    end

    --ѡ��һ�����ʵĳ������ͳ�ȥ
    local nCountry = GetCurCountry(sceneId,selfId)
    if nCountry == 0 then
        
        --¥��
        local nDestSceneId = 50
        local nPosX = 188
        local nPosZ = 39

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300813)

    elseif nCountry == 1 then
        
        --��ɽ
        local nDestSceneId = 150
        local nPosX = 187
        local nPosZ = 49

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300813)

    elseif nCountry == 2 then

        --����
        local nDestSceneId = 250
        local nPosX = 78
        local nPosZ = 217

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300813)

    elseif nCountry == 3 then
        
        --�ػ�
        local nDestSceneId = 350
        local nPosX = 65
        local nPosZ = 209

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300813)

    end
end

----------------------------------------------------------------------------------------------
--�ߵ����������е���
----------------------------------------------------------------------------------------------
function x300813_KingBattleKickAllPlayer( sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            
            x300813_KingBattleKickPlayer( sceneId,objId)

        end
    end
end


----------------------------------------------------------------------------------------------
--ͬ����ս����ʱ��ȫ����ң���ǰ������
----------------------------------------------------------------------------------------------
function x300813_SyncBattleTimeToAllPlayer( sceneId ,nTime )

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then

            TimerCommand( sceneId, objId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, GUILDBATTLE_SCRIPTID,-1,-1);                 --��ǿ�ƹر�

            if nTime > 0 then
                TimerCommand( sceneId, objId, 2, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, GUILDBATTLE_SCRIPTID, nTime, nTime );
            end
        end
    end    
end

----------------------------------------------------------------------------------------------
--ͬ����ս����ʱ�ر���Ϣ��ȫ����ң���ǰ������
----------------------------------------------------------------------------------------------
function x300813_SyncBattleTimeCloseToAllPlayer(sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then

            TimerCommand( sceneId, objId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, GUILDBATTLE_SCRIPTID,-1,-1);                 --��ǿ�ƹر�
        end
    end    

end

----------------------------------------------------------------------------------------------
--ͬ���������
----------------------------------------------------------------------------------------------
function x300813_SyncGuildPower( sceneId )
    
    local nGuildA = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_A_GUILD )
    local nGuildB = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_B_GUILD )

    local nGuildA_Count = 0
    local nGuildB_Count = 0

    --ͳ��������������ڲ��ܴ�����ҵ��ߵ�����������������������ͬ���������
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local nGuildId = GetGuildID( sceneId,objId )
            if nGuildId == nGuildA then
                nGuildA_Count = nGuildA_Count + 1
            elseif nGuildId == nGuildB then
                nGuildB_Count = nGuildB_Count + 1
            end
        end
    end

    --ͬ�������
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            SyncKingBattlePowerInfo(sceneId,objId,nGuildA_Count,nGuildB_Count)
        end
    end

end

----------------------------------------------------------------------------------------------
--����С��ͼ
----------------------------------------------------------------------------------------------
function x300813_UpdateSceneDataFlag( sceneId )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    ClearSceneMapDataFlag( sceneId )

	SetSceneMapDataFlag( sceneId,10,8,"˹��������������",47.8,220,-1)
	SetSceneMapDataFlag( sceneId,11,8,"��������������",210.5,30,-1)

    --���°�����λ��
    local GuildLeaderA = -1
    local GuildLeaderB = -1
    
    local nGuildA = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_A_GUILD )
    local nGuildB = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_B_GUILD )

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            
            local pos = GetGuildOfficial(sceneId, objId)
	        if pos == x300813_g_Leader_Index then
                local nGuild = GetGuildID( sceneId,objId )
                if nGuild == nGuildA then
                    GuildLeaderA = objId
                elseif nGuild == nGuildB then
                    GuildLeaderB = objId
                end
            end
        end
    end


    local a_leader_name = ""
    local a_leader_x = 0
    local a_leader_z = 0
    
    if GuildLeaderA > 0 then
        
        a_leader_name = GetName(sceneId,GuildLeaderA)
        a_leader_x,a_leader_z = GetWorldPos(sceneId,GuildLeaderA)
    end

    local b_leader_name = ""
    local b_leader_x = 0
    local b_leader_z = 0
    
    if GuildLeaderB > 0 then

        b_leader_name = GetName(sceneId,GuildLeaderB)
        b_leader_x,b_leader_z = GetWorldPos(sceneId,GuildLeaderB)
    end

    --���Ͱ���״̬
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            
            if GuildLeaderA > 0 and GuildLeaderA ~= objId then
                SetSceneMapDataFlagToPlayer( sceneId,objId,12,8,a_leader_name,a_leader_x,a_leader_z,-1)
            end

            if GuildLeaderB > 0 and GuildLeaderB ~= objId then
                SetSceneMapDataFlagToPlayer( sceneId,objId,13,8,b_leader_name,b_leader_x,b_leader_z,-1)
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--����ս������ı���
----------------------------------------------------------------------------------------------
--function x300813_OnKingEnterError( sceneId,selfId,nErrorId )
--    
--    if nErrorId == 0 then
--        
--        local name = GetName(sceneId,selfId )
--        LuaScenceM2Player( sceneId,selfId,"ֻ�вμӰ��֮����ܽ��룡",name,3,1)
--
--    elseif nErrorId == 1 then
--        
--        local name = GetName(sceneId,selfId )
--        LuaScenceM2Player( sceneId,selfId,"���İ��û�б�����",name,3,1)
--
--    elseif nErrorId == 2 then
--        
--        local name = GetName(sceneId,selfId )
--        LuaScenceM2Player( sceneId,selfId,"����ս����û������ʱ�䣡",name,3,1)
--
--    elseif nErrorId == 3 then
--        
--        local name = GetName(sceneId,selfId )
--        LuaScenceM2Player( sceneId,selfId,"����ս���Ѿ��ر���ڣ����������ӣ�",name,3,1)
--
--    elseif nErrorId == 4 then
--        
--        local name = GetName(sceneId,selfId )
--        LuaScenceM2Player( sceneId,selfId,"Ŀǰû�й���ս����ʼ",name,3,1)
--
--    elseif nErrorId == 5 then
--        
--        local name = GetName(sceneId,selfId )
--        LuaScenceM2Player( sceneId,selfId,"ս����������",name,3,1)
--
--    elseif nErrorId == 6 then
--        
--        local name = GetName(sceneId,selfId )
--        LuaScenceM2Player( sceneId,selfId,"���Ѿ������ս���������ظ����룡",name,3,1)
--
--    else
--        local name = GetName(sceneId,selfId )
--        LuaScenceM2Player( sceneId,selfId,"δ֪���󣬲��ܽ��룡",name,3,1)
--    end
--
--end


----------------------------------------------------------------------------------------------
--��GLServer������ͬ������ս��ʱ��Ķ���
----------------------------------------------------------------------------------------------
function x300813_OnSyncKingBattleTime( sceneId,nTime )
    
    if x300813_GetKingBattleSceneScript( sceneId ) == 0 then
        return
    end

    local nTime_new = x300813_g_TotalBattleTime - NumberCastIntToUInt( nTime )
    SetKingBattleSceneData_Param(sceneId, LD_KING_BATTLE_COUNT_ITME, nTime_new )

    --��ʱ��ʱ��ͬ��
    ----------------------------------------------------------------------------------------------
    x300813_SyncBattleTimeToAllPlayer( sceneId, nTime_new )
end

----------------------------------------------------------------------------------------------
--�������������Ҫ�ߵ�
----------------------------------------------------------------------------------------------
function x300813_SetAllPlayerNeedKick( sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local KickDown = GetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ) 
            if KickDown <= 0 or KickDown > x300813_g_Kick_Down then                
                SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,x300813_g_Kick_Down) 
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--��������ߵ�״̬
----------------------------------------------------------------------------------------------
function x300813_UpdatePlayerKickState( sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local KickDown = GetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ) 
            if KickDown > 0 then                
                KickDown = KickDown - 1 
                if KickDown == 0 then
                    --����ʱΪ�㣬�ߵ�
                    SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,-1) 
                    x300813_KingBattleKickPlayer( sceneId,objId )                    
                else
                    --���򣬼�������ʱ
                    SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,KickDown) 
                end
            end
        end
    end
end
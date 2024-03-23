
x310110_g_scriptId                      = 310110
x310110_g_TotalBattleTime               = 60 * 20     	--ս������ʱ��1200��        19:00-19:20

--�淨����
x310110_g_SceneName                     = { {Name="zhanchang_qinglongshouhu/zhanchang_qinglongshouhu.scn",Script=310110} }

x310110_g_QingLong_Signup                  = 200     --����
x310110_g_QingLong_WaitBattle              = 201     --�����������ȴ�����ս��
x310110_g_QingLong_BeginBattle             = 202     --��ʼ����ս��
x310110_g_QingLong_EndBattle               = 203     --��������ս��

--�������
x310110_g_MaxScore                     = 49	     --��0��ʼ����
x310110_g_BonusTips                    = "#G�������#R%d#G�㾭��,#R%d#G���ṱ��,#R%d#G��ᾭ��!" --������ʾ
x310110_g_BonusTips1                   = "������˽���" --������ʾ


--���齱��
x310110_g_WinPrise                     = 1000*0.5*20              --��ʤ�����齱��ϵ����ֻ��ȼ��й�
x310110_g_LosePrise                    = 1000*0.1*20              --ʧ�ܷ����齱��ϵ����ֻ��ȼ��й�
x310110_g_DeucePrise                   = 1000*0.3*20              --սƽʱ���齱��ϵ����ֻ��ȼ��й�

--�ﹱ����
x310110_g_WinBangGong                  = 25
x310110_g_DeuceBangGong                = 20

--��ᾭ��
x310110_g_WinBangExp                   = 2
x310110_g_LoseBangExp                  = 2
x310110_g_DeuceBangExp                 = 2

x310110_g_Guild_Camp_A                 = 5
x310110_g_Guild_Camp_B                 = 6

x310110_g_Leader_Index                 = 5

x310110_g_Kick_Down                    = 8


--���״̬����
x310110_g_BattleState				   = {}
x310110_g_BattleEnterFlag			   = {}
x310110_g_GuildA					   = {}
x310110_g_GuildB					   = {}
x310110_g_CountryID					   = {}
x310110_g_CountDownState			   = {}
x310110_g_CountDownTime				   = {}
x310110_g_CountTime				       = {}


----------------------------------------------------------------------------------------------
--��ʼ����ͼ����
----------------------------------------------------------------------------------------------
function x310110_OnMapInit(sceneId)
	
	x310110_g_BattleState[sceneId]				   	= -1
	x310110_g_BattleEnterFlag[sceneId]			   	= 0
	x310110_g_GuildA[sceneId]					   	= -1
	x310110_g_GuildB[sceneId]					   	= -1
	x310110_g_CountryID[sceneId]					= -1
	x310110_g_CountDownState[sceneId]			   	= -1
	x310110_g_CountDownTime[sceneId]				= -1
	x310110_g_CountTime[sceneId]				    = -1
	
end


----------------------------------------------------------------------------------------------
--ȡ��ս��״̬
----------------------------------------------------------------------------------------------
function x310110_GetBattleState(sceneId)
	
	return x310110_g_BattleState[sceneId]
	
end

----------------------------------------------------------------------------------------------
--ȡ��ս��������
----------------------------------------------------------------------------------------------
function x310110_GetBattleEnterSceneFlag(sceneId)
	return x310110_g_BattleEnterFlag[sceneId];
end

----------------------------------------------------------------------------------------------
--���ý�ս�����
----------------------------------------------------------------------------------------------
function x310110_SetBattleEnterSceneFlag(sceneId,nEnterSceneFlag)
	x310110_g_BattleEnterFlag[sceneId] = nEnterSceneFlag
end

----------------------------------------------------------------------------------------------
--����Ƿ�������ս��������������Ƿ���0���Ƿ���1
----------------------------------------------------------------------------------------------
function x310110_GetQingLongBattleSceneScript( sceneId )

    local name = GetBattleSceneName(sceneId)
    for i,item in x310110_g_SceneName do
        if name == item.Name then
            return item.Script
        end
    end

    return 0
end


----------------------------------------------------------------------------------------------
--�����
----------------------------------------------------------------------------------------------
function x310110_OnBattleStateEvent( sceneId, state  )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_QINGLONGBATTLELITE ) == 0 then
        return
    end


	local sceneType = GetSceneType(sceneId);
	if sceneType == 0 then 

		-----------------------------------------------------------------------------------
		--������������ͨ����
		-----------------------------------------------------------------------------------
		
        if state == x310110_g_QingLong_Signup then

            --���״̬�Ƿ��Ѿ��ù�
            if x310110_g_BattleState[sceneId] ~= x310110_g_QingLong_Signup then
                local msg = format("QLBL:x310110_g_QingLong_Signup,SceneId=%d ",sceneId  )
                WriteLog(1,msg)
            end

            
            x310110_g_BattleState[sceneId] = x310110_g_QingLong_Signup
            
        elseif state == x310110_g_QingLong_WaitBattle then

            --���״̬�Ƿ��Ѿ��ù�
            if x310110_g_BattleState[sceneId] ~= x310110_g_QingLong_WaitBattle then
                local msg = format("QLBL:x310110_g_QingLong_WaitBattle,SceneId=%d ",sceneId )
                WriteLog(1,msg)
            end
            
            --��������
            x310110_g_BattleState[sceneId] = x310110_g_QingLong_WaitBattle
            
        elseif state == x310110_g_QingLong_BeginBattle then

            --���״̬�Ƿ��Ѿ��ù�
            if x310110_g_BattleState[sceneId] == x310110_g_QingLong_BeginBattle then
                local msg = format("QLBL:x310110_g_QingLong_BeginBattle,SceneId=%d ",sceneId )
                WriteLog(1,msg)
            end
            
            --��ʼ����ս��
            x310110_g_BattleState[sceneId] = x310110_g_QingLong_BeginBattle
            x310110_g_BattleEnterFlag[sceneId] = 1

        elseif state == x310110_g_QingLong_EndBattle then
            
            --����ս������
            x310110_g_BattleState[sceneId] = x310110_g_QingLong_EndBattle

            local msg = format("QLBL:x310110_g_QingLong_EndBattle, SceneId=%d",sceneId )
            WriteLog(1,msg)

        end

	elseif sceneType == 2 then
	
		-----------------------------------------------------------------------------------
		--��������������ս������
		-----------------------------------------------------------------------------------
        
        --����Ƿ�������ս�������б���������������������ǣ��򲻴���
        local nScriptId = x310110_GetQingLongBattleSceneScript( sceneId )
        if  nScriptId == 0 then
            return
        end

        if state == x310110_g_QingLong_Signup then

            --���״̬�Ƿ��Ѿ��ù�
            if x310110_g_BattleState[sceneId] ~= x310110_g_QingLong_Signup then
                
                --��¼��־
                local msg = format("QLBL:x310110_g_QingLong_Signup,SceneId=%d,2 ",sceneId  )
                WriteLog(1,msg)

            end

            GameBattleSceneAskInit( sceneId,1 )                                             --��GLServerע��һ��
            x310110_g_BattleState[sceneId] = x310110_g_QingLong_Signup		                      	--����״̬

        elseif state == x310110_g_QingLong_WaitBattle then

            --���״̬�Ƿ��Ѿ��ù�
            if x310110_g_BattleState[sceneId] ~= x310110_g_QingLong_WaitBattle then
                local msg = format("QLBL:x310110_g_QingLong_WaitBattle,SceneId=%d,2",sceneId )
                WriteLog(1,msg)
            end

            --���û�������
            x310110_g_BattleState[sceneId] = x310110_g_QingLong_WaitBattle
            
        elseif state == x310110_g_QingLong_BeginBattle then

            --���״̬�Ƿ��Ѿ��ù�
            if x310110_g_BattleState[sceneId] ~= x310110_g_QingLong_BeginBattle then
                local msg = format("QLBL:x310110_g_QingLong_BeginBattle,SceneId=%d,2",sceneId )
                WriteLog(1,msg)
            end

            --���û�������            
            x310110_g_BattleState[sceneId] = x310110_g_QingLong_BeginBattle
            x310110_OnBattleSceneReady( sceneId,( x310110_g_TotalBattleTime) )

        elseif state == x310110_g_QingLong_EndBattle then

            if x310110_g_BattleState[sceneId] > x310110_g_QingLong_BeginBattle or x310110_g_BattleState[sceneId] < x310110_g_QingLong_Signup then
                
                local msg = format("QLBL:x310110_g_QingLong_EndBattle,Result:nState > x310110_g_QingLong_BeginBattle or nState < x310110_g_QingLong_Signup  SceneId=%d,state=%d,2",sceneId, state )
                WriteLog(1,msg)

                --�����淨�Ľű��Ĳ�ͬ��������س�ʼ���ص�
                x310110_OnBattleSceneClose( sceneId )

                local msg = format("QLBL:x310110_g_QingLong_EndBattle, SceneId=%d,2",sceneId )
                WriteLog(1,msg)
                return
            end

            --����״̬�������
    		x310110_g_BattleState[sceneId] = x310110_g_QingLong_EndBattle 
            x310110_OnBattleSceneClose( sceneId )

            local msg = format("QLBL:x310110_g_QingLong_EndBattle, SceneId=%d,3",sceneId )
            WriteLog(1,msg)
        end
	end
end

----------------------------------------------------------------------------------------------
--����ս��������
----------------------------------------------------------------------------------------------
function x310110_ProcTiming( sceneId,uTime )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --����Ƿ�������ս�������б���������������������ǣ��򲻴���
    local nScriptId = x310110_GetQingLongBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end
       
    x310110_OnBattleSceneTimer( sceneId, uTime)
end


----------------------------------------------------------------------------------------------
--��ҽ����¼�
----------------------------------------------------------------------------------------------
function x310110_OnPlayerEnter( sceneId, playerId )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --����Ƿ�������ս�������б���������������������ǣ��򲻴���
    local nScriptId = x310110_GetQingLongBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    local status = x310110_g_BattleState[sceneId]
    if status ~= x310110_g_QingLong_BeginBattle then
    
        x310110_SetAllPlayerNeedKick( sceneId )
        
        local msg = format("QLBL:x310110_OnBattlePlayerEnter Kick,Player,SceneId=%d,playerId=%d status=%d",sceneId,playerId,status )
        WriteLog(1,msg)
        return
    end


    --ȡ�ð��A�Ͱ��B
    local nGuildA = x310110_g_GuildA[sceneId]
    local nGuildB = x310110_g_GuildB[sceneId]

    local nGuildId = GetGuildID( sceneId,playerId )

    --������ս���е���Ӫ����
    local nSendCCamp = -1
    if nGuildId == nGuildA then
        nSendCCamp = 0
    elseif nGuildId == nGuildB then
        nSendCCamp = 1
    else
        SetPlayerRuntimeData( sceneId,playerId,RD_BATTLE_SCENE_KICK_DOWN ,x310110_g_Kick_Down) 
        --��¼��־
        local msg = format("QLBL:x310110_OnBattlePlayerEnter Kick 2,Player,SceneId=%d,playerId=%d",sceneId,playerId )
        WriteLog(1,msg)
        return

    end

    --�������趨
    GameBattleSetDisable(sceneId, playerId, 0, nSendCCamp,1 )

    local strGuildA = GetGuildName( nGuildA )
    local strGuildB = GetGuildName( nGuildB )

    GameBattleSendBattleInfo( sceneId, playerId, strGuildA, strGuildB,1 )

    --��ҽ���ս���������֮ǰ������
    SetPlayerRuntimeData(sceneId,playerId,RD_KING_BATTLE_BEKILLED,0)

    --������Ӫ
    
    if nGuildId == nGuildA then
        SetCurCamp(sceneId,playerId,x310110_g_Guild_Camp_A)
        SetPos(sceneId,playerId,47,218)

    elseif nGuildId == nGuildB then
        SetCurCamp(sceneId,playerId,x310110_g_Guild_Camp_B)
        SetPos(sceneId,playerId,209,35)
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
function x310110_OnPlayerLeave( sceneId, playerId )
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --����Ƿ�������ս�������б���������������������ǣ��򲻴���
    local nScriptId = x310110_GetQingLongBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    local nCountryId = GetCurCountry(sceneId,playerId )
    SetCurCamp( sceneId,playerId,nCountryId )

    GameBattleSetDisable(sceneId, playerId,1,-1,1)
end

----------------------------------------------------------------------------------------------
--����˻�
----------------------------------------------------------------------------------------------
function x310110_OnPlayerLeaveGuild( sceneId,selfId )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --����Ƿ�������ս�������б���������������������ǣ��򲻴���
    local nScriptId = x310110_GetQingLongBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end
    
    x310110_QingLongBattleKickPlayer( sceneId,selfId )
    GameBattleSetDisable(sceneId, selfId,1,-1,1)

end

----------------------------------------------------------------------------------------------
--��������ս����������Ϣ
----------------------------------------------------------------------------------------------
function x310110_OnSetQingLongBattleMatchInfo( sceneId,nGuildA,nGuildB,nCountryId )
    
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return 
    end

    --����Ƿ�������ս�������б���������������������ǣ��򲻴���
    local nScriptId = x310110_GetQingLongBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

	--����д����.�벻Ҫ��
    x310110_g_GuildA[sceneId] = nGuildB 
    x310110_g_GuildB[sceneId] = nGuildA
    x310110_g_CountryID[sceneId] = nCountryId

    --debug
    local a = x310110_g_GuildA[sceneId]
    local b = x310110_g_GuildB[sceneId]
    local c = x310110_g_CountryID[sceneId]

    local msg = format( "QLBL:QINGLONG_BATTLE_MATCHINFO:sceneId=%d,A=%d,B=%d,CountryId=%d", sceneId, a, b,c )
    WriteLog(1,msg)
end

----------------------------------------------------------------------------------------------
--�����������
----------------------------------------------------------------------------------------------
function x310110_OnPlayerNewConnectEnter( sceneId, selfId )
    
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return 
    end

    --����Ƿ�������ս�������б���������������������ǣ��򲻴���
    local nScriptId = x310110_GetQingLongBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    local BattleSceneFlag = GetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG)
    if BattleSceneFlag == 0 then

        --�����ߵ����,����Kick����ʱ��׼���ߵ�
        SetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN,x310110_g_Kick_Down)

        local name = GetName(sceneId,selfId)
        if name == nil then
            name = "ErrorName"
        end
        local msg = format( "QLBL:x310110_OnPlayerNewConnectEnter 0,need kick,sceneId=%d,selfId=%d,name=%s", sceneId, selfId, name )
        WriteLog(1,msg)

    else

        --�ӱ�һ��������ת���������
        --ͬ������������,��ʱ��RD_BATTLESCENE_ENTER_FLAGֵĿǰ�޷���0��
        --ֻ��������뿪ս��������ʱ��������ǲ�ͬ��������Ŀ����������
        local name = GetName(sceneId,selfId)
        if name == nil then
            name = "ErrorName"
        end
        local msg = format( "QLBL:x310110_OnPlayerNewConnectEnter 1,sceneId=%d,selfId=%d,name=%s", sceneId, selfId, name )
        WriteLog(1,msg)

        SetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG,0)

    end
end

----------------------------------------------------------------------------------------------
--�����������
----------------------------------------------------------------------------------------------
function x310110_OnPlayerDie( sceneId, selfId, killerId  )
    
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return 
    end

    --����Ƿ�������ս�������б���������������������ǣ��򲻴���
    local nScriptId = x310110_GetQingLongBattleSceneScript( sceneId )
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

        local str = format("#G%s������ս���б�ɱ��%d�Ρ�",GetName(sceneId,selfId ),nBeKilled )
        LuaThisScenceM2Wrold(sceneId,str,3,1)
        LuaThisScenceM2Wrold(sceneId,str,2,1)
    end

    --�����Σ�����ʾ
    if nBeKilled == 6 then

        local nCountryId = GetCurCountry( sceneId,selfId)

        local str = format("#G%s������ս���У��������������������뿪ս����",GetName(sceneId,selfId ) )
        LuaAllScenceM2Country(sceneId,str,nCountryId,3,1)
        LuaAllScenceM2Country(sceneId,str,nCountryId,2,1)

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
function x310110_CheckPlayerState( sceneId,selfId )
    

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
function x310110_OnQingLongBattleChangeScene( sceneId,selfId,newSceneID,Flag )
    

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
		    SetPos( sceneId , selfId , 47 , 218 )
        else
            SetPos( sceneId , selfId , 209,35 )
        end
	else
        
        --���״̬
        local state,msg = x310110_CheckPlayerState( sceneId,selfId )
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

		NewWorld( sceneId , selfId , newSceneID , PosX , PosZ,310110 )
	end
end

function x310110_DoPlayerRelive( sceneId, selfId )
	
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
function x310110_OnPlayerRelive( sceneId, selfId )

    --����Ƿ�������ս��
    local nScriptId = x310110_GetQingLongBattleSceneScript( sceneId )
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
    local nGuildA = x310110_g_GuildA[sceneId]
    local nGuildB = x310110_g_GuildB[sceneId]

    if nGuildId == nGuildA then

        x310110_OnQingLongBattleChangeScene(sceneId,selfId,sceneId,0)
    else
        x310110_OnQingLongBattleChangeScene(sceneId,selfId,sceneId,1)
    end

end


----------------------------------------------------------------------------------------------
--���쳡����ʼ��
----------------------------------------------------------------------------------------------
function x310110_OnBattleSceneReady( sceneId,totalTime )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --��������س�ʼ��
    x310110_g_CountDownState[sceneId] = -1
    x310110_g_CountDownTime[sceneId] = 10

    --��������ʱ��
    x310110_g_CountTime[sceneId] = totalTime

end

function x310110_OnBattleSceneClose( sceneId )

    if x310110_g_CountDownState[sceneId] == 1 then
        return
    end

    local status = x310110_g_BattleState[sceneId]
	if status == x310110_g_QingLong_EndBattle then
		x310110_BattleGenResult( sceneId,0 )
	end


end

----------------------------------------------------------------------------------------------
--����ս��������
----------------------------------------------------------------------------------------------
function x310110_OnBattleSceneTimer( sceneId,uTime )

    --��ؼ��
    ----------------------------------------------------------------------------------------------
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --�������Kick״̬
    x310110_UpdatePlayerKickState( sceneId )

    local BattleStatus = x310110_g_BattleState[sceneId]
    if BattleStatus ~= x310110_g_QingLong_BeginBattle then
        return
    end

    --��ʱ
    ----------------------------------------------------------------------------------------------
    local nTime = x310110_g_CountTime[sceneId] - 1
    x310110_g_CountTime[sceneId] = nTime

    --����ʱ����
    ----------------------------------------------------------------------------------------------
    if x310110_g_CountDownState[sceneId] == 1 then

	    --����ʱ״̬
	    local time = x310110_g_CountDownTime[sceneId]
	    if time > 0 then

		    x310110_g_CountDownTime[sceneId] = time - 1

		    local str = format("#G����ս������,#R%d��#G��ս���Զ��ر�",time)

		    LuaThisScenceM2Guild(sceneId,str,x310110_g_GuildA[sceneId],3,1)
		    LuaThisScenceM2Guild(sceneId,str,x310110_g_GuildB[sceneId],3,1)

		else

            --�ߵ��������
            x310110_RestoreAllPlayerCamp( sceneId )
	    	x310110_QingLongBattleKickAllPlayer(sceneId)

			--�������
			x310110_g_BattleState[sceneId]				   = -1
			x310110_g_GuildA[sceneId]					   = -1
			x310110_g_GuildB[sceneId]					   = -1
			x310110_g_CountryID[sceneId]					   = -1
			x310110_g_CountDownState[sceneId]			   = -1
			x310110_g_CountDownTime[sceneId]				   = -1
			x310110_g_CountTime[sceneId]				       = -1
            
            --��¼��־
            local msg = format("QLBL:x310110_OnBattleSceneTimer QingLongBattleFinished,SceneId=%d,LeaveTime h= %d,m=%d",sceneId, floor(nTime/60),mod(nTime,60) )
            WriteLog(1,msg)

	    end

	    return

	end

    --����Ƿ����
    ----------------------------------------------------------------------------------------------
    if nTime < 18*60 then
        local bIsFinished = x310110_CheckIsFinished( sceneId)
        if bIsFinished == 1 then
            
            local status = x310110_g_BattleState[sceneId]
            if status == x310110_g_QingLong_BeginBattle then

                x310110_BattleGenResult( sceneId,1 )
                return
            end

        end
    end
	

    --��ʱ��ʱ��ͬ��
    ----------------------------------------------------------------------------------------------
    x310110_SyncGuildPower( sceneId )

    --С��ͼ����ʾ����
    x310110_UpdateSceneDataFlag( sceneId )

end


----------------------------------------------------------------------------------------------
--����Ƿ���Խ���
----------------------------------------------------------------------------------------------
function x310110_CheckIsFinished( sceneId )

    
    --�ռ���Ϣ
    local nGuildA = x310110_g_GuildA[sceneId]
    local nGuildB = x310110_g_GuildB[sceneId]

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
function x310110_GetWinner(sceneId)

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return -1
    end

    --�ռ���Ϣ
    local nGuildA = x310110_g_GuildA[sceneId]
    local nGuildB = x310110_g_GuildB[sceneId]

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
	        if pos == x310110_g_Leader_Index then
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
function x310110_BattleBonus( sceneId,selfId,battleResult )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

end

----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x310110_QingLongBattleBonus( sceneId ,battleResult )

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            x310110_BattleBonus( sceneId,objId,battleResult)
        end
    end
end


----------------------------------------------------------------------------------------------
--�ָ���Ӫ
----------------------------------------------------------------------------------------------
function x310110_RestorePlayerCamp( sceneId,selfId )
    local nCountryId = GetCurCountry( sceneId,selfId )
    SetCurCamp(sceneId,selfId,nCountryId )
end

----------------------------------------------------------------------------------------------
--�ָ���Ӫ
----------------------------------------------------------------------------------------------
function x310110_RestoreAllPlayerCamp( sceneId )

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
function x310110_BattleGenResult( sceneId, callerId  )
    
    local nGuildA = x310110_g_GuildA[sceneId]
    local nGuildB = x310110_g_GuildB[sceneId]

    local nCountryId = x310110_g_CountryID[sceneId]

    if nGuildA == nGuildB then
        return
    end
    
	local strCountryName = GetCountryName(nCountryId)
    local nWinner = x310110_GetWinner( sceneId )
    if nWinner == 0 then
        --��ս����ȡ
        local strGuildName = GetGuildName(nGuildA)
        local strGuildLeaderName = GetGuildLeaderName(nGuildA)
        
        local str = format("#G%s���������ս����ʤ����%s������%s����֮���ı����� ",strGuildName,strGuildLeaderName,strCountryName)
        LuaAllScenceM2Wrold(sceneId, str, 2, 1)
        LuaAllScenceM2Wrold(sceneId, str, 3, 1)
        GameBattleSendResultToGL( 1,1,nCountryId,nGuildB,nGuildA)
    else
        --��������ȡ
        local strGuildName = GetGuildName(nGuildB)
        local strGuildLeaderName = GetGuildLeaderName(nGuildB)
        
        local str = format("#G%s����Ž�һ�µĶ�ס����ս��������%s����֮���ı�����  ",strGuildName,strCountryName)
        local nOfficalGUID = CountryGetOfficerGUID(x310110_g_CountryID[sceneId],0)
        if nOfficalGUID ~= nil and nOfficalGUID > 0 then
        	str = format("#G%s����Ž�һ�µĶ�ס����ս��������%s����֮���ı�����  ",strGuildName,strCountryName )
        end
        
        LuaAllScenceM2Wrold(sceneId, str, 2, 1)
        LuaAllScenceM2Wrold(sceneId, str, 3, 1)
        GameBattleSendResultToGL( 1,0,nCountryId,nGuildB,nGuildA)
    end

    --���뵹��ʱ״̬,�����õ���ʱ��
    x310110_g_CountDownState[sceneId] = 1
    x310110_g_CountDownTime[sceneId] = 10

    local nTime = x310110_g_CountTime[sceneId]
        
    --��¼��־
    local msg = format("QLBL:x310110_BattleGenResult SceneId=%d,LeaveTime h= %d,m=%d,guid=%s,CallerId=%d",sceneId, floor(nTime/60),mod(nTime,60), tostring(CountryGetOfficerGUID(x310110_g_CountryID[sceneId],0)),callerId )
    WriteLog(1,msg)

    x310110_g_GuildA[sceneId] = -1
    x310110_g_GuildB[sceneId] = -1

    x310110_SetAllPlayerNeedKick(sceneId)
    --ClearQingLongBattleSceneData(sceneId)
    
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x310110_QingLongBattleKickPlayer( sceneId,selfId )

    x310110_DoPlayerRelive( sceneId,selfId )

    x310110_RestorePlayerCamp( sceneId,selfId)

    --ֻҪ����뿪ս����������������÷�
    SetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG,0)

    --�������BakScene��Ϣ������BakScene��ϢΪ׼
    local nBakSceneId,x,z = GetPlayerBakSceneInfo(sceneId,selfId )
    if nBakSceneId >= 0 then
        NewWorld(sceneId,selfId,nBakSceneId,x,z,310110)
        return
    end

    --ѡ��һ�����ʵĳ������ͳ�ȥ
    local nCountry = GetCurCountry(sceneId,selfId)
    if nCountry == 0 then
        
        --¥��
        local nDestSceneId = 50
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,310110)

    elseif nCountry == 1 then
        
        --����
        local nDestSceneId = 150
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,310110)

    elseif nCountry == 2 then

        --����
        local nDestSceneId = 250
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,310110)

    elseif nCountry == 3 then
        
        --�ػ�
        local nDestSceneId = 350
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,310110)

    end
end

----------------------------------------------------------------------------------------------
--�ߵ����������е���
----------------------------------------------------------------------------------------------
function x310110_QingLongBattleKickAllPlayer( sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            
            x310110_QingLongBattleKickPlayer( sceneId,objId)

        end
    end
end


----------------------------------------------------------------------------------------------
--ͬ����ս����ʱ��ȫ����ң���ǰ������
----------------------------------------------------------------------------------------------
function x310110_SyncBattleTimeToAllPlayer( sceneId ,nTime )

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
function x310110_SyncBattleTimeCloseToAllPlayer(sceneId )
    
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
function x310110_SyncGuildPower( sceneId )
    
    local nGuildA = x310110_g_GuildA[sceneId]
    local nGuildB = x310110_g_GuildB[sceneId]

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
            GameBattleSyncPowerInfo(sceneId,objId,nGuildA_Count,nGuildB_Count,1)
        end
    end

end

----------------------------------------------------------------------------------------------
--����С��ͼ
----------------------------------------------------------------------------------------------
function x310110_UpdateSceneDataFlag( sceneId )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    ClearSceneMapDataFlag( sceneId )

	SetSceneMapDataFlag( sceneId,10,8,"���뷽������",40,217,-1)
	SetSceneMapDataFlag( sceneId,11,8,"������������",217,37,-1)

    --���°�����λ��
    local GuildLeaderA = -1
    local GuildLeaderB = -1
    
    local nGuildA = x310110_g_GuildA[sceneId]
    local nGuildB = x310110_g_GuildB[sceneId]

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            
            local pos = GetGuildOfficial(sceneId, objId)
	        if pos == x310110_g_Leader_Index then
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
--��GLServer������ͬ������ս��ʱ��Ķ���
----------------------------------------------------------------------------------------------
function x310110_OnSyncQingLongBattleTime( sceneId,nTime )
    
    if x310110_GetQingLongBattleSceneScript( sceneId ) == 0 then
        return
    end

    local nTime_new = x310110_g_TotalBattleTime - NumberCastIntToUInt( nTime )
    x310110_g_CountTime[sceneId] = nTime_new

    --��ʱ��ʱ��ͬ��
    ----------------------------------------------------------------------------------------------
    x310110_SyncBattleTimeToAllPlayer( sceneId, nTime_new )
end

----------------------------------------------------------------------------------------------
--�������������Ҫ�ߵ�
----------------------------------------------------------------------------------------------
function x310110_SetAllPlayerNeedKick( sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local KickDown = GetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ) 
            if KickDown <= 0 or KickDown > x310110_g_Kick_Down then                
                SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,x310110_g_Kick_Down) 
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--��������ߵ�״̬
----------------------------------------------------------------------------------------------
function x310110_UpdatePlayerKickState( sceneId )
    
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
                    x310110_QingLongBattleKickPlayer( sceneId,objId )                    
                else
                    --���򣬼�������ʱ
                    SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,KickDown) 
                end
            end
        end
    end
end
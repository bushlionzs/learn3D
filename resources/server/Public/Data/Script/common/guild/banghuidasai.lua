
x300643_g_ScriptId                      = 300643
x300643_g_TotalBattleTime               = 60 * 20     	--ս������ʱ��1200��        19:00-19:20

--�淨����
x300643_g_SceneName                     = "zhanchang_banghuizhanchang/zhanchang_banghuizhanchang.scn"
x300643_g_MatchOdd                      = "#R�����ڵİ���ڱ��ΰ��ս���ֿգ�"

x300643_g_Guild_Signup                  = 3     --����
x300643_g_Guild_WaitBattle              = 4     --�����������ȴ���ս
x300643_g_Guild_BeginBattle             = 5     --��ʼ��ս
x300643_g_Guild_EndBattle               = 6     --������ս

--�������
x300643_g_MaxScore                      = 99	            
x300643_g_BonusTips                     = "#G�������#R%d#G�㾭��,#R%d#G���ṱ��,#R%d#G���ᾭ��,#R%d#G����ʹ����,#R%d#G������Ǯ!"
x300643_g_BonusTips1                    = "������˽���"

--���齱��
x300643_g_WinPrise                      = 1000*0.5*20              --��ʤ�����齱��ϵ����ֻ��ȼ��й�
x300643_g_LosePrise                     = 1000*0.1*20              --ʧ�ܷ����齱��ϵ����ֻ��ȼ��й�
x300643_g_DeucePrise                    = 1000*0.3*20              --սƽʱ���齱��ϵ����ֻ��ȼ��й�

--�ﹱ����
x300643_g_WinBangGong                   = 150
x300643_g_LoseBangGong                  = 50
x300643_g_DeuceBangGong                 = 100

--��ᾭ��
x300643_g_WinBangExp                    = 5
x300643_g_LoseBangExp                   = 5
x300643_g_DeuceBangExp                  = 5

--���ʹ����
x300643_g_WinBangshiming                = 2
x300643_g_LoseBangshiming               = 2
x300643_g_DeuceBangshiming              = 2

--����Ǯ
x300643_g_WinBangjinqian                = 40000
x300643_g_LoseBangjinqian               = 20000
x300643_g_DeuceBangjinqian              = 20000

--��Ṧ��
x300643_g_WinBanggongde                 = 20
x300643_g_LoseBanggongde                = 15
x300643_g_DeuceBanggongde               = 10

--���ս��˫����Ӫ
x300643_g_Guild_Camp_A                  = 5
x300643_g_Guild_Camp_B                  = 6

x300643_g_Kick_Down                     = 8

--��Ụ����������Ϣ
x300643_g_ConvoyGrowPointState			= {}
x300643_g_ConvoyGrowPointType			= {}
x300643_g_ConvoyGrowPointPosList		= {{40,125},{30,39},{33,219},{93,46},{93,214},{125,98},{125,150},{161,44},{161,219},{213,218},{216,40},{205,122}}

--�ڲ��������
x300643_g_ScoreIntervalA				= {}
x300643_g_ScoreIntervalB				= {}

x300643_g_BattleFlagA    				= {type=9771, x=202, z=122.6, ai=7, guid=150031, facedir=0, title=""}		--ս��A
x300643_g_BattleFlagB    				= {type=9770, x=48,  z=127.1, ai=7, guid=150030, facedir=0, title=""}		--ս��B


function x300643_ProcEventEntry(sceneId, selfId, NPCId, scriptid, index)	--����������ִ�д˽ű�
end

----------------------------------------------------------------------------------------------
--�ೡ������
----------------------------------------------------------------------------------------------
function x300643_OnMapInit(sceneId)
	
	x300643_g_ConvoyGrowPointState[sceneId]			= 0
	x300643_g_ConvoyGrowPointType[sceneId]			= 114
	

	--�ڲ��������
	x300643_g_ScoreIntervalA[sceneId]				= 0
	x300643_g_ScoreIntervalB[sceneId]				= 0
	
end

----------------------------------------------------------------------------------------------
--����Ƿ��ǰ�ս������������Ƿ���0���Ƿ���1
----------------------------------------------------------------------------------------------
function x300643_IsGuildBattleScene_Gjs( sceneId )

    local name = GetBattleSceneName(sceneId)
    if name == x300643_g_SceneName then
        return 1
    end

    return 0
end


----------------------------------------------------------------------------------------------
--�����
----------------------------------------------------------------------------------------------
function x300643_OnBattleStateEvent( sceneId, state  )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_GUILDBATTLE ) == 0 then
        return
    end

	local sceneType = GetSceneType(sceneId);
	if sceneType == 0 then --������������ͨ����

        if state == x300643_g_Guild_Signup then

            --���״̬�Ƿ��Ѿ��ù�
            local selfStatus = GetGuildBattleStatus(sceneId)
            if selfStatus ~= STATE_GUILD_BATTLE_SIGNUP then
                
                --��¼��־
                local msg = format("GBL:STATE_GUILD_BATTLE_SIGNUP,SceneId=%d ",sceneId  )
                WriteLog(1,msg)

            end
            
            --��ʼ����
            SetGuildBattleStatus(sceneId,STATE_GUILD_BATTLE_SIGNUP)
            
        elseif state == x300643_g_Guild_WaitBattle then

            --���״̬�Ƿ��Ѿ��ù�
            local selfStatus = GetGuildBattleStatus(sceneId)
            if selfStatus ~= STATE_GUILD_BATTLE_SIGNUP_FINISH then
                
                --��¼��־
                local msg = format("GBL:STATE_GUILD_BATTLE_SIGNUP_FINISH,SceneId=%d ",sceneId )
                WriteLog(1,msg)

            end
            
            --��������
            SetGuildBattleStatus(sceneId,STATE_GUILD_BATTLE_SIGNUP_FINISH)
            
        elseif state == x300643_g_Guild_BeginBattle then

            --���״̬�Ƿ��Ѿ��ù�
            local selfStatus = GetGuildBattleStatus(sceneId)
            if selfStatus == STATE_GUILD_BATTLE_BATTLE then
                
                --��¼��־
                local msg = format("GBL:STATE_GUILD_BATTLE_BATTLE,SceneId=%d ",sceneId )
                WriteLog(1,msg)

            end
            
            --��ʼ��ս
		    SetGuildBattleStatus(sceneId,STATE_GUILD_BATTLE_BATTLE)

        elseif state == x300643_g_Guild_EndBattle then
            
            --��ս����
            SetGuildBattleStatus(sceneId,STATE_GUILD_BATTLE_BATTLE_FINISH)

            --��¼��־
            local msg = format("GBL:STATE_GUILD_BATTLE_BATTLE_FINISH, SceneId=%d",sceneId )
            WriteLog(1,msg)

        end

	elseif sceneType == 2 then --���������ǰ��ս����
        
        --����Ƿ��ǰ�ս�����б���������������������ǣ��򲻴���
        local bBattleScene_Gjs = x300643_IsGuildBattleScene_Gjs( sceneId )
        if  bBattleScene_Gjs == 0 then
            return
        end

        if state == x300643_g_Guild_Signup then

            --���״̬�Ƿ��Ѿ��ù�
            local selfStatus = GetGuildBattleStatus(sceneId)
            if selfStatus ~= STATE_GUILD_BATTLE_READY then
                
                --��¼��־
                local msg = format("GBL:STATE_GUILD_BATTLE_SIGNUP,SceneId=%d,2 ",sceneId  )
                WriteLog(1,msg)

            end

            GuildBattleAskInit( sceneId )                                               --��GLServerע��һ��
            SetGuildBattleStatus(sceneId,STATE_GUILD_BATTLE_READY)                      --����״̬


            --���û�������
            SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_SCRIPT,GUILDBATTLE_SCRIPTID)

        elseif state == x300643_g_Guild_WaitBattle then

            --���״̬�Ƿ��Ѿ��ù�
            local selfStatus = GetGuildBattleStatus(sceneId)
            if selfStatus ~= STATE_GUILD_BATTLE_SIGNUP_FINISH then
                
                --��¼��־
                local msg = format("GBL:STATE_GUILD_BATTLE_SIGNUP_FINISH,SceneId=%d,2",sceneId )
                WriteLog(1,msg)

            end

            --���û�������
            SetGuildBattleStatus(sceneId,STATE_GUILD_BATTLE_SIGNUP_FINISH)
            SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_SCRIPT,GUILDBATTLE_SCRIPTID)

        elseif state == x300643_g_Guild_BeginBattle then

            --���״̬�Ƿ��Ѿ��ù�
            local selfStatus = GetGuildBattleStatus(sceneId)
            if selfStatus ~= STATE_GUILD_BATTLE_BATTLE then
                
                --��¼��־
                local msg = format("GBL:STATE_GUILD_BATTLE_BATTLE,SceneId=%d,2",sceneId )
                WriteLog(1,msg)

            end

            --���û�������            
            SetGuildBattleStatus(sceneId,STATE_GUILD_BATTLE_BATTLE)                     --���ÿ�ʼ��ս
            SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_SCRIPT,GUILDBATTLE_SCRIPTID)

            x300643_OnBattleSceneReady( sceneId,( x300643_g_TotalBattleTime ) )

        elseif state == x300643_g_Guild_EndBattle then

            local nState = GetGuildBattleStatus( sceneId )
            if nState > STATE_GUILD_BATTLE_BATTLE or nState < STATE_GUILD_BATTLE_READY then
                
                --��¼��־
                local msg = format("GBL:STATE_GUILD_BATTLE_BATTLE_FINISH,Result:nState > STATE_GUILD_BATTLE_BATTLE or nState < STATE_GUILD_BATTLE_READY  SceneId=%d,state=%d,2",sceneId, nState )
                WriteLog(1,msg)

                --�����淨�Ľű��Ĳ�ͬ��������س�ʼ���ص�
                x300643_OnBattleSceneClose(sceneId )

                --��¼��־
                local msg = format("GBL:STATE_GUILD_BATTLE_BATTLE_FINISH, SceneId=%d,2",sceneId )
                WriteLog(1,msg)
                return
            end

            --����״̬�������
    		SetGuildBattleStatus(sceneId,STATE_GUILD_BATTLE_BATTLE_FINISH)
            x300643_OnBattleSceneClose( sceneId )

            --��¼��־
            local msg = format("GBL:STATE_GUILD_BATTLE_BATTLE_FINISH, SceneId=%d,2",sceneId )
            WriteLog(1,msg)
        end
	end
end

----------------------------------------------------------------------------------------------
--���ս������
----------------------------------------------------------------------------------------------
function x300643_ProcTiming( sceneId,uTime )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --����Ƿ��ǰ�ս�����б���������������������ǣ��򲻴���
    local bBattleScene_Gjs = x300643_IsGuildBattleScene_Gjs( sceneId )
    if  bBattleScene_Gjs == 0 then
        return
    end
       
    x300643_OnBattleSceneTimer( sceneId, uTime )
end


----------------------------------------------------------------------------------------------
--��ҽ����¼�
----------------------------------------------------------------------------------------------
function x300643_OnPlayerEnter( sceneId, playerId )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --����Ƿ��ǰ�ս�����б���������������������ǣ��򲻴���
    local bBattleScene_Gjs = x300643_IsGuildBattleScene_Gjs( sceneId )
    if  bBattleScene_Gjs == 0 then
        return
    end

    local status = GetGuildBattleStatus( sceneId )
    if status ~= STATE_GUILD_BATTLE_BATTLE then

        x300643_SetAllPlayerNeedKick( sceneId,x300643_g_Kick_Down )
        --��¼��־
        local msg = format("GBL:x300643_OnBattlePlayerEnter Kick,Player,SceneId=%d,playerId=%d status=%d",sceneId,playerId,status )
        WriteLog(1,msg)
        return
    end

    --ȡ�ð��A�Ͱ��B
    local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
    local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

    local nGuildId = GetGuildID( sceneId,playerId )

    --������ս���е���Ӫ����
    local nSendCCamp = -1
    if nGuildId == nGuildA then
        nSendCCamp = 0
    elseif nGuildId == nGuildB then
        nSendCCamp = 1
    else

        SetPlayerRuntimeData( sceneId,playerId,RD_BATTLE_SCENE_KICK_DOWN ,x300643_g_Kick_Down) 
        --��¼��־
        local name = GetName(sceneId,playerId)
        if name == nil then
            name = "<ErrorName>"
        end
        local msg = format("GBL:x300643_OnBattlePlayerEnter Kick 2,Player,SceneId=%d,playerId=%d,name=%s,guild=%d,guildA=%d,guildB=%d",sceneId, playerId,name, nGuildId, nGuildA, nGuildB )
        WriteLog(1,msg)
        return

    end

    SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_REFRESH_MAP,1)

    --�������趨
    SetGuildBattleDisable(sceneId, playerId, 0,nSendCCamp )
    
    --���Ͱ�ս�����Ϣ
    local strGuildA_name = GetGuildName(nGuildA)
    local strGuildB_name = GetGuildName(nGuildB)
    SendGuildBattleMatchInfo(sceneId,playerId,strGuildA_name,strGuildB_name)

    --��ҽ���ս���������֮ǰ������
    SetPlayerRuntimeData(sceneId,playerId,RD_GUILDBATTLE_BEKILLED,0)
    SetPlayerRuntimeData(sceneId,playerId,RD_GUILDBATTLE_KILLEDOTHER,0)
    SetPlayerRuntimeData(sceneId,playerId,RD_GUILDBATTLE_GETFLAG,0)

    --������Ӫ
    if nGuildId == nGuildA then
        SetCurCamp(sceneId,playerId,x300643_g_Guild_Camp_A)
        SetPos(sceneId,playerId,234,126)
    elseif nGuildId == nGuildB then
        SetCurCamp(sceneId,playerId,x300643_g_Guild_Camp_B)
        SetPos(sceneId,playerId,21,126)
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
function x300643_OnPlayerLeave( sceneId, playerId )
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --����Ƿ��ǰ�ս�����б���������������������ǣ��򲻴���
    local bBattleScene_Gjs = x300643_IsGuildBattleScene_Gjs( sceneId )
    if  bBattleScene_Gjs == 0 then
        return
    end

    local nCountryId = GetCurCountry(sceneId,playerId )
    SetCurCamp( sceneId,playerId,nCountryId )

    SetGuildBattleDisable(sceneId, playerId,1,0)

    --����Ƕ�����ң�ɾ������BUF,����������
    local owner = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_OWNER)
    if owner == playerId then
        CancelSpecificImpact(sceneId,owner,LD_GUILD_BATTLE_DEC_SPEED_BUF )
        CancelSpecificImpact(sceneId,owner,LD_GUILD_BATTLE_INC_DEFENCE_BUF )
        --CancelSpecificImpact(sceneId,owner,LD_GUILD_BATTLE_FLAG_BUF )
        SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_OWNER,-1 )

        local x,y = GetWorldPos(sceneId, playerId)
        --����������������
        SetGrowPointPos(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,x,y)
        --������������ʱ��
        SetGrowPointIntervalContainer(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,1)
    end
end

----------------------------------------------------------------------------------------------
--����˻�
----------------------------------------------------------------------------------------------
function x300643_OnPlayerLeaveGuild( sceneId,selfId )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --����Ƿ��ǰ�ս�����б���������������������ǣ��򲻴���
    local bBattleScene_Gjs = x300643_IsGuildBattleScene_Gjs( sceneId )
    if  bBattleScene_Gjs == 0 then
        return
    end
    
    --����Ƕ�����ң�ɾ������BUF,����������
    local owner = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_OWNER)
    if owner == selfId then
        CancelSpecificImpact(sceneId,owner,LD_GUILD_BATTLE_DEC_SPEED_BUF )
        CancelSpecificImpact(sceneId,owner,LD_GUILD_BATTLE_INC_DEFENCE_BUF )
        SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_OWNER,-1 )

        local x,y = GetWorldPos(sceneId, selfId)
        --����������������
        SetGrowPointPos(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,x,y)
        --������������ʱ��
        SetGrowPointIntervalContainer(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,1)
    end
    
    x300643_GuildBattleKickPlayer( sceneId,selfId )
    SetGuildBattleDisable(sceneId, selfId,1,0)

end

----------------------------------------------------------------------------------------------
--��������¼�
----------------------------------------------------------------------------------------------
function x300643_OnPlayerDie( sceneId, selfId, killerId  )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --����Ƿ��ǰ�ս�����б���������������������ǣ��򲻴���
    local bBattleScene_Gjs = x300643_IsGuildBattleScene_Gjs( sceneId )
    if  bBattleScene_Gjs == 0 then
        return
    end

    local IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId,LD_GUILD_BATTLE_DEC_SPEED_BUF )
    if IsHaveFlag ~= 0 then

        --���������������
        SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_OWNER,-1 )
        CancelSpecificImpact(sceneId,selfId,LD_GUILD_BATTLE_DEC_SPEED_BUF )
        CancelSpecificImpact(sceneId,selfId,LD_GUILD_BATTLE_INC_DEFENCE_BUF )

        local ObjType = GetObjType(sceneId, killerId)

        --ɱ�������߲��������,����û������,������30����,����Ϊ��Ч,���������
        if IsPlayerStateNormal( sceneId,killerId ) == 1 and IsPlayerMutexState(sceneId,killerId,PLAYER_STATE_DIE) ~= 1 and GetDist(sceneId,selfId,killerId,30) <= 30  then
            SendSpecificImpactToUnit(sceneId, killerId,killerId,killerId,LD_GUILD_BATTLE_DEC_SPEED_BUF,0)
            SendSpecificImpactToUnit(sceneId, killerId,killerId,killerId,LD_GUILD_BATTLE_INC_DEFENCE_BUF,0)

            SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_OWNER,killerId )  --��¼��������
            ReCallHorse( sceneId, killerId )--ǿ������

            local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
            local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

            local nGuildId = GetGuildID( sceneId,killerId )

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
        
        --ɱ���߲����߻������������߷����
        else

            local x,y = GetWorldPos( sceneId, selfId )
            SetGrowPointPos( sceneId, LD_GUILD_BATTLE_FLAG_GROW_POINT, x+1, y+1)
            SetGrowPointIntervalContainer( sceneId, LD_GUILD_BATTLE_FLAG_GROW_POINT, 1000 )
            SetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_FLAG_OWNER, -1 )

            x300643_UpdateSceneDataFlag( sceneId, 7 )
        end
    end

   --��¼ɱ�д���
   local nKilledOther = GetPlayerRuntimeData( sceneId, killerId, RD_GUILDBATTLE_KILLEDOTHER ) + 1
   SetPlayerRuntimeData( sceneId, killerId, RD_GUILDBATTLE_KILLEDOTHER, nKilledOther )

   --��¼��ɱ����
   local nBeKilled = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_BEKILLED ) + 1
   SetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_BEKILLED,nBeKilled)

end


----------------------------------------------------------------------------------------------
--���ս�������
----------------------------------------------------------------------------------------------
function x300643_OnPlayerRelive( sceneId, selfId )

    --����Ƿ��ǰ��ս
    local bBattleScene = x300643_IsGuildBattleScene_Gjs( sceneId )
    if bBattleScene == 0 then
        return
    end
    
    --�������ڰ�սδ��ʼ���ǰ�ս����ʱ��Ϊĳ��ԭ����������ô�����临���������
    local status = GetGuildBattleStatus( sceneId )
	if status ~= STATE_GUILD_BATTLE_BATTLE then
        
        local KickDown = GetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ) 
        if KickDown <= 0 or KickDown > 8 then                
            SetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ,8 ) 
        end
        
        return
    end

    --�õ������������A��B��
    local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
    local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

    local nGuildId = GetGuildID( sceneId,selfId )

    --������ս���е���Ӫ����
    local flag = -1
    if nGuildId == nGuildA then
        flag = 0
    elseif nGuildId == nGuildB then
        flag = 1
    end
    
    --��������ű��ӿ�ʵ�ִ���
    CallScriptFunction(800021,"OnGuildBattleChangeScene",sceneId,selfId,sceneId,flag)

end

----------------------------------------------------------------------------------------------
--���ʧ�ܵĲ���
----------------------------------------------------------------------------------------------
function x300643_OnGuildBattleMatchOdd( sceneId, playerId )

    local name = GetName(sceneId,playerId)
    LuaScenceM2Player(sceneId,  playerId, x300643_g_MatchOdd, name , 2,1)
    LuaScenceM2Player(sceneId,  playerId, x300643_g_MatchOdd, name , 3,1)
end

----------------------------------------------------------------------------------------------
--������صĴ���
----------------------------------------------------------------------------------------------
function x300643_OnRideHorse( sceneId,selfId )
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return 1
    end

    --����Ƿ��ǰ�ս�����б���������������������ǣ��򲻴���
    local bBattleScene_Gjs = x300643_IsGuildBattleScene_Gjs( sceneId )
    if  bBattleScene_Gjs == 0 then
        return 1
    end

    --���첻������
    local IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId,LD_GUILD_BATTLE_DEC_SPEED_BUF )
    if IsHaveFlag ~= 0 then
        return 0
    end

    --���죬������
    return 1
end

----------------------------------------------------------------------------------------------
--���ð�ս��������Ϣ
----------------------------------------------------------------------------------------------
function x300643_OnSetGuildBattleMatchInfo( sceneId,nGuildA,nGuildB )
    
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return 
    end

    --����Ƿ��ǰ�ս�����б���������������������ǣ��򲻴���
    local bBattleScene_Gjs = x300643_IsGuildBattleScene_Gjs( sceneId )
    if  bBattleScene_Gjs == 0 then
        return
    end

    SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_GUILD, nGuildA )
    SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_GUILD, nGuildB )

    --debug
    local a = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_GUILD )
    local b = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_GUILD )

    local msg = format( "GBL:GUILD_BATTLE_MATCHINFO:sceneId=%d,A=%d,B=%d",sceneId,a,b )
    WriteLog(1,msg)
end

----------------------------------------------------------------------------------------------
--�����������
----------------------------------------------------------------------------------------------
function x300643_OnPlayerNewConnectEnter( sceneId,selfId )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return 
    end

    --����Ƿ��ǰ�ս�����б���������������������ǣ��򲻴���
    local bBattleScene_Gjs = x300643_IsGuildBattleScene_Gjs( sceneId )
    if  bBattleScene_Gjs == 0 then
        return
    end

    AskGuildBattleEnter(sceneId,selfId)

end

function x300643_OnPlayerAskLeave( sceneId,selfId )
    
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return 
    end

    --����Ƿ��ǰ�ս�����б���������������������ǣ��򲻴���
    local bBattleScene_Gjs = x300643_IsGuildBattleScene_Gjs( sceneId )
    if  bBattleScene_Gjs == 0 then
        return
    end

    x300643_OnPlayerAskLeaveGuildBattle( sceneId, selfId )

end

function x300643_OnDie(sceneId, selfId, killerId)
	if selfId == GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_A_ID) then
	
		SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_SOCRE,200)
    	SetGuildBattleStatus(sceneId,STATE_GUILD_BATTLE_BATTLE_FINISH)
        x300643_OnBattleSceneClose( sceneId )
        local msg = format("GBL:FLAG A DIE, STATE_GUILD_BATTLE_BATTLE_FINISH, SceneId=%d,2",sceneId )
        WriteLog(1,msg)
	elseif selfId == GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_B_ID) then
		SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_SOCRE,200)
		SetGuildBattleStatus(sceneId,STATE_GUILD_BATTLE_BATTLE_FINISH)
        x300643_OnBattleSceneClose( sceneId )
     
        local msg = format("GBL:FLAG B DIE, STATE_GUILD_BATTLE_BATTLE_FINISH, SceneId=%d,2",sceneId )
        WriteLog(1,msg)
	end
end
--����ս��
function x300643_CreateBattleFlags( sceneId )

	local FlagAID,FlagBID
 	if x300643_g_BattleFlagA.title~="" then
		FlagAID = CreateMonster(sceneId, x300643_g_BattleFlagA.type, x300643_g_BattleFlagA.x, x300643_g_BattleFlagA.z, x300643_g_BattleFlagA.ai, 0, x300643_g_ScriptId, x300643_g_BattleFlagA.guid, x300643_g_Guild_Camp_A,-1,x300643_g_BattleFlagA.facedir,  "", x300643_g_BattleFlagA.title)
		
	else
		FlagAID = CreateMonster(sceneId, x300643_g_BattleFlagA.type, x300643_g_BattleFlagA.x, x300643_g_BattleFlagA.z, x300643_g_BattleFlagA.ai, 0, x300643_g_ScriptId, x300643_g_BattleFlagA.guid, x300643_g_Guild_Camp_A,-1,x300643_g_BattleFlagA.facedir)
	end
	SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_A_ID, FlagAID)
	if x300643_g_BattleFlagB.title~="" then
		FlagBID = CreateMonster(sceneId, x300643_g_BattleFlagB.type, x300643_g_BattleFlagB.x, x300643_g_BattleFlagB.z, x300643_g_BattleFlagB.ai, 0, x300643_g_ScriptId, x300643_g_BattleFlagB.guid, x300643_g_Guild_Camp_B,-1,x300643_g_BattleFlagB.facedir,  "", x300643_g_BattleFlagB.title)
	else
		FlagBID = CreateMonster(sceneId, x300643_g_BattleFlagB.type, x300643_g_BattleFlagB.x, x300643_g_BattleFlagB.z, x300643_g_BattleFlagB.ai, 0, x300643_g_ScriptId, x300643_g_BattleFlagB.guid, x300643_g_Guild_Camp_B,-1,x300643_g_BattleFlagB.facedir)
	end
	SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_B_ID, FlagBID)
	
end

--ɾ������
function x300643_DestroyBattleFlags( sceneId )
	
	local FlagAID = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_A_ID)
	local FlagBID = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_B_ID)
	
	if IsObjValid(sceneId,FlagAID) == 1 and GetHp(sceneId,FlagAID) > 0 then
		DeleteMonster(sceneId,FlagAID)
	end
	
	if IsObjValid(sceneId,FlagBID) == 1 and GetHp(sceneId,FlagBID) > 0 then
		DeleteMonster(sceneId,FlagBID)
	end
	
end

function x300643_OnBattleSceneReady( sceneId,totalTime )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --��������س�ʼ��
    SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN1_GUILD,-1)
    SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN2_GUILD,-1)
    SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN3_GUILD,-1)
    SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN4_GUILD,-1)
    SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_OWNER,-1)

    SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_COUNT_DOWN_STATE,-1 )
    SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_COUNT_DOWN_TIME,10 )

    --�����������
    SetGrowPointIntervalContainer(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,1)

    RecycleGrowPointByType( sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,2000)
    SetGrowPointPos(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,LD_GUILD_BATTLE_FLAG_X,LD_GUILD_BATTLE_FLAG_Y)

    --�ֿ��λ��һ���̶�
    SetSceneMapDataFlag( sceneId,5,1,"�ֿ�",219,122.6,-1)
    SetSceneMapDataFlag( sceneId,6,2,"�ֿ�",34, 127.1,-1)

    --����ˢ�µ�ͼ
    SetGuildBattleSceneData_Param(sceneId, LD_GUILD_BATTLE_REFRESH_MAP,1)

    --��������ʱ��
    --SetGuildBattleSceneData_Timer( sceneId,1000 )
    SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_TIME,-1 )

    SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_COUNT_ITME,totalTime )
    
    --����������
    x300643_g_ConvoyGrowPointState[sceneId] = 0
    x300643_ResetConvoyGrowPoint(sceneId,0)
    
    --�����ڲ�����
    x300643_g_ScoreIntervalA[sceneId] = 0
	x300643_g_ScoreIntervalB[sceneId] = 0
	
	--����˫��ս��
	x300643_CreateBattleFlags(sceneId)
end

function x300643_OnBattleSceneClose( sceneId )

    if GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_COUNT_DOWN_STATE) == 1 then
        return
    end

    local status = GetGuildBattleStatus( sceneId )
	if status == STATE_GUILD_BATTLE_BATTLE_FINISH then
		x300643_BattleGenResult( sceneId,0 )
        SendGuildBattleFinishedToGL( sceneId )
	end
end

function x300643_GetBattleState( sceneId )
    
    local down_state = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_COUNT_DOWN_STATE)
    local down_time  = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_COUNT_DOWN_TIME)

    if down_state == -1  and down_time <= 0 then
        return 0
    end

    return 1

end

function x300643_GetBattleDownState( sceneId )
    
    local down_state = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_COUNT_DOWN_STATE)

    if down_state == 1 then
        return 0
    end

    return 1

end

function x300643_CheckBattleState( sceneId )
    
    if x300643_GetBattleState(sceneId) == 0 then
        return 0
    end

    if x300643_GetBattleDownState(sceneId) == 0 then
        return 0
    end

    return 1

end

----------------------------------------------------------------------------------------------
--���ս������
----------------------------------------------------------------------------------------------
function x300643_OnBattleSceneTimer( sceneId,uTime )

    --��ؼ��
    ----------------------------------------------------------------------------------------------
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    x300643_UpdatePlayerKickState( sceneId )


    local status = GetGuildBattleStatus( sceneId )
	if status ~= STATE_GUILD_BATTLE_BATTLE then
        return
    end
    
    
    if x300643_g_ConvoyGrowPointState[sceneId] == 0 then
    	
		x300643_ResetConvoyGrowPoint(sceneId,1)    	
		x300643_g_ConvoyGrowPointState[sceneId] = 1
    end


    --��ʱ
    ----------------------------------------------------------------------------------------------
    local nTime = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_COUNT_ITME ) - 1
    SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_COUNT_ITME,nTime )

    --����ʱ����
    ----------------------------------------------------------------------------------------------
    if GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_COUNT_DOWN_STATE) == 1 then

	    --����ʱ״̬
	    local time = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_COUNT_DOWN_TIME)
	    if time > 0 then

		    SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_COUNT_DOWN_TIME,time-1 )

		else

		    --����ʱ����
	    	SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_COUNT_DOWN_STATE,-1 )
            
            --�ߵ��������
            x300643_RestoreAllPlayerCamp( sceneId )
	    	x300643_GuildBattleKickAllPlayer(sceneId)

		 	--ֹͣ����
			--SetGuildBattleSceneData_Timer(sceneId,0)
			ClearGuildBattleSceneData(sceneId)
            
            --��¼��־
            local msg = format("GBL:x300643_OnBattleSceneTimer GuildBattleFinished,SceneId=%d,LeaveTime m= %d,s=%d",sceneId, floor(nTime/60),mod(nTime,60) )
            WriteLog(1,msg)

	    end

	    return

	end

    --��ս���ܼ�����ʱ��ֹͣ
    if x300643_GetBattleState( sceneId) == 0 then
        return
    end

    --����Ƿ����
    ----------------------------------------------------------------------------------------------
	local status = GetGuildBattleStatus( sceneId )
	if status == STATE_GUILD_BATTLE_BATTLE_FINISH then

		x300643_BattleGenResult( sceneId,1 )
        SendGuildBattleFinishedToGL( sceneId )
        -- ������ս����������ӻ�Ծ��
        x300643_AddActivity( sceneId)
		return
	end

    --ˢ��С��ͼ
    ----------------------------------------------------------------------------------------------
    local nRefresh =  GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_REFRESH_MAP)
    if nRefresh == 1 then

        SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_REFRESH_MAP,0)
        
        for i=1,13 do
        	x300643_UpdateSceneDataFlag( sceneId,i )
        end

    end

    --��������������ϣ�ÿ��ˢ��һ��
    ----------------------------------------------------------------------------------------------
    local owner = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_OWNER)
    if owner ~= -1 then
        x300643_UpdateSceneDataFlag( sceneId,7 )
    end


    --���ּƷִ���
    ----------------------------------------------------------------------------------------------
    x300643_UpdateBarnScore(sceneId,0)	 --����1�Զ��ӷ�
    x300643_UpdateBarnScore(sceneId,1)	 --����2�Զ��ӷ�
    x300643_UpdateBarnScore(sceneId,2)	 --����3�Զ��ӷ�
    x300643_UpdateBarnScore(sceneId,3)	 --����4�Զ��ӷ�

    --�㲥���»���
    ----------------------------------------------------------------------------------------------
    local FlagNumA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_FLAG_NUM)
    local FlagNumB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_FLAG_NUM)

    BroadcastGuildBattleScore(sceneId, 0,GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_SOCRE)+1,FlagNumA+1 )
    BroadcastGuildBattleScore(sceneId, 1,GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_SOCRE)+1,FlagNumB+1 )

    --������ظ���
    ----------------------------------------------------------------------------------------------
    local FlagTime = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_TIME)

    if FlagTime > 0 then

        SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_TIME,FlagTime-1 )     --����������Чʱ��
        FlagTime = FlagTime - 1
        if FlagTime <= 0 then       --ʱ�䵽�����Զ���ʧ

            --ɾ��������BUF
            CancelSpecificImpact(sceneId,owner,LD_GUILD_BATTLE_DEC_SPEED_BUF )
            CancelSpecificImpact(sceneId,owner,LD_GUILD_BATTLE_INC_DEFENCE_BUF )
            --CancelSpecificImpact(sceneId,owner,LD_GUILD_BATTLE_FLAG_BUF )

            SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_TIME,-1 )
            SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_OWNER,-1 )

            --����������
            RecycleGrowPointByType( sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,2000)
            SetGrowPointPos(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,LD_GUILD_BATTLE_FLAG_X,LD_GUILD_BATTLE_FLAG_Y)

            --��������λ��������ʱ��
            --SetGrowPointIntervalContainer(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,1)

            x300643_UpdateSceneDataFlag( sceneId,7 )

        end
    end

    --�ж϶��������������ս�ǻ���ǰ����
    ----------------------------------------------------------------------------------------------
    local IsFinished = 0

    local ScoreA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_SOCRE)
    local ScoreB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_SOCRE)

    if ScoreA >= x300643_g_MaxScore  or ScoreB>=x300643_g_MaxScore  then

        --���ս��ǰ����
        IsFinished = 1

    end

    if IsFinished == 1 then

        x300643_BattleGenResult( sceneId,2 )
        SendGuildBattleFinishedToGL( sceneId )
        return
    end
    
    
    --ͬ��˫��������Ϣ
    ----------------------------------------------------------------------------------------------
    x300643_SyncGuildPower(sceneId )

end

-- ������ս����������ӻ�Ծ��
function x300643_AddActivity( sceneId)
    local nHumanCount = GetScenePlayerCount( sceneId)
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId, i)
        if objId >= 0 then
            -- ���ӻ�Ծ��
            local id = GetGuildID( sceneId, objId)
            if id ~= -1 then
                AddGuildActivity( sceneId, objId, GetGuildCacheFreeParam( id, GD_GUILD_ACTIVITY_PARAM8) )
            end
        end
    end
end


----------------------------------------------------------------------------------------------
--�õ���ʤ����0ΪA����ʤ��1ΪB����ʤ��-1Ϊƽ��
----------------------------------------------------------------------------------------------
function x300643_GetWinner(sceneId)

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return -1
    end

    --�����û���õ��������ӣ�������û���˵�50��
    local ScoreA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_SOCRE)
    local ScoreB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_SOCRE)

    if ScoreA > ScoreB then
        return 0
    elseif ScoreA < ScoreB then
        return 1
    else
        return 2
    end

    return 2

end


----------------------------------------------------------------------------------------------
--�淨1�������Զ��ӷ�
--���ֱ��
----------------------------------------------------------------------------------------------
function x300643_UpdateBarnScore(sceneId,BarnNum)

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

	local Guild1 = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN1_GUILD)
	local Guild2 = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN2_GUILD)
	local Guild3 = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN3_GUILD)
	local Guild4 = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN4_GUILD)

    local Guild = Guild1
    if BarnNum == 0 then
        Guild = Guild1
    elseif BarnNum == 1 then
        Guild = Guild2
    elseif BarnNum == 2 then
        Guild = Guild3
    elseif BarnNum == 3 then
        Guild = Guild4
    end


 	local ScoreA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_SOCRE)
	local ScoreB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_SOCRE)

    local GuildA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_GUILD)
    local GuildB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_GUILD)

	local OldTime = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN1_TIME + BarnNum)
  	SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_BARN1_TIME + BarnNum,OldTime+1)

	--ÿ10�������Զ��ӷֺ�ս����Դ��
	
	local ResPointA = x300643_g_ScoreIntervalA[sceneId]
	local ResPointB = x300643_g_ScoreIntervalB[sceneId]
	if OldTime >= 10 then
		if Guild1 == Guild2 and Guild1 == Guild3 and Guild1 == Guild4 then
			if GuildA >= 0 and GuildA == Guild1 then 		--��A��
				SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_A_SOCRE,ScoreA+4) 
				x300643_g_ScoreIntervalA[sceneId] = x300643_g_ScoreIntervalA[sceneId] + 8
				BroadcastGuildBattleResourceScore(sceneId, 0,x300643_g_ScoreIntervalA[sceneId] )
			elseif GuildB >= 0 and GuildB == Guild1 then 	--��B��
                SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_B_SOCRE,ScoreB+4)
                x300643_g_ScoreIntervalB[sceneId] = x300643_g_ScoreIntervalB[sceneId] + 8
                BroadcastGuildBattleResourceScore(sceneId, 1,x300643_g_ScoreIntervalB[sceneId] )
            end
            
        else

			if GuildA >= 0 and GuildA == Guild then 		--��A��
                SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_A_SOCRE,ScoreA+1)
                x300643_g_ScoreIntervalA[sceneId] = x300643_g_ScoreIntervalA[sceneId] + 1
                BroadcastGuildBattleResourceScore(sceneId, 0,x300643_g_ScoreIntervalA[sceneId] )
            elseif GuildB >= 0 and GuildB == Guild then 	--��B��
                SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_B_SOCRE,ScoreB+1)
                x300643_g_ScoreIntervalB[sceneId] = x300643_g_ScoreIntervalB[sceneId] + 1
                BroadcastGuildBattleResourceScore(sceneId, 1,x300643_g_ScoreIntervalB[sceneId] )
			end
		end
		
		--print("x300643_UpdateBarnScoreA",x300643_g_ScoreIntervalA[sceneId],x300643_g_ScoreIntervalA[sceneId])
		--���豻ռ��ʱ��
		SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_BARN1_TIME + BarnNum,-1 )
	end
	
    --ÿ60�������Զ��ӷ�
--	if OldTime >= 60 then
--
--		if Guild1 == Guild2 and Guild1 == Guild3 and Guild1 == Guild4 then
--
--			if GuildA >= 0 and GuildA == Guild1 then 		--��A��
--
--                SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_A_SOCRE,ScoreA+2)
--
--			elseif GuildB >= 0 and GuildB == Guild1 then 	--��B��
--
--                SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_B_SOCRE,ScoreB+2)
--
--            end
--
--		else
--
--			if GuildA >= 0 and GuildA == Guild then 		--��A��
--
--                SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_A_SOCRE,ScoreA+1)
--
--            elseif GuildB >= 0 and GuildB == Guild then 	--��B��
--
--                SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_B_SOCRE,ScoreB+1)
--			end
--
--		end
--
--		--���豻ռ��ʱ��
--		SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_BARN1_TIME + BarnNum,-1 )
--	end

    --�����ֲܷ�Ҫ��������
  	if GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_SOCRE) > x300643_g_MaxScore  then
  	   SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_A_SOCRE,x300643_g_MaxScore)
  	end

  	if GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_SOCRE) > x300643_g_MaxScore  then
  	   SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_B_SOCRE,x300643_g_MaxScore)
  	end
end

----------------------------------------------------------------------------------------------
--����С��ͼ
----------------------------------------------------------------------------------------------
function x300643_UpdateSceneDataFlag( sceneId,idx )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end


    --ȡ�����ֵ��������
    local Guild1 = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN1_GUILD)
    local Guild2 = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN2_GUILD)
    local Guild3 = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN3_GUILD)
    local Guild4 = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN4_GUILD)

    local GuidA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_GUILD)
    local GuidB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_GUILD)

    --����1
    if idx == 1 then
        if Guild1 < 0 then
            SetSceneMapDataFlag( sceneId,1,0,"����",19,32,-1)
        else
            if Guild1 == GuidA then
                SetSceneMapDataFlag( sceneId,1,2,"����",19,32,-1)
            elseif Guild1 == GuidB then
                SetSceneMapDataFlag( sceneId,1,1,"����",19,32,-1)
            else
                SetSceneMapDataFlag( sceneId,1,0,"����",19,32,-1)
            end
        end
    end

    --����2
    if idx == 2 then
        if Guild2 < 0 then
            SetSceneMapDataFlag( sceneId,2,0,"����",231,33,-1)
        else
            if Guild2 == GuidA then
                SetSceneMapDataFlag( sceneId,2,2,"����",231,33,-1)
            elseif Guild2 == GuidB then
                SetSceneMapDataFlag( sceneId,2,1,"����",231,33,-1)
            else
                SetSceneMapDataFlag( sceneId,2,0,"����",231,33,-1)
            end
        end
    end

    --����3
    if idx == 3 then
        if Guild3 < 0 then
            SetSceneMapDataFlag( sceneId,3,0,"����",20,218,-1)
        else
            if Guild3 == GuidA then
                SetSceneMapDataFlag( sceneId,3,2,"����",20,218,-1)
            elseif Guild3 == GuidB then
                SetSceneMapDataFlag( sceneId,3,1,"����",20,218,-1)
            else
                SetSceneMapDataFlag( sceneId,3,0,"����",20,218,-1)
            end
        end
    end

    --����4
    if idx == 4 then
        if Guild4 < 0 then
            SetSceneMapDataFlag( sceneId,4,0,"����",233,221,-1)
        else
            if Guild4 == GuidA then
                SetSceneMapDataFlag( sceneId,4,2,"����",233,221,-1)
            elseif Guild4== GuidB then
                SetSceneMapDataFlag( sceneId,4,1,"����",233,221,-1)
            else
                SetSceneMapDataFlag( sceneId,4,0,"����",233,221,-1)
            end
        end
    end

    --�ֿ�A
    if idx == 5 then
       SetSceneMapDataFlag( sceneId,5,4,"�ֿ�",219,122.6,-1)
    end

    --�ֿ�B
    if idx == 6 then
       SetSceneMapDataFlag( sceneId,6,3,"�ֿ�",34,127.1,-1)
    end

    --����
    if idx == 7 then
        local owner = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_OWNER)
        if owner ~= -1 and IsPlayerStateNormal(sceneId,owner) == 1  then

            local nGuildID = GetGuildID(sceneId,owner)
            local x,z = GetWorldPos(sceneId,owner)

            if nGuildID == GuidA then
                SetSceneMapDataFlag( sceneId,7,6,"����",x,z,-1)
            elseif nGuildID == GuidB then
                SetSceneMapDataFlag( sceneId,7,5,"����",x,z,-1)
            else
                local x,z= GetGrowPointPos(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT )
                if x ~= nil and z ~= nil then
                    SetSceneMapDataFlag( sceneId,7,7,"����",x,z,-1)
                else
                    SetSceneMapDataFlag( sceneId,7,7,"����",LD_GUILD_BATTLE_FLAG_X,LD_GUILD_BATTLE_FLAG_Y,-1)
                end
            end

        else

            local x,z= GetGrowPointPos(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT )

            if x ~= nil and z ~= nil then
                SetSceneMapDataFlag( sceneId,7,7,"����",x,z,-1)
            else
                SetSceneMapDataFlag( sceneId,7,7,"����",LD_GUILD_BATTLE_FLAG_X,LD_GUILD_BATTLE_FLAG_Y,-1)
            end
        end
    end

    --NPCA
    if idx == 8 then
        SetSceneMapDataFlag( sceneId,8,8,"���ս��������",17.3,134,-1)
    end

    --NPCA1
    --if idx == 9 then
    --    SetSceneMapDataFlag( sceneId,9,8,"ɽկ��Ԯ������",226,232,-1)
    --end

    if idx == 10 then
        SetSceneMapDataFlag( sceneId,10,8,"���ս������Ա",237.8,129.8,-1)
    end

    --NPCB
    if idx == 11 then
        SetSceneMapDataFlag( sceneId,11,8,"���ս��������",237.8,115,-1)
    end

    --NPCB1
    --if idx == 12 then
    --    SetSceneMapDataFlag( sceneId,12,8,"ɽׯ��Ԯ������",22,22,-1)
    --end

    if idx == 13 then
        SetSceneMapDataFlag( sceneId,13,8,"���ս������Ա",17.3,120,-1)
    end
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300643_BattleBonus( sceneId,selfId,battleResult ,nSortID)

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
    local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

    local nGuildId = GetGuildID(sceneId,selfId)

    local nGuildFlag = -1

    --������ս���е���Ӫ����
    if nGuildId == nGuildA then
        nGuildFlag = 0
    elseif nGuildId == nGuildB then
        nGuildFlag = 1
    end


    local nBonusType = 2

    --�ж�һ����Ӯ
    if battleResult == 0 then
        
        if nGuildFlag == 0 then
            nBonusType = 1
        else
            nBonusType = 0
        end

    elseif battleResult == 1 then
        
        if nGuildFlag == 0 then
            nBonusType = 0
        else
            nBonusType = 1
        end
    end

    if nBonusType == 0 then

        local level = GetLevel(sceneId,selfId)
        local name = GetName(sceneId,selfId)
        --ս��
        local expNum =level * x300643_g_LosePrise
        local bangGong =  x300643_g_LoseBangGong
        local bangExp = x300643_g_LoseBangExp
		local bangshiming = x300643_g_LoseBangshiming 
		local bangjinqian = x300643_g_LoseBangjinqian
		--local banggongde = x300643_g_LoseBanggongde

        local msg = format(x300643_g_BonusTips,expNum,bangGong,bangExp,bangshiming,20)

        LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
        LuaScenceM2Player(sceneId, selfId, x300643_g_BonusTips1,name , 3,1)

        AddExp(sceneId,selfId,expNum)
        AddGuildUserPoint(sceneId,selfId,bangGong)
        AddGuildExp(sceneId,selfId,bangExp)
		AddGuildShiMing (sceneId,selfId,bangshiming)
		AddGuildMoney(sceneId,selfId,bangjinqian)
		--AddGuildMerit(sceneId,selfId,banggongde)

        --����Player�����Ϣ
        local nCountryId   = GetCurCountry( sceneId, selfId )
        local nBeKilled    = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_BEKILLED)
        local nKilledOther = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_KILLEDOTHER)
        local nGetFlag     = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_GETFLAG)

        local nRongYu = nKilledOther*2
        AddHonor(sceneId,selfId,nRongYu)

        GuildBattleSendPlayerInfo(sceneId,name,nCountryId,nBeKilled,nKilledOther,nGetFlag,nRongYu,expNum,nGuildFlag)

    elseif nBonusType == 1 then

        local level = GetLevel(sceneId,selfId)
        local name = GetName(sceneId,selfId)
        --սʤ
        local expNum =level * x300643_g_WinPrise
        local bangGong = x300643_g_WinBangGong
        local bangExp =  x300643_g_WinBangExp
		local bangshiming = x300643_g_WinBangshiming
		local bangjinqian = x300643_g_WinBangjinqian
		--local banggongde = x300643_g_WinBanggongde

        local msg = format(x300643_g_BonusTips,expNum,bangGong,bangExp,bangshiming,40)

        LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
        LuaScenceM2Player(sceneId, selfId, x300643_g_BonusTips1,name , 3,1)

        AddExp(sceneId,selfId,expNum)
        AddGuildUserPoint(sceneId,selfId,bangGong)
        AddGuildExp(sceneId,selfId,bangExp)
		AddGuildShiMing (sceneId,selfId,bangshiming)
		AddGuildMoney(sceneId,selfId,bangjinqian)
		--AddGuildMerit(sceneId,selfId,banggongde)

        --����Player�����Ϣ
        local nCountryId   = GetCurCountry( sceneId, selfId )
        local nBeKilled    = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_BEKILLED)
        local nKilledOther = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_KILLEDOTHER)
        local nGetFlag     = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_GETFLAG)

        local nRongYu = nKilledOther*2
        AddHonor(sceneId,selfId,nRongYu)
        
        GuildBattleSendPlayerInfo(sceneId,name,nCountryId,nBeKilled,nKilledOther,nGetFlag,nRongYu,expNum,nGuildFlag)

    elseif nBonusType == 2 then

        local level = GetLevel(sceneId,selfId)
        local name = GetName(sceneId,selfId)
        --սƽ
        local expNum =level * x300643_g_DeucePrise
        local bangGong = x300643_g_DeuceBangGong
        local bangExp = x300643_g_DeuceBangExp
		local bangshiming = x300643_g_DeuceBangshiming
		local bangjinqian = x300643_g_DeuceBangjinqian
		--local banggongde = x300643_g_DeuceBanggongde

        local msg = format(x300643_g_BonusTips,expNum,bangGong,bangExp,bangshiming,20)

        LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
        LuaScenceM2Player(sceneId, selfId, x300643_g_BonusTips1,name , 3,1)

        AddExp(sceneId,selfId,expNum)
        AddGuildUserPoint(sceneId,selfId,bangGong)
        AddGuildExp(sceneId,selfId,bangExp)
		AddGuildShiMing (sceneId,selfId,bangshiming)
		AddGuildMoney(sceneId,selfId,bangjinqian)
		--AddGuildMerit(sceneId,selfId,banggongde)

        --����Player�����Ϣ
        local nCountryId   = GetCurCountry( sceneId, selfId )
        local nBeKilled    = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_BEKILLED)
        local nKilledOther = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_KILLEDOTHER)
        local nGetFlag     = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_GETFLAG)

        local nRongYu = nKilledOther*2
        AddHonor(sceneId,selfId,nRongYu)
        
        GuildBattleSendPlayerInfo(sceneId,name,nCountryId,nBeKilled,nKilledOther,nGetFlag,nRongYu,expNum,nGuildFlag)

    end
    
    --ǰ���������⴦��
    -- if nSortID == 1 then
    	
    	-- AddGuildMerit(sceneId,selfId,45)
    	
    	-- local name = GetName(sceneId,selfId)
    	-- local msg = "��ϲ���ڴ˴ΰ��ս�л�ø��˵�һ��,����45��﹦��"
    	-- LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
        -- LuaScenceM2Player(sceneId, selfId, msg ,name , 3,1)
    	
    -- elseif nSortID == 2 then
    	
    	-- AddGuildMerit(sceneId,selfId,40)
    	
    	-- local name = GetName(sceneId,selfId)
    	-- local msg = "��ϲ���ڴ˴ΰ��ս�л�ø��˵ڶ���,����40��﹦��"
    	-- LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
        -- LuaScenceM2Player(sceneId, selfId, msg ,name , 3,1)
    	
    -- elseif nSortID == 3 then
    
    	-- AddGuildMerit(sceneId,selfId,35)
    	
    	-- local name = GetName(sceneId,selfId)
    	-- local msg = "��ϲ���ڴ˴ΰ��ս�л�ø��˵�����,����35��﹦��"
    	-- LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
        -- LuaScenceM2Player(sceneId, selfId, msg ,name , 3,1)
    -- end
    
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300643_GuildBattleBonus( sceneId ,battleResult )

	--�ռ���Ϣ
	local PlayerList = {}
	local PlayerCount = 0
	
	local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
        	
        	local nBeKilled    	= GetPlayerRuntimeData(sceneId,objId,RD_GUILDBATTLE_BEKILLED)
	        local nKilledOther 	= GetPlayerRuntimeData(sceneId,objId,RD_GUILDBATTLE_KILLEDOTHER)
	        local nGetFlag     	= GetPlayerRuntimeData(sceneId,objId,RD_GUILDBATTLE_GETFLAG)
	        local nPower 		= nKilledOther*5000 + nGetFlag*1000 - nBeKilled 
	        
	        --��ӵ���������
            PlayerCount = PlayerCount + 1
            PlayerList[PlayerCount] = {objId,nPower}
        end
    end
    
    
    --�������Ϊ0
    if PlayerCount == 0 then
    	return
    end
    
    --����
    local sortproc = function(a,b) return a[2] > b[2] end 
    sort(PlayerList,sortproc)
    
    --����
    for i = 1,PlayerCount do
    	x300643_BattleBonus( sceneId,PlayerList[i][1],battleResult,i)
    end
    
end


----------------------------------------------------------------------------------------------
--�ָ���Ӫ
----------------------------------------------------------------------------------------------
function x300643_RestoreAllPlayerCamp( sceneId )

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
--�ָ���Ӫ
----------------------------------------------------------------------------------------------
function x300643_RestorePlayerCamp( sceneId,selfId )
    local nCountryId = GetCurCountry( sceneId,selfId )
    SetCurCamp(sceneId,selfId,nCountryId )
end

----------------------------------------------------------------------------------------------
--���ɰ�ս���
----------------------------------------------------------------------------------------------
function x300643_BattleGenResult( sceneId, callerId  )

    local nTime = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_COUNT_ITME )
    
    --�����֪ͨGLserver
    local GuildIdA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_GUILD)
    SetGuildQuestData(sceneId,GuildIdA,GD_GUILD_INDEX_BATTL_STATE,-1)

    local GuildIdB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_GUILD)
    SetGuildQuestData(sceneId,GuildIdB,GD_GUILD_INDEX_BATTL_STATE,-1)

    local textA = "���ս����"
    local textB = "���ս����"

    local SystemTipsA = ""
    local SystemTipsB = ""

    --�õ���ʤ��
    local Winner = x300643_GetWinner(sceneId)

    --���ͻ�����Ϣ
    local TitleBlue = GetGuildName( GuildIdA)
    local TitleRed  = GetGuildName( GuildIdB)

    GuildBattleSendBaseInfo(sceneId,TitleBlue,TitleRed,Winner,nTime)

    x300643_GuildBattleBonus( sceneId,Winner )

    if Winner == 0 then        --A����ʤ

        SetGuildQuestData( sceneId,GuildIdA,GD_GUILD_INDEX_BATTL_WIN_NUM,1,1 )
        SetGuildQuestData( sceneId,GuildIdB,GD_GUILD_INDEX_BATTL_LOSE_NUM,1,1 )
		
		CallScriptFunction( 300638, "SaveGuildWeekResult", sceneId,GuildIdA, 2 )	
		CallScriptFunction( 300638, "SaveGuildWeekResult", sceneId,GuildIdB, 0 )
		

        --���������ʾ
        textA = "#G�����ڵİ���ڱ��ΰ��ս��ȡ��ʤ��"
        textB = "#G�����ڵİ���ڱ��ΰ��ս�в���ʧ��"

        SystemTipsA = "ս��ʤ��"
        SystemTipsB = "ս��ʧ��"

    elseif Winner == 1 then    --B����ʤ

        SetGuildQuestData( sceneId,GuildIdB,GD_GUILD_INDEX_BATTL_WIN_NUM,1,1 )
        SetGuildQuestData( sceneId,GuildIdA,GD_GUILD_INDEX_BATTL_LOSE_NUM,1,1 )
		CallScriptFunction( 300638, "SaveGuildWeekResult", sceneId,GuildIdA, 0 )	
		CallScriptFunction( 300638, "SaveGuildWeekResult", sceneId,GuildIdB, 2 )

        --���������ʾ
        textA = "#G�����ڵİ���ڱ��ΰ��ս�в���ʧ��"
        textB = "#G�����ڵİ���ڱ��ΰ��ս��ȡ��ʤ��"

        SystemTipsA = "ս��ʧ��"
        SystemTipsB = "ս��ʤ��"

    else                        --�����Ժ�

        SetGuildQuestData( sceneId,GuildIdA,GD_GUILD_INDEX_BATTL_DEUCE_NUM,1,1 )
        SetGuildQuestData( sceneId,GuildIdB,GD_GUILD_INDEX_BATTL_DEUCE_NUM,1,1 )
		CallScriptFunction( 300638, "SaveGuildWeekResult", sceneId,GuildIdA, 1 )	
		CallScriptFunction( 300638, "SaveGuildWeekResult", sceneId,GuildIdB, 1 )

        --���������ʾ
        textA = "#G�����ڵİ���ڱ��ΰ��ս�д��ƽ��"
        textB = "#G�����ڵİ���ڱ��ΰ��ս�д��ƽ��"

        SystemTipsA = "˫��սƽ"
        SystemTipsB = "˫��սƽ"
    end

    --�㲥
    LuaThisScenceM2Guild(sceneId,textA,GuildIdA,2,1)
    LuaThisScenceM2Guild(sceneId,textB,GuildIdB,2,1)

    LuaThisScenceM2Guild(sceneId,textA,GuildIdA,3,1)
    LuaThisScenceM2Guild(sceneId,textB,GuildIdB,3,1)

    LuaThisScenceM2Guild(sceneId,SystemTipsA,GuildIdA,5,1)
    LuaThisScenceM2Guild(sceneId,SystemTipsB,GuildIdB,5,1)


    --���뵹��ʱ״̬,�����õ���ʱ��
    SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_COUNT_DOWN_STATE,1 )
    SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_COUNT_DOWN_TIME,60 )
        
    --��¼��־
    local msg = format("GBL:x300643_BattleGenResult SceneId=%d,LeaveTime h= %d,m=%d,CallerId=%d",sceneId, floor(nTime/60),mod(nTime,60), callerId )
    WriteLog(1,msg)

    x300643_SetAllPlayerNeedKick(sceneId,60)
    x300643_DestroyBattleFlags( sceneId )
    ClearGuildBattleSceneData(sceneId)

end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300643_GuildBattleKickPlayer( sceneId,selfId )

    --�������״̬
    if GetHp(sceneId,selfId) <= 0 then
	
		ClearRageRecoverTick(sceneId, selfId)
		RestoreHp(sceneId, selfId,100)
		RestoreRage(sceneId, selfId,100)
		ClearMutexState(sceneId, selfId, 6)
		SendReliveResult(sceneId, selfId,1)	
	end
	
	LastMount(sceneId, selfId )
	RestoreHp(sceneId, selfId,0)
	
    x300643_RestorePlayerCamp(sceneId,selfId)

    --�������BakScene��Ϣ������BakScene��ϢΪ׼
    local nBakSceneId,x,z = GetPlayerBakSceneInfo(sceneId,selfId )
    if nBakSceneId >= 0 then
        NewWorld(sceneId,selfId,nBakSceneId,x,z,300643)
        return
    end

    --���û��BakScene��Ϣ�����͵��������ִ�
    local nCountry = GetCurCountry(sceneId,selfId)
    if nCountry == 0 then
        
        --¥��
        local nDestSceneId = 50
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300643)

    elseif nCountry == 1 then
        
        --��ɽ
        local nDestSceneId = 150
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300643)

    elseif nCountry == 2 then

        --����
        local nDestSceneId = 250
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300643)

    elseif nCountry == 3 then
        
        --�ػ�
        local nDestSceneId = 350
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300643)

    end
end

----------------------------------------------------------------------------------------------
--�ߵ����������е���
----------------------------------------------------------------------------------------------
function x300643_GuildBattleKickAllPlayer( sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            
            x300643_GuildBattleKickPlayer( sceneId,objId)

        end
    end
end

----------------------------------------------------------------------------------------------
--ͬ����ս����ʱ��ȫ����ң���ǰ������
----------------------------------------------------------------------------------------------
function x300643_SyncBattleTimeToAllPlayer( sceneId ,nTime )

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
--��������뿪���ս��
----------------------------------------------------------------------------------------------
function x300643_OnPlayerAskLeaveGuildBattle( sceneId,selfId )
    
    x300643_GuildBattleKickPlayer( sceneId, selfId )

end

----------------------------------------------------------------------------------------------
--��GLServer������ͬ�����ʱ��Ķ���
----------------------------------------------------------------------------------------------
function x300643_OnSyncGuildBattleTime( sceneId,nTime )
    
    if x300643_IsGuildBattleScene_Gjs( sceneId ) == 0 then
        return
    end

    if x300643_CheckBattleState( sceneId ) == 0 then
        return
    end

    local nTime_new = x300643_g_TotalBattleTime - NumberCastIntToUInt( nTime )
    SetGuildBattleSceneData_Param(sceneId, LD_GUILD_BATTLE_COUNT_ITME, nTime_new )

    --��ʱ��ʱ��ͬ��
    ----------------------------------------------------------------------------------------------
    x300643_SyncBattleTimeToAllPlayer( sceneId, nTime_new )
end


----------------------------------------------------------------------------------------------
--�������������Ҫ�ߵ�
----------------------------------------------------------------------------------------------
function x300643_SetAllPlayerNeedKick( sceneId,nKickTime )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local KickDown = GetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ) 
            if KickDown <= 0 or KickDown > nKickTime then                
                SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,nKickTime) 
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--��������ߵ�״̬
----------------------------------------------------------------------------------------------
function x300643_UpdatePlayerKickState( sceneId )
    
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
                    x300643_GuildBattleKickPlayer( sceneId,objId )
                else
                    --���򣬼�������ʱ
                    SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,KickDown) 
                end
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--ͬ���������
----------------------------------------------------------------------------------------------
function x300643_SyncGuildPower( sceneId )
    
    local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
    local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

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
    BroadcastGuildBattlePower(sceneId,nGuildA_Count,nGuildB_Count)

end

----------------------------------------------------------------------------------------------
--���û���������
----------------------------------------------------------------------------------------------
function x300643_ResetConvoyGrowPoint(sceneId,bShowMsg)

	local nCount = getn(x300643_g_ConvoyGrowPointPosList)
	local nIndex = random(1,nCount)
	
	if nIndex < 1 then
		nIndex = 1
	elseif nIndex > nCount then
		nIndex = nCount
	end
	
	local x = x300643_g_ConvoyGrowPointPosList[nIndex][1]
	local z = x300643_g_ConvoyGrowPointPosList[nIndex][2]
	
	RecycleGrowPointByType(sceneId,x300643_g_ConvoyGrowPointType[sceneId],1000)
    SetGrowPointPos(sceneId,x300643_g_ConvoyGrowPointType[sceneId],x,z)
    
    if bShowMsg == 1 then
	    local msg = format("ս�����µı��������(%d,%d)",x,z)
	    LuaThisScenceM2Wrold(sceneId,msg,2,1)	
	    LuaThisScenceM2Wrold(sceneId,msg,3,1)
    end
end

----------------------------------------------------------------------------------------------
--����Ƿ����ִ�л���������ɼ�
----------------------------------------------------------------------------------------------
function x300643_OnRecyleConvoyGrowPoint_Check(sceneId,selfId)
	
	local status = GetGuildBattleStatus( sceneId )
    if status ~= STATE_GUILD_BATTLE_BATTLE then
    	return 1
    end
    
    local nCampID = GetCurCamp(sceneId,selfId)
    if nCampID ~= x300643_g_Guild_Camp_A and nCampID ~= x300643_g_Guild_Camp_B then
    	return 1
    end
	
	return 0
end

----------------------------------------------------------------------------------------------
--ִ�л���������ɼ�
----------------------------------------------------------------------------------------------
function x300643_OnRecyleConvoyGrowPoint(sceneId,selfId)


	--��ؼ��
	local status = GetGuildBattleStatus( sceneId )
    if status ~= STATE_GUILD_BATTLE_BATTLE then
    	return 0
    end
    
    local nCampID = GetCurCamp(sceneId,selfId)
    if nCampID ~= x300643_g_Guild_Camp_A and nCampID ~= x300643_g_Guild_Camp_B then
    	return 0
    end
	
	--A���Ʒ�
	if nCampID == x300643_g_Guild_Camp_A then
		x300643_g_ScoreIntervalA[sceneId] = x300643_g_ScoreIntervalA[sceneId] + 10
		BroadcastGuildBattleResourceScore(sceneId, 0,x300643_g_ScoreIntervalA[sceneId] )
	end
	
	--B���Ʒ�
	if nCampID == x300643_g_Guild_Camp_B then
		x300643_g_ScoreIntervalB[sceneId] = x300643_g_ScoreIntervalB[sceneId] + 10
		BroadcastGuildBattleResourceScore(sceneId, 1,x300643_g_ScoreIntervalB[sceneId] )
	end
	
	--������������Ҫ����
	x300643_g_ConvoyGrowPointState[sceneId] = 0
	
	--�����������
	SetGrowPointIntervalContainer(sceneId,x300643_g_ConvoyGrowPointType[sceneId],-1)
	
	--����ϵͳ���Ի���
	return 1
end

----------------------------------------------------------------------------------------------
--ȡ���ڲ�����A
----------------------------------------------------------------------------------------------
function x300643_GetScoreIntervalA(sceneId)
	return x300643_g_ScoreIntervalA[sceneId]
end

----------------------------------------------------------------------------------------------
--ȡ���ڲ�����B
----------------------------------------------------------------------------------------------
function x300643_GetScoreIntervalB(sceneId)
	return x300643_g_ScoreIntervalB[sceneId]
end

----------------------------------------------------------------------------------------------
--�淨1�����ս����Դ��
--��ӪID��0��1
----------------------------------------------------------------------------------------------
--���ս��˫����Ӫ

function x300643_GetScoreInterval(sceneId,CampId)
	if CampId == x300643_g_Guild_Camp_A then
		local ResPointA = x300643_g_ScoreIntervalA[sceneId]
		return ResPointA
	elseif CampId == x300643_g_Guild_Camp_B then
		local ResPointB = x300643_g_ScoreIntervalB[sceneId]
		return ResPointB
	end
	return -1
end


----------------------------------------------------------------------------------------------
--����ȡ���ڲ�����
----------------------------------------------------------------------------------------------
function x300643_SetScoreIntervalInc(sceneId,CampId,resPointInc)
	if CampId == x300643_g_Guild_Camp_A then
		local ResPointA = x300643_g_ScoreIntervalA[sceneId]
		x300643_g_ScoreIntervalA[sceneId] = ResPointA + resPointInc
		BroadcastGuildBattleResourceScore(sceneId, 0,x300643_g_ScoreIntervalA[sceneId] )

	elseif CampId == x300643_g_Guild_Camp_B then
		local ResPointB = x300643_g_ScoreIntervalB[sceneId]
		x300643_g_ScoreIntervalB[sceneId] = ResPointB + resPointInc
		BroadcastGuildBattleResourceScore(sceneId, 1,x300643_g_ScoreIntervalB[sceneId] )
	end

end
--MisDescBegin
-------------------------
--***********************
--Const
--***********************
-------------------------

x700005_g_ScriptId              = 700005
x700005_g_MissionId             = 409

x700005_g_FuBenType             = 1

x700005_g_FubenName         = "����"
x700005_g_Name                  = ""
x700005_g_FubenType         	= FUBEN_BIWULEITAI
x700005_g_TickTime              = 5             --�ص��ű���ʱ��ʱ�䣨��λ����/�Σ�
x700005_g_LimitTotalHoldTime    = 100   --�������Դ���ʱ�䣨��λ��������,�����ʱ�䵽�ˣ������񽫻�ʧ��
x700005_g_CloseTick             = 6             --�����ر�ǰ����ʱ����λ��������
x700005_g_NoUserTime            = 10            --������û���˺���Լ��������ʱ�䣨��λ���룩
x700005_g_Fuben_X1              = 46                --����1���븱����λ��X
x700005_g_Fuben_Z1              = 64                --����1���븱����λ��Z
x700005_g_Fuben_X2              = 82                --����2���븱����λ��X
x700005_g_Fuben_Z2              = 66                --����2���븱����λ��Z
x700005_g_Back_X                = 227                --Դ����λ��X
x700005_g_Back_Z                = 239.5               --Դ����λ��Z


x700005_g_MissionName           = "�뿪���䳡"
x700005_g_MissionInfo           = "��ȷ��Ҫ�뿪���䳡��"

x700005_g_FuBenCreateOK             = "������̨�����ɹ���"
x700005_g_FuBenCreateFailed         = "������̨�Ѵ����ޣ����Ժ����ԣ�"
x700005_g_MissionAbandon            = "����ʧ�ܣ�"
x700005_g_CountDownMessage          = "�㽫��%d����뿪������̨��"
x700005_g_SceneMapNavPath           = "fuben_biwuleitai/fuben_biwuleitai.nav"

--MisDescEnd

x700005_g_MissionNPCName            =   {
                                            {scene = 11, name = "�շ�"},        --����
                                            {scene = 18, name = "�շ�"},        --����
                                            {scene = 21, name = "�շ�"},        --ѩ��
                                            {scene = 24, name = "�շ�"},        --��Į
                                            {scene = 36, name = "���¾�"}       --�ʳ�
                                        }

-------------------------
--***********************
--Define
--***********************
-------------------------

x700005_OK                          = 0
x700005_OK_RETURN                   = 1
x700005_ERROR_UNKNOWN               = -1

x700005_FAILED_COUNTRY              = 10
x700005_FAILED_LEVEL                = 11
x700005_FAILED_TEAM                 = 14
x700005_FAILED_TEAMNUM              = 15
x700005_FAILED_CAPTAIN              = 16

x700005_FAILED_OTHERLEVEL           = 20
x700005_FAILED_OTHERMISSION         = 22
x700005_FAILED_OTHERAROUND          = 23

x700005_MP_AIMSCENE                 = 0
x700005_MP_TEAMID                   = 1
x700005_MP_KILLMONSTER              = 2
x700005_MP_ISCOMPLETE               = 7

x700005_CSP_FUBENTYPE               = 0
x700005_CSP_SCRIPTID                = 1
x700005_CSP_TICKCOUNT               = 2
x700005_CSP_FROMSCENEID             = 3
x700005_CSP_ISCLOSING               = 4
x700005_CSP_LEAVECOUNTDOWN          = 5

x700005_CSP_TEAMID_1                = 10
x700005_CSP_TEAMID_2                = 11


x700005_CAMP_Team1                  = 5
x700005_CAMP_Team2                  = 6

x700005_Skill_ID                    = 7602	--�޵�BUFF_ID

x700005_wintalk                     =   "���ϡ������ϡ������ϡ������ϡ������ϡ���"
x700005_losetalk                    =   "�������������������������"


function x700005_MakeFubenEx(sceneId, selfId, memberNum, targetId, memberNum2)

    --local str = format("MakeFubenEx Start");
    --PrintStr(str);

    local teamid = GetTeamId(sceneId, selfId)
    local teamid2 = GetTeamId(sceneId, targetId)

    local guid1 = ObjId2Guid( sceneId,selfId )
    local guid2 = ObjId2Guid( sceneId,targetId )


    if teamid ~=-1 and teamid2 ~=-1 and teamid == teamid2 then
        BeginQuestEvent(sceneId);
            AddQuestText(sceneId, "��ͶԷ���ͬһ��������ܲμӱ��䣡");
        EndQuestEvent();
        DispatchQuestTips(sceneId, selfId);
        DispatchQuestTips(sceneId, targetId);
        return
    end

    local leaderguid = ObjId2Guid(sceneId, selfId);
    SetSceneLoad_Map(sceneId, x700005_g_SceneMapNavPath); --��ͼ�Ǳ���ѡȡ�ģ����ұ�����Config/SceneInfo.ini�����ú�
    SetFubenData_TeamLeader(sceneId, leaderguid);
    SetFubenData_NoUserCloseTime(sceneId, x700005_g_NoUserTime * 1000);
    SetFubenData_Timer(sceneId, x700005_g_TickTime * 1000);
    SetFubenData_Param(sceneId, x700005_CSP_FUBENTYPE, x700005_g_FubenType);--���ø������ݣ����ｫ0����������������Ϊ999�����ڱ�ʾ������999(�����Զ���)
    SetFubenData_Param(sceneId, x700005_CSP_SCRIPTID, x700005_g_ScriptId);--��1����������Ϊ���������¼��ű���
    SetFubenData_Param(sceneId, x700005_CSP_TICKCOUNT, 0);--���ö�ʱ�����ô���
    SetFubenData_Param(sceneId, x700005_CSP_FROMSCENEID, sceneId);--���ø�����ڳ�����, ��ʼ��
    SetFubenData_Param(sceneId, x700005_CSP_ISCLOSING, 0);--���ø����رձ�־, 0���ţ�1�ر�
    SetFubenData_Param(sceneId, x700005_CSP_LEAVECOUNTDOWN, 0);--�����뿪����ʱ����


    SetFubenData_Param(sceneId, x700005_CSP_TEAMID_1, guid1); --��������
    SetFubenData_Param(sceneId, x700005_CSP_TEAMID_2, guid2); --��������


    local bRetSceneID = CreateFuben(sceneId); --��ʼ����ɺ���ô�����������

    BeginQuestEvent(sceneId);
    if bRetSceneID > 0 then
        AddQuestText(sceneId, x700005_g_FuBenCreateOK);
    else
        AddQuestText(sceneId, x700005_g_FuBenCreateFailed);
    end
    EndQuestEvent();
    DispatchQuestTips(sceneId, selfId);

end


------------------------
--***********************
--OnPlayerDie
--***********************
-------------------------

function x700005_OnPlayerDie(sceneId, selfId, killerId)


    --������Ϣ
    BeginQuestEvent(sceneId)
        Msg2Player(sceneId,killerId,"���ϡ������ϡ������ϡ������ϡ������ϡ���",4,2)
        Msg2Player(sceneId,selfId,"�������������������������",4,2)
    EndQuestEvent()



end

-------------------------
--***********************
--OnPlayerEnter
--***********************
-------------------------

function x700005_OnPlayerEnter(sceneId, selfId)

    --SetPlayerDefaultReliveInfo(sceneId, selfId, "%10", "%10", "%10", sceneId, x700005_g_Fuben_X, x700005_g_Fuben_Z);

    SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,x700005_Skill_ID,10);

end


function x700005_RestorePlayerCamp( sceneId,selfId)

      local nCountry = GetCurCountry( sceneId,selfId )
      SetCurCamp( sceneId,selfId,nCountry )
end

--***********************
--OnFubenReady
--***********************
-------------------------

function x700005_OnFubenReady(sceneId, destsceneId)

--    local str = format("[OnFubenReady] Start!!!!!!");
--    PrintStr(str);

    SetFubenData_Param(destsceneId, x700005_CSP_FROMSCENEID, sceneId);--���ø�����ڳ�����

    local selfGuidID    = GetFubenData_Param(sceneId, x700005_CSP_TEAMID_1);
    local targetGuidID  = GetFubenData_Param(sceneId, x700005_CSP_TEAMID_2);

    local selfId = Guid2ObjId( sceneId,selfGuidID)
    local targetId = Guid2ObjId( sceneId,targetGuidID)

    local selfTeamID   = GetTeamId(sceneId, selfId)
    local targetTeamID = GetTeamId(sceneId, targetId)

    --���䷢��
    if selfTeamID == -1 then

            SetCurCamp(sceneId,selfId,x700005_CAMP_Team1)
            NewWorld(sceneId, selfId, destsceneId, x700005_g_Fuben_X1, x700005_g_Fuben_Z1,700005);

    else
        local memberNum = GetNearTeamCount(sceneId, selfId);
        for i = 0, memberNum - 1 do

            local memberId = GetNearTeamMember(sceneId, selfId, i)

            SetCurCamp(sceneId,memberId,x700005_CAMP_Team1)
            NewWorld(sceneId, memberId, destsceneId, x700005_g_Fuben_X1, x700005_g_Fuben_Z1,700005)
        end
    end

    --���ܷ�
    if targetTeamID == -1 then

            SetCurCamp(sceneId,targetId,x700005_CAMP_Team2)
            NewWorld(sceneId, targetId, destsceneId, x700005_g_Fuben_X2, x700005_g_Fuben_Z2,700005)

    else
        local memberNum = GetNearTeamCount(sceneId, targetId);
        for i = 0, memberNum - 1 do

            local memberId = GetNearTeamMember(sceneId, targetId, i)

            SetCurCamp(sceneId,memberId,x700005_CAMP_Team2);
            NewWorld(sceneId, memberId, destsceneId, x700005_g_Fuben_X2, x700005_g_Fuben_Z2,700005)
        end
    end

end

--**********************************

--Ĭ���¼�

--**********************************


function x700005_ProcEventEntry(sceneId, selfId, targetId)  --����������ִ�д˽ű�

    BeginQuestEvent(sceneId)
        AddQuestText(sceneId, x700005_g_MissionInfo)
    EndQuestEvent()
    DispatchQuestInfo(sceneId, selfId, targetId, x700005_g_ScriptId, x700005_g_MissionName)

end



--**********************************

--�о��¼�

--**********************************

function x700005_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

--  BeginQuestEvent(sceneId)
        AddQuestNumText(sceneId, x700005_g_ScriptId, x700005_g_MissionName)
--  EndQuestEvent()
--  DispatchQuestEventList(sceneId, selfId, targetId)

end



--**********************************

--����������

--**********************************

function x700005_ProcAcceptCheck(sceneId, selfId, targetId)
return 1
end


--**********************************

--���鿴����

--**********************************

function x700005_CheckPushList(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x700005_ProcAccept(sceneId, selfId)
end

function x700005_OnLeaveBiwu(sceneId, selfId)

    x700005_RestorePlayerCamp(sceneId,selfId)

    local oldsceneId = GetFubenData_Param(sceneId, x700005_CSP_FROMSCENEID);
    SetPlayerMutexState( sceneId,selfId,PLAYER_STATE_DIE,0) --####
    NewWorld(sceneId,selfId,oldsceneId,x700005_g_Back_X,x700005_g_Back_Z,700005)
end



--**********************************

--����

--**********************************

function x700005_ProcQuestAbandon(sceneId, selfId, MissionId)


end



--**********************************

--����Ƿ�����ύ

--**********************************

function x700005_CheckSubmit( sceneId, selfId, targetId)


end



--**********************************

--�ύ

--**********************************

function x700005_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)


end


--���������¼�

--**********************************

function x700005_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x700005_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end

---------------------------------------------------------------------------------------------------
--ȡ������
---------------------------------------------------------------------------------------------------
function x700005_CancelMission(sceneId, selfId)
end

--**********************************

--������ʱ��

--**********************************
function x700005_OnFubenTimer( sceneId, nowTime )
    local nowTickCount = GetFubenData_Param(sceneId, x700005_CSP_TICKCOUNT) + 1;
    SetFubenData_Param(sceneId, x700005_CSP_TICKCOUNT, nowTickCount);


    local leaveFlag = GetFubenData_Param(sceneId, x700005_CSP_ISCLOSING);

    if leaveFlag > 0 then

        --��ʾxx����˳�����
        local leaveCountDown = GetFubenData_Param(sceneId, x700005_CSP_LEAVECOUNTDOWN) + 1;
        SetFubenData_Param(sceneId, x700005_CSP_LEAVECOUNTDOWN, leaveCountDown);

        if leaveCountDown == x700005_g_CloseTick then
            local oldsceneId = GetFubenData_Param(sceneId, x700005_CSP_FROMSCENEID);
            local humancount = GetFuben_PlayerCount(sceneId);
            for i = 0, humancount - 1 do
                local humanId = GetFuben_PlayerObjId(sceneId, i);
                RelivePlayerNM( sceneId,humanId,2) --����һ��
                SetPlayerMutexState( sceneId,humanId,PLAYER_STATE_DIE,0) --####
                x700005_RestorePlayerCamp(sceneId,humanId)
                NewWorld(sceneId,humanId,oldsceneId,x700005_g_Back_X,x700005_g_Back_Z,700005)
            end
        elseif leaveCountDown < x700005_g_CloseTick then
            local humancount = GetFuben_PlayerCount(sceneId);
            for i = 0, humancount - 1 do
                local humanId = GetFuben_PlayerObjId(sceneId, i);
                local str = format(x700005_g_CountDownMessage, (x700005_g_CloseTick - leaveCountDown) * x700005_g_TickTime);
                BeginQuestEvent(sceneId);
                AddQuestText(sceneId, str);
                EndQuestEvent(sceneId);
                DispatchQuestTips(sceneId, humanId);
            end
        end

    else

        if nowTickCount > 4 then


            local humancount = GetFuben_PlayerCount(sceneId);

            if humancount == 1 then

                SetFubenData_Param(sceneId, x700005_CSP_ISCLOSING,1)

            elseif humancount > 1 then

                -- ��������Ϣ�Ƿ���ͬ
                local bLeave = 1
                local bSameTeam = 1
                local bNotInTeam = 1
                local nTeamid = -2
                local nPreteamid = -2

                for i = 0, humancount - 1 do

                    local humanId = GetFuben_PlayerObjId(sceneId, i);

                    nPreteamid = nTeamid
                    nTeamid = GetTeamId( sceneId, humanId )


                    if nPreteamid ==- 2 then
                        nPreteamid = nTeamid
                    end

                    if nTeamid ~= nPreteamid then
                        bSameTeam = 0
                    end

                    if nTeamid ~= -1 then
                        bNotInTeam = 0
                    end
                end

                -- ͬһ������
                if bSameTeam == 1 then

                    if bNotInTeam == 1 then
                        bLeave = 0
                    end
                else
                    bLeave = 0
                end

                -- ����Ƿ���˳�����������
                if nowTickCount == x700005_g_LimitTotalHoldTime then
                    for i = 0, humancount - 1 do

                        local humanId = GetFuben_PlayerObjId(sceneId, i);
                        local nClosing = GetFubenData_Param(sceneId, x700005_CSP_ISCLOSING )
                        if nClosing == 0 then
                            local oldsceneId = x700005_CancelMission(sceneId, humanId);
                            BeginQuestEvent(sceneId);
                                AddQuestText(sceneId, "����30����˳����䣡");
                            EndQuestEvent();
                            DispatchQuestTips(sceneId, humanId);
                        end
                    end

                    SetFubenData_Param(sceneId, x700005_CSP_ISCLOSING,1)
                end

                -- �˳�
                if bLeave == 1 then
                    SetFubenData_Param(sceneId, x700005_CSP_ISCLOSING,1)
                end
            end
        end
    end
end
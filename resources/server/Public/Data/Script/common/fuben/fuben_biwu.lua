--MisDescBegin
-------------------------
--***********************
--Const
--***********************
-------------------------

x700005_g_ScriptId              = 700005
x700005_g_MissionId             = 409

x700005_g_FuBenType             = 1

x700005_g_FubenName         = "比武"
x700005_g_Name                  = ""
x700005_g_FubenType         	= FUBEN_BIWULEITAI
x700005_g_TickTime              = 5             --回调脚本的时钟时间（单位：秒/次）
x700005_g_LimitTotalHoldTime    = 100   --副本可以存活的时间（单位：次数）,如果此时间到了，则任务将会失败
x700005_g_CloseTick             = 6             --副本关闭前倒计时（单位：次数）
x700005_g_NoUserTime            = 10            --副本中没有人后可以继续保存的时间（单位：秒）
x700005_g_Fuben_X1              = 46                --队伍1进入副本的位置X
x700005_g_Fuben_Z1              = 64                --队伍1进入副本的位置Z
x700005_g_Fuben_X2              = 82                --队伍2进入副本的位置X
x700005_g_Fuben_Z2              = 66                --队伍2进入副本的位置Z
x700005_g_Back_X                = 227                --源场景位置X
x700005_g_Back_Z                = 239.5               --源场景位置Z


x700005_g_MissionName           = "离开比武场"
x700005_g_MissionInfo           = "你确定要离开比武场吗？"

x700005_g_FuBenCreateOK             = "比武擂台创建成功！"
x700005_g_FuBenCreateFailed         = "比武擂台已达上限，请稍后再试！"
x700005_g_MissionAbandon            = "任务失败！"
x700005_g_CountDownMessage          = "你将在%d秒后离开比武擂台！"
x700005_g_SceneMapNavPath           = "fuben_biwuleitai/fuben_biwuleitai.nav"

--MisDescEnd

x700005_g_MissionNPCName            =   {
                                            {scene = 11, name = "苏菲"},        --新月
                                            {scene = 18, name = "苏菲"},        --金帐
                                            {scene = 21, name = "苏菲"},        --雪域
                                            {scene = 24, name = "苏菲"},        --大漠
                                            {scene = 36, name = "天衣居"}       --皇城
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

x700005_Skill_ID                    = 7602	--无敌BUFF_ID

x700005_wintalk                     =   "承认……承认……承认……承认……承认……"
x700005_losetalk                    =   "残念……残念……残念……残念……残念……"


function x700005_MakeFubenEx(sceneId, selfId, memberNum, targetId, memberNum2)

    --local str = format("MakeFubenEx Start");
    --PrintStr(str);

    local teamid = GetTeamId(sceneId, selfId)
    local teamid2 = GetTeamId(sceneId, targetId)

    local guid1 = ObjId2Guid( sceneId,selfId )
    local guid2 = ObjId2Guid( sceneId,targetId )


    if teamid ~=-1 and teamid2 ~=-1 and teamid == teamid2 then
        BeginQuestEvent(sceneId);
            AddQuestText(sceneId, "你和对方在同一队伍里，不能参加比武！");
        EndQuestEvent();
        DispatchQuestTips(sceneId, selfId);
        DispatchQuestTips(sceneId, targetId);
        return
    end

    local leaderguid = ObjId2Guid(sceneId, selfId);
    SetSceneLoad_Map(sceneId, x700005_g_SceneMapNavPath); --地图是必须选取的，而且必须在Config/SceneInfo.ini里配置好
    SetFubenData_TeamLeader(sceneId, leaderguid);
    SetFubenData_NoUserCloseTime(sceneId, x700005_g_NoUserTime * 1000);
    SetFubenData_Timer(sceneId, x700005_g_TickTime * 1000);
    SetFubenData_Param(sceneId, x700005_CSP_FUBENTYPE, x700005_g_FubenType);--设置副本数据，这里将0号索引的数据设置为999，用于表示副本号999(数字自定义)
    SetFubenData_Param(sceneId, x700005_CSP_SCRIPTID, x700005_g_ScriptId);--将1号数据设置为副本场景事件脚本号
    SetFubenData_Param(sceneId, x700005_CSP_TICKCOUNT, 0);--设置定时器调用次数
    SetFubenData_Param(sceneId, x700005_CSP_FROMSCENEID, sceneId);--设置副本入口场景号, 初始化
    SetFubenData_Param(sceneId, x700005_CSP_ISCLOSING, 0);--设置副本关闭标志, 0开放，1关闭
    SetFubenData_Param(sceneId, x700005_CSP_LEAVECOUNTDOWN, 0);--设置离开倒计时次数


    SetFubenData_Param(sceneId, x700005_CSP_TEAMID_1, guid1); --保存队伍号
    SetFubenData_Param(sceneId, x700005_CSP_TEAMID_2, guid2); --保存队伍号


    local bRetSceneID = CreateFuben(sceneId); --初始化完成后调用创建副本函数

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


    --弹出信息
    BeginQuestEvent(sceneId)
        Msg2Player(sceneId,killerId,"承认……承认……承认……承认……承认……",4,2)
        Msg2Player(sceneId,selfId,"残念……残念……残念……残念……残念……",4,2)
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

    SetFubenData_Param(destsceneId, x700005_CSP_FROMSCENEID, sceneId);--设置副本入口场景号

    local selfGuidID    = GetFubenData_Param(sceneId, x700005_CSP_TEAMID_1);
    local targetGuidID  = GetFubenData_Param(sceneId, x700005_CSP_TEAMID_2);

    local selfId = Guid2ObjId( sceneId,selfGuidID)
    local targetId = Guid2ObjId( sceneId,targetGuidID)

    local selfTeamID   = GetTeamId(sceneId, selfId)
    local targetTeamID = GetTeamId(sceneId, targetId)

    --比武发起方
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

    --接受方
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

--默认事件

--**********************************


function x700005_ProcEventEntry(sceneId, selfId, targetId)  --点击该任务后执行此脚本

    BeginQuestEvent(sceneId)
        AddQuestText(sceneId, x700005_g_MissionInfo)
    EndQuestEvent()
    DispatchQuestInfo(sceneId, selfId, targetId, x700005_g_ScriptId, x700005_g_MissionName)

end



--**********************************

--列举事件

--**********************************

function x700005_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

--  BeginQuestEvent(sceneId)
        AddQuestNumText(sceneId, x700005_g_ScriptId, x700005_g_MissionName)
--  EndQuestEvent()
--  DispatchQuestEventList(sceneId, selfId, targetId)

end



--**********************************

--检测接受条件

--**********************************

function x700005_ProcAcceptCheck(sceneId, selfId, targetId)
return 1
end


--**********************************

--检测查看条件

--**********************************

function x700005_CheckPushList(sceneId, selfId, targetId)

end

--**********************************

--接受

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

--放弃

--**********************************

function x700005_ProcQuestAbandon(sceneId, selfId, MissionId)


end



--**********************************

--检测是否可以提交

--**********************************

function x700005_CheckSubmit( sceneId, selfId, targetId)


end



--**********************************

--提交

--**********************************

function x700005_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)


end


--进入区域事件

--**********************************

function x700005_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x700005_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end

---------------------------------------------------------------------------------------------------
--取消任务
---------------------------------------------------------------------------------------------------
function x700005_CancelMission(sceneId, selfId)
end

--**********************************

--副本定时器

--**********************************
function x700005_OnFubenTimer( sceneId, nowTime )
    local nowTickCount = GetFubenData_Param(sceneId, x700005_CSP_TICKCOUNT) + 1;
    SetFubenData_Param(sceneId, x700005_CSP_TICKCOUNT, nowTickCount);


    local leaveFlag = GetFubenData_Param(sceneId, x700005_CSP_ISCLOSING);

    if leaveFlag > 0 then

        --提示xx秒后将退出副本
        local leaveCountDown = GetFubenData_Param(sceneId, x700005_CSP_LEAVECOUNTDOWN) + 1;
        SetFubenData_Param(sceneId, x700005_CSP_LEAVECOUNTDOWN, leaveCountDown);

        if leaveCountDown == x700005_g_CloseTick then
            local oldsceneId = GetFubenData_Param(sceneId, x700005_CSP_FROMSCENEID);
            local humancount = GetFuben_PlayerCount(sceneId);
            for i = 0, humancount - 1 do
                local humanId = GetFuben_PlayerObjId(sceneId, i);
                RelivePlayerNM( sceneId,humanId,2) --复活一下
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

                -- 检查队伍信息是否相同
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

                -- 同一队伍里
                if bSameTeam == 1 then

                    if bNotInTeam == 1 then
                        bLeave = 0
                    end
                else
                    bLeave = 0
                end

                -- 检查是否过了场景的生存期
                if nowTickCount == x700005_g_LimitTotalHoldTime then
                    for i = 0, humancount - 1 do

                        local humanId = GetFuben_PlayerObjId(sceneId, i);
                        local nClosing = GetFubenData_Param(sceneId, x700005_CSP_ISCLOSING )
                        if nClosing == 0 then
                            local oldsceneId = x700005_CancelMission(sceneId, humanId);
                            BeginQuestEvent(sceneId);
                                AddQuestText(sceneId, "将在30秒后退出比武！");
                            EndQuestEvent();
                            DispatchQuestTips(sceneId, humanId);
                        end
                    end

                    SetFubenData_Param(sceneId, x700005_CSP_ISCLOSING,1)
                end

                -- 退出
                if bLeave == 1 then
                    SetFubenData_Param(sceneId, x700005_CSP_ISCLOSING,1)
                end
            end
        end
    end
end
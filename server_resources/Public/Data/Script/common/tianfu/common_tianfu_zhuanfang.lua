--脚本号
x300986_g_ScriptId  = 300986
-- Game open id
x300986_g_OpenID    = 1059

--**********************************
--任务入口函数
--**********************************
function x300986_ProcEventEntry( sceneId, selfId, NPCId)	--点击该任务后执行此脚本
    if GetInherenceLevel( sceneId, selfId) < 50 then
        Msg2Player( sceneId, selfId, "您的天赋等级小于50级，不能进行此操作", 8, 3)
        return
    end

    if GetGameOpenById( x300986_g_OpenID) <= 0 then
        return 0
    end

    BeginUICommand( sceneId)
        UICommand_AddInt( sceneId, NPCId)
        DispatchUICommand( sceneId, selfId, 109)
    EndUICommand( sceneId)
end

--**********************************
--列举事件
--**********************************
function x300986_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    if GetGameOpenById( x300986_g_OpenID) <= 0 then
        return 0
    end

    AddQuestNumText( sceneId, x300986_g_ScriptId, "专精天赋专防训练", 3, 1)
end


--**********************************
--检测接受条件
--**********************************
function x300986_ProcAcceptCheck( sceneId, selfId, NPCId)
end

--**********************************
--接受
--**********************************
function x300986_ProcAccept( sceneId, selfId)
end


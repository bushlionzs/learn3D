
--MisDescBegin
--脚本号
x550530_g_ScriptId = 550530
--任务文本描述
x550530_g_MissionName="国王战场传送"
--MisDescEnd




function x550530_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
    BeginQuestEvent(sceneId)
    AddQuestText(sceneId,"\t我可以送你#G离开战场#W，一旦离开，你在本次争夺战中#G无法再次进入#W。\n \n你确定要#G放弃#W并#G离开战场#W吗？")
    EndQuestEvent(sceneId)
    DispatchQuestInfo(sceneId,selfId,targetId,x550530_g_ScriptId,-1)
    AddQuestNumText(sceneId,x550530_g_ScriptId,"离开战场",3,2)
end


function x550530_ProcEventEntry( sceneId, selfId, targetId,idScript,idExt )

    BeginQuestEvent(sceneId)
    AddQuestText(sceneId,"一旦离开战场将不能再次进入，您确定要离开吗？")
    EndQuestEvent(sceneId)
    DispatchQuestInfo(sceneId,selfId,targetId,x550530_g_ScriptId,-1)
    return 1
end

--********************
--检测接受条件
--**********************************
function x550530_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

--**********************************
--接受
--**********************************
function x550530_ProcAccept( sceneId, selfId )
    CallScriptFunction( KINGBATTLE_FLOW_SCRIPT,"OnPlayerLeave",sceneId, selfId)
    CallScriptFunction( KINGBATTLE_FLOW_SCRIPT,"KingBattleKickPlayer",sceneId,selfId)
end

--**********************************
--放弃
--**********************************
function x550530_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--继续
--**********************************
function x550530_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--检测是否可以提交
--**********************************
function x550530_CheckSubmit( sceneId, selfId )
end

--**********************************
--提交
--**********************************
function x550530_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end


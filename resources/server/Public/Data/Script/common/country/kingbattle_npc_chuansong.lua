
--MisDescBegin
--�ű���
x550530_g_ScriptId = 550530
--�����ı�����
x550530_g_MissionName="����ս������"
--MisDescEnd




function x550530_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
    BeginQuestEvent(sceneId)
    AddQuestText(sceneId,"\t�ҿ�������#G�뿪ս��#W��һ���뿪�����ڱ�������ս��#G�޷��ٴν���#W��\n \n��ȷ��Ҫ#G����#W��#G�뿪ս��#W��")
    EndQuestEvent(sceneId)
    DispatchQuestInfo(sceneId,selfId,targetId,x550530_g_ScriptId,-1)
    AddQuestNumText(sceneId,x550530_g_ScriptId,"�뿪ս��",3,2)
end


function x550530_ProcEventEntry( sceneId, selfId, targetId,idScript,idExt )

    BeginQuestEvent(sceneId)
    AddQuestText(sceneId,"һ���뿪ս���������ٴν��룬��ȷ��Ҫ�뿪��")
    EndQuestEvent(sceneId)
    DispatchQuestInfo(sceneId,selfId,targetId,x550530_g_ScriptId,-1)
    return 1
end

--********************
--����������
--**********************************
function x550530_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

--**********************************
--����
--**********************************
function x550530_ProcAccept( sceneId, selfId )
    CallScriptFunction( KINGBATTLE_FLOW_SCRIPT,"OnPlayerLeave",sceneId, selfId)
    CallScriptFunction( KINGBATTLE_FLOW_SCRIPT,"KingBattleKickPlayer",sceneId,selfId)
end

--**********************************
--����
--**********************************
function x550530_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--����
--**********************************
function x550530_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--����Ƿ�����ύ
--**********************************
function x550530_CheckSubmit( sceneId, selfId )
end

--**********************************
--�ύ
--**********************************
function x550530_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end


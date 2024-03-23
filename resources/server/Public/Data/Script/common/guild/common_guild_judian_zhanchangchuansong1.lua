
--MisDescBegin
--�ű���
x300934_g_ScriptId = 300934
x300934_g_MissionName="ǰ�ߴ���"

x300934_g_ChuanSong_X = 50
x300934_g_ChuanSong_Z = 125



function x300934_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	local npcId = GetMonsterGUID( sceneId, targetId)
    --ս��δ����
	if npcId == 170032 then
		AddQuestNumText(sceneId,x300934_g_ScriptId,"�뿪ս��",3,2)
	end
    --����A��Ӫ������Ч
    local nGuildA,nGuildB = CallScriptFunction(300918,"GetMatchGuild",sceneId)
    if nGuildA == -1 and nGuildB == -1 then
    	return
    end
    
    local nGuildId = GetGuildID( sceneId,selfId )

    --������ս���е���Ӫ����
	if npcId == 170028 then
		if nGuildId == nGuildB or CallScriptFunction(300918,"IsPlayerAidB",sceneId,selfId) == 1 then
			 AddQuestNumText(sceneId,x300934_g_ScriptId,"ǰ�ߴ���",14,1)
		end
	end
	
	if npcId == 170029 then
		if nGuildId == nGuildB or CallScriptFunction(300918,"IsPlayerAidB",sceneId,selfId) == 1 then
			 AddQuestNumText(sceneId,x300934_g_ScriptId,"��Ԯ����",14,3)
		end
	end
end


function x300934_ProcEventEntry( sceneId, selfId, targetId,idScript,idExt )

	if idExt == 1 then
		
		--����A��Ӫ������Ч
	    local nGuildA,nGuildB = CallScriptFunction(300918,"GetMatchGuild",sceneId)
	    if nGuildA == -1 and nGuildB == -1 then
	    	return
	    end
	    
	    local TimeCount = CallScriptFunction(300918,"GetCountTime",sceneId)
	    if TimeCount > 29 * 60 then
	    	BeginQuestEvent(sceneId)
	        AddQuestText(sceneId,"ս����û��ʼ���޷�����")
	        EndQuestEvent(sceneId)
	        DispatchQuestEventList(sceneId,selfId,targetId)
	        return 0
	    end
	    
	    local nGuildId = GetGuildID( sceneId,selfId )
	
	    --������ս���е���Ӫ����
	    if nGuildId == nGuildB or CallScriptFunction(300918,"IsPlayerAidB",sceneId,selfId) == 1 then
	        SetPos(sceneId,selfId,44,202)
	    end
    
	elseif idExt == 2 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"�����Ҫ�뿪ս����")
        EndQuestEvent(sceneId)
        DispatchQuestInfo(sceneId,selfId,targetId,x300934_g_ScriptId,-1)
		  return 1
    end
	
	if idExt == 3 then
		local npcId = GetMonsterGUID( sceneId, targetId)
		local nGuildA,nGuildB = CallScriptFunction(300918,"GetMatchGuild",sceneId)
	    if nGuildA == -1 and nGuildB == -1 then
	    	return
	    end
		
		local nGuildId = GetGuildID( sceneId,selfId )
		if npcId == 170029 then
			if nGuildId == nGuildB or CallScriptFunction(300918,"IsPlayerAidB",sceneId,selfId) == 1 then
				SetPos(sceneId,selfId,193,177)
			end
		end
	end
end

--********************
--����������
--**********************************
function x300934_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x300934_ProcAccept( sceneId, selfId )
	CallScriptFunction(300918,"LairdBattleKickPlayer",sceneId,selfId)
end

--**********************************
--����
--**********************************
function x300934_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--����
--**********************************
function x300934_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300934_CheckSubmit( sceneId, selfId )
end

--**********************************
--�ύ
--**********************************
function x300934_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end


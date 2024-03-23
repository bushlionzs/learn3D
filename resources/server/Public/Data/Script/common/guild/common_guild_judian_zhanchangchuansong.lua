
--MisDescBegin
--脚本号
x300933_g_ScriptId = 300933
x300933_g_MissionName="前线传送"

x300933_g_ChuanSong_X = 205
x300933_g_ChuanSong_Z = 125



function x300933_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
    --战场未开放
	local npcId = GetMonsterGUID( sceneId, targetId)
	if npcId == 170033 then
		AddQuestNumText(sceneId,x300933_g_ScriptId,"离开战场",3,2)
	end

    --仅对A阵营的人有效
    local nGuildA,nGuildB = CallScriptFunction(300918,"GetMatchGuild",sceneId)
    if nGuildA == -1 and nGuildB == -1 then
    	return
    end
    
    local nGuildId = GetGuildID( sceneId,selfId )
    --设置在战场中的阵营属性
	if npcId == 170030 then
		if nGuildId == nGuildA or CallScriptFunction(300918,"IsPlayerAidA",sceneId,selfId) == 1 then
			 AddQuestNumText(sceneId,x300933_g_ScriptId,"前线传送",14,1)
		end
	end
	
	if npcId == 170031 then
		if nGuildId == nGuildA or CallScriptFunction(300918,"IsPlayerAidA",sceneId,selfId) == 1 then
			 AddQuestNumText(sceneId,x300933_g_ScriptId,"回援本阵",14,3)
		end
	end
end


function x300933_ProcEventEntry( sceneId, selfId, targetId,idScript,idExt )
	if idExt == 1 then
		--仅对A阵营的人有效
	    local nGuildA,nGuildB = CallScriptFunction(300918,"GetMatchGuild",sceneId)
	    if nGuildA == -1 and nGuildB == -1 then
	    	return
	    end
	    local TimeCount = CallScriptFunction(300918,"GetCountTime",sceneId)
	    if TimeCount > 29 * 60 then
	    	BeginQuestEvent(sceneId)
	        AddQuestText(sceneId,"战斗还没开始，无法传送")
	        EndQuestEvent(sceneId)
	        DispatchQuestEventList(sceneId,selfId,targetId)
	        return 0
	    end
	    local nGuildId = GetGuildID( sceneId,selfId )
	
	    --设置在战场中的阵营属性
	    if nGuildId == nGuildA  or CallScriptFunction(300918,"IsPlayerAidA",sceneId,selfId) == 1 then
	        SetPos(sceneId,selfId,190,50)
	    end
	elseif idExt == 2 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"你真的要离开战场吗？")
        EndQuestEvent(sceneId)
        DispatchQuestInfo(sceneId,selfId,targetId,x300933_g_ScriptId,-1)
		return 1
    end
	if idExt == 3 then
		local npcId = GetMonsterGUID( sceneId, targetId)
		local nGuildA,nGuildB = CallScriptFunction(300918,"GetMatchGuild",sceneId)
	    if nGuildA == -1 and nGuildB == -1 then
	    	return
	    end
		
		local nGuildId = GetGuildID( sceneId,selfId )
		if npcId == 170031 then
			if nGuildId == nGuildA  or CallScriptFunction(300918,"IsPlayerAidA",sceneId,selfId) == 1 then
				SetPos(sceneId,selfId,55,73)
			end
		end
	end
end

--********************
--检测接受条件
--**********************************
function x300933_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x300933_ProcAccept( sceneId, selfId )
	CallScriptFunction(300918,"LairdBattleKickPlayer",sceneId,selfId)
end

--**********************************
--放弃
--**********************************
function x300933_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--继续
--**********************************
function x300933_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--检测是否可以提交
--**********************************
function x300933_CheckSubmit( sceneId, selfId )
end

--**********************************
--提交
--**********************************
function x300933_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end


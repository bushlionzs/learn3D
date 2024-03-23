--据点战场帮主召集脚本
--MisDescBegin
--脚本号
x300938_g_ScriptId = 300938
x300938_g_MissionName="领主战场召集"
x300938_g_MissionDesc="\t使用此功能，会消耗50点战场积分，可以将本战场内的本帮成员传送至此。您确定要使用积分换取此次召集吗？"
x300938_g_MissionSuccess="消耗50点战场积分，您成功的使用了领主战场召集！"
x300938_g_MissionScoreNotEnough="很抱歉，您的帮会战场积分不足50点,无法召集！"

x300938_g_Guild_Camp_A= 5
x300938_g_Guild_Camp_B= 6

x300938_g_Leader_Index= 5

x300938_g_CostScore   = 50

function x300938_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local nNpcCamp  = GetMonsterCamp(sceneId,targetId)
	local nSelfCamp = GetCurCamp(sceneId,selfId)
	
	--阵营不匹配
	if nNpcCamp ~= nSelfCamp then
		return
	end
	
	--不是帮主
	local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= x300938_g_Leader_Index then
		return
	end
	
	--检查配对帮会
	local nGuildA,nGuildB = CallScriptFunction(300918,"GetMatchGuild",sceneId)
    if nGuildA == -1 and nGuildB == -1 then
    	return
    end
    
    --只能是A帮会或B帮会的帮主使用
    if GetGuildID(sceneId,selfId) ~= nGuildA and GetGuildID(sceneId,selfId) ~= nGuildB then
    	return
    end

	AddQuestNumText(sceneId,x300938_g_ScriptId,x300938_g_MissionName,3,0)

end


function x300938_ProcEventEntry( sceneId, selfId, targetId,idScript,idExt )

	local nNpcCamp  = GetMonsterCamp(sceneId,targetId)
	local nSelfCamp = GetCurCamp(sceneId,selfId)
	
	--阵营不匹配
	if nNpcCamp ~= nSelfCamp then
		return
	end
	
	--不是帮主
	local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= x300938_g_Leader_Index then
		return
	end
	
	--检查配对帮会
	local nGuildA,nGuildB = CallScriptFunction(300918,"GetMatchGuild",sceneId)
    if nGuildA == -1 and nGuildB == -1 then
    	return
    end
    
    --只能是A帮会或B帮会的帮主使用
    if GetGuildID(sceneId,selfId) ~= nGuildA and GetGuildID(sceneId,selfId) ~= nGuildB then
    	return
    end
	
	if idExt == 0 then
	
		BeginQuestEvent(sceneId)
	    AddQuestText(sceneId, x300938_g_MissionDesc);
	    AddQuestNumText(sceneId,x300938_g_ScriptId,"确定..",3,1);
	    EndQuestEvent(sceneId)
	    DispatchQuestEventList(sceneId,selfId,targetId)
	    
	elseif idExt == 1 then
		
		--根据阵营不同,选择不同处理
		if nNpcCamp == x300938_g_Guild_Camp_A then
		
			--检查积分是否足够
			local nScore = CallScriptFunction(300918,"GetBattleScoreA",sceneId)
			if nScore < x300938_g_CostScore then
				BeginQuestEvent(sceneId)
			    AddQuestText(sceneId, x300938_g_MissionScoreNotEnough);
			    EndQuestEvent(sceneId)
			    DispatchQuestEventList(sceneId,selfId,targetId)
			    return
			end
			
			
			--扣除积分
			nScore = nScore - x300938_g_CostScore
			CallScriptFunction(300918,"SetBattleScoreA",sceneId,nScore)
		
			--执行召集
			CallScriptFunction(300918,"TransGuildMemberToAround",sceneId,selfId,nNpcCamp,58,186)
		elseif nNpcCamp == x300938_g_Guild_Camp_B then
		
			--检查积分是否足够
			local nScore = CallScriptFunction(300918,"GetBattleScoreB",sceneId)
			if nScore < x300938_g_CostScore then
				BeginQuestEvent(sceneId)
			    AddQuestText(sceneId, x300938_g_MissionScoreNotEnough);
			    EndQuestEvent(sceneId)
			    DispatchQuestEventList(sceneId,selfId,targetId)
			    return
			end
			
			
			--扣除积分
			nScore = nScore - x300938_g_CostScore
			CallScriptFunction(300918,"SetBattleScoreB",sceneId,nScore)
		
			--执行召集
			CallScriptFunction(300918,"TransGuildMemberToAround",sceneId,selfId,nNpcCamp,212,96)
		end
		
		
		--成功提示
		BeginQuestEvent(sceneId)
	    AddQuestText(sceneId, x300938_g_MissionSuccess);
	    EndQuestEvent(sceneId)
	    DispatchQuestEventList(sceneId,selfId,targetId)

	end
end

--********************
--检测接受条件
--**********************************
function x300938_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x300938_ProcAccept( sceneId, selfId )
end

--**********************************
--放弃
--**********************************
function x300938_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--继续
--**********************************
function x300938_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--检测是否可以提交
--**********************************
function x300938_CheckSubmit( sceneId, selfId )
end

--**********************************
--提交
--**********************************
function x300938_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end


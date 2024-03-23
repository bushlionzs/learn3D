--�ݵ�ս�������ټ��ű�
--MisDescBegin
--�ű���
x300938_g_ScriptId = 300938
x300938_g_MissionName="����ս���ټ�"
x300938_g_MissionDesc="\tʹ�ô˹��ܣ�������50��ս�����֣����Խ���ս���ڵı����Ա�������ˡ���ȷ��Ҫʹ�û��ֻ�ȡ�˴��ټ���"
x300938_g_MissionSuccess="����50��ս�����֣����ɹ���ʹ��������ս���ټ���"
x300938_g_MissionScoreNotEnough="�ܱ�Ǹ�����İ��ս�����ֲ���50��,�޷��ټ���"

x300938_g_Guild_Camp_A= 5
x300938_g_Guild_Camp_B= 6

x300938_g_Leader_Index= 5

x300938_g_CostScore   = 50

function x300938_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local nNpcCamp  = GetMonsterCamp(sceneId,targetId)
	local nSelfCamp = GetCurCamp(sceneId,selfId)
	
	--��Ӫ��ƥ��
	if nNpcCamp ~= nSelfCamp then
		return
	end
	
	--���ǰ���
	local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= x300938_g_Leader_Index then
		return
	end
	
	--�����԰��
	local nGuildA,nGuildB = CallScriptFunction(300918,"GetMatchGuild",sceneId)
    if nGuildA == -1 and nGuildB == -1 then
    	return
    end
    
    --ֻ����A����B���İ���ʹ��
    if GetGuildID(sceneId,selfId) ~= nGuildA and GetGuildID(sceneId,selfId) ~= nGuildB then
    	return
    end

	AddQuestNumText(sceneId,x300938_g_ScriptId,x300938_g_MissionName,3,0)

end


function x300938_ProcEventEntry( sceneId, selfId, targetId,idScript,idExt )

	local nNpcCamp  = GetMonsterCamp(sceneId,targetId)
	local nSelfCamp = GetCurCamp(sceneId,selfId)
	
	--��Ӫ��ƥ��
	if nNpcCamp ~= nSelfCamp then
		return
	end
	
	--���ǰ���
	local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= x300938_g_Leader_Index then
		return
	end
	
	--�����԰��
	local nGuildA,nGuildB = CallScriptFunction(300918,"GetMatchGuild",sceneId)
    if nGuildA == -1 and nGuildB == -1 then
    	return
    end
    
    --ֻ����A����B���İ���ʹ��
    if GetGuildID(sceneId,selfId) ~= nGuildA and GetGuildID(sceneId,selfId) ~= nGuildB then
    	return
    end
	
	if idExt == 0 then
	
		BeginQuestEvent(sceneId)
	    AddQuestText(sceneId, x300938_g_MissionDesc);
	    AddQuestNumText(sceneId,x300938_g_ScriptId,"ȷ��..",3,1);
	    EndQuestEvent(sceneId)
	    DispatchQuestEventList(sceneId,selfId,targetId)
	    
	elseif idExt == 1 then
		
		--������Ӫ��ͬ,ѡ��ͬ����
		if nNpcCamp == x300938_g_Guild_Camp_A then
		
			--�������Ƿ��㹻
			local nScore = CallScriptFunction(300918,"GetBattleScoreA",sceneId)
			if nScore < x300938_g_CostScore then
				BeginQuestEvent(sceneId)
			    AddQuestText(sceneId, x300938_g_MissionScoreNotEnough);
			    EndQuestEvent(sceneId)
			    DispatchQuestEventList(sceneId,selfId,targetId)
			    return
			end
			
			
			--�۳�����
			nScore = nScore - x300938_g_CostScore
			CallScriptFunction(300918,"SetBattleScoreA",sceneId,nScore)
		
			--ִ���ټ�
			CallScriptFunction(300918,"TransGuildMemberToAround",sceneId,selfId,nNpcCamp,58,186)
		elseif nNpcCamp == x300938_g_Guild_Camp_B then
		
			--�������Ƿ��㹻
			local nScore = CallScriptFunction(300918,"GetBattleScoreB",sceneId)
			if nScore < x300938_g_CostScore then
				BeginQuestEvent(sceneId)
			    AddQuestText(sceneId, x300938_g_MissionScoreNotEnough);
			    EndQuestEvent(sceneId)
			    DispatchQuestEventList(sceneId,selfId,targetId)
			    return
			end
			
			
			--�۳�����
			nScore = nScore - x300938_g_CostScore
			CallScriptFunction(300918,"SetBattleScoreB",sceneId,nScore)
		
			--ִ���ټ�
			CallScriptFunction(300918,"TransGuildMemberToAround",sceneId,selfId,nNpcCamp,212,96)
		end
		
		
		--�ɹ���ʾ
		BeginQuestEvent(sceneId)
	    AddQuestText(sceneId, x300938_g_MissionSuccess);
	    EndQuestEvent(sceneId)
	    DispatchQuestEventList(sceneId,selfId,targetId)

	end
end

--********************
--����������
--**********************************
function x300938_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x300938_ProcAccept( sceneId, selfId )
end

--**********************************
--����
--**********************************
function x300938_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--����
--**********************************
function x300938_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300938_CheckSubmit( sceneId, selfId )
end

--**********************************
--�ύ
--**********************************
function x300938_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end


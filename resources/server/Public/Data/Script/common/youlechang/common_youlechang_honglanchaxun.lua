

--MisDescBegin
x310321_g_ScriptId = 310321
x310321_g_MissionId = 9045

x310321_g_MissionName="�����ˡ���������ս"


x310321_g_HongNpc 		= 145002
x310321_g_HongName		="��Ҫ֧�ֱ��죡"
x310321_g_HongChaxun	="��ѯ֧�ֱ��������"
x310321_g_HongBuff		= 7536

x310321_g_LanNpc 		= 145001
x310321_g_LanName		="��Ҫ֧�ֱ�����"
x310321_g_LanChaxun		="��ѯ֧�ֱ���������"
x310321_g_LanBuff		= 7537

x310321_g_MainScriptId	=	310320

--MisDescEnd
--**********************************
x310321_g_HongNum	= 0
x310321_g_LanNum	= 0
x310321_g_MinLevel	= 65


function x310321_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


--CancelSpecificImpact( sceneId, selfId, x310321_g_LanBuff)
--CancelSpecificImpact( sceneId, selfId, x310321_g_HongBuff)
	local npcGuid = GetMonsterGUID(sceneId, NPCId)
	
	if IsHaveQuest(sceneId,selfId, x310321_g_MissionId) > 0 and  IsQuestHaveDone(sceneId, selfId, x310321_g_MissionId) < 1 then
		if npcGuid == x310321_g_HongNpc then
			AddQuestNumText( sceneId, x310321_g_ScriptId, x310321_g_HongName, 3, 0 )
			AddQuestNumText( sceneId, x310321_g_ScriptId, x310321_g_HongChaxun, 3, 1 )
		else
			AddQuestNumText( sceneId, x310321_g_ScriptId,  x310321_g_LanName, 3, 2 )
			AddQuestNumText( sceneId, x310321_g_ScriptId,  x310321_g_LanChaxun, 3, 3 )
		end
	else
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"\t�㻹û�н�ȡ�����ˡ���������ս����")
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,NPCId)
	end
	
end

function x310321_ProcQuestAttach( sceneId, selfId, NPCId, npcGuid, misIndex, MissionId)
	--print("x310321_ProcQuestAttach")
end

function x310321_ProcEventEntry(sceneId ,selfId, NPCId,idScript,idExt )	
	--print("x310321_ProcEventEntry", idExt)
	
	if IsHaveQuest(sceneId,selfId, x310321_g_MissionId) < 1 then
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"\t�㻹û�н�ȡ�����ˡ���������ս����")
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,NPCId)
		return
	end
	local misIndex = GetQuestIndexByID( sceneId, selfId, x310321_g_MissionId)
	--if IsQuestHaveDone(sceneId, selfId, x310321_g_MissionId) > 0 then
	if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"������ɴ�����")
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,NPCId)
		return
	end	
--	local state = CallScriptFunction(x310321_g_MainScriptId,"GetHonglanState",sceneId,selfId)
--	if state ~= 1 then
--		BeginQuestEvent(sceneId)
--        AddQuestText(sceneId,"��������ʱ����")
--        EndQuestEvent(sceneId)
--        DispatchQuestEventList(sceneId,selfId,NPCId)
--		return
--	end		
		
	if idExt == 0 then
		if IsHaveSpecificImpact( sceneId, selfId, x310321_g_HongBuff) == 1 then
			BeginQuestEvent(sceneId)
        	AddQuestText(sceneId,"\t��ղ��Ѿ�ѡ��֧�ֱ����ˡ������ȥ��������ı����ѡ��")
        	EndQuestEvent(sceneId)
        	DispatchQuestEventList(sceneId,selfId,NPCId)
        	return
        	
        	
		elseif IsHaveSpecificImpact( sceneId, selfId, x310321_g_LanBuff) == 1 then
			CancelSpecificImpact( sceneId, selfId, x310321_g_LanBuff)
			
			CallScriptFunction(x310321_g_MainScriptId,"SetLanNumInc",sceneId,selfId, -1)
			
      	end
      	local ret = SendSpecificImpactToUnit(sceneId ,selfId,selfId,selfId,x310321_g_HongBuff, 0)
      	
      	ReCallHorse( sceneId, selfId)
		CallScriptFunction(x310321_g_MainScriptId,"SetHongNumInc",sceneId,selfId, 1)
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"\t�����֧�ֱ��죬Ϊ�˱������л�⣬���콫����������ģ��......")
        EndQuestEvent(sceneId)

        DispatchQuestEventList(sceneId,selfId,NPCId)
        
        
	elseif idExt == 1 then
	    if IsHaveSpecificImpact( sceneId, selfId, x310321_g_HongBuff) == 1 or IsHaveSpecificImpact( sceneId, selfId, x310321_g_LanBuff) == 1 then
		    local num = CallScriptFunction(x310321_g_MainScriptId,"GetHongNum",sceneId,selfId)
		    BeginQuestEvent(sceneId)
            AddQuestText(sceneId,format("\t����ͳ�ƣ�Ŀǰ������%dλ֧���ߡ�", num))
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,NPCId)
        else
            Msg2Player(sceneId, selfId, "ֻ����֧����ĳλ����֮����ܲ�ѯ֧������", 0, 2)
		    Msg2Player(sceneId, selfId, "ֻ����֧����ĳλ����֮����ܲ�ѯ֧������", 0, 3)
		end    
        --DispatchQuestTips(sceneId,selfId)
        
        
	elseif idExt == 2 then
		local s = IsHaveSpecificImpact( sceneId, selfId, x310321_g_LanBuff )
		--print(s)
		if IsHaveSpecificImpact( sceneId, selfId, x310321_g_LanBuff) == 1 then
			BeginQuestEvent(sceneId)
        	AddQuestText(sceneId,"\t��ղ��Ѿ�ѡ��֧�ֱ����ˡ������ȥ��������ı����ѡ��")
        	EndQuestEvent(sceneId)
        	DispatchQuestEventList(sceneId,selfId,NPCId)
        	return
		elseif IsHaveSpecificImpact( sceneId, selfId, x310321_g_HongBuff) == 1 then
			CancelSpecificImpact( sceneId, selfId, x310321_g_HongBuff)
			
			CallScriptFunction(x310321_g_MainScriptId,"SetHongNumInc",sceneId,selfId, -1)
        end
		
		local ret = SendSpecificImpactToUnit(sceneId ,selfId,selfId,selfId,x310321_g_LanBuff, 0)
		
		ReCallHorse( sceneId, selfId)
		
		local num1 = CallScriptFunction(x310321_g_MainScriptId,"SetLanNumInc",sceneId,selfId, 1)
		local num =  CallScriptFunction(x310321_g_MainScriptId,"GetLanNum",sceneId,selfId)	
		--print("num",num1,num)
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"\t�����֧�ֱ�����Ϊ�˱������л�⣬����������������ģ��......")
        EndQuestEvent(sceneId)
       	DispatchQuestEventList(sceneId,selfId,NPCId)
        
	elseif idExt == 3 then
	   if IsHaveSpecificImpact( sceneId, selfId, x310321_g_HongBuff) == 1 or IsHaveSpecificImpact( sceneId, selfId, x310321_g_LanBuff) == 1 then
		local num =  CallScriptFunction(x310321_g_MainScriptId,"GetLanNum",sceneId,selfId)	
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId,format("\t����ͳ�ƣ�Ŀǰ������%dλ֧���ߡ�", num))
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,NPCId)
        --DispatchQuestTips(sceneId,selfId)
       else
        Msg2Player(sceneId, selfId, "ֻ����֧����ĳλ����֮����ܲ�ѯ֧������", 0, 2)
		Msg2Player(sceneId, selfId, "ֻ����֧����ĳλ����֮����ܲ�ѯ֧������", 0, 3)
	   end   
	end
end	


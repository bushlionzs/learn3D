x920001_g_ScriptId = 920001

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x920001_g_MissionName="�ƾ�22"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x920001_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
		QuizAsk(sceneId, selfId, 1, 20, 20); 
end

--**********************************
--�о��¼�
--**********************************
function x920001_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x920001_g_ScriptId,x920001_g_MissionName);
end


--********************
--����������
--**********************************
function x920001_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x920001_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x920001_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x920001_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x920001_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x920001_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x920001_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x920001_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x920001_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

--�����
function x920001_OnAnswer( sceneId, selfId, nStepIndex, questIndex, answerIndex)
		local nCount;
		local nCode;
		--������
		--print( "x920001_OnAnswer1111")
		nCode = QuizCheck(sceneId, questIndex, answerIndex);
		--print( "x920001_OnAnswer222"..nCode)
		--�õ���Ի������
		if (nCode == 0) then
		--print( "x920001_OnAnswer333")
				nCount = GetQuizWrongCount(sceneId, selfId);
				nCount = nCount + 1;
				SetQuizWrongCount( sceneId, selfId, nCount);
		elseif (nCode == 1) then
		--print( "x920001_OnAnswer444")
				nCount = GetQuizRightCount(sceneId, selfId);
				nCount = nCount + 1;
				SetQuizRightCount( sceneId, selfId, nCount);
		end
		--���ͻ��˻ش����
		--print( "x920001_OnAnswer5555")
		QuizResult(sceneId, selfId, nStepIndex, nCode, nCount);
		nStepIndex = nStepIndex + 1;
		if nStepIndex <= 20 then
			QuizAsk(sceneId, selfId, nStepIndex, 20, 20);
		end
		--print( "x920001_OnAnswer666")
end
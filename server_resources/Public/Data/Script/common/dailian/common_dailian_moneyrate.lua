--����֮��Ǯ����

--MisDescBegin
--�ű���
x800026_g_ScriptId = 800026
--MisDescEnd




function x800026_SubTrainMoneyRate( sceneId, level, attack, mode, constant )	--����������ִ�д˽ű�
	local mode = mode/10
	local Money
	if level < 10 then
		Money = ceil(level*attack*mode)
	else
		Money = ceil(level*level*attack*mode/10)
	end
	
	if Money > 0 then
		return Money
	else
		return 0
	end
end




--**********************************
--������ں���
--**********************************
function x800026_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800026_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800026_g_ScriptId,"����");
end


--********************
--����������
--**********************************
function x800026_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800026_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800026_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800026_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800026_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800026_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800026_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800026_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800026_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

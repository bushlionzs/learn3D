--����֮����Ч��

--MisDescBegin
--�ű���
x800025_g_ScriptId = 800025
--MisDescEnd


function x800025_SubTrainExpRate( sceneId, level, attack, mode, constant )	--����������ִ�д˽ű�
	local mode = mode/10
	local Exp
	if level < 10 then
		Exp = ceil(level*attack*mode*2)
	else
		Exp = ceil(level*level*attack*mode/5)
	end
	
	if Exp > 0 then
		return Exp
	else
		return 0
	end
end





--**********************************
--������ں���
--**********************************
function x800025_ProcEventEntry( sceneId, selfId, targetId )	

end

--**********************************
--�о��¼�
--**********************************
function x800025_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

end


--********************
--����������
--**********************************
function x800025_ProcAcceptCheck( sceneId, selfId, NPCId )

end

--**********************************
--����
--**********************************
function x800025_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800025_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800025_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800025_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800025_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800025_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800025_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800025_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

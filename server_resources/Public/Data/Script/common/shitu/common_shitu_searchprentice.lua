--�������
--MisDescBegin
--�ű���
x800040_g_ScriptId = 800040

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800040_g_MissionName="��ʦͽ������ͽ��"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800040_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800040_g_ScriptId,x800040_g_MissionName,3,0);
end

function x800040_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	local Readme_1 = "#Y��ʦͽ������ͽ��#r"
	local Readme_2 = "\t#W������ͨ���ҵİ����ҵ������ɵ�ͽ�ܣ��ɹ����ʦͽ��ϵ����δ�����������÷��Ľ�����#r\t���Ƿ�Ҫ#G����ͽ��#W��"
	local Readme = Readme_1..Readme_2
	BeginQuestEvent(sceneId);AddQuestText(sceneId, Readme);EndQuestEvent();DispatchQuestInfo(sceneId, selfId, targetId, x800040_g_ScriptId,-1);
end

--**********************************
--�о��¼�
--**********************************



--********************
--����������
--**********************************
function x800040_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800040_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800040_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--����
--**********************************
function x800040_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800040_CheckSubmit( sceneId, selfId )
end

--**********************************
--�ύ
--**********************************
function x800040_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

--**********************************
--ɱ����������
--**********************************
function x800040_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

--**********************************
--���������¼�
--**********************************
function x800040_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800040_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

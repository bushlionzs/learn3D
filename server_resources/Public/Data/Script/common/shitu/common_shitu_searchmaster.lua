--�������
--MisDescBegin
--�ű���
x800039_g_ScriptId = 800039

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800039_g_MissionName="��ʦͽ������ʦ��"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800039_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800039_g_ScriptId,x800039_g_MissionName,3,0);
end

function x800039_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	local Readme_1 = "#Y��ʦͽ������ʦ��#r"
	local Readme_2 = "\t#W������ͨ���ҵİ����ҵ������ǵ�ʦ�����ɹ����ʦͽ��ϵ����δ�����������÷��Ľ�����#r\t���Ƿ�Ҫ#G����ʦ��#W��"
	local Readme = Readme_1..Readme_2
	BeginQuestEvent(sceneId);AddQuestText(sceneId, Readme);EndQuestEvent();DispatchQuestInfo(sceneId, selfId, targetId, x800039_g_ScriptId,-1);
end

--**********************************
--�о��¼�
--**********************************



--********************
--����������
--**********************************
function x800039_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800039_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800039_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--����
--**********************************
function x800039_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800039_CheckSubmit( sceneId, selfId )
end

--**********************************
--�ύ
--**********************************
function x800039_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

--**********************************
--ɱ����������
--**********************************
function x800039_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

--**********************************
--���������¼�
--**********************************
function x800039_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800039_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

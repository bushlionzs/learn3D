
x300632_g_ScriptId = 300632

--��һ�������ID
--g_MissionIdPre =

--��������ID
x300632_g_MessionIdAfter1	= 300634
x300632_g_MessionIdAfter2	= 300633


--�����ı�����
x300632_g_MissionName1="����᡿��Ὠ��"
x300632_g_MissionName2="����᡿���ļ��"
x300632_g_MissionName3="����᡿�ﹱ����"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x300632_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�

	local Readme_1 = "#Y����᡿��Ὠ��#W#r"
	
	local Readme_2 = "\t��ᾭ����������ᣬ�����ﹱ�̵�ı���Ʒ��#r"
	
	local Readme_3 = "\t����Ա�����ճ���������⻹����ͨ��".."#G".."���ļ��".."#W".."��".."#G".."�ﹱ����".."#W".."������ᾭ�飬ͬʱ������Ҳ�����#G�߶����#r"
	
	local Readme_4 = "\t#W���ļ��:����Աÿ��ÿ�տ��Խ���1�Ρ�#r"
	
	local Readme_5 = "\t#W�ﹱ����:ÿ�����ÿ�ո��ݱ����ĵȼ����н��衣1�������Խ���25�Σ�2�������Խ���50�Σ�3�������Խ���75�Σ�4�������Խ���100�Σ�5�������Խ���125�Σ�6�������Խ���150��,7�������Խ���175�Ρ�"
	
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
	
	BeginQuestEvent(sceneId);AddQuestText(sceneId,Readme)
	
	AddQuestNumText(sceneId,x300632_g_MessionIdAfter1,x300632_g_MissionName2,3)
	
	AddQuestNumText(sceneId,x300632_g_MessionIdAfter2,x300632_g_MissionName3,3)
	
	EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId)
	
end

--**********************************
--�о��¼�
--**********************************
function x300632_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	local pos = GetGuildOfficial(sceneId, selfId)--�ж��Ƿ������
	if pos == -1 then
		return
	end
	AddQuestNumText(sceneId,x300632_g_ScriptId,x300632_g_MissionName1,3);
end


--********************
--����������
--**********************************
function x300632_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x300632_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x300632_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300632_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300632_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300632_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300632_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300632_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300632_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

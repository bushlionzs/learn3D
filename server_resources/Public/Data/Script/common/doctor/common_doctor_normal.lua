--���ܣ���ͨҽ��


x300411_g_ScriptId = 300411
x300411_g_MissionName="�������"
--**********************************

--������ں���

--**********************************

function x300411_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "���ˣ��Ժ���ȥð�յ�ʱ�򣬼ǵ�Ҫʱ��ע���Լ��İ�Σ��")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	BeginQuestEvent(sceneId)
		local strText = "��ȫ��ָ��˽���"
		AddQuestText(sceneId,strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	
	RestoreHp(sceneId, selfId,100)
	local ZhiYe= GetZhiye( sceneId, selfId)
	if ZhiYe~=0 then
		RestoreRage(sceneId, selfId,100)
	end
end



--**********************************

--�о��¼�

--**********************************

function x300411_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x300411_g_ScriptId, x300411_g_MissionName)
end



--**********************************

--����������

--**********************************

function x300411_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x300411_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x300411_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x300411_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x300411_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x300411_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x300411_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x300411_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end
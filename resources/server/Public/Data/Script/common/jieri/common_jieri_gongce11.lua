
x350010_g_ScriptId = 350010
x350010_g_MissionName = "�����ӽ���"
x350010_g_AwardInfo = "\n\t#Y\n\t#Y�����ӣ�\n\t#Wÿ�����������1�Σ���������������̳ǵ��ߵĽ�����\n\t#Y�ƽ������ӣ�\n\t#W�ƽ������ӿ���һֱ��������ÿ�����󶼻����������̳ǵ��ߵĽ�����"

--�����NPC��
function x350010_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x350010_g_ScriptId,x350010_g_MissionName,0,-1)
	return 0
	
end



--�������ť������������ִ�д˽ű�
function x350010_ProcEventEntry( sceneId, selfId, targetId,state,index )	
	
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,x350010_g_AwardInfo)
	EndQuestEvent(sceneId)
	DispatchQuestEventList( sceneId,selfId,targetId )

	--x350010_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x350010_DispatchMissionInfo( sceneId, selfId, targetId,index)


end



--**********************************
--����
--**********************************
function x350010_ProcAccept( sceneId, selfId )
end

function x350010_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--�����ȷ����
function x350010_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--����
--**********************************
function x350010_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x350010_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x350010_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x350010_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x350010_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--��������
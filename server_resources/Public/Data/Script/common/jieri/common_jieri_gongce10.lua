
x350009_g_ScriptId = 350009
x350009_g_MissionName = "����ʥ����Ը��ʥ����"
x350009_g_AwardInfo = "\n#Y��Ը���ӣ�#W\n\t��Ը���ӣ���������ϵ���ŵ�����õ�Ը����ʹ����Ը���Ӻ󣬿����ú���һֱ�����������ߡ�\n\t�ڻ�ڼ�ÿ�������Ըʮ���Σ�ÿ����Ը��Ҫ3����Ը���ӡ�"
x350009_g_AwardInfo1 ="\n#Y�����ӣ�#W\n\t�����ӣ����������ĵ����������ף����ʹ�������Ӻ��п��ܻ������ص�����Ŷ��\n\t�ڻ�ڼ�ÿ�춼���������������������Ʒ��"
--�����NPC��
function x350009_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x350009_g_ScriptId,x350009_g_MissionName,0,-1)
	return 0
	
end



--�������ť������������ִ�д˽ű�
function x350009_ProcEventEntry( sceneId, selfId, targetId,state,index )	
	
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,x350009_g_AwardInfo)
	AddQuestText(sceneId,x350009_g_AwardInfo1)
	EndQuestEvent(sceneId)
	DispatchQuestEventList( sceneId,selfId,targetId )

	--x350009_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x350009_DispatchMissionInfo( sceneId, selfId, targetId,index)


end



--**********************************
--����
--**********************************
function x350009_ProcAccept( sceneId, selfId )
end

function x350009_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--�����ȷ����
function x350009_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--����
--**********************************
function x350009_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x350009_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x350009_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x350009_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x350009_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--��������
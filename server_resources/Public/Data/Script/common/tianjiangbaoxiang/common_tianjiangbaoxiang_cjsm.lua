--�ռ���ʯ����
--ScriptID = 310017


x310017_g_ScriptId 					= 310017


x310017_g_MissionName				= "���ռ���ʯ�������"

x310017_g_Readme1						=	"\n#Yһ�������\n#W1���ڽ�������������д��#Y���ɡ���������˼����������China Joy��#W����ʯ�������ռ��������ʯ���ˣ������ǵ�888��������ʯͷ���ˣ����л����Ϊ��Ѳμ��Ϻ�China Joy�Ļ�����˶����ʱ��Ϊÿ��#Y12��30~13��00#W��#G19��30~20��00#W���ڽ��ܹ�#Y���콵���䡿#W����󣬿�����#Y��ͱ���#W��������������ʯ�е�һ�֣�#Rÿ��������1��#W��"

--**********************************
--���NPC
--**********************************
function x310017_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x310017_g_ScriptId,x310017_g_MissionName,0,1)
	
end
--**********************************
--ִ��Ĭ���¼�
--**********************************
function x310017_ProcEventEntry( sceneId, selfId, targetId,state,index)

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x310017_g_MissionName)
			AddQuestText(sceneId,x310017_g_Readme1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x310017_g_ScriptId, x310017_g_MissionName)
		
end
--**********************************
--���
--**********************************
function x310017_ProcAcceptCheck( sceneId, selfId, NPCId )

end

--**********************************
--����
--**********************************
function x310017_ProcAccept( sceneId, selfId )
end

--**********************************
--����
--**********************************
function x310017_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x310017_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x310017_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x310017_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x310017_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x310017_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x310017_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end




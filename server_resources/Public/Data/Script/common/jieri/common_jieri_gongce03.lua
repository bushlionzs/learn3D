--��Ϧ���ս���
--ScriptID = 350002


x350002_g_ScriptId 					= 350002


x350002_g_MissionName				= "��Ϧ������"

x350002_g_Readme1						=	"\t�������˵����#Y�����˼������ߣ�����ţ�ɻ�֯Ů��#W��ũ�����³��ߣ��׳ơ�#G��Ϧ#W�����ഫ������ţ��֯Ůһ��һ������ʱ�̣��ֽС�#G���ɽ�#W���� \n\t��һ�죬���ǹ����ܻ���������������ǣţ����֯Ů�ǣ�����������һ���һϦ����ᣬ������ε����˶ϳ���������Ϧ��ʫ����Ϊ���ô����ģ�Ӧ�������ס�#Yȵ����#W��: \n\t#G����Ū�ɣ����Ǵ��ޣ������������ȡ������¶һ��꣬��ʤȴ�˼������� \n\t������ˮ���������Σ��̹�ȵ�Ź�·���������Ǿó�ʱ�������ڳ���ĺĺ��#W"

--**********************************
--���NPC
--**********************************
function x350002_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x350002_g_ScriptId,x350002_g_MissionName,0,1)
	
end
--**********************************
--ִ��Ĭ���¼�
--**********************************
function x350002_ProcEventEntry( sceneId, selfId, targetId,state,index)

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x350002_g_MissionName)
			AddQuestText(sceneId,x350002_g_Readme1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x350002_g_ScriptId, x350002_g_MissionName)
		
end
--**********************************
--���
--**********************************
function x350002_ProcAcceptCheck( sceneId, selfId, NPCId )

end

--**********************************
--����
--**********************************
function x350002_ProcAccept( sceneId, selfId )
end

--**********************************
--����
--**********************************
function x350002_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x350002_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x350002_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x350002_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x350002_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x350002_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x350002_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end




--˫��ս��˵��
--ScriptID = 310603

x310603_g_ScriptId 					= 310603

x310603_g_MissionName				= "�����а���ս��˵����"

x310603_g_Readme1						=	"\n#Yһ�����¹���\n#W1��ÿ�ܶ������һ����ս������ս��ʱ���#G��һ0��00������24��00#W���Ǳ���ʱ���ڵ������Ϊ���������������а����Ӱ�졣\n2��ÿ����24��00��ᱣ�沢��մ������а���ҿ��԰��¡�G���������а������а���ͨ���鿴���������а񡱣�����ѯ�Լ���������\n3�����Դӻ׷�ٵ������в鿴ÿ�ܽ��е����¡�"
x310603_g_Readme2						=	"\n#Y�����콱������\n#W1��#G��һ1��00������23��00#WΪ���������콱ʱ�䡣\n2��ÿ��������Ӧ�����а�ǰ100����������ȡ����������#G�߶��#W��#G���ųƺ�#W��#G��ǿ����#W�ȵȽ�����"
x310603_g_Readme3						=	"\n#Y�������̰��ţ�\n#G���а���ս��ÿ�ܽ�����һ�����а���������ᣬ��������˳����У�\n#W���������а�\n�������а�\n��������а�\nС�������а�\n��Ѫ�����а�\nɱ�����а�\nף��ׯ���а�\nս���ȼ����а�\n����Ĺ���а�\n���̻����а�\nӡ�Ⱥ����а�\n�����������а�\n�ֻ�̨���а�\nõ�����а�\n��������а�\n�����������а�"

--**********************************
--���NPC
--**********************************
function x310603_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x310603_g_ScriptId,x310603_g_MissionName,0,1)
	
end
--**********************************
--ִ��Ĭ���¼�
--**********************************
function x310603_ProcEventEntry( sceneId, selfId, targetId,state,index)

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x310603_g_MissionName)
			AddQuestText(sceneId,x310603_g_Readme1)
			AddQuestText(sceneId,x310603_g_Readme2)
			AddQuestText(sceneId,x310603_g_Readme3)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x310603_g_ScriptId, x310603_g_MissionName)
		
end
--**********************************
--���
--**********************************
function x310603_ProcAcceptCheck( sceneId, selfId, NPCId )

end

--**********************************
--����
--**********************************
function x310603_ProcAccept( sceneId, selfId )
end

--**********************************
--����
--**********************************
function x310603_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x310603_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x310603_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x310603_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x310603_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x310603_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x310603_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end




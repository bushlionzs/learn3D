--��Ϧ���ս���
--ScriptID = 350003


x350003_g_ScriptId 					= 350003


x350003_g_MissionName				= "��Ϧ�����"

x350003_g_Readme1						=	"һ��ӭ����Ϧ���š�#G���˷�#W����\n\t8��21�գ��������˽����յġ����˷�������ʱ��ӭ��������פ��\n������#Gõ������#W�����İ���#RTA#W���\n\t��2009��8��25��0:00��ʼ����ҿ����ڽ���̵��ڹ��򵽽������ε�õ�廨�͸������ˣ� #Y����õ�壬��������#W����ʱȫ������Ҷ����������������ԣ�����һ�ݴ󵨵ı��Ӯ�����İ���ɣ�\n������#GŨ����#W���������ճɾ���\n\t��#Yǧ����Եһ��ǣ����������ͽ��#W������Ϧ����������ҽ�鶼����ѣ��Ͽ����������Ѿõ����Я�ֿ�������ĵ��ðɣ���\n�ġ���#G��������#W��\n\t�����������κУ��ں�#R��������#W������ϵ�����Ʒ���Σ��ڴ��͸���������������ǧ��Ҫ�����\n�塢��#Gȵ�����#W��\n\t30��ȫ��������-ϲȵ����������ҹ���󽫻�ó���ϲȵһֻ���ۼ۽���9��900�ģ����ڲ��ۣ������ղ�ȫ������������������Ŷ��\n������#G����ϲȵ���￨#W�������¡���Ƴ�\n\t��ֵ400Ԫ������ϲȵ���￨��������ں����˽�ʱװ�Լ�ϲȵ���\n�ߡ���#GQQ���»��´����#W��\n\t��Ϧ�ڼ�ע����½�ɼ�˼���ʺţ��ش�򵥵�������⼴�ɻ��QQ���»����е�һö��ȫ��Ϊ���°棬����ö�� ���͸��������˵ı�״���"

--**********************************
--���NPC
--**********************************
function x350003_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x350003_g_ScriptId,x350003_g_MissionName,0,1)
	
end
--**********************************
--ִ��Ĭ���¼�
--**********************************
function x350003_ProcEventEntry( sceneId, selfId, targetId,state,index)

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x350003_g_MissionName)
			AddQuestText(sceneId,x350003_g_Readme1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x350003_g_ScriptId, x350003_g_MissionName)
		
end
--**********************************
--���
--**********************************
function x350003_ProcAcceptCheck( sceneId, selfId, NPCId )

end

--**********************************
--����
--**********************************
function x350003_ProcAccept( sceneId, selfId )
end

--**********************************
--����
--**********************************
function x350003_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x350003_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x350003_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x350003_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x350003_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x350003_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x350003_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end




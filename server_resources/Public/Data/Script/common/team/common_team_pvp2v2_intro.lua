--˫��ս��˵��
--ScriptID = 303002

x303002_g_ScriptId 					= 303002

x303002_g_MissionName				= "��˫��ս��˵����"

x303002_g_Readme1						=	"\n#Yһ����������\n#W1����һ������#G20��00~21��00#W��\n   ����#G13��00~15��00#WΪ˫��ս������ʱ�䡣\n2��˫��ս��ÿ5����Ϊһ�֡�\n   ��һ������#G19:55~20:59#W��\n   ����#G12��55~14��59#W��ʱ���Ա����μӡ�\n3�����Ķ�����������Ϊ���ˡ�\n4�����Ķ�����������ҵĵȼ�������ڻ����60����\n5��ֻ�жӳ���������μ�˫��ս����"
x303002_g_Readme2						=	"\n#Y����˫��ս������\n#W1��ÿ��˫��ս������ս��ʱ��Ϊ4���ӡ�\n2��˫��ս����������������޷������κθ������������������ϵͳ���Զ�����˫����ҡ�\n3�����ɹ�������ϵͳ����ս������ʱ����Ļ����λ�ø��������ʾ�������ʾͼ�꣬���ɽ���������ء�\n4�������������߽��޷�������롣\n5����˫��ս���ڵ��ߵ���ң�����ʱ�ᱻ���ͳ�ս����\n6��˫��ս��������ʤ����ֻ�д�ʱ����˫��ս���ڵ���Ҳ��ܻ����Ӧ��ս�����֡�\n7������7�첻�μ��κ�һ��˫��ս������ҵ�ս���ȼ���3��"
x303002_g_Readme3						=	"\n#Y����ʤ���ж�\n#W1����һ�����������������һ�����д����ң��ж��д����ҵ�һ����ʤ��\n2����˫��ս��ս�������󳬹�1���ӣ�ĳһ����Ȼû����ҽ���˫��ս�������ж���һ����ʤ��\n3����˫��ս��ս��ʱ�������˫��ʣ���Ա����ͬʱ�����ж���Ա���һ����ʤ��\n4����˫��ս��ս��ʱ�������˫��ʣ���Ա����ͬʱ�����ж�˫��ƽ�֡�"

--**********************************
--���NPC
--**********************************
function x303002_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x303002_g_ScriptId,x303002_g_MissionName,0,1)
	
end
--**********************************
--ִ��Ĭ���¼�
--**********************************
function x303002_ProcEventEntry( sceneId, selfId, targetId,state,index)

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x303002_g_MissionName)
			AddQuestText(sceneId,x303002_g_Readme1)
			AddQuestText(sceneId,x303002_g_Readme2)
			AddQuestText(sceneId,x303002_g_Readme3)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x303002_g_ScriptId, x303002_g_MissionName)
		
end
--**********************************
--���
--**********************************
function x303002_ProcAcceptCheck( sceneId, selfId, NPCId )

end

--**********************************
--����
--**********************************
function x303002_ProcAccept( sceneId, selfId )
end

--**********************************
--����
--**********************************
function x303002_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x303002_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x303002_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x303002_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x303002_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x303002_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x303002_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end




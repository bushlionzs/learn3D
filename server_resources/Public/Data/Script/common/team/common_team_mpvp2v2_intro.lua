--˫��ս��˵��
--ScriptID = 303106

x303106_g_ScriptId 					= 303106

x303106_g_MissionName				= "�����˫��ս��˵����"

x303106_g_Readme1						=	"\n#Yһ����������\n#W1����Ҫ��ͨ��#G��#W��#G�����˼�#W��#G���˫��ս��������#W���뱨��������\n2����һ������#G20��00~21��00#W������#G13��00~15��00#WΪ���˫��ս������ʱ�䡣\n3��˫��ս��ÿ5����Ϊһ�֡���һ������#G19:55~20:59#W������#G12��55~14��59#W��ʱ���Ա����μӡ�\n4�����Ķ�����������Ϊ���ˡ�\n5�����Ķ�����������ҵĵȼ�����ﵽ40����\n6��ֻ�жӳ���������μ�˫��ս����"
x303106_g_Readme2						=	"\n#Y����˫��ս������\n#W1��ÿ��˫��ս������ս��ʱ��Ϊ4���ӡ�\n2��˫��ս����������������޷������κθ������������������ϵͳ���Զ�����˫����ҡ�\n3�����ɹ�������ϵͳ����ս������ʱ����Ļ����λ�ø��������ʾ�������ʾͼ�꣬���ɽ���������ء�\n4�������������߻����뿪�����������޷�������롣\n5����˫��ս���ڵ��ߵ���ң�����ʱ�ᱻ���ͳ�ս����\n6��˫��ս��������ʤ����ֻ�д�ʱ����˫��ս���ڵ���Ҳ��ܻ����Ӧ��ս�����֡�"
x303106_g_Readme3						=	"\n#Y����ʤ���ж�\n#W1����һ�����������������һ�����д����ң��ж��д����ҵ�һ����ʤ��\n2����˫��ս��ս�������󳬹�1���ӣ�ĳһ����Ȼû����ҽ���˫��ս�������ж���һ����ʤ��\n3����˫��ս��ս��ʱ�������˫��ʣ���Ա����ͬʱ�����ж���Ա���һ����ʤ��\n4����˫��ս��ս��ʱ�������˫��ʣ���Ա����ͬʱ�����ж�˫��ƽ�֡�"

--**********************************
--���NPC
--**********************************
function x303106_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x303106_g_ScriptId,x303106_g_MissionName,0,1)
	
end
--**********************************
--ִ��Ĭ���¼�
--**********************************
function x303106_ProcEventEntry( sceneId, selfId, targetId,state,index)

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x303106_g_MissionName)
			AddQuestText(sceneId,x303106_g_Readme1)
			AddQuestText(sceneId,x303106_g_Readme2)
			AddQuestText(sceneId,x303106_g_Readme3)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x303106_g_ScriptId, x303106_g_MissionName)
		
end
--**********************************
--���
--**********************************
function x303106_ProcAcceptCheck( sceneId, selfId, NPCId )

end

--**********************************
--����
--**********************************
function x303106_ProcAccept( sceneId, selfId )
end

--**********************************
--����
--**********************************
function x303106_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x303106_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x303106_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x303106_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x303106_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x303106_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x303106_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end




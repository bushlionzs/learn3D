--MisDescBegin 
x300521_g_ScriptId 					= 	300521
x300521_g_MissionName				= 	"����������˵����" 
x300521_g_MissionInfo				= 	"Ѳ��������Ϣ" 
--MisDescEnd

function x300521_ProcEnumEvent( sceneId, selfId, targetId )
	AddQuestNumText(sceneId, x300521_g_ScriptId,x300521_g_MissionName,13,1)
end

function x300521_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y����������˵����#r#W"
		local Readme_2 = "  #Y��ȡ����#W������#G25��#W����ҿ��Խ�ȡ����ÿ������#Gһ�ֹ�10��#W����#r"
		local Readme_4 = "  #Yע�����#W����������վͲ����ٴν�ȡ�����ˣ���#G������������#W��#r"
		local Readme_5 = "  #Y���⽱����#W��#G�ռ���ƥ#W�������У�������ܴ�����Ӧ��#G��Ʒ��#W������#G�߶�ľ��齱��#W��\n  ���ռ���Ʒ�������У�������ܰ���Ҫ���Ͻ�һЩ#G����ܵ�ԭ����#W��#G���������Ĳ���#W��#G�ʴ����̾�#W�ȵȣ������#G�����Ľ���#W��" 
		local Readme = Readme_1..Readme_2..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300521_g_ScriptId, -1 );
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x300521_g_ScriptId,x300521_g_MissionName)
end 

function x300521_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300521_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300521_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300521_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300521_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300521_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300521_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300521_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300521_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
--MisDescBegin 
x562004_g_ScriptId 					= 	562004
x562004_g_MissionName				= 	"���Թ�����˵����" 
x562004_g_MissionInfo				= 	"Ѳ��������Ϣ" 
--MisDescEnd

function x562004_ProcEnumEvent( sceneId, selfId, targetId )
	AddQuestNumText(sceneId, x562004_g_ScriptId,x562004_g_MissionName,13,1)
end

function x562004_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y���Թ�����˵����#r#W"
		local Readme_2 = "  #Y��ȡ����#W#G35����49��#W����ҿ��Խ�ȡ����ÿ������#Gһ�ֹ�10��#W����#r"
		local Readme_4 = "  #Yע�����#W����������վͲ����ٴν�ȡ�����ˣ���#G������������#W��#r"
		local Readme_5 = "  #Y������ʾ��#W��10���������У��ύ�����齨����������������ٶȣ��������������ö��⽱��#W��" 
		local Readme = Readme_1..Readme_2..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x562004_g_ScriptId, -1 );
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x562004_g_ScriptId,x562004_g_MissionName)
end 

function x562004_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x562004_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x562004_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x562004_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x562004_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x562004_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x562004_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x562004_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x562004_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
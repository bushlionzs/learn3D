--MisDescBegin 
x300787_g_ScriptId 					= 	300787
x300787_g_MissionInfo				= 	"Ѳ��������Ϣ" 
--MisDescEnd

function x300787_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300787_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y����᡿��ᾭ��#r#W"
		local Readme_2 = "  1��#G��ᾭ���ã�#W��ᾭ�����ͨ����Ὠ�衢���ļ�������ս�Լ���ɰ�������á�#r"
		local Readme_3 = "  2��#G��ᾭ����;��#W��ᾭ�������������ͼ������̵��ϡ����Ʒ��#r"
		local Readme = Readme_1..Readme_2..Readme_3
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300787_g_ScriptId, -1 );
end 

function x300787_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300787_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300787_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300787_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300787_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300787_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300787_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300787_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300787_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
--MisDescBegin 
x300788_g_ScriptId 					= 	300788
x300788_g_MissionInfo				= 	"Ѳ��������Ϣ" 
--MisDescEnd

function x300788_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300788_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y����᡿����Ǯ#r#W"
		local Readme_2 = "  1��#G����Ǯ��ã�#W����Ǯͨ�����ļ���������ף�������������á�#r"
		local Readme_3 = "  2��#G����Ǯ��;��#Wӵ���㹻�İ���Ǯ�����ɰ���������������Ҳ�������������츳�о���#r"
		local Readme = Readme_1..Readme_2..Readme_3
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300788_g_ScriptId, -1 );
end 

function x300788_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300788_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300788_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300788_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300788_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300788_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300788_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300788_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300788_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
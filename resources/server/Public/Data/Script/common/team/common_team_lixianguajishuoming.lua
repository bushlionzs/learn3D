--MisDescBegin 
x310402_g_ScriptId 					= 	310402
x310402_g_MissionName				= 	"�����ߴ���˵����" 
x310402_g_MissionInfo				= 	"���ߴ���˵��" 
--MisDescEnd

function x310402_ProcEnumEvent( sceneId, selfId, targetId )
	AddQuestNumText(sceneId, x310402_g_ScriptId,x310402_g_MissionName,13,1)
end

function x310402_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y�����ߴ���˵����#r#W"
		local Readme_2 = "\tֻ�в�����#G40#W������Ҳſ���ʹ�����ߴ�����\n\t��ʼ���ߴ������������ߴ���ʱ�佫�ۻ����㵽���´�����Ϊֹ��֮�����ɻ���һ���Ľ�Ǯ��ȡ��Ӧ�����߾��飬���ߴ���ʱ�������ۻ�7�졣"
		local Readme_3 = "\n\t��ѡ����Ҫ��ȡ�����߾��鵵�Σ���ͬ�ĵ�����Ҫ���Ѳ�ͬ�����Ľ�Ǯ��"
		local Readme_4 = "\n\t#G�͵�#W����ͨ����Ч�ʣ���Ҫ����#G����#W��#G40#W����ʹ��\n"..
										 "\t#G�е�#W��˫������Ч�ʣ���Ҫ����#G���#W��#G60#W����ʹ��\n"..
										 "\t#G�ߵ�#W����������Ч�ʣ���Ҫ����#G���#W��#G70#W����ʹ��"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x310402_g_ScriptId, -1 );
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x310402_g_ScriptId,x310402_g_MissionName)
end 

function x310402_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x310402_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x310402_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x310402_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x310402_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x310402_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x310402_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x310402_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x310402_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
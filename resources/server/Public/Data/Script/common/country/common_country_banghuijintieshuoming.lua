--MisDescBegin 
x300794_g_ScriptId 					= 	300794
x300794_g_MissionName				= 	"�����ܡ�������" 
x300794_g_MissionInfo				= 	"��������" 
--MisDescEnd

function x300794_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300794_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y�����ܡ�������#r#W"
		local Readme_2 = "\t����������ÿһ��Ϊ����������׵İ��ڶ�������ȡ�Ľ�����#r"
		local Readme_3 = "\t����#G�ɹ���������#W�Ĵ�����#G���ս��ս��#W����ֱ��Ӱ��ÿ�ܰ������Ķ��١�#r"
		local Readme_4 = "\t�ȼ�������#G60#W��ÿ�ܹ�ѫֵ������#G28��#W����ң�ÿ#G����#W��������������ȡһ�ܵİ�������#r"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300794_g_ScriptId, -1 );
end 

function x300794_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300794_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300794_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300794_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300794_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300794_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300794_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300794_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300794_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
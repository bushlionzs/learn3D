--MisDescBegin 
x300793_g_ScriptId 					= 	300793
x300793_g_MissionName				= 	"�����ܡ��������" 
x300793_g_MissionInfo				= 	"��������" 
--MisDescEnd

function x300793_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300793_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y�����ܡ��������#r#W"
		local Readme_2 = "\t�����������ÿһ��Ϊ�����������׵Ĺ��񶼿�����ȡ�Ľ�����#r"
		local Readme_3 = "\t#Gÿ��#W�Ƿ��ܼ��#G���һ��������#W����ֱ��Ӱ��ÿ�ܹ�������Ķ��١�#r"
		local Readme_4 = "\t�ȼ�������#G60#W��ÿ�ܹ�ѫֵ������#G18��#W����ң�ÿ#G����#W��������������ȡһ�ܵĹ��������#r"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300793_g_ScriptId, -1 );
end 

function x300793_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300793_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300793_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300793_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300793_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300793_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300793_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300793_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300793_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
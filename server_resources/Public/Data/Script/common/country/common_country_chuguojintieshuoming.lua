--MisDescBegin 
x300795_g_ScriptId 					= 	300795
x300795_g_MissionName				= 	"�����ܡ���������" 
x300795_g_MissionInfo				= 	"��������" 
--MisDescEnd

function x300795_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300795_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y�����ܡ���������#r#W"
		local Readme_2 = "\t���������Ƕ��ڳ����������������׵�#G���ҹ�Ա#W��#G��������Ա#W�Ľ�����#r"
		local Readme_3 = "\t�ڷ���#G������#Wʱ���ڣ�����ÿ����ҳɹ�#G��ɳ�������#W�Ĵ�����ֱ��Ӱ����������Ķ��١�#r"
		local Readme_4 = "\tÿ��һ�����գ�ÿ��������ڼ��������ĳɹ����������ۼƣ������գ�������ȡһ�ܵĳ���������#G����#W��ȡ#G�ı�#W����������#G���Ҵ�#W��ȡ#G����#W����������#G��������#W��ȡ#Gһ��#W����������#r"
		local Readme_5 = "\t���ҹ�Ա���߹�������Ա���ȼ�������#G60#W��ÿ�ܹ�ѫֵ������#G38��#W��ÿ#G����#W��������������ȡһ�ܵĳ���������"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300795_g_ScriptId, -1 );
end 

function x300795_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300795_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300795_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300795_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300795_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300795_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300795_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300795_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300795_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
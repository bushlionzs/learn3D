--MisDescBegin 
x300796_g_ScriptId 					= 	300796
x300796_g_MissionName				= 	"�����ܡ����˽���" 
x300796_g_MissionInfo				= 	"��������" 
--MisDescEnd

function x300796_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300796_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y�����ܡ����˽���#r#W"
		local Readme_2 = "\t���˽����Ƕ��ڹ����������������׵�#G���ҹ�Ա#W��#G��������Ա#W�Ľ�����#r"
		local Readme_3 = "\t�ڷ���#G������#Wʱ���ڣ�����ÿ�����#G��ɹ�������#W�Ĵ�����ֱ��Ӱ����˽����Ķ��١�#r"
		local Readme_4 = "\tÿ��һ�����գ�ÿ��������ڼ��������ĳɹ����������ۼƣ������գ�������ȡһ�ܵĹ��˽�����#G����#W��ȡ#G�ı�#W���˽�����#G���Ҵ�#W��ȡ#G����#W���˽�����#G��������#W��ȡ#Gһ��#W���˽�����#r"
		local Readme_5 = "\t���ҹ�Ա���߹�������Ա���ȼ�������#G60#W��ÿ�ܹ�ѫֵ������#G38��#W��ÿ#G����#W��������������ȡһ�ܵĹ��˽�����"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300796_g_ScriptId, -1 );
end 

function x300796_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300796_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300796_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300796_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300796_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300796_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300796_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300796_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300796_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
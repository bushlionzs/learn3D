--MisDescBegin 
x300799_g_ScriptId 					= 	300799
x300799_g_MissionName				= 	"�����ܡ��ػ�����" 
x300799_g_MissionInfo				= 	"��������" 
--MisDescEnd

function x300799_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300799_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y�����ܡ��ػ�����#r#W"
		local Readme_2 = "\t�ػ���������ÿһ��Ϊ�ػ������������׵ģ�#G�ػ�����Ա#W��#G����#W��������ȡ�Ľ�����#r"
		local Readme_3 = "\t�ڷ���#G������#Wʱ���ڣ�ÿ��������#G��������Ĵ���#W��ֱ��Ӱ�쵱���ػ������Ķ��١�#r"
		local Readme_4 = "\tÿ#G��һ#W��#G����#W��ÿ��������ڼ�#G��������ĳɹ�����#W����#G�ۼ�#W����#G����#W��������ȡһ�ܵ��ػ��������ڹ�ѫֵ�㹻�Ļ����ϣ�#G����#W��ȡ#G����#W������#G����#W��ȡ#G�ı�#W������#r"
		local Readme_5 = "\t�ﵽ#G60��#W���ػ�����Աÿ�ܹ�ѫֵ������#G32#W�㣬ÿ#G����#W��������������ȡһ�ܵ��ػ���������ѫֵ��ÿ���ڳ������ڼ���ɳ�������ʱ��á�#r"
		local Readme_6 = "#GС��ʾ�����ػ�����ԱΪ���ҹ�Ա�����ػ���������������˽�����ֻ����ȡ����һ�֡�"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300799_g_ScriptId, -1 );
end 
	
function x300799_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300799_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300799_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300799_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300799_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300799_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300799_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300799_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300799_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
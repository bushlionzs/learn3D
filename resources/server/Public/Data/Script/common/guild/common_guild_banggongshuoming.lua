--MisDescBegin 
x300790_g_ScriptId 					= 	300790
x300790_g_MissionName				= 	"�ռ���ľ"
x300790_g_MissionInfo				= 	"Ѳ��������Ϣ" 
--MisDescEnd

function x300790_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300790_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y����᡿�ﹱ˵��#r#W"
		local Readme_2 = "  1��#G�ﹱ��ã�#W�ﹱͨ����ɰ�����񡢰�Ὠ�衢���ļ�������ս��á�#r"
		local Readme_3 = "  2��#G�ﹱ��;��#W�ﹱ���������ڰ���̵깺����Ʒ���һ�������ʯҲ��Ҫ�ﹱ��#r"
		local Readme = Readme_1..Readme_2..Readme_3
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300790_g_ScriptId, -1 );
end 

function x300790_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300790_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300790_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300790_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300790_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300790_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300790_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300790_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300790_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
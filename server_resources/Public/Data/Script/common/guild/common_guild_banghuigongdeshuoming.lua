--MisDescBegin 
x300791_g_ScriptId 					= 	300791
x300791_g_MissionInfo				= 	"Ѳ��������Ϣ" 
--MisDescEnd

function x300791_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300791_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y����᡿��Ṧ��#r#W"
		local Readme_2 = "  1��#G���»�ã�#W���¿���ͨ����ɰ�����񣨰���������⣩����Ὠ�衢���ļ�������ս��á�#r"
		local Readme_3 = "  2��#G����Ӱ�죺#W����С��5�İ���Ա������ɰ������󣬲������Ӱ�ᾭ�顣#r"
		local Readme_4 = "  3, #G������;��#W����ֵԽ��,��ɻ������ޡ���ᰵս���ռ���ľ���ռ���ľ�����ֳ��������˹ȳ�������ʱ����õľ���ӳ�Խ��,���ܰ���ܻ�����ʱ������ɵĻ�������Խ�ߡ�#r"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300791_g_ScriptId, -1 );
end 

function x300791_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300791_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300791_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300791_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300791_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300791_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300791_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300791_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300791_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
--MisDescBegin 
x300773_g_ScriptId 					= 	300773
x300773_g_MissionName				= 	"�ռ���ľ"
x300773_g_MissionInfo				= 	"Ѳ��������Ϣ" 
--MisDescEnd

function x300773_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300773_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y����������˵����#r#W"
		local Readme_2 = "  1.#G��������#W��������ֻ�а����͸��������Է����������������ʱ#G2Сʱ#W����ɣ���ʱ��Ч��#r"
		local Readme_3 = "  2.#G�������ڣ�#Wÿ������ڰ���������ѡ��#r#Y����᡿������#r����᡿�ռ���#r����᡿��ս��#r����᡿������#r����᡿ļ����#r#W����һ�֣�ÿ����ͬ�İ�������ֻ������һ�Ρ�#r"
		local Readme_4 = "  3.#G����;�У�#W����Ա�����ǰ�����ɼӿ�������ɵ��ٶȡ�#r"
		local Readme_5 = "  4.#G�ظ��ɹ���#W����ɴ�����������ʱ���ڻظ�������ֻ�ܻ�û���������#r"
		local Readme_6 = "  5.#G��������#W����Ա���#G˫��#W�����������������#G����#W���������������#G�ı�#W��������#r" 
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300773_g_ScriptId, -1 );
end 

function x300773_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300773_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300773_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300773_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300773_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300773_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300773_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300773_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300773_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
--MisDescBegin 
x300772_g_ScriptId 					= 	300772
x300772_g_MissionName				= 	"���ֳ���" 
x300772_g_MissionInfo				= 	"Ѳ��������Ϣ" 
--MisDescEnd

function x300772_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300772_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y����᡿���ֳ���#r#W"
		local Readme_2 = "  1��#G��ȡ����#W����У��ȼ�����40���İ���Ա��ÿ��������н�ȡ������#r"
		local Readme_3 = "  2��#G����;�У�#W����Ա�����ǰ�����ɼӿ�������ɵ��ٶȡ�#r"
		local Readme_4 = "  3��#G�ظ��ɹ���#W��ɴ�����������ڵ��ս��лظ�������ջظ�����ɵ����޷���ȡ������#r"
		local Readme_5 = "  4��#G��������#W�ɹ���ɴ�����������ø߶�ľ��飬��ᾭ�飬�ﹱ������" 
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300772_g_ScriptId, -1 );
end 

function x300772_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300772_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300772_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300772_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300772_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300772_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300772_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300772_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300772_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
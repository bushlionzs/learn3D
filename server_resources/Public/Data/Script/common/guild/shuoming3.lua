--MisDescBegin 
x300769_g_ScriptId 					= 	300769
x300769_g_MissionName				= 	"�ռ���ľ" 
x300769_g_MissionInfo				= 	"Ѳ��������Ϣ" 
--MisDescEnd

function x300769_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300769_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y����᡿�ռ���ľ#r#W"
		local Readme_2 = "  1��#G��ȡ����#W����У��ȼ�����#G40��С��65��#W�İ���Ա��ÿ��������н�ȡ������#r"
		local Readme_3 = "  2��#G����;�У�#W����Ա�����ǰ���������Ӹ��˵İ�ȫ��#r"
		local Readme_4 = "  3��#G�ظ��ɹ���#W��ɴ�����������ڵ��ս��лظ�������ջظ�����ɵ����޷���ȡ������#r"
		local Readme_5 = "  4��#G��������#W�ɹ���ɴ�����������ø߶�ľ��飬�ﹱ������" 
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300769_g_ScriptId, -1 );
end 

function x300769_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300769_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300769_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300769_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300769_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300769_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300769_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300769_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300769_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
--MisDescBegin 
x300771_g_ScriptId 					= 	300771
x300771_g_MissionName				= 	"���˹��ռ�" 
x300771_g_MissionInfo				= 	"Ѳ��������Ϣ" 
--MisDescEnd

function x300771_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300771_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y�����ͼ��˵����#r#W"
		local Readme_2 = "  1.#G��ȡ����#W����У��ȼ�������#G40��#W�İ���Ա��ÿ��������н�ȡ�����񣬻���ݵȼ��β�ͬ�����費ͬ������#r"
		local Readme_3 = "  2.#G����;�У�#W����Ա�����ǰ���������Ӹ��˵İ�ȫ��#r"
		local Readme_4 = "  3.#G�ظ��ɹ���#W��ɴ�����������ڵ��ս��лظ�������ջظ�����ɵ����޷���ȡ������#r"
		local Readme_5 = "  4.#G��������#W�ɹ���ɴ�����������ø߶�ľ��飬�ﹱ������" 
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300771_g_ScriptId, -1 );
end 

function x300771_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300771_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300771_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300771_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300771_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300771_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300771_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300771_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300771_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
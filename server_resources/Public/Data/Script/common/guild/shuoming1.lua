--MisDescBegin 
x300767_g_ScriptId 					= 	300767
x300767_g_MissionName				= 	"��ᰵս" 
x300767_g_MissionInfo				= 	"Ѳ��������Ϣ" 
--MisDescEnd

function x300767_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300767_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y����ᰵս˵����#r#W"
		local Readme_2 = "  1.#G��ȡ����#W����Աÿ��������н�ȡ������#r"
		local Readme_3 = "  2.#G����;�У�#W����Ա����ӣ��ɼӿ���������ٶȡ�#r"
		local Readme_4 = "  3.#G�ظ��ɹ���#W��ɴ��������ڵ��ս��лظ�������ջظ�����ɵ����޷���ȡ������#r"
		local Readme_5 = "  4.#G��������#W�ɹ���ɴ�����������ø߶�ľ��飬��ᾭ�飬�ﹱ������"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300767_g_ScriptId, -1 );
end 

function x300767_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300767_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300767_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300767_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300767_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300767_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300767_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300767_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300767_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
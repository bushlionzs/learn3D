--MisDescBegin 
x300830_g_ScriptId 					= 	300830
x300830_g_MissionName				= 	"����ٳ�" 
x300830_g_MissionInfo				= 	"Ѳ��������Ϣ" 
--MisDescEnd

function x300830_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300830_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y������ٳ�˵����#r#W"
		local Readme_2 = "  1.#G��ȡ����#W���ȷ���������1��4�������ϵİ�ᣬ������ŻῪ��������Ϊ������ߵȼ����2������2�������µĴﵽ40���İ���Ա������1���ֽ�/�𿨲ſɽ�������#r"
		local Readme_3 = "  2.#G����;�У�#W����Ա��һͬǰ������������ɱ����Ӧ��ħ��צ������Χͬ�����Ҿ�����ɸ�����#r"
		local Readme_4 = "  3.#G�ظ��ɹ���#W��ɴ��������ڵ��ս��лظ�������ջظ�����ɵ����޷���ȡ������#r"
		local Readme_5 = "  4.#G��������#W�ɹ���ɴ������������һ�Ż��굤����ᾭ�飬�ﹱ������"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300830_g_ScriptId, -1 );
end 

function x300830_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300830_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300830_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300830_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300830_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300830_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300830_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300830_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300830_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
--MisDescBegin 
x300704_g_ScriptId 					= 	300704
x300704_g_MissionName				= 	"�������" 
x300704_g_MissionInfo				= 	"Ѳ��������Ϣ" 
--MisDescEnd

function x300704_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300704_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y���������˵����#r#W"
		local Readme_2 = "  1.#G��ȡ����#W�ڲ�����#G����#W�İ���У����г�Ա�����Խ�ȡ������ÿ��ÿ�����������100�θ����񣬽�ȡ�����Ҫ����#G5��#W������������Ѻ����ɺ󷵻�5��������#r"
		local Readme_3 = "  2.#G������ܣ�#W��ȡ��������󣬻�õ�#G����������#W��һ��#G�����Ʊ#W�����ǵ����ҵ��������ˣ��Ƕ����˺������������ߵ��������̣������ϵİ�������۸����ǣ�׬���������������ע�⣺����һ��Ҫ�������۸�������ߵ����ˣ�����׬ȡ�㹻�Ľ�Ǯ��#r"
			local Readme_4 = "  3.#Gע�����#G��������#W�����л��ﶼ�Ǹ߼��չ��������������������֮ǰ���������̳����˺�����ͬ�Ļ����5�������������̲������չ������Ʒ��#r"
		local Readme_5 = "  4.#G��������#W�ɹ���ɴ�����������ò��Ƶ�#G����#W������#G20��#W����Ǯ��" 
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300704_g_ScriptId, -1 );
end 

function x300704_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300704_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300704_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300704_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300704_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300704_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300704_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300704_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300704_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
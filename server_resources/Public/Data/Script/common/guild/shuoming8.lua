--MisDescBegin 
x300774_g_ScriptId 					= 	300774
x300774_g_MissionName				= 	"��������" 
x300774_g_MissionInfo				= 	"Ѳ��������Ϣ" 
--MisDescEnd

function x300774_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300774_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1  = "#Y���������˵����#r#W"
		local Readme_2  = "  1.#G��ȡ����#W����ÿ�츶��Ѻ��10�������Ϳ���ȡ��������#r"
		local Readme_3  = "  2.#G������#W������ȡ����ʱ��������Χ�ı����Ա�����յ�������ȷ�ϴ��ڣ����ڿ����о����Ƿ���뵽���������С�#r"
		local Readme_4  = "  3.#G����;�У�#W����ֻ������������ƶ��������뿪��Զ�����޽�ֹͣ�ƶ���������ͨ����Ļ�·��ĳ�Ա�б����߳���ɫ���ֵĳ�Ա��#r"
		local Readme_5  = "  4.#G;����Ϣ��#W�����ڹŵ����ʹ����������վ��Ť����ǰ����վ��Χ�İ��ڶ����þ��齱���������������ɻ�������ʱ�����þ���ӳɵĽ�����#r" 
		local Readme_6  = "  5.#G;����ʧ��#W���뻤�ͳ�Ա����ʧ�ܣ��޷���������Ѻ��#r"
		local Readme_7  = "  6.#G;�б�ɱ��#W���뻤�ͳ�Ա����ʧ�ܣ�����Ѻ�𽫱����ߡ�#r"
		local Readme_8  = "  7.#G��������#W���뻤�ͳ�Ա����ʧ�ܣ��޷���������Ѻ��#r"
		local Readme_9  = "  8.#G�ظ��ɹ���#W���뻤�ͳ�Ա����ø߶�飬��ᾭ�飬�ﹱ���������ҷ�������Ѻ�𣬲�������Խ�ྭ�齱��Խ�ࡣ#r"
		local Readme_10 = "  9.#G�ͷ���#W��ɱ������Ա�ڳ���������Ѻ��ͬʱ����÷ǳ������ĳͷ���"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6..Readme_7..Readme_8..Readme_9..Readme_10
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfo( sceneId, selfId, targetId, 300774, -1 );
end

function x300774_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300774_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300774_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300774_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300774_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300774_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300774_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300774_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300774_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
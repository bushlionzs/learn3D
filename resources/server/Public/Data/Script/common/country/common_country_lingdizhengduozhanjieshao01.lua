--MisDescBegin 
x300935_g_ScriptId 					= 	300935
x300935_g_MissionName				= 	"����ؽ��ܡ�" 
x300935_g_MissionInfo				= 	"������ս��˵����" 
--MisDescEnd

function x300935_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300935_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y����ؽ��ܡ�#r#W"
		local Readme_2   = "1����Ϸ�У�����#G9��#W��ؿɹ����ᣬ����#G�ȼ����а�#W���һ����#G��ҵȼ�#W���Ŷ�Ӧ�������ͼ��#r #r"
		local Readme_3   = "2����ؼ���Ӧ���ŵȼ�Ϊ��#r#G���ݳ�           ��45����#W#r#G��Ҷ��           ��60����#W#r#G�͸��           ��70����#W#r#G��������         ��80����#W#r#G��ʥ����۹�     ��90����#W#r#GҮ·����        ��100����#W#r#G����            ��110����#W#r#G���            ��120����#W#r#Gצ�۵�          ��130����#W#r #r"
		local Readme_4   = "3��ռ����صİ���Ա��ÿ����������ȡ�����ͺ������飬������ȡ�Ľ���Ϊ���ڵ��ı���#r"		
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300935_g_ScriptId, -1 );
end 

function x300935_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300935_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300935_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300935_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300935_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300935_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300935_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300935_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300935_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
--MisDescBegin 
x300936_g_ScriptId 					= 	300936
x300936_g_MissionName				= 	"����ؽ��ܡ�" 
x300936_g_MissionInfo				= 	"���������ս˵����" 
--MisDescEnd

function x300936_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300936_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y������������#r #r#W"
		local Readme_2   = "1�������й���������£��ſɱ�����#r2���������ǰ���#r3��#G����13�㵽15��#W�ſɱ�����#r4��ÿ�����#G���#W������#G2����ᱨ������#W������ʱ���ʵ���ߵİ�Ὣ������ʵ���͵İ���ñ����ʸ�ͬһ�����ÿ������ֻ����һ�����μӱ�����#r "
		local Readme_3   = "5�������������ػ�����ռ����صİ������޷�������#r"
		local Readme = Readme_1..Readme_2..Readme_3
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300936_g_ScriptId, -1 );
end 

function x300936_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300936_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300936_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300936_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300936_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300936_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300936_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300936_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300936_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
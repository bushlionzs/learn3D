--MisDescBegin 
x300784_g_ScriptId 					= 	300784
x300784_g_MissionName				= 	"�ռ���ľ"
x300784_g_MissionInfo				= 	"Ѳ��������Ϣ" 
--MisDescEnd

function x300784_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300784_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y����ṱƷ˵����#r#W"
		local Readme_2 = "    ��ṱƷ���񣬷�Ϊ#GѰ��#W��#G����#W���֣���ֻ��Ҫ���հ�����񷢲��˵�Ҫ��������񣬾Ϳ��Ի��#G����#W��#G�ﹱ#W�Ľ�����#r"
		local Readme = Readme_1..Readme_2
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300784_g_ScriptId, -1 );
end 

function x300784_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300784_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300784_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300784_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300784_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300784_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300784_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300784_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300784_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
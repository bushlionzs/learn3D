--MisDescBegin 
x300773_g_ScriptId 					= 	300786
x300773_g_MissionName				= 	"���ȼ�" 
x300773_g_MissionInfo				= 	"Ѳ��������Ϣ" 
--MisDescEnd

function x300786_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300786_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y����᡿���ȼ�#r#W"
		local Readme_2 = "\t#G���ȼ���#W�������ȼ���Ҫһ���İ�����������ᾭ�顣�ȼ�Խ�ߣ������������Խ�ߣ��������Ҳ����ø���Ľ���#r"
		local Readme = Readme_1..Readme_2
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300773_g_ScriptId, -1 );
end 

function x300786_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300786_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300786_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300786_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300786_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300786_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300786_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300786_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300786_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
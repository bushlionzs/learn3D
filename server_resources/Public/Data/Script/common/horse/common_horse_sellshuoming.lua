--MisDescBegin 
x920008_g_ScriptId 					= 	920008
x920008_g_MissionName				= 	"���ռ�ս��˵����" 
x920008_g_MissionInfo				= 	"Ѳ��������Ϣ" 
--MisDescEnd

function x920008_ProcEnumEvent( sceneId, selfId, targetId )
	AddQuestNumText(sceneId, x920008_g_ScriptId,x920008_g_MissionName,13,1)
end

function x920008_ProcEventEntry(sceneId, selfId,targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y���ռ�ս��˵����#r#W"
		local Readme_2 = "  #Y�ռ�ս��#Wÿλ���ÿ������Ͻ�#G10ƥ#Wս��ÿ�ζ���������������#r"
		local Readme_4 = "  #Yע�����#W�ύս���#GЯ���ȼ�#WԽ�ߣ�����õĽ���Ҳ��Խ�ࡣ#r"
		local Readme_5 = "  #Y���⽱����#W��ͬЯ���ȼ��£��ύ#G��Ʒ��#W����#G8��#W����ͨ��Ľ�����" 
		local Readme = Readme_1..Readme_2..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x920008_g_ScriptId, -1 );
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x920008_g_ScriptId,x920008_g_MissionName)
end 

function x920008_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x920008_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x920008_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x920008_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x920008_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x920008_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x920008_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x920008_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x920008_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
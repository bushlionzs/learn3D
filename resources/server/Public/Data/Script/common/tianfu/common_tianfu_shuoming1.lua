--װ���̽�˵��

--MisDescBegin
x570064_g_ScriptId = 570064
x570064_g_MissionName1="�������츳˵����"
x570064_g_MissionInfo1="\t#Wֻ�и�������ȫ����ǿ�����ܱ�ø���ǿ��\n#Y�����츳������#W��\n\tͨ��ѧϰ�������ԣ�����������ۺ�ʵ������ͼ��ս�������ڲ���֮�ء�\n#Y�����츳���ѧϰ#W��\n\t�ڴ��츳��#G�����츳��ʦ#W����ѧϰ���������ܣ�����ѧϰ����Ѿ��з��ļ��ܣ�����Ҫһ�����츳�ȼ��Ͱﹱ��\n#Y�ﹱ��λ��#W��\n\t���ְ���淨�Ͱ��ս�п��Ի�ðﹱ��"  --��������

--**********************************

--������ں���

--**********************************

function x570064_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570064_g_MissionName1)
			AddQuestText(sceneId,x570064_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x570064_g_ScriptId, x570064_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x570064_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

		AddQuestNumText(sceneId, x570064_g_ScriptId, x570064_g_MissionName1,13,1)
	
end



--**********************************

--����������

--**********************************

function x570064_ProcAcceptCheck(sceneId, selfId, NPCId)

		return 1
end


--**********************************

--���鿴����

--**********************************

function x570064_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x570064_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x570064_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x570064_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x570064_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x570064_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x570064_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x570064_ProcTiming(sceneId, selfId )
	 
		
end

function x570064_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x570064_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x570064_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x570064_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x570064_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x570064_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x570064_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x570064_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x570064_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

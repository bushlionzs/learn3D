--װ���̽�˵��

--MisDescBegin
x570067_g_ScriptId = 570067
x570067_g_MissionName1="��Ԫ���츳˵����"
x570067_g_MissionInfo1="\t#WԪ���츳��Ҫ˵����\n#YԪ���츳������#W��\n\t���ܡ�\n#YԪ���츳���ѧϰ#W��\n\tҲ�����ܡ�\n#Y������λ��#W��\n\t�������ܡ�"  --��������

--**********************************

--������ں���

--**********************************

function x570067_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570067_g_MissionName1)
			AddQuestText(sceneId,x570067_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x570067_g_ScriptId, x570067_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x570067_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

		AddQuestNumText(sceneId, x570067_g_ScriptId, x570067_g_MissionName1,13,1)
	
end



--**********************************

--����������

--**********************************

function x570067_ProcAcceptCheck(sceneId, selfId, NPCId)

		return 1
end


--**********************************

--���鿴����

--**********************************

function x570067_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x570067_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x570067_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x570067_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x570067_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x570067_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x570067_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x570067_ProcTiming(sceneId, selfId )
	 
		
end

function x570067_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x570067_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x570067_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x570067_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x570067_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x570067_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x570067_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x570067_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x570067_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

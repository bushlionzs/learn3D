--װ���̽�˵��

--MisDescBegin
x570068_g_ScriptId = 570068
x570068_g_MissionName1="��ս���츳˵����"
x570068_g_MissionInfo1="\t#Wս���츳��Ҫ˵����\n#Yս���츳������#W��\n\t���ܡ�\n#Yս���츳���ѧϰ#W��\n\tҲ�����ܡ�\n#Y������λ��#W��\n\t�������ܡ�"  --��������

--**********************************

--������ں���

--**********************************

function x570068_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570068_g_MissionName1)
			AddQuestText(sceneId,x570068_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x570068_g_ScriptId, x570068_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x570068_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

		AddQuestNumText(sceneId, x570068_g_ScriptId, x570068_g_MissionName1,13,1)
	
end



--**********************************

--����������

--**********************************

function x570068_ProcAcceptCheck(sceneId, selfId, NPCId)

		return 1
end


--**********************************

--���鿴����

--**********************************

function x570068_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x570068_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x570068_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x570068_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x570068_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x570068_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x570068_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x570068_ProcTiming(sceneId, selfId )
	 
		
end

function x570068_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x570068_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x570068_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x570068_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x570068_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x570068_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x570068_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x570068_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x570068_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

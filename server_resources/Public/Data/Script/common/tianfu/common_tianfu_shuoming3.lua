--װ���̽�˵��

--MisDescBegin
x570066_g_ScriptId = 570066
x570066_g_MissionName1="��ר���츳˵����"
x570066_g_MissionInfo1="\t#Wר���츳��Ϊר����ר�����ࡣ\n\t#Yר��������#W������Լ���������ҵ��˺�����ĳ��ְҵ��ר���ȼ�Խ�ߣ��Լ��Դ�ְҵ���˺�����Խ������ʿר��Ϊ����ÿ����һ�����Ի�������������ң���ʿְҵ�������������Խ�࣬��õ�ר������Խ�ࡣ��ר�������ۻ���һ��������ר���ȼ��ͻ�õ�����������Ӧְҵ���˺�������\n\t#R�ر�˵����������������ÿ���ǰ10��������ɱ��Ч������������Ѿ����ܹ�10�����Ի����������ң��ٷ��������������������ܹ����ְҵר��������������������Ч�����ڴ�����Ч��\n\t#Yר��������#W������������Ҷ��Լ����˺�����ĳ��ְҵ��ר���ȼ�Խ�ߣ���ְҵ���Լ����˺�Խ�͡�����ר���ȼ���Ҫ�ۻ�ר��ѵ��������ר��ѵ��������Ҫ��ɡ����ˡ�����֮·�����á�"  --��������

--**********************************

--������ں���

--**********************************

function x570066_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570066_g_MissionName1)
			AddQuestText(sceneId,x570066_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x570066_g_ScriptId, x570066_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x570066_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

		AddQuestNumText(sceneId, x570066_g_ScriptId, x570066_g_MissionName1,13,1)
	
end



--**********************************

--����������

--**********************************

function x570066_ProcAcceptCheck(sceneId, selfId, NPCId)

		return 1
end


--**********************************

--���鿴����

--**********************************

function x570066_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x570066_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x570066_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x570066_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x570066_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x570066_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x570066_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x570066_ProcTiming(sceneId, selfId )
	 
		
end

function x570066_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x570066_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x570066_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x570066_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x570066_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x570066_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x570066_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x570066_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x570066_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

--װ���̽�˵��

--MisDescBegin
x570065_g_ScriptId = 570065
x570065_g_MissionName1="��ƽ���츳˵����"
x570065_g_MissionInfo1="\t#Wÿ���˵ĳɳ�֮·������ͬ���ֲ���������ж���ʱ������˶����������ƣ����ܱ�ø���ǿ��\n#Yƽ���츳������#W��\n\t������������з����Բ�����󣬷���ƽ�����ã�����һ�������Բ��죬ʹ������ս�����������쾡�µķ��ӳ�����\n\t1.��������ƽ�⣺�������Ƽ��ܵ������ʣ�ÿ������1%��\n\t2.���Ƶֿ�ƽ�⣺�������Ƽ��ܵĵֿ��ʣ�ÿ������1%������Ч�ĵֿ�������Ϊ90%��\n\t3.����ƽ�⣺��ʵ�������ʵ���50%ʱ��Ч��ÿ������1�����С�\n\t4.����ƽ�⣺��ʵ�������ʵ���20%ʱ��Ч��ÿ������1�����ܡ�\n\t5.����ƽ�⣺��ʵ�ʱ����ʵ���10%ʱ��Ч��ÿ������1�㱩����\n\t6.����ƽ�⣺��ʵ���Ⱪ���ʵ���50%ʱ��Ч��ÿ������1�����ԡ�����Ӱ�챩���˺���\n\t7.�����˺�ƽ�⣺��ʵ�ʱ����˺�����50ʱ��Ч��ÿ������1%�����˺���\n\t8.��������ƽ�⣺��ʵ�ʱ������˺�����100ʱ��Ч��ÿ������1%�����˺����⡣\n#Yƽ���츳���ѧϰ#W��\n\t�ڴ��츳��#Gƽ���츳��ʦ#W����ѧϰ���������ܡ���Ҫһ�����츳�ȼ�����Ӧ�ȼ���ƽ��֮�顣\n#Yƽ��֮����λ��#W��\n\t����ƽ��֮��ͨ���ͼ�ƽ��֮��ϳɶ�����һ��ƽ��֮��ͨ��ƽ��֮���ҳ�ϳɶ�����ƽ��֮���ҳ�����ڸ����淨�л�á�"  --��������

--**********************************

--������ں���

--**********************************

function x570065_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	--����г�����

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570065_g_MissionName1)
			AddQuestText(sceneId,x570065_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x570065_g_ScriptId, x570065_g_MissionName1)

end



--**********************************

--�о��¼�

--**********************************

function x570065_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

		AddQuestNumText(sceneId, x570065_g_ScriptId, x570065_g_MissionName1,13,1)
	
end



--**********************************

--����������

--**********************************

function x570065_ProcAcceptCheck(sceneId, selfId, NPCId)

		return 1
end


--**********************************

--���鿴����

--**********************************

function x570065_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--����

--**********************************

function x570065_ProcAccept( sceneId, selfId )
	
end



--**********************************

--����

--**********************************

function x570065_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x570065_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--�ύ

--**********************************

function x570065_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x570065_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x570065_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x570065_ProcTiming(sceneId, selfId )
	 
		
end

function x570065_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--���߸ı�

--**********************************

function x570065_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x570065_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x570065_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x570065_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x570065_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x570065_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x570065_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x570065_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

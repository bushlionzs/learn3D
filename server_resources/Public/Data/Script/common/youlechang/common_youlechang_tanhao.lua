--�����֡���һƥ��

--MisDescBegin
x310347_g_ScriptId = 310347
x310347_g_MissionIdPre =-1
x310347_g_MissionId = 9090
x310347_g_LevelLess	= 	65 
x310347_g_MissionIdNext = 3709
x310347_g_Name	={}
x310347_g_ExtTarget={{type=20,n=1,target="ץ��һƥ@npc_134027"}}
x310347_g_MissionName="�����֡���¹���ϵĿ���"
x310347_g_MissionInfo="\t�ڳɼ�˼���������У���Ҫ��Ϊ������Ӣ�ۣ�һƥ��������ز����ٵĻ�顣\n\t������������Щ���˰ɣ���ֻҪ������ƶ���С������ϣ��������Ϳ��Բ�׽�ˡ�\n\t���ڣ����ҽ̸���ķ�����ȥѡ��һƥ����Ϊ���һ�����ɡ�"  --��������
x310347_g_MissionTarget="ץ��һƥ@npc_134027"		
x310347_g_MissionCompleted="\t�μ�ѱ�����ǵķ������������㽫��õ�������õ����"					--�������npc˵���Ļ�
x310347_g_ContinueInfo="\t��ѱ������ô��"
x310347_g_MissionHelp =	"#G������ƶ���#R��ƥ#G�ϣ����#R���#Gһ�£����ĵȴ�ץ�������ϣ�ϵͳ����ʾ����׽#R�ɹ�#G�����ʧ���ˣ��ܿ����������������#R�����Զ#G���µģ���ֻ��Ҫ#R������ƥ#G������ץһ�μ��ɡ�#W"
x310347_g_DemandItem ={}
x310347_g_ExpBonus = 310
x310347_g_BonusMoney1 =5				
x310347_g_BonusMoney2 =0
x310347_g_BonusMoney3 =0
x310347_g_BonusMoney4 =0
x310347_g_BonusMoney5 =12
x310347_g_BonusMoney6 =0
x310347_g_BonusItem	=	{}
x310347_g_BonusChoiceItem ={}
x310347_g_NpcGUID = {}
--MisDescEnd
--**********************************

function x310347_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)   
print(545)
	if GetLevel( sceneId, selfId)>2 then
		return
	end
end

function x310347_DispatchMissionInfo( sceneId, selfId, NPCId )
		
end
--**********************************

function x310347_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	
end
--**********************************

function x310347_ProcAcceptCheck(sceneId, selfId, NPCId)

end
--**********************************
function x310347_CheckSubmit( sceneId, selfId, NPCId)

end
--**********************************
function x310347_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )

end
--**********************************

function x310347_ProcQuestAbandon(sceneId, selfId, MissionId)

end
--**********************************
function x310347_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	
end
--**********************************
function x310347_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	
end

function x310347_GetBonus( sceneId, selfId,NpcID)

end

function x310347_Msg2toplayer( sceneId, selfId,type)

end

function x310347_ProcQuestHorseChanged(sceneId, selfId, horseId, MissionId)
	x310347_CheckSubmit( sceneId, selfId)
end

function x310347_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x310347_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x310347_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x310347_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x310347_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x310347_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

function x310347_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x310347_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x310347_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x310347_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x310347_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x310347_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

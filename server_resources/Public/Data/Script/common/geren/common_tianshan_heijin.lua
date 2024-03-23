--MisDescBegin

x300875_g_ScriptId 	  = 300875
x300875_g_MissionKind 				= 	1                       --��������
x300875_g_Mis_Count   = 1--ÿ������Ĵ���
x300875_g_MissionId = 7649;
x300875_g_ExtTarget					=	{ {type=20,n=1,target="��"} }

--MisDescEnd

--������
x300875_g_SubMissionID				=	{ { MisID=7620,MissionName = "�����ˡ��ٸ�Ѻ��",LevelLess = 30,LevelMax = 40  }, 
										  {	MisID=7621,MissionName = "�����ˡ��ٸ�Ѻ��",LevelLess = 40,LevelMax = 50  },
										  {	MisID=7622,MissionName = "�����ˡ��ٸ�Ѻ��",LevelLess = 50,LevelMax = 60  },
										  {	MisID=7623,MissionName = "�����ˡ��ٸ�Ѻ��",LevelLess = 60,LevelMax = 70  },
										  {	MisID=7624,MissionName = "�����ˡ��ٸ�Ѻ��",LevelLess = 70,LevelMax = 80  },	
										  {	MisID=7625,MissionName = "�����ˡ��ٸ�Ѻ��",LevelLess = 80,LevelMax = 150  },											  
										}								

function x300875_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local index = 0
	local level = GetLevel(sceneId,selfId)
	for i,itm in x300875_g_SubMissionID do
		if level >= itm.LevelLess and level < itm.LevelMax then
			index = i
			break
		end
	end

	local bHaveMission = x300875_IsHaveMission(sceneId, selfId)
	if bHaveMission <= 0 and index > 0 then
		local state = GetQuestStateNM(sceneId,selfId,targetId,x300875_g_SubMissionID[index].MisID)
		AddQuestNumText(sceneId,x300875_g_SubMissionID[index].MisID,x300875_g_SubMissionID[index].MissionName,state,index);
	end

end



--�������ť������������ִ�д˽ű�
function x300875_ProcEventEntry( sceneId, selfId, targetId, MissionId,nExtIdx )
end

--����Ƿ�������
function x300875_IsHaveMission( sceneId, selfId )

	local bHaveMission = 0
	for i,itm in x300875_g_SubMissionID do
		bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MisID );
		if bHaveMission > 0 then
			break
		end
	end
	
	return bHaveMission
end


--**********************************
--����
--**********************************
function x300875_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
end


--**********************************
--����
--**********************************
function x300875_ProcAccept( sceneId, selfId )
	
end

--�������
--����1����ɹ���0��������ʧ��
function x300875_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
end


--********************************************************************
--����
--********************************************************************
function x300875_ProcQuestAbandon( sceneId, selfId,MissionId )  	
end


function x300875_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
end

---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300875_QuestLogRefresh( sceneId, selfId, MissionId)
end

function x300875_ProcQuestLogRefresh( sceneId, selfId, MissionId)

end





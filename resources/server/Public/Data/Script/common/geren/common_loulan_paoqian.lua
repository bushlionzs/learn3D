--MisDescBegin

x300756_g_ScriptId 					= 	300756                  --�ű�ID
x300756_g_MissionId 				= 	7555                    --����ID

x300756_g_MissionKind 				= 	1                       --��������

x300756_g_MissionName				= 	"�����ˡ��ڽ�Ѻ��"                --��������(512)
x300756_g_MissionTarget				= 	"ɱ��@npc_72005"          --����Ŀ��
x300756_g_MissionInfo				= 	"\tɱ��@npc_72004��@npc_72005,�ҵ�@npc_137600"            --������Ϣ
x300756_g_ContinueInfo				= 	"@npc_137602һֱ�����Ұ������@npc_72004��@npc_72005����ȴһֱ�鲻����"  --���������Ϣ
x300756_g_MissionCompleted			= 	"@npc_137602�Ѿ����ż������ˣ����������ְ�Ԫ��ħ����������ˣ�����Ͽ�֪ͨ@npc_137400��"  --���������Ϣ
x300756_g_MissionHelp				=	""          --������ʾ��Ϣ

--Ŀ��
x300756_g_ExtTarget					=	{ {type=20,n=3,target="@npc_72005"} }


--����
x300756_g_ExpBonus					= 	1000                    	--���������� ����ֵ��0���ַ���Ϊ�գ���ʾû�и������
x300756_g_BonusItem					=	{}	--��������Ʒ

x300756_g_BonusMoney1               = 	0    --������������
x300756_g_BonusMoney2               =   0    --�������ǰ�����
x300756_g_BonusMoney3               =   0    --�������󶨽��
x300756_g_BonusMoney4               =   0  --��������͢����
x300756_g_BonusMoney5               =   0  --��������������
x300756_g_BonusMoney6               =   10  --����������

x300756_g_BonusChoiceItem           =   {}

--MisDescEnd


--������
x300756_g_SubMissionID				=	{ { MisID=7556,MissionName = "���ڽ𡿺ڽ�Ѻ��",LevelLess = 30,LevelMax = 40  }, 
										  {	MisID=7557,MissionName = "���ڽ𡿺ڽ�Ѻ��",LevelLess = 40,LevelMax = 50  },
										  {	MisID=7558,MissionName = "���ڽ𡿺ڽ�Ѻ��",LevelLess = 50,LevelMax = 60  },
										  {	MisID=7546,MissionName = "���ڽ𡿺ڽ�Ѻ��",LevelLess = 60,LevelMax = 70  },
										  {	MisID=7547,MissionName = "���ڽ𡿺ڽ�Ѻ��",LevelLess = 70,LevelMax = 80  },	
										  {	MisID=7548,MissionName = "���ڽ𡿺ڽ�Ѻ��",LevelLess = 80,LevelMax = 150  },											  
										}								


--**********************************
--�о��¼�
--**********************************
function x300756_ProcEnumEvent( sceneId, selfId, NPCId )

	local index = 0
	local level = GetLevel(sceneId,selfId)
	for i,itm in x300756_g_SubMissionID do
		if level >= itm.LevelLess and level < itm.LevelMax then
			index = i
			break
		end
	end
	
	local bHaveMission = x300756_IsHaveMission(sceneId, selfId)
	if bHaveMission <= 0 and index > 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x300756_g_SubMissionID[index].MisID)
		AddQuestNumText(sceneId,x300756_g_SubMissionID[index].MisID,x300756_g_SubMissionID[index].MissionName,state,index);
	end
end


--**********************************
--������ں���
--**********************************
function x300756_ProcEventEntry(sceneId, selfId, NPCId, MissionId,nExtIdx)	--����������ִ�д˽ű�
end

--����Ƿ�������
function x300756_IsHaveMission( sceneId, selfId )

	local bHaveMission = 0
	for i,itm in x300756_g_SubMissionID do
		bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MisID );
		if bHaveMission > 0 then
			break
		end
	end
	
	return bHaveMission
end

---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x300756_ProcQuestAbandon(sceneId, selfId, MissionId)
end


---------------------------------------------------------------------------------------------------
--�ύ���񣬲��������Ƿ���ɻ���������ʾ���������Ϣ�������������Ϣ
---------------------------------------------------------------------------------------------------
function x300756_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
end

function x300756_ProcQuestLogRefresh( sceneId, selfId, MissionId)
end


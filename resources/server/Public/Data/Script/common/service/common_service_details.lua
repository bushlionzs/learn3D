--MisDescBegin

x310171_g_ScriptId 					= 	310171                   --�ű�ID

x310171_g_MissionKind 				= 	1                       --��������
x310171_g_LevelLess					= 	20                      --������С�ȼ�  <=0 ��ʾ������

x310171_g_MissionHelp				=	"\t�뵽���ɼ�˼��������������վ���ϲ���,������дһ�����֤Ϊ18�����ϵ�ID,����Ѿ�ע���18���������֤����ҿ��ܻ��ܵ���Ϸ�з�����ϵͳ��Ӱ��,���ڵǼǺ����µ�½��Ϸ��\n�㽫��ý���:\n#Y50000�㾭��#W\n#Y1������#W"          --������ʾ��Ϣ
x310171_g_MissionName				=   "����˵������"

--Ŀ��
x310171_g_ExtTarget					=	{ {type=20,n=1,target="@npc_72005"} }

--����
x310171_g_BonusExp					=	50000	--����������
x310171_g_BonusMoney				=	1000	--����������

--MisDescEnd

--����Ŀ��˳��
x310171_MP_ISCOMPLETE				= 7	--������� 0δ��ɣ� 1���

						
--**********************************
--�о��¼�
--**********************************
function x310171_ProcEnumEvent( sceneId, selfId, NPCId, MissionId )

	AddQuestNumText(sceneId, x310171_g_ScriptId, x310171_g_MissionName,3,1);
	return 0;
end

--**********************************
--������ں���
--**********************************
function x310171_ProcEventEntry(sceneId, selfId, NPCId, MissionId,nExtIdx)	--����������ִ�д˽ű�
	
	if GetNonageFlag(sceneId, selfId) ~= 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,x310171_g_MissionHelp)
		EndQuestEvent(sceneId)
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��л���֧�֣�����:\n")
		AddQuestText(sceneId,"���齱��:"..x310171_g_BonusExp)
		AddQuestText(sceneId,"��������:"..x310171_g_BonusMoney)
		EndQuestEvent(sceneId)
	end

	DispatchQuestInfo(sceneId, selfId, NPCId, x310171_g_ScriptId, -1);
end

---------------------------------------------------------------------------------------------------
--����������
---------------------------------------------------------------------------------------------------
function x310171_ProcAcceptCheck( sceneId, selfId,MissionID )

	if GetLevel( sceneId, selfId ) < x310171_g_LevelLess then
		local Readme = "�ȼ����㣬��������"..x310171_g_LevelLess.."���Ժ��������ܴ�����"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)		
		return
	end

	if GetNonageFlag(sceneId, selfId) ~= 0 then
		return
	end

	if GetQuestData(sceneId,selfId,MD_ZHUCE_DATE[1],MD_ZHUCE_DATE[2],MD_ZHUCE_DATE[3]) == 1 then
		local Readme = "���Ѿ���ȡ����������ˣ�"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)		
		return		
	end

	--������
	AddExp(sceneId, selfId, x310171_g_BonusExp);
	local Readme = "������"..x310171_g_BonusExp.."����Ľ�����"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, Readme);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	Msg2Player(sceneId,selfId,Readme,8,2)

	AddMoney( sceneId, selfId, 1, x310171_g_BonusMoney )
	SetQuestData(sceneId, selfId, MD_ZHUCE_DATE[1], MD_ZHUCE_DATE[2], MD_ZHUCE_DATE[3], 1)

end

---------------------------------------------------------------------------------------------------
--��������Ƿ���ύ
---------------------------------------------------------------------------------------------------
function x310171_CheckSubmit(sceneId, selfId, NPCId, index)
end

---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x310171_ProcQuestAbandon(sceneId, selfId, MissionId)
end

---------------------------------------------------------------------------------------------------
--��ý���
---------------------------------------------------------------------------------------------------
function x310171_GetBonus( sceneId, selfId,NpcID, SelectId,MissionId )
end

---------------------------------------------------------------------------------------------------
--�ύ���񣬲��������Ƿ���ɻ���������ʾ���������Ϣ�������������Ϣ
---------------------------------------------------------------------------------------------------
function x310171_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId,MissionId)
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x310171_DispatchMissionInfo( sceneId, selfId, NPCId )
	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId,"#Y"..x310171_g_MissionName)
		AddQuestText(sceneId,format("%s", x310171_g_MissionInfo))
		AddQuestText(sceneId," ")

		--����Ŀ��
--		AddQuestText( sceneId,"#Y����Ŀ�꣺")
--		AddQuestText( sceneId,format("%s", x300757_g_SubMissionID[index].MissionTarget))
--		AddQuestText( sceneId," ")

		--��ʾ��Ϣ
--		if x300757_g_MissionHelp ~= "" then
--
--			AddQuestText(sceneId,"#Y������ʾ��")
--			AddQuestText(sceneId,format("%s", x310171_g_MissionHelp))
--			AddQuestText(sceneId," ")
--		end

		--��������Ϣ

		--1������
		if x310171_g_BonusExp > 0 then
			AddQuestExpBonus(sceneId, x310171_g_BonusExp )
		end

		--2����Ǯ1
		if x310171_g_BonusMoney > 0 then
			AddQuestMoneyBonus2(sceneId, x310171_g_BonusMoney )
		end

	EndQuestEvent(sceneId)
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x310171_g_ScriptId, -1);	
end

---------------------------------------------------------------------------------------------------
--����NPC�¼�
---------------------------------------------------------------------------------------------------
function x310171_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
end

---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x310171_QuestLogRefresh( sceneId, selfId, MissionId)
end

function x310171_ProcQuestLogRefresh( sceneId, selfId, MissionId)
end



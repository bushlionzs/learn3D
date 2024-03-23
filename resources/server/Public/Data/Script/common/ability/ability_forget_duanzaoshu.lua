
x540013_g_ScriptId = 540013

x540013_g_AbilityName = "ͻ�ʶ�����"
x540013_g_MissionName = "����"..x540013_g_AbilityName
x540013_g_ContinueInfo="\t����ϵ����ܷ�Ϊ���֣���ԭ��ҩ����ӡ���鱦�����ɹ�ѱ������ͻ�ʶ���������������������˹��������\n\t�����ѧϰ������������ϵ����ܡ�������Ѿ�ѧ���������켼�ܣ���ϣ��ѧϰ�µ����켼�ܣ����Ե�����������"..x540013_g_AbilityName.."��\n\t�������ܺ��������Ӧ�ƺ�Ҳ����ʧ����ϣ������"..x540013_g_AbilityName.."��"
x540013_g_TitleId = 84

-- ��سƺ�������Ϣ
x540013_g_Title_Quest_ScriptId = 3613

function x540013_ProcEnumEvent( sceneId, selfId, targetId, index )
	
	AddQuestNumText(sceneId, x540013_g_ScriptId, x540013_g_MissionName, 3)
		
end

function x540013_ProcEventEntry( sceneId , selfId , targetId , state , index )
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x540013_g_MissionName)
		AddQuestText(sceneId,x540013_g_ContinueInfo)
	EndQuestEvent()
	--DispatchQuestEventList(sceneId, selfId, targetId)
	DispatchQuestInfo(sceneId,selfId,-1,x540013_g_ScriptId,-1)
	SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,0)
	return
end

--********************
--����������
--**********************************
function x540013_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

function x540013_ProcAccept( sceneId, selfId )

	local nStep = GetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID)

	if 0 == nStep then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�������ܵȼ��޷��ָ�,��ȷ��Ҫ����ͻ�ʶ�������?")
		EndQuestEvent()
		SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,1)
		DispatchQuestInfo(sceneId,selfId,-1,x540013_g_ScriptId,-1)
	elseif 1 == nStep then
		local abilityLevel = QueryPlayerAbility( sceneId, selfId, 6 )
		if abilityLevel >0 then
			-- ɾ�������
			local nRet = DelAbility( sceneId,selfId, 6 )
			if nRet == 1 then
				DeleteTitle(sceneId, selfId, x540013_g_TitleId)
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "��������"..x540013_g_AbilityName)
				DispatchQuestTips(sceneId, selfId)
				EndQuestEvent(sceneId)
				Msg2Player(sceneId,selfId,"��������"..x540013_g_AbilityName,8,2)
				--TipsToPlayer (sceneId,selfId,"��������"..x540013_g_AbilityName)
	
				-- ������سƺ�����
				if IsHaveQuestNM( sceneId, selfId, x540013_g_Title_Quest_ScriptId) > 0 then
					DelQuest( sceneId, selfId, x540013_g_Title_Quest_ScriptId)
				end
			end
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "����δѧϰ"..x540013_g_AbilityName)
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			--TipsToPlayer (sceneId,selfId,"����δѧϰ"..x540013_g_AbilityName)
		end
	end
end
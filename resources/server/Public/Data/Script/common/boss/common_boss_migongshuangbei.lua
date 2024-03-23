
x310001_g_ScriptId = 310001
x310001_g_MissionName = "����ȡս��ӻ���" 
x310001_g_ContinueInfo="\t�����Ĵ�������У�Ҫȥ�Թ��Ļ���ҪС��Ϊ�ϡ�\n\t�ҿ���Ϊ������#Gս��ӻ�#W����˵���ܰ���ǿ�����У����ô������㾫���ӣ�������ս���л�ø��������ɡ�\n\t#Rע�⣺#Gս��ӻ�#W����#G��߼���������ŵ���������´����ͬ·������·������·���������֡����˹�#W��Ч��\n\tÿ����ȡ�����#G1Сʱ#W���ڸõ������е�#R����ӳ�#W��ս��ӻ���ʱ��#G���Ե���#W��Ҳ����#G�ͱ�ľ���ӳɽ�����ͬ����#W��\n\t��#Rÿ����ֻ������ȡ1��#W��������š�"

x310001_g_SuccessInfo="����ȡ��һСʱ��ս��ӻ�"
--x310001_g_MD_AcceptTime = 210
--x310001_g_MD_Rounds = 211
x310001_g_LevelLimit = 20
x310001_g_ImpactId = 7041

x310001_g_RoundLimit= 1


x310001_SceneList = {2,3,4,5,6,7,8,9,10,11,86,87,89,186,187,189,286,287,289,386,387,389,73,173,273,373,74,174,274,374,68,168,268,368}

--�о��¼�
--**********************************

function x310001_NextDayReset(sceneId, selfId)
	local lastDay = GetQuestData(sceneId, selfId, MD_MIGONG_SHUANGBEI_DATE[1], MD_MIGONG_SHUANGBEI_DATE[2], MD_MIGONG_SHUANGBEI_DATE[3])

	if lastDay ~= GetDayOfYear() then
		SetQuestData(sceneId, selfId, MD_MIGONG_SHUANGBEI_DATE[1], MD_MIGONG_SHUANGBEI_DATE[2], MD_MIGONG_SHUANGBEI_DATE[3], 0)
		SetQuestData(sceneId, selfId, MD_MIGONG_SHUANGBEI_ROUNDS[1], MD_MIGONG_SHUANGBEI_ROUNDS[2], MD_MIGONG_SHUANGBEI_ROUNDS[3], 0)
	end
end

function x310001_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

	local country = GetCurCountry(sceneId, selfId)
	local nDefaultCamp = GetSceneCamp( sceneId )-16

	if GetLevel( sceneId, selfId ) < x310001_g_LevelLimit then 
		return
	end
	if country == nDefaultCamp then 
		x310001_NextDayReset(sceneId, selfId)
		AddQuestNumText(sceneId, x310001_g_ScriptId, x310001_g_MissionName, 3, 1)
	else 
			return
	end
	
end

function x310001_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x310001_g_MissionName)
		AddQuestText(sceneId,x310001_g_ContinueInfo)
	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, targetId, x310001_g_ScriptId, -1)

end

--����������

--**********************************

function x310001_ProcAcceptCheck(sceneId, selfId, NPCId)
	local curRounds = GetQuestData(sceneId, selfId, MD_MIGONG_SHUANGBEI_ROUNDS[1], MD_MIGONG_SHUANGBEI_ROUNDS[2], MD_MIGONG_SHUANGBEI_ROUNDS[3])

	if curRounds >= x310001_g_RoundLimit then
		local str = "���Ѿ���ȡ��ս��ӻ��ˣ�����������";
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,str,8,2)
		return 0
	end

	if GetLevel( sceneId, selfId ) < x310001_g_LevelLimit then 
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "�ȼ�������");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"�ȼ�������",8,2)
		return 0
	end


	return 1
end

function x310001_ProcAccept( sceneId, selfId )
	local rounds = GetQuestData(sceneId, selfId, MD_MIGONG_SHUANGBEI_ROUNDS[1], MD_MIGONG_SHUANGBEI_ROUNDS[2], MD_MIGONG_SHUANGBEI_ROUNDS[3])

	local today = GetDayOfYear() 

	if IsHaveSpecificImpact(sceneId, selfId,x310001_g_ImpactId) > 0 then
		local lastContinuance = GetImpactContinuanceByDataIndex(sceneId, selfId, x310001_g_ImpactId) - GetImpactContinuanceElapsed(sceneId, selfId, x310001_g_ImpactId) 
		if lastContinuance >= 0 then
			SetImpactContinuanceByDataIndex( sceneId, selfId, x310001_g_ImpactId, lastContinuance+60*60*1000 )
			ResetImpactContinuanceElapsed(sceneId, selfId, x310001_g_ImpactId)

			SetQuestData(sceneId, selfId, MD_MIGONG_SHUANGBEI_DATE[1], MD_MIGONG_SHUANGBEI_DATE[2], MD_MIGONG_SHUANGBEI_DATE[3], today)
			SetQuestData(sceneId, selfId, MD_MIGONG_SHUANGBEI_ROUNDS[1], MD_MIGONG_SHUANGBEI_ROUNDS[2], MD_MIGONG_SHUANGBEI_ROUNDS[3], rounds+1)

			RefreshImpactByDataIndex(sceneId, selfId,x310001_g_ImpactId)
		end
	else
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x310001_g_ImpactId, 0)

		SetQuestData(sceneId, selfId, MD_MIGONG_SHUANGBEI_DATE[1], MD_MIGONG_SHUANGBEI_DATE[2], MD_MIGONG_SHUANGBEI_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_MIGONG_SHUANGBEI_ROUNDS[1], MD_MIGONG_SHUANGBEI_ROUNDS[2], MD_MIGONG_SHUANGBEI_ROUNDS[3], rounds+1)
	end
	
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, x310001_g_SuccessInfo);
	EndQuestEvent(sceneId);
	DispatchQuestTips(sceneId,selfId);
	Msg2Player(sceneId,selfId,x310001_g_SuccessInfo,8,2)
	
	x310001_EnterScene(sceneId,selfId)
	
end

function x310001_EnterScene(sceneId, selfId)
	local sign=0;
	for i, item in x310001_SceneList do
		if sceneId == item then sign = 1 break end
	end

	if sign == 1 then
		if IsHaveSpecificImpact( sceneId, selfId, x310001_g_ImpactId ) > 0 then
			--local curMult = GetWanFaExpMult(sceneId, selfId)
			SetWanFaExpMult( sceneId, selfId, 0.5 )
			
		end
	else
        SetWanFaExpMult( sceneId, selfId, 0 )
    end
end
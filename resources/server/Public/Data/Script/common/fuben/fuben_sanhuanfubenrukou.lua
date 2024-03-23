
x700096_g_ScriptId = 700096
x700096_g_MissionName = "�����顿��������"

x700096_g_LevelLimited = 20

x700096_g_LimitMember = 1
--�����������
x700096_g_SanHuan_Fuben_Len = 7
x700096_g_SanHuan_Fuben_list = { 
							{name="�����顿ף��ׯ",		scriptid = 700030, nlevel = 60},
							{name="�����顿�����",		scriptid = 700003, nlevel = 50},
							{name="�����顿�����",		scriptid = 700024, nlevel = 40},
							{name="�����顿������",		scriptid = 700028, nlevel = 20},
							{name="�����顿̽��ս��Ĺ",	scriptid = 700084, nlevel = 35},
							{name="�����顿ӡ�Ⱥ�",	    scriptid = 700087, nlevel = 55},
							{name="�����顿���õ�����",	scriptid = 700090, nlevel = 45},
							
						}

function x700096_ProcEnumEvent( sceneId, selfId, targetId, index )
	
	local nLevel = GetLevel(sceneId, selfId)
	if nLevel < x700096_g_LevelLimited then

		return
		
	end	

	AddQuestNumText(sceneId,x700096_g_ScriptId, x700096_g_MissionName, 14, 0)
end

function x700096_ProcEventEntry( sceneId , selfId , targetId , state , nExt )
	
	if nExt == nil then
		return
	end


	x700096_DispatchSanHuanMode(sceneId , selfId , targetId  , nExt)
	
end

function x700096_DispatchSanHuanMode(sceneId , selfId , targetId  , nExt)
	if nExt == nil then
		return
	end

	local nLevel = GetLevel(sceneId, selfId)
	if nLevel < x700096_g_LevelLimited then
		return
	end

	
	if nExt == 0 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\tֻҪ��ͼ���־ͬ���ϵ�����һ����ӣ��ҾͿ��������ǽ���������������ø߶��ֵ�����п��ܻ�ü���ϡ�е��������\n\t���⣬�����ﻹ�е���������������������Ӣ��ģʽ�������������Ѷȣ�������������������ѡ��")
			AddQuestNumText(sceneId,x700096_g_ScriptId, "�����顿��ͨ��������", 14, 1)
			AddQuestNumText(sceneId,x700096_g_ScriptId, "�����顿������������", 14, 2)
			--AddQuestNumText(sceneId,x700096_g_ScriptId, x700096_g_MissionName.."������ģʽ", 14, 3)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, targetId)
	else
		x700096_DispatchDetailMode(sceneId , selfId , targetId  , nExt)
	end
	
end

function x700096_DispatchDetailMode(sceneId , selfId , targetId  , nExt)

	if nExt == nil then
		return
	end

	BeginQuestEvent(sceneId)
		
		if nExt ==1 then
			AddQuestText(sceneId,"#Y"..x700096_g_MissionName.."��ͨģʽ")
		elseif nExt ==2 then
			AddQuestText(sceneId,"#Y"..x700096_g_MissionName.."����ģʽ")
		elseif nExt ==3 then
			AddQuestText(sceneId,"#Y"..x700096_g_MissionName.."������ģʽ")
		else
			return
		end
		--������Ϣ
		AddQuestText(sceneId,"\n\tÿ��һ�����Խ���21����ͨ����������ʹ�������������������������3�α��ܵ���������������ͬʱ���3����ͨ�����Ľ�����������ʣ������������������3�Σ��򲻿�ʹ�������")

		if nExt ==1 then
			AddQuestText(sceneId,"\n#Y����ʱ�䣺#Wȫ�쿪�ţ�\n#Y������ʾ��#W3�����ϵĶ��飬���ܽ���ø�����\n#Y����˵����#W����������У�����Ի�ô������齱����")
		elseif nExt ==2 then
			AddQuestText(sceneId,"\n#Y����ʱ�䣺#Wȫ�쿪�ţ�\n#Y������ʾ��#W3�����ϵĶ��飬���ܽ���ø�����\n#Y����˵����#W����������У�����Ի����ͨ��������3���ľ��齱����")
		elseif nExt ==3 then
			AddQuestText(sceneId,"����˵����"..x700096_g_MissionName.."������ģʽ")
		else
			return
		end

		x700096_SaveSanhuanFubenTalkMode(sceneId, selfId, nExt)


	EndQuestEvent()

	DispatchQuestInfo(sceneId, selfId, targetId, x700096_g_ScriptId, -1);
end

---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x700096_ProcAcceptCheck( sceneId, selfId, NPCId )

	local nLevel = GetLevel(sceneId, selfId)
	if nLevel < x700096_g_LevelLimited then
		return 0
	end

    return 1
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x700096_ProcAccept( sceneId, selfId )
	if x700096_CheckCommonTeamCondition(sceneId, selfId)<=0 then
		return
	end

	local nMode = x700096_GetSanhuanFubenTalkMode(sceneId, selfId)

	if nMode<=0 or nMode>3 then
		return
	end

	local nRandom = x700096_GetRandom(sceneId, selfId)

	if nRandom<=0 then
		return
	end

	local nScriptId = x700096_g_SanHuan_Fuben_list[7].scriptid --TEST
	
	nMode = nMode -1
	CallScriptFunction(FUBEN_COMMON_SCRIPT, "OnRequestEnterFuben", sceneId, selfId, nMode, 0, nScriptId, 0);
	
	--д��־
	local msg = format("x700096_ProcAccept ����, sceneId = %d, name = %s, nMode = %d, nScriptId = %d", sceneId,GetName(sceneId, selfId), nMode,nScriptId);

	WriteLog(1,msg)



end

function x700096_GetRandom(sceneId, selfId)
	local nLevel = x700096_GetTeamMinLevel(sceneId, selfId)
	
	local randomlist = {}
	local nCount = 0
	local nIndex = 0
	for i, item in x700096_g_SanHuan_Fuben_list do
		nIndex = nIndex + 1
		if nLevel>=item.nlevel then
			nCount = nCount +1
			randomlist[nCount] = nIndex
		end
	end

	if nCount ==0 then
		return 0
	end

	return randomlist[random(1,nCount)]
end

function x700096_GetTeamMinLevel(sceneId, selfId)

	if IsTeamLeader(sceneId, selfId) <= 0 then
		local nLevel = GetLevel(sceneId, selfId)
		return nLevel
	end

	local teamid = GetTeamId(sceneId, selfId);
	local teamnum = GetTeamSize(sceneId, selfId);
	local nearteamnum = GetNearTeamCount(sceneId, selfId);
	
	local nMinLevel = 200
	for i = 0, teamnum - 1 do
		local memberId = GetNearTeamMember(sceneId, selfId, i);
		
		local nLevel = GetLevel(sceneId, memberId)

		if nLevel<nMinLevel then
			nMinLevel = nLevel
		end
	end

	return nMinLevel
end

function x700096_CheckCommonTeamCondition(sceneId, selfId)
	local teamid = GetTeamId(sceneId, selfId);
	local teamnum = GetTeamSize(sceneId, selfId);
	local nearteamnum = GetNearTeamCount(sceneId, selfId);

	local str = "";
	local bPassed = 1;

	if IsTeamLeader(sceneId, selfId) <= 0 then
		str	= "�㲻�Ƕӳ���"
		bPassed = 0
	elseif x700081_CheckAllMemberNear( sceneId,selfId) <= 0 then
		str	= "��Ҫ���еĶ����ڸ�����"
		bPassed = 0
	elseif teamid < 0 then
		str	= "�㲻�ڶ����У�"
		bPassed = 0
	elseif teamnum < x700096_g_LimitMember then
		str	= format("��Ķ��鲻��%d�ˣ�", x700096_g_LimitMember)
		bPassed = 0
	elseif nearteamnum < x700096_g_LimitMember then
		str	= format("�������Ѳ���%d�ˣ�", x700096_g_LimitMember)
		bPassed = 0
	else

		for i = 0, teamnum - 1 do
			local memberId = GetNearTeamMember(sceneId, selfId, i);
			
			local nLevel = GetLevel(sceneId, memberId)

			if nLevel<x700096_g_LevelLimited then
				local strName = GetName(sceneId, memberId)
				str = format("����%s�ȼ�����%d�������ܽ��븱����", strName,x700096_g_LevelLimited)
				bPassed = 0

				break;
			end
		end
		

	end

	if bPassed == 1 then
		return 1;
	else
		if str ~= "" then
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return 0;
		end
	end


	return 1;
end


function x700096_SaveSanhuanFubenTalkMode(sceneId, selfId, nValue)
	SetQuestData(sceneId, selfId, MD_SANHUAN_FUBEN_TALK_MODE[1], MD_SANHUAN_FUBEN_TALK_MODE[2], MD_SANHUAN_FUBEN_TALK_MODE[3], nValue)
end

function x700096_GetSanhuanFubenTalkMode(sceneId, selfId)
	return GetQuestData(sceneId, selfId, MD_SANHUAN_FUBEN_TALK_MODE[1], MD_SANHUAN_FUBEN_TALK_MODE[2], MD_SANHUAN_FUBEN_TALK_MODE[3])
end



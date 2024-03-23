
x300358_g_ScriptId 					= 300358
x300358_g_MissionName				= "����ѯ��ͽʣ��ʱ�䡿"

function x300358_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId,x300358_g_ScriptId,x300358_g_MissionName,3,0)
end

function x300358_ProcEventEntry(sceneId, selfId, targetId)
	if GetLevel(sceneId, selfId) >= 50 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x300358_ShituQuery(sceneId, selfId))
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, targetId, x300358_g_ScriptId, -1)
	else
		Msg2Player(sceneId, selfId, "50�����ϵ���Ҳſ�����ͽ�ܡ�", 8, 3)
	end
end

function x300358_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end

function x300358_ProcAccept(sceneId, selfId, targetId)
	return 1
end

function x300358_ShituQuery(sceneId, selfId)
	if IsPrenticeFull(sceneId, selfId) == 1 then
		return "\t��ͽ����������������ʦ���ƺ�����ȡ�����ͽ�ܣ�ÿλʦ���������ȡ5λͽ�ܡ�"
	end
	
	--�Ƿ����3�� �õ����һ�����ͽ�ܵ�ʱ��,�õ�����ʱ��������
	local iTime = GetPrenticeBetrayTime(sceneId, selfId)
	if iTime > 0 and iTime < MASTER_PRENTICE_TIME_LIMIT*3600 then
		return format("\t��������һ����ͽ�ܻ���Ҫ%dСʱ%d�֡�", x300358_Time(iTime))
	end
	
	return "\t�����ھͿ�����ȡ��һλͽ���ˣ�������ͨ������ͽ�ܹ�����Ѱͽ�ܡ�"
end

function x300358_Time(iTime)
	iTime = iTime/60
	local h = iTime/60
	local m = mod(iTime, 60)
	if m >= 1 then
		h = h+1
	end
	if m < 1 then
		m = 60
	end
	return MASTER_PRENTICE_TIME_LIMIT-floor(h), 60-floor(m)
end
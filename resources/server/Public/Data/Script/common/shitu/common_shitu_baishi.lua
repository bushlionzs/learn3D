
x300361_g_ScriptId 					= 300361
x300361_g_MissionName				= "��ʦͽ����ͽ"
x300361_g_MasterLevelMin		= 50
x300361_g_PrenticeLevelMin	= 20
x300361_g_MasterPrenticeLevelConfine	= 10

function x300361_IsCanBaiShi(sceneId, selfId)

	if (IsCaptain(sceneId, selfId)) ~= 1 then
		return "ֻ�жӳ�����������ͽ��";
	end
	--�Ƿ������ ���Ҷ���������2��
	if (GetTeamSize(sceneId, selfId) ~= 2) then
		return "��Ҫʦͽ������������ҡ�";
	end
	
	--�õ�ͽ�ܵ�objID
	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	if IsInDist(sceneId, selfId, targetId, 10) ~= 1 then
		return "ʦͽ���˱��붼�ڴ˸�����";
	end
	
	--ʦ���ĵȼ�Ҫ��
	if GetLevel(sceneId, selfId) < x300361_g_MasterLevelMin then
		return format("ʦ���ȼ�����ﵽ%d����", x300361_g_MasterLevelMin);
	end
	
	--ͽ�ܵĵȼ�Ҫ��
	if GetLevel(sceneId, targetId) < x300361_g_PrenticeLevelMin then
		return format("ͽ�ܵȼ��ﵽ%d�����ܰ�ʦ��", x300361_g_PrenticeLevelMin);
	end
	
	--ʦͽ�ȼ����Ҫ��
	if GetLevel(sceneId, selfId) - GetLevel(sceneId, targetId) < x300361_g_MasterPrenticeLevelConfine then
		return format("ʦ�������ͽ�ܸ�%d�����ܰ�ʦ��", x300361_g_MasterPrenticeLevelConfine);
	end

	--�Ƿ�������ʦ��
	if IsHaveMaster(sceneId, targetId) == 1 then
		return "�Է��Ѿ���ʦ�����޷���ʦ��";
	end
	
	--�Ƿ����3�� �õ����һ�����ͽ�ܵ�ʱ��,�õ�����ʱ��������
	local iTime = GetPrenticeBetrayTime(sceneId, selfId);
	iTime = iTime/3600;
	if iTime > 0 and iTime < MASTER_PRENTICE_TIME_LIMIT then
		return format("ʦ��%.1fСʱ������ٴ���ͽ��", MASTER_PRENTICE_TIME_LIMIT - iTime);
	end
	
	--�Ƿ����3�� �õ����һ�θ�ʦ�������ϵ��ʱ��,�õ�����ʱ��������
	iTime = GetMasterBetrayTime(sceneId, targetId);
	iTime = iTime/3600;	--����תΪСʱ
	if iTime > 0 and iTime < MASTER_PRENTICE_TIME_LIMIT then
		return format("ͽ��%.1fСʱ������ٴΰ�ʦ��", MASTER_PRENTICE_TIME_LIMIT - iTime);
	end
	
	--ͽ�ܵ�����
	if IsPrenticeFull(sceneId, selfId) == 1 then
		return "ͽ���Ѿ����ˡ�";
	end

	--�����Ǻ���
	if IsFriend(sceneId, selfId, targetId) ~= 1 or IsFriend(sceneId, targetId, selfId) ~= 1 then
		return "�໥��Ϊ���Ѳ��ܰ�ʦ��";
	end	

	--�Ƿ��Ƿ���
	if IsSpouses(sceneId, selfId, targetId) == 1 then
		return  "���޹�ϵ���ܰ�ʦ��";
	end
	
	--�Է��Ƿ������ʦ��
	if IsMaster(sceneId, selfId, targetId) == 1 then
		return "�Է������ʦ�����޷���ʦ��";
	end

	return nil;

end

function x300361_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId,x300361_g_ScriptId,x300361_g_MissionName,3,0);
end

function x300361_ProcEventEntry(sceneId, selfId, targetId)

	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, "#Y��ʦͽ����ͽ#W\n\t���������Ϊʦ��������ʱ��������������Ϊ���ӵ����������������ʦ������Ϊ�ӳ������Ұ������ǽ��ʦͽ��ϵ��\n\t����ʦͽ��ϵ��ʦͽ˫�����ܹ����#G���ֺô�#W����Ҫ���Ŷ��");
	EndQuestEvent();
	DispatchQuestInfo(sceneId, selfId, targetId, x300361_g_ScriptId,-1);
	
end

function x300361_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

function x300361_ProcAccept(sceneId, selfId, targetId)

	local ret = x300361_IsCanBaiShi(sceneId, selfId);
	
	if ret ~= nil then
		Msg2Player(sceneId,selfId,ret,8,2)
		Msg2Player(sceneId,selfId,ret,8,3)
	else
		--�õ�ͽ�ܵ�objID
		local targetId = GetTeamSceneMember(sceneId, selfId, 0);
		Aprentice(sceneId, targetId, selfId);		--��ʦ
		Msg2Player(sceneId, selfId, "��ϲ��ͽ�ɹ���ʦ��ҪŬ���̺����ͽ����",8,2);
		Msg2Player(sceneId, targetId, "��ϲ��ʦ�ɹ���",8,2);
		Msg2Player(sceneId, selfId, "��ϲ��ͽ�ɹ���ʦ��ҪŬ���̺����ͽ����",8,3);
		Msg2Player(sceneId, targetId, "��ϲ��ʦ�ɹ���",8,3);
	end

end
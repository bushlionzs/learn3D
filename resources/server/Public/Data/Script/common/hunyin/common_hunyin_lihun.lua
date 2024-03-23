
-------------------------
--***********************
--Const
--***********************
-------------------------

x800007_g_ScriptId 					= 800007
x800007_g_MissionName				= "���"
x800007_g_CostMoneyUnmarry	= 55555
x800007_g_FriendPointNotify = 100
x800007_SkillId							= 149

-------------------------
--***********************
--Define
--***********************
-------------------------

x800007_CHAT_TYPE_NORMAL	= 0
x800007_CHAT_TYPE_SYSTEM	= 4

x800007_OK							= 0
x800007_ERROR_UNKNOWN		= -1
x800007_FAILED_CAPTAIN	= 1
x800007_FAILED_TEAM			= 2
x800007_FAILED_MARRIGE	= 3
x800007_FAILED_DISTANCE	= 4
x800007_FAILED_MONEY		= 5

-------------------------
--***********************
--IsCanUnmarry
--***********************
-------------------------

function x800007_IsCanUnmarry(sceneId, selfId) 
	
	if (IsCaptain(sceneId, selfId)) ~= 1 then
		return x800007_FAILED_CAPTAIN;
	end

	if (GetTeamSize(sceneId, selfId) ~= 2) then
		return x800007_FAILED_TEAM;		--��ӳ�Ա�������˲������
	end
	
	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	if IsSpouses(sceneId, selfId, targetId) ~= 1 then
		return x800007_FAILED_MARRIGE;
	end
	
	if IsInDist(sceneId, selfId,targetId,10) ~= 1 then
		return x800007_FAILED_DISTANCE;		--˫���������10�ײ��������
	end
	
	local money;
	if GetSex(sceneId, selfId) == 0 then		--�Լ������з����Է������з�
		money = GetMoney(sceneId, targetId);
	else
		money = GetMoney(sceneId, selfId);
	end
	
	if money < x800007_g_CostMoneyUnmarry then
		return x800007_FAILED_MONEY;
	end
	
	return x800007_OK;
	
end

-------------------------
--***********************
--DoUnmarry
--***********************
-------------------------

function x800007_DoUnmarry(sceneId, selfId, NPCId)

	local ret = x800007_SafeUnmarryCheck(sceneId, selfId, NPCId, 1);
	if ret ~= x800007_OK then
		return ret;
	end
	
	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	local ManId;
	if GetSex(sceneId, selfId) == 1 then
		ManId = selfId;
	else
		ManId = targetId;
	end
	
	if CostMoney(sceneId, ManId, x800007_g_CostMoneyUnmarry,305) == -1 then
		return x800007_FAILED_MONEY;
	end
	
	--��˫���ĺ��Ѷȶ����ó�X��XΪ�ܹ������Է����ߵ����ֵ
	SetFriendPoint(sceneId, selfId, targetId, x800007_g_FriendPointNotify);
	SetFriendPoint(sceneId, targetId, selfId, x800007_g_FriendPointNotify);
	
	--ɾ�����޼���,Ŀǰû�У��ݲ����
	DelSkill(sceneId, selfId, x800007_SkillId);
	DelSkill(sceneId, targetId, x800007_SkillId);
	
	--ɾ��˫���ĳƺ�"ĳĳ�ķ��""ĳĳ������"
	AwardSpouseTitle(sceneId, selfId, "");
	AwardSpouseTitle(sceneId, targetId, "");
		
	--�����촰�ڸ���Ů����ʾ��
	local Msg = "��ָ������ˡ�\n ʧȥ���޳ƺš�\n ʧȥ���з��޼��ܡ�";
	Msg2Player(sceneId, selfId, Msg, x800007_CHAT_TYPE_NORMAL);
	Msg2Player(sceneId, targetId, Msg, x800007_CHAT_TYPE_NORMAL);
	
	--���һ��,˫�����
	UnMarry(sceneId, selfId, targetId);
	
	return x800007_OK;
end

-------------------------
--***********************
--SafeUnmarryCheck
--***********************
-------------------------

function x800007_SafeUnmarryCheck(sceneId, selfId, targetId, bDirect)

	local ret 	= x800007_IsCanUnmarry(sceneId, selfId);
	local str 	= "�Ѿ���顣";
	
	if ret == x800007_OK then
		str = format("ȷ��Ҫ��飿\n�з���Ҫ֧��%d��Ǯ��", x800007_g_CostMoneyUnmarry);
	
	elseif ret == x800007_FAILED_CAPTAIN then
		str = "ֻ�жӳ����������顣";
	
	elseif ret == x800007_FAILED_TEAM then
		str = "�������飬����Ů˫���������һ���������ҡ�";
	
	elseif ret == x800007_FAILED_MARRIGE then
		str = "���ǻ�û����أ�ΪɶҪ�����";
	
	elseif ret == x800007_FAILED_DISTANCE then
		str = "ֻ�ж��˶��ߵ�����߲ſ�����顣";
	
	elseif ret == x800007_FAILED_MONEY then
		str = format("�з���ҪЯ��%d��Ǯ������顣", x800007_g_CostMoneyUnmarry);
	end
	
	if ret == x800007_OK and bDirect == 1 then
		return ret;
	end
	
	BeginQuestEvent(sceneId);
	
		AddQuestText(sceneId, str);
	
	EndQuestEvent();

	if ret == x800007_OK then
		DispatchQuestInfo(sceneId, selfId, targetId, x800007_g_ScriptId);
	else
		DispatchQuestEventList(sceneId, selfId, targetId);
	end
	
	return ret;
	
end

-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x800007_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x800007_g_ScriptId, x800007_g_MissionName);
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x800007_ProcEventEntry(sceneId, selfId, targetId)

	x800007_SafeUnmarryCheck(sceneId, selfId, targetId, 0);
	
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x800007_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x800007_ProcAccept(sceneId, selfId, targetId)

	local ret = x800007_DoUnmarry(sceneId, selfId, targetId);
	
	if ret == x800007_OK then
		return
	end
	
	local str = "ERROR��";
	
	if ret == x800007_FAILED_MONEY then
		str = "�۳���Ǯ����";
	end
	
	BeginQuestEvent(sceneId);
	
		AddQuestText(sceneId, str);
	
	EndQuestEvent();

	DispatchQuestEventList(sceneId, selfId, targetId);

end
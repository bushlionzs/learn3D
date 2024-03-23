-------------------------
--***********************
--Const
--***********************
-------------------------

x800010_g_ScriptId 			= 800010
x800010_g_MissionName		= "��ʦ"
x800010_g_LevelMin			= 40
x800010_g_ItemId				= 10280001
x800010_g_MoralPoint		= 100
x800010_g_MoralPointUp	= 1000
x800010_g_LevelOver			= 45
x800010_g_FriendLess		= 300

-------------------------
--***********************
--Define
--***********************
-------------------------

x800010_CHAT_TYPE_NORMAL	= 0
x800010_CHAT_TYPE_SYSTEM	= 4

x800010_OK									= 0
x800010_ERROR_UNKNOWN				= -1
x800010_FAILED_TEAM					= 1
x800010_FAILED_LEVEL				= 2
x800010_FAILED_MASTER				= 3
x800010_FAILED_BAG_MASTER		= 4
x800010_FAILED_BAG_PRENTICE	= 5

-------------------------
--***********************
--IsCanChuShi
--***********************
-------------------------

function x800010_IsCanChuShi(sceneId, selfId)

	if (GetTeamSize(sceneId, selfId) ~= 2) then
		return x800010_FAILED_TEAM;
	end

	--�õ�ͽ�ܵ�objID
	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	if IsMaster(sceneId, targetId, selfId) ~= 1 then
		return x800010_FAILED_MASTER;
	end
	
	if GetLevel(sceneId, targetId) < x800010_g_LevelMin then
		return x800010_FAILED_LEVEL;
	end
	
	--A��B�ı����зֱ�������һ����ͨ��Ʒ�Ŀո�
	if (GetItemIsEmpty(sceneId, selfId) == -1) then
		return x800010_FAILED_BAG_MASTER;
	end
		
	if (GetItemIsEmpty(sceneId, targetId) == -1) then
		return x800010_FAILED_BAG_PRENTICE;
	end
	
	return x800010_OK;

end

-------------------------
--***********************
--DoChuShi
--***********************
-------------------------

function x800010_DoChuShi(sceneId, selfId, NPCId)

	local ret = x800010_SafeChuShiCheck(sceneId, selfId, NPCId, 1);

	if ret ~= x800010_OK then
		return ret;
	end
	
	--�õ�ͽ��objID
	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	--��˫���ı����зֱ���뽱������
	if (TryRecieveItem(sceneId, selfId, x800010_g_ItemId, 1) == -1) then
		return x800010_FAILED_BAG_MASTER;
	end
	
	if (TryRecieveItem(sceneId, targetId, x800010_g_ItemId, 1) == -1) then
		return x800010_FAILED_BAG_PRENTICE;
	end
	
	FinishAprentice(sceneId, targetId, selfId);	--ȡ��ʦͽ��ϵ
	
	--�õ�ʦ�µ�
	local point = GetMasterMoralPoint(sceneId, selfId);
	
	--��ʦ������ʦ�µ���
	point = point + x800010_g_MoralPoint;
	SetMasterMoralPoint(sceneId, selfId, point);
	
	--��ʦ������ʾ��Ϣ
	local Msg = format(" ��ʦ�ɹ���\n ��õ���ʦ�Ƕ�һ����\n �õ�ʦ�µ���%d��", x800010_g_MoralPoint);
	
	--����ۻ�ʦ�µ����ﵽһ����ֵ,��óƺ�
	if point >= x800010_g_MoralPointUp then
		--��óƺţ���û�����
		--AwardTitle(sceneId,selfId,0,0)
		Msg = format("%s\n ��óƺ�%s", Msg, "�ƺ���");
	end

	Msg2Player(sceneId, selfId, Msg, x800010_CHAT_TYPE_NORMAL);
	
	--AwardTitle(sceneId, targetId, 0, 0);
	--��ͽ�ܵ���ʾ��Ϣ
	Msg = format("��ʦ�ɹ���\n ��õ���ʦ�Ƕ�һ����\n ��óƺţ�%s֮ͽ��", GetName(sceneId, selfId));
	Msg2Player(sceneId, targetId, Msg, x800010_CHAT_TYPE_NORMAL);
	
	if GetLevel(sceneId, selfId) < x800010_g_LevelOver or GetFriendPoint(sceneId, selfId, targetId) < x800010_g_FriendLess then
		--FinishAprentice(sceneId, targetId, selfId);	--ȡ��ʦͽ��ϵ
		--��ʦ������ʾ��Ϣ
		local Msg = format("��ʦ�ɹ���\n �����ѺöȲ���%d����ͽ�ܵȼ�����%d����û�н�����", x800010_g_FriendLess, x800010_g_LevelOver);
		Msg2Player(sceneId, selfId, Msg, x800010_CHAT_TYPE_NORMAL);
		--��ͽ�ܵ���ʾ��Ϣ
		Msg2Player(sceneId, targetId, Msg, x800010_CHAT_TYPE_NORMAL);
	end	
	
	return x800010_OK;

end

-------------------------
--***********************
--SafeChuShiCheck
--***********************
-------------------------

function x800010_SafeChuShiCheck(sceneId, selfId, NPCId, bDirect)

	local ret 	= x800010_IsCanChuShi(sceneId, selfId);
	local str 	= "�ɹ���ʦ��";
	
	if ret == x800010_OK then
		str = "ȷ��Ҫ��ʦ��";
	
	elseif ret == x800010_FAILED_TEAM then
		str = "��Ҫʦͽ������������ҡ�";
	
	elseif ret == x800010_FAILED_LEVEL then
		str = format("ͽ�ܵȼ��ﵽ%d�����ܳ�ʦ��", x800010_g_LevelMin);
	
	elseif ret == x800010_FAILED_MASTER then
		str = "���ǲ���ʦͽ��ϵ��";
	
	elseif ret == x800010_FAILED_BAG_MASTER then
		str = format("%s������һ��������λ��", selfId);
		
	elseif ret == x800010_FAILED_BAG_PRENTICE then
		local targetId = GetTeamSceneMember(sceneId, selfId, 0);
		str = format("%s������һ��������λ��", targetId);
	
	end
	
	if ret == x800010_OK and bDirect == 1 then
		return ret;
	end
	
	BeginQuestEvent(sceneId);
	
		AddQuestText(sceneId, str);
	
	EndQuestEvent();

	if ret == x800010_OK then
		DispatchQuestInfo(sceneId, selfId, NPCId, x800010_g_ScriptId);
	else
		DispatchQuestEventList(sceneId, selfId, NPCId);
	end
	
	return ret;
	
end

-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x800010_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x800010_g_ScriptId, x800010_g_MissionName);
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x800010_ProcEventEntry(sceneId, selfId, targetId)

	x800010_SafeChuShiCheck(sceneId, selfId, targetId, 0);
	
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x800010_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x800010_ProcAccept(sceneId, selfId, targetId)

	local ret = x800010_DoChuShi(sceneId, selfId, targetId);
		
	if ret == x800010_OK then
		return
	end

end
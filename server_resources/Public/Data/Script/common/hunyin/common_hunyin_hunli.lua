
-------------------------
--***********************
--Const
--***********************
-------------------------

x800049_g_ScriptId 					= 800049
x800049_g_MissionName				= "���������ٰ����"
x800049_g_NeedGold					= 18888

-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x800049_ProcEnumEvent(sceneId, selfId, targetId, eventId, index)
	AddQuestNumText(sceneId, x800049_g_ScriptId, x800049_g_MissionName,3);
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x800049_ProcEventEntry(sceneId, selfId, targetId)
	BeginQuestEvent(sceneId);
	local Readme_1 = "#Y���������ٰ����#W#r"
	local Readme_2 = "\t�ɼ�˼���У������ǿ���ͨ���ٰ�������ٻ�������ѣ������ǻ���һ�ò��ܻ������ף����#r #r"
	local Readme_3 = "�����Ҫ�����Ҫ�����ĸ�������#r #r"
	local Readme_4 = "1.��������������ż���#G2�˶���#W��#r #r"
	local Readme_5 = "2.��������������ż����#G��һ��#W��#r #r"
	local Readme_6 = "3.����ͬһ��żֻ�ٰܾ�#Gһ�λ���#W��#r #r"
	local Readme_7 = format("4.��ֻ��ӵ��#Y#{_MONEY%d}�𿨣��ֽ�#W��ɾٰ�#Gһ�λ���#W��#r #r", x800049_g_NeedGold)
	local Readme_8 = "\tһ�ж�׼�����˾Ϳ��Ծ��л����ˡ�"
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6..Readme_7..Readme_8
	AddQuestText(sceneId, Readme);
	EndQuestEvent();
	DispatchQuestInfo(sceneId, selfId, targetId, x800049_g_ScriptId, -1);
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x800049_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x800049_ProcAccept(sceneId, selfId, targetId)
	local str = x800049_DoWedding(sceneId, selfId, targetId)
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
		Msg2Player(sceneId,selfId,str,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
	end
end

function x800049_DoWedding(sceneId, selfId, targetId)
	
	if 0 >= IsEnoughGold(sceneId, selfId, x800049_g_NeedGold) then
		return format("�ܱ�Ǹ����Ҫ#{_MONEY%d}�𿨣��ֽ𣩲ſ��Ծٰ����", x800049_g_NeedGold)
	end
	if IsMarried(sceneId, selfId) ~= 1 then
		return "�ܱ�Ǹ������δ��飬�޷�ѡ�����"
	end
	if HasTeam(sceneId, selfId) ~= 1 then
		return "�ܱ�Ǹ������δ��������޷�ѡ�����"
	end
	
	if (GetTeamSize(sceneId, selfId) < 2) then
		return "�ܱ�Ǹ�������ڵĶ����г�ԱС��2�ˣ��޷�ѡ�����";
	end
	
	if (GetTeamSize(sceneId, selfId) > 2) then
		return "�ܱ�Ǹ�������ڵĶ����г�Ա����2�ˣ��޷�ѡ�����";
	end

	local targetId = GetTeamSceneMember(sceneId, selfId, 0);
	
	if IsInDist(sceneId, selfId, targetId, 10) ~= 1 then
		return "�ܱ�Ǹ�����Ķ��Ѳ��ڸ������޷�ѡ�����";
	end
	
	if IsSpouses(sceneId, selfId, targetId) ~= 1 then
		return "�ܱ�Ǹ�������ڵĶ����г�Ա���Ƿ��޹�ϵ���޷�ѡ�����";
	end		
	
	if IsHaveWedding(sceneId, selfId) == 1 then
		return "�ܱ�Ǹ�����Ѿ��ٰ�����񣬲������ٴξٰ졣";
	end
	local nEvent = 46 --�ٰ����
	local bMutex, errCode = IsMutex(sceneId, selfId, nEvent) 
	if bMutex == 1 then
		return "�ܱ�Ǹ������ǰ��״̬�����Ծٰ����";
	end 
	
	bMutex, errCode = IsMutex(sceneId, targetId, nEvent) 
	if bMutex == 1 then
		return "�ܱ�Ǹ������ż��ǰ��״̬�����Ծٰ����";
	end
	local IsSelfMan = GetSex(sceneId, selfId);
	local ManId;
	local WomanId;
	if IsSelfMan > 0 then
		ManId = selfId;
		WomanId = targetId;
	else
		ManId = targetId;
		WomanId = selfId;
	end
	
	if 0 >= x800049_CostGold(sceneId, selfId) then
		return "��Ǯ����";
	end
	
	DoWedding(sceneId, selfId)
	DoWedding(sceneId, targetId)
	
	local szMsg = format("������%s��%s�Ĵ�ϲ֮�գ�ϣ�����ܲμӣ����������ף����", GetName( sceneId, WomanId ), GetName(sceneId, ManId));
	local MoneyReceiver = GetName( sceneId, WomanId )
	WeddingInvite(sceneId, selfId, MoneyReceiver, szMsg)
	WeddingInvite(sceneId, targetId, MoneyReceiver, szMsg)
	
	DispelImpact(sceneId, ManId)
	DispelImpact(sceneId, WomanId)
	
	SetPlayerPatrolId(sceneId, ManId, 0);
	SetPlayerPatrolId(sceneId, WomanId, 0);

	Teleport(sceneId, WomanId, 123, 58)
	Teleport(sceneId, ManId, 123, 64)
	SendSpecificImpactToUnit(sceneId, ManId, ManId, ManId, 7642, 0);--Ѳ��
	SendSpecificImpactToUnit(sceneId, WomanId, WomanId, WomanId, 7642, 0);--Ѳ��
	SendSpecificImpactToUnit(sceneId, ManId, ManId, ManId, 7641, 0);--��
	SendSpecificImpactToUnit(sceneId, WomanId, WomanId, WomanId, 7640, 0);--��
	local mamName = GetName(sceneId, ManId)
	local womamName = GetName(sceneId, WomanId)
	local str = format("��ϲ%s��%s�ٰ��˱�����Ļ��񣬲��յ���������ѵ�ף����", mamName, womamName);
	LuaAllScenceM2Wrold (sceneId, str, CHAT_MAIN_WINDOW, 1)
	
	SendSpecificImpactToUnit(sceneId, ManId, ManId, ManId, 8537, 0);--������Ʒ
	
	return nil
	
end

function x800049_CostGold(sceneId, selfId)
	local nGoldMode = GetGoldMode( sceneId, selfId )
	
	if nGoldMode == 1 then		--�����ֽ����
		if CostMoney(sceneId, selfId, 2, x800049_g_NeedGold,305) == -1 then
			return 0
		end
	
	elseif nGoldMode == 0 then	--���Ƚ𿨽���
		if CostMoney(sceneId, selfId, 3, x800049_g_NeedGold,305) == -1 then
			if CostMoney(sceneId, selfId, 2, x800049_g_NeedGold,305) == -1 then
				return 0
			end
		end
	else						--δ֪�Ľ���ģʽ
		return 0
	end
	return 1
end
function DispelImpact(sceneId, selfId)
	DispelSpecificImpact(sceneId, selfId, 7902)
	DispelSpecificImpact(sceneId, selfId, 10330)
	for i = 4211, 4220 do
		DispelSpecificImpact(sceneId, selfId, i)
	end
end
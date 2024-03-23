
-------------------------
--***********************
--Const
--***********************
-------------------------

x300316_g_ScriptId 					= 300316
x300316_g_MissionName				= "�����ҡ���������"
x300316_g_NeedMoney = 20000
x300316_g_GameId						= 1023 --ʮ��ħ������
x300316_g_GameOpenId				= 1031 --�淨����
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x300316_ProcEnumEvent(sceneId, selfId, targetId, eventId, index)
	if GetGameOpenById(x300316_g_GameOpenId) <= 0 then
		return
	end
	AddQuestNumText(sceneId, x300316_g_ScriptId, x300316_g_MissionName,3);
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x300316_ProcEventEntry(sceneId, selfId, targetId)
	BeginQuestEvent(sceneId);
	local Readme1 = "#Y�����ҡ���������#W#r\t���ȼ����а��һ������70��ʱ��ÿ�ܶ���#R20��00-21��00֮��#W���ڱ���#R����ǰ5���ǹ�������#W��#G�������#W�����������﷢����������"
	local Readme2 =  "�����#G������֮��#W������#G��λ�����еĶ�λ#Wͬ�ⷢ��#R��������#W��#G40����#W�����߹��񽫻��յ�#G������#W��������߹������150�ˣ������Զ�ʧ�ܡ�#G��Ӧ����#W�Ĺ��񳬹�#R70%#W����#R�����Զ���̨#W��ͬʱ#R�������Զ���̨#W���������İ���Զ���Ϊ#G�¹�����#W���ð������Ϊ#G�µĹ���#W��"
	local Readme  =  Readme1..Readme2
	AddQuestText(sceneId, Readme);
	EndQuestEvent();
	DispatchQuestInfo(sceneId, selfId, targetId, x300316_g_ScriptId, -1);
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x300316_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x300316_ProcAccept(sceneId, selfId, targetId)
	local str = x300316_DoCountryDelate(sceneId, selfId, targetId)
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
		Msg2Player(sceneId,selfId,str,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
	end
end

function x300316_DoCountryDelate(sceneId, selfId, targetId)
	
	local guildId = GetGuildID(sceneId, selfId)
	if 0 > guildId then
		return "�ܱ�Ǹ������û�м����ᡣ"
	end
	
	local guildLevel,memNum,guidEXP = GetGuildSimpleData(guildId)
	if 2 > guildLevel then
		return "�ܱ�Ǹ�����İ��ȼ�̫�͡�"
	end
	
	if 5 ~= GetGuildOfficial(sceneId, selfId) then
		return "�ܱ�Ǹ��ֻ�а������ܷ�������"
	end
	
	if 30 > GetLevel(sceneId, selfId) then
		return "�ܱ�Ǹ�����ĵȼ�̫�͡�"
	end
	
	local week = GetWeek()
	local hour,minute,second = GetHourMinSec()
	if (2 == week and hour >= 20 and hour < 21) then
	else
		return "�ܱ�Ǹ�������ܶ�20��00-21��00ʱǰ�����е�����"
	end
	
	-- if GetGameOpenById(x300316_g_GameId) ~= 1 then
		-- return "ʮ��ħ��ȫ������ɱ�����ܵ���������"
	-- end
	
	local remainTime = ((20 - hour)*3600 + (59 - minute)*60)*1000
	CountryDelateReq(sceneId, selfId, remainTime)
	
	return nil
	
end

function x300316_OnCountryDelateRet(sceneId, selfId, retCode)
	if 0 == retCode then
		Msg2Player(sceneId,selfId,"��������ɹ��ύ��",8,3)
		Msg2Player(sceneId,selfId,"��������ɹ��ύ��",8,2)
	elseif 1 == retCode then
		Msg2Player(sceneId,selfId,"���ܵ����Լ���",8,3)
		Msg2Player(sceneId,selfId,"���ܵ����Լ���",8,2)
	elseif 2 == retCode then
		Msg2Player(sceneId,selfId,"�Ѿ��ڵ����С�",8,3)
		Msg2Player(sceneId,selfId,"�Ѿ��ڵ����С�",8,2)
	elseif 3 == retCode then
		Msg2Player(sceneId,selfId,"û���㹻�İ������ߡ�",8,3)
		Msg2Player(sceneId,selfId,"û���㹻�İ������ߡ�",8,2)
	elseif 4 == retCode then
		Msg2Player(sceneId,selfId,"û�й�����",8,3)
		Msg2Player(sceneId,selfId,"û�й�����",8,2)
	elseif 5 == retCode then
		Msg2Player(sceneId,selfId,"��Ҫ���ߵİ��������",8,3)
		Msg2Player(sceneId,selfId,"��Ҫ���ߵİ��������",8,2)
	end
	return 1
end

-- �ر��淨GMָ��
function x300316_SetClose( param0, param1, param2)
    SetCountryQuestData( param0, 1, CD_INDEX_MOJUN_KILL_COUNT1, 0)
    SetGameOpenById( 1021, 0)
    SetGameOpenById( 1023, 0)
    SetGameOpenById( 1031, 0)
end

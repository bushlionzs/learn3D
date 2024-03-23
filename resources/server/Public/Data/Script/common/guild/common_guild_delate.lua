
-------------------------
--***********************
--Const
--***********************
-------------------------

x300828_g_ScriptId 					= 300828
x300828_g_MissionName				= "����᡿��������"
x300828_g_NeedMoney = 20000
x300828_g_GameId					= 1032
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x300828_ProcEnumEvent(sceneId, selfId, targetId, eventId, index)
	if 0 > GetGuildID(sceneId, selfId) then
		return
	end
	if GetGameOpenById(x300828_g_GameId) <= 0 then
		return
	end
	AddQuestNumText(sceneId, x300828_g_ScriptId, x300828_g_MissionName,3);
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x300828_ProcEventEntry(sceneId, selfId, targetId)
	BeginQuestEvent(sceneId);
	local Readme = "#Y����᡿��������#W#r\tÿ���յ�21��00-22��00֮�䣬30�����ϵİ���Ա��������������Է���#R��������#W��\n\t��������Ҫ����#Y20������#W�����#G�������#W�ĵ�����#G���߱����Ա#W�����յ�#G������#W����Ӧ�����İ���#R����90%#W����#R�����Զ���̨#W��Ϊ����Ա��ͬʱ#R�������Զ���Ϊ����#W��\n\t���Ƿ�Ҫ��������"
	AddQuestText(sceneId, Readme);
	EndQuestEvent();
	DispatchQuestInfo(sceneId, selfId, targetId, x300828_g_ScriptId, -1);
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x300828_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x300828_ProcAccept(sceneId, selfId, targetId)
	local str = x300828_DoGuildDelate(sceneId, selfId, targetId)
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
		Msg2Player(sceneId,selfId,str,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
	end
end

function x300828_DoGuildDelate(sceneId, selfId, targetId)
	
	if 30 > GetLevel(sceneId, selfId) then
		return "�ܱ�Ǹ�����ĵȼ�̫�͡�"
	end
	
	if 0 > GetGuildID(sceneId, selfId) then
		return "�ܱ�Ǹ������û�м����ᡣ"
	end
	
	local week = GetWeek()
	local hour,minute,second = GetHourMinSec()
	if 0 == week and hour == 21 then
	else
		return "�ܱ�Ǹ����������21��00-22��00ʱǰ�����е�����"
	end
	
	if 0 >= IsEnoughMoney(sceneId, selfId, x300828_g_NeedMoney) then
		return "�ܱ�Ǹ�������������㣬���ܽ��е�����"
	end
	
	local nLairdMapId = GetGuildLairdSceneId(GetGuildID(sceneId, selfId))
	if nLairdMapId > 0 then
		return "�ܱ�Ǹ�����ռ���ᣬ���ܽ��е���������"
	end
	
	local remainTime = ( 59 - minute) * 60 * 1000
	GuildDelateReq(sceneId, selfId, remainTime)
	return nil
	
end

function x300828_OnGuildDelateRet(sceneId, selfId, retCode)
	
	if 0 == retCode then
		Msg2Player(sceneId,selfId,"��������ɹ��ύ",8,3)
		Msg2Player(sceneId,selfId,"��������ɹ��ύ",8,2)
	elseif 1 == retCode then
		Msg2Player(sceneId,selfId,"���ܵ����Լ�",8,3)
		Msg2Player(sceneId,selfId,"���ܵ����Լ�",8,2)
	elseif 2 == retCode then
		Msg2Player(sceneId,selfId,"�Ѿ��ڵ�����",8,3)
		Msg2Player(sceneId,selfId,"�Ѿ��ڵ�����",8,2)
	elseif 3 == retCode then
		Msg2Player(sceneId,selfId,"���ܵ�������",8,3)
		Msg2Player(sceneId,selfId,"���ܵ�������",8,2)
	elseif 4 == retCode then
		Msg2Player(sceneId,selfId,"����Ա����������̫��",8,3)
		Msg2Player(sceneId,selfId,"����Ա����������̫��",8,2)
	elseif 5 == retCode then
		Msg2Player(sceneId,selfId,"���ܵ�������֮��",8,3)
		Msg2Player(sceneId,selfId,"���ܵ�������֮��",8,2)
	elseif 6 == retCode then
		Msg2Player(sceneId,selfId,"���ܵ�����ȸ֮��",8,3)
		Msg2Player(sceneId,selfId,"���ܵ�����ȸ֮��",8,2)
	end
	
	if 0 == retCode then
		if 0 >= SpendMoney(sceneId, selfId, x300828_g_NeedMoney) then
			return -1;
		end
	end
	
	return 1
end
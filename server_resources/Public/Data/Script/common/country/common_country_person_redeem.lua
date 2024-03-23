
x300637_g_ScriptId          		= 300637
x300637_g_Leader_Index      		= 5
x300637_g_MissionName       		="�����ҡ���ȡ�������"
x300637_g_HaveBonusThisWeek			="\t�������Ѿ���ȡ����������ˣ�ÿ��ֻ����ȡһ�Ρ�"
x300637_g_LevelError				="\t���ź���ֻ�в�����60������Ҳſ�����ȡ���������"
x300637_g_WeekDayError				="\t���ź���ֻ�����ղſ�����ȡ���������"
x300637_g_ExploitError				="\t���ź���ֻ�б��ܹ�ѫֵ������18�����Ҳ�����ȡ���������"
x300637_g_BonusTips					="#Y�����ҡ���ȡ�������\n\t#W�����������Ϊ�˽���������ͨ����Թ��������Ĺ��ס�\n\tÿ���Ƿ��ܼ�����#Gһ��������#W����ֱ��Ӱ���������Ķ��١�\n\t�ȼ�������#G60#W��ÿ�ܹ�ѫֵ������#G18#W�����ң�ÿ#G����#W��������������ȡ���������#r \n\t�����ܵĹ�ѫֵΪ#G%d#W\n\t�����ܹ������#G%d#W����������\n\t�������ϵ�ͳ�ƣ�����������ȡ��\n\t#R%d#W��#R%d#W��#R%d#W�Ľ�\n\t#R%d#W��#R%d#W��#R%d#W��������"
x300637_g_GiveBonusTips				="#Y��ȡ��������ɹ��������#R%d#Y��#R%d#Y��#R%d#Y�Ľ𿨵Ľ�����"
x300637_g_GiveBonusTips1			="#Y��ȡ��������ɹ��������#R%d#Y��#R%d#Y��#R%d#Y���������Ľ�����"
x300637_g_GameOpenID				= 1033
x300637_g_GamePlayID				= 1342


----------------------------------------------------------------------------------------------
--ȡ�ý�����ǵڼ�����
----------------------------------------------------------------------------------------------
function x300637_GetCurrentWeek()
	
	--ȡ�ý��������
	local nCurrentTime = (GetCurrentTime()+8*3600)/86400 - 4  --�������
	local nWeek = floor(nCurrentTime / 7)		 --�������,��ȡ��
	return nWeek
end

----------------------------------------------------------------------------------------------
--ȡ�����һ��0
----------------------------------------------------------------------------------------------
function x300637_GetLastWeek(sceneId,selfId)
	
	return GetQuestData(sceneId,selfId,MD_COUNTRY_PERSON_REDEEM_WEEK[1],MD_COUNTRY_PERSON_REDEEM_WEEK[2],MD_COUNTRY_PERSON_REDEEM_WEEK[3])
	
end

----------------------------------------------------------------------------------------------
--�������һ��
----------------------------------------------------------------------------------------------
function x300637_SetLastWeek(sceneId,selfId)
	
	SetQuestData(sceneId,selfId,MD_COUNTRY_PERSON_REDEEM_WEEK[1],MD_COUNTRY_PERSON_REDEEM_WEEK[2],MD_COUNTRY_PERSON_REDEEM_WEEK[3],x300637_GetCurrentWeek())
end

----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x300637_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	--��Ƿ���
	if GetGameOpenById(x300637_g_GameOpenID) ~= 1 then
		return
	end
	
	--ˢ��BUF�б�
	AddQuestNumText(sceneId,x300637_g_ScriptId,x300637_g_MissionName,3,-1);
	
end

----------------------------------------------------------------------------------------------
--Ĭ���¼�
----------------------------------------------------------------------------------------------
function x300637_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

	--��Ƿ���
	if GetGameOpenById(x300637_g_GameOpenID) ~= 1 then
		return
	end
--
--	--����Ƿ����
--	if x300637_GetCurrentWeek() == x300637_GetLastWeek(sceneId,selfId) then
--		BeginQuestEvent(sceneId)
--			AddQuestText(sceneId,x300637_g_HaveBonusThisWeek)
--	    EndQuestEvent(sceneId)
--		DispatchQuestEventList(sceneId,selfId,targetId)
--		return
--	end
--
--	--���ȼ�
	local level = GetLevel(sceneId,selfId)
--	if level < 60 then
--		BeginQuestEvent(sceneId)
--			AddQuestText(sceneId,x300637_g_LevelError)
--	    EndQuestEvent(sceneId)
--		DispatchQuestEventList(sceneId,selfId,targetId)
--		return
--	end
--	
--	--���ʱ��
	local nWeekDay = GetWeek()
--	if nWeekDay ~= 0 then
--		BeginQuestEvent(sceneId)
--			AddQuestText(sceneId,x300637_g_WeekDayError)
--	    EndQuestEvent(sceneId)
--		DispatchQuestEventList(sceneId,selfId,targetId)
--		return
--	end
--	
--	--��鹦ѫ
	local nExploit = GetExploit(sceneId,selfId)
--	if nExploit < 18 then
--		BeginQuestEvent(sceneId)
--			AddQuestText(sceneId,x300637_g_ExploitError)
--	    EndQuestEvent(sceneId)
--		DispatchQuestEventList(sceneId,selfId,targetId)
--		return
--	end
--	
	--���㽱��
	local money1 = 0		--��
	local money2 = 0		--����
	if nExploit >=18 then
		money1 = 2*1000   --��
		money2 = 8*1000   --����
	else
		money1 = 0
		money2 = 0
    end

	local ding = 0
	local liang = 0
	local wen = 0
	local ding1 = 0
	local liang1 = 0
	local wen1 = 0
	
	local lastweek = GetQuestData(sceneId,selfId,MD_NEIZHENG_WEEK[1],MD_NEIZHENG_WEEK[2],MD_NEIZHENG_WEEK[3])
	local round = GetQuestData(sceneId,selfId,MD_NEIZHENG_WEEKCOUNT[1],MD_NEIZHENG_WEEKCOUNT[2],MD_NEIZHENG_WEEKCOUNT[3])
	
	if round < 0 then 
		round = 0 
	end
	
	--����ܲ�ƥ��
	if x300637_GetCurrentWeek() ~= lastweek then
		round = 0
	end
	
	money1 = money1 + round*1000
	money2 = money2 + round*4*1000
	 local	ding = floor( money1 / (1000*1000) )
	 local	liang = floor( mod(money1,1000*1000)/ 1000 )
	 local  wen = mod(money1,1000)
	 local	ding1 = floor( money2 / (1000*1000) )
	 local	liang1 = floor( mod(money2,1000*1000)/ 1000 )
	 local  wen1 = mod(money2,1000)
	--��ʽ�������Ϣ
	local msg = format(x300637_g_BonusTips,nExploit,round,ding,liang,wen,ding1,liang1,wen1)

	--���м��ͨ��������ʾ��������
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,msg)
    EndQuestEvent(sceneId)
	DispatchQuestInfoNM( sceneId, selfId, targetId, x300637_g_ScriptId, x300637_g_ScriptId)
end

----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x300637_ProcAcceptCheck( sceneId, selfId, NPCId )
	
	--��Ƿ���
	if GetGameOpenById(x300637_g_GameOpenID) ~= 1 then
		return 0
	end
	
    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300637_ProcAccept( sceneId, selfId )
	
	--��Ƿ���
	if GetGameOpenById(x300637_g_GameOpenID) ~= 1 then
		return
	end
	
	--����Ƿ����
	if x300637_GetCurrentWeek() == x300637_GetLastWeek(sceneId,selfId) then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x300637_g_HaveBonusThisWeek)
	    EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

	--���ȼ�
	local level = GetLevel(sceneId,selfId)
	if level < 60 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x300637_g_LevelError)
	    EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end
	
	--���ʱ��
	local nWeekDay = GetWeek()
	if nWeekDay ~= 0 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x300637_g_WeekDayError)
	    EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end
	
	--��鹦ѫ
	local nExploit = GetExploit(sceneId,selfId)
	if nExploit < 18 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x300637_g_ExploitError)
	    EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end
	
	--���㽱��
	local money1 = 2*1000		--��
	local money2 = 8*1000		--����
	local ding = 0
	local liang = 0
	local wen = 0
	local ding1 = 0
	local liang1 = 0
	local wen1 = 0
	
	
	local lastweek = GetQuestData(sceneId,selfId,MD_NEIZHENG_WEEK[1],MD_NEIZHENG_WEEK[2],MD_NEIZHENG_WEEK[3])
	local round = GetQuestData(sceneId,selfId,MD_NEIZHENG_WEEKCOUNT[1],MD_NEIZHENG_WEEKCOUNT[2],MD_NEIZHENG_WEEKCOUNT[3])
	
	if round < 0 then 
		round = 0 
	end
	
	--����ܲ�ƥ��
	if x300637_GetCurrentWeek() ~= lastweek then
		round = 0
	end
	
	money1 = money1 + round*1000
	money2 = money2 + round*4*1000
	
	--��ӽ�
	AddMoney(sceneId,selfId,3,money1,x300637_g_ScriptId)
	
	--�������
	AddMoney(sceneId,selfId,0,money2,x300637_g_ScriptId)
	
	--������ȡ�������
	x300637_SetLastWeek(sceneId,selfId)
	
	--��¼�淨��־
	GamePlayScriptLog(sceneId,selfId,x300637_g_GamePlayID)

	--��ȡ������ʾ
	 local	ding = floor( money1 / (1000*1000) )
	 local	liang = floor( mod(money1,1000*1000)/ 1000 )
	 local  wen = mod(money1,1000)
	 local	ding1 = floor( money2 / (1000*1000) )
	 local	liang1 = floor( mod(money2,1000*1000)/ 1000 )
	 local  wen1 = mod(money2,1000)
		
	local msg  = format(x300637_g_GiveBonusTips,ding,liang,wen)
	local msg1 = format(x300637_g_GiveBonusTips1,ding1,liang1,wen1)
	Msg2Player(sceneId, selfId, msg, 0, 3)
	Msg2Player(sceneId, selfId, msg1, 0, 3)
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300637_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300637_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x300637_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x300637_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x300637_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x300637_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x300637_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

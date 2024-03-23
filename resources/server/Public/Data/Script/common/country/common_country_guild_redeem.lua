 x300638_g_ScriptId = 300638
x300638_LevelLess		=	60
x300638_NeedExploit		= 28
x300638_g_DayLimited	=	1
x300638_g_GameId		=	1034
x300638_g_MissionName = "�����ҡ���ȡ������"
x300638_g_TalkContent = "\t����������ÿһ��Ϊ����������׵İ��ڶ�������ȡ�Ľ�����\n\t����#G�ɹ���������#W�Ĵ�����#G���ս��ս��#W����ֱ��Ӱ��ÿ�ܰ������Ķ��١�\n\t�ȼ�������#G60#W��ÿ�ܹ�ѫֵ������#G28��#W����ң�ÿ#G����#W��������������ȡһ�ܵİ�������\n\tȷ��Ҫ��ȡ��������#r"

--**********************************
--�о��¼�
--**********************************

function x300638_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if GetGameOpenById(x300638_g_GameId)<=0 then
		return
	end
	
	--if GetLevel(sceneId, selfId) < x300638_LevelLess then
	--	return
	--end
	
	
	
	AddQuestNumText(sceneId, x300638_g_ScriptId, x300638_g_MissionName,3)
			
end

function x300638_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	
	if GetGameOpenById(x300638_g_GameId)<=0 then
		return
	end

	BeginQuestEvent(sceneId)

		--������Ϣ
		local nGold = 2*1000
	local nSilver = 10*1000

	-- ���ս
		local nCount1 = GetQuestData(sceneId, selfId, MD_GUILD_BHZ_WIN_COUNT[1], MD_GUILD_BHZ_WIN_COUNT[2], MD_GUILD_BHZ_WIN_COUNT[3])
		local nCount2 = GetQuestData(sceneId, selfId, MD_GUILD_BHZ_LOSE_COUNT[1], MD_GUILD_BHZ_LOSE_COUNT[2], MD_GUILD_BHZ_LOSE_COUNT[3])
		local nCount3 = GetQuestData(sceneId, selfId, MD_GUILD_BHZ_PING_COUNT[1], MD_GUILD_BHZ_PING_COUNT[2], MD_GUILD_BHZ_PING_COUNT[3])

		if x300638_IsNewPeroid(sceneId, selfId,MD_GUILD_BHZ_DATE)>0 then
			nCount1 = 0
			nCount2 = 0
			nCount3 = 0
		end

	--x300638_ShowTips(sceneId, selfId,format("nCount2 = %d, nCount3 = %d",nCount2,nCount3))

		nGold = nGold + nCount1*4*1000+(nCount2+nCount3)*2*1000
		nSilver = nSilver + nCount1*20*1000+ (nCount2+nCount3)*10*1000

	--���ս end

	--������� start
		local nCount4 = GetQuestData(sceneId, selfId, MD_GUILD_YB_WEEK_COUNT[1], MD_GUILD_YB_WEEK_COUNT[2], MD_GUILD_YB_WEEK_COUNT[3])
	
		if x300638_IsNewPeroid(sceneId, selfId,MD_GUILD_YB_DATE)>0 then
		
			nCount4 = 0
		end
		local nExploit = GetExploit(sceneId,selfId)
		local award1 = "������ӵ��#G"..nExploit.."��#W��ѫֵ";
		local award2 = "�����ܲμ���#G"..(nCount1+nCount2+nCount3).."��#W���ս";
		local award3 = "�����ܳɹ�������#G"..nCount4.."��#W����";
		nGold = nGold + nCount4*1*1000
		nSilver = nSilver + nCount4*5*1000
		local ding=0
		local liang=0
		local wen=0
		ding = floor( nGold / (1000*1000) )
		liang = floor( mod(nGold,1000*1000)/ 1000 )
		wen = mod(nGold,1000)
		local award4 = format("�������#R%d��%d��%d��#W�𿨽���", ding,liang,wen);
		ding = floor( nSilver / (1000*1000) )
		liang = floor( mod(nSilver,1000*1000)/ 1000 )
		wen = mod(nSilver,1000)
		local award5 = format("�������#R%d��%d��%d��#W��������", ding,liang,wen);
		AddQuestText(sceneId,"#Y"..x300638_g_MissionName)
		local blank=" #r";
		AddQuestText(sceneId,x300638_g_TalkContent..blank..award1..blank..award2..blank..award3..blank..award4..blank..award5)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, NPCId, x300638_g_ScriptId, -1);
		if  nExploit < 28 then
			local Readme_1 = "�������#R0��0��0��#W�𿨽���"
			local Readme_2 = "�������#R0��0��0��#W��������"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x300638_g_TalkContent..blank..award1..blank..award2..blank..award3..blank..Readme_1..blank..Readme_2)
			EndQuestEvent()
			DispatchQuestInfo(sceneId, selfId, NPCId, x300638_g_ScriptId, -1);
		end
	
end

---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x300638_ProcAcceptCheck( sceneId, selfId, NPCId )
	if GetGameOpenById(x300638_g_GameId)<=0 then
		return
	end
	if GetGuildID(sceneId, selfId)<0 then
		x300638_ShowTips(sceneId, selfId, "�ܱ�Ǹ������û�м����ᣬ������ȡ��")
		return 0;
	end

	if GetLevel(sceneId, selfId) < x300638_LevelLess then
		x300638_ShowTips(sceneId, selfId, format("�ܱ�Ǹ���ȼ�δ�ﵽ%d����������ȡ��",x300638_LevelLess))
		return 0;
	end

	if GetWeek() ~=0 then
		x300638_ShowTips(sceneId, selfId, "�ܱ�Ǹ��ֻ����������ȡ��")
		return 0;
	end

	if GetExploit(sceneId,selfId) < x300638_NeedExploit then
		x300638_ShowTips(sceneId, selfId, format("�ܱ�Ǹ�����Ĺ�ѫֵ����%d��������ȡ��",x300638_NeedExploit))
		return 0;
	end

	if x300638_GetDayCount(sceneId, selfId)>=x300638_g_DayLimited then
		x300638_ShowTips(sceneId, selfId,"�ܱ�Ǹ������������ȡ���������ˣ�������������")
		return 0;
	end

    return 1
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x300638_ProcAccept( sceneId, selfId )
	if GetGameOpenById(x300638_g_GameId)<=0 then
		return
	end

	x300638_OnGiveReward( sceneId, selfId)
	
end

function x300638_OnGiveReward( sceneId, selfId)

	
	
	local nGold = 2*1000
	local nSilver = 10*1000

	-- ���ս
	local nCount1 = GetQuestData(sceneId, selfId, MD_GUILD_BHZ_WIN_COUNT[1], MD_GUILD_BHZ_WIN_COUNT[2], MD_GUILD_BHZ_WIN_COUNT[3])
	local nCount2 = GetQuestData(sceneId, selfId, MD_GUILD_BHZ_LOSE_COUNT[1], MD_GUILD_BHZ_LOSE_COUNT[2], MD_GUILD_BHZ_LOSE_COUNT[3])
	local nCount3 = GetQuestData(sceneId, selfId, MD_GUILD_BHZ_PING_COUNT[1], MD_GUILD_BHZ_PING_COUNT[2], MD_GUILD_BHZ_PING_COUNT[3])

	if x300638_IsNewPeroid(sceneId, selfId,MD_GUILD_BHZ_DATE)>0 then
		nCount1 = 0
		nCount2 = 0
		nCount3 = 0
	end

	--x300638_ShowTips(sceneId, selfId,format("nCount2 = %d, nCount3 = %d",nCount2,nCount3))

	nGold = nGold + nCount1*4*1000+(nCount2+nCount3)*2*1000
	nSilver = nSilver + nCount1*20*1000+ (nCount2+nCount3)*10*1000

	--���ս end

	--������� start
	local nCount4 = GetQuestData(sceneId, selfId, MD_GUILD_YB_WEEK_COUNT[1], MD_GUILD_YB_WEEK_COUNT[2], MD_GUILD_YB_WEEK_COUNT[3])
	
	if x300638_IsNewPeroid(sceneId, selfId,MD_GUILD_YB_DATE)>0 then
		
		nCount4 = 0
	end

	--x300638_ShowTips(sceneId, selfId,format("nCount2 = %d, nCount3 = %d nCount4 =%d",nCount2,nCount3,nCount4))

	nGold = nGold + nCount4*1*1000
	nSilver = nSilver + nCount4*5*1000
	--������� end



	AddMoney(sceneId, selfId, 3, nGold)
	AddMoney(sceneId, selfId, 1, nSilver)

	x300638_ShowTips(sceneId, selfId,format("���%d����",nGold/1000))
	x300638_ShowTips(sceneId, selfId,format("���%d������",nSilver/1000))

	x300638_SetDayCount(sceneId, selfId)

	-- write log
	GamePlayScriptLog(sceneId, selfId, 1351)  --�淨Log

	local str = format("x300638_OnGiveReward guid = %x, name=%s, nGold= %d, nSilver=%d, nCount1 = %d, nCount2 = %d, nCount3 = %d nCount4 =%d",GetPlayerGUID( sceneId,selfId ),GetName(sceneId, selfId),nGold,nSilver,nCount1,nCount2,nCount3,nCount4)
	WriteLog(1, str)
	
end



function x300638_SaveGuildWeekResult(sceneId,guildId, nValue)
-------------------------------------------
--@param nValue: 0:���� 1��ƽ�� 2��ʤ��
-------------------------------------------
	if GetGameOpenById(x300638_g_GameId)<=0 then
		return
	end
	if nValue ~=0 and nValue ~=1 and nValue ~=2 then
		return
	end

	local sceneType = GetSceneType(sceneId) ;
	if sceneType~=2 then
		local str = format("x300638_SaveGuildWeekResult not Banghuizhan Scene= %d",sceneId)
		WriteLog(1, str)
		return
	end

	local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local selfId = GetScenePlayerObjId( sceneId,i)
        if selfId >= 0 then
            local nGuildId = GetGuildID( sceneId,selfId )
            if nGuildId == guildId then
				
				local nCount1 = GetQuestData(sceneId, selfId, MD_GUILD_BHZ_WIN_COUNT[1], MD_GUILD_BHZ_WIN_COUNT[2], MD_GUILD_BHZ_WIN_COUNT[3])
				local nCount2 = GetQuestData(sceneId, selfId, MD_GUILD_BHZ_LOSE_COUNT[1], MD_GUILD_BHZ_LOSE_COUNT[2], MD_GUILD_BHZ_LOSE_COUNT[3])
				local nCount3 = GetQuestData(sceneId, selfId, MD_GUILD_BHZ_PING_COUNT[1], MD_GUILD_BHZ_PING_COUNT[2], MD_GUILD_BHZ_PING_COUNT[3])
				if x300638_IsNewPeroid(sceneId, selfId,MD_GUILD_BHZ_DATE)>0 then
					SetQuestData(sceneId, selfId, MD_GUILD_BHZ_DATE[1], MD_GUILD_BHZ_DATE[2], MD_GUILD_BHZ_DATE[3], GetDayOfYear())
					SetQuestData(sceneId, selfId, MD_GUILD_BHZ_WIN_COUNT[1], MD_GUILD_BHZ_WIN_COUNT[2], MD_GUILD_BHZ_WIN_COUNT[3], 0)
					SetQuestData(sceneId, selfId, MD_GUILD_BHZ_LOSE_COUNT[1], MD_GUILD_BHZ_LOSE_COUNT[2], MD_GUILD_BHZ_LOSE_COUNT[3], 0)
					SetQuestData(sceneId, selfId, MD_GUILD_BHZ_PING_COUNT[1], MD_GUILD_BHZ_PING_COUNT[2], MD_GUILD_BHZ_PING_COUNT[3], 0)
					nCount1 = 0
					nCount2 = 0
					nCount3 = 0
				end
				
				if nValue==2 then
					nCount1 = nCount1 + 1
					SetQuestData(sceneId, selfId, MD_GUILD_BHZ_WIN_COUNT[1], MD_GUILD_BHZ_WIN_COUNT[2], MD_GUILD_BHZ_WIN_COUNT[3], nCount1)
				elseif nValue==1 then
					nCount2 = nCount2 + 1
					SetQuestData(sceneId, selfId, MD_GUILD_BHZ_LOSE_COUNT[1], MD_GUILD_BHZ_LOSE_COUNT[2], MD_GUILD_BHZ_LOSE_COUNT[3], nCount2)
				elseif nValue==0 then
					nCount3 = nCount3 + 1
					SetQuestData(sceneId, selfId, MD_GUILD_BHZ_PING_COUNT[1], MD_GUILD_BHZ_PING_COUNT[2], MD_GUILD_BHZ_PING_COUNT[3], nCount3)
				end
            end
        end
    end

end

function x300638_SaveGuildYunBiaoMD(sceneId, selfId)
	if GetGameOpenById(x300638_g_GameId)<=0 then
		return
	end
	
	local nCount1 = GetQuestData(sceneId, selfId, MD_GUILD_YB_WEEK_COUNT[1], MD_GUILD_YB_WEEK_COUNT[2], MD_GUILD_YB_WEEK_COUNT[3])
	
	if x300638_IsNewPeroid(sceneId, selfId,MD_GUILD_YB_DATE)>0 then
		SetQuestData(sceneId, selfId, MD_GUILD_YB_DATE[1], MD_GUILD_YB_DATE[2], MD_GUILD_YB_DATE[3], GetDayOfYear())
		SetQuestData(sceneId, selfId, MD_GUILD_YB_WEEK_COUNT[1], MD_GUILD_YB_WEEK_COUNT[2], MD_GUILD_YB_WEEK_COUNT[3], 0)
		nCount1 = 0
	end
	
	nCount1 = nCount1 + 1
	SetQuestData(sceneId, selfId, MD_GUILD_YB_WEEK_COUNT[1], MD_GUILD_YB_WEEK_COUNT[2], MD_GUILD_YB_WEEK_COUNT[3], nCount1)
	
end




---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x300638_IsNewPeroid(sceneId, selfId, md_date)



	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, md_date[1], md_date[2],md_date[3] );
	
	if today>=lastday then
		local nWeek = GetWeek()
		if nWeek==0 then
			nWeek =7
		end
		if (today-lastday)>=nWeek then  --���������֮��
			return 1
		end
	else
		return 1
	end

	return 0


end


function x300638_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x300638_GetDayCount(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_GUILD_JINTIE_DATE[1], MD_GUILD_JINTIE_DATE[2],MD_GUILD_JINTIE_DATE[3] );
	
	if lastday ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, MD_GUILD_JINTIE_DAYCOUNT[1], MD_GUILD_JINTIE_DAYCOUNT[2],MD_GUILD_JINTIE_DAYCOUNT[3] );
	return daycount;
end

---------------------------------------------------------------------------------------------------
--���õ������
---------------------------------------------------------------------------------------------------
function x300638_SetDayCount(sceneId, selfId)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_GUILD_JINTIE_DATE[1], MD_GUILD_JINTIE_DATE[2], MD_GUILD_JINTIE_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_GUILD_JINTIE_DATE[1], MD_GUILD_JINTIE_DATE[2], MD_GUILD_JINTIE_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_GUILD_JINTIE_DAYCOUNT[1], MD_GUILD_JINTIE_DAYCOUNT[2], MD_GUILD_JINTIE_DAYCOUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_GUILD_JINTIE_DAYCOUNT[1], MD_GUILD_JINTIE_DAYCOUNT[2], MD_GUILD_JINTIE_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, MD_GUILD_JINTIE_DAYCOUNT[1], MD_GUILD_JINTIE_DAYCOUNT[2], MD_GUILD_JINTIE_DAYCOUNT[3], daycount+1)
	end

	SetQuestData(sceneId, selfId, MD_GUILD_BHZ_DATE[1], MD_GUILD_BHZ_DATE[2], MD_GUILD_BHZ_DATE[3], 0)
	SetQuestData(sceneId, selfId, MD_GUILD_BHZ_WIN_COUNT[1], MD_GUILD_BHZ_WIN_COUNT[2], MD_GUILD_BHZ_WIN_COUNT[3], 0)
	SetQuestData(sceneId, selfId, MD_GUILD_BHZ_LOSE_COUNT[1], MD_GUILD_BHZ_LOSE_COUNT[2], MD_GUILD_BHZ_LOSE_COUNT[3], 0)
	SetQuestData(sceneId, selfId, MD_GUILD_BHZ_PING_COUNT[1], MD_GUILD_BHZ_PING_COUNT[2], MD_GUILD_BHZ_PING_COUNT[3], 0)
	SetQuestData(sceneId, selfId, MD_GUILD_YB_DATE[1], MD_GUILD_YB_DATE[2], MD_GUILD_YB_DATE[3], 0)
	SetQuestData(sceneId, selfId, MD_GUILD_YB_WEEK_COUNT[1], MD_GUILD_YB_WEEK_COUNT[2], MD_GUILD_YB_WEEK_COUNT[3], 0)
end
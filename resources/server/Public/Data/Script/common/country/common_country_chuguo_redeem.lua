x300636_g_ScriptId = 300636
x300636_g_MissionName = "�����ҡ���ȡ��������"
x300636_g_GameId =1009
x300636_g_Level = 60
function x300636_ProcEnumEvent( sceneId, selfId, targetId, index )
	if GetGameOpenById(x300636_g_GameId) > 0 then
		AddQuestNumText(sceneId,x300636_g_ScriptId, x300636_g_MissionName, 3)
	end
	
end

function x300636_ProcEventEntry( sceneId , selfId , targetId , state , index )
	GetCountryQuestData(sceneId,selfId,CD_INDEX_CHUGUO_COUNT, x300636_g_ScriptId,-1,"OnReturn1")
end

--********************
--����������
--**********************************
function x300636_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x300636_Newking(sceneId, selfId,MissionData,MissionId)
	local curDay = GetDayTime()
	if curDay == MissionData then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�ܱ�Ǹ��������̨�Ĺ������Ա��󳼲�����ȡ����");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������̨�Ĺ������Ա��󳼲�����ȡ����",4,2)
		return
	end
	GetCountryQuestData(sceneId,selfId,CD_INDEX_CHUGUO_COUNT, x300636_g_ScriptId,-1,"OnReturn3")
end

function x300636_ProcAccept( sceneId, selfId)
	
	local hour,minute,second = GetHourMinSec()
	if GetWeek() ~= 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����������ȡ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����������ȡ��",8,2)
		return
	end

	--if x300636_GetOfficialMissionId(sceneId, selfId)<=0 then
		if GetExploit(sceneId, selfId) < 38 then
			if x300631_GetOfficialMissionId(sceneId, selfId)==-2 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "�ܱ�Ǹ���������Ա�ſ�����ȡ���˽�����")
				DispatchQuestTips(sceneId, selfId)
				EndQuestEvent(sceneId)
				Msg2Player(sceneId,selfId,"�ܱ�Ǹ���������Ա�ſ�����ȡ���˽�����",8,2)		
				return
			end
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�ܱ�Ǹ�����Ĺ�ѫֵ����38��������ȡ��")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����Ĺ�ѫֵ����38��������ȡ��",8,2)		
			return
		end	
	--end
	if	GetLevel(sceneId, selfId) < x300636_g_Level then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ���ﵽ60���ſ�����ȡ����������")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ���ﵽ60���ſ�����ȡ����������",8,2)
		return
	end
	
	if CountryIsFortuneTime(sceneId, selfId, 1) > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�������ڼ䲻����ȡ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ڼ䲻����ȡ��",8,2)
		return
	end

	local lastDay = GetQuestData(sceneId, selfId, MD_CHUGUO_DATE[1], MD_CHUGUO_DATE[2], MD_CHUGUO_DATE[3])
	local lastFortune = GetFortuneLastTime(sceneId, selfId, 1)

	if lastDay ~= 0 and GetDayOfYear() == lastDay then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ���Ѿ��������������")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ���Ѿ��������������",8,2)
		return
	end
	
	local Shouhu = GetQuestData(sceneId, selfId, MD_SHOUHU_DATE[1], MD_SHOUHU_DATE[2], MD_SHOUHU_DATE[3])
	if GetDayOfYear() ==Shouhu  then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����Ѿ����������������ȸ���ػ�������")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����Ѿ����������������ȸ���ػ�������",8,2)
		return
	end
	if lastFortune > 0 then 
	
		local officalId = x300636_GetOfficialMissionId(sceneId, selfId)
		if officalId == -2 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�ܱ�Ǹ����������ȡ������")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ����������ȡ������",8,2)
			return
		elseif officalId ~= -1 then
			GetCountryQuestData(sceneId,selfId,officalId, x300636_g_ScriptId,-1,"OnReturn2")
			return
		end	
		
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "��δ����������")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"��δ����������",8,2)
		return
	end
	
	GetJoinGuildTime(sceneId,selfId,x300636_g_ScriptId)
end

function x300636_OnMemberJoinTimeReturn( sceneId, selfId, param )

	if param == -1 or GetCurrentTime()-param<24*3600 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��������������ʱ�����24Сʱ��������ȡ������")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������������ʱ�����24Сʱ��������ȡ������",8,2)
		return		
	end
	
	local officalId = x300636_GetOfficialMissionId(sceneId, selfId)
	if officalId == -1 then
		x300636_OnReturn2(sceneId, selfId,-1,MissionId)
		return
	end
	
	GetCountryQuestData(sceneId,selfId,officalId, x300636_g_ScriptId,-1,"OnReturn2")

end

function x300636_GetOfficialMissionId(sceneId, selfId)
	local officalId = -1
	local selfGuildId = GetGuildID(sceneId, selfId)
	local countryGuildId = GetCountryKingGuildId(sceneId, selfId)
	
	if IsKing(sceneId, selfId) > 0 then
		officalId = CD_INDEX_CHUGUO_KING
	elseif IsCountryOffical(sceneId, selfId) > 0 then
		if IsSpecialCountryOffical(sceneId, selfId, 7 ) > 0 then  --����
			officalId = CD_INDEX_CHUGUO_QUEEN
		elseif IsSpecialCountryOffical(sceneId, selfId, 6 ) > 0 then --��
			officalId = CD_INDEX_CHUGUO_GENERAL
		elseif IsSpecialCountryOffical(sceneId, selfId, 5 ) > 0 then -- ����
			officalId = CD_INDEX_CHUGUO_RMINISTER	
		elseif IsSpecialCountryOffical(sceneId, selfId, 4 ) > 0 then --����
			officalId = CD_INDEX_CHUGUO_LMINISTER	
		elseif IsSpecialCountryOffical(sceneId, selfId, 3 ) > 0 then  --�Ҳ�
			officalId = CD_INDEX_CHUGUO_RGUARD	
		elseif IsSpecialCountryOffical(sceneId, selfId, 2 ) > 0 then --��
			officalId = CD_INDEX_CHUGUO_LGUARD
		end
	elseif selfGuildId ~= -1 and countryGuildId == selfGuildId then
		officalId = -1
	else
		officalId = -2
	end
	
	return officalId
end

function x300636_OnReturn1(sceneId, selfId,MissionData,MissionId)
	
	local count = MissionData + 1

	if count < -1 then
		return
	end

	if count == -1 then
		count = 0
	end
				
	if count > 22400 then
		count = 22400
	end
	
	
	local awardRongyu =0;
	local awardExp =0;
	local awardJinKa =0;

	local selfGuildId = GetGuildID(sceneId, selfId)
	local countryGuildId = GetCountryKingGuildId(sceneId, selfId)
	local level = GetLevel(sceneId, selfId)
	
	local toggle = 0

	if IsKing(sceneId, selfId) > 0 then
		awardRongyu =floor(count/10)
		awardExp =floor(level*80*count/10)
		awardJinKa =floor(100*count/10)
	elseif IsCountryOffical(sceneId, selfId) > 0 then
		awardRongyu =floor(count*0.5/10)
		awardExp =floor(level*80*count*0.5/10)
		awardJinKa =floor(100*count*0.5/10)
	elseif selfGuildId ~= -1 and countryGuildId == selfGuildId then
		awardRongyu =floor(count*0.25/10)
		awardExp =floor(level*80*count*0.25/10)
		awardJinKa =floor(100*count*0.25/10)
	else
		toggle =1
	end

	local ding=0
	local liang=0
	local wen=0
	
	BeginQuestEvent(sceneId)
	local nExploit = GetExploit(sceneId,selfId)
	if IsKing(sceneId, selfId) > 0 then
		awardJinKa =floor(100*count/10)
		ding = floor( awardJinKa / (1000*1000) )
		liang = floor( mod(awardJinKa,1000*1000)/ 1000 )
		wen = mod(awardJinKa,1000)
	elseif IsCountryOffical(sceneId, selfId) > 0 then
		awardJinKa =floor(100*count*0.5/10)
		ding = floor( awardJinKa / (1000*1000) )
		liang = floor( mod(awardJinKa,1000*1000)/ 1000 )
		wen = mod(awardJinKa,1000)
	elseif selfGuildId ~= -1 and countryGuildId == selfGuildId then
		awardJinKa =floor(100*count*0.25/10)
		ding = floor( awardJinKa / (1000*1000) )
		liang = floor( mod(awardJinKa,1000*1000)/ 1000 )
		wen = mod(awardJinKa,1000)
	end
	local Readme = "#Y�����ҡ���ȡ��������#r";
	local Readme2 = "#W    ���������Ƕ��ڳ��������������޴��׵�#G���ҹ�Ա#W��#G��������Ա#W׼���Ľ�����#r"
	local Readme3 = "    �ڷ���#G������#Wʱ���ڣ�ÿ�����#G��ɳ�������#W�Ĵ�����ֱ��Ӱ�쵱�������������Ķ��١�#r"
	local Readme4 = "    ÿ��һ�����գ�ÿ��������ڼ��������ĳɹ����������ۼƣ������գ�������ȡһ�ܵĳ����������ڹ�ѫֵ�㹻�Ļ����ϣ�#G����#W��ȡ#G�ı�#W������#G���Ҵ�#W��ȡ#G����#W�Ľ�����#G��������#W��ȡ#Gһ��#W�Ľ�����#r"
	local Readme5 = "    �ﵽ#G60��#W���������ӳ�Աÿ�ܵĹ�ѫֵ����ﵽ#G38#W�����ϲſ�����ȡ������������ѫֵ��ÿ���ڳ������ڼ���ɳ�������ʱ��á�#r\t�������Ƿ�Ҫ��ȡ��"
	local award1 = format("#W�������#R%d#W��������#r", awardRongyu);
	local award2 = format("�������#R%d#W���齱��#r", awardExp);
	local award3 = format("�������#R%d��%d��%d#W�Ľ𿨽���", ding,liang,wen);
	local award = "������ӵ��#G"..nExploit.."��#W��ѫֵ";
	local blank=" #r";
	if toggle == 0 then
		AddQuestText(sceneId,Readme..Readme2..Readme3..Readme4..Readme5..blank..award..blank..award1..award2..award3)
	else
		AddQuestText(sceneId,Readme..Readme2..Readme3..Readme4..Readme5)
	end
	EndQuestEvent(sceneId)	
	DispatchQuestInfo(sceneId,selfId,-1,x300636_g_ScriptId,-1)

	return 	
end

function x300636_OnReturn2(sceneId, selfId,MissionData,MissionId)

	if MissionData>=0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ����ְλ�Ѿ��������������")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ����ְλ�Ѿ��������������",8,2)
		return		
	end
	GetCountryQuestData(sceneId,selfId,CD_INDEX_CREATEKING_DATE, x300636_g_ScriptId,-1,"Newking")
end

function x300636_OnReturn3(sceneId, selfId,MissionData,MissionId)
	
	local selfGuildId = GetGuildID(sceneId, selfId)
	local countryGuildId = GetCountryKingGuildId(sceneId, selfId)
	local officalId = -1
	local country = GetCurCountry(sceneId, selfId)
	local lastFortune = GetFortuneLastTime(sceneId, selfId, 1)
	
	local count = MissionData + 1
	if count < -1 then
		return
	end
	if count == -1 then
		count = 0
	end
	if count > 22400 then
		count = 22400
	end

	
	--������
		if IsKing(sceneId, selfId) > 0 then

			local level = GetLevel(sceneId, selfId)
			
			AddHonor( sceneId, selfId, floor(count/10) )
			local str=format("#o���#R����%d��#o�Ľ���", floor(count/10))
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,str,4,2)

			AddExp( sceneId, selfId, floor(level*80*count/10) )
			str=format("#o���#R����%d��#o�Ľ���", floor(level*80*count/10))
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,str,4,2)

			local awardMoney = 100*count
			AddMoney( sceneId, selfId,3, floor(awardMoney/10) )
			str = format( "���#R��#{_MONEY%d}#o�Ľ���", floor(awardMoney/10))
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId, str,4,2)

			officalId = x300636_GetOfficialMissionId(sceneId, selfId)
			SetQuestData(sceneId, selfId, MD_CHUGUO_DATE[1], MD_CHUGUO_DATE[2], MD_CHUGUO_DATE[3], GetDayOfYear())
			SetCountryQuestData(sceneId, country, officalId, GetDayOfYear() )

			--����淨��־
			GamePlayScriptLog( sceneId, selfId, 981)
			
		elseif IsCountryOffical(sceneId, selfId) > 0 then

			local level = GetLevel(sceneId, selfId)

			AddHonor( sceneId, selfId, floor(count*0.5/10) )
			local str=format("#o���#R����%d��#o�Ľ���", floor(count*0.5/10))
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,str,4,2)

			AddExp( sceneId, selfId, floor(level*40*count/10) )
			str=format("#o���#R����%d��#o�Ľ���", floor(level*40*count/10))
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,str,4,2)

			local awardMoney = 50*count
			AddMoney( sceneId, selfId,3, floor(awardMoney/10) )
			str = format( "���#R��#{_MONEY%d}#o�Ľ���", floor(awardMoney/10) )
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId, str,4,2)
			
			officalId = x300636_GetOfficialMissionId(sceneId, selfId)
			SetQuestData(sceneId, selfId, MD_CHUGUO_DATE[1], MD_CHUGUO_DATE[2], MD_CHUGUO_DATE[3], GetDayOfYear())
			SetCountryQuestData(sceneId, country, officalId, GetDayOfYear() )
		
			--����淨��־
			GamePlayScriptLog( sceneId, selfId, 981)
			
		elseif selfGuildId ~= -1 and countryGuildId == selfGuildId then
		
			local level = GetLevel(sceneId, selfId)

			AddHonor( sceneId, selfId, floor(count*0.25/10) )
			local str=format("#o���#R����%d��#o�Ľ���", floor(count*0.25/10))
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,str,4,2)

			AddExp( sceneId, selfId, floor(level*20*count/10) )
			str=format("#o���#R����%d��#o�Ľ���", floor(level*20*count/10))
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,str,4,2)

			local awardMoney = 25*count
			AddMoney( sceneId, selfId,3, floor(awardMoney/10) )
			str = format( "���#R��#{_MONEY%d}#o�Ľ���", floor(awardMoney/10) )
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId, str,4,2)
			SetQuestData(sceneId, selfId, MD_CHUGUO_DATE[1], MD_CHUGUO_DATE[2], MD_CHUGUO_DATE[3], GetDayOfYear())
			
			--����淨��־
			GamePlayScriptLog( sceneId, selfId, 981)
			
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�ܱ�Ǹ����������ȡ������")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ����������ȡ������",8,2)
		end
end
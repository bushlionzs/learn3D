x300631_g_ScriptId = 300631
x300631_g_MissionName = "�����ҡ���ȡ���˽���"
x300631_g_GameId =1008
x300631_g_Level = 60
function x300631_ProcEnumEvent( sceneId, selfId, targetId, index )
	if GetGameOpenById(x300631_g_GameId) > 0 then
		AddQuestNumText(sceneId,x300631_g_ScriptId, x300631_g_MissionName, 3)
	end
	
end

function x300631_ProcEventEntry( sceneId , selfId , targetId , state , index )
	GetCountryQuestData(sceneId,selfId,CD_INDEX_GUOYUN_COUNT, x300631_g_ScriptId,-1,"OnReturn1")	
end

--********************
--����������
--**********************************
function x300631_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

function x300631_Newking(sceneId, selfId,MissionData,MissionId)
	local curDay = GetDayTime()
	if curDay == MissionData then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�ܱ�Ǹ��������̨�Ĺ������Ա��󳼲�����ȡ����");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������̨�Ĺ������Ա��󳼲�����ȡ����",4,2)
		return
	end
	GetCountryQuestData(sceneId,selfId,CD_INDEX_GUOYUN_COUNT, x300631_g_ScriptId,-1,"OnReturn3")
end

--**********************************
--����
--**********************************
function x300631_ProcAccept( sceneId, selfId )

	local hour,minute,second = GetHourMinSec()
	if GetWeek() ~= 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����������ȡ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����������ȡ��",8,2)
		return
	end
	
	--if x300631_GetOfficialMissionId(sceneId, selfId)<=0 then
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
	if	GetLevel(sceneId, selfId) < x300631_g_Level then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ���ﵽ60���ſ�����ȡ���˽�����")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ���ﵽ60���ſ�����ȡ���˽�����",8,2)
		return
	end
		
	if CountryIsFortuneTime(sceneId, selfId, 0) > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�������ڼ䲻����ȡ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ڼ䲻����ȡ��",8,2)
		return
	end

	local lastDay = GetQuestData(sceneId, selfId, MD_GUOYUN_DATE[1], MD_GUOYUN_DATE[2], MD_GUOYUN_DATE[3])
	local lastFortune = GetFortuneLastTime(sceneId, selfId, 0)

	if lastDay ~= 0 and GetDayOfYear() == lastDay then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ���Ѿ�������˽�����")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ���Ѿ�������˽�����",8,2)
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
	
	if lastFortune > 0 then --���˴���
	
		local officalId = x300631_GetOfficialMissionId(sceneId, selfId)
		
		if officalId == -2 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�ܱ�Ǹ����������ȡ������")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ����������ȡ������",8,2)
			return
		elseif officalId ~= -1 then
			GetCountryQuestData(sceneId,selfId,officalId, x300631_g_ScriptId,-1,"OnReturn2")
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
		
	GetJoinGuildTime(sceneId,selfId,x300631_g_ScriptId)
end

function x300631_OnMemberJoinTimeReturn( sceneId, selfId, param )

	if param == -1 or GetCurrentTime()-param<24*3600 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��������������ʱ�����24Сʱ��������ȡ������")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������������ʱ�����24Сʱ��������ȡ������",8,2)
		return		
	end
	
	local officalId = x300631_GetOfficialMissionId(sceneId, selfId)
	if officalId == -1 then
		x300631_OnReturn2(sceneId, selfId,-1,MissionId)
		return
	end
	
	GetCountryQuestData(sceneId,selfId,officalId, x300631_g_ScriptId,-1,"OnReturn2")
end

function x300631_GetOfficialMissionId(sceneId, selfId)
	local officalId = -1
	local selfGuildId = GetGuildID(sceneId, selfId)
	local countryGuildId = GetCountryKingGuildId(sceneId, selfId)
	
	if IsKing(sceneId, selfId) > 0 then
		officalId = CD_INDEX_GUOYUN_KING
	elseif IsCountryOffical(sceneId, selfId) > 0 then
		if IsSpecialCountryOffical(sceneId, selfId, 7 ) > 0 then  --����
			officalId = CD_INDEX_GUOYUN_QUEEN
		elseif IsSpecialCountryOffical(sceneId, selfId, 6 ) > 0 then --��
			officalId = CD_INDEX_GUOYUN_GENERAL
		elseif IsSpecialCountryOffical(sceneId, selfId, 5 ) > 0 then -- ����
			officalId = CD_INDEX_GUOYUN_RMINISTER	
		elseif IsSpecialCountryOffical(sceneId, selfId, 4 ) > 0 then --����
			officalId = CD_INDEX_GUOYUN_LMINISTER	
		elseif IsSpecialCountryOffical(sceneId, selfId, 3 ) > 0 then  --�Ҳ�
			officalId = CD_INDEX_GUOYUN_RGUARD	
		elseif IsSpecialCountryOffical(sceneId, selfId, 2 ) > 0 then --��
			officalId = CD_INDEX_GUOYUN_LGUARD
		end
	elseif selfGuildId ~= -1 and countryGuildId == selfGuildId then
		officalId = -1
	else
		officalId = -2
	end
	
	return officalId
end

function x300631_OnReturn1(sceneId, selfId,MissionData,MissionId)
	local count = MissionData + 1
	
	if count < -1 then
		return
	end

	if count == -1 then
		count = 0
	end
	
	if count > 21000 then
		count = 21000
	end
	
	local awardExp =0;
	local awardShengWang =0;
	local awardYinKa =0;

	local selfGuildId = GetGuildID(sceneId, selfId)
	local countryGuildId = GetCountryKingGuildId(sceneId, selfId)
	local level = GetLevel(sceneId, selfId)
	
	local toggle = 0
	if IsKing(sceneId, selfId) > 0 then
		awardExp =floor(level*12*count)
		awardShengWang =count
		awardYinKa =level*count
	elseif IsCountryOffical(sceneId, selfId) > 0 then
		awardExp =floor(level*12*count*0.5)
		awardShengWang =floor(count*0.5)
		awardYinKa =floor(level*count*0.5)
	elseif selfGuildId ~= -1 and countryGuildId == selfGuildId then
		awardExp =floor(level*12*count*0.25)
		awardShengWang =floor(count*0.25)
		awardYinKa =floor(level*count*0.25)
	else
		toggle =1
	end

	local ding=0
	local liang=0
	local wen=0
	
	BeginQuestEvent(sceneId)
	local nExploit = GetExploit(sceneId,selfId)
	if IsKing(sceneId, selfId) > 0 then
		awardYinKa =floor(level*count)
		ding = floor( awardYinKa / (1000*1000) )
		liang = floor( mod(awardYinKa,1000*1000)/ 1000 )
		wen = mod(awardYinKa,1000)
	elseif IsCountryOffical(sceneId, selfId) > 0 then
		awardYinKa =floor(level*count*0.5)
		ding = floor( awardYinKa / (1000*1000) )
		liang = floor( mod(awardYinKa,1000*1000)/ 1000 )
		wen = mod(awardYinKa,1000)
	elseif selfGuildId ~= -1 and countryGuildId == selfGuildId then
		awardYinKa =floor(level*count*0.25)
		ding = floor( awardYinKa / (1000*1000) )
		liang = floor( mod(awardYinKa,1000*1000)/ 1000 )
		wen = mod(awardYinKa,1000)
	end
	local Readme = "#Y�����ҡ���ȡ���˽���#r";
	local Readme2 = "#W    ���˽����Ƕ��ڹ����������޴��׵�#G���ҹ�Ա#W��#G��������Ա#W׼���Ľ�����#r"
	local Readme3 = "    �ڷ���#G������#Wʱ���ڣ�#G�ٸ�Ѻ�˵ĳɹ�����#W��ֱ��Ӱ�쵱����˽����Ķ��١�#r"
	local Readme4 = "    ÿ��һ�����գ�ÿ��������ڼ�ٸ�Ѻ�˵ĳɹ����������ۼƣ������գ�������ȡһ�ܵĹ��˽������ڹ�ѫֵ�㹻�Ļ����ϣ�#G����#W��ȡ#G�ı�#W������#G���Ҵ�#W��ȡ#G����#W�Ľ�����#G��������#W��ȡ#Gһ��#W�Ľ�����#r"
	local Readme5 = "    �ﵽ#G60��#W���������ӳ�Աÿ�ܵĹ�ѫֵ����ﵽ#G38#W�����ϲſ�����ȡ���˽�������ѫֵ��ÿ���ڳ������ڼ���ɳ�������ʱ��á�#r\t�������Ƿ�Ҫ��ȡ��"
	local award1 = format("#W�������#R%d#W���齱��#r", awardExp);
	local award2 = format("�������#R%d#W��������#r", awardShengWang);
	local award3 = format("�������#R%d��%d��%d��#W��������", ding,liang,wen);
	local award = "������ӵ��#G"..nExploit.."��#W��ѫֵ"
	local blank=" #r";
	if toggle == 0 then
		AddQuestText(sceneId,Readme..Readme2..Readme3..Readme4..Readme5..blank..award..blank..award1..award2..award3)
	else
		AddQuestText(sceneId,Readme..Readme2..Readme3..Readme4..Readme5)
	end
	EndQuestEvent(sceneId)	
	DispatchQuestInfo(sceneId,selfId,-1,x300631_g_ScriptId,-1)

	return 

end


function x300631_OnReturn2(sceneId, selfId,MissionData,MissionId)
	
	if MissionData>=0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ����ְλ�Ѿ�������˽�����")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ����ְλ�Ѿ�������˽�����",8,2)
		return		
	end
	
	GetCountryQuestData(sceneId,selfId,CD_INDEX_CREATEKING_DATE, x300631_g_ScriptId,-1,"Newking")
	
end


function x300631_OnReturn3(sceneId, selfId,MissionData,MissionId)

	local selfGuildId = GetGuildID(sceneId, selfId)
	local countryGuildId = GetCountryKingGuildId(sceneId, selfId)
	local officalId = -1
	local country = GetCurCountry(sceneId, selfId)
	local lastFortune = GetFortuneLastTime(sceneId, selfId, 0)
	
	local count = MissionData + 1

	if count < -1 then
		return
	end
	if count == -1 then
		count = 0
	end
	if count > 21000 then
		count = 21000
	end
	
	--������
	if IsKing(sceneId, selfId) > 0 then

		local level = GetLevel(sceneId, selfId)
		AddExp( sceneId, selfId, floor(level*12*count) )
		local str=format("#o���#R����%d��#o�Ľ���", floor(level*12*count))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)

		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + count
		SetShengWang( sceneId, selfId, nShengWang )
		str = format("���#R����%d#o�Ľ���", count)
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)
		
		local awardMoney = level*count
		AddMoney( sceneId, selfId,1, awardMoney )
		str = format( "���#R����#{_MONEY%d}#o�Ľ���", awardMoney)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, str,4,2)

		officalId = x300631_GetOfficialMissionId(sceneId, selfId)
		SetQuestData(sceneId, selfId, MD_GUOYUN_DATE[1], MD_GUOYUN_DATE[2], MD_GUOYUN_DATE[3], GetDayOfYear())
		SetCountryQuestData(sceneId, country, officalId, GetDayOfYear() )
		

		--����淨��־
		GamePlayScriptLog( sceneId, selfId, 991)
		
	elseif IsCountryOffical(sceneId, selfId) > 0 then

		local level = GetLevel(sceneId, selfId)
		AddExp( sceneId, selfId, floor(level*12*count*0.5) )
		local str=format("#o���#R����%d��#o�Ľ���", floor(level*12*count*0.5))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)

		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + (count*0.5)
		SetShengWang( sceneId, selfId, floor(nShengWang) )
		str = format("���#R����%d#o�Ľ���", floor(count*0.5))
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)

		local awardMoney = level*count*0.5
		AddMoney( sceneId, selfId,1, floor(awardMoney) )
		str = format( "���#R����#{_MONEY%d}#o�Ľ���", floor(awardMoney))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, str,4,2)
		
		officalId = x300631_GetOfficialMissionId(sceneId, selfId)
		SetQuestData(sceneId, selfId, MD_GUOYUN_DATE[1], MD_GUOYUN_DATE[2], MD_GUOYUN_DATE[3], GetDayOfYear())
		SetCountryQuestData(sceneId, country, officalId, GetDayOfYear() )
		
	
		--����淨��־
		GamePlayScriptLog( sceneId, selfId, 991)
		
	elseif selfGuildId ~= -1 and countryGuildId == selfGuildId then
	
		local level = GetLevel(sceneId, selfId)
		AddExp( sceneId, selfId, floor(level*12*count*0.25) )
		local str=format("#o���#R����%d��#o�Ľ���", floor(level*12*count*0.25))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)

		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + (count*0.25)
		SetShengWang( sceneId, selfId, floor(nShengWang) )
		str = format("���#R����%d#o�Ľ���", floor(count*0.25))
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)

		local awardMoney = level*count*0.25
		AddMoney( sceneId, selfId,1, floor(awardMoney) )
		str = format( "���#R����#{_MONEY%d}#o�Ľ���", floor(awardMoney))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, str,4,2)
		SetQuestData(sceneId, selfId, MD_GUOYUN_DATE[1], MD_GUOYUN_DATE[2], MD_GUOYUN_DATE[3], GetDayOfYear())
	
		--����淨��־
		GamePlayScriptLog( sceneId, selfId, 991)
		
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ����������ȡ������")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ����������ȡ������",8,2)
	end	
	
end
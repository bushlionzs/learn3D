x300658_g_ScriptId = 300658
x300658_g_MissionName = "�����ҡ���ȡ�����ػ�����"
x300658_g_GameId =1037
x300658_g_GongValud = 32

function x300658_ProcEnumEvent( sceneId, selfId, targetId, index )
	if GetGameOpenById(x300658_g_GameId) > 0 then
		-- if IsInCountrySpecialGuild(sceneId, selfId,0) > 0  then
		AddQuestNumText(sceneId,x300658_g_ScriptId, x300658_g_MissionName, 3)
		-- end
	end
	
end

function x300658_ProcEventEntry( sceneId , selfId , targetId , state , index )
	GetCountryQuestData(sceneId,selfId,CD_INDEX_CHUGUO_COUNT, x300658_g_ScriptId,-1,"OnReturn1")
end

function x300658_OnReturn1(sceneId, selfId,MissionData,MissionId)
	local count = MissionData + 1

	if count < -1 then
		return
	end

	if count == -1 then
		count = 0
	end
				
	if count > 10000 then
		count = 10000
	end
	
	local awardExp =0;
	local awardJinKa =0;
	local awardShengWang =0;
	local awardRongyu =0;
	local awardExp1 =0;
	local awardJinKa1 =0;
	local awardShengWang1 =0;
	local awardRongyu1 =0;
	local level = GetLevel(sceneId, selfId)
	local toggle = 0
		if IsQinglongZhuque(sceneId, selfId, 0) > 0 then
			awardRongyu =floor(count*3/10)
			awardExp =floor(level*70*count)
			awardJinKa =floor(100*count*0.5/10)
			awardShengWang =floor(count*3)
		elseif IsInCountrySpecialGuild(sceneId, selfId,0) > 0 then
			awardRongyu1 =floor(count*3/40)
			awardExp1 =floor(level*70/4*count)
			awardShengWang1 =floor(count*3/4)
			awardJinKa1 =floor(100*count*0.5/10/4)
		else 
			toggle = -1
		end
		
		local ding=0
		local liang=0
		local wen=0
		
		local ding1=0
		local liang1=0
		local wen1=0
		
		BeginQuestEvent(sceneId)
		local nExploit = GetExploit(sceneId,selfId)
		if IsQinglongZhuque(sceneId, selfId, 0) > 0 then
			awardJinKa =floor(100*count*0.5/10)
			ding = floor( awardJinKa / (1000*1000) )
			liang = floor( mod(awardJinKa,1000*1000)/ 1000 )
			wen = mod(awardJinKa,1000)
		elseif IsInCountrySpecialGuild(sceneId, selfId,0) > 0 then
			awardJinKa1 =floor(100*count*0.5/10/4)
			ding1 = floor( awardJinKa1 / (1000*1000) )
			liang1 = floor( mod(awardJinKa1,1000*1000)/ 1000 )
			wen1 = mod(awardJinKa1,1000)
		end
		
		local Readme = "#Y�����ҡ���ȡ�����ػ�����#r";
		local Readme2 = "\t#W�����ػ���������ÿһ��Ϊ�ػ������������׵ģ��ﵽ#R60��#W��#G�����ػ�����Ա#W��#G����֮��#W��������ȡ�Ľ�����#r"
		local Readme3 = "\t�ڷ���#G������#Wʱ���ڣ�ÿ��������#G��������Ĵ���#W��ֱ��Ӱ�쵱���ػ������Ķ��١�#r"
		local Readme4 = "\tÿ#G��һ#W��#G����#W��ÿ��������ڼ�#G��������ĳɹ�����#W����#G�ۼ�#W����#G����#W��������ȡһ�ܵ��ػ��������ڹ�ѫֵ�㹻�Ļ����ϣ�#G����#W��ȡ#G����#W������#G����#W��ȡ#G�ı�#W������#r"
		local Readme5 = "\t�ػ�����Աÿ�ܹ�ѫֵ������#G32#W�㣬ÿ#G����#W��������������ȡһ�ܵ��ػ���������ѫֵ��ÿ���ڳ������ڼ���ɳ�������ʱ��á�#r\t�������Ƿ�Ҫ��ȡ��"
		local award1 = format("#W�������#R%d#W��������#r", awardRongyu);
		local award2 = format("�������#R%d#W���齱��#r", awardExp);
		local award3 = format("�������#R%d#W��������#r", awardShengWang);
		local award4 = format("�������#R%d#K��#R%d#K��#R%d#K�Ľ𿨽���", ding,liang,wen);
		local award5 = format("#W�������#R%d#W��������#r", awardRongyu1);
		local award6 = format("�������#R%d#W���齱��#r", awardExp1);
		local award7 = format("�������#R%d#W��������#r", awardShengWang1);
		local award8 = format("�������#R%d#K��#R%d#K��#R%d#K�Ľ𿨽���", ding1,liang1,wen1);
		local award = "������ӵ��#G"..nExploit.."��#W��ѫֵ";
		local blank=" #r";
			AddQuestText(sceneId,Readme..Readme2..Readme3..Readme4..Readme5)
		if toggle == 0 then
			if IsQinglongZhuque(sceneId, selfId, 0) > 0 then
			AddQuestText(sceneId,award..blank..award1..award2..award3..award4)
			elseif IsInCountrySpecialGuild(sceneId, selfId,0) > 0 then
			AddQuestText(sceneId,award..blank..award5..award6..award7..award8)
			end
		end
		EndQuestEvent(sceneId)	
		DispatchQuestInfo(sceneId,selfId,-1,x300658_g_ScriptId,-1)
		return 	
end


function x300658_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

function x300658_ProcAccept( sceneId, selfId)
	local hour,minute,second = GetHourMinSec()
		if GetWeek() ~= 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����������ȡ��")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����������ȡ��",8,2)
			return
		end
		if	GetLevel(sceneId, selfId) < 60 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�ܱ�Ǹ���ﵽ60���ſ�����ȡ�����ػ�������")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ���ﵽ60���ſ�����ȡ�����ػ�������",8,2)
			return
		end
		if IsInCountrySpecialGuild(sceneId, selfId,0)~=1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�ܱ�Ǹ�������ػ�����Ա�ſ�����ȡ�����ػ�������")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ػ�����Ա�ſ�����ȡ�����ػ�������",8,2)		
			return
		end
		
		if GetExploit(sceneId, selfId) < x300658_g_GongValud then
			local msg = format("�ܱ�Ǹ�����Ĺ�ѫֵ����%d�㣬������ȡ��",x300658_g_GongValud)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, msg)
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,msg,8,2)		
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
		
		local lastDay = GetQuestData(sceneId, selfId, MD_SHOUHU_DATE[1], MD_SHOUHU_DATE[2], MD_SHOUHU_DATE[3])
		local lastFortune = GetFortuneLastTime(sceneId, selfId, 1)

		if lastDay ~= 0 and GetDayOfYear() == lastDay then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�ܱ�Ǹ���Ѿ���������ػ�������")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ���Ѿ���������ػ�������",8,2)
			return
		end
		
		local chuguo = GetQuestData(sceneId, selfId, MD_CHUGUO_DATE[1], MD_CHUGUO_DATE[2], MD_CHUGUO_DATE[3]) --��������
		if  GetDayOfYear() == chuguo then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�ܱ�Ǹ�����Ѿ�������ܳ���������")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����Ѿ�������ܳ���������",8,2)
			return
		end
		
		local guoyun = GetQuestData(sceneId, selfId, MD_GUOYUN_DATE[1], MD_GUOYUN_DATE[2], MD_GUOYUN_DATE[3]) --���˽���
		if  GetDayOfYear() == guoyun  then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�ܱ�Ǹ�����Ѿ�������ܹ��˽�����")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����Ѿ�������ܹ��˽�����",8,2)
			return
		end
		
		if lastFortune <= 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "��δ����������")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"��δ����������",8,2)
			return
		end
		
		GetJoinGuildTime(sceneId,selfId,x300658_g_ScriptId)
end

function x300658_OnMemberJoinTimeReturn( sceneId, selfId, param )
	
	if param == -1 or GetCurrentTime()-param<24*3600 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�������������ػ����ʱ�����24Сʱ��������ȡ������")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������������ػ����ʱ�����24Сʱ��������ȡ������",8,2)
		return		
	end
	
	GetCountryQuestData(sceneId,selfId,CD_INDEX_CREATE_QINGLONG_DATE, x300658_g_ScriptId,-1,"Newqinglong")
end

function x300658_Newqinglong(sceneId, selfId,MissionData,MissionId)
	local curDay = GetDayTime()
		if curDay == MissionData then
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "�ܱ�Ǹ��������̨�������ػ���Ա������ȡ����");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������̨�������ػ���Ա������ȡ����",4,2)
			return
		end
	GetCountryQuestData(sceneId,selfId,CD_INDEX_CHUGUO_COUNT, x300658_g_ScriptId,-1,"OnReturn2")
end


function x300658_OnReturn2(sceneId, selfId,MissionData,MissionId)
	local selfGuildId = GetGuildID(sceneId, selfId)
	local country = GetCurCountry(sceneId, selfId)
	local officalId = -1
	local lastFortune = GetFortuneLastTime(sceneId, selfId, 1)
	
	local count = MissionData + 1
	if count < -1 then
		return
	end
	if count == -1 then
		count = 0
	end
	if count > 10000 then
		count = 10000
	end
	--������
	if IsQinglongZhuque(sceneId, selfId, 0) > 0 then
		local level = GetLevel(sceneId, selfId)
		AddHonor( sceneId, selfId, floor(count*3/10) )
		local str=format("#o���#R����%d��#o�Ľ���", floor(count*3/10))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)

		AddExp( sceneId, selfId, floor(level*70*count) )
		str=format("#o���#R����%d��#o�Ľ���", floor(level*70*count))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)

		local awardMoney = floor(100*count*0.5)
		AddMoney( sceneId, selfId,3, floor(awardMoney/10) )
		str = format( "���#R��#{_MONEY%d}#o�Ľ���", floor(awardMoney/10))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, str,4,2)
		
		local nShengWang = GetShengWang( sceneId, selfId )
		local nShengWang1 = floor(3*count)
		nShengWang = nShengWang + nShengWang1
		SetShengWang( sceneId, selfId, nShengWang )
		str=format("#o���#R����%d��#o�Ľ���",nShengWang1)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, str,4,2)
		SetQuestData(sceneId, selfId, MD_SHOUHU_DATE[1], MD_SHOUHU_DATE[2], MD_SHOUHU_DATE[3], GetDayOfYear())
		--����淨��־
			GamePlayScriptLog( sceneId, selfId, 1441)
			
	elseif IsInCountrySpecialGuild(sceneId, selfId,0) > 0 then --����
		local level = GetLevel(sceneId, selfId)
		AddHonor( sceneId, selfId, floor(count*3/10/4) )
		local str=format("#o���#R����%d��#o�Ľ���", floor(count*3/10/4))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)

		AddExp( sceneId, selfId, floor(level*70*count/4) )
		str=format("#o���#R����%d��#o�Ľ���", floor(level*70*count/4))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)

		local nShengWang = GetShengWang( sceneId, selfId )
		local nShengWang1 = floor(count*3/4)
		nShengWang = nShengWang + nShengWang1
		SetShengWang( sceneId, selfId, nShengWang )
		str=format("#o���#R����%d��#o�Ľ���",nShengWang1)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,str,4,2)
		SetQuestData(sceneId, selfId, MD_SHOUHU_DATE[1], MD_SHOUHU_DATE[2], MD_SHOUHU_DATE[3], GetDayOfYear())

		local awardMoney = floor(100*count*0.5/4)
		AddMoney( sceneId, selfId,3, floor(awardMoney/10) )
		str = format( "���#R��#{_MONEY%d}#o�Ľ���", floor(awardMoney/10))
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, str,4,2)
		
		--����淨��־
			GamePlayScriptLog( sceneId, selfId, 1441)
	end
		
end


	
	
	
	
	
	
	
	
	

--�ű���
x310034_g_ScriptId = 310034

--�����ı�����
x310034_g_MissionName="ʥɽ�ع�����1"

x310034_g_MaxHuman = 100
x310034_g_MaxHumanOther = 200

x310034_g_ItemId = 12030027

function x310034_IsOpenedTime()
	local minute = GetMinOfDay();
	if (minute >=2*60 and minute<=2*60+4) or ( minute>=6*60 and minute<=6*60+4 ) or (minute>=10*60 and minute<=10*60+4) or 
		(minute >=14*60 and minute<=14*60+4) or (minute >=18*60 and minute<=18*60+4) or (minute >=22*60 and minute<=22*60+4) then
		return 1
	end

	return -1
end


function x310034_HaveAccepted(sceneId, selfId)
	
	local lastDay = GetQuestData(sceneId, selfId, MD_YAOXIE_DIGONG_DAY[1], MD_YAOXIE_DIGONG_DAY[2], MD_YAOXIE_DIGONG_DAY[3])

	if lastDay == GetDayOfYear() then
		return 1
	end
	return -1
end

function x310034_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if GetLevel(sceneId, selfId) < 60 then
		return
	end
    AddQuestNumText(sceneId,x310034_g_ScriptId,"ʥɽ�ع�(60��)",14,-1)
     
end


function x310034_ProcEventEntry( sceneId, selfId, targetId,idScript,idExt )

	BeginQuestEvent(sceneId)
	  local Readme_1 = "#Y��ʥɽ�ع���#r"
	  local Readme_2 = "#W\tÿ���#G02:00#W��#G06:00#W��#G10:00#W��#G14:00#W��#G18:00#W��#G22:00#W��ʥɽ�ع�����ڻ��#R5����#W�������ӵ��#G����֮��#W����ô��ʥɽ�ع����ŵ�����ʱ���ﶼ���Խ��롣"
	  local Readme_3 = "#W\n\t����ʱ���ҿ��Ը�����#G��ҫ֤֮#W����#G����֮��#W����ʿ�Ǽӳ�#G��ҫ֮��#W���������Ǿ������㹻������������ħ��Ȼ������ҫ֮����һ�ַǳ��Ե�����������ͨ�˵�����#Rһ��#Wֻ�ܼӳ�#Rһ��#W��"
	  local Readme_4 = "#W\n\tͬʱ���ۼ��������ҫ֮�����ܻ���ɲ���Ԥ֪�����⣬���ʥɽ�ع������ֻ����#Rһ����#Wͬʱ����ս�������������ӵ��#G����֮��#W���Ϳ��Դ�������ҫ֮����ɢ��������ʥɽ�ع���������#R������#Wͬʱ����ս����"
	  local Readme = Readme_1..Readme_2..Readme_3..Readme_4
		AddQuestText(sceneId,Readme)
		EndQuestEvent(sceneId)	
	DispatchQuestInfo(sceneId,selfId,targetId,x310034_g_ScriptId,-1)

	return 
end

--********************
--����������
--**********************************
function x310034_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

function x310034_IsGameTime()
	local minute = GetMinOfDay();
	if (minute >=2*60 and minute<=2*60+20) or ( minute>=6*60 and minute<=6*60+20 ) or (minute>=10*60 and minute<=10*60+20) or 
		(minute >=14*60 and minute<=14*60+20) or (minute >=18*60 and minute<=18*60+20) or (minute >=22*60 and minute<=22*60+20) then
		return 1
	end
	return -1
end

--**********************************
--����
--**********************************
function x310034_ProcAccept( sceneId, selfId )
	
	if GetLevel( sceneId, selfId ) < 60 then
	
		Msg2Player(sceneId,selfId,"�ȼ��������޷�����",8,3)		
		Msg2Player(sceneId,selfId,"�ȼ��������޷�����",8,2)
		return
	end

	if x310034_IsGameTime() < 0 then
			Msg2Player(sceneId,selfId,"�����ڻʱ����",8,3)		
			Msg2Player(sceneId,selfId,"�����ڻʱ����",8,2)
			return
	end

	local bHave = 0
	if GetItemCount(sceneId, selfId, 11990100)  > 0 then
		bHave = 1
	end

	if bHave == 0 then
		if x310034_IsOpenedTime() < 0 then
			Msg2Player(sceneId,selfId,"�����ڻʱ���ڣ���ӵ�л���֮�ǣ�Ҳ�ɽ���",8,3)		
			Msg2Player(sceneId,selfId,"�����ڻʱ���ڣ���ӵ�л���֮�ǣ�Ҳ�ɽ���",8,2)
			return
		end
	else
		if x310034_IsGameTime() < 0 then
			Msg2Player(sceneId,selfId,"�����ڻʱ����",8,3)		
			Msg2Player(sceneId,selfId,"�����ڻʱ����",8,2)
			return
		end
	end

	if x310034_HaveAccepted(sceneId, selfId) > 0 then
		
		Msg2Player(sceneId,selfId,"һ��ֻ�ܽ���һ��ʥɽ�ع�",8,3)		
		Msg2Player(sceneId,selfId,"һ��ֻ�ܽ���һ��ʥɽ�ع�",8,2)
		return 
	end

	if bHave == 0 then
		if GetItemCount(sceneId, selfId, x310034_g_ItemId)  == 0 then
			Msg2Player(sceneId,selfId,"��û����ҫ֤֮����ӵ�л���֮�ǣ�Ҳ���Խ���",8,3)		
			Msg2Player(sceneId,selfId,"��û����ҫ֤֮����ӵ�л���֮�ǣ�Ҳ���Խ���",8,2)
			return
		end
	end
	

	if IsBusMember(sceneId, selfId) > 0 then
		Msg2Player(sceneId,selfId,"����״̬���޷�����",8,3)		
		Msg2Player(sceneId,selfId,"����״̬���޷�����",8,2)
		return
	end

	local countryId = GetCurCountry(sceneId, selfId)
	
	local curNum = 0
	if countryId == 0 then
		curNum = YX_LOULAN_HUMAN_NUM2 
	elseif countryId == 1 then
		curNum = YX_LAIYIN_HUMAN_NUM2 
	elseif countryId == 2 then
		curNum = YX_KUNLUN_HUMAN_NUM2 
	elseif countryId == 3 then
		curNum = YX_DUNHUANG_HUMAN_NUM2 
	end
	local sign = 0;

	--if curNum < x310034_g_MaxHuman then
		if x310034_IsOpenedTime() > 0 then
			if GetItemCount(sceneId, selfId, x310034_g_ItemId)  > 0 then
				sign = 1
			else
				if bHave > 0 then
					sign =2;
				end
			end
		else
			if bHave > 0 then
				sign =2;
			end
		end
	--elseif curNum >= x310034_g_MaxHuman and curNum < x310034_g_MaxHumanOther then
		
		--if bHave  > 0 then
		--	sign =2;	
		--else	
		--	Msg2Player(sceneId,selfId,"ʥɽ�ع��ѳ������ˣ��޷�����",8,3)	
		--	Msg2Player(sceneId,selfId,"ʥɽ�ع��ѳ������ˣ��޷�����",8,2)
		--	return
		--end

	 
	--else	
	--	Msg2Player(sceneId,selfId,"ʥɽ�ع��Ѵ�����ˣ��޷�����",8,3)	
	--	Msg2Player(sceneId,selfId,"ʥɽ�ع��Ѵ�����ˣ��޷�����",8,2)
	--	return

	--end

	SetQuestData(sceneId, selfId, MD_YAOXIE_DIGONG_DAY[1], MD_YAOXIE_DIGONG_DAY[2], MD_YAOXIE_DIGONG_DAY[3], GetDayOfYear())
	SetQuestData(sceneId, selfId, MD_YAOXIE_DIGONG_MINUTE[1], MD_YAOXIE_DIGONG_MINUTE[2], MD_YAOXIE_DIGONG_MINUTE[3], GetMinOfDay())
	SetQuestData(sceneId, selfId, MD_YAOXIE_DIGONG_COUNT[1], MD_YAOXIE_DIGONG_COUNT[2], MD_YAOXIE_DIGONG_COUNT[3], 1)


	if sign == 0 then
		return
	elseif sign == 1 then
		DelItem(sceneId, selfId, x310034_g_ItemId, 1)
	elseif sign == 2 then
		DelItem(sceneId, selfId, 11990100, 1)
	end
	

	local NewSceneId;

	if countryId == 0 then
		NewSceneId = YX_LOULAN_SCENE_ID2
		YX_LOULAN_HUMAN_NUM2 = YX_LOULAN_HUMAN_NUM2 + 1
	elseif countryId == 1 then
		NewSceneId = YX_LAIYIN_SCENE_ID2
		YX_LAIYIN_HUMAN_NUM2 = YX_LAIYIN_HUMAN_NUM2 + 1
	elseif countryId == 2 then
		NewSceneId = YX_KUNLUN_SCENE_ID2
		YX_KUNLUN_HUMAN_NUM2 = YX_KUNLUN_HUMAN_NUM2 + 1
	elseif countryId == 3 then
		NewSceneId = YX_DUNHUANG_SCENE_ID2
		YX_DUNHUANG_HUMAN_NUM2 = YX_DUNHUANG_HUMAN_NUM2 + 1
	end
	local PosX = 67
	local PosZ = 63
	
	NewWorld(sceneId, selfId, NewSceneId,PosX ,PosZ, 310034 )

end




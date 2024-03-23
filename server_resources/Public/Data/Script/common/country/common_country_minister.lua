--���Ҵ󳼽ű�
x310101_g_scriptId 				= 310101					--���ű�
x310101_g_minsterGuid			= 129720					--���Ҵ�GUID
x310101_g_Time					= { min = 1930,max = 2259 }	--ʱ������
--x310101_g_guardGuid 			= {129721,129722,129723,129724,129725}
--x310101_g_DieMessage			= "#Yս��֮��#R��Ȼ���£���������ŭ�����񻩱䣬��������������λ��"		--���Ҵ󳼱�ɱ��ʾ
x310101_g_DieLog				= "Minister = 310101, sceneId=%d,Country = %d,kingGUID=%X ,killerGUID=%X"
x310101_g_PreTime				=  0						
x310101_g_AreaTipsInterval		=  2						--�����¼����
x310101_g_AreaTips				= "#R������������������#Yս��֮��#R#aB{goto_%d,%d,%d}(%d,%d)#aE�������ܵй��Ĺ�����������й��ɹ��������ģ��������ᱻ������λ����ȫ��������ǰ����Ԯ��"	--����������ʾ
x310101_g_EnterDay					=	{1,2,3,4,5,6};


----------------------------------------------------------------------------------------------
--��鱾���Ƿ��Ѿ�ɱ����
----------------------------------------------------------------------------------------------
function x310101_CheckWeekValid( nPreTime )

	if nPreTime> 0 then
		local nTime = GetCurrentTime()/86400
		nTime = nTime - nPreTime
		if nTime < 7 then
			return 0
		end
		
		local bFind = -1
		local weekDay = GetWeek()
		
		for i, item in x310101_g_EnterDay do
			if weekDay==item then
				bFind = 1
				break;
			end
		end
		
		
		if bFind == -1 then
			return 0
		end
		
		return 1
	else
		
		local bFind = -1
		local weekDay = GetWeek()
		for i, item in x310101_g_EnterDay do
			if weekDay==item then
				bFind = 1
				break;
			end
		end
		
		
		if bFind == -1 then
			return 0
		end
		
		return 1
	end
	
end


function x310101_GetCountryParam( nSelfCountry )
	
	return CD_INDEX_MINSTER_KILLDATE
end

----------------------------------------------------------------------------------------------
--�ű�Ĭ���¼�
----------------------------------------------------------------------------------------------
function x310101_ProcEventEntry( sceneId ,selfId, npcId )
end


function x310101_ProcTiming( sceneId,now)
end

function x310101_OnDie( sceneId,selfId,killerId )

	--�淨û�п���
	if GetGameOpenById(1026) <= 0 then
		return
	end

	--�������
	local ObjType = GetObjType(sceneId, killerId)	
	if ObjType == 3 then
		ObjType = 1
		killerId = GetOwnerID(sceneId, killerId)
	end
	
	--���Killer����Ч��
	if IsPlayerStateNormal(sceneId,killerId)~=1 then
		return
	end
	


	--���ʱ��
--	local hour,minute,sec =GetHourMinSec();
--	local now = hour *100 + minute
--	if now < x310101_g_Time.min or now > x310101_g_Time.max then
--		return
--	end

	--ȡ�ù�����Ϣ	
	local nCountry = -1
	if sceneId == 50 then
		nCountry = 0
	elseif sceneId == 150 then
		nCountry = 1
	elseif sceneId == 250 then
		nCountry = 2
	elseif sceneId == 350 then
		nCountry = 3
	else
		return
	end
	

	--����Ƿ��й���
	local nKingGUID = CountryGetKingGUID(nCountry)
	if nKingGUID == -1 then
		local kingCountryName = GetCountryName(nCountry)
		local name = GetName(sceneId,killerId)
		local msg = "���ź���Ŀǰ"..kingCountryName.."û�й���"
		LuaScenceM2Player(sceneId,killerId,msg,name,2,1)
		LuaScenceM2Player(sceneId,killerId,msg,name,3,1)
		return
	end

	--�����ͬ��,�˳�
	if nCountry == GetCurCountry(sceneId,killerId) then
		return
	end	
	
	--����Ƿ����⼸��NPC����
	-- local bAllDie = 0
	-- local npcGUID = GetMonsterGUID(sceneId,selfId)
	-- for i,item in x310101_g_guardGuid do
		-- local objId = FindMonsterByGUID(sceneId,item)
		-- if IsObjValid(sceneId,objId ) ~= 1 or GetHp(sceneId,objId) <= 0 then
			-- bAllDie = bAllDie + 1
		-- end
	-- end
	
	-- if bAllDie < getn(x310101_g_guardGuid) then
		
		-- local name = GetName(sceneId,killerId)
		-- local msg = "���ź��������뽫���ֻ����ʿȫ��ɱ���󣬻�ɱ���ֻ�Ż�߸��ù�������ͳ�Ρ�"
		-- local msg6="#Rδ���ȫ��������"
		-- LuaScenceM2Player(sceneId,killerId,msg,name,2,1)
		-- LuaScenceM2Player(sceneId,killerId,msg6,name,3,1)
		
		-- return
	-- end

	--��ѯ������û��ɱ��
	local playerGUID = GetPlayerGUID(sceneId,killerId)
	if playerGUID == nil then
		playerGUID = -1
	end
	
	local playerCP = x310101_GetCountryParam(nCountry)
	GetCountryQuestDataNM(sceneId,playerGUID,nCountry, playerCP, x310101_g_scriptId,-1,"OnReturn",1)
end

function x310101_OnReturn( sceneId, selfId,MissionData,MissionId )

	--�淨û�п���
	if GetGameOpenById(1026) <= 0 then
		return
	end
	
	--���Killer����Ч��
	if IsPlayerStateNormal(sceneId,selfId)~=1 then
		return
	end
	
	--������
	local nCountry = -1
	if sceneId == 50 then
		nCountry = 0
	elseif sceneId == 150 then
		nCountry = 1
	elseif sceneId == 250 then
		nCountry = 2
	elseif sceneId == 350 then
		nCountry = 3
	else
		return
	end
	if x310101_CheckWeekValid(MissionData) ~= 1 then
		local kingCountryName = GetCountryName(nCountry)
		local name = GetName(sceneId,selfId)
		local msg = "#Rһ��֮�ڴݻ�#Yս��֮��#Rֻ�ܵ���"..kingCountryName.."������̨һ�Σ�����#G����#R��ɱ��Ч��"
		local msg5="#R��ɱ��Ч��"
		LuaScenceM2Player(sceneId,selfId,msg,name,2,1)
		LuaScenceM2Player(sceneId,selfId,msg5,name,3,1)
		return
	end
	
	

	--���ʱ��
	local hour,minute,sec =GetHourMinSec();
	local now = hour *100 + minute
	if now < x310101_g_Time.min or now > x310101_g_Time.max then
		local kingCountryName = GetCountryName(nCountry)
		local name = GetName(sceneId,selfId)
		local msg = "#R��19��30-23��00�ڼ�ݻ�#Yս��֮��#R���ܰ���"..kingCountryName.."��������λ��"
		local msg4= "#Rʱ�����"
		LuaScenceM2Player(sceneId,selfId,msg,name,2,1)
		LuaScenceM2Player(sceneId,selfId,msg4,name,3,1)
		return
	end
	
	
	
	--ȡ�ù�����Ϣ	
	local nCountry = -1
	if sceneId == 50 then
		nCountry = 0
	elseif sceneId == 150 then
		nCountry = 1
	elseif sceneId == 250 then
		nCountry = 2
	elseif sceneId == 350 then
		nCountry = 3
	else
		return
	end
	
	--����Ƿ��й���
	local nKingGUID = CountryGetKingGUID(nCountry)
	if nKingGUID == -1 then
		return
	end
	
	--�����ͬ��,�˳�
	if nCountry == GetCurCountry(sceneId,selfId) then
		return
	end
	
	--���minster�Ƿ����
	local misterId = FindMonsterByGUID(sceneId,x310101_g_minsterGuid)
	if IsObjValid(sceneId,misterId ) ~= 1 or GetHp(sceneId,misterId) <= 0 then
	
		local nTime = GetCurrentTime()/86400 	--���������������Ѿ�����ʱ��,��ʱ���ж�������Ϊ׼
	
		--�����Ѿ����
		local playerCP = x310101_GetCountryParam(nCountry)
		SetCountryQuestData(sceneId,nCountry,playerCP,nTime,0)
		SetGuildQuestData(sceneId,GetCountryKingGuildIdNM(nCountry),GD_GUILD_INDEX_MINISTER_GUILD_DATE,nTime,0)
		
		--ȡ������
		CancelKing(sceneId,selfId,nKingGUID,nCountry)
		
		--����־
		local msg = format(x310101_g_DieLog,sceneId,nCountry,nKingGUID,GetPlayerGUID(sceneId,selfId) )
		WriteLog(1,msg);
	
		--��ʾ
		local kingCountryName = GetCountryName(nCountry)
		local killerCountryName = GetCountryName(GetCurCountry( sceneId, selfId))
		local killerName = GetName( sceneId, selfId)
		local msg1 = format("#R%s��ս��֮���ѱ�%s#R��%s�ݻ٣���������������λ��",kingCountryName,killerCountryName,killerName)
		local msg2 ="#Rս��֮�챻�ݻ٣���������������λ��"
		LuaAllScenceM2Country( sceneId,x310101_g_DieMessage,nCountry, 2,1)
		LuaAllScenceM2Country( sceneId,msg2,nCountry, 2,1)
		LuaAllScenceM2Wrold(sceneId, msg1, 5, 1)
		
		--��¼�淨��־
		GamePlayScriptLog(sceneId,selfId,1312)

	end
	
end

---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x310101_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	

	--�淨û�п���
	if GetGameOpenById(1026) <= 0 then
		return
	end
	
	
	--���Killer����Ч��
	if IsPlayerStateNormal(sceneId,selfId)~=1 then
		return
	end
	
	
	--���ʱ��
	local hour,minute,sec =GetHourMinSec();
	local now = hour *100 + minute
	if now < x310101_g_Time.min or now > x310101_g_Time.max then
		return
	end

	
	--ȡ�ù�����Ϣ	
	local nCountry = -1
	if sceneId == 50 then
		nCountry = 0
	elseif sceneId == 150 then
		nCountry = 1
	elseif sceneId == 250 then
		nCountry = 2
	elseif sceneId == 350 then
		nCountry = 3
	else
		return
	end
	
	
	--����Ƿ��й���
	local nKingGUID = CountryGetKingGUID(nCountry)
	if nKingGUID == -1 then
		return
	end
	
	
	
	
	--�����ͬ����������,�˳�
	if nCountry == GetCurCountry(sceneId,selfId) then
		return
	end
	
	

	
	--�����һ������ʱ��
	local nCurMin = GetMinOfYear()
	local nInterval = nCurMin - x310101_g_PreTime
	if nInterval < x310101_g_AreaTipsInterval then
		return	
	end
	
	

	
	--��ѯ������û��ɱ��
	local playerGUID = GetPlayerGUID(sceneId,selfId)
	if playerGUID == nil then
		playerGUID = -1
	end
	local playerCP = x310101_GetCountryParam(nCountry)
	GetCountryQuestDataNM(sceneId,playerGUID,nCountry, playerCP, x310101_g_scriptId,-1,"OnReturn2",1)
	
	
	--GetCountryQuestData(sceneId,selfId,playerCP, x310101_g_scriptId,-1,"OnReturn2",1)
end


function x310101_OnReturn2( sceneId, selfId,MissionData,MissionId )

	
	--�淨û�п���
	if GetGameOpenById(1026) <= 0 then
		return
	end
	
	
	--���Killer����Ч��
	if IsPlayerStateNormal(sceneId,selfId)~=1 then
		return
	end

	
	--���ʱ��
	local hour,minute,sec =GetHourMinSec();
	local now = hour *100 + minute
	if now < x310101_g_Time.min or now > x310101_g_Time.max then
		return
	end
	

	--��鱾���Ƿ��Ѿ�ɱ����
	if x310101_CheckWeekValid(MissionData) ~= 1 then
		return
	end
	
	
	
	--ȡ�ù�����Ϣ	
	local nCountry = -1
	if sceneId == 50 then
		nCountry = 0
	elseif sceneId == 150 then
		nCountry = 1
	elseif sceneId == 250 then
		nCountry = 2
	elseif sceneId == 350 then
		nCountry = 3
	else
		return
	end
	
	
	
	--����Ƿ��й���
	local nKingGUID = CountryGetKingGUID(nCountry)
	if nKingGUID == -1 then
		return
	end
	
	
	
	--�����ͬ����������,�˳�
	if nCountry == GetCurCountry(sceneId,selfId) then
		return
	end	
	
	
	
	--�����һ������ʱ��
	local nCurMin = GetMinOfYear()
	local nInterval = nCurMin - x310101_g_PreTime
	if nInterval < x310101_g_AreaTipsInterval then
		return	
	end
	

	
	--����ʱ��
	x310101_g_PreTime = nCurMin
	
	--���minster�Ƿ����
	local misterId = FindMonsterByGUID(sceneId,x310101_g_minsterGuid)
	if IsObjValid(sceneId,misterId ) == 1 and GetHp(sceneId,misterId) > 0 then
	
		local msg = format( x310101_g_AreaTips,sceneId,284,189,284,189)
		local msg3 ="#Rս��֮���ܵ��й�Ϯ����"
		
		LuaAllScenceM2Country( sceneId,msg,nCountry, 2,1)
		LuaAllScenceM2Country( sceneId,msg3,nCountry, 5,1)
	end
	
end

---------------------------------------------------------------------------------------------------
--�뿪����
---------------------------------------------------------------------------------------------------
function x310101_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end
--���Ҵ󳼾����ű�
x310102_g_scriptId 		= 310102
x310102_g_guardGuid 	= {129721,129722,129723,129724,129725}
x310102_g_minsterGuid	= 129720
x310102_g_Time			= { min = 1200,max = 2359 }
x310102_g_DieMessage	= "#R�з��˶����ڣ���ǰ�����Ѿ�ս����#Y���ֻ����#R#aB{goto_%d,%d,%d}(%d,%d)#aEΣ�ڵ�Ϧ�����������������ᱻ���ְ����ȫ��������ǰ����Ԯ��"
--x310102_g_AllDieMessage	= "���о�������"



----------------------------------------------------------------------------------------------
--��鱾���Ƿ��Ѿ�ɱ����
----------------------------------------------------------------------------------------------
function x310102_CheckWeekValid( nPreTime )
	
	if nPreTime < 0 then
		return 1
	end
	
	local nTime = GetCurrentTime()
	local nTime = nTime - nPreTime
	if nTime >= 7*24*3600 then
		return 1
	end
	
	return 0
end

function x310102_GetCountryParam( nSelfCountry )
	
	return CD_INDEX_MINSTER_KILLDATE
end

----------------------------------------------------------------------------------------------
--�ű�Ĭ���¼�
----------------------------------------------------------------------------------------------
function x310102_ProcEventEntry( sceneId ,selfId, npcId )
end


function x310102_OnDie( sceneId,selfId,killerId )

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
--	if now < x310102_g_Time.min or now > x310102_g_Time.max then
		
--		return
--	end
	
	--ȡ�ù�����Ϣ	
	local nCountry = -1
	if sceneId == 51 then
		nCountry = 0
	elseif sceneId == 151 then
		nCountry = 1
	elseif sceneId == 251 then
		nCountry = 2
	elseif sceneId == 351 then
		nCountry = 3
	else
		return
	end
	
	
	--����Ƿ��й���
	local nKingGUID = CountryGetKingGUID(nCountry)
	if nKingGUID == -1 then
		local name = GetName(sceneId,killerId)
		local msg = "���ź���Ŀǰ�ù�û�й�����"
		LuaScenceM2Player(sceneId,killerId,msg,name,2,1)
		LuaScenceM2Player(sceneId,killerId,msg,name,3,1)
		return
	end
	

	--��ѯ������û��ɱ��
	local playerGUID = GetPlayerGUID(sceneId,killerId)
	if playerGUID == nil then
		playerGUID = -1
	end
	local playerCountry = GetCurCountry(sceneId,killerId)
	local playerCP = x310102_GetCountryParam(nCountry)
	GetCountryQuestDataNM(sceneId,playerGUID,nCountry, playerCP, x310102_g_scriptId,-1,"OnReturn",1)
	
end

function x310102_OnReturn( sceneId, selfId,MissionData,MissionId )

	--�淨û�п���
	if GetGameOpenById(1026) <= 0 then
		return
	end
	
	--������
	if x310102_CheckWeekValid(MissionData ) ~= 1 then
		
		local name = GetName(sceneId,selfId)
		local msg = "#Rһ��֮�ڻ�ɱ#Y���ֻ#Rֻ�ܵ��¸ù�������̨һ�Ρ�"
		local msg3 ="#R��ɱ��Ч��"
		LuaScenceM2Player(sceneId,selfId,msg,name,2,1)
		LuaScenceM2Player(sceneId,selfId,msg3,name,3,1)
		
		return
	end
	
	--���ʱ��
	local hour,minute,sec =GetHourMinSec();
	local now = hour *100 + minute
	if now < x310102_g_Time.min or now > x310102_g_Time.max then
		
		local name = GetName(sceneId,selfId)
		local msg = "#R��12��00-0��00�ڼ��ɱ#Y���ֻ#R�Żᵼ�¸ù�������̨��"
		local msg2 ="#Rʱ�����"
		LuaScenceM2Player(sceneId,selfId,msg,name,2,1)
		LuaScenceM2Player(sceneId,selfId,msg2,name,3,1)
		
		return
	end
	

	--ȡ�ù�����Ϣ	
	local nCountry = -1
	if sceneId == 51 then
		nCountry = 0
	elseif sceneId == 151 then
		nCountry = 1
	elseif sceneId == 251 then
		nCountry = 2
	elseif sceneId == 351 then
		nCountry = 3
	else
		return
	end
	
	
	--����Ƿ��й���
	local nKingGUID = CountryGetKingGUID(nCountry)
	if nKingGUID == -1 then
		local name = GetName(sceneId,selfId)
		local msg = "���ź���Ŀǰ�ù�û�й�����"
		LuaScenceM2Player(sceneId,selfId,msg,name,2,1)
		LuaScenceM2Player(sceneId,selfId,msg,name,3,1)
		return
	end
	
	
	--���minster�Ƿ����
--	local misterId = FindMonsterByGUID(sceneId,x310102_g_minsterGuid)
--	if IsObjValid(sceneId,misterId) ~= 1 or GetHp(sceneId,misterId) <= 0 then
--		return
--	end
	
	
	
	--����Ƿ����⼸��NPC����
--	local bAllDie = 0
--	local npcGUID = GetMonsterGUID(sceneId,selfId)
--	for i,item in x310102_g_guardGuid do
--		local objId = FindMonsterByGUID(sceneId,item)
--		if IsObjValid(sceneId,objId ) ~= 1 or GetHp(sceneId,objId) <= 0 then
--			bAllDie = bAllDie + 1
--		end
--	end
	
	
	--������⼸��NPC����,�������NPC�Ƿ�����,����������
	local msg = format(x310102_g_DieMessage,sceneId,96,100,96,100)
	local msg1 ="#R��ǰ����ս����"
	
	LuaAllScenceM2Country( sceneId,msg,nCountry, 2,1)
	LuaAllScenceM2Country( sceneId,msg1,nCountry, 3,1)
	
	--��¼�淨��־
	GamePlayScriptLog(sceneId,selfId,1311)
						
	
end

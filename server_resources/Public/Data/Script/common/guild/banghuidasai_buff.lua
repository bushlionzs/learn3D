
--��սBUFF

--MisDescBegin
x300681_g_ScriptId         		= 300681
x300681_g_MissionName          	= "����᡿ս��֮��"
x300681_g_BuffCriName          	= "����᡿����ս��֮ŭ"
x300681_g_BuffTenName          	= "����᡿����ս��֮��"
x300681_g_Leader_Index      	= 5

--���ս��˫����Ӫ
x300681_g_Guild_Camp_A          = 5
x300681_g_Guild_Camp_B          = 6


x300681_g_NpcIDA      			= 150015
x300681_g_NpcIDB     			= 150014
x300681_g_BuffCriImpactID     	= 8862
x300681_g_BuffTenImpactID     	= 8861

x300681_g_GuildNotify    		= "�������ս��֮��"
--x300681_g_MapNotify    			= "�����ս��֮��"
x300681_g_PointNotEnough    	= "ս����Դ����"

--ÿ�μ�BUFF�����ĵ���Դ����
x300681_g_Guild_BufResPoint     = 60  

function x300681_GetNPCCamp(sceneId, selfId, NPCId)
	if NPCId == x300681_g_NpcIDA then
		return x300681_g_Guild_Camp_A
	elseif NPCId == x300681_g_NpcIDB then
		return x300681_g_Guild_Camp_B
	end 
	return -1
end

function x300681_ProcEnumEvent(sceneId, selfId, NPCId)

	local nCampID = GetCurCamp(sceneId,selfId)
	local npcGuid = GetMonsterGUID(sceneId, NPCId)
	local NPCcamp = x300681_GetNPCCamp(sceneId, selfId, npcGuid)
	if nCampID ~= NPCcamp then
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId, "����ͬһ��Ӫ��");
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,NPCId)
		return
	end
	
	
        
	AddQuestNumText(sceneId,x300681_g_ScriptId,x300681_g_MissionName,3,1)
end



function x300681_ProcEventEntry(sceneId, selfId, NPCId, scriptid, index)	--����������ִ�д˽ű�
	
	if index < 100 then
		
		BeginQuestEvent(sceneId)
		
			local Readme_1 = "#Y����᡿ս��֮��#r#W"
			local Readme_2 = "\tÿλ����������ͨ������60�����ս����Դ�������еİ���Ա����ս��֮�����������а���Ա��ս������#r"
			local Readme_3 = "\t����ս����Դ��Ҫ��Դ�ڶ԰��ս���ڵ������Ŀ��ƣ��ɹ�ռ��һ�������󣬻�ÿ10������1�㱾����ս����Դ�����ͬʱռ���˱���������������з���������������ÿ10������4��ս����Դ��#r"
			local Readme_4 = "\tս������ʱ���������ս���䣬ÿ�ɹ�����һ�����䣬������������10��ս����Դ��"
			local Readme_5 = "ע�⣺ս����Դֻ���ڰ��ս���в����ɰ���ʹ�ã������ڰ��ս�����������ա�"
			local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
			
			AddQuestText(sceneId, Readme);
			AddQuestNumText(sceneId,x300681_g_ScriptId,x300681_g_BuffCriName,3,1+100)
			AddQuestNumText(sceneId,x300681_g_ScriptId,x300681_g_BuffTenName,3,2+100)
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,NPCId)
		
	else
	
		index = index - 100
		x300681_ClickBuffMenu(sceneId, selfId, NPCId, index)
		
	end
	
end

function x300681_ProcAccept( sceneId, selfId, NPCId, MissionId, index )
   local pos = GetGuildOfficial(sceneId, selfId)
    if pos ~= x300681_g_Leader_Index then
       BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ�а�������Ȩ��ȡս��ף����");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
	   Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ�а�������Ȩ��ȡս��ף����",8,2)
        return
    end

end

function x300681_ClickBuffMenu(sceneId, selfId, NPCId, index)

	local pos = GetGuildOfficial(sceneId, selfId)
    if pos ~= x300681_g_Leader_Index then
       BeginQuestEvent(sceneId)
        AddQuestText(sceneId, "���ź��������ǰ�����û��Ȩ����ȡս��ף����");
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,NPCId)
		return
    end
    
	local nCampID = GetCurCamp(sceneId,selfId)
	local resPoint = CallScriptFunction(300643,"GetScoreInterval",sceneId,nCampID)
	if resPoint < x300681_g_Guild_BufResPoint then
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId, x300681_g_PointNotEnough);
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,NPCId)
		return 
	end
	
	if nCampID == x300681_g_Guild_Camp_A then
		if index == 1 then
			x300681_AddImpactToAllUser(sceneId, selfId, NPCId, x300681_g_BuffCriImpactID)  --����
		elseif index == 2 then
			x300681_AddImpactToAllUser(sceneId, selfId, NPCId, x300681_g_BuffTenImpactID)  --����
		end

		local GuildIdA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_GUILD)
		local GuildTitle = GetGuildTitle(sceneId,selfId)
		local msg = "���������ս��֮��"
		LuaThisScenceM2Wrold(sceneId,msg,2,1)
        LuaThisScenceM2Wrold(sceneId,msg,3,1)	

	elseif nCampID == x300681_g_Guild_Camp_B then
		if index == 1 then
			x300681_AddImpactToAllUser(sceneId, selfId, NPCId, x300681_g_BuffCriImpactID)  --����
		elseif index == 2 then
			x300681_AddImpactToAllUser(sceneId, selfId, NPCId, x300681_g_BuffTenImpactID)  --����
		end
	
		
		local GuildIdB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_GUILD)
		local GuildTitle = GetGuildTitle(sceneId,selfId)
		local msg = "�췽�����ս��֮��"
		LuaThisScenceM2Wrold(sceneId,msg,2,1)
        LuaThisScenceM2Wrold(sceneId,msg,3,1)	
	end
	
	CallScriptFunction(300643,"SetScoreIntervalInc",sceneId,nCampID,-x300681_g_Guild_BufResPoint)  --������Դ��
	
	--LuaThisScenceM2Wrold(sceneId,x300681_g_MapNotify,2,1)
	
end

function x300681_AddImpactToAllUser( sceneId, selfId, targetId, impactId )
	
	local nCampID = GetCurCamp(sceneId,selfId)
	local nHumanCount = GetScenePlayerCount( sceneId )
	for i = 0,nHumanCount-1 do
	    local objId = GetScenePlayerObjId( sceneId,i)
	    if objId >= 0 then
	        local nCampIDOther = GetCurCamp(sceneId,objId)
	        if nCampID == nCampIDOther then
	        	SendSpecificImpactToUnit(sceneId, selfId,objId,objId,impactId,0)
	        end
	    end
	end
end

function x300681_ProcAccept( sceneId, selfId, targetId, MissionId, index )
	local nCampID = GetCurCamp(sceneId,selfId)
	
	local resPoint = CallScriptFunction(300643,"GetScoreInterval",sceneId,nCampID)
	if resPoint < x300681_g_Guild_BufResPoint then
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId, x300681_g_PointNotEnough);
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,NPCId)
		return 
	end
	
	
	if nCampID == x300681_g_Guild_Camp_A then
		if index == 1 then
			x300681_AddImpactToAllUser(sceneId, selfId, targetId, x300681_g_BuffCriImpactID)  --����
		elseif index == 2 then
			x300681_AddImpactToAllUser(sceneId, selfId, targetId, x300681_g_BuffTenImpactID)  --����
		end
	
		
		local GuildIdA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_GUILD)
		LuaThisScenceM2Guild(sceneId,x300681_g_GuildNotify,GuildIdA,2,1)

	elseif nCampID == x300681_g_Guild_Camp_B then
		if index == 1 then
			x300681_AddImpactToAllUser(sceneId, selfId, targetId, x300681_g_BuffCriImpactID)  --����
		elseif index == 2 then
			x300681_AddImpactToAllUser(sceneId, selfId, targetId, x300681_g_BuffTenImpactID)  --����
		end
	
		
		local GuildIdB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_GUILD)
		LuaThisScenceM2Guild(sceneId,x300681_g_GuildNotify,GuildIdB,2,1)	
	end
	
	CallScriptFunction(300643,"SetScoreIntervalInc",sceneId,nCampID,-x300681_g_Guild_BufResPoint)  --������Դ��
	--LuaThisScenceM2Wrold(sceneId,x300681_g_MapNotify,2,1)
end

function x300681_ProcAcceptCheck( sceneId, selfId, targetId, MissionId, index )
    return 1
end

function x300681_ProcQuestAccept( sceneId, selfId, targetId, MissionId, index )
    
end

	
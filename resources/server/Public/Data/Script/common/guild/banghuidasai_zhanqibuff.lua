
--��սս��BUFF

--MisDescBegin
x300682_g_ScriptId          	= 300682
x300682_g_MissionName          	= "����᡿ս��ף��"
x300682_g_Leader_Index      	= 5
x300682_g_NpcIDA      			= 150015
x300682_g_NpcIDB     			= 150014

x300682_g_FlagImpactID    		= 8860   --ս��BUFF

--���ս��˫����Ӫ
x300682_g_Guild_Camp_A          = 5
x300682_g_Guild_Camp_B          = 6

--ÿ�μ�BUFF�����ĵ���Դ����
x300682_g_Guild_BufResPoint     = 20  



--С��ID    x����        y����
--150014    22.77097     121.0536
--150015    233.1756     127.5841



--���ս��˫����Ӫ
x300682_g_Guild_Camp_A          = 5
x300682_g_Guild_Camp_B          = 6

x300682_g_SubMenuDesc     		= "#Y����᡿ս��ף��#r#W\tÿλ����������ͨ������20�����ս����Դ��ʹ��ս��ף��������ս��ָ�10%��������#r \t����ս����Դ��Ҫ��Դ�ڶ԰��ս���ڵ������Ŀ��ƣ��ɹ�ռ��һ�������󣬻�ÿ10������1�㱾����ս����Դ�����ͬʱռ���˱���������������з���������������ÿ10������4��ս����Դ��#r \tս������ʱ���������ս���䣬ÿ�ɹ�����һ�����䣬������������10��ս����Դ����ȷ��Ҫʹ��ս��ף����"

x300682_g_PointNotEnough    	= "ս����Դ����"
x300682_g_GuildNotify    		= "����ս������ս��ף����Ѫ���ָ�10%"
x300682_g_MapNotify    			= "�����ս��ף��"

function x300682_GetNPCCamp(sceneId, selfId, NPCId)
	if NPCId == x300682_g_NpcIDA then
		return x300682_g_Guild_Camp_A
	elseif NPCId == x300682_g_NpcIDB then
		return x300682_g_Guild_Camp_B
	end 
	return -1
end

function x300682_ProcEnumEvent(sceneId, selfId, NPCId)
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
	
	
	-- local pos = GetGuildOfficial(sceneId, selfId)
    -- if pos ~= x300682_g_Leader_Index then
        -- BeginQuestEvent(sceneId)
        -- AddQuestText(sceneId, "�����ǰ�����");
        -- EndQuestEvent(sceneId)
        -- DispatchQuestEventList(sceneId,selfId,NPCId)
        -- return
    -- end
        
	AddQuestNumText(sceneId,x300682_g_ScriptId,x300682_g_MissionName,3,100)
end


function x300682_ProcEventEntry(sceneId, selfId, NPCId, scriptid, index)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,x300682_g_SubMenuDesc)
   	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x300682_g_ScriptId, -1)
	--DispatchQuestEventList(sceneId,selfId,NPCId)
end

function x300682_ProcAccept( sceneId, selfId, NPCId, MissionId, index )
	local pos = GetGuildOfficial(sceneId, selfId)
    if pos ~= x300682_g_Leader_Index then
       Msg2Player( sceneId, selfId, "�����ǰ���", 8, 3)
	   Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ�а�������Ȩ��ȡս��ף����",8,2)
        return
    end
	local nCampID = GetCurCamp(sceneId,selfId)
	
	local resPoint = CallScriptFunction(300643,"GetScoreInterval",sceneId,nCampID)
	if resPoint < x300682_g_Guild_BufResPoint then
	
		Msg2Player( sceneId, selfId, x300682_g_PointNotEnough, 8, 3)
--		BeginQuestEvent(sceneId)
--        AddQuestText(sceneId, x300682_g_PointNotEnough);
--        EndQuestEvent(sceneId)
--        DispatchQuestEventList(sceneId,selfId,NPCId)
		return 
	end
	
	local battleFlagAID =  GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_A_ID)
	local battleFlagBID =  GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_B_ID)

	if nCampID == x300682_g_Guild_Camp_A then
	
		if IsObjValid(sceneId,battleFlagAID) == 1 and GetHp(sceneId,battleFlagAID) > 0 then
			
			local nAdd = floor(GetMaxHp(sceneId,battleFlagAID)* 0.1)
			if nAdd > 0 then
				SetHp(sceneId,battleFlagAID,nAdd)
			end
			
			--SendSpecificImpactToUnit(sceneId, selfId,selfId,battleFlagAID,x300682_g_FlagImpactID,0)
		end
		
		local GuildIdA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_GUILD)
		LuaThisScenceM2Guild(sceneId,x300682_g_GuildNotify,GuildIdA,2,1)
		local msg = "����ս������ս��ף��"
		LuaThisScenceM2Wrold(sceneId,msg,2,1)
        LuaThisScenceM2Wrold(sceneId,msg,3,1)	
		
		

	elseif nCampID == x300682_g_Guild_Camp_B then
		
		if IsObjValid(sceneId,battleFlagBID) == 1 and GetHp(sceneId,battleFlagBID) > 0 then
			local nAdd = floor(GetMaxHp(sceneId,battleFlagBID)* 0.1)
			if nAdd > 0 then
				SetHp(sceneId,battleFlagBID,nAdd)
			end
			--SendSpecificImpactToUnit(sceneId, selfId,selfId,battleFlagBID,x300682_g_FlagImpactID,0)
		end
		
		local GuildIdB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_GUILD)
		LuaThisScenceM2Guild(sceneId,x300682_g_GuildNotify,GuildIdB,2,1)
		local msg = "�췽ս������ս��ף��"
		LuaThisScenceM2Wrold(sceneId,msg,2,1)
        LuaThisScenceM2Wrold(sceneId,msg,3,1)	
	end
	
	CallScriptFunction(300643,"SetScoreIntervalInc",sceneId,nCampID,-x300682_g_Guild_BufResPoint)  --������Դ��
	
	--LuaThisScenceM2Wrold(sceneId,x300682_g_MapNotify,2,1)

end

function x300682_ProcAcceptCheck( sceneId, selfId, targetId, MissionId, index )
    return 1
end
function x300682_ProcQuestAccept( sceneId, selfId, targetId, MissionId, index )
    
end

	
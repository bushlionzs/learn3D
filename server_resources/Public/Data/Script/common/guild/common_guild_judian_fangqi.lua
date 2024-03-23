x300932_g_ScriptId = 300932
x300932_g_MissionName = "【国家】放弃领地"

function x300932_ProcEnumEvent( sceneId, selfId, targetId, index )
	if GetGuildID( sceneId, selfId ) == -1 then
		--不在帮会中
		return
	end
	
	--if GetGameOpenById(x300932_g_GameId) > 0 then
		AddQuestNumText(sceneId,x300932_g_ScriptId, x300932_g_MissionName, 3)
	--end
end

function x300932_ProcEventEntry( sceneId , selfId , targetId , state , index )
	BeginQuestEvent(sceneId)
	local Readme_1 = "#Y【国家】放弃领地#r#W"
	local Readme_2 = "\t您好，尊敬的领地占有者！您可以在我这里对您当前的领地进行处置，如果您选择放弃领地，您将不会获得任何收益，您现在要放弃对领地的所有权吗？"
	local Readme = Readme_1..Readme_2
	AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300932_g_ScriptId, -1 );
end

function x300932_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end

function x300932_ProcAccept( sceneId, selfId)
	
	
	
	--检查帮会
	local nGuildId = GetGuildID(sceneId,selfId)
	if nGuildId < 0 then
		return
	end
	
	--是否是帮主
    local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= 5 then
		Msg2Player(sceneId,selfId,"很抱歉，您没有权利",8,3)
		Msg2Player(sceneId,selfId,"只有帮主才可以放弃对领地的拥有权！",8,2)
        return
    end
	
	--检查是否是据点守护帮会
	local nMapId0,nMapId1,nMapId2 = GetGuildLairdSceneId(nGuildId)
	if nMapId0 <= 0 then
		Msg2Player(sceneId,selfId,"你不是领地的主人",8,3)
		Msg2Player(sceneId,selfId,"很抱歉，您的帮会目前没有领地所有权",8,2)
		return
	end
	
	--检查是否处于密保状态
	if IsPasswordProtect(sceneId,selfId ) == 1 then
		return
	end
	
	--执行放弃操作
	GameBattleCancleLaird(sceneId,selfId)
	Msg2Player(sceneId,selfId,"成功放弃领地",8,3)
	Msg2Player(sceneId,selfId,"很遗憾，您放弃了领地所有权。",8,2)
	Msg2Player(sceneId,selfId,"很遗憾，帮主放弃了领地所有权！",6,1)
	--其他提示
end
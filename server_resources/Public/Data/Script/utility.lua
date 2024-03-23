-------------------------------------------------------------------------
--问路
-------------------------------------------------------------------------
function x888894_AskTheWay( sceneId, selfId, sceneNum, x, y, tip )
	Msg2Player( sceneId, selfId, "@*;flagNPC;" .. sceneNum .. ";" .. x .. ";" .. y .. ";" .. tip, MSG2PLAYER_PARA )
	Msg2Player( sceneId, selfId, "@*;flashNPC;" .. sceneNum .. ";" .. x .. ";" .. y .. ";" .. tip, MSG2PLAYER_PARA )
end

-------------------------------------------------------------------------
--问路
-------------------------------------------------------------------------
function x888894_AskTheWayPos( sceneId, selfId, sceneNum, x, y, tip )
	Msg2Player( sceneId, selfId, "@*;flagPOS;" .. sceneNum .. ";" .. x .. ";" .. y .. ";" .. tip, MSG2PLAYER_PARA )
	Msg2Player( sceneId, selfId, "@*;flashPOS;" .. sceneNum .. ";" .. x .. ";" .. y .. ";" .. tip, MSG2PLAYER_PARA )
end

-------------------------------------------------------------------------
--让客户端播放背景声音，UICommandID = 11
-------------------------------------------------------------------------
function x888894_PlaySound( sceneId, selfId, soundId )
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, soundId)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId, 11)
end

-------------------------------------------------------------------------
--让客户端停止播放背景声音
-------------------------------------------------------------------------
function x888894_StopSound( sceneId, selfId, soundId )
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, soundId)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId, 12)
end

-------------------------------------------------------------------------
--让客户端播放灯光，UICommandID = 13
-------------------------------------------------------------------------
function x888894_PlayLight( sceneId, selfId, lightId )
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, lightId)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,13)
end

-------------------------------------------------------------------------
--让客户端停止播放灯光
-------------------------------------------------------------------------
function x888894_StopLight( sceneId, selfId, lightId )
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, lightId)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,14)
end

-------------------------------------------------------------------------
--让客户端播放特效，UICommandID = 15
-------------------------------------------------------------------------
function x888894_PlayEffect( sceneId, selfId, effectId )
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, effectId)
	UICommand_AddInt(sceneId, GetSceneInfo(sceneId,"CLIENTRES"))
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,15)
end

-------------------------------------------------------------------------
--停止特效
-------------------------------------------------------------------------
function x888894_StopEffect( sceneId, selfId, effectId )
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, effectId)
	UICommand_AddInt(sceneId, GetSceneInfo(sceneId,"CLIENTRES"))
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,16)
end

-------------------------------------------------------------------------
--让客户端播放snd_info.tab表中的音乐（作为背景音乐）
-------------------------------------------------------------------------
function x888894_PlayBkgSound( sceneId, selfId, soundId )
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, soundId)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,17)
end

-------------------------------------------------------------------------
--让客户端停止播放背景音乐
-------------------------------------------------------------------------
function x888894_StopBkgSound( sceneId, selfId )
	BeginUICommand(sceneId)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,18)
end

-------------------------------------------------------------------------
--客户端新手帮助提示事件
-------------------------------------------------------------------------
function x888894_ShowNewHelp( sceneId, selfId, tableId )
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, tableId)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,19)
end

-------------------------------------------------------------------------
--客户端新手界面引导提示信息
-------------------------------------------------------------------------
function x888894_ShowNewUITips( sceneId, selfId, UITipId,nToggle )
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, UITipId)
	UICommand_AddInt(sceneId, nToggle)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,20)
end

-------------------------------------------------------------------------
--通知客户端播放镜头特效
-------------------------------------------------------------------------
function x888894_PlayClientCameraEffect( sceneId, selfId, effectId,nToggle )
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, effectId)
	UICommand_AddInt(sceneId, nToggle)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,21)
end

-------------------------------------------------------------------------
--播放玫瑰花特效,不走技能系统
-------------------------------------------------------------------------
function x888894_PlayClientRiseEffect( sceneId, selfId)
	BeginUICommand(sceneId)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,22)
end


-------------------------------------------------------------------------
--播放客户端动画特效
-------------------------------------------------------------------------
function x888894_PlayClientAnimEffect( sceneId, selfI,effectId)
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, effectId)
	UICommand_AddInt(sceneId, 1)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,23)
end

-------------------------------------------------------------------------
--停止客户端动画特效
-------------------------------------------------------------------------
function x888894_StopClientAnimEffect( sceneId, selfId,effectId)
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, effectId)
	UICommand_AddInt(sceneId, 0)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,23)
end

-------------------------------------------------------------------------
--播放客户端场景颜色
-------------------------------------------------------------------------
function x888894_PlayClientMapColor( sceneId, selfId, colorId, nTime)
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, colorId)
	UICommand_AddInt(sceneId, 1)
	UICommand_AddInt(sceneId, nTime)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,24)
end

-------------------------------------------------------------------------
--停止客户端场景颜色
-------------------------------------------------------------------------
function x888894_StopClientMapColor( sceneId, selfId, nTime)
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, -1)
	UICommand_AddInt(sceneId, 0)
	UICommand_AddInt(sceneId, nTime)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,24)
end


-------------------------------------------------------------------------
--打开江湖指南
-------------------------------------------------------------------------
function x888894_OpenWorldDirectory( sceneId, selfId)
	BeginUICommand(sceneId)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,25)
end

-------------------------------------------------------------------------
--取得国家名称
-------------------------------------------------------------------------
function x888894_GetCountryName(sceneId,nCountryId)
	
	if nCountryId == 0 then
		return "楼兰王国"
	elseif nCountryId == 1 then
		return "天山王国"
	elseif nCountryId == 2 then
		return "昆仑王国"
	elseif nCountryId == 3 then
		return "敦煌王国"
	end
	
	return ""
	
end

-------------------------------------------------------------------------
--活动:清空MD
-------------------------------------------------------------------------
function x888894_Feast_ClearMD(sceneId,selfId)

	local nFrom = MD_FEAST_BEGIN[1]
	local nTo   = MD_FEAST_END[1]

	SetQuestData(sceneId,selfId,nFrom,16,16,0)
	nFrom = nFrom + 1
	
	for i = nFrom,nTo do
		SetQuestData(sceneId,selfId, i, 0, 32, 0)
	end
end


-------------------------------------------------------------------------
--活动:取得当前ID
-------------------------------------------------------------------------
function x888894_Feast_GetCurrentId(sceneId,selfId)
	return GetQuestData(sceneId,selfId,MD_FEAST_INDEX[1],MD_FEAST_INDEX[2],MD_FEAST_INDEX[3])
end

-------------------------------------------------------------------------
--活动:设置当前ID
-------------------------------------------------------------------------
function x888894_Feast_SetCurrentId( sceneId,selfId,nFeastId)
	
	--检查是否需要清空
	if nFeastId ~=  x888894_Feast_GetCurrentId(sceneId,selfId) then
		x888894_Feast_ClearMD(sceneId,selfId)
	end
	
	--设置当前活动ID
	SetQuestData(sceneId,selfId,MD_FEAST_INDEX[1],MD_FEAST_INDEX[2],MD_FEAST_INDEX[3],nFeastId)
end



--MisDescBegin

x310703_g_ScriptId 					= 310703
x310703_g_MissionName				= "【个人】进阶驯马大师"
x310703_g_MissionId					= 3612
x310703_g_Ability					= 10
x310703_g_Title						= 83
x310703_g_AbillityLevel				= 5
x310703_g_LevelLess					= 55

--MisDescEnd

x310703_g_CommitNPC     = "@npc_139079"
x310703_g_MissionInfo   = "\t想进阶为蒙古驯马术的大师，必须要完成我的考验。\n\t但是要注意，一旦成功进阶，除非遗忘整个蒙古驯马术，否则无法成为其他生活技能的大师。\n\t成为驯马大师可以学习9级蒙古驯马术及一些特殊的蒙古驯马术配方。\n\t你确定要接受考验吗？"           --任务信息
x310703_g_MissionHelp   = "所需的部件由生活技能制造，也可以从其他玩家处获得"          --任务提示信息
x310703_g_MissionTarget = "  收集@item_11041022#W三个\n  收集@item_11041010#W一个\n  收集@item_11041000#W一个\n  收集@item_11041030#W一个\n  收集@item_11041040#W一个\n  收集@item_11041050#W一个"      --任务目标
x310703_g_TitleBonus    = "称号：驯马大师（拥有此称号可以学习更多的驯马技能）"

x310703_g_MissionItem = {
{itemDataId=11041022,count=3},
{itemDataId=11041010,count=1},
{itemDataId=11041000,count=1},
{itemDataId=11041030,count=1},
{itemDataId=11041040,count=1},
{itemDataId=11041050,count=1}
}

x310703_g_AllTitle = {81,82,83,84,85,86}

x310703_g_AllMission = {3610,3611,3612,3613,3614,3615}

function x310703_CheckTitle(sceneId, selfId)
	for i, title in x310703_g_AllTitle do
		if IsHaveTitle(sceneId, selfId, title) > 0 then
			return 0
		end
	end
	return 1
end

function x310703_CheckMission(sceneId, selfId)
	for i, mission in x310703_g_AllMission do
		if IsHaveQuestNM( sceneId, selfId, mission ) == 1 then
			return 0
		end
	end
	return 1
end

function x310703_DoLearn(sceneId, selfId)
	
	local level = QueryPlayerAbilityLevel( sceneId, selfId, x310703_g_Ability );
	if level <= 0 then
		return "您还没有学会相应的生活技能"
	end
	
	if level < x310703_g_AbillityLevel then
		return format("需要%d级的生活技能", x310703_g_AbillityLevel)
	end
	
	if x310703_CheckTitle(sceneId, selfId) == 0 then
		return "你已经获得生活称号了"
	end
	
	if x310703_CheckMission(sceneId, selfId) == 0 then
		return "你已经有其他生活称号任务了，不能接受此任务"
	end
	
	if AddQuestNM( sceneId, selfId, x310703_g_MissionId, x310703_g_ScriptId, 0, 0, 1 ) ~= 1 then
		return "添加任务失败，无法接取本任务。"
	end
	
	if 1 == x310703_IsHaveAllItem( sceneId, selfId ) then
  	local misIndex = GetQuestIndexByID( sceneId, selfId, x310703_g_MissionId )
  	SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
  end
  
	return nil;

end

function x310703_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	state = GetQuestStateNM(sceneId, selfId, targetId, x310703_g_MissionId)
	AddQuestNumText(sceneId,x310703_g_MissionId,x310703_g_MissionName,state,-1);
end

function x310703_IsHaveAllItem( sceneId, selfId )
	local isHaveAllMissionItem = 1
  for i, item in x310703_g_MissionItem do
  	if GetItemCountInBag(sceneId, selfId, item.itemDataId) < item.count then
  		isHaveAllMissionItem = 0
  	end
  end
  return isHaveAllMissionItem
end

function x310703_GetNeedCount( sceneId, selfId, itemDataId )
  for i, item in x310703_g_MissionItem do
  	if itemDataId == item.itemDataId then
  		return item.count
  	end
  end
  return 0
end

function x310703_IsCanSubmit( sceneId, selfId )
	local isHaveAllMissionItem = x310703_IsHaveAllItem( sceneId, selfId )

  if 0 == isHaveAllMissionItem then
  	return "需要的物品还没有收集全"
  end
  
  return nil
end

function x310703_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	if IsHaveQuestNM( sceneId, selfId, x310703_g_MissionId ) <= 0 then
		return
	end
	
	local str = x310703_IsCanSubmit( sceneId, selfId )
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return
	end
	
	for i, item in x310703_g_MissionItem do
		DelItem(sceneId, selfId, item.itemDataId, item.count)
  end

	DelQuestNM( sceneId, selfId, x310703_g_MissionId )
	AwardTitle( sceneId, selfId, x310703_g_Title )
end

function x310703_ProcEventEntry(sceneId, selfId, targetId, MissionId)

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 1 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		if GetQuestParam( sceneId, selfId, misIndex, 7 ) == 1 then
			local str = x310703_IsCanSubmit( sceneId, selfId )
			if str ~= nil then
				Msg2Player(sceneId,selfId,str,8,2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				return
			end
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t你这就收集齐了所有的东西？看来你可以成为蒙古驯马术大师了。")
			EndQuestEvent()
			DispatchQuestContinueInfoNM(sceneId, selfId, targetId, -1, MissionId  );
			return
		end
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y【个人】进阶驯马大师\n\t#W你还没有收集齐我要的东西，收齐再来找我吧。")
		EndQuestEvent()
		DispatchQuestDemandInfo(sceneId, selfId, targetId, x310703_g_ScriptId, MissionId, 0);
	  return
	  
	end
	
	BeginQuestEvent(sceneId);
	
	--任务信息
    AddQuestText( sceneId, "#Y"..x310703_g_MissionName.."\n#W"..x310703_g_MissionInfo)
                 
    --任务目标
    AddQuestText( sceneId, "#Y任务目标：\n#W"..x310703_g_MissionTarget)
    AddQuestText( sceneId, " ")

    --提示信息
    AddQuestText( sceneId, "#Y任务提示：\n#W"..x310703_g_MissionHelp)
    AddQuestText( sceneId, " ")

    --奖励内容
    AddQuestText( sceneId, "#Y奖励内容：\n#W"..x310703_g_TitleBonus)
    AddQuestText( sceneId, " ")

	EndQuestEvent();
	DispatchQuestInfo(sceneId, selfId, targetId, x310703_g_MissionId, -1);
	
end

function x310703_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end

--**********************************

--接受

--**********************************
function x310703_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	local ret = x310703_DoLearn(sceneId, selfId);
	
	if ret ~= nil then
		Msg2Player(sceneId,selfId,ret,8,2)
		Msg2Player(sceneId,selfId,ret,8,3)
	end
	
end

function x310703_ProcQuestItemChanged(sceneId, selfId, itemdataId, nChangeType)

  if IsHaveQuestNM(sceneId, selfId, x310703_g_MissionId) <= 0 then
      return
  end
  
  local isMissionItem = 0
  for i, item in x310703_g_MissionItem do
  	if item.itemDataId == itemdataId then
  		isMissionItem = 1
  	end
  end
  
  if isMissionItem ~= 1 then
  	return
  end
  
  local curCount = GetItemCountInBag(sceneId, selfId, itemdataId)
  local needCount = x310703_GetNeedCount(sceneId, selfId, itemdataId)
  if curCount > needCount then
  	curCount = needCount
  end
  if nChangeType == 0 and curCount <= needCount then
      BeginQuestEvent(sceneId)
      local strText = format("#Y获得物品#G#{_ITEM%d}#Y: %d/%d", itemdataId, curCount, needCount )
      if strText == nil then
          strText = "";
      end
      AddQuestText( sceneId, strText )
      EndQuestEvent( sceneId )
      DispatchQuestTips( sceneId, selfId )
  end
  
  x310703_QuestLogRefresh(sceneId, selfId, x310703_g_MissionId)
  
  if 1 == x310703_IsHaveAllItem( sceneId, selfId ) then
  	local misIndex = GetQuestIndexByID( sceneId, selfId, x310703_g_MissionId )
  	SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
  else
  	local misIndex = GetQuestIndexByID( sceneId, selfId, x310703_g_MissionId )
  	SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
  end
	
end

function x310703_GetCurCount(sceneId, selfId, index)
	local itemCount = GetItemCountInBag(sceneId, selfId, x310703_g_MissionItem[index].itemDataId)
  if itemCount > x310703_g_MissionItem[index].count then
  	itemCount = x310703_g_MissionItem[index].count
  end
  return itemCount
end

function x310703_QuestLogRefresh( sceneId, selfId, MissionId)
		
	if MissionId == nil or MissionId < 0 then
        return
    end
    
    if IsHaveQuestNM(sceneId,selfId,MissionId) <= 0 then
        return
    end

    local szTarget   = ""
    local itemcount  = 0
    local totlecount = 0

    for i = 1, 6 do
        itemcount = x310703_GetCurCount(sceneId, selfId, i)
        totlecount = x310703_g_MissionItem[i].count
        
        if itemcount == totlecount then
            szTarget = szTarget .. format("  #G收集@item_%d#W(%d/%d)", 
            x310703_g_MissionItem[i].itemDataId, itemcount, totlecount)
        else
            szTarget = szTarget .. format("  #W收集@item_%d#W(%d/%d)", 
            x310703_g_MissionItem[i].itemDataId, itemcount, totlecount)
        end
        
        if i < 6 then
        	szTarget = szTarget .. "\n"
        end
    end
  
  BeginQuestEvent(sceneId)
	AddQuestLogCustomText( sceneId,
							x310703_g_MissionName,						-- 标题
							x310703_g_MissionName,        -- 任务名字
							szTarget,		--任务目标
							x310703_g_CommitNPC,			--任务NPC
							"  所需的部件由生活技能制造，也可以从其他玩家处获得\n \n#Y奖励内容：\n\t#W称号：驯马大师（拥有此称号可以学习更多的驯马技能）",               --任务攻略
							"\t想进阶为蒙古驯马术的大师，必须要完成我的考验。\n\t但是要注意，一旦成功进阶，除非遗忘整个蒙古驯马术，否则无法成为其他生活技能的大师。",	--任务描述
							""					--任务小提示
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
end

function x310703_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	x310703_QuestLogRefresh( sceneId, selfId, MissionId );
end

function x310703_ProcQuestAbandon(sceneId, selfId, MissionId)
	DelQuestNM( sceneId, selfId, MissionId )

	local message = "您放弃了:"..x310703_g_MissionName
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 4, 2);

end

function x310703_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没有这个任务
		return
	end
	
end
--MisDescBegin

x310706_g_ScriptId 					= 310706
x310706_g_MissionName				= "�����ˡ����׹��մ�ʦ"
x310706_g_MissionId					= 3615
x310706_g_Ability					= 7
x310706_g_Title						= 86
x310706_g_AbillityLevel				= 5
x310706_g_LevelLess					= 55

--MisDescEnd

x310706_g_CommitNPC     = "@npc_141030"
x310706_g_MissionInfo   = "\t�����Ϊ��˹�������Ĵ�ʦ������Ҫ����ҵĿ��顣\n\t����Ҫע�⣬һ���ɹ����ף���������������˹�������������޷���Ϊ��������ܵĴ�ʦ��\n\t��Ϊ���մ�ʦ����ѧϰ9����˹��������һЩ����Ĳ�˹�������䷽��\n\t��ȷ��Ҫ���ܿ�����"           --������Ϣ
x310706_g_MissionHelp   = "����Ĳ�������������죬Ҳ���Դ�������Ҵ����"          --������ʾ��Ϣ
x310706_g_MissionTarget = "  �ռ�@item_11041052#W����\n  �ռ�@item_11041010#Wһ��\n  �ռ�@item_11041000#Wһ��\n  �ռ�@item_11041020#Wһ��\n  �ռ�@item_11041030#Wһ��\n  �ռ�@item_11041040#Wһ��"      --����Ŀ��
x310706_g_TitleBonus    = "�ƺţ����մ�ʦ��ӵ�д˳ƺſ���ѧϰ����Ĺ��ռ��ܣ�"

x310706_g_MissionItem = {
{itemDataId=11041052,count=3},
{itemDataId=11041010,count=1},
{itemDataId=11041000,count=1},
{itemDataId=11041020,count=1},
{itemDataId=11041030,count=1},
{itemDataId=11041040,count=1}
}

x310706_g_AllTitle = {81,82,83,84,85,86}

x310706_g_AllMission = {3610,3611,3612,3613,3614,3615}

function x310706_CheckTitle(sceneId, selfId)
	for i, title in x310706_g_AllTitle do
		if IsHaveTitle(sceneId, selfId, title) > 0 then
			return 0
		end
	end
	return 1
end

function x310706_CheckMission(sceneId, selfId)
	for i, mission in x310706_g_AllMission do
		if IsHaveQuestNM( sceneId, selfId, mission ) == 1 then
			return 0
		end
	end
	return 1
end

function x310706_DoLearn(sceneId, selfId)
	
	local level = QueryPlayerAbilityLevel( sceneId, selfId, x310706_g_Ability );
	if level <= 0 then
		return "����û��ѧ����Ӧ�������"
	end
	
	if level < x310706_g_AbillityLevel then
		return format("��Ҫ%d���������", x310706_g_AbillityLevel)
	end
	
	if x310706_CheckTitle(sceneId, selfId) == 0 then
		return "���Ѿ��������ƺ���"
	end
	
	if x310706_CheckMission(sceneId, selfId) == 0 then
		return "���Ѿ�����������ƺ������ˣ����ܽ��ܴ�����"
	end
	
	if AddQuestNM( sceneId, selfId, x310706_g_MissionId, x310706_g_ScriptId, 0, 0, 1 ) ~= 1 then
		return "��������ʧ�ܣ��޷���ȡ������"
	end
	
	if 1 == x310706_IsHaveAllItem( sceneId, selfId ) then
  	local misIndex = GetQuestIndexByID( sceneId, selfId, x310706_g_MissionId )
  	SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
  end
  
	return nil;

end

function x310706_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	state = GetQuestStateNM(sceneId, selfId, targetId, x310706_g_MissionId)
	AddQuestNumText(sceneId,x310706_g_MissionId,x310706_g_MissionName,state,-1);
end

function x310706_IsHaveAllItem( sceneId, selfId )
	local isHaveAllMissionItem = 1
  for i, item in x310706_g_MissionItem do
  	if GetItemCountInBag(sceneId, selfId, item.itemDataId) < item.count then
  		isHaveAllMissionItem = 0
  	end
  end
  return isHaveAllMissionItem
end

function x310706_GetNeedCount( sceneId, selfId, itemDataId )
  for i, item in x310706_g_MissionItem do
  	if itemDataId == item.itemDataId then
  		return item.count
  	end
  end
  return 0
end

function x310706_IsCanSubmit( sceneId, selfId )
	local isHaveAllMissionItem = x310706_IsHaveAllItem( sceneId, selfId )

  if 0 == isHaveAllMissionItem then
  	return "��Ҫ����Ʒ��û���ռ�ȫ"
  end
  
  return nil
end

function x310706_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	if IsHaveQuestNM( sceneId, selfId, x310706_g_MissionId ) <= 0 then
		return
	end
	
	local str = x310706_IsCanSubmit( sceneId, selfId )
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return
	end
	
	for i, item in x310706_g_MissionItem do
		DelItem(sceneId, selfId, item.itemDataId, item.count)
  end

	DelQuestNM( sceneId, selfId, x310706_g_MissionId )
	AwardTitle( sceneId, selfId, x310706_g_Title )
end

function x310706_ProcEventEntry(sceneId, selfId, targetId, MissionId)

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 1 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		if GetQuestParam( sceneId, selfId, misIndex, 7 ) == 1 then
			local str = x310706_IsCanSubmit( sceneId, selfId )
			if str ~= nil then
				Msg2Player(sceneId,selfId,str,8,2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				return
			end
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t������ռ��������еĶ�������������Գ�Ϊ��˹��������ʦ�ˡ�")
			EndQuestEvent()
			DispatchQuestContinueInfoNM(sceneId, selfId, targetId, -1, MissionId  );
			return
		end
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y�����ˡ����׹��մ�ʦ\n\t#W�㻹û���ռ�����Ҫ�Ķ����������������Ұɡ�")
		EndQuestEvent()
		DispatchQuestDemandInfo(sceneId, selfId, targetId, x310706_g_ScriptId, MissionId, 0);
	  return
	  
	end
	
	BeginQuestEvent(sceneId);
	
	--������Ϣ
    AddQuestText( sceneId, "#Y"..x310706_g_MissionName.."\n#W"..x310706_g_MissionInfo)
                 
    --����Ŀ��
    AddQuestText( sceneId, "#Y����Ŀ�꣺\n#W"..x310706_g_MissionTarget)
    AddQuestText( sceneId, " ")

    --��ʾ��Ϣ
    AddQuestText( sceneId, "#Y������ʾ��\n#W"..x310706_g_MissionHelp)
    AddQuestText( sceneId, " ")

    --��������
    AddQuestText( sceneId, "#Y�������ݣ�\n#W"..x310706_g_TitleBonus)
    AddQuestText( sceneId, " ")

	EndQuestEvent();
	DispatchQuestInfo(sceneId, selfId, targetId, x310706_g_MissionId, -1);
	
end

function x310706_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end

--**********************************

--����

--**********************************
function x310706_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	local ret = x310706_DoLearn(sceneId, selfId);
	
	if ret ~= nil then
		Msg2Player(sceneId,selfId,ret,8,2)
		Msg2Player(sceneId,selfId,ret,8,3)
	end
	
end

function x310706_ProcQuestItemChanged(sceneId, selfId, itemdataId, nChangeType)

  if IsHaveQuestNM(sceneId, selfId, x310706_g_MissionId) <= 0 then
      return
  end
  
  local isMissionItem = 0
  for i, item in x310706_g_MissionItem do
  	if item.itemDataId == itemdataId then
  		isMissionItem = 1
  	end
  end
  
  if isMissionItem ~= 1 then
  	return
  end
  
  local curCount = GetItemCountInBag(sceneId, selfId, itemdataId)
  local needCount = x310706_GetNeedCount(sceneId, selfId, itemdataId)
  if curCount > needCount then
  	curCount = needCount
  end
  if nChangeType == 0 and curCount <= needCount then
      BeginQuestEvent(sceneId)
      local strText = format("#Y�����Ʒ#G#{_ITEM%d}#Y: %d/%d", itemdataId, curCount, needCount )
      if strText == nil then
          strText = "";
      end
      AddQuestText( sceneId, strText )
      EndQuestEvent( sceneId )
      DispatchQuestTips( sceneId, selfId )
  end
  
  x310706_QuestLogRefresh(sceneId, selfId, x310706_g_MissionId)
  
  if 1 == x310706_IsHaveAllItem( sceneId, selfId ) then
  	local misIndex = GetQuestIndexByID( sceneId, selfId, x310706_g_MissionId )
  	SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
  else
  	local misIndex = GetQuestIndexByID( sceneId, selfId, x310706_g_MissionId )
  	SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
  end
	
end

function x310706_GetCurCount(sceneId, selfId, index)
	local itemCount = GetItemCountInBag(sceneId, selfId, x310706_g_MissionItem[index].itemDataId)
  if itemCount > x310706_g_MissionItem[index].count then
  	itemCount = x310706_g_MissionItem[index].count
  end
  return itemCount
end

function x310706_QuestLogRefresh( sceneId, selfId, MissionId)
		
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
        itemcount = x310706_GetCurCount(sceneId, selfId, i)
        totlecount = x310706_g_MissionItem[i].count
        
        if itemcount == totlecount then
            szTarget = szTarget .. format("  #G�ռ�@item_%d#W(%d/%d)", 
            x310706_g_MissionItem[i].itemDataId, itemcount, totlecount)
        else
            szTarget = szTarget .. format("  #W�ռ�@item_%d#W(%d/%d)", 
            x310706_g_MissionItem[i].itemDataId, itemcount, totlecount)
        end
        
        if i < 6 then
        	szTarget = szTarget .. "\n"
        end
    end
  
  BeginQuestEvent(sceneId)
	AddQuestLogCustomText( sceneId,
							x310706_g_MissionName,						-- ����
							x310706_g_MissionName,        -- ��������
							szTarget,		--����Ŀ��
							x310706_g_CommitNPC,			--����NPC
							"  ����Ĳ�������������죬Ҳ���Դ�������Ҵ����\n \n#Y�������ݣ�\n\t#W�ƺţ����մ�ʦ��ӵ�д˳ƺſ���ѧϰ����Ĺ��ռ��ܣ�",               --������
							"\t�����Ϊ��˹�������Ĵ�ʦ������Ҫ����ҵĿ��顣\n\t����Ҫע�⣬һ���ɹ����ף���������������˹�������������޷���Ϊ��������ܵĴ�ʦ��",	--��������
							""					--����С��ʾ
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
end

function x310706_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	x310706_QuestLogRefresh( sceneId, selfId, MissionId );
end

function x310706_ProcQuestAbandon(sceneId, selfId, MissionId)
	DelQuestNM( sceneId, selfId, MissionId )

	local message = "��������:"..x310706_g_MissionName
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 4, 2);

end

function x310706_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û���������
		return
	end
	
end
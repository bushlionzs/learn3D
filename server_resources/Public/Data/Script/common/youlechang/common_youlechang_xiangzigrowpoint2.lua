--������

x310331_g_GrowpointId = 198 		--��Ӧ������ID
x310331_g_MinLevel = 20   	


x310331_g_MissionName="�����ˡ����ı���"
x310331_g_MissionId = 9050
x310331_g_ItemNum = 1

x310331_g_ItemId = 12035000
x310331_g_ItemIndex =12035000
x310331_g_BossTypeTab ={17300,17301,17302,17303,17304,17305,17306,17307,17308,17309,17310,17311,17312}

function x310331_HaveAccepted(sceneId, selfId)
	if IsHaveQuestNM( sceneId, selfId, x310331_g_MissionId ) > 0 then
		return 1
	end
	return 0
end



--���ɺ�����ʼ************************************************************************
function 	x310331_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x310331_g_GrowpointId, sceneId, 0, x310331_g_ItemIndex)
	SetGrowPointObjID(sceneId,x310331_g_GrowpointId,x, y,ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x310331_OnOpen(sceneId,selfId,targetId)
		--PrintStr("x310331_OnOpen")
    return x310331_OnOpenItemBox(sceneId, selfId, targetId, x310331_g_GrowpointId, x310331_g_ItemIndex)	
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x310331_OnRecycle(sceneId,selfId,targetId)
	return   x310331_OnGuildRecycle( sceneId, selfId, targetId, x310331_g_GrowpointId, x310331_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x310331_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x310331_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--**********************************************************************
--�ɼ�����
--��ItemBox
function x310331_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	local misIndex = GetQuestIndexByID( sceneId, selfId, x310331_g_MissionId)
	if x310331_HaveAccepted(sceneId, selfId) <= 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��û�����񡾸��ˡ����ı��䡣")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return -31
	end
	if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"������ɴ�����")
        EndQuestEvent(sceneId)
        --DispatchQuestEventList(sceneId,selfId,NPCId)
        DispatchQuestTips(sceneId,selfId)
		return -31
	end	
	    
	if GetLevel(sceneId, selfId) < x310331_g_MinLevel then  		--�ȼ����� 
		return -31
	end
	--SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
  	--SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
	return 0
	
	
end

function x310331_ShowTipsToAll(sceneId, str)

	local nHumanCount = GetScenePlayerCount( sceneId)
    if nHumanCount > 0 then
        for i = 0, nHumanCount do
            local objId = GetScenePlayerObjId( sceneId,i)
            if objId >= 0 then
                Msg2Player(sceneId, objId, str, 0, 2)
            end
        end
    end
end

function x310331_GiveMainItem(sceneId, selfId)
	BeginAddItem( sceneId)
	AddItem( sceneId, x310331_g_ItemId, 1)
	if EndAddItem( sceneId, selfId) <= 0 then
	    Msg2Player( sceneId, selfId, "��ı����������޷���õ��߽�����", 8, 2)
	else
	    AddItemListToPlayer( sceneId, selfId)
	end
end


function x310331_GiveExp( sceneId, selfId)
	local rate = random(1,100)
	if rate == 100 then
		local level = GetLevel(sceneId,selfId)
		local bonusExp = 64800 * level * 3
		AddExp(sceneId,selfId,bonusExp)
		local name = GetName(sceneId,selfId)
		if name == nil then
			name = "ErrorName"
		end

		x310331_ShowTipsToAll(sceneId, name.."�����˸߾��顣")
		return 1
	elseif rate >= 75 then
		local level = GetLevel(sceneId,selfId)
		local bonusExp = 64800 * level * 1.5
		AddExp(sceneId,selfId,bonusExp)
		return 1
	else
		local level = GetLevel(sceneId,selfId)
		local bonusExp = 64800 * level
		AddExp(sceneId,selfId,bonusExp)
		return 1
	end
	return 0
end
function x310331_GiveItem( sceneId, selfId)
	local bossRate = random(1,100)*random(1,100)
	if bossRate == 1 then   --������ʮ��ħ��
		local ran = random(1,getn(x310331_g_BossTypeTab))
		local x,z = GetWorldPos(sceneId, selfId)
		CreateMonster(sceneId, x310331_g_BossTypeTab[ran], x, z, 1, -1, -1, -1, 21,-1, 0)
		
		local name = GetName(sceneId,selfId)
		if name == nil then
			name = "ErrorName"
		end
		x310331_ShowTipsToAll(sceneId, name.."�ڿ�������ʱ�ų���ʮ��ħ����")
		return 0
	end
	
	local rate = random(1,100)
	local itemId = 12035010
	if rate <= 10 then
		itemId = 12035010
	elseif rate <= 20 then
		itemId = 12035011
	elseif rate <= 30 then
		itemId = 12035012
	elseif rate <= 40 then
		itemId = 12035013
	else
		Msg2Player(sceneId, selfId, "�����������ʲôҲû�С�", 0, 3)
		return 0
	end
	--����һ�βɼ�����
	BeginAddItem( sceneId )
	AddItem( sceneId, itemId, 1 )
	--print(needItemID)
	local ret = EndAddItem( sceneId, selfId )
	if ret > 0 then
		--SetGrowPointCurrSeedNum( sceneId, gpType, seedNum-1 )
		AddItemListToPlayer(sceneId,selfId)
		BeginQuestEvent(sceneId)
		local msg = format( "������@item_%d��",itemId)
		AddQuestText(sceneId,msg)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		return 1
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��������������������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return -1
	end	
		
		
	--LuaAllScenceM2Wrold (sceneId,str, 5, 1)
	return 0
end


function x310331_CreateBoss( sceneId, selfId)
	local name = GetName(sceneId,selfId)
	if name == nil then
		name = "ErrorName"
	end
	LuaAllScenceM2Wrold (sceneId,name.."�����BOSS", 5, 1)
	return 1
end
--����
function x310331_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )
		
	local misIndex = GetQuestIndexByID(sceneId,selfId,x310331_g_MissionId)
	if GetBagSpace(sceneId,selfId) <= 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��������������������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end
	if x310331_GiveItem( sceneId, selfId) ~= -1 then		
		local num = GetQuestParam( sceneId,selfId,misIndex,1)
		num = num + 1
		SetQuestByIndex( sceneId, selfId, misIndex, 1, num )
		if num >= 5 then
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 1 )
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
		end
	end
		CallScriptFunction( 310322, "ProcQuestLogRefresh", sceneId, selfId, x310331_g_MissionId)
		return 1

end
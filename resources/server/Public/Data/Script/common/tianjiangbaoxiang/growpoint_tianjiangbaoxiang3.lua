--������

x310013_g_GrowpointId = 402 		--��Ӧ������ID
x310013_g_MinLevel = 20   	
x310013_g_ItemIndex =  12030051


x310013_g_MissionList = {8022,8023,8024,8025,8026,8027,8028,8029,8030,8031,8032,8033,8034,8035,8036,8037,8038,8039,8040, 8041, 8042, 8043, 8044, 8045}
x310013_g_ItemNum = 3
x310013_g_ItemList = {12030051, 12030052, 12030053}
x310013_g_MaterialNum = 8
x310013_g_MaterialList ={11020001, 11020002, 11020006, 11020007, 11030001, 11030003, 11030401, 11030402}

function x310013_HaveAccepted(sceneId, selfId)

	for i, item in x310013_g_MissionList do
		if IsHaveQuestNM( sceneId, selfId, item ) > 0 then
			return 1
		end
	end
	return -1
end

function x310013_RandItem(sceneId, selfId)
	local kindIndex = random(1, 3);
	
	if kindIndex == 1 then
		local itemIndex = random(1, x310013_g_ItemNum)
		return x310013_g_ItemList[itemIndex]
	end

	if kindIndex == 2 then
		local materialIndex = random(1, x310013_g_MaterialNum)
		return x310013_g_MaterialList[materialIndex]
	end

    return -1

end


--���ɺ�����ʼ************************************************************************
function 	x310013_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x310013_g_GrowpointId, sceneId, 0, x310013_g_ItemIndex)
	SetGrowPointObjID(sceneId,x310013_g_GrowpointId,x, y,ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x310013_OnOpen(sceneId,selfId,targetId)
		--PrintStr("x310013_OnOpen")
    return x310013_OnOpenItemBox(sceneId, selfId, targetId, x310013_g_GrowpointId, x310013_g_ItemIndex)	
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x310013_OnRecycle(sceneId,selfId,targetId)
	return   x310013_OnGuildRecycle( sceneId, selfId, targetId, x310013_g_GrowpointId, x310013_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x310013_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x310013_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--**********************************************************************
--�ɼ�����
--��ItemBox
function x310013_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	
	if x310013_HaveAccepted(sceneId, selfId) < 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��û�����񡾸��ˡ��콵���䣬������עϵͳ���档")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return -31
	end
	    
	if GetLevel(sceneId, selfId) < x310013_g_MinLevel then  		--�ȼ����� 
		return -31
	end

	return 0
end

--����
function x310013_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )
  	
	--����һ�βɼ�����
	local itemAdd = 1
	needItemID = x310013_RandItem(sceneId, selfId)

	if needItemID == nil or needItemID < 0 then 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"������ʲôҲû��")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		return 1
	end

	BeginAddItem( sceneId )
	AddItem( sceneId, needItemID, itemAdd )
	local ret = EndAddItem( sceneId, selfId )
	if ret > 0 then
		--SetGrowPointCurrSeedNum( sceneId, gpType, seedNum-1 )
		AddItemListToPlayer(sceneId,selfId)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,format("#Y�����Ʒ#G#{_ITEM%d}#Y��", needItemID))
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		
		return 1
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��������������������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end
	
end
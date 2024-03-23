--������
--MisDescBegin
x301458_g_GrowpointId = 124 --��Ӧ������ID
x301458_g_ItemIndex = 13011604 --��Ӧ�ռ���Ʒ��ID
x301458_g_BufIndex = 7600
x301458_g_GroupPoint	=	{ {type=10,id =124,target = "��ľ"}}
--MisDescEnd

x301458_g_Growpointlevel = {
							{MissionId = 7006, level = 60,itmID =13011005,needItemCount = 5,collNum = 1},
							{MissionId = 7011, level = 75,itmID =13011602,needItemCount = 5,collNum = 1},
							{MissionId = 7012, level = 85,itmID =13011604,needItemCount = 5,collNum = 1},
							{MissionId = 7746, level = 95,itmID =13011605,needItemCount = 5,collNum = 1},
							{MissionId = 7747, level = 105,itmID =13011606,needItemCount = 5,collNum = 1},							
							{MissionId = 7780, level = 115,itmID =13011607,needItemCount = 5,collNum = 1},								
							{MissionId = 7013, level = 60,itmID =13011005,needItemCount = 5,collNum = 1},
							{MissionId = 7014, level = 75,itmID =13011602,needItemCount = 5,collNum = 1},
							{MissionId = 7015, level = 85,itmID =13011604,needItemCount = 5,collNum = 1},
							{MissionId = 7748, level = 95,itmID =13011605,needItemCount = 5,collNum = 1},
							{MissionId = 7749, level = 105,itmID =13011606,needItemCount = 5,collNum = 1},							
							{MissionId = 7781, level = 115,itmID =13011607,needItemCount = 5,collNum = 1},								
							{MissionId = 7698, level = 60,itmID =13011005,needItemCount = 5,collNum = 1},
							{MissionId = 7699, level = 75,itmID =13011602,needItemCount = 5,collNum = 1},
							{MissionId = 7700, level = 85,itmID =13011604,needItemCount = 5,collNum = 1},
							{MissionId = 7750, level = 95,itmID =13011605,needItemCount = 5,collNum = 1},
							{MissionId = 7751, level = 105,itmID =13011606,needItemCount = 5,collNum = 1},							
							{MissionId = 7782, level = 115,itmID =13011607,needItemCount = 5,collNum = 1},								
							{MissionId = 7701, level = 60,itmID =13011005,needItemCount = 5,collNum = 1},
							{MissionId = 7702, level = 75,itmID =13011602,needItemCount = 5,collNum = 1},
							{MissionId = 7703, level = 85,itmID =13011604,needItemCount = 5,collNum = 1},						
							{MissionId = 7752, level = 95,itmID =13011605,needItemCount = 5,collNum = 1},
							{MissionId = 7753, level = 105,itmID =13011606,needItemCount = 5,collNum = 1},	
							{MissionId = 7783, level = 115,itmID =13011607,needItemCount = 5,collNum = 1},					
		}                                         

x301458_g_GrowpointPos = {
							 {posx1=176, posz1=220,posx2=43, posz2=57,posx3=86, posz3=60,--posx4 = 67.879761, posz4 = 92.065254,posx5 = 32.79665, posz5 = 204.992188,posx6 = 197.990417, posz6 = 97.425476,posx7 = 224.641403, posz7 = 104.538422,posx8 = 58.52943, posz8 = 82.746719,posx9 = 47.733585, posz9 = 74.672951,
							 },							
		}		

--���ɺ�����ʼ************************************************************************
function 	x301458_OnCreate(sceneId,growPointType,x,y)
	
	local ItemBoxId = ItemBoxEnterScene(x, y, x301458_g_GrowpointId, sceneId, 0, x301458_g_ItemIndex)
	SetGrowPointObjID(sceneId,x301458_g_GrowpointId,x, y,ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301458_OnOpen(sceneId,selfId,targetId)
	return x301458_OnOpenItemBox(sceneId, selfId, targetId, x301458_g_GrowpointId, x301458_g_ItemIndex)
	--return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox", sceneId, selfId, targetId, x301458_g_GrowpointId, x301458_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301458_OnRecycle(sceneId,selfId,targetId)
	return   x301458_OnGuildRecycle( sceneId, selfId, targetId, x301458_g_GrowpointId, x301458_g_ItemIndex )
	--return CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x301458_g_GrowpointId, x301458_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301458_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function x301458_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, -1 )
end


--**********************************************************************
--�ɼ�����
--��ItemBox
function x301458_GetMissionDesc(sceneId, selfId)
	for i,itm in x301458_g_Growpointlevel do
		if IsHaveQuestNM(sceneId, selfId,itm.MissionId ) > 0 then
			return itm
		end
	end
	return nil
end

function x301458_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	local missionDesc = x301458_GetMissionDesc(sceneId, selfId)
	if missionDesc == nil then
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ����û�С���᡿���ͼ�������޷��ɼ�",8,2)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ����û�С���᡿���ͼ�������޷��ɼ�",8,3)
		return 1
	end
	local MissionId = missionDesc.MissionId
	local needItemCount = missionDesc.needItemCount
	local collNum = missionDesc.collNum 
	local needItemID = missionDesc.itmID
	local itemCountNow = GetItemCount( sceneId, selfId, needItemID )
		if itemCountNow >= needItemCount then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��Ʒ�Ѿ��ռ���ȫ")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1
	end
	if MissionId == -1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ����û������");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ����û������",8,2)
		return 0 --û���������
	end
	
	if IsQuestHaveDoneNM( sceneId, selfId, missionDesc.MissionId ) > 0 then --�����Ѿ����
		return 1
	end
	
	local level = GetLevel(sceneId,selfId)
	if sceneId == 8 and level > 65 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"���ĵȼ�����")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����ĵȼ����ڱ���ͼ����ȥ���ߵȼ��ĵ�ͼ�������",8,2)
		return 1
	end
	if sceneId == 9 and level > 70 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"���ĵȼ�����")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����ĵȼ����ڱ���ͼ����ȥ���ߵȼ��ĵ�ͼ�������",8,2)
		return 1
	end
	if sceneId ==10 and level > 75 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"���ĵȼ�����")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����ĵȼ����ڱ���ͼ����ȥ���ߵȼ��ĵ�ͼ�������",8,2)
		return 1
	end
end

function x301458_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )
	local missionDesc = x301458_GetMissionDesc(sceneId, selfId)
	if missionDesc == nil then
		return 1
	end
	local MissionId = missionDesc.MissionId
	local needItemCount = missionDesc.needItemCount
	local collNum = missionDesc.collNum 
	local needItemID = missionDesc.itmID
	local level = GetLevel(sceneId,selfId)
	if level <=  75 then
		if sceneId == 9 then
			 local nRet = random(1,80000)
			 if nRet <= 10 then --�ɼ���ȫ�����
					local name = GetName(sceneId,selfId)
					local msg1 = "����"..name.."���ռ�ͼ��ʱ��������䣬��Ҷ�Ǹ�����������֮��"
					LuaAllScenceM2Wrold(sceneId, msg1, CHAT_PLANE_SCROLL, 1)
					LuaAllScenceM2Wrold(sceneId, msg1, CHAT_LEFTDOWN, 1)
					LuaAllScenceM2Wrold(sceneId, msg1, CHAT_MAIN_RIGHTDOWN, 1)
					CreateMonster(sceneId,3059,x301458_g_GrowpointPos[1].posx1, x301458_g_GrowpointPos[1].posz1, 16,-1, -1,13079463,21,1000 * 60 *15 )
					CreateMonster(sceneId,3059,x301458_g_GrowpointPos[1].posx2, x301458_g_GrowpointPos[1].posz2, 16,-1, -1,13079463,21,1000 * 60 *15 )
					CreateMonster(sceneId,3059,x301458_g_GrowpointPos[1].posx3, x301458_g_GrowpointPos[1].posz3, 16,-1, -1,13079463,21,1000 * 60 *15 )
					-- CreateMonster(sceneId,3059,x301458_g_GrowpointPos[1].posx4, x301458_g_GrowpointPos[1].posz4, 16,50, -1,13079463,21,1000 * 60 *5 )
					-- CreateMonster(sceneId,3059,x301458_g_GrowpointPos[1].posx5, x301458_g_GrowpointPos[1].posz5, 16,50, -1,13079463,21,1000 * 60 *5 )
					-- CreateMonster(sceneId,3059,x301458_g_GrowpointPos[1].posx6, x301458_g_GrowpointPos[1].posz6, 16,50, -1,13079463,21,1000 * 60 *5 )
					-- CreateMonster(sceneId,3059,x301458_g_GrowpointPos[1].posx7, x301458_g_GrowpointPos[1].posz7, 16,50, -1,13079463,21,1000 * 60 *5 )
					-- CreateMonster(sceneId,3059,x301458_g_GrowpointPos[1].posx8, x301458_g_GrowpointPos[1].posz8, 16,50, -1,13079463,21,1000 * 60 *5 )
					-- CreateMonster(sceneId,3059,x301458_g_GrowpointPos[1].posx9, x301458_g_GrowpointPos[1].posz9, 16,50, -1,13079463,21,1000 * 60 *5 )
				return 1
			end                                                                                   
		end
	--����һ�βɼ�����
		local itemCountNow = GetItemCount( sceneId, selfId, needItemID )
		local itemAdd = needItemCount - itemCountNow
		itemAdd = random(itemAdd)
		if itemAdd < collNum then
			itemAdd = collNum
		end

		BeginAddItem( sceneId )
		AddItem( sceneId, needItemID, itemAdd )
		local ret = EndAddItem( sceneId, selfId )
		if ret > 0 then
			 AddItemListToPlayer(sceneId,selfId)
			 return 1
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�޷��õ��ɼ���Ʒ������������")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 0
		end
	end
    return 0
end

--**********************************************************************


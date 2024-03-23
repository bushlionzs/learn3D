--������
--MisDescBegin
x300650_g_GrowpointId = 101 --��Ӧ������ID
x300650_g_ItemIndex = 13011005 --��Ӧ�ռ���Ʒ��ID
x300650_g_BufIndex = 7631
x300650_g_GroupPoint	=	{ {type=10,id =101,target = "��ľ"}}
--MisDescEnd

x300650_g_GrowpointPos = {
							{posx1=69, posz1=88,posx2=10, posz2=16,posx3=84, posz3=61,posx4 = 84, posz4 = 61,posx5 = 84, posz5 = 61,},
							{posx1=88, posz1=31,posx2=14, posz2=97,posx3=72, posz3=106,posx4 = 84, posz4 = 61,posx5 = 84, posz5 = 61,},
							{posx1=84, posz1=61,posx2=21, posz2=24,posx3=29, posz3=107,posx4 = 44, posz4 = 68,posx5 = 45, posz5 = 40,},							
		}

--���ɺ�����ʼ************************************************************************
function 	x300650_OnCreate(sceneId,growPointType,x,y)
	
	local ItemBoxId = ItemBoxEnterScene(x, y, x300650_g_GrowpointId, sceneId, 0, x300650_g_ItemIndex)
	SetGrowPointObjID(sceneId,x300650_g_GrowpointId,x, y,ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x300650_OnOpen(sceneId,selfId,targetId)
	return x300650_OnOpenItemBox(sceneId, selfId, targetId, x300650_g_GrowpointId, x300650_g_ItemIndex)
	--return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox", sceneId, selfId, targetId, x300650_g_GrowpointId, x300650_g_ItemIndex )
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x300650_OnRecycle(sceneId,selfId,targetId)
	return   x300650_OnGuildRecycle( sceneId, selfId, targetId, x300650_g_GrowpointId, x300650_g_ItemIndex )
	--return CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x300650_g_GrowpointId, x300650_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x300650_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x300650_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, -1 )
end


--**********************************************************************
--�ɼ�����
--��ItemBox
function x300650_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )

	local MissionId, needItemCount, collNum = GetItemIdInItemBoxNM( sceneId, selfId, targetId, gpType, needItemID )
	if MissionId == -1 then
		return  --û���������
	end

	--����������Ѿ����ֱ���˳�
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --�����Ѿ����
		return 1
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��û���������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1
	end
	local level = GetLevel(sceneId,selfId)
	if level > 60 then
	return 1
	end

	local itemCountNow = GetItemCount( sceneId, selfId, needItemID )
	if itemCountNow >= needItemCount then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��Ʒ�Ѿ��ռ���ȫ")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1
	end

	return 0
end

--����
function x300650_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )

	local MissionId, needItemCount, collNum = GetItemIdInItemBoxNM( sceneId, selfId, targetId, gpType, needItemID )
	if MissionId == -1 then
		return 0 --û���������
	end

	--����������Ѿ����ֱ���˳�
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --�����Ѿ����
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end

	local itemCountNow = GetItemCount( sceneId, selfId, needItemID )
	if itemCountNow >= needItemCount then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��Ʒ�Ѿ��ռ���ȫ")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end

	--����������¼�
	local nRet = random(1,1160)   --�ɼ����֡��ɼ���ȫ����ʧ���侭�顢BUF���ɼ���ȫ�����     10��10+5��15+50��65+50��115+1

	if nRet <= 10 then
		 --�ɼ�����ʧ��ԭ��ˢ��һֻ��
		local x = GetItemBoxWorldPosX(sceneId,targetId)
		local z = GetItemBoxWorldPosZ(sceneId,targetId)
   		CreateMonster(sceneId,9562, x, z, 16,50, -1,13079463,21,1000 * 60 *3 )
		BeginQuestEvent(sceneId);AddQuestText( sceneId, "��ľ��ɹ��������й���");EndQuestEvent( sceneId );DispatchQuestTips( sceneId, selfId )
		return 1
	-- elseif nRet <= 15 then
	    --�����ڲɼ���ȫ����ʧ
		-- local name = GetName(sceneId,selfId)
	    -- LuaThisScenceM2Wrold(sceneId,"����"..name.."�ڲɼ��д����˵ر䣬���к�ľ��ʧ",2,1)
		-- RecycleGrowPointByType(sceneId,x300650_g_GrowpointId,1000 * 60 *3)
	    -- return 0
	elseif nRet <= 65 then
  		--�ɼ�����ʧ����þ���
        AddExp(sceneId, selfId,10000)
		BeginQuestEvent(sceneId);AddQuestText( sceneId, "��ľ���ߣ��õ�10000�㾭��");EndQuestEvent( sceneId );DispatchQuestTips( sceneId, selfId )
	    return 1
 	elseif nRet <= 115 then
        --�ɼ�����ʧ�����BUF
		local Ret = SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x300650_g_BufIndex, 0);
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x300650_g_BufIndex, 0);
		BeginQuestEvent(sceneId);AddQuestText( sceneId, "��ľ���ߣ����������˵�ô�");EndQuestEvent( sceneId );DispatchQuestTips( sceneId, selfId )
 	    return 1
   	-- elseif nRet <= 116 then
 	    --����ȫ�����
		-- RecycleGrowPointByType(sceneId,x300650_g_GrowpointId,1000 * 60 *3)
	    -- local name = GetName(sceneId,selfId)
	    -- LuaThisScenceM2Wrold(sceneId,"����"..name.."�ڲɼ��д��������֣����к�ľ��ʧ��ɹ���",2,1)
			-- if sceneId == 4 then
				-- CreateMonster(sceneId,9562,x300650_g_GrowpointPos[1].posx1, x300650_g_GrowpointPos[1].posz1, 16,50, -1,13079463,21,1000 * 60 *5 )
				-- CreateMonster(sceneId,9562,x300650_g_GrowpointPos[1].posx2, x300650_g_GrowpointPos[1].posz2, 16,50, -1,13079463,21,1000 * 60 *5 )				
			-- elseif sceneId == 5 then
				-- CreateMonster(sceneId,9562,x300650_g_GrowpointPos[2].posx1, x300650_g_GrowpointPos[2].posz1, 16,50, -1,13079463,21,1000 * 60 *5 )
				-- CreateMonster(sceneId,9562,x300650_g_GrowpointPos[2].posx2, x300650_g_GrowpointPos[2].posz2, 16,50, -1,13079463,21,1000 * 60 *5 )				
				-- CreateMonster(sceneId,9562,x300650_g_GrowpointPos[2].posx3, x300650_g_GrowpointPos[2].posz3, 16,50, -1,13079463,21,1000 * 60 *1 )					
			-- elseif sceneId == 6 then
				-- CreateMonster(sceneId,9562,x300650_g_GrowpointPos[3].posx1, x300650_g_GrowpointPos[3].posz1, 16,50, -1,13079463,21,1000 * 60 *5 )
				-- CreateMonster(sceneId,9562,x300650_g_GrowpointPos[3].posx2, x300650_g_GrowpointPos[3].posz2, 16,50, -1,13079463,21,1000 * 60 *5 )				
				-- CreateMonster(sceneId,9562,x300650_g_GrowpointPos[3].posx3, x300650_g_GrowpointPos[3].posz3, 16,50, -1,13079463,21,1000 * 60 *5 )								
				-- CreateMonster(sceneId,9562,x300650_g_GrowpointPos[3].posx4, x300650_g_GrowpointPos[3].posz4, 16,50, -1,13079463,21,1000 * 60 *5 )				
				-- CreateMonster(sceneId,9562,x300650_g_GrowpointPos[3].posx5, x300650_g_GrowpointPos[3].posz5, 16,50, -1,13079463,21,1000 * 60 *5 )								
			-- end
 	    -- return 0
	end

	--����һ�βɼ�����
	local itemAdd = needItemCount - itemCountNow
	if collNum == -1 then
		itemAdd = 1
	else
		if itemAdd > collNum then
			itemAdd = collNum
		end
	end
	if itemAdd > 1 then
		itemAdd = random(itemAdd)
		if itemAdd == 0 then
			itemAdd = 1
		end
	end

	BeginAddItem( sceneId )
	AddItem( sceneId, needItemID, itemAdd )
	local ret = EndAddItem( sceneId, selfId )
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
		return 1
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�޷��õ��ɼ���Ʒ���������������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end

end

--**********************************************************************


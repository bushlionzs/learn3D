--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x300576_g_MissionId 				= 	9332                     --����ID
x300576_g_ScriptId 					= 	300576                  --�ű�ID
x300576_g_MissionKind 				= 	1                       --��������
x300576_g_LevelLess					= 	40                      --�������ŵȼ�  <=0 ��ʾ������


x300576_g_MissionName				= 	"�����ˡ���ǻ���"
x300576_g_MissionName1				= 	"�����˵��������Ů��"
x300576_g_MissionTarget				= 	"��ϸ�о�#G���׵�����ͼ#W���ҵ������#G���׵���"
x300576_g_MissionInfo				= 	""
x300576_g_ContinueInfo				= 	""
x300576_g_MissionCompleted			= 	""
x300576_g_MissionHelp				=	""          --������ʾ��Ϣ

--Ŀ��
x300576_g_ExtTarget					=	{ {type=20,n=1,target="�����ˡ���ǻ���"}}

--����

x300576_g_ExpBonus					= 	0;--x300576_AddExpAward               	--����������
x300576_g_BonusItem					=	{}	--��������Ʒ

x300576_g_BonusMoney1               = 	0
x300576_g_BonusMoney2               =   0
x300576_g_BonusMoney3               =   0

x300576_g_BonusChoiceItem           =   {}


--MisDescEnd



x300576_g_NpcCount =10

x300576_g_GrowPointList = {                                  
						{name = "���׵�", x=87.4, z=153.7 ,itemid=13810140,gpid=208},
						{name = "���׵�", x=119.4, z=141.2,itemid=13810141,gpid=209},
						{name = "���׵�", x=101.4, z=119.5,itemid=13810142,gpid=210},
						{name = "���׵�", x=110.7, z=163.1,itemid=13810143,gpid=211},
						{name = "���׵�", x=125.2, z=88.4,itemid=13810144,gpid=212},
						{name = "���׵�", x=87.2, z=132.5,itemid=13810145,gpid=213}, 
						{name = "���׵�", x=125.1, z=112.8,itemid=13810146,gpid=214},
						{name = "���׵�", x=89.5, z=89.7,itemid=13810147,gpid=215}, 
						{name = "���׵�", x=131, z=163.5,itemid=13810148,gpid=216},
						{name = "���׵�", x=86.7, z=119.5,itemid=13810149,gpid=217} 
                                                       
					}
					
x300576_g_ReplyNpcId = 143046

x300576_g_GameId	= 1013

x300576_g_TaskItemId = 13810151
x300576_g_ItemId = 12030028


x300576_g_BonusChoiceItem2   = {
								{10019300,10077300,10238300,10208300,10268300,10248300,10258300,10278300},
								{10028300,10087300,10238310,10208310,10268310,10248310,10258310,10278310},
								{10038300,10097300,10238320,10208320,10268320,10248320,10258320,10278320},
								{10048300,10107300,10238330,10208330,10268330,10248330,10258330,10278330},
								{10058300,10117300,10238340,10208340,10268340,10248340,10258340,10278340},
								{10068300,10127300,10238350,10208350,10268350,10248350,10258350,10278350}
									
								}

-- ��������Ʒ�б�
x300576_g_RewardTable       = {
                                { minLevel = 40, maxLevel = 60,  items = { { id = 11000201, cnt = 8 }, { id = 11050002, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 60, maxLevel = 80,  items = { { id = 11000202, cnt = 8 }, { id = 11050003, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 80, maxLevel = 999, items = { { id = 11000203, cnt = 8 }, { id = 11050004, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
}


function x300576_GetMissionId( sceneId, selfId )
	return x300576_g_MissionId
end

function x300576_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local level = GetLevel( sceneId,selfId )
    if level < x300576_g_LevelLess then
       return
    end

	local myMissionId = x300576_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300576_g_MissionName,8,1);
	else
		local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		
		AddQuestNumText(sceneId, myMissionId, x300576_g_MissionName,state,state);

	end


	
end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300576_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	
	if GetGameOpenById(x300576_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300576_g_MissionId) == 0 then
		x300576_ShowTips(sceneId, selfId, "�˻���첻���ţ������뵽�󶼰�������ѯÿ��������")
		return
	end

	local myMissionId = x300576_GetMissionId( sceneId, selfId )	
	
	
	
	
		
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		x300576_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
	else
		if nExt==7 then
			x300576_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
		else
			x300576_DispatchContinueInfo( sceneId, selfId, targetId,myMissionId )
		end
		
	end
end


function x300576_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x300576_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300576_g_MissionId) == 0 then
		
		return 0;
	end
	return 1;

end

function x300576_CheckRequest(sceneId, selfId)
	if GetGameOpenById(x300576_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300576_g_MissionId) == 0 then
		x300576_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0
	end
	local myMissionId = x300576_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300576_g_LevelLess then
		x300576_ShowTips(sceneId, selfId, "��ȼ�����")
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300576_ShowTips(sceneId, selfId, "���Ѿ������������������������")
		return 0;
	end

    local today = GetDayOfYear()
    if GetQuestData(sceneId, selfId, MD_LVZHUANG70_DATE[1], MD_LVZHUANG70_DATE[2],MD_LVZHUANG70_DATE[3] ) == today then
        x300576_ShowTips(sceneId, selfId, "�ܱ�Ǹ���������Ѿ����������񣬲����ٴ���ȡ")
        return 0;
    end

    if GetQuestData( sceneId, selfId, MD_RICHANG_DAY[ 1], MD_RICHANG_DAY[ 2], MD_RICHANG_DAY[ 3] ) == today then
        if GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[ 1], MD_RICHANG_COUNT[ 2], MD_RICHANG_COUNT[ 3] ) >= 3 then
            Msg2Player( sceneId, selfId, "�㲻������ȡ������ճ�������", 8, 3)
            return 0
        end
    else
        SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 0)
    end

	return 1;

end

function x300576_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	
	
	if GetGameOpenById(x300576_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300576_g_MissionId) == 0 then
		x300576_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	if x300576_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300576_GetMissionId( sceneId, selfId )

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300576_ShowTips(sceneId, selfId, "�����������޷���������")
		return 0
	end
	---------------------------- add end -------------------------------

	--���ǰ������
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,myMissionId  )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 0
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 0
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return 0
		end
	end

	local ret = AddQuest( sceneId, selfId, myMissionId, x300576_g_ScriptId, 0, 0, 0,0)-- ������������		
		
	if ret > 0 then
		
		
		local myMissionId = x300576_GetMissionId( sceneId, selfId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

		BeginAddItem(sceneId)
			AddItem( sceneId, x300576_g_TaskItemId, 1 )
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
			
			AddItemListToPlayer(sceneId,selfId)
			
			
		else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"�����ռ䲻�㣬����������������")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)

			DelQuestNM( sceneId, selfId, myMissionId )
			return 0;	
		end

		local str = "������������"..x300576_g_MissionName;
		x300576_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)
		

		local nNpcType = random(1,x300576_g_NpcCount)

		SetQuestByIndex( sceneId, selfId, misIndex, 6, nNpcType )
        SetQuestByIndex( sceneId, selfId, misIndex, 1, 0)

		
		GamePlayScriptLog(sceneId, selfId, 831)
		return 1
	else
		
		x300576_ShowTips(sceneId, selfId, "�����������")
	
	end


end



function x300576_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300576_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300576_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	local ret = DelQuestNM( sceneId, selfId, myMissionId )

	if ret>0 then

		local str = "������������"..x300576_g_MissionName;
	    x300576_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)


		local n = GetItemCount( sceneId, selfId, x300576_g_TaskItemId );

	
		if n > 0 then
			DelItem(sceneId, selfId,x300576_g_TaskItemId,n)
			
		end

		for i,item in x300576_g_GrowPointList do
			n = GetItemCount( sceneId, selfId, item.itemid );
			if n > 0 then
				DelItem(sceneId, selfId,item.itemid,n)
				
			end	

		end

        local today = GetDayOfYear()
		SetQuestData(sceneId, selfId, MD_LVZHUANG70_DATE[1], MD_LVZHUANG70_DATE[2], MD_LVZHUANG70_DATE[3], today)
		if today == GetQuestData( sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2], MD_RICHANG_DAY[3] ) then
            local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
            if count < 3 then
                SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 1 + count)
            end
        else
            SetQuestData( sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2], MD_RICHANG_DAY[3], today)
            SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 1)
        end
	else
		x300576_ShowTips(sceneId, selfId, "��������ʧ��")
	end

	
end



function x300576_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	if GetGameOpenById(x300576_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300576_g_MissionId) == 0 then
		x300576_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	local myMissionId = x300576_GetMissionId( sceneId, selfId )
	
	if x300576_CheckSubmit(sceneId, selfId )>0 then
		local today = GetDayOfYear()
        local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
        if today == GetQuestData(sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2],MD_RICHANG_DAY[3] ) and count >= 3 then
            Msg2Player( sceneId, selfId, "������ճ������Ѿ������ٽ��ˣ�����������", 8, 3)
            return 0
        end

		local nRet = x300576_GiveReward(sceneId,selfId,selectId)

		if nRet<=0 then
			return
		end
		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then
			CallScriptFunction( 270300, "OnSubmissionFinished", sceneId, selfId, x300576_g_MissionId)
			local n = GetItemCount( sceneId, selfId, x300576_g_TaskItemId );

	
			if n > 0 then
				DelItem(sceneId, selfId,x300576_g_TaskItemId,n)
				
			end

			for i,item in x300576_g_GrowPointList do
				n = GetItemCount( sceneId, selfId, item.itemid );
				if n > 0 then
					DelItem(sceneId, selfId,item.itemid,n)
					
				end	

			end

			local str = "�����������:"..x300576_g_MissionName;
			x300576_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

			GamePlayScriptLog(sceneId, selfId, 832)

            SetQuestData(sceneId, selfId, MD_LVZHUANG70_DATE[1], MD_LVZHUANG70_DATE[2], MD_LVZHUANG70_DATE[3], GetDayOfYear() )
			
		else
			x300576_ShowTips(sceneId, selfId, "������ʧ��")
		end
		
	end
end

function x300576_GiveReward(sceneId,selfId,selectRadioId)
	
	if GetGameOpenById(x300576_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300576_g_MissionId) == 0 then
		x300576_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	
    -- ������ѡ��Ľ����ǲ��ǿ��ж��ǰ󶨵�
	local level = GetLevel( sceneId, selfId)
    local canBind = 0
    local count = 0
    local id = 0
    for i, item in x300576_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                if selectRadioId == iter.id then
                    if j <= 2 then
                        canBind = 1
                    end
                    count = iter.cnt
                    id = iter.id
                    break
                end
            end
            break
        end
    end

    -- ����������������ѡ����Ʒ��������Խ���¸�������ʱ�Ĵ���
    if count == 0 then
        for i, item in x300576_g_RewardTable do
            for j, iter in item.items do
                if selectRadioId == iter.id then
                    if j <= 2 then
                        canBind = 1
                    end
                    count = iter.cnt
                    id = iter.id
                    break
                end
            end
        end
    end

    if id == 0 or count == 0 then
        return 0
    end

	BeginAddItem(sceneId)
    if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
        if canBind == 1 then
            AddItem( sceneId, id, count)
        else
            AddBindItem( sceneId, id, count)
        end
    else
		AddBindItem( sceneId, id, count)
    end
		
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		
		AddItemListToPlayer(sceneId,selfId)
		
		
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,format("���������Ʒ��@itemid_%d",id))
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        local myMissionId = x300576_GetMissionId( sceneId, selfId)
        local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId)
        local useCount = GetQuestParam( sceneId, selfId, misIndex, 1)
        if useCount <= 4 then
            BeginAddItem( sceneId)
            AddItem( sceneId, x300576_g_ItemId, 1)
            if EndAddItem( sceneId, selfId) == 1 then
                AddItemListToPlayer( sceneId, selfId)
                -- Msg2Player( sceneId, selfId, format( "��ֻ�鿴�����Ĵξ��ҵ��ˣ��ؽ���һ��@item_%d��", 
                    -- x300576_g_ItemId), 8, 2)
            else
                Msg2Player( sceneId, selfId, "��Ʒ���������޷���ö��⽱����Ʒ", 8, 3)
            end
        end

		return 1;
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�����ռ䲻�㣬�޷������������Ʒ��������ʧ��")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0;	
	end
	
end



function x300576_CheckSubmit(sceneId, selfId )
	
	if GetGameOpenById(x300576_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300576_g_MissionId) == 0 then
		x300576_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	local myMissionId = x300576_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nNpcIndex = GetQuestParam( sceneId, selfId, misIndex, 6 )

	local n = GetItemCount( sceneId, selfId, x300576_g_GrowPointList[nNpcIndex].itemid );

	if n<=0 then
		return 0;
	end
	
		
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
	

	if (bCompleted)<=0 then
		return 0
	end

	


	return 1;
end



---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x300576_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )

	
	
	BeginQuestEvent(sceneId)

		
	
	AddQuestText(sceneId,"#Y"..x300576_g_MissionName)
	AddQuestText(sceneId,"\t�Դ��Ҵ�Ԫˮ����������������ĳ��孵������뾡������ͼ�ƻ��Ҷ�����ƣ����գ����Ǹ���ɥ�Ĳ���������������ڰ����������޴�Ļ��׵����������ǵ���������������׵����Ǳ����������Դݻٰ�������ۣ�\n\t#Y@myname#W���������������Ļ��׵�����ͼ�����Ѿ���ȱ�ˣ�����Ӧ�û����ṩһЩ������")
	AddQuestText( sceneId,"#Y����Ŀ��:")
			
	AddQuestText( sceneId,x300576_g_MissionTarget)
	AddQuestText(sceneId," ")

	--1������
	local level = GetLevel(sceneId, selfId)
    for i, item in x300576_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	-- local nExpBonus = level*0;
	
	-- if nExpBonus > 0 then
		-- AddQuestExpBonus( sceneId, nExpBonus)
	-- end

	-- local ZhiYe= GetZhiye( sceneId, selfId)
	-- for i, item in x300576_g_BonusChoiceItem2[ZhiYe+1] do
		
		-- AddQuestRadioItemBonus(sceneId, item, 1)
		
	-- end

	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300576_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300576_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300576_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	
	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300576_g_MissionName)
		AddQuestText(sceneId,"����׵�һ��������������������룡")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300576_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300576_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local myMissionId = x300576_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	
	

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300576_g_MissionName)
		AddQuestText(sceneId,"\t#Y@myname#W��������һ�󹦣�����׵����Ǳ�ը�������ҵȶ������ӳ����졣\n\tΪ�˱������л�⣬��Щװ�������ѡһ����")
	
	
	
	--1������
	local level = GetLevel(sceneId, selfId)
    for i, item in x300576_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	-- local nExpBonus = level*0;
	
	-- if nExpBonus > 0 then
		-- AddQuestExpBonus( sceneId, nExpBonus)
	-- end

	-- local ZhiYe= GetZhiye( sceneId, selfId)
	-- for i, item in x300576_g_BonusChoiceItem2[ZhiYe+1] do
		
		-- AddQuestRadioItemBonus(sceneId, item, 1)
		
	-- end
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300576_g_ScriptId, MissionId);

end







---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300576_QuestLogRefresh( sceneId, selfId, MissionId)
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end
		
	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- ����
							x300576_GetMissionName(sceneId,selfId),        -- ��������
							x300576_GetMissionTask(sceneId,selfId),		--����Ŀ��
							x300576_GetReplyNpcId(sceneId,selfId),			--����NPC
							x300576_GetMissionMethod(sceneId,selfId),               --������
							x300576_GetMissionText(sceneId,selfId),	--��������
							x300576_GetMissionHelp(sceneId,selfId)					--����С��ʾ
							)

	--1������
	local level = GetLevel(sceneId, selfId)
    for i, item in x300576_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	-- local nExpBonus = level*0;
	
	-- if nExpBonus > 0 then
		-- AddQuestExpBonus( sceneId, nExpBonus)
	-- end

	-- local ZhiYe= GetZhiye( sceneId, selfId)
	-- for i, item in x300576_g_BonusChoiceItem2[ZhiYe+1] do
		
		-- AddQuestRadioItemBonus(sceneId, item, 1)
		
	-- end

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300576_GetMissionName(sceneId,selfId)
	

	return x300576_g_MissionName;
end

function x300576_GetMissionTask(sceneId,selfId)
	local myMissionId = x300576_GetMissionId( sceneId, selfId )

	

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nNpcIndex = GetQuestParam( sceneId, selfId, misIndex, 6 )

	local nValue = GetQuestParam( sceneId, selfId, misIndex, 0 )

	local str = "  ͨ��#G���׵�����ͼ#W�ҵ�#G"..x300576_g_GrowPointList[nNpcIndex].name..format("#W(%d/1)",nValue)

	
		
	return str;
end

function x300576_GetReplyNpcId(sceneId,selfId)
	local myMissionId = x300576_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nNpcIndex = GetQuestParam( sceneId, selfId, misIndex, 6 )

	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )


	--if bCompleted>0 then
		return "@npc_"..x300576_g_ReplyNpcId
	--else

		--return x300576_g_GrowPointList[nNpcIndex].name;
	--end
end

function x300576_GetMissionMethod(sceneId,selfId)
	return "\t������#G�Ҽ�#W���ʹ��#G���׵�����ͼ#W��������ʾ����ϸѰ�ҡ�"
end

function x300576_GetMissionText(sceneId,selfId)
	return "\t�Դ��Ҵ�Ԫˮ����������������ĳ��孵������뾡������ͼ�ƻ��Ҷ�����ƣ����գ����Ǹ���ɥ�Ĳ���������������ڰ����������޴�Ļ��׵����������ǵ���������������׵����Ǳ����������Դݻٰ���������ۣ�\n\t#Y@myname#W���������������Ļ��׵�����ͼ�����Ѿ���ȱ�ˣ�����Ӧ�û����ṩһЩ������"
end

function x300576_GetMissionHelp(sceneId,selfId)
	return "\t�Ҽ����ʹ�û��׵�����ͼ����õ���Ӧ����ʾ��"
end



function x300576_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300576_QuestLogRefresh( sceneId, selfId, MissionId );
end

--// system function start
function x300576_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	
	
	
end



function x300576_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end


function x300576_GetDirText(x,z,x1,z1)
	local strDir1 =""
	local strDir2 =""
	local strDir=""
	if x>x1 then
		strDir1 = "��"
	elseif x<x1 then
		strDir1 = "��"
	else
		if( z-z1<0) then
			strDir = "����"
		else
			strDir = "����"
		end

		return strDir
	end
	

	if z>z1 then
		strDir2 = "��"
	elseif z<z1 then
		strDir2 = "��"
	else
		if( x-x1<0) then
			strDir = "����"
		else
			strDir = "����"
		end

		return strDir
	end

	return strDir1..strDir2;


end

-----------------------------------------------------------------------------------------------
--����ʹ����Ʒ����
----------------------------------------------------------------------------------------------
function x300576_PositionUseItem( sceneId, selfId, BagIndex )
	

	local myMissionId = x300576_GetMissionId( sceneId, selfId )

	

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end


	
	

	if(sceneId~=15) then  --�������������
		x300576_ShowTips(sceneId, selfId, "��������ĳ�������Զ�ĵط�")
		return
	end


	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nNpcIndex = GetQuestParam( sceneId, selfId, misIndex, 6 )
    local useCount = GetQuestParam( sceneId, selfId, misIndex, 1)
    SetQuestByIndex( sceneId, selfId, misIndex, 1, useCount + 1)

	local x = x300576_g_GrowPointList[nNpcIndex].x;
	local z = x300576_g_GrowPointList[nNpcIndex].z;

	

	local x1,z1 = GetWorldPos( sceneId, selfId )

	local strDir = 	x300576_GetDirText(x,z,x1,z1)

	strDir = "����ϸ�о���һ��ͼֽ����"..strDir.."����,"
		
	
		
		

	local nDistance = (x1-x)*(x1-x) +(z1-z)*(z1-z)
	
	

	local str1 = "";
	if nDistance>80*80 then
		str1 = "��Զ�ĵط�"
	elseif nDistance>50*50 then
		str1 = "�����ﻹ��һЩ����"
	elseif nDistance>30*30 then
		str1 = "�����ﲻԶ��"
	elseif nDistance>10*10 then
		str1 = "�Ϳ쵽��"
	else
		str1 = "�������������ˣ���ϸ������Χ��û�п��ɵ���Ʒ��"
		x300576_ShowTips(sceneId, selfId, str1)
		return
	end

	x300576_ShowTips(sceneId, selfId, strDir..str1)
	
end



--// system end


--------------------------------------------------------------------------------------
-- ������ű�
--------------------------------------------------------------------------------------



function x300576_OnOpenItemBox(sceneId, selfId, targetId, growpointId, itemId)
	
	if GetGameOpenById(x300576_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300576_g_MissionId) == 0 then
        x300576_ShowTips(sceneId, selfId, "�˻���첻����")
		return 1
    end

	local myMissionId = x300576_GetMissionId( sceneId, selfId )

	

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then	-- ���û�������ֱ���˳�
		x300576_ShowTips(sceneId, selfId, "��û������:"..x300576_g_MissionName)
		return 1
	end

   
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId)
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7)

	if bCompleted==1 then
		x300576_ShowTips(sceneId, selfId, "�����������:"..x300576_g_MissionName)
		return 1;
	end

	return 0;
	
end

function x300576_OnRecycle(sceneId, selfId, targetId, growpointId, itemId)
	
	if GetGameOpenById(x300576_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300576_g_MissionId) == 0 then
        x300576_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0
    end

	local myMissionId = x300576_GetMissionId( sceneId, selfId )

	

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then	-- ���û�������ֱ���˳�
		x300576_ShowTips(sceneId, selfId, "��û������:"..x300576_g_MissionName)
		return 0
	end

   
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId)
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7)

	if bCompleted==1 then
		x300576_ShowTips(sceneId, selfId, "�����������:"..x300576_g_MissionName)
		return 0;
	end


	local nNpcIndex = GetQuestParam( sceneId, selfId, misIndex, 6 )


	if x300576_g_GrowPointList[nNpcIndex].gpid ~= growpointId then
		x300576_ShowTips(sceneId, selfId, "һ���о�֮���㷢���Ⲣ������Ҫ�ҵĻ��׵���")
		return 0;
	end

	

	BeginAddItem(sceneId)
		AddItem( sceneId, x300576_g_GrowPointList[nNpcIndex].itemid, 1 )
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		
		AddItemListToPlayer(sceneId,selfId)
		x300576_ShowTips(sceneId, selfId, "��ɹ����ҵ��˻��׵���")
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 1 )

		x300576_QuestLogRefresh( sceneId, selfId, myMissionId );
		
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��Ʒ���������޷��õ�������Ʒ��")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

		
	end

	return 1;
	--return CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x300576_g_GrowpointId, x300576_g_ItemIndex )
end



function x300576_OnProcOver(sceneId, selfId, targetId)
	-- �ɼ����
	
	

	return 1;
end








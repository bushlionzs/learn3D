--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x300572_g_MissionId 				= 	9325                     --����ID
x300572_g_ScriptId 					= 	300572                  --�ű�ID
x300572_g_MissionKind 				= 	1                       --��������
x300572_g_LevelLess					= 	40                      --�������ŵȼ�  <=0 ��ʾ������


x300572_g_MissionName				= 	"�����ˡ�������̽"
x300572_g_MissionName1				= 	"���......����Ǭ����"
x300572_g_MissionTarget				= 	"  �ҵ�αװ��#G��������������#W�Ĵ�����̽����ͨ������¥һ���߶�"
x300572_g_MissionInfo				= 	""
x300572_g_ContinueInfo				= 	""
x300572_g_MissionCompleted			= 	""
x300572_g_MissionHelp				=	"������ͨ��������¥һ�����ߡ�"          --������ʾ��Ϣ

--Ŀ��
x300572_g_ExtTarget					=	{ {type=20,n=1,target="������̽"}}

--����

x300572_g_ExpBonus					= 	0;--x300572_AddExpAward               	--����������
x300572_g_BonusItem					=	{}	--��������Ʒ

x300572_g_BonusMoney1               = 	0
x300572_g_BonusMoney2               =   0
x300572_g_BonusMoney3               =   0

x300572_g_BonusChoiceItem           =   {}


--MisDescEnd


x300572_g_HourCountLimited			=	1

x300572_g_EnterTime					=	{                       --���������ʱ��
											{min=0*60+0,  max=23*60+59},
										}

x300572_g_SubNpcId = 139137
x300572_g_ReplyNpcId = 139134

x300572_g_GameId	= 1010
x300572_g_BuffId	= 7715


x300572_g_nTypeCount = 4

x300572_g_TypeList = {
						{name="@npc_141022",id=1178, tipname = "��孴̿�" },
						{name="@npc_141023",id=1179, tipname = "����ϸ��" },
						{name="@npc_141024",id=1180, tipname = "צ�ۼ�ϸ" },
						{name="@npc_141025",id=1181, tipname = "������̽" }
					 }	


x300572_g_BonusChoiceItem2   = {
								{10019000,10077000,10238000,10208000,10268000,10248000,10258000,10278000},
								{10028000,10087000,10238010,10208010,10268010,10248010,10258010,10278010},
								{10038000,10097000,10238020,10208020,10268020,10248020,10258020,10278020},
								{10048000,10107000,10238030,10208030,10268030,10248030,10258030,10278030},
								{10058000,10117000,10238040,10208040,10268040,10248040,10258040,10278040},
								{10068000,10127000,10238050,10208050,10268050,10248050,10258050,10278050}
									
								}


-- ��������Ʒ�б�
x300572_g_RewardTable       = {
                                { minLevel = 40, maxLevel = 60,  items = { { id = 11000201, cnt = 8 }, { id = 11050002, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 60, maxLevel = 80,  items = { { id = 11000202, cnt = 8 }, { id = 11050003, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 80, maxLevel = 999, items = { { id = 11000203, cnt = 8 }, { id = 11050004, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
}



function x300572_GetMissionId( sceneId, selfId )
	return x300572_g_MissionId
end

function x300572_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local level = GetLevel( sceneId,selfId )
    if level < x300572_g_LevelLess then
       return
    end

	local myMissionId = x300572_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300572_g_MissionName,8,1);
	else
		local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		
		AddQuestNumText(sceneId, myMissionId, x300572_g_MissionName,state,state);

	end


	
end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300572_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	
	if GetGameOpenById(x300572_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300572_g_MissionId) == 0 then
		x300572_ShowTips(sceneId, selfId, "�˻���첻���ţ������뵽�󶼰�������ѯÿ��������")
		return
	end

	local myMissionId = x300572_GetMissionId( sceneId, selfId )	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId )>0 then
		if nExt==30 then
			x300572_GiveSubMission(sceneId, selfId, targetId, MissionId,2)
			return
		end
	end

	
	
	
		
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		x300572_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
	else
		if nExt==7 then -- �������
			x300572_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
			
			
		else
			
			x300572_DispatchContinueInfo( sceneId, selfId, targetId,myMissionId )
		end
	end
	
end


function x300572_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x300572_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300572_g_MissionId) == 0 then
		
		return 0;
	end
	return 1;

end

function x300572_CheckRequest(sceneId, selfId)
	if GetGameOpenById(x300572_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300572_g_MissionId) == 0 then
		x300572_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0
	end
	local myMissionId = x300572_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300572_g_LevelLess then
		x300572_ShowTips(sceneId, selfId, "�ȼ�����")
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300572_ShowTips(sceneId, selfId, "���Ѿ������������������������")
		return 0;
	end

	if  x300572_CheckCommonCondition_Time(sceneId, selfId)<=0 then
		return 0;
	end

    local today = GetDayOfYear()
    if GetQuestData(sceneId, selfId, MD_LVZHUANG40_DATE[1], MD_LVZHUANG40_DATE[2],MD_LVZHUANG40_DATE[3] ) == today then
        x300572_ShowTips(sceneId, selfId, "�ܱ�Ǹ���������Ѿ����������񣬲����ٴ���ȡ")
        return 0
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

function x300572_CheckCommonCondition_Time(sceneId, selfId)
	local hour,minute,sec =GetHourMinSec();
	local nowtime = hour*60+minute
	
	for i, item in x300572_g_EnterTime do
		if nowtime >= item.min and nowtime <= item.max then
			
			
			return 1;
			
		end
	end
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "����14��00-21��59��������");
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	return 0;
end

function x300572_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	
	
	if GetGameOpenById(x300572_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300572_g_MissionId) == 0 then
		x300572_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	if x300572_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300572_GetMissionId( sceneId, selfId )

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300572_ShowTips(sceneId, selfId, "�����������޷���������")
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

	local ret = AddQuest( sceneId, selfId, myMissionId, x300572_g_ScriptId, 1, 0, 0,1)-- ������������		
		
	if ret > 0 then
		local str = "������������"..x300572_g_MissionName;
		x300572_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)
		
		local myMissionId = x300572_GetMissionId( sceneId, selfId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 5, 0 )

        SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300572_g_BuffId, 0)
		GamePlayScriptLog(sceneId, selfId, 801)
		
		return 1
	else
		
		x300572_ShowTips(sceneId, selfId, "�����������")
	
	end


end

function x300572_GiveSubMission(sceneId, selfId, targetId, MissionId, nExt)
	
	if GetGameOpenById(x300572_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300572_g_MissionId) == 0 then
		x300572_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end
	local myMissionId = x300572_GetMissionId( sceneId, selfId )

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 5, 1 )  --��û�д���
	SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )

	local killType = random(1, x300572_g_nTypeCount)
	SetQuestByIndex( sceneId, selfId, misIndex, 1, killType )
	SetQuestByIndex( sceneId, selfId, misIndex, 2, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 3, 0 )

    if IsHaveSpecificImpact( sceneId, selfId, x300572_g_BuffId) == 1 then
        CancelSpecificImpact( sceneId, selfId, x300572_g_BuffId)
        SetQuestByIndex( sceneId, selfId, misIndex, 4, 1)
    else
        SetQuestByIndex( sceneId, selfId, misIndex, 4, 3)
    end

	x300572_ShowSubMission( sceneId, selfId, targetId,MissionId, nExt )

	x300572_QuestLogRefresh( sceneId, selfId, myMissionId );
end

function x300572_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300572_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300572_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	local ret = DelQuestNM( sceneId, selfId, myMissionId )

	if ret>0 then

		local str = "������������:"..x300572_g_MissionName;
	    x300572_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

        local today = GetDayOfYear()
		SetQuestData( sceneId, selfId, MD_LVZHUANG40_DATE[1], MD_LVZHUANG40_DATE[2], MD_LVZHUANG40_DATE[3], today)
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
		x300572_ShowTips(sceneId, selfId, "��������ʧ��")
	end

	
end



function x300572_ProcQuestSubmit( sceneId, selfId, targetId, selectRadioId, MissionId )
	
	if GetGameOpenById(x300572_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300572_g_MissionId) == 0 then
		x300572_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end
	
	if IsHaveQuestNM( sceneId, selfId, x300572_g_MissionId ) <= 0 then
		return
	end

	local myMissionId = x300572_GetMissionId( sceneId, selfId )
	
	if x300572_CheckSubmit(sceneId, selfId )>0 then
		local today = GetDayOfYear()
        local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
        if today == GetQuestData(sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2],MD_RICHANG_DAY[3] ) and count >= 3 then
            Msg2Player( sceneId, selfId, "������ճ������Ѿ������ٽ��ˣ�����������", 8, 3)
            return 0
        end

		local nRet = x300572_GiveReward(sceneId,selfId,selectRadioId)

		if nRet<=0 then
			return
		end
		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then
            CallScriptFunction( 270300, "OnSubmissionFinished", sceneId, selfId, x300572_g_MissionId)

			local str = "�����������:"..x300572_g_MissionName;
			x300572_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

			SetQuestData(sceneId, selfId, MD_LVZHUANG40_DATE[1], MD_LVZHUANG40_DATE[2], MD_LVZHUANG40_DATE[3], GetDayOfYear() )

			GamePlayScriptLog(sceneId, selfId, 802)
			
		else
			x300572_ShowTips(sceneId, selfId, "������ʧ��")
		end
		
	end
end

function x300572_GiveReward(sceneId,selfId,selectRadioId)
	
	if GetGameOpenById(x300572_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300572_g_MissionId) == 0 then
		x300572_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	
	

    -- ������ѡ��Ľ����ǲ��ǿ��ж��ǰ󶨵�
	local level = GetLevel( sceneId, selfId)
    local canBind = 0
    local count = 0
    local id = 0
    for i, item in x300572_g_RewardTable do
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
        for i, item in x300572_g_RewardTable do
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

		return 1;
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�����ռ䲻�㣬�޷������������Ʒ��������ʧ��")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0;	
	end
	
	
	
end



function x300572_CheckSubmit(sceneId, selfId )
	
	if GetGameOpenById(x300572_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300572_g_MissionId) == 0 then
		x300572_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	local myMissionId = x300572_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
	

	if (bCompleted)<=0 then
		return 0
	end

	return 1;
end



---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x300572_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )

	
	
	BeginQuestEvent(sceneId)

		
	
	AddQuestText(sceneId,"#Y"..x300572_g_MissionName)
	AddQuestText(sceneId,"\t���ţ����յ���Ϣ��������֮���ɳ��˲�����������Ǳ��󶼡��䲻֪�����Ǻ���ͼ��������ͷ¶β����Ȼû��ʲô���¡�\n\t�����ȥ�ҵ������µ���ϯ��̽������װ����һ�������������ڴ���¥һ���߶���\n\t��ס���������п��ǣ�#G����Ǭ��#W��")
	AddQuestText( sceneId,"#Y����Ŀ��:")
			
	AddQuestText( sceneId,x300572_g_MissionTarget)
	AddQuestText(sceneId," ")

	--1������
	local level = GetLevel(sceneId, selfId)
    for i, item in x300572_g_RewardTable do
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
	-- for i, item in x300572_g_BonusChoiceItem2[ZhiYe+1] do
		
		-- AddQuestRadioItemBonus(sceneId, item, 1)
		
	-- end

	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300572_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300572_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300572_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	
	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300572_g_MissionName)
		AddQuestText(sceneId,"\t��ô�����㻹û�ҵ���̽�������Ӧ�û�װ����һ������������������¥һ���߶���")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300572_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300572_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local myMissionId = x300572_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	
	

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300572_g_MissionName)
		AddQuestText(sceneId,"\t�ã��������С��Ҳ���������Ҵ�Ԫ������Σ����ǿ�Ц֮����\n\t#Y@myname#W����˴ι��Ͳ�С����Щװ������������ѡһ����")
	
	
	
	--1������
	local level = GetLevel(sceneId, selfId)
    for i, item in x300572_g_RewardTable do
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
	-- for i, item in x300572_g_BonusChoiceItem2[ZhiYe+1] do
		
		-- AddQuestRadioItemBonus(sceneId, item, 1)
		
	-- end
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300572_g_ScriptId, MissionId);

end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�����Ŀ
---------------------------------------------------------------------------------------------------
function x300572_ShowSubMission( sceneId, selfId, NPCId,MissionId, nExt )


	
	local myMissionId = x300572_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )


	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300572_g_MissionName)
		AddQuestText(sceneId,format("\t��......������ģ�\n\t��Ȼ����˵���пڣ���Ȼ�Ǵ�³�������������ġ�\n\t���Ѿ���̽��������һ��"..x300572_g_TypeList[value2].name.."�ڴ󶼳���ۼ���ͼı���죬����ȥ����������Ȼ��֪������"))
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300572_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300572_QuestLogRefresh( sceneId, selfId, MissionId)
	
	
		
	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- ����
							x300572_GetMissionName(sceneId,selfId),        -- ��������
							x300572_GetMissionTask(sceneId,selfId),		--����Ŀ��
							"@npc_"..x300572_GetReplyNpcId(sceneId,selfId),			--����NPC
							x300572_GetMissionMethod(sceneId,selfId),               --������
							x300572_GetMissionText(sceneId,selfId),	--��������
							x300572_GetMissionHelp(sceneId,selfId)					--����С��ʾ
							)

	--1������
	local level = GetLevel(sceneId, selfId)
    for i, item in x300572_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300572_GetMissionName(sceneId,selfId)
	

	return x300572_g_MissionName;
end

function x300572_GetMissionTask(sceneId,selfId)
	local myMissionId = x300572_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	if nStep==0 then
		
		return "  �ҵ�αװ��#G��������������#W�Ĵ�����̽����ͨ������¥һ���߶�"
	end
	

	
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )

	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )

    local killCount = GetQuestParam( sceneId, selfId, misIndex, 4)


	local strTable ="  ";
	local str1 = strTable.."����#G"..x300572_g_TypeList[value2].name.."#W"..format("(%d/%d)",value1,killCount)
	--local str2 = "\n"..strTable.."�ҵ�#G��С����#W"..format("(%d/1)",value2)

	if value1>=killCount then
		str1 = "#G"..str1
	else
		str1 = "#W"..str1
	end

	return str1
end

function x300572_GetReplyNpcId(sceneId,selfId)
	return x300572_g_ReplyNpcId;
end

function x300572_GetMissionMethod(sceneId,selfId)

	local myMissionId = x300572_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	if nStep==0 then
		
		return "�ҵ�αװ��#G��������������#W�Ĵ�����̽����ͨ������¥һ���߶���"
	end

	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )

	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )

	local killCount = GetQuestParam( sceneId, selfId, misIndex, 4)

	local strTable = "";
	local str1 = strTable.."����#G"..x300572_g_TypeList[value2].name.."#W"..format("(%d/%d)",value1,killCount)
	--local str2 = "\n"..strTable.."�ҵ�#G��С����#W"..format("(%d/1)",value2)

	if value1>=killCount then
		str1 = "#G"..str1
	else
		str1 = "#W"..str1
	end

	return str1

	
end

function x300572_GetMissionText(sceneId,selfId)
	return "\t���ţ����յ���Ϣ��������֮���ɳ��˲�����������Ǳ��󶼡��䲻֪�����Ǻ���ͼ��������ͷ¶β����Ȼû��ʲô���¡�\n\t�����ȥ�ҵ������µ���ϯ��̽������װ����һ�������������ڴ���¥һ���߶���\n\t��ס���������п��ǣ�#G����Ǭ��#W��"
end

function x300572_GetMissionHelp(sceneId,selfId)
	return "\t������ͨ��������¥һ����̽��Ϣ��"
end



function x300572_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300572_QuestLogRefresh( sceneId, selfId, MissionId );
end

--// system function start
function x300572_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	
	local myMissionId = x300572_GetMissionId( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		return
	end


	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	
	
	
	
	
	local bFind =0;
	local iIndex=0
	
	if npcGuid==x300572_g_SubNpcId then
		bFind=1;
		
	end

	

	if bFind==0 then
		return
	end

	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	if nStep~=0 then
		return
	end



	
	


	AddQuestNumText(sceneId, x300572_g_MissionId, x300572_g_MissionName1,2,30);
	
	
	

	
end



function x300572_CheckSceneOnKill(sceneId, selfId)
	if sceneId==36 or sceneId==37 or sceneId==38 then
		return 1
	else
		return 0
	end
end

function x300572_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

	local HumenNum = GetMonsterOwnerCount( sceneId, objId ) --ȡ�������������ӵ�з���Ȩ������
	for i = 0, HumenNum-1 do
		local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --ȡ��ӵ�з���Ȩ���˵�objId
		if humanObjId ~= -1 then
		local myMissionId = x300572_GetMissionId( sceneId, humanObjId )
			if IsHaveQuestNM( sceneId, humanObjId, myMissionId ) > 0 then	--��������ӵ������
				x300572_OnValidKillObject( sceneId, humanObjId, objdataId, objId, MissionId )
			end
		end
	end
	
end

function x300572_OnValidKillObject( sceneId, selfId, objdataId, objId, MissionId )

	if x300572_CheckSceneOnKill(sceneId, selfId)<=0 then
		return 0;
	end

	local myMissionId = x300572_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	if nStep~=1 then
		return
	end

	

	
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )

	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )

    local killCount = GetQuestParam( sceneId, selfId, misIndex, 4)

	if value1>=killCount then
		return
	end

	

	if x300572_g_TypeList[value2].id~=objdataId then
		return
	end

	

	SetQuestByIndex( sceneId, selfId, misIndex, 0, value1+1 )

	if (value1+1)==killCount then
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
	end

	x300572_ShowTips(sceneId, selfId, format("����"..x300572_g_TypeList[value2].tipname.."(%d/%d)",value1+1,killCount ))

	x300572_QuestLogRefresh( sceneId, selfId, myMissionId );
	
end




--// system end





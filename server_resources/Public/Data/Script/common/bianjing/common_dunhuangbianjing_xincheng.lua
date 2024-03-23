--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x300580_g_MissionId 				= 	9500                     --����ID
x300580_g_ScriptId 					= 	300580                  --�ű�ID
x300580_g_MissionKind 				= 	1                       --��������
x300580_g_LevelLess					= 	40                      --�������ŵȼ�  <=0 ��ʾ������


x300580_g_MissionName				= 	"�����ˡ��ĳ�����"
x300580_g_MissionName1				= 	"�����˵��������Ů��"
x300580_g_MissionTarget				= 	"\tǰ��#G����ˮ��#W�����ܿ���"
x300580_g_MissionInfo				= 	""
x300580_g_ContinueInfo				= 	""
x300580_g_MissionCompleted			= 	""
x300580_g_MissionHelp				=	""          --������ʾ��Ϣ

--Ŀ��
x300580_g_ExtTarget					=	{ {type=20,n=1,target="�����ˡ��ĳ�����"}}

--����

x300580_g_ExpBonus					= 	0;--x300580_AddExpAward               	--����������
x300580_g_BonusChoiceItem			={{item=11000203,n=6},{item=11000203,n=7},{item=11000203,n=8}}	--��������Ʒ

x300580_g_BonusMoney1               = 	0
x300580_g_BonusMoney2               =   0
x300580_g_BonusMoney3               =   0




--MisDescEnd

x300580_G_GAMESTEP					=	6
x300580_G_QUESTIONID				=	5
x300580_G_ACTIONFLAG				=	4
x300580_G_FRAME						=	3
x300580_G_ANWER_STEP				=	2

x300580_Min_Step					=	6
x300580_Max_Step					=	8

x300580_Round_wait					=	5 --��һ�ֵȴ�
x300580_g_Answer_Wait				=	1 --���Դ���ȴ�

x300580_g_BuffId					=	7903
x300580_g_ItemId                    =   12030028

x300580_g_DayCountLimited			=	1

x300580_g_QuestCountList ={4,8,8,8,8,8,8,8}  --ÿһ������ĸ���
x300580_g_QuestList ={
						{ --��1��
							{0},
							{1},
							{2},
							{3},
						},

						{ --��2��
							{0,1},
							{1,2},
							{2,3},
							{3,2},
							{3,3},
							{2,2},
							{1,3},
							{0,3},
						},

						{ --��3��
							{0,1,2},
							{0,1,3},
							{2,1,2},
							{3,1,2},
							{3,3,2},
							{1,1,2},
							{3,2,2},
							{1,1,3},
						},

						{ --��4��
							{0,1,2,3},
							{3,1,3,3},
							{2,1,2,3},
							{0,1,3,2},
							{1,2,1,3},
							{3,3,2,1},
							{1,3,1,3},
							{2,1,2,0},
						},

						{ --��5��
							{0,1,2,3,0},
							{2,1,2,2,0},
							{3,3,2,1,0},
							{1,1,2,1,3},
							{3,1,2,3,0},
							{0,2,2,1,3},
							{1,2,2,3,0},
							{0,3,2,1,2},
						},

						{ --��6��
							{0,1,3,2,0,1},
							{2,1,2,1,1,3},
							{3,1,3,2,2,1},
							{0,3,1,2,3,1},
							{1,2,3,2,0,1},
							{1,3,2,3,3,1},
							{2,3,2,3,0,1},
							{3,1,0,3,0,1},
						},

						{ --��7��
							{1,3,2,0,0,1,2},
							{1,2,3,3,2,0,1},
							{2,1,2,0,3,1,2},
							{3,1,2,1,0,3,2},
							{2,1,0,3,2,1,2},
							{3,2,2,1,0,3,2},
							{1,1,2,3,1,0,2},
							{0,1,3,1,2,2,3},
						},

						{ --��8��
							{0,1,2,3,0,1,2,3},
							{0,1,3,3,0,1,1,3},
							{1,1,2,2,0,2,3,1},
							{3,1,3,3,0,3,2,1},
							{2,1,2,0,1,3,2,2},
							{1,1,2,3,1,0,2,2},
							{2,3,2,1,0,1,1,3},
							{1,1,2,3,0,2,3,2},
						},
					 }







x300580_g_GameId	= 1025

x300580_g_PlayNpcId  = 110102
x300580_g_ReplyNpcId = 110102

-- ��������Ʒ�б�
x300580_g_RewardTable       = {
                                { minLevel = 40, maxLevel = 60,  items = { { id = 11000201, cnt = 8 }, { id = 11050002, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 60, maxLevel = 80,  items = { { id = 11000202, cnt = 8 }, { id = 11050003, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 80, maxLevel = 999, items = { { id = 11000203, cnt = 8 }, { id = 11050004, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
}

function x300580_GetMissionId( sceneId, selfId )
	return x300580_g_MissionId
end

function x300580_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	local level = GetLevel( sceneId,selfId )
    if level < x300580_g_LevelLess then
       return
    end

	local myMissionId = x300580_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300580_g_MissionName,8,1);
	else
		--local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		
		--AddQuestNumText(sceneId, myMissionId, x300580_g_MissionName,state,state);

	end


	
end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300580_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	
	if nExt==nil then
		return
	end

	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		x300580_ShowTips(sceneId, selfId, "�˻���첻���ţ������뵽�󶼰�������ѯÿ��������")
		return
	end

	local myMissionId = x300580_GetMissionId( sceneId, selfId )	
	
	
	
	
		
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		x300580_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
	else
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	
		local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
		local nCurrentStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_GAMESTEP )

		if nExt==7 then
			x300580_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
		elseif nExt==10 then
			x300580_DispatchStartGame( sceneId, selfId, targetId,myMissionId )

			x300580_StartPlayGame(sceneId, selfId, 0)
		elseif nExt==11 then
			x300580_DispatchStartGame( sceneId, selfId, targetId,myMissionId )

			x300580_StartPlayGame(sceneId, selfId, 1)
		elseif nExt>=20 then
			x300580_DispatchDifficultLevel( sceneId, selfId, targetId,myMissionId, nExt-20 )

			SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
			x300580_OnStartDifficultLevel(sceneId, selfId)
			--x300580_OnPlayNextRound(sceneId, selfId)
		end
		
	end
end

--// system function start
function x300580_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	
	if npcGuid ~= x300580_g_PlayNpcId and npcGuid ~= x300580_g_ReplyNpcId then
		return
	end

	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		return 0;
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
	local nCurrentStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_GAMESTEP )
	local nActionFlag = GetQuestParam( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG )

	if npcGuid == x300580_g_PlayNpcId then
		--if bCompleted<=0 then
			if nCurrentStep==0 then
				if nActionFlag==0 then
				AddQuestNumText(sceneId, myMissionId, "�������ܿ���",2,10);
				end
			elseif nCurrentStep>=x300580_Min_Step  and nCurrentStep<=x300580_Max_Step then
				local nActionFlag = GetQuestParam( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG )

				if nActionFlag==4 then
					AddQuestNumText(sceneId, myMissionId, format("��ʼ��%d�ֿ���",nCurrentStep+1),2,(20+nCurrentStep+1-x300580_Min_Step));
				end
			
			end
			
			if nCurrentStep>0 then	
				if IsHaveSpecificImpact(sceneId, selfId, x300580_g_BuffId)<=0 then
					if bCompleted<=0 then
						AddQuestNumText(sceneId, myMissionId, "������ս",2,11);
					end
					
				end
			else
				if IsHaveSpecificImpact(sceneId, selfId, x300580_g_BuffId)<=0 then
					if nActionFlag>0 then
						
						if bCompleted<=0 then
							AddQuestNumText(sceneId, myMissionId, "������ս",2,11);
						end
						
					end
				end
			end
		--end
	end
	
	if npcGuid == x300580_g_ReplyNpcId then
		if bCompleted>0 then
			local state = GetQuestStateNM(sceneId, selfId, npcId, myMissionId);
			AddQuestNumText(sceneId, myMissionId, x300580_g_MissionName,state,state);
		end
	end

	
	
end

function x300580_StartPlayGame(sceneId, selfId, nMode)

	if nMode==nil then
		return
	end

	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		return
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nCurrentStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_GAMESTEP )

	if nMode ==0 then

		if IsHaveSpecificImpact(sceneId, selfId, x300580_g_BuffId)<=0 then
			SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId, x300580_g_BuffId,0 )  --����Ҽ�buff��ʱ
		
		end
		
		x300580_OnOneRoundCompleted(sceneId, selfId)
		
		--SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_GAMESTEP, 1 )

		
		--x300580_StartChuTi(sceneId, selfId, 1)
	elseif nMode==1 then
		x300580_ShowTips(sceneId, selfId, format("%d���ʼ��һ��",x300580_Round_wait))
		x300580_Restart(sceneId, selfId) --���¿�ʼ����
	
	end

	

	
	
end



function x300580_StartChuTi(sceneId, selfId, nStep)

	if nStep<=0 or nStep>8 then
		return
	end

	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		return
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	
	local nCount = x300580_g_QuestCountList[nStep]
	
	local nQuestionId = random(1,nCount)

	

	
	
	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_QUESTIONID, nQuestionId )	--����id
	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG, 1 )	--����Flag

	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_FRAME, 0 )

	if IsHaveSpecificImpact(sceneId, selfId, x300580_g_BuffId)<=0 then
		SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId, x300580_g_BuffId,0 )  --����Ҽ�buff��ʱ
		
	end
end


function x300580_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		return
	end
	return 1;

end

function x300580_CheckRequest(sceneId, selfId)
	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		x300580_ShowTips(sceneId, selfId, "�˻���첻����")
		return
	end
	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300580_g_LevelLess then
		x300580_ShowTips(sceneId, selfId, "��ȼ�����")
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300580_ShowTips(sceneId, selfId, "���Ѿ������������������������")
		return 0;
	end

    if GetQuestData(sceneId, selfId, MD_XCZL_DATE[1], MD_XCZL_DATE[2],MD_XCZL_DATE[3] ) == GetDayOfYear() then
        x300580_ShowTips(sceneId, selfId, "�ܱ�Ǹ���������Ѿ����������񣬲����ٴ���ȡ")
        return 0;
    end

    if GetQuestData( sceneId, selfId, MD_RICHANG_DAY[ 1], MD_RICHANG_DAY[ 2], MD_RICHANG_DAY[ 3] ) == GetDayOfYear() then
        if GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[ 1], MD_RICHANG_COUNT[ 2], MD_RICHANG_COUNT[ 3] ) >= 3 then
            Msg2Player( sceneId, selfId, "�㲻������ȡ������ճ�������", 8, 3)
            return 0
        end
    else
        SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 0)
    end

	return 1;

end

function x300580_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	
	
	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		x300580_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0
	end

	if x300580_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300580_ShowTips(sceneId, selfId, "�����������޷���������")
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

	local ret = AddQuest( sceneId, selfId, myMissionId, x300580_g_ScriptId, 0, 0, 0,1)-- ������������		
		
	if ret > 0 then
		
		
		local myMissionId = x300580_GetMissionId( sceneId, selfId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

		

		local str = "������������"..x300580_g_MissionName;
		x300580_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)
		

	
		
		SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_GAMESTEP, 0 )

		
		GamePlayScriptLog(sceneId, selfId, 1551)
		return 1
	else
		
		x300580_ShowTips(sceneId, selfId, "�����������")
	
	end


end



function x300580_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300580_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300580_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	local ret = DelQuestNM( sceneId, selfId, myMissionId )

	if ret>0 then
		CancelSpecificImpact( sceneId, selfId, x300580_g_BuffId)

		local str = "������������:"..x300580_g_MissionName;
	    x300580_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

        local today = GetDayOfYear()
		SetQuestData( sceneId, selfId, MD_XCZL_DATE[1], MD_XCZL_DATE[2], MD_XCZL_DATE[3], today)
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
		x300580_ShowTips(sceneId, selfId, "��������ʧ��")
	end

	
end



function x300580_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		x300580_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0
	end

	

	local myMissionId = x300580_GetMissionId( sceneId, selfId )
	
	if x300580_CheckSubmit(sceneId, selfId )>0 then
		local today = GetDayOfYear()
        local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
        if today == GetQuestData(sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2],MD_RICHANG_DAY[3] ) and count >= 3 then
            Msg2Player( sceneId, selfId, "������ճ������Ѿ������ٽ��ˣ�����������", 8, 3)
            return 0
        end

		local nRet = x300580_GiveReward(sceneId,selfId,selectId)

		if nRet<=0 then
			return
		end
		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then
			CallScriptFunction( 270300, "OnSubmissionFinished", sceneId, selfId, x300580_g_MissionId)
			
			local str = "�����������:"..x300580_g_MissionName;
			x300580_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

			GamePlayScriptLog(sceneId, selfId, 1552)
            SetQuestData( sceneId, selfId, MD_XCZL_DATE[1], MD_XCZL_DATE[2], MD_XCZL_DATE[3], GetDayOfYear() )

			CancelSpecificImpact( sceneId, selfId, x300580_g_BuffId)
			
		else
			x300580_ShowTips(sceneId, selfId, "������ʧ��")
		end
		
	end
end

function x300580_GiveReward( sceneId, selfId, selectRadioId)
	
	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		x300580_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0
	end

	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		return 0;
	end
	
    -- ������ѡ��Ľ����ǲ��ǿ��ж��ǰ󶨵�
	local level = GetLevel( sceneId, selfId)
    local canBind = 0
    local count = 0
    local id = 0
    for i, item in x300580_g_RewardTable do
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
        for i, item in x300580_g_RewardTable do
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
	local ret1 = EndAddItem(sceneId,selfId)

	if ret1 > 0 then
		
		AddItemListToPlayer(sceneId,selfId)
		
		
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,format("���������Ʒ��@itemid_%d",id))
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId)
        local circle = GetQuestParam( sceneId, selfId, misIndex, x300580_G_ANWER_STEP)
        local giveReward = 0
        if circle == 7 then
            if random( 1, 100) <= 20 then
                giveReward = 1
            end
        elseif circle == 8 then
            giveReward = 1
        end
        if giveReward == 1 then
            BeginAddItem( sceneId)
            AddItem( sceneId, x300580_g_ItemId, 1)
            local ret = EndAddItem( sceneId, selfId)
            if ret == 1 then
                AddItemListToPlayer( sceneId, selfId)
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



function x300580_CheckSubmit(sceneId, selfId )
	
	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		x300580_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0
	end

	local myMissionId = x300580_GetMissionId( sceneId, selfId )
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
function x300580_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )

	
	
	BeginQuestEvent(sceneId)

		
	
	AddQuestText(sceneId,"#Y"..x300580_g_MissionName)
	AddQuestText(sceneId,"\t����������һ�����ϴ�˵����������֮ʱ�������޴����ѣ�Ψ���ƽ�ˮ��֮�գ����ܻ�����һ���ƽ١�\n\t����⼸���º�������Ű���Ѿ�Ӱ��˵ذ��յ�����ҷ����ӵ����䡣ͬʱ���������Ĺ���ˮ���ڳ�����������ٴβ�ʱ������ɫ��â��\n\t#Y@myname#W�����Ƿ�Ը��ǰȥһ̽ˮ���İ��أ�")
	AddQuestText( sceneId,"#Y")
	AddQuestText( sceneId,"#Y����Ŀ�꣺")	
	AddQuestText( sceneId,x300580_g_MissionTarget)
	AddQuestText(sceneId," ")

	--1������
	local level = GetLevel(sceneId, selfId)
    for i, item in x300580_g_RewardTable do
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
	-- --2.��Ʒ
	
	-- for i, item in x300580_g_BonusChoiceItem do
	    -- AddQuestRadioItemBonus(sceneId, item.item, item.n)
	-- end

	
	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300580_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--���NpC��ʼ��Ϸ
---------------------------------------------------------------------------------------------------
function x300580_DispatchStartGame( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300580_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	
	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300580_g_MissionName)
		AddQuestText(sceneId,"\t��ע�⣬�����Ѿ���ʼ")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300580_g_ScriptId, MissionId,0);
	


end

---------------------------------------------------------------------------------------------------
--���NpC��ս���Ѷ�
---------------------------------------------------------------------------------------------------
function x300580_DispatchDifficultLevel( sceneId, selfId, NPCId,MissionId, nExt )

	local myMissionId = x300580_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end



	
	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300580_g_MissionName)
		AddQuestText(sceneId,format("\t��%d�ֿ������Ͽ�ʼ",x300580_Min_Step+nExt))
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300580_g_ScriptId, MissionId,0);
	


end




---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300580_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300580_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	
	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300580_g_MissionName)
		AddQuestText(sceneId,"ͨ����ο��飬���Ƿ��ǰ����ڴ����˱��֪����")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300580_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300580_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local myMissionId = x300580_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	
	local nCurrentStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_GAMESTEP )
	
	local nCount =0;

	
	if nCurrentStep >= x300580_Min_Step then
		nCount = nCurrentStep
	else
		return 0
	end
	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300580_g_MissionName)
		AddQuestText(sceneId,"\t#Y@myname#W����л�����ˣ������ƽ���ˮ��֮�պ�Զ�������ϵĿ����ˣ�����Ҳ������ɢ������\n\t������Щ������ǰ��ն���ľ��⡣")
	
	local level = GetLevel(sceneId, selfId)
    for i, item in x300580_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300580_g_ScriptId, MissionId);

end







---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300580_QuestLogRefresh( sceneId, selfId, MissionId)
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end
		
	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- ����
							x300580_GetMissionName(sceneId,selfId),        -- ��������
							x300580_GetMissionTask(sceneId,selfId),		--����Ŀ��
							x300580_GetReplyNpcId(sceneId,selfId),			--����NPC
							x300580_GetMissionMethod(sceneId,selfId),               --������
							x300580_GetMissionText(sceneId,selfId),	--��������
							x300580_GetMissionHelp(sceneId,selfId)					--����С��ʾ
							)

	--1������
	local level = GetLevel(sceneId, selfId)
    for i, item in x300580_g_RewardTable do
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
	
	-- --2.��Ʒ
	
	-- for i, item in x300580_g_BonusChoiceItem do
	    -- AddQuestRadioItemBonus(sceneId, item.item, item.n)
	-- end

	

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300580_GetMissionName(sceneId,selfId)
	

	return x300580_g_MissionName;
end

function x300580_GetMissionTask(sceneId,selfId)
	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	
	local nValue = GetQuestParam( sceneId, selfId, misIndex, 0 )

	--local str = "  ͨ��#G���׵�����ͼ#W�ҵ�#G"..format("#W(%d/1)",nValue)
		local str = "  #Y����ظ�:@npc_110102"
	
		
	return str;
end

function x300580_GetReplyNpcId(sceneId,selfId)
	
	return "@npc_"..x300580_g_ReplyNpcId
	
end

function x300580_GetMissionMethod(sceneId,selfId)
	return "\t��ס�ĸ��ɼ����ϵ�#Gˮ����Ч��ɫ#W��ÿ�������˸��Ч����ס#G��˸�Ĵ�����˳��#W������Ч���Ź��󣬰���ԭ�в���˳�����ε���Ŀ�#GСˮ��#W��ɿ��顣"
end

function x300580_GetMissionText(sceneId,selfId)
	return "\t����������һ�����ϴ�˵����������֮ʱ�������޴����ѣ�Ψ���ƽ�ˮ��֮�գ����ܻ�����һ���ƽ١�\n\t����⼸���º�������Ű���Ѿ�Ӱ��˵ذ��յ�����ҷ����ӵ����䡣ͬʱ���������Ĺ���ˮ���ڳ�����������ٴβ�ʱ������ɫ��â��\n\t#Y@myname#W�����Ƿ�Ը��ǰȥһ̽ˮ���İ��أ�"
end

function x300580_GetMissionHelp(sceneId,selfId)
	return ""
end


function x300580_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300580_QuestLogRefresh( sceneId, selfId, MissionId );
end





function x300580_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end




function x300580_OnClickBox( sceneId, selfId, nIndex)

	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		return 0
	end
	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		x300580_ShowTips(sceneId, selfId, "��û���ĳ���������")
		return 0;
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
	local nCurrentStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_GAMESTEP )

	if bCompleted>0 then
		if nCurrentStep<8 then
			x300580_ShowTips(sceneId, selfId, "��ϲ��ͨ���˿��飬��ȥ����ˮ����ѡ������������ս�����Ѷ�")
		else
			x300580_ShowTips(sceneId, selfId, "��ϲ��ͨ���˿��飬��ȥ����ˮ�����������")
		end
		return
	end

	if IsHaveSpecificImpact(sceneId, selfId, x300580_g_BuffId)<=0 then
		x300580_ShowTips(sceneId, selfId, "��������ˮ����ʼ����")
		return
	end

	local nAcitionFlag = GetQuestParam( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG )
	

	if nCurrentStep<=0 then
		x300580_ShowTips(sceneId, selfId, "���黹δ��ʼ")
		return
	end

	if nAcitionFlag~=2 then
		x300580_ShowTips(sceneId, selfId, "���ڻ����ܵ��ˮ��")
		return
	end

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, x300580_G_QUESTIONID )

	local nAnswerStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_ANWER_STEP )+1

	local nCurrentAnswer = x300580_g_QuestList[nCurrentStep][nQuestionId][nAnswerStep]

	--x300580_ShowTips(sceneId, selfId, format("%d",nIndex))
	if nCurrentAnswer==nIndex then
		x300580_PlayGameEffect( sceneId, selfId, nIndex)
		SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ANWER_STEP, nAnswerStep )
		x300580_ShowTips(sceneId, selfId, "��ȷ��")

		if nAnswerStep>=nCurrentStep then
			x300580_OnOneRoundCompleted(sceneId, selfId)
		end
	else
		if (nCurrentStep-1)<x300580_Min_Step then
			x300580_ShowTips(sceneId, selfId, "����")
		else
		x300580_OnAnswerWrong(sceneId, selfId)
	end
	end
	
end

function x300580_OnAnswerWrong(sceneId, selfId)  --�ش����
	
	x300580_ShowTips(sceneId, selfId, format("�ش����%d������¿�ʼ��һ��",x300580_Round_wait))
	x300580_Restart(sceneId, selfId)
	
end


function x300580_Restart(sceneId, selfId) --���¿�ʼ����
	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		return 0
	end
	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		return 0;
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nCurrentStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_GAMESTEP )
	
	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_GAMESTEP, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ANWER_STEP, 0 )

	SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_FRAME, 0 )

	
	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG, 3 )	--����Flag
	
	if IsHaveSpecificImpact(sceneId, selfId, x300580_g_BuffId)<=0 then
		SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId, x300580_g_BuffId,0 )  --����Ҽ�buff��ʱ
		
	end
end


function x300580_OnOneRoundCompleted(sceneId, selfId)  --�ش�һ�����
	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		return 0
	end
	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		return 0;
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nCurrentStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_GAMESTEP )
	
	
	--SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ANWER_STEP, 0 )

	
	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_FRAME, 0 )

	if nCurrentStep==0 then
		SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG, 3 )	--����Flag
		x300580_ShowTips(sceneId, selfId, format("%d���ʼ��һ�ֿ���",x300580_Round_wait))
	elseif nCurrentStep<x300580_Min_Step then
		SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG, 3 )	--����Flag
		x300580_ShowTips(sceneId, selfId, format("��ϲ��ͨ�����ֿ��飬%d���ʼ��һ��",x300580_Round_wait))
	elseif nCurrentStep<x300580_Max_Step then
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 1 )

		SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG, 4 )	--����Flag
		x300580_ShowTips(sceneId, selfId, format("��ϲ��ͨ��ǰ%d�ֿ��飬�����ѡ��������ȡ���������߼�����ս��%d�ֿ����ø��ߵĽ�����",nCurrentStep,nCurrentStep+1))
	else
		SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG, 10 )	--����Flag
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 1 )

		x300580_ShowTips(sceneId, selfId, "��ϲ�㣬�ɹ�ͨ�������еĿ��飡")
	end

	if IsHaveSpecificImpact(sceneId, selfId, x300580_g_BuffId)<=0 then
		SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId, x300580_g_BuffId,0 )  --����Ҽ�buff��ʱ
		
	end
end


function x300580_OnStartDifficultLevel(sceneId, selfId)  --��ʼ���Ѷ���ս
	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		return 0
	end
	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		return 0;
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nCurrentStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_GAMESTEP )
	
	
	--SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ANWER_STEP, 0 )

	
	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_FRAME, 0 )

	
	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG, 3 )	--����Flag
	x300580_ShowTips(sceneId, selfId, format("%d���ʼ��%d�ֿ���",x300580_Round_wait,nCurrentStep+1))

	if IsHaveSpecificImpact(sceneId, selfId, x300580_g_BuffId)<=0 then
		SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId, x300580_g_BuffId,0 )  --����Ҽ�buff��ʱ
		
	end
end


function x300580_OnPlayNextRound(sceneId, selfId)
	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		return 0
	end
	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		return 0;
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nCurrentStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_GAMESTEP )+1

	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_GAMESTEP, nCurrentStep )

	x300580_StartChuTi(sceneId, selfId, nCurrentStep)
end

function x300580_PlayGameEffect( sceneId, selfId, nIndex)
	CallScriptFunction(UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 25+nIndex )
end

------------------------------------------------
-- buff start 
-------------------------------------------------
--�������ʱ����
function x300580_OnIntervalOverEvent( sceneId, selfId )

	
	
	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		return 0;
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )

	if bCompleted>0 then
		return
	end

	

	local nCurrentStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_GAMESTEP )

	if nCurrentStep<0 then
		return
	end

	local nActionFlag = GetQuestParam( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG )
	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, x300580_G_QUESTIONID )
	local nFrame = GetQuestParam( sceneId, selfId, misIndex, x300580_G_FRAME )+1  --��ǰ�ǵڼ�֡

	if nActionFlag==1 then --����
		SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_FRAME, nFrame )
			
		if nFrame<=nCurrentStep then
			
			local nIndex = x300580_g_QuestList[nCurrentStep][nQuestionId][nFrame]

			x300580_PlayGameEffect( sceneId, selfId, nIndex)
		end

		if nFrame>=nCurrentStep+x300580_g_Answer_Wait then
			SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_FRAME, 0 )
			SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ANWER_STEP, 0 )
			SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG, 2 ) --����2��ʾ������ϣ��ȴ��������
			x300580_ShowTips(sceneId, selfId, "���Կ�ʼ���ողŷ����˳����Сˮ����")	
		end
	elseif nActionFlag==3 then  --����ȴ�����
		SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_FRAME, nFrame )
		if nFrame>=x300580_Round_wait then
			x300580_OnPlayNextRound(sceneId, selfId)
		end
	end

	

	
	
end

--��Чʱ����
function x300580_OnActiveEvent( sceneId, selfId )

end

--Ч����ɢʱ����
function x300580_OnFadeOutEvent( sceneId, selfId )

	
end


------------------------------------------------
-- buff end 
-------------------------------------------------














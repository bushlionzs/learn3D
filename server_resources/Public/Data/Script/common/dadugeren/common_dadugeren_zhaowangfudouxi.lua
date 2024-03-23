--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x300563_g_MissionId 				= 	9301                     --����ID
x300563_g_ScriptId 					= 	300563                  --�ű�ID
x300563_g_MissionKind 				= 	1                       --��������
x300563_g_LevelLess					= 	40                      --�������ŵȼ�  <=0 ��ʾ������


x300563_g_MissionName				= 	"�����ˡ���������Ϸ"
x300563_g_MissionName1				= 	"��ϷҪ��ʼ�ˣ�"
x300563_g_MissionTarget				= 	"�ҵ�@npc_139114"
x300563_g_MissionInfo				= 	""
x300563_g_ContinueInfo				= 	""
x300563_g_MissionCompleted			= 	""
x300563_g_MissionHelp				=	""          --������ʾ��Ϣ

--Ŀ��
x300563_g_ExtTarget					=	{ {type=20,n=1,target="��������Ϸ"}}

--����

x300563_g_ExpBonus					= 	0;--x300563_AddExpAward               	--����������
x300563_g_BonusItem					=	{{item=11000201,n=8}}	--��������Ʒ

x300563_g_BonusMoney1               = 	0
x300563_g_BonusMoney2               =   0
x300563_g_BonusMoney3               =   0

x300563_g_BonusChoiceItem           =   {}


--MisDescEnd

x300563_g_NpcList = {141501,141502,141503,141504,141505}
x300563_g_ReplyNpcId = 139114

x300563_g_GameId	= 1002

x300563_g_BuffId    = 7713
-- ��Ʒ����
x300563_g_ItemId    = 12030028
												
x300563_g_NpcTalkCount1 = 3
x300563_g_NpcTalkList1={"�����Ǽ����࣬������ʩ��һͷ�������������������ѽ��ϷҪ���ݣ��Ϸ����ǰ����","����֮�£����࿪Ʃ�������������Ƿ�δ��������θ�������������ѽ��ϷҪ���ݣ��Ϸ����ǰ����","���������������ؽ�����ߣ���Ҿ���Զ��������Ϊ�ʹ�Ҳ�����ѵ����ݣ����޷֮�⣬�����������ֲ���������ѽ��ϷҪ���ݣ��Ϸ����ǰ����"}	
	
x300563_g_NpcTalkCount2 = 3
x300563_g_NpcTalkList2={"ʮ�겻ʶ�����棬ʼ��濾�����ˡ�ϷҪ���ݣ�С��֪���ˡ�","�Ϸ��������ݣ�������Ϊ����С����;ϲ�����ǡ������������У���С��Ȩʱ��� ϷҪ���ݣ�С��֪���ˡ�","�����г������ܣ���֪��������֪�����ɣ��²��������ݡ�ϷҪ���ݣ�С��֪���ˡ�"}	

x300563_g_NpcTalkCount3 = 3
x300563_g_NpcTalkList3={"��ɫ����ҹ�������żŴ����������ǣ����������ˣ� ū�����ȥϷ̨~","����Ѱ˼�������ĳ������죬�첻Ӧ���κ��졣ū�����ȥϷ̨~","��ױ�У����Ʋʵ��������˷��������������ߡ����������飬��ױ�ж��������۷�Ƥ���ο���������ȥ�����ķ���ū�����ȥϷ̨~"}	

x300563_g_NpcTalkCount4 = 3
x300563_g_NpcTalkList4={"����֮�ۣ��󽫾������м䣬�޲��ѽ飬¾����κ�����ͽ�ͣ���һ�����������������յ�а��������ԣ���ĳ��֪ǰ����","�������ߣ�Ω�����ڶ����γ�֮�У�������ԣ���ĳ��֪ǰ����","�����ն�����������߹�Ҳ�ҵ�����������ԣ���ĳ��֪ǰ����"}	

x300563_g_NpcTalkCount5 = 3
x300563_g_NpcTalkList5={"���ж�Щ������ʱ��Ҳ��\n����������������������ǰȥ��","����������������г����Թ����Ҳ�ٲ���һƬѩ�����ɲ���˵������������������������ǰȥ��","���������ԩ��������׮��Ӧ���ˣ���֪���������˵����׼Ҳ��׼���ҿ�������Ρ����ң�Ҳ���صȴ�ѩ�磬������̧��ʬ�ף������ǲ�����ȥ�ա�����������������������ǰȥ��"}	
		


-- ��������Ʒ�б�
x300563_g_RewardTable       = {
                                { minLevel = 40, maxLevel = 60,  items = { { id = 11000201, cnt = 8 }, { id = 11050002, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 60, maxLevel = 80,  items = { { id = 11000202, cnt = 8 }, { id = 11050003, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 80, maxLevel = 999, items = { { id = 11000203, cnt = 8 }, { id = 11050004, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
}



function x300563_GetMissionId( sceneId, selfId )
	return x300563_g_MissionId
end

function x300563_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local level = GetLevel( sceneId,selfId )
    if level < x300563_g_LevelLess then
       return
    end

	local myMissionId = x300563_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300563_g_MissionName,8,1);
	else
		--local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		
		--AddQuestNumText(sceneId, myMissionId, x300563_g_MissionName,state,state);

	end


	
end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300563_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	
	if GetGameOpenById(x300563_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300563_g_MissionId) == 0 then
		x300563_ShowTips(sceneId, selfId, "�˻���첻���ţ������뵽�󶼰�������ѯÿ��������")
		return
	end

	local myMissionId = x300563_GetMissionId( sceneId, selfId )	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId )>0 then
		if nExt==30 then
			x300563_GiveQuestion(sceneId, selfId, targetId, MissionId,2)
			return
		end
	end

	
	
	if nExt>10 then --��npc�Ի�ʱ
		if nExt>=20 then
			return
		end

		local iIndex = nExt-10

		if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
			return
		end

		x300563_DispatchNpcTalkInfo( sceneId, selfId, targetId,myMissionId,iIndex )

	
	else
		
		if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
			x300563_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
		else
			if nExt==7 then -- �������
				x300563_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
				
				
			else
				
				x300563_DispatchContinueInfo( sceneId, selfId, targetId,myMissionId )				
			end
		end
	end
	    	
end


function x300563_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x300563_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300563_g_MissionId) == 0 then
		
		return 0;
	end
	return 1;

end

function x300563_CheckRequest(sceneId, selfId)
	if GetGameOpenById(x300563_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300563_g_MissionId) == 0 then
		x300563_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0
	end
	local myMissionId = x300563_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300563_g_LevelLess then
		x300563_ShowTips(sceneId, selfId, "��ȼ�����")
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300563_ShowTips(sceneId, selfId, "���Ѿ������������������������")
		return 0;
	end

    local day = GetDayOfYear()
    if day == GetQuestData( sceneId, selfId, MD_ZDOUXI_DATE[1], MD_ZDOUXI_DATE[2],MD_ZDOUXI_DATE[3] ) then
        Msg2Player( sceneId, selfId, "�ܱ�Ǹ���������Ѿ����������񣬲����ٴ���ȡ", 8, 3)
        return 0
    end

    if GetQuestData( sceneId, selfId, MD_RICHANG_DAY[ 1], MD_RICHANG_DAY[ 2], MD_RICHANG_DAY[ 3] ) == day then
        if GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[ 1], MD_RICHANG_COUNT[ 2], MD_RICHANG_COUNT[ 3] ) >= 3 then
            Msg2Player( sceneId, selfId, "�㲻������ȡ������ճ�������", 8, 3)
            return 0
        end
    else
        SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 0)
    end

	return 1;

end

function x300563_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	
	
	if GetGameOpenById(x300563_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300563_g_MissionId) == 0 then
		x300563_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	if x300563_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300563_GetMissionId( sceneId, selfId )

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300563_ShowTips(sceneId, selfId, "�����������޷���������")
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

    if GetQuestData( sceneId, selfId, MD_RICHANG_DAY[ 1], MD_RICHANG_DAY[ 2], MD_RICHANG_DAY[ 3] ) == GetDayOfYear() then
        if GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[ 1], MD_RICHANG_COUNT[ 2], MD_RICHANG_COUNT[ 3] ) >= 3 then
            Msg2Player( sceneId, selfId, "�㲻������ȡ������ճ�������", 8, 3)
            return 0
        end
    end

	local ret = AddQuest( sceneId, selfId, myMissionId, x300563_g_ScriptId, 0, 0, 0,1)-- ������������		
		
	if ret > 0 then
		local str = "������������"..x300563_g_MissionName;
		x300563_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)
		
		local myMissionId = x300563_GetMissionId( sceneId, selfId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 5, 0 )
        SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300563_g_BuffId, 0)
		GamePlayScriptLog(sceneId, selfId, 911)
		return 1
	else
		
		x300563_ShowTips(sceneId, selfId, "�����������")
	
	end


end

function x300563_GiveQuestion(sceneId, selfId, targetId, MissionId, nExt)
	
	if GetGameOpenById(x300563_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300563_g_MissionId) == 0 then
		x300563_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end
	local myMissionId = x300563_GetMissionId( sceneId, selfId )

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 5, 1 )  --��û�д���
	SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 1, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 2, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 3, 0 )

	x300563_ShowQuestion( sceneId, selfId, targetId,MissionId )

	x300563_QuestLogRefresh( sceneId, selfId, myMissionId );
end

function x300563_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300563_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300563_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	local ret = DelQuestNM( sceneId, selfId, myMissionId )

	if ret>0 then

		local str = "������������"..x300563_g_MissionName;
	    x300563_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

        local today = GetDayOfYear()
		SetQuestData( sceneId, selfId, MD_ZDOUXI_DATE[1], MD_ZDOUXI_DATE[2], MD_ZDOUXI_DATE[3], today)
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
		x300563_ShowTips(sceneId, selfId, "��������ʧ��")
	end

	
end



function x300563_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	if GetGameOpenById(x300563_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300563_g_MissionId) == 0 then
		x300563_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	local myMissionId = x300563_GetMissionId( sceneId, selfId )
	
	if x300563_CheckSubmit(sceneId, selfId )>0 then
		local today = GetDayOfYear()
        local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
        if today == GetQuestData(sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2],MD_RICHANG_DAY[3] ) and count >= 3 then
            Msg2Player( sceneId, selfId, "������ճ������Ѿ������ٽ��ˣ�����������", 8, 3)
            return 0
        end

		local nRet,nRet2 = x300563_GiveRewardTest(sceneId,selfId)

		if nRet<=0 then
			return
		end
        x300563_GiveReward(sceneId,selfId,nRet, nRet2,selectId)

		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then
            CallScriptFunction( 270300, "OnSubmissionFinished", sceneId, selfId, x300563_g_MissionId)

			local str = "�����������"..x300563_g_MissionName;
			x300563_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

            SetQuestData( sceneId, selfId, MD_ZDOUXI_DATE[1], MD_ZDOUXI_DATE[2], MD_ZDOUXI_DATE[3], GetDayOfYear() )

            if IsHaveSpecificImpact( sceneId, selfId, x300563_g_BuffId) == 1 then
                CancelSpecificImpact( sceneId, selfId, x300563_g_BuffId)
                if random( 1, 100) <= 20 then
                    BeginAddItem( sceneId)
                    AddItem( sceneId, x300563_g_ItemId, 1)
                    local ret = EndAddItem( sceneId, selfId)
                    if ret == 1 then
                        AddItemListToPlayer( sceneId, selfId)
                        LuaThisScenceM2Wrold( sceneId, format( "%sʵ���˵ã���������Ϸ��ʼǰ�ǳ���ʱ���ҵ��˸�λϷ�ӣ��ؽ���һ��@item_%d��", 
                            GetName( sceneId, selfId), x300563_g_ItemId), 1, 1)
                    else
                        Msg2Player( sceneId, selfId, "��Ʒ���������޷������Ʒ", 8, 3)
                    end
                end
            end

			GamePlayScriptLog(sceneId, selfId, 912)
			
		else
			x300563_ShowTips(sceneId, selfId, "������ʧ��")
		end
		
	end
end

function x300563_GiveRewardTest(sceneId,selfId)
	if GetGameOpenById(x300563_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300563_g_MissionId) == 0 then
		x300563_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	
	
	
	local bGetRandom = 0;
	
	local nItemTypeCount = 2;
	local itemlist = {  11000201,11000201}
	local iIndex = 0
	
	BeginAddItem(sceneId)
		AddItem( sceneId, 11000201, 8 )
		if random(1,100)<=1 then  --1% �ĸ���
			iIndex = random(1,nItemTypeCount);
			AddItem( sceneId, itemlist[iIndex], 15 )
			bGetRandom = 1
			
		end
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		
		
		if bGetRandom>0 then

			return 2,iIndex ;
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

function x300563_GiveReward(sceneId,selfId, nExt, nExt2, selectRadioId)
	
	if GetGameOpenById(x300563_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300563_g_MissionId) == 0 then
		x300563_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

    -- ������ѡ��Ľ����ǲ��ǿ��ж��ǰ󶨵�
	local level = GetLevel( sceneId, selfId)
    local canBind = 0
    local count = 0
    local id = 0
    for i, item in x300563_g_RewardTable do
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
        for i, item in x300563_g_RewardTable do
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



function x300563_CheckSubmit(sceneId, selfId )
	
	if GetGameOpenById(x300563_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300563_g_MissionId) == 0 then
		x300563_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	local myMissionId = x300563_GetMissionId( sceneId, selfId )
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
function x300563_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )

	
	
	BeginQuestEvent(sceneId)

		
	
	AddQuestText(sceneId,"#Y"..x300563_g_MissionName)
	AddQuestText(sceneId,"\t�����ٵ�һ�����ٽ������¶�Ҳ��һ��������������������������¶�æ�Ĳ��ɿ�����\n\t�ҿ�����ò������̸�²��ף���û����Ȥ����æ�����ģ������������������ġ�")
	AddQuestText( sceneId,"#Y����Ŀ��:")
			
	AddQuestText( sceneId,x300563_g_MissionTarget)
	AddQuestText(sceneId," ")

	--1������
	local level = GetLevel(sceneId, selfId)
    for i, item in x300563_g_RewardTable do
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

	-- for i, item in x300563_g_BonusItem do
		-- AddQuestItemBonus(sceneId, item.item, item.n)
	-- end

	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300563_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300563_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300563_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	
	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300563_g_MissionName)
		AddQuestText(sceneId,"�㻹û���һ��⼸��Ϸ���𣿿����Ǽ������ˡ�")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300563_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300563_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local myMissionId = x300563_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	
	

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300563_g_MissionName)
		AddQuestText(sceneId,"\t#Y@myname#W�������٣�ټ��Ĵ󶼣�����ô��ͽ������Ϸ�������ˣ���Ȼ��Ӣ�����갡��\n\t����һ��СС�����⣬������Ц�ɡ�")
	
	
	
	--1������
	local level = GetLevel(sceneId, selfId)
    for i, item in x300563_g_RewardTable do
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

	-- for i, item in x300563_g_BonusItem do
		-- AddQuestItemBonus(sceneId, item.item, item.n)
	-- end
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300563_g_ScriptId, MissionId);
	 CallScriptFunction( 256225, "Finishdouxi", sceneId, selfId)

end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�����Ŀ
---------------------------------------------------------------------------------------------------
function x300563_ShowQuestion( sceneId, selfId, NPCId,MissionId )


	
	local myMissionId = x300563_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	

	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300563_g_MissionName)
		AddQuestText(sceneId,"\t���������ã��ۿ����Ϸ��Ҫ�����ˣ���ЩϷ�������ǣ����ڴ����ι䣬�����Ǽ�ɷ��Ҳ��\n\t���ȥ�ҵ���ЩϷ�ӣ����������ٻ���׼����̨��\n\t#G(��λϷ�Ӷ��ڴ��ڱ����ι䣬ȥ֪ͨ���ǻ���׼����̨��)")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300563_g_ScriptId, MissionId,0);
	


end


function x300563_DispatchNpcTalkInfo( sceneId, selfId, NPCId,MissionId,iIndex )
	local myMissionId = x300563_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	SetQuestByIndex( sceneId, selfId, misIndex, iIndex-1, 1 )
	

	local strTalkText = ""
  if iIndex==1 then
  	strTalkText = x300563_g_NpcTalkList1[random(1,x300563_g_NpcTalkCount1)]
  elseif iIndex==2 then
  	strTalkText = x300563_g_NpcTalkList2[random(1,x300563_g_NpcTalkCount2)]
  elseif iIndex==3 then
  	strTalkText = x300563_g_NpcTalkList3[random(1,x300563_g_NpcTalkCount3)]
  elseif iIndex==4 then
  	strTalkText = x300563_g_NpcTalkList4[random(1,x300563_g_NpcTalkCount4)]
  elseif iIndex==5 then
  	strTalkText = x300563_g_NpcTalkList5[random(1,x300563_g_NpcTalkCount5)]
  end
	
	
	
	NpcTalk(sceneId, NPCId, strTalkText, selfId)

	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local value3 = GetQuestParam( sceneId, selfId, misIndex, 2 )
	local value4 = GetQuestParam( sceneId, selfId, misIndex, 3 )
	local value5 = GetQuestParam( sceneId, selfId, misIndex, 4 )

	if value1*value2*value3*value4*value5>0 then
		SetQuestByIndex( sceneId, selfId, misIndex, 5, 2 ) --�������
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
	end
	
	x300563_QuestLogRefresh( sceneId, selfId, myMissionId );

	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300563_g_MissionName)
		
		if iIndex==1 then
			AddQuestText(sceneId,"\t�����Ǽ����࣬������ʩ��һͷ�����������������\n\t��ѽ��ϷҪ���ݣ��Ϸ����ǰ����")
		elseif iIndex==2 then
			AddQuestText(sceneId,"\t�����г������ܣ���֪��������֪�����ɣ��²��������ݡ�\n\tϷҪ���ݣ�С��֪���ˡ�")
		elseif iIndex==3 then
			AddQuestText(sceneId,"\t��ɫ����ҹ�������żŴ����������ǣ����������ˣ�\n\tū��֪���ˣ����ǰ����")
		elseif iIndex==4 then
			AddQuestText(sceneId,"\t����֮�ۣ��󽫾������м䣬�޲��ѽ飬¾����κ�����ͽ�ͣ���һ�����������������յ�а��\n\t������ԣ���ĳ��֪ǰ����")
		elseif iIndex==5 then
			AddQuestText(sceneId,"\t����������������г����Թ����Ҳ�ٲ���һƬѩ�����ɲ���˵��\n\t����������������������ǰȥ��")
		end
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300563_g_ScriptId, myMissionId,0);

	

end





---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300563_QuestLogRefresh( sceneId, selfId, MissionId)
	
	
		
	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- ����
							x300563_GetMissionName(sceneId,selfId),        -- ��������
							x300563_GetMissionTask(sceneId,selfId),		--����Ŀ��
							"@npc_"..x300563_GetReplyNpcId(sceneId,selfId),			--����NPC
							x300563_GetMissionMethod(sceneId,selfId),               --������
							x300563_GetMissionText(sceneId,selfId),	--��������
							x300563_GetMissionHelp(sceneId,selfId)					--����С��ʾ
							)

	--1������
	local level = GetLevel(sceneId, selfId)
    for i, item in x300563_g_RewardTable do
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

	-- for i, item in x300563_g_BonusItem do
		-- AddQuestItemBonus(sceneId, item.item, item.n)
	-- end

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300563_GetMissionName(sceneId,selfId)
	

	return x300563_g_MissionName;
end

function x300563_GetMissionTask(sceneId,selfId)
	local myMissionId = x300563_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	if nStep==0 then
		
		return "  #Y����ظ�:@npc_"..x300563_g_ReplyNpcId;
	end
	

	
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local value3 = GetQuestParam( sceneId, selfId, misIndex, 2 )
	local value4 = GetQuestParam( sceneId, selfId, misIndex, 3 )
	local value5 = GetQuestParam( sceneId, selfId, misIndex, 4 )

	local strTable = "  ";
	local str1 = strTable.."�ҵ�#G��ͭ����#W"..format("(%d/1)",value1)
	local str2 = "\n"..strTable.."�ҵ�#G��С����#W"..format("(%d/1)",value2)
	local str3 = "\n"..strTable.."�ҵ�#G��������#W"..format("(%d/1)",value3)
	local str4 = "\n"..strTable.."�ҵ�#G���ع���#W"..format("(%d/1)",value4)
	local str5 = "\n"..strTable.."�ҵ�#G�����#W"..format("(%d/1)",value5)

	if value1>=1 then
		str1 = "#G"..str1
	else
		str1 = "#W"..str1
	end
	if value2>=1 then
		str2 = "#G"..str2
	else
		str2 = "#W"..str2
	end
	if value3>=1 then
		str3 = "#G"..str3
	else
		str3 = "#W"..str3
	end
	if value4>=1 then
		str4 = "#G"..str4
	else
		str4 = "#W"..str4
	end

	if value5>=1 then
		str5 = "#G"..str5
	else
		str5 = "#W"..str5
	end

	return str1..str2..str3..str4..str5
end

function x300563_GetReplyNpcId(sceneId,selfId)
	return x300563_g_ReplyNpcId;
end

function x300563_GetMissionMethod(sceneId,selfId)
	return "\t�ҵ���λϷ�ӡ�#GС��#W������#G����#W������#G���#W������#G�ع�#W������#Gͭ��#W��������Ӧ����#G���ڱ����й䡣"
end

function x300563_GetMissionText(sceneId,selfId)
	return "\t��ɼ������ˣ����������ã���ЩϷ���ǣ����ڴ��ڱ����ι䣬�ۿ����Ϸ��Ҫ�����ˣ����ȥ�ҵ���ЩϷ�ӣ����������ٻ���׼����̨��"
end

function x300563_GetMissionHelp(sceneId,selfId)
	return "\t��λϷ��һֱ���ڴ��ڱ����߶���Ҫ��ϸѰ�ҡ�\n\t#W��#Gͭ��#W�����������ںܸ���Ȥ�����������ڣ�\n\t��#GС��#W���Բ�˹��Ů��֮���͡����������ḽ����\n\t��#G����#W�����Ƕ��б�ʯ�ĵط�����������������ʯ���˸�����\n\t��#G�ع�#W��ϲ��ȥ�С���������ʨ�ӡ��ĵط������ʹ������⣩\n\t��#G���#W�������ָ��ַǳ���Ľ������������ڣ�"
end



function x300563_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300563_QuestLogRefresh( sceneId, selfId, MissionId );
end

--// system function start
function x300563_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	
	local myMissionId = x300563_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	
	
	if npcGuid == x300563_g_ReplyNpcId then
		local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

		if nStep==0 then
			AddQuestNumText(sceneId, x300563_g_MissionId, x300563_g_MissionName,2,30);
		elseif nStep>0 then
			local state = GetQuestStateNM(sceneId, selfId, npcGuid, myMissionId);

		
			AddQuestNumText(sceneId, myMissionId, x300563_g_MissionName,state,state);
		end
	
	else
		local bFind =0;
		local iIndex=0
		for i,item in x300563_g_NpcList do
			iIndex = iIndex+1;
			if npcGuid==item then
				bFind=1;
				break;
			end
		end

		

		if bFind==0 then
			return
		end

		local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

		if nStep~=1 then
			return
		end



		
		local value = GetQuestParam( sceneId, selfId, misIndex, iIndex-1)

		if value==0 then


			AddQuestNumText(sceneId, x300563_g_MissionId, x300563_g_MissionName1,2,iIndex+10);
		end
	end
	

	
end


function x300563_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end



--// system end





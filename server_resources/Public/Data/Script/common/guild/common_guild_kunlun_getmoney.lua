--�����Ǯ�ű�

x300678_g_ScriptId = 300678
x300678_g_MissionName = "����᡿�������"
x300678_g_MissionId = 7028

x300678_g_Min_Level = 20

x300678_g_SubmitParamIndex = 0
x300678_g_SubmitMoney = 10000

x300678_Item_Goods = { 13030122, 13030123, 13030124, 13030125, 13030126, 13030127 }
x300678_Item_GoodsCount = 3
x300678_Item_Money = 13030128

x300678_Max_Count = 100
x300678_g_MoneyBuff = 8353
x300678_gameopenid = 1029


function x300678_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x300678_gameopenid)<=0 then
		return
	end

	
	if GetGuildID(sceneId, selfId) ~= -1 then
		local state = GetQuestStateNM(sceneId, selfId, targetId, MissionId);
		AddQuestNumText(sceneId, MissionId, x300678_g_MissionName, state, -1)
	end
end

function x300678_DispatchMissionInfo( sceneId, selfId, NPCId )
		local level = GetLevel(sceneId,selfId)
		local nExp = level*3000
		local GuildMoney =20
		local maxlevel = GetTopListInfo_MaxLevel(GetWorldID(sceneId, selfId))
		local explevel = maxlevel - 10
	
		if nExp> 0 then
			AddQuestExpBonus(sceneId, nExp )
		end

		
end



--ѡ������
function x300678_ProcEventEntry( sceneId, selfId, targetId, MissionId )

	if GetGuildID(sceneId, selfId) == -1 then
		return
	end

		local level = GetLevel(sceneId,selfId)
		local GuildLevel = GetGuildSimpleData(GetGuildID( sceneId, selfId ))
		local nExp = level*3000
		local GuildMoney =20
		local maxlevel = GetTopListInfo_MaxLevel(GetWorldID(sceneId, selfId))
		local explevel = maxlevel - 10
	
		if GetGameOpenById(x300678_gameopenid)<=0 then
			return
		end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 1 then	-- ������������
	 	if GetGuildID(sceneId, selfId) == -1 then
	 		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"���Ѿ����ڰ���У����������ټ���������")
			EndQuestEvent()
			DispatchQuestDemandInfo(sceneId, selfId, targetId, x300678_g_ScriptId, MissionId,0);
			return
		end	
		
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		if GetQuestParam( sceneId, selfId, misIndex, 6) == 0 then	--����ʧ�ܣ�������ȡ
		
			if x300678_IsMissionCompleted( sceneId, selfId, MissionId ) == 1 then -- �������������
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y����᡿�������")
				AddQuestText(sceneId,"\t��ô���׬����ô�ࣿ\n\t������᲻��������㡣������Ľ�����#r")
				AddQuestText(sceneId,"#Y�������ݣ�")
					AddQuestText(sceneId,"#W����ֵ��"..nExp)
				AddQuestText(sceneId,"#W����Ǯ��20��")
				--x300678_DispatchMissionInfo( sceneId, selfId, targetId )
				--AddQuestText(sceneId,"#W����Ǯ��20��")
				EndQuestEvent()
				DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300678_g_ScriptId, MissionId);
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y����᡿�������")
				AddQuestText(sceneId,"\tһ������ǿ�󣬲��ǿ�����֮������Ҫ���а��ڵ�Ŭ����ȡ��\n\t��ҲӦ��Ϊ�����Щ���顣#r")
				--AddQuestText(sceneId,"#Y�������ݣ�")
				--if level < 60 then
				--	AddQuestText(sceneId,"#W����ֵ��"..nExp)
				--elseif level >= 60 and level <=explevel then
				--AddQuestText(sceneId,"#W����ֵ��"..nExp)
				--end
				--AddQuestText(sceneId,"#W����Ǯ��20��")
				--x300678_DispatchMissionInfo( sceneId, selfId, targetId )
				--AddQuestText(sceneId,"#W����Ǯ��20��")
				EndQuestEvent()
				DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300678_g_ScriptId, MissionId);		
			end
			return
		end
		
	end

	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_GET_MONEY_COUNT, x300678_g_ScriptId, MissionId, "ProcAcceptMission", targetId );
	
end

function x300678_ProcAcceptMission(sceneId, selfId,MissionData,MissionId,targetId)

	if GetGameOpenById(x300678_gameopenid)<=0 then
		return
	end

	if GetGuildID(sceneId, selfId) == -1 then
		return
	end

	local count = 99-(MissionData)
	local level = GetLevel(sceneId,selfId)
	local nExp = level*3000
	local GuildMoney =20
	local maxlevel = GetTopListInfo_MaxLevel(GetWorldID(sceneId, selfId))
	local explevel = maxlevel - 10
	BeginQuestEvent(sceneId)
	local Readme_1 = ""		
	local Readme_2 = "\t��������һЩ����������Ҫ���۸�����@npc_129180��@npc_129181��@npc_129182Ϊ���׬ȡ��Ǯ�����⣬�������ڵ���������@npc_129183������#G�߼��չ����л���#W��\n\tÿ��������Ҫ����#R5#W��������������ΪѺ��������񷵻�5���������������ʧ�ܣ�Ѻ�𽫱�#Rû��#W��#r"
	local Readme = Readme_1 .. Readme_2
	AddQuestText(sceneId,"#Y����᡿�������")
	AddQuestText(sceneId,Readme)
	AddQuestText(sceneId,"#W#G��᱾������ʣ�������#Y"..count.."#G��#r")
	AddQuestText(sceneId,"#Y�������ݣ�")
		AddQuestText(sceneId,"#W����ֵ��"..nExp)
	AddQuestText(sceneId,"#W����Ǯ��20��")
	
	--x300678_DispatchMissionInfo( sceneId, selfId, targetId )
	--AddQuestText(sceneId,"#W����Ǯ��20��")
	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, targetId, x300678_g_ScriptId, MissionId);
	
end

function x300678_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if GetGameOpenById(x300678_gameopenid)<=0 then
		return
	end
	
	if GetGuildID(sceneId, selfId) == -1 then
		return
	end
	
	local GuildLevel = GetGuildSimpleData(GetGuildID( sceneId, selfId ))
	if GuildLevel < 3 then
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ�а��ȼ��������������ܽ�ȡ����᡿�����������",8,3) 
		return 
	end	
	
	
	if GetGameOpenById(x300678_gameopenid)<=0 then
		return
	end
	
	if IsQuestFullNM( sceneId, selfId )==1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ɽ�������������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 
	end	

	if GetLevel(sceneId, selfId) < x300678_g_Min_Level then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�ȼ����ͣ����ܽ��ܴ�����");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"�ȼ����ͣ����ܽ��ܴ�����",8,2)	
		return
	end
	
	if GetGuildID(sceneId, selfId) == -1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t���Ѿ����ڰ���У����������ټ���������");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"���Ѿ����ڰ���У����������ټ���������",8,2)	
		return
	end
	
	local subsillertype=1
	if CostMoney(sceneId, selfId, 1, 5000) == -1 then
		subsillertype = 0
		if CostMoney(sceneId, selfId, 0, 5000) == -1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "\t�������������㣬���ܽ��ܴ�����");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,"�������������㣬���ܽ��ܴ�����",8,2)				
			return
		end
	end
	

	--�����м���Ʒ
	x300678_DelMissionItems(sceneId, selfId)
	if x300678_AddMissionItems(sceneId, selfId) == 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�����ռ䲻�㣬���ܽ���������ı���������Ҫ4���ո�");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"�����ռ䲻�㣬���ܽ���������ı���������Ҫ4���ո�",8,2)	
		
		AddMoney(sceneId,selfId,subsillertype,5000)
		
		return
	end
	
	AddQuestNM(sceneId, selfId, x300678_g_MissionId);
	--SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300678_g_MoneyBuff, 0)
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	SetQuestParam(sceneId, selfId, misIndex, 0, 0)
	
	local str = format("����ȡ������%s", x300678_g_MissionName)
	Msg2Player(sceneId,selfId,"�������5�����ӵ�Ѻ��",8,2)
	Msg2Player(sceneId,selfId,str,8,2)	
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);	
	
	SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
	SetQuestByIndex( sceneId, selfId, misIndex, 6, 0)
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
	x300678_ProcQuestLogRefresh(sceneId, selfId, MissionId)
	
	--дLog
	GamePlayScriptLog(sceneId, selfId, 1321)

end

--�������
--����1����ɹ���0��������ʧ��
function x300678_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
    
	if GetGameOpenById(x300678_gameopenid)<=0 then
		return
	end	
	
	if GetGuildID(sceneId, selfId) == -1 then
		return
	end
	
	local GuildLevel = GetGuildSimpleData(GetGuildID( sceneId, selfId ))
	if GuildLevel < 3 then 
		return 
	end		
	
	if MissionId == nil or MissionId < 0 then
        return 0
    end

	if IsHaveQuestNM( sceneId, selfId, MissionId) <= 0 then	-- ���û�������ֱ���˳�
		return 0
	end
	
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --�����Ѿ����
		return 0
	end
	
	if HaveItem(sceneId, selfId,x300678_Item_Money) <= 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�����Ʊ�����ڣ����ܽ�����");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"�����Ʊ�����ڣ����ܽ�����",8,2)			
		return 0		
	end
	
	if GetGuildID(sceneId, selfId) == -1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"���Ѿ����ڰ���У����������ټ���������")
		EndQuestEvent()
		DispatchQuestDemandInfo(sceneId, selfId, targetId, x300678_g_ScriptId, MissionId,0);
		return 0
	end		

	if x300678_IsMissionCompleted(sceneId, selfId, MissionId) ~= 1 then 
		return 0
	end
	
	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_GET_MONEY_COUNT, x300678_g_ScriptId, MissionId, "OnMissionComplete" );
	
end

-- �������
function x300678_OnMissionComplete(sceneId, selfId,MissionData,MissionId,targetId)


	if GetGameOpenById(x300678_gameopenid)<=0 then
		return
	end	
	
	if GetGuildID(sceneId, selfId) == -1 then
		return
	end
	
	local GuildLevel = GetGuildSimpleData(GetGuildID( sceneId, selfId ))
	if GuildLevel < 3 then 
		return 
	end		
	
	if MissionId == nil or MissionId < 0 then
        return 0
    end

	if IsHaveQuestNM( sceneId, selfId, MissionId) <= 0 then	-- ���û�������ֱ���˳�
		return 0
	end
	
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --�����Ѿ����
		return 0
	end
	
	if HaveItem(sceneId, selfId,x300678_Item_Money) <= 0 then	
		return 0		
	end
	
	if GetGuildID(sceneId, selfId) == -1 then
		return 0
	end		

	if x300678_IsMissionCompleted(sceneId, selfId, MissionId) ~= 1 then 
		return 0
	end


	if MissionData >= x300678_Max_Count-1 then
		local message = "�����������"
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId, selfId, message, 8, 2)
		return
	end

	-- �������
	DelQuestNM( sceneId, selfId, MissionId)
	--CancelSpecificImpact( sceneId, selfId,  x300678_g_MoneyBuff)

    -- ���ӻ�Ծ��
    local id = GetGuildID( sceneId, selfId)
    if id ~= -1 then
        AddGuildActivity( sceneId, selfId, GetGuildCacheFreeParam( id, GD_GUILD_ACTIVITY_PARAM6) )
    end
	
	-- ɾ�����������Ʒ
	x300678_DelMissionItems(sceneId, selfId)
	
	local message = format("�����������%s", x300678_g_MissionName);
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 8, 2);
	
	local guildid = GetGuildID(sceneId,selfId);
	SetGuildQuestData(sceneId, guildid, GD_GUILD_INDEX_GET_MONEY_COUNT, 1, 1 );	
	
	x300678_GiveBonus(sceneId,selfId,99 - MissionData)
	
	--дLog
	GamePlayScriptLog(sceneId, selfId, 1322)
end

--������
function x300678_GiveBonus(sceneId,selfId,count)
	
	-- ���˽���������
	local level = GetLevel(sceneId,selfId)
	local nExp = level*3000
	local money =5000
	local moneymes = "��������Ѻ��5��������"
	local name =GetName(sceneId,selfId)
	--local times = 
	local banghuimes = format("#G���#Y%s#G�ɹ��������#Y����᡿�������#G���񣬰���Ǯ������#Y20#G������᱾����������ʣ��#Y%s#G�Ρ�",name,count-1)
	local guildid = GetGuildID(sceneId, selfId)
	local maxlevel = GetTopListInfo_MaxLevel(GetWorldID(sceneId, selfId))
	local explevel = maxlevel - 10
	--���˾���
	AddExp(sceneId,selfId,nExp)
	--����������ʱ�Ľ�Ǯ
	AddMoney( sceneId, selfId, 1, money )
	Msg2Player(sceneId, selfId, moneymes, 8, 2);
	Msg2Player(sceneId, selfId,"������#R����"..nExp.."��#cffcf00�Ľ�����",8,2)
	-- ��ά��������Ǯ,��ṫ��
	AddGuildMoney(sceneId,selfId,20000)
	--Msg2Player(sceneId, selfId, banghuimes, 6, 2);
	LuaAllScenceM2Guild(sceneId, banghuimes, guildid, 0,1)
	
	
	
end

function x300678_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û���������
		return
	end
end

function x300678_ProcQuestAbandon( sceneId, selfId, MissionId )
	
	DelQuestNM( sceneId, selfId, MissionId)
	x300678_DelMissionItems(sceneId, selfId)
	
	local message = format("������������%s", x300678_g_MissionName);
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 8, 2);
	
end

function x300678_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	local nMoney = GetQuestParam( sceneId, selfId, misIndex, x300678_g_SubmitParamIndex)
	local strTarget = "  ��@npc_129181��@npc_129182��@npc_129180�������۰�����׬ȡ�㹻��Ǯ("..nMoney.."/"..x300678_g_SubmitMoney..")";
	
	if GetQuestParam( sceneId, selfId, misIndex, 6) == 1 then	--����ʧ��
		strTarget = "  ����ʧ�ܣ���������ȡ"
	end
	
	BeginQuestEvent( sceneId)
		local level = GetLevel(sceneId,selfId)
		local nExp = level*3000
		local GuildMoney =20
		local maxlevel = GetTopListInfo_MaxLevel(GetWorldID(sceneId, selfId))
		local explevel = maxlevel - 10
	
	AddQuestLogCustomText( sceneId,
							"",                             -- ����
							x300678_g_MissionName,          -- ��������
							strTarget,
							"",
                             -- ����NPC
							"\t�ҵ��Ƕ����ˣ��������ˣ������Գ����˼��������̣������ϵİ�������۸����ǣ�һ��Ҫ׬ȡ�㹻�Ľ�Ǯ�����������#Y\n�������ݣ�\n#W����ֵ��"..nExp.."\n#W����Ǯ��20��",
							"\t���ķ�չ�벻������Ǯ��\n\t��������һЩ�������ʴ��ۣ���˵�Ƕ�����@npc_129181����������@npc_129182�������Գ�����@npc_129180�����չ����ǡ�\n\t�������Щ���ʣ�����������,Ϊ���׬ȡ�㹻�Ľ�Ǯ�ɡ�\n\tֵ��ע����ǣ���������λ���ص����ˣ�����@npc_129183������������#G�߼��չ����л���#W��\n\t�����ﹲ���������ࣺ#G��˹�𰰣���������������ɽ�Σ�������֥���������������ɺ����",
							"\t�������˻������ǵĹ㳡�������ߣ�Ҫ�ҵ��������̿ɲ��Ǹ����׵��¡�")
		AddQuestText(sceneId,"#Y�������ݣ�")
			AddQuestText(sceneId,"#W����ֵ��"..nExp)
		AddQuestText(sceneId,"#W����Ǯ��20��")
	EndQuestEvent()	
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
	
	-- �������
	if x300678_IsMissionCompleted(sceneId, selfId, MissionId) == 1 then
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
	end
	
end

-- �ж�Ǯ��������
function x300678_IsMissionCompleted(sceneId, selfId, MissionId)

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	local nMoney = GetQuestParam( sceneId, selfId, misIndex, x300678_g_SubmitParamIndex)
	if nMoney > x300678_g_SubmitMoney then
		return 1
	else
		return 0
	end

end

-- ���������Ʒ
function x300678_AddMissionItems(sceneId, selfId)
	local item1, item2, item3
	local nTotalNum = getn(x300678_Item_Goods)
	item1 = x300678_Item_Goods[ random(1,nTotalNum) ]
	item2 = x300678_Item_Goods[ random(1,nTotalNum) ]
	while item2 == item1 do
		item2 = x300678_Item_Goods[ random(1,nTotalNum) ]
	end
	item3 = x300678_Item_Goods[ random(1,nTotalNum) ]
	while item3==item2 or item3==item1 do
		item3 = x300678_Item_Goods[ random(1,nTotalNum) ]
	end
	
	BeginAddItem(sceneId)
	AddItem(sceneId, item1, 1)
	AddItem(sceneId, item2, 1)
	AddItem(sceneId, item3, 1)
	AddItem(sceneId, x300678_Item_Money, 1)
    local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
	end
	return ret
end

-- ɾ��������Ʒ
function x300678_DelMissionItems(sceneId, selfId)
	local i = 0
	for i, item in x300678_Item_Goods do
		if HaveItem(sceneId,selfId,item)>0 then
			DelItem(sceneId,selfId,item,1)
		end
	end
	
	if HaveItem(sceneId,selfId,x300678_Item_Money) > 0 then
		DelItem(sceneId,selfId,x300678_Item_Money,1)
	end
end

-- �뿪���
function x300678_OnLeaveGuild(sceneId, selfId, MissionId)

	DelQuestNM( sceneId, selfId, MissionId)
	x300678_DelMissionItems(sceneId, selfId)
	
	local message = format("���Ѿ����ڰ�����ˣ�ɾ��������%s", x300678_g_MissionName);
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 8, 2);	
	
end
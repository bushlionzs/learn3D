
x300839_g_ScriptId = 300839

--�����ı�����
x300839_g_MissionName1 = "����᡿������"
x300839_g_MissionName2 = "����᡿����10������"
x300839_g_MissionName3 = "����᡿����100������"
x300839_g_MissionName4 = "����᡿����1������"
-- ���ȼ���Ӧ��Ǯ���ޱ�
x300839_g_GuildLevelMoney   = {
                                 6000000, 
                                 8000000, 
                                20000000, 
                                24000000, 
                                42000000, 
                                48000000, 
                                54000000, 
                                60000000, 
                                66000000, 
}
x300839_g_GuildDayMoney	= 30000000
--MisDescEnd
--**********************************
--������ں���
--**********************************
function x300839_ProcEventEntry( sceneId, selfId, targetId, MissionId, idExt)	--����������ִ�д˽ű�

	if idExt == 1 then 

		local Readme_1 = "#Y����᡿������#r#W"
		
		local Readme_2 = "\t������ͨ����������������#G����Ǯ#W��ÿ����#G1��#W����������ǮҲ������#G1��#W����ÿ�ξ��׶����ð���Ծ�ȺͰﹱ�Ľ�����ÿ�����������δ�ﵽ����Ǯ���޵������£������Խ���#G30��#W�ľ��ס�"
		
		local Readme_3 = "#W#r#Y\t��ѡ����Ҫ���׵�����������"
		
		local Readme = Readme_1..Readme_2..Readme_3
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, Readme);
		AddQuestNumText(sceneId, x300839_g_ScriptId, x300839_g_MissionName2, 3, 2)
		AddQuestNumText(sceneId, x300839_g_ScriptId, x300839_g_MissionName3, 3, 3)
		AddQuestNumText(sceneId, x300839_g_ScriptId, x300839_g_MissionName4, 3, 4)
		DispatchQuestEventList(sceneId,selfId,targetId);
	
	elseif idExt == 2 then

		local Readme_1 = "#Y����᡿����10������#r#W"
		
		local Readme_2 = "\t����10��������������#G10������Ǯ#W��ͬʱ��������#G1#W�����Ծ�Ⱥ�#G1#W��ﹱ��"
		
		local Readme_3 = "#W#r#Y\t���Ƿ�Ҫ���а����ף�"
		
		local Readme = Readme_1..Readme_2..Readme_3
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId);
		DispatchQuestInfo( sceneId, selfId, targetId, x300839_g_ScriptId, -1 );
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 10000)
	elseif idExt == 3 then
			
		local Readme_1 = "#Y����᡿����100������#r#W"
		
		local Readme_2 = "\t����100��������������#G100������Ǯ#W��ͬʱ��������#G10#W�����Ծ�Ⱥ�#G10#W��ﹱ��"
		
		local Readme_3 = "#W#r#Y\t���Ƿ�Ҫ���а����ף�"
		
		local Readme = Readme_1..Readme_2..Readme_3
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId);
		DispatchQuestInfo( sceneId, selfId, targetId, x300839_g_ScriptId, -1 );
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 100000)
	elseif idExt == 4 then
		local Readme_1 = "#Y����᡿����1������#r#W"
		
		local Readme_2 = "\t����1��������������#G1������Ǯ#W��ͬʱ��������#G100#W�����Ծ�Ⱥ�#G100#W��ﹱ��"
		
		local Readme_3 = "#W#r#Y\t���Ƿ�Ҫ���а����ף�"
		
		local Readme = Readme_1..Readme_2..Readme_3
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);
		DispatchQuestInfo( sceneId, selfId, targetId, x300839_g_ScriptId, -1 );
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 1000000)
	end
	
end

--**********************************
--�о��¼�
--**********************************
function x300839_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	if GetGuildID( sceneId, selfId ) == -1 then
		--���ڰ����
		return
	end
	
    AddQuestNumText(sceneId, x300839_g_ScriptId, x300839_g_MissionName1, 3, 1)
    local gid = GetGuildID( sceneId, selfId)
    if gid >= 0 then
        local today = GetDayOfYear()
        if today ~= GetGuildCacheFreeParam( gid, GD_GUILD_HANDIN_DATE) then
            SetGuildParam( gid, GD_GUILD_HANDIN_DATE, today)
            SetGuildParam( gid, GD_GUILD_HANDIN_MONEY, 0)
        end
    end
end


--********************
--����������
--**********************************
function x300839_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x300839_ProcAccept( sceneId, selfId)
    local money = GetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID)
    SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 0)
    local gmoney = GetGuildMoney( sceneId, selfId)
    local glv = GetGuildLevel( sceneId, selfId)
    local gid = GetGuildID( sceneId, selfId)

    if gid < 0 then
		BeginQuestEvent(sceneId);AddQuestText(sceneId, "����Ҫ�ȼ���һ����ᡣ");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ǰ���Ա���޷����а����ס�",8,2)
		return
    end

    if glv <= 0 then
        return
    end

	if GetGuildCacheFreeParam( gid, GD_GUILD_HANDIN_MONEY) >= x300839_g_GuildDayMoney then
        Msg2Player( sceneId, selfId, "����������ܶ��Ѵ����ޣ�����������", 8, 3)
        return
    elseif GetGuildCacheFreeParam( gid, GD_GUILD_HANDIN_MONEY) + money > x300839_g_GuildDayMoney then
        Msg2Player( sceneId, selfId, "���׵���������հ��ɾ����ޣ��޷�����", 8, 3)
        return
    end

    if gmoney + money > x300839_g_GuildLevelMoney[ glv] then
        Msg2Player( sceneId, selfId, "����Ǯ�ӽ����ѵ������ޣ��޷�����", 8, 3)
        return
    end

	if GetMoney(sceneId, selfId, 0) < money then
		BeginQuestEvent(sceneId);AddQuestText(sceneId, "�ܱ�Ǹ�������������㡣");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������������㣬�޷����а����ס�",8,2)
		return
	end

	CostMoney(sceneId, selfId, 0, money, 310)
	BeginQuestEvent(sceneId);AddQuestText(sceneId, format("�۳���Ǯ#G#{_MONEY%d}#cFFCF00����ðﹱ#G"..tostring( money / 10000).."#cFFCF00�㣬����Ծ��#G"..tostring( money / 10000).."#cFFCF00��", money));EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
	Msg2Player(sceneId,selfId,format("����᡿������:�۳���Ǯ#G#{_MONEY%d}#W", money),8,2)

	AddGuildUserPoint( sceneId, selfId, money / 10000)
	Msg2Player(sceneId,selfId,"��ðﹱ#G"..tostring( money / 10000).."#cFFCF00��",8,2)

	AddGuildActivity( sceneId, selfId, money / 10000)
	Msg2Player(sceneId,selfId,"����Ծ������#G"..tostring( money / 10000).."#cFFCF00��",8,2)

	AddGuildMoney( sceneId, selfId, money)
	Msg2Player( sceneId, selfId, format("%s����������ʹ����Ǯ������#{_MONEY%d}��",GetName(sceneId, selfId), money), 6)

    SetGuildParam( gid, GD_GUILD_HANDIN_MONEY, money + GetGuildCacheFreeParam( gid, GD_GUILD_HANDIN_MONEY) )
end

--**********************************
--����
--**********************************
function x300839_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300839_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300839_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300839_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300839_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300839_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300839_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end



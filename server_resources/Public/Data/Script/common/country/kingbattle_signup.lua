
--����ս������

--MisDescBegin
x300815_g_ScriptId              = 300815
x300815_g_Leader_Index          = 5
x300815_g_MissionName           ="�����ҡ���ս����"
x300815_g_MissionName0          ="�����ҡ��������"
x300815_g_MissionName1          ="�����ҡ�����ս����ѯ"
x300815_g_NeedMoney             = 50*1000
x300815_g_GuildLevel            = 1
x300815_g_GuildMemberNum        = 1

x300815_g_Signup_None                       = -1         --û�˱���
x300815_g_Signup_OK                         =  0         --�����ɹ�
x300815_g_Signup_Failed                     =  1         --����ʧ��
x300815_g_Signup_Signed                     =  2         --�Ѿ���������
x300815_g_Signup_Other                      =  3         --�������˱���
x300815_g_Signup_TimeNotMatch               =  4         --ʱ�䲻�ԣ����ܱ���
x300815_g_Signup_NoGuild                    =  5         --û�а��
x300815_g_Signup_GuildNotMatchPlayer        =  6         --�����������Ұ�᲻ƥ��
x300815_g_Signup_NotGuildLeader             =  7         --������Ҳ��ǰ���
x300815_g_Signup_GuildLevelError            =  8         --��ἶ�𲻹�
x300815_g_Signup_GuildMemberCountError      =  9         --��᲻��15��
x300815_g_Signup_NoKing                     =  10        --����û�й���
x300815_g_Signup_KingPlayerInSameGuild      =  11        --�����Ͱ�������ͬһ���
x300815_g_Signup_KingPlayerIsOnePlayer      =  12        --�����Ͱ�����ͬһ��
x300815_g_Signup_PowerNotEnough             =  13        --ʵ������
x300815_g_KingBattleNotPermitSignUp         =  14        --������δ����
x300815_g_Signup_OtherError                 =  15        --��������
x300815_g_Leader_Index                      =  5
--MisDescEnd
----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x300815_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
  --�������ݿ⿪��
	local UpdateDBflag = GetUpdateDBBeforeToggle()
	if UpdateDBflag==1 then
		return
	end
    
    --���Է�����
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --ս���Լ��Ŀ���
    if GetBattleSceneToggle( BATTLESCENE_TYPE_KINGBATTLE ) == 0 then
        return
    end

    --�Ƿ��й����������߲����ǹ���
    local nGuildId = GetGuildID(sceneId,selfId )

    --�ް��
    if nGuildId < 0 then
        return
    end
    

    --�ǰ���
    local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= x300815_g_Leader_Index then
        return
    end

    local nHumanGUID = GetPlayerGUID( sceneId,selfId )
    
    --ֻҪ���ǹ������ܱ���
    local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
    local nKingGuildID = GetCountryKingGuildId( sceneId,selfId )
    if nHumanGUID ~= nKingGUID then
    	if nKingGuildID < 0 then
        	AddQuestNumText(sceneId,x300815_g_ScriptId,x300815_g_MissionName0,3);
        else
        	AddQuestNumText(sceneId,x300815_g_ScriptId,x300815_g_MissionName0,3);
        end
        
        --�ڹ���ս������֮��,��ʼ֮ǰ,���Խ�����ز�ѯ����
        if GetKingBattleStatus( sceneId ) >= STATE_KING_BATTLE_SIGNUP and GetKingBattleStatus( sceneId ) < STATE_KING_BATTLE_BATTLE then
        	AddQuestNumText(sceneId,x300815_g_ScriptId,x300815_g_MissionName1,3,x300815_g_ScriptId);
        end
        
    end
    
end

----------------------------------------------------------------------------------------------
--Ĭ���¼�
----------------------------------------------------------------------------------------------
function x300815_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

    if idExt == 0 then
    
    	--���ڱ���ʱ����
    	if GetKingBattleStatus( sceneId ) ~= STATE_KING_BATTLE_SIGNUP then
    		BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ��ܱ�Ǹ�����ڲ��Ǳ���ʱ�䡣");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
    		return
    	end

        --��ѯ���
        local nGuildId = GetGuildID( sceneId,selfId )
        
         --����Ƿ��Ǿݵ�
--	    local nLairdM1,_,_,nLairdDate = GetGuildLairdSceneId(nGuildId) 
--	    if nLairdM1 > 0 then
--	    	BeginQuestEvent(sceneId)
--            AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ��������ܱ�����");
--            EndQuestEvent(sceneId)
--            DispatchQuestEventList(sceneId,selfId,targetId)
--	    	return 
--	    end
	    
        QueryKingBattleSignupState( sceneId,selfId,nGuildId,targetId )

    elseif idExt == 1 then

        --�Ƿ��ǰ���
        local pos = GetGuildOfficial(sceneId, selfId)
        if pos ~= x300815_g_Leader_Index then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ��ܱ�Ǹ���������ǰ����޷����������");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
        end

        local nGuildId = GetGuildID(sceneId,selfId )
        local nLevel,nMemberNum,nExp = GetGuildSimpleData( nGuildId )

        --���ȼ�������
        -- if nLevel < x300815_g_GuildLevel then
            -- BeginQuestEvent(sceneId)
            -- AddQuestText(sceneId, "����ʧ�ܣ����ȼ����㣲����");
            -- EndQuestEvent(sceneId)
            -- DispatchQuestEventList(sceneId,selfId,targetId)
            -- return
        -- end

        --����Ա�����Ƿ�����
        if nMemberNum < x300815_g_GuildMemberNum then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ�����Ա����15�ˣ�");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
        end
        
        
        --����Ƿ��Ǿݵ�
--	    local nLairdM1,_,_,nLairdDate = GetGuildLairdSceneId(nGuildId) 
--	    if nLairdM1 > 0 then
--	    	BeginQuestEvent(sceneId)
--            AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ��������ܱ�����");
--            EndQuestEvent(sceneId)
--            DispatchQuestEventList(sceneId,selfId,targetId)
--	    	return 
--	    end

        --�����Ƿ�����
--        local nMoney = GetMoney(sceneId,selfId,0)
--        if nMoney < x300815_g_NeedMoney then
--            BeginQuestEvent(sceneId)
--            AddQuestText(sceneId, "����ʧ�ܣ��ܱ�Ǹ���������е���������50�����޷����������");
--            EndQuestEvent(sceneId)
--            DispatchQuestEventList(sceneId,selfId,targetId)
--            return
--        end

        --�Ƿ��ǹ���ս������ʱ��
        --if GetKingBattleStatus(sceneId) ~= STATE_KING_BATTLE_SIGNUP then
        --    BeginQuestEvent(sceneId)
        --    AddQuestText(sceneId, "����ʧ�ܣ��ܱ�Ǹ������14��00~17��00֮�����������");
        --    EndQuestEvent(sceneId)
        --    DispatchQuestEventList(sceneId,selfId,targetId)
        --    return
        --end

        --�ȿ�Ǯ
        --CostMoney( sceneId,selfId,0,x300815_g_NeedMoney )

        --���϶�ͨ������������
        SignupKingBattle( sceneId,selfId,nGuildId )

    elseif idExt == x300815_g_ScriptId then
    	
    	KingBattleQueryCurrentGuild(sceneId,selfId,targetId)
    	
    end

    return 1

end

----------------------------------------------------------------------------------------------
--��ѯ����ս������״̬��Ӧ
----------------------------------------------------------------------------------------------
function x300815_OnQueryKingBattleSignupState( sceneId,selfId,nResult,targetId,nCurrentGuildA,nCurrentGuildB )
    
    if nResult == x300815_g_Signup_None then

        --δ����
        x300815_KingBattleSignup( sceneId,selfId,targetId,nCurrentGuildA,nCurrentGuildB )

    elseif nResult == x300815_g_Signup_Signed then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t�ܱ�Ǹ���Ѿ�����������ս�����������޷��ٴ���ս������");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif nResult == x300815_g_Signup_Other then

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ��ܱ�Ǹ������֮ǰ�Ѿ��а����������������");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    -- elseif nResult == x300815_g_Signup_TimeNotMatch then
        
        -- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ��ܱ�Ǹ����������14��00~17��00֮�����������");
		-- EndQuestEvent(sceneId)
		-- DispatchQuestEventList(sceneId,selfId,targetId)
    
    elseif nResult == x300815_g_Signup_NoGuild then

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ������а�����������ս��");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif nResult == x300815_g_Signup_GuildNotMatchPlayer then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ���������Ϣ��������ڰ�᲻ƥ�䣡");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif nResult == x300815_g_Signup_NotGuildLeader then

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ������ǰ����ſ������룡");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    -- elseif nResult == x300815_g_Signup_GuildLevelError then

        -- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "����ʧ�ܣ����ȼ�����2����");
		-- EndQuestEvent(sceneId)
		-- DispatchQuestEventList(sceneId,selfId,targetId)

    elseif nResult == x300815_g_Signup_GuildMemberCountError then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ�����Ա����15�ˣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif nResult == x300815_g_Signup_NoKing then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ��޷�������ս�����ڻ�û�й�����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif nResult == x300815_g_Signup_KingPlayerInSameGuild then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ������������ͬһ����ᣡ");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif nResult == x300815_g_Signup_KingPlayerIsOnePlayer then

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ����������������ս����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
		
	elseif nResult == x300815_g_Signup_PowerNotEnough then
	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ����ʵ����������Ѿ�����İ��ʵ����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
	elseif nResult == x300815_g_KingBattleNotPermitSignUp then
	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ��,�����ڹ��ҵĹ�������ս��δ����!");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		

    else
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ�δ֪ԭ�򣬿��ܹ���ս���������Ѵ����ߣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    end

    return 1

end

----------------------------------------------------------------------------------------------
--��ս����
----------------------------------------------------------------------------------------------
function x300815_KingBattleSignup( sceneId,selfId,targetId ,nCurrentGuildA,nCurrentGuildB)
    
    --�Ƿ��ǰ���
    local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= x300815_g_Leader_Index then
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t�ܱ�Ǹ���������ǰ����޷����������");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		return 0
	end

    local nGuildId = GetGuildID(sceneId,selfId )
    local nLevel,nMemberNum,nExp = GetGuildSimpleData( nGuildId )

    --���ȼ�������
    -- if nLevel < x300815_g_GuildLevel then
        -- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "����ʧ�ܣ����ȼ�����2����");
		-- EndQuestEvent(sceneId)
		-- DispatchQuestEventList(sceneId,selfId,targetId)
		-- return 0
    -- end

    --����Ա�����Ƿ�����
    if nMemberNum < x300815_g_GuildMemberNum then
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ�����Ա����15�ˣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		return 0
    end
    
    --����Ƿ��Ǿݵ�
--    local nLairdM1,_,_,nLairdDate = GetGuildLairdSceneId(nGuildId) 
--    if nLairdM1 > 0 then
--    	return 
--    end

    --�����Ƿ�����
--    local nMoney = GetMoney(sceneId,selfId,0)
--    if nMoney < x300815_g_NeedMoney then
--        BeginQuestEvent(sceneId)
--		AddQuestText(sceneId, "����ʧ�ܣ��ܱ�Ǹ���������е���������50�����޷����������");
--		EndQuestEvent(sceneId)
--		DispatchQuestEventList(sceneId,selfId,targetId)
--		return 0
--    end


    --�Ƿ��ǹ���ս������ʱ��
	if GetKingBattleStatus(sceneId) ~= STATE_KING_BATTLE_SIGNUP then
 		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ��ܱ�Ǹ����������14��00~17��00֮�����������");
		EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,targetId)
		return 0
	end


	
	local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
	local nKingGuildID = GetCountryKingGuildId( sceneId,selfId )
	
	local msg = ""
	if nKingGuildID >= 0 then
		if nCurrentGuildA >= 0 then
			local strCurrentGuildName = GetGuildName( nCurrentGuildA )
			msg = format("#R�Ѿ��й�������ȷ����������ι�������ս��\n#G��ǰ�ѷ���Թ�����ս����ʵ����ǿ���Ϊ:#c0000FF%s",strCurrentGuildName)
		else
			msg = "#R�Ѿ��й�������ȷ����������ι�������ս��\n#G��ǰû�а�ᷢ��Թ���������!"
		end
	else
		if nCurrentGuildA < 0 and nCurrentGuildB < 0 then
			msg = "#RĿǰû�й�������ȷ��Ҫ���������\n#G��ǰû�а�ᷢ��Թ���������!"
		elseif nCurrentGuildA <0 and nCurrentGuildB >= 0 then
			local strGuildBName = GetGuildName( nCurrentGuildB )
			msg = format("#RĿǰû�й�������ȷ��Ҫ���������\n#G��ǰ�ѷ���Թ�����ս����ʵ����ǿ���Ϊ:#c0000FF%s!",strGuildBName)
		elseif nCurrentGuildA >= 0 and nCurrentGuildB >= 0 then
			local strGuildBNameA = GetGuildName( nCurrentGuildA )
			local strGuildBNameB = GetGuildName( nCurrentGuildB )
			msg = format("#RĿǰû�й�������ȷ��Ҫ���������\n#G��ǰ�ѷ���Թ�����ս����ʵ����ǿ���Ϊ:#c0000FF%s,%s!",strGuildBNameA,strGuildBNameB)
		end
	end 
	
    BeginQuestEvent(sceneId)
	local msg1 ="#Y�����ҡ��������#W#r #r 1����������#G����14��00-17��00#W֮������#W��#r #r2������������������#G���ʵ����#W���������������ڰ�������İ�ᱨ�������ı������뽫�ᱻ#G����#W��#W#r #r 3��������ﱨ����ֹʱ�䣬#Gֻ��һ��#W��ᱨ������ð��#G�Զ���Ϊ��������#W������#G�Զ���Ϊ����#W��#W#r #r 4��������ﱨ����ֹʱ�䣬���뱨���İ����2���������#G����19��30-19��50#W��������ս����ʤ�߰���Ϊ�������ӣ�������Ϊ������#W#r #r5����������ĳ������#G����#W��#r #r6�����İ��#G����#W����#G����15��#W��#r #r"
	AddQuestText(sceneId, msg1);
    AddQuestText(sceneId, msg);
    AddQuestNumText(sceneId,x300815_g_ScriptId,"ȷ��..",3,1);
    EndQuestEvent(sceneId)
    DispatchQuestEventList(sceneId,selfId,targetId)

    return 1
end

function x300815_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300815_ProcAccept( sceneId, selfId )
end


----------------------------------------------------------------------------------------------
--������
----------------------------------------------------------------------------------------------
function x300815_OnKingBattleSignupResult( sceneId,selfId,nResult,targetId ,nSignupCount)
    

    --���³�������ɹ��������Ķ���Ҫ���۳���Ǯ�������
    if nResult == x300815_g_Signup_OK then

        local nGuildId = GetGuildID(sceneId,selfId )
        local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )

        local strGuildA = GetGuildName( nGuildId )
        local strGuildB = GetGuildName( GetCountryKingGuildId( sceneId,selfId ) )

        local strMsg = ""
        
        if nSignupCount > 0 then
        	strMsg = format("��ϲ�����ɹ���������ս����ĿǰΪֹ����%d����ᱨ���μӡ�",nSignupCount)
        else
        	strMsg = "��ϲ�����ɹ���������ս����Ŀǰ���˱���ỹû��������ᱨ���μӡ�"
        end
        
        LuaAllScenceM2Guild(sceneId,strMsg,nGuildId,3,1)
        LuaAllScenceM2Guild(sceneId,strMsg,nGuildId,2,1)

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strMsg);
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif nResult == x300815_g_Signup_Signed then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t�ܱ�Ǹ���Ѿ�����������ս�����������޷��ٴ���ս������");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        --��Ǯ
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )

    elseif nResult == x300815_g_Signup_Other then

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "##Y�����ҡ��������#W#r\t����ʧ�ܣ��ܱ�Ǹ������֮ǰ�Ѿ��а����������������");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        --��Ǯ
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )

    -- elseif nResult == x300815_g_Signup_TimeNotMatch then
        
        -- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ��ܱ�Ǹ����������14��00~17��00֮�����������");
		-- EndQuestEvent(sceneId)
		-- DispatchQuestEventList(sceneId,selfId,targetId)

        --��Ǯ
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )
    
    elseif nResult == x300815_g_Signup_NoGuild then

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ������а�����������ս��");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        --��Ǯ
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )

    elseif nResult == x300815_g_Signup_GuildNotMatchPlayer then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ���������Ϣ��������ڰ�᲻ƥ�䣡");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        --��Ǯ
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )

    elseif nResult == x300815_g_Signup_NotGuildLeader then

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ������ǰ����ſ������룡");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        --��Ǯ
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )

    -- elseif nResult == x300815_g_Signup_GuildLevelError then

        -- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "����ʧ�ܣ����ȼ�����2����");
		-- EndQuestEvent(sceneId)
		-- DispatchQuestEventList(sceneId,selfId,targetId)

        --��Ǯ
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )

    elseif nResult == x300815_g_Signup_GuildMemberCountError then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ�����Ա����15�ˣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        --��Ǯ
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )

    elseif nResult == x300815_g_Signup_NoKing then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ��޷�������ս�����ڻ�û�й�����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        --��Ǯ
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )

    elseif nResult == x300815_g_Signup_KingPlayerInSameGuild then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ������������ͬһ����ᣡ");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        --��Ǯ
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )

    elseif nResult == x300815_g_Signup_KingPlayerIsOnePlayer then

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ����������������ս����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        --��Ǯ
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )

	elseif nResult == x300815_g_Signup_PowerNotEnough then
	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ����ʵ����������Ѿ�����İ��ʵ����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

		--��Ǯ
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )
		
	elseif nResult == x300815_g_KingBattleNotPermitSignUp then
	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ��,�����ڹ��ҵĹ�������ս��δ����!");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId) 
		
    else
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������#W#r\t����ʧ�ܣ�δ֪ԭ�򣬿��ܹ���ս���������Ѵ����ߣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        --��Ǯ
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )
    end

    return 1

end

----------------------------------------------------------------------------------------------
--����������״̬
----------------------------------------------------------------------------------------------
function OnKingBattleAskPlayerEnterScene( sceneId, selfId )

    --֪ͨ��ҽ��볡��
    KingBattleAskEnterScene( sceneId, selfId )
    
end


----------------------------------------------------------------------------------------------
--��ѯ���
----------------------------------------------------------------------------------------------
function OnQueryCurrentGuild(sceneId,selfId,targetId,nCurrentGuildA,nCurrentGuildB,nCount)
	
	
	local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
	local nKingGuildID = GetCountryKingGuildId( sceneId,selfId )
	
	local msg = ""
	if nKingGuildID >= 0 then
		if nCurrentGuildA >= 0 then
			local strCurrentGuildName = GetGuildName( nCurrentGuildA )
			msg = format("#Y�����ҡ�����ս����ѯ#W#r #r #R�Ѿ��й�������ȷ�����������ս��\n#G��ǰ�ѷ���Թ�������ս����ʵ����ǿ���Ϊ:#c0000FF%s",strCurrentGuildName)
		else
			msg = "#Y�����ҡ�����ս����ѯ#W#r #r #R�Ѿ��й�������ȷ�����������ս��\n#G��ǰû�а�ᷢ��Թ���������!"
		end
	else
		if nCurrentGuildA < 0 and nCurrentGuildB < 0 then	
			msg = "#Y�����ҡ�����ս����ѯ#W#r #r #RĿǰû�й���!\n\t#G��ǰû�а�ᷢ�𵽹���������!"
		elseif nCurrentGuildA <0 and nCurrentGuildB >= 0 then
			local strGuildBName = GetGuildName( nCurrentGuildB )
			msg = format("#Y�����ҡ�����ս����ѯ#W#r #r #RĿǰû�й���!\n#G��ǰ�ѷ���Թ�������ս����ʵ����ǿ���Ϊ:#c0000FF%s!",strGuildBName)
		elseif nCurrentGuildA >= 0 and nCurrentGuildB >= 0 then
			local strGuildBNameA = GetGuildName( nCurrentGuildA )
			local strGuildBNameB = GetGuildName( nCurrentGuildB )
			msg = format("#Y�����ҡ�����ս����ѯ#W#r #r #RĿǰû�й���!\n#G��ǰ�ѷ���Թ�������ս����ʵ����ǿ���Ϊ:#c0000FF%s,%s!",strGuildBNameA,strGuildBNameB)
		end
	end 

    BeginQuestEvent(sceneId)
    AddQuestText(sceneId, msg);
    EndQuestEvent(sceneId)
    DispatchQuestEventList(sceneId,selfId,targetId)

    return 1
    	
end


----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x300815_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300815_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300815_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300815_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x300815_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x300815_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x300815_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x300815_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x300815_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
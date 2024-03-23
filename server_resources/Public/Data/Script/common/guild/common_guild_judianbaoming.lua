
--�������ս����

x300919_g_ScriptId              			= 300919
x300919_g_Leader_Index          			= 5
x300919_g_MissionName           			="�����ҡ��������ս����"
x300919_g_MissionName1          			="�����ҡ��������ս��ѯ"
x300919_g_NeedMoney             			= 50*1000
x300919_g_GuildLevel            			= 1
x300919_g_GuildMemberNum       				= 1
x300919_g_Laird_Signup                  	= 300     --����
x300919_g_Laird_WaitBattle              	= 301     --�����������ȴ��������ս
x300919_g_Laird_BeginBattle             	= 302     --��ʼ�������ս
x300919_g_Laird_EndBattle               	= 303     --�����������ս
x300919_g_Leader_Index                      =  5


----------------------------------------------------------------------------------------------
--ȡ����س�����Ϣ��װ����
----------------------------------------------------------------------------------------------
function x300919_GetLairdSceneCount(sceneId)
	return CallScriptFunction(300918,"GetLairdSceneCount",sceneId)
end

function x300919_GetLairdSceneInfo(sceneId,nIndex)
	return CallScriptFunction(300918,"GetLairdSceneInfo",sceneId,nIndex)
end

function x300919_GetLairdMapNameByID(sceneId,MapSignuped)

	if MapSignuped == nil then
		return "����"
	end
	
	local nLairdSceneCount = x300919_GetLairdSceneCount(sceneId)
	for i=1,nLairdSceneCount do
		local nRetNpcGUID,nRetLairdScene,strRetLairdSceneName,nRetLevel,nRetFlag0,nRetFlag1 = x300919_GetLairdSceneInfo(sceneId,i)
		if nRetLairdScene == MapSignuped then
			return strRetLairdSceneName
		end
	end
	
	return "����"	
end
											   
----------------------------------------------------------------------------------------------
--ȡ�õȼ����а����һ��
----------------------------------------------------------------------------------------------
function x300919_GetLastLevelFromLevelTopList(sceneId, selfId)
	
	local nWorldID = GetWorldID(sceneId,selfId)
	local nLevelTopListType = LEVEL_TOP_LIST_BK - 1
	local nLevelCount = GetToplistCount(nWorldID,nLevelTopListType)
	if nLevelCount <= 0 then
		return 0
	else
		local _,nLastLevel = GetToplistInfo(nWorldID,nLevelTopListType,nLevelCount-1) 
		return nLastLevel
	end
end

----------------------------------------------------------------------------------------------
--�����س��������Ƿ�ﵽ����Ҫ��
----------------------------------------------------------------------------------------------	
function x300919_CheckLairdSceneLevel(sceneId, selfId, nLevel )

	local nLastLevel = x300919_GetLastLevelFromLevelTopList(sceneId, selfId)
	if nLastLevel >= nLevel then
		return 1
	end
	
	return 0
	
end
											   
----------------------------------------------------------------------------------------------
--���NPC�Ƿ������
----------------------------------------------------------------------------------------------										   
function x300919_IsNpcEntrance( sceneId,nNpcGUID )

	local nLairdSceneCount = x300919_GetLairdSceneCount(sceneId)
	for i=1,nLairdSceneCount do
		local nRetNpcGUID,nRetLairdScene,strRetLairdSceneName,nRetLevel,nRetFlag0,nRetFlag1 = x300919_GetLairdSceneInfo(sceneId,i)
		if nRetNpcGUID == nNpcGUID then
			return 1
		end
	end
	
	
	return 0	
end


----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x300919_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_LAIRDGBATTLELITE ) == 0 then
        return
    end

    --�����
    local nGuildId = GetGuildID(sceneId,selfId )
    if nGuildId < 0 then
        return
    end
    
    --�������ѡ��
    --local nBattleStatus = CallScriptFunction(300918,"GetBattleState",sceneId)
	--if nBattleStatus == x300919_g_Laird_Signup then
		--if x300919_IsNpcEntrance(sceneId,GetMonsterGUID(sceneId,targetId)) == 1  then
			AddQuestNumText(sceneId,x300919_g_ScriptId,x300919_g_MissionName1,3,x300919_g_ScriptId);
		--end
	--end

    --����Ƿ��ǰ���

    --����Ƿ��й���
    local nHumanGUID = GetPlayerGUID( sceneId,selfId )
    local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
    if nKingGUID <= 0 or nHumanGUID == nKingGUID then
    	return    	
    end
    
    --����Ƿ�������
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_QINGLONG_LEADER) == 1 then
    	return
    end
    
    --����Ƿ�����ȸ
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_ZHUQUE_LEADER) == 1 then
    	return
    end
    
    --����Ƿ��ǹ���
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_KING) == 1 then
    	return
    end
    
    
	--�������ѡ��
	--if nBattleStatus == x300919_g_Laird_Signup then
		--if x300919_IsNpcEntrance(sceneId,GetMonsterGUID(sceneId,targetId)) == 1 then
    		AddQuestNumText(sceneId,x300919_g_ScriptId,x300919_g_MissionName,3);
    	--end
   -- end
    
end

----------------------------------------------------------------------------------------------
--Ĭ���¼�
----------------------------------------------------------------------------------------------
function x300919_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

	 local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= x300919_g_Leader_Index then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "����ʧ�ܣ��ܱ�Ǹ��ֻ�а�������Ȩ��ѯ�����롣");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
        return
    end

	local nNpcGUID = GetMonsterGUID(sceneId,targetId)

    if idExt == 0 then
    
    
    	--״̬���
    	local nBattleStatus = CallScriptFunction(300918,"GetBattleState",sceneId)
    	if nBattleStatus ~= x300919_g_Laird_Signup then
    		--�û����
    		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "����ʧ�ܣ��ܱ�Ǹ������ÿ������13��00~15��00֮�������������ս��");
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,targetId)
    		return
    	end
    	
    	--��NPC���
    	if x300919_IsNpcEntrance(sceneId, nNpcGUID ) == 0 then
    		return
    	end
		
    	--��ʾ����б�
    	local nLairdSceneCount = x300919_GetLairdSceneCount(sceneId)
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r \n#G�����Է����������ص�����:#W");
    	for i=1,nLairdSceneCount do
			local nRetNpcGUID,nRetLairdScene,strRetLairdSceneName,nRetLevel,nRetFlag0,nRetFlag1 = x300919_GetLairdSceneInfo(sceneId,i)
			if nRetNpcGUID == nNpcGUID and x300919_CheckLairdSceneLevel( sceneId, selfId,nRetLevel ) == 1 then	
				AddQuestNumText(sceneId,x300919_g_ScriptId,"����ء�"..strRetLairdSceneName,3,nRetFlag0);
			end
		end
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif idExt == x300919_g_ScriptId then
    
    
    	--��NPC���
    	if x300919_IsNpcEntrance( sceneId,nNpcGUID ) == 0 then
    		return
    	end
    	
    	--��ʾ����б�
    	local nLairdSceneCount = x300919_GetLairdSceneCount(sceneId)
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս��ѯ#W#r#G��ѡ�����а�ť��ѯ��Ӧ��ر������:#W");
    	for i=1,nLairdSceneCount do
			local nRetNpcGUID,nRetLairdScene,strRetLairdSceneName,nRetLevel,nRetFlag0,nRetFlag1 = x300919_GetLairdSceneInfo(sceneId,i)
			if nRetNpcGUID == nNpcGUID and x300919_CheckLairdSceneLevel(sceneId, selfId, nRetLevel ) == 1 then	
				AddQuestNumText(sceneId,x300919_g_ScriptId,"����ء�"..strRetLairdSceneName,3,nRetFlag1);
	
			end
		end
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    else
    	
    	--������
    	local nLairdSceneCount = x300919_GetLairdSceneCount(sceneId)
    	for i=1,nLairdSceneCount do
    	
			local nRetNpcGUID,nRetLairdScene,strRetLairdSceneName,nRetLevel,nRetFlag0,nRetFlag1 = x300919_GetLairdSceneInfo(sceneId,i)
    		
    		if nRetFlag0 == idExt then
    		
    			 --ս��û�п���
		        if x300919_CheckLairdSceneLevel(sceneId, selfId, nRetLevel ) ~= 1 then
		        	
		        	BeginQuestEvent(sceneId)
		            AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ��������սĿǰû�п��ţ�");
		            EndQuestEvent(sceneId)
		            DispatchQuestEventList(sceneId,selfId,targetId)
		            return
		        	
		        end
    			
    			--��ѯ���
		        GameBattleQuerySignupState( sceneId,selfId,2,nRetLairdScene )
		        SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,targetId)   
		        
		        break	
    			
    		elseif nRetFlag1 == idExt then
    		
    			 --ս��û�п���
		        if x300919_CheckLairdSceneLevel(sceneId, selfId, nRetLevel ) ~= 1 then
		        	
		        	BeginQuestEvent(sceneId)
		            AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ��������սĿǰû�п��ţ�");
		            EndQuestEvent(sceneId)
		            DispatchQuestEventList(sceneId,selfId,targetId)
		            return
		        	
		        end
    			
    			--��Բ�ѯ
    			GameBattleQueryMatchState(sceneId,selfId,2,nRetLairdScene)
    			SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,targetId)
    			break
    			
    		elseif nRetLairdScene == idExt then
    			
    			--�Ƿ��ǰ���
		        local pos = GetGuildOfficial(sceneId, selfId)
		        if pos ~= x300919_g_Leader_Index then
		            BeginQuestEvent(sceneId)
		            AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ��ܱ�Ǹ���������ǰ����޷������Ϊ���֮����");
		            EndQuestEvent(sceneId)
		            DispatchQuestEventList(sceneId,selfId,targetId)
		            return
		        end
		
		        local nGuildId = GetGuildID(sceneId,selfId )
		        local nLevel,nMemberNum,nExp = GetGuildSimpleData( nGuildId )
		
		        --���ȼ�������
		        if nLevel < x300919_g_GuildLevel then
		            BeginQuestEvent(sceneId)
		            AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ����ȼ����㣲����");
		            EndQuestEvent(sceneId)
		            DispatchQuestEventList(sceneId,selfId,targetId)
		            return
		        end
		
		        --����Ա�����Ƿ�����
		        if nMemberNum < x300919_g_GuildMemberNum then
		            BeginQuestEvent(sceneId)
		            AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ�����Ա����30�ˣ�");
		            EndQuestEvent(sceneId)
		            DispatchQuestEventList(sceneId,selfId,targetId)
		            return
		        end
		        
		        --ս��û�п���
		        if x300919_CheckLairdSceneLevel(sceneId, selfId, nRetLevel ) ~= 1 then
		        	
		        	BeginQuestEvent(sceneId)
		            AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ��������սĿǰû�п��ţ�");
		            EndQuestEvent(sceneId)
		            DispatchQuestEventList(sceneId,selfId,targetId)
		            return
		        	
		        end
		        
		        --�Ƿ�������
		        local nLairdMap1,nLairdMap2,nLairdMap3,nLairdMap4 = GetGuildLairdSceneId(nGuildId)
		        if nLairdMap1 > 0 then
		        	
		        	BeginQuestEvent(sceneId)
		            AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ��Ѿ��������ˣ��޷��ٴ����룡");
		            EndQuestEvent(sceneId)
		            DispatchQuestEventList(sceneId,selfId,targetId)
		            return
		        	
		        end
		
		        --���϶�ͨ������������
		        GameBattleExecuteSignup( sceneId,selfId, 2, idExt )
		        SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,targetId)
		        break
    		end
    	end
    	
    end

    return 1

end

----------------------------------------------------------------------------------------------
--��ѯ�������ս����״̬��Ӧ
----------------------------------------------------------------------------------------------
function x300919_OnQueryLairdBattleSignupState( sceneId,selfId,nResult,nLairdMapId,nGuildA,nGuildB,nHasLaird,nMapSignuped )
    
    local targetId = GetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID)
    if nResult == 0 then
    	--OK,��ѯ״̬�������������
    	
    elseif nResult == 300 then
    	
    	--�û����
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ��ܱ�Ǹ������ÿ������13��00~15��00֮�������������ս��");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
    elseif nResult == 301 then
    
    	--���û�б���
        x300919_LairdBattleSignup( sceneId,selfId,targetId,nLairdMapId,nGuildA,nGuildB,nHasLaird )
        
    elseif nResult == 302 then
    	
    	--�Ѿ�����
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t�ܱ�Ǹ�����Ѿ��ɹ�������һ����ص����ᣬĿǰ���������У��޷��ٴ������������ص����ᡣ");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
    elseif nResult == 303 then
    	
    	--û�а��
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ������а�����������ս��");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 304 then
    
    	--���ȼ�����
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ����ȼ�����2����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 305 then
    
    	--���ǰ���
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ������ǰ����ſ������룡");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 306 then
    	
    	--�����������
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ�����Ա����30�ˣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 307 then
    
    	--��ȸ�����,��������ȸ��
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ���ȸ��������ռ����أ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 308 then
    
    	--���������,������������
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ�������������ռ����أ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 309 then
    	
    	--���������,�����ǹ�����
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ�������������ռ����أ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
	elseif nResult == 310 then
    	
    	--���ʵ������
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ����ʵ�����㣡");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
	
	elseif nResult == 311 then
		
		--�����Ѿ�����
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ������Ѿ�������");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
	elseif nResult == 312 then
	
		--�Ѿ�������������ص�����
    	BeginQuestEvent(sceneId)
		local strMapSignedup = x300919_GetLairdMapNameByID(sceneId,nMapSignuped)
		AddQuestText(sceneId, format("#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ��Ѿ�������%s��ص�����",strMapSignedup));
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
	elseif nResult == 313 then
	
		--ȡ�ð����Ϣ
		local nGuidID = GetGuildID(sceneId,selfId)
		if nGuidID < 0 then
			return
		end
		
		--ȡ�ð�������Ϣ

		local nGuildLairdMapId = GetGuildLairdSceneId(nGuidID)
		
		local nLairdSceneCount = x300919_GetLairdSceneCount(sceneId)
    	BeginQuestEvent(sceneId)
    	for i=1,nLairdSceneCount do
			local nRetNpcGUID,nRetLairdScene,strRetLairdSceneName,nRetLevel,nRetFlag0,nRetFlag1 = x300919_GetLairdSceneInfo(sceneId,i)
			if nGuildLairdMapId == nRetLairdScene then	
				--�Ѿ�����ذ��
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, format("#Y�����ҡ��������ս����#W#r\t����%s�������޷������μ��������ս",strRetLairdSceneName));
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,targetId)
				break
			end
		end

		
    else
    
    	--δ֪����
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ�δ֪ԭ�򣬿����������ս�������Ѵ����ޣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    end

    return 1

end

----------------------------------------------------------------------------------------------
--��ս����
----------------------------------------------------------------------------------------------
function x300919_LairdBattleSignup( sceneId,selfId,targetId ,nLairdMapId,nGuildA, nGuildB,nHasLaird,nMapSignuped)

	
	SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,targetId)
    
    --�Ƿ��ǰ���
    local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= x300919_g_Leader_Index then
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t�ܱ�Ǹ���������ǰ����޷�������ս���֮����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		return 0
	end

    local nGuildId = GetGuildID(sceneId,selfId )
    local nLevel,nMemberNum,nExp = GetGuildSimpleData( nGuildId )

    --���ȼ�������
    if nLevel < x300919_g_GuildLevel then
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ����ȼ�����2����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		return 0
    end

    --����Ա�����Ƿ�����
    if nMemberNum < x300919_g_GuildMemberNum then
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ�����Ա����30�ˣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		return 0
    end

    --�Ƿ����������ս����ʱ��
    local nBattleStatus = CallScriptFunction(300918,"GetBattleState",sceneId)
	if nBattleStatus ~= x300919_g_Laird_Signup then
 		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ��ܱ�Ǹ������ÿ������13��00~15��00֮�������������ս��");
		EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,targetId)
		return 0
	end
	
	--�ָ����������ذ����д���
	local msg = ""
	local nCountryGuildId = CountryGetOfficerGUID(GetCurCountry(sceneId,selfId),1)
	if nHasLaird ~= 1 then

		
		--û����ذ������
		if nGuildA >= 0 and nGuildB >= 0 then
			
			--����Ѿ�������ս��
			local strGuildA = GetGuildName( nGuildA )
			local strGuildB = GetGuildName( nGuildB )
			msg = format("#Y�����ҡ��������ս����#W#r#R\t�Ѿ��а��Ը���ط������������룬��ȷ���Ըð�������ս��\n\t#G��ǰ�ѷ���Ը���ص��������벢��ʵ����ǿ���ֱ�Ϊ:#r#c0000FF%s#r%s",strGuildA,strGuildB)
			
		elseif nGuildA >= 0 and nGuildB < 0 then
			--���ֻ��һ����ս
			local strGuildA = GetGuildName( nGuildA )
			msg = format("#Y�����ҡ��������ս����#W#r#R\t�Ѿ��а��Ը���ط������������룬��ȷ���Ըð�������ս��\n\t#G��ǰ�ѷ���Ը���ص����Ტ��ʵ����ǿ���Ϊ:#r#c0000FF%s",strGuildA)
		else
			--���û������ս
			msg = "#Y�����ҡ��������ս����#W#r\t#G��ǰû��������ᷢ��Ը���ص�����!"
		end
		
	else
		--����ذ������
		if nGuildB >= 0 then
			--����Ѿ�������ս��
			
			local strGuildA = GetGuildName( nGuildA )
			local strGuildB = GetGuildName( nGuildB )
			msg = format("#Y�����ҡ��������ս����#W#r#R\tĿǰռ�ݸ���صİ����:%s����ȷ�����������ս��\n\t#G��ǰ�ѷ���Ը���ص����Ტ��ʵ����ǿ���Ϊ:#r#c0000FF%s",strGuildA,strGuildB)
			
		else
			--���û������ս
			msg = "#Y�����ҡ��������ս����#W#r#R\t�Ѿ��а��ӵ�жԸ���ص�ռ�죬��ȷ��Ҫ����Ը���ص���ս��\n\t#G��ǰû���κΰ�ᷢ��Ը���ص���ս!"
		end
	end

    BeginQuestEvent(sceneId)
    AddQuestText(sceneId, msg);
    AddQuestNumText(sceneId,x300919_g_ScriptId,"ȷ��..",3,nLairdMapId);
    EndQuestEvent(sceneId)
    DispatchQuestEventList(sceneId,selfId,targetId)

    return 1
end

function x300919_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300919_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--������
----------------------------------------------------------------------------------------------
function x300919_OnLairdBattleSignupResult( sceneId,selfId,nResult,nLiardMapId,nGuildA, nGuildB,nSignupCount,nHasLaird,nMapSignuped)

	local targetId = GetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID)
	
	if nResult == 0 then

		local strMsg = ""
		if nSignupCount > 0 then
        	strMsg = format("#Y�����ҡ��������ս����#W#r\t��ϲ�����ɹ����������ҡ��������ս��ĿǰΪֹ����%d����ᱨ���μӡ�",nSignupCount)
        	strMsg1= format("��ϲ�����ɹ������������ս��ĿǰΪֹ����%d����ᱨ���μӡ�",nSignupCount)
        else
        	strMsg = "#Y�����ҡ��������ս����#W#r\t��ϲ�����ɹ����������ҡ��������ս��Ŀǰ���˱���ỹû��������ᱨ���μӡ�"
        	strMsg1= "��ϲ�����ɹ������������ս��Ŀǰ���˱���ỹû��������ᱨ���μӡ�"
        end
	
    	local nGuildId = GetGuildID(sceneId,selfId )        
       
        LuaAllScenceM2Guild(sceneId,strMsg1,nGuildId,3,1)
        LuaAllScenceM2Guild(sceneId,strMsg1,nGuildId,2,1)
		LuaAllScenceM2Guild(sceneId,strMsg1,nGuildId,6,1)

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strMsg);
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 300 then
    	
    	--�û����
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ��ܱ�Ǹ������ÿ������13��00~15��00֮�������������ս��");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
    elseif nResult == 301 then
    
    	--���û�б���
        --x300919_LairdBattleSignup( sceneId,selfId,targetId,nLiardMapId,nGuildA,nGuildB,nHasLaird)
        
    elseif nResult == 302 then
    	
    	--�Ѿ�����
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t�ܱ�Ǹ�����Ѿ��ɹ�������һ����ص����ᣬĿǰ���������У��޷��ٴ������������ص����ᡣ");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
    elseif nResult == 303 then
    	
    	--û�а��
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ������а�����������ս���֮����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 304 then
    
    	--���ȼ�����
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ����ȼ�����2����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 305 then
    
    	--���ǰ���
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ������ǰ����ſ������룡");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 306 then
    	
    	--�����������
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ�����Ա����30�ˣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 307 then
    
    	--��ȸ�����,��������ȸ��
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ���������ȸ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 308 then
    
    	--���������,������������
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ������������");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 309 then
    	
    	--���������,�����ǹ�����
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ������ǹ����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
	elseif nResult == 310 then
	
		
		local nCountryId = GetSceneLairdCountryId(nLiardMapId)
		local nSelfCountryId = GetCurCountry(sceneId,selfId)
		if nCountryId >= 0 and nCountryId <= 3 then
			if nCountryId == nSelfCountryId then
				--���������,�����ǹ�����
		    	BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ�������������Ѿ�������ռ�죡");
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,targetId)
				return
			end
		end

		--���ʵ������
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ����ʵ�����㣡");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
			
	
	elseif nResult == 311 then
		
		--�����Ѿ�����
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ������Ѿ�������");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
	elseif nResult == 312 then
	
		--�Ѿ�������������ص�����
    	BeginQuestEvent(sceneId)
    	local strMapSignedup = x300919_GetLairdMapNameByID(sceneId,nMapSignuped)
		AddQuestText(sceneId, format("#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ��Ѿ�������%s��ص�����",strMapSignedup));
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
	elseif nResult == 313 then
	
		--ȡ�ð����Ϣ
		local nGuidID = GetGuildID(sceneId,selfId)
		if nGuidID < 0 then
			return
		end
		
		--ȡ�ð�������Ϣ
		local nGuildLairdMapId = GetGuildLairdSceneId(nGuidID)		
		local nLairdSceneCount = x300919_GetLairdSceneCount(sceneId)
    	BeginQuestEvent(sceneId)
    	for i=1,nLairdSceneCount do
			local nRetNpcGUID,nRetLairdScene,strRetLairdSceneName,nRetLevel,nRetFlag0,nRetFlag1 = x300919_GetLairdSceneInfo(sceneId,i)
			if nGuildLairdMapId == nRetLairdScene then	
				--�Ѿ�����ذ��
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, format("#Y�����ҡ��������ս����#W#r\t����%s�������޷������μ��������ս",strRetLairdSceneName));
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,targetId)
				break
			end
		end
		
    else
    
    	--δ֪����
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ��������ս����#W#r\t����ʧ�ܣ�δ֪ԭ�򣬿����������ս�������Ѵ����ޣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    end

    return 1

end


----------------------------------------------------------------------------------------------
--��ѯ���
----------------------------------------------------------------------------------------------
function x300919_OnQueryCurrentGuild(sceneId,selfId,nLairdMapId,nGuildA,nGuildB,nCount,nHasLaird,nMapSignuped)


	--��������
	local targetId = GetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID)
	local nNpcGUID = GetMonsterGUID(sceneId,targetId)
	local strLairdSceneName = ""
	local bFind = 0
	local nLairdSceneCount = x300919_GetLairdSceneCount(sceneId)
	for i=1,nLairdSceneCount do
		local nRetNpcGUID,nRetLairdScene,strRetLairdSceneName,nRetLevel,nRetFlag0,nRetFlag1 = x300919_GetLairdSceneInfo(sceneId,i)
		if nRetNpcGUID == nNpcGUID and nRetLairdScene == nLairdMapId then
			strLairdSceneName = strRetLairdSceneName
			bFind = 1
			break
		end
	end
	
	--û���ҵ�
	if bFind == 0 then
		return
	end
	
	--�ָ����������ذ����д���
	local msg = ""
	if nHasLaird ~= 1 then
		
		--û����ذ������
		if nGuildA >= 0 and nGuildB >= 0 then
			
			--����Ѿ�������ս��
			local strGuildA = GetGuildName( nGuildA )
			local strGuildB = GetGuildName( nGuildB )
			msg = format("#Y�����ҡ��������ս��ѯ#W#r#R\t#G��ǰ�ѷ���ԡ���ء�%s�����Ტ��ʵ����ǿ���ֱ�Ϊ:#r#c0000FF%s#r%s",strLairdSceneName,strGuildA,strGuildB)
			
		elseif nGuildA >= 0 and nGuildB < 0 then
			--���ֻ��һ����ս
			local strGuildA = GetGuildName( nGuildA )
			msg = format("#Y�����ҡ��������ս��ѯ#W#r#R\t#G��ǰ�ѷ���ԡ���ء�%s�����Ტ��ʵ����ǿ���Ϊ:#r#c0000FF%s",strLairdSceneName,strGuildA)
		else
			--���û������ս
			msg = format("#Y�����ҡ��������ս��ѯ#W#r\t#GĿǰû���κΰ�ᷢ��ԡ���ء�%s������!",strLairdSceneName)
		end
		
	else
		--����ذ������
		if nGuildB >= 0 then
			--����Ѿ�������ս��
			
			local strGuildA = GetGuildName( nGuildA )
			local strGuildB = GetGuildName( nGuildB )
			msg = format("#Y�����ҡ��������ս��ѯ#W#r#R\tĿǰռ�ݸ���صİ����:%s,#G��ǰ�ѷ���Ը���ص���ս����ʵ����ǿ���Ϊ:#r#c0000FF%s",strGuildA,strGuildB)
			
		else
			local strGuildA = GetGuildName( nGuildA )
			--���û������ս
			msg = format("#Y�����ҡ��������ս��ѯ#W#r#R\tĿǰռ�ݸ���صİ����:%s,û��������ᷢ��Ը���ص���ս!",strGuildA)
		end
	end

    BeginQuestEvent(sceneId)
    AddQuestText(sceneId, msg);
    EndQuestEvent(sceneId)
    DispatchQuestEventList(sceneId,selfId,targetId)

    return 1
    	
end

----------------------------------------------------------------------------------------------
--���������洦��
----------------------------------------------------------------------------------------------
function x300919_OnSignupInstead(sceneId,nLairdMapId,nGuildA,nGuildB)
	
	local strGuildB = GetGuildName(nGuildB)
	local msg = format("#R������������ս�ı�����%s��ᶥ����",strGuildB)  
            	
	LuaThisScenceM2Guild(sceneId,msg,nGuildA,3,1)
	LuaThisScenceM2Guild(sceneId,msg,nGuildA,2,1)
end

----------------------------------------------------------------------------------------------
--��Ԯ���뷴��
----------------------------------------------------------------------------------------------
function x300919_OnPlayerAidSignupQuery(sceneId,selfId,nRet)
	
	local msg = "δ֪����,��Ԯ����ʧ��"
	if nRet == 0 then
		--OK
		msg = "�Ѿ��ɹ���������."
	elseif nRet == 1 then
		--�������Ԯ�����߻���û�ҵ�
		msg = "���������Ԯ�����߻򲻴���."
	elseif nRet == 2 then
		--�������Ԯ����ͬ��
		msg = "���������Ԯ�����Ǳ������"
	elseif nRet == 3 then
		--�������Ԯ�ȼ�����
		msg = "���������Ԯ�ȼ�����"
	elseif nRet == 4 then
		--�������Ԯû�а��
		msg = "���������Ԯû�а��"
	elseif nRet == 5 then
		--�������Ԯ���ڰ���������߰����ͬ
		msg = "�ܱ�Ǹ���������뱾����Ա"
	elseif nRet == 6 then
		--�������Ԯֻ���ǹ���������ػ���
		msg = "��ֻ���������������ػ����Ա�μ��������ս"
	elseif nRet == 7 then
		--�������Ԯ������
		msg = "�������Ŀ������Ѿ��ɹ�������������"
	elseif nRet == 8 then
		--�������Ԯ�ѱ���İ������
		msg = "���������Ԯ�ѱ������İ������"
	elseif nRet == 9 then
		--��Ԯ��������
		msg = "��Ԯ�������������ܼ�������"
	elseif nRet == 10 then
		--��Ԯ���ڰ��Ҳ�����˾ݵ�ս��
		msg = "���������Ԯ���ڰ���ѱ����μ��������ս"
	elseif nRet == 11 then
		--������û�а��
		msg = "�ܱ�Ǹ����û�а�ᣬ���ܽ�������"
	elseif nRet == 12 then
		--�����߲��ǰ���
		msg = "�ܱ�Ǹ�������ǰ��������ܽ����������"
	elseif nRet == 13 then
		--���������ڰ��û�б����ݵ�ս
		msg = "�ܱ�Ǹ�����İ����δ�����μ��������ս"
	end
	
	
	Msg2Player(sceneId, selfId, msg, 8, 2)
	Msg2Player(sceneId, selfId, msg, 8, 3)
	
end


----------------------------------------------------------------------------------------------
--��Ԯ���뷴��
----------------------------------------------------------------------------------------------
function x300919_OnPlayerAidSignupExecute(sceneId,selfId,nRet)
	
	local msg = "δ֪����,��Ԯ����ʧ��"
	if nRet == 0 then
		--OK
		msg = "���ܳɹ�."
	elseif nRet == 1 then
		--�������Ԯ�����߻���û�ҵ�
		msg = "����ʧ��,�������Ԯ�����߻���û�ҵ�."
	elseif nRet == 2 then
		--�������Ԯ����ͬ��
		msg = "����ʧ��,��������ͬ�����"
	elseif nRet == 3 then
		--�������Ԯ�ȼ�����
		msg = "����ʧ��,�ȼ�����"
	elseif nRet == 4 then
		--�������Ԯû�а��
		msg = "����ʧ��,û�а��"
	elseif nRet == 5 then
		--�������Ԯ���ڰ���������߰����ͬ
		msg = "����ʧ��,��ԮΪ������Ա"
	elseif nRet == 6 then
		--�������Ԯֻ���ǹ���������ػ���
		msg = "����ʧ��,ֻ�й���������ػ���ĳ�Ա�ſ��Գ�Ϊ��Ԯ"
	elseif nRet == 7 then
		--�������Ԯ������
		msg = "����ʧ��,���Ѿ����ܸð�������"
	elseif nRet == 8 then
		--�������Ԯ�ѱ���İ������
		msg = "����ʧ��,���Ѿ���������������Ԯ���룬������ټ�����������"
	elseif nRet == 9 then
		--��Ԯ��������
		msg = "����ʧ��,�������İ����Ԯ������������"
	elseif nRet == 13 then
		--���������ڰ��û�б����ݵ�ս
		msg = "����ʧ��,�������İ��û�вμ��������ս"
	end
	
	
	Msg2Player(sceneId, selfId, msg, 8, 2)
	Msg2Player(sceneId, selfId, msg, 8, 3)
	
end

----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x300919_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300919_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300919_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300919_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x300919_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x300919_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x300919_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x300919_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x300919_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
--���ܣ����Ĵ���
--NPC�����Ĵ���ʹ��

--**********************************
--�������ȫ�ֱ���
x800021_g_newSceneID={ID1=50,ID2=150,ID3=250,ID4=350,}    --����ڳ���ID
x800021_g_PosX = {Pos1=176,Pos2=176,Pos3=78,Pos4=69,}
x800021_g_PosZ = {Pos1=179,Pos2=179,Pos3=76,Pos4=77,}
--x800021_g_OffsetX = 10
--x800021_g_OffsetZ = 10
--**********************************


--**********************************
--��������ȫ�ֱ���
x800021_g_newCountrySceneID ={ID1=51,ID2=151,ID3=251,ID4=351,}    --����ڳ���ID
x800021_g_CountryPosX = {Pos1=126,Pos2=126,Pos3=126,Pos4=126,}
x800021_g_CountryPosZ = {Pos1=184,Pos2=185,Pos3=62,Pos4=62,}
--x800021_g_CountryOffsetX = 5
--x800021_g_CountryOffsetZ = 5
--**********************************



---------------------------------------------------------------------------------
--������ں���
---------------------------------------------------------------------------------
function x800021_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�

end

---------------------------------------------------------------------------------
--�û�ͨ��UI�����л�����
--��CGMapInfoHandler�б�����
---------------------------------------------------------------------------------
function x800021_OnChangeSceneEvent(sceneId, selfId, index, Backhaul)

	local strText = ""
	local CanTrans = IsCashboxState(sceneId,selfId)
	if CanTrans == 1 then
		BeginQuestEvent(sceneId)
			strText = "#Y���ڻ��߻���״̬�У���������"
			AddQuestText(sceneId,strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

	--�õ�����ó�����Ҫ����С�ȼ�������ID��λ����Ϣ
	local MinUserLevel, targetSceneId, PosX,PosZ, needMoney, needItemID,SourceSceneId,SourcePosX,SourcePosZ = GetNewSceneInfoByIndex(sceneId,index)
	if SourceSceneId ~= sceneId then
		--���͵���ʼ�����뵱ǰ������ƥ��
		return
	end

	local selfPosX,selfPosZ = GetWorldPos(sceneId, selfId)
	if IsInDistByPoint(sceneId,selfPosX,selfPosZ,SourcePosX,SourcePosZ,7 ) ~= 1 then
		--λ�ô���
		return
	end

	PosX = PosX - 4 + random(1,7)
	PosZ = PosZ - 4 + random(1,7)
	local level = GetLevel(sceneId, selfId)

	--��鼶��
	if level < MinUserLevel then
	
		BeginQuestEvent(sceneId)
			strText = "#Y�ȼ�����#G"..MinUserLevel.."#Y�����޷�ǰ���õ�"
			AddQuestText(sceneId,strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		
		return
	end
		
	--��̯ģʽ
	if IsInStall(sceneId, selfId) ~= 0 then
		return
	end
	
	--�������
	local life=IsCharacterLiving( sceneId,selfId)
	if life == 0 then
		return
	end
	
	--���¿�ʼ���������
	if GetTeamId( sceneId, selfId) > 0  then
	
		--�ж���������������Ƕ������ģʽ
		if IsTeamFollow(sceneId, selfId) ~= 1 then
			
			local bCostMoney = 0;
			local bCostItem = 0;
			if( needMoney > 0 ) then
				if( IsEnoughMoney( sceneId, selfId, needMoney ) == 0 ) then
					BeginQuestEvent(sceneId)
						strText = "#Y���Ľ�Ǯ���㣬�޷�ǰ���õ�"
						AddQuestText(sceneId,strText);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					return 0;
				else
					bCostMoney = 1;
				end
			end
			
			if( needItemID >= 0 ) then
				if( GetItemCount( sceneId, selfId, needItemID ) <= 0 ) then
					BeginQuestEvent(sceneId)
						strText = "#Y������û�д�����Ʒ���޷�ǰ���õ�"
						AddQuestText(sceneId,strText);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					return 0;
				else
					bCostItem = 1;
				end
			end
			
			--��Ǯ
			if( bCostMoney == 1 ) then
				if( SpendMoney( sceneId, selfId, needMoney,302 ) == -1 ) then
					BeginQuestEvent(sceneId)
						strText = "#Y���Ľ�Ǯ���㣬�޷�ǰ���õ�"
						AddQuestText(sceneId,strText);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					return 0;
				end
			end
			
			--����Ʒ
			if( bCostItem == 1 ) then
				if( DelItem(sceneId, selfId, needItemID, 1) == 0 ) then
					BeginQuestEvent(sceneId)
						strText = "#Y������û�д�����Ʒ���޷�ǰ���õ�"
						AddQuestText(sceneId,strText);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					return 0;
				end
			end
			
			--����
			CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferFunc",sceneId,selfId,targetSceneId,PosX,PosZ)	
		else
		
			--����Ǹ���ģʽ�������Ƕӳ�
			if IsTeamLeader(sceneId,selfId)==1 then
				
				local num=GetFollowedMembersCount( sceneId, selfId)
				local mems = {}
				local j = 0
				for	i=0,num-1 do
					mems[i] = GetFollowedMember(sceneId, selfId, i)
					if mems[i] == -1 then
						return
					else
						local memslevel = GetLevel(sceneId, mems[i])
						if memslevel < MinUserLevel then
							j = 1
						end
					end
				end	
				
				if j == 0 then
					--�����˶���������������
					CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferFunc",sceneId,selfId,targetSceneId,PosX,PosZ)
				else
					for i=0,num-1 do
						BeginQuestEvent(sceneId)
							strText = "#Y�ж����Ա�ȼ�����#G"..MinUserLevel.."#Y�����޷�ǰ���õ�"
							AddQuestText(sceneId,strText);
						EndQuestEvent(sceneId)
						DispatchQuestTips(sceneId,mems[i])
					end
				end	
			end	
		end						
	else
		--û�ж���Ĵ���
		local bCostMoney = 0;
		local bCostItem = 0;
		if( needMoney > 0 ) then
			if( IsEnoughMoney( sceneId, selfId, needMoney ) == 0 ) then
				BeginQuestEvent(sceneId)
					strText = "#Y���Ľ�Ǯ���㣬�޷�ǰ���õ�"
					AddQuestText(sceneId,strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0;
			else
				bCostMoney = 1;
			end
		end
		
		if( needItemID >= 0 ) then
			if( GetItemCount( sceneId, selfId, needItemID ) <= 0 ) then
				BeginQuestEvent(sceneId)
					strText = "#Y������û�д�����Ʒ���޷�ǰ���õ�"
					AddQuestText(sceneId,strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0;
			else
				bCostItem = 1;
			end
		end
		
		--��Ǯ
		if( bCostMoney == 1 ) then
			if( SpendMoney( sceneId, selfId, needMoney,302 ) == -1 ) then
				BeginQuestEvent(sceneId)
					strText = "#Y���Ľ�Ǯ���㣬�޷�ǰ���õ�"
					AddQuestText(sceneId,strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0;
			end
		end
		
		--����Ʒ
		if( bCostItem == 1 ) then
			if( DelItem(sceneId, selfId, needItemID, 1) == 0 ) then
				BeginQuestEvent(sceneId)
					strText = "#Y������û�д�����Ʒ���޷�ǰ���õ�"
					AddQuestText(sceneId,strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0;
			end
		end
		
		--ִ�д���
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferFunc",sceneId,selfId,targetSceneId,PosX,PosZ)
	end

end


---------------------------------------------------------------------------------
--�о��¼�
---------------------------------------------------------------------------------
function x800021_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

end


---------------------------------------------------------------------------------
--��������¼�
---------------------------------------------------------------------------------
function x800021_OnGuildConvoyChangeScene(sceneId,selfId)

	--����ڼ��������Ա�����
	if sceneId == PK_PUNISH_PRISON_SCENE_ID then
		BeginQuestEvent(sceneId)
		local strText = "�����ﻹ����ʵ,����,û�š�"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
	end

	local country = GetCurCountry(sceneId,selfId)--0.1.2.3

	local Map_ID = x800021_g_newSceneID.ID1

	local offsetX = random(1,5)
	local PosX = 0
	local PosZ = 0

	if country == 0 then--?����?
		Map_ID = x800021_g_newSceneID.ID1
		PosX = x800021_g_PosX.Pos1 + offsetX
		PosZ = x800021_g_PosZ.Pos1 + offsetX
	end

	if country == 1 then--��3��e
		Map_ID = x800021_g_newSceneID.ID2
		PosX = x800021_g_PosX.Pos2 + offsetX
		PosZ = x800021_g_PosZ.Pos2 + offsetX
	end

	if country == 2 then--����??
		Map_ID = x800021_g_newSceneID.ID3
		PosX = x800021_g_PosX.Pos3 + offsetX
		PosZ = x800021_g_PosZ.Pos3 + offsetX
	end

	if country == 3 then--???��
		Map_ID = x800021_g_newSceneID.ID4
		PosX = x800021_g_PosX.Pos4 + offsetX
		PosZ = x800021_g_PosZ.Pos4 + offsetX
	end
	
	--��������ս�ڼ�
	if sceneId == 39 then
	    if IsHaveSpecificImpact(sceneId, selfId, 7537 ) ~= 0 or IsHaveSpecificImpact(sceneId, selfId, 7536  ) ~= 0 then
	        BeginQuestEvent(sceneId)
			AddQuestText( sceneId, "�ڱ�������ս�ڼ䣬���ܴ���" )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
	    end
		return		
	end
	
	if sceneId == Map_ID then
		SetPos( sceneId , selfId , PosX , PosZ )

	else
	
		--����Ƿ���Դ���
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,Map_ID) == 0 then
			return
		end
		
        -- ������������������ֹ������
        if sceneId == 14 then
            SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_FORBID_RIDE, 0)
        end
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,Map_ID) == 0 then
			return
		end
        NewWorld( sceneId , selfId , Map_ID , PosX , PosZ, 8000210 )
	end

    -- ���ӻ�Ծ��
    local id = GetGuildID( sceneId, selfId)
    if id ~= -1 then
        AddGuildActivity( sceneId, selfId, GetGuildCacheFreeParam( id, GD_GUILD_ACTIVITY_PARAM7) )
    end
end

---------------------------------------------------------------------------------
--�������
---------------------------------------------------------------------------------
function x800021_OnGuildConvokeChangeScene( sceneId,selfId, newSceneId, posX, posZ )
	
	--��ʼ����
	if sceneId == PK_PUNISH_PRISON_SCENE_ID then
		BeginQuestEvent(sceneId)
		local strText = "�����У����ܴ���"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return		
	end
	
	--��������ս�ڼ�
	if sceneId == 39 then
	    if IsHaveSpecificImpact(sceneId, selfId, 7537 ) ~= 0 or IsHaveSpecificImpact(sceneId, selfId, 7536  ) ~= 0 then
	        BeginQuestEvent(sceneId)
			AddQuestText( sceneId, "�ڱ�������ս�ڼ䣬���ܴ���" )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
	    end
		return		
	end
	
	--�������ݣ�ֻ��60�����ϴ���
	if newSceneId == 50 or newSceneId == 150 or newSceneId == 250 or newSceneId == 350 or 
	   newSceneId == 51 or newSceneId == 151 or newSceneId == 251 or newSceneId == 351 or 
	   newSceneId == 86 or newSceneId == 186 or newSceneId == 286 or newSceneId == 386 or 
	   newSceneId == 2 or newSceneId == 3 or newSceneId == 4 or newSceneId == 5 then 
		if GetLevel(sceneId,selfId) < 40 then
			BeginQuestEvent(sceneId)
			local strText = "ֻ��40�����ϣ����ܴ��͵�Ŀ�ĵ�"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 6 then
		if GetLevel(sceneId,selfId) < 40 then
			BeginQuestEvent(sceneId)
			local strText = "ֻ��40�����ϣ����ܴ��͵����ݳ�"  
			AddQuestText( sceneId, strText )                  
			EndQuestEvent( sceneId )                          
			DispatchQuestTips( sceneId, selfId )              
			return				                              
		end                                                   
	end                                                       
	                                                          
	if newSceneId == 7 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                          
			local strText = "ֻ��40�����ϣ����ܴ��͵�����"    
			AddQuestText( sceneId, strText )                  
			EndQuestEvent( sceneId )                          
			DispatchQuestTips( sceneId, selfId )              
			return				                              
		end                                                   
	end                                                       
	                                                          
	if newSceneId == 8 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "ֻ��40�����ϣ����ܴ��͵�������ɽ"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 9 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "ֻ��40�����ϣ����ܴ��͵���Ҷ��"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 10 or newSceneId == 11 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "ֻ��40�����ϣ����ܴ��͵���ɳĮ���������"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 13 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "ֻ��40�����ϣ����ܴ��͵��͸��"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 16 or newSceneId == 17 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "ֻ��40�����ϣ����ܴ��͵���˹��ԭ��Ī˹�ƹ���"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 18 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "ֻ��40�����ϣ����ܴ��͵��͸��"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 19 or newSceneId == 20 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "ֻ��40�����ϣ����ܴ��͵�����������������"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 21 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "ֻ��40�����ϣ����ܴ��͵���ʥ����۹�"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 22 or newSceneId == 23 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "ֻ��40�����ϣ����ܴ��͵���ռͥ�۹������ʿ��"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 24 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "ֻ��40�����ϣ����ܴ��͵�Ү·����"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 25 or newSceneId == 26 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "ֻ��40�����ϣ����ܴ��͵����ΰ뵺�����"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 27 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "ֻ��40�����ϣ����ܴ��͵�Ү·����"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 29 or newSceneId == 30 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "ֻ��40�����ϣ����ܴ��͵����ݵ���Դ���"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 31 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "ֻ��40�����ϣ����ܴ��͵����"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 32 or newSceneId == 33 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "ֻ��40�����ϣ����ܴ��͵�ӡ�Ⱥӻ�������"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 34 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "ֻ��40�����ϣ����ܴ��͵�צ�۵�"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 35 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "ֻ��40�����ϣ����ܴ��͵����Ŵ���"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if sceneId == newSceneId then
		SetPos( sceneId , selfId , posX , posZ )
	else
		
		--����Ƿ���Դ���
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
			return
		end
		NewWorld( sceneId , selfId , newSceneId , posX , posZ, 8000211 )
	end

    -- ���ӻ�Ծ��
    local id = GetGuildID( sceneId, selfId)
    if id ~= -1 then
        AddGuildActivity( sceneId, selfId, GetGuildCacheFreeParam( id, GD_GUILD_ACTIVITY_PARAM7) )
    end

end

---------------------------------------------------------------------------------
--���������¼�
---------------------------------------------------------------------------------
function x800021_OnCountryChangeScene(sceneId,selfId)

	--����ڼ��������Ա�����
	if sceneId == PK_PUNISH_PRISON_SCENE_ID then
		BeginQuestEvent(sceneId)
		local strText = "�����ﻹ����ʵ,����,û�š�"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
	end
	
	--����ڸ�����
	local sceneType = GetSceneType(sceneId)
	if sceneType==1 then
		BeginQuestEvent(sceneId)
		local strText = "�����У�������Ӧ���������¼���"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
	end
	
	--�Ƿ������ֳ������ڱ���״̬
	IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId, 7536  )
    if IsHaveFlag ~= 0 then
        BeginQuestEvent(sceneId)
		local strText = "�ڱ�������ս�ڼ䣬������Ӧ���������¼���"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
    end
    
    IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId, 7537 )
    if IsHaveFlag ~= 0 then
        BeginQuestEvent(sceneId)
		local strText = "�ڱ�������ս�ڼ䣬������Ӧ���������¼���"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
    end
	

	--�ж��Ƿ������
		if GetLevel(sceneId, selfId) >= 40 then
			GetCountryQuestData(sceneId,selfId,CD_INDEX_DESTROY_ISSUE_TIME, CHUANSONG_SCENEMAP_SCRIPT,-1,"OnReturn1")
		else
			BeginQuestEvent(sceneId)
			local strText = "�ܱ�Ǹ�����ĵȼ�����40�������ܱ����͵Ĵ󽫾���ߡ�"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
		end

end

---------------------------------------------------------------------------------
--OnReturn1
---------------------------------------------------------------------------------
function x800021_OnReturn1(sceneId, selfId,MissionData,MissionId)
	local CurDaytime = GetDayTime()
	if MissionData == CurDaytime then
		GetCountryQuestData(sceneId,selfId,CD_INDEX_DESTROY_ISSUE_COUNT, CHUANSONG_SCENEMAP_SCRIPT,-1,"OnReturn2")
	end
end

---------------------------------------------------------------------------------
--OnReturn2
---------------------------------------------------------------------------------
function x800021_OnReturn2(sceneId, selfId,MissionData,MissionId)
	if MissionData > 10 then
		return
	end
	GetCountryQuestData(sceneId,selfId,CD_INDEX_DESTROY_ISSUE_SCENE, CHUANSONG_SCENEMAP_SCRIPT,-1,"OnReturn3")
end

---------------------------------------------------------------------------------
--OnReturn3
---------------------------------------------------------------------------------
function x800021_OnReturn3(sceneId, selfId,MissionData,MissionId)
	if MissionData < 0 then
		return
	end

	local country = GetCurCountry(sceneId,selfId)

	local offsetX = random(1,5)
	local offsetZ = random(1,5)

	local BasePosX = 0
	local BasePosZ = 0
	local NewSceneID = MissionData

	if NewSceneID == 51 then
		BasePosX = x800021_g_CountryPosX.Pos1
		BasePosZ = x800021_g_CountryPosZ.Pos1
	elseif NewSceneID == 151 then
		BasePosX = x800021_g_CountryPosX.Pos2
		BasePosZ = x800021_g_CountryPosZ.Pos2
	elseif NewSceneID == 251 then
		BasePosX = x800021_g_CountryPosX.Pos3
		BasePosZ = x800021_g_CountryPosZ.Pos3
	else
		BasePosX = x800021_g_CountryPosX.Pos4
		BasePosZ = x800021_g_CountryPosZ.Pos4
	end

	local PosX = BasePosX + offsetX
	local PosZ = BasePosZ + offsetZ

	if sceneId == NewSceneID then
		SetPos(sceneId, selfId,PosX,PosZ)
	else
        -- ������������������ֹ������
        if sceneId == 14 then
            SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_FORBID_RIDE, 0)
        end
        
        --����Ƿ���Դ���
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,NewSceneID) == 0 then
			return
		end
		NewWorld(sceneId, selfId, NewSceneID,PosX ,PosZ, 8000212 )
	end
end


---------------------------------------------------------------------------------
--�����Ҵ���״̬
---------------------------------------------------------------------------------
function x800021_BattleTransCheckPlayerState( sceneId,selfId )

    local state = IsPlayerStateNormal(sceneId,selfId )
    if state == 0 then
        return 1,"״̬�쳣"
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_MENTALGAME )
    if state == 1 then
        return 1,"���ڴ���״̬�����ܽ���ս��"
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_STALL )
    if state == 1 then
        return 1,"���ڰ�̯״̬�����ܽ���ս��"
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_DIE )
    if state == 1 then
        return 1,"��������״̬�����ܽ���ս��"
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_CRASHBOX )
    if state == 1 then
        return 1,"��������״̬�����ܽ���ս��"
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_AUTOPLAY )
    if state == 1 then
        ErrorMsg = "���ڹһ�״̬�����ܽ���ս��"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_SUBTRAIN )
    if state == 1 then
        return 1,"���ڴ���״̬�����ܽ���ս��"
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_BUS )
    if state == 1 then
        return 1,"����BUS״̬�����ܽ���ս��"
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_PKMODE )
    if state == 1 then
        return 1,"PKֵ���߻��ڿ�ģʽ�����ܽ���ս��"
    end
    
    local IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId, 7702 )
    if IsHaveFlag ~= 0 then
        return 1, "�ڶ���״̬�£����ܽ���ս��"
    end
    
    if IsHideName(sceneId, selfId) > 0 then
    	return 1,"����״̬��,���ܽ���ս��"
    end
    
    if sceneId == PK_PUNISH_PRISON_SCENE_ID then
    	return 1,"�ڼ�������ܽ���ս��"
    end
    
    IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId, 7536  )
    if IsHaveFlag ~= 0 then
        return 1, "�ڱ�������ս�ڼ䣬���ܽ���ս��"
    end
    
    IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId, 7537 )
    if IsHaveFlag ~= 0 then
        return 1, "�ڱ�������ս�ڼ䣬���ܽ���ս��"
    end

    return 0

end

---------------------------------------------------------------------------------
--����������ս��
---------------------------------------------------------------------------------
function x800021_AskEnterKingBattle( sceneId,selfId )

    --���״̬
    local state,msg = x800021_BattleTransCheckPlayerState( sceneId,selfId )
    if state == 1 then
        
        BeginQuestEvent(sceneId)
        AddQuestText( sceneId, msg );
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return
    end

    --�������ս��
    RequestEnterKingBattleScene(sceneId, selfId)
end

---------------------------------------------------------------------------------
--����������籭ս��
---------------------------------------------------------------------------------
function x800021_AskEnterWorldCup( sceneId,selfId)
    local nGuildId = GetGuildID( sceneId, selfId)
    if nGuildId < 0 or nGuildId > 1024 then
        if targetId ~= 0 then
            BeginQuestEvent( sceneId)
                AddQuestText( sceneId, "#Y"..x300615_g_Name)
                AddQuestText( sceneId, "����δ�����κΰ�ᣡ���ܽ���ս����" )
            EndQuestEvent()
            DispatchQuestEventList( sceneId, selfId, targetId)
            return
        end
    end

    --���״̬
    local state,msg = x800021_BattleTransCheckPlayerState( sceneId,selfId )
    if state == 1 then
        
        BeginQuestEvent(sceneId)
        AddQuestText( sceneId, msg );
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return
    end

    GuildContendAskEnter( sceneId, selfId)
end

---------------------------------------------------------------------------------
--GLserver����������籭ս��
---------------------------------------------------------------------------------
function x800021_OnEnterWorldCup( sceneId, selfId, targetSceneId)
    GetGuildQuestData( sceneId, selfId, GD_GUILD_INDEX_CONTEND_STATE, 800021, targetSceneId, "EnterWorldCup" )
end

--����������ڰ�����籭״̬����Ҵ���ս��
function x800021_EnterWorldCup( sceneId, selfId, MissionData, MissionId, targetId)

    if MissionData == STATE_GUILD_WORLDCUP_END then
        Msg2Player( sceneId, selfId, "�����Ѿ��������㲻���ٽ���ս���ˡ�", 8, 2)
        Msg2Player( sceneId, selfId, "�����Ѿ��������㲻���ٽ���ս����", 8, 3)
        return
    end
    
    --����Ƿ���Դ���
	if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,MissionId) == 0 then
		return
	end

    local nCurX,nCurZ = GetWorldPos( sceneId, selfId)
    SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_SCENE_PRE, sceneId)
    SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_POSX_PRE, nCurX)
    SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_POSZ_PRE, nCurZ)
    SetPlayerRuntimeData( sceneId, selfId, RD_BATTLE_SCENE_KICK_DOWN, 0)

    SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_GUILDBATTLEFIELDSCENE, 1)
	if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,MissionId) == 0 then
		return
	end
    NewWorld( sceneId, selfId, MissionId, 50, 50, 8000213)
end

---------------------------------------------------------------------------------
--pvp2v2ս������
---------------------------------------------------------------------------------
function x800021_OnPVP2v2BattleChangeScene( sceneId,selfId,targetSceneId )
	
	--��ʼ����
	if sceneId ~= targetSceneId then
		
		--���״̬
        local state,msg = x800021_BattleTransCheckPlayerState( sceneId,selfId )
        if state == 1 then
            
            BeginQuestEvent(sceneId)
            AddQuestText( sceneId, msg );
            EndQuestEvent(sceneId)
            DispatchQuestTips(sceneId,selfId)
            return
        end
        
        --����Ƿ���Դ���
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,targetSceneId) == 0 then
			return
		end
		
		--��¼һ��RuntimeData
        local nCurX,nCurZ = GetWorldPos( sceneId,selfId )
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_SCENE_PRE,sceneId + 1)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSX_PRE,nCurX)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSZ_PRE,nCurZ)
		SetPlayerRuntimeData(sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ,0)
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,targetSceneId) == 0 then
			return
		end
		NewWorld(sceneId, selfId, targetSceneId, 100, 100, 8000214);		
		
		--�ټ���־
		local name = GetName(sceneId,selfId)
	    local strMsg = format("P2BL:<Info>x800021_OnPVP2v2BattleChangeScene sceneId = %d name=%s targetSceneId=%d", sceneId, name, targetSceneId  )
	    WriteLog( 1, strMsg ) 
	end
end

---------------------------------------------------------------------------------
--pvp2v2ս�����ʹ�����
---------------------------------------------------------------------------------
function x800021_OnPVP2v2BattleTransError( sceneId,selfId,nErrorCode )
	
	local str = nil
	if nErrorCode == 1 then
		str = "�ܱ�Ǹ��˫��ս����û�п�ʼ��"
	elseif nErrorCode == 2 then
		str = "�ܱ�Ǹ����û�б����μ�˫��ս����"
	elseif nErrorCode == 3 then
		str = "�ܱ�Ǹ��û��Ϊ���Ķ����ҵ����ʵĶ��֣�"
	elseif nErrorCode == 4 then
		str = "�ܱ�Ǹ��˫��ս���Ѿ�������"
	elseif nErrorCode == 5 then
		str = "�ܱ�Ǹ��˫��ս���������Ѿ����ˣ����Ժ����ԡ�"
	elseif nErrorCode == 6 then
		str = "�ܱ�Ǹ��˫��ս���ѹرգ�"
	elseif nErrorCode == 7 then
		str = "�ܱ�Ǹ����ʱ�޷�����˫��ս��������"
	end
	
	if str ~= nil then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
    end
	
end



---------------------------------------------------------------------------------
--pvp6v6ս������
---------------------------------------------------------------------------------
function x800021_OnPVP6v6BattleChangeScene( sceneId,selfId,targetSceneId )
	
	--��ʼ����
	if sceneId ~= targetSceneId then
		
		--���״̬
        local state,msg = x800021_BattleTransCheckPlayerState( sceneId,selfId )
        if state == 1 then
            
            BeginQuestEvent(sceneId)
            AddQuestText( sceneId, msg );
            EndQuestEvent(sceneId)
            DispatchQuestTips(sceneId,selfId)
            return
        end
        
        --����Ƿ���Դ���
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,targetSceneId) == 0 then
			return
		end
		
		--��¼һ��RuntimeData
        local nCurX,nCurZ = GetWorldPos( sceneId,selfId )
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_SCENE_PRE,sceneId + 1)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSX_PRE,nCurX)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSZ_PRE,nCurZ)
		SetPlayerRuntimeData(sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ,0)
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,targetSceneId) == 0 then
			return
		end
		NewWorld(sceneId, selfId, targetSceneId, 100, 100, 8000214);		
		
		--�ټ���־
		local name = GetName(sceneId,selfId)
	    local strMsg = format("P2BL:<Info>x800021_OnPVP6v6BattleChangeScene sceneId = %d name=%s targetSceneId=%d", sceneId, name, targetSceneId  )
	    WriteLog( 1, strMsg ) 	
	end
end

---------------------------------------------------------------------------------
--pvp6v6ս�����ʹ�����
---------------------------------------------------------------------------------
function x800021_OnPVP6v6BattleTransError( sceneId,selfId,nErrorCode )
	
	local str = nil
	if nErrorCode == 1 then
		str = "�ܱ�Ǹ�����ս����û�п�ʼ��"
	elseif nErrorCode == 2 then
		str = "�ܱ�Ǹ����û�б����μ����ս����"
	elseif nErrorCode == 3 then
		str = "�ܱ�Ǹ��û��Ϊ���Ķ����ҵ����ʵĶ��֣�"
	elseif nErrorCode == 4 then
		str = "�ܱ�Ǹ�����ս���Ѿ�������"
	elseif nErrorCode == 5 then
		str = "�ܱ�Ǹ�����ս���������Ѿ����ˣ����Ժ����ԡ�"
	elseif nErrorCode == 6 then
		str = "�ܱ�Ǹ�����ս���ѹرգ�"
	elseif nErrorCode == 7 then
		str = "�ܱ�Ǹ����ʱ�޷��������ս����"
	end
	
	if str ~= nil then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
    end
	
end

---------------------------------------------------------------------------------
--����ս����ش��ͽű�
---------------------------------------------------------------------------------
function x800021_OnKingBattleChangeScene( sceneId,selfId,newSceneID,Flag )
    

    --����ڼ��������Ա�����
	if sceneId == PK_PUNISH_PRISON_SCENE_ID then
		BeginQuestEvent(sceneId)
		local strText = "�����ﻹ����ʵ,����,û�š�"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
	end

    local PosX = 100
    local PosZ = 100

			
    if sceneId == newSceneID then
			
			if Flag == 0 then
		    SetPos( sceneId , selfId , 77 , 174 )
			else
            SetPos( sceneId , selfId , 213,54 )
			end
		else
			
			--���״̬
			local state,msg = x800021_BattleTransCheckPlayerState( sceneId,selfId )
			if state == 1 then
				
				BeginQuestEvent(sceneId)
				AddQuestText( sceneId, msg );
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return
			end
			
			--����Ƿ���Դ���
			if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneID) == 0 then
				return
			end

			--��¼һ��RuntimeData
			local nCurX,nCurZ = GetWorldPos( sceneId,selfId )
			SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_SCENE_PRE,sceneId + 1)
			SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSX_PRE,nCurX)
			SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSZ_PRE,nCurZ)
			SetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG,1)
			if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneID) == 0 then
				return
			end
			NewWorld( sceneId , selfId , newSceneID , PosX , PosZ,8000215 )
	end
end

---------------------------------------------------------------------------------
--�������ս������˵��
---------------------------------------------------------------------------------
function x800021_OnKingBattleTransError( sceneId,selfId,nErrorId )
    
    
    local str = nil
    if nErrorId == 0 then        
        str = "ֻ�вμӰ��֮����ܽ��룡"
    elseif nErrorId == 1 then
        str = "���İ��û�б�����"
    elseif nErrorId == 2 then
        str = "����ս����û������ʱ�䣡"
    elseif nErrorId == 3 then
        str = "����ս���Ѿ��ر���ڣ����������ӣ�"
    elseif nErrorId == 4 then
        str = "Ŀǰû�й���ս����ʼ"
    elseif nErrorId == 5 then
        str = "ս����������"
    elseif nErrorId == 6 then
        str ="���Ѿ������ս���������ظ����룡"
    elseif nErrorId == 7 then
    	str ="ֻ��һ������,�����Ѿ�����,ս���ر�"
    else
        str ="δ֪���󣬲��ܽ��룡"
    end
    
    if str ~= nil then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
    end

end

---------------------------------------------------------------------------------
--���ս�����¼�
---------------------------------------------------------------------------------
function x800021_OnGuildBattleChangeScene(sceneId,selfId,newSceneID,Flag)

	--����ڼ��������Ա�����
	if sceneId == PK_PUNISH_PRISON_SCENE_ID then
		BeginQuestEvent(sceneId)
		local strText = "�����ﻹ����ʵ,����,û�š�"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
	end

    --����λ��
	local BasePosX = 0
	local BasePosZ = 0
    if Flag == 0 then
        BasePosX = 234
        BasePosZ = 126
    elseif Flag == 1 then
        BasePosX = 21
        BasePosZ = 126
    end


    --�������ݲ���
	local PosX = BasePosX 
	local PosZ = BasePosZ 

    if sceneId == newSceneID then
    	
        ClearRageRecoverTick(sceneId, selfId)
	    RestoreHp(sceneId, selfId,100)
	    RestoreRage(sceneId, selfId,100)
	    ClearMutexState(sceneId, selfId, 6)
	    SendReliveResult(sceneId, selfId,1)	
	
		SetPos( sceneId , selfId , PosX , PosZ )
	else
        
        --���״̬
        local state,msg = x800021_BattleTransCheckPlayerState( sceneId,selfId )
        if state == 1 then
            
            BeginQuestEvent(sceneId)
            AddQuestText( sceneId, msg );
            EndQuestEvent(sceneId)
            DispatchQuestTips(sceneId,selfId)
            return
        end
        
        --����Ƿ���Դ���
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneID) == 0 then
			return
		end

        --��¼һ��RuntimeData
        local nCurX,nCurZ = GetWorldPos( sceneId,selfId )
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_SCENE_PRE,sceneId + 1)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSX_PRE,nCurX)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSZ_PRE,nCurZ)

        --������ս����ʱ��¼һ�µ�ǰ���ڵĳ�����λ��
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneID) == 0 then
			return
		end
		NewWorld( sceneId , selfId , newSceneID , PosX , PosZ, 8000216 )
	end

end

---------------------------------------------------------------------------------
--������ս�쳣
---------------------------------------------------------------------------------
function x800021_OnGuildBattleTransError( sceneId,selfId,nError )
    
    local str = nil
    if nError == 1 then
		str = "�ܱ�Ǹ�����û�п�ʼ��"
    elseif nError == 2 then
		str = "�ܱ�Ǹ����û�а�ᣡ"
    elseif nError == 3 then
		str = "�ܱ�Ǹ�������ڵİ�ỹû�б�����"
    elseif nError == 4 then
		str = "�ܱ�Ǹ�����ս��û�п�ʼ��"
    elseif nError == 5 then
		str = "�ܱ�Ǹ�������ڵİ���ڴ˴ΰ��ս���ֿգ�"
    elseif nError == 6 then
		str = "�ܱ�Ǹ�����İ����Ϣ���䲻��ȷ��"
    elseif nError == 7 then
		str = "�ܱ�Ǹ�������ǰ�����"
    elseif nError == 8 then
		str = "�ܱ�Ǹ�����İ���Ա����10�ˣ�"
    elseif nError == 9 then
		str = "�ܱ�Ǹ���Ѿ���������İ�ս��������"
    elseif nError == 10 then
		str = "�ܱ�Ǹ�����ս�����Ѵ����ޣ�"
    elseif nError == 11 then
		str = "�ܱ�Ǹ�����ս�Ѿ�������"
    else
		str = "�ܱ�Ǹ��δ֪����"
    end
    
    if str ~= nil then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
    end
end

---------------------------------------------------------------------------------
--���pvp2v2ս�����ͻص�
---------------------------------------------------------------------------------
function x800021_OnMPVP2v2BattleChangeScene(sceneId, selfId, targetSceneId)
	
	--��ʼ����
	if sceneId ~= targetSceneId then
		
		--���״̬
        local state, msg = x800021_BattleTransCheckPlayerState(sceneId, selfId)
        if state == 1 then
            Msg2Player(sceneId, selfId, msg, 8, 3)
            return
        end
        
        --����Ƿ���Դ���
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT, "CheckCountryBattleLiteSceneTrans", sceneId, selfId, targetSceneId) == 0 then
			return
		end
		
		--��¼ RuntimeData
        local nCurX, nCurZ = GetWorldPos(sceneId, selfId)
        SetPlayerRuntimeData(sceneId, selfId, RD_HUMAN_SCENE_PRE, sceneId + 1)
        SetPlayerRuntimeData(sceneId, selfId, RD_HUMAN_POSX_PRE, nCurX)
        SetPlayerRuntimeData(sceneId, selfId, RD_HUMAN_POSZ_PRE, nCurZ)
		SetPlayerRuntimeData(sceneId, selfId, RD_BATTLE_SCENE_KICK_DOWN, 0)
		
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT, "CheckCountryBattleLiteSceneTrans", sceneId, selfId, targetSceneId) == 0 then
			return
		end
		
		NewWorld(sceneId, selfId, targetSceneId, 100, 100, 8000217)		
		
		local name = GetName(sceneId, selfId)
	    local strMsg = format("MP2BL:<Info>x800021_OnMPVP2v2BattleChangeScene sceneId = %d name=%s targetSceneId=%d", sceneId, name, targetSceneId )
	    WriteLog(1, strMsg) 
	end
end

---------------------------------------------------------------------------------
--���pvp2v2ս�����ʹ�����ص�
---------------------------------------------------------------------------------
function x800021_OnMPVP2v2BattleTransError(sceneId, selfId, nErrorCode)
	
	local str = nil
	if nErrorCode == 1 then
		str = "�ܱ�Ǹ��˫��ս����û�п�ʼ��"
	elseif nErrorCode == 2 then
		str = "�ܱ�Ǹ����û�б����μ�˫��ս����"
	elseif nErrorCode == 3 then
		str = "�ܱ�Ǹ��û��Ϊ���Ķ����ҵ����ʵĶ��֣�"
	elseif nErrorCode == 4 then
		str = "�ܱ�Ǹ��˫��ս���Ѿ�������"
	elseif nErrorCode == 5 then
		str = "�ܱ�Ǹ��˫��ս���������Ѿ����ˣ����Ժ����ԡ�"
	elseif nErrorCode == 6 then
		str = "�ܱ�Ǹ��˫��ս���ѹرգ�"
	elseif nErrorCode == 7 then
		str = "�ܱ�Ǹ����ʱ�޷�����˫��ս��������"
	end
	
	if str ~= nil then
        Msg2Player(sceneId, selfId, str, 8, 3)
    end
end

---------------------------------------------------------------------------------
--����������
---------------------------------------------------------------------------------
function x800021_ProcAcceptCheck(sceneId, selfId, targetId)
end

---------------------------------------------------------------------------------
--����
---------------------------------------------------------------------------------
function x800021_ProcAccept(sceneId, selfId)
end


---------------------------------------------------------------------------------
--����
---------------------------------------------------------------------------------
function x800021_ProcQuestAbandon(sceneId, selfId, MissionId)
end

---------------------------------------------------------------------------------
--����Ƿ�����ύ
---------------------------------------------------------------------------------
function x800021_CheckSubmit( sceneId, selfId, targetId)
end

---------------------------------------------------------------------------------
--�ύ
---------------------------------------------------------------------------------
function x800021_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
end

---------------------------------------------------------------------------------
--ɱ����������
---------------------------------------------------------------------------------
function x800021_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end

---------------------------------------------------------------------------------
--���������¼�
---------------------------------------------------------------------------------
function x800021_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
end

---------------------------------------------------------------------------------
--���߸ı�
---------------------------------------------------------------------------------
function x800021_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
end
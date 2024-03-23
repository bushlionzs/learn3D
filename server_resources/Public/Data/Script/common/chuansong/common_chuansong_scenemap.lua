--功能：中心传送
--NPC：中心传送使者

--**********************************
--帮会拉人全局变量
x800021_g_newSceneID={ID1=50,ID2=150,ID3=250,ID4=350,}    --活动所在场景ID
x800021_g_PosX = {Pos1=176,Pos2=176,Pos3=78,Pos4=69,}
x800021_g_PosZ = {Pos1=179,Pos2=179,Pos3=76,Pos4=77,}
--x800021_g_OffsetX = 10
--x800021_g_OffsetZ = 10
--**********************************


--**********************************
--国家拉人全局变量
x800021_g_newCountrySceneID ={ID1=51,ID2=151,ID3=251,ID4=351,}    --活动所在场景ID
x800021_g_CountryPosX = {Pos1=126,Pos2=126,Pos3=126,Pos4=126,}
x800021_g_CountryPosZ = {Pos1=184,Pos2=185,Pos3=62,Pos4=62,}
--x800021_g_CountryOffsetX = 5
--x800021_g_CountryOffsetZ = 5
--**********************************



---------------------------------------------------------------------------------
--任务入口函数
---------------------------------------------------------------------------------
function x800021_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

end

---------------------------------------------------------------------------------
--用户通过UI请求切换场景
--在CGMapInfoHandler中被呼叫
---------------------------------------------------------------------------------
function x800021_OnChangeSceneEvent(sceneId, selfId, index, Backhaul)

	local strText = ""
	local CanTrans = IsCashboxState(sceneId,selfId)
	if CanTrans == 1 then
		BeginQuestEvent(sceneId)
			strText = "#Y运镖或者护送状态中，不允许传送"
			AddQuestText(sceneId,strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

	--得到进入该场景需要的最小等级、场景ID，位置信息
	local MinUserLevel, targetSceneId, PosX,PosZ, needMoney, needItemID,SourceSceneId,SourcePosX,SourcePosZ = GetNewSceneInfoByIndex(sceneId,index)
	if SourceSceneId ~= sceneId then
		--传送的起始场景与当前场景不匹配
		return
	end

	local selfPosX,selfPosZ = GetWorldPos(sceneId, selfId)
	if IsInDistByPoint(sceneId,selfPosX,selfPosZ,SourcePosX,SourcePosZ,7 ) ~= 1 then
		--位置错误
		return
	end

	PosX = PosX - 4 + random(1,7)
	PosZ = PosZ - 4 + random(1,7)
	local level = GetLevel(sceneId, selfId)

	--检查级别
	if level < MinUserLevel then
	
		BeginQuestEvent(sceneId)
			strText = "#Y等级低于#G"..MinUserLevel.."#Y级，无法前往该地"
			AddQuestText(sceneId,strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		
		return
	end
		
	--摆摊模式
	if IsInStall(sceneId, selfId) ~= 0 then
		return
	end
	
	--检查死亡
	local life=IsCharacterLiving( sceneId,selfId)
	if life == 0 then
		return
	end
	
	--以下开始处理传送情况
	if GetTeamId( sceneId, selfId) > 0  then
	
		--有队伍的情况，如果不是队伍跟随模式
		if IsTeamFollow(sceneId, selfId) ~= 1 then
			
			local bCostMoney = 0;
			local bCostItem = 0;
			if( needMoney > 0 ) then
				if( IsEnoughMoney( sceneId, selfId, needMoney ) == 0 ) then
					BeginQuestEvent(sceneId)
						strText = "#Y您的金钱不足，无法前往该地"
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
						strText = "#Y您身上没有传送物品，无法前往该地"
						AddQuestText(sceneId,strText);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					return 0;
				else
					bCostItem = 1;
				end
			end
			
			--扣钱
			if( bCostMoney == 1 ) then
				if( SpendMoney( sceneId, selfId, needMoney,302 ) == -1 ) then
					BeginQuestEvent(sceneId)
						strText = "#Y您的金钱不足，无法前往该地"
						AddQuestText(sceneId,strText);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					return 0;
				end
			end
			
			--扣物品
			if( bCostItem == 1 ) then
				if( DelItem(sceneId, selfId, needItemID, 1) == 0 ) then
					BeginQuestEvent(sceneId)
						strText = "#Y您身上没有传送物品，无法前往该地"
						AddQuestText(sceneId,strText);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					return 0;
				end
			end
			
			--传送
			CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferFunc",sceneId,selfId,targetSceneId,PosX,PosZ)	
		else
		
			--如果是跟随模式，但是是队长
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
					--所有人都满足条件，传送
					CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferFunc",sceneId,selfId,targetSceneId,PosX,PosZ)
				else
					for i=0,num-1 do
						BeginQuestEvent(sceneId)
							strText = "#Y有队伍成员等级低于#G"..MinUserLevel.."#Y级，无法前往该地"
							AddQuestText(sceneId,strText);
						EndQuestEvent(sceneId)
						DispatchQuestTips(sceneId,mems[i])
					end
				end	
			end	
		end						
	else
		--没有队伍的处理
		local bCostMoney = 0;
		local bCostItem = 0;
		if( needMoney > 0 ) then
			if( IsEnoughMoney( sceneId, selfId, needMoney ) == 0 ) then
				BeginQuestEvent(sceneId)
					strText = "#Y您的金钱不足，无法前往该地"
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
					strText = "#Y您身上没有传送物品，无法前往该地"
					AddQuestText(sceneId,strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0;
			else
				bCostItem = 1;
			end
		end
		
		--扣钱
		if( bCostMoney == 1 ) then
			if( SpendMoney( sceneId, selfId, needMoney,302 ) == -1 ) then
				BeginQuestEvent(sceneId)
					strText = "#Y您的金钱不足，无法前往该地"
					AddQuestText(sceneId,strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0;
			end
		end
		
		--扣物品
		if( bCostItem == 1 ) then
			if( DelItem(sceneId, selfId, needItemID, 1) == 0 ) then
				BeginQuestEvent(sceneId)
					strText = "#Y您身上没有传送物品，无法前往该地"
					AddQuestText(sceneId,strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0;
			end
		end
		
		--执行传送
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferFunc",sceneId,selfId,targetSceneId,PosX,PosZ)
	end

end


---------------------------------------------------------------------------------
--列举事件
---------------------------------------------------------------------------------
function x800021_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

end


---------------------------------------------------------------------------------
--帮会拉人事件
---------------------------------------------------------------------------------
function x800021_OnGuildConvoyChangeScene(sceneId,selfId)

	--如果在监狱不可以被传送
	if sceneId == PK_PUNISH_PRISON_SCENE_ID then
		BeginQuestEvent(sceneId)
		local strText = "监狱里还不老实,想走,没门。"
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

	if country == 0 then--?￥à?
		Map_ID = x800021_g_newSceneID.ID1
		PosX = x800021_g_PosX.Pos1 + offsetX
		PosZ = x800021_g_PosZ.Pos1 + offsetX
	end

	if country == 1 then--à3òe
		Map_ID = x800021_g_newSceneID.ID2
		PosX = x800021_g_PosX.Pos2 + offsetX
		PosZ = x800021_g_PosZ.Pos2 + offsetX
	end

	if country == 2 then--à￥??
		Map_ID = x800021_g_newSceneID.ID3
		PosX = x800021_g_PosX.Pos3 + offsetX
		PosZ = x800021_g_PosZ.Pos3 + offsetX
	end

	if country == 3 then--???í
		Map_ID = x800021_g_newSceneID.ID4
		PosX = x800021_g_PosX.Pos4 + offsetX
		PosZ = x800021_g_PosZ.Pos4 + offsetX
	end
	
	--暴龙大作战期间
	if sceneId == 39 then
	    if IsHaveSpecificImpact(sceneId, selfId, 7537 ) ~= 0 or IsHaveSpecificImpact(sceneId, selfId, 7536  ) ~= 0 then
	        BeginQuestEvent(sceneId)
			AddQuestText( sceneId, "在暴龙大作战期间，不能传送" )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
	    end
		return		
	end
	
	if sceneId == Map_ID then
		SetPos( sceneId , selfId , PosX , PosZ )

	else
	
		--检查是否可以传送
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,Map_ID) == 0 then
			return
		end
		
        -- 如果在舞厅，先清除禁止骑马标记
        if sceneId == 14 then
            SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_FORBID_RIDE, 0)
        end
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,Map_ID) == 0 then
			return
		end
        NewWorld( sceneId , selfId , Map_ID , PosX , PosZ, 8000210 )
	end

    -- 增加活跃度
    local id = GetGuildID( sceneId, selfId)
    if id ~= -1 then
        AddGuildActivity( sceneId, selfId, GetGuildCacheFreeParam( id, GD_GUILD_ACTIVITY_PARAM7) )
    end
end

---------------------------------------------------------------------------------
--帮会拉人
---------------------------------------------------------------------------------
function x800021_OnGuildConvokeChangeScene( sceneId,selfId, newSceneId, posX, posZ )
	
	--开始传送
	if sceneId == PK_PUNISH_PRISON_SCENE_ID then
		BeginQuestEvent(sceneId)
		local strText = "监狱中，不能传送"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return		
	end
	
	--暴龙大作战期间
	if sceneId == 39 then
	    if IsHaveSpecificImpact(sceneId, selfId, 7537 ) ~= 0 or IsHaveSpecificImpact(sceneId, selfId, 7536  ) ~= 0 then
	        BeginQuestEvent(sceneId)
			AddQuestText( sceneId, "在暴龙大作战期间，不能传送" )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
	    end
		return		
	end
	
	--在婆罗州，只有60级以上传送
	if newSceneId == 50 or newSceneId == 150 or newSceneId == 250 or newSceneId == 350 or 
	   newSceneId == 51 or newSceneId == 151 or newSceneId == 251 or newSceneId == 351 or 
	   newSceneId == 86 or newSceneId == 186 or newSceneId == 286 or newSceneId == 386 or 
	   newSceneId == 2 or newSceneId == 3 or newSceneId == 4 or newSceneId == 5 then 
		if GetLevel(sceneId,selfId) < 40 then
			BeginQuestEvent(sceneId)
			local strText = "只有40级以上，才能传送到目的地"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 6 then
		if GetLevel(sceneId,selfId) < 40 then
			BeginQuestEvent(sceneId)
			local strText = "只有40级以上，才能传送到蔡州城"  
			AddQuestText( sceneId, strText )                  
			EndQuestEvent( sceneId )                          
			DispatchQuestTips( sceneId, selfId )              
			return				                              
		end                                                   
	end                                                       
	                                                          
	if newSceneId == 7 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                          
			local strText = "只有40级以上，才能传送到秦岭"    
			AddQuestText( sceneId, strText )                  
			EndQuestEvent( sceneId )                          
			DispatchQuestTips( sceneId, selfId )              
			return				                              
		end                                                   
	end                                                       
	                                                          
	if newSceneId == 8 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "只有40级以上，才能传送到阿尔金山"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 9 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "只有40级以上，才能传送到碎叶城"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 10 or newSceneId == 11 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "只有40级以上，才能传送到红沙漠或撒马尔罕"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 13 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "只有40级以上，才能传送到巴格达"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 16 or newSceneId == 17 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "只有40级以上，才能传送到波斯高原或莫斯科公国"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 18 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "只有40级以上，才能传送到巴格达"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 19 or newSceneId == 20 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "只有40级以上，才能传送到波兰王国或匈牙利"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 21 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "只有40级以上，才能传送到神圣罗马帝国"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 22 or newSceneId == 23 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "只有40级以上，才能传送到拜占庭帝国或大马士革"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 24 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "只有40级以上，才能传送到耶路撒冷"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 25 or newSceneId == 26 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "只有40级以上，才能传送到西奈半岛或对马岛"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 27 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "只有40级以上，才能传送到耶路撒冷"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 29 or newSceneId == 30 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "只有40级以上，才能传送到九州岛或对大理"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 31 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "只有40级以上，才能传送到缅甸"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 32 or newSceneId == 33 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "只有40级以上，才能传送到印度河或婆罗洲"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 34 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "只有40级以上，才能传送到爪哇岛"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if newSceneId == 35 then                                   
		if GetLevel(sceneId,selfId) < 40 then                 
			BeginQuestEvent(sceneId)                        
			local strText = "只有40级以上，才能传送到苏门答腊"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return				
		end
	end
	
	if sceneId == newSceneId then
		SetPos( sceneId , selfId , posX , posZ )
	else
		
		--检查是否可以传送
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
			return
		end
		NewWorld( sceneId , selfId , newSceneId , posX , posZ, 8000211 )
	end

    -- 增加活跃度
    local id = GetGuildID( sceneId, selfId)
    if id ~= -1 then
        AddGuildActivity( sceneId, selfId, GetGuildCacheFreeParam( id, GD_GUILD_ACTIVITY_PARAM7) )
    end

end

---------------------------------------------------------------------------------
--国家拉人事件
---------------------------------------------------------------------------------
function x800021_OnCountryChangeScene(sceneId,selfId)

	--如果在监狱不可以被传送
	if sceneId == PK_PUNISH_PRISON_SCENE_ID then
		BeginQuestEvent(sceneId)
		local strText = "监狱里还不老实,想走,没门。"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
	end
	
	--如果在副本里
	local sceneType = GetSceneType(sceneId)
	if sceneType==1 then
		BeginQuestEvent(sceneId)
		local strText = "副本中，不能响应国家拉人事件。"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
	end
	
	--是否在游乐场并处于变身状态
	IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId, 7536  )
    if IsHaveFlag ~= 0 then
        BeginQuestEvent(sceneId)
		local strText = "在暴龙大作战期间，不能响应国家拉人事件。"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
    end
    
    IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId, 7537 )
    if IsHaveFlag ~= 0 then
        BeginQuestEvent(sceneId)
		local strText = "在暴龙大作战期间，不能响应国家拉人事件。"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
    end
	

	--判断是否是武官
		if GetLevel(sceneId, selfId) >= 40 then
			GetCountryQuestData(sceneId,selfId,CD_INDEX_DESTROY_ISSUE_TIME, CHUANSONG_SCENEMAP_SCRIPT,-1,"OnReturn1")
		else
			BeginQuestEvent(sceneId)
			local strText = "很抱歉，您的等级不足40级，不能被传送的大将军身边。"
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
        -- 如果在舞厅，先清除禁止骑马标记
        if sceneId == 14 then
            SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_FORBID_RIDE, 0)
        end
        
        --检查是否可以传送
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,NewSceneID) == 0 then
			return
		end
		NewWorld(sceneId, selfId, NewSceneID,PosX ,PosZ, 8000212 )
	end
end


---------------------------------------------------------------------------------
--检查玩家传送状态
---------------------------------------------------------------------------------
function x800021_BattleTransCheckPlayerState( sceneId,selfId )

    local state = IsPlayerStateNormal(sceneId,selfId )
    if state == 0 then
        return 1,"状态异常"
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_MENTALGAME )
    if state == 1 then
        return 1,"处于答题状态，不能进入战场"
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_STALL )
    if state == 1 then
        return 1,"处于摆摊状态，不能进入战场"
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_DIE )
    if state == 1 then
        return 1,"处于死亡状态，不能进入战场"
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_CRASHBOX )
    if state == 1 then
        return 1,"处于运镖状态，不能进入战场"
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_AUTOPLAY )
    if state == 1 then
        ErrorMsg = "处于挂机状态，不能进入战场"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_SUBTRAIN )
    if state == 1 then
        return 1,"处于代练状态，不能进入战场"
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_BUS )
    if state == 1 then
        return 1,"处于BUS状态，不能进入战场"
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_PKMODE )
    if state == 1 then
        return 1,"PK值过高或处于狂暴模式，不能进入战场"
    end
    
    local IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId, 7702 )
    if IsHaveFlag ~= 0 then
        return 1, "在夺旗状态下，不能进入战场"
    end
    
    if IsHideName(sceneId, selfId) > 0 then
    	return 1,"蒙面状态下,不能进入战场"
    end
    
    if sceneId == PK_PUNISH_PRISON_SCENE_ID then
    	return 1,"在监狱里，不能进入战场"
    end
    
    IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId, 7536  )
    if IsHaveFlag ~= 0 then
        return 1, "在暴龙大作战期间，不能进入战场"
    end
    
    IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId, 7537 )
    if IsHaveFlag ~= 0 then
        return 1, "在暴龙大作战期间，不能进入战场"
    end

    return 0

end

---------------------------------------------------------------------------------
--请求进入国王战场
---------------------------------------------------------------------------------
function x800021_AskEnterKingBattle( sceneId,selfId )

    --玩家状态
    local state,msg = x800021_BattleTransCheckPlayerState( sceneId,selfId )
    if state == 1 then
        
        BeginQuestEvent(sceneId)
        AddQuestText( sceneId, msg );
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return
    end

    --进入国王战场
    RequestEnterKingBattleScene(sceneId, selfId)
end

---------------------------------------------------------------------------------
--请求进入世界杯战场
---------------------------------------------------------------------------------
function x800021_AskEnterWorldCup( sceneId,selfId)
    local nGuildId = GetGuildID( sceneId, selfId)
    if nGuildId < 0 or nGuildId > 1024 then
        if targetId ~= 0 then
            BeginQuestEvent( sceneId)
                AddQuestText( sceneId, "#Y"..x300615_g_Name)
                AddQuestText( sceneId, "你尚未加入任何帮会！不能进入战场。" )
            EndQuestEvent()
            DispatchQuestEventList( sceneId, selfId, targetId)
            return
        end
    end

    --检查状态
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
--GLserver允许进入世界杯战场
---------------------------------------------------------------------------------
function x800021_OnEnterWorldCup( sceneId, selfId, targetSceneId)
    GetGuildQuestData( sceneId, selfId, GD_GUILD_INDEX_CONTEND_STATE, 800021, targetSceneId, "EnterWorldCup" )
end

--根据玩家所在帮会世界杯状态将玩家传入战场
function x800021_EnterWorldCup( sceneId, selfId, MissionData, MissionId, targetId)

    if MissionData == STATE_GUILD_WORLDCUP_END then
        Msg2Player( sceneId, selfId, "比赛已经结束，你不能再进入战场了。", 8, 2)
        Msg2Player( sceneId, selfId, "比赛已经结束，你不能再进入战场了", 8, 3)
        return
    end
    
    --检查是否可以传送
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
--pvp2v2战场传送
---------------------------------------------------------------------------------
function x800021_OnPVP2v2BattleChangeScene( sceneId,selfId,targetSceneId )
	
	--开始传送
	if sceneId ~= targetSceneId then
		
		--检查状态
        local state,msg = x800021_BattleTransCheckPlayerState( sceneId,selfId )
        if state == 1 then
            
            BeginQuestEvent(sceneId)
            AddQuestText( sceneId, msg );
            EndQuestEvent(sceneId)
            DispatchQuestTips(sceneId,selfId)
            return
        end
        
        --检查是否可以传送
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,targetSceneId) == 0 then
			return
		end
		
		--记录一个RuntimeData
        local nCurX,nCurZ = GetWorldPos( sceneId,selfId )
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_SCENE_PRE,sceneId + 1)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSX_PRE,nCurX)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSZ_PRE,nCurZ)
		SetPlayerRuntimeData(sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ,0)
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,targetSceneId) == 0 then
			return
		end
		NewWorld(sceneId, selfId, targetSceneId, 100, 100, 8000214);		
		
		--再记日志
		local name = GetName(sceneId,selfId)
	    local strMsg = format("P2BL:<Info>x800021_OnPVP2v2BattleChangeScene sceneId = %d name=%s targetSceneId=%d", sceneId, name, targetSceneId  )
	    WriteLog( 1, strMsg ) 
	end
end

---------------------------------------------------------------------------------
--pvp2v2战场传送错误处理
---------------------------------------------------------------------------------
function x800021_OnPVP2v2BattleTransError( sceneId,selfId,nErrorCode )
	
	local str = nil
	if nErrorCode == 1 then
		str = "很抱歉，双人战场还没有开始！"
	elseif nErrorCode == 2 then
		str = "很抱歉，你没有报名参加双人战场！"
	elseif nErrorCode == 3 then
		str = "很抱歉，没有为您的队伍找到合适的对手！"
	elseif nErrorCode == 4 then
		str = "很抱歉，双人战场已经结束！"
	elseif nErrorCode == 5 then
		str = "很抱歉，双人战场的赛场已经满了！请稍候重试。"
	elseif nErrorCode == 6 then
		str = "很抱歉，双人战场已关闭！"
	elseif nErrorCode == 7 then
		str = "很抱歉，暂时无法开启双人战场赛场！"
	end
	
	if str ~= nil then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
    end
	
end



---------------------------------------------------------------------------------
--pvp6v6战场传送
---------------------------------------------------------------------------------
function x800021_OnPVP6v6BattleChangeScene( sceneId,selfId,targetSceneId )
	
	--开始传送
	if sceneId ~= targetSceneId then
		
		--检查状态
        local state,msg = x800021_BattleTransCheckPlayerState( sceneId,selfId )
        if state == 1 then
            
            BeginQuestEvent(sceneId)
            AddQuestText( sceneId, msg );
            EndQuestEvent(sceneId)
            DispatchQuestTips(sceneId,selfId)
            return
        end
        
        --检查是否可以传送
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,targetSceneId) == 0 then
			return
		end
		
		--记录一个RuntimeData
        local nCurX,nCurZ = GetWorldPos( sceneId,selfId )
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_SCENE_PRE,sceneId + 1)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSX_PRE,nCurX)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSZ_PRE,nCurZ)
		SetPlayerRuntimeData(sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ,0)
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,targetSceneId) == 0 then
			return
		end
		NewWorld(sceneId, selfId, targetSceneId, 100, 100, 8000214);		
		
		--再记日志
		local name = GetName(sceneId,selfId)
	    local strMsg = format("P2BL:<Info>x800021_OnPVP6v6BattleChangeScene sceneId = %d name=%s targetSceneId=%d", sceneId, name, targetSceneId  )
	    WriteLog( 1, strMsg ) 	
	end
end

---------------------------------------------------------------------------------
--pvp6v6战场传送错误处理
---------------------------------------------------------------------------------
function x800021_OnPVP6v6BattleTransError( sceneId,selfId,nErrorCode )
	
	local str = nil
	if nErrorCode == 1 then
		str = "很抱歉，组队战场还没有开始！"
	elseif nErrorCode == 2 then
		str = "很抱歉，你没有报名参加组队战场！"
	elseif nErrorCode == 3 then
		str = "很抱歉，没有为您的队伍找到合适的对手！"
	elseif nErrorCode == 4 then
		str = "很抱歉，组队战场已经结束！"
	elseif nErrorCode == 5 then
		str = "很抱歉，组队战场的赛场已经满了！请稍候重试。"
	elseif nErrorCode == 6 then
		str = "很抱歉，组队战场已关闭！"
	elseif nErrorCode == 7 then
		str = "很抱歉，暂时无法开启组队战场！"
	end
	
	if str ~= nil then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
    end
	
end

---------------------------------------------------------------------------------
--国王战场相关传送脚本
---------------------------------------------------------------------------------
function x800021_OnKingBattleChangeScene( sceneId,selfId,newSceneID,Flag )
    

    --如果在监狱不可以被传送
	if sceneId == PK_PUNISH_PRISON_SCENE_ID then
		BeginQuestEvent(sceneId)
		local strText = "监狱里还不老实,想走,没门。"
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
			
			--检查状态
			local state,msg = x800021_BattleTransCheckPlayerState( sceneId,selfId )
			if state == 1 then
				
				BeginQuestEvent(sceneId)
				AddQuestText( sceneId, msg );
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return
			end
			
			--检查是否可以传送
			if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneID) == 0 then
				return
			end

			--记录一个RuntimeData
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
--进入国王战场报错说明
---------------------------------------------------------------------------------
function x800021_OnKingBattleTransError( sceneId,selfId,nErrorId )
    
    
    local str = nil
    if nErrorId == 0 then        
        str = "只有参加帮会之后才能进入！"
    elseif nErrorId == 1 then
        str = "您的帮会没有报名！"
    elseif nErrorId == 2 then
        str = "国王战场还没到开放时间！"
    elseif nErrorId == 3 then
        str = "国王战场已经关闭入口（超过两分钟）"
    elseif nErrorId == 4 then
        str = "目前没有国王战场开始"
    elseif nErrorId == 5 then
        str = "战场人数已满"
    elseif nErrorId == 6 then
        str ="你已经进入过战场，不能重复进入！"
    elseif nErrorId == 7 then
    	str ="只有一方报名,国王已经诞生,战场关闭"
    else
        str ="未知错误，不能进入！"
    end
    
    if str ~= nil then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
    end

end

---------------------------------------------------------------------------------
--帮会战拉人事件
---------------------------------------------------------------------------------
function x800021_OnGuildBattleChangeScene(sceneId,selfId,newSceneID,Flag)

	--如果在监狱不可以被传送
	if sceneId == PK_PUNISH_PRISON_SCENE_ID then
		BeginQuestEvent(sceneId)
		local strText = "监狱里还不老实,想走,没门。"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
	end

    --设置位置
	local BasePosX = 0
	local BasePosZ = 0
    if Flag == 0 then
        BasePosX = 234
        BasePosZ = 126
    elseif Flag == 1 then
        BasePosX = 21
        BasePosZ = 126
    end


    --其他数据测试
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
        
        --检查状态
        local state,msg = x800021_BattleTransCheckPlayerState( sceneId,selfId )
        if state == 1 then
            
            BeginQuestEvent(sceneId)
            AddQuestText( sceneId, msg );
            EndQuestEvent(sceneId)
            DispatchQuestTips(sceneId,selfId)
            return
        end
        
        --检查是否可以传送
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneID) == 0 then
			return
		end

        --记录一个RuntimeData
        local nCurX,nCurZ = GetWorldPos( sceneId,selfId )
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_SCENE_PRE,sceneId + 1)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSX_PRE,nCurX)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSZ_PRE,nCurZ)

        --传到帮战场景时记录一下当前所在的场景及位置
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneID) == 0 then
			return
		end
		NewWorld( sceneId , selfId , newSceneID , PosX , PosZ, 8000216 )
	end

end

---------------------------------------------------------------------------------
--进入帮会战异常
---------------------------------------------------------------------------------
function x800021_OnGuildBattleTransError( sceneId,selfId,nError )
    
    local str = nil
    if nError == 1 then
		str = "很抱歉，活动还没有开始！"
    elseif nError == 2 then
		str = "很抱歉，您没有帮会！"
    elseif nError == 3 then
		str = "很抱歉，您所在的帮会还没有报名！"
    elseif nError == 4 then
		str = "很抱歉，帮会战还没有开始！"
    elseif nError == 5 then
		str = "很抱歉，您所在的帮会在此次帮会战中轮空！"
    elseif nError == 6 then
		str = "很抱歉，您的帮会信息区配不正确！"
    elseif nError == 7 then
		str = "很抱歉，您不是帮主！"
    elseif nError == 8 then
		str = "很抱歉，您的帮会成员不足10人！"
    elseif nError == 9 then
		str = "很抱歉，已经受理过您的帮战申请请求！"
    elseif nError == 10 then
		str = "很抱歉，帮会战报名已达上限！"
    elseif nError == 11 then
		str = "很抱歉，帮会战已经结束！"
    else
		str = "很抱歉，未知错误！"
    end
    
    if str ~= nil then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
    end
end

---------------------------------------------------------------------------------
--跨服pvp2v2战场传送回调
---------------------------------------------------------------------------------
function x800021_OnMPVP2v2BattleChangeScene(sceneId, selfId, targetSceneId)
	
	--开始传送
	if sceneId ~= targetSceneId then
		
		--检查状态
        local state, msg = x800021_BattleTransCheckPlayerState(sceneId, selfId)
        if state == 1 then
            Msg2Player(sceneId, selfId, msg, 8, 3)
            return
        end
        
        --检查是否可以传送
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT, "CheckCountryBattleLiteSceneTrans", sceneId, selfId, targetSceneId) == 0 then
			return
		end
		
		--记录 RuntimeData
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
--跨服pvp2v2战场传送错误处理回调
---------------------------------------------------------------------------------
function x800021_OnMPVP2v2BattleTransError(sceneId, selfId, nErrorCode)
	
	local str = nil
	if nErrorCode == 1 then
		str = "很抱歉，双人战场还没有开始！"
	elseif nErrorCode == 2 then
		str = "很抱歉，你没有报名参加双人战场！"
	elseif nErrorCode == 3 then
		str = "很抱歉，没有为您的队伍找到合适的对手！"
	elseif nErrorCode == 4 then
		str = "很抱歉，双人战场已经结束！"
	elseif nErrorCode == 5 then
		str = "很抱歉，双人战场的赛场已经满了！请稍候重试。"
	elseif nErrorCode == 6 then
		str = "很抱歉，双人战场已关闭！"
	elseif nErrorCode == 7 then
		str = "很抱歉，暂时无法开启双人战场赛场！"
	end
	
	if str ~= nil then
        Msg2Player(sceneId, selfId, str, 8, 3)
    end
end

---------------------------------------------------------------------------------
--检测接受条件
---------------------------------------------------------------------------------
function x800021_ProcAcceptCheck(sceneId, selfId, targetId)
end

---------------------------------------------------------------------------------
--接受
---------------------------------------------------------------------------------
function x800021_ProcAccept(sceneId, selfId)
end


---------------------------------------------------------------------------------
--放弃
---------------------------------------------------------------------------------
function x800021_ProcQuestAbandon(sceneId, selfId, MissionId)
end

---------------------------------------------------------------------------------
--检测是否可以提交
---------------------------------------------------------------------------------
function x800021_CheckSubmit( sceneId, selfId, targetId)
end

---------------------------------------------------------------------------------
--提交
---------------------------------------------------------------------------------
function x800021_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
end

---------------------------------------------------------------------------------
--杀死怪物或玩家
---------------------------------------------------------------------------------
function x800021_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end

---------------------------------------------------------------------------------
--进入区域事件
---------------------------------------------------------------------------------
function x800021_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
end

---------------------------------------------------------------------------------
--道具改变
---------------------------------------------------------------------------------
function x800021_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
end
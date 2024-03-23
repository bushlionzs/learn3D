x310020_g_ScriptId = 310020
--x310020_g_MD_AcceptTime = 240

x310020_g_MD_ItemMission = {  {itemId=13013301, mission=8001}, {itemId=13013302, mission=8002}, {itemId=13013303, mission=8003}, {itemId=13013304, mission=8004} }
x310020_g_MissionCommentId = 1102

x310020_g_ItemUsePosition = {	{id=13013300, buff=7053, r=10, x1=85, z1=25, x2=17, z2=69, x3=104, z3=88, find1=37000, find2=37001, find3=37002, sceneName="地下粮仓一层", mission=8000, usedItem ="始耀结晶" ,destItem="理耀结晶" }, 
								{id=13013301, buff=7054, r=10, x1=93, z1=34, x2=79, z2=99, x3=46, z3=15, find1=38000, find2=38001, find3=38002, sceneName="地下粮仓二层", mission=8001, usedItem ="理耀结晶" ,destItem="命耀结晶"  },
								{id=13013302, buff=7055, r=10, x1=104, z1=47, x2=71, z2=97, x3=57, z3=47, find1=39000, find2=39001, find3=39002, sceneName="地下粮仓三层", mission=8002, usedItem ="命耀结晶" ,destItem="化耀结晶"  },
								{id=13013303, buff=7056, r=10, x1=114, z1=76, x2=97, z2=8, x3=50, z3=101, find1=40000, find2=40001, find3=40002, sceneName="地下粮仓四层", mission=8003, usedItem ="化耀结晶" ,destItem="灭耀结晶"  },
								{id=13013304, buff=7057, r=10, x1=101, z1=76, x2=101, z2=76, x3=101, z3=76, find1=41000, find2=41000, find3=41000, sceneName="地下粮仓五层", mission=8004, usedItem ="灭耀结晶" ,destItem=""  }
								}

x310020_g_MissionScene = { {mission=8000, scene=2 }, 
							{mission=8001, scene=3},
							{mission=8002, scene=4},
							{mission=8003, scene=5} 
							}

x310020_g_AwardItemId = 12030027
x310020_g_AbandonMessage	= "你放弃了任务：%s"
x310020_g_AcceptMessage		= "你接受了任务：%s"
x310020_g_CompleteMessage	= "你完成了任务：%s"

function x310020_HaveAccepted(sceneId, selfId)

	local day = GetQuestData(sceneId, selfId, MD_WUYAO_LVJUE_DATE[1], MD_WUYAO_LVJUE_DATE[2], MD_WUYAO_LVJUE_DATE[3])
	if day > 0 then
		return 1
	end
	return -1
end

function x310020_ResetMission( sceneId, selfId, itemId, MissionId )
	for i, item in x310020_g_MD_ItemMission do
		if item.itemId == itemId then
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			local level = GetQuestParam( sceneId, selfId, misIndex, 2 ) 
					
			DelQuestNM( sceneId, selfId, MissionId )
			
			--检查前置任务
			local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, item.mission )
			if FrontMissiontId1 ~= -1 then
				if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
					return 0--如果前置任务没做直接返回
				end
			end
			if FrontMissiontId2 ~= -1 then
				if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
					return 0--如果前置任务没做直接返回
				end
			end
			if FrontMissiontId3 ~= -1 then
				if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
					return 0--如果前置任务没做直接返回
				end
			end
			
			--PrintNum(itemId)
			local ret = AddQuestNM( sceneId, selfId, item.mission)
			if ret < 1 then
				if ret == -2 then
					local strText = "任务已满，添加任务失败"
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, strText);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
				elseif ret == -1 then
					local strText = "背包已满,添加任务失败"
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, strText);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
				else
					local strText = "添加任务失败"
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, strText);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
				end
				
			else
				
				if item.mission == 8001 then
					SetQuestParam( sceneId, selfId, 8001, MP_CIRCLE, 1 )
				elseif item.mission == 8002 then
					SetQuestParam( sceneId, selfId, 8002, MP_CIRCLE, 2 )
				elseif item.mission == 8003 then
					SetQuestParam( sceneId, selfId, 8003, MP_CIRCLE, 3 )
				elseif item.mission == 8004 then
					SetQuestParam( sceneId, selfId, 8004, MP_CIRCLE, 4 )
				end
				misIndex = GetQuestIndexByID( sceneId, selfId, item.mission )
				SetQuestByIndex( sceneId, selfId, misIndex, 2, level )

				x310020_SetRandPosition(sceneId, selfId, item.mission)
			end

			return
		end
	end	
end

function x310020_NextDayRest(sceneId, selfId)
	--local lastDay = LuaGetThatDayTime(lasttime)
	local lastDay = GetQuestData(sceneId, selfId, MD_WUYAO_LVJUE_DATE[1], MD_WUYAO_LVJUE_DATE[2], MD_WUYAO_LVJUE_DATE[3])

	local today = GetDayOfYear()
	if today ~= lastDay then 
		SetQuestData(sceneId, selfId, MD_WUYAO_LVJUE_DATE[1], MD_WUYAO_LVJUE_DATE[2], MD_WUYAO_LVJUE_DATE[3], 0)
	end
end

function x310020_SetRandPosition(sceneId, selfId, MissionId)
	local rp = random(1, 3)
	SetQuestParam( sceneId, selfId, MissionId, 5, rp )		
end

function x310020_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	--if x310020_HaveAccepted(sceneId, selfId) > 0 then
		--return
	--end
	if IsHaveQuestNM( sceneId, selfId, 8000 ) > 0 then
		return 0
	elseif IsHaveQuestNM( sceneId, selfId, 8001 ) > 0 then
		return 0
	elseif IsHaveQuestNM( sceneId, selfId, 8002 ) > 0 then
		return 0
	elseif IsHaveQuestNM( sceneId, selfId, 8003 ) > 0 then
		return 0
	elseif IsHaveQuestNM( sceneId, selfId, 8004 ) > 0 then
		return 0
	elseif IsHaveQuestNM( sceneId, selfId, 8005 ) > 0 then
		return 0
	elseif IsHaveQuestNM( sceneId, selfId, 8006 ) > 0 then
		return 0
	elseif IsHaveQuestNM( sceneId, selfId, 8007 ) > 0 then
		return 0
	elseif IsHaveQuestNM( sceneId, selfId, 8008 ) > 0 then
		return 0
	elseif IsHaveQuestNM( sceneId, selfId, 8009 ) > 0 then
		return 0
	end
	
	if QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId ) > 0 then
		AddQuestTextNM(sceneId, selfId, targetId, x310020_g_MissionCommentId, 13, -1)
		local  missionState = GetQuestStateNM(sceneId, selfId, targetId, MissionId)
		AddQuestTextNM(sceneId, selfId, targetId, MissionId, missionState);
		return 1
	end
    
	return 0
end

function x310020_ProcEventEntry( sceneId, selfId, targetId, MissionId, selectId )

	if MissionId == x310020_g_MissionCommentId then
		local str;
		local contentStr = "";
		
		if selectId == -1 then
			contentStr = "\t国库#G地下粮仓#W在前一个王朝时期曾名曰#G怨冢#W，得名之源是数百年前在此发生的一场惨剧，贪财的国王洗劫了数千名为避战祸流亡到此的百姓的家产，并把他们残忍的#G坑杀#W在了此地，冤魂滞留百年不散，四周荒芜不生，才得名为#G怨冢#W。"
		elseif selectId == 0 then
			contentStr = "\t当然，我皇惠天，如今这些也都成了历史，冤魂厉鬼已经远离此地，安乐成佛了。我蒙古大军西征期间曾把这里改建为囤集粮食草料的粮仓，以供20万蒙古骑兵西征之用。西征完成后此粮仓也结束了它伟大的历史使命。但是这个废弃的粮仓并没有淡出人们的视线……"
		elseif selectId == 1 then
			contentStr = "\t随着时间的推移，粮仓中本已消失的瘴气又出现了，很多误入其中的人，再也没能回来。我查阅古书，偶间看到#G怨冢#W后续的故事，才发现古书中描述了一种更具有神效的力量存在：#G五耀#W。传说这五耀掌管了一切事物的#G始、理、命、化、灭#W。若能释放五耀的力量，可以破除此气，还此地太平。"
		elseif selectId == 2 then
			contentStr = "\t据我调查，这地下粮仓的五层之中，也分别对应着五耀的五种力量。我这里有一个#G始耀结晶#W，在一层中使用它便能引出始耀的力量，而这时拥有全部五耀流转的妖魔鬼怪、甚至人体在离世时，都会因五耀轮转而现出理耀的属性，如果顺利的话，将会获得#G激活理耀的结晶#W。如此一来，直到你到达粮仓五层，#G引出灭耀之力#W，便能发动#G五耀律诀#W，使粮仓中的瘴气一举消灭。"
		elseif selectId == 3 then
			contentStr = "\t保一方平安本是下官分内之事，无奈我武艺平平，难胜此任，还烦请您鼎力相助。此事若成，您乃此地百姓再生父母，下官定为您树碑立传，传知后代。"
		end
		
		local MissionName;
		if MissionId > 0 then
			MissionName = GetQuestNameNM(sceneId, selfId, MissionId);
		end
		local str = "#Y";
		str = str..MissionName;
		str = str.."#W\n\n"..contentStr;
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();
		if selectId < 3 then
			AddQuestNumText(sceneId, MissionId, "继续", 0, selectId+1)
		end
		DispatchQuestEventList(sceneId, selfId, targetId);
		
		return
	end
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
		x310020_NextDayRest(sceneId, selfId)
		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
			if ret > 0 then	-- 如果可以接这个任务
				AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示接受任务信息
			else
				local strText = "未知错误，无法接新的任务"
				if ret == -1 then
					strText = "等级不足，无法接新的任务"
				elseif ret == -2 then
					strText = "等级过高，无法接新的任务"
				elseif ret == -3 then
					strText = "金钱不足，无法接新的任务"
				elseif ret == -4 then
					strText = "你不是本国玩家，无法接新的任务"
				elseif ret == -5 then
					strText = "职业类型不符，无法接新的任务"
				elseif ret == -6 then
					strText = "阵营不符，无法接新的任务"
				elseif ret == -7 then
					strText = "此人无此任务"
				end
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end

	else --如果有这个任务
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then -- 如果任务可以完成
			QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示完成信息
		else
			QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示任务未完成信息
		end
	end
end

function x310020_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if x310020_HaveAccepted(sceneId, selfId) > 0 then
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "今天已经接过任务，不能再接。");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"今天已经接过任务，不能再接。",8,2)
			return 
	end

	if GetLevel(sceneId, selfId) >= 65 then
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "你已经是65级大侠了，请到仙人谷接任务");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"你已经是65级大侠了，请到仙人谷接任务",8,2)
		return
	end
	
	--检查前置任务
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 0--如果前置任务没做直接返回
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 0--如果前置任务没做直接返回
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return 0--如果前置任务没做直接返回
		end
	end

	local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId ) -- 获取接受任务检查信息
	if ret > 0 then -- 如果可以接这个任务
		ret = AddQuestNM( sceneId, selfId, MissionId ) -- 给玩家添加任务
		if ret > 0 then
			SetQuestData(sceneId, selfId, MD_WUYAO_LVJUE_DATE[1], MD_WUYAO_LVJUE_DATE[2], MD_WUYAO_LVJUE_DATE[3], GetDayOfYear())

			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			
			SetQuestByIndex( sceneId, selfId, misIndex, 2, GetLevel(sceneId, selfId) )
			
			x310020_SetRandPosition(sceneId, selfId, MissionId)

			local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
			local message = format(x310020_g_AcceptMessage, MissionName);
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, message);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId, message, 4, 2)
			GamePlayScriptLog(sceneId, selfId, 521)

		elseif ret == 0 then
			local strText = "添加任务失败"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		elseif ret == -1 then
			local strText = "背包已满,请整理后再来接任务"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		elseif ret == -2 then
			local strText = "任务已满，添加任务失败"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
	
	end
end

--任务放弃
function x310020_ProcQuestAbandon( sceneId, selfId, MissionId )
	local ret = 0
	ret = DelQuestNM( sceneId, selfId, MissionId )
	if ret == 1 then
		local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
		local message = format(x310020_g_AbandonMessage, MissionName);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, message, 8,2)
		SetQuestData(sceneId, selfId, MD_WUYAO_LVJUE_DATE[1], MD_WUYAO_LVJUE_DATE[2], MD_WUYAO_LVJUE_DATE[3], GetDayOfYear())
	end
end

function x310020_ProcQuestAttach( sceneId, selfId, targetId, npcGuid, misIndex, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
		return
	end
	local guid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )
	local  missionState = GetQuestStateNM(sceneId, selfId, targetId, MissionId)
	if guid ~= -1 then --这个任务有完成的NPC
		if guid == npcGuid then	--点击的NPC的名字和任务中NPC的名字相同，场景也判断过了
			AddQuestTextNM( sceneId, selfId, targetId, MissionId, missionState, -1 ) -- 显示任务信息
		end
	else
		AddQuestTextNM( sceneId, selfId, targetId, MissionId, missionState, -1 ) -- 显示任务信息
	end
end

--返回1代表成功，0代表交任务失败
function x310020_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local level = GetQuestParam( sceneId, selfId, misIndex, 2 ) 

	local ret = CallScriptFunction( MISSION_SCRIPT, "ProcQuestSubmit", sceneId, selfId, targetId, selectId, MissionId )

	if ret >0 then
		SetQuestData(sceneId, selfId, MD_WUYAO_LVJUE_DATE[1], MD_WUYAO_LVJUE_DATE[2], MD_WUYAO_LVJUE_DATE[3], GetDayOfYear())

		GamePlayScriptLog(sceneId, selfId, 522)
	end
end

--物品改变
function x310020_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
	
	return 0
end


function x310020_GetRand(sceneId, selfId)
	local level = GetLevel( sceneId, selfId )
	local rand =0;
	if level >= 40 and level <= 49 then
		rand = 90;
	elseif level >=50 and level <=59 then
		rand = 70;
	elseif level >=60 and level <=69 then
		rand = 50;
	elseif level >=70 and level <=79 then
		rand = 30;
	elseif level >=80 then
		rand = 10;
	end
	return rand;
end
--杀死怪物
function x310020_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
--场景ID, 自己的ID, 怪物表位置号, 怪物objId, 任务ID
	local bSign=0;

	for i, item in x310020_g_MissionScene do
		if item.mission == MissionId then
			if item.scene == sceneId then
				bSign = 1;
				break
			end
		end
	end
	
	if bSign == 0 then
		return
	end
	
	local ItemCount=0;
	local ItemID=0;
	local ItemRand=0;
	local ItemDropNum=0;
	--场景ID, 自己的ID, 怪物表位置号, 怪物objId, 任务ID

		local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
			if humanObjId ~= -1 then
				if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
					if GetHp(sceneId, humanObjId) > 0 then
						if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--如果这个人拥有任务
							local rand=0;
							local misIndex = GetQuestIndexByID( sceneId, humanObjId, MissionId )
							if GetQuestParam( sceneId, humanObjId, misIndex, 0 ) == 1 then
								rand = x310020_GetRand(sceneId, humanObjId)
							end

							local InstIndex = 1
							ItemCount, ItemID, ItemRand, ItemDropNum = GetQuestItemNM( sceneId, humanObjId, MissionId, InstIndex )
							local dropRand = random(1, 100);
							
							if rand ~= 0 and dropRand <= rand then
							--要收集的个数，物品ID，掉落率，一次最大掉落
								if HaveItem( sceneId, humanObjId, ItemID ) <= 0 then --如果没有这个物品 
									if GetBagSpace(sceneId, humanObjId) > 0 then
										BeginQuestEvent(sceneId)
										local strText = format( "你获得了#G@itemid_%d", ItemID)
										if strText == nil then
											strText = "";
										end
										AddQuestText( sceneId, strText )
										EndQuestEvent( sceneId )
										DispatchQuestTips( sceneId, humanObjId )
										x310020_ResetMission( sceneId, humanObjId, ItemID, MissionId )	
									else
										local strText = "背包已满,请整理后再来杀怪"
										BeginQuestEvent(sceneId)
										AddQuestText(sceneId, strText);
										EndQuestEvent(sceneId)
										DispatchQuestTips(sceneId,humanObjId)
									end
								 end
							end
										

						end

					end--end
				end
			end
		end

end

--定点使用物品任务
function x310020_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	--如果该任务已经完成直接退出
	local ItemID = GetItemTableIndexByIndex( sceneId, selfId, BagIndex ) --得到物品ID
	local MissionId = GetQuestIDByItemIDNM( sceneId, selfId, ItemID )

	if MissionId == -1 then 	--没有找到这个任务
		return 0
	end

	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --任务已经完成
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end

	local scene, posx, posz, radii, MissionIdx, dispStr, bDispOther, otherStr = GetQuestUseItemInfoNM( sceneId, selfId, MissionId, ItemID )
	--if scene == -1 or sceneId ~= scene then --没有找到这个任务信息
		--return 0
	--end
	local offset = -1;

	if IsHaveQuestNM( sceneId, selfId, 8000 ) > 0 then
		offset = 1;
	elseif IsHaveQuestNM( sceneId, selfId, 8001 ) > 0 then
		offset = 2;
	elseif IsHaveQuestNM( sceneId, selfId, 8002 ) > 0 then
		offset = 3;
	elseif IsHaveQuestNM( sceneId, selfId, 8003 ) > 0 then
		offset = 4;
	elseif IsHaveQuestNM( sceneId, selfId, 8004 ) > 0 then
		offset = 5;
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

	local rp = GetQuestParam( sceneId, selfId, misIndex, 5 )
	local rFind = 0;
	for i, item in x310020_g_ItemUsePosition do
		if item.id == ItemID then
			local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )
			local rPositionx = 0
			local rPositionz =0
			
			if rp == 1 then
				rPositionx = item.x1
				rPositionz = item.z1
				rFind	= item.find1
			elseif rp == 2 then
				rPositionx = item.x2
				rPositionz = item.z2
				rFind	= item.find2
			elseif rp == 3 then
				rPositionx = item.x3
				rPositionz = item.z3
				rFind	= item.find3
			end

		if scene == -1 or sceneId ~= scene then
			if offset ~= -1 then
				local strText = format("你应该在%s(@npc_%d)使用此物品！", x310020_g_ItemUsePosition[offset].sceneName, rFind)
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText)
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId, selfId)
			end
			
			
			return 0
		end 

			local distanceRet = item.r * item.r - (rPositionx - PlayerPosX) * (rPositionx - PlayerPosX) - (rPositionz - PlayerPosZ) * (rPositionz - PlayerPosZ)

			if distanceRet <=0 then
				if offset ~= -1 then
					local strText = format("你应该在%s(@npc_%d)使用此物品！", x310020_g_ItemUsePosition[offset].sceneName, rFind )
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, strText)
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId, selfId)
				end
				return 0
			else
				
				if GetQuestParam( sceneId, selfId, misIndex, MissionIdx ) == 1 then
					return 0
				end

				--删除物品
				EraseItem(sceneId, selfId, BagIndex)

				--发送提示
				SetQuestByIndex( sceneId, selfId, misIndex, MissionIdx, 1 )

				BeginQuestEvent(sceneId)
				--AddQuestText(sceneId, dispStr)
				AddQuestText( sceneId, otherStr )
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId, selfId)

				if MissionId == 8004 then
					SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )         --by zheng
				end

				x310020_ProcQuestLogRefresh( sceneId, selfId, MissionId)
				--播放效果
				
				impactId = item.buff;
				
				if impactId ~= -1 then
					SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, impactId, 0);
				end
				return 1
			end
		
		end
	end

	if posx > 0 then --需要检查地点
		local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )

		local distanceRet = radii * radii - (posx - PlayerPosX) * (posx - PlayerPosX) - (posz - PlayerPosZ) * (posz - PlayerPosZ)
		if distanceRet <= 0 then
			local strText = format("你应该在@sceneid_%d(@npc_%d)使用此物品！", scene, rFind )
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText)
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId, selfId)
			return 0
		end
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	if GetQuestParam( sceneId, selfId, misIndex, MissionIdx ) == 1 then
		return 0
	end

	--删除物品
	EraseItem(sceneId, selfId, BagIndex)

	--发送提示
	SetQuestByIndex( sceneId, selfId, misIndex, MissionIdx, 1 )

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, dispStr)
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId, selfId)

	--播放效果
	if impactId ~= -1 then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, impactId, 0);
	end
	return 1
end


function x310020_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )	
	local str;
	str = GetQuestNameNM(sceneId, selfId, MissionId);
	--local maxcircle = GetQuestParam( sceneId, selfId, misIndex, MP_MAXCIRCLE )
	local circle;
	
	if MissionId == 8004 then
		local inst = GetQuestParam( sceneId, selfId, misIndex, 0 )
		if inst == 1 then
			circle = 5
		else
			circle= GetQuestParam( sceneId, selfId, misIndex, MP_CIRCLE )
		end
	else
		circle= GetQuestParam( sceneId, selfId, misIndex, MP_CIRCLE )
	end
	
	if circle ~= nil then
		str = str.."("..circle;
		str = str.."/".."5";
		str = str..")";
	end

	local rp = GetQuestParam( sceneId, selfId, misIndex, 5 )
	local instData1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local instData2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local instDataStr1 = ""
	local instDataStr2 = ""

	if instData1 ~= nil and instData2 ~= nil then
		 instDataStr1 = format("(%d/1)", instData1 )
		 instDataStr2 = format("(%d/1)", instData2 )
	end

	local str_target="";
	local str_proc="";
	local str_tip="";
	local posfind;
	for i, item in x310020_g_ItemUsePosition do
		if MissionId == item.mission then
			local posText="";--使用位置
			if rp == 1 then
				posfind = item.find1;
			elseif rp == 2 then
				posfind = item.find2;
			elseif rp == 3 then
				posfind = item.find3;
			end

			if posfind ~= nil then
				posText = format("(@npc_%d)", posfind )
			end

			local sceneName = item.sceneName;--场景名字
			local usedItem = item.usedItem --被使用的物品名字
			local destItem = item.destItem --要寻找的物品的名字
			str_proc = "\t到"..sceneName..posText.."使用#G"..usedItem

			if posfind ~= nil then
				str_target = "  到@npcsp_指定地点_"..posfind.."使用#G"..usedItem.."#W"..instDataStr1
			end
			if MissionId ~= 8004 then
				if instData1 > 0 then
					str_target = "  #W获得#G"..destItem.."#W"..instDataStr2
					str_proc = "\t到#G"..sceneName.."#W击败敌人，获得#G"..destItem
				end
			else
				if instData1 > 0 then
					str_target = ""
					str_proc = ""
				end
			end

	 		str_tip = "请在"..sceneName..posText.."附近使用"..usedItem.."，在结晶的发动的本场景内杀怪可以获得激活下一个耀星的结晶。"
			break
		end
	end

    BeginQuestEvent(sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                    -- 标题
                                "",                 -- 任务名字
                                str_target,               --任务目标
                                "",                         --任务NPC
                                str_proc,                   --任务攻略
                                "",                --任务描述
                                str_tip        --任务小提示
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);

end
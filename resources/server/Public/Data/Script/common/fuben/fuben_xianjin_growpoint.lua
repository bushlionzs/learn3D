-----------------------------------------
-- fuben_xianjian_growpoint.lua
-----------------------------------------
x700083_CSP_GUID_START              =   248

x700083_g_ScriptList = {700099,700098,700029,700097,700100,700101}
x700083_g_bGathered_StartList ={220,220,220,220,220,220}

function x700083_OnCreate(sceneId,growPointType,x,y)
	
	local ItemBoxId = ItemBoxEnterScene(x, y, growPointType, sceneId, 0, -1)

end



function x700083_OnOpen(sceneId,selfId,targetId)
	
	return 0;
	
end

function x700083_OnRecycle(sceneId,selfId,targetId)
	
	return 0;
	--return CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x700083_g_GrowpointId, x700083_g_ItemIndex )
end



function x700083_OnProcOver(sceneId,selfId,targetId)
	-- 采集完毕
	
	local nScriptId = GetFubenData_Param(sceneId, 1);

	local nIndex =0

	for i,item in x700083_g_ScriptList do
		nIndex = nIndex +1
		if item==nScriptId then
			break;
		end
	end

	if nIndex<=0 then
		return
	end

	
	x700083_OnAnwer(sceneId,selfId,nIndex)
	

	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end


function x700083_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


function x700083_OnAnwer(sceneId,selfId, nIndex)

	local nParam_Gathered_Start = x700083_g_bGathered_StartList[nIndex]

	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u", myGuid)

	

	for i=0, 5 do
        local paramidx = x700083_CSP_GUID_START + i
        local nGUID = GetFubenData_Param(sceneId, paramidx  )
		nGUID = format("%u", nGUID)
		
		

        if nGUID == myGuid then

			local bGathered = GetFubenData_Param(sceneId, nParam_Gathered_Start+i);
			
			
			if bGathered<=0 then
				
				x700083_GetXianJinFubenBonus(sceneId,selfId, nIndex, i)
				
				
			else
				x700083_ShowTips(sceneId, selfId, "您只能采集一次！")
				
			end

			
			break;
           
        end
    end
end


function x700083_GetXianJinFubenBonus(sceneId,selfId, nIndex, nPlayerIndex)
	local nParam_Gathered_Start = x700083_g_bGathered_StartList[nIndex]
	

	local nLevel = GetFubenData_Param(sceneId, 9);--GetLevel(sceneId,selfId)
	if nIndex==1 then
		local bufflist = {9011,9012,9013}
		
		local bFind =0
		for i, item in bufflist do
			if IsHaveSpecificImpact( sceneId, selfId, item )>0 then
				bFind =1
				break;
				
			end
		end

		if bFind>0 then
			local nMoney = nLevel*1040
			local strMoney = x700083_GetMoneyName(sceneId,nMoney)
			
			x700083_ShowTips(sceneId, selfId, format("获得%s的现银",strMoney))
			x700083_ShowMsgToTeam(sceneId, selfId, format("#G%s的现银",strMoney))
			AddMoney(sceneId, selfId, 0, nMoney)

			SetFubenData_Param(sceneId, nParam_Gathered_Start+nPlayerIndex,1);
		else
			x700083_ShowTips(sceneId, selfId, "你没有江湖请柬，无法采集")
		end

	end


	if nIndex==2 then
		local bufflist = {9011,9012,9013}
		
		local bFind =0
		for i, item in bufflist do
			if IsHaveSpecificImpact( sceneId, selfId, item )>0 then
				bFind =1
				break;
				
			end
		end
		
		local nShengWangBonus = 620*4*1.3
		if bFind>0 then
			
			
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + nShengWangBonus*2
			SetShengWang( sceneId, selfId, nShengWang )
            
            local str = format("您获得了%d点声望值的奖励。", nShengWangBonus)
			Msg2Player(sceneId,selfId,str,4,2)
			Msg2Player(sceneId,selfId,str,4,3)

			local str = format("江湖请柬使额外获得了%d点声望值的奖励。", nShengWangBonus)
			Msg2Player(sceneId,selfId,str,4,2)
			Msg2Player(sceneId,selfId,str,4,3)

			
		else
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + nShengWangBonus
			SetShengWang( sceneId, selfId, nShengWang )
            
            local str = format("您获得了%d点声望值的奖励。", nShengWangBonus)
			Msg2Player(sceneId,selfId,str,4,2)
			Msg2Player(sceneId,selfId,str,4,3)
		end

		SetFubenData_Param(sceneId, nParam_Gathered_Start+nPlayerIndex,1);
	end


	if nIndex==3 then
		local nItemId =0

		
		if nLevel>=80 then
			nItemId = 11000203
		elseif nLevel>=60 then
			nItemId = 11000202
		elseif nLevel>=40 then
			nItemId = 11000201
		else
			nItemId = 11000200
		end
		local nItemCount =37
		
		BeginAddItem(sceneId)
			AddItem( sceneId, nItemId, nItemCount )
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
			
			AddItemListToPlayer(sceneId,selfId)

			SetFubenData_Param(sceneId, nParam_Gathered_Start+nPlayerIndex,1);
		
			x700083_ShowTips(sceneId, selfId, "采集成功")
			x700083_ShowMsgToTeam(sceneId, selfId, format("#G%s个@itemid_%d",nItemCount,nItemId))
		else
			x700083_ShowTips(sceneId, selfId, "背包空间不足，无法获得物品")
		end
	end

	if nIndex==4 then
		local nItemId =0

		if nLevel>=80 then
			nItemId = 11050004
		elseif nLevel>=65 then
			nItemId = 11050003
		elseif nLevel>=50 then
			nItemId = 11050002
		else
			nItemId = 11050001
		end
		local nItemCount =37
		
		BeginAddItem(sceneId)
			AddItem( sceneId, nItemId, nItemCount )
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
			
			AddItemListToPlayer(sceneId,selfId)

			SetFubenData_Param(sceneId, nParam_Gathered_Start+nPlayerIndex,1);
			x700083_ShowTips(sceneId, selfId, "采集成功")
			x700083_ShowMsgToTeam(sceneId, selfId, format("#G%s个@itemid_%d",nItemCount,nItemId))
		else
			x700083_ShowTips(sceneId, selfId, "背包空间不足，无法获得物品")
		end
	end

	if nIndex==5 then
		local nItemId1 =0
		local nItemId2 =0
		local nItemId3 =0

		if nLevel>=70 then
			
			nItemId1 = 11990206
			nItemId2 = 11990306
			nItemId3 = 11030603

		elseif nLevel>=60 then
			nItemId1 = 11990205
			nItemId2 = 11990305
			nItemId3 = 11030603

		elseif nLevel>=50 then
			nItemId1 = 11990204
			nItemId2 = 11990304
			nItemId3 = 11030634

		else
			
			nItemId1 = 11990203
			nItemId2 = 11990303
			nItemId3 = 11030602
		end

		local nItemCount1 =8
		local nItemCount2 =8
		local nItemCount3 =8
		
		BeginAddItem(sceneId)
			AddItem( sceneId, nItemId1, nItemCount1 )
			AddItem( sceneId, nItemId2, nItemCount2 )
			AddItem( sceneId, nItemId3, nItemCount3 )
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
			
			AddItemListToPlayer(sceneId,selfId)

			SetFubenData_Param(sceneId, nParam_Gathered_Start+nPlayerIndex,1);
			x700083_ShowTips(sceneId, selfId, "采集成功")
			x700083_ShowMsgToTeam(sceneId, selfId, format("#G%s个@itemid_%d",nItemCount1,nItemId1))
			x700083_ShowMsgToTeam(sceneId, selfId, format("#G%s个@itemid_%d",nItemCount2,nItemId2))
			x700083_ShowMsgToTeam(sceneId, selfId, format("#G%s个@itemid_%d",nItemCount3,nItemId3))
		else
			x700083_ShowTips(sceneId, selfId, "背包空间不足，无法获得物品")
		end
	end

	if nIndex==6 then
		local nItemId1 =11020501
		local nItemId2 =11030405
		local nItemId3 =11030501

		

		local nItemCount1 =8
		local nItemCount2 =8
		local nItemCount3 =8

		if nLevel>=70 then
			
			nItemCount1 = 46
			nItemCount2 = 46
			nItemCount3 = 104

		elseif nLevel>=60 then
			
			nItemCount1 = 39
			nItemCount2 = 39
			nItemCount3 = 78
		else
			
			nItemCount1 = 20
			nItemCount2 = 20
			nItemCount3 = 39
		end
		
		BeginAddItem(sceneId)
			AddItem( sceneId, nItemId1, nItemCount1 )
			AddItem( sceneId, nItemId2, nItemCount2 )
			AddItem( sceneId, nItemId3, nItemCount3 )
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
			
			AddItemListToPlayer(sceneId,selfId)

			SetFubenData_Param(sceneId, nParam_Gathered_Start+nPlayerIndex,1);
			x700083_ShowTips(sceneId, selfId, "采集成功")
			x700083_ShowMsgToTeam(sceneId, selfId, format("#G%s个@itemid_%d",nItemCount1,nItemId1))
			x700083_ShowMsgToTeam(sceneId, selfId, format("#G%s个@itemid_%d",nItemCount2,nItemId2))
			x700083_ShowMsgToTeam(sceneId, selfId, format("#G%s个@itemid_%d",nItemCount3,nItemId3))
		else
			x700083_ShowTips(sceneId, selfId, "背包空间不足，无法获得物品")
		end
	end

end


function x700083_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end


function x700083_ShowMsgToTeam(sceneId, selfId, str)

	if IsPlayerStateNormal(sceneId,selfId ) <= 0 then
		return
	end
	local teamid = GetTeamId(sceneId, selfId);
	local teamnum = GetTeamSize(sceneId, selfId);
	local nearteamnum = GetNearTeamCount(sceneId, selfId);

	
	local strName =GetName(sceneId, selfId).."获得了:"
	

	if nearteamnum>0 then
		for i = 0, nearteamnum - 1 do
	
			local memberId = GetNearTeamMember(sceneId, selfId, i);
			if IsPlayerStateNormal(sceneId,memberId ) > 0 then		
--				Msg2Player(sceneId, memberId, strName..str, 0, 0)
			LuaThisScenceM2Team (sceneId, strName..str, teamid, 0, 0)
			end
			
		end
	else
		Msg2Player(sceneId, selfId, strName..str, 0, 0)
	end

	

	
end





function x700083_GetMoneyName(sceneId,nMoney)
	local ding = floor(nMoney/(1000*1000))
	local liang = floor((nMoney-ding*1000*1000)/1000)
	local wen = nMoney-(ding*1000*1000+liang*1000)

	local str=""
	if ding>0 then
		str = str..format("%d锭",ding)
	end

	if liang>0 then
		str = str..format("%d两",liang)
	end

	if wen>0 then
		str = str..format("%d文",wen)
	end

	return str;
	
end
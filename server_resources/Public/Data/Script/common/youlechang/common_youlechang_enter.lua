--大都南进入天上人间·麒麟脚本

x310327_g_ScriptId = 310327
x310327_g_ask ={"进入天上人间·麒麟(65级)","确定"}
x310327_g_answer ={"\t想进入大都天上人间·麒麟么？那里有着无数热闹好玩的新鲜玩法，钧窑和勾栏曲台也在其中。\n\t天上人间·麒麟在每周六、日零点正式开放！每周六、日第一次进入天上人间·麒麟需要#R花费10两现银或银卡#W。\n\t你想现在进去看看么？"}

x310327_g_Item = 12035005 -- 无敌幸运星

function x310327_IsEnterFirst(sceneId ,selfId)
	local today = GetDayOfYear()
	local lastDay = GetQuestData(sceneId, selfId, MD_YOULECHANG_DATE[1], MD_YOULECHANG_DATE[2], MD_YOULECHANG_DATE[3])
	if today ~= lastDay then
		return 1
	end
	
	
	return 0
end

function x310327_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		--print("x310327_ProcEventEntry",which)
		local level =GetLevel(sceneId, selfId)
		if which == 0 then
				BeginQuestEvent(sceneId)
				AddQuestNumText(sceneId, x310327_g_ScriptId, x310327_g_ask[1],0,1)
		  	EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x310327_g_answer[1])
			AddQuestNumText(sceneId, x310327_g_ScriptId, x310327_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			--local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            
           --local  WorldID = GetWorldID(sceneId,selfId)
			--local  toplevel = GetToplistCount(WorldID,0)
			--local  guid,LevelMax = GetToplistInfo(WorldID,0,toplevel-1)
		--	if LevelMax < 65 then
		--		BeginQuestEvent(sceneId)
		--		AddQuestText(sceneId,"\t天上人间·麒麟开启条件不够，到时候再来吧。")				
		--		EndQuestEvent(sceneId)
		--		DispatchQuestEventList(sceneId,selfId,NPCId)
		--			
		--		return
		--	end
	
	
            if level>= 65 then
            	local subsillertype=1
            	if GetWeek() ~= 0 and GetWeek() ~= 6 then
            		BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t天上人间·麒麟只有在周六、日才会开启，到时候再来吧。")				
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,NPCId)
					return
				end
				
				local curTime = GetMinOfDay()
				if curTime < 540 then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t天上人间·麒麟还未开放，请上午9：00以后再来。")				
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,NPCId)
					return
				end			
				
				if curTime >= 1380 then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t天上人间·麒麟已经关闭，下次开放时间再来吧。")				
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,NPCId)
					return
				end
				
				
--				if count >= 5 then
--		       		BeginQuestEvent(sceneId)
--					AddQuestText(sceneId,"\t天上人间·麒麟每天只能进五次。")				
--					EndQuestEvent(sceneId)
--					DispatchQuestEventList(sceneId,selfId,NPCId)
--					return
--				end
--		
				local res =  GetSillerMode(sceneId, selfId) 
				print("ss",res)
				local ret = x310327_IsEnterFirst(sceneId ,selfId)
   				if ret == 1 then  --第一次要扣钱
					if GetSillerMode(sceneId, selfId) == 1 then
						if CostMoney(sceneId, selfId, 0, 10000) == -1 then				--现银是0   银卡是1	
							if CostMoney(sceneId, selfId, 1, 10000) == -1 then
								BeginQuestEvent(sceneId)
								AddQuestText(sceneId, "很抱歉，当天第一次进入天上人间·麒麟要花费10两现银或银卡");
								EndQuestEvent(sceneId)
								DispatchQuestTips(sceneId,selfId)	
								Msg2Player(sceneId,selfId,"很抱歉，当天第一次进入天上人间·麒麟要花费10两现银或银卡",8,2)				
								return
							else
								subsillertype	=	0
							end
						else
							subsillertype	=	1
						end
					else
						if CostMoney(sceneId, selfId,1, 10000) == -1 then
							if CostMoney(sceneId, selfId, 0, 10000) == -1 then	
								BeginQuestEvent(sceneId)
								AddQuestText(sceneId, "很抱歉，当天第一次进入天上人间·麒麟要花费10两现银或银卡");
								EndQuestEvent(sceneId)
								DispatchQuestTips(sceneId,selfId)	
								Msg2Player(sceneId,selfId,"很抱歉，当天第一次进入天上人间·麒麟要花费10两现银或银卡",8,2)				
								return
							else
								subsillertype	=	1
							end
						else
							subsillertype =	0
						end
					end
				end
				if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,0) == 0 then
					--print("CheckCountryBattleLiteSceneTrans")
					return
				end
				
				if ret == 1  then
					-- 没有就添加道具
					if HaveItemInBag(sceneId, selfId, x310327_g_Item) <= 0 then
						BeginAddItem( sceneId )	
						AddBindItem( sceneId, x310327_g_Item, 1)
						local ret = EndAddItem( sceneId, selfId )
						if ret > 0 then
							AddItemListToPlayer(sceneId,selfId)
							
							local msg = format("#Y获得#G1个#Y#{_ITEM%d}",x310327_g_Item)
							Msg2Player(sceneId,selfId,msg,8,2)
						else	
							local msg = format("#Y背包空间不足，无法得到#{_ITEM%d}！",x310327_g_Item)			
							Msg2Player(sceneId,selfId,msg,8,3)
							
							---------------退钱。
							if subsillertype ==	1 then --现银
								AddMoney( sceneId, selfId, 0, 10000 )
							elseif subsillertype == 0 then
								AddMoney( sceneId, selfId, 1, 10000 )
							end
							return
						end
					end
					
					local bagIndex = FindFirstBagIndexOfItem( sceneId, selfId, x310327_g_Item)
					
					if bagIndex >= 0 then
						GamePlayScriptLog(sceneId, selfId, 1611)
						local count = GetCountryParam( sceneId, 0, CD_YOULECHANG_CAIPIAO1)
						SetCountryParam( sceneId, 0, CD_YOULECHANG_CAIPIAO1, count+1)
						--local time = GetItemParam( sceneId, selfId, bagIndex, 8, 2)
						SetItemParam( sceneId, selfId, bagIndex, 4, 2, count )
						SetItemParam( sceneId, selfId, bagIndex, 8, 2, GetDayOfYear() )
					end
				end
				
				if IsHaveSpecificImpact( sceneId, selfId, 7717) == 1 then
					CancelSpecificImpact( sceneId, selfId, 7717)	
				end
				SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, 7717, 0)
								
				
				NewWorld( sceneId, selfId, 39, 204 + random( -2,2 ), 203 + random( -2, 2), 310327)
				if ret == 1 then  
           		if subsillertype	==	1 then
           			Msg2Player(sceneId,selfId,"您花费了10两现银进入了天上人间·麒麟。",8,2)	
           		else
           			Msg2Player(sceneId,selfId,"您花费了10两银卡进入了天上人间·麒麟。",8,2)		
	           		end
           		end
           		local today = GetDayOfYear()
           		SetQuestData(sceneId, selfId, MD_YOULECHANG_DATE[1], MD_YOULECHANG_DATE[2], MD_YOULECHANG_DATE[3], today)
           		
           		
            else 
            	BeginQuestEvent(sceneId)
            	AddQuestText(sceneId,"\t很抱歉，只有不低于65级的玩家才能进入天上人间·麒麟。")
            	EndQuestEvent()
            	DispatchQuestEventList(sceneId, selfId, NPCId)
            end
        end
	

	
	
end


--**********************************

--列举事件

--**********************************

function x310327_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
		local minlevel = GetTopListInfo_MinLevel(GetWorldID(sceneId, selfId))
		-- if minlevel >=65 then
			AddQuestNumText(sceneId, x310327_g_ScriptId, x310327_g_ask[1],3,1)
		--end
end









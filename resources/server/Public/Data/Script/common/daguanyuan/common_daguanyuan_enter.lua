--大都南进入天上人间·梦聊脚本

x310368_g_ScriptId = 310368
x310368_g_ask ={"进入天上人间·梦聊(85级)","确定"}
x310368_g_answer ={"\t想进入大都天上人间·梦聊么？那里有着无数热闹好玩的新鲜玩法，画皮和倩女幽魂也在其中。\n\t天上人间·梦聊在每周六、日零点正式开放！每周六、日第一次进入天上人间·梦聊需要#R花费10两现银或银卡#W。\n\t你想现在进去看看么？"}

x310368_g_Item = 12035005 -- 无敌幸运星

function x310368_IsEnterFirst(sceneId ,selfId)
	local today = GetDayOfYear()
	local lastDay = GetQuestData(sceneId, selfId, MD_DAGUANYUAN_DATE[1], MD_DAGUANYUAN_DATE[2], MD_DAGUANYUAN_DATE[3])
	if today ~= lastDay then
		return 1
	end
	
	
	return 0
end

function x310368_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本

		local level =GetLevel(sceneId, selfId)
		if which == 0 then
				BeginQuestEvent(sceneId)
				AddQuestNumText(sceneId, x310368_g_ScriptId, x310368_g_ask[1],0,1)
		  	EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x310368_g_answer[1])
			AddQuestNumText(sceneId, x310368_g_ScriptId, x310368_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
            if level>= 85 then
            	local subsillertype=1
            	if GetWeek() ~= 0 and GetWeek() ~= 6 then
            		BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t天上人间·梦聊只有在周六、日才会开启，到时候再来吧。")				
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,NPCId)
					return
				end
										
			    local curTime = GetMinOfDay()
				if curTime < 540 then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t天上人间·梦聊还未开放，请上午9：00以后再来。")				
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,NPCId)
					return
				end			
				if curTime >= 1380 then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t天上人间·梦聊已经关闭，下次开放时间再来吧。")				
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,NPCId)
					return
				end
									
				local res =  GetSillerMode(sceneId, selfId) 
				print("ss",res)
				local ret = x310368_IsEnterFirst(sceneId ,selfId)
				
   				if ret == 1 then  --第一次要扣钱  		
   					if GetBagSpace(sceneId, selfId) <= 0 then
							Msg2Player(sceneId, selfId, "背包已满，无法获得天上人间·梦聊乐透彩票", 0, 2)
							Msg2Player(sceneId, selfId, "背包已满，无法获得天上人间·梦聊乐透彩票", 0, 3)
							return
						end		
					if GetSillerMode(sceneId, selfId) == 1 then
						if CostMoney(sceneId, selfId, 0, 10000) == -1 then				--现银是0   银卡是1	
							if CostMoney(sceneId, selfId, 1, 10000) == -1 then
								BeginQuestEvent(sceneId)
								AddQuestText(sceneId, "很抱歉，当天第一次进入天上人间·梦聊要花费10两现银或银卡");
								EndQuestEvent(sceneId)
								DispatchQuestTips(sceneId,selfId)	
								Msg2Player(sceneId,selfId,"很抱歉，当天第一次进入天上人间·梦聊要花费10两现银或银卡",8,2)				
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
								AddQuestText(sceneId, "很抱歉，当天第一次进入天上人间·梦聊要花费10两现银或银卡");
								EndQuestEvent(sceneId)
								DispatchQuestTips(sceneId,selfId)	
								Msg2Player(sceneId,selfId,"很抱歉，当天第一次进入天上人间·梦聊要花费10两现银或银卡",8,2)				
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

				if IsHaveSpecificImpact( sceneId, selfId, 7718) == 1 then
					CancelSpecificImpact( sceneId, selfId, 7718)	
				end
				SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, 7718, 0)
				
				NewWorld( sceneId, selfId, 40, 127 + random( -2,2 ), 140 + random( -2, 2), 310368)
				if ret == 1 then  
           		if subsillertype	==	1 then
           			Msg2Player(sceneId,selfId,"您花费了10两现银进入了天上人间·梦聊。",8,2)	
           		else
           			Msg2Player(sceneId,selfId,"您花费了10两银卡进入了天上人间·梦聊。",8,2)		
	           		end
	           	CallScriptFunction(310362,"GiveItem",sceneId,selfId)	
           		end
           		local today = GetDayOfYear()
           		SetQuestData(sceneId, selfId, MD_DAGUANYUAN_DATE[1], MD_DAGUANYUAN_DATE[2], MD_DAGUANYUAN_DATE[3], today)
           		
           		
            else 
            	BeginQuestEvent(sceneId)
            	AddQuestText(sceneId,"\t很抱歉，只有不低于85级的玩家才能进入天上人间·梦聊。")
            	EndQuestEvent()
            	DispatchQuestEventList(sceneId, selfId, NPCId)
            end
        end
	

	
	
end


--**********************************

--列举事件

--**********************************

function x310368_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
		local minlevel = GetTopListInfo_MinLevel(GetWorldID(sceneId, selfId))
		-- if minlevel >=65 then
			AddQuestNumText(sceneId, x310368_g_ScriptId, x310368_g_ask[1],3,1)
		--end
end









--MisDescBegin


x300983_g_ScriptId = 300983

x300983_g_MissionId_List = {
							7800,	--楼兰的对应任务号
							7801,	--天山的对应任务号
							7802,	--昆仑的对应任务号
							7803,	--敦煌的对应任务号
							}
x300983_g_MissionId = 7803


x300983_g_Title = "防御之路"

x300983_g_Profession_Enum = {	--12种职业
								0,	--武士  
								1,	--剑侠  
								2, 	--骑射  
								3, 	--火枪  
								4, 	--先知  
								5,	--萨满  
								6, 	--十字军
								7, 	--圣火使
								8, 	--刺客  
								9, 	--近卫军
								10,	--隐修士
								11,	--僧侣  
								0,	--武士  
								2, 	--骑射  
								3, 	--火枪  
								4, 	--先知  
								5,	--萨满 
								6, 	--十字军
								8, 	--刺客  
								10,	--隐修士
								2, 	--骑射  
								3, 	--火枪  
								4, 	--先知   
								8, 	--刺客  
							}
							
x300983_g_Profession_Desc = {	--12种职业
								"武士",
								"剑侠",  
								"骑射",  
								"火枪",  
								"先知",  
								"萨满",  
								"十字军",
								"圣火使",
								"刺客",  
								"近卫军",
								"隐修士",
								"僧侣",
								"武士", 
								"骑射",  
								"火枪",  
								"先知",  
								"萨满",  
								"十字军",
								"刺客",  
								"隐修士",
								"骑射",  
								"火枪",  
								"先知",   
								"刺客",  
							}							

--x300983_g_Profession  = 0   --全局变量，每次点击任务npc的时候会随机一个
--x300983_g_Profession_Desc = "" --全局变量，每次点击任务npc的时候随机一个
--x300983_g_Kill_Count  = 0   --全局变量，记录击败某种职业的玩家的个数  
--x300983_g_Completed   = 0   --全局变量，标记是否完成任务
x300983_g_Quest_Max_Count = 1	--全局变量，本任务只限接1次,使用专精之书·防御可以多接1次


x300983_g_MissionName = "【个人】防御之路"
x300983_g_MissionInfo				= 	"\t防御与攻击的关系很微妙。想要追求至高的防御，没有一定的攻击也是没有意义的。所以我要给你一个考验——击败某一个职业的6名敌国高手。通过了这个考验之后我会帮你接近那至高的防御。#G（击败的玩家不低于自己20级才有效。）" 
x300983_g_Mission_Kill_Cnt = 6				   

x300983_g_CommitNPC     = "@npc_141103"

--print(".........................................")					   
--需要的等级
function x300983_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	if GetCurCountry(sceneId,selfId) ~=3 or GetLevel(sceneId, selfId) < 80 then
		return -1
	end	

	--PrintStr("x300983_ProcEnumEvent")
	local state = GetQuestStateNM(sceneId,selfId,NPCId,x300983_g_MissionId)
	AddQuestTextNM( sceneId, selfId, NPCId, x300983_g_MissionId, state, -1 )

end


--D:\workspace\khan2_run\Public\Data\Script\common\cangbaotu\common_gujitanyi.lua
--如果没有任务；接任务
--如果有任务，显示是否继续或者任务完成
function x300983_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)
	
	if GetGameOpenById(1060)<=0 then
		Msg2Player(sceneId, selfId, "此活动已关闭，请耐心等待开启。", 0, 3)
		return
	end
	
	--PrintStr("x300983_ProcEventEntry")

	--判断是否有专精之书·防御道具,yes 则可以接第二次;否则只能接一次
	local nCntItem_tuozhanzhishu = GetItemCountInBag( sceneId, selfId, 11010125)
	--PrintNum(nCntItem_tuozhanzhishu)
	
	
	local nCnt = x300983_GetDayCount(sceneId, selfId) + 1
	print("-----------------nCntItem_tuozhanzhishu",nCntItem_tuozhanzhishu,"nCnt",nCnt)
    if IsHaveQuestNM( sceneId, selfId, x300983_g_MissionId ) == 0 then	-- 如果没有这个任务 
				
				if nCnt == 1 then --第一次接任务
							x300983_DistachMission_Info(sceneId,selfId,NPCId,1)
				elseif  nCnt == 2 then
							if nCntItem_tuozhanzhishu > 0  then 
															--已经接了一次任务,有专精之书·防御
															--消耗一次专精之书·防御道具
															--DelItemByIDInBag( sceneId, selfId, 11010125, 1)
															--使用专精之书·防御道具可以多接一次任务,在ProcQuestAccept里面计数
															x300983_DistachMission_Info(sceneId,selfId,NPCId,2)
															--Msg2Player( sceneId, selfId, "接受防御任务消耗专精之书·防御道具一个", 8, 3)
							else
															BeginQuestEvent(sceneId)
															AddQuestText( sceneId, "#Y"..x300983_g_MissionName)
															AddQuestText(sceneId,"\t您今天已经完成一次本任务了，如果有#G专精之书·防御#W可以再领取一次本任务。\n\t#G专精之书·防御#W可以在我这里的#G专精天赋金币商店#W购买。")															
															EndQuestEvent(sceneId)
															DispatchQuestEventList(sceneId, selfId, NPCId)
															return -1  
							end
				else --超过2次了					
							BeginQuestEvent(sceneId)
							AddQuestText( sceneId, "#Y"..x300983_g_MissionName)
							AddQuestText(sceneId,"\t今天已经达到接任务的上限，请改天再来。\n")
							EndQuestEvent(sceneId)
							DispatchQuestEventList(sceneId, selfId, NPCId)
							return -1  
				end
					
					
					
    else--检查是不是可以提交    
				local misIndex = GetQuestIndexByID( sceneId, selfId, x300983_g_MissionId)
		        local isFinish = GetQuestParam( sceneId, selfId, misIndex, 7)
		        
				if isFinish > 0 then -- 如果任务可以完成
							    --x300340_MissionComplateInfo( sceneId, selfId, targetId, MissionId) -- 显示完成信息
							  	BeginQuestEvent( sceneId)
								AddQuestText( sceneId, "#Y"..x300983_g_MissionName.."#W\n\t不错，不错。按照咱们的约定，我会帮助你的防御更上一层楼。" )
								AddQuestText( sceneId, "\n#Y任务奖励： ")
								AddQuestText( sceneId, "专防训练点数：13点 ")	
								EndQuestEvent( sceneId)
								DispatchQuestInfoNM( sceneId, selfId, NPCId, x300983_g_ScriptId, x300983_g_MissionId)
								--SetQuestByIndex( sceneId, selfId, misIndex, 7,0) --完成任务标志清0
								
				else
								--PrintNum(isFinish)			        
								--x300340_MissionContinue( sceneId, selfId, targetId, x300983_g_MissionId) -- 显示任务未完成信息
								
								local nRemain = 0
								local today = GetDayOfYear()
								local lastday = GetQuestData(sceneId, selfId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3])
								if lastday ~= today then --如果是第一次杀人
									nRemain = x300983_g_Mission_Kill_Cnt
								else										
									local nKillCnt = GetQuestParam( sceneId, selfId, misIndex , 2 )
									nRemain = x300983_g_Mission_Kill_Cnt - nKillCnt
								end
								--local nIdx     = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDCONTEND_KILL_OTHER)
								local nIdx		 = GetQuestParam( sceneId, selfId, misIndex , 3)          --获取随机的下标
								print("------------------------------->",nIdx)
								if nIdx <=0 or nIdx > getn(x300983_g_Profession_Desc) then
									return -1
								end
								local strPro   = x300983_g_Profession_Desc[nIdx]								
								BeginQuestEvent( sceneId)
								AddQuestText( sceneId, "#Y"..x300983_g_MissionName)
							    AddQuestText( sceneId, "\t这个很困难吗？继续加油吧，只有付出才有回报。\n\t你还需要击败"..nRemain.."个#R"..strPro.."#W职业的敌国玩家或者#R练功人偶")
								EndQuestEvent()
							    DispatchQuestEventList( sceneId, selfId, NPCId)
							    --PrintNum(GetQuestParam( sceneId, selfId, misIndex, 0))
				end
    end
end

function x300983_DistachMission_Info(sceneId,selfId,NPCId,nFlag)
							--local misIndex = GetQuestIndexByID( sceneId, selfId, x300983_g_MissionId ) 
							local nIndex  = random(1,24)           
							--SetQuestParam( sceneId, selfId, misIndex , 3 ,nIndex)
							SetPlayerRuntimeData(sceneId,selfId,RD_GUILDCONTEND_KILL_OTHER,nIndex)	--保存全局变量            
							--PrintStr("nIndex")
							--PrintNum(nIndex)                        
							---local misIndex = GetQuestIndexByID( sceneId, selfId, x300983_g_MissionId ) 
							---SetQuestByIndex(sceneId, selfId, misIndex,1,nIndex)
							---PrintNum(GetQuestParam(sceneId, selfId, misIndex,1))
							---assert(GetQuestParam(sceneId, selfId, misIndex,1) == nIndex)
							
								
							
							if nFlag == 2 then		
												BeginQuestEvent( sceneId)
												AddQuestText( sceneId, "#Y"..x300983_g_MissionName)
												AddQuestText( sceneId, x300983_g_MissionInfo)
												--任务目标
												AddQuestText( sceneId, "#Y任务目标：")
												AddQuestText( sceneId, format( "击败某种职业的敌国玩家或者练功人偶#R6个#W。") )
												AddQuestText( sceneId, "\n#G小提示：\n\t接本次任务需要消耗一本专精之书·防御，您确认要接受此任务吗?")
												AddQuestText( sceneId, "\n#Y任务奖励： ")
												AddQuestText( sceneId, "专防训练点数：13点 ")	
												EndQuestEvent()
					
												DispatchQuestInfoNM( sceneId, selfId, NPCId, x300983_g_ScriptId, x300983_g_MissionId);
							else
												BeginQuestEvent( sceneId)
												AddQuestText( sceneId, "#Y"..x300983_g_MissionName)
												AddQuestText( sceneId, x300983_g_MissionInfo)
												--任务目标
												AddQuestText( sceneId, "#Y任务目标：")
												AddQuestText( sceneId, format( "击败某种职业的敌国玩家或者练功人偶#R6个#W。") )
												AddQuestText( sceneId, "\n#Y任务奖励： ")
												AddQuestText( sceneId, "专防训练点数：13点 ")	
													
												EndQuestEvent()
					
												DispatchQuestInfoNM( sceneId, selfId, NPCId, x300983_g_ScriptId, x300983_g_MissionId);
							end
											

end


function x300983_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	--PrintStr("x300983_ProcQuestAccept")
		if GetInherenceLevel(sceneId, selfId) < 50  then
			Msg2Player(sceneId, selfId, "天赋等级不到50级，不能领取此任务", 0, 2)
			Msg2Player(sceneId, selfId, "天赋等级不到50级，不能领取此任务", 0, 3)
			return -1
		end
    if IsHaveQuestNM( sceneId, selfId, x300983_g_MissionId) == 0 then   -- 没有这个任务
				        -- 检查当天是否已经做过这个任务,如果接过一次而且有专精之书·防御道具的话，可以再接一次任务

				        ---------------------------------if x300983_GetDayCount(sceneId, selfId) ~= 0 then
						---------------------------------					local str = "你今天已经完成过这个任务，请明天再来"
						---------------------------------					BeginQuestEvent( sceneId)
						---------------------------------					AddQuestText( sceneId, str )
						---------------------------------					EndQuestEvent()
						---------------------------------					DispatchQuestTips( sceneId, selfId)
						---------------------------------					Msg2Player(sceneId, selfId, str, 8, 2)
						---------------------------------					return
				        ---------------------------------end
						--如果不是本国的成员，则无法接任务
						if GetCurCountry(sceneId, selfId) ~= 3 then
							--print("00000000000000000000000000")
							return -1
						end
						
						local nCnt = x300983_GetDayCount(sceneId, selfId)
						if nCnt == 1 then --已经接了一次任务
								local nCntItem_tuozhanzhishu = GetItemCountInBag( sceneId, selfId, 11010125)
								if nCntItem_tuozhanzhishu > 0 then
										DelItemByIDInBag( sceneId, selfId, 11010125, 1)
										Msg2Player( sceneId, selfId, "消耗专精之书·防御道具一个", 8, 2)
										Msg2Player( sceneId, selfId, "消耗专精之书·防御道具一个", 8, 3)
								else
										Msg2Player( sceneId, selfId, "没有消耗专精之书·防御道具，无法接第二次任务", 8, 2)
										Msg2Player( sceneId, selfId, "没有消耗专精之书·防御道具，无法接第二次任务", 8, 3)
										return -1
								end
						end
							
						
						local ret	= AddQuest( sceneId, selfId, x300983_g_MissionId, x300983_g_ScriptId, 1, 0, 0) --注意这里的参数
						if ret == 0 then
											local str = "任务已满，任务接受失败！"
											BeginQuestEvent( sceneId)
											AddQuestText( sceneId, str )
											EndQuestEvent( sceneId)
											DispatchQuestTips( sceneId, selfId)
											Msg2Player(sceneId, selfId, str, 8, 2)
											return 0
						else
											local nIndex = GetPlayerRuntimeData(sceneId, selfId,RD_GUILDCONTEND_KILL_OTHER)
											local misIndex = GetQuestIndexByID( sceneId, selfId, x300983_g_MissionId)
											--local nIndex =   GetQuestParam(sceneId, selfId, misIndex, 3)
											--PrintNum(nIndex)
											SetQuestByIndex(sceneId, selfId,misIndex,3,nIndex)
											-- 更新接任务时间
											x300983_SetDayCount(sceneId, selfId)   								
											BeginQuestEvent( sceneId)
											AddQuestText( sceneId, "您接受了【个人】防御之路的任务");
											EndQuestEvent( sceneId);
											DispatchQuestTips( sceneId, selfId);
											Msg2Player( sceneId, selfId, "您接受了【个人】防御之路的任务", 8, 2)
											Msg2Player( sceneId, selfId, "您接受了【个人】防御之路的任务", 8, 3)
								
			
					    end
    else
						DelQuest(sceneId, selfId , x300983_g_MissionId) --完成任务后删除任务  
						--x300983_SetDayCount(sceneId, selfId)
			        
						
						--to be fixed!!!
						--shangyu提供接口,奖励13点专精天赋中职业专防总技能点数
						local nExp = 13
						SetInherenceZhuanFangExp(sceneId, selfId, nExp)
						--PrintNum(13)
						
						Msg2Player( sceneId, selfId, "您获得了13点专防技能点数", 8, 2)
						Msg2Player( sceneId, selfId, "您获得了13点专防技能点数", 8, 3)
						
			        
    end
end















--core.lua调用本脚本的接口
--刷新击败的玩家个数
--判断dieId的职业是否是接任务的指定的击败的职业
--如果是则计数加1
function x300983_UpdateKillCountProfession(sceneId,selfId,dieId)
	if selfId == dieId then --处理自杀的情况
		return -1
	end
	if IsHaveQuestNM( sceneId, selfId, x300983_g_MissionId ) == 0 then	-- 如果没有这个任务
							return
	else	

						    local teamSize = GetNearTeamCount( sceneId, selfId)
						    if teamSize <= 1 then -- 非组队，单独做任务
						    
											local misIndex 		=  GetQuestIndexByID( sceneId, selfId, x300983_g_MissionId )
											local nIndex 		=  GetQuestParam(sceneId, selfId, misIndex,3)
											local nProfession   =  x300983_g_Profession_Enum[nIndex]
											
											--判断当前杀人的数目,这里仅仅借用了计算接任务次数的MD的天数
											local today = GetDayOfYear()
											local lastday = GetQuestData(sceneId, selfId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3])
											if lastday ~= today then --如果是第一次杀人
														if nProfession      == GetZhiye(sceneId, dieId) and GetCurCountry(sceneId,dieId) ~=3  then 
																local nKillCnt = 1
																SetQuestByIndex(sceneId, selfId, misIndex,2,nKillCnt)
																SetQuestData(sceneId, selfId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3], today)
																x300983_QuestLogRefresh( sceneId, selfId, x300983_g_MissionId)
														end
											else	
														if nProfession      == GetZhiye(sceneId, dieId) and GetCurCountry(sceneId,dieId) ~=3 then          --如果被击败的玩家的职业和接任务的随机的玩家职业符合
																local nKillCnt = GetQuestParam( sceneId, selfId, misIndex , 2 )
																nKillCnt       = nKillCnt + 1
																SetQuestByIndex(sceneId, selfId, misIndex,2,nKillCnt) --使用第3位保存本次任务击败的某种职业的玩家的数量 
																if nKillCnt >= x300983_g_Mission_Kill_Cnt then
																	SetQuestByIndex(sceneId, selfId, misIndex,7, 1 ) --设置任务完成标志
																	SetQuestByIndex(sceneId, selfId, misIndex,0, 1 ) --设置任务完成标志
																end
																x300983_QuestLogRefresh( sceneId, selfId, x300983_g_MissionId)
														end	
											 end
						    
						    else
								        for i = 0, teamSize - 1 do
								            local memberId = GetNearTeamMember( sceneId, selfId, i)
								            if memberId >= 0 and IsPlayerStateNormal( sceneId, memberId) == 1 then
													if IsHaveQuestNM( sceneId, memberId, x300983_g_MissionId) ~= 0 then -- 如果该成员接受了防御之路			
																				local misIndex = GetQuestIndexByID( sceneId, memberId, x300983_g_MissionId)
															                    if GetQuestParam( sceneId, memberId, misIndex, 0) == 0 or GetQuestParam( sceneId, memberId, misIndex, 7) == 0 then
																								local misIndex 		=  GetQuestIndexByID( sceneId, memberId, x300983_g_MissionId )
																								local nIndex 		=  GetQuestParam(sceneId, memberId, misIndex,3)
																								local nProfession   =  x300983_g_Profession_Enum[nIndex]
																								
																								--判断当前杀人的数目,这里仅仅借用了计算接任务次数的MD的天数
																								local today = GetDayOfYear()
																								local lastday = GetQuestData(sceneId, memberId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3])
																								if lastday ~= today then --如果是第一次杀人
																											if nProfession      == GetZhiye(sceneId, dieId) and GetCurCountry(sceneId,dieId) ~=3  then 
																													local nKillCnt = 1
																													SetQuestByIndex(sceneId, memberId, misIndex,2,nKillCnt)
																													SetQuestData(sceneId, memberId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3], today)
																													x300983_QuestLogRefresh( sceneId, memberId, x300983_g_MissionId)
																											end
																								else	
																											if nProfession      == GetZhiye(sceneId, dieId) and GetCurCountry(sceneId,dieId) ~=3 then          --如果被击败的玩家的职业和接任务的随机的玩家职业符合
																													local nKillCnt = GetQuestParam( sceneId, memberId, misIndex , 2 )
																													nKillCnt       = nKillCnt + 1
																													SetQuestByIndex(sceneId, memberId, misIndex,2,nKillCnt) --使用第3位保存本次任务击败的某种职业的玩家的数量 
																													if nKillCnt >= x300983_g_Mission_Kill_Cnt then
																														SetQuestByIndex(sceneId, memberId, misIndex,7, 1 ) --设置任务完成标志
																														SetQuestByIndex(sceneId, memberId, misIndex,0, 1 ) --设置任务完成标志
																													end
																													x300983_QuestLogRefresh( sceneId, memberId, x300983_g_MissionId)
																											end	
																								 end
																				end
													end
										  end
									end
							end


	end
end


--提交任务
--from common_cangbaotu.lua
function x300983_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	--判断是否有任务
	local bHaveMission = IsHaveQuestNM(sceneId, selfId, x300983_g_MissionId);
	local misIndex 		=  GetQuestIndexByID( sceneId, selfId, MissionId )
	local nKillCnt 		=  GetQuestParam(sceneId, selfId, misIndex,2)
	if bHaveMission > 0 then
				if nKillCnt >= x300983_g_Mission_Kill_Cnt then
						local str = "完成任务"
						Msg2Player(sceneId,selfId,str,8,2)
						BeginQuestEvent(sceneId);
						AddQuestText(sceneId, str);
						EndQuestEvent();
						DispatchQuestTips(sceneId, selfId)						
						
						--更新接任务次数
						x300983_SetDayCount(sceneId, selfId)
						
						--完成任务之后把次数重新置为1
						--x300983_g_Quest_Max_Count = 1
						return
				end
	end
end



--更新总的接任务的次数，默认是1次，
--使用专精之书·防御道具的时候，修改为2次
--此函数仅供专精之书·防御道具脚本调用
--function x300983_Update_Quest_Max_Count(sceneID,selfId)
--	--x300983_g_Quest_Max_Count = 2
--	local misIndex = GetQuestIndexByID( sceneId, selfId, x300983_g_MissionId )
--	local nQuest_Max_Count = GetQuestParam( sceneId, selfId, misIndex , 1 )
--	nQuest_Max_Count = 2
--	SetQuestByIndex(sceneId, selfId, misIndex,1,nQuest_Max_Count)					  --使用第2位保存每天接任务的最大次数 
--end


--放弃任务也记次
--********************************************************************
--放弃
--********************************************************************
function x300983_ProcQuestAbandon( sceneId, selfId, MissionId )
	--放弃任务同样计数
	--PrintStr("x300983_ProcQuestAbandon")
	DelQuest( sceneId, selfId, x300983_g_MissionId )
	--x300983_SetDayCount(sceneId, selfId)   
	Msg2Player(sceneId, selfId, "您放弃了任务【个人】防御之路！", 0, 2)
end


---------------------------------------------------------------------------------------------------
--取得此任务当天当前已完成次数
--from common_daguanyuan_tianfu.lua
---------------------------------------------------------------------------------------------------
function x300983_GetDayCount(sceneId, selfId)
	--PrintStr("x300983_GetDayCount")
	if x300983_g_Quest_Max_Count > 0 then
		local today = GetDayOfYear()
		local lastday = GetQuestData(sceneId, selfId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3])
		if lastday ~= today then
			return 0
		end

		local daycount =  GetQuestData(sceneId, selfId, MD_FANGYUZHILU_DAYCOUNT[1], MD_FANGYUZHILU_DAYCOUNT[2], MD_FANGYUZHILU_DAYCOUNT[3])
		return daycount

	end
	return 0
end



-------------------------------------`--------------------------------------------------------------
--更新当天接任务次数
--from common_daguanyuan_tianfu.lua
---------------------------------------------------------------------------------------------------
function x300983_SetDayCount(sceneId, selfId)
	--PrintStr("x300983_SetDayCount")
    local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3])
	if lastday ~= today then
			
		SetQuestData(sceneId, selfId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_FANGYUZHILU_DAYCOUNT[1], MD_FANGYUZHILU_DAYCOUNT[2], MD_FANGYUZHILU_DAYCOUNT[3], 1)		
	else
				
		local daycount = GetQuestData(sceneId, selfId, MD_FANGYUZHILU_DAYCOUNT[1], MD_FANGYUZHILU_DAYCOUNT[2], MD_FANGYUZHILU_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, MD_FANGYUZHILU_DAYCOUNT[1], MD_FANGYUZHILU_DAYCOUNT[2], MD_FANGYUZHILU_DAYCOUNT[3], daycount+1)		
	end
end


--**********************************

--击败怪物或玩家

--**********************************

function x300983_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId) 
	--print("----------------->","x300983_ProcQuestObjectKilled")
	--需要在这里判断是否击败的练功人偶的怪物！
	--to be fixed!!!
	if objdataId ~= 9526 and objdataId ~= 9527 then --练功人偶只对防御任务有效
		return -1
	end
	
    local teamSize = GetNearTeamCount( sceneId, selfId)
    if teamSize <= 1 then -- 非组队，单独做任务
    
				local misIndex 		=  GetQuestIndexByID( sceneId, selfId, x300983_g_MissionId )
				local nKillCnt = GetQuestParam( sceneId, selfId, misIndex , 2 )
				--print("-------------->",nKillCnt)
				
				--判断当前杀人的数目,这里仅仅借用了计算接任务次数的MD的天数
				local today = GetDayOfYear()
				local lastday = GetQuestData(sceneId, selfId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3])
				if lastday ~= today then --如果是第一次杀人
					nKillCnt = 1
					SetQuestData(sceneId, selfId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3], today)
					SetQuestByIndex(sceneId, selfId, misIndex,7, 0 )
				else
					nKillCnt       = nKillCnt + 1
				end
				
				SetQuestByIndex(sceneId, selfId, misIndex,2,nKillCnt) --使用第3位保存本次任务击败的某种职业的玩家的数量 
				if nKillCnt >= x300983_g_Mission_Kill_Cnt then
					print("...........................................................")
					SetQuestByIndex(sceneId, selfId, misIndex,7, 1 ) --设置任务完成标志
					SetQuestByIndex(sceneId, selfId, misIndex,0, 1 ) --设置任务完成标志
				end
				
				x300983_QuestLogRefresh( sceneId, selfId, MissionId)
    
    else
		        for i = 0, teamSize - 1 do
		            local memberId = GetNearTeamMember( sceneId, selfId, i)
		            if memberId >= 0 and IsPlayerStateNormal( sceneId, memberId) == 1 then
							if IsHaveQuestNM( sceneId, memberId, x300983_g_MissionId) ~= 0 then -- 如果该成员接受了防御之路			
														local misIndex = GetQuestIndexByID( sceneId, memberId, x300983_g_MissionId)
									                    if GetQuestParam( sceneId, memberId, misIndex, 0) == 0 or GetQuestParam( sceneId, memberId, misIndex, 7) == 0 then
																		local misIndex 		=  GetQuestIndexByID( sceneId, memberId, x300983_g_MissionId )
																		local nKillCnt = GetQuestParam( sceneId, memberId, misIndex , 2 )
																		--print("-------------->",nKillCnt)
																		
																		--判断当前杀人的数目,这里仅仅借用了计算接任务次数的MD的天数
																		local today = GetDayOfYear()
																		local lastday = GetQuestData(sceneId, memberId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3])
																		if lastday ~= today then --如果是第一次杀人
																			nKillCnt = 1
																			SetQuestData(sceneId, memberId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3], today)
																			SetQuestByIndex(sceneId, memberId, misIndex,7, 0 )
																		else
																			nKillCnt       = nKillCnt + 1
																		end
																		
																		SetQuestByIndex(sceneId, memberId, misIndex,2,nKillCnt) --使用第3位保存本次任务击败的某种职业的玩家的数量 
																		if nKillCnt >= x300983_g_Mission_Kill_Cnt then
																			print("...........................................................")
																			SetQuestByIndex(sceneId, memberId, misIndex,7, 1 ) --设置任务完成标志
																			SetQuestByIndex(sceneId, memberId, misIndex,0, 1 ) --设置任务完成标志
																		end
																		
																		x300983_QuestLogRefresh( sceneId, memberId, MissionId)
														end
							end
				  end
			end
end
	

	
end

function x300983_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	x300983_QuestLogRefresh( sceneId, selfId, MissionId );
end

function x300983_QuestLogRefresh( sceneId, selfId, MissionId)
	--print("----------------------x300983_QuestLogRefresh")
    if IsHaveQuestNM( sceneId, selfId, x300983_g_MissionId ) == 0 then	-- 如果没有这个任务 
    		return
    end
    
	local mission = "  击败#G"
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300983_g_MissionId)
	local nIdx		 = GetQuestParam( sceneId, selfId, misIndex , 3)          --获取随机的下标
	if nIdx <=0 or nIdx > getn(x300983_g_Profession_Desc) then
		return
	end
	local strPro   = x300983_g_Profession_Desc[nIdx]	
	mission = mission..strPro.."#W职业的敌国玩家或者#G练功人偶#W"							
	
	local nRemain = 0
	local nKillCnt = 0;
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3])
	if lastday ~= today then --如果是第一次杀人
		nRemain = x300983_g_Mission_Kill_Cnt
	else										
		nKillCnt = GetQuestParam( sceneId, selfId, misIndex , 2 )
		nRemain = x300983_g_Mission_Kill_Cnt - nKillCnt
	end
		
	local strTarget  = format("%d",nKillCnt) 				
	BeginQuestEvent(sceneId)
	if nKillCnt < x300983_g_Mission_Kill_Cnt then
				AddQuestLogCustomText( sceneId,
										x300983_g_MissionName,		-- 标题
										x300983_g_MissionName,      -- 任务名字
										mission.."("..strTarget.."/6)",					--任务目标
										x300983_g_CommitNPC,		--任务NPC
										mission,               		--任务攻略
										x300983_g_MissionInfo.."\n \n#Y任务奖励：#W\n专防训练点数：13点 ",				--任务描述
										"使用专精之书·防御道具每天可以多接一次任务"			--任务小提示
										)
	else
				AddQuestLogCustomText( sceneId,
										x300983_g_MissionName,		-- 标题
										x300983_g_MissionName,      -- 任务名字
										mission.."(6/6)",		--任务目标
										x300983_g_CommitNPC,		--任务NPC
										mission,               		--任务攻略
										x300983_g_MissionInfo.."\n \n#Y任务奖励：#W\n专防训练点数：13点 ",				--任务描述
										"使用专精之书·防御道具每天可以多接一次任务"			--任务小提示
										)
	end
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, x300983_g_MissionId);
end

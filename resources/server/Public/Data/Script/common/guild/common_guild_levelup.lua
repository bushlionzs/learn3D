--点击（NPC）
function x300715_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

		if  GetGuildOfficial(sceneId, selfId) ~= 5 then--判断是否为帮主		
					return
		end
			
			AddQuestNumText(sceneId,300715,"【帮会】帮会升级",3,1)--增加按钮A

end

--点击（按钮）点击该任务后执行此脚本
function x300715_ProcEventEntry( sceneId, selfId, targetId,state,index)	

	local x300715xinwu = 0
	
	local x300715jinka = 0
	
	local x300715banghuijingyan = 0
	
	local x300715Readme_5 = ""
	
	local x300715Readme_6 = ""
	
	local x300715Readme_7 = ""	

	if index == 1 then
	
			local GuildId = GetGuildID(sceneId, selfId)--获得帮会ID
			
			local GuildLevel,GuildMemcount,GuildExp = GetGuildSimpleData(GuildId)--得到帮会简单数据（等级，人数，经验）
							
					if GuildLevel == 1 then					
								x300715xinwu = 1
								x300715jinka = 5
								x300715banghuijingyan = 800								
								if HaveItem( sceneId,selfId,11990001) < 1 then--判断是否有帮助令如果成功,返回大于0,如果失败,返回-1
									x300715Readme_5 = "  #R帮会信物："..x300715xinwu.."个帮会令。#r#W"
								else
									x300715Readme_5 = "  #G帮会信物："..x300715xinwu.."个帮会令。#r"
								end								
								if GetMoney(sceneId, selfId, 0) < 5000 then--判断身上的钱
									x300715Readme_6 = "  #R现银    ："..x300715jinka.."两。#r#W"
								else
									x300715Readme_6 = "  #G现银    ："..x300715jinka.."两。#r"
								end								
								if GuildExp < 800 then--判断帮会经验
									x300715Readme_7 = "  #R帮会经验："..x300715banghuijingyan.."点。#r#W"
								else
									x300715Readme_7 = "  #G帮会经验："..x300715banghuijingyan.."点。#r"
								end						
					elseif GuildLevel == 2 then					
								x300715xinwu = 2
								x300715jinka = 10
								x300715banghuijingyan = 4000								
								if HaveItem( sceneId,selfId,11990001) < 2 then--判断是否有帮助令如果成功,返回大于0,如果失败,返回-1
									x300715Readme_5 = "  #R帮会信物："..x300715xinwu.."个帮会令。#r#W"
								else
									x300715Readme_5 = "  #G帮会信物："..x300715xinwu.."个帮会令。#r"
								end								
								if GetMoney(sceneId, selfId, 0) < 10000 then--判断身上的钱
									x300715Readme_6 = "  #R现银    ："..x300715jinka.."两。#r#W"
								else
									x300715Readme_6 = "  #G现银    ："..x300715jinka.."两。#r"
								end								
								if GuildExp < 4000 then--判断帮会经验
									x300715Readme_7 = "  #R帮会经验："..x300715banghuijingyan.."点。#r#W"
								else
									x300715Readme_7 = "  #G帮会经验："..x300715banghuijingyan.."点。#r"
								end								
					elseif GuildLevel == 3 then					
								x300715xinwu = 3
								x300715jinka = 25
								x300715banghuijingyan = 12000								
								if HaveItem( sceneId,selfId,11990001) < 3 then--判断是否有帮助令如果成功,返回大于0,如果失败,返回-1
									x300715Readme_5 = "  #R帮会信物："..x300715xinwu.."个帮会令。#r#W"
								else
									x300715Readme_5 = "  #G帮会信物："..x300715xinwu.."个帮会令。#r"
								end								
								if GetMoney(sceneId, selfId, 0) < 25000 then--判断身上的钱
									x300715Readme_6 = "  #R现银    ："..x300715jinka.."两。#r#W"
								else
									x300715Readme_6 = "  #G现银    ："..x300715jinka.."两。#r"
								end								
								if GuildExp < 12000 then--判断帮会经验
									x300715Readme_7 = "  #R帮会经验："..x300715banghuijingyan.."点。#r#W"
								else
									x300715Readme_7 = "  #G帮会经验："..x300715banghuijingyan.."点。#r"
								end								
					elseif GuildLevel == 4 then					
								x300715xinwu = 4
								x300715jinka = 50
								x300715banghuijingyan = 40000							
								if HaveItem( sceneId,selfId,11990001) < 4 then--判断是否有帮助令如果成功,返回大于0,如果失败,返回-1
									x300715Readme_5 = "  #R帮会信物："..x300715xinwu.."个帮会令。#r#W"
								else
									x300715Readme_5 = "  #G帮会信物："..x300715xinwu.."个帮会令。#r"
								end								
								if GetMoney(sceneId, selfId, 0) < 50000 then--判断身上的钱
									x300715Readme_6 = "  #R现银    ："..x300715jinka.."两。#r#W"
								else
									x300715Readme_6 = "  #G现银    ："..x300715jinka.."两。#r"
								end								
								if GuildExp < 40000 then--判断帮会经验
									x300715Readme_7 = "  #R帮会经验："..x300715banghuijingyan.."点。#r#W"
								else
									x300715Readme_7 = "  #G帮会经验："..x300715banghuijingyan.."点。#r"
								end					
					elseif GuildLevel == 5 then					
								x300715xinwu = 5
								x300715jinka = 500
								x300715banghuijingyan = 96000							
								if HaveItem( sceneId,selfId,11990001) < 5 then--判断是否有帮助令如果成功,返回大于0,如果失败,返回-1
									x300715Readme_5 = "  #R帮会信物："..x300715xinwu.."个帮会令。#r#W"
								else
									x300715Readme_5 = "  #G帮会信物："..x300715xinwu.."个帮会令。#r"
								end								
								if GetMoney(sceneId, selfId, 0) < 500000 then--判断身上的钱
									x300715Readme_6 = "  #R现银    ："..x300715jinka.."两。#r#W"
								else
									x300715Readme_6 = "  #G现银    ："..x300715jinka.."两。#r"
								end								
								if GuildExp < 96000 then--判断帮会经验
									x300715Readme_7 = "  #R帮会经验："..x300715banghuijingyan.."点。#r#W"
								else
									x300715Readme_7 = "  #G帮会经验："..x300715banghuijingyan.."点。#r"
								end			
					elseif GuildLevel == 6 then					
								x300715xinwu = 6
								x300715jinka = 800
								x300715banghuijingyan = 192000							
								if HaveItem( sceneId,selfId,11990001) < 6 then--判断是否有帮助令如果成功,返回大于0,如果失败,返回-1
									x300715Readme_5 = "  #R帮会信物："..x300715xinwu.."个帮会令。#r#W"
								else
									x300715Readme_5 = "  #G帮会信物："..x300715xinwu.."个帮会令。#r"
								end								
								if GetMoney(sceneId, selfId, 0) < 800000 then--判断身上的钱
									x300715Readme_6 = "  #R现银    ："..x300715jinka.."两。#r#W"
								else
									x300715Readme_6 = "  #G现银    ："..x300715jinka.."两。#r"
								end								
								if GuildExp < 192000 then--判断帮会经验
									x300715Readme_7 = "  #R帮会经验："..x300715banghuijingyan.."点。#r#W"
								else
									x300715Readme_7 = "  #G帮会经验："..x300715banghuijingyan.."点。#r"
								end											
					elseif GuildLevel == 7 then					
								Msg2Player(sceneId,selfId,"帮会等级目前只开放到7级！",8,2)
								Msg2Player(sceneId,selfId,"帮会等级目前只开放到7级！",8,3)
						return						
					end
		
					
			local Readme_1 = "#Y【帮会】帮会升级：#r"
			
			local Readme_2 = "#W您所在帮会的当前等级为：#G"..GuildLevel.."#W 级。#r"
			
			local Readme_3 = "您所在帮会的帮会经验为：#G"..GuildExp.."#W 点。#r ".."#r"
			
			local Readme_4 = "升#G"..(GuildLevel+1).."级帮会#W需要以下条件：#r #r"
			
			local Readme_8 = "#W ".."#r您是否要升级帮会？"
			
			local Readme = Readme_1..Readme_2..Readme_3..Readme_4..x300715Readme_5..x300715Readme_6..x300715Readme_7..Readme_8
						
			BeginQuestEvent(sceneId);AddQuestText( sceneId,Readme);EndQuestEvent(sceneId);DispatchQuestInfo(sceneId, selfId, targetId, 300715, -1)
			
	end
	
end


--点击（确定）
function x300715_ProcAcceptCheck( sceneId, selfId, NPCId )

			local guildid = GetGuildID(sceneId, selfId)
	
			local GuildLevel,GuildMemcount,GuildExp = GetGuildSimpleData(guildid)--得到帮会简单数据（等级，人数，经验）			
			
			if  GetGuildOfficial(sceneId, selfId) == 5 then--判断是否为帮主
						if GuildLevel == 1 then--判断帮派等级1-2
							if GetMoney(sceneId, selfId, 0) >= 5000 then--判断身上的钱
									if HaveItem( sceneId,selfId,11990001) >= 1 then--判断是否有帮助令如果成功,返回大于0,如果失败,返回-1
											if GuildExp >= 800 then
													CostMoney(sceneId, selfId, 0,5000,304)--扣钱
													DelItem( sceneId,selfId,11990001,1 )--删信物
													SubGuildExp(sceneId,selfId, 800)--删除帮会经验
													GuildLevelup(sceneId, selfId)--给帮会升级
													Msg2Player(sceneId,selfId,"号外！号外！帮会升级喽~",6)
													Msg2Player(sceneId,selfId,"号外！号外！帮会升级喽~",8,2)
													Msg2Player(sceneId,selfId,"号外！号外！帮会升级喽~",8,3)
											else
												Msg2Player(sceneId,selfId,"很抱歉，帮会经验不够，无法升级帮会！",8,2)
												Msg2Player(sceneId,selfId,"很抱歉，帮会经验不够，无法升级帮会！",8,3)
											end
									else
										Msg2Player(sceneId,selfId,"很抱歉，帮会信物不够，无法升级帮会！",8,2)
										Msg2Player(sceneId,selfId,"很抱歉，帮会信物不够，无法升级帮会！",8,3)
									end
							else
								Msg2Player(sceneId,selfId,"很抱歉，您身上的现银不够，无法升级帮会！",8,2)
								Msg2Player(sceneId,selfId,"很抱歉，您身上的现银不够，无法升级帮会！",8,3)
							end
					elseif GuildLevel == 2 then--2-3					
							if GetMoney(sceneId, selfId, 0) >= 10000 then--判断身上的钱
									if HaveItem( sceneId,selfId,11990001) >= 2 then--判断是否有帮助令如果成功,返回大于0,如果失败,返回-1
											if GuildExp >= 4000 then
													
													CostMoney(sceneId, selfId, 0,10000,304)--扣钱
													DelItem( sceneId,selfId,11990001,2 )--删信物
													SubGuildExp(sceneId,selfId, 4000)--删除帮会经验
													GuildLevelup(sceneId, selfId)--给帮会升级	
													Msg2Player(sceneId,selfId,"号外！号外！帮会升级喽~",6)
													Msg2Player(sceneId,selfId,"号外！号外！帮会升级喽~",8,2)
													Msg2Player(sceneId,selfId,"号外！号外！帮会升级喽~",8,3)
											else
												Msg2Player(sceneId,selfId,"很抱歉，帮会经验不够，无法升级帮会！",8,2)
												Msg2Player(sceneId,selfId,"很抱歉，帮会经验不够，无法升级帮会！",8,3)
											end
									else
										Msg2Player(sceneId,selfId,"很抱歉，帮会信物不够，无法升级帮会！",8,2)
										Msg2Player(sceneId,selfId,"很抱歉，帮会信物不够，无法升级帮会！",8,3)
									end
							else
								Msg2Player(sceneId,selfId,"很抱歉，您身上的现银不够，无法升级帮会！",8,2)
								Msg2Player(sceneId,selfId,"很抱歉，您身上的现银不够，无法升级帮会！",8,3)
							end
							
					elseif GuildLevel == 3 then--3-4
					
							if GetMoney(sceneId, selfId, 0) >= 25000 then--判断身上的钱
									if HaveItem( sceneId,selfId,11990001) >= 3 then--判断是否有帮助令如果成功,返回大于0,如果失败,返回-1
											if GuildExp >= 12000 then
													
													CostMoney(sceneId, selfId, 0,25000,304)--扣钱
													DelItem( sceneId,selfId,11990001,3 )--删信物
													SubGuildExp(sceneId,selfId, 12000)--删除帮会经验
													GuildLevelup(sceneId, selfId)--给帮会升级	
													Msg2Player(sceneId,selfId,"号外！号外！帮会升级喽~",6)
													Msg2Player(sceneId,selfId,"号外！号外！帮会升级喽~",8,2)
													Msg2Player(sceneId,selfId,"号外！号外！帮会升级喽~",8,3)
											else
												Msg2Player(sceneId,selfId,"很抱歉，帮会经验不够，无法升级帮会！",8,2)
												Msg2Player(sceneId,selfId,"很抱歉，帮会经验不够，无法升级帮会！",8,3)
											end
									else
										Msg2Player(sceneId,selfId,"很抱歉，帮会信物不够，无法升级帮会！",8,2)
										Msg2Player(sceneId,selfId,"很抱歉，帮会信物不够，无法升级帮会！",8,3)
									end
							else
								Msg2Player(sceneId,selfId,"很抱歉，您身上的现银不够，无法升级帮会！",8,2)
								Msg2Player(sceneId,selfId,"很抱歉，您身上的现银不够，无法升级帮会！",8,3)
							end
								
					elseif GuildLevel == 4 then--4-5
					
							if GetMoney(sceneId, selfId, 0) >= 50000 then--判断身上的钱
									if HaveItem( sceneId,selfId,11990001) >= 4 then--判断是否有帮助令如果成功,返回大于0,如果失败,返回-1
											if GuildExp >= 40000 then
													
													CostMoney(sceneId, selfId, 0,50000,304)--扣钱
													DelItem( sceneId,selfId,11990001,4 )--删信物
													SubGuildExp(sceneId,selfId, 40000)--删除帮会经验
													GuildLevelup(sceneId, selfId)--给帮会升级	
													Msg2Player(sceneId,selfId,"号外！号外！帮会升级喽~",6)
													Msg2Player(sceneId,selfId,"号外！号外！帮会升级喽~",8,2)
													Msg2Player(sceneId,selfId,"号外！号外！帮会升级喽~",8,3)
											else
												Msg2Player(sceneId,selfId,"很抱歉，帮会经验不够，无法升级帮会！",8,2)
												Msg2Player(sceneId,selfId,"很抱歉，帮会经验不够，无法升级帮会！",8,3)
											end
									else
										Msg2Player(sceneId,selfId,"很抱歉，帮会信物不够，无法升级帮会！",8,2)
										Msg2Player(sceneId,selfId,"很抱歉，帮会信物不够，无法升级帮会！",8,3)
									end
							else
								Msg2Player(sceneId,selfId,"很抱歉，您身上的现银不够，无法升级帮会！",8,2)
								Msg2Player(sceneId,selfId,"很抱歉，您身上的现银不够，无法升级帮会！",8,3)
							end				

					elseif GuildLevel == 5 then--5-6
					
							if GetMoney(sceneId, selfId, 0) >= 500000 then--判断身上的钱
									if HaveItem( sceneId,selfId,11990001) >= 5 then--判断是否有帮助令如果成功,返回大于0,如果失败,返回-1
											if GuildExp >= 96000 then
													
													CostMoney(sceneId, selfId, 0,500000,304)--扣钱
													DelItem( sceneId,selfId,11990001,5 )--删信物
													SubGuildExp(sceneId,selfId, 96000)--删除帮会经验
													GuildLevelup(sceneId, selfId)--给帮会升级	
													Msg2Player(sceneId,selfId,"号外！号外！帮会升级喽~",6)
													Msg2Player(sceneId,selfId,"号外！号外！帮会升级喽~",8,2)
													Msg2Player(sceneId,selfId,"号外！号外！帮会升级喽~",8,3)
											else
												Msg2Player(sceneId,selfId,"很抱歉，帮会经验不够，无法升级帮会！",8,2)
												Msg2Player(sceneId,selfId,"很抱歉，帮会经验不够，无法升级帮会！",8,3)
											end
									else
										Msg2Player(sceneId,selfId,"很抱歉，帮会信物不够，无法升级帮会！",8,2)
										Msg2Player(sceneId,selfId,"很抱歉，帮会信物不够，无法升级帮会！",8,3)
									end
							else
								Msg2Player(sceneId,selfId,"很抱歉，您身上的现银不够，无法升级帮会！",8,2)
								Msg2Player(sceneId,selfId,"很抱歉，您身上的现银不够，无法升级帮会！",8,3)
							end				

					elseif GuildLevel == 6 then--6-7
					
							if GetMoney(sceneId, selfId, 0) >= 800000 then--判断身上的钱
									if HaveItem( sceneId,selfId,11990001) >= 6 then--判断是否有帮助令如果成功,返回大于0,如果失败,返回-1
											if GuildExp >= 192000 then
													
													CostMoney(sceneId, selfId, 0,800000,304)--扣钱
													DelItem( sceneId,selfId,11990001,6 )--删信物
													SubGuildExp(sceneId,selfId, 192000)--删除帮会经验
													GuildLevelup(sceneId, selfId)--给帮会升级	
													Msg2Player(sceneId,selfId,"号外！号外！帮会升级喽~",6)
													Msg2Player(sceneId,selfId,"号外！号外！帮会升级喽~",8,2)
													Msg2Player(sceneId,selfId,"号外！号外！帮会升级喽~",8,3)
											else
												Msg2Player(sceneId,selfId,"很抱歉，帮会经验不够，无法升级帮会！",8,2)
												Msg2Player(sceneId,selfId,"很抱歉，帮会经验不够，无法升级帮会！",8,3)
											end
									else
										Msg2Player(sceneId,selfId,"很抱歉，帮会信物不够，无法升级帮会！",8,2)
										Msg2Player(sceneId,selfId,"很抱歉，帮会信物不够，无法升级帮会！",8,3)
									end
							else
								Msg2Player(sceneId,selfId,"很抱歉，您身上的现银不够，无法升级帮会！",8,2)
								Msg2Player(sceneId,selfId,"很抱歉，您身上的现银不够，无法升级帮会！",8,3)
							end				
					end
			else
				Msg2Player(sceneId,selfId,"您不是帮主！",8,2)
				Msg2Player(sceneId,selfId,"您不是帮主！",8,3)
			end
			
end

--**********************************
--接受
--**********************************
function x300715_ProcAccept( sceneId, sceneId )

end

--**********************************
--放弃
--**********************************
function x300715_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x300715_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300715_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300715_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300715_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300715_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300715_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end



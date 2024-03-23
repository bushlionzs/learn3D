 --密探
x270354_g_ScriptId	= 270354
x270354_g_MissionId	=	{1390 , 1391, 1392, 1393}
x270354_g_MissionScriptId	=	{270350 , 270351, 270352, 270353}

--**********************************
--事件交互入口
--**********************************
function x270354_ProcEventEntry( sceneId, selfId,targetId )            
	BeginQuestEvent(sceneId)                                             
	AddQuestText(sceneId,"\t哈哈！还是外面的世界好啊，这次终于不用继续在那暗无天日的地方待着了。")     
	EndQuestEvent(sceneId)
	local misIndex = -1                                               
	if IsHaveQuest(sceneId,selfId, 1390) > 0 then
		misIndex = GetQuestIndexByID(sceneId,selfId,1390) 
		if GetQuestParam(sceneId,selfId,misIndex,0) <= 0 then	                     
		 	AddQuestNumText(sceneId, x270354_g_MissionId[1], "你并不属于这里！",0, 1)
		end                  
	end                                               
	if IsHaveQuest(sceneId,selfId, 1391) > 0 then
		misIndex = GetQuestIndexByID(sceneId,selfId,1391) 
		if GetQuestParam(sceneId,selfId,misIndex,0) <= 0 then	                     
		 	AddQuestNumText(sceneId, x270354_g_MissionId[2], "你并不属于这里！",0, 1)
		end                  
	end                                             
	if IsHaveQuest(sceneId,selfId, 1392) > 0 then
		misIndex = GetQuestIndexByID(sceneId,selfId,1392) 
		if GetQuestParam(sceneId,selfId,misIndex,0) <= 0 then	                     
		 	AddQuestNumText(sceneId, x270354_g_MissionId[3], "你并不属于这里！",0, 1)
		end                  
	end                                              
	if IsHaveQuest(sceneId,selfId, 1393) > 0 then
		misIndex = GetQuestIndexByID(sceneId,selfId,1393) 
		if GetQuestParam(sceneId,selfId,misIndex,0) <= 0 then	                     
		 	AddQuestNumText(sceneId, x270354_g_MissionId[4], "你并不属于这里！",0, 1)
		end                  
	end	                                                                  
	DispatchQuestEventList(sceneId,selfId,targetId)                      
	ShowNpcQuestEventList(sceneId,selfId,targetId)                       
end                                                                    

x270354_g_MonsterTable              = {
                                        { minLevel = 20, maxLevel = 29, monList = { { id = 3840, objid = 400040, mapid = 58,  name = "角木熊星",   Place = "西北方" , posName = "@npc_59670"  }, { id = 3841, objid = 400041, mapid = 58,  name = "奎木狼星", 	Place = "东北方" , posName = "@npc_59670"  }, { id = 3842, objid = 400042, mapid = 58,  name = "毕月乌星", 	 Place = "西南方" , posName = "@npc_59670"  }, { id = 3843, objid = 400043, mapid = 58,  name = "翼火蛇星",    		Place = "东南方" , posName = "@npc_59670"  }, { id = 3844, objid = 400044,mapid = 58, name = "胃土彘星", Place = "南方" ,posName = "@npc_59670"  }, { id = 3845, objid = 400045,mapid = 58, name = "女土蝠星", Place = "南方" ,posName = "@npc_59670" } }},  
                                        { minLevel = 30, maxLevel = 34, monList = { { id = 3846, objid = 400046, mapid = 104, name = "鬼金羊星",   Place = "西北方" , posName = "@npc_59671"  }, { id = 3847, objid = 400047, mapid = 104, name = "尾火虎星", 	Place = "东北方" , posName = "@npc_59671"  }, { id = 3849, objid = 400049, mapid = 104, name = "龙堡守卫", 	 Place = "西南方" ,	posName = "@npc_59671"  }, { id = 3850, objid = 400050, mapid = 104, name = "蓝虺", 			 		Place = "东南方" , posName = "@npc_59671"  } }},
                                        { minLevel = 35, maxLevel = 39, monList = { { id = 3849, objid = 400049, mapid = 104, name = "龙堡守卫",   Place = "西南方" , posName = "@npc_59671"  }, { id = 3850, objid = 400050, mapid = 104, name = "蓝虺", 			Place = "东南方" , posName = "@npc_59671"  }, { id = 3852, objid = 400052, mapid = 105, name = "长爪翼龙", 	 Place = "西南方" , posName = "@npc_59672"  }, { id = 3853, objid = 400053, mapid = 105, name = "厌火异兽", 	 		Place = "中部" ,	 posName = "@npc_59672"  } }}, 
                                        { minLevel = 40, maxLevel = 44, monList = { { id = 3852, objid = 400052, mapid = 105, name = "长爪翼龙",   Place = "西南方" , posName = "@npc_59672"  }, { id = 3853, objid = 400053, mapid = 105, name = "厌火异兽", 	Place = "中部" ,	 posName = "@npc_59672"  }, { id = 3854, objid = 400054, mapid = 105, name = "探宝矿工", 	 Place = "东北方" ,	posName = "@npc_59672"  }, { id = 3856, objid = 400056, mapid = 105, name = "地穴恶魔",    		Place = "东方" ,	 posName = "@npc_59672"  } }}, 
                                        { minLevel = 45, maxLevel = 49, monList = { { id = 3854, objid = 400054, mapid = 105, name = "探宝矿工",   Place = "东北方" , posName = "@npc_59672"  }, { id = 3856, objid = 400056, mapid = 105, name = "地穴恶魔", 	Place = "东方" ,	 posName = "@npc_59672"  }, { id = 3858, objid = 400058, mapid = 106, name = "国王子民",	 Place = "西方" ,   posName = "@npc_59673"  }, { id = 3859, objid = 400059, mapid = 106, name = "狼人布鲁斯",  		Place = "西北方" , posName = "@npc_59673"  } }}, 
                                        { minLevel = 50, maxLevel = 54, monList = { { id = 3858, objid = 400058, mapid = 106, name = "国王子民",   Place = "西方" ,   posName = "@npc_59673"  }, { id = 3859, objid = 400059, mapid = 106, name = "狼人布鲁斯", Place = "西北方" , posName = "@npc_59673"  }, { id = 3862, objid = 400062, mapid = 106, name = "血蝙蝠",		 Place = "中部" ,		posName = "@npc_59673"  }, { id = 3863, objid = 400063, mapid = 106, name = "死亡骑士",    		Place = "东南方" , posName = "@npc_59673"  } }}, 
                                        { minLevel = 55, maxLevel = 59, monList = { { id = 3862, objid = 400062, mapid = 106, name = "血蝙蝠",     Place = "中部" ,   posName = "@npc_59673"  }, { id = 3863, objid = 400063, mapid = 106, name = "死亡骑士", 	Place = "东南方" , posName = "@npc_59673"  }, { id = 3864, objid = 400064, mapid = 107, name = "喷毒红蛛",   Place = "中部" ,   posName = "@npc_59674"  }, { id = 3866, objid = 400066, mapid = 107, name = "巨钳毒蝎",    		Place = "东北方" , posName = "@npc_59674"  } }}, 
                                        { minLevel = 60, maxLevel = 64, monList = { { id = 3864, objid = 400064, mapid = 107, name = "喷毒红蛛",   Place = "中部" ,   posName = "@npc_59674"  }, { id = 3866, objid = 400066, mapid = 107, name = "巨钳毒蝎", 	Place = "东北方" , posName = "@npc_59674"  }, { id = 3868, objid = 400068, mapid = 107, name = "祝家庄护院", Place = "中部" ,		posName = "@npc_59674"  }, { id = 3869, objid = 400069, mapid = 107, name = "祝家庄乡勇",  		Place = "东北方" , posName = "@npc_59674"  } }}, 
 										{ minLevel = 65, maxLevel = 69, monList = { { id = 3868, objid = 400068, mapid = 107, name = "祝家庄护院", Place = "中部" ,		posName = "@npc_59674"	}, { id = 3869, objid = 400069, mapid = 107, name = "祝家庄乡勇", Place = "东北方" , posName = "@npc_59674"  }, { id = 3870, objid = 400070, mapid = 108, name = "冰之灵", 		 Place = "中部" ,		posName = "@npc_59701"  }, { id = 3871, objid = 400071, mapid = 108, name = "炎之灵", 		 		Place = "西北方" , posName = "@npc_59701"  } }}, 
                                        { minLevel = 70, maxLevel = 74, monList = { { id = 3870, objid = 400070, mapid = 108, name = "冰之灵",     Place = "中部" ,		posName = "@npc_59701"  }, { id = 3871, objid = 400071, mapid = 108, name = "炎之灵", 		Place = "西北方" , posName = "@npc_59701"  }, { id = 3872, objid = 400072, mapid = 108, name = "地之灵", 		 Place = "北方" ,		posName = "@npc_59701"  }, { id = 3873, objid = 400073, mapid = 108, name = "突厥蛮卫",    		Place = "东北方" , posName = "@npc_59701"  } }}, 
                                        { minLevel = 75, maxLevel = 79, monList = { { id = 3872, objid = 400072, mapid = 108, name = "地之灵",     Place = "北方" ,		posName = "@npc_59701"  }, { id = 3873, objid = 400073, mapid = 108, name = "突厥蛮卫", 	Place = "东北方" , posName = "@npc_59701"  }, { id = 3874, objid = 400074, mapid = 109, name = "聚之灵", 		 Place = "中部" ,   posName = "@npc_59702"  }, { id = 3875, objid = 400075, mapid = 109, name = "突厥禁军", 	 		Place = "东北方" , posName = "@npc_59702"  } }}, 
                                        { minLevel = 80, maxLevel = 84, monList = { { id = 3874, objid = 400074, mapid = 109, name = "聚之灵",     Place = "中部" ,   posName = "@npc_59702"  }, { id = 3875, objid = 400075, mapid = 109, name = "突厥禁军", 	Place = "东北方" , posName = "@npc_59702"  }, { id = 3876, objid = 400076, mapid = 109, name = "扈家庄庄丁", Place = "北方" ,		posName = "@npc_59702"  }, { id = 3877, objid = 400077, mapid = 109, name = "祝家庄庄丁",  		Place = "东方" ,	 posName = "@npc_59702"  } }}, 
                                        { minLevel = 85, maxLevel = 89, monList = { { id = 3876, objid = 400076, mapid = 109, name = "扈家庄庄丁", Place = "北方" ,		posName = "@npc_59702"  }, { id = 3877, objid = 400077, mapid = 109, name = "祝家庄庄丁", Place = "东方" ,	 posName = "@npc_59702"  }, { id = 3878, objid = 400078, mapid = 110, name = "县衙官兵",   Place = "中部" ,		posName = "@npc_59703"  }, { id = 3879, objid = 400079, mapid = 110, name = "突厥蛮兵",    		Place = "东方" ,	 posName = "@npc_59703"  } }}, 
                                        { minLevel = 90, maxLevel = 94, monList = { { id = 3878, objid = 400078, mapid = 110, name = "县衙官兵",   Place = "中部" ,		posName = "@npc_59703"  }, { id = 3879, objid = 400079, mapid = 110, name = "突厥蛮兵", 	Place = "东方" ,	 posName = "@npc_59703"  }, { id = 3880, objid = 400080, mapid = 110, name = "灰壳蟹", 		 Place = "西北方" ,	posName = "@npc_59703"  }, { id = 3881, objid = 400081, mapid = 110, name = "金国怯薛军",  		Place = "东北方" , posName = "@npc_59703"  } }}, 
                                        { minLevel = 95, maxLevel = 99, monList = { { id = 3880, objid = 400080, mapid = 110, name = "灰壳蟹",     Place = "西北方" ,	posName = "@npc_59703"  }, { id = 3881, objid = 400081, mapid = 110, name = "金国怯薛军", Place = "东北方" , posName = "@npc_59703"  },	{ id = 3882, objid = 400082, mapid = 111, name = "金国质子军", Place = "东南方" , posName = "@npc_59704"},   { id = 3883, objid = 400083, mapid = 111, name = "随军巫师",    		Place = "东方" ,   posName = "@npc_59704"  } }}, 
                                        { minLevel = 100,maxLevel =160, monList = { { id = 3882, objid = 400082, mapid = 111, name = "金国质子军", Place = "东南方" , posName = "@npc_59704"  }, { id = 3883, objid = 400083, mapid = 111, name = "随军巫师", 	Place = "东方" ,   posName = "@npc_59704"  }, { id = 3884, objid = 400084, mapid = 111, name = "神机营精锐", Place = "西方" ,		posName = "@npc_59704"  }, { id = 3885, objid = 400085, mapid = 111, name = "金国乌月营斥候", Place = "东方" ,   posName = "@npc_59704"  } }}, 
}
function x270354_OnDie(sceneId, selfId, killerId)
	SetMonsterCamp(sceneId,selfId,20)
	local MissionId = 0
	local Index = 0
	local guid = GetMonsterGUID(sceneId, selfId)
	local x,z = GetWorldPos(sceneId,selfId)
	local Num =  GetNearPlayerCount(sceneId, killerId,x,z,30)  
	for i = 0, Num-1 do
		local humanObjId = GetNearPlayerMember(sceneId, killerId,i);

		if humanObjId >= 0 then
			if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
				if IsHaveQuestNM(sceneId, humanObjId, x270354_g_MissionId[1]) == 1 then
					MissionId = x270354_g_MissionId[1]
					Index = 1
				elseif IsHaveQuestNM(sceneId, humanObjId, x270354_g_MissionId[2]) == 1 then
					MissionId = x270354_g_MissionId[2]
					Index = 2
				elseif IsHaveQuestNM(sceneId, humanObjId, x270354_g_MissionId[3]) == 1 then
					MissionId = x270354_g_MissionId[3]
					Index = 3
				elseif IsHaveQuestNM(sceneId, humanObjId, x270354_g_MissionId[4]) == 1 then
					MissionId = x270354_g_MissionId[4]
					Index = 4
				end
				if MissionId ~= 0 then
					
	            local misIndex = GetQuestIndexByID( sceneId, humanObjId, MissionId)
	            local monidx = GetQuestParam( sceneId, humanObjId, misIndex, 1)
	            local index = GetQuestParam( sceneId, humanObjId, misIndex, 2)
		            if monidx == nil or monidx == 0 or index == nil or index == 0 then
		            	return
		            end
	            local name = x270354_g_MonsterTable[index].monList[monidx].name
	            if guid == x270354_g_MonsterTable[ index].monList[ monidx].objid then
		            SetQuestByIndex( sceneId, humanObjId, misIndex, 0, 1)
				        SetQuestByIndex( sceneId, humanObjId, misIndex, 7, 1)
				        SetQuestByIndex( sceneId, humanObjId, misIndex, 6, 1)
				        Msg2Player( sceneId, humanObjId, format( "%s已被消灭，【个人】三环任务(通缉令)任务完成", name), 8, 3)
				        Msg2Player( sceneId, humanObjId, format( "%s已被消灭，【个人】三环任务(通缉令)任务完成", name), 8, 2)
				        
				        CallScriptFunction( x270354_g_MissionScriptId[Index], "ProcQuestLogRefresh", sceneId, humanObjId, MissionId)
			    		end
			    end
	        	
			end
		end
	end
end
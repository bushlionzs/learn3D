--author: 	jiangchao
--function:	国王争夺战广播
--date:		2010-09-23

--脚本号
x300970_g_ScriptId = 300970

function x300970_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5 )
	
	if GetWeek() == 0 then --过滤原有的触发条件：周天正常开启
		return
	end
	
	local nWorldId = GetWorldIdEx()
	local nGuid , nRank = GetToplistInfo(nWorldId, 0 , 0) --获取等级排行榜的第一名
	if nRank < 50 then
		return
	end

	for i=0, 3 do 
		if GetCountryKingGuildIdNM(i) < 0 then
			x300970_BroadcastMsg2Country(sceneId , i , Param1)
		end
	end
end
			
			

function x300970_BroadcastMsg2Country(sceneId , nCountryID , Param1)			
	--相关广播
	if Param1 == 0 then
		
		LuaAllScenceM2Country(sceneId,"国王战场报名时间将在14：00开始，请参加报名的帮会做好准备！", nCountryID , CHAT_RIGHTDOWN,1)
		LuaAllScenceM2Country(sceneId,"国王战场报名时间将在14：00开始，请参加报名的帮会做好准备！", nCountryID , CHAT_LEFTDOWN, 1)
		LuaAllScenceM2Country(sceneId,"国王战场报名时间将在14：00开始，请参加报名的帮会做好准备！", nCountryID , CHAT_MAIN_RIGHTDOWN, 1)
		
	elseif Param1 == 1 then
		
		LuaAllScenceM2Country(sceneId,"国王战场报名时间将在14：00开始，请参加报名的帮会做好准备！", nCountryID , CHAT_RIGHTDOWN,1)
		LuaAllScenceM2Country(sceneId,"国王战场报名时间将在14：00开始，请参加报名的帮会做好准备！", nCountryID , CHAT_LEFTDOWN, 1)
		LuaAllScenceM2Country(sceneId,"国王战场报名时间将在14：00开始，请参加报名的帮会做好准备！", nCountryID , CHAT_MAIN_RIGHTDOWN, 1)
		
	elseif Param1 == 2 then
		
		LuaAllScenceM2Country(sceneId,"国王战场报名时间将在14：00开始，请参加报名的帮会做好准备！",nCountryID , CHAT_RIGHTDOWN,1)      
		LuaAllScenceM2Country(sceneId,"国王战场报名时间将在14：00开始，请参加报名的帮会做好准备！",nCountryID , CHAT_LEFTDOWN, 1)      
		LuaAllScenceM2Country(sceneId,"国王战场报名时间将在14：00开始，请参加报名的帮会做好准备！",nCountryID , CHAT_MAIN_RIGHTDOWN, 1)
		
	elseif Param1 == 3 then
		
		LuaAllScenceM2Country(sceneId,"国王战场报名时间将在14：00开始，请参加报名的帮会做好准备！",nCountryID , CHAT_RIGHTDOWN,1)      
		LuaAllScenceM2Country(sceneId,"国王战场报名时间将在14：00开始，请参加报名的帮会做好准备！",nCountryID , CHAT_LEFTDOWN, 1)      
		LuaAllScenceM2Country(sceneId,"国王战场报名时间将在14：00开始，请参加报名的帮会做好准备！",nCountryID , CHAT_MAIN_RIGHTDOWN, 1)
	
	elseif Param1 == 4 then
	
	    LuaAllScenceM2Country(sceneId,"国王战场报名开始，请参加的帮会前往本国王城国家管理员处报名！",nCountryID , CHAT_RIGHTDOWN,1)      
	    LuaAllScenceM2Country(sceneId,"国王战场报名开始，请参加的帮会前往本国王城国家管理员处报名！",nCountryID , CHAT_LEFTDOWN, 1)      
	    LuaAllScenceM2Country(sceneId,"国王战场报名开始，请参加的帮会前往本国王城国家管理员处报名！",nCountryID , CHAT_MAIN_RIGHTDOWN, 1)
	elseif Param1 == 5 then
	
	    LuaAllScenceM2Country(sceneId,"国王战场报名开始，请参加的帮会前往本国王城国家管理员处报名！",nCountryID , CHAT_RIGHTDOWN,1)      
	    LuaAllScenceM2Country(sceneId,"国王战场报名开始，请参加的帮会前往本国王城国家管理员处报名！",nCountryID , CHAT_LEFTDOWN, 1)      
	    LuaAllScenceM2Country(sceneId,"国王战场报名开始，请参加的帮会前往本国王城国家管理员处报名！",nCountryID , CHAT_MAIN_RIGHTDOWN, 1)
	elseif Param1 == 6 then
	
	    LuaAllScenceM2Country(sceneId,"国王战场报名开始，请参加的帮会前往本国王城国家管理员处报名！",nCountryID , CHAT_RIGHTDOWN,1)      
	    LuaAllScenceM2Country(sceneId,"国王战场报名开始，请参加的帮会前往本国王城国家管理员处报名！",nCountryID , CHAT_LEFTDOWN, 1)      
	    LuaAllScenceM2Country(sceneId,"国王战场报名开始，请参加的帮会前往本国王城国家管理员处报名！",nCountryID , CHAT_MAIN_RIGHTDOWN, 1)
	elseif Param1 == 7 then
	
	    LuaAllScenceM2Country(sceneId,"国王战场报名结束！",nCountryID , CHAT_RIGHTDOWN,1)      
	    LuaAllScenceM2Country(sceneId,"国王战场报名结束！",nCountryID , CHAT_LEFTDOWN, 1)      
	    LuaAllScenceM2Country(sceneId,"国王战场报名结束！",nCountryID , CHAT_MAIN_RIGHTDOWN, 1)
	elseif Param1 == 8 then
	
		LuaAllScenceM2Country(sceneId,"国王战场将在20：00分开启，请提前做好准备！",nCountryID , CHAT_RIGHTDOWN,1)      
		LuaAllScenceM2Country(sceneId,"国王战场将在20：00分开启，请提前做好准备！",nCountryID , CHAT_LEFTDOWN, 1)      
		LuaAllScenceM2Country(sceneId,"国王战场将在20：00分开启，请提前做好准备！",nCountryID , CHAT_MAIN_RIGHTDOWN, 1)
	elseif Param1 == 9 then
	
		LuaAllScenceM2Country(sceneId,"国王战场开始了！",nCountryID , CHAT_RIGHTDOWN,1)      
		LuaAllScenceM2Country(sceneId,"国王战场开始了！",nCountryID , CHAT_LEFTDOWN, 1)      
		LuaAllScenceM2Country(sceneId,"国王战场开始了！",nCountryID , CHAT_MAIN_RIGHTDOWN, 1)
	end
end

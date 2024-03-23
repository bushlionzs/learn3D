x300150_g_scriptId = 300150
x300150_g_Impact1	= 9825

--答题状态
x300150_g_METAIL_GAME_INVALID = -1
x300150_g_METAIL_GAME_STARTING = 0
x300150_g_METAIL_GAME_STARTED = 1
x300150_g_METAIL_GAME_THINK = 2
x300150_g_METAIL_GAME_FINISH = 3

--答题道具
x300150_g_METAIL_GAME_ITEM_NUM = 3

--答题数据
x300150_g_TotalQuests = 20
x300150_g_ThinkTimeLen = 5000


--活动触发
function x300150_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4 )
	--print( "_ProcEventEntry")
	local sceneType = GetSceneType(sceneId);
	if sceneType ~= 0 then
		return
	end
	
	MentalGameAskRandSeed( sceneId, actId )
	
	SetMentalGameStatus( sceneId, x300150_g_METAIL_GAME_STARTING )

	SetSystemTimerTick( sceneId, x300150_g_scriptId, "ProcTiming", actId, 30*1000 ) --0.5分钟后开始
end

--活动的Tick
function x300150_ProcTiming( sceneId, actId, uTime )
	
	--print( "_ProcTiming sceneId="..sceneId.." actid="..actId.." uTime="..uTime)

	local status = GetMentalGameStatus( sceneId )
	
	if status == x300150_g_METAIL_GAME_STARTING then
		--print("_ProcTiming_STARTING")
		-- 2分钟后，答题自动开始。。
		SetMentalGameStatus( sceneId, x300150_g_METAIL_GAME_STARTED )
		
		SetSystemTimerTick( sceneId, x300150_g_scriptId, "ProcTiming", actId, 5000 ) --5秒钟后出题，此时不让报名了

	elseif status == x300150_g_METAIL_GAME_STARTED then
		--print("_ProcTiming_STARTED")
		local MentalGameCycle = GetMentalGameCycle( sceneId )
		if MentalGameCycle < x300150_g_TotalQuests then
		
			
			MentalGameBroadCastQuiz( sceneId, actId, MentalGameCycle, 0 ) --出题
			
			SetSystemTimerTick( sceneId, x300150_g_scriptId, "ProcTiming", actId, x300150_g_ThinkTimeLen ) --3秒钟思考时间，这时候可以使用道具

			SetMentalGameStatus( sceneId, x300150_g_METAIL_GAME_THINK )

			IncMentalGameCycle( sceneId )	--计数次数+1
			
			MentalGameAskNameList( sceneId, actId )	--请求排行榜
		elseif MentalGameCycle == x300150_g_TotalQuests then
			SetMentalGameStatus( sceneId, x300150_g_METAIL_GAME_STARTED )
			SetSystemTimerTick( sceneId, x300150_g_scriptId, "ProcTiming", actId, 5*1000 ) --答题结束，停留5秒钟
			IncMentalGameCycle( sceneId )	--计数次数+1
			MentalGameAskNameList( sceneId, actId )	--请求排行榜
		else
			SetMentalGameStatus( sceneId, x300150_g_METAIL_GAME_FINISH )
			--print("		_ProcTiming_STARTED 1111111")
			MentalGameGiveAward( sceneId, actId )
			MentalGameFinished( sceneId,actId) --通知客户端已经结束 

		end
		
	elseif status == x300150_g_METAIL_GAME_THINK then
		--print("_ProcTiming_THINK")
		SetMentalGameStatus( sceneId, x300150_g_METAIL_GAME_STARTED )
	
		SetSystemTimerTick( sceneId, x300150_g_scriptId, "ProcTiming", actId, 11*1000 ) --10秒钟答题时间，这时候可以答题

	elseif status == x300150_g_METAIL_GAME_FINISH then
	--print("_ProcTiming_FINISH")
	    MentalGameGiveAward( sceneId, actId )
		SetMentalGameStatus( sceneId, x300150_g_METAIL_GAME_INVALID )
		
	end
end

--开始活动
function x300150_StartGame( sceneId, actId )

	--print( "_StartGame")
--	Msg2Player(  sceneId, selfId,"要提示的信息" , MSG2PLAYER_PARA )

  --初始化答题活动
	InitMentalGame( sceneId, actId )	--初始化答题活动
	
	--所有玩家答题参数清空
	SetAllPlayerRuntimeDataInScene( sceneId, RD_HUMAN_MENTALGAME, -1 )

	--设置状态为开始中ing
	SetMentalGameStatus( sceneId, x300150_g_METAIL_GAME_STARTING )

	
	--向客户端广播答题活动
	BroadCastMentalGameStart(sceneId, actId)

end



--功能函数
--报名成功
function x300150_OnSignUpSuccessed( sceneId, selfId, actId )
--	print( "_OnSignUpSuccessed\n")
	--报名
	local status = GetMentalGameStatus( sceneId )
	--print( "_OnSignUpSuccessed"..status .." "..x300150_g_METAIL_GAME_STARTING)
	if status ~= x300150_g_METAIL_GAME_STARTING then
		return
	end
	
	local nSignUpIndex = SignUpMentalGame( sceneId, selfId, actId )
	if nSignUpIndex == -1 then
		return --报名失败了？？
	end
	
	--保存答题索引
	SetPlayerRuntimeData(sceneId, selfId, RD_HUMAN_MENTALGAME, nSignUpIndex)
	
	--去掉其他状态
	
	--增加“隐身”“无敌”“定身”状态
	SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x300150_g_Impact1, 0);--9825  标记有问题
	
	--给玩家增加5个答题道具
	InitMentalGame_Player( sceneId, selfId, x300150_g_METAIL_GAME_ITEM_NUM );
	--记录参与人数
	GamePlayScriptLog( sceneId, selfId, 91)
	--通知客户端显示界面
	ShowMentalGameInterface( sceneId, selfId, actId )
end

--功能函数
--取消报名
function x300150_OnUnSignUp( sceneId, selfId, actId )
	--去掉玩家“隐身”“无敌”“定身”状态
	CancelSpecificImpact(sceneId, selfId, x300150_g_Impact1);
end

function x300150_GiveAward( sceneId, selfId, score, sortid )

--	local exp = GetLevel(sceneId, selfId) * score * 2.25;
--	if sortid < 3 then
--		if sortid == 0 then
--			exp = exp * 2.5;
--		elseif sortid == 1 then
--			exp = exp * 2;
--		else
--			exp = exp * 1.5
--		end
--	end
--	AddExp(sceneId, selfId, exp);
--	local str = format("在本次智力竞赛活动中你获得了%d经验的奖励！", exp);
--	hf_DisplayAwardInfo(sceneId, selfId, -1, -1, -1, 0, 0, exp, 0, 0);
	local gudingjiangli = ( GetLevel(sceneId, selfId) * 2000 ) /2;
	local fujiajiangli	= 0
	--( GetLevel(sceneId, selfId) * score * 10 ) /2;
		if score < 460 then
			fujiajiangli = ( GetLevel(sceneId, selfId) * score * 10 ) /2;
		else
			fujiajiangli = ( GetLevel(sceneId, selfId) * score * 10 )
		end	
	local paimingjiangli = gudingjiangli + fujiajiangli;
	local paimingtishi;
	if sortid < 3 then
		if sortid == 0 then
			paimingjiangli = paimingjiangli * 2;
--			paimingtishi = format("在本次答题中，%s获得了第一名！", GetName(sceneId, selfId));
--			--Msg2Player(sceneId, selfId, paimingtishi, 2, 4);
--			LuaAllScenceM2Wrold(sceneId, paimingtishi,4,1)
		elseif sortid == 1 then
			paimingjiangli = paimingjiangli * 1.5;
--			paimingtishi = format("在本次答题中，%s获得了第二名！", GetName(sceneId, selfId));
--			--Msg2Player(sceneId, selfId, paimingtishi, 2, 4);
--			LuaAllScenceM2Wrold(sceneId, paimingtishi,4,1)
		else
			paimingjiangli = paimingjiangli * 1.2
--			paimingtishi = format("在本次答题中，%s获得了第三名！", GetName(sceneId, selfId));
--			--Msg2Player(sceneId, selfId, paimingtishi, 2, 4);
--			LuaAllScenceM2Wrold(sceneId, paimingtishi,4, 1)
		end
	end
	AddExp(sceneId, selfId, paimingjiangli);
	--记录完成人数
	GamePlayScriptLog( sceneId, selfId, 92)
	
	local str = "";
	if(sortid < 3) then
		if(fujiajiangli > 0) then
			str = format("#o在本次智力竞赛活动中你获得了#r#R%d点经验#o的固定奖励,#r#R%d点经验#o的附加奖励,#r由于您在本次答题中获得了#R第%d名#o,#r您获得了#R%d点经验#o的总奖励！", gudingjiangli, fujiajiangli, sortid+1, paimingjiangli);
		else
			str = format("#o在本次智力竞赛活动中你获得了#r#R%d点经验#o的固定奖励,#r由于您在本次答题中获得了#R第%d名#o,#r您获得了#R%d点经验#o的总奖励！", gudingjiangli, sortid+1, paimingjiangli);
		end
	else
		if(fujiajiangli > 0) then
			str = format("#o在本次智力竞赛活动中你获得了#r#R%d点经验#o的固定奖励,#r#R%d点经验#o的附加奖励,#r您获得了#R%d点经验#o的总奖励！", gudingjiangli, fujiajiangli, paimingjiangli);
		else
			str = format("#o在本次智力竞赛活动中你获得了#r#R%d点经验#o的固定奖励,#r您获得了#R%d点经验#o的总奖励！", gudingjiangli, paimingjiangli);
		end
		
	end
	Msg2Player(sceneId, selfId, str, 4, 2);
end
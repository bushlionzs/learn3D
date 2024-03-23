---------------------------------------------------------------------
-- fuben common callscriptfunction
--副本回调函数:副本脚本可以Call这个脚本的函数
------------------------------------------------------------------
x700103_g_ScriptId			=	700103
---
--# define 0-20 for common,  240-255 for common
-----------------------------------------------
x700103_CSP_FUBENTYPE				= 	0
x700103_CSP_SCRIPTID				=	1
x700103_CSP_TICKCOUNT				= 	2
x700103_CSP_BACKSCENEID				= 	3
x700103_CSP_ISCLOSING				= 	4
x700103_CSP_LEAVECOUNTDOWN			= 	5
x700103_CSP_TEAMID					=	6
x700103_CSP_TICKTIME				=	7
x700103_CSP_HOLDTIME				=	8
x700103_CSP_FUBENLEVEL				=	9

x700103_CSP_FUBEN_SCENE_ID			=	10
x700103_CSP_CLOSETICK				=	11
x700103_CSP_TICKCOUNT_ADD			=	12
x700103_CSP_TICKCOUNT_SUB			=	13
x700103_CSP_B_TOPLIST_ABLE			=	14
x700103_CSP_PLAYER_DEAD				=	15


x700103_CSP_HUMAN_COUNT				=	240
x700103_CSP_PLAYER_ENTER_START		=	241

x700103_CSP_LAST_TICKOUNT			=	247
x700103_CSP_GUID_START              =   248  --空6个
x700103_CSP_FUBEN_TYPE				=	254	--试炼，普通，英雄，三种类型
x700103_CSP_FUBEN_MODE				=   255


------------------------ fuben common data start---------------------

x700103_g_TopListMonsterLimited = {
									{scriptid = 700028, count = 10, campid = 21},  --囚龙岛    
									{scriptid = 700023, count = 10, campid = 21},  --囚龙城堡  
									{scriptid = 700004, count = 10, campid = 21},  --龙穴      
									{scriptid = 700024, count = 10, campid = 21},  --东海眼    
									{scriptid = 700008, count = 10, campid = 21},  --和氏璧    
									{scriptid = 700009, count = 10, campid = 21},  --金銮殿    
									{scriptid = 700108, count = 10, campid = 21},  --赤血号    
									{scriptid = 700027, count = 10, campid = 21},  --水师大营    
									{scriptid = 700109, count = 10, campid = 21},  --赤血号    
									{scriptid = 700030, count = 10, campid = 21},  --一打祝家庄
									{scriptid = 700031, count = 10, campid = 21},  --二打祝家庄
									{scriptid = 700032, count = 10, campid = 21},  --三打祝家庄
									{scriptid = 700084, count = 10, campid = 21}, --【队伍】探索战神墓（一）
									{scriptid = 700085, count = 10, campid = 21}, --【队伍】探索战神墓（二）
									{scriptid = 700086, count = 10, campid = 21}, --【队伍】探索战神墓（三）
									{scriptid = 700087, count = 10, campid = 21}, --【队伍】印度神庙（一）
									{scriptid = 700088, count = 10, campid = 21}, --【队伍】印度神庙（二）
									{scriptid = 700089, count = 10, campid = 21}, --【队伍】印度神庙（三）
									{scriptid = 700090, count = 10, campid = 21}, --【队伍】教堂的秘密（一）
									{scriptid = 700091, count = 10, campid = 21}, --【队伍】教堂的秘密（二）
									{scriptid = 700092, count = 10, campid = 21}, --【队伍】教堂的秘密（三）
								}
------------------------ fuben common data end---------------------
------------------------------------------------------
-- 记录副本排行榜
---------------------------------------------------------
function x700103_OnFubuenCompleted(sceneId)
	if GetSceneType(sceneId)~=1 then
		return
	end

	

	local nFubenType = GetFubenData_Param(sceneId, 0 )
	local nFubenMode = GetFubenData_Param(sceneId, 255 )

	local nParam = 0
	
	local strFubenName = ""
	if nFubenType == FUBEN_DONGHAIHAIYAN then
		nParam = QIULONGDAO_TOPLIST
		strFubenName = "囚龙岛"
	elseif nFubenType == FUBEN_HESHIBI then
		nParam = HESHIBI_TOPLIST
		strFubenName = "和氏璧"
	elseif nFubenType == FUBEN_HUOQIYING then
		nParam = CAISHENDIAN_TOPLIST
		strFubenName = "赤血号"
	elseif nFubenType == FUBEN_ZHUJIAZHUANG3 then
		nParam = ZHUJIAZHUANG_TOPLIST
		strFubenName = "祝家庄"
	elseif nFubenType == FUBEN_FUTUTA4 then
		nParam = LUNHUITAI_TOPLIST
		strFubenName = "轮回台"
	elseif nFubenType == FUBEN_TANSUO_ZHANSHENMU_3 then
		nParam = ZHANSHENMU_TOPLIST
		strFubenName = "夏王墓"
	elseif nFubenType == FUBEN_YINDUSHENMIAO3 then
		nParam = INDIANTEMPLE_TOPLIST
		strFubenName = "印度河"
	elseif nFubenType == FUBEN_JIAOTANGMIMI3 then
		nParam = JINGJIAOTANG_TOPLIST
		strFubenName = "大教堂"			
	else
		return
	end

	--连环副本非现金副本不进排行榜
--	if nFubenMode == 0 then
--		return
--	end
	if nFubenType ~= FUBEN_FUTUTA4 then
		if nFubenMode == 0 then
			return
		end
	else
		Type = GetFubenData_Param(sceneId, x700103_CSP_FUBEN_TYPE )
		if Type ~= 0 then
			return
		end
	end
	
	local nResult = x700103_CheckFubenTopList(sceneId)
	if nResult~=3 and nResult~=6 then
		return
	end

	local nTick = GetFubenData_Param(sceneId, x700103_CSP_LAST_TICKOUNT )
	local nTickCount = GetFubenData_Param(sceneId, x700103_CSP_TICKCOUNT )

	local humancount = GetFuben_PlayerCount(sceneId);

	--副本时间Start
	local nowTime = (nTick+nTickCount)*5;
	local nHour = floor(nowTime/3600)
	local nMinute = floor(nowTime/60)
	local nSec = mod(nowTime,60)
	
	local strTime = "恭喜您仅用了"
	if nHour>0 then
		strTime = strTime..format("%d小时", nHour)
	end
	if nMinute>0 then
		strTime = strTime..format("%d分",nMinute)
	end
	if nSec>0 then
		strTime = strTime..format("%d秒",nSec)
	end

	strTime = strTime.."完成了"..strFubenName.."副本";
	
	x700103_ShowTipsToAll(sceneId,strTime)
	--//副本时间End
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		SendToplistKeyValue2GL(sceneId,humanId,nParam,(nTick+nTickCount)*5)
	end

	if nowTime>15*60 then
		return
	end

	if nFubenType == FUBEN_DONGHAIHAIYAN then
		CallScriptFunction( 701103, "OnFubuenCompleted", sceneId) --"囚龙岛"
	elseif nFubenType == FUBEN_HESHIBI then
		CallScriptFunction( 701109, "OnFubuenCompleted", sceneId)  --"和氏璧"
	elseif nFubenType == FUBEN_HUOQIYING then						
		CallScriptFunction( 701115, "OnFubuenCompleted", sceneId)  --赤血号
	elseif nFubenType == FUBEN_ZHUJIAZHUANG3 then
		CallScriptFunction( 701121, "OnFubuenCompleted", sceneId) 
	elseif nFubenType == FUBEN_FUTUTA4 then
		
	elseif nFubenType == FUBEN_TANSUO_ZHANSHENMU_3 then
		CallScriptFunction( 701106, "OnFubuenCompleted", sceneId) -- 夏王墓
		
	elseif nFubenType == FUBEN_YINDUSHENMIAO3 then
		CallScriptFunction( 701118, "OnFubuenCompleted", sceneId)	--印度河
	elseif nFubenType == FUBEN_JIAOTANGMIMI3 then
		CallScriptFunction( 701112, "OnFubuenCompleted", sceneId)  --大教堂
	else
		return
	end

	
	
	
end

--检查副本能不能进排行榜， 0：不能进， 1：能进
function x700103_CheckFubenTopList(sceneId, nCheckMode)
	if GetSceneType(sceneId)~=1 then
		return 1 -- "非副本内"
	end

	
	local bToplistDisabled = GetFubenData_Param(sceneId, x700103_CSP_B_TOPLIST_ABLE )

	if(bToplistDisabled>0) then
		return 2 -- "已经关闭"
	end

	local nScriptId = GetFubenData_Param(sceneId, 1 )

	

	local bFind = 0;
	local nMaxCount = 0;
	local nStdCampId = 0
	for i,item in x700103_g_TopListMonsterLimited do
		if item.scriptid ==  nScriptId then
			bFind = 1;
			nMaxCount = item.count;
			nStdCampId = item.campid
			break;
		end
	end

	if(bFind==0) then
		return 3 --"这个副本没有限制, 可以进入排行榜"
	end

	local nFubenType = GetFubenData_Param(sceneId, 0 )
	local nFubenMode = GetFubenData_Param(sceneId, 255 )

	--连环副本非现金副本不进排行榜
--	if nFubenMode == 0 then
--		return 4 --"不是现金连环副本"
--	end
	if nFubenType ~= FUBEN_FUTUTA4 then
		if nFubenMode == 0 then
			return 4 --"不是现金连环副本"
		end
	else
		Type = GetFubenData_Param(sceneId, x700103_CSP_FUBEN_TYPE )
		if Type ~= 0 then
			return
		end
	end
	
	local nCount = 0;
	local nMonsterCount = GetMonsterCount(sceneId)
	for i=1,nMonsterCount do
    	local objid = GetMonsterObjID(sceneId,i-1)

		local nCamp = GetMonsterCamp(sceneId,objid)
    	if nCamp == nStdCampId then  --如果是敌对阵营
    		nCount = nCount + 1
    	end
	end

	if(nCount>nMaxCount) then
		if nCheckMode~=nil then
			if nCheckMode==1 then
			else
				SetFubenData_Param(sceneId, x700103_CSP_B_TOPLIST_ABLE, 1 )
				x700103_ShowTipsToAll(sceneId,"剩余怪物数过多，无法进入排行榜！")
			end
		else
			SetFubenData_Param(sceneId, x700103_CSP_B_TOPLIST_ABLE, 1 )
			x700103_ShowTipsToAll(sceneId,"剩余怪物数过多，无法进入排行榜！")
		end
		 
		return 5, nCount,nMaxCount --"剩余怪物数过多，无法进入排行榜！"
	end
	return 6


	
end

---------------------------------------------------------------------------------------------------
--检查玩家错误状态
---------------------------------------------------------------------------------------------------
function x700103_IsPlayerErrorState( sceneId,selfId )

    local state

    state = IsPlayerStateNormal(sceneId,selfId )
    if state == 0 then
        return 1
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_MENTALGAME )
    if state == 1 then
        return 1
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_STALL )
    if state == 1 then
        return 1
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_DIE )
    if state == 1 then
        return 1
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_CRASHBOX )
    if state == 1 then
        return 1
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_AUTOPLAY )
    if state == 1 then
        return 1
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_SUBTRAIN )
    if state == 1 then
        return 1
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_BUS )
    if state == 1 then
        return 1
    end

		state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_ENJAIL )
    if state == 1 then
        return 1
    end	

	--// add in 2-20-2009
	state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_WEDDING )
    if state == 1 then
        return 1
    end

	state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_TONGQUBUFF )
    if state == 1 then
        return 1
    end

	state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_TIESAN )
    if state == 1 then
        return 1
    end
	--// added end


    return 0

end

function x700103_ShowTipsToAll(sceneId, str)

	local humancount = GetFuben_PlayerCount(sceneId);

	--通知玩家
	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId,str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, humanId);
	end
end


function x700103_OnXianjinBossDie(sceneId)	

	local humancount = GetFuben_PlayerCount(sceneId);

	--通知玩家
	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local addInh = 600
		if GetLevel(sceneId, humanId) >= 80 then
			if IsHaveSpecificImpact( sceneId, humanId, 9012) == 1 then --朝迋请柬
				addInh =  addInh + floor(addInh*0.20)
			end
			local refixInh = AddInherenceExp(sceneId, humanId, addInh)
			local str = format("你获得了%d点天赋值",refixInh)
			Msg2Player(sceneId,humanId,str,8,2)
			Msg2Player(sceneId,humanId,str,8,3)
			--BeginQuestEvent(sceneId);
			--AddQuestText(sceneId,str);
			--EndQuestEvent();
			--DispatchQuestTips(sceneId, humanId)
			
		end
	end
end

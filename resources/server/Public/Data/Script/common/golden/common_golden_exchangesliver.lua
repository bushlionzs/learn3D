--功能：现金换银卡

--MisDescBegin
--脚本号
x800056_g_ScriptId = 800056

--上一个任务的ID
--g_MissionIdPre =



--任务文本描述
x800056_g_MissionName="兑换银票"

x800056_g_LevelLess	= 20
x800056_g_DayCountUntil = 50

x800056_g_ItemList = {11060001,11060002,11060003}

--MisDescEnd

x800056_g_GameId	= 1003


--**********************************
--任务入口函数
--**********************************

function x800056_ProcEventEntry( sceneId, selfId, NPCId, MissionId,nExt)	--点击该任务后执行此脚本
	if GetGameOpenById(x800056_g_GameId)<=0 then
		x800056_ShowTips(sceneId, selfId,"此功能已关闭")
		return
	end

	if nExt==nil then
		return
	end

	if nExt==0 then

		local nLevel = GetLevel( sceneId, selfId)
		if nLevel<x800056_g_LevelLess then
			x800056_ShowTips(sceneId, selfId,format("等级不足%d，无法使用该功能",x800056_g_LevelLess))
			return 0
		end

		if x800056_g_DayCountUntil>0 then

			
			if x800056_GetDayCount(sceneId, selfId)>=x800056_g_DayCountUntil then
				x800056_ShowTips(sceneId, selfId,format("您当天已经换满了%d张，无法再次换取",x800056_g_DayCountUntil))
				return 0
			end
			
		end

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800056_g_MissionName)
			AddQuestText(sceneId,"\t在我这里，你可以将银票兑换为银卡。等级越高，可以兑换的银票种类越多。银票可以在金币商店（快捷键J）购买。每天可以允许兑换50张。")

			AddQuestText(sceneId,format("\t#Y  您今天还可以换取#G%d#Y张",x800056_g_DayCountUntil-x800056_GetDayCount(sceneId, selfId)))
			if nLevel>=20 then
				AddQuestNumText(sceneId, MissionId, "全部兑换",3,15);
				AddQuestNumText(sceneId, MissionId, "我要用王国银票兑换",3,1);
			end
			if nLevel>=40 then
				AddQuestNumText(sceneId, MissionId, "我要用大元银票兑换",3,5);
			end
			if nLevel>=60 then
				AddQuestNumText(sceneId, MissionId, "我要用帝国银票兑换",3,10);
			end
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, NPCId, x800056_g_ScriptId, MissionId);


	end

	if nExt==1 or nExt==5 or nExt==10 or nExt==15 then
		x800056_DispatchExchangeInfo( sceneId, selfId, NPCId,nExt )
	end
end



function x800056_DispatchExchangeInfo( sceneId, selfId, NPCId, nExt )
	if GetGameOpenById(x800056_g_GameId)<=0 then
		x800056_ShowTips(sceneId, selfId,"此功能已关闭")
		return
	end

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y"..x800056_g_MissionName)
		if nExt==1 then
			AddQuestText(sceneId,format("\t你要用#G王国银票#W换取%d两银卡吗？", nExt*18))
		elseif nExt==5 then
			AddQuestText(sceneId,format("\t你要用#G大元银票#W换取%d两银卡吗？", nExt*18))
		elseif nExt==10 then
			AddQuestText(sceneId,format("\t你要用#G帝国银票#W换取%d两银卡吗？", nExt*18))
		elseif nExt==15 then
			AddQuestText(sceneId,format("\t你要用背包中#G全部银票#W换取银卡吗？\n \n\t1张#G帝国银票#W=180两银卡\n\t1张#G大元银票#W=90两银卡\n\t1张#G王国银票#W=18两银卡\n \n\t将按照银票等级由高到低的优先级换取，每日银票换取数量上限为50张。"))
		else
			return
		end

		--AddQuestItemDemand(sceneId, 10018001, 2)
		--AddQuestText(sceneId," ")

		

	print(nExt)
	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x800056_g_ScriptId, -1);
	x800056_SetSelected(sceneId, selfId, nExt)
end



--**********************************
--列举事件
--**********************************
function x800056_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x800056_g_GameId)<=0 then
		
		return
	end
	AddQuestNumText(sceneId,x800056_g_ScriptId,x800056_g_MissionName,3,0);
end


--********************
--检测接受条件
--**********************************
function x800056_ProcAcceptCheck( sceneId, selfId, NPCId )
	if GetGameOpenById(x800056_g_GameId)<=0 then
		x800056_ShowTips(sceneId, selfId,"此功能已关闭")
		return 0
	end
		return 1
end

--**********************************
--接受
--**********************************
function x800056_ProcAccept( sceneId, selfId )

	if GetGameOpenById(x800056_g_GameId)<=0 then
		x800056_ShowTips(sceneId, selfId,"此功能已关闭")
		return
	end

	local nLevel = GetLevel( sceneId, selfId)
	if nLevel<x800056_g_LevelLess then
		x800056_ShowTips(sceneId, selfId,format("等级不足%d，无法使用该功能",x800056_g_LevelLess))
		return
	end

	if x800056_g_DayCountUntil>0 then
		if x800056_GetDayCount(sceneId, selfId)>=x800056_g_DayCountUntil then
			x800056_ShowTips(sceneId, selfId,format("您当天已经换满了%d张，无法再次换取",x800056_g_DayCountUntil))
			return
		end
		
	end

	local nExt = x800056_GetSelected(sceneId, selfId)
	print(nExt)
	local nHaveCount = 0

	local nIndex = 0
	
	if nExt==1 then
		nIndex = 1;
	elseif nExt==5 then
		nIndex = 2;
	elseif nExt==10 then
		nIndex = 3;
	elseif nExt==15 then
		nIndex = 4;
	else
		return
	end
	
	local nHaveCount1 = GetItemCount( sceneId, selfId, x800056_g_ItemList[1] )
	local nHaveCount2 = GetItemCount( sceneId, selfId, x800056_g_ItemList[2] ) 
	local nHaveCount3 = GetItemCount( sceneId, selfId, x800056_g_ItemList[3] )

	if nExt==15 then 
	
		nHaveCount = nHaveCount1
		
		if nLevel >= 40 then
			nHaveCount = nHaveCount1 + nHaveCount2
		end
		
		if nLevel >= 60 then
	 	nHaveCount = nHaveCount1 + nHaveCount2 + nHaveCount3
	 	end
	else
		nHaveCount = GetItemCount( sceneId, selfId, x800056_g_ItemList[nIndex] )
	end

	if nHaveCount<1 then
		if nExt==1 then
			local str = format("背包中没有足够的#G@item_%d",x800056_g_ItemList[nIndex])
			x800056_ShowTips(sceneId, selfId,str)
		elseif nExt==5 then
			local str = format("背包中没有足够的#G@item_%d",x800056_g_ItemList[nIndex])
			x800056_ShowTips(sceneId, selfId,str)
		elseif nExt==10 then
			local str = format("背包中没有足够的#G@item_%d",x800056_g_ItemList[nIndex])
			x800056_ShowTips(sceneId, selfId,str)
		elseif nExt==15 then
			x800056_ShowTips(sceneId, selfId,"背包中没有可兑换的#G银票")
		else
			return
		end

		return
	end
	
	local nDelCount = 1
	
	if nExt==15 then 
		if nLevel >= 60 and nHaveCount3 > 0 then
			nExt = 10 
			nIndex = 3
			local nCanCount = x800056_g_DayCountUntil-x800056_GetDayCount(sceneId, selfId)
			if nHaveCount3 < nCanCount then 
				nDelCount = nHaveCount3
				x800056_Addmoney(sceneId, selfId, nExt,nIndex,nDelCount)
			else
				nDelCount = nCanCount
				x800056_Addmoney(sceneId, selfId, nExt,nIndex,nDelCount)
				return
			end
		end
		if nLevel >= 40 and nHaveCount2 > 0 then 
			nExt = 5 
			nIndex = 2
			local nCanCount = x800056_g_DayCountUntil-x800056_GetDayCount(sceneId, selfId)
			if nHaveCount2 < nCanCount then 
				nDelCount = nHaveCount2
				x800056_Addmoney(sceneId, selfId, nExt,nIndex,nDelCount)
			else
				nDelCount = nCanCount
				x800056_Addmoney(sceneId, selfId, nExt,nIndex,nDelCount)
				return
			end
		end
		if nLevel >= 20 and nHaveCount1 > 0 then 
			nExt = 1 
			nIndex =1
			local nCanCount = x800056_g_DayCountUntil-x800056_GetDayCount(sceneId, selfId)
			if nHaveCount1 < nCanCount then 
				nDelCount = nHaveCount1
				x800056_Addmoney(sceneId, selfId, nExt,nIndex,nDelCount)
			else
				nDelCount = nCanCount
				x800056_Addmoney(sceneId, selfId, nExt,nIndex,nDelCount)
				return
			end
		end	
		
	else
		x800056_Addmoney(sceneId, selfId, nExt,nIndex,nDelCount)
		
	end
end

--**********************************
--放弃
--**********************************
function x800056_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x800056_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x800056_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x800056_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x800056_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x800056_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x800056_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

function x800056_ShowTips(sceneId, selfId,str)
	
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, str);
	EndQuestEvent(sceneId);

	DispatchQuestTips(sceneId, selfId);
end

---------------------------------------------------------------------------------------------------
--取得当前张数
---------------------------------------------------------------------------------------------------
function x800056_GetDayCount(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_XIANJIN2YINKA_DATE[1], MD_XIANJIN2YINKA_DATE[2],MD_XIANJIN2YINKA_DATE[3] );
	
	if lastday ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, MD_XIANJIN2YINKA_DAYCOUNT[1], MD_XIANJIN2YINKA_DAYCOUNT[2],MD_XIANJIN2YINKA_DAYCOUNT[3] );
	return daycount;
end

---------------------------------------------------------------------------------------------------
--设置当天张数
---------------------------------------------------------------------------------------------------
function x800056_SetDayCount(sceneId, selfId, flag)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_XIANJIN2YINKA_DATE[1], MD_XIANJIN2YINKA_DATE[2], MD_XIANJIN2YINKA_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_XIANJIN2YINKA_DATE[1], MD_XIANJIN2YINKA_DATE[2], MD_XIANJIN2YINKA_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_XIANJIN2YINKA_DAYCOUNT[1], MD_XIANJIN2YINKA_DAYCOUNT[2], MD_XIANJIN2YINKA_DAYCOUNT[3], flag)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_XIANJIN2YINKA_DAYCOUNT[1], MD_XIANJIN2YINKA_DAYCOUNT[2], MD_XIANJIN2YINKA_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, MD_XIANJIN2YINKA_DAYCOUNT[1], MD_XIANJIN2YINKA_DAYCOUNT[2], MD_XIANJIN2YINKA_DAYCOUNT[3], daycount+flag)
	end
end


---------------------------------------------------------------------------------------------------
--得到玩家刚才选择的界面选项
---------------------------------------------------------------------------------------------------
function x800056_GetSelected(sceneId, selfId)
	local flag = GetQuestData(sceneId, selfId, MD_XIANJIN2YINKA_FLAG[1], MD_XIANJIN2YINKA_FLAG[2],MD_XIANJIN2YINKA_FLAG[3] )
	return flag
end


---------------------------------------------------------------------------------------------------
--设置玩家刚才选择的界面选项
---------------------------------------------------------------------------------------------------
function x800056_SetSelected(sceneId, selfId, flag)
	SetQuestData(sceneId, selfId, MD_XIANJIN2YINKA_FLAG[1], MD_XIANJIN2YINKA_FLAG[2], MD_XIANJIN2YINKA_FLAG[3], flag)
end


function x800056_Addmoney(sceneId, selfId, nExt,nIndex,nDelCount)

	local nMoney1 = GetMoney(sceneId, selfId, 1) --银卡
	if(nMoney1+nExt*nDelCount*1000*18)>999999999 then
		x800056_ShowTips(sceneId, selfId,"银卡已达上限")
		return
	end
	
	local	nRet = DelItem(sceneId, selfId,x800056_g_ItemList[nIndex],nDelCount)

	if nRet<=0 then
		x800056_ShowTips(sceneId, selfId,"使用物品失败")
		return
	end
	
	AddMoney(sceneId, selfId, 1, nExt*nDelCount*1000*18)

	local str = format("你使用%d个#G@item_%d#o换取了%d两银卡",nDelCount,x800056_g_ItemList[nIndex], nExt*nDelCount*18 );

	x800056_ShowTips(sceneId, selfId,str)

	Msg2Player(sceneId, selfId, str, 4, 2);

	x800056_SetDayCount(sceneId, selfId ,nDelCount)

	
	GamePlayScriptLog(sceneId, selfId, 921)

	--// 增加日志
	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u",myGuid)
	local strName = GetName(sceneId,selfId)
	local nDayCount = x800056_GetDayCount(sceneId, selfId)
	local msg = "DHYP,"..myGuid..","..strName..","..nExt..","..nDayCount;

	WriteLog(1,msg)
end
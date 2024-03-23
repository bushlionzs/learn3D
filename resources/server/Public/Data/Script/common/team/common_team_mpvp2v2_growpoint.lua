--############################################
--##跨服 2v2 战场采集点脚本 by rj 2010-11-3 ##
--############################################

--当前采集点类型配置数组，希望在这个地图上出现的采集点类型及对应的buf
x303104_g_GrowPonitTypeAry 			= 
{
{type = 840, bufid = 30070}, 
{type = 841, bufid = 30071},
{type = 842, bufid = 30072}, 
{type = 843, bufid = 30073},
{type = 844, bufid = 30074}, 
{type = 845, bufid = 30075},
{type = 846, bufid = 30070}, 
{type = 847, bufid = 30071},
{type = 848, bufid = 30072}, 
{type = 849, bufid = 30073},
{type = 850, bufid = 30074}, 
{type = 851, bufid = 30075},
{type = 852, bufid = 30070}, 
{type = 853, bufid = 30071},
{type = 854, bufid = 30072}, 
{type = 855, bufid = 30073},
{type = 856, bufid = 30074}, 
{type = 857, bufid = 30075},
}											
--采集点出现随机点表
x303104_g_curGrowPonitInfoTbl 		= {}
--当前采集点哈希表，使用objid做key
x303104_g_curExistAllGrowPonitTbl 	= {}	
--当前场景是否已经初始化过标志表													
x303104_g_curSceneInit	 			= {}		
--采集箱子buf对应名字，key是bufid
x303104_g_GrowPonitBufName			= {}

-------------------------------------------------------------------------
--被主战场逻辑调用的初始化采集点函数
-------------------------------------------------------------------------
function x303104_OnInit(sceneId)
	
	--每次进入战场采集点全部回收，-1 参数调用在程序内部会强转成最大值，使其无线延迟不会刷出资源
	for i, item in x303104_g_GrowPonitTypeAry do
		RecycleGrowPointByType(sceneId, item.type, -1)
	end

	--初始化采集buf名字，key是bufid
	x303104_g_GrowPonitBufName[30070] = "加速"
	x303104_g_GrowPonitBufName[30071] = "回复"
	x303104_g_GrowPonitBufName[30072] = "暴击伤害增加"
	x303104_g_GrowPonitBufName[30073] = "补给"
	x303104_g_GrowPonitBufName[30074] = "伤害减免"
	x303104_g_GrowPonitBufName[30075] = "忽视减免"	
	--初始化本场景配置坐标点表
	x303104_g_curGrowPonitInfoTbl[sceneId] =
	 {
		 {type = 0, exist = 0, tmp = 0, x = 90,y = 	140	}, 
		 {type = 0, exist = 0, tmp = 0, x =	86,y = 	140	}, 
		 {type = 0, exist = 0, tmp = 0, x =	88,y = 	141	}, 
		 {type = 0, exist = 0, tmp = 0, x =	87,y = 	113	}, 
		 {type = 0, exist = 0, tmp = 0, x =	84,y = 	111	}, 
		 {type = 0, exist = 0, tmp = 0, x =	79,y = 	112	}, 
		 {type = 0, exist = 0, tmp = 0, x =	167,y =	140	}, 
		 {type = 0, exist = 0, tmp = 0, x =	170,y =	136	}, 
		 {type = 0, exist = 0, tmp = 0, x =	174,y =	140	}, 
		 {type = 0, exist = 0, tmp = 0, x =	167,y =	116	}, 
		 {type = 0, exist = 0, tmp = 0, x =171,y =	112	}, 
		 {type = 0, exist = 0, tmp = 0, x =174,y =	114	}, 
		 {type = 0, exist = 0, tmp = 0, x =127,y =	142	}, 
		 {type = 0, exist = 0, tmp = 0, x =125,y =	151	}, 
		 {type = 0, exist = 0, tmp = 0, x =130,y =	151	}, 
		 {type = 0, exist = 0, tmp = 0, x =125,y =	105	}, 
		 {type = 0, exist = 0, tmp = 0, x =128,y =	113	}, 
		 {type = 0, exist = 0, tmp = 0, x =130,y =	105	}, 

	 }
	 
	 --删除在启动地图就创建的采集资源点
	 x303104_g_curSceneInit[sceneId] = 1
end

-------------------------------------------------------------------------
--回收这个玩家战场中拿到的采集点 buf
-------------------------------------------------------------------------
function x303104_RecyclePlayerAllBuf(sceneId, selfId)

	for i, item in x303104_g_GrowPonitTypeAry do
        DispelSpecificImpact(sceneId, selfId, item.bufid, 1)
    end
end


-------------------------------------------------------------------------
--被主战场逻辑定时调用的产生采集点函数
-------------------------------------------------------------------------
function x303104_OnTimeMakeGrowPoint(sceneId)

	--记录操作必须在OnInit之后将空间分配才能进行，否则会出错误
	if x303104_g_curSceneInit[sceneId] == nil then
		return
	end
	
	--忽略错误或取消的配置
	local nTypeNum = getn(x303104_g_GrowPonitTypeAry)
	if nTypeNum == 0 then
		return
	end

	local tblOkPoint = {}
	local tblOkType = {}
	local nOkPointIdx = 0
	local nOkTypeIdx = 0
	local nExistNum = 0
	local nPosNum = getn(x303104_g_curGrowPonitInfoTbl[sceneId])

	--找出所有还没添加到地图上的类型集合组成临时数组
	for i, item1 in x303104_g_GrowPonitTypeAry do
		
		local nExist = 0
		for j, item2 in x303104_g_curGrowPonitInfoTbl[sceneId] do
			if item1.type == item2.type then
				nExist = 1
				break
			end
		end
		
		if nExist == 0 then
			nOkTypeIdx = nOkTypeIdx + 1
			tblOkType[nOkTypeIdx] = item1.type
		end
	end

	--所有类型采集点都在地图上了，不能再添加了
	if getn(tblOkType) == 0 then
		return
	end

	--找出所有还没有被占用的位置点组成临时数组
	for i = 1, nPosNum do
		if x303104_g_curGrowPonitInfoTbl[sceneId][i].exist == 0 then
			nOkPointIdx = nOkPointIdx + 1
			tblOkPoint[nOkPointIdx] = x303104_g_curGrowPonitInfoTbl[sceneId][i]
		
			--记录x303104_g_curGrowPonitTypeTbl的索引
			tblOkPoint[nOkPointIdx].tmp = i
		else
			nExistNum = nExistNum + 1
		end
	end
	
	--已经到达刷新位置点的上限（点已经与类型最大值一样多了）
	if nExistNum >= nTypeNum then
		return
	end
	
	--随机这个数组找出一个位置随机创建资源
	if nOkPointIdx > 0 then
		local nIndex1 = random(1, nOkPointIdx)
		local nIndex2 = random(1, nOkTypeIdx)

		--刷出这个资源, 0 表示立即刷出，没有延迟，调用 OnCreate 创建 obj
		RecycleGrowPointByType(sceneId, tblOkType[nIndex2], 0)
		SetGrowPointPos(sceneId, tblOkType[nIndex2], tblOkPoint[nIndex1].x, tblOkPoint[nIndex1].y)

		--更新这个位置点信息
		x303104_g_curGrowPonitInfoTbl[sceneId][tblOkPoint[nIndex1].tmp].type = tblOkType[nIndex2]	
		x303104_g_curGrowPonitInfoTbl[sceneId][tblOkPoint[nIndex1].tmp].exist = 1	
	end		
end

-------------------------------------------------------------------------
--采集点创建
-------------------------------------------------------------------------
function x303104_OnCreate(sceneId, growPointType, x, y)

	--实际创建采集资源，默认不显示
	local ItemBoxId = ItemBoxEnterScene(x, y, growPointType, sceneId, 0, -1)
	SetGrowPointObjID(sceneId, growPointType, x, y, ItemBoxId)
	
	--使用前必须初始化，否则出错
	if x303104_g_curExistAllGrowPonitTbl[sceneId] == nil then
		x303104_g_curExistAllGrowPonitTbl[sceneId] = {}
	end
	
	x303104_g_curExistAllGrowPonitTbl[sceneId][ItemBoxId] = growPointType
end

-------------------------------------------------------------------------
--采集点打开
-------------------------------------------------------------------------
function x303104_OnOpen(sceneId, selfId, targetId)

	--记录操作必须在OnInit之后将空间分配才能进行，否则会出错误
	if x303104_g_curSceneInit[sceneId] == nil then
		return 1
	end
	
	if getn(x303104_g_GrowPonitTypeAry) == 0 then
		return 1
	end

	if x303104_g_curExistAllGrowPonitTbl[sceneId][targetId] == nil then
		return 1
	end
	
	--回收这个采集点，不会触发 OnRecycle，从地图上删除 obj，不再新生成
	RecycleGrowPointByType(sceneId, x303104_g_curExistAllGrowPonitTbl[sceneId][targetId], -1)

	--将这个位置清除保存
	local nPosNum = getn(x303104_g_curGrowPonitInfoTbl[sceneId])

	for i = 1, nPosNum do
		if x303104_g_curGrowPonitInfoTbl[sceneId][i].type == x303104_g_curExistAllGrowPonitTbl[sceneId][targetId] then
			x303104_g_curGrowPonitInfoTbl[sceneId][i].type = 0
			x303104_g_curGrowPonitInfoTbl[sceneId][i].exist = 0
			break
		end
	end
	
	--添加 buf
	for i, item in x303104_g_GrowPonitTypeAry do
		if item.type == x303104_g_curExistAllGrowPonitTbl[sceneId][targetId] then
			SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, item.bufid, 0)
			if x303104_g_GrowPonitBufName[item.bufid] ~= nil then
				Msg2Player(sceneId, selfId, format("您采集到了【%s】效果", x303104_g_GrowPonitBufName[item.bufid]), 8, 2)
				Msg2Player(sceneId, selfId, format("您采集到了【%s】效果", x303104_g_GrowPonitBufName[item.bufid]), 8, 3)	
				WriteLog(1, format("MP2BL:x303104_OnOpen 1 SceneId=%d PlayerGUID=%u Param1=%d", sceneId, GetGUID(sceneId, selfId), item.bufid))			
			end
			break
		end
	end
	
	--返回 1 使读条不能进行，无结束时 OnRecycle 回调
    return 1
end

-------------------------------------------------------------------------
--采集点回收
-------------------------------------------------------------------------
function x303104_OnRecycle(sceneId, selfId, targetId)
	return 1
end

-------------------------------------------------------------------------
--采集点结束
-------------------------------------------------------------------------
function x303104_OnProcOver(sceneId,selfId,targetId)
end

-------------------------------------------------------------------------
--采集点检查
-------------------------------------------------------------------------
function x303104_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
end

-------------------------------------------------------------------------
--采集任务
-------------------------------------------------------------------------
function x303104_OnOpenItemBox(sceneId, selfId, targetId, gpType, needItemID)
	return 0
end

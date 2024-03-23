--生长点

x301209_g_GrowpointId = 159 --对应生长点ID
x301209_g_ItemIndex = 13030026 --对应收集物品的ID
x301209_g_MonsterType1              =   653                    --Monster ID1
x301209_g_MonsterType2              =   654                    --Monster ID2
x301209_g_MonsterGroup3              =   
                                       {
                                            {   type=x301209_g_MonsterType1, x=228,  z=46,   ai=5,  aiscript=-1 },
                                             {   type=x301209_g_MonsterType1, x=230,  z=46,   ai=5,  aiscript=-1 },
                                              {   type=x301209_g_MonsterType1, x=229,  z=45,   ai=5,  aiscript=-1 },
                                               {   type=x301209_g_MonsterType1, x=229,  z=47,   ai=5,  aiscript=-1 },
                                                {   type=x301209_g_MonsterType2, x=229,  z=46,   ai=5,  aiscript=-1 },
                                          
                                        }

---------------------------------------------------------------------------------------------------
--创建BOSS
---------------------------------------------------------------------------------------------------
function x301209_CreateMonster3(sceneId)
	local nFindObjid = 0
	local nMonsterCount = GetMonsterCount(sceneId)
	for i=1,nMonsterCount do
    	local objid = GetMonsterObjID(sceneId,i-1)
    	if GetMonsterDataID(sceneId,objid) == x301209_g_MonsterType1 then
    		nFindObjid = nFindObjid+1
    	elseif GetMonsterDataID(sceneId,objid) == x301209_g_MonsterType2 then
    		nFindObjid = nFindObjid+1
    	end
	end
	if nFindObjid == 0 then
		for i, item in x301209_g_MonsterGroup3 do
			CreateMonster(sceneId, item.type, item.x , item.z, item.ai, item.aiscript, -1,-1,21,30000);
		end
	end
end	

--生成函数开始************************************************************************
function 	x301209_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301209_g_GrowpointId, sceneId, 0, x301209_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301209_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox", sceneId, selfId, targetId, x301209_g_GrowpointId, x301209_g_ItemIndex )
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301209_OnRecycle(sceneId,selfId,targetId)
    x301209_CreateMonster3(sceneId)
	CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x301209_g_GrowpointId, x301209_g_ItemIndex )
	return 0
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301209_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



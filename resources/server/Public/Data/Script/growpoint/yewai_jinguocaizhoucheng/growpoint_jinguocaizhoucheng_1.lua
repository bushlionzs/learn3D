--生长点

x301212_g_GrowpointId = 162 --对应生长点ID
x301212_g_ItemIndex = 13030049 --对应收集物品的ID
x301212_g_MonsterType              =  708                    --Monster ID
x301212_g_MonsterGroup3              =   
                                       {
                                            {   type=x301212_g_MonsterType, x=74,  z=219,   ai=5,  aiscript=-1 },
                                             {   type=x301212_g_MonsterType, x=76,  z=219,   ai=5,  aiscript=-1 },
                                              {   type=x301212_g_MonsterType, x=77,  z=221,   ai=5,  aiscript=-1 },
                                               {   type=x301212_g_MonsterType, x=77,  z=219,   ai=5,  aiscript=-1 },
                                                {   type=x301212_g_MonsterType, x=74,  z=221,   ai=5,  aiscript=-1 },
                                                 {   type=x301212_g_MonsterType, x=76,  z=221,   ai=5,  aiscript=-1 },
                                                     {   type=x301212_g_MonsterType, x=73,  z=219,   ai=5,  aiscript=-1 },
                                                      {   type=x301212_g_MonsterType, x=73,  z=221,   ai=5,  aiscript=-1 },
                                                         {   type=x301212_g_MonsterType, x=74,  z=220,   ai=5,  aiscript=-1 },
                                                              {   type=x301212_g_MonsterType, x=75,  z=220,   ai=5,  aiscript=-1 },
                                                                  {   type=x301212_g_MonsterType, x=76,  z=220,   ai=5,  aiscript=-1 },
                                          
                                        }

function x301212_CreateMonster3(sceneId)
	local nFindObjid = 0
	local nMonsterCount = GetMonsterCount(sceneId)
	for i=1,nMonsterCount do
    	local objid = GetMonsterObjID(sceneId,i-1)
    	if GetMonsterDataID(sceneId,objid) == x301212_g_MonsterType then
    		nFindObjid = nFindObjid+1
    	end
	end
	if nFindObjid <= 3 then
		for i, item in x301212_g_MonsterGroup3 do
			CreateMonster(sceneId, item.type, item.x , item.z, item.ai, item.aiscript, -1,-1,21);
		end
	end
end	


--生成函数开始************************************************************************
function 	x301212_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301212_g_GrowpointId, sceneId, 0, x301212_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301212_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox", sceneId, selfId, targetId, x301212_g_GrowpointId, x301212_g_ItemIndex )
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301212_OnRecycle(sceneId,selfId,targetId)
    --x301212_CreateMonster3(sceneId)
 CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x301212_g_GrowpointId, x301212_g_ItemIndex )
 return 0
end

--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301212_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



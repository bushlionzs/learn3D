

x310031_g_ScriptId = 310031

function x310031_KickMonster( sceneId, actId, uTime )
	--print( "delete monster sceneId"..sceneId )

	if sceneId == YX_LOULAN_SCENE_ID1 then
			--local logMsg = "sceneId"..tostring(sceneId).."KickMonster"
			--WriteLog(15,logMsg)
		for i=1, YX_LOULAN_MONSTER_OBJ_NUM1 do
				if YX_LOULAN_MONSTER_OBJ_ID1[i] ~= nil then
					--print( "delete monster"..YX_LOULAN_MONSTER_OBJ_ID1[i] )
					DeleteMonsterEx(sceneId, YX_LOULAN_MONSTER_OBJ_ID1[i])
				end
		end
		YX_LOULAN_MONSTER_OBJ_NUM1 = 0
		YX_LOULAN_MONSTER_OBJ_ID1 = {}		
	elseif sceneId == YX_LOULAN_SCENE_ID2 then
		for i=1, YX_LOULAN_MONSTER_OBJ_NUM2 do
				if YX_LOULAN_MONSTER_OBJ_ID2[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_LOULAN_MONSTER_OBJ_ID2[i])
				end
		end

		YX_LOULAN_MONSTER_OBJ_NUM2 = 0
		YX_LOULAN_MONSTER_OBJ_ID2 = {}		
	elseif sceneId == YX_LOULAN_SCENE_ID3 then
		for i=1, YX_LOULAN_MONSTER_OBJ_NUM3 do
				if YX_LOULAN_MONSTER_OBJ_ID3[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_LOULAN_MONSTER_OBJ_ID3[i])
				end
		end
		YX_LOULAN_MONSTER_OBJ_NUM3 = 0
		YX_LOULAN_MONSTER_OBJ_ID3 ={}	
	elseif sceneId == YX_LOULAN_SCENE_ID4 then
		for i=1, YX_LOULAN_MONSTER_OBJ_NUM4 do
				if YX_LOULAN_MONSTER_OBJ_ID4[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_LOULAN_MONSTER_OBJ_ID4[i])
				end
		end
		YX_LOULAN_MONSTER_OBJ_NUM4 = 0
		YX_LOULAN_MONSTER_OBJ_ID4 ={}	

	elseif sceneId == YX_LOULAN_SCENE_ID5 then
		for i=1, YX_LOULAN_MONSTER_OBJ_NUM5 do
				if YX_LOULAN_MONSTER_OBJ_ID5[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_LOULAN_MONSTER_OBJ_ID5[i])
				end
		end
		YX_LOULAN_MONSTER_OBJ_NUM5 = 0
		YX_LOULAN_MONSTER_OBJ_ID5 ={}	

	elseif sceneId == YX_LOULAN_SCENE_ID6 then
		for i=1, YX_LOULAN_MONSTER_OBJ_NUM6 do
				if YX_LOULAN_MONSTER_OBJ_ID6[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_LOULAN_MONSTER_OBJ_ID6[i])
				end
		end
		YX_LOULAN_MONSTER_OBJ_NUM6 = 0
		YX_LOULAN_MONSTER_OBJ_ID6 ={}	
	elseif sceneId == YX_LOULAN_SCENE_ID7 then
		for i=1, YX_LOULAN_MONSTER_OBJ_NUM7 do
				if YX_LOULAN_MONSTER_OBJ_ID7[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_LOULAN_MONSTER_OBJ_ID7[i])
				end
		end
		YX_LOULAN_MONSTER_OBJ_NUM7 = 0
		YX_LOULAN_MONSTER_OBJ_ID7 ={}	
	elseif sceneId == YX_LOULAN_SCENE_ID8 then
		for i=1, YX_LOULAN_MONSTER_OBJ_NUM8 do
				if YX_LOULAN_MONSTER_OBJ_ID8[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_LOULAN_MONSTER_OBJ_ID8[i])
				end
		end
		YX_LOULAN_MONSTER_OBJ_NUM8 = 0
		YX_LOULAN_MONSTER_OBJ_ID8 ={}		
	elseif sceneId == YX_LOULAN_SCENE_ID9 then
		for i=1, YX_LOULAN_MONSTER_OBJ_NUM9 do
				if YX_LOULAN_MONSTER_OBJ_ID9[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_LOULAN_MONSTER_OBJ_ID9[i])
				end
		end
		YX_LOULAN_MONSTER_OBJ_NUM9 = 0
		YX_LOULAN_MONSTER_OBJ_ID9 ={}		

	elseif sceneId == YX_LAIYIN_SCENE_ID1 then

		for i=1, YX_LAIYIN_MONSTER_OBJ_NUM1 do
				if YX_LAIYIN_MONSTER_OBJ_ID1[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_LAIYIN_MONSTER_OBJ_ID1[i])
				end
		end
		YX_LAIYIN_MONSTER_OBJ_NUM1 = 0
		YX_LAIYIN_MONSTER_OBJ_ID1 = {}
	elseif sceneId == YX_LAIYIN_SCENE_ID2 then
		for i=1, YX_LAIYIN_MONSTER_OBJ_NUM2 do
				if YX_LAIYIN_MONSTER_OBJ_ID2[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_LAIYIN_MONSTER_OBJ_ID2[i])
				end
		end
		YX_LAIYIN_MONSTER_OBJ_NUM2 = 0
	elseif sceneId == YX_LAIYIN_SCENE_ID3 then
		
		for i=1, YX_LAIYIN_MONSTER_OBJ_NUM3 do
				if YX_LAIYIN_MONSTER_OBJ_ID3[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_LAIYIN_MONSTER_OBJ_ID3[i])
				end
		end
		YX_LAIYIN_MONSTER_OBJ_NUM3 = 0
		YX_LAIYIN_MONSTER_OBJ_ID3 = {}
	elseif sceneId == YX_LAIYIN_SCENE_ID4 then
		
		for i=1, YX_LAIYIN_MONSTER_OBJ_NUM4 do
				if YX_LAIYIN_MONSTER_OBJ_ID4[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_LAIYIN_MONSTER_OBJ_ID4[i])
				end
		end
		YX_LAIYIN_MONSTER_OBJ_NUM4 = 0
		YX_LAIYIN_MONSTER_OBJ_ID4 = {}

	elseif sceneId == YX_LAIYIN_SCENE_ID5 then
		for i=1, YX_LAIYIN_MONSTER_OBJ_NUM5 do
				if YX_LAIYIN_MONSTER_OBJ_ID5[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_LAIYIN_MONSTER_OBJ_ID5[i])
				end
		end
		YX_LAIYIN_MONSTER_OBJ_NUM5 = 0
		YX_LAIYIN_MONSTER_OBJ_ID5 ={}	

	elseif sceneId == YX_LAIYIN_SCENE_ID6 then
		for i=1, YX_LAIYIN_MONSTER_OBJ_NUM6 do
				if YX_LAIYIN_MONSTER_OBJ_ID6[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_LAIYIN_MONSTER_OBJ_ID6[i])
				end
		end
		YX_LAIYIN_MONSTER_OBJ_NUM6 = 0
		YX_LAIYIN_MONSTER_OBJ_ID6 ={}	
	elseif sceneId == YX_LAIYIN_SCENE_ID7 then
		for i=1, YX_LAIYIN_MONSTER_OBJ_NUM7 do
				if YX_LAIYIN_MONSTER_OBJ_ID7[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_LAIYIN_MONSTER_OBJ_ID7[i])
				end
		end
		YX_LAIYIN_MONSTER_OBJ_NUM7 = 0
		YX_LAIYIN_MONSTER_OBJ_ID7 ={}	
	elseif sceneId == YX_LAIYIN_SCENE_ID8 then
		for i=1, YX_LAIYIN_MONSTER_OBJ_NUM8 do
				if YX_LAIYIN_MONSTER_OBJ_ID8[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_LAIYIN_MONSTER_OBJ_ID8[i])
				end
		end
		YX_LAIYIN_MONSTER_OBJ_NUM8 = 0
		YX_LAIYIN_MONSTER_OBJ_ID8 ={}
	elseif sceneId == YX_LAIYIN_SCENE_ID9 then
		for i=1, YX_LAIYIN_MONSTER_OBJ_NUM9 do
				if YX_LAIYIN_MONSTER_OBJ_ID9[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_LAIYIN_MONSTER_OBJ_ID9[i])
				end
		end
		YX_LAIYIN_MONSTER_OBJ_NUM9 = 0
		YX_LAIYIN_MONSTER_OBJ_ID9 ={}			
		
	elseif sceneId == YX_KUNLUN_SCENE_ID1 then

		for i=1, YX_KUNLUN_MONSTER_OBJ_NUM1 do
				if YX_KUNLUN_MONSTER_OBJ_ID1[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_KUNLUN_MONSTER_OBJ_ID1[i])
				end
		end
		YX_KUNLUN_MONSTER_OBJ_NUM1 = 0
		YX_KUNLUN_MONSTER_OBJ_ID1 = {}
	elseif sceneId == YX_KUNLUN_SCENE_ID2 then

		for i=1, YX_KUNLUN_MONSTER_OBJ_NUM2 do
				if YX_KUNLUN_MONSTER_OBJ_ID2[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_KUNLUN_MONSTER_OBJ_ID2[i])
				end
		end
		YX_KUNLUN_MONSTER_OBJ_NUM2 = 0
		YX_KUNLUN_MONSTER_OBJ_ID2 = {}
	elseif sceneId == YX_KUNLUN_SCENE_ID3 then

		for i=1, YX_KUNLUN_MONSTER_OBJ_NUM3 do
				if YX_KUNLUN_MONSTER_OBJ_ID3[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_KUNLUN_MONSTER_OBJ_ID3[i])
				end
		end
		YX_KUNLUN_MONSTER_OBJ_NUM3 = 0
		YX_KUNLUN_MONSTER_OBJ_ID3 = {}
	elseif sceneId == YX_KUNLUN_SCENE_ID4 then

		for i=1, YX_KUNLUN_MONSTER_OBJ_NUM4 do
				if YX_KUNLUN_MONSTER_OBJ_ID4[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_KUNLUN_MONSTER_OBJ_ID4[i])
				end
		end
		YX_KUNLUN_MONSTER_OBJ_NUM4 = 0
		YX_KUNLUN_MONSTER_OBJ_ID4 = {}

	elseif sceneId == YX_KUNLUN_SCENE_ID5 then
		for i=1, YX_KUNLUN_MONSTER_OBJ_NUM5 do
				if YX_KUNLUN_MONSTER_OBJ_ID5[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_KUNLUN_MONSTER_OBJ_ID5[i])
				end
		end
		YX_KUNLUN_MONSTER_OBJ_NUM5 = 0
		YX_KUNLUN_MONSTER_OBJ_ID5 ={}	

	elseif sceneId == YX_KUNLUN_SCENE_ID6 then
		for i=1, YX_KUNLUN_MONSTER_OBJ_NUM6 do
				if YX_KUNLUN_MONSTER_OBJ_ID6[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_KUNLUN_MONSTER_OBJ_ID6[i])
				end
		end
		YX_KUNLUN_MONSTER_OBJ_NUM6 = 0
		YX_KUNLUN_MONSTER_OBJ_ID6 ={}	

	elseif sceneId == YX_KUNLUN_SCENE_ID7 then
		for i=1, YX_KUNLUN_MONSTER_OBJ_NUM7 do
				if YX_KUNLUN_MONSTER_OBJ_ID7[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_KUNLUN_MONSTER_OBJ_ID7[i])
				end
		end
		YX_KUNLUN_MONSTER_OBJ_NUM7 = 0
		YX_KUNLUN_MONSTER_OBJ_ID7 ={}
	
	elseif sceneId == YX_KUNLUN_SCENE_ID8 then
		for i=1, YX_KUNLUN_MONSTER_OBJ_NUM8 do
				if YX_KUNLUN_MONSTER_OBJ_ID8[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_KUNLUN_MONSTER_OBJ_ID8[i])
				end
		end
		YX_KUNLUN_MONSTER_OBJ_NUM8 = 0
		YX_KUNLUN_MONSTER_OBJ_ID8 ={}

	elseif sceneId == YX_KUNLUN_SCENE_ID9 then
		for i=1, YX_KUNLUN_MONSTER_OBJ_NUM9 do
				if YX_KUNLUN_MONSTER_OBJ_ID9[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_KUNLUN_MONSTER_OBJ_ID9[i])
				end
		end
		YX_KUNLUN_MONSTER_OBJ_NUM9 = 0
		YX_KUNLUN_MONSTER_OBJ_ID9 ={}		
		
	elseif sceneId == YX_DUNHUANG_SCENE_ID1 then	

		for i=1, YX_DUNHUANG_MONSTER_OBJ_NUM1 do
				if YX_DUNHUANG_MONSTER_OBJ_ID1[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_DUNHUANG_MONSTER_OBJ_ID1[i])
				end
		end
		YX_DUNHUANG_MONSTER_OBJ_NUM1 = 0
		YX_DUNHUANG_MONSTER_OBJ_ID1 = {}
	elseif sceneId == YX_DUNHUANG_SCENE_ID2 then

		for i=1, YX_DUNHUANG_MONSTER_OBJ_NUM2 do
				if YX_DUNHUANG_MONSTER_OBJ_ID2[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_DUNHUANG_MONSTER_OBJ_ID2[i])
				end
		end
		YX_DUNHUANG_MONSTER_OBJ_NUM2 = 0
		YX_DUNHUANG_MONSTER_OBJ_ID2 = {}

	elseif sceneId == YX_DUNHUANG_SCENE_ID3 then

		for i=1, YX_DUNHUANG_MONSTER_OBJ_NUM3 do
				if YX_DUNHUANG_MONSTER_OBJ_ID3[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_DUNHUANG_MONSTER_OBJ_ID3[i])
				end
		end
		YX_DUNHUANG_MONSTER_OBJ_NUM3 =0
		YX_DUNHUANG_MONSTER_OBJ_ID3 = {}
	elseif sceneId == YX_DUNHUANG_SCENE_ID4 then

		for i=1, YX_DUNHUANG_MONSTER_OBJ_NUM4 do
				if YX_DUNHUANG_MONSTER_OBJ_ID4[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_DUNHUANG_MONSTER_OBJ_ID4[i])
				end
		end
		YX_DUNHUANG_MONSTER_OBJ_NUM4 =0
		YX_DUNHUANG_MONSTER_OBJ_ID4 = {}

	elseif sceneId == YX_DUNHUANG_SCENE_ID5 then
		for i=1, YX_DUNHUANG_MONSTER_OBJ_NUM5 do
				if YX_DUNHUANG_MONSTER_OBJ_ID5[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_DUNHUANG_MONSTER_OBJ_ID5[i])
				end
		end
		YX_DUNHUANG_MONSTER_OBJ_NUM5 = 0
		YX_DUNHUANG_MONSTER_OBJ_ID5 ={}	

	elseif sceneId == YX_DUNHUANG_SCENE_ID6 then
		for i=1, YX_DUNHUANG_MONSTER_OBJ_NUM6 do
				if YX_DUNHUANG_MONSTER_OBJ_ID6[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_DUNHUANG_MONSTER_OBJ_ID6[i])
				end
		end
		YX_DUNHUANG_MONSTER_OBJ_NUM6 = 0
		YX_DUNHUANG_MONSTER_OBJ_ID6 ={}	
	elseif sceneId == YX_DUNHUANG_SCENE_ID7 then
		for i=1, YX_DUNHUANG_MONSTER_OBJ_NUM7 do
				if YX_DUNHUANG_MONSTER_OBJ_ID7[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_DUNHUANG_MONSTER_OBJ_ID7[i])
				end
		end
		YX_DUNHUANG_MONSTER_OBJ_NUM7 = 0
		YX_DUNHUANG_MONSTER_OBJ_ID7 ={}	
	elseif sceneId == YX_DUNHUANG_SCENE_ID8 then
		for i=1, YX_DUNHUANG_MONSTER_OBJ_NUM8 do
				if YX_DUNHUANG_MONSTER_OBJ_ID8[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_DUNHUANG_MONSTER_OBJ_ID8[i])
				end
		end
		YX_DUNHUANG_MONSTER_OBJ_NUM8 = 0
		YX_DUNHUANG_MONSTER_OBJ_ID8 ={}	
	elseif sceneId == YX_DUNHUANG_SCENE_ID9 then
		for i=1, YX_DUNHUANG_MONSTER_OBJ_NUM9 do
				if YX_DUNHUANG_MONSTER_OBJ_ID9[i] ~= nil then
					DeleteMonsterEx(sceneId, YX_DUNHUANG_MONSTER_OBJ_ID9[i])
				end
		end
		YX_DUNHUANG_MONSTER_OBJ_NUM9 = 0
		YX_DUNHUANG_MONSTER_OBJ_ID9 ={}	
						
	end

end

function x310031_ProcTiming( sceneId, actId, uTime )

end



x310403_g_ScriptId = 310403

function x310403_KickMonster( sceneId, actId, uTime )
	--print( "delete monster sceneId"..sceneId )

	if sceneId == QT_LOULAN_SCENE_ID then
			--local logMsg = "sceneId"..tostring(sceneId).."KickMonster"
			--WriteLog(15,logMsg)
		for i=1, QT_LOULAN_MONSTER_OBJ_NUM do
				if QT_LOULAN_MONSTER_OBJ_ID[i] ~= nil then
					--print( "delete monster"..QT_LOULAN_MONSTER_OBJ_ID[i] )
					DeleteMonsterEx(sceneId, QT_LOULAN_MONSTER_OBJ_ID[i])
				end
		end
		QT_LOULAN_MONSTER_OBJ_NUM = 0
		QT_LOULAN_MONSTER_OBJ_ID = {}		
	elseif sceneId == QT_LAIYIN_SCENE_ID then

		for i=1, QT_LAIYIN_MONSTER_OBJ_NUM do
				if QT_LAIYIN_MONSTER_OBJ_ID[i] ~= nil then
					DeleteMonsterEx(sceneId, QT_LAIYIN_MONSTER_OBJ_ID[i])
				end
		end
		QT_LAIYIN_MONSTER_OBJ_NUM = 0
		QT_LAIYIN_MONSTER_OBJ_ID = {}
	elseif sceneId == QT_KUNLUN_SCENE_ID then

		for i=1, QT_KUNLUN_MONSTER_OBJ_NUM do
				if QT_KUNLUN_MONSTER_OBJ_ID[i] ~= nil then
					DeleteMonsterEx(sceneId, QT_KUNLUN_MONSTER_OBJ_ID[i])
				end
		end
		QT_KUNLUN_MONSTER_OBJ_NUM = 0
		QT_KUNLUN_MONSTER_OBJ_ID = {}
	elseif sceneId == QT_DUNHUANG_SCENE_ID then

		for i=1, QT_DUNHUANG_MONSTER_OBJ_NUM do
				if QT_DUNHUANG_MONSTER_OBJ_ID[i] ~= nil then
					DeleteMonsterEx(sceneId, QT_DUNHUANG_MONSTER_OBJ_ID[i])
				end
		end
		QT_DUNHUANG_MONSTER_OBJ_NUM = 0
		QT_DUNHUANG_MONSTER_OBJ_ID = {}
	end

end

function x310403_ProcTiming( sceneId, actId, uTime )

end

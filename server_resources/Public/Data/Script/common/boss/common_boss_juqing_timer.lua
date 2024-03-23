--½Å±¾ºÅ
x305000_g_ScriptId = 305000
x305000_g_FilterScene = {
							54,56,57,58,59,60,61,62,
							154,156,157,158,159,160,161,162,
							254,256,257,258,259,260,261,262,
							354,356,357,358,359,360,361,362,
						}

function x305000_OnTimerDoingStart( SceneId, actId, Param1, Param2, Param3, Param4, Param5 )

	local bFind = 0
	for i,item in x305000_g_FilterScene do
		if item == SceneId then
			bFind = 1
			break
		end
	end
	
	if bFind == 0 then
		return
	end

	local nIndexFrom = GetFubenDataPosByScriptID( x305000_g_ScriptId )
	local nDataCount = GetFubenDataCountByScriptID( x305000_g_ScriptId )
	for i = 0,nDataCount-1 do
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x305000_g_ScriptId,nIndexFrom,i)
		if idScript == x305000_g_ScriptId and monsterFlag == 0 and SceneId == flag then
			for j=0,count -1 do
				CreateMonster( SceneId, type, x, z, ai, aiscript, -1, -1, 21, 30*60*1000)
			end
		end
	end
end
--创建海贼

x300560_g_MissionName="定点创建海贼"


--脚本号
x300560_g_ScriptId = 300560


x300560_g_SceneMonsterPosCount = 40
x300560_g_SceneMonsterCount = 30

x300560_g_SceneMonsterType = 3060
x300560_g_KillScriptId = 300561

x300560_g_ScenePos =    {
		{x=	92.75	,	z=	122.75	},
		{x=	98.5	,	z=	124.25	},
		{x=	104.75	,	z=	125.25	},
		{x=	109.25	,	z=	130	},
		{x=	111.5	,	z=	137	},
		{x=	111.5	,	z=	143.75	},
		{x=	125.75	,	z=	94.5	},
		{x=	123.5	,	z=	100.25	},
		{x=	124.5	,	z=	106.5	},
		{x=	130	,	z=	113.75	},
		{x=	137.25	,	z=	114	},
		{x=	144.75	,	z=	115.25	},
		{x=	111	,	z=	117.75	},
		{x=	115	,	z=	113.75	},
		{x=	116.5	,	z=	123.5	},
		{x=	122.5	,	z=	119.25	},
		{x=	132	,	z=	147.5	},
		{x=	139.75	,	z=	144.75	},
		{x=	146	,	z=	140	},
		{x=	140.75	,	z=	83	},
		{x=	147	,	z=	85.75	},
		{x=	151	,	z=	91.75	},
		{x=	104.25	,	z=	96.5	},
		{x=	106.25	,	z=	103	},
		{x=	103.5	,	z=	108.75	},
		{x=	79	,	z=	136	},
		{x=	83.5	,	z=	142.75	},
		{x=	90	,	z=	145.5	},
		{x=	101	,	z=	156.75	},
		{x=	111.75	,	z=	153.5	}

}


function x300560_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4,Param5 )

    if sceneId == 19 then

		CallScriptFunction(x300560_g_KillScriptId, "clearKillNum",  sceneId, -1, -1);
	
        for i=1,x300560_g_SceneMonsterCount do


            --PrintStr("create: posindex="..posindex.." i="..i.." sceneId="..sceneId)
            --print("create: posindex="..posindex.." i="..i.." sceneId="..sceneId)

            -- 开始创建怪物
            local pos = x300560_g_ScenePos[i]
            local monsterObj, monsterGuid = CreateMonster(sceneId,x300560_g_SceneMonsterType, pos.x,pos.z, 1,-1, x300560_g_KillScriptId,-1,21,1800*1000);
	    			HZ_MONSTER_OBJ[i] = monsterObj
        end

   end

end


--活动的Tick
function x300560_ProcTiming( sceneId, actId, uTime )
end
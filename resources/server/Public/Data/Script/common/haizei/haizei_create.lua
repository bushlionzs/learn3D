--创建海贼

x300550_g_MissionName="定点创建海贼"


--脚本号
x300550_g_ScriptId = 300550


x300550_g_SceneMonsterPosCount = 40
x300550_g_SceneMonsterCount = 30

x300550_g_SceneMonsterType = 3060
x300550_g_KillScriptId = 300551

x300550_g_ScenePos =    {
		{x=	73.950119	,	z=	289.453552	},
		{x=	79.042709	,	z=	295.240601	},
		{x=	82.283447	,	z=	299.407257	},
		{x=	83.440857	,	z=	303.342468	},
		{x=	85.987152	,	z=	310.05542	},
		{x=	87.607521	,	z=	317.694305	},
		{x=	88.996414	,	z=	322.55542	},
		{x=	92.005669	,	z=	306.351715	},
		{x=	93.394562	,	z=	311.444305	},
		{x=	96.6353	,	z=	315.842468	},
		{x=	76.033447	,	z=	301.953552	},
		{x=	78.57975	,	z=	307.740601	},
		{x=	80.431595	,	z=	313.064667	},
		{x=	81.126045	,	z=	317.925781	},
		{x=	81.820488	,	z=	322.092468	},
		{x=	80.431595	,	z=	327.185059	},
		{x=	78.116783	,	z=	332.046143	},
		{x=	71.403824	,	z=	329.036896	},
		{x=	73.950119	,	z=	325.101685	},
		{x=	71.866783	,	z=	319.314697	},
		{x=	74.876045	,	z=	314.222076	},
		{x=	74.644562	,	z=	307.740601	},
		{x=	69.089005	,	z=	301.722076	},
		{x=	91.079742	,	z=	301.027649	},
		{x=	96.6353	,	z=	307.277649	},
		{x=	100.570488	,	z=	312.601715	},
		{x=	103.579742	,	z=	316.768372	},
		{x=	104.274193	,	z=	323.249878	},
		{x=	98.950119	,	z=	327.185059	},
		{x=	92.005669	,	z=	326.953552	}

}


function x300550_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4,Param5 )

    if sceneId == 50 or sceneId == 150 or sceneId == 250 or sceneId == 350 then

		CallScriptFunction(x300550_g_KillScriptId, "clearKillNum",  sceneId, -1, -1);
	
        for i=1,x300550_g_SceneMonsterCount do


            --PrintStr("create: posindex="..posindex.." i="..i.." sceneId="..sceneId)
            --print("create: posindex="..posindex.." i="..i.." sceneId="..sceneId)

            -- 开始创建怪物
            local pos = x300550_g_ScenePos[i]
            local monsterObj, monsterGuid = CreateMonster(sceneId,x300550_g_SceneMonsterType, pos.x,pos.z, 1,-1, x300550_g_KillScriptId,-1,21,1800*1000);
	    			HZ_MONSTER_OBJ[i] = monsterObj
        end

   end

end


--活动的Tick
function x300550_ProcTiming( sceneId, actId, uTime )
end
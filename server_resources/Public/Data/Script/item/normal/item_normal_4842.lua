--注意：

--物品技能的逻辑只能使用基础技能和脚本来实现

--脚本:

--以下是脚本样例:


--4842.lua
------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号
x404842_g_scriptId = 404842 --临时写这个,真正用的时候一定要改.

--需要的等级

--效果的ID
x404842_g_Impact1 = 8001 --临时写这个
x404842_g_Impact2 = -1 --不用

x404842_g_MapList = { 
						{itemId=12050201, prescrId=142, abilityId =1  },
						{itemId=12050202, prescrId=212, abilityId =1  },
						{itemId=12050203, prescrId=302, abilityId =1  },
						{itemId=12050204, prescrId=422, abilityId =1  },
						{itemId=12050205, prescrId=552, abilityId =1  },
						{itemId=12050206, prescrId=602, abilityId =1  },
						{itemId=12050207, prescrId=712, abilityId =1  },
						{itemId=12050208, prescrId=802, abilityId =1  },
						{itemId=12050209, prescrId=922, abilityId =1  },
						{itemId=12050210, prescrId=1042, abilityId =1  },
						{itemId=12050211, prescrId=141, abilityId =1  },
						{itemId=12050212, prescrId=211, abilityId =1  },
						{itemId=12050213, prescrId=301, abilityId =1  },
						{itemId=12050214, prescrId=421, abilityId =1  },
						{itemId=12050215, prescrId=551, abilityId =1  },
						{itemId=12050216, prescrId=31, abilityId =1  },
						{itemId=12050217, prescrId=32, abilityId =1  },
						{itemId=12050218, prescrId=33, abilityId =1  },
						{itemId=12050219, prescrId=34, abilityId =1  },
						{itemId=12050220, prescrId=35, abilityId =1  },
						{itemId=12050221, prescrId=41, abilityId =1  },
						{itemId=12050222, prescrId=42, abilityId =1  },
						{itemId=12050223, prescrId=43, abilityId =1  },
						{itemId=12050224, prescrId=44, abilityId =1  },
						{itemId=12050225, prescrId=45, abilityId =1  },
						{itemId=12050300, prescrId=3004, abilityId =1  },
						{itemId=12050226, prescrId=51, abilityId =1  },
						{itemId=12050227, prescrId=3500, abilityId =1  },
						{itemId=12050228, prescrId=3600, abilityId =1  },
						{itemId=12050229, prescrId=3610, abilityId =1  },
						{itemId=12050230, prescrId=3620, abilityId =1  },
						{itemId=12050231,prescrId=2301, abilityId =1},
						{itemId=12050232,prescrId=2311, abilityId =1},
						{itemId=12050233,prescrId=2321, abilityId =1},
						{itemId=12050234,prescrId=2331, abilityId =1},
						{itemId=12050235,prescrId=2341, abilityId =1},
						{itemId=12050236,prescrId=2501, abilityId =1},
						{itemId=12050237,prescrId=2511, abilityId =1},
						{itemId=12050238,prescrId=2521, abilityId =1},
						{itemId=12050239,prescrId=2531, abilityId =1},
						{itemId=12050240,prescrId=2541, abilityId =1},
						{itemId=12050241,prescrId=3630, abilityId =1},
						{itemId=12050242,prescrId=3801, abilityId =1},
						{itemId=12050243,prescrId=2701, abilityId =1},
						{itemId=12050244,prescrId=2711, abilityId =1},
						{itemId=12050245,prescrId=2721, abilityId =1},
						{itemId=12050246,prescrId=2731, abilityId =1},
						{itemId=12050247,prescrId=3901, abilityId =1},
						{itemId=12050248,prescrId=3911, abilityId =1},
						{itemId=12050249,prescrId=3921, abilityId =1},
						{itemId=12050250,prescrId=3931, abilityId =1},
						{itemId=12050251,prescrId=3941, abilityId =1},
						{itemId=12050252,prescrId=3701, abilityId =1},
                        {itemId=12050253,prescrId=3711, abilityId =1},
                        {itemId=12050254,prescrId=3721, abilityId =1},
                        {itemId=12050255,prescrId=3731, abilityId =1},
                        {itemId=12050256,prescrId=3741, abilityId =1},
                        {itemId=12050257,prescrId=4071, abilityId =1},
                        {itemId=12050258,prescrId=4081, abilityId =1},
                        {itemId=12050259,prescrId=4091, abilityId =1},
                        {itemId=12050260,prescrId=4061, abilityId =1},
                        {itemId=12050261,prescrId=5081, abilityId =1},
						{itemId=12050262,prescrId=5091, abilityId =1},
						{itemId=12050263,prescrId=5101, abilityId =1},
						{itemId=12050264,prescrId=5111, abilityId =1},

					} 
            
--**********************************
--事件交互入口
--**********************************
function x404842_ProcEventEntry( sceneId, selfId, bagIndex )
-- 不需要这个接口，但要保留空函数
            
	local itemInBag = GetItemIDByIndexInBag(sceneId, selfId, bagIndex)
	
	for i, item in x404842_g_MapList do
		if (item.itemId == itemInBag) then
			if (1 == CreateHorseToPlayer( sceneId, selfId, item.prescrId, bagIndex, -1 )) then
				Msg2Player(sceneId, selfId, "您获得了新的骑乘", 8, 3)
				Msg2Player(sceneId, selfId, "您获得了新的骑乘", 8, 2)
			end
			return
		end
	end

end

--**********************************
--这个物品的使用过程是否类似于技能：
--系统会在执行开始时检测这个函数的返回值，如果返回失败则忽略后面的类似技能的执行。
--返回1：技能类似的物品，可以继续类似技能的执行；返回0：忽略后面的操作。
--**********************************
function x404842_IsSkillLikeScript( sceneId, selfId)

	return 0; --这个脚本需要动作支持

end


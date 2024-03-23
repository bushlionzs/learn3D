--MisDescBegin

x300330_g_ScriptId 					= 	300330                  --脚本ID
x300330_g_MissionId 				= 	8050                    --任务ID

x300330_g_MissionKind 				= 	1                       --任务类型
x300330_g_LevelLess					= 	40                      --场景开放等级  <=0 表示不限制

x300330_g_MissionName				= 	"【个人】藏宝图的秘密"                                        --任务名称(512)
x300330_g_MissionTarget				= 	"  去#aB#h00CCFF{goto_%d,%d,%d}%s(%d,%d)#aE处使用铁铲挖掘宝藏"      --任务目标
x300330_g_MissionInfo				= 	"通过阅读这张神龙藏宝图，您发现了宝藏的所在。去#aB#h00CCFF{goto_%d,%d,%d}%s(%d,%d)#aE处去挖掘宝藏吧。\n\t注意：当你有#G江湖请柬#W状态时，有可能会挖到现银奖励，否则，只能挖到银卡奖励。"            --任务信息
x300330_g_ContinueInfo				= 	""  --任务继续信息
x300330_g_MissionCompleted			= 	"\t看来您已经得到@item_12030107,并初步了解藏宝图的秘密了吧？现在我给您一条线索，传说按照这条线索追查下去有可能得到天龙的宝藏！天龙的魂魄有可能栖息在地下粮仓，粮仓里深处的五个妖孽趁天龙魂魄虚弱的时候得到了它。打败那些妖孽就有可能得到@item_12030108。"  --任务完成信息
x300330_g_MissionHelp				=	"去杂货商人处买一个铁铲，然后去宝藏所在地使用"          --任务提示信息
-- 任务放弃提示信息
x300330_g_strMissionAbandon         = "您放弃了任务：【个人】藏宝图的秘密"

--目标
x300330_g_ExtTarget					=	{ {type=20,n=1,target="去杂货商人处买一把铁铲，然后去宝藏所在地使用。"} }


--奖励
x300330_g_ExpBonus					= 	0                    	--奖励：经验 （数值填0，字符串为空，表示没有该项奖励）
x300330_g_BonusItem					=	{}	--奖励：物品

x300330_g_BonusMoney1               = 	0  --任务奖励绑定银币
x300330_g_BonusMoney2               =   0  --任务奖励非绑定银币
x300330_g_BonusMoney3               =   0  --任务奖励绑定金币
x300330_g_BonusMoney4               =   0  --任务奖励朝廷声望
x300330_g_BonusMoney5               =   0  --任务奖励江湖声望
x300330_g_BonusMoney6               =   0  --任务奖励荣誉

x300330_g_BonusChoiceItem           =   {}


--MisDescEnd

--任务目标顺序
x300330_MP_TARGET1					= 1
x300330_MP_TARGET2					= 2
x300330_MP_TARGET3					= 3
x300330_MP_TARGET4					= 4 -- 挖掘目标场景
x300330_MP_ISCOMPLETE				= 7	--代表完成 0未完成， 1完成

x300330_PREVIOUS_QUESTID			= -1		--前一个任务ID
x300330_NEXT_QUESTID				= 7552		--后一个任务ID
x300330_NEXT_QUESTSCRIPTID			= 300754	--后一个任务ID
x300330_QUEST_HUANSHU				= 0			--当前任务的环数

-- 挖宝点列表，使用藏宝图时从中随机抽取一个
x300330_g_MissionTargetTable0        = {
                                        { mapId = 0, mapName = "王国", posX = 162, posZ = 238 }, 
                                        { mapId = 0, mapName = "王国", posX = 161, posZ = 221 }, 
                                        { mapId = 0, mapName = "王国", posX = 163, posZ = 224 },  
                                        { mapId = 0, mapName = "王国", posX = 92, posZ = 238 }, 
                                        { mapId = 0, mapName = "王国", posX = 96, posZ = 223 }, 
                                        { mapId = 0, mapName = "王国", posX = 159, posZ = 193 }, 
                                        { mapId = 0, mapName = "王国", posX = 209, posZ = 166 }, 
                                        { mapId = 0, mapName = "王国", posX = 208, posZ = 199 }, 
                                        { mapId = 0, mapName = "王国", posX = 170, posZ = 114 }, 
                                        { mapId = 0, mapName = "王国", posX = 167, posZ = 162 }, 
                                        { mapId = 0, mapName = "王国", posX = 170, posZ = 112 }, 
                                        { mapId = 0, mapName = "王国", posX = 167, posZ = 198 }, 
                                        { mapId = 0, mapName = "王国", posX = 210, posZ = 72 }, 
                                        { mapId = 0, mapName = "王国", posX = 202, posZ = 77 }, 
                                        { mapId = 0, mapName = "王国", posX = 210, posZ = 61 }, 
                                        { mapId = 0, mapName = "王国", posX = 171, posZ = 69  }, 
                                        { mapId = 0, mapName = "王国", posX = 171, posZ = 78 }, 
                                        { mapId = 0, mapName = "王国", posX = 87 , posZ = 76 }, 
                                        { mapId = 0, mapName = "王国", posX = 91, posZ = 59 }, 
                                        { mapId = 0, mapName = "王国", posX = 77, posZ = 71 }, 
                                        { mapId = 0, mapName = "王国", posX = 8, posZ = 149 }, 
                                        { mapId = 0, mapName = "王国", posX = 31, posZ = 145 }, 
                                        { mapId = 0, mapName = "王国", posX = 57 , posZ = 90 }, 
                                        { mapId = 0, mapName = "王国", posX = 249 , posZ = 87 }, 
                                        { mapId = 0, mapName = "王国", posX = 224 , posZ = 146 }, 
                                        { mapId = 0, mapName = "王国", posX = 224 , posZ = 137 }, 
                                        { mapId = 0, mapName = "王国", posX = 250 , posZ = 149 }, 
                                        { mapId = 0, mapName = "王国", posX = 208 , posZ = 191 }, 
                                        { mapId = 0, mapName = "王国", posX = 168 , posZ = 198 }, 
                                        { mapId = 0, mapName = "王国", posX = 90 , posZ = 194 }, 
                                        { mapId = 0, mapName = "王国", posX = 80 , posZ = 203 }, 
                                        { mapId = 0, mapName = "王国", posX = 50 , posZ = 167 }, 
                                        { mapId = 0, mapName = "王国", posX = 20 , posZ = 150 }, 
                                        { mapId = 0, mapName = "王国", posX = 30 , posZ = 99 }, 
                                        { mapId = 0, mapName = "王国", posX = 31 , posZ = 89 }, 
                                        { mapId = 0, mapName = "王国", posX = 8 , posZ = 131 }, 
                                        { mapId = 0, mapName = "王国", posX = 31 , posZ = 137 }, 
                                        { mapId = 0, mapName = "王国", posX = 6 , posZ = 104 }, 
                                        { mapId = 0, mapName = "王国", posX = 113 , posZ = 92 }, 
                                        { mapId = 0, mapName = "王国", posX = 141 , posZ = 92 }, 
                                        { mapId = 0, mapName = "王国", posX = 163 , posZ = 91 }, 
                                        { mapId = 0, mapName = "王国", posX = 178 , posZ = 56 }, 
                                        { mapId = 0, mapName = "王国", posX = 192 , posZ = 54 }, 
                                        { mapId = 0, mapName = "王国", posX = 206 , posZ = 46 }, 
                                        { mapId = 0, mapName = "王国", posX = 207 , posZ = 41 }, 
                                        { mapId = 0, mapName = "王国", posX = 200 , posZ = 47 }, 
                                        { mapId = 0, mapName = "王国", posX = 205 , posZ = 24 }, 
                                        { mapId = 0, mapName = "王国", posX = 197 , posZ = 23 }, 
                                        { mapId = 0, mapName = "王国", posX = 206 , posZ = 27 }, 
                                        { mapId = 0, mapName = "王国", posX = 203 , posZ = 32 }, 
                                        { mapId = 1, mapName = "边塞", posX = 25, posZ = 80 }, 
                                        { mapId = 1, mapName = "边塞", posX = 33, posZ = 60 }, 
                                        { mapId = 1, mapName = "边塞", posX = 37, posZ = 66 },  
                                        { mapId = 1, mapName = "边塞", posX = 70, posZ = 78 }, 
                                        { mapId = 1, mapName = "边塞", posX = 75, posZ = 76 }, 
                                        { mapId = 1, mapName = "边塞", posX = 21, posZ = 30 }, 
                                        { mapId = 1, mapName = "边塞", posX = 140, posZ = 23 }, 
                                        { mapId = 1, mapName = "边塞", posX = 163, posZ = 16 }, 
                                        { mapId = 1, mapName = "边塞", posX = 171, posZ = 24 }, 
                                        { mapId = 1, mapName = "边塞", posX = 211, posZ = 47 }, 
                                        { mapId = 1, mapName = "边塞", posX = 212, posZ = 71 }, 
                                        { mapId = 1, mapName = "边塞", posX = 199, posZ = 95 }, 
                                        { mapId = 1, mapName = "边塞", posX = 160, posZ = 113 }, 
                                        { mapId = 1, mapName = "边塞", posX = 188, posZ = 92 }, 
                                        { mapId = 1, mapName = "边塞", posX = 163, posZ = 78 }, 
                                        { mapId = 1, mapName = "边塞", posX = 170, posZ = 70  }, 
                                        { mapId = 1, mapName = "边塞", posX = 166, posZ = 88 }, 
                                        { mapId = 1, mapName = "边塞", posX = 169 , posZ = 101 }, 
                                        { mapId = 1, mapName = "边塞", posX = 177, posZ = 157 }, 
                                        { mapId = 1, mapName = "边塞", posX = 178, posZ = 143 }, 
                                        { mapId = 1, mapName = "边塞", posX = 216, posZ = 127 }, 
                                        { mapId = 1, mapName = "边塞", posX = 227, posZ = 136 }, 
                                        { mapId = 1, mapName = "边塞", posX = 222 , posZ = 149 }, 
                                        { mapId = 1, mapName = "边塞", posX = 211 , posZ = 144 }, 
                                        { mapId = 1, mapName = "边塞", posX = 186 , posZ = 164 }, 
                                        { mapId = 1, mapName = "边塞", posX = 204 , posZ = 214 }, 
                                        { mapId = 1, mapName = "边塞", posX = 217 , posZ = 204 }, 
                                        { mapId = 1, mapName = "边塞", posX = 223 , posZ = 233 }, 
                                        { mapId = 1, mapName = "边塞", posX = 218 , posZ = 222 }, 
                                        { mapId = 1, mapName = "边塞", posX = 130 , posZ = 220 }, 
                                        { mapId = 1, mapName = "边塞", posX = 98 , posZ = 218 }, 
                                        { mapId = 1, mapName = "边塞", posX = 56 , posZ = 228 }, 
                                        { mapId = 1, mapName = "边塞", posX = 44 , posZ = 226 }, 
                                        { mapId = 1, mapName = "边塞", posX = 39 , posZ = 217 }, 
                                        { mapId = 1, mapName = "边塞", posX = 51 , posZ = 189 }, 
                                        { mapId = 1, mapName = "边塞", posX = 62 , posZ = 188 }, 
                                        { mapId = 1, mapName = "边塞", posX = 86 , posZ = 168 }, 
                                        { mapId = 1, mapName = "边塞", posX = 90 , posZ = 90 }, 
                                        { mapId = 1, mapName = "边塞", posX = 75 , posZ = 90 }, 
                                        { mapId = 1, mapName = "边塞", posX = 45 , posZ = 58 }, 
                                        { mapId = 1, mapName = "边塞", posX = 38 , posZ = 46 }, 
                                        { mapId = 1, mapName = "边塞", posX = 100 , posZ = 40 }, 
                                        { mapId = 1, mapName = "边塞", posX = 121 , posZ = 27 }, 
                                        { mapId = 1, mapName = "边塞", posX = 143 , posZ = 25 }, 
                                        { mapId = 1, mapName = "边塞", posX = 149 , posZ = 29 }, 
                                        { mapId = 1, mapName = "边塞", posX = 162 , posZ = 19 }, 
                                        { mapId = 1, mapName = "边塞", posX = 238 , posZ = 36 }, 
                                        { mapId = 1, mapName = "边塞", posX = 221 , posZ = 47 }, 
                                        { mapId = 1, mapName = "边塞", posX = 189 , posZ = 55 }, 
                                        { mapId = 1, mapName = "边塞", posX = 175 , posZ = 74 },
                                        { mapId = 2, mapName = "大都", posX = 76, posZ = 22 }, 
                                        { mapId = 2, mapName = "大都", posX = 55, posZ = 183 }, 
                                        { mapId = 2, mapName = "大都", posX = 217, posZ = 217 }, 
                                        { mapId = 2, mapName = "大都", posX = 173, posZ = 39 }, 
                                        { mapId = 2, mapName = "大都", posX = 64, posZ = 219 }, 
                                        { mapId = 2, mapName = "大都", posX = 226, posZ = 85  }, 
                                        { mapId = 2, mapName = "大都", posX = 185, posZ = 224 }, 
                                        { mapId = 2, mapName = "大都", posX = 182, posZ = 23 }, 
                                        { mapId = 2, mapName = "大都", posX = 191, posZ = 69 }, 
                                        { mapId = 2, mapName = "大都", posX = 188, posZ = 85 }, 
                                        { mapId = 2, mapName = "大都", posX = 26, posZ = 178 }, 
                                        { mapId = 2, mapName = "大都", posX = 70, posZ = 48 }, 
                                        { mapId = 2, mapName = "大都", posX = 28, posZ = 69 }, 
                                        { mapId = 2, mapName = "大都", posX = 63, posZ = 110 }, 
                                        { mapId = 2, mapName = "大都", posX = 25, posZ = 206 }, 
                                        { mapId = 2, mapName = "大都", posX = 57 , posZ = 206 }, 
                                        { mapId = 2, mapName = "大都", posX = 53 , posZ = 177  }, 
                                        { mapId = 2, mapName = "大都", posX = 73 , posZ = 84  }, 
                                        { mapId = 2, mapName = "大都", posX = 177, posZ = 25  }, 
                                        { mapId = 2, mapName = "大都", posX = 224, posZ = 61  },                                         
                                        { mapId = 3, mapName = "威海港", posX = 141, posZ = 185  }, 
                                        { mapId = 3, mapName = "威海港", posX = 106, posZ = 185  }, 
                                        { mapId = 3, mapName = "威海港", posX = 67,  posZ = 148  }, 
                                        { mapId = 3, mapName = "威海港", posX = 129, posZ = 65  }, 
                                        { mapId = 3, mapName = "威海港", posX = 119, posZ = 90  }, 
                                        { mapId = 3, mapName = "威海港", posX = 130,  posZ = 91 }, 
                                        { mapId = 3, mapName = "威海港", posX = 89, posZ = 135  }, 
                                        { mapId = 3, mapName = "威海港", posX = 121, posZ = 134  }, 
                                        { mapId = 3, mapName = "威海港", posX = 195, posZ = 79 }, 
                                        { mapId = 3, mapName = "威海港", posX = 111,  posZ = 102 }, 
                                        { mapId = 3, mapName = "威海港", posX = 111,  posZ = 124 },
                                        { mapId = 3, mapName = "威海港", posX = 89,  posZ = 156 },
                                        { mapId = 3, mapName = "威海港", posX = 92,  posZ = 166 },
                                        { mapId = 3, mapName = "威海港", posX = 110,  posZ = 148 },
                                        { mapId = 3, mapName = "威海港", posX = 103,  posZ = 162 },
                                        { mapId = 3, mapName = "威海港", posX = 87,  posZ = 168 },
                                        { mapId = 3, mapName = "威海港", posX = 33,  posZ = 102 },
                                        { mapId = 3, mapName = "威海港", posX = 43,  posZ = 119 },
                                        { mapId = 3, mapName = "威海港", posX = 62,  posZ = 140 },
                                        { mapId = 3, mapName = "威海港", posX = 64,  posZ = 176 },
                                       	{ mapId = 36, mapName = "大都南", posX = 24, posZ = 102 }, 
                                        { mapId = 36, mapName = "大都南", posX = 24, posZ = 101 }, 
                                        { mapId = 36, mapName = "大都南", posX = 32, posZ = 115 }, 
                                        { mapId = 36, mapName = "大都南", posX = 22, posZ = 108 }, 
                                        { mapId = 36, mapName = "大都南", posX = 20, posZ = 132 }, 
                                        { mapId = 36, mapName = "大都南", posX = 31, posZ = 157  }, 
                                        { mapId = 36, mapName = "大都南", posX = 59 , posZ = 158 }, 
                                        { mapId = 36, mapName = "大都南", posX = 72, posZ = 159 }, 
                                        { mapId = 36, mapName = "大都南", posX = 54, posZ = 140 }, 
                                        { mapId = 36, mapName = "大都南", posX = 100, posZ = 151  }, 
                                        { mapId = 36, mapName = "大都南", posX = 140, posZ = 165 }, 
                                        { mapId = 36, mapName = "大都南", posX = 158, posZ = 160 }, 
                                        { mapId = 36, mapName = "大都南", posX = 174, posZ = 168 }, 
                                        { mapId = 36, mapName = "大都南", posX = 209, posZ = 156 }, 
                                        { mapId = 36, mapName = "大都南", posX = 234, posZ = 161 }, 
                                        { mapId = 36, mapName = "大都南", posX = 238 , posZ = 213 }, 
                                        { mapId = 36, mapName = "大都南", posX = 158 , posZ = 235  }, 
                                        { mapId = 36, mapName = "大都南", posX = 202 , posZ = 225  }, 
                                        { mapId = 36, mapName = "大都南", posX = 150, posZ = 235  },       
                                        { mapId = 36, mapName = "大都南", posX = 121, posZ = 230  },                                                                                
                                        { mapId = 37, mapName = "大都东", posX = 64, posZ = 49  },       
                                        { mapId = 37, mapName = "大都东", posX = 86, posZ = 118  }, 
                                        { mapId = 37, mapName = "大都东", posX = 87, posZ = 168  },       
                                        { mapId = 37, mapName = "大都东", posX = 120, posZ = 158  },
                                        { mapId = 37, mapName = "大都东", posX = 161, posZ = 198  },       
                                        { mapId = 37, mapName = "大都东", posX = 139, posZ = 240 },
                                        { mapId = 37, mapName = "大都东", posX = 116, posZ = 241  },       
                                        { mapId = 37, mapName = "大都东", posX = 106, posZ = 212  },
                                        { mapId = 37, mapName = "大都东", posX = 90, posZ = 210  },       
                                        { mapId = 37, mapName = "大都东", posX = 92, posZ = 244  },
                                        { mapId = 37, mapName = "大都东", posX = 108, posZ = 242  },       
                                        { mapId = 37, mapName = "大都东", posX = 104, posZ = 231  }, 
                                        { mapId = 37, mapName = "大都东", posX = 155, posZ = 165  },       
                                        { mapId = 37, mapName = "大都东", posX = 215, posZ = 224  },
                                        { mapId = 37, mapName = "大都东", posX = 221, posZ = 124  },       
                                        { mapId = 37, mapName = "大都东", posX = 190, posZ = 81  },
                                        { mapId = 37, mapName = "大都东", posX = 169, posZ = 135  },       
                                        { mapId = 37, mapName = "大都东", posX = 149, posZ = 95  },
                                        { mapId = 37, mapName = "大都东", posX = 130, posZ = 90  },       
                                        { mapId = 37, mapName = "大都东", posX = 121, posZ = 158  },                                        
                                        { mapId = 38, mapName = "大都西", posX = 137, posZ = 86  },       
                                        { mapId = 38, mapName = "大都西", posX = 135, posZ = 97  }, 
                                        { mapId = 38, mapName = "大都西", posX = 133, posZ = 108  },       
                                        { mapId = 38, mapName = "大都西", posX = 166, posZ = 111  },
                                        { mapId = 38, mapName = "大都西", posX = 182, posZ = 130  },       
                                        { mapId = 38, mapName = "大都西", posX = 234, posZ = 103  },
                                        { mapId = 38, mapName = "大都西", posX = 213, posZ = 179  },       
                                        { mapId = 38, mapName = "大都西", posX = 185, posZ = 167  },
                                        { mapId = 38, mapName = "大都西", posX = 147, posZ = 195  },       
                                        { mapId = 38, mapName = "大都西", posX = 160, posZ = 223  },
                                        { mapId = 38, mapName = "大都西", posX = 131, posZ = 222  },       
                                        { mapId = 38, mapName = "大都西", posX = 72, posZ = 161  }, 
                                        { mapId = 38, mapName = "大都西", posX = 33, posZ = 192  },       
                                        { mapId = 38, mapName = "大都西", posX = 89, posZ = 232  },
                                        { mapId = 38, mapName = "大都西", posX = 67, posZ = 135  },       
                                        { mapId = 38, mapName = "大都西", posX = 43, posZ = 86  },
                                        { mapId = 38, mapName = "大都西", posX = 87, posZ = 37  },       
                                        { mapId = 38, mapName = "大都西", posX = 134, posZ = 41  },
                                        { mapId = 38, mapName = "大都西", posX = 161, posZ = 74  },       
                                        { mapId = 38, mapName = "大都西", posX = 134, posZ = 107  },
                                                                                
}                                                                                        

x300330_g_MissionTargetTable1        = {
                                        { mapId = 0, mapName = "王国", posX = 51, posZ = 83 }, 
                                        { mapId = 0, mapName = "王国", posX = 50, posZ = 107 }, 
                                        { mapId = 0, mapName = "王国", posX = 25, posZ = 92 },  
                                        { mapId = 0, mapName = "王国", posX = 6, posZ = 105 }, 
                                        { mapId = 0, mapName = "王国", posX = 7, posZ = 149 }, 
                                        { mapId = 0, mapName = "王国", posX = 28, posZ = 142 }, 
                                        { mapId = 0, mapName = "王国", posX = 31, posZ = 137 }, 
                                        { mapId = 0, mapName = "王国", posX = 47, posZ = 141 }, 
                                        { mapId = 0, mapName = "王国", posX = 87, posZ = 148 }, 
                                        { mapId = 0, mapName = "王国", posX = 101, posZ = 165 }, 
                                        { mapId = 0, mapName = "王国", posX = 101, posZ = 185 }, 
                                        { mapId = 0, mapName = "王国", posX = 62, posZ = 148 }, 
                                        { mapId = 0, mapName = "王国", posX = 51, posZ = 68 }, 
                                        { mapId = 0, mapName = "王国", posX = 78, posZ = 71 }, 
                                        { mapId = 0, mapName = "王国", posX = 100, posZ = 71 }, 
                                        { mapId = 0, mapName = "王国", posX = 135, posZ = 75  }, 
                                        { mapId = 0, mapName = "王国", posX = 168, posZ = 70 }, 
                                        { mapId = 0, mapName = "王国", posX = 196 , posZ = 74 }, 
                                        { mapId = 0, mapName = "王国", posX = 171, posZ = 44 }, 
                                        { mapId = 0, mapName = "王国", posX = 203, posZ = 26 }, 
                                        { mapId = 0, mapName = "王国", posX = 202, posZ = 32 }, 
                                        { mapId = 0, mapName = "王国", posX = 228, posZ = 105 }, 
                                        { mapId = 0, mapName = "王国", posX = 235 , posZ = 87 }, 
                                        { mapId = 0, mapName = "王国", posX = 247 , posZ = 103 }, 
                                        { mapId = 0, mapName = "王国", posX = 248 , posZ = 134 }, 
                                        { mapId = 0, mapName = "王国", posX = 247 , posZ = 148 }, 
                                        { mapId = 0, mapName = "王国", posX = 243 , posZ = 160 }, 
                                        { mapId = 0, mapName = "王国", posX = 225 , posZ = 161 }, 
                                        { mapId = 0, mapName = "王国", posX = 227 , posZ = 145 }, 
                                        { mapId = 0, mapName = "王国", posX = 227 , posZ = 137 }, 
                                        { mapId = 0, mapName = "王国", posX = 203 , posZ = 136 }, 
                                        { mapId = 0, mapName = "王国", posX = 153 , posZ = 191 }, 
                                        { mapId = 0, mapName = "王国", posX = 146 , posZ = 208 }, 
                                        { mapId = 0, mapName = "王国", posX = 162 , posZ = 226 }, 
                                        { mapId = 0, mapName = "王国", posX = 162 , posZ = 239 }, 
                                        { mapId = 0, mapName = "王国", posX = 144 , posZ = 241 }, 
                                        { mapId = 0, mapName = "王国", posX = 111 , posZ = 238 }, 
                                        { mapId = 0, mapName = "王国", posX = 96 , posZ = 235 }, 
                                        { mapId = 0, mapName = "王国", posX = 93 , posZ = 226 }, 
                                        { mapId = 0, mapName = "王国", posX = 99 , posZ = 221 }, 
                                        { mapId = 0, mapName = "王国", posX = 110 , posZ = 207 }, 
                                        { mapId = 0, mapName = "王国", posX = 114 , posZ = 187 }, 
                                        { mapId = 0, mapName = "王国", posX = 90 , posZ = 196 }, 
                                        { mapId = 0, mapName = "王国", posX = 82 , posZ = 202 }, 
                                        { mapId = 0, mapName = "王国", posX = 77 , posZ = 198 }, 
                                        { mapId = 0, mapName = "王国", posX = 51 , posZ = 185 }, 
                                        { mapId = 0, mapName = "王国", posX = 50 , posZ = 173 }, 
                                        { mapId = 0, mapName = "王国", posX = 51 , posZ = 98 }, 
                                        { mapId = 0, mapName = "王国", posX = 14 , posZ = 148 }, 
                                        { mapId = 0, mapName = "王国", posX = 29 , posZ = 137 }, 
                                        { mapId = 1, mapName = "边塞", posX = 25, posZ = 43 }, 
                                        { mapId = 1, mapName = "边塞", posX = 24, posZ = 35 }, 
                                        { mapId = 1, mapName = "边塞", posX = 51, posZ = 31 },  
                                        { mapId = 1, mapName = "边塞", posX = 70, posZ = 30 }, 
                                        { mapId = 1, mapName = "边塞", posX = 81, posZ = 45 }, 
                                        { mapId = 1, mapName = "边塞", posX = 111, posZ = 28 }, 
                                        { mapId = 1, mapName = "边塞", posX = 131, posZ = 23 }, 
                                        { mapId = 1, mapName = "边塞", posX = 137, posZ = 24 }, 
                                        { mapId = 1, mapName = "边塞", posX = 172, posZ = 38 }, 
                                        { mapId = 1, mapName = "边塞", posX = 183, posZ = 30 }, 
                                        { mapId = 1, mapName = "边塞", posX = 231, posZ = 32 }, 
                                        { mapId = 1, mapName = "边塞", posX = 181, posZ = 72 }, 
                                        { mapId = 1, mapName = "边塞", posX = 228, posZ = 60 }, 
                                        { mapId = 1, mapName = "边塞", posX = 233, posZ = 70 }, 
                                        { mapId = 1, mapName = "边塞", posX = 197, posZ = 157 }, 
                                        { mapId = 1, mapName = "边塞", posX = 195, posZ = 139 }, 
                                        { mapId = 1, mapName = "边塞", posX = 183, posZ = 131 }, 
                                        { mapId = 1, mapName = "边塞", posX = 168 , posZ = 153 }, 
                                        { mapId = 1, mapName = "边塞", posX = 150, posZ = 156 }, 
                                        { mapId = 1, mapName = "边塞", posX = 194, posZ = 172 }, 
                                        { mapId = 1, mapName = "边塞", posX = 200, posZ = 173 }, 
                                        { mapId = 1, mapName = "边塞", posX = 192, posZ = 176 }, 
                                        { mapId = 1, mapName = "边塞", posX = 204 , posZ = 186 }, 
                                        { mapId = 1, mapName = "边塞", posX = 228 , posZ = 202 }, 
                                        { mapId = 1, mapName = "边塞", posX = 198 , posZ = 203 }, 
                                        { mapId = 1, mapName = "边塞", posX = 168 , posZ = 195 }, 
                                        { mapId = 1, mapName = "边塞", posX = 169 , posZ = 216 }, 
                                        { mapId = 1, mapName = "边塞", posX = 173 , posZ = 225 }, 
                                        { mapId = 1, mapName = "边塞", posX = 156 , posZ = 220 }, 
                                        { mapId = 1, mapName = "边塞", posX = 126 , posZ = 223 }, 
                                        { mapId = 1, mapName = "边塞", posX = 109 , posZ = 231 }, 
                                        { mapId = 1, mapName = "边塞", posX = 91 , posZ = 225 }, 
                                        { mapId = 1, mapName = "边塞", posX = 53 , posZ = 224 }, 
                                        { mapId = 1, mapName = "边塞", posX = 45 , posZ = 225 }, 
                                        { mapId = 1, mapName = "边塞", posX = 26 , posZ = 226 }, 
                                        { mapId = 1, mapName = "边塞", posX = 30 , posZ = 202 }, 
                                        { mapId = 1, mapName = "边塞", posX = 30 , posZ = 181 }, 
                                        { mapId = 1, mapName = "边塞", posX = 44 , posZ = 166 }, 
                                        { mapId = 1, mapName = "边塞", posX = 24 , posZ = 154 }, 
                                        { mapId = 1, mapName = "边塞", posX = 31 , posZ = 152 }, 
                                        { mapId = 1, mapName = "边塞", posX = 60 , posZ = 137 }, 
                                        { mapId = 1, mapName = "边塞", posX = 88 , posZ = 135 }, 
                                        { mapId = 1, mapName = "边塞", posX = 77 , posZ = 162 }, 
                                        { mapId = 1, mapName = "边塞", posX = 105 , posZ = 145 }, 
                                        { mapId = 1, mapName = "边塞", posX = 104 , posZ = 106 }, 
                                        { mapId = 1, mapName = "边塞", posX = 79 , posZ = 37 }, 
                                        { mapId = 1, mapName = "边塞", posX = 51 , posZ = 31 }, 
                                        { mapId = 1, mapName = "边塞", posX = 48 , posZ = 104 }, 
                                        { mapId = 1, mapName = "边塞", posX = 31 , posZ = 86 }, 
                                        { mapId = 1, mapName = "边塞", posX = 38 , posZ = 75 },
                                        { mapId = 2, mapName = "大都", posX = 76, posZ = 22 }, 
                                        { mapId = 2, mapName = "大都", posX = 55, posZ = 183 }, 
                                        { mapId = 2, mapName = "大都", posX = 217, posZ = 217 }, 
                                        { mapId = 2, mapName = "大都", posX = 173, posZ = 39 }, 
                                        { mapId = 2, mapName = "大都", posX = 64, posZ = 219 }, 
                                        { mapId = 2, mapName = "大都", posX = 226, posZ = 85  }, 
                                        { mapId = 2, mapName = "大都", posX = 185, posZ = 224 }, 
                                        { mapId = 2, mapName = "大都", posX = 182, posZ = 23 }, 
                                        { mapId = 2, mapName = "大都", posX = 191, posZ = 69 }, 
                                        { mapId = 2, mapName = "大都", posX = 188, posZ = 85 }, 
                                        { mapId = 2, mapName = "大都", posX = 26, posZ = 178 }, 
                                        { mapId = 2, mapName = "大都", posX = 70, posZ = 48 }, 
                                        { mapId = 2, mapName = "大都", posX = 28, posZ = 69 }, 
                                        { mapId = 2, mapName = "大都", posX = 63, posZ = 110 }, 
                                        { mapId = 2, mapName = "大都", posX = 25, posZ = 206 }, 
                                        { mapId = 2, mapName = "大都", posX = 57 , posZ = 206 }, 
                                        { mapId = 2, mapName = "大都", posX = 53 , posZ = 177  }, 
                                        { mapId = 2, mapName = "大都", posX = 73 , posZ = 84  }, 
                                        { mapId = 2, mapName = "大都", posX = 177, posZ = 25  }, 
                                        { mapId = 2, mapName = "大都", posX = 224, posZ = 61  },                                         
                                        { mapId = 3, mapName = "威海港", posX = 141, posZ = 185  }, 
                                        { mapId = 3, mapName = "威海港", posX = 106, posZ = 185  }, 
                                        { mapId = 3, mapName = "威海港", posX = 67,  posZ = 148  }, 
                                        { mapId = 3, mapName = "威海港", posX = 129, posZ = 65  }, 
                                        { mapId = 3, mapName = "威海港", posX = 119, posZ = 90  }, 
                                        { mapId = 3, mapName = "威海港", posX = 130,  posZ = 91 }, 
                                        { mapId = 3, mapName = "威海港", posX = 89, posZ = 135  }, 
                                        { mapId = 3, mapName = "威海港", posX = 121, posZ = 134  }, 
                                        { mapId = 3, mapName = "威海港", posX = 195, posZ = 79 }, 
                                        { mapId = 3, mapName = "威海港", posX = 111,  posZ = 102 }, 
                                        { mapId = 3, mapName = "威海港", posX = 111,  posZ = 124 },
                                        { mapId = 3, mapName = "威海港", posX = 89,  posZ = 156 },
                                        { mapId = 3, mapName = "威海港", posX = 92,  posZ = 166 },
                                        { mapId = 3, mapName = "威海港", posX = 110,  posZ = 148 },
                                        { mapId = 3, mapName = "威海港", posX = 103,  posZ = 162 },
                                        { mapId = 3, mapName = "威海港", posX = 87,  posZ = 168 },
                                        { mapId = 3, mapName = "威海港", posX = 33,  posZ = 102 },
                                        { mapId = 3, mapName = "威海港", posX = 43,  posZ = 119 },
                                        { mapId = 3, mapName = "威海港", posX = 62,  posZ = 140 },
                                        { mapId = 3, mapName = "威海港", posX = 64,  posZ = 176 },
                                       	{ mapId = 36, mapName = "大都南", posX = 24, posZ = 102 }, 
                                        { mapId = 36, mapName = "大都南", posX = 24, posZ = 101 }, 
                                        { mapId = 36, mapName = "大都南", posX = 32, posZ = 115 }, 
                                        { mapId = 36, mapName = "大都南", posX = 22, posZ = 108 }, 
                                        { mapId = 36, mapName = "大都南", posX = 20, posZ = 132 }, 
                                        { mapId = 36, mapName = "大都南", posX = 31, posZ = 157  }, 
                                        { mapId = 36, mapName = "大都南", posX = 59 , posZ = 158 }, 
                                        { mapId = 36, mapName = "大都南", posX = 72, posZ = 159 }, 
                                        { mapId = 36, mapName = "大都南", posX = 54, posZ = 140 }, 
                                        { mapId = 36, mapName = "大都南", posX = 100, posZ = 151  }, 
                                        { mapId = 36, mapName = "大都南", posX = 140, posZ = 165 }, 
                                        { mapId = 36, mapName = "大都南", posX = 158, posZ = 160 }, 
                                        { mapId = 36, mapName = "大都南", posX = 174, posZ = 168 }, 
                                        { mapId = 36, mapName = "大都南", posX = 209, posZ = 156 }, 
                                        { mapId = 36, mapName = "大都南", posX = 234, posZ = 161 }, 
                                        { mapId = 36, mapName = "大都南", posX = 238 , posZ = 213 }, 
                                        { mapId = 36, mapName = "大都南", posX = 158 , posZ = 235  }, 
                                        { mapId = 36, mapName = "大都南", posX = 202 , posZ = 225  }, 
                                        { mapId = 36, mapName = "大都南", posX = 150, posZ = 235  },       
                                        { mapId = 36, mapName = "大都南", posX = 121, posZ = 230  },                                                                                
                                        { mapId = 37, mapName = "大都东", posX = 64, posZ = 49  },       
                                        { mapId = 37, mapName = "大都东", posX = 86, posZ = 118  }, 
                                        { mapId = 37, mapName = "大都东", posX = 87, posZ = 168  },       
                                        { mapId = 37, mapName = "大都东", posX = 120, posZ = 158  },
                                        { mapId = 37, mapName = "大都东", posX = 161, posZ = 198  },       
                                        { mapId = 37, mapName = "大都东", posX = 139, posZ = 240 },
                                        { mapId = 37, mapName = "大都东", posX = 116, posZ = 241  },       
                                        { mapId = 37, mapName = "大都东", posX = 106, posZ = 212  },
                                        { mapId = 37, mapName = "大都东", posX = 90, posZ = 210  },       
                                        { mapId = 37, mapName = "大都东", posX = 92, posZ = 244  },
                                        { mapId = 37, mapName = "大都东", posX = 108, posZ = 242  },       
                                        { mapId = 37, mapName = "大都东", posX = 104, posZ = 231  }, 
                                        { mapId = 37, mapName = "大都东", posX = 155, posZ = 165  },       
                                        { mapId = 37, mapName = "大都东", posX = 215, posZ = 224  },
                                        { mapId = 37, mapName = "大都东", posX = 221, posZ = 124  },       
                                        { mapId = 37, mapName = "大都东", posX = 190, posZ = 81  },
                                        { mapId = 37, mapName = "大都东", posX = 169, posZ = 135  },       
                                        { mapId = 37, mapName = "大都东", posX = 149, posZ = 95  },
                                        { mapId = 37, mapName = "大都东", posX = 130, posZ = 90  },       
                                        { mapId = 37, mapName = "大都东", posX = 121, posZ = 158  },                                        
                                        { mapId = 38, mapName = "大都西", posX = 137, posZ = 86  },       
                                        { mapId = 38, mapName = "大都西", posX = 135, posZ = 97  }, 
                                        { mapId = 38, mapName = "大都西", posX = 133, posZ = 108  },       
                                        { mapId = 38, mapName = "大都西", posX = 166, posZ = 111  },
                                        { mapId = 38, mapName = "大都西", posX = 182, posZ = 130  },       
                                        { mapId = 38, mapName = "大都西", posX = 234, posZ = 103  },
                                        { mapId = 38, mapName = "大都西", posX = 213, posZ = 179  },       
                                        { mapId = 38, mapName = "大都西", posX = 185, posZ = 167  },
                                        { mapId = 38, mapName = "大都西", posX = 147, posZ = 195  },       
                                        { mapId = 38, mapName = "大都西", posX = 160, posZ = 223  },
                                        { mapId = 38, mapName = "大都西", posX = 131, posZ = 222  },       
                                        { mapId = 38, mapName = "大都西", posX = 72, posZ = 161  }, 
                                        { mapId = 38, mapName = "大都西", posX = 33, posZ = 192  },       
                                        { mapId = 38, mapName = "大都西", posX = 89, posZ = 232  },
                                        { mapId = 38, mapName = "大都西", posX = 67, posZ = 135  },       
                                        { mapId = 38, mapName = "大都西", posX = 43, posZ = 86  },
                                        { mapId = 38, mapName = "大都西", posX = 87, posZ = 37  },       
                                        { mapId = 38, mapName = "大都西", posX = 134, posZ = 41  },
                                        { mapId = 38, mapName = "大都西", posX = 161, posZ = 74  },       
                                        { mapId = 38, mapName = "大都西", posX = 134, posZ = 107  },
}

x300330_g_MissionTargetTable2        = {
                                        { mapId = 0, mapName = "王国", posX = 89, posZ = 109 }, 
                                        { mapId = 0, mapName = "王国", posX = 98, posZ = 99 }, 
                                        { mapId = 0, mapName = "王国", posX = 76, posZ = 105 },  
                                        { mapId = 0, mapName = "王国", posX = 77, posZ = 93 }, 
                                        { mapId = 0, mapName = "王国", posX = 87, posZ = 95 }, 
                                        { mapId = 0, mapName = "王国", posX = 92, posZ = 84 }, 
                                        { mapId = 0, mapName = "王国", posX = 92, posZ = 68 }, 
                                        { mapId = 0, mapName = "王国", posX = 88, posZ = 58 }, 
                                        { mapId = 0, mapName = "王国", posX = 82, posZ = 54 }, 
                                        { mapId = 0, mapName = "王国", posX = 49, posZ = 57 }, 
                                        { mapId = 0, mapName = "王国", posX = 53, posZ = 93 }, 
                                        { mapId = 0, mapName = "王国", posX = 49, posZ = 91 }, 
                                        { mapId = 0, mapName = "王国", posX = 59, posZ = 93 }, 
                                        { mapId = 0, mapName = "王国", posX = 49, posZ = 120 }, 
                                        { mapId = 0, mapName = "王国", posX = 50, posZ = 148 }, 
                                        { mapId = 0, mapName = "王国", posX = 85, posZ = 156  }, 
                                        { mapId = 0, mapName = "王国", posX = 111, posZ = 163 }, 
                                        { mapId = 0, mapName = "王国", posX = 164 , posZ = 186 }, 
                                        { mapId = 0, mapName = "王国", posX = 93, posZ = 204 }, 
                                        { mapId = 0, mapName = "王国", posX = 150, posZ = 234 }, 
                                        { mapId = 0, mapName = "王国", posX = 101, posZ = 229 }, 
                                        { mapId = 0, mapName = "王国", posX = 96, posZ = 215 }, 
                                        { mapId = 0, mapName = "王国", posX = 76 , posZ = 226 }, 
                                        { mapId = 0, mapName = "王国", posX = 52 , posZ = 223 }, 
                                        { mapId = 0, mapName = "王国", posX = 49 , posZ = 220 }, 
                                        { mapId = 0, mapName = "王国", posX = 56 , posZ = 202 }, 
                                        { mapId = 0, mapName = "王国", posX = 67 , posZ = 201 }, 
                                        { mapId = 0, mapName = "王国", posX = 92 , posZ = 206 }, 
                                        { mapId = 0, mapName = "王国", posX = 90 , posZ = 190 }, 
                                        { mapId = 0, mapName = "王国", posX = 112 , posZ = 186 }, 
                                        { mapId = 0, mapName = "王国", posX = 156 , posZ = 167 }, 
                                        { mapId = 0, mapName = "王国", posX = 164 , posZ = 186 }, 
                                        { mapId = 0, mapName = "王国", posX = 171 , posZ = 170 }, 
                                        { mapId = 0, mapName = "王国", posX = 203 , posZ = 194 }, 
                                        { mapId = 0, mapName = "王国", posX = 202 , posZ = 210 }, 
                                        { mapId = 0, mapName = "王国", posX = 200 , posZ = 233 }, 
                                        { mapId = 0, mapName = "王国", posX = 183 , posZ = 240 }, 
                                        { mapId = 0, mapName = "王国", posX = 179 , posZ = 229 }, 
                                        { mapId = 0, mapName = "王国", posX = 200 , posZ = 165 }, 
                                        { mapId = 0, mapName = "王国", posX = 205 , posZ = 148 }, 
                                        { mapId = 0, mapName = "王国", posX = 210 , posZ = 117 }, 
                                        { mapId = 0, mapName = "王国", posX = 226 , posZ = 119 }, 
                                        { mapId = 0, mapName = "王国", posX = 226 , posZ = 110 }, 
                                        { mapId = 0, mapName = "王国", posX = 240 , posZ = 107 }, 
                                        { mapId = 0, mapName = "王国", posX = 246 , posZ = 109 }, 
                                        { mapId = 0, mapName = "王国", posX = 225 , posZ = 167 }, 
                                        { mapId = 0, mapName = "王国", posX = 226 , posZ = 155 }, 
                                        { mapId = 0, mapName = "王国", posX = 205 , posZ = 146 }, 
                                        { mapId = 0, mapName = "王国", posX = 165 , posZ = 108 }, 
                                        { mapId = 0, mapName = "王国", posX = 153 , posZ = 92 }, 
                                        { mapId = 1, mapName = "边塞", posX = 46, posZ = 59 }, 
                                        { mapId = 1, mapName = "边塞", posX = 56, posZ = 57 }, 
                                        { mapId = 1, mapName = "边塞", posX = 50, posZ = 76 },  
                                        { mapId = 1, mapName = "边塞", posX = 81, posZ = 76 }, 
                                        { mapId = 1, mapName = "边塞", posX = 102, posZ = 88 }, 
                                        { mapId = 1, mapName = "边塞", posX = 80, posZ = 87 }, 
                                        { mapId = 1, mapName = "边塞", posX = 35, posZ = 95 }, 
                                        { mapId = 1, mapName = "边塞", posX = 33, posZ = 142 }, 
                                        { mapId = 1, mapName = "边塞", posX = 40, posZ = 169 }, 
                                        { mapId = 1, mapName = "边塞", posX = 40, posZ = 175 }, 
                                        { mapId = 1, mapName = "边塞", posX = 46, posZ = 189 }, 
                                        { mapId = 1, mapName = "边塞", posX = 81, posZ = 220 }, 
                                        { mapId = 1, mapName = "边塞", posX = 111, posZ = 226 }, 
                                        { mapId = 1, mapName = "边塞", posX = 130, posZ = 226 }, 
                                        { mapId = 1, mapName = "边塞", posX = 153, posZ = 213 }, 
                                        { mapId = 1, mapName = "边塞", posX = 166, posZ = 230  }, 
                                        { mapId = 1, mapName = "边塞", posX = 171, posZ = 231 }, 
                                        { mapId = 1, mapName = "边塞", posX = 184, posZ = 221 }, 
                                        { mapId = 1, mapName = "边塞", posX = 199, posZ = 226 }, 
                                        { mapId = 1, mapName = "边塞", posX = 216, posZ = 210 }, 
                                        { mapId = 1, mapName = "边塞", posX = 218, posZ = 193 }, 
                                        { mapId = 1, mapName = "边塞", posX = 210, posZ = 198 }, 
                                        { mapId = 1, mapName = "边塞", posX = 210 , posZ = 187 }, 
                                        { mapId = 1, mapName = "边塞", posX = 209 , posZ = 182 }, 
                                        { mapId = 1, mapName = "边塞", posX = 210 , posZ = 155 }, 
                                        { mapId = 1, mapName = "边塞", posX = 212 , posZ = 143 }, 
                                        { mapId = 1, mapName = "边塞", posX = 204 , posZ = 134 }, 
                                        { mapId = 1, mapName = "边塞", posX = 199 , posZ = 135 }, 
                                        { mapId = 1, mapName = "边塞", posX = 171 , posZ = 170 }, 
                                        { mapId = 1, mapName = "边塞", posX = 158 , posZ = 172 }, 
                                        { mapId = 1, mapName = "边塞", posX = 155 , posZ = 155 }, 
                                        { mapId = 1, mapName = "边塞", posX = 169 , posZ = 116 }, 
                                        { mapId = 1, mapName = "边塞", posX = 203 , posZ = 109 }, 
                                        { mapId = 1, mapName = "边塞", posX = 208 , posZ = 95 }, 
                                        { mapId = 1, mapName = "边塞", posX = 203 , posZ = 93 }, 
                                        { mapId = 1, mapName = "边塞", posX = 149 , posZ = 77 }, 
                                        { mapId = 1, mapName = "边塞", posX = 157 , posZ = 88 }, 
                                        { mapId = 1, mapName = "边塞", posX = 164 , posZ = 230 }, 
                                        { mapId = 1, mapName = "边塞", posX = 155 , posZ = 209 }, 
                                        { mapId = 1, mapName = "边塞", posX = 132 , posZ = 227 }, 
                                        { mapId = 1, mapName = "边塞", posX = 118 , posZ = 226 }, 
                                        { mapId = 1, mapName = "边塞", posX = 50 , posZ = 184 }, 
                                        { mapId = 1, mapName = "边塞", posX = 45 , posZ = 165 }, 
                                        { mapId = 1, mapName = "边塞", posX = 36 , posZ = 96 }, 
                                        { mapId = 1, mapName = "边塞", posX = 75 , posZ = 93 }, 
                                        { mapId = 1, mapName = "边塞", posX = 77 , posZ = 110 }, 
                                        { mapId = 1, mapName = "边塞", posX = 89 , posZ = 88 }, 
                                        { mapId = 1, mapName = "边塞", posX = 102 , posZ = 88 }, 
                                        { mapId = 1, mapName = "边塞", posX = 88 , posZ = 76 }, 
                                        { mapId = 1, mapName = "边塞", posX = 71 , posZ = 63 },
                                        { mapId = 2, mapName = "大都", posX = 76, posZ = 22 }, 
                                        { mapId = 2, mapName = "大都", posX = 55, posZ = 183 }, 
                                        { mapId = 2, mapName = "大都", posX = 217, posZ = 217 }, 
                                        { mapId = 2, mapName = "大都", posX = 173, posZ = 39 }, 
                                        { mapId = 2, mapName = "大都", posX = 64, posZ = 219 }, 
                                        { mapId = 2, mapName = "大都", posX = 226, posZ = 85  }, 
                                        { mapId = 2, mapName = "大都", posX = 185, posZ = 224 }, 
                                        { mapId = 2, mapName = "大都", posX = 182, posZ = 23 }, 
                                        { mapId = 2, mapName = "大都", posX = 191, posZ = 69 }, 
                                        { mapId = 2, mapName = "大都", posX = 188, posZ = 85 }, 
                                        { mapId = 2, mapName = "大都", posX = 26, posZ = 178 }, 
                                        { mapId = 2, mapName = "大都", posX = 70, posZ = 48 }, 
                                        { mapId = 2, mapName = "大都", posX = 28, posZ = 69 }, 
                                        { mapId = 2, mapName = "大都", posX = 63, posZ = 110 }, 
                                        { mapId = 2, mapName = "大都", posX = 25, posZ = 206 }, 
                                        { mapId = 2, mapName = "大都", posX = 57 , posZ = 206 }, 
                                        { mapId = 2, mapName = "大都", posX = 53 , posZ = 177  }, 
                                        { mapId = 2, mapName = "大都", posX = 73 , posZ = 84  }, 
                                        { mapId = 2, mapName = "大都", posX = 177, posZ = 25  }, 
                                        { mapId = 2, mapName = "大都", posX = 224, posZ = 61  },                                         
                                        { mapId = 3, mapName = "威海港", posX = 141, posZ = 185  }, 
                                        { mapId = 3, mapName = "威海港", posX = 106, posZ = 185  }, 
                                        { mapId = 3, mapName = "威海港", posX = 67,  posZ = 148  }, 
                                        { mapId = 3, mapName = "威海港", posX = 129, posZ = 65  }, 
                                        { mapId = 3, mapName = "威海港", posX = 119, posZ = 90  }, 
                                        { mapId = 3, mapName = "威海港", posX = 130,  posZ = 91 }, 
                                        { mapId = 3, mapName = "威海港", posX = 89, posZ = 135  }, 
                                        { mapId = 3, mapName = "威海港", posX = 121, posZ = 134  }, 
                                        { mapId = 3, mapName = "威海港", posX = 195, posZ = 79 }, 
                                        { mapId = 3, mapName = "威海港", posX = 111,  posZ = 102 }, 
                                        { mapId = 3, mapName = "威海港", posX = 111,  posZ = 124 },
                                        { mapId = 3, mapName = "威海港", posX = 89,  posZ = 156 },
                                        { mapId = 3, mapName = "威海港", posX = 92,  posZ = 166 },
                                        { mapId = 3, mapName = "威海港", posX = 110,  posZ = 148 },
                                        { mapId = 3, mapName = "威海港", posX = 103,  posZ = 162 },
                                        { mapId = 3, mapName = "威海港", posX = 87,  posZ = 168 },
                                        { mapId = 3, mapName = "威海港", posX = 33,  posZ = 102 },
                                        { mapId = 3, mapName = "威海港", posX = 43,  posZ = 119 },
                                        { mapId = 3, mapName = "威海港", posX = 62,  posZ = 140 },
                                        { mapId = 3, mapName = "威海港", posX = 64,  posZ = 176 },
                                       	{ mapId = 36, mapName = "大都南", posX = 24, posZ = 102 }, 
                                        { mapId = 36, mapName = "大都南", posX = 24, posZ = 101 }, 
                                        { mapId = 36, mapName = "大都南", posX = 32, posZ = 115 }, 
                                        { mapId = 36, mapName = "大都南", posX = 22, posZ = 108 }, 
                                        { mapId = 36, mapName = "大都南", posX = 20, posZ = 132 }, 
                                        { mapId = 36, mapName = "大都南", posX = 31, posZ = 157  }, 
                                        { mapId = 36, mapName = "大都南", posX = 59 , posZ = 158 }, 
                                        { mapId = 36, mapName = "大都南", posX = 72, posZ = 159 }, 
                                        { mapId = 36, mapName = "大都南", posX = 54, posZ = 140 }, 
                                        { mapId = 36, mapName = "大都南", posX = 100, posZ = 151  }, 
                                        { mapId = 36, mapName = "大都南", posX = 140, posZ = 165 }, 
                                        { mapId = 36, mapName = "大都南", posX = 158, posZ = 160 }, 
                                        { mapId = 36, mapName = "大都南", posX = 174, posZ = 168 }, 
                                        { mapId = 36, mapName = "大都南", posX = 209, posZ = 156 }, 
                                        { mapId = 36, mapName = "大都南", posX = 234, posZ = 161 }, 
                                        { mapId = 36, mapName = "大都南", posX = 238 , posZ = 213 }, 
                                        { mapId = 36, mapName = "大都南", posX = 158 , posZ = 235  }, 
                                        { mapId = 36, mapName = "大都南", posX = 202 , posZ = 225  }, 
                                        { mapId = 36, mapName = "大都南", posX = 150, posZ = 235  },       
                                        { mapId = 36, mapName = "大都南", posX = 121, posZ = 230  },                                                                                
                                        { mapId = 37, mapName = "大都东", posX = 64, posZ = 49  },       
                                        { mapId = 37, mapName = "大都东", posX = 86, posZ = 118  }, 
                                        { mapId = 37, mapName = "大都东", posX = 87, posZ = 168  },       
                                        { mapId = 37, mapName = "大都东", posX = 120, posZ = 158  },
                                        { mapId = 37, mapName = "大都东", posX = 161, posZ = 198  },       
                                        { mapId = 37, mapName = "大都东", posX = 139, posZ = 240 },
                                        { mapId = 37, mapName = "大都东", posX = 116, posZ = 241  },       
                                        { mapId = 37, mapName = "大都东", posX = 106, posZ = 212  },
                                        { mapId = 37, mapName = "大都东", posX = 90, posZ = 210  },       
                                        { mapId = 37, mapName = "大都东", posX = 92, posZ = 244  },
                                        { mapId = 37, mapName = "大都东", posX = 108, posZ = 242  },       
                                        { mapId = 37, mapName = "大都东", posX = 104, posZ = 231  }, 
                                        { mapId = 37, mapName = "大都东", posX = 155, posZ = 165  },       
                                        { mapId = 37, mapName = "大都东", posX = 215, posZ = 224  },
                                        { mapId = 37, mapName = "大都东", posX = 221, posZ = 124  },       
                                        { mapId = 37, mapName = "大都东", posX = 190, posZ = 81  },
                                        { mapId = 37, mapName = "大都东", posX = 169, posZ = 135  },       
                                        { mapId = 37, mapName = "大都东", posX = 149, posZ = 95  },
                                        { mapId = 37, mapName = "大都东", posX = 130, posZ = 90  },       
                                        { mapId = 37, mapName = "大都东", posX = 121, posZ = 158  },                                        
                                        { mapId = 38, mapName = "大都西", posX = 137, posZ = 86  },       
                                        { mapId = 38, mapName = "大都西", posX = 135, posZ = 97  }, 
                                        { mapId = 38, mapName = "大都西", posX = 133, posZ = 108  },       
                                        { mapId = 38, mapName = "大都西", posX = 166, posZ = 111  },
                                        { mapId = 38, mapName = "大都西", posX = 182, posZ = 130  },       
                                        { mapId = 38, mapName = "大都西", posX = 234, posZ = 103  },
                                        { mapId = 38, mapName = "大都西", posX = 213, posZ = 179  },       
                                        { mapId = 38, mapName = "大都西", posX = 185, posZ = 167  },
                                        { mapId = 38, mapName = "大都西", posX = 147, posZ = 195  },       
                                        { mapId = 38, mapName = "大都西", posX = 160, posZ = 223  },
                                        { mapId = 38, mapName = "大都西", posX = 131, posZ = 222  },       
                                        { mapId = 38, mapName = "大都西", posX = 72, posZ = 161  }, 
                                        { mapId = 38, mapName = "大都西", posX = 33, posZ = 192  },       
                                        { mapId = 38, mapName = "大都西", posX = 89, posZ = 232  },
                                        { mapId = 38, mapName = "大都西", posX = 67, posZ = 135  },       
                                        { mapId = 38, mapName = "大都西", posX = 43, posZ = 86  },
                                        { mapId = 38, mapName = "大都西", posX = 87, posZ = 37  },       
                                        { mapId = 38, mapName = "大都西", posX = 134, posZ = 41  },
                                        { mapId = 38, mapName = "大都西", posX = 161, posZ = 74  },       
                                        { mapId = 38, mapName = "大都西", posX = 134, posZ = 107  },
}

x300330_g_MissionTargetTable3        = {
                                        { mapId = 0, mapName = "王国", posX = 93, posZ = 103 }, 
                                        { mapId = 0, mapName = "王国", posX = 78, posZ = 123 }, 
                                        { mapId = 0, mapName = "王国", posX = 46, posZ = 103 },  
                                        { mapId = 0, mapName = "王国", posX = 78, posZ = 94 }, 
                                        { mapId = 0, mapName = "王国", posX = 57, posZ = 94 }, 
                                        { mapId = 0, mapName = "王国", posX = 88, posZ = 93 }, 
                                        { mapId = 0, mapName = "王国", posX = 92, posZ = 82 }, 
                                        { mapId = 0, mapName = "王国", posX = 102, posZ = 86 }, 
                                        { mapId = 0, mapName = "王国", posX = 85, posZ = 163 }, 
                                        { mapId = 0, mapName = "王国", posX = 96, posZ = 162 }, 
                                        { mapId = 0, mapName = "王国", posX = 109, posZ = 163 }, 
                                        { mapId = 0, mapName = "王国", posX = 108, posZ = 180 }, 
                                        { mapId = 0, mapName = "王国", posX = 104, posZ = 188 }, 
                                        { mapId = 0, mapName = "王国", posX = 101, posZ = 218 }, 
                                        { mapId = 0, mapName = "王国", posX = 99, posZ = 227 }, 
                                        { mapId = 0, mapName = "王国", posX = 106, posZ = 233  }, 
                                        { mapId = 0, mapName = "王国", posX = 113, posZ = 240 }, 
                                        { mapId = 0, mapName = "王国", posX = 143 , posZ = 239 }, 
                                        { mapId = 0, mapName = "王国", posX = 149, posZ = 232 }, 
                                        { mapId = 0, mapName = "王国", posX = 155, posZ = 224 }, 
                                        { mapId = 0, mapName = "王国", posX = 155, posZ = 218 }, 
                                        { mapId = 0, mapName = "王国", posX = 104, posZ = 189 }, 
                                        { mapId = 0, mapName = "王国", posX = 144 , posZ = 177 }, 
                                        { mapId = 0, mapName = "王国", posX = 183 , posZ = 194 }, 
                                        { mapId = 0, mapName = "王国", posX = 182 , posZ = 188 }, 
                                        { mapId = 0, mapName = "王国", posX = 174 , posZ = 209 }, 
                                        { mapId = 0, mapName = "王国", posX = 170 , posZ = 215 }, 
                                        { mapId = 0, mapName = "王国", posX = 183 , posZ = 233 }, 
                                        { mapId = 0, mapName = "王国", posX = 176 , posZ = 228 }, 
                                        { mapId = 0, mapName = "王国", posX = 200 , posZ = 229 }, 
                                        { mapId = 0, mapName = "王国", posX = 202 , posZ = 224 }, 
                                        { mapId = 0, mapName = "王国", posX = 200 , posZ = 211 }, 
                                        { mapId = 0, mapName = "王国", posX = 194 , posZ = 195 }, 
                                        { mapId = 0, mapName = "王国", posX = 200 , posZ = 193 }, 
                                        { mapId = 0, mapName = "王国", posX = 192 , posZ = 181 }, 
                                        { mapId = 0, mapName = "王国", posX = 190 , posZ = 176 }, 
                                        { mapId = 0, mapName = "王国", posX = 198 , posZ = 164 }, 
                                        { mapId = 0, mapName = "王国", posX = 211 , posZ = 150 }, 
                                        { mapId = 0, mapName = "王国", posX = 211 , posZ = 145 }, 
                                        { mapId = 0, mapName = "王国", posX = 228 , posZ = 154 }, 
                                        { mapId = 0, mapName = "王国", posX = 225 , posZ = 166 }, 
                                        { mapId = 0, mapName = "王国", posX = 250 , posZ = 149 }, 
                                        { mapId = 0, mapName = "王国", posX = 244 , posZ = 166 }, 
                                        { mapId = 0, mapName = "王国", posX = 250 , posZ = 161 }, 
                                        { mapId = 0, mapName = "王国", posX = 248 , posZ = 108 }, 
                                        { mapId = 0, mapName = "王国", posX = 226 , posZ = 110 }, 
                                        { mapId = 0, mapName = "王国", posX = 226 , posZ = 119 }, 
                                        { mapId = 0, mapName = "王国", posX = 211 , posZ = 128 }, 
                                        { mapId = 0, mapName = "王国", posX = 211 , posZ = 120 }, 
                                        { mapId = 0, mapName = "王国", posX = 162 , posZ = 71 }, 
                                        { mapId = 1, mapName = "边塞", posX = 80, posZ = 26 }, 
                                        { mapId = 1, mapName = "边塞", posX = 100, posZ = 31 }, 
                                        { mapId = 1, mapName = "边塞", posX = 104, posZ = 24 },  
                                        { mapId = 1, mapName = "边塞", posX = 111, posZ = 27 }, 
                                        { mapId = 1, mapName = "边塞", posX = 117, posZ = 28 }, 
                                        { mapId = 1, mapName = "边塞", posX = 173, posZ = 36 }, 
                                        { mapId = 1, mapName = "边塞", posX = 179, posZ = 42 }, 
                                        { mapId = 1, mapName = "边塞", posX = 202, posZ = 47 }, 
                                        { mapId = 1, mapName = "边塞", posX = 204, posZ = 23 }, 
                                        { mapId = 1, mapName = "边塞", posX = 212, posZ = 23 }, 
                                        { mapId = 1, mapName = "边塞", posX = 219, posZ = 49 }, 
                                        { mapId = 1, mapName = "边塞", posX = 216, posZ = 60 }, 
                                        { mapId = 1, mapName = "边塞", posX = 210, posZ = 57 }, 
                                        { mapId = 1, mapName = "边塞", posX = 198, posZ = 57 }, 
                                        { mapId = 1, mapName = "边塞", posX = 217, posZ = 74 }, 
                                        { mapId = 1, mapName = "边塞", posX = 208, posZ = 75  }, 
                                        { mapId = 1, mapName = "边塞", posX = 190, posZ = 76 }, 
                                        { mapId = 1, mapName = "边塞", posX = 184 , posZ = 76 }, 
                                        { mapId = 1, mapName = "边塞", posX = 157, posZ = 73 }, 
                                        { mapId = 1, mapName = "边塞", posX = 176, posZ = 97 }, 
                                        { mapId = 1, mapName = "边塞", posX = 212, posZ = 87 }, 
                                        { mapId = 1, mapName = "边塞", posX = 228, posZ = 95 }, 
                                        { mapId = 1, mapName = "边塞", posX = 234 , posZ = 109 }, 
                                        { mapId = 1, mapName = "边塞", posX = 229 , posZ = 197 }, 
                                        { mapId = 1, mapName = "边塞", posX = 230 , posZ = 204 }, 
                                        { mapId = 1, mapName = "边塞", posX = 188 , posZ = 230 }, 
                                        { mapId = 1, mapName = "边塞", posX = 169 , posZ = 229 }, 
                                        { mapId = 1, mapName = "边塞", posX = 160 , posZ = 223 }, 
                                        { mapId = 1, mapName = "边塞", posX = 145 , posZ = 217 }, 
                                        { mapId = 1, mapName = "边塞", posX = 139 , posZ = 205 }, 
                                        { mapId = 1, mapName = "边塞", posX = 122 , posZ = 227 }, 
                                        { mapId = 1, mapName = "边塞", posX = 110 , posZ = 216 }, 
                                        { mapId = 1, mapName = "边塞", posX = 87 , posZ = 217 }, 
                                        { mapId = 1, mapName = "边塞", posX = 71 , posZ = 227 }, 
                                        { mapId = 1, mapName = "边塞", posX = 36 , posZ = 202 }, 
                                        { mapId = 1, mapName = "边塞", posX = 34 , posZ = 196 }, 
                                        { mapId = 1, mapName = "边塞", posX = 44 , posZ = 164 }, 
                                        { mapId = 1, mapName = "边塞", posX = 34 , posZ = 147 }, 
                                        { mapId = 1, mapName = "边塞", posX = 44 , posZ = 141 }, 
                                        { mapId = 1, mapName = "边塞", posX = 54 , posZ = 138 }, 
                                        { mapId = 1, mapName = "边塞", posX = 65 , posZ = 146 }, 
                                        { mapId = 1, mapName = "边塞", posX = 70 , posZ = 165 }, 
                                        { mapId = 1, mapName = "边塞", posX = 129 , posZ = 26 }, 
                                        { mapId = 1, mapName = "边塞", posX = 96 , posZ = 30 }, 
                                        { mapId = 1, mapName = "边塞", posX = 71 , posZ = 46 }, 
                                        { mapId = 1, mapName = "边塞", posX = 82 , posZ = 46 }, 
                                        { mapId = 1, mapName = "边塞", posX = 60 , posZ = 102 }, 
                                        { mapId = 1, mapName = "边塞", posX = 67 , posZ = 81 }, 
                                        { mapId = 1, mapName = "边塞", posX = 58 , posZ = 78 }, 
                                        { mapId = 1, mapName = "边塞", posX = 45 , posZ = 89 },
                                        { mapId = 2, mapName = "大都", posX = 76, posZ = 22 }, 
                                        { mapId = 2, mapName = "大都", posX = 55, posZ = 183 }, 
                                        { mapId = 2, mapName = "大都", posX = 217, posZ = 217 }, 
                                        { mapId = 2, mapName = "大都", posX = 173, posZ = 39 }, 
                                        { mapId = 2, mapName = "大都", posX = 64, posZ = 219 }, 
                                        { mapId = 2, mapName = "大都", posX = 226, posZ = 85  }, 
                                        { mapId = 2, mapName = "大都", posX = 185, posZ = 224 }, 
                                        { mapId = 2, mapName = "大都", posX = 182, posZ = 23 }, 
                                        { mapId = 2, mapName = "大都", posX = 191, posZ = 69 }, 
                                        { mapId = 2, mapName = "大都", posX = 188, posZ = 85 }, 
                                        { mapId = 2, mapName = "大都", posX = 26, posZ = 178 }, 
                                        { mapId = 2, mapName = "大都", posX = 70, posZ = 48 }, 
                                        { mapId = 2, mapName = "大都", posX = 28, posZ = 69 }, 
                                        { mapId = 2, mapName = "大都", posX = 63, posZ = 110 }, 
                                        { mapId = 2, mapName = "大都", posX = 25, posZ = 206 }, 
                                        { mapId = 2, mapName = "大都", posX = 57 , posZ = 206 }, 
                                        { mapId = 2, mapName = "大都", posX = 53 , posZ = 177  }, 
                                        { mapId = 2, mapName = "大都", posX = 73 , posZ = 84  }, 
                                        { mapId = 2, mapName = "大都", posX = 177, posZ = 25  }, 
                                        { mapId = 2, mapName = "大都", posX = 224, posZ = 61  },                                         
                                        { mapId = 3, mapName = "威海港", posX = 141, posZ = 185  }, 
                                        { mapId = 3, mapName = "威海港", posX = 106, posZ = 185  }, 
                                        { mapId = 3, mapName = "威海港", posX = 67,  posZ = 148  }, 
                                        { mapId = 3, mapName = "威海港", posX = 129, posZ = 65  }, 
                                        { mapId = 3, mapName = "威海港", posX = 119, posZ = 90  }, 
                                        { mapId = 3, mapName = "威海港", posX = 130,  posZ = 91 }, 
                                        { mapId = 3, mapName = "威海港", posX = 89, posZ = 135  }, 
                                        { mapId = 3, mapName = "威海港", posX = 121, posZ = 134  }, 
                                        { mapId = 3, mapName = "威海港", posX = 195, posZ = 79 }, 
                                        { mapId = 3, mapName = "威海港", posX = 111,  posZ = 102 }, 
                                        { mapId = 3, mapName = "威海港", posX = 111,  posZ = 124 },
                                        { mapId = 3, mapName = "威海港", posX = 89,  posZ = 156 },
                                        { mapId = 3, mapName = "威海港", posX = 92,  posZ = 166 },
                                        { mapId = 3, mapName = "威海港", posX = 110,  posZ = 148 },
                                        { mapId = 3, mapName = "威海港", posX = 103,  posZ = 162 },
                                        { mapId = 3, mapName = "威海港", posX = 87,  posZ = 168 },
                                        { mapId = 3, mapName = "威海港", posX = 33,  posZ = 102 },
                                        { mapId = 3, mapName = "威海港", posX = 43,  posZ = 119 },
                                        { mapId = 3, mapName = "威海港", posX = 62,  posZ = 140 },
                                        { mapId = 3, mapName = "威海港", posX = 64,  posZ = 176 },
                                       	{ mapId = 36, mapName = "大都南", posX = 24, posZ = 102 }, 
                                        { mapId = 36, mapName = "大都南", posX = 24, posZ = 101 }, 
                                        { mapId = 36, mapName = "大都南", posX = 32, posZ = 115 }, 
                                        { mapId = 36, mapName = "大都南", posX = 22, posZ = 108 }, 
                                        { mapId = 36, mapName = "大都南", posX = 20, posZ = 132 }, 
                                        { mapId = 36, mapName = "大都南", posX = 31, posZ = 157  }, 
                                        { mapId = 36, mapName = "大都南", posX = 59 , posZ = 158 }, 
                                        { mapId = 36, mapName = "大都南", posX = 72, posZ = 159 }, 
                                        { mapId = 36, mapName = "大都南", posX = 54, posZ = 140 }, 
                                        { mapId = 36, mapName = "大都南", posX = 100, posZ = 151  }, 
                                        { mapId = 36, mapName = "大都南", posX = 140, posZ = 165 }, 
                                        { mapId = 36, mapName = "大都南", posX = 158, posZ = 160 }, 
                                        { mapId = 36, mapName = "大都南", posX = 174, posZ = 168 }, 
                                        { mapId = 36, mapName = "大都南", posX = 209, posZ = 156 }, 
                                        { mapId = 36, mapName = "大都南", posX = 234, posZ = 161 }, 
                                        { mapId = 36, mapName = "大都南", posX = 238 , posZ = 213 }, 
                                        { mapId = 36, mapName = "大都南", posX = 158 , posZ = 235  }, 
                                        { mapId = 36, mapName = "大都南", posX = 202 , posZ = 225  }, 
                                        { mapId = 36, mapName = "大都南", posX = 150, posZ = 235  },       
                                        { mapId = 36, mapName = "大都南", posX = 121, posZ = 230  },                                                                                
                                        { mapId = 37, mapName = "大都东", posX = 64, posZ = 49  },       
                                        { mapId = 37, mapName = "大都东", posX = 86, posZ = 118  }, 
                                        { mapId = 37, mapName = "大都东", posX = 87, posZ = 168  },       
                                        { mapId = 37, mapName = "大都东", posX = 120, posZ = 158  },
                                        { mapId = 37, mapName = "大都东", posX = 161, posZ = 198  },       
                                        { mapId = 37, mapName = "大都东", posX = 139, posZ = 240 },
                                        { mapId = 37, mapName = "大都东", posX = 116, posZ = 241  },       
                                        { mapId = 37, mapName = "大都东", posX = 106, posZ = 212  },
                                        { mapId = 37, mapName = "大都东", posX = 90, posZ = 210  },       
                                        { mapId = 37, mapName = "大都东", posX = 92, posZ = 244  },
                                        { mapId = 37, mapName = "大都东", posX = 108, posZ = 242  },       
                                        { mapId = 37, mapName = "大都东", posX = 104, posZ = 231  }, 
                                        { mapId = 37, mapName = "大都东", posX = 155, posZ = 165  },       
                                        { mapId = 37, mapName = "大都东", posX = 215, posZ = 224  },
                                        { mapId = 37, mapName = "大都东", posX = 221, posZ = 124  },       
                                        { mapId = 37, mapName = "大都东", posX = 190, posZ = 81  },
                                        { mapId = 37, mapName = "大都东", posX = 169, posZ = 135  },       
                                        { mapId = 37, mapName = "大都东", posX = 149, posZ = 95  },
                                        { mapId = 37, mapName = "大都东", posX = 130, posZ = 90  },       
                                        { mapId = 37, mapName = "大都东", posX = 121, posZ = 158  },                                        
                                        { mapId = 38, mapName = "大都西", posX = 137, posZ = 86  },       
                                        { mapId = 38, mapName = "大都西", posX = 135, posZ = 97  }, 
                                        { mapId = 38, mapName = "大都西", posX = 133, posZ = 108  },       
                                        { mapId = 38, mapName = "大都西", posX = 166, posZ = 111  },
                                        { mapId = 38, mapName = "大都西", posX = 182, posZ = 130  },       
                                        { mapId = 38, mapName = "大都西", posX = 234, posZ = 103  },
                                        { mapId = 38, mapName = "大都西", posX = 213, posZ = 179  },       
                                        { mapId = 38, mapName = "大都西", posX = 185, posZ = 167  },
                                        { mapId = 38, mapName = "大都西", posX = 147, posZ = 195  },       
                                        { mapId = 38, mapName = "大都西", posX = 160, posZ = 223  },
                                        { mapId = 38, mapName = "大都西", posX = 131, posZ = 222  },       
                                        { mapId = 38, mapName = "大都西", posX = 72, posZ = 161  }, 
                                        { mapId = 38, mapName = "大都西", posX = 33, posZ = 192  },       
                                        { mapId = 38, mapName = "大都西", posX = 89, posZ = 232  },
                                        { mapId = 38, mapName = "大都西", posX = 67, posZ = 135  },       
                                        { mapId = 38, mapName = "大都西", posX = 43, posZ = 86  },
                                        { mapId = 38, mapName = "大都西", posX = 87, posZ = 37  },       
                                        { mapId = 38, mapName = "大都西", posX = 134, posZ = 41  },
                                        { mapId = 38, mapName = "大都西", posX = 161, posZ = 74  },       
                                        { mapId = 38, mapName = "大都西", posX = 134, posZ = 107  },
}


x300330_g_MonsterTable              = {
                                        { level = 20, bossId = 3050, strName = "巨角羊"    },
                                        { level = 25, bossId = 3051, strName = "白头鸠"    },
                                        { level = 30, bossId = 3052, strName = "铁骨僵尸"  },
                                        { level = 35, bossId = 3053, strName = "毒爪蛛"    },
                                        { level = 40, bossId = 3054, strName = "狡尾狐"    },
                                        { level = 45, bossId = 3055, strName = "闪尾蝎"    },
                                        { level = 50, bossId = 3056, strName = "怒角牛"    },
                                        { level = 55, bossId = 3057, strName = "粉羽雉"    },
                                        { level = 60, bossId = 3058, strName = "长牙雪怪"  },
                                        { level = 65, bossId = 3062, strName = "黑影豹"    },
                                        { level = 70, bossId = 3063, strName = "铁鬃熊"    },
                                        { level = 75, bossId = 3064, strName = "金尾狮"    },
}
-- 怪物存活标记表
x300330_g_MonsterLive               = {
                                        { live = 0, sceneId = 50,  mapName = "楼兰王城"   }, 
                                        { live = 0, sceneId = 51,  mapName = "楼兰边塞"   }, 
                                        { live = 0, sceneId = 150, mapName = "天山王城"   }, 
                                        { live = 0, sceneId = 151, mapName = "天山边塞"   }, 
                                        { live = 0, sceneId = 250, mapName = "昆仑王城"   }, 
                                        { live = 0, sceneId = 251, mapName = "昆仑边塞"   }, 
                                        { live = 0, sceneId = 350, mapName = "敦煌王城"   }, 
                                        { live = 0, sceneId = 351, mapName = "敦煌边塞"   }, 
                                        { live = 0, sceneId = 0,   mapName = "大都"       }, 
                                        { live = 0, sceneId = 15,  mapName = "威海港"     }, 
}

-- 召怪者Id
x300330_g_CallerId      = 0
x300330_g_CountryID     = 0
x300330_g_CallerName    = ""
-- 挖掘范围，在挖掘点周围这个范围内挖掘有效
x300330_g_DigRange      = 2
-- 钱袋光效
x300330_g_MoneyBuff     = 7046
-- 宝石光效
x300330_g_GemBuff       = 7047
-- 药瓶光效
x300330_g_MedicineBuff  = 7048
-- 妖魔光效
x300330_g_MonsterBuff   = 7049	

---------------------------------------------------------------------------------------------------
--列举事件
---------------------------------------------------------------------------------------------------
function x300330_ProcEnumEvent( sceneId, selfId, NPCId, MissionId )
    --print( "*****" )
end

---------------------------------------------------------------------------------------------------
--任务入口函数
---------------------------------------------------------------------------------------------------
function x300330_ProcEventEntry(sceneId, selfId, NPCId, MissionId,nExtIdx)	--点击该任务后执行此脚本

	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300330_g_MissionId);
	if(bHaveMission > 0) then
		local bDone = x300330_CheckSubmit(sceneId, selfId, NPCId);
		if(bDone > 0) then
			if nExtIdx ~= -1 then
				x300330_DispatchCompletedInfo( sceneId, selfId, NPCId ) --完成任务显示
			end
		else
			if nExtIdx ~= -1 then
				x300330_DispatchContinueInfo( sceneId, selfId, NPCId ) --未完成任务显示
			end
		end
	else
		x300330_DispatchMissionInfo( sceneId, selfId, NPCId )	--任务信息显示
	end
end

---------------------------------------------------------------------------------------------------
--检测接受条件
---------------------------------------------------------------------------------------------------
function x300330_ProcAcceptCheck( sceneId, selfId, npcId)
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300330_g_MissionId);
	if( bHaveMission > 0) then
		return 0;
	else
		return 1;
	end
end

---------------------------------------------------------------------------------------------------
--接受条件
---------------------------------------------------------------------------------------------------
function x300330_ProcQuestAccept( sceneId, selfId, targetId, missionId)
	return 0
end

---------------------------------------------------------------------------------------------------
--放弃任务
---------------------------------------------------------------------------------------------------
function x300330_ProcQuestAbandon(sceneId, selfId, MissionId)
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300330_g_MissionId);
	if(bHaveMission > 0) then
		local misIndex = GetQuestIndexByID(sceneId, selfId, x300330_g_MissionId); 
		DelQuest(sceneId, selfId, x300330_g_MissionId)

		BeginQuestEvent( sceneId)
		AddQuestText( sceneId, x300330_g_strMissionAbandon)
		EndQuestEvent( sceneId)
		DispatchQuestTips( sceneId, selfId)
		Msg2Player( sceneId, selfId, x300330_g_strMissionAbandon, 8, 2)
	end
end

---------------------------------------------------------------------------------------------------
--检查任务是否可提交
---------------------------------------------------------------------------------------------------
function x300330_CheckSubmit(sceneId, selfId, NPCId)

	local misIndex = GetQuestIndexByID(sceneId, selfId, x300330_g_MissionId);
	return GetQuestParam(sceneId, selfId, misIndex, x300330_MP_ISCOMPLETE);

end

---------------------------------------------------------------------------------------------------
--获得奖励
---------------------------------------------------------------------------------------------------
function x300330_GetBonus( sceneId, selfId,NpcID, SelectId )

	--奖励金钱1
	if x300330_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x300330_g_BonusMoney1 )
	    Msg2Player(sceneId,selfId,format("获得银卡#{_MONEY%d}的奖励。", x300330_g_BonusMoney1),4,2)
	end

	--奖励金钱2
	if x300330_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x300330_g_BonusMoney2 )
	    Msg2Player(sceneId,selfId,format("获得银币#{_MONEY%d}的奖励。", x300330_g_BonusMoney2),4,2)
	end

	--奖励金钱1
	if x300330_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x300330_g_BonusMoney3 )
	    Msg2Player(sceneId,selfId,format("获得金卡#{_MONEY%d}的奖励。", x300330_g_BonusMoney3),4,2)
	end

	--江湖声望
	if x300330_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
		nRongYu = nRongYu + x300330_g_BonusMoney4
		SetRongYu( sceneId, selfId, nRongYu )
		Msg2Player(sceneId,selfId,format("获得江湖声望%d的奖励。", x300330_g_BonusMoney4),4,2)
	end

	--朝廷声望
	if x300330_g_BonusMoney5 > 0 then
		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + x300330_g_BonusMoney5
		SetShengWang( sceneId, selfId, nShengWang )
		Msg2Player(sceneId,selfId,format("获得朝廷声望%d的奖励。", x300330_g_BonusMoney5),4,2)
	end

	--朝廷声望
	if x300330_g_BonusMoney6 > 0 then
		AddHonor(sceneId,selfId,x300330_g_BonusMoney6)
		Msg2Player(sceneId,selfId,format("获得荣誉值%d的奖励。", x300330_g_BonusMoney6),4,2)
	end

 	--奖励固定物品
	for i, item in x300330_g_BonusItem do
 		BeginAddItem(sceneId)
		AddItem( sceneId, item.item, item.n )
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"物品栏已满，无法得到任务物品！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
    end

	--奖励可选物品
	for i, item in x300330_g_BonusChoiceItem do
	    if item.item == SelectId then
	        BeginAddItem(sceneId)
			AddItem( sceneId, item.item, item.n )
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"物品栏已满，无法得到任务物品！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end

			--获取完必，请返回，防止重复添加
			return
		end
    end

end

---------------------------------------------------------------------------------------------------
--提交任务，不管任务是否完成或是任务，显示任务继续信息或是任务完成信息
---------------------------------------------------------------------------------------------------
function x300330_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

	--判断是否有任务
	local bHaveMission = IsHaveQuestNM(sceneId, selfId, x300330_g_MissionId);
	if bHaveMission > 0 then

		local misIndex = GetQuestIndexByID(sceneId, selfId, x300330_g_MissionId)
		local completed = GetQuestParam(sceneId, selfId, misIndex, x300330_MP_ISCOMPLETE)

		if completed == 1 then
			local result = x300330_CheckPlayerBagFull(sceneId,selfId)
			if result == 1 then
		    	x300330_GetBonus( sceneId,selfId,NPCId,selectRadioId )
		    	DelQuest(sceneId, selfId, x300330_g_MissionId)
		    	
					local scriptId = -1;
					local missionId = -1;
					local randnum = random(1, 5);
					if(randnum == 1) then
						scriptId = 300761;
						missionId = 7553;
					elseif(randnum == 2) then
						scriptId = 300762;
						missionId = 7554;
					elseif(randnum == 3) then
						scriptId = 300330;
						missionId = 7581;
					elseif(randnum == 4) then
						scriptId = 300764;
						missionId = 7582;
					elseif(randnum == 5) then
						scriptId = 300765;
						missionId = 7583;
					end
					CallScriptFunction( scriptId, "OnForceAddMission", sceneId, selfId, NPCId, missionId );
			   	--end
		    else
		    	BeginQuestEvent( sceneId )
				AddQuestText( sceneId,"包裹已满！")
				EndQuestEvent()
				DispatchQuestTips(sceneId, selfId);
		    end

		else
			BeginQuestEvent( sceneId )
				AddQuestText( sceneId,"任务没有完成！")
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId);
		end
	else

		BeginQuestEvent( sceneId )
			AddQuestText( sceneId,"任务不存在，获取任务信息失败！")
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId);

		return
	end

end

---------------------------------------------------------------------------------------------------
--检查玩家包裹已满
---------------------------------------------------------------------------------------------------
function x300330_CheckPlayerBagFull( sceneId ,selfId )


	local result = 1

	local j = 0

	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满

	--普通的奖励检查
	BeginAddItem(sceneId)
	for j, item in x300330_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
    end

	local ret = EndAddItem(sceneId,selfId)
	if ret <= 0 then
		result = 0
		bAdd = 1
	end

    --奖励可选物品
	if bAdd == 0 then

		for j, item in x300330_g_BonusChoiceItem do
	        BeginAddItem(sceneId)
			AddItem( sceneId, item.item, item.n )
			local ret = EndAddItem(sceneId,selfId)
			if ret <= 0 then
				if result == 1 then
					result = 0
				end
			end
	    end
	end

	return result
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300330_DispatchMissionInfo( sceneId, selfId, NPCId )
--print( "***********" )
	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y"..x300330_g_MissionName)
		AddQuestText(sceneId,x300330_g_MissionInfo)
		AddQuestText(sceneId," ")

		--任务目标
		AddQuestText( sceneId,"#Y任务目标：")
		AddQuestText( sceneId,x300330_g_MissionTarget)
		AddQuestText( sceneId," ")

		--提示信息
		if x300330_g_MissionHelp ~= "" then

			AddQuestText(sceneId,"#Y任务提示：")
			AddQuestText(sceneId,x300330_g_MissionHelp )
			AddQuestText(sceneId," ")
		end

		--任务奖励信息

		--1、经验
		if x300330_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x300330_g_ExpBonus )
		end

		--2、金钱1
		if x300330_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x300330_g_BonusMoney1 )
		end

		--3、金钱2
		if x300330_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x300330_g_BonusMoney2 )
		end
		--4、金钱3
		if x300330_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x300330_g_BonusMoney3 )
		end

		--江湖声望
		if x300330_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x300330_g_BonusMoney4 )
		end

		--朝廷声望
		if x300330_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x300330_g_BonusMoney5 )
		end

		--荣誉值
		if x300330_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x300330_g_BonusMoney6 )
		end


		--5、固定物品
		for i, item in x300330_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	    end

		--6、可选物品
		for i, item in x300330_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	    end


	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300330_g_ScriptId, x300330_g_MissionId);
end

---------------------------------------------------------------------------------------------------
--使用铁铲挖掘，通过铁铲的脚本调用此函数
---------------------------------------------------------------------------------------------------
function x300330_OnDigbyShovel( sceneId, selfId)
    --print( "使用铁铲" )
    if IsHaveQuestNM( sceneId, selfId, x300330_g_MissionId) == 0 then
		-- BeginQuestEvent( sceneId)
		-- AddQuestText( sceneId, "您尝试地挖掘了一阵，可惜一无所得。" )
		-- EndQuestEvent( sceneId)
		-- DispatchQuestTips( sceneId, selfId)
        -- Msg2Player( sceneId, selfId, "您尝试地挖掘了一阵，可惜一无所得。", 8, 2)
        return 0
    else
        -- 检查挖掘点
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300330_g_MissionId)
        local ts = GetQuestParam( sceneId, selfId, misIndex, x300330_MP_TARGET4)
        if ts ~= sceneId then
    		BeginQuestEvent( sceneId)
    		AddQuestText( sceneId, "挖掘场景不对，您白忙活一场" )
    		EndQuestEvent( sceneId)
    		DispatchQuestTips( sceneId, selfId)
            Msg2Player( sceneId, selfId, "挖掘场景不对，您白忙活一场", 8, 2)
            return 0
        end
        local x = GetQuestParam( sceneId, selfId, misIndex, x300330_MP_TARGET2)
        local z = GetQuestParam( sceneId, selfId, misIndex, x300330_MP_TARGET3)
        local curX, curZ = GetWorldPos( sceneId, selfId)
        curX = abs( x - curX)
        curZ = abs( z - curZ)
        if curX > x300330_g_DigRange or curZ > x300330_g_DigRange then
    		BeginQuestEvent( sceneId)
    		AddQuestText( sceneId, "您尝试地挖掘了一阵，可惜一无所得" )
    		EndQuestEvent( sceneId)
    		DispatchQuestTips( sceneId, selfId)
            Msg2Player( sceneId, selfId, "您尝试地挖掘了一阵，可惜一无所得", 8, 2)
            return 0
        end
        local control = 1
        local brk = 0

        while control == 1 do 
            local irand = random( 1, 100)
            brk = 0
            local buff 	=	9011
						local buff1 =	9013
						local buff2 =	9012
            if irand <= 20 then -- 获得现银3两(20%)

            	if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
	        		BeginQuestEvent( sceneId)
	        		AddQuestText( sceneId, "在藏宝图的指引下，您得到了#R现银3两#cffcf00，恭喜恭喜。" )
	        		EndQuestEvent( sceneId)
	        		DispatchQuestTips( sceneId, selfId)
	                Msg2Player( sceneId, selfId, "在藏宝图的指引下，您得到了#R现银3两#cffcf00，恭喜恭喜。", 8, 2)
	                AddMoney( sceneId, selfId, 0, 3000)
                else
                	BeginQuestEvent( sceneId)
	        		AddQuestText( sceneId, "在藏宝图的指引下，您得到了#R银卡3两#cffcf00，恭喜恭喜。" )
	        		EndQuestEvent( sceneId)
	        		DispatchQuestTips( sceneId, selfId)
	                Msg2Player( sceneId, selfId, "在藏宝图的指引下，您得到了#R银卡3两#cffcf00，恭喜恭喜。", 8, 2)
	                AddMoney( sceneId, selfId, 1, 3000)
	            end
                -- 钱袋光效
                --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_MoneyBuff, 0)
            elseif irand > 20 and irand <= 23 then -- 玩家获得现银10两(3%)
            	if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
	        		BeginQuestEvent( sceneId)
	        		AddQuestText( sceneId, "在藏宝图的指引下，您得到了#R现银10两#cffcf00，恭喜恭喜。" )
	        		EndQuestEvent( sceneId)
	        		DispatchQuestTips( sceneId, selfId)
	                Msg2Player( sceneId, selfId, "在藏宝图的指引下，您得到了#R现银10两#cffcf00，恭喜恭喜。", 8, 2)
	                AddMoney( sceneId, selfId, 0, 10000)
	                local strName = GetName( sceneId, selfId)
               		Msg2Player( sceneId, selfId, "#cffcf00恭喜恭喜！玩家"..strName.."使用藏宝图寻宝时获得了#R10两现银#cffcf00，真是好运气啊！", 2, 1)-- 左下角
                	Msg2Player( sceneId, selfId, "#cffcf00恭喜恭喜！玩家"..strName.."使用藏宝图寻宝时获得了#R10两现银#cffcf00，真是好运气啊！", 2, 4)-- 水平滚动
	            else
	            	BeginQuestEvent( sceneId)
	        		AddQuestText( sceneId, "在藏宝图的指引下，您得到了#R银卡10两#cffcf00，恭喜恭喜。" )
	        		EndQuestEvent( sceneId)
	        		DispatchQuestTips( sceneId, selfId)
	                Msg2Player( sceneId, selfId, "在藏宝图的指引下，您得到了#R银卡10两#cffcf00，恭喜恭喜。", 8, 2)
	                AddMoney( sceneId, selfId, 1, 10000)
	            end
                -- 钱袋光效
                --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_MoneyBuff, 0)
                -- 广播
                
            elseif irand > 23 and irand <= 33 then -- 获得现银3两
            	if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
	        		BeginQuestEvent( sceneId)
	        		AddQuestText( sceneId, "在藏宝图的指引下，您得到了#R现银3两#cffcf00，恭喜恭喜。" )
	        		EndQuestEvent( sceneId)
	        		DispatchQuestTips( sceneId, selfId)
	                Msg2Player( sceneId, selfId, "在藏宝图的指引下，您得到了#R现银3两#cffcf00，恭喜恭喜。", 8, 2)
	                AddMoney( sceneId, selfId, 0, 3000)
                else 
	                BeginQuestEvent( sceneId)
	        		AddQuestText( sceneId, "在藏宝图的指引下，您得到了#R银卡3两#cffcf00，恭喜恭喜。" )
	        		EndQuestEvent( sceneId)
	        		DispatchQuestTips( sceneId, selfId)
	                Msg2Player( sceneId, selfId, "在藏宝图的指引下，您得到了#R银卡3两#cffcf00，恭喜恭喜。", 8, 2)
	                AddMoney( sceneId, selfId, 1, 3000)
                end
                -- 钱袋光效
                --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_MoneyBuff, 0)
            elseif irand > 33 and irand <= 43 then -- 获得1个无暇
                BeginAddItem( sceneId)
                if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
                	AddItem( sceneId, 11000201, 1)-- 无瑕星尘
                else
                	AddBindItem( sceneId, 11000201, 1)-- 无瑕星尘
                end
                local result = EndAddItem( sceneId, selfId)
                if result == 0 then
            		BeginQuestEvent( sceneId)
            		AddQuestText( sceneId, "背包已满，无法放入挖到的物品！" )
            		EndQuestEvent( sceneId)
            		DispatchQuestTips( sceneId, selfId)
                    DelQuest( sceneId, selfId, x300330_g_MissionId)
                    return 1
                end
        		BeginQuestEvent( sceneId)
        		AddQuestText( sceneId, "在藏宝图的指引下，您得到了#R一个#{_ITEM11000201}#cffcf00，恭喜恭喜。" )
                AddItemListToPlayer( sceneId, selfId)
        		EndQuestEvent( sceneId)
        		DispatchQuestTips( sceneId, selfId)
                Msg2Player( sceneId, selfId, "在藏宝图的指引下，您得到了#R一个#{_ITEM11000201}#cffcf00，恭喜恭喜。", 8, 2)
                --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_GemBuff, 0)
            -- elseif irand > 23 and irand <= 43 then -- 获得5个微瑕(20%)
                -- BeginAddItem( sceneId)
                -- AddItem( sceneId, 11000200, 5)-- 微瑕星尘
                -- local result = EndAddItem( sceneId, selfId)
                -- if result == 0 then
            		-- BeginQuestEvent( sceneId)
            		-- AddQuestText( sceneId, "背包已满，无法放入挖到的物品！" )
            		-- EndQuestEvent( sceneId)
            		-- DispatchQuestTips( sceneId, selfId)
                    -- DelQuest( sceneId, selfId, x300330_g_MissionId)
                    -- return 1
                -- end
        		-- BeginQuestEvent( sceneId)
        		-- AddQuestText( sceneId, "在藏宝图的指引下，您得到了#R5个#{_ITEM11000200}#cffcf00，恭喜恭喜。" )
                -- AddItemListToPlayer( sceneId, selfId)
        		-- EndQuestEvent( sceneId)
        		-- DispatchQuestTips( sceneId, selfId)
                -- Msg2Player( sceneId, selfId, "在藏宝图的指引下，您得到了#R5个#{_ITEM11000200}#cffcf00，恭喜恭喜。", 8, 2)
                -- SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_GemBuff, 0)
            elseif irand > 43 and irand <= 48 then -- 获得1个无暇(5%)
                BeginAddItem( sceneId)
                if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
                	AddItem( sceneId, 11000201, 1)-- 无瑕星尘
                else
                	AddBindItem( sceneId, 11000201, 1)-- 无瑕星尘
                end	
                local result = EndAddItem( sceneId, selfId)
                if result == 0 then
            		BeginQuestEvent( sceneId)
            		AddQuestText( sceneId, "背包已满，无法放入挖到的物品！" )
            		EndQuestEvent( sceneId)
            		DispatchQuestTips( sceneId, selfId)
                    DelQuest( sceneId, selfId, x300330_g_MissionId)
                    return 1
                end
        		BeginQuestEvent( sceneId)
        		AddQuestText( sceneId, "在藏宝图的指引下，您得到了#R一个#{_ITEM11000201}#cffcf00，恭喜恭喜。" )
                AddItemListToPlayer( sceneId, selfId)
        		EndQuestEvent( sceneId)
        		DispatchQuestTips( sceneId, selfId)
                Msg2Player( sceneId, selfId, "在藏宝图的指引下，您得到了#R一个#{_ITEM11000201}#cffcf00，恭喜恭喜。", 8, 2)
                --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_GemBuff, 0)
            elseif irand > 48 and irand <= 58 then -- 获得1级力量黄宝石，1级敏捷黄宝石，1级智力黄宝石，1级体质蓝宝石中的3个（可重复）(20%)
                local gemArray = { 14030001, 14030006, 14030011, 14040001 }
                local gemName = { "1级力量黄", "1级敏捷黄", "1级智力黄", "1级体质蓝" }
                local index = random( 1, 4)
                BeginAddItem( sceneId)
                if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
                	AddItem( sceneId, gemArray[ index], 3)
                else
                	AddBindItem( sceneId, gemArray[ index], 3)
                end	
                local result = EndAddItem( sceneId, selfId)
                if result == 0 then
            		BeginQuestEvent( sceneId)
            		AddQuestText( sceneId, "背包已满，无法放入挖到的物品！" )
            		EndQuestEvent( sceneId)
            		DispatchQuestTips( sceneId, selfId)
                    DelQuest( sceneId, selfId, x300330_g_MissionId)
                    return 1
                end
                local strTemp = format( "在藏宝图的指引下，您得到了#R3个#{_ITEM%d}#cffcf00，恭喜恭喜。", gemArray[ index] )
                AddItemListToPlayer( sceneId, selfId)
                Msg2Player( sceneId, selfId, strTemp, 8, 2)
                Msg2Player( sceneId, selfId, strTemp, 8, 3)
                --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_GemBuff, 0)
            elseif irand > 58 and irand <= 68 then -- 获得神传水晶（10%）
                BeginAddItem( sceneId)
                if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
                	AddItem( sceneId, 11000202, 1)
                else
                	AddBindItem( sceneId, 11000202, 1)
                end	
                local result = EndAddItem( sceneId, selfId)
                if result == 0 then
            		BeginQuestEvent( sceneId)
            		AddQuestText( sceneId, "背包已满，无法放入挖到的物品！" )
            		EndQuestEvent( sceneId)
            		DispatchQuestTips( sceneId, selfId)
                    DelQuest( sceneId, selfId, x300330_g_MissionId)
                    return 1
                end
                local strTemp = format( "在藏宝图的指引下，您得到了#R1个#{_ITEM%d}#cffcf00，恭喜恭喜。", 11000202)
                AddItemListToPlayer( sceneId, selfId)
                Msg2Player( sceneId, selfId, strTemp, 8, 2)
                Msg2Player( sceneId, selfId, strTemp, 8, 3)
            -- elseif irand > 68 and irand <= 73 then -- 获得潜能点书(5%)
                -- BeginAddItem( sceneId)
                -- AddItem( sceneId, 12055000, 1)-- 潜能点书
                -- local result = EndAddItem( sceneId, selfId)
                -- if result == 0 then
            		-- BeginQuestEvent( sceneId)
            		-- AddQuestText( sceneId, "背包已满，无法放入挖到的物品！" )
            		-- EndQuestEvent( sceneId)
            		-- DispatchQuestTips( sceneId, selfId)
                    -- DelQuest( sceneId, selfId, x300330_g_MissionId)
                    -- return 1
                -- end
        		-- BeginQuestEvent( sceneId)
        		-- AddQuestText( sceneId, "在藏宝图的指引下，您得到了一本潜能点书，恭喜恭喜。" )
                -- AddItemListToPlayer( sceneId, selfId)
        		-- EndQuestEvent( sceneId)
        		-- DispatchQuestTips( sceneId, selfId)
                -- Msg2Player( sceneId, selfId, "在藏宝图的指引下，您得到了一本潜能点书，恭喜恭喜。", 8, 2)
            elseif irand > 68 and irand <= 69 then -- 获得骑乘还童药(1%)
                BeginAddItem( sceneId)
                if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
                	AddItem( sceneId, 12054300, 1)-- 骑乘还童书
                else
                	AddBindItem( sceneId, 12054300, 1)-- 骑乘还童书
                end	
                local result = EndAddItem( sceneId, selfId)
                if result == 0 then
            		BeginQuestEvent( sceneId)
            		AddQuestText( sceneId, "背包已满，无法放入挖到的物品！" )
            		EndQuestEvent( sceneId)
            		DispatchQuestTips( sceneId, selfId)
                    DelQuest( sceneId, selfId, x300330_g_MissionId)
                    return 1
                end
        		BeginQuestEvent( sceneId)
        		AddQuestText( sceneId, "在藏宝图的指引下，您得到了#R一本骑乘还童书#cffcf00，恭喜恭喜。" )
                AddItemListToPlayer( sceneId, selfId)
        		EndQuestEvent( sceneId)
        		DispatchQuestTips( sceneId, selfId)
                Msg2Player( sceneId, selfId, "在藏宝图的指引下，您得到了#R一本骑乘还童书#cffcf00，恭喜恭喜。", 8, 2)
                --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_MedicineBuff, 0)
            elseif irand > 69 and irand <= 90 then -- 召唤BOSS(21%)
                if x300330_CallBoss( sceneId, selfId) == 0 then
                    brk = 1
                else
                    --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_MonsterBuff, 0)
                end
            elseif irand > 90 and irand <= 95 then -- 获得1个无暇(5%)
                BeginAddItem( sceneId)
                if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
               	 AddItem( sceneId, 11000201, 1)-- 无瑕星尘
               	else
               		AddBindItem( sceneId, 11000201, 1)-- 无瑕星尘	 
               	end	
                local result = EndAddItem( sceneId, selfId)
                if result == 0 then
            		BeginQuestEvent( sceneId)
            		AddQuestText( sceneId, "背包已满，无法放入挖到的物品！" )
            		EndQuestEvent( sceneId)
            		DispatchQuestTips( sceneId, selfId)
                    DelQuest( sceneId, selfId, x300330_g_MissionId)
                    return 1
                end
        		BeginQuestEvent( sceneId)
        		AddQuestText( sceneId, "在藏宝图的指引下，您得到了#R一个#{_ITEM11000201}#cffcf00，恭喜恭喜。" )
                AddItemListToPlayer( sceneId, selfId)
        		EndQuestEvent( sceneId)
        		DispatchQuestTips( sceneId, selfId)
                Msg2Player( sceneId, selfId, "在藏宝图的指引下，您得到了#R一个#{_ITEM11000201}#cffcf00，恭喜恭喜。", 8, 2)
                --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_GemBuff, 0)
            elseif irand > 95 and irand <= 100 then -- 挖出龙首残骸，龙身残骸，龙爪残骸和龙尾残骸中的一个(10%)
                local gemArray = { 12030022, 12030023, 12030024, 12030025 }
                local gemName = { "龙首残骸", "龙身残骸", "龙爪残骸", "龙尾残骸" }
                local index = random( 1, 4)
                BeginAddItem( sceneId)
                if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
                	AddItem( sceneId, gemArray[ index], 1)
                else
                	AddBindItem( sceneId, gemArray[ index], 1)	
                end	
                local result = EndAddItem( sceneId, selfId)
                if result == 0 then
            		BeginQuestEvent( sceneId)
            		AddQuestText( sceneId, "背包已满，无法放入挖到的物品！" )
            		EndQuestEvent( sceneId)
            		DispatchQuestTips( sceneId, selfId)
                    DelQuest( sceneId, selfId, x300330_g_MissionId)
                    return 1
                end
        		BeginQuestEvent( sceneId)
        		AddQuestText( sceneId, "在藏宝图的指引下，您得到了一个#R"..gemName[ index].."#cffcf00，恭喜恭喜。" )
                AddItemListToPlayer( sceneId, selfId)
        		EndQuestEvent( sceneId)
        		DispatchQuestTips( sceneId, selfId)
                Msg2Player( sceneId, selfId, "在藏宝图的指引下，您得到了一个#R"..gemName[ index].."#cffcf00，恭喜恭喜。", 8, 2)
                --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_MedicineBuff, 0)
            end

            control = brk
        end

        -- 删除任务
        DelQuest( sceneId, selfId, x300330_g_MissionId)
        -- 提示任务完成
        Msg2Player( sceneId, selfId, "您完成了："..x300330_g_MissionName, 8, 2)
        Msg2Player( sceneId, selfId, "您完成了："..x300330_g_MissionName, 8, 3)
        -- 写日志
        GamePlayScriptLog( sceneId, selfId, 622)
        -- 消耗铁铲可用次数
        CallScriptFunction( 300331, "LogicDeplete", sceneId, selfId)
    end

    return 1
end

---------------------------------------------------------------------------------------------------
-- 挖掘后召唤Boss
---------------------------------------------------------------------------------------------------
function x300330_CallBoss( sceneId, selfId)
    local monsters = {}
    local count = 1

    -- 根据当前场景限定选怪范围
    local maxLevel = 100
    if sceneId == 50 or sceneId == 150 or sceneId == 250 or sceneId == 350 then
        -- 王城出现的Boss最大40级
        maxLevel = 40
    elseif sceneId == 51 or sceneId == 151 or sceneId == 251 or sceneId == 351 then
        -- 边塞出现的Boss最大60级
        maxLevel = 60
    elseif sceneId == 36 or sceneId == 37 or sceneId == 38 or sceneId == 15 then
        maxLevel = 80
    end

    for i, item in x300330_g_MonsterTable do
        if item.level <= maxLevel then
            monsters[ count] = item
            count = count + 1
        end
    end

    -- 随机选取一只怪
    local i = random( 1, getn( monsters) )
    -- 如果本场景已经有玩家召唤过Boss
    for i, item in x300330_g_MonsterLive do
        if item.sceneId == sceneId and item.live == 1 then
            return 0
        end
    end

    -- 获得玩家当前位置
    local x, z = GetWorldPos( sceneId, selfId)
    local mapName = ""
    CreateMonster( sceneId, monsters[ i].bossId, x + random( 1, 3), z + random( 1, 3), 1, -1, x300330_g_ScriptId, -1, 21, 30*60*1000)
    -- 更新Boss存活标记
    for i, item in x300330_g_MonsterLive do
        if item.sceneId == sceneId then
            x300330_g_MonsterLive[ i].live = 1
            mapName = item.mapName
        end
    end

    Msg2Player( sceneId, selfId, "你一阵挖掘，却看见一道黑光从地下冒出，出现在了你的身边。", 8, 2)
    Msg2Player( sceneId, selfId, "你一阵挖掘，却看见一道黑光从地下冒出，出现在了你的身边。", 8, 3)
    -- 广播
    local name = GetName( sceneId, selfId)
    local broadcast = "#e010101#cFF7903玩家#G"..name.."#e010101#cFF7903在使用藏宝图寻宝的过程中不小心把妖兽给放了出来，现在妖兽在#S"..mapName.."#e010101#cFF7903附近游荡，请大家快快前往消灭。"
    LuaAllScenceM2Country( sceneId, broadcast, GetCurCountry( sceneId, selfId), 0, 1)
    LuaAllScenceM2Country( sceneId, broadcast, GetCurCountry( sceneId, selfId), 4, 1)

    return 1
end

---------------------------------------------------------------------------------------------------
-- 挖掘后随机产生的怪被杀后调用此函数
---------------------------------------------------------------------------------------------------
function x300330_OnDie( sceneId, selfId, killerId)

    
--    GetCountryQuestDataNM(sceneId,x300330_g_CallerId,x300330_g_CountryID,CD_INDEX_MISSION_CAOBAOTU,x300330_g_ScriptId,-1,"OnCreaterGetBonus")

    --广播相关信息
    --ThisScenceM2Country( sceneId, x300330_g_CountryID, "恭喜恭喜！玩家"..x300330_g_CallerName.."使用藏宝图寻宝时获得了#R10两银卡#cffcf00，真是好运气啊！", 2, 1)-- 左下角
    --ThisScenceM2Country( sceneId, x300330_g_CountryID, "恭喜恭喜！玩家"..x300330_g_CallerName.."使用藏宝图寻宝时获得了#R10两银卡#cffcf00，真是好运气啊！", 3, 1)-- 水平滚动

    for i, item in x300330_g_MonsterLive do
        if item.sceneId == sceneId then
            x300330_g_MonsterLive[ i].live = 0
        end
    end

    x300330_g_CountryID = 0
    x300330_g_CallerId = 0    
    x300330_g_CallerName = ""

end

---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300330_DispatchContinueInfo( sceneId, selfId, NPCId )
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300330_DispatchCompletedInfo( sceneId, selfId, NPCId )
end

---------------------------------------------------------------------------------------------------
--怪物被杀的消息处理
---------------------------------------------------------------------------------------------------
function x300330_ProcQuestObjectKilled(sceneId, selfId, objdataId ,objId, MissionId )
end

---------------------------------------------------------------------------------------------------
--物品改变
---------------------------------------------------------------------------------------------------
function x300330_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

---------------------------------------------------------------------------------------------------
--单击NPC事件
---------------------------------------------------------------------------------------------------
function x300330_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
end

---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300330_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300330_g_MissionId)
    local mapId = GetQuestParam( sceneId, selfId, misIndex, x300330_MP_TARGET1)
    local targetId = GetQuestParam( sceneId, selfId, misIndex, x300330_MP_TARGET4)
    local x = GetQuestParam( sceneId, selfId, misIndex, x300330_MP_TARGET2)
    local z = GetQuestParam( sceneId, selfId, misIndex, x300330_MP_TARGET3)
    local strMapName = ""

    if mapId == 0 then
        strMapName = "王国"
    elseif mapId == 1 then
        strMapName = "边塞"
    elseif mapId == 2 then
        strMapName = "大都"
    elseif mapId == 3 then
        strMapName = "威海港"
    elseif mapId == 36 then
        strMapName = "大都南"        
    elseif mapId == 37 then
        strMapName = "大都东"        
    elseif mapId == 38 then
        strMapName = "大都西"        
    end

    

	BeginQuestEvent(sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                             -- 标题
                                x300330_g_MissionName,             -- 任务名字
                                format( x300330_g_MissionTarget, targetId, x, z,strMapName,x,z),
                                "无",                             --任务NPC
                                x300330_g_MissionHelp,
                                format( x300330_g_MissionInfo, targetId, x, z,strMapName,x,z),
                                "" )

	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

---------------------------------------------------------------------------------------------------
--强行加任务，玩家右键点击藏宝图后调用此函数
---------------------------------------------------------------------------------------------------
function x300330_OnForceAddMission( sceneId, selfId, npcId, MissionId)
	if( MissionId ~= x300330_g_MissionId) then
		return 0;
	end

	-- print( "*********" )
	if(x300330_ProcAcceptCheck( sceneId, selfId, -1 ) ~= 1) then
		return 0;
	end
	local ret = AddQuest( sceneId, selfId, x300330_g_MissionId, x300330_g_ScriptId, 0, 0, 0, 0)
	if(ret == 0) then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"任务已满，任务接受失败！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
    else
        -- 显示任务接受信息
        BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "您获得了任务：【个人】藏宝图的秘密" )
        EndQuestEvent( sceneId)
        DispatchQuestTips( sceneId, selfId)
        Msg2Player( sceneId, selfId, "您获得了任务：【个人】藏宝图的秘密", 8, 2)
	end

		local guo = GetCurCountry(sceneId,selfId)
		if guo ==0 then
	    -- 随机选取挖掘点
	    local size = getn( x300330_g_MissionTargetTable0)
	    local i = random( 1, size)
	    -- 如果玩家等级小于40级，则只能领取王国的挖掘点
	    if GetLevel( sceneId, selfId) < 40 then
	        i = random( 1, 100)
	    end
	
	    local misIndex = GetQuestIndexByID(sceneId, selfId, x300330_g_MissionId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET1, x300330_g_MissionTargetTable0[ i].mapId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET2, x300330_g_MissionTargetTable0[ i].posX)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET3, x300330_g_MissionTargetTable0[ i].posZ)
	    local mapId = GetCurCountry( sceneId, selfId) * 100 + x300330_g_MissionTargetTable0[ i].mapId + 50
	    if x300330_g_MissionTargetTable0[ i].mapId == 2 then
	        mapId = 0
	    elseif x300330_g_MissionTargetTable0[ i].mapId == 3 then
	        mapId = 15
	    elseif x300330_g_MissionTargetTable0[ i].mapId == 36 then
	        mapId = 36	        
	    elseif x300330_g_MissionTargetTable0[ i].mapId == 37 then
	        mapId = 37	                
	    elseif x300330_g_MissionTargetTable0[ i].mapId == 38 then
	        mapId = 38       
	    end
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET4, mapId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_ISCOMPLETE, 0)
	    -- 写日志
	    GamePlayScriptLog( sceneId, selfId, 621)
	    return 1
	    
	    
	    elseif guo ==1 then
	    -- 随机选取挖掘点
	    local size = getn( x300330_g_MissionTargetTable1)
	    local i = random( 1, size)
	    -- 如果玩家等级小于40级，则只能领取王国的挖掘点
	    if GetLevel( sceneId, selfId) < 40 then
	        i = random( 1, 100)
	    end
	
	    local misIndex = GetQuestIndexByID(sceneId, selfId, x300330_g_MissionId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET1, x300330_g_MissionTargetTable1[ i].mapId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET2, x300330_g_MissionTargetTable1[ i].posX)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET3, x300330_g_MissionTargetTable1[ i].posZ)
	    local mapId = GetCurCountry( sceneId, selfId) * 100 + x300330_g_MissionTargetTable1[ i].mapId + 50
	    if x300330_g_MissionTargetTable1[ i].mapId == 2 then
	        mapId = 0
	    elseif x300330_g_MissionTargetTable1[ i].mapId == 3 then
	        mapId = 15
	    elseif x300330_g_MissionTargetTable1[ i].mapId == 36 then
	        mapId = 36	        
	    elseif x300330_g_MissionTargetTable1[ i].mapId == 37 then
	        mapId = 37	                
	    elseif x300330_g_MissionTargetTable1[ i].mapId == 38 then
	        mapId = 38 	        
	    end
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET4, mapId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_ISCOMPLETE, 0)
	    -- 写日志
	    GamePlayScriptLog( sceneId, selfId, 621)
	    return 1
	    
	    
	    elseif guo ==2 then
	    -- 随机选取挖掘点
	    local size = getn( x300330_g_MissionTargetTable2)
	    local i = random( 1, size)
	    -- 如果玩家等级小于40级，则只能领取王国的挖掘点
	    if GetLevel( sceneId, selfId) < 40 then
	        i = random( 1, 100)
	    end
	
	    local misIndex = GetQuestIndexByID(sceneId, selfId, x300330_g_MissionId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET1, x300330_g_MissionTargetTable2[ i].mapId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET2, x300330_g_MissionTargetTable2[ i].posX)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET3, x300330_g_MissionTargetTable2[ i].posZ)
	    local mapId = GetCurCountry( sceneId, selfId) * 100 + x300330_g_MissionTargetTable2[ i].mapId + 50
	    if x300330_g_MissionTargetTable2[ i].mapId == 2 then
	        mapId = 0
	    elseif x300330_g_MissionTargetTable2[ i].mapId == 3 then
	        mapId = 15
	    elseif x300330_g_MissionTargetTable2[ i].mapId == 36 then
	        mapId = 36	        
	    elseif x300330_g_MissionTargetTable2[ i].mapId == 37 then
	        mapId = 37	                
	    elseif x300330_g_MissionTargetTable2[ i].mapId == 38 then
	        mapId = 38 	        
	    end
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET4, mapId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_ISCOMPLETE, 0)
	    -- 写日志
	    GamePlayScriptLog( sceneId, selfId, 621)
	    return 1
	    
	    
	    elseif guo ==3 then
	    -- 随机选取挖掘点
	    local size = getn( x300330_g_MissionTargetTable3)
	    local i = random( 1, size)
	    -- 如果玩家等级小于40级，则只能领取王国的挖掘点
	    if GetLevel( sceneId, selfId) < 40 then
	        i = random( 1, 100)
	    end
	
	    local misIndex = GetQuestIndexByID(sceneId, selfId, x300330_g_MissionId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET1, x300330_g_MissionTargetTable3[ i].mapId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET2, x300330_g_MissionTargetTable3[ i].posX)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET3, x300330_g_MissionTargetTable3[ i].posZ)
	    local mapId = GetCurCountry( sceneId, selfId) * 100 + x300330_g_MissionTargetTable3[ i].mapId + 50
	    if x300330_g_MissionTargetTable3[ i].mapId == 2 then
	        mapId = 0
	    elseif x300330_g_MissionTargetTable3[ i].mapId == 3 then
	        mapId = 15
	    elseif x300330_g_MissionTargetTable3[ i].mapId == 36 then
	        mapId = 36	        
	    elseif x300330_g_MissionTargetTable3[ i].mapId == 37 then
	        mapId = 37	                
	    elseif x300330_g_MissionTargetTable3[ i].mapId == 38 then
	        mapId = 38 	        
	    end
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET4, mapId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_ISCOMPLETE, 0)
	    -- 写日志
	    GamePlayScriptLog( sceneId, selfId, 621)
	
	    return 1
	  end
	    
end

-----------------------------------------------------------------------------
--给创建怪物的玩家奖励
-----------------------------------------------------------------------------
function x300330_OnCreaterGetBonus(sceneId,guid,missiondata)

    local nCastGuid = NumberCastIntToUInt(guid)
    
    --先找到玩家
    local selfId = -1
    local nHumanCount = GetScenePlayerCount( sceneId )
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local objGUID = GetPlayerGUID(sceneId, objId )
            if objGUID == nCastGuid then
                selfId = objId
                break
            end
        end
    end

    if selfId == -1 then
        return
    end

    --给奖励，并给出相关提示
    local xp = GetLevel( sceneId, selfId) * 500
    AddExp( sceneId, selfId, xp)

    local strMsg = format("您放出的怪已经被消灭，因此您获得%d点经验", xp)

    local name = GetName(sceneId,selfId)
    LuaScenceM2Player(sceneId,selfId,strMsg,name,2,1)
    LuaScenceM2Player(sceneId,selfId,strMsg,name,3,1)

end

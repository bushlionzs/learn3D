--注意：

--物品技能的逻辑只能使用基础技能和脚本来实现

--脚本:

--以下是脚本样例:


--3001.lua
------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号
x417000_g_scriptId = 417000 --临时写这个,真正用的时候一定要改.
x417000_g_MissionId = {2707,2708,2709,2710,2711,2712,3099,3100,3101,3102,3103,3104,1663,1664,1665,1666,1667,1668,3062,3769,3770,3771,3772,3773,3774,3775,3776,3777,3778,3779,3780,3369,3370,3371,3372,3373,3374,3375,3376,3377,3378,3379,3380,3462,3463,3464,3465,3466,3467,3468,3469,3470,3471,3472,3473,3269,3270,3271,3272,3273,3274,3275,3276,3277,3278,3279,3280,4204,4205,4206,4207,4264,4265,4266,4267,4268,4269,4270,4271,4272,4273,4274,4275,4276,4277,4278,4279,4280,4281,4282,4283,4284,4285,4286,4287,4288,4289,4290,4291,4292,4293,4294,4295,4296,4297,4298,4299,4300,4301,4302,4303,4304,4305,4306,4307,4308,4309,4310,4311,4312,4313,4314,4315,4316,4317,4318,4319,4320,4321,4322,4323,4324,4325,4326,4327,4328,4329,4330,4331,4332,4333,4334,4335,4336,4337,4338,4339,4340,4341,4342,4343,4344,4345,4346,4347,4348,4349,4350,4351,4352,4353,4354,4355,4356,4357,4358,4359}
-------------------ID  	1			2		3			4		5			6			7		8		9			10	11		12	13	14		15		16	17		18	19		20	21		22	23		24	25		26	27		28	29		30	31		32	33		34	35		36	37	38		39		40	41		42	43		44	45		46	47		48	49	50		51		52	53	54		55	56		57		58	59		60	61		62	63		64	65		66	67		68	69		70	71	72		73	74		75 		76	77		78	79		80	81	82		83	84		85		86	87		88	89		90	91		92	93		94	95		96	97		98	99	100		101	102		103	104		105	106		107	108		109	110		111	112		113	114		115	116		117	118		119	120		121	122		123	124		125	126		127	128		129	130	131		132		133	134		135	136		137	138		139	140		141	142		143	144		145	146		147	148		149	150		151	152		153	154		155	156		157	158		159	160	161		162		163	164		165	166		167
--需要的等级

--效果的ID
x417000_g_Impact1 = 8001 --临时写这个
x417000_g_Impact2 = -1 --不用

--**********************************
--事件交互入口
--**********************************
function x417000_ProcEventEntry( sceneId, selfId, bagIndex,rorf )
        
        --检查玩家状态是否正常
        if IsPlayerStateNormal( sceneId,selfId) ~= 1 then
            return
        end
        
        local misIndex = GetQuestIndexByID( sceneId, selfId, x417000_g_MissionId[1] )
		if rorf==0 then
			if IsHaveQuest(sceneId,selfId, x417000_g_MissionId[1]) > 0 then
						--misIndex = GetQuestIndexByID( sceneId, selfId, x417000_g_MissionId[1] )
						--SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						--SetQuestByIndex(sceneId,selfId,misIndex,0,1)
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[2]) > 0 then
						--misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[2] )
						--SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						--SetQuestByIndex(sceneId,selfId,misIndex,0,1)
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[3]) > 0 then
						--misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[3] )
						--SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						--SetQuestByIndex(sceneId,selfId,misIndex,0,1)
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[4]) > 0 then
						--misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[4] )
						--SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						--SetQuestByIndex(sceneId,selfId,misIndex,0,1)
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[5]) > 0 then
						--misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[5] )
						--SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						--SetQuestByIndex(sceneId,selfId,misIndex,0,1)
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[6]) > 0 then
						--misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[6] )
						--SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						--SetQuestByIndex(sceneId,selfId,misIndex,0,1)
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[7]) > 0 then
					if bagIndex	>1321 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[7] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[8]) > 0 then
					if bagIndex	>2081 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[8] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[9]) > 0 then
					if bagIndex	>3091 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[9] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[10]) > 0 then
					if bagIndex	>4091 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[10] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[11]) > 0 then
					if bagIndex	>5081 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[11] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[12]) > 0 then
--			print(11)
					if bagIndex	>6101 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[12] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[13]) > 0 then
					if bagIndex	>1322 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[13] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[14]) > 0 then
					if bagIndex	>2082 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[14] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[15]) > 0 then
					if bagIndex	>3092 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[15] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[16]) > 0 then
					if bagIndex	>4092 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[16] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[17]) > 0 then
					if bagIndex	>5082 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[17] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[18]) > 0 then
--			print(11)
					if bagIndex	>6102 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[18] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
					elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[20]) > 0 then
					if bagIndex	>1321 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[20] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[21]) > 0 then
					if bagIndex	>2081 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[21] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[22]) > 0 then
					if bagIndex	>3091 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[22] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[23]) > 0 then
					if bagIndex	>4091 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[23] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[24]) > 0 then
					if bagIndex	>5081 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[24] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[25]) > 0 then
--			print(11)
					if bagIndex	>6101 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[25] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[26]) > 0 then
					if bagIndex	>17040 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[26] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[27]) > 0 then
					if bagIndex	>18080 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[27] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[28]) > 0 then
					if bagIndex	>19070 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[28] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[29]) > 0 then
					if bagIndex	>20070 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[29] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[30]) > 0 then
					if bagIndex	>21060 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[30] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[31]) > 0 then
--			print(11)
					if bagIndex	>22080 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[31] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
		  elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[32]) > 0 then
					if bagIndex	>1321 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[32] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[33]) > 0 then
					if bagIndex	>2081 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[33] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[34]) > 0 then
					if bagIndex	>3091 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[34] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[35]) > 0 then
					if bagIndex	>4091 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[35] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[36]) > 0 then
					if bagIndex	>5081 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[36] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[37]) > 0 then
--			print(11)
					if bagIndex	>6101 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[37] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[38]) > 0 then
					if bagIndex	>17040 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[38] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[39]) > 0 then
					if bagIndex	>18080 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[39] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[40]) > 0 then
					if bagIndex	>19070 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[40] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[41]) > 0 then
					if bagIndex	>20070 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[41] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[42]) > 0 then
					if bagIndex	>21060 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[42] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[43]) > 0 then
--			print(11)
					if bagIndex	>22080 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[43] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[44]) > 0 then
					if bagIndex	>1321 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[44] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[45]) > 0 then
					if bagIndex	>2081 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[45] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[46]) > 0 then
					if bagIndex	>3091 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[46] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[47]) > 0 then
					if bagIndex	>4091 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[47] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[48]) > 0 then
					if bagIndex	>5081 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[48] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[49]) > 0 then
--			print(11)
					if bagIndex	>6101 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[49] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[50]) > 0 then
					if bagIndex	>17040 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[50] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[51]) > 0 then
					if bagIndex	>18080 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[51] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[52]) > 0 then
					if bagIndex	>19070 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[52] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[53]) > 0 then
					if bagIndex	>20070 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[53] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[54]) > 0 then
					if bagIndex	>21060 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[54] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[55]) > 0 then
--			print(11)
					if bagIndex	>22080 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[55] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end		
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[56]) > 0 then
					if bagIndex	>1321 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[56] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[57]) > 0 then
					if bagIndex	>2081 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[57] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[58]) > 0 then
					if bagIndex	>3091 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[58] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[59]) > 0 then
					if bagIndex	>4091 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[59] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[60]) > 0 then
					if bagIndex	>5081 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[60] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[61]) > 0 then
--			print(11)
					if bagIndex	>6101 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[61] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[62]) > 0 then
					if bagIndex	>17040 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[62] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[63]) > 0 then
					if bagIndex	>18080 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[63] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[64]) > 0 then
					if bagIndex	>19070 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[64] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[65]) > 0 then
					if bagIndex	>20070 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[65] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[66]) > 0 then
					if bagIndex	>21060 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[66] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[67]) > 0 then
--			print(11)
					if bagIndex	>22080 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[67] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end	
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[72]) > 0 then
					if bagIndex	>1322 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[72] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[73]) > 0 then
					if bagIndex	>2082 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[73] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[74]) > 0 then
					if bagIndex	>3092 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[74] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[75]) > 0 then
					if bagIndex	>4092 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[75] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[76]) > 0 then
					if bagIndex	>5082 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[76] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[77]) > 0 then
--			print(11)
					if bagIndex	>6102 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[77] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[78]) > 0 then
					if bagIndex	>17041 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[78] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[79]) > 0 then
					if bagIndex	>18081 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[79] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[80]) > 0 then
					if bagIndex	>19071 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[80] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[81]) > 0 then
					if bagIndex	>20071 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[81] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[82]) > 0 then
					if bagIndex	>21061 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[82] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[83]) > 0 then
--			print(11)
					if bagIndex	>22081 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[83] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end		
				end
--天山20级技能引导
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[84]) > 0 then
					if bagIndex	>1322 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[84] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[85]) > 0 then
					if bagIndex	>2082 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[85] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[86]) > 0 then
					if bagIndex	>3092 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[86] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[87]) > 0 then
					if bagIndex	>4092 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[87] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[88]) > 0 then
					if bagIndex	>5082 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[88] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[89]) > 0 then
--			print(11)
					if bagIndex	>6102 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[89] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[90]) > 0 then
					if bagIndex	>17041 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[90] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[91]) > 0 then
					if bagIndex	>18081 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[91] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[92]) > 0 then
					if bagIndex	>19071 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[92] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[93]) > 0 then
					if bagIndex	>20071 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[93] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[94]) > 0 then
					if bagIndex	>21061 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[94] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[95]) > 0 then
--			print(11)
					if bagIndex	>22081 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[95] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end		
			end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[96]) > 0 then
					if bagIndex	>1322 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[96] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[97]) > 0 then
					if bagIndex	>2082 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[97] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[98]) > 0 then
					if bagIndex	>3092 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[98] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[99]) > 0 then
					if bagIndex	>4092 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[99] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[100]) > 0 then
					if bagIndex	>5082 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[100] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[101]) > 0 then
--			print(11)
					if bagIndex	>6102 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[101] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[102]) > 0 then
					if bagIndex	>17041 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[102] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[103]) > 0 then
					if bagIndex	>18081 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[103] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[104]) > 0 then
					if bagIndex	>19071 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[104] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[105]) > 0 then
					if bagIndex	>20071 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[105] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[106]) > 0 then
					if bagIndex	>21061 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[106] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[107]) > 0 then
--			print(11)
					if bagIndex	>22081 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[107] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end		
			end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[108]) > 0 then
					if bagIndex	>1322 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[108] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[109]) > 0 then
					if bagIndex	>2082 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[109] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[110]) > 0 then
					if bagIndex	>3092 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[110] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[111]) > 0 then
					if bagIndex	>4092 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[111] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[112]) > 0 then
					if bagIndex	>5082 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[112] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[113]) > 0 then
--			print(11)
					if bagIndex	>6102 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[113] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[114]) > 0 then
					if bagIndex	>17041 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[114] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[115]) > 0 then
					if bagIndex	>18081 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[115] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[116]) > 0 then
					if bagIndex	>19071 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[116] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[117]) > 0 then
					if bagIndex	>20071 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[117] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[118]) > 0 then
					if bagIndex	>21061 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[118] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[119]) > 0 then
--			print(11)
					if bagIndex	>22081 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[119] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end		
			end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[120]) > 0 then
					if bagIndex	>1323 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[120] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[121]) > 0 then
					if bagIndex	>2083 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[121] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[122]) > 0 then
					if bagIndex	>3093 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[122] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[123]) > 0 then
					if bagIndex	>4093 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[123] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[124]) > 0 then
					if bagIndex	>5083 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[124] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[125]) > 0 then
--			print(11)
					if bagIndex	>6103 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[125] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[126]) > 0 then
					if bagIndex	>17042 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[126] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[127]) > 0 then
					if bagIndex	>18082 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[127] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[128]) > 0 then
					if bagIndex	>19072 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[128] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[129]) > 0 then
					if bagIndex	>20072 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[129] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[130]) > 0 then
					if bagIndex	>21062 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[130] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[131]) > 0 then
--			print(11)
					if bagIndex	>22082 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[131] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end		
			end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[132]) > 0 then
					if bagIndex	>1323 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[132] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[133]) > 0 then
					if bagIndex	>2083 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[133] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[134]) > 0 then
					if bagIndex	>3093 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[134] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[135]) > 0 then
					if bagIndex	>4093 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[135] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[136]) > 0 then
					if bagIndex	>5083 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[136] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[137]) > 0 then
--			print(11)
					if bagIndex	>6103 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[137] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[138]) > 0 then
					if bagIndex	>17042 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[138] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[139]) > 0 then
					if bagIndex	>18082 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[139] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[140]) > 0 then
					if bagIndex	>19072 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[140] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[141]) > 0 then
					if bagIndex	>20072 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[141] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[142]) > 0 then
					if bagIndex	>21062 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[142] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[143]) > 0 then
--			print(11)
					if bagIndex	>22082 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[143] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end		
			end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[144]) > 0 then
					if bagIndex	>1323 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[144] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[145]) > 0 then
					if bagIndex	>2083 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[145] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[146]) > 0 then
					if bagIndex	>3093 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[146] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[147]) > 0 then
					if bagIndex	>4093 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[147] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[148]) > 0 then
					if bagIndex	>5083 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[148] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[149]) > 0 then
--			print(11)
					if bagIndex	>6103 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[149] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[150]) > 0 then
					if bagIndex	>17042 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[150] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[151]) > 0 then
					if bagIndex	>18082 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[151] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[152]) > 0 then
					if bagIndex	>19072 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[152] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[153]) > 0 then
					if bagIndex	>20072 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[153] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[154]) > 0 then
					if bagIndex	>21062 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[154] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[155]) > 0 then
--			print(11)
					if bagIndex	>22082 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[155] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end		
			end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[156]) > 0 then
					if bagIndex	>1323 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[156] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[157]) > 0 then
					if bagIndex	>2083 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[157] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[158]) > 0 then
					if bagIndex	>3093 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[158] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[159]) > 0 then
					if bagIndex	>4093 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[159] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[160]) > 0 then
					if bagIndex	>5083 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[160] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[161]) > 0 then
--			print(11)
					if bagIndex	>6103 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[161] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[162]) > 0 then
					if bagIndex	>17042 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[162] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[163]) > 0 then
					if bagIndex	>18082 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[163] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[164]) > 0 then
					if bagIndex	>19072 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[164] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[165]) > 0 then
					if bagIndex	>20072 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[165] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[166]) > 0 then
					if bagIndex	>21062 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[166] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[167]) > 0 then
--			print(11)
					if bagIndex	>22082 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[167] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end		
			end
			end
			if IsHaveQuest(sceneId,selfId, x417000_g_MissionId[19]) > 0 then
		
					if bagIndex	>=7510 then
						if bagIndex	<=7511 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[19] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 41,0 )
						end
					end
					--下面四个是khan2领双引导任务，对应任务4204,4205,4206,4207			
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[68]) > 0 then
		
					if bagIndex	>=7510 then
						if bagIndex	<=7511 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[68] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 41,0 )
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[69]) > 0 then
		
					if bagIndex	>=7510 then
						if bagIndex	<=7511 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[69] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 41,0 )
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[70]) > 0 then
		
					if bagIndex	>=7510 then
						if bagIndex	<=7511 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[70] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 41,0 )
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[71]) > 0 then
		
					if bagIndex	>=7510 then
						if bagIndex	<=7511 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[71] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 41,0 )
						end
					end	
			end		
			
			elseif rorf==1 then
			if IsHaveQuest(sceneId,selfId, x417000_g_MissionId[1]) > 0 then
						--misIndex = GetQuestIndexByID( sceneId, selfId, x417000_g_MissionId[1] )
						--SetQuestByIndex(sceneId,selfId,misIndex,7,0)
						--SetQuestByIndex(sceneId,selfId,misIndex,0,0)
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[2]) > 0 then
						--misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[2] )
						--SetQuestByIndex(sceneId,selfId,misIndex,7,0)
						--SetQuestByIndex(sceneId,selfId,misIndex,0,0)
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[3]) > 0 then
						--misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[3] )
						--SetQuestByIndex(sceneId,selfId,misIndex,7,0)
						--SetQuestByIndex(sceneId,selfId,misIndex,0,0)
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[4]) > 0 then
						--misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[4] )
						--SetQuestByIndex(sceneId,selfId,misIndex,7,0)
						--SetQuestByIndex(sceneId,selfId,misIndex,0,0)
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[5]) > 0 then
						--misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[5] )
						--SetQuestByIndex(sceneId,selfId,misIndex,7,0)
						--SetQuestByIndex(sceneId,selfId,misIndex,0,0)
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[6]) > 0 then
						--misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[6] )
						--SetQuestByIndex(sceneId,selfId,misIndex,7,0)
						--SetQuestByIndex(sceneId,selfId,misIndex,0,0)
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[7]) > 0 then
					if bagIndex	>1321 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[7] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,0)
						SetQuestByIndex(sceneId,selfId,misIndex,0,0)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[8]) > 0 then
					if bagIndex	>2081 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[8] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,0)
						SetQuestByIndex(sceneId,selfId,misIndex,0,0)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[9]) > 0 then
					if bagIndex	>3091 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[9] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,0)
						SetQuestByIndex(sceneId,selfId,misIndex,0,0)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[10]) > 0 then
					if bagIndex	>4091 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[10] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,0)
						SetQuestByIndex(sceneId,selfId,misIndex,0,0)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[11]) > 0 then
					if bagIndex	>5081 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[11] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,0)
						SetQuestByIndex(sceneId,selfId,misIndex,0,0)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[12]) > 0 then
					if bagIndex	>6101 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[12] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,0)
						SetQuestByIndex(sceneId,selfId,misIndex,0,0)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[13]) > 0 then
					if bagIndex	>1322 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[13] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[14]) > 0 then
					if bagIndex	>2082 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[14] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[15]) > 0 then
					if bagIndex	>3092 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[15] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[16]) > 0 then
					if bagIndex	>4092 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[16] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[17]) > 0 then
					if bagIndex	>5082 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[17] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[18]) > 0 then
--			print(11)
					if bagIndex	>6102 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[18] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[20]) > 0 then
					if bagIndex	>1321 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[20] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[21]) > 0 then
					if bagIndex	>2081 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[21] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[22]) > 0 then
					if bagIndex	>3091 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[22] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[23]) > 0 then
					if bagIndex	>4091 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[23] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[24]) > 0 then
					if bagIndex	>5081 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[24] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[25]) > 0 then
--			print(11)
					if bagIndex	>6101 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[25] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[26]) > 0 then
					if bagIndex	>17040 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[26] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[27]) > 0 then
					if bagIndex	>18080 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[27] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[28]) > 0 then
					if bagIndex	>19070 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[28] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[29]) > 0 then
					if bagIndex	>20070 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[29] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[30]) > 0 then
					if bagIndex	>21060 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[30] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[31]) > 0 then
--			print(11)
					if bagIndex	>22080 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[31] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
				elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[32]) > 0 then
					if bagIndex	>1321 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[32] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[33]) > 0 then
					if bagIndex	>2081 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[33] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[34]) > 0 then
					if bagIndex	>3091 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[34] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[35]) > 0 then
					if bagIndex	>4091 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[35] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[36]) > 0 then
					if bagIndex	>5081 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[36] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[37]) > 0 then
--			print(11)
					if bagIndex	>6101 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[37] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[38]) > 0 then
					if bagIndex	>17040 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[38] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[39]) > 0 then
					if bagIndex	>18080 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[39] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[40]) > 0 then
					if bagIndex	>19070 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[40] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[41]) > 0 then
					if bagIndex	>20070 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[41] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[42]) > 0 then
					if bagIndex	>21060 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[42] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[43]) > 0 then
--			print(11)
					if bagIndex	>22080 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[43] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[44]) > 0 then
					if bagIndex	>1321 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[44] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[45]) > 0 then
					if bagIndex	>2081 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[45] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[46]) > 0 then
					if bagIndex	>3091 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[46] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[47]) > 0 then
					if bagIndex	>4091 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[47] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[48]) > 0 then
					if bagIndex	>5081 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[48] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[49]) > 0 then
--			print(11)
					if bagIndex	>6101 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[49] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[50]) > 0 then
					if bagIndex	>17040 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[50] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[51]) > 0 then
					if bagIndex	>18080 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[51] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[52]) > 0 then
					if bagIndex	>19070 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[52] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[53]) > 0 then
					if bagIndex	>20070 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[53] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[54]) > 0 then
					if bagIndex	>21060 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[54] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[55]) > 0 then
--			print(11)
					if bagIndex	>22080 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[55] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end		
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[56]) > 0 then
					if bagIndex	>1321 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[56] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[57]) > 0 then
					if bagIndex	>2081 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[57] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[58]) > 0 then
					if bagIndex	>3091 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[58] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[59]) > 0 then
					if bagIndex	>4091 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[59] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[60]) > 0 then
					if bagIndex	>5081 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[60] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[61]) > 0 then
--			print(11)
					if bagIndex	>6101 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[61] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[62]) > 0 then
					if bagIndex	>17040 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[62] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[63]) > 0 then
					if bagIndex	>18080 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[63] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[64]) > 0 then
					if bagIndex	>19070 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[64] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[65]) > 0 then
					if bagIndex	>20070 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[65] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[66]) > 0 then
					if bagIndex	>21060 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[66] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[67]) > 0 then
--			print(11)
					if bagIndex	>22080 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[67] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[72]) > 0 then
					if bagIndex	>1322 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[72] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[73]) > 0 then
					if bagIndex	>2082 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[73] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[74]) > 0 then
					if bagIndex	>3092 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[74] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[75]) > 0 then
					if bagIndex	>4092 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[75] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[76]) > 0 then
					if bagIndex	>5082 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[76] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[77]) > 0 then
--			print(11)
					if bagIndex	>6102 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[77] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[78]) > 0 then
					if bagIndex	>17041 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[78] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[79]) > 0 then
					if bagIndex	>18081 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[79] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[80]) > 0 then
					if bagIndex	>19071 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[80] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[81]) > 0 then
					if bagIndex	>20071 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[81] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[82]) > 0 then
					if bagIndex	>21061 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[82] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[83]) > 0 then
--			print(11)
					if bagIndex	>22081 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[83] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end		
				end
--天山20级技能引导
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[84]) > 0 then
					if bagIndex	>1322 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[84] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[85]) > 0 then
					if bagIndex	>2082 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[85] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[86]) > 0 then
					if bagIndex	>3092 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[86] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[87]) > 0 then
					if bagIndex	>4092 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[87] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[88]) > 0 then
					if bagIndex	>5082 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[88] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[89]) > 0 then
--			print(11)
					if bagIndex	>6102 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[89] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[90]) > 0 then
					if bagIndex	>17041 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[90] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[91]) > 0 then
					if bagIndex	>18081 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[91] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[92]) > 0 then
					if bagIndex	>19071 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[92] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[93]) > 0 then
					if bagIndex	>20071 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[93] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[94]) > 0 then
					if bagIndex	>21061 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[94] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[95]) > 0 then
--			print(11)
					if bagIndex	>22081 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[95] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end		
			end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[96]) > 0 then
					if bagIndex	>1322 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[96] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[97]) > 0 then
					if bagIndex	>2082 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[97] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[98]) > 0 then
					if bagIndex	>3092 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[98] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[99]) > 0 then
					if bagIndex	>4092 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[99] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[100]) > 0 then
					if bagIndex	>5082 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[100] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[101]) > 0 then
--			print(11)
					if bagIndex	>6102 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[101] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[102]) > 0 then
					if bagIndex	>17041 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[102] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[103]) > 0 then
					if bagIndex	>18081 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[103] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[104]) > 0 then
					if bagIndex	>19071 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[104] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[105]) > 0 then
					if bagIndex	>20071 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[105] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[106]) > 0 then
					if bagIndex	>21061 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[106] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[107]) > 0 then
--			print(11)
					if bagIndex	>22081 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[107] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end		
			end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[108]) > 0 then
					if bagIndex	>1322 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[108] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[109]) > 0 then
					if bagIndex	>2082 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[109] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[110]) > 0 then
					if bagIndex	>3092 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[110] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[111]) > 0 then
					if bagIndex	>4092 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[111] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[112]) > 0 then
					if bagIndex	>5082 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[112] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[113]) > 0 then
--			print(11)
					if bagIndex	>6102 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[113] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[114]) > 0 then
					if bagIndex	>17041 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[114] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[115]) > 0 then
					if bagIndex	>18081 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[115] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[116]) > 0 then
					if bagIndex	>19071 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[116] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[117]) > 0 then
					if bagIndex	>20071 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[117] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[118]) > 0 then
					if bagIndex	>21061 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[118] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[119]) > 0 then
--			print(11)
					if bagIndex	>22081 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[119] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end		
			end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[120]) > 0 then
					if bagIndex	>1323 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[120] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[121]) > 0 then
					if bagIndex	>2083 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[121] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[122]) > 0 then
					if bagIndex	>3093 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[122] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[123]) > 0 then
					if bagIndex	>4093 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[123] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[124]) > 0 then
					if bagIndex	>5083 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[124] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[125]) > 0 then
--			print(11)
					if bagIndex	>6103 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[125] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[126]) > 0 then
					if bagIndex	>17042 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[126] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[127]) > 0 then
					if bagIndex	>18082 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[127] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[128]) > 0 then
					if bagIndex	>19072 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[128] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[129]) > 0 then
					if bagIndex	>20072 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[129] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[130]) > 0 then
					if bagIndex	>21062 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[130] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[131]) > 0 then
--			print(11)
					if bagIndex	>22082 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[131] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end		
			end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[132]) > 0 then
					if bagIndex	>1323 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[132] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[133]) > 0 then
					if bagIndex	>2083 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[133] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[134]) > 0 then
					if bagIndex	>3093 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[134] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[135]) > 0 then
					if bagIndex	>4093 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[135] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[136]) > 0 then
					if bagIndex	>5083 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[136] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[137]) > 0 then
--			print(11)
					if bagIndex	>6103 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[137] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[138]) > 0 then
					if bagIndex	>17042 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[138] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[139]) > 0 then
					if bagIndex	>18082 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[139] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[140]) > 0 then
					if bagIndex	>19072 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[140] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[141]) > 0 then
					if bagIndex	>20072 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[141] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[142]) > 0 then
					if bagIndex	>21062 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[142] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[143]) > 0 then
--			print(11)
					if bagIndex	>22082 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[143] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end		
			end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[144]) > 0 then
					if bagIndex	>1323 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[144] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[145]) > 0 then
					if bagIndex	>2083 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[145] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[146]) > 0 then
					if bagIndex	>3093 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[146] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[147]) > 0 then
					if bagIndex	>4093 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[147] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[148]) > 0 then
					if bagIndex	>5083 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[148] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[149]) > 0 then
--			print(11)
					if bagIndex	>6103 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[149] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[150]) > 0 then
					if bagIndex	>17042 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[150] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[151]) > 0 then
					if bagIndex	>18082 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[151] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[152]) > 0 then
					if bagIndex	>19072 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[152] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[153]) > 0 then
					if bagIndex	>20072 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[153] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[154]) > 0 then
					if bagIndex	>21062 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[154] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[155]) > 0 then
--			print(11)
					if bagIndex	>22082 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[155] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end		
			end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[156]) > 0 then
					if bagIndex	>1323 then
						if bagIndex	<=1330 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[156] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[157]) > 0 then
					if bagIndex	>2083 then
						if bagIndex	<=2090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[157] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[158]) > 0 then
					if bagIndex	>3093 then
						if bagIndex	<=3100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[158] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[159]) > 0 then
					if bagIndex	>4093 then
						if bagIndex	<=4100 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[159] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[160]) > 0 then
					if bagIndex	>5083 then
						if bagIndex	<=5090 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[160] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[161]) > 0 then
--			print(11)
					if bagIndex	>6103 then
						if bagIndex	<=6110 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[161] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[162]) > 0 then
					if bagIndex	>17042 then
						if bagIndex	<=17049 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[162] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[163]) > 0 then
					if bagIndex	>18082 then
						if bagIndex	<=18089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[163] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[164]) > 0 then
					if bagIndex	>19072 then
						if bagIndex	<=19079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[164] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[165]) > 0 then
					if bagIndex	>20072 then
						if bagIndex	<=20079 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[165] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[166]) > 0 then
					if bagIndex	>21062 then
						if bagIndex	<=21069 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[166] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
			elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[167]) > 0 then
--			print(11)
					if bagIndex	>22082 then
						if bagIndex	<=22089 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[167] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end		
			end
	end
	if IsHaveQuest(sceneId,selfId, x417000_g_MissionId[19]) > 0 then
					if bagIndex	>=	7510 then
						if bagIndex	<=	7511 then
						misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[19] )
						SetQuestByIndex(sceneId,selfId,misIndex,7,0)
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						end
					end
	--下面四个是khan2领双引导任务，对应任务4204,4205,4206,4207			
	elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[68]) > 0 then

			if bagIndex	>=7510 then
				if bagIndex	<=7511 then
				misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[68] )
				SetQuestByIndex(sceneId,selfId,misIndex,7,1)
				SetQuestByIndex(sceneId,selfId,misIndex,0,1)
				CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 41,0 )
				end
			end
	elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[69]) > 0 then

			if bagIndex	>=7510 then
				if bagIndex	<=7511 then
				misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[69] )
				SetQuestByIndex(sceneId,selfId,misIndex,7,1)
				SetQuestByIndex(sceneId,selfId,misIndex,0,1)
				CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 41,0 )
				end
			end
	elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[70]) > 0 then

			if bagIndex	>=7510 then
				if bagIndex	<=7511 then
				misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[70] )
				SetQuestByIndex(sceneId,selfId,misIndex,7,1)
				SetQuestByIndex(sceneId,selfId,misIndex,0,1)
				CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 41,0 )
				end
			end
	elseif IsHaveQuest(sceneId,selfId, x417000_g_MissionId[71]) > 0 then

			if bagIndex	>=7510 then
				if bagIndex	<=7511 then
				misIndex = GetQuestIndexByID( sceneId, selfId,  x417000_g_MissionId[71] )
				SetQuestByIndex(sceneId,selfId,misIndex,7,1)
				SetQuestByIndex(sceneId,selfId,misIndex,0,1)
				CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 41,0 )
				end
			end	
	end				
	end				
-- 不需要这个接口，但要保留空函数
end

--**********************************
--这个物品的使用过程是否类似于技能：
--系统会在执行开始时检测这个函数的返回值，如果返回失败则忽略后面的类似技能的执行。
--返回1：技能类似的物品，可以继续类似技能的执行；返回0：忽略后面的操作。
--**********************************
function x417000_IsSkillLikeScript( sceneId, selfId)
	return 1; --这个脚本需要动作支持
end

--**********************************
--直接取消效果：
--系统会直接调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：已经取消对应效果，不再执行后续操作；返回0：没有检测到相关效果，继续执行。
--**********************************
function x417000_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

--**********************************
--条件检测入口：
--系统会在技能检测的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：条件检测通过，可以继续执行；返回0：条件检测失败，中断后续执行。
--**********************************
function x417000_OnConditionCheck( sceneId, selfId )
	--校验使用的物品
	--if(1~=VerifyUsedItem(sceneId, selfId)) then
		--return 0
	--end
	--return 1; --不需要任何条件，并且始终返回1。
end

--**********************************
--消耗检测及处理入口：
--系统会在技能消耗的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：消耗处理通过，可以继续执行；返回0：消耗检测失败，中断后续执行。
--注意：这不光负责消耗的检测也负责消耗的执行。
--**********************************
function x417000_OnDeplete( sceneId, selfId )
	--if(DepletingUsedItem(sceneId, selfId)) then
		--return 1;
	--end
	--return 0;
end

--**********************************
--只会执行一次入口：
--聚气和瞬发技能会在消耗完成后调用这个接口（聚气结束并且各种条件都满足的时候），而引导
--技能也会在消耗完成后调用这个接口（技能的一开始，消耗成功执行之后）。
--返回1：处理成功；返回0：处理失败。
--注：这里是技能生效一次的入口
--**********************************
function x417000_OnActivateOnce( sceneId, selfId )
	--if(-1~=x417000_g_Impact1) then
		--SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x417000_g_Impact1, 0);
	--end
	--return 1;
end

--**********************************
--引导心跳处理入口：
--引导技能会在每次心跳结束时调用这个接口。
--返回：1继续下次心跳；0：中断引导。
--注：这里是技能生效一次的入口
--**********************************
function x417000_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end

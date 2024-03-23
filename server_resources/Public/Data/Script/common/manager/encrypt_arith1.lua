
x800101_g_ScriptId = 800101
x800101_g_MissionName = "加密算法集"

--加密算法函数集
x800101_g_FunctionList =	{
								0,1,2,3,4,5,6,7,8,9,
								10,11,12,13,14,15,16,17,18,19,
								20,21,22,23,24,25,26,27,28,29,
								30,31,32,33,34,35,36,37,38,39,
								40,41,42,43,44,45,46,47,48,49,
								50,51,52,53,54,55,56,57,58,59,
								60,61,62,63,64,65,66,67,68,69,
								70,71,72,73,74,75,76,77,78,79,
								80,81,82,83,84,85,86,87,88,89,
								90,91,92,93,94,95,96,97,98,99,
							}

--加密算法规则集
x800101_g_RulerList =	{ 
							0,	--加法
							1,	--减法
							2,	--乘法
							3,	--除法: 工具要注意检测除数为0的情况
						}

--点击（NPC）
function x800101_ProcEnumEvent( sceneId, selfId, targetId, MissionId )	
end



--点击（按钮）点击该任务后执行此脚本
function x800101_ProcEventEntry( sceneId, selfId, targetId,state,index )	
end


function x800101_OnEncryptArith1( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[82]
	local fn2 = x800101_g_FunctionList[62]
	local fn3 = x800101_g_FunctionList[26]
	local fn4 = x800101_g_FunctionList[96]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith2( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[45]
	local fn2 = x800101_g_FunctionList[54]
	local fn3 = x800101_g_FunctionList[3]
	local fn4 = x800101_g_FunctionList[66]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith3( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[90]
	local fn2 = x800101_g_FunctionList[66]
	local fn3 = x800101_g_FunctionList[48]
	local fn4 = x800101_g_FunctionList[43]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith4( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[90]
	local fn2 = x800101_g_FunctionList[45]
	local fn3 = x800101_g_FunctionList[76]
	local fn4 = x800101_g_FunctionList[36]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith5( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[55]
	local fn2 = x800101_g_FunctionList[43]
	local fn3 = x800101_g_FunctionList[72]
	local fn4 = x800101_g_FunctionList[27]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith6( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[36]
	local fn2 = x800101_g_FunctionList[54]
	local fn3 = x800101_g_FunctionList[75]
	local fn4 = x800101_g_FunctionList[23]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[3]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith7( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[44]
	local fn2 = x800101_g_FunctionList[9]
	local fn3 = x800101_g_FunctionList[70]
	local fn4 = x800101_g_FunctionList[51]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith8( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[34]
	local fn2 = x800101_g_FunctionList[48]
	local fn3 = x800101_g_FunctionList[27]
	local fn4 = x800101_g_FunctionList[45]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith9( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[54]
	local fn2 = x800101_g_FunctionList[55]
	local fn3 = x800101_g_FunctionList[36]
	local fn4 = x800101_g_FunctionList[73]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[3]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith10( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[95]
	local fn2 = x800101_g_FunctionList[41]
	local fn3 = x800101_g_FunctionList[8]
	local fn4 = x800101_g_FunctionList[46]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[3]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith11( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[77]
	local fn2 = x800101_g_FunctionList[37]
	local fn3 = x800101_g_FunctionList[100]
	local fn4 = x800101_g_FunctionList[61]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith12( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[45]
	local fn2 = x800101_g_FunctionList[12]
	local fn3 = x800101_g_FunctionList[90]
	local fn4 = x800101_g_FunctionList[48]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith13( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[85]
	local fn2 = x800101_g_FunctionList[31]
	local fn3 = x800101_g_FunctionList[34]
	local fn4 = x800101_g_FunctionList[66]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith14( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[30]
	local fn2 = x800101_g_FunctionList[74]
	local fn3 = x800101_g_FunctionList[86]
	local fn4 = x800101_g_FunctionList[73]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith15( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[69]
	local fn2 = x800101_g_FunctionList[97]
	local fn3 = x800101_g_FunctionList[37]
	local fn4 = x800101_g_FunctionList[100]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[3]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith16( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[17]
	local fn2 = x800101_g_FunctionList[46]
	local fn3 = x800101_g_FunctionList[97]
	local fn4 = x800101_g_FunctionList[9]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[4]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith17( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[51]
	local fn2 = x800101_g_FunctionList[7]
	local fn3 = x800101_g_FunctionList[96]
	local fn4 = x800101_g_FunctionList[97]

	local ruler1 = x800101_g_RulerList[1]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[3]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith18( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[34]
	local fn2 = x800101_g_FunctionList[31]
	local fn3 = x800101_g_FunctionList[14]
	local fn4 = x800101_g_FunctionList[26]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[4]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith19( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[9]
	local fn2 = x800101_g_FunctionList[38]
	local fn3 = x800101_g_FunctionList[47]
	local fn4 = x800101_g_FunctionList[4]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[3]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith20( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[82]
	local fn2 = x800101_g_FunctionList[76]
	local fn3 = x800101_g_FunctionList[68]
	local fn4 = x800101_g_FunctionList[55]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith21( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[31]
	local fn2 = x800101_g_FunctionList[56]
	local fn3 = x800101_g_FunctionList[62]
	local fn4 = x800101_g_FunctionList[85]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[3]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith22( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[40]
	local fn2 = x800101_g_FunctionList[97]
	local fn3 = x800101_g_FunctionList[70]
	local fn4 = x800101_g_FunctionList[4]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith23( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[12]
	local fn2 = x800101_g_FunctionList[7]
	local fn3 = x800101_g_FunctionList[64]
	local fn4 = x800101_g_FunctionList[2]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith24( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[59]
	local fn2 = x800101_g_FunctionList[96]
	local fn3 = x800101_g_FunctionList[45]
	local fn4 = x800101_g_FunctionList[94]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith25( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[4]
	local fn2 = x800101_g_FunctionList[100]
	local fn3 = x800101_g_FunctionList[14]
	local fn4 = x800101_g_FunctionList[5]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[4]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith26( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[72]
	local fn2 = x800101_g_FunctionList[99]
	local fn3 = x800101_g_FunctionList[2]
	local fn4 = x800101_g_FunctionList[88]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[4]
	local ruler3 = x800101_g_RulerList[3]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith27( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[68]
	local fn2 = x800101_g_FunctionList[31]
	local fn3 = x800101_g_FunctionList[74]
	local fn4 = x800101_g_FunctionList[5]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith28( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[96]
	local fn2 = x800101_g_FunctionList[79]
	local fn3 = x800101_g_FunctionList[61]
	local fn4 = x800101_g_FunctionList[87]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[4]
	local ruler3 = x800101_g_RulerList[3]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith29( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[100]
	local fn2 = x800101_g_FunctionList[71]
	local fn3 = x800101_g_FunctionList[56]
	local fn4 = x800101_g_FunctionList[26]

	local ruler1 = x800101_g_RulerList[1]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith30( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[74]
	local fn2 = x800101_g_FunctionList[20]
	local fn3 = x800101_g_FunctionList[40]
	local fn4 = x800101_g_FunctionList[12]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith31( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[9]
	local fn2 = x800101_g_FunctionList[22]
	local fn3 = x800101_g_FunctionList[54]
	local fn4 = x800101_g_FunctionList[61]

	local ruler1 = x800101_g_RulerList[1]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith32( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[23]
	local fn2 = x800101_g_FunctionList[5]
	local fn3 = x800101_g_FunctionList[76]
	local fn4 = x800101_g_FunctionList[20]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith33( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[83]
	local fn2 = x800101_g_FunctionList[25]
	local fn3 = x800101_g_FunctionList[95]
	local fn4 = x800101_g_FunctionList[64]

	local ruler1 = x800101_g_RulerList[1]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith34( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[43]
	local fn2 = x800101_g_FunctionList[30]
	local fn3 = x800101_g_FunctionList[65]
	local fn4 = x800101_g_FunctionList[81]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith35( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[44]
	local fn2 = x800101_g_FunctionList[74]
	local fn3 = x800101_g_FunctionList[72]
	local fn4 = x800101_g_FunctionList[30]

	local ruler1 = x800101_g_RulerList[1]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith36( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[89]
	local fn2 = x800101_g_FunctionList[62]
	local fn3 = x800101_g_FunctionList[47]
	local fn4 = x800101_g_FunctionList[39]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith37( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[4]
	local fn2 = x800101_g_FunctionList[64]
	local fn3 = x800101_g_FunctionList[37]
	local fn4 = x800101_g_FunctionList[28]

	local ruler1 = x800101_g_RulerList[1]
	local ruler2 = x800101_g_RulerList[4]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith38( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[32]
	local fn2 = x800101_g_FunctionList[54]
	local fn3 = x800101_g_FunctionList[32]
	local fn4 = x800101_g_FunctionList[36]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith39( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[74]
	local fn2 = x800101_g_FunctionList[35]
	local fn3 = x800101_g_FunctionList[23]
	local fn4 = x800101_g_FunctionList[76]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith40( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[51]
	local fn2 = x800101_g_FunctionList[3]
	local fn3 = x800101_g_FunctionList[40]
	local fn4 = x800101_g_FunctionList[54]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[3]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith41( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[65]
	local fn2 = x800101_g_FunctionList[48]
	local fn3 = x800101_g_FunctionList[21]
	local fn4 = x800101_g_FunctionList[31]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith42( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[80]
	local fn2 = x800101_g_FunctionList[90]
	local fn3 = x800101_g_FunctionList[68]
	local fn4 = x800101_g_FunctionList[23]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith43( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[93]
	local fn2 = x800101_g_FunctionList[60]
	local fn3 = x800101_g_FunctionList[88]
	local fn4 = x800101_g_FunctionList[19]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith44( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[22]
	local fn2 = x800101_g_FunctionList[94]
	local fn3 = x800101_g_FunctionList[12]
	local fn4 = x800101_g_FunctionList[28]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith45( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[52]
	local fn2 = x800101_g_FunctionList[49]
	local fn3 = x800101_g_FunctionList[52]
	local fn4 = x800101_g_FunctionList[90]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[4]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith46( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[18]
	local fn2 = x800101_g_FunctionList[46]
	local fn3 = x800101_g_FunctionList[45]
	local fn4 = x800101_g_FunctionList[24]

	local ruler1 = x800101_g_RulerList[1]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith47( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[99]
	local fn2 = x800101_g_FunctionList[20]
	local fn3 = x800101_g_FunctionList[27]
	local fn4 = x800101_g_FunctionList[11]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[3]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith48( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[67]
	local fn2 = x800101_g_FunctionList[80]
	local fn3 = x800101_g_FunctionList[23]
	local fn4 = x800101_g_FunctionList[39]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith49( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[2]
	local fn2 = x800101_g_FunctionList[73]
	local fn3 = x800101_g_FunctionList[30]
	local fn4 = x800101_g_FunctionList[65]

	local ruler1 = x800101_g_RulerList[1]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith50( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[69]
	local fn2 = x800101_g_FunctionList[33]
	local fn3 = x800101_g_FunctionList[51]
	local fn4 = x800101_g_FunctionList[38]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith51( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[90]
	local fn2 = x800101_g_FunctionList[53]
	local fn3 = x800101_g_FunctionList[59]
	local fn4 = x800101_g_FunctionList[20]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[4]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith52( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[23]
	local fn2 = x800101_g_FunctionList[2]
	local fn3 = x800101_g_FunctionList[45]
	local fn4 = x800101_g_FunctionList[3]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[4]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith53( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[20]
	local fn2 = x800101_g_FunctionList[47]
	local fn3 = x800101_g_FunctionList[25]
	local fn4 = x800101_g_FunctionList[69]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith54( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[99]
	local fn2 = x800101_g_FunctionList[29]
	local fn3 = x800101_g_FunctionList[38]
	local fn4 = x800101_g_FunctionList[98]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith55( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[28]
	local fn2 = x800101_g_FunctionList[11]
	local fn3 = x800101_g_FunctionList[53]
	local fn4 = x800101_g_FunctionList[7]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith56( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[9]
	local fn2 = x800101_g_FunctionList[29]
	local fn3 = x800101_g_FunctionList[79]
	local fn4 = x800101_g_FunctionList[86]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[4]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith57( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[19]
	local fn2 = x800101_g_FunctionList[87]
	local fn3 = x800101_g_FunctionList[54]
	local fn4 = x800101_g_FunctionList[18]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith58( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[16]
	local fn2 = x800101_g_FunctionList[33]
	local fn3 = x800101_g_FunctionList[89]
	local fn4 = x800101_g_FunctionList[49]

	local ruler1 = x800101_g_RulerList[1]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith59( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[43]
	local fn2 = x800101_g_FunctionList[43]
	local fn3 = x800101_g_FunctionList[24]
	local fn4 = x800101_g_FunctionList[91]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[4]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith60( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[97]
	local fn2 = x800101_g_FunctionList[77]
	local fn3 = x800101_g_FunctionList[53]
	local fn4 = x800101_g_FunctionList[83]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith61( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[72]
	local fn2 = x800101_g_FunctionList[26]
	local fn3 = x800101_g_FunctionList[22]
	local fn4 = x800101_g_FunctionList[29]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith62( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[45]
	local fn2 = x800101_g_FunctionList[71]
	local fn3 = x800101_g_FunctionList[69]
	local fn4 = x800101_g_FunctionList[12]

	local ruler1 = x800101_g_RulerList[1]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[3]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith63( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[43]
	local fn2 = x800101_g_FunctionList[29]
	local fn3 = x800101_g_FunctionList[73]
	local fn4 = x800101_g_FunctionList[84]

	local ruler1 = x800101_g_RulerList[1]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith64( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[64]
	local fn2 = x800101_g_FunctionList[7]
	local fn3 = x800101_g_FunctionList[82]
	local fn4 = x800101_g_FunctionList[31]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith65( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[33]
	local fn2 = x800101_g_FunctionList[55]
	local fn3 = x800101_g_FunctionList[35]
	local fn4 = x800101_g_FunctionList[2]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith66( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[92]
	local fn2 = x800101_g_FunctionList[10]
	local fn3 = x800101_g_FunctionList[8]
	local fn4 = x800101_g_FunctionList[40]

	local ruler1 = x800101_g_RulerList[1]
	local ruler2 = x800101_g_RulerList[4]
	local ruler3 = x800101_g_RulerList[3]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith67( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[43]
	local fn2 = x800101_g_FunctionList[84]
	local fn3 = x800101_g_FunctionList[51]
	local fn4 = x800101_g_FunctionList[53]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[4]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith68( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[25]
	local fn2 = x800101_g_FunctionList[2]
	local fn3 = x800101_g_FunctionList[73]
	local fn4 = x800101_g_FunctionList[66]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[4]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith69( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[94]
	local fn2 = x800101_g_FunctionList[47]
	local fn3 = x800101_g_FunctionList[100]
	local fn4 = x800101_g_FunctionList[21]

	local ruler1 = x800101_g_RulerList[1]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[3]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith70( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[49]
	local fn2 = x800101_g_FunctionList[85]
	local fn3 = x800101_g_FunctionList[22]
	local fn4 = x800101_g_FunctionList[51]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[4]
	local ruler3 = x800101_g_RulerList[3]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith71( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[4]
	local fn2 = x800101_g_FunctionList[89]
	local fn3 = x800101_g_FunctionList[47]
	local fn4 = x800101_g_FunctionList[12]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith72( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[60]
	local fn2 = x800101_g_FunctionList[40]
	local fn3 = x800101_g_FunctionList[50]
	local fn4 = x800101_g_FunctionList[87]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[3]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith73( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[43]
	local fn2 = x800101_g_FunctionList[30]
	local fn3 = x800101_g_FunctionList[14]
	local fn4 = x800101_g_FunctionList[37]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith74( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[61]
	local fn2 = x800101_g_FunctionList[24]
	local fn3 = x800101_g_FunctionList[43]
	local fn4 = x800101_g_FunctionList[46]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith75( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[25]
	local fn2 = x800101_g_FunctionList[67]
	local fn3 = x800101_g_FunctionList[67]
	local fn4 = x800101_g_FunctionList[10]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith76( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[41]
	local fn2 = x800101_g_FunctionList[26]
	local fn3 = x800101_g_FunctionList[75]
	local fn4 = x800101_g_FunctionList[54]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[4]
	local ruler3 = x800101_g_RulerList[3]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith77( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[93]
	local fn2 = x800101_g_FunctionList[35]
	local fn3 = x800101_g_FunctionList[21]
	local fn4 = x800101_g_FunctionList[5]

	local ruler1 = x800101_g_RulerList[1]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith78( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[94]
	local fn2 = x800101_g_FunctionList[66]
	local fn3 = x800101_g_FunctionList[58]
	local fn4 = x800101_g_FunctionList[40]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith79( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[19]
	local fn2 = x800101_g_FunctionList[25]
	local fn3 = x800101_g_FunctionList[83]
	local fn4 = x800101_g_FunctionList[63]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith80( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[18]
	local fn2 = x800101_g_FunctionList[37]
	local fn3 = x800101_g_FunctionList[21]
	local fn4 = x800101_g_FunctionList[90]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith81( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[14]
	local fn2 = x800101_g_FunctionList[94]
	local fn3 = x800101_g_FunctionList[70]
	local fn4 = x800101_g_FunctionList[47]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[4]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith82( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[15]
	local fn2 = x800101_g_FunctionList[32]
	local fn3 = x800101_g_FunctionList[49]
	local fn4 = x800101_g_FunctionList[62]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith83( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[52]
	local fn2 = x800101_g_FunctionList[16]
	local fn3 = x800101_g_FunctionList[53]
	local fn4 = x800101_g_FunctionList[12]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith84( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[8]
	local fn2 = x800101_g_FunctionList[66]
	local fn3 = x800101_g_FunctionList[85]
	local fn4 = x800101_g_FunctionList[94]

	local ruler1 = x800101_g_RulerList[1]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith85( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[98]
	local fn2 = x800101_g_FunctionList[8]
	local fn3 = x800101_g_FunctionList[1]
	local fn4 = x800101_g_FunctionList[18]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[3]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith86( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[57]
	local fn2 = x800101_g_FunctionList[28]
	local fn3 = x800101_g_FunctionList[83]
	local fn4 = x800101_g_FunctionList[100]

	local ruler1 = x800101_g_RulerList[1]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith87( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[51]
	local fn2 = x800101_g_FunctionList[74]
	local fn3 = x800101_g_FunctionList[27]
	local fn4 = x800101_g_FunctionList[75]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith88( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[39]
	local fn2 = x800101_g_FunctionList[24]
	local fn3 = x800101_g_FunctionList[68]
	local fn4 = x800101_g_FunctionList[44]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith89( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[55]
	local fn2 = x800101_g_FunctionList[30]
	local fn3 = x800101_g_FunctionList[70]
	local fn4 = x800101_g_FunctionList[95]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith90( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[22]
	local fn2 = x800101_g_FunctionList[97]
	local fn3 = x800101_g_FunctionList[42]
	local fn4 = x800101_g_FunctionList[68]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith91( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[38]
	local fn2 = x800101_g_FunctionList[54]
	local fn3 = x800101_g_FunctionList[59]
	local fn4 = x800101_g_FunctionList[54]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith92( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[96]
	local fn2 = x800101_g_FunctionList[84]
	local fn3 = x800101_g_FunctionList[90]
	local fn4 = x800101_g_FunctionList[89]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith93( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[56]
	local fn2 = x800101_g_FunctionList[1]
	local fn3 = x800101_g_FunctionList[15]
	local fn4 = x800101_g_FunctionList[82]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[4]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith94( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[72]
	local fn2 = x800101_g_FunctionList[70]
	local fn3 = x800101_g_FunctionList[8]
	local fn4 = x800101_g_FunctionList[21]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith95( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[3]
	local fn2 = x800101_g_FunctionList[66]
	local fn3 = x800101_g_FunctionList[77]
	local fn4 = x800101_g_FunctionList[39]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[4]
	local ruler3 = x800101_g_RulerList[3]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith96( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[15]
	local fn2 = x800101_g_FunctionList[17]
	local fn3 = x800101_g_FunctionList[65]
	local fn4 = x800101_g_FunctionList[27]

	local ruler1 = x800101_g_RulerList[4]
	local ruler2 = x800101_g_RulerList[3]
	local ruler3 = x800101_g_RulerList[3]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith97( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[57]
	local fn2 = x800101_g_FunctionList[61]
	local fn3 = x800101_g_FunctionList[1]
	local fn4 = x800101_g_FunctionList[46]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith98( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[93]
	local fn2 = x800101_g_FunctionList[37]
	local fn3 = x800101_g_FunctionList[8]
	local fn4 = x800101_g_FunctionList[91]

	local ruler1 = x800101_g_RulerList[1]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[1]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith99( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[78]
	local fn2 = x800101_g_FunctionList[63]
	local fn3 = x800101_g_FunctionList[91]
	local fn4 = x800101_g_FunctionList[99]

	local ruler1 = x800101_g_RulerList[2]
	local ruler2 = x800101_g_RulerList[1]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

function x800101_OnEncryptArith100( sceneId, selfId, enctyptId1 )

	local fn1 = x800101_g_FunctionList[53]
	local fn2 = x800101_g_FunctionList[45]
	local fn3 = x800101_g_FunctionList[61]
	local fn4 = x800101_g_FunctionList[96]

	local ruler1 = x800101_g_RulerList[3]
	local ruler2 = x800101_g_RulerList[2]
	local ruler3 = x800101_g_RulerList[2]

	SendEncryptMsg( sceneId, selfId, enctyptId1, fn1,fn2,fn3,fn4,ruler1,ruler2,ruler3 )

end

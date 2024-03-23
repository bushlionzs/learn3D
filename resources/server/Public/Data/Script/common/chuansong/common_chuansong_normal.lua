--传送模块


x800019_g_BusMaxFollowDist = 10		--BUS跟随的最大有效距离 



--组队跟随状态下，队长传送时整个组队也将被传送
function	x800019_TransferFunc(sceneId, selfId, newSceneId, PosX, PosZ)
	--print("传送这里?")
	--如果玩家没有处于组队状态,则直接传送
	local life=IsCharacterLiving( sceneId,selfId)
	if	life==0	then
		return
	else
		if	GetTeamId( sceneId, selfId)<0	then
			local InBus = IsBusMember(sceneId, selfId)
			if InBus == 1 then
				--print("???")
				local BusId = GetBusId(sceneId, selfId)
				local IsLeader = IsTheBusLeader(sceneId, selfId,BusId)   	--司机才可以操作BUS跨场景 
				local InDist =IsInDist(sceneId, selfId,BusId,x800019_g_BusMaxFollowDist)     
				if InDist == 1 and IsLeader == 1 then
					x800019_BusTransfer(sceneId,BusId,newSceneId, PosX, PosZ)
				else	
					if sceneId == newSceneId then
						SetPos(sceneId, selfId,PosX,PosZ)
					else
						if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
						end
						NewWorld(sceneId, selfId, newSceneId, PosX, PosZ, 800019)
					end							
				end

			else 
				if sceneId == newSceneId then
					SetPos(sceneId, selfId,PosX,PosZ)
				else
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
						return
					end
					NewWorld(sceneId, selfId, newSceneId, PosX, PosZ, 800019)
				end
			end
		--如果玩家处于组队状态但不处于组队跟随状态,则直接传送
		elseif	IsTeamFollow(sceneId, selfId)~=1	then
			local InBus = IsBusMember(sceneId, selfId)
			if InBus == 1 then
				local BusId = GetBusId(sceneId, selfId)
				local IsLeader = IsTheBusLeader(sceneId, selfId,BusId)   	--司机才可以操作BUS跨场景 
				local InDist = IsInDist(sceneId, selfId,BusId,x800019_g_BusMaxFollowDist)
				if InDist == 1 and IsLeader == 1 then
					x800019_BusTransfer(sceneId,BusId,newSceneId, PosX, PosZ)
				else	
					if sceneId == newSceneId then
						SetPos(sceneId, selfId,PosX,PosZ)
					else
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
						return
					end
						NewWorld(sceneId, selfId, newSceneId, PosX, PosZ, 800019)
					end							
				end			

			else 
				if sceneId == newSceneId then
					SetPos(sceneId, selfId,PosX,PosZ)
				else
						if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
						end
					NewWorld(sceneId, selfId, newSceneId, PosX, PosZ, 800019)
				end
			end
		--如果玩家处于组队跟随状态,且玩家是队长,则小队传送
		elseif	IsTeamLeader(sceneId,selfId)==1	 then
			local num=GetFollowedMembersCount( sceneId, selfId)
			local mems = {}
			for	i=0,num-1 do
				mems[i] = GetFollowedMember(sceneId, selfId, i)
				if mems[i] == -1 then
					return
				end
			end
			
			if sceneId == newSceneId then
				for	i=0,num-1 do
					SetPos(sceneId, mems[i],PosX,PosZ)
				end
			else

				for	i=0,num-1 do
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,mems[i],newSceneId) ~= 0 then
						NewWorld(sceneId, mems[i], newSceneId, PosX, PosZ, 800019)
					end		
					
				end
			end
		--如果玩家处于组队跟随状态,且不是队长,则……可以发条消息也好啊
		end
	end
end


function	x800019_BusTransfer(sceneId,BusId,newSceneId, posX, posY)
--	print("战车这里?")
	local num = GetBusMemberCount(sceneId, BusId)
	--if num <= 0 then
	--	return
	--end
	if sceneId == newSceneId then
		--同地图战车的传送
		SetPos(sceneId, BusId,posX,posY)
	else
		--注意：此步骤是必需的.BUS切换场景，要先做些准备工作,
		ReadyBusChangeScene(sceneId, newSceneId,BusId)
		
		for	i=0,num-1 do
			local ObjID = GetBusMemberObjId(sceneId,BusId,i)
			if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,ObjID,newSceneId) == 0 then
						return
			end
			NewWorld(sceneId, ObjID, newSceneId, posX, posY, 800019)
		end
		
		--删除BUS,但乘员仍在车上
		DeleteBus(sceneId, BusId,0)		
	end
end

--用一个数组记录游戏里面所有用到的落点
	CJSH_WorldPos= {

				--trap点(边境通往王城)
				loulanbianjing2wangcheng={newSceneId=73,PosX=418,PosZ=477},
				laiyinbianjing2wangcheng={newSceneId=150,PosX=418,PosZ=477},
				kunlunbianjing2wangcheng={newSceneId=250,PosX=418,PosZ=477},
				dunhuangbianjing2wangcheng={newSceneId=350,PosX=418,PosZ=477},
				--trap点(王城通往边境)
				loulanwangcheng2bianjing={newSceneId=74,PosX=36,PosZ=60},
				laiyinwangcheng2bianjing={newSceneId=151,PosX=36,PosZ=60},
				kunlunwangcheng2bianjing={newSceneId=251,PosX=36,PosZ=60},
				dunhuangwangcheng2bianjing={newSceneId=351,PosX=36,PosZ=60},
				
				--trap点(和林通往边境)
				--dadu2loulanbianjing={newSceneId=51,PosX=486,PosZ=473},
				--dadu2laiyinbianjing={newSceneId=151,PosX=486,PosZ=473},
				--dadu2kunlunbianjing={newSceneId=251,PosX=486,PosZ=473},
				--dadu2dunhuangbianjing={newSceneId=351,PosX=486,PosZ=473},
				--trap点(边境通往和林)
				--loulanbianjing2helin={newSceneId=17,PosX=267,PosZ=486},
				
				--trap点(和林通往大都)
				--bianjing2dadu={newSceneId=0,PosX=29,PosZ=362},
				
				--trap点(和林通往边境)
				--helin2daduloulan={newSceneId=51,PosX=479,PosZ=80},
				--helin2dadulaiyin={newSceneId=151,PosX=479,PosZ=80},
			  --helin2dadukunlun={newSceneId=251,PosX=479,PosZ=80},
				--helin2dadudunhuang={newSceneId=351,PosX=479,PosZ=80},
				
				--trap点(大都通往和林)
				--dadu2helin={newSceneId=17,PosX=483,PosZ=470},		
				
				--trap点(边境通道1通往下水道)
				loulanbianjingenter2xiaoshuidao={newSceneId=76,PosX=51,PosZ=12},		
				laiyinbianjingenter2xiaoshuidao={newSceneId=176,PosX=51,PosZ=12},		
				kunlunbianjingenter2xiaoshuidao={newSceneId=276,PosX=51,PosZ=12},		
				dunhuangbianjingenter2xiaoshuidao={newSceneId=376,PosX=51,PosZ=12},		

				--trap点(边境通道2通往下水道)
				loulanbianjingexit2xiaoshuidao={newSceneId=76,PosX=12,PosZ=51},		
				laiyinbianjingexit2xiaoshuidao={newSceneId=176,PosX=12,PosZ=51},		
				kunlunbianjingexit2xiaoshuidao={newSceneId=276,PosX=12,PosZ=51},				
				dunhuangbianjingexit2xiaoshuidao={newSceneId=376,PosX=12,PosZ=51},				

				--trap点(下水道通往边境西通道口)  （下水道到边境王国方向）
				loulanbianjingexit2xiaoshuidaowest={newSceneId=51,PosX=61,PosZ=169},		
				laiyinbianjingexit2xiaoshuidaowest={newSceneId=151,PosX=191,PosZ=175},	
				kunlunbianjingexit2xiaoshuidaowest={newSceneId=251,PosX=95,PosZ=178},		
				dunhuangbianjingexit2xiaoshuidaowest={newSceneId=351,PosX=190,PosZ=182},		

				--trap点(下水道通往边境东通道口)  （下水道到边境大都方向）
				loulanbianjingexit2xiaoshuidaoeast={newSceneId=51,PosX=97,PosZ=70},		
				laiyinbianjingexit2xiaoshuidaoeast={newSceneId=151,PosX=163,PosZ=72},		
				kunlunbianjingexit2xiaoshuidaoeast={newSceneId=251,PosX=58,PosZ=75},		
				dunhuangbianjingexit2xiaoshuidaoeast={newSceneId=351,PosX=187,PosZ=69},		

				--trap点(王城通往新手村)(王城到猎场)
				loulanwangcheng2xinshoucun={newSceneId=89,PosX=17,PosZ=145},
				laiyinwangcheng2xinshoucun={newSceneId=189,PosX=239,PosZ=124},
				kunlunwangcheng2xinshoucun={newSceneId=289,PosX=19,PosZ=134},
				dunhuangwangcheng2xinshoucun={newSceneId=389,PosX=230,PosZ=124},
				--trap点(王城通往新手村)（猎场到王城）
				loulanxinshoucun2wangcheng={newSceneId=50,PosX=244,PosZ=119},
				laiyinxinshoucun2wangcheng={newSceneId=150,PosX=13,PosZ=124},
				kunlunxinshoucun2wangcheng={newSceneId=250,PosX=242,PosZ=136},
				dunhuangxinshoucun2wangcheng={newSceneId=350,PosX=13,PosZ=141}, 			
				--trap点(大都到大都东)
				loulanwangcheng2wenquancun={newSceneId=37,PosX=25,PosZ=138},
				laiyinwangcheng2wenquancun={newSceneId=37,PosX=25,PosZ=138},
				kunlunwangcheng2wenquancun={newSceneId=37,PosX=25,PosZ=138},
				dunhuangwangcheng2wenquancun={newSceneId=37,PosX=25,PosZ=138},
				--trap点(大都东到大都)
				loulanwenquancun2wangcheng={newSceneId=0,PosX=219,PosZ=127},
				laiyinwenquancun2wangcheng={newSceneId=0,PosX=219,PosZ=127},
				kunlunwenquancun2wangcheng={newSceneId=0,PosX=219,PosZ=127},
				dunhuangwenquancun2wangcheng={newSceneId=0,PosX=219,PosZ=127},
				--trap点(大都到皇城)
				dadu2huangcheng0={newSceneId=41,PosX=64,PosZ=113},
				dadu2huangcheng1={newSceneId=41,PosX=64,PosZ=113},
				dadu2huangcheng2={newSceneId=41,PosX=64,PosZ=113},
				dadu2huangcheng3={newSceneId=41,PosX=64,PosZ=113},
				--trap点(皇城到大都)
				huangcheng2dadu0={newSceneId=0,PosX=127,PosZ=34},
				huangcheng2dadu1={newSceneId=0,PosX=127,PosZ=34},
				huangcheng2dadu2={newSceneId=0,PosX=127,PosZ=34},
				huangcheng2dadu3={newSceneId=0,PosX=127,PosZ=34},
				--trap点(大都到大都西)
				loulanwangcheng2fenglingdu={newSceneId=38,PosX=227,PosZ=148},
				laiyinwangcheng2fenglingdu={newSceneId=38,PosX=227,PosZ=148},
				kunlunwangcheng2fenglingdu={newSceneId=38,PosX=227,PosZ=148},
				dunhuangwangcheng2fenglingdu={newSceneId=38,PosX=227,PosZ=148},
				--trap点(大都西到大都)
				loulanfenglingdu2wangcheng={newSceneId=0,PosX=31,PosZ=127},
				laiyinfenglingdu2wangcheng={newSceneId=0,PosX=31,PosZ=127},
				kunlunfenglingdu2wangcheng={newSceneId=0,PosX=31,PosZ=127},
				dunhuangfenglingdu2wangcheng={newSceneId=0,PosX=31,PosZ=127},
				--传送点(大都到保定道)(改大都到大都南)
				dadu2baodingloulan={newSceneId=36,PosX=127,PosZ=32},
				dadu2baodinglaiyin={newSceneId=36,PosX=127,PosZ=32},
				dadu2baodingkunlun={newSceneId=36,PosX=127,PosZ=32},
				dadu2baodingdunhuang={newSceneId=36,PosX=127,PosZ=32},

				--传送点(保定道到大都)(改大都南到大都)
				baoding2dadu={newSceneId=0,PosX=128,PosZ=220},
				----NPC传送(PVE迷宫通往王城)
				--loulanmigong2wangcheng={newSceneId=50,PosX=271,PosZ=34},
				--laiyinmigong2wangcheng={newSceneId=150,PosX=271,PosZ=34},
				--kunlunmigong2wangcheng={newSceneId=250,PosX=271,PosZ=34},
				--dunhuangmigong2wangcheng={newSceneId=350,PosX=271,PosZ=34},				
				--
				--trap点(王城通往铁骑牧场)      （大都南到凤翔府）
				loulanwangcheng2machang={newSceneId=5,PosX=129,PosZ=29},
				laiyinwangcheng2machang={newSceneId=5,PosX=129,PosZ=29},
				kunlunwangcheng2machang={newSceneId=5,PosX=129,PosZ=29},
				dunhuangwangcheng2machang={newSceneId=5,PosX=129,PosZ=29},
				--trap点(铁骑牧场通往王城)   （凤翔府到大都南）
				loulanmachang2wangcheng={newSceneId=36,PosX=181,PosZ=233},
				laiyinmachang2wangcheng={newSceneId=36,PosX=181,PosZ=233},
				kunlunmachang2wangcheng={newSceneId=36,PosX=181,PosZ=233},
				dunhuangmachang2wangcheng={newSceneId=36,PosX=181,PosZ=233},
				--
				--trap点(金戈马场通往铁骑牧场)  (改金戈马场通往牧场)
				jinge2tieqiloulan={newSceneId=87,PosX=42,PosZ=33},
				jinge2tieqitianshan={newSceneId=187,PosX=100,PosZ=100},
				jinge2tieqikunlun={newSceneId=287,PosX=220,PosZ=139},
				jinge2tieqidunhuang={newSceneId=387,PosX=100,PosZ=100},
				                                                     
				--trap点(铁骑牧场通往金戈马场)  (改牧场通往金戈马场)                     
				tieqi2jingeloulan={newSceneId=19,PosX=100,PosZ=100},  
				tieqi2jingetianshan={newSceneId=19,PosX=100,PosZ=100},
				tieqi2jingekunlun={newSceneId=19,PosX=100,PosZ=100}, 
				tieqi2jingedunhuang={newSceneId=19,PosX=100,PosZ=100},
				
				----传送点(大都苏鲁锭)
				--dadusuluding={newSceneId=0,PosX=261,PosZ=203},
				----传送点(王城苏鲁锭)
				loulansuluding={newSceneId=50,PosX=127,PosZ=29},
				laiyinsuluding={newSceneId=150,PosX=128,PosZ=29},
				kunlunsuluding={newSceneId=250,PosX=126,PosZ=211},
				dunhuangsuluding={newSceneId=350,PosX=128,PosZ=226},

				--传送点(保定道到大同道)(改凤翔府蔡州城)
				baoding2datongloulan={newSceneId=6,PosX=62,PosZ=23},
				baoding2datonglaiyin={newSceneId=6,PosX=62,PosZ=23},
				baoding2datongkunlun={newSceneId=6,PosX=62,PosZ=23},
				baoding2datongdunhuang={newSceneId=6,PosX=62,PosZ=23},
				
				--传送点(大同道到保定道)(改蔡州到凤翔府)
				datong2baodingloulan={newSceneId=5,PosX=130,PosZ=220},
				datong2baodinglaiyin={newSceneId=5,PosX=130,PosZ=220},
				datong2baodingkunlun={newSceneId=5,PosX=130,PosZ=220},
				datong2baodingdunhuang={newSceneId=5,PosX=130,PosZ=220},

				--传送点(保定道到济宁道) (改蔡州到秦岭)   
				baoding2jiningloulan={newSceneId=7,PosX=164,PosZ=26},
				baoding2jininglaiyin={newSceneId=7,PosX=164,PosZ=26},
				baoding2jiningkunlun={newSceneId=7,PosX=164,PosZ=26},
				baoding2jiningdunhuang={newSceneId=7,PosX=164,PosZ=26},

			  --传送点(济宁道到保定道) （改秦岭到蔡州）
				jining2baodingloulan={newSceneId=6,PosX=128,PosZ=228},
				jining2baodinglaiyin={newSceneId=6,PosX=128,PosZ=228},
				jining2baodingkunlun={newSceneId=6,PosX=128,PosZ=228},
				jining2baodingdunhuang={newSceneId=6,PosX=128,PosZ=228},
				
				--传送点(济宁路到威海港)(改泰山到威海港)
				jining2weihailoulan={newSceneId=15,PosX=34,PosZ=109},
				jining2weihailaiyin={newSceneId=15,PosX=34,PosZ=109},
				jining2weihaikunlun={newSceneId=15,PosX=34,PosZ=109},
				jining2weihaidunhuang={newSceneId=15,PosX=34,PosZ=109},
				
				--传送点(威海港到济宁路)(改威海港到泰山)
				weihai2jiningloulan={newSceneId=2,PosX=226,PosZ=137},
				weihai2jininglaiyin={newSceneId=2,PosX=226,PosZ=137},
				weihai2jiningkunlun={newSceneId=2,PosX=226,PosZ=137},
				weihai2jiningdunhuang={newSceneId=2,PosX=226,PosZ=137},
				
				--传送点(保定路到安庆路)
			  --baoding2anqingloulan={newSceneId=22,PosX=185,PosZ=18},
				--baoding2anqinglaiyin={newSceneId=22,PosX=185,PosZ=18},
				--baoding2anqingkunlun={newSceneId=22,PosX=185,PosZ=18},
				--baoding2anqingdunhuang={newSceneId=22,PosX=185,PosZ=18},
				
				--传送点(安庆路到保定路)
				--anqing2baodingloulan={newSceneId=16,PosX=194,PosZ=228},
				--anqing2baodinglaiyin={newSceneId=16,PosX=194,PosZ=228},
				--anqing2baodingkunlun={newSceneId=16,PosX=194,PosZ=228},
				--anqing2baodingdunhuang={newSceneId=16,PosX=194,PosZ=228},
				
				--补充传送
				--dixialiangcang={newSceneId=2,PosX=11,PosZ=112},
				--xianrenguloulanin={newSceneId=7,PosX=25,PosZ=24},
				--xianrengulaiyinin={newSceneId=7,PosX=102,PosZ=20},
				--xianrengukunlunin={newSceneId=7,PosX=97,PosZ=100},
				--xianrengudunhuangin={newSceneId=7,PosX=25,PosZ=101},				
				----传送点(粮仓传送)
				--liangcangenterone={newSceneId=3,PosX=96,PosZ=16},
				liangcangexitone1={newSceneId=51,PosX=100,PosZ=100},
				liangcangexitone2={newSceneId=151,PosX=100,PosZ=100},
				liangcangexitone3={newSceneId=251,PosX=100,PosZ=100},
				liangcangexitone4={newSceneId=351,PosX=100,PosZ=100},
				--liangcangentertwo={newSceneId=3,PosX=95,PosZ=21},
				--liangcangexittwo={newSceneId=4,PosX=92,PosZ=19},
				--liangcangenterthree={newSceneId=2,PosX=105,PosZ=26},
				--liangcangexitthree={newSceneId=3,PosX=16,PosZ=18},
				--liangcangenterfour={newSceneId=5,PosX=115,PosZ=108},
				--liangcangexitfour={newSceneId=6,PosX=88,PosZ=103},
				--liangcangenterfive={newSceneId=4,PosX=59,PosZ=30},
				--liangcangexitfive={newSceneId=5,PosX=24,PosZ=114},
			
				----传送点(仙人谷传送)
				----xianrenguexitone1={newSceneId=51,PosX=110,PosZ=229},
				--xianrenguexitone2={newSceneId=151,PosX=100,PosZ=100},
				--xianrenguexitone3={newSceneId=251,PosX=100,PosZ=100},
				--xianrenguexitone4={newSceneId=351,PosX=100,PosZ=100},
				--xianrenguentertwo={newSceneId=8,PosX=52,PosZ=47},
				--xianrenguexittwo1={newSceneId=7,PosX=59,PosZ=71},	
				--xianrenguexittwo2={newSceneId=7,PosX=75,PosZ=63},	
				--xianrenguexittwo3={newSceneId=7,PosX=59,PosZ=71},	
				--xianrenguexittwo4={newSceneId=7,PosX=59,PosZ=71},
				--xianrenguenterthree={newSceneId=9,PosX=108,PosZ=101},
				--xianrenguexitthree={newSceneId=8,PosX=103,PosZ=19},
				--xianrenguenterfour={newSceneId=10,PosX=108,PosZ=17},
				--xianrenguexitfour={newSceneId=9,PosX=18,PosZ=26},
				--xianrenguenterfive={newSceneId=11,PosX=21,PosZ=111},
				--xianrenguexitfive={newSceneId=10,PosX=16,PosZ=105},
			
				----比武传送回国
				--biwu2loulan={newSceneId=50,PosX=227,PosZ=239},
				--biwu2laiyin={newSceneId=150,PosX=227,PosZ=239},				
				--biwu2kunlun={newSceneId=250,PosX=227,PosZ=239},				
				--biwu2dunhuang={newSceneId=350,PosX=227,PosZ=239},		
        --传送点(泰山到大都东)                                        
        taishan2daduloulan={newSceneId=37,PosX=223,PosZ=75},       
        taishan2dadutianshan={newSceneId=37,PosX=223,PosZ=75},       
        taishan2dadukunlun={newSceneId=37,PosX=223,PosZ=75},       
        taishan2dadudunhuang={newSceneId=37,PosX=223,PosZ=75},     
       --传送点(大都到泰山)                                                                                                
        dadu2taishanloulan={newSceneId=2,PosX=24,PosZ=144},                                                               
        dadu2taishantianshan={newSceneId=2,PosX=24,PosZ=144},                                                             
        dadu2taishankunlun={newSceneId=2,PosX=24,PosZ=144},                                                               
        dadu2taishandunhuang={newSceneId=2,PosX=24,PosZ=144},                                                             
       --传送点(太行山到大都西)                                    
        taihangshan2daduloulan={newSceneId=38,PosX=24,PosZ=222},   
        taihangshan2dadutianshan={newSceneId=38,PosX=24,PosZ=222}, 
        taihangshan2dadukunlun={newSceneId=38,PosX=24,PosZ=222},   
        taihangshan2dadudunhuang={newSceneId=38,PosX=24,PosZ=222}, 
       --传送点(大都到太行山)                                     
        dadu2taihangshanloulan={newSceneId=4,PosX=219,PosZ=33},    
        dadu2taihangshantianshan={newSceneId=4,PosX=219,PosZ=33},  
        dadu2taihangshankunlun={newSceneId=4,PosX=219,PosZ=33},    
        dadu2taihangshandunhuang={newSceneId=4,PosX=219,PosZ=33},   
       --传送点(太行山到河西)                                        
        taihangshan2hexiloulan={newSceneId=3,PosX=225,PosZ=131},   
        taihangshan2hexitianshan={newSceneId=3,PosX=225,PosZ=131}, 
        taihangshan2hexikunlun={newSceneId=3,PosX=225,PosZ=131},   
        taihangshan2hexidunhuang={newSceneId=3,PosX=225,PosZ=131}, 
       --传送点(中兴府到太行山)                                       
        hexi2taihangshanloulan={newSceneId=4,PosX=52,PosZ=187},    
        hexi2taihangshantianshan={newSceneId=4,PosX=52,PosZ=187},  
        hexi2taihangshankunlun={newSceneId=4,PosX=52,PosZ=187},    
        hexi2taihangshandunhuang={newSceneId=4,PosX=52,PosZ=187},      
       --传送点(金山到河西)   (金山到中兴府)                                         
        jinshan2hexiloulan={newSceneId=3,PosX=30,PosZ=126},        
        jinshan2hexitianshan={newSceneId=3,PosX=30,PosZ=126},      
        jinshan2hexikunlun={newSceneId=3,PosX=30,PosZ=126},        
        jinshan2hexidunhuang={newSceneId=3,PosX=30,PosZ=126},      
        --传送点(河西到金山)  (中兴府到金山)                                          
        hexi2jinshanloulan={newSceneId=8,PosX=225,PosZ=164},         
        hexi2jinshantianshan={newSceneId=8,PosX=225,PosZ=164},       
        hexi2jinshankunlun={newSceneId=8,PosX=225,PosZ=164},         
        hexi2jinshandunhuang={newSceneId=8,PosX=225,PosZ=164},    
        --传送点(金山到叶密立)  (改金山到碎叶城)                                     
        jinshan2yemililoulan={newSceneId=9,PosX=228,PosZ=69},      
        jinshan2yemilitianshan={newSceneId=9,PosX=228,PosZ=69},    
        jinshan2yemilikunlun={newSceneId=9,PosX=228,PosZ=69},      
        jinshan2yemilidunhuang={newSceneId=9,PosX=228,PosZ=69},    
        --传送点(叶密立到金山)   (碎叶城到阿尔金山)                                      
        yemili2jinshanloulan={newSceneId=8,PosX=30,PosZ=113},       
        yemili2jinshantianshan={newSceneId=8,PosX=30,PosZ=113},     
        yemili2jinshankunlun={newSceneId=8,PosX=30,PosZ=113},       
        yemili2jinshandunhuang={newSceneId=8,PosX=30,PosZ=113},  
         --传送点(中兴府到边塞)                                       
        hexi2bianjingloulan={newSceneId=51,PosX=180,PosZ=214},       
        hexi2bianjingtianshan={newSceneId=151,PosX=69,PosZ=225},     
        hexi2bianjingkunlun={newSceneId=251,PosX=174,PosZ=36},       
        hexi2bianjingdunhuang={newSceneId=351,PosX=70,PosZ=37},  
         --传送点(边境到中兴府)                                        
        bianjing2hexiloulan={newSceneId=3,PosX=37,PosZ=38},       
        bianjing2hexitianshan={newSceneId=3,PosX=226,PosZ=34},     
        bianjing2hexikunlun={newSceneId=3,PosX=43,PosZ=216},       
        bianjing2hexidunhuang={newSceneId=3,PosX=220,PosZ=220},  
        --传送点(边塞到草场) (改边塞到古道)                                       
        bianjing2caochangloulan={newSceneId=86,PosX=133,PosZ=207},             
        bianjing2caochangtianshan={newSceneId=186,PosX=132,PosZ=205},     
        bianjing2caochangkunlun={newSceneId=286,PosX=117,PosZ=40},       
        bianjing2caochangdunhuang={newSceneId=386,PosX=110,PosZ=40},  
        --传送点(草场到边塞) （改古道到边塞）                                       
        caochang2bianjingloulan={newSceneId=51,PosX=34,PosZ=33},       
        caochang2bianjingtianshan={newSceneId=151,PosX=220,PosZ=36},     
        caochang2bianjingkunlun={newSceneId=251,PosX=46,PosZ=216},       
        caochang2bianjingdunhuang={newSceneId=351,PosX=202,PosZ=200},  
         --传送点(边塞到古道)                                        
        bianjing2gudaoloulan={newSceneId=86,PosX=96,PosZ=240},       
        bianjing2gudaotianshan={newSceneId=186,PosX=135,PosZ=208},     
        bianjing2gudaokunlun={newSceneId=286,PosX=125,PosZ=38},       
        bianjing2gudaodunhuang={newSceneId=386,PosX=117,PosZ=38},  
         --传送点(古道到边塞)                                        
        --gudao2bianjingloulan={newSceneId=89,PosX=124,PosZ=13},       
        --gudao2bianjingtianshan={newSceneId=189,PosX=116,PosZ=27},     
        --gudao2bianjingkunlun={newSceneId=289,PosX=218,PosZ=225},       
        --gudao2bianjingdunhuang={newSceneId=389,PosX=43,PosZ=210},   
         --传送点(牧场到草场)   （改外城到王城）                                    
        muchang2caochangloulan={newSceneId=50,PosX=128,PosZ=236},       
        muchang2caochangtianshan={newSceneId=150,PosX=126,PosZ=235},     
        muchang2caochangkunlun={newSceneId=250,PosX=128,PosZ=11},       
        muchang2caochangdunhuang={newSceneId=350,PosX=128,PosZ=11},  
         --传送点(草场到牧场)   (改王城到外城)                                     
        caochang2muchangloulan={newSceneId=58,PosX=126,PosZ=40},     
        caochang2muchangtianshan={newSceneId=158,PosX=126,PosZ=40},     
        caochang2muchangkunlun={newSceneId=258,PosX=128,PosZ=225},       
        caochang2muchangdunhuang={newSceneId=358,PosX=128,PosZ=225},      
       --传送点(王城到牧场)                                        
        wangcheng2gudaoloulan={newSceneId=87,PosX=235,PosZ=172},       
        wangcheng2gudaotianshan={newSceneId=187,PosX=11,PosZ=140},     
        wangcheng2gudaokunlun={newSceneId=287,PosX=232,PosZ=75},       
        wangcheng2gudaodunhuang={newSceneId=387,PosX=21,PosZ=73}, 
        --传送点(古道到王城) （改古道到外城）                                       
        gudao2wangchengloulan={newSceneId=58,PosX=131,PosZ=213},       
        gudao2wangchengtianshan={newSceneId=158,PosX=130,PosZ=212},     
        gudao2wangchengkunlun={newSceneId=258,PosX=127,PosZ=40},       
        gudao2wangchengdunhuang={newSceneId=358,PosX=127,PosZ=40},              
       --传送点(王城到古道)  （改外城到古道）                                       
        wangcheng2muchangloulan={newSceneId=86,PosX=116,PosZ=32},       
        wangcheng2muchangtianshan={newSceneId=186,PosX=110,PosZ=44},     
        wangcheng2muchangkunlun={newSceneId=286,PosX=120,PosZ=224},       
        wangcheng2muchangdunhuang={newSceneId=386,PosX=150,PosZ=219}, 
        --传送点(牧场到王城)                                        
        muchang2wangchengloulan={newSceneId=50,PosX=13,PosZ=126},       
        muchang2wangchengtianshan={newSceneId=150,PosX=240,PosZ=115},     
        muchang2wangchengkunlun={newSceneId=250,PosX=13,PosZ=138},       
        muchang2wangchengdunhuang={newSceneId=350,PosX=242,PosZ=138},   
        --- --传送点(将军冢1到古道)                                        
        ---jiangjunone2wangguogudao={newSceneId=86,PosX=64,PosZ=230},       
        ---jiangjunone2wangguogudao={newSceneId=186,PosX=64,PosZ=230},     
        ---jiangjunone2wangguogudao={newSceneId=286,PosX=64,PosZ=230},       
        ---jiangjunone2wangguogudao={newSceneId=386,PosX=64,PosZ=230},   
         --传送点(古道到将军冢1)   （改为大马士革到耶路撒冷）                                     
        wangguogudao2jiangjunone={newSceneId=24,PosX=9,PosZ=115},       
        wangguogudao2jiangjunone={newSceneId=24,PosX=9,PosZ=115},     
        wangguogudao2jiangjunone={newSceneId=24,PosX=9,PosZ=115},       
        wangguogudao2jiangjunone={newSceneId=24,PosX=9,PosZ=115},   
         --传送点(将军冢1到将军冢2) (改耶路撒冷到大马士革)                                       
        jiangjunone2jiangjuntwo={newSceneId=23,PosX=96,PosZ=13},       
        jiangjunone2jiangjuntwo={newSceneId=23,PosX=96,PosZ=13},    
        jiangjunone2jiangjuntwo={newSceneId=23,PosX=96,PosZ=13},          
        jiangjunone2jiangjuntwo={newSceneId=23,PosX=96,PosZ=13},    
         --传送点(将军冢2到将军冢1) （改耶路撒冷到西奈）                                        
         jiangjuntwo2jiangjunone={newSceneId=25,PosX=108,PosZ=22},       
         jiangjuntwo2jiangjunone={newSceneId=25,PosX=108,PosZ=22},  
         jiangjuntwo2jiangjunone={newSceneId=25,PosX=108,PosZ=22},       
         jiangjuntwo2jiangjunone={newSceneId=25,PosX=108,PosZ=22},  
        --传送点(将军冢2到将军冢3) （改西奈到耶路撒冷）                                      
         jiangjuntwo2jiangjunshree={newSceneId=24,PosX=94,PosZ=14},       
         jiangjuntwo2jiangjunshree={newSceneId=24,PosX=94,PosZ=14},     
         jiangjuntwo2jiangjunshree={newSceneId=24,PosX=94,PosZ=14},        
         jiangjuntwo2jiangjunshree={newSceneId=24,PosX=94,PosZ=14},      
         --传送点(边塞到浮屠塔1) (改婆罗洲到爪哇)                                 
        biansai2futuone={newSceneId=34,PosX=9,PosZ=115},           
        biansai2futuone={newSceneId=34,PosX=9,PosZ=115},           
        biansai2futuone={newSceneId=34,PosX=9,PosZ=115},           
        biansai2futuone={newSceneId=34,PosX=9,PosZ=115},           
         --传送点(浮屠塔1到浮屠塔2) （改爪哇到婆罗洲）                              
        futuone2fututwo={newSceneId=33,PosX=96,PosZ=13},           
        futuone2fututwo={newSceneId=33,PosX=96,PosZ=13},           
        futuone2fututwo={newSceneId=33,PosX=96,PosZ=13},           
        futuone2fututwo={newSceneId=33,PosX=96,PosZ=13},           
         --传送点(浮屠塔2到浮屠塔1) （改爪哇到苏门答腊）                              
         fututwo2futuone={newSceneId=35,PosX=108,PosZ=22},         
         fututwo2futuone={newSceneId=35,PosX=108,PosZ=22},         
         fututwo2futuone={newSceneId=35,PosX=108,PosZ=22},         
         fututwo2futuone={newSceneId=35,PosX=108,PosZ=22},         
        --传送点(浮屠塔2到浮屠塔3)   （改苏门答腊到爪哇）                             
         fututwo2futushree={newSceneId=34,PosX=94,PosZ=14},        
         fututwo2futushree={newSceneId=34,PosX=94,PosZ=14},        
         fututwo2futushree={newSceneId=34,PosX=94,PosZ=14},        
         fututwo2futushree={newSceneId=34,PosX=94,PosZ=14},        
        ----传送点(浮屠塔3到浮屠塔2)                                
        --futushree2fututwo={newSceneId=6,PosX=10,PosZ=15},         
        --futushree2fututwo={newSceneId=6,PosX=10,PosZ=15},         
        --futushree2fututwo={newSceneId=6,PosX=10,PosZ=15},         
        --futushree2fututwo={newSceneId=6,PosX=10,PosZ=15},  
        --传送点(万佛洞1到中兴府) （改秦岭到大理）                                     
        wanfoone2zhongxingfu={newSceneId=30,PosX=64,PosZ=230},             
        wanfoone2zhongxingfu={newSceneId=30,PosX=64,PosZ=230},            
        wanfoone2zhongxingfu={newSceneId=30,PosX=64,PosZ=230},            
        wanfoone2zhongxingfu={newSceneId=30,PosX=64,PosZ=230},            
         --传送点(中兴府到万佛洞1) （改大理到秦岭）                                     
        zhongxingfu2wanfoone={newSceneId=8,PosX=80,PosZ=228},               
        zhongxingfu2wanfoone={newSceneId=8,PosX=80,PosZ=228},               
        zhongxingfu2wanfoone={newSceneId=8,PosX=80,PosZ=228},               
        zhongxingfu2wanfoone={newSceneId=8,PosX=80,PosZ=228},               
         --传送点(万佛洞1到万佛洞2) （改大理到缅甸）                                  
        wanfoone2wanfotwo={newSceneId=7,PosX=96,PosZ=13},           
        wanfoone2wanfotwo={newSceneId=7,PosX=96,PosZ=13},           
        wanfoone2wanfotwo={newSceneId=7,PosX=96,PosZ=13},           
        wanfoone2wanfotwo={newSceneId=7,PosX=96,PosZ=13},           
         --传送点(万佛洞2到万佛洞1) （改缅甸到大理）                                     
         wanfotwo2wanfoone={newSceneId=30,PosX=108,PosZ=22},         
         wanfotwo2wanfoone={newSceneId=30,PosX=108,PosZ=22},         
         wanfotwo2wanfoone={newSceneId=30,PosX=108,PosZ=22},         
         wanfotwo2wanfoone={newSceneId=30,PosX=108,PosZ=22},         
        --传送点(万佛洞2到万佛洞3)   （改缅甸到印度河）                                 
         wanfotwo2wanfoshree={newSceneId=32,PosX=94,PosZ=14},    
         wanfotwo2wanfoshree={newSceneId=32,PosX=94,PosZ=14},    
         wanfotwo2wanfoshree={newSceneId=32,PosX=94,PosZ=14},    
         wanfotwo2wanfoshree={newSceneId=32,PosX=94,PosZ=14},    
        --传送点(万佛洞3到万佛洞2)  （印度河到缅甸）                                  
        wanfoshree2wanfotwo={newSceneId=31,PosX=10,PosZ=15},     
        wanfoshree2wanfotwo={newSceneId=31,PosX=10,PosZ=15},     
        wanfoshree2wanfotwo={newSceneId=31,PosX=10,PosZ=15},     
        wanfoshree2wanfotwo={newSceneId=31,PosX=10,PosZ=15},        
         --传送点(沙河水道1到沙河水道2)  （改对马岛到福冈）                                 
        shaheone2shahetwo={newSceneId=27,PosX=96,PosZ=13},           
        shaheone2shahetwo={newSceneId=27,PosX=96,PosZ=13},           
        shaheone2shahetwo={newSceneId=27,PosX=96,PosZ=13},           
        shaheone2shahetwo={newSceneId=27,PosX=96,PosZ=13},           
         --传送点(沙河水道2到沙河水道1)   （改福冈到对马岛）                                
         shahetwo2shaheone={newSceneId=26,PosX=108,PosZ=22},         
         shahetwo2shaheone={newSceneId=26,PosX=108,PosZ=22},         
         shahetwo2shaheone={newSceneId=26,PosX=108,PosZ=22},         
         shahetwo2shaheone={newSceneId=26,PosX=108,PosZ=22},         
        --传送点(沙河水道2到沙河水道3)   （改福冈到九州岛）                                 
         shahetwo2shaheshree={newSceneId=29,PosX=94,PosZ=14},    
         shahetwo2shaheshree={newSceneId=29,PosX=94,PosZ=14},    
         shahetwo2shaheshree={newSceneId=29,PosX=94,PosZ=14},    
         shahetwo2shaheshree={newSceneId=29,PosX=94,PosZ=14},    
        --传送点(沙河水道3到沙河水道2)    （改九州到福冈）                                
        shaheshree2shahetwo={newSceneId=27,PosX=10,PosZ=15},     
        shaheshree2shahetwo={newSceneId=27,PosX=10,PosZ=15},     
        shaheshree2shahetwo={newSceneId=27,PosX=10,PosZ=15},     
        shaheshree2shahetwo={newSceneId=27,PosX=10,PosZ=15}, 
		
		
		--传送点(王城到迷宫1)                                      
        wangcheng2migongone1={newSceneId=104,PosX=182,PosZ=44},             
        wangcheng2migongone2={newSceneId=204,PosX=68,PosZ=194},            
        wangcheng2migongone3={newSceneId=304,PosX=56,PosZ=68},            
        wangcheng2migongone4={newSceneId=404,PosX=65,PosZ=59},            
         --传送点(迷宫1到王城)                                      
        migongone2wangcheng1={newSceneId=50,PosX=21,PosZ=92},               
        migongone2wangcheng2={newSceneId=150,PosX=236,PosZ=152},               
        migongone2wangcheng3={newSceneId=250,PosX=21,PosZ=110},               
        migongone2wangcheng4={newSceneId=350,PosX=234,PosZ=163}, 
		--传送点(王城到小屋1)                                      
        wangcheng2xiaowuone1={newSceneId=62,PosX=30,PosZ=27},             
        wangcheng2xiaowuone2={newSceneId=162,PosX=30,PosZ=27},            
        wangcheng2xiaowuone3={newSceneId=262,PosX=30,PosZ=27},            
        wangcheng2xiaowuone4={newSceneId=362,PosX=30,PosZ=27},            
         --传送点(小屋1到王城)                                      
        xiaowuone2wangcheng1={newSceneId=50,PosX=156,PosZ=97},               
        xiaowuone2wangcheng2={newSceneId=150,PosX=92,PosZ=138},               
        xiaowuone2wangcheng3={newSceneId=250,PosX=198,PosZ=159},               
        xiaowuone2wangcheng4={newSceneId=350,PosX=199,PosZ=156}, 
		--传送点(王城到小屋2)                                      
        wangcheng2xiaowutwo1={newSceneId=63,PosX=36,PosZ=25},             
        wangcheng2xiaowutwo2={newSceneId=163,PosX=36,PosZ=25},            
        wangcheng2xiaowutwo3={newSceneId=263,PosX=36,PosZ=25},            
        wangcheng2xiaowutwo4={newSceneId=363,PosX=36,PosZ=25},            
        --传送点(小屋2到王城)                                      
        xiaowutwo2wangcheng1={newSceneId=50,PosX=56,PosZ=94},               
        xiaowutwo2wangcheng2={newSceneId=150,PosX=162,PosZ=99},               
        xiaowutwo2wangcheng3={newSceneId=250,PosX=207,PosZ=116},               
        xiaowutwo2wangcheng4={newSceneId=350,PosX=69,PosZ=201}, 
		--传送点(边塞到民居)                                      
        biasnai2minju1={newSceneId=61,PosX=30,PosZ=27},             
        biasnai2minju2={newSceneId=161,PosX=30,PosZ=27},            
        biasnai2minju3={newSceneId=261,PosX=30,PosZ=26},            
        biasnai2minju4={newSceneId=361,PosX=30,PosZ=26},            
        --传送点(民居到边塞)                                      
        minju2biasnai1={newSceneId=51,PosX=155,PosZ=126},               
        minju2biasnai2={newSceneId=151,PosX=76,PosZ=117},               
        minju2biasnai3={newSceneId=251,PosX=153,PosZ=129},               
        minju2biasnai4={newSceneId=351,PosX=99,PosZ=129}, 
		--传送点(大都到大都民居1)                                      
        dadu2dadumingjuone1={newSceneId=42,PosX=30,PosZ=27},             
        dadu2dadumingjuone2={newSceneId=42,PosX=30,PosZ=27},            
        dadu2dadumingjuone3={newSceneId=42,PosX=30,PosZ=27},            
        dadu2dadumingjuone4={newSceneId=42,PosX=30,PosZ=27},            
        --传送点(大都民居1到大都)                                      
        dadumingjuone2dadu1={newSceneId=0,PosX=195,PosZ=41},               
        dadumingjuone2dadu2={newSceneId=0,PosX=195,PosZ=41},               
        dadumingjuone2dadu3={newSceneId=0,PosX=195,PosZ=41},               
        dadumingjuone2dadu4={newSceneId=0,PosX=195,PosZ=41}, 
		--传送点(大都到大都民居2)                                     
        dadu2dadumingjutwo1={newSceneId=43,PosX=36,PosZ=25},             
        dadu2dadumingjutwo2={newSceneId=43,PosX=36,PosZ=25},            
        dadu2dadumingjutwo3={newSceneId=43,PosX=36,PosZ=25},            
        dadu2dadumingjutwo4={newSceneId=43,PosX=36,PosZ=25},            
         --传送点(大都民居2到大都)                                     
        dadumingjutwo2dadu1={newSceneId=0,PosX=211,PosZ=163},               
        dadumingjutwo2dadu2={newSceneId=0,PosX=211,PosZ=163},               
        dadumingjutwo2dadu3={newSceneId=0,PosX=211,PosZ=163},               
        dadumingjutwo2dadu4={newSceneId=0,PosX=211,PosZ=163}, 
		
		

		
         --传送点(牧场到迷宫1)                                      
        gubaoone2bageda1={newSceneId=104,PosX=182,PosZ=44},             
        gubaoone2bageda2={newSceneId=204,PosX=68,PosZ=194},            
        gubaoone2bageda3={newSceneId=304,PosX=56,PosZ=68},            
        gubaoone2bageda4={newSceneId=404,PosX=65,PosZ=59},            
         --传送点(迷宫1到王城)                                      
        bageda2gubaoone1={newSceneId=50,PosX=21,PosZ=92},               
        bageda2gubaoone2={newSceneId=150,PosX=236,PosZ=152},               
        bageda2gubaoone3={newSceneId=250,PosX=21,PosZ=111},               
        bageda2gubaoone4={newSceneId=350,PosX=234,PosZ=163},   	
         --传送点(迷宫1到迷宫2)                                   
        gubaoone2gubaotwo1={newSceneId=105,PosX=55,PosZ=72},           
        gubaoone2gubaotwo2={newSceneId=205,PosX=189,PosZ=199},           
        gubaoone2gubaotwo3={newSceneId=305,PosX=72,PosZ=60},           
        gubaoone2gubaotwo4={newSceneId=405,PosX=62,PosZ=60},           
         --传送点(迷宫2到迷宫1)                                     
        gubaotwo2gubaoone1={newSceneId=104,PosX=189,PosZ=192},         
        gubaotwo2gubaoone2={newSceneId=204,PosX=69,PosZ=61},         
        gubaotwo2gubaoone3={newSceneId=304,PosX=205,PosZ=193},         
        gubaotwo2gubaoone4={newSceneId=404,PosX=190,PosZ=197},         
         --传送点(迷宫2到迷宫3)                                      
        gubaotwo2gubaoshree1={newSceneId=106,PosX=46,PosZ=187},    
        gubaotwo2gubaoshree2={newSceneId=206,PosX=46,PosZ=128},    
        gubaotwo2gubaoshree3={newSceneId=306,PosX=210,PosZ=74},    
        gubaotwo2gubaoshree4={newSceneId=406,PosX=195,PosZ=182},    
         --传送点(迷宫3到迷宫2)                                       
        gubaoshree2gubaotwoloulan={newSceneId=105,PosX=208,PosZ=195},     
        gubaoshree2gubaotwotianshan={newSceneId=205,PosX=192,PosZ=47},     
        gubaoshree2gubaotwokunlun={newSceneId=305,PosX=50,PosZ=188},     
        gubaoshree2gubaotwodunhuang={newSceneId=405,PosX=50,PosZ=128},  
        --传送点(迷宫3到迷宫4)                                       
        eerduosi2hannanhe1={newSceneId=107,PosX=71,PosZ=195},     
        eerduosi2hannanhe2={newSceneId=207,PosX=62,PosZ=56},     
        eerduosi2hannanhe3={newSceneId=307,PosX=184,PosZ=48},     
        eerduosi2hannanhe4={newSceneId=407,PosX=72,PosZ=215},  
         --传送点(迷宫4到迷宫3)                                       
        hannanhe2eerduosi1={newSceneId=106,PosX=210,PosZ=62},     
        hannanhe2eerduosi2={newSceneId=206,PosX=195,PosZ=48},     
        hannanhe2eerduosi3={newSceneId=306,PosX=69,PosZ=195},     
        hannanhe2eerduosi4={newSceneId=406,PosX=57,PosZ=68}, 
          --传送点(迷宫4到迷宫5)                                      
        baizhanting2bosi1={newSceneId=108,PosX=181,PosZ=50},     
        baizhanting2bosi2={newSceneId=208,PosX=215,PosZ=62},     
        baizhanting2bosi3={newSceneId=308,PosX=189,PosZ=49},     
        baizhanting2bosi4={newSceneId=408,PosX=211,PosZ=199},  
        --传送点(迷宫5到迷宫4)                                  
        damashige2bosi1={newSceneId=107,PosX=70,PosZ=59},     
        damashige2bosi2={newSceneId=207,PosX=58,PosZ=196},     
        damashige2bosi3={newSceneId=307,PosX=50,PosZ=198},     
        damashige2bosi4={newSceneId=407,PosX=70,PosZ=60},  
        --传送点(迷宫5到迷宫6)                                      
        jiangjunshree2jiangjuntwo1={newSceneId=109,PosX=180,PosZ=54},       
        jiangjunshree2jiangjuntwo2={newSceneId=209,PosX=212,PosZ=195},     
        jiangjunshree2jiangjuntwo3={newSceneId=309,PosX=191,PosZ=54},        
        jiangjunshree2jiangjuntwo4={newSceneId=409,PosX=60,PosZ=203},  
        --传送点(迷宫6到迷宫5)                                    
        futuone2biansai1={newSceneId=108,PosX=60,PosZ=129},      
        futuone2biansai2={newSceneId=208,PosX=40,PosZ=193},     
        futuone2biansai3={newSceneId=308,PosX=51,PosZ=128},     
        futuone2biansai4={newSceneId=408,PosX=188,PosZ=46},       
        --trap点(迷宫6到迷宫7)
				loulanwangcheng2huangyelin={newSceneId=110,PosX=77,PosZ=62},
				laiyinwangcheng2huangyelin={newSceneId=210,PosX=189,PosZ=199},
				kunlunwangcheng2huangyelin={newSceneId=310,PosX=95,PosZ=39},
				dunhuangwangcheng2huangyelin={newSceneId=410,PosX=67,PosZ=195},
				----trap点(迷宫7到迷宫6)
				loulanhuangyelin2wangcheng={newSceneId=109,PosX=184,PosZ=199},
				laiyinhuangyelin2wangcheng={newSceneId=209,PosX=55,PosZ=67},
				kunlunhuangyelin2wangcheng={newSceneId=309,PosX=188,PosZ=195},
				dunhuanghuangyelin2wangcheng={newSceneId=409,PosX=207,PosZ=64},	
				----trap点(迷宫7到迷宫8)
				migong7ceng2migong8cengloulan={newSceneId=111,PosX=201,PosZ=193},
				migong7ceng2migong8cengtianshan={newSceneId=211,PosX=194,PosZ=197},
				migong7ceng2migong8cengkunlun={newSceneId=311,PosX=76,PosZ=65},
				migong7ceng2migong8cengdunhuang={newSceneId=411,PosX=212,PosZ=195},	
				----trap点(迷宫8到迷宫7)
			  migong8ceng2migong7cengloulan={newSceneId=110,PosX=64,PosZ=222},
				migong8ceng2migong7cengtianshan={newSceneId=210,PosX=190,PosZ=42},
				migong8ceng2migong7cengkunlun={newSceneId=310,PosX=211,PosZ=60},
				migong8ceng2migong7cengdunhuang={newSceneId=410,PosX=67,PosZ=58},	
         --传送点(王城到罕难河)                                    
        wangcheng2hannanheloulan={newSceneId=98,PosX=92,PosZ=219},     
        wangcheng2hannanhetianshan={newSceneId=198,PosX=92,PosZ=219},     
        wangcheng2hannanhekunlun={newSceneId=298,PosX=92,PosZ=219},     
        wangcheng2hannanhedunhuang={newSceneId=398,PosX=92,PosZ=219},  
         --传送点(罕难河到王城)                                    
        hannanheloulan2wangcheng={newSceneId=50,PosX=235,PosZ=100},     
        hannanhetianshan2wangcheng={newSceneId=150,PosX=11,PosZ=91},     
        hannanhekunlun2wangcheng={newSceneId=250,PosX=235,PosZ=159},     
        hannanhedunhuang2wangcheng={newSceneId=350,PosX=20,PosZ=156},  
         --传送点(罕难河到乞颜)                                    
        hannanhe2qiyan0={newSceneId=99,PosX=216,PosZ=24},     
        hannanhe2qiyan1={newSceneId=199,PosX=216,PosZ=24},     
        hannanhe2qiyan2={newSceneId=299,PosX=216,PosZ=24},     
        hannanhe2qiyan3={newSceneId=399,PosX=216,PosZ=24},  
         --传送点(乞颜到罕难河)                                    
        qiyan2hannanhe0={newSceneId=98,PosX=221,PosZ=210},     
        qiyan2hannanhe1={newSceneId=198,PosX=221,PosZ=210},     
        qiyan2hannanhe2={newSceneId=298,PosX=221,PosZ=210},     
        qiyan2hannanhe3={newSceneId=398,PosX=221,PosZ=210},  
         --传送点(乞颜到乃蛮)                                    
        qiyan2nainan0={newSceneId=102,PosX=227,PosZ=124},     
        qiyan2nainan1={newSceneId=202,PosX=227,PosZ=124},     
        qiyan2nainan2={newSceneId=302,PosX=227,PosZ=124},     
        qiyan2nainan3={newSceneId=402,PosX=227,PosZ=124},               
         --传送点(乞颜到塔塔尔)                                    
        qiyan2tataer0={newSceneId=100,PosX=29,PosZ=144},
        qiyan2tataer1={newSceneId=200,PosX=29,PosZ=144},     
        qiyan2tataer2={newSceneId=300,PosX=29,PosZ=144},     
        qiyan2tataer3={newSceneId=400,PosX=29,PosZ=144},  
        --传送点(塔塔尔到乞颜)                                    
        tataer2qiyan0={newSceneId=99,PosX=232,PosZ=216},     
        tataer2qiyan1={newSceneId=199,PosX=232,PosZ=216},     
        tataer2qiyan2={newSceneId=299,PosX=232,PosZ=216},     
        tataer2qiyan3={newSceneId=399,PosX=232,PosZ=216},  
         --传送点(乞颜到克列)                                    
        qiyan2kelie0={newSceneId=101,PosX=147,PosZ=48},     
        qiyan2kelie1={newSceneId=201,PosX=147,PosZ=48},     
        qiyan2kelie2={newSceneId=301,PosX=147,PosZ=48},     
        qiyan2kelie3={newSceneId=401,PosX=147,PosZ=48},  
         --传送点(乃蛮到乞颜)                                    
        naiman2qiyan0={newSceneId=99,PosX=24,PosZ=123},     
        naiman2qiyan1={newSceneId=199,PosX=24,PosZ=123},     
        naiman2qiyan2={newSceneId=299,PosX=24,PosZ=123},     
        naiman2qiyan3={newSceneId=399,PosX=24,PosZ=123},  
         --传送点(塔塔尔到乞颜)                                    
        tatare2qiyan0={newSceneId=99,PosX=100,PosZ=100},     
        tatare2qiyan1={newSceneId=199,PosX=100,PosZ=100},     
        tatare2qiyan2={newSceneId=299,PosX=100,PosZ=100},     
        tatare2qiyan3={newSceneId=399,PosX=100,PosZ=100},  
         --传送点(克列到乞颜)                                    
        kelie2qiyan0={newSceneId=99,PosX=102,PosZ=230},     
        kelie2qiyan1={newSceneId=199,PosX=102,PosZ=230},     
        kelie2qiyan2={newSceneId=299,PosX=102,PosZ=230},     
        kelie2qiyan3={newSceneId=399,PosX=102,PosZ=230},  
         --传送点(克烈到居庸)                                    
        kelie2juyongguan0={newSceneId=103,PosX=90,PosZ=31},     
        kelie2juyongguan1={newSceneId=203,PosX=90,PosZ=31},     
        kelie2juyongguan2={newSceneId=303,PosX=90,PosZ=31},     
        kelie2juyongguan3={newSceneId=403,PosX=90,PosZ=31},  
        --传送点(居庸关到克烈)                                    
        juyongguan2tataer0={newSceneId=101,PosX=127,PosZ=218},     
        juyongguan2tataer1={newSceneId=201,PosX=127,PosZ=218},     
        juyongguan2tataer2={newSceneId=301,PosX=127,PosZ=218},     
        juyongguan2tataer3={newSceneId=401,PosX=127,PosZ=218},  
         --传送点(居庸关到大都西)                                    
        juyongguan2dadu0={newSceneId=38,PosX=167,PosZ=26},     
        juyongguan2dadu1={newSceneId=38,PosX=167,PosZ=26},     
        juyongguan2dadu2={newSceneId=38,PosX=167,PosZ=26},     
        juyongguan2dadu3={newSceneId=38,PosX=167,PosZ=26},  
         --传送点(大都到居庸关)                                    
        dadu2juyongguan0={newSceneId=103,PosX=205,PosZ=230},     
        dadu2juyongguan1={newSceneId=203,PosX=205,PosZ=230},     
        dadu2juyongguan2={newSceneId=303,PosX=205,PosZ=230},     
        dadu2juyongguan3={newSceneId=403,PosX=205,PosZ=230},  
         --传送点(碎叶城到撒马尔罕)（改红沙漠到撒马尔罕）                                    
        suiyecheng2samaerhan={newSceneId=11,PosX=233,PosZ=163},     
        suiyecheng2samaerhan={newSceneId=11,PosX=233,PosZ=163},     
        suiyecheng2samaerhan={newSceneId=11,PosX=233,PosZ=163},     
        suiyecheng2samaerhan={newSceneId=11,PosX=233,PosZ=163},  
         --传送点(碎叶城到红沙漠)                                    
        suiyecheng2hongshamo={newSceneId=10,PosX=229,PosZ=140},     
        suiyecheng2hongshamo={newSceneId=10,PosX=229,PosZ=140},     
        suiyecheng2hongshamo={newSceneId=10,PosX=229,PosZ=140},     
        suiyecheng2hongshamo={newSceneId=10,PosX=229,PosZ=140},  
         --传送点(撒马尔罕到碎叶城)（改撒马尔罕到红沙漠）                                    
        samaerhan2suiyecheng={newSceneId=10,PosX=36,PosZ=124},     
        samaerhan2suiyecheng={newSceneId=10,PosX=36,PosZ=124},     
        samaerhan2suiyecheng={newSceneId=10,PosX=36,PosZ=124},     
        samaerhan2suiyecheng={newSceneId=10,PosX=36,PosZ=124},  
        --传送点(红沙漠到碎叶城)                                    
        hongshamo2suiyecheng={newSceneId=9,PosX=24,PosZ=178},     
        hongshamo2suiyecheng={newSceneId=9,PosX=24,PosZ=178},     
        hongshamo2suiyecheng={newSceneId=9,PosX=24,PosZ=178},     
        hongshamo2suiyecheng={newSceneId=9,PosX=24,PosZ=178},  
         --传送点(红沙漠到巴格达) (改撒马尔罕到巴格达)                                    
        hongshamo2bageda={newSceneId=13,PosX=222,PosZ=158},     
        hongshamo2bageda={newSceneId=13,PosX=222,PosZ=158},     
        hongshamo2bageda={newSceneId=13,PosX=222,PosZ=158},     
        hongshamo2bageda={newSceneId=13,PosX=222,PosZ=158},  
         --传送点(巴格达到莫斯科)                                   
        bageda2mosike1={newSceneId=17,PosX=188,PosZ=230},     
        bageda2mosike2={newSceneId=17,PosX=188,PosZ=230},     
        bageda2mosike3={newSceneId=17,PosX=188,PosZ=230},     
        bageda2mosike4={newSceneId=17,PosX=188,PosZ=230},  
        --传送点(巴格达到红沙漠)  （改巴格达到撒马尔罕）                                     
        bageda2hongshamo={newSceneId=11,PosX=18,PosZ=126},     
        bageda2hongshamo={newSceneId=11,PosX=18,PosZ=126},     
        bageda2hongshamo={newSceneId=11,PosX=18,PosZ=126},     
        bageda2hongshamo={newSceneId=11,PosX=18,PosZ=126},  
         --传送点(巴格达到波斯)                                   
        bageda2bosi={newSceneId=16,PosX=65,PosZ=34},     
        bageda2bosi={newSceneId=16,PosX=65,PosZ=34},     
        bageda2bosi={newSceneId=16,PosX=65,PosZ=34},     
        bageda2bosi={newSceneId=16,PosX=65,PosZ=34},  
          --传送点(莫斯科到巴格达)                                 
        mosike2bageda1={newSceneId=13,PosX=34,PosZ=30},     
        mosike2bageda2={newSceneId=13,PosX=34,PosZ=30},     
        mosike2bageda3={newSceneId=13,PosX=34,PosZ=30},     
        mosike2bageda4={newSceneId=13,PosX=34,PosZ=30},  
         --传送点(莫斯科到基辅)                                    
        mosike2jifu={newSceneId=18,PosX=222,PosZ=222},     
        mosike2jifu={newSceneId=18,PosX=222,PosZ=222},     
        mosike2jifu={newSceneId=18,PosX=222,PosZ=222},     
        mosike2jifu={newSceneId=18,PosX=222,PosZ=222},  
         --传送点 （基辅到波兰）                                   
        jifu2bolan0={newSceneId=19,PosX=230,PosZ=148},     
        jifu2bolan1={newSceneId=19,PosX=230,PosZ=148},     
        jifu2bolan2={newSceneId=19,PosX=230,PosZ=148},     
        jifu2bolan3={newSceneId=19,PosX=230,PosZ=148},  
         --传送点（波兰到基辅）                                 
        bolan2jifu0={newSceneId=18,PosX=23,PosZ=62},     
        bolan2jifu1={newSceneId=18,PosX=23,PosZ=62},     
        bolan2jifu2={newSceneId=18,PosX=23,PosZ=62},     
        bolan2jifu3={newSceneId=18,PosX=23,PosZ=62},  
        --传送点(波兰到匈牙利)                                    
        bolan2xiongyali0={newSceneId=20,PosX=228,PosZ=22},     
        bolan2xiongyali1={newSceneId=20,PosX=228,PosZ=22},     
        bolan2xiongyali2={newSceneId=20,PosX=228,PosZ=22},     
        bolan2xiongyali3={newSceneId=20,PosX=228,PosZ=22},  
         --传送点(匈牙利到波兰)                                    
        xiongyali2bolan0={newSceneId=19,PosX=23,PosZ=213},     
        xiongyali2bolan1={newSceneId=19,PosX=23,PosZ=213},     
        xiongyali2bolan2={newSceneId=19,PosX=23,PosZ=213},     
        xiongyali2bolan3={newSceneId=19,PosX=23,PosZ=213},  
         --传送点(匈牙利到圣神罗马)                                    
        xiongyali2luoma={newSceneId=21,PosX=227,PosZ=37},     
        xiongyali2luoma={newSceneId=21,PosX=227,PosZ=37},     
        xiongyali2luoma={newSceneId=21,PosX=227,PosZ=37},     
        xiongyali2luoma={newSceneId=21,PosX=227,PosZ=37},  
        --传送点(神圣罗马到匈牙利)                                    
        luoma2xiongyali={newSceneId=20,PosX=26,PosZ=229},     
        luoma2xiongyali={newSceneId=20,PosX=26,PosZ=229},     
        luoma2xiongyali={newSceneId=20,PosX=26,PosZ=229},     
        luoma2xiongyali={newSceneId=20,PosX=26,PosZ=229},  
         --传送点(基辅到莫斯科)                                    
        jifu2mosike={newSceneId=17,PosX=30,PosZ=66},     
        jifu2mosike={newSceneId=17,PosX=30,PosZ=66},     
        jifu2mosike={newSceneId=17,PosX=30,PosZ=66},     
        jifu2mosike={newSceneId=17,PosX=30,PosZ=66},  
           --传送点(波斯到巴格达)                                    
        bosi2bageda={newSceneId=13,PosX=139,PosZ=227},     
        bosi2bageda={newSceneId=13,PosX=138,PosZ=227},     
        bosi2bageda={newSceneId=13,PosX=138,PosZ=227},     
        bosi2bageda={newSceneId=13,PosX=138,PosZ=227},  
         --传送点(拜占庭到罗马）                                
        baizhanting2luoma0={newSceneId=21,PosX=231,PosZ=217},     
        baizhanting2luoma1={newSceneId=21,PosX=231,PosZ=217},     
        baizhanting2luoma2={newSceneId=21,PosX=231,PosZ=217},     
        baizhanting2luoma3={newSceneId=21,PosX=231,PosZ=217},  
        --传送点(罗马到拜占庭）                                  
        luoma2baizhanting0={newSceneId=22,PosX=34,PosZ=111},     
        luoma2baizhanting1={newSceneId=22,PosX=34,PosZ=111},     
        luoma2baizhanting2={newSceneId=22,PosX=34,PosZ=111},     
        luoma2baizhanting3={newSceneId=22,PosX=34,PosZ=111},  
         --传送点(拜占庭到大马士革)                                    
        baizhanting2damashige0={newSceneId=23,PosX=55,PosZ=68},     
        baizhanting2damashige1={newSceneId=23,PosX=55,PosZ=68},     
        baizhanting2damashige2={newSceneId=23,PosX=55,PosZ=68},     
        baizhanting2damashige3={newSceneId=23,PosX=55,PosZ=68},  
       --传送点(大马士革到拜占庭)                                    
        damashige2baizhanting0={newSceneId=22,PosX=178,PosZ=82},     
        damashige2baizhanting1={newSceneId=22,PosX=178,PosZ=82},     
        damashige2baizhanting2={newSceneId=22,PosX=178,PosZ=82},     
        damashige2baizhanting3={newSceneId=22,PosX=178,PosZ=82},  
         --传送点(大马士革到耶路撒冷)                                    
        damashige2yelusaileng0={newSceneId=24,PosX=133,PosZ=21},     
        damashige2yelusaileng1={newSceneId=24,PosX=133,PosZ=21},     
        damashige2yelusaileng2={newSceneId=24,PosX=133,PosZ=21},     
        damashige2yelusaileng3={newSceneId=24,PosX=133,PosZ=21},  
          --传送点(耶路撒冷到大马士革)                                    
        yelusaileng2damashige0={newSceneId=23,PosX=107,PosZ=233},     
        yelusaileng2damashige1={newSceneId=23,PosX=107,PosZ=233},     
        yelusaileng2damashige2={newSceneId=23,PosX=107,PosZ=233},     
        yelusaileng2damashige3={newSceneId=23,PosX=107,PosZ=233},  
       --传送点(耶路撒冷到西奈半岛)                                    
        yelusaleng2xinaibandao0={newSceneId=25,PosX=121,PosZ=24},     
        yelusaleng2xinaibandao1={newSceneId=25,PosX=121,PosZ=24},     
        yelusaleng2xinaibandao2={newSceneId=25,PosX=121,PosZ=24},     
        yelusaleng2xinaibandao3={newSceneId=25,PosX=121,PosZ=24},  
          --传送点(西奈半岛到耶路撒冷)                                    
        xinaibandao2yelusaleng0={newSceneId=24,PosX=121,PosZ=224},     
        xinaibandao2yelusaleng1={newSceneId=24,PosX=121,PosZ=224},     
        xinaibandao2yelusaleng2={newSceneId=24,PosX=121,PosZ=224},     
        xinaibandao2yelusaleng3={newSceneId=24,PosX=121,PosZ=224},  
        
        
         --传送点(边境上到暗道)                                    
        bianjingshang2andao0={newSceneId=76,PosX=34,PosZ=47},     
        bianjingshang2andao1={newSceneId=176,PosX=218,PosZ=39},     
        bianjingshang2andao2={newSceneId=276,PosX=34,PosZ=47},     
        bianjingshang2andao3={newSceneId=376,PosX=218,PosZ=39},   
        --传送点(边境下到暗道)                                    
        bianjingxia2andao0={newSceneId=76,PosX=37,PosZ=218},     
        bianjingxia2andao1={newSceneId=176,PosX=220,PosZ=208},     
        bianjingxia2andao2={newSceneId=276,PosX=37,PosZ=218},     
        bianjingxia2andao3={newSceneId=376,PosX=220,PosZ=207},   
         --传送点(边境任务到暗道)                                    
        bianjingrenwu2andao0={newSceneId=76,PosX=220,PosZ=37},     
        bianjingrenwu2andao1={newSceneId=176,PosX=35,PosZ=215},     
        bianjingrenwu2andao2={newSceneId=276,PosX=220,PosZ=37},     
        bianjingrenwu2andao3={newSceneId=376,PosX=35,PosZ=215},   
         --传送点(暗道到边境上)                                    
        andao2bianjingshang0={newSceneId=51,PosX=92,PosZ=67},     
        andao2bianjingshang1={newSceneId=151,PosX=159,PosZ=72},     
        andao2bianjingshang2={newSceneId=251,PosX=62,PosZ=72},     
        andao2bianjingshang3={newSceneId=351,PosX=167,PosZ=68},   
        --传送点(暗道到边境下)                                    
        andao2bianjingxai0={newSceneId=51,PosX=69,PosZ=171},     
        andao2bianjingxai1={newSceneId=151,PosX=167,PosZ=172},     
        andao2bianjingxai2={newSceneId=251,PosX=91,PosZ=179},     
        andao2bianjingxai3={newSceneId=351,PosX=182,PosZ=179},   
         --传送点(暗道到边境任务)                                    
        andao2bianjingrenwu0={newSceneId=51,PosX=202,PosZ=135},     
        andao2bianjingrenwu1={newSceneId=151,PosX=39,PosZ=149},     
        andao2bianjingrenwu2={newSceneId=251,PosX=211,PosZ=109},     
        andao2bianjingrenwu3={newSceneId=351,PosX=36,PosZ=97},     
                
        --传送点(边境到一号密室)                                    
        bianjing2mishione0={newSceneId=59,PosX=29,PosZ=26},     
        bianjing2mishione1={newSceneId=159,PosX=29,PosZ=26},     
        bianjing2mishione2={newSceneId=259,PosX=29,PosZ=26},     
        bianjing2mishione3={newSceneId=359,PosX=29,PosZ=26},   
         --传送点(边境到二号密室)                                    
        bianjing2mishitwo0={newSceneId=60,PosX=36,PosZ=24},     
        bianjing2mishitwo1={newSceneId=160,PosX=36,PosZ=24},     
        bianjing2mishitwo2={newSceneId=260,PosX=36,PosZ=24},     
        bianjing2mishitwo3={newSceneId=360,PosX=36,PosZ=24},   
        --传送点(一号密室到边境)                                    
        mishione2bianjing0={newSceneId=51,PosX=178,PosZ=32},     
        mishione2bianjing1={newSceneId=151,PosX=118,PosZ=30},     
        mishione2bianjing2={newSceneId=251,PosX=94,PosZ=211},     
        mishione2bianjing3={newSceneId=351,PosX=95,PosZ=218},   
        --传送点(二号密室到边境)                                    
        mishitwo2bianjing0={newSceneId=51,PosX=97,PosZ=209},     
        mishitwo2bianjing1={newSceneId=151,PosX=172,PosZ=203},     
        mishitwo2bianjing2={newSceneId=251,PosX=94,PosZ=41},     
        mishitwo2bianjing3={newSceneId=351,PosX=144,PosZ=25},     
        --传送点（敦煌边塞洞口）
        dunhuangbiansaidongkou1={newSceneId=351,PosX=144,PosZ=25},
				dunhuangbiansaidongkou2={newSceneId=351,PosX=144,PosZ=25},
        --传送点（昆仑边塞洞口）
        kunlunbiansaidongkou1={newSceneId=251,PosX=94,PosZ=41},
        kunlunbiansaidongkou2={newSceneId=251,PosX=94,PosZ=41},
        --传送点（天山边塞洞口）
        tianshanbiansaidongkou1={newSceneId=151,PosX=172,PosZ=203},
        tianshanbiansaidongkou2={newSceneId=151,PosX=172,PosZ=203},
        --传送点（楼兰边塞洞口）
        loulanbiansaidongkou1={newSceneId=51,PosX=97,PosZ=209},                                                                              
				loulanbiansaidongkou2={newSceneId=51,PosX=97,PosZ=209},
				--传送点（敦煌王城洞口）
				dunhuangwangchengdongkou1={newSceneId=350,PosX=234,PosZ=163},
				dunhuangwangchengdongkou2={newSceneId=350,PosX=234,PosZ=163},
				--传送点（昆仑王城洞口）
				kunlunwangchengdongkou1={newSceneId=250,PosX=21,PosZ=111},
				kunlunwangchengdongkou2={newSceneId=250,PosX=21,PosZ=111},
				--传送点（天山王城洞口）
				tianshanwangchengdongkou1={newSceneId=150,PosX=236,PosZ=152},
				tianshanwangchengdongkou2={newSceneId=150,PosX=236,PosZ=152},
				--传送点（楼兰王城洞口）
				loulanwangchengdongkou1={newSceneId=50,PosX=21,PosZ=92},
				loulanwangchengdongkou2={newSceneId=50,PosX=21,PosZ=92},             
																																
				} 
--  11       楼兰王城       0 
--  18       天山王城       1
--  21       昆仑王城       2
--  24       敦煌王城       3
--  36         大都         



function	x800019_TransferToWorld(sceneId, selfId, Pos)
--	if CJSH_WorldPos[Pos].newSceneId == 50 then
--		local country = GetCurCountry(sceneId,selfId)
--		local countryscene={50,150,250,350}
--		if country == 0 then
--			x800019_TransferFunc(sceneId, selfId, countryscene[country+1], CJSH_WorldPos[Pos].PosX, CJSH_WorldPos[Pos].PosZ)
--		elseif country == 1 then
--			x800019_TransferFunc(sceneId, selfId, countryscene[country+1], CJSH_WorldPos[Pos].PosX, CJSH_WorldPos[Pos].PosZ)
--		elseif country == 2 then
--			x800019_TransferFunc(sceneId, selfId, countryscene[country+1], CJSH_WorldPos[Pos].PosX, CJSH_WorldPos[Pos].PosZ)
--		elseif country == 3 then
--			x800019_TransferFunc(sceneId, selfId, countryscene[country+1], CJSH_WorldPos[Pos].PosX, CJSH_WorldPos[Pos].PosZ)
--		else
--			return
--		end
--	elseif  CJSH_WorldPos[Pos].newSceneId == 51 then
--		local country = GetCurCountry(sceneId,selfId)
--		local bianjingscene={51,151,251,351}
--		if country == 0 then
--			x800019_TransferFunc(sceneId, selfId, bianjingscene[country+1], CJSH_WorldPos[Pos].PosX, CJSH_WorldPos[Pos].PosZ)
--		elseif country == 1 then
--			x800019_TransferFunc(sceneId, selfId, bianjingscene[country+1], CJSH_WorldPos[Pos].PosX, CJSH_WorldPos[Pos].PosZ)
--		elseif country == 2 then
--			x800019_TransferFunc(sceneId, selfId, bianjingscene[country+1], CJSH_WorldPos[Pos].PosX, CJSH_WorldPos[Pos].PosZ)
--		elseif country == 3 then
--			x800019_TransferFunc(sceneId, selfId, bianjingscene[country+1], CJSH_WorldPos[Pos].PosX, CJSH_WorldPos[Pos].PosZ)
--		else
--			return
--		end
--	else
		x800019_TransferFunc(sceneId, selfId, CJSH_WorldPos[Pos].newSceneId, CJSH_WorldPos[Pos].PosX, CJSH_WorldPos[Pos].PosZ)
--	end
--	print(CJSH_WorldPos[Pos].newSceneId)
--	print(CJSH_WorldPos[Pos].PosX)
--	print(CJSH_WorldPos[Pos].PosZ)
end

--����ģ��


x800019_g_BusMaxFollowDist = 10		--BUS����������Ч���� 



--��Ӹ���״̬�£��ӳ�����ʱ�������Ҳ��������
function	x800019_TransferFunc(sceneId, selfId, newSceneId, PosX, PosZ)
	--print("��������?")
	--������û�д������״̬,��ֱ�Ӵ���
	local life=IsCharacterLiving( sceneId,selfId)
	if	life==0	then
		return
	else
		if	GetTeamId( sceneId, selfId)<0	then
			local InBus = IsBusMember(sceneId, selfId)
			if InBus == 1 then
				--print("???")
				local BusId = GetBusId(sceneId, selfId)
				local IsLeader = IsTheBusLeader(sceneId, selfId,BusId)   	--˾���ſ��Բ���BUS�糡�� 
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
		--�����Ҵ������״̬����������Ӹ���״̬,��ֱ�Ӵ���
		elseif	IsTeamFollow(sceneId, selfId)~=1	then
			local InBus = IsBusMember(sceneId, selfId)
			if InBus == 1 then
				local BusId = GetBusId(sceneId, selfId)
				local IsLeader = IsTheBusLeader(sceneId, selfId,BusId)   	--˾���ſ��Բ���BUS�糡�� 
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
		--�����Ҵ�����Ӹ���״̬,������Ƕӳ�,��С�Ӵ���
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
		--�����Ҵ�����Ӹ���״̬,�Ҳ��Ƕӳ�,�򡭡����Է�����ϢҲ�ð�
		end
	end
end


function	x800019_BusTransfer(sceneId,BusId,newSceneId, posX, posY)
--	print("ս������?")
	local num = GetBusMemberCount(sceneId, BusId)
	--if num <= 0 then
	--	return
	--end
	if sceneId == newSceneId then
		--ͬ��ͼս���Ĵ���
		SetPos(sceneId, BusId,posX,posY)
	else
		--ע�⣺�˲����Ǳ����.BUS�л�������Ҫ����Щ׼������,
		ReadyBusChangeScene(sceneId, newSceneId,BusId)
		
		for	i=0,num-1 do
			local ObjID = GetBusMemberObjId(sceneId,BusId,i)
			if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,ObjID,newSceneId) == 0 then
						return
			end
			NewWorld(sceneId, ObjID, newSceneId, posX, posY, 800019)
		end
		
		--ɾ��BUS,����Ա���ڳ���
		DeleteBus(sceneId, BusId,0)		
	end
end

--��һ�������¼��Ϸ���������õ������
	CJSH_WorldPos= {

				--trap��(�߾�ͨ������)
				loulanbianjing2wangcheng={newSceneId=73,PosX=418,PosZ=477},
				laiyinbianjing2wangcheng={newSceneId=150,PosX=418,PosZ=477},
				kunlunbianjing2wangcheng={newSceneId=250,PosX=418,PosZ=477},
				dunhuangbianjing2wangcheng={newSceneId=350,PosX=418,PosZ=477},
				--trap��(����ͨ���߾�)
				loulanwangcheng2bianjing={newSceneId=74,PosX=36,PosZ=60},
				laiyinwangcheng2bianjing={newSceneId=151,PosX=36,PosZ=60},
				kunlunwangcheng2bianjing={newSceneId=251,PosX=36,PosZ=60},
				dunhuangwangcheng2bianjing={newSceneId=351,PosX=36,PosZ=60},
				
				--trap��(����ͨ���߾�)
				--dadu2loulanbianjing={newSceneId=51,PosX=486,PosZ=473},
				--dadu2laiyinbianjing={newSceneId=151,PosX=486,PosZ=473},
				--dadu2kunlunbianjing={newSceneId=251,PosX=486,PosZ=473},
				--dadu2dunhuangbianjing={newSceneId=351,PosX=486,PosZ=473},
				--trap��(�߾�ͨ������)
				--loulanbianjing2helin={newSceneId=17,PosX=267,PosZ=486},
				
				--trap��(����ͨ����)
				--bianjing2dadu={newSceneId=0,PosX=29,PosZ=362},
				
				--trap��(����ͨ���߾�)
				--helin2daduloulan={newSceneId=51,PosX=479,PosZ=80},
				--helin2dadulaiyin={newSceneId=151,PosX=479,PosZ=80},
			  --helin2dadukunlun={newSceneId=251,PosX=479,PosZ=80},
				--helin2dadudunhuang={newSceneId=351,PosX=479,PosZ=80},
				
				--trap��(��ͨ������)
				--dadu2helin={newSceneId=17,PosX=483,PosZ=470},		
				
				--trap��(�߾�ͨ��1ͨ����ˮ��)
				loulanbianjingenter2xiaoshuidao={newSceneId=76,PosX=51,PosZ=12},		
				laiyinbianjingenter2xiaoshuidao={newSceneId=176,PosX=51,PosZ=12},		
				kunlunbianjingenter2xiaoshuidao={newSceneId=276,PosX=51,PosZ=12},		
				dunhuangbianjingenter2xiaoshuidao={newSceneId=376,PosX=51,PosZ=12},		

				--trap��(�߾�ͨ��2ͨ����ˮ��)
				loulanbianjingexit2xiaoshuidao={newSceneId=76,PosX=12,PosZ=51},		
				laiyinbianjingexit2xiaoshuidao={newSceneId=176,PosX=12,PosZ=51},		
				kunlunbianjingexit2xiaoshuidao={newSceneId=276,PosX=12,PosZ=51},				
				dunhuangbianjingexit2xiaoshuidao={newSceneId=376,PosX=12,PosZ=51},				

				--trap��(��ˮ��ͨ���߾���ͨ����)  ����ˮ�����߾���������
				loulanbianjingexit2xiaoshuidaowest={newSceneId=51,PosX=61,PosZ=169},		
				laiyinbianjingexit2xiaoshuidaowest={newSceneId=151,PosX=191,PosZ=175},	
				kunlunbianjingexit2xiaoshuidaowest={newSceneId=251,PosX=95,PosZ=178},		
				dunhuangbianjingexit2xiaoshuidaowest={newSceneId=351,PosX=190,PosZ=182},		

				--trap��(��ˮ��ͨ���߾���ͨ����)  ����ˮ�����߾��󶼷���
				loulanbianjingexit2xiaoshuidaoeast={newSceneId=51,PosX=97,PosZ=70},		
				laiyinbianjingexit2xiaoshuidaoeast={newSceneId=151,PosX=163,PosZ=72},		
				kunlunbianjingexit2xiaoshuidaoeast={newSceneId=251,PosX=58,PosZ=75},		
				dunhuangbianjingexit2xiaoshuidaoeast={newSceneId=351,PosX=187,PosZ=69},		

				--trap��(����ͨ�����ִ�)(���ǵ��Գ�)
				loulanwangcheng2xinshoucun={newSceneId=89,PosX=17,PosZ=145},
				laiyinwangcheng2xinshoucun={newSceneId=189,PosX=239,PosZ=124},
				kunlunwangcheng2xinshoucun={newSceneId=289,PosX=19,PosZ=134},
				dunhuangwangcheng2xinshoucun={newSceneId=389,PosX=230,PosZ=124},
				--trap��(����ͨ�����ִ�)���Գ������ǣ�
				loulanxinshoucun2wangcheng={newSceneId=50,PosX=244,PosZ=119},
				laiyinxinshoucun2wangcheng={newSceneId=150,PosX=13,PosZ=124},
				kunlunxinshoucun2wangcheng={newSceneId=250,PosX=242,PosZ=136},
				dunhuangxinshoucun2wangcheng={newSceneId=350,PosX=13,PosZ=141}, 			
				--trap��(�󶼵��󶼶�)
				loulanwangcheng2wenquancun={newSceneId=37,PosX=25,PosZ=138},
				laiyinwangcheng2wenquancun={newSceneId=37,PosX=25,PosZ=138},
				kunlunwangcheng2wenquancun={newSceneId=37,PosX=25,PosZ=138},
				dunhuangwangcheng2wenquancun={newSceneId=37,PosX=25,PosZ=138},
				--trap��(�󶼶�����)
				loulanwenquancun2wangcheng={newSceneId=0,PosX=219,PosZ=127},
				laiyinwenquancun2wangcheng={newSceneId=0,PosX=219,PosZ=127},
				kunlunwenquancun2wangcheng={newSceneId=0,PosX=219,PosZ=127},
				dunhuangwenquancun2wangcheng={newSceneId=0,PosX=219,PosZ=127},
				--trap��(�󶼵��ʳ�)
				dadu2huangcheng0={newSceneId=41,PosX=64,PosZ=113},
				dadu2huangcheng1={newSceneId=41,PosX=64,PosZ=113},
				dadu2huangcheng2={newSceneId=41,PosX=64,PosZ=113},
				dadu2huangcheng3={newSceneId=41,PosX=64,PosZ=113},
				--trap��(�ʳǵ���)
				huangcheng2dadu0={newSceneId=0,PosX=127,PosZ=34},
				huangcheng2dadu1={newSceneId=0,PosX=127,PosZ=34},
				huangcheng2dadu2={newSceneId=0,PosX=127,PosZ=34},
				huangcheng2dadu3={newSceneId=0,PosX=127,PosZ=34},
				--trap��(�󶼵�����)
				loulanwangcheng2fenglingdu={newSceneId=38,PosX=227,PosZ=148},
				laiyinwangcheng2fenglingdu={newSceneId=38,PosX=227,PosZ=148},
				kunlunwangcheng2fenglingdu={newSceneId=38,PosX=227,PosZ=148},
				dunhuangwangcheng2fenglingdu={newSceneId=38,PosX=227,PosZ=148},
				--trap��(��������)
				loulanfenglingdu2wangcheng={newSceneId=0,PosX=31,PosZ=127},
				laiyinfenglingdu2wangcheng={newSceneId=0,PosX=31,PosZ=127},
				kunlunfenglingdu2wangcheng={newSceneId=0,PosX=31,PosZ=127},
				dunhuangfenglingdu2wangcheng={newSceneId=0,PosX=31,PosZ=127},
				--���͵�(�󶼵�������)(�Ĵ󶼵�����)
				dadu2baodingloulan={newSceneId=36,PosX=127,PosZ=32},
				dadu2baodinglaiyin={newSceneId=36,PosX=127,PosZ=32},
				dadu2baodingkunlun={newSceneId=36,PosX=127,PosZ=32},
				dadu2baodingdunhuang={newSceneId=36,PosX=127,PosZ=32},

				--���͵�(����������)(�Ĵ��ϵ���)
				baoding2dadu={newSceneId=0,PosX=128,PosZ=220},
				----NPC����(PVE�Թ�ͨ������)
				--loulanmigong2wangcheng={newSceneId=50,PosX=271,PosZ=34},
				--laiyinmigong2wangcheng={newSceneId=150,PosX=271,PosZ=34},
				--kunlunmigong2wangcheng={newSceneId=250,PosX=271,PosZ=34},
				--dunhuangmigong2wangcheng={newSceneId=350,PosX=271,PosZ=34},				
				--
				--trap��(����ͨ����������)      �����ϵ����踮��
				loulanwangcheng2machang={newSceneId=5,PosX=129,PosZ=29},
				laiyinwangcheng2machang={newSceneId=5,PosX=129,PosZ=29},
				kunlunwangcheng2machang={newSceneId=5,PosX=129,PosZ=29},
				dunhuangwangcheng2machang={newSceneId=5,PosX=129,PosZ=29},
				--trap��(��������ͨ������)   �����踮�����ϣ�
				loulanmachang2wangcheng={newSceneId=36,PosX=181,PosZ=233},
				laiyinmachang2wangcheng={newSceneId=36,PosX=181,PosZ=233},
				kunlunmachang2wangcheng={newSceneId=36,PosX=181,PosZ=233},
				dunhuangmachang2wangcheng={newSceneId=36,PosX=181,PosZ=233},
				--
				--trap��(�����ͨ����������)  (�Ľ����ͨ������)
				jinge2tieqiloulan={newSceneId=87,PosX=42,PosZ=33},
				jinge2tieqitianshan={newSceneId=187,PosX=100,PosZ=100},
				jinge2tieqikunlun={newSceneId=287,PosX=220,PosZ=139},
				jinge2tieqidunhuang={newSceneId=387,PosX=100,PosZ=100},
				                                                     
				--trap��(��������ͨ�������)  (������ͨ�������)                     
				tieqi2jingeloulan={newSceneId=19,PosX=100,PosZ=100},  
				tieqi2jingetianshan={newSceneId=19,PosX=100,PosZ=100},
				tieqi2jingekunlun={newSceneId=19,PosX=100,PosZ=100}, 
				tieqi2jingedunhuang={newSceneId=19,PosX=100,PosZ=100},
				
				----���͵�(����³��)
				--dadusuluding={newSceneId=0,PosX=261,PosZ=203},
				----���͵�(������³��)
				loulansuluding={newSceneId=50,PosX=127,PosZ=29},
				laiyinsuluding={newSceneId=150,PosX=128,PosZ=29},
				kunlunsuluding={newSceneId=250,PosX=126,PosZ=211},
				dunhuangsuluding={newSceneId=350,PosX=128,PosZ=226},

				--���͵�(����������ͬ��)(�ķ��踮���ݳ�)
				baoding2datongloulan={newSceneId=6,PosX=62,PosZ=23},
				baoding2datonglaiyin={newSceneId=6,PosX=62,PosZ=23},
				baoding2datongkunlun={newSceneId=6,PosX=62,PosZ=23},
				baoding2datongdunhuang={newSceneId=6,PosX=62,PosZ=23},
				
				--���͵�(��ͬ����������)(�Ĳ��ݵ����踮)
				datong2baodingloulan={newSceneId=5,PosX=130,PosZ=220},
				datong2baodinglaiyin={newSceneId=5,PosX=130,PosZ=220},
				datong2baodingkunlun={newSceneId=5,PosX=130,PosZ=220},
				datong2baodingdunhuang={newSceneId=5,PosX=130,PosZ=220},

				--���͵�(��������������) (�Ĳ��ݵ�����)   
				baoding2jiningloulan={newSceneId=7,PosX=164,PosZ=26},
				baoding2jininglaiyin={newSceneId=7,PosX=164,PosZ=26},
				baoding2jiningkunlun={newSceneId=7,PosX=164,PosZ=26},
				baoding2jiningdunhuang={newSceneId=7,PosX=164,PosZ=26},

			  --���͵�(��������������) �������뵽���ݣ�
				jining2baodingloulan={newSceneId=6,PosX=128,PosZ=228},
				jining2baodinglaiyin={newSceneId=6,PosX=128,PosZ=228},
				jining2baodingkunlun={newSceneId=6,PosX=128,PosZ=228},
				jining2baodingdunhuang={newSceneId=6,PosX=128,PosZ=228},
				
				--���͵�(����·��������)(��̩ɽ��������)
				jining2weihailoulan={newSceneId=15,PosX=34,PosZ=109},
				jining2weihailaiyin={newSceneId=15,PosX=34,PosZ=109},
				jining2weihaikunlun={newSceneId=15,PosX=34,PosZ=109},
				jining2weihaidunhuang={newSceneId=15,PosX=34,PosZ=109},
				
				--���͵�(�����۵�����·)(�������۵�̩ɽ)
				weihai2jiningloulan={newSceneId=2,PosX=226,PosZ=137},
				weihai2jininglaiyin={newSceneId=2,PosX=226,PosZ=137},
				weihai2jiningkunlun={newSceneId=2,PosX=226,PosZ=137},
				weihai2jiningdunhuang={newSceneId=2,PosX=226,PosZ=137},
				
				--���͵�(����·������·)
			  --baoding2anqingloulan={newSceneId=22,PosX=185,PosZ=18},
				--baoding2anqinglaiyin={newSceneId=22,PosX=185,PosZ=18},
				--baoding2anqingkunlun={newSceneId=22,PosX=185,PosZ=18},
				--baoding2anqingdunhuang={newSceneId=22,PosX=185,PosZ=18},
				
				--���͵�(����·������·)
				--anqing2baodingloulan={newSceneId=16,PosX=194,PosZ=228},
				--anqing2baodinglaiyin={newSceneId=16,PosX=194,PosZ=228},
				--anqing2baodingkunlun={newSceneId=16,PosX=194,PosZ=228},
				--anqing2baodingdunhuang={newSceneId=16,PosX=194,PosZ=228},
				
				--���䴫��
				--dixialiangcang={newSceneId=2,PosX=11,PosZ=112},
				--xianrenguloulanin={newSceneId=7,PosX=25,PosZ=24},
				--xianrengulaiyinin={newSceneId=7,PosX=102,PosZ=20},
				--xianrengukunlunin={newSceneId=7,PosX=97,PosZ=100},
				--xianrengudunhuangin={newSceneId=7,PosX=25,PosZ=101},				
				----���͵�(���ִ���)
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
			
				----���͵�(���˹ȴ���)
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
			
				----���䴫�ͻع�
				--biwu2loulan={newSceneId=50,PosX=227,PosZ=239},
				--biwu2laiyin={newSceneId=150,PosX=227,PosZ=239},				
				--biwu2kunlun={newSceneId=250,PosX=227,PosZ=239},				
				--biwu2dunhuang={newSceneId=350,PosX=227,PosZ=239},		
        --���͵�(̩ɽ���󶼶�)                                        
        taishan2daduloulan={newSceneId=37,PosX=223,PosZ=75},       
        taishan2dadutianshan={newSceneId=37,PosX=223,PosZ=75},       
        taishan2dadukunlun={newSceneId=37,PosX=223,PosZ=75},       
        taishan2dadudunhuang={newSceneId=37,PosX=223,PosZ=75},     
       --���͵�(�󶼵�̩ɽ)                                                                                                
        dadu2taishanloulan={newSceneId=2,PosX=24,PosZ=144},                                                               
        dadu2taishantianshan={newSceneId=2,PosX=24,PosZ=144},                                                             
        dadu2taishankunlun={newSceneId=2,PosX=24,PosZ=144},                                                               
        dadu2taishandunhuang={newSceneId=2,PosX=24,PosZ=144},                                                             
       --���͵�(̫��ɽ������)                                    
        taihangshan2daduloulan={newSceneId=38,PosX=24,PosZ=222},   
        taihangshan2dadutianshan={newSceneId=38,PosX=24,PosZ=222}, 
        taihangshan2dadukunlun={newSceneId=38,PosX=24,PosZ=222},   
        taihangshan2dadudunhuang={newSceneId=38,PosX=24,PosZ=222}, 
       --���͵�(�󶼵�̫��ɽ)                                     
        dadu2taihangshanloulan={newSceneId=4,PosX=219,PosZ=33},    
        dadu2taihangshantianshan={newSceneId=4,PosX=219,PosZ=33},  
        dadu2taihangshankunlun={newSceneId=4,PosX=219,PosZ=33},    
        dadu2taihangshandunhuang={newSceneId=4,PosX=219,PosZ=33},   
       --���͵�(̫��ɽ������)                                        
        taihangshan2hexiloulan={newSceneId=3,PosX=225,PosZ=131},   
        taihangshan2hexitianshan={newSceneId=3,PosX=225,PosZ=131}, 
        taihangshan2hexikunlun={newSceneId=3,PosX=225,PosZ=131},   
        taihangshan2hexidunhuang={newSceneId=3,PosX=225,PosZ=131}, 
       --���͵�(���˸���̫��ɽ)                                       
        hexi2taihangshanloulan={newSceneId=4,PosX=52,PosZ=187},    
        hexi2taihangshantianshan={newSceneId=4,PosX=52,PosZ=187},  
        hexi2taihangshankunlun={newSceneId=4,PosX=52,PosZ=187},    
        hexi2taihangshandunhuang={newSceneId=4,PosX=52,PosZ=187},      
       --���͵�(��ɽ������)   (��ɽ�����˸�)                                         
        jinshan2hexiloulan={newSceneId=3,PosX=30,PosZ=126},        
        jinshan2hexitianshan={newSceneId=3,PosX=30,PosZ=126},      
        jinshan2hexikunlun={newSceneId=3,PosX=30,PosZ=126},        
        jinshan2hexidunhuang={newSceneId=3,PosX=30,PosZ=126},      
        --���͵�(��������ɽ)  (���˸�����ɽ)                                          
        hexi2jinshanloulan={newSceneId=8,PosX=225,PosZ=164},         
        hexi2jinshantianshan={newSceneId=8,PosX=225,PosZ=164},       
        hexi2jinshankunlun={newSceneId=8,PosX=225,PosZ=164},         
        hexi2jinshandunhuang={newSceneId=8,PosX=225,PosZ=164},    
        --���͵�(��ɽ��Ҷ����)  (�Ľ�ɽ����Ҷ��)                                     
        jinshan2yemililoulan={newSceneId=9,PosX=228,PosZ=69},      
        jinshan2yemilitianshan={newSceneId=9,PosX=228,PosZ=69},    
        jinshan2yemilikunlun={newSceneId=9,PosX=228,PosZ=69},      
        jinshan2yemilidunhuang={newSceneId=9,PosX=228,PosZ=69},    
        --���͵�(Ҷ��������ɽ)   (��Ҷ�ǵ�������ɽ)                                      
        yemili2jinshanloulan={newSceneId=8,PosX=30,PosZ=113},       
        yemili2jinshantianshan={newSceneId=8,PosX=30,PosZ=113},     
        yemili2jinshankunlun={newSceneId=8,PosX=30,PosZ=113},       
        yemili2jinshandunhuang={newSceneId=8,PosX=30,PosZ=113},  
         --���͵�(���˸�������)                                       
        hexi2bianjingloulan={newSceneId=51,PosX=180,PosZ=214},       
        hexi2bianjingtianshan={newSceneId=151,PosX=69,PosZ=225},     
        hexi2bianjingkunlun={newSceneId=251,PosX=174,PosZ=36},       
        hexi2bianjingdunhuang={newSceneId=351,PosX=70,PosZ=37},  
         --���͵�(�߾������˸�)                                        
        bianjing2hexiloulan={newSceneId=3,PosX=37,PosZ=38},       
        bianjing2hexitianshan={newSceneId=3,PosX=226,PosZ=34},     
        bianjing2hexikunlun={newSceneId=3,PosX=43,PosZ=216},       
        bianjing2hexidunhuang={newSceneId=3,PosX=220,PosZ=220},  
        --���͵�(�������ݳ�) (�ı������ŵ�)                                       
        bianjing2caochangloulan={newSceneId=86,PosX=133,PosZ=207},             
        bianjing2caochangtianshan={newSceneId=186,PosX=132,PosZ=205},     
        bianjing2caochangkunlun={newSceneId=286,PosX=117,PosZ=40},       
        bianjing2caochangdunhuang={newSceneId=386,PosX=110,PosZ=40},  
        --���͵�(�ݳ�������) ���Ĺŵ���������                                       
        caochang2bianjingloulan={newSceneId=51,PosX=34,PosZ=33},       
        caochang2bianjingtianshan={newSceneId=151,PosX=220,PosZ=36},     
        caochang2bianjingkunlun={newSceneId=251,PosX=46,PosZ=216},       
        caochang2bianjingdunhuang={newSceneId=351,PosX=202,PosZ=200},  
         --���͵�(�������ŵ�)                                        
        bianjing2gudaoloulan={newSceneId=86,PosX=96,PosZ=240},       
        bianjing2gudaotianshan={newSceneId=186,PosX=135,PosZ=208},     
        bianjing2gudaokunlun={newSceneId=286,PosX=125,PosZ=38},       
        bianjing2gudaodunhuang={newSceneId=386,PosX=117,PosZ=38},  
         --���͵�(�ŵ�������)                                        
        --gudao2bianjingloulan={newSceneId=89,PosX=124,PosZ=13},       
        --gudao2bianjingtianshan={newSceneId=189,PosX=116,PosZ=27},     
        --gudao2bianjingkunlun={newSceneId=289,PosX=218,PosZ=225},       
        --gudao2bianjingdunhuang={newSceneId=389,PosX=43,PosZ=210},   
         --���͵�(�������ݳ�)   ������ǵ����ǣ�                                    
        muchang2caochangloulan={newSceneId=50,PosX=128,PosZ=236},       
        muchang2caochangtianshan={newSceneId=150,PosX=126,PosZ=235},     
        muchang2caochangkunlun={newSceneId=250,PosX=128,PosZ=11},       
        muchang2caochangdunhuang={newSceneId=350,PosX=128,PosZ=11},  
         --���͵�(�ݳ�������)   (�����ǵ����)                                     
        caochang2muchangloulan={newSceneId=58,PosX=126,PosZ=40},     
        caochang2muchangtianshan={newSceneId=158,PosX=126,PosZ=40},     
        caochang2muchangkunlun={newSceneId=258,PosX=128,PosZ=225},       
        caochang2muchangdunhuang={newSceneId=358,PosX=128,PosZ=225},      
       --���͵�(���ǵ�����)                                        
        wangcheng2gudaoloulan={newSceneId=87,PosX=235,PosZ=172},       
        wangcheng2gudaotianshan={newSceneId=187,PosX=11,PosZ=140},     
        wangcheng2gudaokunlun={newSceneId=287,PosX=232,PosZ=75},       
        wangcheng2gudaodunhuang={newSceneId=387,PosX=21,PosZ=73}, 
        --���͵�(�ŵ�������) ���Ĺŵ�����ǣ�                                       
        gudao2wangchengloulan={newSceneId=58,PosX=131,PosZ=213},       
        gudao2wangchengtianshan={newSceneId=158,PosX=130,PosZ=212},     
        gudao2wangchengkunlun={newSceneId=258,PosX=127,PosZ=40},       
        gudao2wangchengdunhuang={newSceneId=358,PosX=127,PosZ=40},              
       --���͵�(���ǵ��ŵ�)  ������ǵ��ŵ���                                       
        wangcheng2muchangloulan={newSceneId=86,PosX=116,PosZ=32},       
        wangcheng2muchangtianshan={newSceneId=186,PosX=110,PosZ=44},     
        wangcheng2muchangkunlun={newSceneId=286,PosX=120,PosZ=224},       
        wangcheng2muchangdunhuang={newSceneId=386,PosX=150,PosZ=219}, 
        --���͵�(����������)                                        
        muchang2wangchengloulan={newSceneId=50,PosX=13,PosZ=126},       
        muchang2wangchengtianshan={newSceneId=150,PosX=240,PosZ=115},     
        muchang2wangchengkunlun={newSceneId=250,PosX=13,PosZ=138},       
        muchang2wangchengdunhuang={newSceneId=350,PosX=242,PosZ=138},   
        --- --���͵�(����ڣ1���ŵ�)                                        
        ---jiangjunone2wangguogudao={newSceneId=86,PosX=64,PosZ=230},       
        ---jiangjunone2wangguogudao={newSceneId=186,PosX=64,PosZ=230},     
        ---jiangjunone2wangguogudao={newSceneId=286,PosX=64,PosZ=230},       
        ---jiangjunone2wangguogudao={newSceneId=386,PosX=64,PosZ=230},   
         --���͵�(�ŵ�������ڣ1)   ����Ϊ����ʿ�ﵽҮ·���䣩                                     
        wangguogudao2jiangjunone={newSceneId=24,PosX=9,PosZ=115},       
        wangguogudao2jiangjunone={newSceneId=24,PosX=9,PosZ=115},     
        wangguogudao2jiangjunone={newSceneId=24,PosX=9,PosZ=115},       
        wangguogudao2jiangjunone={newSceneId=24,PosX=9,PosZ=115},   
         --���͵�(����ڣ1������ڣ2) (��Ү·���䵽����ʿ��)                                       
        jiangjunone2jiangjuntwo={newSceneId=23,PosX=96,PosZ=13},       
        jiangjunone2jiangjuntwo={newSceneId=23,PosX=96,PosZ=13},    
        jiangjunone2jiangjuntwo={newSceneId=23,PosX=96,PosZ=13},          
        jiangjunone2jiangjuntwo={newSceneId=23,PosX=96,PosZ=13},    
         --���͵�(����ڣ2������ڣ1) ����Ү·���䵽���Σ�                                        
         jiangjuntwo2jiangjunone={newSceneId=25,PosX=108,PosZ=22},       
         jiangjuntwo2jiangjunone={newSceneId=25,PosX=108,PosZ=22},  
         jiangjuntwo2jiangjunone={newSceneId=25,PosX=108,PosZ=22},       
         jiangjuntwo2jiangjunone={newSceneId=25,PosX=108,PosZ=22},  
        --���͵�(����ڣ2������ڣ3) �������ε�Ү·���䣩                                      
         jiangjuntwo2jiangjunshree={newSceneId=24,PosX=94,PosZ=14},       
         jiangjuntwo2jiangjunshree={newSceneId=24,PosX=94,PosZ=14},     
         jiangjuntwo2jiangjunshree={newSceneId=24,PosX=94,PosZ=14},        
         jiangjuntwo2jiangjunshree={newSceneId=24,PosX=94,PosZ=14},      
         --���͵�(������������1) (�������޵�צ��)                                 
        biansai2futuone={newSceneId=34,PosX=9,PosZ=115},           
        biansai2futuone={newSceneId=34,PosX=9,PosZ=115},           
        biansai2futuone={newSceneId=34,PosX=9,PosZ=115},           
        biansai2futuone={newSceneId=34,PosX=9,PosZ=115},           
         --���͵�(������1��������2) ����צ�۵������ޣ�                              
        futuone2fututwo={newSceneId=33,PosX=96,PosZ=13},           
        futuone2fututwo={newSceneId=33,PosX=96,PosZ=13},           
        futuone2fututwo={newSceneId=33,PosX=96,PosZ=13},           
        futuone2fututwo={newSceneId=33,PosX=96,PosZ=13},           
         --���͵�(������2��������1) ����צ�۵����Ŵ�����                              
         fututwo2futuone={newSceneId=35,PosX=108,PosZ=22},         
         fututwo2futuone={newSceneId=35,PosX=108,PosZ=22},         
         fututwo2futuone={newSceneId=35,PosX=108,PosZ=22},         
         fututwo2futuone={newSceneId=35,PosX=108,PosZ=22},         
        --���͵�(������2��������3)   �������Ŵ�����צ�ۣ�                             
         fututwo2futushree={newSceneId=34,PosX=94,PosZ=14},        
         fututwo2futushree={newSceneId=34,PosX=94,PosZ=14},        
         fututwo2futushree={newSceneId=34,PosX=94,PosZ=14},        
         fututwo2futushree={newSceneId=34,PosX=94,PosZ=14},        
        ----���͵�(������3��������2)                                
        --futushree2fututwo={newSceneId=6,PosX=10,PosZ=15},         
        --futushree2fututwo={newSceneId=6,PosX=10,PosZ=15},         
        --futushree2fututwo={newSceneId=6,PosX=10,PosZ=15},         
        --futushree2fututwo={newSceneId=6,PosX=10,PosZ=15},  
        --���͵�(���1�����˸�) �������뵽����                                     
        wanfoone2zhongxingfu={newSceneId=30,PosX=64,PosZ=230},             
        wanfoone2zhongxingfu={newSceneId=30,PosX=64,PosZ=230},            
        wanfoone2zhongxingfu={newSceneId=30,PosX=64,PosZ=230},            
        wanfoone2zhongxingfu={newSceneId=30,PosX=64,PosZ=230},            
         --���͵�(���˸������1) ���Ĵ������룩                                     
        zhongxingfu2wanfoone={newSceneId=8,PosX=80,PosZ=228},               
        zhongxingfu2wanfoone={newSceneId=8,PosX=80,PosZ=228},               
        zhongxingfu2wanfoone={newSceneId=8,PosX=80,PosZ=228},               
        zhongxingfu2wanfoone={newSceneId=8,PosX=80,PosZ=228},               
         --���͵�(���1�����2) ���Ĵ�����飩                                  
        wanfoone2wanfotwo={newSceneId=7,PosX=96,PosZ=13},           
        wanfoone2wanfotwo={newSceneId=7,PosX=96,PosZ=13},           
        wanfoone2wanfotwo={newSceneId=7,PosX=96,PosZ=13},           
        wanfoone2wanfotwo={newSceneId=7,PosX=96,PosZ=13},           
         --���͵�(���2�����1) ������鵽����                                     
         wanfotwo2wanfoone={newSceneId=30,PosX=108,PosZ=22},         
         wanfotwo2wanfoone={newSceneId=30,PosX=108,PosZ=22},         
         wanfotwo2wanfoone={newSceneId=30,PosX=108,PosZ=22},         
         wanfotwo2wanfoone={newSceneId=30,PosX=108,PosZ=22},         
        --���͵�(���2�����3)   ������鵽ӡ�Ⱥӣ�                                 
         wanfotwo2wanfoshree={newSceneId=32,PosX=94,PosZ=14},    
         wanfotwo2wanfoshree={newSceneId=32,PosX=94,PosZ=14},    
         wanfotwo2wanfoshree={newSceneId=32,PosX=94,PosZ=14},    
         wanfotwo2wanfoshree={newSceneId=32,PosX=94,PosZ=14},    
        --���͵�(���3�����2)  ��ӡ�Ⱥӵ���飩                                  
        wanfoshree2wanfotwo={newSceneId=31,PosX=10,PosZ=15},     
        wanfoshree2wanfotwo={newSceneId=31,PosX=10,PosZ=15},     
        wanfoshree2wanfotwo={newSceneId=31,PosX=10,PosZ=15},     
        wanfoshree2wanfotwo={newSceneId=31,PosX=10,PosZ=15},        
         --���͵�(ɳ��ˮ��1��ɳ��ˮ��2)  ���Ķ��������ԣ�                                 
        shaheone2shahetwo={newSceneId=27,PosX=96,PosZ=13},           
        shaheone2shahetwo={newSceneId=27,PosX=96,PosZ=13},           
        shaheone2shahetwo={newSceneId=27,PosX=96,PosZ=13},           
        shaheone2shahetwo={newSceneId=27,PosX=96,PosZ=13},           
         --���͵�(ɳ��ˮ��2��ɳ��ˮ��1)   ���ĸ��Ե�������                                
         shahetwo2shaheone={newSceneId=26,PosX=108,PosZ=22},         
         shahetwo2shaheone={newSceneId=26,PosX=108,PosZ=22},         
         shahetwo2shaheone={newSceneId=26,PosX=108,PosZ=22},         
         shahetwo2shaheone={newSceneId=26,PosX=108,PosZ=22},         
        --���͵�(ɳ��ˮ��2��ɳ��ˮ��3)   ���ĸ��Ե����ݵ���                                 
         shahetwo2shaheshree={newSceneId=29,PosX=94,PosZ=14},    
         shahetwo2shaheshree={newSceneId=29,PosX=94,PosZ=14},    
         shahetwo2shaheshree={newSceneId=29,PosX=94,PosZ=14},    
         shahetwo2shaheshree={newSceneId=29,PosX=94,PosZ=14},    
        --���͵�(ɳ��ˮ��3��ɳ��ˮ��2)    ���ľ��ݵ����ԣ�                                
        shaheshree2shahetwo={newSceneId=27,PosX=10,PosZ=15},     
        shaheshree2shahetwo={newSceneId=27,PosX=10,PosZ=15},     
        shaheshree2shahetwo={newSceneId=27,PosX=10,PosZ=15},     
        shaheshree2shahetwo={newSceneId=27,PosX=10,PosZ=15}, 
		
		
		--���͵�(���ǵ��Թ�1)                                      
        wangcheng2migongone1={newSceneId=104,PosX=182,PosZ=44},             
        wangcheng2migongone2={newSceneId=204,PosX=68,PosZ=194},            
        wangcheng2migongone3={newSceneId=304,PosX=56,PosZ=68},            
        wangcheng2migongone4={newSceneId=404,PosX=65,PosZ=59},            
         --���͵�(�Թ�1������)                                      
        migongone2wangcheng1={newSceneId=50,PosX=21,PosZ=92},               
        migongone2wangcheng2={newSceneId=150,PosX=236,PosZ=152},               
        migongone2wangcheng3={newSceneId=250,PosX=21,PosZ=110},               
        migongone2wangcheng4={newSceneId=350,PosX=234,PosZ=163}, 
		--���͵�(���ǵ�С��1)                                      
        wangcheng2xiaowuone1={newSceneId=62,PosX=30,PosZ=27},             
        wangcheng2xiaowuone2={newSceneId=162,PosX=30,PosZ=27},            
        wangcheng2xiaowuone3={newSceneId=262,PosX=30,PosZ=27},            
        wangcheng2xiaowuone4={newSceneId=362,PosX=30,PosZ=27},            
         --���͵�(С��1������)                                      
        xiaowuone2wangcheng1={newSceneId=50,PosX=156,PosZ=97},               
        xiaowuone2wangcheng2={newSceneId=150,PosX=92,PosZ=138},               
        xiaowuone2wangcheng3={newSceneId=250,PosX=198,PosZ=159},               
        xiaowuone2wangcheng4={newSceneId=350,PosX=199,PosZ=156}, 
		--���͵�(���ǵ�С��2)                                      
        wangcheng2xiaowutwo1={newSceneId=63,PosX=36,PosZ=25},             
        wangcheng2xiaowutwo2={newSceneId=163,PosX=36,PosZ=25},            
        wangcheng2xiaowutwo3={newSceneId=263,PosX=36,PosZ=25},            
        wangcheng2xiaowutwo4={newSceneId=363,PosX=36,PosZ=25},            
        --���͵�(С��2������)                                      
        xiaowutwo2wangcheng1={newSceneId=50,PosX=56,PosZ=94},               
        xiaowutwo2wangcheng2={newSceneId=150,PosX=162,PosZ=99},               
        xiaowutwo2wangcheng3={newSceneId=250,PosX=207,PosZ=116},               
        xiaowutwo2wangcheng4={newSceneId=350,PosX=69,PosZ=201}, 
		--���͵�(���������)                                      
        biasnai2minju1={newSceneId=61,PosX=30,PosZ=27},             
        biasnai2minju2={newSceneId=161,PosX=30,PosZ=27},            
        biasnai2minju3={newSceneId=261,PosX=30,PosZ=26},            
        biasnai2minju4={newSceneId=361,PosX=30,PosZ=26},            
        --���͵�(��ӵ�����)                                      
        minju2biasnai1={newSceneId=51,PosX=155,PosZ=126},               
        minju2biasnai2={newSceneId=151,PosX=76,PosZ=117},               
        minju2biasnai3={newSceneId=251,PosX=153,PosZ=129},               
        minju2biasnai4={newSceneId=351,PosX=99,PosZ=129}, 
		--���͵�(�󶼵������1)                                      
        dadu2dadumingjuone1={newSceneId=42,PosX=30,PosZ=27},             
        dadu2dadumingjuone2={newSceneId=42,PosX=30,PosZ=27},            
        dadu2dadumingjuone3={newSceneId=42,PosX=30,PosZ=27},            
        dadu2dadumingjuone4={newSceneId=42,PosX=30,PosZ=27},            
        --���͵�(�����1����)                                      
        dadumingjuone2dadu1={newSceneId=0,PosX=195,PosZ=41},               
        dadumingjuone2dadu2={newSceneId=0,PosX=195,PosZ=41},               
        dadumingjuone2dadu3={newSceneId=0,PosX=195,PosZ=41},               
        dadumingjuone2dadu4={newSceneId=0,PosX=195,PosZ=41}, 
		--���͵�(�󶼵������2)                                     
        dadu2dadumingjutwo1={newSceneId=43,PosX=36,PosZ=25},             
        dadu2dadumingjutwo2={newSceneId=43,PosX=36,PosZ=25},            
        dadu2dadumingjutwo3={newSceneId=43,PosX=36,PosZ=25},            
        dadu2dadumingjutwo4={newSceneId=43,PosX=36,PosZ=25},            
         --���͵�(�����2����)                                     
        dadumingjutwo2dadu1={newSceneId=0,PosX=211,PosZ=163},               
        dadumingjutwo2dadu2={newSceneId=0,PosX=211,PosZ=163},               
        dadumingjutwo2dadu3={newSceneId=0,PosX=211,PosZ=163},               
        dadumingjutwo2dadu4={newSceneId=0,PosX=211,PosZ=163}, 
		
		

		
         --���͵�(�������Թ�1)                                      
        gubaoone2bageda1={newSceneId=104,PosX=182,PosZ=44},             
        gubaoone2bageda2={newSceneId=204,PosX=68,PosZ=194},            
        gubaoone2bageda3={newSceneId=304,PosX=56,PosZ=68},            
        gubaoone2bageda4={newSceneId=404,PosX=65,PosZ=59},            
         --���͵�(�Թ�1������)                                      
        bageda2gubaoone1={newSceneId=50,PosX=21,PosZ=92},               
        bageda2gubaoone2={newSceneId=150,PosX=236,PosZ=152},               
        bageda2gubaoone3={newSceneId=250,PosX=21,PosZ=111},               
        bageda2gubaoone4={newSceneId=350,PosX=234,PosZ=163},   	
         --���͵�(�Թ�1���Թ�2)                                   
        gubaoone2gubaotwo1={newSceneId=105,PosX=55,PosZ=72},           
        gubaoone2gubaotwo2={newSceneId=205,PosX=189,PosZ=199},           
        gubaoone2gubaotwo3={newSceneId=305,PosX=72,PosZ=60},           
        gubaoone2gubaotwo4={newSceneId=405,PosX=62,PosZ=60},           
         --���͵�(�Թ�2���Թ�1)                                     
        gubaotwo2gubaoone1={newSceneId=104,PosX=189,PosZ=192},         
        gubaotwo2gubaoone2={newSceneId=204,PosX=69,PosZ=61},         
        gubaotwo2gubaoone3={newSceneId=304,PosX=205,PosZ=193},         
        gubaotwo2gubaoone4={newSceneId=404,PosX=190,PosZ=197},         
         --���͵�(�Թ�2���Թ�3)                                      
        gubaotwo2gubaoshree1={newSceneId=106,PosX=46,PosZ=187},    
        gubaotwo2gubaoshree2={newSceneId=206,PosX=46,PosZ=128},    
        gubaotwo2gubaoshree3={newSceneId=306,PosX=210,PosZ=74},    
        gubaotwo2gubaoshree4={newSceneId=406,PosX=195,PosZ=182},    
         --���͵�(�Թ�3���Թ�2)                                       
        gubaoshree2gubaotwoloulan={newSceneId=105,PosX=208,PosZ=195},     
        gubaoshree2gubaotwotianshan={newSceneId=205,PosX=192,PosZ=47},     
        gubaoshree2gubaotwokunlun={newSceneId=305,PosX=50,PosZ=188},     
        gubaoshree2gubaotwodunhuang={newSceneId=405,PosX=50,PosZ=128},  
        --���͵�(�Թ�3���Թ�4)                                       
        eerduosi2hannanhe1={newSceneId=107,PosX=71,PosZ=195},     
        eerduosi2hannanhe2={newSceneId=207,PosX=62,PosZ=56},     
        eerduosi2hannanhe3={newSceneId=307,PosX=184,PosZ=48},     
        eerduosi2hannanhe4={newSceneId=407,PosX=72,PosZ=215},  
         --���͵�(�Թ�4���Թ�3)                                       
        hannanhe2eerduosi1={newSceneId=106,PosX=210,PosZ=62},     
        hannanhe2eerduosi2={newSceneId=206,PosX=195,PosZ=48},     
        hannanhe2eerduosi3={newSceneId=306,PosX=69,PosZ=195},     
        hannanhe2eerduosi4={newSceneId=406,PosX=57,PosZ=68}, 
          --���͵�(�Թ�4���Թ�5)                                      
        baizhanting2bosi1={newSceneId=108,PosX=181,PosZ=50},     
        baizhanting2bosi2={newSceneId=208,PosX=215,PosZ=62},     
        baizhanting2bosi3={newSceneId=308,PosX=189,PosZ=49},     
        baizhanting2bosi4={newSceneId=408,PosX=211,PosZ=199},  
        --���͵�(�Թ�5���Թ�4)                                  
        damashige2bosi1={newSceneId=107,PosX=70,PosZ=59},     
        damashige2bosi2={newSceneId=207,PosX=58,PosZ=196},     
        damashige2bosi3={newSceneId=307,PosX=50,PosZ=198},     
        damashige2bosi4={newSceneId=407,PosX=70,PosZ=60},  
        --���͵�(�Թ�5���Թ�6)                                      
        jiangjunshree2jiangjuntwo1={newSceneId=109,PosX=180,PosZ=54},       
        jiangjunshree2jiangjuntwo2={newSceneId=209,PosX=212,PosZ=195},     
        jiangjunshree2jiangjuntwo3={newSceneId=309,PosX=191,PosZ=54},        
        jiangjunshree2jiangjuntwo4={newSceneId=409,PosX=60,PosZ=203},  
        --���͵�(�Թ�6���Թ�5)                                    
        futuone2biansai1={newSceneId=108,PosX=60,PosZ=129},      
        futuone2biansai2={newSceneId=208,PosX=40,PosZ=193},     
        futuone2biansai3={newSceneId=308,PosX=51,PosZ=128},     
        futuone2biansai4={newSceneId=408,PosX=188,PosZ=46},       
        --trap��(�Թ�6���Թ�7)
				loulanwangcheng2huangyelin={newSceneId=110,PosX=77,PosZ=62},
				laiyinwangcheng2huangyelin={newSceneId=210,PosX=189,PosZ=199},
				kunlunwangcheng2huangyelin={newSceneId=310,PosX=95,PosZ=39},
				dunhuangwangcheng2huangyelin={newSceneId=410,PosX=67,PosZ=195},
				----trap��(�Թ�7���Թ�6)
				loulanhuangyelin2wangcheng={newSceneId=109,PosX=184,PosZ=199},
				laiyinhuangyelin2wangcheng={newSceneId=209,PosX=55,PosZ=67},
				kunlunhuangyelin2wangcheng={newSceneId=309,PosX=188,PosZ=195},
				dunhuanghuangyelin2wangcheng={newSceneId=409,PosX=207,PosZ=64},	
				----trap��(�Թ�7���Թ�8)
				migong7ceng2migong8cengloulan={newSceneId=111,PosX=201,PosZ=193},
				migong7ceng2migong8cengtianshan={newSceneId=211,PosX=194,PosZ=197},
				migong7ceng2migong8cengkunlun={newSceneId=311,PosX=76,PosZ=65},
				migong7ceng2migong8cengdunhuang={newSceneId=411,PosX=212,PosZ=195},	
				----trap��(�Թ�8���Թ�7)
			  migong8ceng2migong7cengloulan={newSceneId=110,PosX=64,PosZ=222},
				migong8ceng2migong7cengtianshan={newSceneId=210,PosX=190,PosZ=42},
				migong8ceng2migong7cengkunlun={newSceneId=310,PosX=211,PosZ=60},
				migong8ceng2migong7cengdunhuang={newSceneId=410,PosX=67,PosZ=58},	
         --���͵�(���ǵ����Ѻ�)                                    
        wangcheng2hannanheloulan={newSceneId=98,PosX=92,PosZ=219},     
        wangcheng2hannanhetianshan={newSceneId=198,PosX=92,PosZ=219},     
        wangcheng2hannanhekunlun={newSceneId=298,PosX=92,PosZ=219},     
        wangcheng2hannanhedunhuang={newSceneId=398,PosX=92,PosZ=219},  
         --���͵�(���Ѻӵ�����)                                    
        hannanheloulan2wangcheng={newSceneId=50,PosX=235,PosZ=100},     
        hannanhetianshan2wangcheng={newSceneId=150,PosX=11,PosZ=91},     
        hannanhekunlun2wangcheng={newSceneId=250,PosX=235,PosZ=159},     
        hannanhedunhuang2wangcheng={newSceneId=350,PosX=20,PosZ=156},  
         --���͵�(���Ѻӵ�����)                                    
        hannanhe2qiyan0={newSceneId=99,PosX=216,PosZ=24},     
        hannanhe2qiyan1={newSceneId=199,PosX=216,PosZ=24},     
        hannanhe2qiyan2={newSceneId=299,PosX=216,PosZ=24},     
        hannanhe2qiyan3={newSceneId=399,PosX=216,PosZ=24},  
         --���͵�(���յ����Ѻ�)                                    
        qiyan2hannanhe0={newSceneId=98,PosX=221,PosZ=210},     
        qiyan2hannanhe1={newSceneId=198,PosX=221,PosZ=210},     
        qiyan2hannanhe2={newSceneId=298,PosX=221,PosZ=210},     
        qiyan2hannanhe3={newSceneId=398,PosX=221,PosZ=210},  
         --���͵�(���յ�����)                                    
        qiyan2nainan0={newSceneId=102,PosX=227,PosZ=124},     
        qiyan2nainan1={newSceneId=202,PosX=227,PosZ=124},     
        qiyan2nainan2={newSceneId=302,PosX=227,PosZ=124},     
        qiyan2nainan3={newSceneId=402,PosX=227,PosZ=124},               
         --���͵�(���յ�������)                                    
        qiyan2tataer0={newSceneId=100,PosX=29,PosZ=144},
        qiyan2tataer1={newSceneId=200,PosX=29,PosZ=144},     
        qiyan2tataer2={newSceneId=300,PosX=29,PosZ=144},     
        qiyan2tataer3={newSceneId=400,PosX=29,PosZ=144},  
        --���͵�(������������)                                    
        tataer2qiyan0={newSceneId=99,PosX=232,PosZ=216},     
        tataer2qiyan1={newSceneId=199,PosX=232,PosZ=216},     
        tataer2qiyan2={newSceneId=299,PosX=232,PosZ=216},     
        tataer2qiyan3={newSceneId=399,PosX=232,PosZ=216},  
         --���͵�(���յ�����)                                    
        qiyan2kelie0={newSceneId=101,PosX=147,PosZ=48},     
        qiyan2kelie1={newSceneId=201,PosX=147,PosZ=48},     
        qiyan2kelie2={newSceneId=301,PosX=147,PosZ=48},     
        qiyan2kelie3={newSceneId=401,PosX=147,PosZ=48},  
         --���͵�(����������)                                    
        naiman2qiyan0={newSceneId=99,PosX=24,PosZ=123},     
        naiman2qiyan1={newSceneId=199,PosX=24,PosZ=123},     
        naiman2qiyan2={newSceneId=299,PosX=24,PosZ=123},     
        naiman2qiyan3={newSceneId=399,PosX=24,PosZ=123},  
         --���͵�(������������)                                    
        tatare2qiyan0={newSceneId=99,PosX=100,PosZ=100},     
        tatare2qiyan1={newSceneId=199,PosX=100,PosZ=100},     
        tatare2qiyan2={newSceneId=299,PosX=100,PosZ=100},     
        tatare2qiyan3={newSceneId=399,PosX=100,PosZ=100},  
         --���͵�(���е�����)                                    
        kelie2qiyan0={newSceneId=99,PosX=102,PosZ=230},     
        kelie2qiyan1={newSceneId=199,PosX=102,PosZ=230},     
        kelie2qiyan2={newSceneId=299,PosX=102,PosZ=230},     
        kelie2qiyan3={newSceneId=399,PosX=102,PosZ=230},  
         --���͵�(���ҵ���ӹ)                                    
        kelie2juyongguan0={newSceneId=103,PosX=90,PosZ=31},     
        kelie2juyongguan1={newSceneId=203,PosX=90,PosZ=31},     
        kelie2juyongguan2={newSceneId=303,PosX=90,PosZ=31},     
        kelie2juyongguan3={newSceneId=403,PosX=90,PosZ=31},  
        --���͵�(��ӹ�ص�����)                                    
        juyongguan2tataer0={newSceneId=101,PosX=127,PosZ=218},     
        juyongguan2tataer1={newSceneId=201,PosX=127,PosZ=218},     
        juyongguan2tataer2={newSceneId=301,PosX=127,PosZ=218},     
        juyongguan2tataer3={newSceneId=401,PosX=127,PosZ=218},  
         --���͵�(��ӹ�ص�����)                                    
        juyongguan2dadu0={newSceneId=38,PosX=167,PosZ=26},     
        juyongguan2dadu1={newSceneId=38,PosX=167,PosZ=26},     
        juyongguan2dadu2={newSceneId=38,PosX=167,PosZ=26},     
        juyongguan2dadu3={newSceneId=38,PosX=167,PosZ=26},  
         --���͵�(�󶼵���ӹ��)                                    
        dadu2juyongguan0={newSceneId=103,PosX=205,PosZ=230},     
        dadu2juyongguan1={newSceneId=203,PosX=205,PosZ=230},     
        dadu2juyongguan2={newSceneId=303,PosX=205,PosZ=230},     
        dadu2juyongguan3={newSceneId=403,PosX=205,PosZ=230},  
         --���͵�(��Ҷ�ǵ��������)���ĺ�ɳĮ�����������                                    
        suiyecheng2samaerhan={newSceneId=11,PosX=233,PosZ=163},     
        suiyecheng2samaerhan={newSceneId=11,PosX=233,PosZ=163},     
        suiyecheng2samaerhan={newSceneId=11,PosX=233,PosZ=163},     
        suiyecheng2samaerhan={newSceneId=11,PosX=233,PosZ=163},  
         --���͵�(��Ҷ�ǵ���ɳĮ)                                    
        suiyecheng2hongshamo={newSceneId=10,PosX=229,PosZ=140},     
        suiyecheng2hongshamo={newSceneId=10,PosX=229,PosZ=140},     
        suiyecheng2hongshamo={newSceneId=10,PosX=229,PosZ=140},     
        suiyecheng2hongshamo={newSceneId=10,PosX=229,PosZ=140},  
         --���͵�(�����������Ҷ��)���������������ɳĮ��                                    
        samaerhan2suiyecheng={newSceneId=10,PosX=36,PosZ=124},     
        samaerhan2suiyecheng={newSceneId=10,PosX=36,PosZ=124},     
        samaerhan2suiyecheng={newSceneId=10,PosX=36,PosZ=124},     
        samaerhan2suiyecheng={newSceneId=10,PosX=36,PosZ=124},  
        --���͵�(��ɳĮ����Ҷ��)                                    
        hongshamo2suiyecheng={newSceneId=9,PosX=24,PosZ=178},     
        hongshamo2suiyecheng={newSceneId=9,PosX=24,PosZ=178},     
        hongshamo2suiyecheng={newSceneId=9,PosX=24,PosZ=178},     
        hongshamo2suiyecheng={newSceneId=9,PosX=24,PosZ=178},  
         --���͵�(��ɳĮ���͸��) (������������͸��)                                    
        hongshamo2bageda={newSceneId=13,PosX=222,PosZ=158},     
        hongshamo2bageda={newSceneId=13,PosX=222,PosZ=158},     
        hongshamo2bageda={newSceneId=13,PosX=222,PosZ=158},     
        hongshamo2bageda={newSceneId=13,PosX=222,PosZ=158},  
         --���͵�(�͸�ﵽĪ˹��)                                   
        bageda2mosike1={newSceneId=17,PosX=188,PosZ=230},     
        bageda2mosike2={newSceneId=17,PosX=188,PosZ=230},     
        bageda2mosike3={newSceneId=17,PosX=188,PosZ=230},     
        bageda2mosike4={newSceneId=17,PosX=188,PosZ=230},  
        --���͵�(�͸�ﵽ��ɳĮ)  ���İ͸�ﵽ���������                                     
        bageda2hongshamo={newSceneId=11,PosX=18,PosZ=126},     
        bageda2hongshamo={newSceneId=11,PosX=18,PosZ=126},     
        bageda2hongshamo={newSceneId=11,PosX=18,PosZ=126},     
        bageda2hongshamo={newSceneId=11,PosX=18,PosZ=126},  
         --���͵�(�͸�ﵽ��˹)                                   
        bageda2bosi={newSceneId=16,PosX=65,PosZ=34},     
        bageda2bosi={newSceneId=16,PosX=65,PosZ=34},     
        bageda2bosi={newSceneId=16,PosX=65,PosZ=34},     
        bageda2bosi={newSceneId=16,PosX=65,PosZ=34},  
          --���͵�(Ī˹�Ƶ��͸��)                                 
        mosike2bageda1={newSceneId=13,PosX=34,PosZ=30},     
        mosike2bageda2={newSceneId=13,PosX=34,PosZ=30},     
        mosike2bageda3={newSceneId=13,PosX=34,PosZ=30},     
        mosike2bageda4={newSceneId=13,PosX=34,PosZ=30},  
         --���͵�(Ī˹�Ƶ�����)                                    
        mosike2jifu={newSceneId=18,PosX=222,PosZ=222},     
        mosike2jifu={newSceneId=18,PosX=222,PosZ=222},     
        mosike2jifu={newSceneId=18,PosX=222,PosZ=222},     
        mosike2jifu={newSceneId=18,PosX=222,PosZ=222},  
         --���͵� ��������������                                   
        jifu2bolan0={newSceneId=19,PosX=230,PosZ=148},     
        jifu2bolan1={newSceneId=19,PosX=230,PosZ=148},     
        jifu2bolan2={newSceneId=19,PosX=230,PosZ=148},     
        jifu2bolan3={newSceneId=19,PosX=230,PosZ=148},  
         --���͵㣨������������                                 
        bolan2jifu0={newSceneId=18,PosX=23,PosZ=62},     
        bolan2jifu1={newSceneId=18,PosX=23,PosZ=62},     
        bolan2jifu2={newSceneId=18,PosX=23,PosZ=62},     
        bolan2jifu3={newSceneId=18,PosX=23,PosZ=62},  
        --���͵�(������������)                                    
        bolan2xiongyali0={newSceneId=20,PosX=228,PosZ=22},     
        bolan2xiongyali1={newSceneId=20,PosX=228,PosZ=22},     
        bolan2xiongyali2={newSceneId=20,PosX=228,PosZ=22},     
        bolan2xiongyali3={newSceneId=20,PosX=228,PosZ=22},  
         --���͵�(������������)                                    
        xiongyali2bolan0={newSceneId=19,PosX=23,PosZ=213},     
        xiongyali2bolan1={newSceneId=19,PosX=23,PosZ=213},     
        xiongyali2bolan2={newSceneId=19,PosX=23,PosZ=213},     
        xiongyali2bolan3={newSceneId=19,PosX=23,PosZ=213},  
         --���͵�(��������ʥ������)                                    
        xiongyali2luoma={newSceneId=21,PosX=227,PosZ=37},     
        xiongyali2luoma={newSceneId=21,PosX=227,PosZ=37},     
        xiongyali2luoma={newSceneId=21,PosX=227,PosZ=37},     
        xiongyali2luoma={newSceneId=21,PosX=227,PosZ=37},  
        --���͵�(��ʥ����������)                                    
        luoma2xiongyali={newSceneId=20,PosX=26,PosZ=229},     
        luoma2xiongyali={newSceneId=20,PosX=26,PosZ=229},     
        luoma2xiongyali={newSceneId=20,PosX=26,PosZ=229},     
        luoma2xiongyali={newSceneId=20,PosX=26,PosZ=229},  
         --���͵�(������Ī˹��)                                    
        jifu2mosike={newSceneId=17,PosX=30,PosZ=66},     
        jifu2mosike={newSceneId=17,PosX=30,PosZ=66},     
        jifu2mosike={newSceneId=17,PosX=30,PosZ=66},     
        jifu2mosike={newSceneId=17,PosX=30,PosZ=66},  
           --���͵�(��˹���͸��)                                    
        bosi2bageda={newSceneId=13,PosX=139,PosZ=227},     
        bosi2bageda={newSceneId=13,PosX=138,PosZ=227},     
        bosi2bageda={newSceneId=13,PosX=138,PosZ=227},     
        bosi2bageda={newSceneId=13,PosX=138,PosZ=227},  
         --���͵�(��ռͥ������                                
        baizhanting2luoma0={newSceneId=21,PosX=231,PosZ=217},     
        baizhanting2luoma1={newSceneId=21,PosX=231,PosZ=217},     
        baizhanting2luoma2={newSceneId=21,PosX=231,PosZ=217},     
        baizhanting2luoma3={newSceneId=21,PosX=231,PosZ=217},  
        --���͵�(������ռͥ��                                  
        luoma2baizhanting0={newSceneId=22,PosX=34,PosZ=111},     
        luoma2baizhanting1={newSceneId=22,PosX=34,PosZ=111},     
        luoma2baizhanting2={newSceneId=22,PosX=34,PosZ=111},     
        luoma2baizhanting3={newSceneId=22,PosX=34,PosZ=111},  
         --���͵�(��ռͥ������ʿ��)                                    
        baizhanting2damashige0={newSceneId=23,PosX=55,PosZ=68},     
        baizhanting2damashige1={newSceneId=23,PosX=55,PosZ=68},     
        baizhanting2damashige2={newSceneId=23,PosX=55,PosZ=68},     
        baizhanting2damashige3={newSceneId=23,PosX=55,PosZ=68},  
       --���͵�(����ʿ�ﵽ��ռͥ)                                    
        damashige2baizhanting0={newSceneId=22,PosX=178,PosZ=82},     
        damashige2baizhanting1={newSceneId=22,PosX=178,PosZ=82},     
        damashige2baizhanting2={newSceneId=22,PosX=178,PosZ=82},     
        damashige2baizhanting3={newSceneId=22,PosX=178,PosZ=82},  
         --���͵�(����ʿ�ﵽҮ·����)                                    
        damashige2yelusaileng0={newSceneId=24,PosX=133,PosZ=21},     
        damashige2yelusaileng1={newSceneId=24,PosX=133,PosZ=21},     
        damashige2yelusaileng2={newSceneId=24,PosX=133,PosZ=21},     
        damashige2yelusaileng3={newSceneId=24,PosX=133,PosZ=21},  
          --���͵�(Ү·���䵽����ʿ��)                                    
        yelusaileng2damashige0={newSceneId=23,PosX=107,PosZ=233},     
        yelusaileng2damashige1={newSceneId=23,PosX=107,PosZ=233},     
        yelusaileng2damashige2={newSceneId=23,PosX=107,PosZ=233},     
        yelusaileng2damashige3={newSceneId=23,PosX=107,PosZ=233},  
       --���͵�(Ү·���䵽���ΰ뵺)                                    
        yelusaleng2xinaibandao0={newSceneId=25,PosX=121,PosZ=24},     
        yelusaleng2xinaibandao1={newSceneId=25,PosX=121,PosZ=24},     
        yelusaleng2xinaibandao2={newSceneId=25,PosX=121,PosZ=24},     
        yelusaleng2xinaibandao3={newSceneId=25,PosX=121,PosZ=24},  
          --���͵�(���ΰ뵺��Ү·����)                                    
        xinaibandao2yelusaleng0={newSceneId=24,PosX=121,PosZ=224},     
        xinaibandao2yelusaleng1={newSceneId=24,PosX=121,PosZ=224},     
        xinaibandao2yelusaleng2={newSceneId=24,PosX=121,PosZ=224},     
        xinaibandao2yelusaleng3={newSceneId=24,PosX=121,PosZ=224},  
        
        
         --���͵�(�߾��ϵ�����)                                    
        bianjingshang2andao0={newSceneId=76,PosX=34,PosZ=47},     
        bianjingshang2andao1={newSceneId=176,PosX=218,PosZ=39},     
        bianjingshang2andao2={newSceneId=276,PosX=34,PosZ=47},     
        bianjingshang2andao3={newSceneId=376,PosX=218,PosZ=39},   
        --���͵�(�߾��µ�����)                                    
        bianjingxia2andao0={newSceneId=76,PosX=37,PosZ=218},     
        bianjingxia2andao1={newSceneId=176,PosX=220,PosZ=208},     
        bianjingxia2andao2={newSceneId=276,PosX=37,PosZ=218},     
        bianjingxia2andao3={newSceneId=376,PosX=220,PosZ=207},   
         --���͵�(�߾����񵽰���)                                    
        bianjingrenwu2andao0={newSceneId=76,PosX=220,PosZ=37},     
        bianjingrenwu2andao1={newSceneId=176,PosX=35,PosZ=215},     
        bianjingrenwu2andao2={newSceneId=276,PosX=220,PosZ=37},     
        bianjingrenwu2andao3={newSceneId=376,PosX=35,PosZ=215},   
         --���͵�(�������߾���)                                    
        andao2bianjingshang0={newSceneId=51,PosX=92,PosZ=67},     
        andao2bianjingshang1={newSceneId=151,PosX=159,PosZ=72},     
        andao2bianjingshang2={newSceneId=251,PosX=62,PosZ=72},     
        andao2bianjingshang3={newSceneId=351,PosX=167,PosZ=68},   
        --���͵�(�������߾���)                                    
        andao2bianjingxai0={newSceneId=51,PosX=69,PosZ=171},     
        andao2bianjingxai1={newSceneId=151,PosX=167,PosZ=172},     
        andao2bianjingxai2={newSceneId=251,PosX=91,PosZ=179},     
        andao2bianjingxai3={newSceneId=351,PosX=182,PosZ=179},   
         --���͵�(�������߾�����)                                    
        andao2bianjingrenwu0={newSceneId=51,PosX=202,PosZ=135},     
        andao2bianjingrenwu1={newSceneId=151,PosX=39,PosZ=149},     
        andao2bianjingrenwu2={newSceneId=251,PosX=211,PosZ=109},     
        andao2bianjingrenwu3={newSceneId=351,PosX=36,PosZ=97},     
                
        --���͵�(�߾���һ������)                                    
        bianjing2mishione0={newSceneId=59,PosX=29,PosZ=26},     
        bianjing2mishione1={newSceneId=159,PosX=29,PosZ=26},     
        bianjing2mishione2={newSceneId=259,PosX=29,PosZ=26},     
        bianjing2mishione3={newSceneId=359,PosX=29,PosZ=26},   
         --���͵�(�߾�����������)                                    
        bianjing2mishitwo0={newSceneId=60,PosX=36,PosZ=24},     
        bianjing2mishitwo1={newSceneId=160,PosX=36,PosZ=24},     
        bianjing2mishitwo2={newSceneId=260,PosX=36,PosZ=24},     
        bianjing2mishitwo3={newSceneId=360,PosX=36,PosZ=24},   
        --���͵�(һ�����ҵ��߾�)                                    
        mishione2bianjing0={newSceneId=51,PosX=178,PosZ=32},     
        mishione2bianjing1={newSceneId=151,PosX=118,PosZ=30},     
        mishione2bianjing2={newSceneId=251,PosX=94,PosZ=211},     
        mishione2bianjing3={newSceneId=351,PosX=95,PosZ=218},   
        --���͵�(�������ҵ��߾�)                                    
        mishitwo2bianjing0={newSceneId=51,PosX=97,PosZ=209},     
        mishitwo2bianjing1={newSceneId=151,PosX=172,PosZ=203},     
        mishitwo2bianjing2={newSceneId=251,PosX=94,PosZ=41},     
        mishitwo2bianjing3={newSceneId=351,PosX=144,PosZ=25},     
        --���͵㣨�ػͱ������ڣ�
        dunhuangbiansaidongkou1={newSceneId=351,PosX=144,PosZ=25},
				dunhuangbiansaidongkou2={newSceneId=351,PosX=144,PosZ=25},
        --���͵㣨���ر������ڣ�
        kunlunbiansaidongkou1={newSceneId=251,PosX=94,PosZ=41},
        kunlunbiansaidongkou2={newSceneId=251,PosX=94,PosZ=41},
        --���͵㣨��ɽ�������ڣ�
        tianshanbiansaidongkou1={newSceneId=151,PosX=172,PosZ=203},
        tianshanbiansaidongkou2={newSceneId=151,PosX=172,PosZ=203},
        --���͵㣨¥���������ڣ�
        loulanbiansaidongkou1={newSceneId=51,PosX=97,PosZ=209},                                                                              
				loulanbiansaidongkou2={newSceneId=51,PosX=97,PosZ=209},
				--���͵㣨�ػ����Ƕ��ڣ�
				dunhuangwangchengdongkou1={newSceneId=350,PosX=234,PosZ=163},
				dunhuangwangchengdongkou2={newSceneId=350,PosX=234,PosZ=163},
				--���͵㣨�������Ƕ��ڣ�
				kunlunwangchengdongkou1={newSceneId=250,PosX=21,PosZ=111},
				kunlunwangchengdongkou2={newSceneId=250,PosX=21,PosZ=111},
				--���͵㣨��ɽ���Ƕ��ڣ�
				tianshanwangchengdongkou1={newSceneId=150,PosX=236,PosZ=152},
				tianshanwangchengdongkou2={newSceneId=150,PosX=236,PosZ=152},
				--���͵㣨¥�����Ƕ��ڣ�
				loulanwangchengdongkou1={newSceneId=50,PosX=21,PosZ=92},
				loulanwangchengdongkou2={newSceneId=50,PosX=21,PosZ=92},             
																																
				} 
--  11       ¥������       0 
--  18       ��ɽ����       1
--  21       ��������       2
--  24       �ػ�����       3
--  36         ��         



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

--***********************
--Const
--***********************
-------------------------

--MisDescBegin

x300807_g_MissionId 				= 	9418                    --����ID
x300807_g_ScriptId 					= 	300807                  --�ű�ID
x300807_g_MissionKind 				= 	1                       --��������
x300807_g_LevelLess					= 	75                      --�������ŵȼ�  <=0 ��ʾ������


x300807_g_MissionName				= 	"�����ˡ������䱸"
x300807_g_MissionTarget				= 	""          --����Ŀ��
x300807_g_MissionInfo				= 	"\tʱ�¶���֮��������кܶ༬�ֵ�������Ҫ��������ȥ������ϣ����������һ��֮����\n\t���Ƿ�Ҫ��������"         
x300807_g_ContinueInfo				= 	"\t��ô��������Щ�򵥵������޷���ɣ���������Ҫ������ɫ��ѡ�ˡ�"  --���������Ϣ
x300807_g_MissionCompleted			= 	"\t��ı������Һ���ο��ϣ�����Ժ��ܹ�����Ϊ���ǵ������������ף�"  --���������Ϣ
x300807_g_MissionHelp				=	"\t�����䱸����ÿ��Ϊ#G30��#W�����񣬻���Խ�ߣ�#G���齱��#WҲԽ�ߣ�\n\t�����䱸���ռ�����Ʒ���ܶ����ͨ����������������������ҽ��׵�����"          --������ʾ��Ϣ

--Ŀ��
x300807_g_ExtTarget					=	{ {type=20,n=1,target="�����ˡ������䱸"}}

--����

x300807_g_ExpBonus					= 	0;--x300807_AddExpAward               	--����������
x300807_g_BonusItem					=	{}	--��������Ʒ

x300807_g_BonusMoney1               = 	0
x300807_g_BonusMoney2               =   0
x300807_g_BonusMoney3               =   0

x300807_g_BonusChoiceItem           =   {}


--MisDescEnd

x300807_g_GameId					=	1030
x300807_g_DayCountLimited			=	1
--x300807_g_nDaySpace					=	5    --����������һ��

x300807_g_EnterTime					=	{                       --���������ʱ��
											{min=0*60+0,  max=23*60+59},
										}

x300807_g_MaxStep					=	30
x300807_g_ReplyNpcId				=	132153
x300807_g_ReplyNpcObjId				=	3
----------------------------- common start ------------------------

x300807_g_BaseBonusRate = {50000,52000,54000,56000,58000,60000,62000,64000,66000,68000}  --������������
x300807_g_ExtraBonusRate = {1,1.6,2.9}  --10������

----------------------------- common end---------------------------

----------------------------- �ռ� start ------------------------
x300807_g_MissionInfo2				= 	"\t�����������ң����մ���ˮ�����֮�У������е���ʶ֮ʿ׼����֯�����������񣬵�Ŀǰ���������ѷ������貹�䡣"
x300807_g_ContinueInfo2				= 	"\t�����Ʒ����ô�����ҵ���"
x300807_g_MissionCompleted2			= 	"\tлл��Ŀ������ҡ�"
x300807_g_MissionHelp2					=	"\t�����䱸����ÿ��Ϊ#G30��#W�����񣬻���Խ�ߣ�#G���齱��#WҲԽ�ߣ�\n\t�����䱸���ռ�����Ʒ���ܶ����ͨ����������������������ҽ��׵�����"            --������ʾ��Ϣ

x300807_g_MissionTable2 =	{ --needvalue:��Ṧ��
							
 { id=1, ncount=6,needitem={{itemid=11020080,count=5},{itemid=11020070,count=5},{itemid=11020050,count=5},{itemid=11020060,count=5},{itemid=11020030,count=5},{itemid=11020040,count=5}}},
 { id=2, ncount=6,needitem={{itemid=11041010,count=5},{itemid=11041000,count=5},{itemid=11041020,count=5},{itemid=11041030,count=5},{itemid=11041040,count=5},{itemid=11041050,count=5}}},
 { id=3, ncount=10,needitem={{itemid=12240003,count=1},{itemid=12240004,count=1},{itemid=12240005,count=1},{itemid=12240007,count=1},{itemid=12240008,count=1},{itemid=12240009,count=1},{itemid=12240010,count=1},{itemid=12240011,count=1},{itemid=12240012,count=1},{itemid=12240012,count=1}}},
 { id=4, ncount=6,needitem={{itemid=11020080,count=5},{itemid=11020070,count=5},{itemid=11020050,count=5},{itemid=11020060,count=5},{itemid=11020030,count=5},{itemid=11020040,count=5}}},
 { id=5, ncount=8,needitem={{itemid=12200600,count=1},{itemid=12200601,count=1},{itemid=12200602,count=1},{itemid=12200603,count=1},{itemid=12200604,count=1},{itemid=12200605,count=1},{itemid=12200606,count=1},{itemid=12200607,count=1}}},
 { id=6, ncount=4,needitem={{itemid=11020071,count=5},{itemid=11020081,count=5},{itemid=11020051,count=5},{itemid=11020061,count=5}}},
 { id=7, ncount=9,needitem={{itemid=12240003,count=1},{itemid=12240004,count=1},{itemid=12240005,count=1},{itemid=12240007,count=1},{itemid=12240008,count=1},{itemid=12240009,count=1},{itemid=12240010,count=1},{itemid=12240011,count=1},{itemid=12240012,count=1}}},
 { id=8, ncount=5,needitem={{itemid=12052013,count=1},{itemid=12052023,count=1},{itemid=12052033,count=1},{itemid=12052043,count=1},{itemid=12052053,count=1}}},
 { id=9, ncount=7,needitem={{itemid=11041032,count=2},{itemid=11041051,count=4},{itemid=11041052,count=2},{itemid=11041021,count=4},{itemid=11041022,count=4},{itemid=11041041,count=4},{itemid=11041042,count=2}}},
 { id=10, ncount=9,needitem={{itemid=12240003,count=1},{itemid=12240004,count=1},{itemid=12240005,count=1},{itemid=12240007,count=1},{itemid=12240008,count=1},{itemid=12240009,count=1},{itemid=12240010,count=1},{itemid=12240011,count=1},{itemid=12240012,count=1}}},
 { id=11, ncount=6,needitem={{itemid=11020071,count=12},{itemid=11020081,count=12},{itemid=11020051,count=12},{itemid=11020061,count=12},{itemid=11020031,count=12},{itemid=11020041,count=12}}},
 { id=12, ncount=5,needitem={{itemid=12240002,count=2},{itemid=11000902,count=1},{itemid=12050091,count=2},{itemid=12050092,count=1},{itemid=12054300,count=1}}},
 { id=13, ncount=7,needitem={{itemid=12200705,count=1},{itemid=12200704,count=1},{itemid=12200706,count=1},{itemid=12221812,count=1},{itemid=12223802,count=1},{itemid=12223800,count=1},{itemid=12223801,count=1}}},
 { id=14, ncount=9,needitem={{itemid=12240003,count=5},{itemid=12240004,count=5},{itemid=12240005,count=5},{itemid=12240007,count=5},{itemid=12240008,count=5},{itemid=12240009,count=5},{itemid=12240010,count=5},{itemid=12240011,count=5},{itemid=12240012,count=5}}},
 { id=15, ncount=11,needitem={{itemid=12221800,count=1},{itemid=12221801,count=1},{itemid=12221802,count=1},{itemid=12221803,count=1},{itemid=12221804,count=1},{itemid=12221805,count=1},{itemid=12222800,count=1},{itemid=12222801,count=1},{itemid=12222802,count=1},{itemid=12222803,count=1},{itemid=12222804,count=1}}},
 { id=16, ncount=6,needitem={{itemid=11020082,count=20},{itemid=11020072,count=20},{itemid=11020052,count=20},{itemid=11020062,count=20},{itemid=11020032,count=20},{itemid=11020042,count=20}}},
 { id=17, ncount=7,needitem={{itemid=14040003,count=1},{itemid=14010008,count=1},{itemid=14010003,count=1},{itemid=14010013,count=1},{itemid=14020003,count=1},{itemid=14020008,count=1},{itemid=14020013,count=1}}},
 { id=18, ncount=6,needitem={{itemid=11041012,count=10},{itemid=11041002,count=10},{itemid=11041022,count=10},{itemid=11041032,count=10},{itemid=11041042,count=10},{itemid=11041052,count=10}}},
 { id=19, ncount=7,needitem={{itemid=12200800,count=1},{itemid=12200808,count=1},{itemid=12200809,count=1},{itemid=12200810,count=1},{itemid=12210805,count=1},{itemid=12221816,count=1},{itemid=12223804,count=1}}},
 { id=20, ncount=9,needitem={{itemid=12240003,count=5},{itemid=12240004,count=5},{itemid=12240005,count=5},{itemid=12240007,count=5},{itemid=12240008,count=5},{itemid=12240009,count=5},{itemid=12240010,count=5},{itemid=12240011,count=5},{itemid=12240012,count=5}}},
 { id=21, ncount=7,needitem={{itemid=12200800,count=1},{itemid=12200808,count=1},{itemid=12200809,count=1},{itemid=12200810,count=1},{itemid=12210805,count=1},{itemid=12221816,count=1},{itemid=12223804,count=1}}},
 { id=22, ncount=9,needitem={{itemid=12240007,count=7},{itemid=12240008,count=7},{itemid=12240009,count=7},{itemid=12240010,count=7},{itemid=12240011,count=7},{itemid=12240003,count=7},{itemid=12240004,count=7},{itemid=12240005,count=7},{itemid=12240010,count=7}}},
 { id=23, ncount=8,needitem={{itemid=12240003,count=7},{itemid=12240004,count=7},{itemid=12240005,count=7},{itemid=12240007,count=7},{itemid=12240008,count=7},{itemid=12240009,count=7},{itemid=12240010,count=7},{itemid=12240011,count=7}}},
 { id=24, ncount=6,needitem={{itemid=11020073,count=20},{itemid=11020083,count=20},{itemid=11020053,count=20},{itemid=11020063,count=20},{itemid=11020032,count=20},{itemid=11020042,count=20}}},
 { id=25, ncount=3,needitem={{itemid=12041110,count=5},{itemid=12041111,count=5},{itemid=12041112,count=5}}},
 { id=26, ncount=6,needitem={{itemid=11041003,count=10},{itemid=11041043,count=10},{itemid=11041013,count=10},{itemid=11041033,count=10},{itemid=11041023,count=10},{itemid=11041053,count=10}}},
 { id=27, ncount=6,needitem={{itemid=11020073,count=20},{itemid=11020083,count=20},{itemid=11020053,count=20},{itemid=11020063,count=20},{itemid=11020032,count=20},{itemid=11020042,count=20}}},
 { id=28, ncount=7,needitem={{itemid=14040003,count=1},{itemid=14010008,count=1},{itemid=14010003,count=1},{itemid=14010013,count=1},{itemid=14020003,count=1},{itemid=14020008,count=1},{itemid=14020013,count=1}}},
 { id=29, ncount=8,needitem={{itemid=12240003,count=7},{itemid=12240004,count=7},{itemid=12240005,count=7},{itemid=12240007,count=7},{itemid=12240008,count=7},{itemid=12240009,count=7},{itemid=12240010,count=7},{itemid=12240011,count=7}}},
 { id=30, ncount=4,needitem={{itemid=11020073,count=20},{itemid=11020083,count=20},{itemid=11020053,count=20},{itemid=11020063,count=20}}},
							}
----------------------------- �ռ� end---------------------------

function x300807_GetMissionId( sceneId, selfId )
	return x300807_g_MissionId
end

function x300807_GetMissionStep(sceneId, selfId)

---������
    --return 1
	local nLastFlag = GetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_CURRENT_ID[1], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[2], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[3])
	if nLastFlag>=x300807_GetMaxStep(sceneId,selfId) then
		nLastFlag = 0
	end
	return nLastFlag+1
	
end

function x300807_SaveMissionStep(sceneId, selfId)

	local nLastFlag = GetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_CURRENT_ID[1], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[2], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[3])



	if nLastFlag<(x300807_GetMaxStep(sceneId,selfId)-1) then
		
		SetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_CURRENT_ID[1], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[2], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[3],nLastFlag+1)
		local myMissionId = x300807_GetMissionId( sceneId, selfId )	
		x300807_DispatchMissionInfo( sceneId, selfId, x300807_g_ReplyNpcObjId, myMissionId, 0 )
	else
		SetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_CURRENT_ID[1], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[2], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[3],0)
		x300807_SetDayCount(sceneId, selfId)
		
		if random( 1, 1000000) <= 25 then
            BeginAddItem( sceneId)
            AddItem( sceneId, 10310003, 1)
            local ret = EndAddItem( sceneId, selfId)
            if ret > 0 then
                AddItemListToPlayer( sceneId, selfId)
				local msg = format( "��ϲ#R%s#cffcc00��ɾ����䱸�������˵Ļ����һ��#G�����ƣ�����Ԫ(����ĥ��)��", GetName( sceneId, selfId) )
                LuaAllScenceM2Wrold (sceneId, msg, 5, 1)
                Msg2Player( sceneId, selfId, msg, 2, 0)
            else
                Msg2Player( sceneId, selfId, "��Ʒ���������޷��õ���Ʒ", 8, 3)
            end
        end
		
	end
	
  
end

function x300807_ResetMissionStep(sceneId, selfId)
	SetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_CURRENT_ID[1], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[2], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[3],0)
end

function x300807_GetMissionTypeById(nStep)
	
	local nIndex =0
	for i,item in x300807_g_MissionTable2 do
		nIndex = nIndex+1;
		if item.id == nStep then
			return nIndex
		end
	end
end

function x300807_GetMaxStep(sceneId,selfId)
	return x300807_g_MaxStep
end

function x300807_GetData(sceneId, selfId)
	local nStep = x300807_GetMissionStep(sceneId, selfId)
	local nIndex = x300807_GetMissionTypeById(nStep)
	local n1 = mod(nStep,10)

	

	local n2 = (nStep - mod(nStep,10))/10+1
	if n1==0 then
		n1 = 10
		
		n2 = (nStep - mod(nStep,10))/10
	end
	
	local nBaseBonusRate = x300807_g_BaseBonusRate[n1]  --������������
	local nExtraBonusRate = x300807_g_ExtraBonusRate[n2] --������������
	local nLevel = GetLevel(sceneId, selfId)
	local nExpBonus = nLevel*nBaseBonusRate*nExtraBonusRate
	
	nExpBonus = tonumber(format("%d",nExpBonus))
	if nLevel >= 80 and nLevel < 90 then
		nExpBonus = nExpBonus*2
	elseif nLevel >= 90 and nLevel < 160 then 
	 	nExpBonus = nExpBonus*2.6
	end
	return nStep,nIndex,nExpBonus
end

function x300807_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if GetGameOpenById(x300807_g_GameId)<=0 then
		return
	end

	if IsPlayerStateNormal(sceneId,selfId ) <= 0 then
		return
	end

	local level = GetLevel( sceneId,selfId )
    if level < x300807_g_LevelLess then
       return
    end

	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300807_g_MissionName,8,1);
		
	else
		local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		AddQuestNumText(sceneId, myMissionId, x300807_g_MissionName,state,state);

	end


	DispatchQuestEventList(sceneId, selfId, targetId)


	
end





---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300807_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	
	
	
	if GetGameOpenById(x300807_g_GameId)<=0 then
		x300807_ShowTips(sceneId, selfId, "�˻δ����")
		return
	end

	local myMissionId = x300807_GetMissionId( sceneId, selfId )	
	
	

	
	
	
		
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		if nExt~=30 then
		
		x300807_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
		else
			x300807_ShowTips(sceneId, selfId, "��û������"..x300807_g_MissionName)
			return
		end
		
		
	else
		if nExt==7 then -- �������
			x300807_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
			
		elseif nExt==30 then
			x300807_DispatchSongxinInfo( sceneId, selfId, targetId,myMissionId )
		else
			
			x300807_DispatchContinueInfo( sceneId, selfId, targetId,myMissionId )
		end
	end
	
end



function x300807_DispatchSongxinInfo( sceneId, selfId, NPCId,MissionId )

end

---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x300807_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )
	

	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300807_g_MissionName)
		
			
		AddQuestText(sceneId,x300807_g_MissionInfo)
		AddQuestText(sceneId," ")
			
		--AddQuestText( sceneId,"#Y����Ŀ��:")
					
		AddQuestText( sceneId,x300807_g_MissionTarget)
		--AddQuestText(sceneId," ")

		
		if nExpBonus > 0 then
			AddQuestExpBonus( sceneId, nExpBonus)
		end

		AddQuestText( sceneId,"#GС��ʾ��#W\n\t�����䱸����ÿ��Ϊ#G30��#W�����񣬻���Խ�ߣ�#G���齱��#WҲԽ�ߣ�\n\t�����䱸���ռ�����Ʒ���ܶ����ͨ����������������������ҽ��׵�����")
	

	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300807_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300807_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	
	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300807_g_MissionName)
		AddQuestText(sceneId," ")
		AddQuestText(sceneId,"\t����û����ɱ���������Ͽ�ȥ��ɰɣ�")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300807_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300807_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	
	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)
	

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300807_g_MissionName)
		AddQuestText(sceneId,"\t#Y@myname#W����л���������Ĺ��ף������ڴ�ҵĹ�ͬŬ���£����ǵ�����һ�������ǿʢ��")
	

	
	if nExpBonus > 0 then
		AddQuestExpBonus( sceneId, nExpBonus)
	end

	
		
	EndQuestEvent()
	
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300807_g_ScriptId, MissionId);

end


function x300807_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x300807_g_GameId)<=0 then
		
		return 0;
	end
	return 1;

end

function x300807_CheckRequest(sceneId, selfId)
	if GetGameOpenById(x300807_g_GameId)<=0 then
		x300807_ShowTips(sceneId, selfId, "�˻δ����")
		return 0
	end


	local myMissionId = x300807_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300807_g_LevelLess then
		x300807_ShowTips(sceneId, selfId, "���ĵȼ����㣬�޷���ȡ������")
		return 0
	end

	--if GetGuildID( sceneId, selfId ) == -1 then
	--  x300807_ShowTips(sceneId, selfId, "����û�м����ᣬ�޷���ȡ������")
	--  return 0
	--end

	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300807_ShowTips(sceneId, selfId, "���Ѿ���ȡ�˸�����������ɵ�ǰ����")
		return 0;
	end


	if x300807_g_DayCountLimited >0 then
		--local nDayCount, nLastDay = x300807_GetDayCount(sceneId, selfId)

		
		--if nDayCount>= x300807_g_DayCountLimited then
		--	local today = GetDayOfYear() 

		--	local nNeedDay = x300807_g_nDaySpace-(today-nLastDay)

		--	x300807_ShowTips(sceneId, selfId, format("�ܱ�Ǹ�������ˡ������䱸������%d�����������",nNeedDay))
		--	return 0;
		--end
		if x300807_GetDayCount(sceneId, selfId) > 0 then
			x300807_ShowTips(sceneId, selfId, "�ܱ�Ǹ��������������ȡ������")
			x300807_ResetMissionStep(sceneId, selfId)
			return 0
		end
	end

	

	return 1;

end



function x300807_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	
	if x300807_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300807_ShowTips(sceneId, selfId, "�����������޷���������")
		return 0
	end
	---------------------------- add end -------------------------------
	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)

	local ret = AddQuest( sceneId, selfId, myMissionId, x300807_g_ScriptId, 1, 0, 1,1)-- ������������		
		
	if ret > 0 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

---������
		local nRandom = random(1,x300807_g_MissionTable2[nIndex].ncount)
		if nRandom < 1 then
			nRandom = 1
		elseif nRandom > x300807_g_MissionTable2[nIndex].ncount then
			nRandom = x300807_g_MissionTable2[nIndex].ncount
		end
		
		local str = "������������"..x300807_g_MissionName;
		x300807_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)
		
		SetQuestByIndex( sceneId, selfId, misIndex, 6, nRandom )
		

		x300807_ShowSubMission( sceneId, selfId, targetId,MissionId,nRandom )

		x300807_CheckShoujiHaveAll(sceneId, selfId, nRandom)

		GamePlayScriptLog(sceneId, selfId, 1271)
		return 1
	else
		
		x300807_ShowTips(sceneId, selfId, "�����������")
	
	end


end


function x300807_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300807_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )


	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )

    local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)
	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )
	

	local ret = DelQuestNM( sceneId, selfId, myMissionId )
	if ret>0 then

		local str = "������������:"..x300807_g_MissionName;
	    x300807_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

		x300807_SetDayCount(sceneId, selfId)
		x300807_ResetMissionStep(sceneId, selfId)
	else
		x300807_ShowTips(sceneId, selfId, "��������ʧ��")
	end
end


function x300807_ProcQuestSubmit( sceneId, selfId, targetId, selectRadioId, MissionId )
	
	
	if GetGameOpenById(x300807_g_GameId)<=0 then
		x300807_ShowTips(sceneId, selfId, "�˻δ����")
		return 0;
	end

	
	local myMissionId = x300807_GetMissionId( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )


	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)
	
	if x300807_CheckSubmit(sceneId, selfId )>0 then
		if x300807_SubmitShouji(sceneId, selfId,targetId)<=0 then
				return 0
			end
		
		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then

			local str = "�����������:"..x300807_g_MissionName;
			x300807_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

			
			
			x300807_GiveReward(sceneId,selfId)

			x300807_SaveMissionStep(sceneId, selfId)

			CallScriptFunction( 300807, "ProcEventEntry", sceneId, selfId, targetId, x300807_g_MissionId )	
			GamePlayScriptLog(sceneId, selfId, 1272)
			
		else
			x300807_ShowTips(sceneId, selfId, "������ʧ��")
		end
		
	end
end


function x300807_SubmitShouji(sceneId, selfId,targetId)
	
	
	local myMissionId = x300807_GetMissionId( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )



	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)
	
	
	local itemid_t = x300807_g_MissionTable2[nIndex].needitem[nRandom].itemid
	local count_t = x300807_g_MissionTable2[nIndex].needitem[nRandom].count

	
	if GetItemClass(itemid_t)~=10 then

		local nRet = DelItem(sceneId, selfId,itemid_t,count_t)
		
		if nRet<=0 then
			x300807_ShowTips(sceneId, selfId, "ɾ����Ʒʧ��")
			
			return 0
		else
		
		end
	
	else
		--�����װ��
		
		
		local nItemCount = GetItemCount( sceneId, selfId, itemid_t )
		
		BeginUICommand( sceneId)
			UICommand_AddInt( sceneId, x300807_g_ScriptId)
			UICommand_AddInt( sceneId, myMissionId)
			UICommand_AddInt( sceneId, targetId)
			UICommand_AddInt( sceneId, itemid_t)
			
			
			DispatchUICommand( sceneId, selfId, 106)  --104
		EndUICommand( sceneId)

		BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "#Y"..x300807_g_MissionName)
			AddQuestText( sceneId, "\t����Ҫѡ���Ͻ�һ����ɱ��������������Ʒ" )
		EndQuestEvent( sceneId)
		DispatchQuestEventList( sceneId, selfId, targetId)

		--AskDeleteWhichEquip(sceneId, selfId,itemid_t,count_t)  --���͸��ͻ���ɾ���ĸ�װ��

		return 0
	end

	return 1
end

function x300807_OnComitSubmitItem(sceneId, selfId,bagIndex)

	local myMissionId = x300807_GetMissionId( sceneId, selfId )

	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)
	
	if x300807_CheckSubmit(sceneId, selfId )>0 then
		
		if EraseItem(sceneId, selfId,bagIndex)>0 then
			local ret = DelQuestNM( sceneId, selfId, myMissionId )

			if ret>0 then

				local str = "�����������:"..x300807_g_MissionName;
				x300807_ShowTips(sceneId, selfId, str)
				Msg2Player(sceneId,selfId,str,8,2)

				
				
				x300807_GiveReward(sceneId,selfId)

				x300807_SaveMissionStep(sceneId, selfId)


				GamePlayScriptLog(sceneId, selfId, 1272)
				
			else
				x300807_ShowTips(sceneId, selfId, "������ʧ��")
			end
		else
			x300807_ShowTips(sceneId, selfId, "ɾ����Ʒʧ��")
		end
		
	end
end



function x300807_GiveReward(sceneId,selfId)
	
	if GetGameOpenById(x300807_g_GameId)<=0 then
		x300807_ShowTips(sceneId, selfId, "�˻δ����")
		return 0;
	end

	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)
	
	AddExp(sceneId,selfId,nExpBonus)
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, "#o�������#R����"..nExpBonus.."��#o�Ľ���");
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId,selfId,"#o������ˡ����ˡ������䱸���񣬻����#R����"..nExpBonus.."��#o�Ľ���",4,2)
	
	
end



function x300807_CheckSubmit(sceneId, selfId )
	
	if GetGameOpenById(x300807_g_GameId)<=0 then
		x300807_ShowTips(sceneId, selfId, "�˻δ����")
		return 0;
	end

	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )


	

	if (bCompleted)<=0 then
		return 0
	end

	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)

		local itemid_t = x300807_g_MissionTable2[nIndex].needitem[nRandom].itemid
		local count_t = x300807_g_MissionTable2[nIndex].needitem[nRandom].count
		local nItemCount = GetItemCount( sceneId, selfId, itemid_t )
		if nItemCount<count_t then
			return 0
		end
		

	return 1;
end






---------------------------------------------------------------------------------------------------
--��ͻ��˷�����Ŀ
---------------------------------------------------------------------------------------------------
function x300807_ShowSubMission( sceneId, selfId, NPCId,MissionId, nRandom )


	
	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)

	

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"#Y"..x300807_g_MissionName)
	
		local str1 = "  �ռ�"..x300807_g_MissionTable2[nIndex].needitem[nRandom].count.."��#G@itemid_"..x300807_g_MissionTable2[nIndex].needitem[nRandom].itemid.."\n"
		
		AddQuestText(sceneId,x300807_g_MissionInfo2)
		AddQuestText( sceneId,"\n#Y����Ŀ��:")
		AddQuestText(sceneId,"#W"..str1)
	

	
	if nExpBonus > 0 then
		AddQuestExpBonus( sceneId, nExpBonus)
	end

	

	EndQuestEvent()

	DispatchQuestEventList( sceneId, selfId, NPCId)
end







---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300807_QuestLogRefresh( sceneId, selfId, MissionId)
	
	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end
		
	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- ����
							x300807_GetMissionName(sceneId,selfId),        -- ��������
							x300807_GetMissionTask(sceneId,selfId),		--����Ŀ��
							"@npc_"..x300807_GetReplyNpcId(sceneId,selfId),			--����NPC
							x300807_GetMissionMethod(sceneId,selfId),               --������
							x300807_GetMissionText(sceneId,selfId),	--��������
							x300807_GetMissionHelp(sceneId,selfId)					--����С��ʾ
							)

	--1������
	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)

	if nExpBonus > 0 then
		AddQuestExpBonus( sceneId, nExpBonus)
	end

	
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300807_GetMissionName(sceneId,selfId)
	
	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)

	return x300807_g_MissionName..format("(%d/%d)",nStep,x300807_GetMaxStep(sceneId,selfId));
end

function x300807_GetMissionTask(sceneId,selfId)
	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	
	local value0 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local value7 = GetQuestParam( sceneId, selfId, misIndex, 7 )
	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )
	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)

	local str1=""

	

		local id = x300807_g_MissionTable2[nIndex].needitem[nRandom].itemid
		local count_t = x300807_g_MissionTable2[nIndex].needitem[nRandom].count
		
		local strTail = format("(%d/%d)",value0,count_t)
		if value0>=count_t then
			strTail = "#G"..strTail
		else
			strTail = "#W"..strTail
		end
		str1 = str1.."  #W�ռ�"..count_t.."��#G@itemid_"..id..strTail
		

		return str1
	

	

	
end

function x300807_GetReplyNpcId(sceneId,selfId)
	return x300807_g_ReplyNpcId;
end

function x300807_GetMissionMethod(sceneId,selfId)
	

	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)
	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )

	local str1=""

		
		local id = x300807_g_MissionTable2[nIndex].needitem[nRandom].itemid
		local count_t = x300807_g_MissionTable2[nIndex].needitem[nRandom].count
		
		str1 = str1.."  #W�ռ�"..count_t.."��#G@itemid_"..id
		

	return str1
end

function x300807_GetMissionText(sceneId,selfId)
	
	

	return x300807_g_MissionInfo
end

function x300807_GetMissionHelp(sceneId,selfId)
	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)
	
		return x300807_g_MissionHelp2
	
end



function x300807_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300807_QuestLogRefresh( sceneId, selfId, MissionId );
end

--// system function start
function x300807_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	
	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )

	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)
	
end

---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x300807_GetDayCount(sceneId, selfId)

	local today = GetWeekIndex()
	local lastday = GetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DATE_NV[1], MD_GUILD_CIRCLE_MISSION_DATE_NV[2],MD_GUILD_CIRCLE_MISSION_DATE_NV[3] )
	local daycount = GetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DAYCOUNT[1], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[2],MD_GUILD_CIRCLE_MISSION_DAYCOUNT[3] );

	if today == lastday then
		return daycount 
	end
	
	return 0

end

---------------------------------------------------------------------------------------------------
--���õ������
---------------------------------------------------------------------------------------------------
function x300807_SetDayCount(sceneId, selfId)

	local today = GetWeekIndex()
	local lastday = GetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DATE_NV[1], MD_GUILD_CIRCLE_MISSION_DATE_NV[2],MD_GUILD_CIRCLE_MISSION_DATE_NV[3] );
	
	if today == lastday then
			local daycount = GetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DAYCOUNT[1], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[2], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[3])
			SetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DAYCOUNT[1], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[2], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[3], daycount+1)
		else
		SetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DATE_NV[1], MD_GUILD_CIRCLE_MISSION_DATE_NV[2], MD_GUILD_CIRCLE_MISSION_DATE_NV[3], today)
		SetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DAYCOUNT[1], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[2], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[3], 1)
		end
end

--function x300807_CheckSceneOnKill(sceneId, selfId)
	--return 1
--end

--����ʹ����Ʒ����
function x300807_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return 1
end


--// system end


-------------------------------------------------------------------
-- OnItemChange
-------------------------------------------------------------------
--��Ʒ�ı�
function x300807_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId, nChangeType, nCount)

    local myMissionId = x300807_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)


	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	local itemid_t	= x300807_g_MissionTable2[nIndex].needitem[nRandom].itemid
	local count_t	= x300807_g_MissionTable2[nIndex].needitem[nRandom].count
	if itemid_t==itemdataId then
		local Num = GetItemCount( sceneId, selfId, itemdataId )

		if Num<count_t then
			SetQuestByIndex( sceneId, selfId, misIndex, 0, Num )
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
		else
			SetQuestByIndex( sceneId, selfId, misIndex, 0, count_t )
			
			local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )

			if bCompleted<=0 then
				SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
				
				--x300807_ShowTips(sceneId, selfId, "���������:"..x300807_g_MissionName)
				
			end
		end
		
	end


	x300807_QuestLogRefresh( sceneId, selfId, myMissionId );

    
	
end

function x300807_CheckShoujiHaveAll(sceneId, selfId, nRandom)
	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)


	local itemid_t = x300807_g_MissionTable2[nIndex].needitem[nRandom].itemid
	x300807_ProcQuestItemChanged( sceneId, selfId,itemid_t, -1, -1, -1)
	
end

function x300807_OnSelectSubmitItem( sceneId, selfId , bagIndex, nGuid_Serial, nGuid_Server, nGuid_World)

	if x300807_CheckSubmit(sceneId, selfId )<=0 then
		return 0
	end

	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	
	if IsHaveQuest( sceneId, selfId, myMissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId)

	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)
	


	--x300807_ShowTips(sceneId, selfId, format("bagIndex=%d,itemGuid1=%d, itemGuild2=%d, itemGuid3=%d",bagIndex , nGuid_Serial, nGuid_Server, nGuid_World))

	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	local itemid_t = x300807_g_MissionTable2[nIndex].needitem[nRandom].itemid
	local count_t = x300807_g_MissionTable2[nIndex].needitem[nRandom].count

	if (CheckItemMatchInBag( sceneId, selfId , bagIndex, itemid_t,nGuid_Serial, nGuid_Server, nGuid_World))>0 then  --�����Ʒ�����ȷ
		x300807_OnComitSubmitItem(sceneId, selfId,bagIndex)
	end
end


-- �뿪���
function x300807_OnLeaveGuild(sceneId, selfId, MissionId)

	--DelQuestNM( sceneId, selfId, MissionId)
	--local message = format("���Ѿ����ڰ�����ˣ�ɾ��������%s", x300807_g_MissionName);
	--BeginQuestEvent(sceneId);
	--AddQuestText(sceneId, message);
	--EndQuestEvent();
	--DispatchQuestTips(sceneId, selfId);
	--Msg2Player(sceneId, selfId, message, 8, 2);	
	
end

function x300807_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end




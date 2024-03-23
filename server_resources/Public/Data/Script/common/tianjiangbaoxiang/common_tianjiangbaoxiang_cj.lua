----------------------------------------------------
-- �ռ���ʯ
----------------------------------------------------

x310016_g_ScriptId 					= 310016

x310016_g_LevelMin					= 20
x310016_g_LevelMax					= 100
x310016_g_DayCountUntil				= 1

x310016_g_ItemIdList				= {12030328,12030329,12030330,12030331,12030332}

x310016_g_NeedItemCount				= 1	

x310016_g_MissionName				= "�����ˡ��ռ���ʯ"
x310016_g_EnterInfo					= "\t��˵���𣿴�����ʮ���տ�ʼ��ÿ���ռ���ȫ#Y���ɡ�������������˼��������������China Joy��#W��������ʯ�����ң�ÿ��������һ�Σ�����ǵ�#R888#W����������������˶�������п��ܻ��#Y�Կ�#W��#Y�ʼǱ�#W�ĳ�ֵ�󽱣�\n\t��������ˡ�#G�콵����#W��������ھ��п��ܴ���Щ�����л����Щʯͷ����ÿ��#Y12��30-24��00#W�У�������������ʯ#Y\n���ɡ�����ʯ * 1\n����������ʯ * 1\n��˼������ʯ * 1\n����������ʯ * 1\n��ChinaJoy������ʯ * 1#W"

x310016_g_BonusItem1 = 12030209
x310016_g_BonusItem2 = 11000300
x310016_g_BonusItem3 = 12010020
x310016_g_BonusItem4 = 12030200
x310016_g_BonusItem5 = 12041101

x310016_GameId = 1017


x310016_g_EnterTime					=	{                       --�ɽ���ʱ���
											{min=12*60+30,  max=24*60+0},
											--{min=19*60+30,  max=20*60+0},
										}
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x310016_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	if GetGameOpenById(x310016_GameId)<=0 then
		return
	end

	local level = GetLevel( sceneId,selfId )
    if level < x310016_g_LevelMin then
       return
    end

    if level > x310016_g_LevelMax then
		 return
    end
	
	AddQuestNumText(sceneId, x310016_g_ScriptId, x310016_g_MissionName,5,1);
	
end

---------------------------------------------------------------------------------------------------
--���븱��������ʾ
---------------------------------------------------------------------------------------------------
function x310016_DispatchEnterInfo( sceneId, selfId, NPCId )

	if GetGameOpenById(x310016_GameId)<=0 then
		x310016_ShowTips(sceneId, selfId,"�˻�ѹر�");
		return
	end

	local level = GetLevel(sceneId, selfId)
	local nYinkaBonus = level*600;
	local str1 = format("#Y%d����#W\n",nYinkaBonus)
 	local nExpBonus = level*4500;
	local str2 = format("#Y%d��ľ���#W\n",nExpBonus) 
	local nShengWangBonus = 1000
	
	local str3 = format("#Y%d������#W\n", nShengWangBonus) 
	
	local str4 = "#Y@itemid_"..x310016_g_BonusItem1.."\n#W"
	local str5 = "#Y@itemid_"..x310016_g_BonusItem2.."\n#W"
	local str6 = "#Y@itemid_"..x310016_g_BonusItem3.."\n#W"
	local str7 = "#Y@itemid_"..x310016_g_BonusItem4.."\n#W"
	local str8 = "#Y@itemid_"..x310016_g_BonusItem5.."\n#W"
  local str9 ="\n�㻹���ܻ�����½����е�һ�֣�\n"
	local str = "\n����ù̶�������\n"..str2..str9..str1..str3..str4..str5..str6..str7..str8


	BeginQuestEvent(sceneId)
	
  
  	
		--������Ϣ
		AddQuestText(sceneId,"#Y"..x310016_g_MissionName)
		AddQuestText(sceneId,x310016_g_EnterInfo..str)
		--AddQuestText(sceneId,str)
		


	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x310016_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x310016_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x310016_ProcAccept( sceneId, selfId )
	if GetGameOpenById(x310016_GameId)<=0 then
		x310016_ShowTips(sceneId, selfId,"�˻�ѹر�");
		return
	end

	x310016_OnRequestSubmit(sceneId, selfId);
end


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x310016_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)
	if GetGameOpenById(x310016_GameId)<=0 then
		x310016_ShowTips(sceneId, selfId,"�˻�ѹر�");
		return
	end

	if nFlag== nil then
		return
	end

	x310016_DispatchEnterInfo( sceneId, selfId, NPCId )
	
end


function x310016_OnRequestSubmit(sceneId, selfId)

	local iRet = x310016_CheckRequest(sceneId, selfId)

	if iRet>0 then
		x310016_OnApproveRequest(sceneId, selfId)
	end
end

function x310016_CheckRequest(sceneId, selfId)

	if( x310016_g_DayCountUntil > 0 ) then
		
		if x310016_GetDayCount(sceneId, selfId) >= x310016_g_DayCountUntil then

			local str = format("ÿ��ֻ�����%d�α��������������ɡ�",x310016_g_DayCountUntil)

			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return 0;
		end
	end

	for i,item in x310016_g_ItemIdList do
		local ItemCnt = GetItemCount( sceneId, selfId, item )

		if ItemCnt<x310016_g_NeedItemCount then
			local str = format("�������ƺ�û��@itemid_%d��",item)

			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
			EndQuestEvent();

			DispatchQuestTips(sceneId, selfId);
			return 0;
		end
	end

	local hour,minute,sec =GetHourMinSec();

	local nowtime = hour*60+minute
	

	
	for i, item in x310016_g_EnterTime do
		if nowtime >= item.min and nowtime <= item.max then
			
			
			return 1;
			
		end
	end
	x310016_ShowTips(sceneId, selfId,"���û��ʼ�أ������⹫�棬���ĵȴ���");
	return 0;

end

function x310016_OnApproveRequest(sceneId, selfId)
	
	if GetGameOpenById(x310016_GameId)<=0 then
		x310016_ShowTips(sceneId, selfId,"�˻�ѹر�");
		return
	end

	local nRet1, iRandom = x310016_GetBonusTest(sceneId, selfId)

	if nRet1==0 then
		x310016_ShowTips(sceneId, selfId,"�����ռ䲻�㣬�޷���ý�����Ʒ,����������");
	end
	
	local iRet=0;
	for i,item in x310016_g_ItemIdList do
		iRet = DelItem(sceneId, selfId,item,x310016_g_NeedItemCount)
	end



	if iRet>0 then
		x310016_GetBonus(sceneId, selfId,iRandom)
		x310016_SetDayCount(sceneId, selfId);

		
		local myGuid = GetPlayerGUID( sceneId,selfId )

		GetCountryQuestDataNM(sceneId,myGuid,0, CD_INDEX_CHINAJOY_DATE, x310016_g_ScriptId,-1,"OnGetChinaJoyDate",1)
	end
		
	
	
end


function x310016_OnGetChinaJoyDate(sceneId, selfId,MissionData,MissionId)

	
	
	local today = GetDayOfYear()

	

	if today~=MissionData then
		SetCountryQuestData(sceneId, 0, CD_INDEX_CHINAJOY_DATE,today)
		SetCountryQuestData(sceneId, 0, CD_INDEX_CHINAJOY_TIMES,0)
		
		local myGuid = GetPlayerGUID( sceneId,selfId )
		GetCountryQuestDataNM(sceneId,myGuid,0, CD_INDEX_CHINAJOY_TIMES, x310016_g_ScriptId,-1,"OnGetChinaJoyTimes",1)
		
	else
		local myGuid = GetPlayerGUID( sceneId,selfId )
		GetCountryQuestDataNM(sceneId,myGuid,0, CD_INDEX_CHINAJOY_TIMES, x310016_g_ScriptId,-1,"OnGetChinaJoyTimes",1)
	end

	
end

function x310016_OnGetChinaJoyTimes(sceneId, selfId,MissionData,MissionId)

	
	SetCountryQuestData(sceneId, 0, CD_INDEX_CHINAJOY_TIMES,MissionData+1)
	x310016_OnCompleteTimes(sceneId, selfId, MissionData+1)


	
end


function x310016_OnCompleteTimes(sceneId, selfId, nTimes)
	
	
	local guid = GetPlayerGUID( sceneId,selfId )	

	if nTimes==nil then
		return
	end

	
	if nTimes==888 then
		--д�����־
		
		--local msg = "ChinaJoy Bonus: guid="..guid..",name="..GetName(sceneId,selfId)..",country="..GetCurCountry(sceneId,selfId)..",times="..nTimes

		--WriteLog(23,msg)
		GamePlayScriptLog(sceneId, selfId, 892)

		local str = GetName(sceneId,selfId).."��ϲ�����ǵ�"..nTimes.."��������ռ���ʯ�������ң�����п��ܻ���Կ���ʼǱ��Ľ���Ŷ��"

		LuaAllScenceM2Wrold (sceneId,str, 0, 1)

		x310016_ShowTips(sceneId, selfId,"��ϲ�㣬����п��ܻ���Կ���ʼǱ��Ľ���Ŷ��");
	end

	--local msg = "ChinaJoy:"..guid..","..GetName(sceneId,selfId)..","..GetCurCountry(sceneId,selfId)..",times="..nTimes  -- 

	--WriteLog(1,msg)
	GamePlayScriptLog(sceneId, selfId, 882)

	
end

function x310016_GetBonusTest(sceneId, selfId)

	if GetGameOpenById(x310016_GameId)<=0 then
		x310016_ShowTips(sceneId, selfId,"�˻�ѹر�");
		return 0
	end

	local level = GetLevel(sceneId, selfId)



	local iRandom = random(1,1000)
	local nRet1 = 1;

	if iRandom<=370 then
		
	elseif iRandom<=780 then
		
	elseif iRandom<=820 then
		
		BeginAddItem(sceneId)
			AddBindItem( sceneId, x310016_g_BonusItem1, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
		else
			nRet1 = 0
		end
	elseif iRandom<=821 then
		
		BeginAddItem(sceneId)
			AddBindItem( sceneId, x310016_g_BonusItem2, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
		else
			nRet1 = 0
		end
	elseif iRandom<=850 then
		
		BeginAddItem(sceneId)
			AddItem( sceneId, x310016_g_BonusItem3, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
		else
			nRet1 = 0
		end
	elseif iRandom<=900 then
		
		BeginAddItem(sceneId)
			AddItem( sceneId, x310016_g_BonusItem4, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
		else
			nRet1 = 0
		end
	elseif iRandom<=1000 then
		
		BeginAddItem(sceneId)
			AddItem( sceneId, x310016_g_BonusItem5, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
		else
			nRet1 = 0
		end

	
	end
	
	return nRet1,iRandom
end

function x310016_GetBonus(sceneId, selfId, iRandom)

	if GetGameOpenById(x310016_GameId)<=0 then
		x310016_ShowTips(sceneId, selfId,"�˻�ѹر�");
		return
	end

	local level = GetLevel(sceneId, selfId)

--	a��LV*600��������      25%����
--b��LV*4500�ľ��飻     25%����
--c��1000��������        25%����
--d��1����������󶨣�  4%����   ȫ������
--e��1�����ӡ�ǣ��󶨣�  1%����   ȫ������
--f��1��С������¶        5%����   ȫ������
--g��1��С����            5%����   ȫ������
--h��1�����в�            10%����  ȫ������


	--local iRandom = 100

	if iRandom<=370 then

		local nYinkaBonus = level*600;
		if nYinkaBonus > 0 then
			AddMoney(sceneId, selfId, 1, nYinkaBonus)
			
			--local str = format("����%d������",nYinkaBonus)
			--Msg2Player(sceneId,selfId,str,4,2)
		local nExpBonus = level*4500;
			AddExp(sceneId, selfId, nExpBonus);
			
			local str = format("����%d��ľ��齱��",nExpBonus)
			Msg2Player(sceneId,selfId,str,4,2)			
		end
	elseif iRandom<=780 then
		local nShengWangBonus = 1000
		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + nShengWangBonus
		SetShengWang( sceneId, selfId, nShengWang )
		
		local str = format("�������%d������ֵ�Ľ�����", nShengWangBonus)
		Msg2Player(sceneId,selfId,str,4,2)
		Msg2Player(sceneId,selfId,str,4,3)
		local nExpBonus = level*4500;
			AddExp(sceneId, selfId, nExpBonus);
			
			local str = format("����%d��ľ��齱��",nExpBonus)
			Msg2Player(sceneId,selfId,str,4,2)	
	elseif iRandom<=820 then
		
		BeginAddItem(sceneId)
			AddBindItem( sceneId, x310016_g_BonusItem1, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
			AddItemListToPlayer(sceneId,selfId)
		

			x310016_ShowTips(sceneId, selfId, "��ý�����Ʒ@itemid_"..x310016_g_BonusItem1)

			local str = "��ϲ���"..GetName(sceneId, selfId).."���ռ���ʯ�Ļ�л�ý�����Ʒ@itemid_"..x310016_g_BonusItem1

			LuaAllScenceM2Wrold (sceneId,str, 0, 1)
					local nExpBonus = level*4500;
			AddExp(sceneId, selfId, nExpBonus);
			
			local str = format("����%d��ľ��齱��",nExpBonus)
			Msg2Player(sceneId,selfId,str,4,2)	
		end
	elseif iRandom<=821 then
		
		BeginAddItem(sceneId)
			AddBindItem( sceneId, x310016_g_BonusItem2, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
			AddItemListToPlayer(sceneId,selfId)
		

			x310016_ShowTips(sceneId, selfId, "��ý�����Ʒ@itemid_"..x310016_g_BonusItem2)

			local str = "��ϲ���"..GetName(sceneId, selfId).."���ռ���ʯ�Ļ�л�ý�����Ʒ@itemid_"..x310016_g_BonusItem2

			LuaAllScenceM2Wrold (sceneId,str, 0, 1)
					local nExpBonus = level*4500;
			AddExp(sceneId, selfId, nExpBonus);
			
			local str = format("����%d��ľ��齱��",nExpBonus)
			Msg2Player(sceneId,selfId,str,4,2)	
		end
	elseif iRandom<=850 then
		
		BeginAddItem(sceneId)
			AddItem( sceneId, x310016_g_BonusItem3, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
			AddItemListToPlayer(sceneId,selfId)
		

			x310016_ShowTips(sceneId, selfId, "��ý�����Ʒ@itemid_"..x310016_g_BonusItem3)

			local str = "��ϲ���"..GetName(sceneId, selfId).."���ռ���ʯ�Ļ�л�ý�����Ʒ@itemid_"..x310016_g_BonusItem3

			LuaAllScenceM2Wrold (sceneId,str, 0, 1)
					local nExpBonus = level*4500;
			AddExp(sceneId, selfId, nExpBonus);
			
			local str = format("����%d��ľ��齱��",nExpBonus)
			Msg2Player(sceneId,selfId,str,4,2)	
		end
	elseif iRandom<=900 then
		
		BeginAddItem(sceneId)
			AddItem( sceneId, x310016_g_BonusItem4, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
			AddItemListToPlayer(sceneId,selfId)
		

			x310016_ShowTips(sceneId, selfId, "��ý�����Ʒ@itemid_"..x310016_g_BonusItem4)

			local str = "��ϲ���"..GetName(sceneId, selfId).."���ռ���ʯ�Ļ�л�ý�����Ʒ@itemid_"..x310016_g_BonusItem4

			LuaAllScenceM2Wrold (sceneId,str, 0, 1)
					local nExpBonus = level*4500;
			AddExp(sceneId, selfId, nExpBonus);
			
			local str = format("����%d��ľ��齱��",nExpBonus)
			Msg2Player(sceneId,selfId,str,4,2)	
		end
	elseif iRandom<=1000 then
		
		BeginAddItem(sceneId)
			AddItem( sceneId, x310016_g_BonusItem5, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
			AddItemListToPlayer(sceneId,selfId)
		

			x310016_ShowTips(sceneId, selfId, "��ý�����Ʒ@itemid_"..x310016_g_BonusItem5)

			local str = "��ϲ���"..GetName(sceneId, selfId).."���ռ���ʯ�Ļ�л�ý�����Ʒ@itemid_"..x310016_g_BonusItem5

			LuaAllScenceM2Wrold (sceneId,str, 0, 1)
					local nExpBonus = level*4500;
			AddExp(sceneId, selfId, nExpBonus);
			
			local str = format("����%d��ľ��齱��",nExpBonus)
			Msg2Player(sceneId,selfId,str,4,2)	
		end

	end
	
end

function x310016_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end


---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x310016_GetDayCount(sceneId, selfId)



	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_CHINAJOY_DATE[1], MD_CHINAJOY_DATE[2],MD_CHINAJOY_DATE[3] );
	
	if lastday ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, MD_CHINAJOY_DAYCOUNT[1], MD_CHINAJOY_DAYCOUNT[2],MD_CHINAJOY_DAYCOUNT[3] );

	return daycount;

	

end

---------------------------------------------------------------------------------------------------
--���õ������
---------------------------------------------------------------------------------------------------
function x310016_SetDayCount(sceneId, selfId)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_CHINAJOY_DATE[1], MD_CHINAJOY_DATE[2], MD_CHINAJOY_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_CHINAJOY_DATE[1], MD_CHINAJOY_DATE[2], MD_CHINAJOY_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_CHINAJOY_DAYCOUNT[1], MD_CHINAJOY_DAYCOUNT[2], MD_CHINAJOY_DAYCOUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_CHINAJOY_DAYCOUNT[1], MD_CHINAJOY_DAYCOUNT[2], MD_CHINAJOY_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, MD_CHINAJOY_DAYCOUNT[1], MD_CHINAJOY_DAYCOUNT[2], MD_CHINAJOY_DAYCOUNT[3], daycount+1)
	end
	
	
	
end
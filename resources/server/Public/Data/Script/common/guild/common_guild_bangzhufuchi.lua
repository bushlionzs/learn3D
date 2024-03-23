--desc  : "�������ּƻ�"

x300972_g_ScriptId 					= 	300972                  --�ű�ID
x300972_g_Title						=  "����᡿��ᷢչ����" 
x300972_g_BONUS_TBL_IDX = 
{
1000000 ,
2000000,
3000000,
5000000,
7000000,
10000000,
15000000,
20000000,
25000000,
30000000,
35000000,
40000000,
50000000,
60000000,
70000000,
80000000,
90000000,
100000000
} 
x300972_g_BONUS_TBL = 
{
100000,
200000,
300000,
400000,
560000,
800000,
1000000,
1200000,
1500000,
1800000,
2100000,
2400000,
2800000,
3300000,
3800000,
4300000,
4800000,
5300000
}

x300972_g_Quest_Max_Count = 1 
x300972_g_GameId = 1057
 

function x300972_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	if GetGameOpenById(x300972_g_GameId) ~= 1 then
		return 0
	end

	if GetGuildID(sceneId, selfId) == -1 then
		--δ������
		return 0
	end
	
	local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= 5 then
		return 0
	end
	AddQuestNumText(sceneId,x300972_g_ScriptId,x300972_g_Title, 3, -1)	
end


--ѡ������
function x300972_ProcEventEntry( sceneId, selfId, NPCId, MissionId,nExtIdx )
	--PrintNum(nExtIdx)
	if nExtIdx == -1 then
						--�Ƿ�Ϊ����
						local pos = GetGuildOfficial(sceneId, selfId)
						--PrintNum(pos)
						if pos ~= 5 then
												BeginQuestEvent(sceneId)
												AddQuestText(sceneId,"�ܱ�Ǹ��ֻ�а���������ȡ��ᷢչ����")
												EndQuestEvent(sceneId)
												--DispatchQuestEventList(sceneId, selfId, NPCId)       
												DispatchQuestInfo(sceneId, selfId, NPCId, x300972_g_ScriptId, -1,  0)
												Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ�а���������ȡ��ᷢչ����",8,2)	
												return
						end
						
						local nGuildID = GetGuildID(sceneId,selfId)
						
						local year, curMonth,  day = GetYearMonthDay()
						curMonth = year*100 + curMonth
						local sysCurMonth = GetGuildParam(nGuildID, GD_GUILD_CURMONTH)
						if curMonth ~= sysCurMonth then --������,����ƽ��
						
									local nCurMonth = GetGuildParam(nGuildID, GD_GUILD_CURMONTH)
									local nCurMoney = GetGuildParam(nGuildID, GD_GUILD_CURMONTH_GUILD_MEMBER_MONEY)
									
									SetGuildParam(nGuildID,GD_GUILD_CURMONTH,curMonth)
									SetGuildParam(nGuildID,GD_GUILD_CURMONTH_GUILD_MEMBER_MONEY,0)					--�������¿�ʼ����
									
									
									SetGuildParam(nGuildID,GD_GUILD_LASTMONTH,nCurMonth)
									SetGuildParam(nGuildID,GD_GUILD_LASTMONTH_GUILD_MEMBER_MONEY,nCurMoney )			        --�������µ��ܽ��						
						end
						
				

						
						--���±�����Ա�����ܶ�
						local nTotalLast = GetGuildParam(nGuildID,GD_GUILD_LASTMONTH_GUILD_MEMBER_MONEY) 
						
						--���±�����Ա��ֵ�ܶ�
						local nTotalNow = GetGuildParam(nGuildID,GD_GUILD_CURMONTH_GUILD_MEMBER_MONEY)  
						--PrintNum(nTotalNow)
						
						local nTotal   = GetGuildParam(nGuildID,GD_GUILD_LASTMONTH_GUILD_MEMBER_MONEY)  --��ȡ�����°���Ա���ܵ����ѽ��
						--PrintNum(nTotal)
						
						--��ʾ�콱�����Լ�˵������
						local nCur ,nIdx  =  x300972_GetBonus(sceneId, selfId,nTotalNow)
						local nNext =  x300972_GetBonus_NextMonth(sceneId, selfId,nIdx)
						local nNext2 = 0
						if nIdx < 18 then
												nNext2 =  x300972_g_BONUS_TBL[nIdx+1]
										
												local str_last = x300972_GetMoney_Liang(sceneId,nTotalLast)
												local str_now  = x300972_GetMoney_Liang(sceneId,nTotalNow)
												local str_cur = x300972_GetMoney_Liang(sceneId,nCur)
												local str_next = x300972_GetMoney_Liang(sceneId,nNext)
												local str_next2 = x300972_GetMoney_Liang(sceneId,nNext2)
												
												local nBindGold ,nIdx = x300972_GetBonus(sceneId, selfId,nTotal)
												local str_bind = x300972_GetMoney_Liang(sceneId,nBindGold)



												BeginQuestEvent(sceneId)
												AddQuestText(sceneId,"#Y"..x300972_g_Title)
												AddQuestText(sceneId,"\t���ķ�չ����Ҫ����һ�ģ��ͳ�����ʽ𡣶����õİ���ټ���츳�з��ȵȣ�����Ҫ�������Ƶ��ʽ�\n\t��ᷢչ�����Ŀ������Ϊ�˰��ĳ�����չ������Դ�ڸ�λ����ÿ�µ��ֽ�����֮�ͣ�ÿ�µ׽��㣬�����ڱ��½���֮ǰ��������ȡ���µĻ���\n#B���˹��ܽ������ɼ���#W\n \n#Y������ȡ��\n#W��#G����#W������ȡ����#R"..str_bind.."#W\n \n#Y������ȡ��#W\n��#G����#W������ȡ����#R"..str_cur.."#W,���#G����#W�����������ֽ�#G"..str_next.."#W����#G����#W�Ϳ�����ȡ#R"..str_next2.."#W���ˡ�")
												--AddQuestNumText(sceneId,x300972_g_ScriptId,"��ȡ��������",13,1)
												EndQuestEvent()
												--DispatchQuestEventList(sceneId, selfId, NPCId)			
												DispatchQuestInfo(sceneId, selfId, NPCId, x300972_g_ScriptId, -1,  0)
							
							
						else
												nNext2 =  x300972_g_BONUS_TBL[nIdx]
									
																			
												local str_last = x300972_GetMoney_Liang(sceneId,nTotalLast)
												local str_now  = x300972_GetMoney_Liang(sceneId,nTotalNow)

												local str_cur = x300972_GetMoney_Liang(sceneId,nCur)
												local str_next = x300972_GetMoney_Liang(sceneId,nNext)
												local str_next2 = x300972_GetMoney_Liang(sceneId,nNext2)
												
												local nBindGold ,nIdx = x300972_GetBonus(sceneId, selfId,nTotal)
												local str_bind = x300972_GetMoney_Liang(sceneId,nBindGold)



												BeginQuestEvent(sceneId)
												AddQuestText(sceneId,"#Y"..x300972_g_Title)
												AddQuestText(sceneId,"\t���ķ�չ����Ҫ����һ�ģ��ͳ�����ʽ𡣶����õİ���ټ���츳�з��ȵȣ�����Ҫ�������Ƶ��ʽ�\n\t��ᷢչ�����Ŀ������Ϊ�˰��ĳ�����չ������Դ�ڸ�λ����ÿ�µ��ֽ�����֮�ͣ�ÿ�µ׽��㣬�����ڱ��½���֮ǰ��������ȡ���µĻ���\n#B���˹��ܽ������ɼ���#W\n \n#Y������ȡ��\n#W��#G����#W������ȡ����#R"..str_bind.."#W\n \n#Y������ȡ��#W\n��#G����#W������ȡ����#R"..str_cur.."")
												--AddQuestNumText(sceneId,x300972_g_ScriptId,"��ȡ��������",13,1)
												EndQuestEvent()
												--DispatchQuestEventList(sceneId, selfId, NPCId)			
												DispatchQuestInfo(sceneId, selfId, NPCId, x300972_g_ScriptId, -1,  0)
												--DispatchQuestTips(sceneId,selfId)     
							
						end

	 end
	
end


function x300972_GetMoney_Liang(sceneId,nMoney)
			if nMoney <= 0 then
				local str = "0��"
				return str
			end
				
				
			local ding = floor(nMoney/(1000*1000))
			local liang = floor((nMoney-ding*1000*1000)/1000)
			local wen = nMoney-(ding*1000*1000+liang*1000)
			local str=""
			if ding>0 then
				str = str..format("%d��",ding)
			end

			if liang>0 then
				str = str..format("%d��",liang)
			end

			if wen>0 then
				str = str..format("%d��",wen)
			end

			return str;
end


function x300972_GetBonus_NextMonth(sceneId, selfId,nIdx)
		local nGuildID = GetGuildID(sceneId,selfId)
		if nIdx < 18 then
			--PrintNum(GetGuildParam(nGuildID,GD_GUILD_CURMONTH_GUILD_MEMBER_MONEY))
			return x300972_g_BONUS_TBL_IDX[nIdx + 1] - GetGuildParam(nGuildID,GD_GUILD_CURMONTH_GUILD_MEMBER_MONEY)			
		else
			return x300972_g_BONUS_TBL_IDX[nIdx]
		end
		return 0
end



function x300972_GetBonus(sceneId, selfId,nTotal)
	if nTotal <= 0 then
		return 0,0
	end
	
	if nTotal < x300972_g_BONUS_TBL_IDX[1] then
		return 0 , 0
	end
	
	if nTotal >= x300972_g_BONUS_TBL_IDX[1] and nTotal < x300972_g_BONUS_TBL_IDX[2] then
		return x300972_g_BONUS_TBL[1] , 1
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[2] and nTotal < x300972_g_BONUS_TBL_IDX[3] then
		return x300972_g_BONUS_TBL[2] , 2
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[3] and nTotal < x300972_g_BONUS_TBL_IDX[4] then
		return x300972_g_BONUS_TBL[3] ,  3
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[4] and nTotal < x300972_g_BONUS_TBL_IDX[5] then
		return x300972_g_BONUS_TBL[4],  4
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[5] and nTotal < x300972_g_BONUS_TBL_IDX[6] then
		return x300972_g_BONUS_TBL[5], 5
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[6] and nTotal < x300972_g_BONUS_TBL_IDX[7] then
		return x300972_g_BONUS_TBL[6], 6
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[7] and nTotal < x300972_g_BONUS_TBL_IDX[8] then
		return x300972_g_BONUS_TBL[7], 7
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[8] and nTotal < x300972_g_BONUS_TBL_IDX[9] then
		return x300972_g_BONUS_TBL[8], 8
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[9] and nTotal < x300972_g_BONUS_TBL_IDX[10] then
		return x300972_g_BONUS_TBL[9], 9
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[10] and nTotal < x300972_g_BONUS_TBL_IDX[11] then
		return x300972_g_BONUS_TBL[10], 10
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[11] and nTotal < x300972_g_BONUS_TBL_IDX[12] then
		return x300972_g_BONUS_TBL[11], 11
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[12] and nTotal < x300972_g_BONUS_TBL_IDX[13] then
		return x300972_g_BONUS_TBL[12], 12
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[13] and nTotal < x300972_g_BONUS_TBL_IDX[14] then
		return x300972_g_BONUS_TBL[13], 13
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[14] and nTotal < x300972_g_BONUS_TBL_IDX[15] then
		return x300972_g_BONUS_TBL[14], 14
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[15] and nTotal < x300972_g_BONUS_TBL_IDX[16] then
		return x300972_g_BONUS_TBL[15], 15
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[16] and nTotal < x300972_g_BONUS_TBL_IDX[17] then
		return x300972_g_BONUS_TBL[16], 16
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[17] and nTotal < x300972_g_BONUS_TBL_IDX[18] then
		return x300972_g_BONUS_TBL[17], 17
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[18] then
		return x300972_g_BONUS_TBL[18], 18
	end	
	
	return  0, 0
end


--------------------------------------------------------------------------------------------------------------
-------------���µ�������ȡ�����Ĵ���
-------------from common_loulan_fangyuzhilu.lua
--------------------------------------------------------------------------------------------------------------
-----------function x300972_GetMonthCount(sceneId, selfId)
-----------	--PrintStr("x300980_GetDayCount")
-----------	if x300972_g_Quest_Max_Count > 0 then
-----------		local year, curMonth,  day = GetYearMonthDay()
-----------		local lastMonth			   = GetQuestData(sceneId, selfId, MD_LOULAN_GUILD_BANGZHUFUZHI_MONTH[1], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTH[2], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTH[3])
-----------		if curMonth ~= lastMonth then
-----------			return 0
-----------		end
-----------
-----------		local monthcount =  GetQuestData(sceneId, selfId, MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[1], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[2], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[3])
-----------		return monthcount
-----------
-----------	end
-----------	return 0
-----------end



-----------------------------------------------`--------------------------------------------------------------
------------���µ�������ȡ���½����Ĵ���
------------from common_loulan_fangyuzhilu.lua
-------------------------------------------------------------------------------------------------------------
----------function x300972_SetMonthCount(sceneId, selfId)
----------	local year, curMonth,  day = GetYearMonthDay()
----------	local lastMonth = GetQuestData(sceneId, selfId, MD_LOULAN_GUILD_BANGZHUFUZHI_MONTH[1], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTH[2], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTH[3])
----------	if curMonth ~= lastMonth then
----------		SetQuestData(sceneId, selfId, MD_LOULAN_GUILD_BANGZHUFUZHI_MONTH[1], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTH[2], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTH[3], curMonth)
----------		SetQuestData(sceneId, selfId, MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[1], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[2], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[3], 1)		
----------	else
----------				
----------		local monthcount = GetQuestData(sceneId, selfId, MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[1], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[2], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[3])
----------		SetQuestData(sceneId, selfId, MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[1], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[2], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[3], monthcount+1)		
----------	end
----------end


--**********************************
--����
--**********************************
function x300972_ProcAccept( sceneId, selfId )
	--�ڴ˴��������
	--PrintStr("x300972_ProcAccept")

	--�Ƿ�Ϊ����
	local pos = GetGuildOfficial(sceneId, selfId)
	--PrintNum(pos)
	if pos ~= 5 then
							return -1
	end

					
	--���±�����Ա��ֵ�ܶ�
	local nGuildID = GetGuildID(sceneId,selfId)
	--PrintNum(nGuildID)
	local nTotal    = GetGuildParam(nGuildID,GD_GUILD_LASTMONTH_GUILD_MEMBER_MONEY)  --��ȡ�����°���Ա���ܵ����ѽ��
	if nTotal <= 0 then
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"�������İ���Ա���ֽ����Ѳ�����߱�����������Ѿ���ȡ��һ�Σ��޷���ȡ��ᷢչ����")
							--DispatchQuestEventList(sceneId, selfId, NPCId)       
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId, selfId)
							Msg2Player(sceneId,selfId,"�������İ���Ա���ֽ����Ѳ�����߱�����������Ѿ���ȡ��һ�Σ��޷���ȡ��ᷢչ����",8,2)
							return
	end

	
	--���ݹ�ʽ���㷵����
	--to be fixed!!!
	--��֪����ʽ!!!	
	local nBindGold ,nIdx = x300972_GetBonus(sceneId, selfId,nTotal)
	if nBindGold == 0 then
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"#Y"..x300972_g_Title)
							AddQuestText(sceneId,"�������İ���Ա���ֽ����Ѳ�����߱�����������Ѿ���ȡ��һ�Σ��޷���ȡ��ᷢչ����")
							EndQuestEvent()
							--DispatchQuestInfo(sceneId, selfId, -1,x300972_g_ScriptId,-1,0) 
							DispatchQuestEventList(sceneId, selfId, -1) 
							
							Msg2Player(sceneId,selfId,"�������İ���Ա���ֽ����Ѳ�����߱�����������Ѿ���ȡ��һ�Σ��޷���ȡ��ᷢչ����",8,2)							
							return -1
	end

	--�ϸ�����0
	--��0�������ڽ�����ǰ���ֹ�����ȡ
	local year, curMonth,  day = GetYearMonthDay()
	curMonth = year*100 + curMonth
	SetGuildParam(nGuildID,GD_GUILD_LASTMONTH_GUILD_MEMBER_MONEY,0)
	SetGuildParam(nGuildID,GD_GUILD_LASTMONTH,curMonth)
	SetGuildParam(nGuildID,GD_GUILD_CURMONTH, curMonth)
	
				
	local moneymes = "������"
	--������
	local ret = AddMoney( sceneId, selfId, 3, nBindGold )
	if ret <= 0 then
							GamePlayScriptLog(sceneId, selfId, 1732) --��ȡʧ��
	else
							local nBindStr = x300972_GetMoney_Liang(sceneId,nBindGold)
							Msg2Player(sceneId, selfId,"�ɹ���ȡ��ᷢչ����#R"..nBindStr.."�𿨽���", 8, 2);
							Msg2Player(sceneId, selfId,"�ɹ���ȡ��ᷢչ����#R"..nBindStr.."�𿨽���", 8, 3)
							GamePlayScriptLog(sceneId, selfId, 1731) --��ȡ�ɹ�
	end
	

	
end

function x300972_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--�����ȷ����
function x300972_ProcQuestAccept( sceneId, selfId, NPCId )
	--PrintStr("x300972_ProcQuestAccept")
end



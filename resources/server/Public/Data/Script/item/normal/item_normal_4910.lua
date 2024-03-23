--desc	: "��Ч������ż"���߽ű�

x404910_g_scriptId = 404910


x404910_g_DestSceneName = "ǿЧ������ż"
x404910_g_Get_Exp_Max_Cnt = 15 --������Ч������ż������һ�ü��ܾ������������Ϊ15��
x404910_g_BossType  = 9527
x404910_g_MissionID = 9092

function x404910_GetMonsterCount(sceneId, selfId)
	local nCount = 0;
	local nMonsterCount = GetMonsterCount(sceneId)
	for i=1,nMonsterCount do
    	local objid		 	= 	GetMonsterObjID(sceneId,i-1)
		--if IsObjValid(sceneId,objid) == 1 and GetHp(sceneId,objid) > 0 then
			local npcType 		= 	GetMonsterDataID(sceneId,objid)

				if npcType == 9526 or npcType == 9527 then
					nCount = nCount + 1
			end
		--end
	end

	return nCount
end

function x404910_ProcEventEntry( sceneId, selfId, BagIndex )

	local nCnt  =  x404910_GetDayCount(sceneId, selfId) + 1
	if    nCnt  >  x404910_g_Get_Exp_Max_Cnt then
		  local strText = "#Yר��ѵ����\n\t#W��������Ի��ר��������ɱ������#R����#W��������ͨ������������ż���ר��������\n \n#Yר��ѵ����\n\t#W������ż����#G����#W����ɡ�����֮·�����񣬻���������ż�൱�ڻ���#G�κ�ְҵ#W����ҡ�\n \n#Y������\n\t#W��������δ��������£�����������ż�Կ��Ի��������\n \n\t#R���Ƿ�Ҫ���ʹ�ã�"
		  BeginQuestEvent(sceneId)
		  AddQuestText(sceneId, strText)
		  EndQuestEvent(sceneId)
		  --DispatchQuestTips(sceneId, selfId)
		  --DispatchQuestInfo(sceneId, selfId, selfId, x404910_g_scriptId, x404910_g_MissionID,  0)
		  DispatchQuestInfoNM(sceneId, selfId, selfId, x404910_g_scriptId, x404910_g_MissionID,  0)
		  --Msg2Player(sceneId,selfId,strText, 8, 2)
		  return 
	else
		  x404910_ProcMyTask( sceneId, selfId)
	end




	------------------------------------------------if x404910_GetMonsterCount(sceneId, selfId) == 10 then
	------------------------------------------------	  BeginQuestEvent(sceneId)
	------------------------------------------------	  AddQuestText(sceneId, "��������ľ׮�˹��࣬����ܺ��ټ����ٻ���")
	------------------------------------------------	  EndQuestEvent(sceneId)
	------------------------------------------------	  DispatchQuestTips(sceneId, selfId)
	------------------------------------------------	  return
	------------------------------------------------end
	------------------------------------------------
	--------------------------------------------------ɾ�������߼�,ʹ��һ��ɾ��һ��
	------------------------------------------------local nItemCount = GetItemCountInBag( sceneId, selfId, 12030218)
	------------------------------------------------if nItemCount >= 1 then
	------------------------------------------------		local ret = DelItemByIDInBag( sceneId, selfId, 12030218, 1) --ɾ����Ʒ
	------------------------------------------------else
	------------------------------------------------		return 0
	------------------------------------------------end
	------------------------------------------------
	------------------------------------------------local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )
	------------------------------------------------local ret = CreateMonster( sceneId, x404910_g_BossType, PlayerPosX, PlayerPosZ, 1, -1, x404910_g_scriptId, -1, 21,3*60000) --���ʱ��3����
    ------------------------------------------------
	------------------------------------------------if ret > 0 then
	------------------------------------------------		--DelItem( sceneId, selfId, 12030218, 1); --ɾ����Ʒ
	------------------------------------------------		--local ret = DelItemByIDInBag( sceneId, selfId, 12030218, 1) --ɾ����Ʒ
	------------------------------------------------		local message = "��Ч������ż�ٻ��Ĺ��������"
	------------------------------------------------		Msg2Player(sceneId,selfId,message, 8, 2)
	------------------------------------------------		Msg2Player(sceneId,selfId,message, 8, 3)
	------------------------------------------------		--GLOBAL_CREATE_MONSTER_CNT_PER_SCENE[sceneId] = GLOBAL_CREATE_MONSTER_CNT_PER_SCENE[sceneId] + 1
	------------------------------------------------else
	------------------------------------------------		local strText = format("������Ч������ż�޷��ٳ�����" )
	------------------------------------------------		BeginQuestEvent(sceneId)
	------------------------------------------------		AddQuestText(sceneId, strText)
	------------------------------------------------		EndQuestEvent(sceneId)
	------------------------------------------------		DispatchQuestTips(sceneId, selfId)
	------------------------------------------------		Msg2Player(sceneId,selfId,strText, 8, 2)
	------------------------------------------------end
end

function x404910_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x404910_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x404910_OnConditionCheck( sceneId, selfId )
	return 0
end

function x404910_OnDeplete( sceneId, selfId )

	return 0
end

function x404910_OnActivateOnce( sceneId, selfId )
end

function x404910_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end

function x404910_OnDie(sceneId, selfId, killerId)--�����������־

	--�ٻ�������˿��Ի����ͬɱ������ͬ�ȼ������ҵ�Ч�������Ի��������ר�����ܾ���㣩
	--�����롰������ż��һ�£����ǿ��������ͨ���ר�������ɱ������
    --������Ҫʵ���߼�
	--to be fixed!!!

	--ɱ��������˿��Ի����ͬɱ������ͬ�ȼ������ҵ�Ч�������Ի��������ר�����ܾ���㣩
	--to be fixed!!!


	--����������������ʵ���ع�һ��
	--function x888888_CalculateHonor( mapId, diedId, killerId )
	--��Ҫ�ж϶��ߵļ����Ƿ����
	--from function x888888_HonorNumCalculate( mapId, diedId, killerId )

	local killerLevel = GetLevel(sceneId, killerId)
	local diedLevel   = killerLevel

	--����ɱ�ߵȼ���ƽ��/��ɱ���ߵȼ�+��ɱ�ߵȼ�����/2
	local honor = (diedLevel * diedLevel / (killerLevel + diedLevel)) / 2
	local killerCountry = GetCurCountry(sceneId, killerId)
	--��������
	local tempHonor = floor(honor);
	if honor >= tempHonor + 0.5 then
		honor = tempHonor + 1
	else
		honor = tempHonor
	end

	if x404910_IsCanAddHonor(sceneId, selfId, killerId) == 1 then
		SetHonorInfo(sceneId, killerId, "HONORNUM", GetHonorInfo(sceneId, killerId, "HONORNUM") +honor)
		AddHonor(sceneId, killerId, honor)
		local szMsg = "�������#G" .. honor .. "#o��"
		local killerName = GetName(sceneId,killerId)
		LuaScenceM2Player(sceneId, killerId, szMsg, killerName, CHAT_RIGHTDOWN, 1 )
	end

	--���ר�����ܵ�
	--to be fixed!!!
	local nCnt  =  x404910_GetDayCount(sceneId, killerId) + 1
	if    nCnt  >  x404910_g_Get_Exp_Max_Cnt then
		  return -1
	else
		local strMSG = AddInherenceZhuanGongExp(sceneId,killerId)
		Msg2Player(sceneId,killerId,strMSG,8,2)
		x404910_SetDayCount(sceneId, killerId)
	end

end



--������ż����Ч������ż����ͬһ��MD
--ÿ���жϵ���������ͬ
---------------------------------------------------------------------------------------------------
--ȡ�û�ȡר�����ܾ���������
--from common_daguanyuan_tianfu.lua
---------------------------------------------------------------------------------------------------
function x404910_GetDayCount(sceneId, selfId)
	if x404910_g_Get_Exp_Max_Cnt > 0 then
		local today = GetDayOfYear()
		--local lastday = GetQuestData(sceneId, selfId, MD_FUBEN_DAGUANYUAN_SHANGXIANG_DATE[1], MD_FUBEN_DAGUANYUAN_SHANGXIANG_DATE[2], MD_FUBEN_DAGUANYUAN_SHANGXIANG_DATE[3])
		local lastday = GetQuestData(sceneId, selfId, MD_TISHENSHADAI_DATE[1], MD_TISHENSHADAI_DATE[2], MD_TISHENSHADAI_DATE[3])
		if lastday ~= today then
			return 0
		end

		--local daycount =  GetQuestData(sceneId, selfId, MD_FUBEN_DAGUANYUAN_SHANGXIANG_DAYCOUNT[1], MD_FUBEN_DAGUANYUAN_SHANGXIANG_DAYCOUNT[2], MD_FUBEN_DAGUANYUAN_SHANGXIANG_DAYCOUNT[3])
		local daycount =  GetQuestData(sceneId, selfId, MD_TISHENSHADAI_DAYCOUNT[1], MD_TISHENSHADAI_DAYCOUNT[2], MD_TISHENSHADAI_DAYCOUNT[3])
		return daycount

	end
	return 0
end



-------------------------------------`--------------------------------------------------------------
--���µ����ȡר�����ܾ�������
--from common_daguanyuan_tianfu.lua
---------------------------------------------------------------------------------------------------
function x404910_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_TISHENSHADAI_DATE[1], MD_TISHENSHADAI_DATE[2], MD_TISHENSHADAI_DATE[3])
	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_TISHENSHADAI_DATE[1], MD_TISHENSHADAI_DATE[2], MD_TISHENSHADAI_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_TISHENSHADAI_DAYCOUNT[1], MD_TISHENSHADAI_DAYCOUNT[2], MD_TISHENSHADAI_DAYCOUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_TISHENSHADAI_DAYCOUNT[1], MD_TISHENSHADAI_DAYCOUNT[2], MD_TISHENSHADAI_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, MD_TISHENSHADAI_DAYCOUNT[1], MD_TISHENSHADAI_DAYCOUNT[2], MD_TISHENSHADAI_DAYCOUNT[3], daycount+1)
	end
end


function x404910_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x404910_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x404910_OnConditionCheck( sceneId, selfId )
	return 0
end

function x404910_OnDeplete( sceneId, selfId )

	return 0
end

function x404910_OnActivateOnce( sceneId, selfId )
end

function x404910_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end

function x404910_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
end

function x404910_ProcAccept( sceneId, selfId )
end

function x404910_ProcMyTask( sceneId, selfId)

	if GetSceneType(sceneId) ~=0 then
			BeginQuestEvent(sceneId)
		  AddQuestText(sceneId, "�����޷�ʹ�øõ��ߣ���ǰ����ͨ������")
		  EndQuestEvent(sceneId)
		  DispatchQuestTips(sceneId, selfId)
		  return 
	end

	if x404910_GetMonsterCount(sceneId, selfId) == 50 then
		  BeginQuestEvent(sceneId)
		  AddQuestText(sceneId, "����������ż���࣬����ܺ��ټ����ٻ���")
		  EndQuestEvent(sceneId)
		  DispatchQuestTips(sceneId, selfId)
		  return
	end

	local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )
	local nGuid   = GetGUID(sceneId,    selfId)
	local nCampId = 21
	--local nCampId = GetCurCamp(sceneId, selfId)

	--ɾ�������߼�,ʹ��һ��ɾ��һ��
	local nItemCount = GetItemCountInBag( sceneId, selfId, 12030218)
	--print("-------------------->",nItemCount)
	if nItemCount >= 1 then
			local ret = DelItemByIDInBag( sceneId, selfId, 12030218, 1) --ɾ����Ʒ
	else
			--print("------------------------------------")
			return 0
	end
	local r0 = random(-1,1)
	local r1 = random(-1,1)
	local ret = CreateMonster( sceneId, x404910_g_BossType, PlayerPosX+r0, PlayerPosZ+r1, 7, -1, x404910_g_scriptId, nGuid, 21, 3*60000) --���ʱ��3����

	if ret > 0 then
					local message = "ǿЧ������ż������"
					Msg2Player(sceneId,selfId,message, 8, 2)
					Msg2Player(sceneId,selfId,message, 8, 3)
	else
					local strText = format("�����޷��ٳ�ǿЧ������ż" )
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, strText)
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId, selfId)
					Msg2Player(sceneId,selfId,strText, 8, 2)
	end
end


--********************
--����������
--**********************************
function x404910_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

function x404910_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	x404910_ProcMyTask( sceneId, selfId)
end



function x404910_IsCanAddHonor(sceneId, selfId, killerId)
	--ÿ����������� ����������� ����֮
	local today = GetDayOfYear()
	local honorDay = GetHonorInfo(sceneId, killerId, "HONORDAY") 
	if today ~= honorDay then
		SetHonorInfo(sceneId, killerId, "HONORDAY", today)
		SetHonorInfo(sceneId, killerId, "HONORNUM", 0)
	end
	
	local selfLevel = GetLevel(sceneId, killerId)
	local honorNum = GetHonorInfo(sceneId, killerId, "HONORNUM")
	local honorMax = 0
	if IsHaveSpecificImpact( sceneId, killerId, 9016) > 0 then
		honorMax = selfLevel * 40
	else
		honorMax = selfLevel * 20
	end
	
	if honorNum >= honorMax then
		Msg2Player(sceneId,killerId,"������Ѿ��ﵽÿ��ɱ���������ޣ����첻����ͨ����ɱľż�������������", 8, 2) 
		return -1
	end
	
	return 1
end

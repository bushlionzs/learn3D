--¥��ʦͽ����
x310307_g_ScriptId = 310307
x310307_g_GameId	= 1037

x310307_g_MissionName	= "��ʦͽ��������ʿ"
x310307_g_MissionId	= 9342
x310307_g_MasterDistance = 15
x310307_g_LimitTimes = 1

x310307_g_GoodBadValue = 2500
x310307_g_ExpRate = 30000
x310307_g_ExpRate_Low = 5000

x310307_g_LevelLessPrentice = 20
x310307_g_LevelLessMaster = 50
x310307_g_MissionReplyGuid = 129023
x310307_g_MissionReply          = "@npc_129023"

x310307_g_ItemID = 12030211

-- NPC Id�����ϵ����ʾ�Ѿ����й�����Ի�
x310307_g_HasTalkedCoff            = 100
-- ������񱣴��MP���ڴ�ֵ��ʾ�Ѿ����й�����Ի�
x310307_g_HasTalkedValue           = 10000000

-- NPC Id�����ϵ����ʾ�Ѿ����й�����
x310307_g_HasAnsweredCoff            = 10
-- ������񱣴��MP���ڴ�ֵ��ʾ�Ѿ����й�����
x310307_g_HasAnsweredValue           = 100000000

x310307_g_strNPCTalk             = {
					{ID = 129017 , content = "\t�����������ҽʦ������������ˣ��ҿ��԰���ָ�������"},	
					{ID = 129018 , content = "\t���ǰ�ս�����ˣ��ܵ���İ���۸����������ͨ��������Է������ս�ɡ�"}, 
					{ID = 129019 , content = "\t���ǹ�ս�����ˣ�������ս�²��ϣ�����ӵ��һ��ʵ����Ҫ��������Ϊ��������"}, 
					{ID = 129020 , content = "\t���ǰ�����񷢲��ˣ���ҪΪ�Լ��İ�ᾡһ���������ҾͶ��ˡ�"}, 
					{ID = 129021 , content = "\t���ǹ��ҹ���Ա��ͨ���ҿ��Բμ�����ս����ѯ�Լ��Ĺ�ѫֵ"}, 

					{ID = 129024 , content = "\t�����������ˣ������������������ֵ��ȡ�ܶ�ʵ�õĶ�������Ҫ�������"},
					{ID = 129025 , content = "\t����ҩ�����ˣ�������������򵽺ܶೣ��ҩƷ������Я��һЩҩƷ�ǻ�����ʶ��"}, 
					{ID = 129026 , content = "\t���Ƿ������ˣ������������򵽸�ʽ���ߣ�����Ҫ��ʱ����ʱ�����ҡ�"}, 
					{ID = 129027 , content = "\t�����������ˣ������������򵽸�ʽ����������Ҫ��ʱ����ʱ�����ҡ�"}, 
					{ID = 129029 , content = "\t������˫����Ա������20����ÿ�ܶ���������ȡ5Сʱ��˫������ʱ�䡣"}, 
				  }

x310307_g_NPCLevel_Tab             = {
					{minlevel = 20 ,maxlevel = 30, 
						npcGUID = {
							129017,
							129018, 
							129019, 
							129020, 
							129021,
							},
					},
					{minlevel = 30 ,maxlevel = 160, 
						npcGUID = {
							129024,
							129025, 
							129026, 
							129027, 
							129029,
							129017,
							129018, 
							129019, 
							129020, 
							129021							},
					},

				  }


x310307_g_FinishOne             = "������ɰݷ�@npc_%s������%d/5��"
-- �ݷ�����
x310307_g_TargetCount           = 5

-- ����Ŀ��
x310307_g_MissionTarget			=	"  �ݷ�@npc_%d(%d/1)"

-- ��������
x310307_g_MissionInfo           = "\t�ҵ�@npc_%d��@npc_%d��@npc_%d��@npc_%d��@npc_%d�����õ�������ջ�"

-- ������ʾ
x310307_g_MissionHelp           = "#G�ҵ�ָ��NPC�󣬿��Իش����ǵ����⣬��Ի�õ�����ľ��飡"

-- ������Ҫ��Ǯ
x310307_g_MissionMoney = 5000

function x310307_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	if GetGameOpenById(x310307_g_GameId)<=0 then
		return
	end
	--local level = GetLevel(sceneId, selfId)
	--if level < x310307_g_LevelLessMaster then
		--return
	--end

	local level = GetLevel(sceneId, selfId)
	if level < x310307_g_LevelLessPrentice then
		return
	end

	local npcGuid = GetMonsterGUID( sceneId, targetId)
	if npcGuid == x310307_g_MissionReplyGuid then
		if IsHaveQuestNM( sceneId, selfId, x310307_g_MissionId) == 1 then
			local state = GetQuestStateNM( sceneId, selfId, targetId, x310307_g_MissionId)
			AddQuestNumText( sceneId, x310307_g_MissionId, x310307_g_MissionName, state)
		else
			AddQuestNumText( sceneId, x310307_g_MissionId, x310307_g_MissionName, 8)
		end
	end
end

function x310307_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )
	if GetGameOpenById(x310307_g_GameId)<=0 then
		return
	end

	if MissionId ~= x310307_g_MissionId then
		return
	end

	local npcGuid = GetMonsterGUID( sceneId, targetId)
	if npcGuid == x310307_g_MissionReplyGuid then
		-- ������NPC
		local nMOPFlag = x310307_CheckIsMasterOrPrentice(sceneId, selfId)
		if nMOPFlag == 1 then -- ͽ�ܵ��
			if IsHaveQuestNM( sceneId, selfId, x310307_g_MissionId) == 1 then
				local misIndex = GetQuestIndexByID( sceneId, selfId, x310307_g_MissionId)
				local isFinish = GetQuestParam( sceneId, selfId, misIndex, 7)
				BeginQuestEvent(sceneId)
				AddQuestText( sceneId, "#Y"..x310307_g_MissionName)
				if isFinish == 0 then
					-- ����δ���
					AddQuestText( sceneId, "\t����������鶼�����ˣ�")
					EndQuestEvent( sceneId)
					DispatchQuestEventList( sceneId, selfId, targetId)
				else
					x310307_DispatchCompletedInfo(sceneId, selfId, targetId, index)
					--AddQuestText(sceneId,"\t��ϲ���������ʦͽ����")
					----AddQuestText(sceneId,"\t�������ʦ�����������������ʦ�������ύ����")
					--local exp = x310307_CalculateExp(sceneId, selfId)
					--local szAwardForPrentice = "\n \n \n#Yͽ�ܽ������ݣ�\n#W����ֵ:"..exp.."��"
					--AddQuestText(sceneId, szAwardForPrentice)
					--local szAwardForMaster = "\n#Yʦ���������ݣ�\n#W����ֵ:"..x310307_g_GoodBadValue.."��"
					--AddQuestText(sceneId, szAwardForMaster)
					--EndQuestEvent()
					----DispatchQuestEventList( sceneId, selfId, targetId)
					--DispatchQuestInfoNM( sceneId, selfId, targetId, x310307_g_ScriptId, x310307_g_MissionId)
				end
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y��ʦͽ��������ʿ")
				local str = "\t���������У����¼�������ʿ�������в��پͳ�û�ڸ������С���ͨҪ����ʱ��ȥ�ݷ����ǣ���ͽ�ܵĳɳ��кܴ�İ�����\n\t���Ƿ�Ը�⻨��#G5������#W����ͽ��ǰȥ�ݷü�λ���ˣ���������������"
				AddQuestText(sceneId,str)
				AddQuestText(sceneId,"\n#Y����Ŀ�꣺")
				local target = "#W�ݷ�5λ�������ˡ�"
				AddQuestText(sceneId,target)
				AddQuestText(sceneId,"\n#GС��ʾ��\n1.����������ʦ�����������ύ��\n2.��ͽ�ܵȼ����ڵȼ����а����һ��10�����ϣ�ͽ�ܻ�ø߶�齱��������ͽ�ܻ����ͨ���齱����ʦ���������䡣#W")
				AddQuestText(sceneId,"\n#Y��������")
				local exp, expRate = x310307_CalculateExp(sceneId, selfId)
				AddQuestText(sceneId,format("#Wͽ�ܻ�þ��飺ͽ�ܵȼ�*%s��", expRate))
				AddQuestText(sceneId,format("#Wʦ�����������%s��", x310307_g_GoodBadValue))
				EndQuestEvent()

				DispatchQuestInfo(sceneId, selfId, targetId, x310307_g_MissionId, -1)
			end
			return

		elseif nMOPFlag == 2 then -- ʦ����� 
			local nPrenticeId = x310307_GetPrenticeObjId(sceneId, selfId)
			if IsHaveQuestNM( sceneId, nPrenticeId, x310307_g_MissionId) == 0 then
				-- û������
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y��ʦͽ��������ʿ")
				local str = "\t���������У����¼�������ʿ�������в��پͳ�û�ڸ������С���ͨҪ����ʱ��ȥ�ݷ����ǣ���ͽ�ܵĳɳ��кܴ�İ�����\n\t���Ƿ�Ը�⻨��#G5������#W����ͽ��ǰȥ�ݷü�λ���ˣ���������������"
				AddQuestText(sceneId,str)
				AddQuestText(sceneId,"\n#Y����Ŀ�꣺")
				local target = "#W�ݷ�5λ�������ˡ�"
				AddQuestText(sceneId,target)
				AddQuestText(sceneId,"\n#GС��ʾ��\n1.����������ʦ�����������ύ��\n2.��ͽ�ܵȼ����ڵȼ����а����һ��10�����ϣ�ͽ�ܻ�ø߶�齱��������ͽ�ܻ����ͨ���齱����ʦ���������䡣#W")
				AddQuestText(sceneId,"\n#Y��������")
				local exp,expRate = x310307_CalculateExp(sceneId, nPrenticeId)
				AddQuestText(sceneId,format("#Wͽ�ܻ�þ��飺ͽ�ܵȼ�*%s��", expRate))
				AddQuestText(sceneId,format("#Wʦ�����������%s��", x310307_g_GoodBadValue))
				EndQuestEvent()

				DispatchQuestInfo(sceneId, selfId, targetId, x310307_g_MissionId, -1)

			else
				-- �Ѿ����ܹ�����
				local misIndex = GetQuestIndexByID( sceneId, nPrenticeId, x310307_g_MissionId)
				local isFinish = GetQuestParam( sceneId, nPrenticeId, misIndex, 7)
				BeginQuestEvent(sceneId)
				AddQuestText( sceneId, "#Y"..x310307_g_MissionName)
				if isFinish == 0 then
					-- ����δ���
					AddQuestText( sceneId, "\t����������鶼�����ˣ�")
					EndQuestEvent( sceneId)
					DispatchQuestEventList( sceneId, selfId, targetId)
				else
					AddQuestText(sceneId,"\t����λͽ�ܽ����Ѿ���ȡ��ʦͽ�����ˣ��������ύ������")
					local exp = x310307_CalculateExp(sceneId, nPrenticeId)
					local szAwardForPrentice = "\n \n \n#Yͽ�ܽ������ݣ�\n#W����ֵ:"..exp.."��"
					AddQuestText(sceneId, szAwardForPrentice)
					local szAwardForMaster = "\n#Yʦ���������ݣ�\n#W����ֵ:"..x310307_g_GoodBadValue.."��"
					AddQuestText(sceneId, szAwardForMaster)
					EndQuestEvent()
					--DispatchQuestEventList( sceneId, selfId, targetId)
					DispatchQuestInfoNM( sceneId, selfId, targetId, x310307_g_ScriptId, x310307_g_MissionId)
				end
			end
			return
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y��ʦͽ��������ʿ")
			local str = "\t���������У����¼�������ʿ�������в��پͳ�û�ڸ������С���ͨҪ����ʱ��ȥ�ݷ����ǣ���ͽ�ܵĳɳ��кܴ�İ�����\n\t���Ƿ�Ը�⻨��#G5������#W����ͽ��ǰȥ�ݷü�λ���ˣ���������������"
			AddQuestText(sceneId,str)
			AddQuestText(sceneId,"\n#Y����Ŀ�꣺")
			local target = "#W�ݷ�5λ�������ˡ�"
			AddQuestText(sceneId,target)
			AddQuestText(sceneId,"\n#GС��ʾ��\n1.����������ʦ�����������ύ��\n2.��ͽ�ܵȼ����ڵȼ����а����һ��10�����ϣ�ͽ�ܻ�ø߶�齱��������ͽ�ܻ����ͨ���齱����ʦ���������䡣#W")
				AddQuestText(sceneId,"\n#Y��������")
			local exp,expRate = x310307_CalculateExp(sceneId, selfId)
			AddQuestText(sceneId,format("#Wͽ�ܻ�þ��飺ͽ�ܵȼ�*%s��", expRate))
			AddQuestText(sceneId,format("#Wʦ�����������%s��", x310307_g_GoodBadValue))
			EndQuestEvent()

			DispatchQuestInfo(sceneId, selfId, targetId, x310307_g_MissionId, -1)
			return
		end
	else
	-- ������NPC
		if IsHaveQuestNM( sceneId, selfId, x310307_g_MissionId) == 1 then	--ֻ��ͽ���и��������Դ˴�selfIdΪͽ�ܵ�ID
			if  index >= 11001 and index <= 11004 then
				-- �ش�NPC������
				if x310307_CanAnswerQuestion(sceneId, selfId, targetId)  == 1  then
					x310307_NPCQuestion(sceneId, selfId, targetId, index)
				end
			else
				-- ��ɰݷø�NPC������
				x310307_FindNPC(sceneId, selfId, targetId)
			end
		end
	end
end

function x310307_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if GetGameOpenById(x310307_g_GameId)<=0 then
		return
	end
	
	if MissionId ~= x310307_g_MissionId then
		return
	end

	local npcGuid = GetMonsterGUID( sceneId, targetId)
	if npcGuid == x310307_g_MissionReplyGuid then
		-- ������NPC
		local nMOPFlag = x310307_CheckIsMasterOrPrentice(sceneId, selfId)
		local strMOP = nil
		if nMOPFlag == -1 then
			strMOP = "��ʦͽ�����������ȡ����"
		elseif nMOPFlag == 0 then
			strMOP = "�������û��ʦͽ��ϵ�����̫Զ���޷���ȡ����"
		end

		if strMOP ~= nil then
			Msg2Player(sceneId,selfId,strMOP,8,2)
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, strMOP);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId)
			return
		end


		if nMOPFlag == 1 then	--ͽ�ܵ��ȷ��
			local nMasterId = x310307_GetMasterObjId(sceneId, selfId)
			if IsHaveQuestNM( sceneId, selfId, x310307_g_MissionId) > 0 then -- ������
				x310307_DoSubmit( sceneId, nMasterId, selfId, 2)
			else
				Msg2Player(sceneId,selfId,"�������ʦ������ȡ����",8,2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "�������ʦ������ȡ����");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId)
			end
		elseif nMOPFlag == 2 then	--ʦ�����ȷ��
			local nPrenticeId = x310307_GetPrenticeObjId(sceneId, selfId)
			if IsHaveQuestNM( sceneId, nPrenticeId, x310307_g_MissionId) > 0 then -- ������
				Msg2Player(sceneId,selfId,"����λͽ�ܽ����Ѿ���ȡ��ʦͽ�����ˣ��������ύ������",8,2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "����λͽ�ܽ����Ѿ���ȡ��ʦͽ�����ˣ��������ύ������");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId)
			else
				local str = x310307_DoAccept( sceneId, selfId ,nPrenticeId)
				if str ~= nil then
					Msg2Player(sceneId,selfId,str,8,2)
					BeginQuestEvent(sceneId);
					AddQuestText(sceneId, str);
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
				return
				end

				local szMasterName = GetName(sceneId, selfId)
				local szMsg = format("���ʦ��%s�Ѿ�Ϊ����ȡ��ʦͽ������Ŭ����ɣ���Ҫ������ʦ����������", szMasterName)
		
				Msg2Player(sceneId, nPrenticeId, szMsg, 8, 2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, szMsg);
				EndQuestEvent();
				DispatchQuestTips(sceneId, nPrenticeId);
			end

		end
	else
		--������NPC,�ش�NPC������
		if IsHaveQuestNM( sceneId, selfId, x310307_g_MissionId) == 1 then	--ֻ��ͽ���и��������Դ˴�selfIdΪͽ�ܵ�ID
			x310307_ShowQuestion(sceneId, selfId, targetId)

		end
	end	
end

function x310307_DoAccept( sceneId, MasterId, PrenticeId )

	if IsQuestFullNM(sceneId, PrenticeId) == 1 then
		return "�ܱ�Ǹ����ͽ�ܵ������Ѿ����ˣ��޷���ȡ������"
	end
	
	if x310307_GetMissionTimes(sceneId, PrenticeId) >= x310307_g_LimitTimes then
		return format("�ܱ�Ǹ�������ͽ�ܱ��յ��Ѿ���ȡ��%s�α������������ٴ�������", x310307_g_LimitTimes)
	end

	if IsEnoughMoney(sceneId, MasterId,x310307_g_MissionMoney) == 0 then
		return "�ܱ�Ǹ����û���㹻�����ң��޷�Ϊͽ�ܷ���ȡ������"
	end

	if SpendMoney(sceneId, MasterId, x310307_g_MissionMoney) ~= 1 then
		return "�۷�ʧ�ܣ��޷�Ϊͽ�ܷ���ȡ������"
	end

	local errorCode = AddQuest( sceneId, PrenticeId, x310307_g_MissionId, x310307_g_ScriptId, 0, 0, 0, 1)
	if errorCode ~= 1 then
		return "�������ʧ�ܣ�"
	end
	
	BeginQuestEvent( sceneId)
        -- ��������
        AddQuestText( sceneId, "#Y"..x310307_g_MissionName)

        -- ���ݼ���ѡ��5��NPC
	local nindex = 0
	local indexs = {}
	local Prenticelevel = GetLevel(sceneId, PrenticeId)
        for i, item in x310307_g_NPCLevel_Tab do
		if Prenticelevel >= item.minlevel and Prenticelevel < item.maxlevel then
			nindex = i
			indexs[1] = random( 1, getn( item.npcGUID) )
			local rndm = random( 1, getn( item.npcGUID) )
			while rndm == indexs[1] do
				rndm = random( 1, getn( item.npcGUID) )
			end
			indexs[2] = rndm
			rndm = random( 1, getn( item.npcGUID) )
			while rndm == indexs[1] or rndm == indexs[2] do
				rndm = random( 1, getn( item.npcGUID) )
			end
			indexs[3] = rndm
			rndm = random( 1, getn( item.npcGUID) )
			while rndm == indexs[1] or rndm == indexs[2] or rndm == indexs[3] do
				rndm = random( 1, getn( item.npcGUID) )
			end
			indexs[4] = rndm
			rndm = random( 1, getn( item.npcGUID) )
			while rndm == indexs[1] or rndm == indexs[2] or rndm == indexs[3] or rndm == indexs[4] do
				rndm = random( 1, getn( item.npcGUID) )
			end
			indexs[5] = rndm
		end
	end
				local str = "\t���������У����¼�������ʿ�������в��پͳ�û�ڸ������С���ͨҪ����ʱ��ȥ�ݷ����ǣ�����ĳɳ��кܴ�İ�����"
				AddQuestText(sceneId,str)
        AddQuestText( sceneId, "\n#Y����Ŀ�꣺" )
        -- ��ʽ������������Ϣ
	local npcGUIDs =  x310307_g_NPCLevel_Tab[nindex].npcGUID
        AddQuestText( sceneId, format( "�ݷ�@npc_%s,@npc_%s,@npc_%s,@npc_%s,@npc_%s", x310307_g_NPCLevel_Tab[nindex].npcGUID[indexs[1]], x310307_g_NPCLevel_Tab[nindex].npcGUID[indexs[2]], x310307_g_NPCLevel_Tab[nindex].npcGUID[indexs[3]],x310307_g_NPCLevel_Tab[nindex].npcGUID[indexs[4]],x310307_g_NPCLevel_Tab[nindex].npcGUID[indexs[5]] ) )
        AddQuestText( sceneId, " " )

        -- ����ظ�
        AddQuestText( sceneId, "#Y����ظ���" )
        AddQuestText( sceneId, x310307_g_MissionReply)
        AddQuestText( sceneId, " " )

        AddQuestText( sceneId, "#YС��ʾ��" )
        AddQuestText( sceneId, x310307_g_MissionHelp)
        AddQuestText( sceneId, " " )

        --AddQuestText( sceneId, "#Y�������ݣ�" )
	local exp = x310307_CalculateExp(sceneId, PrenticeId)
	local szAward = "\n#Y�������ݣ�\n#W����ֵ:"..exp.."��"
	AddQuestText( sceneId, szAward )
        AddQuestText( sceneId, " " )

	EndQuestEvent( sceneId)
	DispatchQuestEventList( sceneId, PrenticeId, MasterId)


	-- ����ݷõ�Ŀ��
	local misIndex = GetQuestIndexByID( sceneId, PrenticeId, x310307_g_MissionId)

	SetQuestByIndex( sceneId, PrenticeId, misIndex, 0, 0)
	SetQuestByIndex( sceneId, PrenticeId, misIndex, 1, x310307_g_NPCLevel_Tab[ nindex].npcGUID[indexs[1]] )
	SetQuestByIndex( sceneId, PrenticeId, misIndex, 2, x310307_g_NPCLevel_Tab[ nindex].npcGUID[indexs[2]] )
	SetQuestByIndex( sceneId, PrenticeId, misIndex, 3, x310307_g_NPCLevel_Tab[ nindex].npcGUID[indexs[3]] )
	SetQuestByIndex( sceneId, PrenticeId, misIndex, 4, x310307_g_NPCLevel_Tab[ nindex].npcGUID[indexs[4]] )
	SetQuestByIndex( sceneId, PrenticeId, misIndex, 5, x310307_g_NPCLevel_Tab[ nindex].npcGUID[indexs[5]] )
	SetQuestByIndex( sceneId, PrenticeId, misIndex, 6, 0)
	SetQuestByIndex( sceneId, PrenticeId, misIndex, 7, 0)
	-- ��ʾ���������Ϣ
	Msg2Player( sceneId, MasterId, format("���Ѿ��ɹ��İ���ͽ����ȡ������%s,��ȥ���ң�%d��", x310307_g_MissionName, x310307_g_MissionMoney / 1000), 8, 2)
	Msg2Player( sceneId, MasterId, format("���Ѿ��ɹ��İ���ͽ����ȡ������%s,��ȥ���ң�%d��", x310307_g_MissionName, x310307_g_MissionMoney / 1000), 8, 3)

	if GetQuestData(sceneId, PrenticeId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3]) ~= GetDayOfYear() then
		SetQuestData(sceneId, PrenticeId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3], GetDayOfYear())
		SetQuestData(sceneId, PrenticeId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3], 1)
	else
		local times = GetQuestData(sceneId, PrenticeId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3])
		times = times + 1
		SetQuestData(sceneId, PrenticeId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3], times)
	end

	GamePlayScriptLog(sceneId, PrenticeId, 1471)
	return nil
end

function x310307_CalculateExp(sceneId, selfId)
	local level = GetLevel(sceneId, selfId)
	local minlevel = GetTopListInfo_MinLevel(GetWorldID(sceneId, selfId))
	local exp = 0
	local ExpRate = 0
	if (minlevel - level) <= 10 then
		exp = level * x310307_g_ExpRate_Low
		ExpRate = x310307_g_ExpRate_Low
	else
		exp = level * x310307_g_ExpRate
		ExpRate = x310307_g_ExpRate
	end

	return exp,ExpRate
end

function x310307_DoSubmit( sceneId, MasterId , PrenticeId , Param)
	if Param == 2 then
	        -- ɾ������
                if DelItem( sceneId, PrenticeId, x310307_g_ItemID, 1) == 0 then
                    Msg2Player( sceneId, PrenticeId, format( "û�е���@item_%d#cffcc00���ύ����ʧ��", x310307_g_ItemID), 8, 3)
                    return
                end

	end

	if GetQuestData(sceneId, PrenticeId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3]) ~= GetDayOfYear() then
		SetQuestData(sceneId, PrenticeId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3], GetDayOfYear())
		SetQuestData(sceneId, PrenticeId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3], 1)
	end
	
	
	
	local bret = DelQuest( sceneId, PrenticeId, x310307_g_MissionId )
	if bret == 0 then
		return
	end
	
	--ʦ������
	local value = GetPlayerGoodBadValue(sceneId, MasterId)
	value = value + x310307_g_GoodBadValue* Param
	SetPlayerGoodBadValue(sceneId, MasterId, value)
	local str = format("���ͽ�������ʦͽ��������%d��������", x310307_g_GoodBadValue * Param)
	Msg2Player(sceneId,MasterId,str,8,2)
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, MasterId);
	--ͽ�ܽ���
	local exp = x310307_CalculateExp(sceneId, PrenticeId)
	AddExp(sceneId, PrenticeId, exp* Param);
	str = format("�������ʦͽ���񣬻��%d�㾭��Ľ�����", exp * Param)
	Msg2Player(sceneId,PrenticeId,str,8,2)
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, PrenticeId);
	GamePlayScriptLog(sceneId, PrenticeId, 1472)
end

function x310307_ProcQuestAttach( sceneId, selfId, targetId, npcGuid, misIndex, MissionId )
    if GetGameOpenById(x310307_g_GameId)<=0 then
	return
    end
    local level = GetLevel(sceneId, selfId)
	
    if level < x310307_g_LevelLessPrentice then
	return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x310307_g_MissionId)
    local npc1 = GetQuestParam( sceneId, selfId, misIndex, 1)
    if npc1 > x310307_g_HasTalkedValue then
		if npc1 > x310307_g_HasAnsweredValue then
			npc1 = npc1 / x310307_g_HasAnsweredCoff / x310307_g_HasTalkedCoff
		else
			npc1 = npc1 / x310307_g_HasTalkedCoff
		end
    end
    local npc2 = GetQuestParam( sceneId, selfId, misIndex, 2)
    if npc2 > x310307_g_HasTalkedValue then
		if npc2 > x310307_g_HasAnsweredValue then
			npc2 = npc2 / x310307_g_HasAnsweredCoff / x310307_g_HasTalkedCoff
		else
			npc2 = npc2 / x310307_g_HasTalkedCoff
		end
    end
    local npc3 = GetQuestParam( sceneId, selfId, misIndex, 3)
    if npc3 > x310307_g_HasTalkedValue then
		if npc3 > x310307_g_HasAnsweredValue then
			npc3 = npc3 / x310307_g_HasAnsweredCoff / x310307_g_HasTalkedCoff
		else
			npc3 = npc3 / x310307_g_HasTalkedCoff
		end
    end
    local npc4 = GetQuestParam( sceneId, selfId, misIndex, 4)
    if npc4 > x310307_g_HasTalkedValue then
		if npc4 > x310307_g_HasAnsweredValue then
			npc4 = npc4 / x310307_g_HasAnsweredCoff / x310307_g_HasTalkedCoff
		else
			npc4 = npc4 / x310307_g_HasTalkedCoff
		end
    end
    local npc5 = GetQuestParam( sceneId, selfId, misIndex, 5)
    if npc5 > x310307_g_HasTalkedValue then
		if npc5 > x310307_g_HasAnsweredValue then
			npc5 = npc5 / x310307_g_HasAnsweredCoff / x310307_g_HasTalkedCoff
		else
			npc5 = npc5 / x310307_g_HasTalkedCoff
		end
    end
    if npcGuid == npc1 then
        local isFinish = GetQuestParam( sceneId, selfId, misIndex, 1)
        if isFinish < x310307_g_HasTalkedValue then
            AddQuestNumText( sceneId, x310307_g_MissionId, x310307_g_MissionName, 6)
        end
        return
    end
    if npcGuid == npc2 then
        local isFinish = GetQuestParam( sceneId, selfId, misIndex, 2)
        if isFinish < x310307_g_HasTalkedValue then
            AddQuestNumText( sceneId, x310307_g_MissionId, x310307_g_MissionName, 6)
        end
        return
    end
    if npcGuid == npc3 then
        local isFinish = GetQuestParam( sceneId, selfId, misIndex, 3)
        if isFinish < x310307_g_HasTalkedValue then
            AddQuestNumText( sceneId, x310307_g_MissionId, x310307_g_MissionName, 6)
        end
        return
    end
    if npcGuid == npc4 then
        local isFinish = GetQuestParam( sceneId, selfId, misIndex, 4)
        if isFinish < x310307_g_HasTalkedValue then
            AddQuestNumText( sceneId, x310307_g_MissionId, x310307_g_MissionName, 6)
        end
        return
    end
    if npcGuid == npc5 then
        local isFinish = GetQuestParam( sceneId, selfId, misIndex, 5)
        if isFinish < x310307_g_HasTalkedValue then
            AddQuestNumText( sceneId, x310307_g_MissionId, x310307_g_MissionName, 6)
        end
        return
    end
end

function x310307_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    if GetGameOpenById(x310307_g_GameId)<=0 then
	return
    end
    local misIndex = GetQuestIndexByID( sceneId, selfId, x310307_g_MissionId)
    local mFinished = GetQuestParam( sceneId, selfId, misIndex, 7)
    local F1 = GetQuestParam( sceneId, selfId, misIndex, 1)
    if F1 > x310307_g_HasTalkedValue then
        F1 = 1
    else
        F1 = 0
    end
    local F2 = GetQuestParam( sceneId, selfId, misIndex, 2)
    if F2 > x310307_g_HasTalkedValue then
        F2 = 1
    else
        F2 = 0
    end
    local F3 = GetQuestParam( sceneId, selfId, misIndex, 3)
    if F3 > x310307_g_HasTalkedValue then
        F3 = 1
    else
        F3 = 0
    end
    local F4 = GetQuestParam( sceneId, selfId, misIndex, 4)
    if F4 > x310307_g_HasTalkedValue then
        F4 = 1
    else
        F4 = 0
    end
    local F5 = GetQuestParam( sceneId, selfId, misIndex, 5)
    if F5 > x310307_g_HasTalkedValue then
        F5 = 1
    else
        F5 = 0
    end
    --local PrenticeObjId = x310307_GetPrenticeObjId(sceneId, selfId)

	
    local npc1, npc2, npc3, npc4, npc5 = x310307_GetNPCID( sceneId, selfId)
    local strMissionInfo = ""

    if mFinished == 0 then
    		if F1 > 0 then
    			strMissionInfo = strMissionInfo.."#G";
    		else
    			strMissionInfo = strMissionInfo.."#W";
    		end
    		strMissionInfo = strMissionInfo..format(x310307_g_MissionTarget, npc1, F1);
    		strMissionInfo = strMissionInfo.."\n"
    		
    		if F2 > 0 then
    			strMissionInfo = strMissionInfo.."#G";
    		else
    			strMissionInfo = strMissionInfo.."#W";
    		end
    		strMissionInfo = strMissionInfo..format(x310307_g_MissionTarget, npc2, F2);
    		strMissionInfo = strMissionInfo.."\n"
    		
    		if F3 > 0 then
    			strMissionInfo = strMissionInfo.."#G";
    		else
    			strMissionInfo = strMissionInfo.."#W";
    		end
    		strMissionInfo = strMissionInfo..format(x310307_g_MissionTarget, npc3, F3);
		strMissionInfo = strMissionInfo.."\n"

		if F4 > 0 then
    			strMissionInfo = strMissionInfo.."#G";
    		else
    			strMissionInfo = strMissionInfo.."#W";
    		end
    		strMissionInfo = strMissionInfo..format(x310307_g_MissionTarget, npc4, F4);
		strMissionInfo = strMissionInfo.."\n"

		if F5 > 0 then
    			strMissionInfo = strMissionInfo.."#G";
    		else
    			strMissionInfo = strMissionInfo.."#W";
    		end
    		strMissionInfo = strMissionInfo..format(x310307_g_MissionTarget, npc5, F5);
		strMissionInfo = strMissionInfo.."\n"
    else
        strMissionInfo = "�����Ѿ���ɣ����ȥ��"..x310307_g_MissionReply.."�㱨��"
    end

    BeginQuestEvent( sceneId)
        AddQuestLogCustomText( sceneId,
                               "ʦͽ����",                             -- ����
                               x310307_g_MissionName,          -- ��������
                               strMissionInfo,     -- ����Ŀ��
                               x310307_g_MissionReply,         -- ����NPC
                               "�ҵ����صĸ���",	--������
                               format( x310307_g_MissionInfo, npc1, npc2, npc3, npc4, npc5),   -- ��������
                               x310307_g_MissionHelp)          -- ������ʾ


    local exp = x310307_CalculateExp(sceneId, selfId)
            
    AddQuestExpBonus( sceneId, exp)
    EndQuestEvent()
    DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

function x310307_ProcQuestAbandon(sceneId, selfId, MissionId)
	DelQuest( sceneId, selfId, x310307_g_MissionId )
	
	local message = "��������ʦͽ����"
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 4, 2);
	
	if GetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3]) ~= GetDayOfYear() then
		SetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3], GetDayOfYear())
		SetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3], 1)
	end
end

-- ���������NPC��Id
function x310307_GetNPCID(sceneId, selfId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x310307_g_MissionId)
    local F1 = GetQuestParam( sceneId, selfId, misIndex, 1)
    local F2 = GetQuestParam( sceneId, selfId, misIndex, 2)
    local F3 = GetQuestParam( sceneId, selfId, misIndex, 3)
    local F4 = GetQuestParam( sceneId, selfId, misIndex, 4)
    local F5 = GetQuestParam( sceneId, selfId, misIndex, 5)

    local npc1 = F1
    local npc2 = F2
    local npc3 = F3
    local npc4 = F4
    local npc5 = F5

    if npc1 > x310307_g_HasTalkedValue then
		if npc1 > x310307_g_HasAnsweredValue then
			npc1 = npc1 / x310307_g_HasAnsweredCoff / x310307_g_HasTalkedCoff
		else
			npc1 = npc1 / x310307_g_HasTalkedCoff
		end
    end
    if npc2 > x310307_g_HasTalkedValue then
		if npc2 > x310307_g_HasAnsweredValue then
			npc2 = npc2 / x310307_g_HasAnsweredCoff / x310307_g_HasTalkedCoff
		else
			npc2 = npc2 / x310307_g_HasTalkedCoff
		end
    end
    if npc3 > x310307_g_HasTalkedValue then
		if npc3 > x310307_g_HasAnsweredValue then
			npc3 = npc3 / x310307_g_HasAnsweredCoff / x310307_g_HasTalkedCoff
		else
			npc3 = npc3 / x310307_g_HasTalkedCoff
		end
    end
    if npc4 > x310307_g_HasTalkedValue then
		if npc4 > x310307_g_HasAnsweredValue then
			npc4 = npc4 / x310307_g_HasAnsweredCoff / x310307_g_HasTalkedCoff
		else
			npc4 = npc4 / x310307_g_HasTalkedCoff
		end
    end
    if npc5 > x310307_g_HasTalkedValue then
		if npc5 > x310307_g_HasAnsweredValue then
			npc5 = npc5 / x310307_g_HasAnsweredCoff / x310307_g_HasTalkedCoff
		else
			npc5 = npc5 / x310307_g_HasTalkedCoff
		end
    end
    return npc1, npc2, npc3, npc4, npc5
end

function x310307_GetNPCTalk(targetId)
	for i, item in x310307_g_strNPCTalk do
		if item.ID == targetId then
			return item.content
		end
	end
end

function x310307_GetMissionTimes(sceneId, selfId)
	if GetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3]) ~= GetDayOfYear() then
		return 0
	else
		return GetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3])
	end
end

function x310307_CheckIsMasterOrPrentice( sceneId, selfId)	--����ͽ�ܻ���ʦ���ı�־  -1 ����������� 0 û�й�ϵ 1 ��ͽ�� 2 ��ʦ��	
	local teamSize = GetTeamSize(sceneId, selfId)
	if (teamSize ~= 2) then
		return -1
	end
	
	local MasterOrPrenticeFlag = 0 
	for i = 0, teamSize - 1 do
		local targetId = GetTeamMemberId(sceneId, selfId, i)
		if targetId ~= selfId then
			if IsInDist(sceneId, selfId, targetId, x310307_g_MasterDistance) == 1then
				if GetObjType(sceneId, targetId) == 1 then
					if IsPrentice(sceneId, selfId, targetId) == 1 then
						MasterOrPrenticeFlag = 2
					elseif IsMaster(sceneId, selfId, targetId) == 1 then
						MasterOrPrenticeFlag = 1
					end
				end
			end
		end
	end

	return MasterOrPrenticeFlag
end

function x310307_ShowQuestion(sceneId, selfId, targetId)
	local npcGuid = GetMonsterGUID( sceneId, targetId)
	--�õ�����
	local id,strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer = QuestShitu_GetQuestionInfo(npcGuid)

	if id ~= npcGuid then
		return
	end

	--���¶Ի�������
	BeginQuestEvent(sceneId)
		
		AddQuestText(sceneId,"#Y��ʦͽ��������ʿ#W\n")
		
		AddQuestText(sceneId,strDesc)
		x310307_AddDengmiAnswerOption( sceneId, 
							strAnswer1, 
							strAnswer2, 
							strAnswer3, 
							strAnswer4 )
									
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)	
end

----------------------------------------------------------------------------------------------
--���ʦͽ����NPC�����ѡ��
----------------------------------------------------------------------------------------------
function x310307_AddDengmiAnswerOption( sceneId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)

	--������ѡ��
	local arr_answer = { {strAnswer1,11001},{strAnswer2,11002},{strAnswer3,11003},{strAnswer4,11004} }
	for j = 1, 2 do
		local n = random(1, 4)
		local m =  random(1, 4)
		if n ~= m then
			local t = arr_answer[n]
			arr_answer[n] = arr_answer[m]
			arr_answer[m] = t
		end
	end
	
	for i=1,4 do
		AddQuestNumText(sceneId,x310307_g_MissionId,arr_answer[i][1],3,arr_answer[i][2] )
	end
end


function x310307_AnswerRight( sceneId, selfId, targetId )
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"��ϲ�㣬�ش���ȷ��")	
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
		
	local exp = x310307_CalculateExp(sceneId, selfId)/10
	AddExp(sceneId, selfId, exp);
	str = format("��ش�������⣬���%d�㾭��Ľ�����", exp)
	Msg2Player(sceneId,selfId,str,8,2)
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x310307_AnswerError( sceneId, selfId, targetId )
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"���ź�����ش���ˣ����ܻ�ö��⽱����")	
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)

	Msg2Player(sceneId,selfId,"���ź����������ش���ˣ����ܻ�ö��⽱����",8,2)
end

function x310307_GetPrenticeObjId(sceneId, selfId)
	local teamSize = GetTeamSize(sceneId, selfId)
	local nPrenticeObjId = -1
	for i = 0, teamSize - 1 do
		local targetId = GetTeamMemberId(sceneId, selfId, i)
		if 1 == IsInDist(sceneId, selfId, targetId, x310307_g_MasterDistance) then
			if 1 == GetObjType(sceneId, targetId) and 1 == IsPrentice(sceneId, selfId, targetId) then
				nPrenticeObjId = targetId
			end
		end
	end
	
	return nPrenticeObjId
end

function x310307_GetMasterObjId(sceneId, selfId)
	local teamSize = GetTeamSize(sceneId, selfId)
	local nMasterObjId = -1
	for i = 0, teamSize - 1 do
		local targetId = GetTeamMemberId(sceneId, selfId, i)
		if 1 == IsInDist(sceneId, selfId, targetId, x310307_g_MasterDistance) then
			if 1 == GetObjType(sceneId, targetId) and 1 == IsMaster(sceneId, selfId, targetId) then
				nMasterObjId = targetId
			end
		end
	end
	
	return nMasterObjId
end

function x310307_AnswerQuestion(sceneId, selfId, targetId, index)
	if  index >= 11001 and index <= 11004	then
		local npcGuid = GetMonsterGUID( sceneId, targetId)
		--ȡ����Ŀ��Ϣ
		local id,strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer = QuestShitu_GetQuestionInfo(npcGuid)
		if id ~= npcGuid then
			return
		end

		--�����Ƿ���ȷ
		if 11000+nAnswer == index then
			--��ȷ
			x310307_AnswerRight( sceneId, selfId, targetId )
		else
			--����
			x310307_AnswerError( sceneId, selfId, targetId )
		end
		
	end

end

function x310307_NPCQuestion(sceneId, selfId, targetId, index)
	local logFmtMsg         = "x310307_NPCQuestion : sceneId = %d,selfId = %d,targetId = %d,index = %d" 	
	local logMsg = format(logFmtMsg,sceneId,selfId,targetId,index)
	WriteLog(1,logMsg)
	x310307_AnswerQuestion(sceneId, selfId, targetId, index)
end

function x310307_FindNPC(sceneId, selfId, targetId)
	local npcGuid = GetMonsterGUID( sceneId, targetId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x310307_g_MissionId)
	local npc1, npc2, npc3, npc4, npc5 = x310307_GetNPCID(sceneId, selfId)
	local count = GetQuestParam( sceneId, selfId, misIndex, 6)
	BeginQuestEvent(sceneId)

	local npcTalkContent = ""
	AddQuestText( sceneId, "#Y"..x310307_g_MissionName)

	if npcGuid == npc1 and GetQuestParam( sceneId, selfId, misIndex, 1) < x310307_g_HasTalkedValue then
		SetQuestByIndex( sceneId, selfId, misIndex, 1, GetQuestParam( sceneId, selfId, misIndex, 1) * x310307_g_HasTalkedCoff)
		count = count + 1
		npcTalkContent = x310307_GetNPCTalk(npc1)
	end
	if npcGuid == npc2 and GetQuestParam( sceneId, selfId, misIndex, 2) < x310307_g_HasTalkedValue then
		SetQuestByIndex( sceneId, selfId, misIndex, 2, GetQuestParam( sceneId, selfId, misIndex, 2) * x310307_g_HasTalkedCoff)
		count = count + 1
		npcTalkContent = x310307_GetNPCTalk(npc2)
	end
	if npcGuid == npc3 and GetQuestParam( sceneId, selfId, misIndex, 3) < x310307_g_HasTalkedValue then
		SetQuestByIndex( sceneId, selfId, misIndex, 3, GetQuestParam( sceneId, selfId, misIndex, 3) * x310307_g_HasTalkedCoff)
		count = count + 1
		npcTalkContent = x310307_GetNPCTalk(npc3)
	end
	if npcGuid == npc4 and GetQuestParam( sceneId, selfId, misIndex, 4) < x310307_g_HasTalkedValue then
		SetQuestByIndex( sceneId, selfId, misIndex, 4, GetQuestParam( sceneId, selfId, misIndex, 4) * x310307_g_HasTalkedCoff)
		count = count + 1
		npcTalkContent = x310307_GetNPCTalk(npc4)
	end
	if npcGuid == npc5 and GetQuestParam( sceneId, selfId, misIndex, 5) < x310307_g_HasTalkedValue then
		SetQuestByIndex( sceneId, selfId, misIndex, 5, GetQuestParam( sceneId, selfId, misIndex, 5) * x310307_g_HasTalkedCoff)
		count = count + 1
		npcTalkContent = x310307_GetNPCTalk(npc5)
	end
	
	AddQuestText( sceneId, npcTalkContent)
	AddQuestText( sceneId, "\n \n#GС��ʾ#W��\n\t����ȷ���ش�����������⡣��Ի��ж��⾭�齱����" )
	EndQuestEvent( sceneId)
	--DispatchQuestEventList( sceneId, selfId, targetId)
	DispatchQuestInfoNM( sceneId, selfId, targetId, x310307_g_ScriptId, x310307_g_MissionId, 0)

	local strTip = format( x310307_g_FinishOne, npcGuid, count)
	BeginQuestEvent( sceneId)
	AddQuestText( sceneId, strTip)
	EndQuestEvent( sceneId)
	DispatchQuestTips( sceneId, selfId)
	if count >= x310307_g_TargetCount then
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
		Msg2Player( sceneId, selfId, "�����Ѿ���ɣ�����ȥ�㱨�ɣ�", 8, 2)
		Msg2Player( sceneId, selfId, "�����Ѿ���ɣ�����ȥ�㱨�ɣ�", 8, 3)
	end
	-- �����Ѱݷ�����
	SetQuestByIndex( sceneId, selfId, misIndex, 6, count)
	-- �����������
	x310307_ProcQuestLogRefresh( sceneId, selfId, x310307_g_MissionId)

end

function x310307_DispatchCompletedInfo( sceneId, selfId, targetId, index)
	if index == 31 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x310307_g_MissionName)
		AddQuestText(sceneId, "\t���¼�����������ʱ���߷���Щ���˻����ĳɳ����а�����\n\t������ύ����һ��#Gʦ����л#W�������������ʦ��������˫���Ľ�����\n\t��ȷ��Ҫ�ύһ��ʦ����лô��" )
		local exp = x310307_CalculateExp(sceneId, selfId)
		exp = exp * 2
		local szAwardForPrentice = "\n \n \n#Yͽ�ܽ������ݣ�\n#W����ֵ��˫����:"..exp.."��"
		AddQuestText(sceneId, szAwardForPrentice)
		local GoodBadValue = x310307_g_GoodBadValue * 2
		local szAwardForMaster = "\n#Yʦ���������ݣ�\n#W����ֵ��˫����:"..GoodBadValue.."��"
		AddQuestText(sceneId, szAwardForMaster)
		EndQuestEvent()
		DispatchQuestInfoNM( sceneId, selfId, targetId, x310307_g_ScriptId, x310307_g_MissionId)

	elseif index == 32 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x310307_g_MissionName)
		AddQuestText(sceneId, "\t���¼�����������ʱ���߷���Щ���˻����ĳɳ����а�����\n\t������ܽ�����һ��#Gʦ����л#W����������������ʦ��������˫���Ľ�����\n \n#GС��ʾ:\n\t�����ϣ���ύʦ����лʹ�Լ���ʦ���Ľ�����������رմ˽��������ύ������" )
		local exp = x310307_CalculateExp(sceneId, selfId)
		local szAwardForPrentice = "\n \n \n#Yͽ�ܽ������ݣ�\n#W����ֵ:"..exp.."��"
		AddQuestText(sceneId, szAwardForPrentice)
		local szAwardForMaster = "\n#Yʦ���������ݣ�\n#W����ֵ:"..x310307_g_GoodBadValue.."��"
		AddQuestText(sceneId, szAwardForMaster)
		EndQuestEvent()
		DispatchQuestContinueInfoNM( sceneId, selfId, targetId, x310307_g_ScriptId, x310307_g_MissionId)

	else
		BeginQuestEvent(sceneId)
		    AddQuestText(sceneId,"#Y"..x310307_g_MissionName)
		    AddQuestText(sceneId, "\t��ϲ���������ʦͽ����" )
		    AddQuestText(sceneId," ")

		    AddQuestNumText( sceneId, x310307_g_MissionId, "ʹ��ʦ����л�ύ����", 3, 31)
		    AddQuestNumText( sceneId, x310307_g_MissionId, "ֱ���ύ����", 3, 32)
		EndQuestEvent()
		DispatchQuestEventList( sceneId, selfId, targetId)
	end

end

function x310307_ProcQuestSubmit( sceneId, selfId, targetId, selectRadioId, MissionId)

	if GetGameOpenById(x310307_g_GameId)<=0 then
		return
	end
	
	if MissionId ~= x310307_g_MissionId then
		return
	end

	local npcGuid = GetMonsterGUID( sceneId, targetId)
	if npcGuid == x310307_g_MissionReplyGuid then
		-- ������NPC
		local nMOPFlag = x310307_CheckIsMasterOrPrentice(sceneId, selfId)

		if nMOPFlag == 1 then	--ͽ�ܵ��ȷ��
			local nMasterId = x310307_GetMasterObjId(sceneId, selfId)
			if IsHaveQuestNM( sceneId, selfId, x310307_g_MissionId) > 0 then -- ������
				x310307_DoSubmit( sceneId, nMasterId, selfId, 1)
			end
		end
	end
end

function x310307_CanAnswerQuestion(sceneId, selfId, targetId)
	local npcGuid = GetMonsterGUID( sceneId, targetId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x310307_g_MissionId)
	local npc1, npc2, npc3, npc4, npc5 = x310307_GetNPCID(sceneId, selfId)
	local ret = 0

	if npcGuid == npc1 and GetQuestParam( sceneId, selfId, misIndex, 1) > x310307_g_HasTalkedValue and GetQuestParam( sceneId, selfId, misIndex, 1) < x310307_g_HasAnsweredValue then
		SetQuestByIndex( sceneId, selfId, misIndex, 1, GetQuestParam( sceneId, selfId, misIndex, 1) * x310307_g_HasAnsweredCoff)
		ret = 1
	end
	if npcGuid == npc2 and GetQuestParam( sceneId, selfId, misIndex, 2) > x310307_g_HasTalkedValue and GetQuestParam( sceneId, selfId, misIndex, 2) < x310307_g_HasAnsweredValue  then
		SetQuestByIndex( sceneId, selfId, misIndex, 2, GetQuestParam( sceneId, selfId, misIndex, 2) * x310307_g_HasAnsweredCoff)
		ret = 1
	end
	if npcGuid == npc3 and GetQuestParam( sceneId, selfId, misIndex, 3) > x310307_g_HasTalkedValue and GetQuestParam( sceneId, selfId, misIndex, 3) < x310307_g_HasAnsweredValue then
		SetQuestByIndex( sceneId, selfId, misIndex, 3, GetQuestParam( sceneId, selfId, misIndex, 3) * x310307_g_HasAnsweredCoff)
		ret = 1
	end
	if npcGuid == npc4 and GetQuestParam( sceneId, selfId, misIndex, 4) > x310307_g_HasTalkedValue and GetQuestParam( sceneId, selfId, misIndex, 4) < x310307_g_HasAnsweredValue  then
		SetQuestByIndex( sceneId, selfId, misIndex, 4, GetQuestParam( sceneId, selfId, misIndex, 4) * x310307_g_HasAnsweredCoff)
		ret = 1
	end
	if npcGuid == npc5 and GetQuestParam( sceneId, selfId, misIndex, 5) > x310307_g_HasTalkedValue and GetQuestParam( sceneId, selfId, misIndex, 5) < x310307_g_HasAnsweredValue   then
		SetQuestByIndex( sceneId, selfId, misIndex, 5, GetQuestParam( sceneId, selfId, misIndex, 5) * x310307_g_HasAnsweredCoff)
		ret = 1
	end
	
	return ret

end

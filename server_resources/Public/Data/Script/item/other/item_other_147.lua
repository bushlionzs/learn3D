--��֭��������̽����	12030449
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x418147_g_scriptId = 418147
x418147_g_LevelMin = 30	

x418147_g_ItemTable             = {
                                    { itemId = 11020502, probability = 7200, special = 0, broad = 0, itemname = "ˮľ����" }, 
                                    { itemId = 11030405, probability = 7200, special = 0, broad = 0, itemname = "�߲���" }, 
                                    { itemId = 11000201, probability = 7200, special = 0, broad = 0, itemname = "����ˮ��" }, 
                                    { itemId = 11050002, probability = 7200, special = 0, broad = 0, itemname = "�м�����ʯ" }, 
                                    { itemId = 11000202, probability = 6000, special = 0, broad = 0, itemname = "��ˮ��" }, 
                                    { itemId = 11030502, probability = 6000,  special = 0, broad = 0, itemname = "����ʯ" }, 
                                    { itemId = 11050003, probability = 6000,  special = 0, broad = 0, itemname = "�߼�����ʯ" }, 
                                    { itemId = 12031019, probability = 5500,  special = 0, broad = 0, itemname = "ն" }, 
                                    { itemId = 12030201, probability = 5500,  special = 0, broad = 0, itemname = "����ʯ" }, 
                                    { itemId = 12031005, probability = 4000,  special = 0, broad = 0, itemname = "������ӡ" }, 
                                    { itemId = 12031006, probability = 4000,  special = 0, broad = 0, itemname = "һ������" }, 
                                    { itemId = 11990011, probability = 4000,  special = 0, broad = 0, itemname = "������" }, 
                                    { itemId = 12030210, probability = 4000,   special = 0, broad = 0, itemname = "����֮��" }, 
                                    { itemId = 12050009, probability = 4000,   special = 0, broad = 0, itemname = "���ֲ�" }, 
                                    { itemId = 11990012, probability = 3500,   special = 0, broad = 0, itemname = "�巬��" }, 
                                    { itemId = 12010020, probability = 3000,  special = 0, broad = 0, itemname = "С������¶" },
                                    { itemId = 11000800, probability = 3000,  special = 0, broad = 0, itemname = "��ʯ��" }, 
                                    { itemId = 12054300, probability = 3000,  special = 0, broad = 0, itemname = "��ͯ��" }, 
                                    { itemId = 11000501, probability = 3000,  special = 0, broad = 0, itemname = "��̴ľ̿" }, 
                                    { itemId = 11000902, probability = 3000,  special = 0, broad = 0, itemname = "�߼�ϴʯ��" }, 
                                    { itemId = 11000800, probability = 3000,  special = 0, broad = 0, itemname = "��ʯ��" }, 
                                    { itemId = 12030202, probability = 100,  special = 0, broad = 0, itemname = "�������" }, 
                                    { itemId = 12110207, probability = 100,  special = 0, broad = 0, itemname = "����ֹ��" }, 
                                    { itemId = 12030200, probability = 100,  special = 0, broad = 0, itemname = "С����" }, 
                                    { itemId = 11990110, probability = 100,  special = 0, broad = 0, itemname = "ļ��ȯ" }, 
                                    { itemId = 12054301, probability = 90,  special = 0, broad = 0, itemname = "������" }, 
                                    { itemId = 11000502, probability = 64,  special = 0, broad = 0, itemname = "����ˮ��ˮ��" }, 
                                    { itemId = 11000504, probability = 55,  special = 0, broad = 0, itemname = "�����Ų�ˮ��" },
                                    { itemId = 11000500, probability = 54,  special = 0, broad = 0, itemname = "���Ϻ���ˮ��" },
                                    { itemId = 11000503, probability = 33,  special = 0, broad = 0, itemname = "�����ι�ˮ��" },
                                    { itemId = 10310028, probability = 2,  special = 0, broad = 1, itemname = "�����ƣ�������(30��)" }, 
                                    { itemId = 10310029, probability = 2,  special = 0, broad = 1, itemname = "�����ƣ���һɫ(30��)" },
}                                                                               
--x418147_g_ItemSpecial           = {
--                                    { itemId = 10287075, itemname = "���������ָ", leveldown = 30, levelup = 40 }, 
--                                    { itemId = 10287076, itemname = "���������ָ", leveldown = 40, levelup = 60 }, 
--                                    { itemId = 10287073, itemname = "�񴫽����ָ", leveldown = 60, levelup = 80 }, 
--                                    { itemId = 10287074, itemname = "�촫�����ָ", leveldown = 80, levelup = 999 }, 
--                                    { itemId = 10297075, itemname = "������������", leveldown = 30, levelup = 40 }, 
--                                    { itemId = 10297076, itemname = "������������", leveldown = 40, levelup = 60 }, 
--                                    { itemId = 10297073, itemname = "�񴫽�������", leveldown = 60, levelup = 80 }, 
--                                    { itemId = 10297074, itemname = "�촫��������", leveldown = 80, levelup = 999 }, 
--}

--**********************************
--�¼��������
--**********************************
function x418147_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x418147_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x418147_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x418147_OnConditionCheck( sceneId, selfId )
	
	--У��ʹ�õ���Ʒ
	
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end
	return 1; --����Ҫ�κ�����������ʼ�շ���1��
end

--**********************************
--���ļ�⼰������ڣ�
--ϵͳ���ڼ������ĵ�ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1�����Ĵ���ͨ�������Լ���ִ�У�����0�����ļ��ʧ�ܣ��жϺ���ִ�С�
--ע�⣺�ⲻ�⸺�����ĵļ��Ҳ�������ĵ�ִ�С�
--**********************************
function x418147_OnDeplete( sceneId, selfId )
	
	
	--if(DepletingUsedItem(sceneId, selfId)) == 1 then
	--	return 1;
	--end
	--return 0;
	
	return 1;
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x418147_OnActivateOnce( sceneId, selfId, impactId )
    local day = GetDayOfYear()
    local last = GetQuestData( sceneId, selfId, MD_GUOZHI_DAY[ 1], MD_GUOZHI_DAY[ 2], MD_GUOZHI_DAY[ 3] )
    if day == last then
        if GetQuestData( sceneId, selfId, MD_GUOZHI_DAYCOUNT[ 1], MD_GUOZHI_DAYCOUNT[ 2], MD_GUOZHI_DAYCOUNT[ 3] ) >= 3 then
            Msg2Player(sceneId, selfId, "�������ʹ�ô����ѳ������ޣ�",8,3)
            return
        end
    else
        SetQuestData( sceneId, selfId, MD_GUOZHI_DAYCOUNT[ 1], MD_GUOZHI_DAYCOUNT[ 2], MD_GUOZHI_DAYCOUNT[ 3], 0)
    end

    SetQuestData( sceneId, selfId, MD_GUOZHI_DAYCOUNT[ 1], MD_GUOZHI_DAYCOUNT[ 2], MD_GUOZHI_DAYCOUNT[ 3], GetQuestData( sceneId, selfId, MD_GUOZHI_DAYCOUNT[ 1], MD_GUOZHI_DAYCOUNT[ 2], MD_GUOZHI_DAYCOUNT[ 3] ) + 1)
    SetQuestData( sceneId, selfId, MD_GUOZHI_DAY[ 1], MD_GUOZHI_DAY[ 2], MD_GUOZHI_DAY[ 3], day)
    
	local lv = GetLevel(sceneId, selfId)
		local money = 0
  if lv < 50 and lv >= 30 then
  	money = 5000
  elseif lv < 80 and lv >= 50 then
  	money = 10000
  elseif lv < 150 and lv >= 80 then
  	money = 18000
  else
  	return
  end 
	
	if lv < x418147_g_LevelMin then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ȼ����㣬�޷��������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

  if GetBagSpace(sceneId, selfId) < 1 then
      Msg2Player( sceneId, selfId, "�����ռ䲻��һ���޷��򿪹�֭��������̽����", 8, 3)
      return
  end

	local rand = random( 1, 100000)
    local index = 1
    local num1 = 1
    local num2 = 1
    local giveitem = 11020502
    for i, item in x418147_g_ItemTable do
        num1 = num1 + item.probability
        if rand >= num2 and rand < num1 then
            index = i
            break
        end
        num2 = num2 + item.probability
    end
    
			giveitem = x418147_g_ItemTable[ index].itemId

	BeginAddItem(sceneId)
		AddBindItem( sceneId, giveitem, 1)
		AddMoney( sceneId, selfId, 1, money )
  	Msg2Player( sceneId, selfId, format( "������#R#{_MONEY%d}������", money), 8, 2)
  	Msg2Player( sceneId, selfId, format( "������#R#{_MONEY%d}������", money), 8, 3)

	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
			if(DepletingUsedItem(sceneId, selfId)) == 1 then
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"�򿪹�֭��������̽�������������Ʒ")
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					AddItemListToPlayer(sceneId,selfId)
	
	    -- ����㲥
		    if x418147_g_ItemTable[ index].broad == 1 then
		        LuaAllScenceM2Wrold( sceneId, format( "��ϲ���%s�򿪻�Դ���������#{_ITEM%d}", GetName( sceneId, selfId), giveitem), 5, 1)
		    end
	
			else
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"�򿪹�֭��������̽�����쳣��")
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
				end

	else
				BeginQuestEvent( sceneId)
				AddQuestText( sceneId, "�����������޷��õ���Ʒ��" )
				EndQuestEvent( sceneId)
				DispatchQuestTips( sceneId, selfId)
	end

end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x418147_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end

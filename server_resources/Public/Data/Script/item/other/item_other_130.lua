--��������	11010019
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x418130_g_scriptId = 418130
x418130_g_LevelMin = 30	

x418130_g_ItemTable             = {
                                    { itemId = 12054300, probability = 120, special = 0, broad = 0, itemname = "��ͯ��" }, 
                                    { itemId = 11000501, probability = 120, special = 0, broad = 0, itemname = "��̴ľ̼" }, 
                                    { itemId = 11000902, probability = 120, special = 0, broad = 0, itemname = "�߼�ϴʯ��" }, 
                                    { itemId = 12010020, probability = 120, special = 0, broad = 0, itemname = "С������¶" }, 
                                    { itemId = 11000800, probability = 120, special = 0, broad = 0, itemname = "��ʯ��" }, 
                                    { itemId = 12030202, probability = 70,  special = 0, broad = 0, itemname = "�������" }, 
                                    { itemId = 12110207, probability = 70,  special = 0, broad = 0, itemname = "����ֹ��" }, 
                                    { itemId = 12030200, probability = 70,  special = 0, broad = 0, itemname = "С����" }, 
                                    { itemId = 11990110, probability = 70,  special = 0, broad = 0, itemname = "ļ��ȯ" }, 
                                    { itemId = 12054301, probability = 50,  special = 0, broad = 0, itemname = "������" }, 
                                    { itemId = 11990114, probability = 16,  special = 0, broad = 0, itemname = "������ʯ" }, 
                                    { itemId = 11000502, probability = 25,  special = 0, broad = 0, itemname = "����ˮ��ˮ��" }, 
                                    { itemId = 11000504, probability = 7,   special = 0, broad = 0, itemname = "�����Ų�ˮ��" }, 
                                    { itemId = 11000500, probability = 6,   special = 0, broad = 0, itemname = "���Ϻ���ˮ��" }, 
                                    { itemId = 11000503, probability = 5,   special = 0, broad = 0, itemname = "�����ι�ˮ��" }, 
                                    { itemId = 12050249, probability = 10,  special = 0, broad = 1, itemname = "���޽�����" }, 
                                    { itemId = 10287075, probability = 1,   special = 1, broad = 1, itemname = "���������ָ" }, 
}                                                                               
x418130_g_ItemSpecial           = {
                                    { itemId = 10287075, itemname = "���������ָ", leveldown = 30, levelup = 40 }, 
                                    { itemId = 10287076, itemname = "���������ָ", leveldown = 40, levelup = 60 }, 
                                    { itemId = 10287073, itemname = "�񴫽����ָ", leveldown = 60, levelup = 80 }, 
                                    { itemId = 10287074, itemname = "�촫�����ָ", leveldown = 80, levelup = 999 }, 
                                    { itemId = 10297075, itemname = "������������", leveldown = 30, levelup = 40 }, 
                                    { itemId = 10297076, itemname = "������������", leveldown = 40, levelup = 60 }, 
                                    { itemId = 10297073, itemname = "�񴫽�������", leveldown = 60, levelup = 80 }, 
                                    { itemId = 10297074, itemname = "�촫��������", leveldown = 80, levelup = 999 }, 
}

--**********************************
--�¼��������
--**********************************
function x418130_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x418130_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x418130_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x418130_OnConditionCheck( sceneId, selfId )
	
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
function x418130_OnDeplete( sceneId, selfId )
	
	
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
function x418130_OnActivateOnce( sceneId, selfId, impactId )

	local lv = GetLevel(sceneId, selfId)
	if lv < x418130_g_LevelMin then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ȼ�����")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

    if GetBagSpace(sceneId, selfId) < 1 then
        Msg2Player( sceneId, selfId, "�����ռ䲻��һ���޷��򿪽�������", 8, 3)
        return
    end

	local rand = random( 1, 1000)
    local index = 1
    local num1 = 1
    local num2 = 1
    local giveitem = 12054300
    for i, item in x418130_g_ItemTable do
        num1 = num1 + item.probability
        if rand >= num2 and rand < num1 then
            index = i
            break
        end
        num2 = num2 + item.probability
    end
    local arr = {}
    local count = 0
    if x418130_g_ItemTable[ index].special == 1 then
        for i, item in x418130_g_ItemSpecial do
            if lv >= item.leveldown and lv < item.levelup then
                count = count + 1
                arr[ count] = item
            end
        end
        giveitem = arr[ random( 1, getn( arr) ) ].itemId
    else
        giveitem = x418130_g_ItemTable[ index].itemId
    end

	BeginAddItem(sceneId)
		AddBindItem( sceneId, giveitem, 1)

	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		if(DepletingUsedItem(sceneId, selfId)) == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�򿪽����������������Ʒ")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			AddItemListToPlayer(sceneId,selfId)

            -- ����㲥
            if x418130_g_ItemTable[ index].broad == 1 then
                LuaAllScenceM2Wrold( sceneId, format( "��ϲ���%s�򿪽������������#{_ITEM%d}", GetName( sceneId, selfId), giveitem), 5, 1)
            end

            local xp = random( 60000, 980000)
            AddExp( sceneId, selfId, xp)
            Msg2Player( sceneId, selfId, format( "������#R%d#cffcc00�㾭�顣", xp), 8, 2)
            Msg2Player( sceneId, selfId, format( "������#R%d#cffcc00�㾭��", xp), 8, 3)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�򿪽��������쳣��")
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
function x418130_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end

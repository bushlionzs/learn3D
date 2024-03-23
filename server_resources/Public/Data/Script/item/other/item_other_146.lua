
x418146_g_ScriptId = 418146
x418146_g_MissionName = "�����ܱ����"

x418146_g_Profession1       = {
                                { lmin =  1, lmax = 30,  itemid = 14030001 }, 
                                { lmin = 31, lmax = 40,  itemid = 14030002 }, 
                                { lmin = 41, lmax = 50,  itemid = 14030003 }, 
                                { lmin = 51, lmax = 60,  itemid = 14030004 }, 
                                { lmin = 61, lmax = 70,  itemid = 14030005 }, 
                                { lmin = 71, lmax = 80,  itemid = 14030031 }, 
                                { lmin = 81, lmax = 160, itemid = 14030032 },
}                                                          
x418146_g_Profession2       = {
                                { lmin =  1, lmax = 30,  itemid = 14030006 }, 
                                { lmin = 31, lmax = 40,  itemid = 14030007 }, 
                                { lmin = 41, lmax = 50,  itemid = 14030008 }, 
                                { lmin = 51, lmax = 60,  itemid = 14030009 }, 
                                { lmin = 61, lmax = 70,  itemid = 14030010 }, 
                                { lmin = 71, lmax = 80,  itemid = 14030035 }, 
                                { lmin = 81, lmax = 160, itemid = 14030036 }, 
}                                                          
x418146_g_Profession3       = {
                                { lmin =  1, lmax = 30,  itemid = 14030011 }, 
                                { lmin = 31, lmax = 40,  itemid = 14030012 }, 
                                { lmin = 41, lmax = 50,  itemid = 14030013 }, 
                                { lmin = 51, lmax = 60,  itemid = 14030014 }, 
                                { lmin = 61, lmax = 70,  itemid = 14030015 }, 
                                { lmin = 71, lmax = 80,  itemid = 14030039 }, 
                                { lmin = 81, lmax = 160, itemid = 14030040 }, 
}                                                          

function x418146_g_Gem( sceneId, selfId)
    local prof = GetZhiye( sceneId, selfId)
    local level = GetLevel( sceneId, selfId)
    local itemid = 14030001
    local tab = nil

    if prof == 0 or prof == 1 or prof == 6 or prof == 7 then
        tab = x418146_g_Profession1
    elseif prof == 2 or prof == 3 or prof == 8 or prof == 9 then
        tab = x418146_g_Profession2
    elseif prof == 4 or prof == 5 or prof == 10 or prof == 11 then
        tab = x418146_g_Profession3
    end
    for i, item in tab do
        if level >= item.lmin and level <= item.lmax then
            itemid = item.itemid
            break
        end
    end

    BeginAddItem( sceneId)
    AddBindItem( sceneId, itemid, 1)
    if EndAddItem( sceneId, selfId) > 0 then
        AddItemListToPlayer( sceneId, selfId)
    else
        Msg2Player( sceneId, selfId, "�����������޷������Ʒ", 8, 3)
    end
end

x418146_g_ItemTable         = {
                                { itemid = 12031019, probability = 157, proc = nil }, 
                                { itemid = 12031013, probability = 157, proc = nil }, 
                                { itemid = 12031007, probability = 157, proc = nil }, 
                                { itemid = 12110206, probability = 157, proc = nil }, 
                                { itemid = 12031000, probability = 100, proc = nil }, 
                                { itemid = 11990011, probability = 100, proc = nil }, 
                                { itemid = 12050009, probability = 100, proc = nil }, 
                                { itemid = 11000501, probability =  50, proc = nil }, 
                                { itemid = 12030200, probability =  20, proc = nil }, 
                                { itemid = 12030200, probability =   2, proc = x418146_g_Gem }, 
}                                                              

x418146_g_ItemList = {}
x418146_g_LevelMin = 1
--��Ҫ�ĵȼ�


--**********************************
--�¼��������
--**********************************
function x418146_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x418146_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x418146_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x418146_OnConditionCheck( sceneId, selfId )
	
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
function x418146_OnDeplete( sceneId, selfId )
    if GetBagSpace( sceneId, selfId) < 1 then
        Msg2Player( sceneId, selfId, format( "�����ռ䲻��#G%d#cffcc00�����޷���������Ʒ", 1), 8, 3)
        return 0
    end
    
	if(DepletingUsedItem(sceneId, selfId) > 0) then
		return 1;
	end
	return 0;
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x418146_OnActivateOnce( sceneId, selfId, impactId )

    if GetBagSpace( sceneId, selfId) < 1 then
        Msg2Player( sceneId, selfId, format( "�����ռ䲻��#G%d#cffcc00�����޷���������Ʒ", 1), 8, 3)
        return
    end

	local r = random( 1, 1000)
    local top = 1
    local bottom = 1
    local index = 1
    for i, item in x418146_g_ItemTable do
        top = top + item.probability
        if r >= bottom and r < top then
            index = i
            break
        end
        bottom = bottom + item.probability
    end
    if x418146_g_ItemTable[ index].proc ~= nil then
        x418146_g_ItemTable[ index].proc( sceneId, selfId)
    else
 		BeginAddItem( sceneId)
		AddBindItem( sceneId, x418146_g_ItemTable[ index].itemid, 1)
		if EndAddItem( sceneId, selfId) > 0 then
			AddItemListToPlayer( sceneId, selfId)
		else
            Msg2Player( sceneId, selfId, "�����������޷������Ʒ", 8, 3)
		end
    end

end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x418146_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end



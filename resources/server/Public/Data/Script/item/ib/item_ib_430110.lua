-- �񴫽�ָ���κ�
x430110_g_ItemTable         = {
                                { name = "��������ָ����ʿ��", itemid = 10284003 }, 
                                { name = "�������ָ��������", itemid = 10284013 }, 
                                { name = "�����ս�ָ�����䣩", itemid = 10284023 }, 
                                { name = "�񴫻�Ծ��ָ����ǹ��", itemid = 10284033 }, 
                                { name = "�񴫰׻���ָ����֪��", itemid = 10284043 }, 
                                { name = "��ʦ����ָ��������", itemid = 10284053 }, 
                                { name = "��������ָ��ʮ�־���", itemid = 10288020 }, 
                                { name = "�������ָ��ʥ��ʹ��", itemid = 10288024 }, 
                                { name = "�����ս�ָ���̿ͣ�", itemid = 10288028 }, 
                                { name = "�񴫻�Ծ��ָ����������", itemid = 10288032 }, 
                                { name = "�񴫰׻���ָ������ʿ��", itemid = 10288036 }, 
                                { name = "��ʦ����ָ��ɮ�£�", itemid = 10288040 }, 

                                
}

x430110_g_MissionId         = 10265
x430110_g_scriptId          = 430110
-- VIP���κ�
x430110_g_VIPItem           = 12030484

function x430110_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
	BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "\t��ֻ���صĺ���������Ÿ��������Σ���ֻ��ѡ�����е�һֻ��\n\t����ϧ��λ��ᣬ��Ϊѡ������ֻ���Σ�������κн�������ʧ��" )
        for i, item in x430110_g_ItemTable do
            AddQuestNumText( sceneId, x430110_g_MissionId, item.name, 3, i)
        end
	EndQuestEvent()                                                
    DispatchQuestEventList( sceneId, selfId, selfId)
end

function x430110_ProcEventEntry( sceneId, selfId, targetId, scriptid, extid)
    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, format( "\t��ȷ��Ҫѡ��#Y%s#W��\n\t��ȷ�Ϻ����õĻ�ã��������ѡ��", x430110_g_ItemTable[ extid].name) )
        AddQuestItemBonus( sceneId, x430110_g_ItemTable[ extid].itemid, 1)
        SetPlayerRuntimeData( sceneId, selfId, RD_VIP_BOX, extid)
    EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, selfId, x430110_g_scriptId, x430110_g_MissionId)
end

function x430110_ProcQuestAccept( sceneId, selfId, targetId, missionId)
    -- ��鱳���ռ�
    local index = GetPlayerRuntimeData( sceneId, selfId, RD_VIP_BOX)
    BeginAddItem( sceneId)
    AddItem( sceneId, x430110_g_ItemTable[ index].itemid, 1)
    if EndAddItem( sceneId, selfId) <= 0 then
        Msg2Player( sceneId, selfId, "�޷��õ���Ʒ����������", 8, 3)
        return
    end
    -- ɾ��VIP���κ�
    if DelItem( sceneId, selfId, x430110_g_VIPItem, 1) == 0 then
        Msg2Player( sceneId, selfId, "�����κ�ɾ��ʧ�ܡ�", 8, 2)
        Msg2Player( sceneId, selfId, "�����κ�ɾ��ʧ�ܡ�", 8, 3)
        return 0
    end
    -- �����Ʒ
    AddItemListToPlayer( sceneId, selfId)
end


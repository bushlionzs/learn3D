#pragma once

#include "net/net_message.h"

struct CHARDBNODE;
class DSCharData : public NetPacket
{
public:
    DSCharData(CHARDBNODE* charDBNode);
    ~DSCharData();

    bool process();
private:
    CHARDBNODE* mCharDBNode;
};
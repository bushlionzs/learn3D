#include "OgreHeader.h"
#include "PackageBox.h"
#include "application_util.h"

#define ITEM_WIDTH 32
#define ITEM_HEIGHT 32
#define CELL_WIDTH  46
#define CELL_HEIGHT 45

PackageBox::PackageBox(MyGUI::Widget* _parent) : wraps::BaseLayout("packagebox.layout", _parent)
{
    
}

PackageBox::~PackageBox()
{
    
}

void PackageBox::init(uint32_t row, uint32_t column, MyGUI::IntCoord& pos)
{
    _row = row;
    _column = column;

    _imageboxs.resize(row * column);

    mMainWidget->setCoord(pos);


    _background = mMainWidget->createWidget<MyGUI::ImageBox>("ImageBox", pos, MyGUI::Align::Stretch, "aabb");
    String imagesetname = "UI_MainBoard_3";
    String imagename = "UI_MainBoard_3_Packet_Cover";
    setImageInfo(_background, imagesetname, imagename);
    _background->setItemSelect(0);

    _background->eventMouseMove += MyGUI::newDelegate(this, &PackageBox::notifyMouseMove);
    _background->eventMouseButtonPressed += MyGUI::newDelegate(this, &PackageBox::notifyMouseButtonPressed);


    MyGUI::IntCoord aa;
    aa.left = 16 + 0 * CELL_WIDTH;
    aa.top = 5 + 0 * CELL_HEIGHT;
    aa.width = ITEM_WIDTH;
    aa.height = ITEM_HEIGHT;
    _focus_box = _background->createWidget<MyGUI::ImageBox>("ImageBox", aa, MyGUI::Align::Stretch, "focus");
    setImageInfo(_focus_box, "CJSH_icons_1", "CJSH_icons_1_action_1");
    _focus_box->setItemSelect(0);
    _focus_box->setVisible(false);
}

bool PackageBox::updateItem(
    uint32_t row, 
    uint32_t column, 
    uint32_t itemId)
{
    uint32_t index = row * _column + column;

    auto imagebox = _imageboxs[index];
    if (imagebox == nullptr)
    {
        MyGUI::IntCoord coord;
        coord.left = 16 + column * CELL_WIDTH;
        coord.top = 5 + row * CELL_HEIGHT;
        coord.width = ITEM_WIDTH;
        coord.height = ITEM_HEIGHT;
        imagebox = _background->createWidget<MyGUI::ImageBox>("ImageBox", coord, MyGUI::Align::Stretch, "aabb");
        _imageboxs[index] = imagebox;
        setImageInfoFromIcon(imagebox, itemId);

        imagebox->setItemSelect(0);
        imagebox->setDepth(index + 1);
        imagebox->eventMouseSetFocus += MyGUI::newDelegate(this, &PackageBox::notifySetFocus);
        imagebox->eventMouseLostFocus += MyGUI::newDelegate(this, &PackageBox::notifySetFocus);
    }
    return true;
}

void PackageBox::setItemFocus(
    uint32_t row,
    uint32_t column)
{
    MyGUI::IntCoord aa;
    aa.left = 16 + column * CELL_WIDTH;
    aa.top = 5 + row * CELL_HEIGHT;
    aa.width = ITEM_WIDTH;
    aa.height = ITEM_HEIGHT;

    _focus_box->setCoord(aa);
    _focus_box->setVisible(true);
}

void PackageBox::notifyMouseButtonPressed(MyGUI::Widget* _sender,
    int _left, int _top, MyGUI::MouseButton _id)
{
    
}

void PackageBox::notifyMouseDrag(MyGUI::Widget* _sender,
    int _left, int _top, MyGUI::MouseButton _id)
{
    
}

void PackageBox::notifyMouseMove(MyGUI::Widget* _sender, int _left, int _top)
{

}

void PackageBox::notifySetFocus(MyGUI::Widget* current, MyGUI::Widget* last)
{
    if (last)
    {
        _focus_box->setVisible(false);
    }

    if (current)
    {
        MyGUI::ImageBox* imagebox = (MyGUI::ImageBox*)current;
        uint32_t index = imagebox->getDepth() - 1;

        uint32_t row = index / _column;
        uint32_t column = index % _column;

        setItemFocus(row, column);
    }

}



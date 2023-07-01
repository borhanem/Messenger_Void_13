#include "refresherdirectlist.h"

refresherDirectList::refresherDirectList(QObject *parent)
{

}

void refresherDirectList::refresherMain()
{
    currUser->userListReinit();
    int countTemp = currUser->userCountGetter();
    if(userCount != countTemp){
        jsonHandle();
        userCount = countTemp;
    }
}

void refresherDirectList::jsonHandle()
{
    QList<QString> userList;
    QVector<QString> userListVec = currUser->userListGetter();
    for (const auto& item : userListVec) {
        userList.append(item); // Append each item from the QVector to the QList
    }
    emit newUserFound(userList);
}

void refresherDirectList::userMalloc()
{
    currUser = new User();
    if(currUser->loadFromFile()){
        //         file no exist
        qDebug() << "file problem abstract refresherdirect::userMalloc";
    }
    contactCountInit();
}

void refresherDirectList::contactCountInit()
{
    currUser->userListReinit();
    userCount = currUser->userCountGetter();
}

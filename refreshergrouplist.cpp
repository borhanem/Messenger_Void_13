//#include "refreshergrouplist.h"

//refresherGroupList::refresherGroupList(QObject *parent)
//{

//}

//void refresherGroupList::refresherMain()
//{
//    currUser->groupListReinit();
//    int countTemp = currUser->groupCountGetter();
//    if(groupCount != countTemp){
//        jsonHandle();
//        groupCount = countTemp;
//    }
//}

//void refresherGroupList::jsonHandle()
//{
//    QList<QString> groupList;
//    QVector<QString> groupListVec = currUser->groupListGetter();
//    for (const auto& item : groupListVec) {
//        groupList.append(item); // Append each item from the QVector to the QList
//    }
//    emit newGroupFound(groupList);
//}

//void refresherGroupList::userMalloc()
//{
//    currUser = new User();
//    if(currUser->loadFromFile()){
//        //         file no exist
//        qDebug() << "file problem abstract refresherdirect::userMalloc";
//    }
//    groupCountInit();
//}

//void refresherGroupList::groupCountInit()
//{
//    currUser->groupListReinit();
//    groupCount = currUser->groupCountGetter();
//}

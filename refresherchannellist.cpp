//#include "refresherchannellist.h"

//refresherChannelList::refresherChannelList(QObject *parent)
//{

//}

//void refresherChannelList::refresherMain()
//{
//    currUser->channelListReinit();
//    int countTemp = currUser->channelCountGetter();
//    if(channelCount != countTemp){
//        jsonHandle();
//        channelCount = countTemp;
//    }
//}

//void refresherChannelList::jsonHandle()
//{
//    QList<QString> channelList;
//    QVector<QString> channelListVec = currUser->channelListGetter();
//    for (const auto& item : channelListVec) {
//        channelList.append(item); // Append each item from the QVector to the QList
//    }
//    emit newChannelFound(channelList);
//}

//void refresherChannelList::userMalloc()
//{
//    currUser = new User();
//    if(currUser->loadFromFile()){
//        //         file no exist
//        qDebug() << "file problem abstract refresherdirect::userMalloc";
//    }
//    channelCountInit();
//}

//void refresherChannelList::channelCountInit()
//{
//    currUser->channelListReinit();
//    channelCount = currUser->channelCountGetter();
//}

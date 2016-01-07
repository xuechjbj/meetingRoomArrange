//
//  main.cpp
//  Algo-meeting
//
//  Created by Chaojun Xue on 1/5/16.
//  Copyright © 2016 Chaojun Xue. All rights reserved.
//

#include <iostream>
#include <list>

const int MAX_ROOMS = 100;
const int NO_ROOM = -1;

class MeetingTime{
public:
    MeetingTime(int s, int e){
        start = s;
        end = e;
        roomId = NO_ROOM;
    }
    int start;
    int end;
    int roomId;
};

class RoomTime{
public:
    RoomTime(){
    }
    
    void setBusyTime(std::shared_ptr<MeetingTime> &meeting){
        meetingHold.push_back(meeting);
    }
    
    bool isIdle(std::shared_ptr<MeetingTime> &meeting){
        for (std::shared_ptr<MeetingTime> &m : meetingHold){
            int start = m->start;
            int end = m->end;
            
            if(meeting->start > start && meeting->start < end)
                return false;
            
            if(meeting->end > start && meeting->end < end)
                return false;
            
            if(meeting->start <= start && meeting->end >= end)
                return false;
        }
        
        return true;
    }
    
private:
    
    std::list<std::shared_ptr<MeetingTime>> meetingHold;
    
};

RoomTime Room[MAX_ROOMS];
int roomId;
int roomNum;

int reuseRoom(std::list<std::shared_ptr<MeetingTime>> &meetingList, std::shared_ptr<MeetingTime> &newMeeting){
    for(std::shared_ptr<MeetingTime> &meeting : meetingList){
        if(meeting->roomId != NO_ROOM &&  Room[meeting->roomId].isIdle(newMeeting)){
            return meeting->roomId;
        }
    }
    return NO_ROOM;
}

int main(int argc, const char * argv[]) {
    roomNum = 0;
    std::list<std::shared_ptr<MeetingTime>> meetingList;
    
    meetingList.push_back(std::shared_ptr<MeetingTime>(new MeetingTime(1,3)));
    meetingList.push_back(std::shared_ptr<MeetingTime>(new MeetingTime(1,5)));
    meetingList.push_back(std::shared_ptr<MeetingTime>(new MeetingTime(6,7)));
    meetingList.push_back(std::shared_ptr<MeetingTime>(new MeetingTime(4,7)));
    
    meetingList.sort([](std::shared_ptr<MeetingTime>&t1, std::shared_ptr<MeetingTime>&t2){
                  return t1->start < t2->start?true:
                  ((t1->start == t2->start)? t1->end <= t2->end:false);
              });
    
    for(std::shared_ptr<MeetingTime>& meeting : meetingList){
        int roomNo = reuseRoom(meetingList, meeting);
        if(roomNo == NO_ROOM){
            roomNo = roomNum++;
        }
        Room[roomNo].setBusyTime(meeting);
        meeting->roomId = roomNo;
    }
    
    printf("Need meeting rooms=%d\n", roomNum);
    std::for_each(meetingList.begin(), meetingList.end(),
                  [](std::shared_ptr<MeetingTime>&meeting){
                      printf("(%d, %d, room=%d)\n", meeting->start, meeting->end, meeting->roomId);
                  });
    
    return 0;
}

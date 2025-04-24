#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& shifts, 
    size_t sp,
    size_t days
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
) {
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    sched.assign(avail.size(), vector<Worker_T>());

    //tracks numbers of shifts per worker
    vector<int> shifts(avail[0].size(), 0);
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, 0, 0);
}
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& shifts, 
    size_t sp,
    size_t days
) {
    //in the case all days scheduled 
    if(days == avail.size()) return true;
    //if all spots filled move to next day
    if(sp == dailyNeed) return scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, 0, days + 1);

    //find valid assign for current spot
    for (size_t worker = 0; worker < avail[0].size(); ++worker) {
       //prevents double booking 
        set<Worker_T> assigned(sched[days].begin(), sched[days].end());
       
        //checking if worker has exceeded max shifts, available on day, and hasnt already assigned today
        bool belowMS = maxShifts > shifts[worker];
        bool available = avail[days][worker];
        bool notAssign = assigned.find(worker) == assigned.end();
        if (belowMS && notAssign && available) {

            sched[days].push_back(worker);
            shifts[worker]++;
            //trying to schedule next avail spot
            bool succ = scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, sp + 1, days);
            if (succ) return true;  

            //backtrack
            sched[days].pop_back();
            shifts[worker]--;
        }
    }

    return false;
}



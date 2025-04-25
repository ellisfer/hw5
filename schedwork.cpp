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
bool isValid(int day, int id, const size_t dailyNeed, const size_t maxShifts, vector<int>& shiftsWorked, DailySchedule& sched);

bool schedHelper(int day, unsigned int worker, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, vector<int>& shiftsWorked, DailySchedule& sched);

void printShifts(const vector<int>& shiftsWorked);
// type for the ID of a worker
typedef unsigned int Worker_T;
// n-by-k Matrix of each of the k workers' availability over an n-day period
typedef std::vector<std::vector<bool>> AvailabilityMatrix;
// n-by-d matrix with the d worker IDs who are scheduled 
// to work on each of the n days
typedef std::vector<std::vector<Worker_T> > DailySchedule;

// Add your implementation of schedule() and other helper functions here

/**
 * @brief Produces a work schedule given worker availability,
 *        the number of needed workers per day, and the maximum 
 *        shifts any single worker is allowed. Returns true if
 *        and the valid schedule if a solution exists, and false
 *        otherwise. 
 * 
 * @param [in]  avail n x k vector of vectors (i.e. matrix) of the availability
 *                    of the k workers for each of the n days
 * @param [in]  dailyNeed Number of workers needed per day (aka d)
 * @param [in]  maxShifts Maximum shifts any worker is allowed over 
 *                        the n day period (aka m)
 * @param [out] sched n x d vector of vectors indicating the d workers
 *                    who are scheduled to work on each of the n days
 * @return true if a solution exists; sched contains the solution
 * @return false if no solution exists; sched is undefined (can be anything)
 */
bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    vector<int> shiftsWorked(avail[0].size(), 0);

    for(unsigned int i = 0; i < avail.size(); i++){
      sched.push_back(vector<unsigned int>(dailyNeed, avail[0].size()));
    }

    return (schedHelper(0, 0, avail, dailyNeed, maxShifts, shiftsWorked, sched));



}

void printShifts(const vector<int>& shiftsWorked){
  for(unsigned int i = 0; i < shiftsWorked.size(); i++){
    cout << shiftsWorked[i] << " ";
  }
  cout << endl;
}

bool isValid(int day, int id, const size_t dailyNeed, const size_t maxShifts, vector<int>& shiftsWorked, DailySchedule& sched){
  if(shiftsWorked[id] > maxShifts){
    //cout << "isValid: false. DAY: " << day << " ID: " << id << endl;
    return false;
  };
//cout << "isValid: true. DAY: " << day << " ID: " << id << endl;
  return true;
}

bool schedHelper(int day, unsigned int worker, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, vector<int>& shiftsWorked, DailySchedule& sched){
  // base case: made it to end, scheduling  
  //cout << "Helper. DAY: " << day << " WORKER: " << worker << endl;
  //cout <<  "   shiftsWorked "; printShifts(shiftsWorked); 
  if(day == avail.size()) return true;

  int ogval = sched[day][worker];
  for(unsigned int i = 0; i < avail[0].size(); i++){
    if(avail[day][i] == 0 || (find(sched[day].begin(), sched[day].end(), i) != sched[day].end())) continue;
    sched[day][worker] = i;
    if(shiftsWorked[i] < maxShifts){
      //cout << "   VALID: " << i << endl;
      shiftsWorked[i] ++;
      if(worker != dailyNeed-1){
        if(schedHelper(day, worker +1, avail, dailyNeed, maxShifts, shiftsWorked, sched)) return true;
      }
      else{
        if(schedHelper(day+1, 0, avail, dailyNeed, maxShifts, shiftsWorked, sched)) return true;
      }
      shiftsWorked[i] --;
      //cout << "BACTRACKING: Day: " << day << " worker " << worker << " i: " << i << endl;
    }
      //cout << "   INVALID: " << i << endl;
      sched[day][worker] = ogval;
  
  }

  if(ogval == avail[0].size()){
    sched[day][worker] = ogval;
  }

  return false;
}

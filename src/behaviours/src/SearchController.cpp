#include "SearchController.h"

int SearchController::caseTurn = 1;
int SearchController::counter = 1;


SearchController::SearchController() {
  rng = new random_numbers::RandomNumberGenerator();
  currentLocation.x = 0;
  currentLocation.y = 0;
  currentLocation.theta = 0;

  centerLocation.x = 0;
  centerLocation.y = 0;
  centerLocation.theta = 0;
  result.PIDMode = FAST_PID;

  result.fingerAngle = M_PI/2;
  result.wristAngle = M_PI/4;
}

void SearchController::Reset() {
  result.reset = false;
}

/**
 * This code implements a basic random walk search.
 */
Result SearchController::DoWork() {

  if (!result.wpts.waypoints.empty()) {
    if (hypot(result.wpts.waypoints[0].x-currentLocation.x, result.wpts.waypoints[0].y-currentLocation.y) < 0.10) {
      attemptCount = 0;
    }
  }

  if (attemptCount > 0 && attemptCount < 5) {
    attemptCount++;
    if (succesfullPickup) {
      succesfullPickup = false;
      attemptCount = 1;
    }
    return result;
  }
  else if (attemptCount >= 5 || attemptCount == 0) {
    attemptCount = 1;


    result.type = waypoint;
    Point  searchLocation;

    //select new position 50 cm from current location
	    if (first_waypoint)
	    {
	      first_waypoint = false;
	      searchLocation.theta = M_PI/2;
	      searchLocation.x = 0;
	      searchLocation.y = 2;
	    }    

	else if (caseTurn == 1) {		
			
			searchLocation.theta = M_PI/2.0;
			searchLocation.x = currentLocation.x + (counter * cos(searchLocation.theta)); 
  			searchLocation.y = currentLocation.y + (counter * sin(searchLocation.theta));
			caseTurn++;
					
		}

		else if (caseTurn == 2) {
			
			
			searchLocation.theta = 0;
			searchLocation.x = currentLocation.x + (counter * cos(searchLocation.theta)); 
  			searchLocation.y = currentLocation.y + (counter * sin(searchLocation.theta));
			caseTurn++;
			counter++;
		}
		
		else if (caseTurn == 3) {
			
			
			searchLocation.theta = M_PI/(-2.0);
			searchLocation.x = currentLocation.x + (counter * cos(searchLocation.theta)); 
  			searchLocation.y = currentLocation.y + (counter * sin(searchLocation.theta));
			caseTurn++;	

		}

		else if (caseTurn == 4) {
		
			searchLocation.theta = M_PI;
			searchLocation.x = currentLocation.x + (counter * cos(searchLocation.theta)); 
  			searchLocation.y = currentLocation.y + (counter * sin(searchLocation.theta));
			counter++;
			caseTurn = 1;
					
		}



if( caseTurn % 2 != 0)
counter++;

searchLocation.theta = currentLocation.theta - (M_PI/2);
searchLocation.x = currentLocation.x + (counter * cos(searchLocation.theta)); 
searchLocation.y = currentLocation.y + (counter * sin(searchLocation.theta));
caseTurn++;

    result.wpts.waypoints.clear();
    result.wpts.waypoints.insert(result.wpts.waypoints.begin(), searchLocation);

    return result;
  }

}

void SearchController::SetCenterLocation(Point centerLocation) {
  this->centerLocation = centerLocation;
}

void SearchController::SetCurrentLocation(Point currentLocation) {
  this->currentLocation = currentLocation;
}

void SearchController::ProcessData() {
}

bool SearchController::ShouldInterrupt(){
  ProcessData();

  return false;
}

bool SearchController::HasWork() {
  return true;
}

void SearchController::SetSuccesfullPickup() {
  succesfullPickup = true;
}



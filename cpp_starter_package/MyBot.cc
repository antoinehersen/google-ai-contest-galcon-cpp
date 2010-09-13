#include <iostream>
#include "PlanetWars.h"

int  ClosestPlanet(const PlanetWars& pw,
                   int planet_source_id) {
  int result = 0;
  int shortest_distance = 99999;
  std::vector<Planet> not_my_planets = pw.NotMyPlanets();
  for (int i = 0; i < not_my_planets.size(); ++i) {
    const Planet& p = not_my_planets[i];

    int distance = pw.Distance( p.PlanetID(), planet_source_id);
    if (distance < shortest_distance) {
      shortest_distance = distance;
      result = p.PlanetID();
    }
  }
  return result;
}

// The DoTurn function is where your code goes. The PlanetWars object contains
// the state of the game, including information about all planets and fleets
// that currently exist. Inside this function, you issue orders using the
// pw.IssueOrder() function. For example, to send 10 ships from planet 3 to
// planet 8, you would say pw.IssueOrder(3, 8, 10).
//
// There is already a basic strategy in place here. You can use it as a
// starting point, or you can throw it out entirely and replace it with your
// own. Check out the tutorials and articles on the contest website at
// http://www.ai-contest.com/resources.
void DoTurn(const PlanetWars& pw) {

  std::vector<Planet> my_planets = pw.MyPlanets();
  for (int i = 0; i < my_planets.size(); ++i) {
    const Planet& p = my_planets[i];
    int source = p.PlanetID();
    int dest = ClosestPlanet( pw, source);

    pw.IssueOrder( source, dest, p.NumShips());

  }
}

// This is just the main game loop that takes care of communicating with the
// game engine for you. You don't have to understand or change the code below.
int main(int argc, char *argv[]) {
  std::string current_line;
  std::string map_data;
  while (true) {
    int c = std::cin.get();
    current_line += (char)c;
    if (c == '\n') {
      if (current_line.length() >= 2 && current_line.substr(0, 2) == "go") {
        PlanetWars pw(map_data);
        map_data = "";
        DoTurn(pw);
	pw.FinishTurn();
      } else {
        map_data += current_line;
      }
      current_line = "";
    }
  }
  return 0;
}

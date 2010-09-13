#include <iostream>
#include "PlanetWars.h"

int  ClosestPlanet(const PlanetWars& pw,
                   int planet_source_id) {
  int result = -1;
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

int  EasiestPlanet(const PlanetWars& pw,
                   int planet_source_id) {
  int result = -1;
  int shortest_distance = 99999;

  int own_gr = pw.GetPlanet(planet_source_id).GrowthRate();

  std::vector<Planet> not_my_planets = pw.NotMyPlanets();
  for (int i = 0; i < not_my_planets.size(); ++i) {
    const Planet& p = not_my_planets[i];

    int distance = pw.Distance( p.PlanetID(), planet_source_id);
    distance += p.NumShips() / own_gr;

    if (distance < shortest_distance) {
      shortest_distance = distance;
      result = p.PlanetID();
    }
  }
  return result;
}

int Attacked(const PlanetWars& pw,
             int planet_source_id) {

  int result = 0;
  std::vector<Fleet> enemy_fleets = pw.EnemyFleets();
  for (int i = 0; i < enemy_fleets.size(); ++i) {
    const Fleet & fleet = enemy_fleets[i];
    if (fleet.DestinationPlanet() == planet_source_id) {
      result += fleet.NumShips();
    }
  }
  return result;
}

// The DoTurn function is where your code goes. The PlanetWars object contains


void DoTurn(const PlanetWars& pw) {

  std::vector<Planet> my_planets = pw.MyPlanets();
  for (int i = 0; i < my_planets.size(); ++i) {
    const Planet& p = my_planets[i];
    int source = p.PlanetID();
    int dest = ClosestPlanet( pw, source);
    if (dest != -1) {
      int num_ships = p.NumShips() - Attacked(pw, source);
      if (num_ships > 0)
        pw.IssueOrder( source, dest, num_ships);
    }
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

#ifndef CONFIG_H
#define CONFIG_H

struct Config {
  int  version          = 1;
  std::string ElevatorBlock = "minecraft:iron_block";
  int minElevatorDistance = 3;
  int maxElevatorDistance = 27;
};

#endif //CONFIG_H

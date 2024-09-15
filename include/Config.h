#ifndef CONFIG_H
#define CONFIG_H

struct Config {
    int         version                  = 2;
    std::string ElevatorBlock            = "minecraft:iron_block";
    int         minElevatorDistance      = 3;
    int         maxElevatorDistance      = 27;
    bool        checkTeleportPointSafety = true;
};

#endif // CONFIG_H

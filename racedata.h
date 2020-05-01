/*
Racedata is the class that holds the information to set up a race, such as the gamemode and the characters each player chose
A pointer to an instance of this class is stored at 0x809bd728 PAL
TheLordScruffy helped massively with this
*/

typedef enum : int {
    BATTLE_BALLOON,
    BATTLE_COIN
} BattleType;

typedef enum : int {
    CPU_EASY,
    CPU_NORMAL,
    CPU_HARD,
    CPU_NONE
} CpuMode;

typedef enum : int {
    MODE_GRAND_PRIX,
    MODE_VS_RACE,
    MODE_TIME_TRIAL,
    MODE_BATTLE,
    MODE_MISSION_TOURNAMENT,
    MODE_GHOST_RACE,
    MODE_6,
    MODE_PRIVATE_VS,
    MODE_PUBLIC_VS,
    MODE_PUBLIC_BATTLE,
    MODE_PRIVATE_BATTLE,
    MODE_AWARD,
    MODE_CREDITS
} GameMode;

typedef enum : int {
    CC_50,
    CC_100,
    CC_150,
    CC_BATTLE // Note: Battle mode actually sets it to 50cc (which is ignored by code), but setting it to this in other modes results in Battle CC
} EngineClass;

typedef enum : int {
    ITEMS_BALANCED,
    ITEMS_FRANTIC,
    ITEMS_STRATEGIC,
    ITEMS_NONE
} ItemMode;

typedef struct {
  uint32_t courseId; // http://wiki.tockdom.com/wiki/List_of_Identifiers#Courses
  EngineClass engineClass;
  GameMode gamemode;
  uint32_t unknown_0xC;
  BattleType battleType;
  CpuMode cpuMode;
  ItemMode itemMode;
  uint8_t hudPlayerIds[4];
  uint32_t cupId; // http://wiki.tockdom.com/wiki/List_of_Identifiers#Cups
  uint8_t unknown_0x24;
  uint8_t unknown_0x25;
  uint8_t unknown_0x26;
  uint8_t unknown_0x27;
  uint32_t mirrorModeAndSomeOtherStuff; // bit flags, 0x1 is mirror mode, others unknown
  uint32_t unknown_0x2c;
  uint32_t unknown_0x30;
} RacedataSettings; // Total size 0x34

class RacedataPlayer {
    virtual ~RacedataPlayer(); // 8052DC68 PAL
    RacedataPlayer(); // 8052d96c PAL
    
    // vtable 808b3294 PAL
    uint8_t unknown_0x4;
    uint8_t unknown_0x5;
    uint8_t unknown_0x6;
    uint8_t unknown_0x7; // possibly padding
    uint32_t vehicleId; // http://wiki.tockdom.com/wiki/List_of_Identifiers#Vehicles
    uint32_t characterId; // http://wiki.tockdom.com/wiki/List_of_Identifiers#Characters
    uint32_t unknown_0x10;
    // Start of some other class inside of it, length is uncertain
    // The rest is unknown, total size is 0xf0 bytes
}; // Total size 0xf0

class RacedataScenario {
  virtual ~RacedataScenario();
  RacedataScenario(RacedataBigThing * bigThing); // 8052dbc8 PAL, never used afaik (Racedata's constructor does it inline)

  // vtable 808b3288 PAL
  uint8_t playerCount;
  // unknown 0x5-7, 6 & 7 might be padding but 5 is set to 0 in constructor
  RacedataPlayer players[12];
  RacedataSettings settings;
  KMTFile mission; // http://wiki.tockdom.com/wiki/Mission_Mode#mission_single.kmt - size is 0x70
  RacedataBigThing * bigThing; // Scenario 0 points to big thing 0, 1 to 1, 2 to null
}; // Total size 0xbf0

class RacedataMain {
  // Always constructed inline, functions seem to always be members of Racedata rather than specifically RacedataMain

  //vtable 808b3260 PAL (empty)  
  RacedataScenario scenarios[3]; // 0 is in race, 1 is in menu, not sure what 2 is
  RacedataBigThing bigThings[2]; // 0x2800 struct, memset to 0 on construction, not seen any code use them yet
}; // Total size 0x73d4

class Racedata : public ParameterFile { // https://github.com/riidefi/MKWDecompilation/blob/master/Static/System/ParameterFile.hpp with /boot/menuset.prm parameter file
public:
  virtual ~Racedata(); // 80530038 PAL
  virtual FUN_80009ddc();
  virtual FUN_80532078(); // just a blr
  virtual FUN_80532074(); // just a blr
  virtual FUN_80532070(); // just a blr
  // Always constructed inline
  
  // vtable 808b3268 PAL
  RacedataMain main; // 0x1c bytes in
}; // Total size 0x73f0

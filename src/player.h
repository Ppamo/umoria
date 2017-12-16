// Copyright (c) 1989-94 James E. Wilson, Robert A. Koeneke
//
// Umoria is free software released under a GPL v2 license and comes with
// ABSOLUTELY NO WARRANTY. See https://www.gnu.org/licenses/gpl-2.0.html
// for further details.

#pragma once

// Player_t contains everything to be known about our player character
typedef struct {
    struct {
        char name[PLAYER_NAME_SIZE];    // Name of character
        bool gender;                    // Gender of character (Female = 0, Male = 1)
        int32_t date_of_birth;          // Unix time for when the character was created
        int32_t au;                     // Gold
        int32_t max_exp;                // Max experience
        int32_t exp;                    // Cur experience
        uint16_t exp_fraction;          // Cur exp fraction * 2^16
        uint16_t age;                   // Characters age
        uint16_t height;                // Height
        uint16_t weight;                // Weight
        uint16_t level;                 // Level
        uint16_t max_dungeon_depth;     // Max level explored
        int16_t chance_in_search;       // Chance in search
        int16_t fos;                    // Frequency of search
        int16_t bth;                    // Base to hit
        int16_t bth_with_bows;          // BTH with bows
        int16_t mana;                   // Mana points
        int16_t max_hp;                 // Max hit pts
        int16_t plusses_to_hit;         // Plusses to hit
        int16_t plusses_to_damage;      // Plusses to dam
        int16_t ac;                     // Total AC
        int16_t magical_ac;             // Magical AC
        int16_t display_to_hit;         // Display +ToHit
        int16_t display_to_damage;      // Display +ToDam
        int16_t display_ac;             // Display +ToTAC
        int16_t display_to_ac;          // Display +ToAC
        int16_t disarm;                 // % to Disarm
        int16_t saving_throw;           // Saving throw
        int16_t social_class;           // Social Class
        int16_t stealth_factor;         // Stealth factor
        uint8_t class_id;               // # of class
        uint8_t race_id;                // # of race
        uint8_t hit_die;                // Char hit die
        uint8_t experience_factor;      // Experience factor
        int16_t current_mana;           // Current mana points
        uint16_t current_mana_fraction; // Current mana fraction * 2^16
        int16_t current_hp;             // Current hit points
        uint16_t current_hp_fraction;   // Current hit points fraction * 2^16
        char history[4][60];            // History record
    } misc;

    // Stats now kept in arrays, for more efficient access. -CJS-
    struct {
        uint8_t max[6];      // What is restored
        uint8_t current[6];  // What is natural
        int16_t modified[6]; // What is modified, may be +/-
        uint8_t used[6];     // What is used
    } stats;

    struct {
        uint32_t status;             // Status of player
        int16_t rest;                // Rest counter
        int16_t blind;               // Blindness counter
        int16_t paralysis;           // Paralysis counter
        int16_t confused;            // Confusion counter
        int16_t food;                // Food counter
        int16_t food_digested;       // Food per round
        int16_t protection;          // Protection fr. evil
        int16_t speed;               // Cur speed adjust
        int16_t fast;                // Temp speed change
        int16_t slow;                // Temp speed change
        int16_t afraid;              // Fear
        int16_t poisoned;            // Poisoned
        int16_t image;               // Hallucinate
        int16_t protect_evil;        // Protect VS evil
        int16_t invulnerability;     // Increases AC
        int16_t heroism;             // Heroism
        int16_t super_heroism;       // Super Heroism
        int16_t blessed;             // Blessed
        int16_t heat_resistance;     // Timed heat resist
        int16_t cold_resistance;     // Timed cold resist
        int16_t detect_invisible;    // Timed see invisible
        int16_t word_of_recall;      // Timed teleport level
        int16_t see_infra;           // See warm creatures
        int16_t timed_infra;         // Timed infra vision
        bool see_invisible;          // Can see invisible
        bool teleport;               // Random teleportation
        bool free_action;            // Never paralyzed
        bool slow_digest;            // Lower food needs
        bool aggravate;              // Aggravate monsters
        bool resistant_to_fire;      // Resistance to fire
        bool resistant_to_cold;      // Resistance to cold
        bool resistant_to_acid;      // Resistance to acid
        bool regenerate_hp;          // Regenerate hit pts
        bool resistant_to_light;     // Resistance to light
        bool free_fall;              // No damage falling
        bool sustain_str;            // Keep strength
        bool sustain_int;            // Keep intelligence
        bool sustain_wis;            // Keep wisdom
        bool sustain_con;            // Keep constitution
        bool sustain_dex;            // Keep dexterity
        bool sustain_chr;            // Keep charisma
        bool confuse_monster;        // Glowing hands.

        uint8_t new_spells_to_learn;      // Number of spells can learn.
        uint32_t spells_learnt;           // bit mask of spells learned
        uint32_t spells_worked;           // bit mask of spells tried and worked
        uint32_t spells_forgotten;        // bit mask of spells learned but forgotten
        uint8_t spells_learned_order[32]; // order spells learned/remembered/forgotten
    } flags;

    // location in dungeon
    int16_t row;
    int16_t col;

    // calculated base hp values at each level, store them so that
    // drain life + restore life does not affect hit points.
    uint16_t base_hp_levels[PLAYER_MAX_LEVEL];

    // Base experience levels, may be adjusted up for race and/or class
    uint32_t base_exp_levels[PLAYER_MAX_LEVEL];

    uint8_t running_tracker;   // Tracker for number of turns taken during one run cycle
    bool temporary_light_only; // Track if temporary light about player

    int32_t max_score = 0; // Maximum score attained

    // TODO: create a pack/inventory object?
    int16_t unique_inventory_items = 0;
    int16_t inventory_weight = 0; // Current carried weight
    int16_t pack_heaviness;       // Heaviness of pack - used to calculate if pack is too heavy -CJS-

    // TODO: create an equipment object?
    int16_t equipment_count = 0; // Number of equipped items
    bool weapon_is_heavy;        // Weapon is too heavy -CJS-
    bool carrying_light;         // `true` when player is carrying light
} Player_t;
bool playerIsMale();
void playerSetGender(bool is_male);
const char *playerGetGenderLabel();
void playerInitializeBaseExperienceLevels();
void playerCalculateHitPoints();
int playerAttackBlows(int weight, int &weight_to_hit);
bool playerMovePosition(int dir, int &new_y, int &new_x);
void playerTeleport(int new_distance);
bool playerNoLight();
void playerDisturb(int major_disturbance, int light_disturbance);
void playerSearchOn();
void playerSearchOff();
void playerRestOn();
void playerRestOff();
bool executeAttackOnPlayer(uint8_t creature_level, int16_t &monster_hp, int monster_id, int attack_type, int damage, vtype_t death_description, bool noticed);
void playerDiedFromString(vtype_t *description, const char *monster_name, uint32_t move);
bool playerTestAttackHits(int attack_id, uint8_t level);

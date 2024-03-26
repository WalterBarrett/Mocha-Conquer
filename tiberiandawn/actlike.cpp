//
// Copyright 2020 Electronic Arts Inc.
//
// TiberianDawn.DLL and RedAlert.dll and corresponding source code is free
// software: you can redistribute it and/or modify it under the terms of
// the GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.

// TiberianDawn.DLL and RedAlert.dll and corresponding source code is distributed
// in the hope that it will be useful, but with permitted additional restrictions
// under Section 7 of the GPL. See the GNU General Public License in LICENSE.TXT
// distributed with this program. You should have received a copy of the
// GNU General Public License along with permitted additional restrictions
// with this program. If not, see https://github.com/electronicarts/CnC_Remastered_Collection

#include "function.h"

// The cases where a technotype is checked for and then returns itself are just
// the skeleton for when more factions are added later.

StructType RemapStructure(StructType structure, HousesType house)
{
    switch (structure) {
        case STRUCT_WEAP:
        case STRUCT_AIRSTRIP:
            switch (house) {
                case HOUSE_GOOD: return STRUCT_WEAP;
                case HOUSE_BAD: return STRUCT_AIRSTRIP;
                default: return STRUCT_WEAP;
            }
        case STRUCT_GTOWER:
        case STRUCT_TURRET:
            switch (house) {
                case HOUSE_GOOD: return STRUCT_GTOWER;
                case HOUSE_BAD: return STRUCT_TURRET;
                default: return STRUCT_GTOWER;
            }
        case STRUCT_ATOWER:
        case STRUCT_OBELISK:
            switch (house) {
                case HOUSE_GOOD: return STRUCT_ATOWER;
                case HOUSE_BAD: return STRUCT_OBELISK;
                default: return STRUCT_ATOWER;
            }
        case STRUCT_RADAR:
            switch (house) {
                case HOUSE_GOOD: return STRUCT_RADAR;
                case HOUSE_BAD: return STRUCT_RADAR;
                default: return STRUCT_RADAR;
            }
        case STRUCT_CONST:
            switch (house) {
                case HOUSE_GOOD: return STRUCT_CONST;
                case HOUSE_BAD: return STRUCT_CONST;
                default: return STRUCT_CONST;
            }
        case STRUCT_REFINERY:
            switch (house) {
                case HOUSE_GOOD: return STRUCT_REFINERY;
                case HOUSE_BAD: return STRUCT_REFINERY;
                default: return STRUCT_REFINERY;
            }
        case STRUCT_STORAGE:
            switch (house) {
                case HOUSE_GOOD: return STRUCT_STORAGE;
                case HOUSE_BAD: return STRUCT_STORAGE;
                default: return STRUCT_STORAGE;
            }
        case STRUCT_HELIPAD:
            switch (house) {
                case HOUSE_GOOD: return STRUCT_HELIPAD;
                case HOUSE_BAD: return STRUCT_HELIPAD;
                default: return STRUCT_HELIPAD;
            }
        case STRUCT_SAM:
            switch (house) {
                case HOUSE_GOOD: return STRUCT_SAM;
                case HOUSE_BAD: return STRUCT_SAM;
                default: return STRUCT_SAM;
            }
        case STRUCT_POWER:
            switch (house) {
                case HOUSE_GOOD: return STRUCT_POWER;
                case HOUSE_BAD: return STRUCT_POWER;
                default: return STRUCT_POWER;
            }
        case STRUCT_ADVANCED_POWER:
            switch (house) {
                case HOUSE_GOOD: return STRUCT_ADVANCED_POWER;
                case HOUSE_BAD: return STRUCT_ADVANCED_POWER;
                default: return STRUCT_ADVANCED_POWER;
            }
        case STRUCT_BARRACKS:
        case STRUCT_HAND:
            switch (house) {
                case HOUSE_GOOD: return STRUCT_BARRACKS;
                case HOUSE_BAD: return STRUCT_HAND;
                default: return STRUCT_BARRACKS;
            }
        case STRUCT_REPAIR:
            switch (house) {
                case HOUSE_GOOD: return STRUCT_REPAIR;
                case HOUSE_BAD: return STRUCT_REPAIR;
                default: return STRUCT_REPAIR;
            }
        case STRUCT_EYE:
        case STRUCT_TEMPLE:
            switch (house) {
                case HOUSE_GOOD: return STRUCT_EYE;
                case HOUSE_BAD: return STRUCT_TEMPLE;
                default: return STRUCT_EYE;
            }
        default: return structure;
    }
}

InfantryType RemapInfantry(InfantryType infantry, HousesType house)
{
    switch (infantry) {
        case INFANTRY_E1: // Minigunner
            switch (house) {
                case HOUSE_GOOD: return INFANTRY_E1; // Minigunner
                case HOUSE_BAD: return INFANTRY_E1; // Minigunner
                default: return INFANTRY_E1; // Minigunner
            }
        case INFANTRY_E2: // Grenadier
        case INFANTRY_E3: // Rocket Soldier
            switch (house) {
                case HOUSE_GOOD: return INFANTRY_E2; // Grenadier
                case HOUSE_BAD: return INFANTRY_E3; // Rocket Soldier
                default: return infantry;
            }
        case INFANTRY_E4: // Flamethrower
            switch (house) {
                case HOUSE_GOOD: return INFANTRY_E2; // Grenadier
                case HOUSE_BAD: return INFANTRY_E4; // Flamethrower
                default: return INFANTRY_E4; // Flamethrower
            }
        case INFANTRY_E5: // Chemical Warrior
            switch (house) {
                case HOUSE_BAD: return INFANTRY_E5; // Chemical Warrior
                case HOUSE_GOOD: return INFANTRY_E2; // Grenadier
                default: return INFANTRY_E4; // Flamethrower
            }
        case INFANTRY_E7: // Engineer
            switch (house) {
                case HOUSE_GOOD: return INFANTRY_E7; // Engineer
                case HOUSE_BAD: return INFANTRY_E7; // Engineer
                default: return INFANTRY_E7; // Engineer
            }
        case INFANTRY_RAMBO:
            switch (house) {
                case HOUSE_GOOD: return INFANTRY_RAMBO;
                case HOUSE_BAD: return INFANTRY_RAMBO;
                default: return INFANTRY_RAMBO;
            }
        default: return infantry;
    }
}

UnitType RemapUnit(UnitType unit, HousesType house)
{
    switch (unit) {
        case UNIT_HTANK:
            switch (house) {
                case HOUSE_GOOD: return UNIT_HTANK;
                case HOUSE_BAD: return UNIT_FTANK;
                default: return UNIT_MTANK;
            }
        case UNIT_MTANK:
        case UNIT_LTANK:
            switch (house) {
                case HOUSE_GOOD: return UNIT_MTANK;
                case HOUSE_BAD: return UNIT_LTANK;
                default: return UNIT_MTANK;
            }
        case UNIT_STANK:
            switch (house) {
                case HOUSE_GOOD: return UNIT_MTANK;
                case HOUSE_BAD: return UNIT_STANK;
                default: return UNIT_MTANK;
            }
        case UNIT_FTANK:
            switch (house) {
                case HOUSE_GOOD: return UNIT_HTANK;
                case HOUSE_BAD: return UNIT_FTANK;
                default: return UNIT_MTANK;
            }
        case UNIT_JEEP:
        case UNIT_BUGGY:
            switch (house) {
                case HOUSE_GOOD: return UNIT_JEEP;
                case HOUSE_BAD: return UNIT_BUGGY;
                default: return UNIT_JEEP;
            }
        case UNIT_BIKE:
            switch (house) {
                case HOUSE_GOOD: return UNIT_JEEP;
                case HOUSE_BAD: return UNIT_BIKE;
                default: return UNIT_JEEP;
            }
        case UNIT_APC:
            switch (house) {
                case HOUSE_GOOD:
                case HOUSE_BAD:
                    return UNIT_APC;
                default: return UNIT_APC;
            }
        case UNIT_ARTY:
            switch (house) {
                case HOUSE_GOOD: return UNIT_MSAM;
                case HOUSE_BAD: return UNIT_ARTY;
                default: return UNIT_ARTY;
            }
        case UNIT_MLRS:
        case UNIT_MSAM:
            switch (house) {
                case HOUSE_GOOD: return UNIT_MSAM;
                case HOUSE_BAD: return UNIT_MLRS;
                default: return unit;
            }
        case UNIT_HARVESTER:
            switch (house) {
                case HOUSE_GOOD: return UNIT_HARVESTER;
                case HOUSE_BAD: return UNIT_HARVESTER;
                default: return UNIT_HARVESTER;
            }
        case UNIT_MCV:
            switch (house) {
                case HOUSE_GOOD: return UNIT_MCV;
                case HOUSE_BAD: return UNIT_MCV;
                default: return UNIT_MCV;
            }
        default: return unit;
    }
}

AircraftType RemapAircraft(AircraftType aircraft, HousesType house)
{
    switch (aircraft) {
        case AIRCRAFT_TRANSPORT:
            switch (house) {
                case HOUSE_GOOD: return AIRCRAFT_TRANSPORT;
                case HOUSE_BAD: return AIRCRAFT_TRANSPORT;
                default: return AIRCRAFT_TRANSPORT;
            }
        case AIRCRAFT_HELICOPTER:
        case AIRCRAFT_ORCA:
            switch (house) {
                case HOUSE_GOOD: return AIRCRAFT_HELICOPTER;
                case HOUSE_BAD: return AIRCRAFT_ORCA;
                default: return AIRCRAFT_HELICOPTER;
            }
        default: return aircraft;
    }
}

HousesType RemapHouse(HousesType house)
{
    switch (house) {
        case HOUSE_GOOD: return Options.ActLikeOverrideGDI;
        case HOUSE_BAD: return Options.ActLikeOverrideNod;
        default: return house;
    }
}

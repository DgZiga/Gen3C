# [FR] Chill system
These changes override the normal "Freeze" status in a Pokemon FireRed ROM.

## Installation

### Requirements
The installation of this change requires:
- Python 3.8+
- armips (only tested with v0.11.0)
- The devkitPro devkitARM toolchain
- A legally acquired Pokemon FireRed USA v1.0 (BPRE) ROM

### Compatibility
Compatible with Physical/Special split by DoesntKnowHowToPlay and Dreamaker

### Usage
Put the original ROM in the root folder, and name it "BPRE0". This file will not be modified. \
Pick out some free space (the compiled code is about 110 bytes long) and note down the address. \
From the root directory, run `python scripts/build.py ADDRESS`, where `ADDRESS` is the address you noted down in the last step. \
Both a `multi.gba` and a `symbols.txt` file will appear. \
`multi.gba` is the modified ROM, and `symbols.txt` is a summary of where exactly in the ROM everything has been inserted. Keep a copy of boh. 

## Contents

### New Effects of Freeze
The old turn-skipping freeze has been removed. In its place, freeze now acts as a counterpart to the Burn status, by:
- Halving the Special Attack stat of the pokemon inflicted with it
- Inflicting 1/16th of the total pokemon's health of damage at the end of each turn

### Side Effects
Since the routine that inflicts damage at the end of each turn is the exact same one as the one the "Burn" effect uses, the text has been changed to a more generic one. 

## Technical Details

The changes are made in four key points:
- A first hook at 0x0803ED76 (when the attacking pokémon special attack is first loaded) enables us to check for the status condition and cut the stat in half if needed
- A second hook at 0x0801950A (when the game chooses wether or not to thaw the pokemon out) enables us to remove this feature.
- A third hook at 0x08018552 (when the game checks wether or not the pokemon has the Burn status at the end of the turn) enables us to use the exact same code of the Burn status effect for freeze. A nice coincidence is that the graphics and the sound played actually mirror the status without any need for intervention
- A fourth hook at 0x083FDFCC just changes the "PKMN is hurt by its burn!" to "PKMN is hurt by its status condition!" as a side-effect of the third hook.

## Credits
The build script is a modified version of an old FBI's script. \
You cand find the original script [here](https://github.com/EternalCode/Empty-Template/blob/master/Sample%20Project/scripts/build2)
# Ideas Scratchpad
An overview for the main parts of the game.

## Game Design
General ideas for the game, ranging from combat to the story.

### Story
TODO

### Combat
TODO: Polish and add as necessary

N.B. For the combat section, unless otherwise specified, (parentheses) will
indicate a submenu, and [square brackets] will indicate extra information.

Combat in [Some Game] will be semi-turn based. All battle actions will take time
to perform, which means each combatant will not necessarily have the same number
of turns in a battle. However, when a character is ready to perform an action,
time will freeze until the action is chosen.

Options in combat:
Attack (Physical ([List of physical attacks]), Magical ([List of magic attacks]),
   Special [Displays as Speical: SpecialName])
Defend (Defend [Basic defense], [List of defense skills])
Item ([List of combat items])
Misc/Other [Name pending] (Wait [Character does nothing until a button is
   pushed [increased stamina regen]], [Other misc skills])
Escape/Run/Flee [Name pending]

#### Attacking
TODO: Polish and add as necessary
Attacking is the main way of dealing damage in [Some Game]. Every attack will
have a charge time, recovery time, and a cooldown time.

Charge time determines how long the character will need to wait to perform an
action after selecting it. Each action will have a specific charge time that
will be noted in the overworld menu. Inside battle, however, charge time will be
listed as **instantaneous**, **short**, **medium**, **long**, or **very long**.
These descriptions correspond to the following time ranges:
- **Instantaneous**: 0 seconds
- **Short**: 0-3 seconds
- **Medium**: 3-6 seconds
- **Long**: 6-9 seconds
- **Very Long**: 9+ seconds

Recovery time determines how long the character will need to wait after an
action is completed to perform a new action. Recovery time is measured in
essentially the same way as charge time [specific when viewed from overworld,
simplified when displayed in battle], with the only exception being that there
is no instantaneous speed for recovery. The recovery times are as follows:
- **Short**: 0-2 seconds
- **Medium**: 2-4 seconds
- **Long**: 4-6 seconds
- **Very long**: 6+ seconds

Cooldown time is how long the character must wait before using an ability again.
For most abilities, cooldown time is shorter than the recovery time, making it
essentially meaningless. However, for some powerful abilities, the cooldown time
will be longer than the recovery time, making the ability unusable for some
time. Unlike charge time and recovery time, the specific time will be indicated
in battle. No cooldown will be displayed for abilities that have recovery times
longer than their cooldown time. [Some perks may reduce recovery time - this
will be taken into account when deciding whether or not cooldown time will be
displayed] [The *Instant Recover* [Name pending] perk will not necessarily
display the cooldown time because it is used after the skill has been used, not
before]

##### Types of attack
TODO: Pretty much everything, espeically formatting
The two main types of attack for the game will be physical, and magical. 
Idea for combat: stamina bar, different levels of stamina needed for different
attacks (more for physical, less for magic [magic would still require some,
however])
Stamina gradually replenishes, but attacks can be used without enough stamina,
with an additional hp cost based on missing stamina (might be % based, or based
on stamina values directly, not sure yet)

### Overworld
TODO

### Ideas taken from Fallout 4
1. NPC dialogues change depending on the armour I'm wearing (vault suit,
   power armour, or running around naked).
2. NPC dialogues change after some missions (e.x. I saw some
   dude painting a wall and helped him, then other NPCs told me
   that the wall looked good and that I did a good job).
3. ~~Multiple factions to join/endings to achieve.~~
4. ~~I can have companions follow me around (like a dog or actual people)
   depending on what I do (kill factions they like/hate, find stuff, or
   lockpick/pickpocket in front of them) they start to like me more/less
   and possibly give me stuff.~~

## Program

### Threads
The program will have 5 threads in total:
1. Heavy backend work 1
  - **attempt to share as much load with thread 2 as possible - ~50% each**
2. Heavy backend work 2
3. Main interface
  - hanles displaying stuff/getting input from user
4. Broadcast
  - will send player info to ally(s)
  - Protocols [subject to change]
    - If 1 ally only - use TCP
    - ~~if multiple are possible - use UDP~~
5. Receive
  - Will get ally(s) info and update their local info

### Intrenal Representation
sf::Image with all tiles will be stored in the map object
Tiles will store 2 sf::Texture vars

## Files

### Save Files
TODO

### Map Files
TODO

### File/character Files
TODO

### Other
Anything I missed?

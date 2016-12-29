# Ideas Scratchpad
A place to put diffrent ideas for the game (mainly relating to the story).

## Story

### Ideas taken from Fallout 4
1. NPC dialogues change depending on the armour I'm wearing (vault suit,
   power armour, or running around naked).
2. NPC dialogues change after some missions (e.x. I saw some
   dude painting a wall and helped him, then other NPCs told me
   that the wall looked good and that I did a good job).
3. Multiple factions to join/endings to achieve.
4. I can have companions follow me around (like a dog or actual people)
   depending on what I do (kill factions they like/hate, find stuff, or
   lockpick/pickpocket in front of them) they start to like me more/less
   and possibly give me stuff.

## Program

### Treads
The program will have 5 threads in total:
1. Heavy backend work 1
  - **attempt to share as much load with thread 2 as possible - ~50%**
2. Heavy backend work 2
3. Main interface
  - hanles displaying stuff/getting input from user
4. Broadcast
  - will send player info to ally(s)
  - Protacols [subject to change]
    - If 1 ally only - use TCP
    - if multiple are possible - use UDP
5. Recive
  - Will get ally(s) info and update their local info

## Files

### Save Files
TODO

### Map Files
TODO

### File/character Files
TODO

### Other
Anything I missed?

# Game design  

Levels are generated proceduraly.  

Combats are 'turn based', the player need to make contact with an enemy to deal his contact damage.  
Moves are only horiwontal and verticalm, no diagonal.  

Caracteristics:
- Health  
- Damage  
- Defence  
- Keys  

# Combat system  

Once the player move to a tile containing an enemy, the following appends:  
- Character hit the moster with his attack value.  
- Monster reduce this by his defence amount.  
- If still alive, do the same to the player.  

# Game Development with Allegro Framework - 86－Eighty Six
This is the final project on text mining class(Course code：10920CS135500) at National Tsing Hua University. I used **C++** to design a game using allegro framework. This game is inspired by my favorite animation, 86―エイティシックス― 

## Game story background
The Republic of San Magnolia suffers from aggression by drone "legions" from neighboring countries every day.
Fortunately, the Republic has also successfully developed the same type of weapon "God of Destruction" to deal with its offensive, and barely defuses threats from neighboring countries without casualties on the surface.
Officials of the Republic claimed to its citizens that there were no casualties, but in reality, there were not zero casualties. Because in the "non-existent 86th district" outside of the 85 administrative districts of the United States, a group of young girls is fighting tirelessly day and night with "manned drones." Xin, who led a group of young people born and died, and the commander Reina, who is in the far rear, commanding them through special communications, will protect the safety of the team members and the Republic.

   ![擷取2](https://user-images.githubusercontent.com/84038124/136113371-1c9c71cf-f43f-494c-9050-372c84dc5e4b.PNG)

## The basic structure of the game
- Main menu: Start/About/Exit

   ![擷取1](https://user-images.githubusercontent.com/84038124/136113349-41264703-6134-4b5a-a628-e1eedb0b1fb3.PNG) 

- The main screen of the game: the player drives the "God of Destruction" fighter against the enemy army. The artillery fired by the enemy must be avoided and the enemy army must also be prevented from entering our territory.

   ![擷取3](https://user-images.githubusercontent.com/84038124/136113379-e05c9dfb-3803-470c-ad7b-416ed4c9d60d.PNG)
   
- Conditions for triggering victory: The player can win after repelling a certain number of enemies, and the victory screen will be presented.

   ![擷取6](https://user-images.githubusercontent.com/84038124/136113403-852836f6-867c-4f6b-b9ad-4b7371646cc2.PNG)

- Conditions for trigger failure:
  - When an enemy touches our territory, the game ends and a victory screen is presented.
  - If the player is attacked, the confidence will be weakened. When the player is attacked five times, he will immediately die. The failure screen will be present.

   ![擷取5](https://user-images.githubusercontent.com/84038124/136113392-bef343e3-32f6-4b29-a8f9-24a7ed64ce6a.PNG)
   ![擷取4](https://user-images.githubusercontent.com/84038124/136113389-18288f00-1c08-451f-8bd2-d41ca14b3b76.PNG)

## Other basic units
- Role: The player is Xin who is driving the "God of Destruction", and the enemy is a random army.
- Weapons: The player will launch bullets to destroy the enemy, and the enemy will also launch attacks.
- Counting tool: Two Counting tools, one is the team confidence value (five grids), the player will disappear one grid after being attacked. The other is the number of enemies being destroyed.

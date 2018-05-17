Start all pertinent data with a > and end it with a new line.

For character files fill out the lines in this order:
>Name of the image file used by the character
>Move speed of character
>Number of consecutive jumps a character can do
>Height of jumps
>Folder and file for basic melee attack
>Folder and file for sideways melee attack
>Folder and file for upwards melee attack
>Folder and file for down melee attack
>Folder and file for basic special attack
>Folder and file for sideways special attack
>Folder and file for upwards special attack
>Folder and file for down special attack

For ranged and melee attacks fill out the lines in this order:
>what they are destroyed on hitting (anything, player or nothing)
>the hold value (see note below)
>the time until the move despawns
>the speed at which the attack moves
>the damage the attack does
>the knockback of the attack
>the x direction of the projectile/attack collider
>the y direction of the projectile/attack collider
>the x size of the projectile/attack collider
>the y size of the projectile/attack collider
>whether the projectile is affected by gravity (true, false)

note below:
	- a positive value in the hold value is a charge attack,
	the number relating to how long the attack can be charged for
	- a negative value in the hold value is a spam attack,
	holding the button will spam this attack, the number is the rate at which the attack is used
	- a value of 0 will neither be charged nor spammed

For dash attacks fill out the lines in this order:
>what the projectile is destroyed on hitting (anything, player or nothing)
>the time until the projectile despawns
>the speed at which the projectile moves
>the damage the projectile does
>the knockback of the projectil
>the x direction of the projectile
>the y direction of the projectile
>the x size of the projectile
>the y size of the projectile
>the x direction the player will move
>the y direction the player will move
>the force with which the player will move
>whether the projectile is affected by gravity (true, false)
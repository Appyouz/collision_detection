# 2D Collision Detection Project

The provided code implements Axis-Aligned Bounding Box (AABB) collision detection for a 2D game. This type of collision detection uses rectangles to represent the colliders (player and obstacle in this case) and checks for overlaps between these rectangles to determine if a collision has occurred.

#### Collision Detection Process:

1. **Checking for Overlap:**

    The code checks if the player's rectangle overlaps with the obstacle's rectangle using four conditions:
   
   - `player.x < obstacle.x + obstacle.w`: Checks if the player's left edge is to the left of the obstacle's right edge.
   - `player.x + player.w > obstacle.x`: Checks if the player's right edge is to the right of the obstacle's left edge.
   - `player.y < obstacle.y + obstacle.h`: Checks if the player's top edge is above the obstacle's bottom edge.
   - `player.y + player.h > obstacle.y`: Checks if the player's bottom edge is below the obstacle's top edge.

2. **Calculating Overlap Values:**

    If an overlap is detected, the code calculates the amount of overlap along the X-axis (`overlapX`) and Y-axis (`overlapY`).
   
   - `overlapX`: This is calculated by finding the minimum distance between the right edges of the player and the obstacle, and subtracting the maximum distance between their left edges.
   - `overlapY`: This is calculated similarly, using the minimum distance between the bottom edges and the maximum distance between the top edges.

3. **Resolving Collision:**

    The code compares `overlapX` and `overlapY` to determine which axis has a smaller overlap. It then prioritizes resolving the collision along the axis with the smaller overlap to minimize the overall movement required to push the player out of the overlap.
   
   - **X-axis collision:** If `overlapX` is smaller, the code checks the player's movement direction (`playerRight < obstacleRight`) and pushes the player by the `overlapX` amount in the appropriate direction (left or right) to resolve the overlap.
   - **Y-axis collision:** If `overlapY` is smaller, the code checks the relative vertical positions (`playerBottom < obstacleBottom`) and pushes the player by the `overlapY` amount upwards or downwards to resolve the overlap.

#### Summary:

This code snippet utilizes AABB collision detection to identify and resolve collisions between the player and the obstacle in a 2D game environment. It prioritizes resolving the axis with the smallest overlap for smoother and more efficient collision handling.

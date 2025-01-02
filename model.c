// This file is going to have all the important function that are going to be implemented in the main.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// The loop in this function ensures that vehicle is getting a random position on road and is getting a random speed
void initialize_vehicles(int vehicles[], int speeds[], int road_length, int max_speed) 
{
    srand(time(NULL)); // ensures that we are getting a random number 
    for (int i = 0; i < 20; i++) 
    {
        vehicles[i] = rand() % road_length; //% road_length part ensures that the random number is below the max vehicles
        speeds[i] = rand() % max_speed; //% speed_max part ensures that the random number is below the max_speed
    }
}

void update_vehicles(int vehicles[], int speeds[], int road_length, int max_speed, int time_step) 
{
    for (int i = 0; i < 20; i++)
    {
        int density = (20 * 1000) / road_length;
        int acceleration = (10 - density) * 10;

        if (acceleration <= 0)
        {
            // Set the acceleration to be zero so that the acceleration dont become negative
            acceleration = 0;
        }

        // Upadte the speed by adding the acceleration to it
        speeds[i] += acceleration;

        // if speed is above the maximum limit than dont add any acceleration just keep it to be the max speed
        if (speeds[i] > max_speed) {
            speeds[i] = max_speed; 
        }

        // calculates how much distance it will travel in that time by that updated speed
        vehicles[i] += (speeds[i] * time_step) / 1000; 
        // ensures that the position is within the road length
        vehicles[i] = vehicles[i] % road_length;
    }
}

int calculate_traffic_flow(int vehicles[], int speeds[], int road_length, int time_step) {
    int count = 0; 
    int fixed_point = road_length / 2; // Choose a fixed point in the middle of the road

    for (int i = 0; i < 20; i++) {
        int new_position = vehicles[i] + (speeds[i] * time_step) / 1000;
        new_position %= road_length; // Ensure the new position is within the road bounds

        if (vehicles[i] < fixed_point && new_position >= fixed_point) { 
            count++; 
        }
    }

    return count;
}
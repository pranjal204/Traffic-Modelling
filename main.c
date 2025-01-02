#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int NUM_VEHICLES = 20;

// Function prototypes
void initialize_vehicles(int vehicles[], int speeds[], int road_length, int max_speed);
void update_vehicles(int vehicles[], int speeds[], int road_length, int time_step);
int calculate_traffic_flow(int vehicles[], int prev_vehicles[], int road_length);

int main(void)
{
    // Define constants for the simulation
    const int road_length = 5000; // Length of the road in meters
    const int time_step = 100;   // Time step in milliseconds
    const int max_speed = 1000; // Maximum vehicle speed in m/s

    // Declare arrays to store vehicle positions and speeds
    int vehicles[NUM_VEHICLES];
    int speeds[NUM_VEHICLES];
    int prev_vehicles[NUM_VEHICLES]; // Store previous positions for flow calculation

    // Initialize vehicle positions and speeds
    initialize_vehicles(vehicles, speeds, road_length, max_speed);

    // Copy initial positions to prev_vehicles
    for (int i = 0; i < NUM_VEHICLES; i++)
    {
        prev_vehicles[i] = vehicles[i];
    }

    // Print initial positions and speeds
    printf("Initial Positions and Speeds:\n");
    for (int i = 0; i < NUM_VEHICLES; i++)
    {
        printf("Vehicle %d: Position = %d, Speed = %d\n", i + 1, vehicles[i], speeds[i]);
    }

    int total_flow = 0; // Track total number of vehicles crossing the fixed point

    // Run the simulation for 10,000 milliseconds
    for (int time = 0; time < 10000; time += time_step)
    {
        update_vehicles(vehicles, speeds, road_length, time_step);
        int flow = calculate_traffic_flow(vehicles, prev_vehicles, road_length);
        total_flow += flow;

        // Update previous positions for the next iteration
        for (int i = 0; i < NUM_VEHICLES; i++)
        {
            prev_vehicles[i] = vehicles[i];
        }

    }

    // Print the total traffic flow
    printf("\nTotal Traffic Flow: %d vehicles\n", total_flow);

    // Print final positions and speeds
    printf("\nFinal Positions and Speeds:\n");
    for (int i = 0; i < NUM_VEHICLES; i++)
    {
        printf("Vehicle %d: Position = %d, Speed = %d\n", i + 1, vehicles[i], speeds[i]);
    }

    return 0;
}

// Function to initialize vehicle positions and speeds
void initialize_vehicles(int vehicles[], int speeds[], int road_length, int max_speed)
{
    srand(time(NULL)); // Seeds a random number 
    for (int i = 0; i < NUM_VEHICLES; i++)
    {
        vehicles[i] = rand() % road_length; // Random position on the road
        speeds[i] = rand() % (max_speed / 2) + 1; // Random speed between 1 and half of max_speed
    }
}

// Function to update vehicle positions and speeds
void update_vehicles(int vehicles[], int speeds[], int road_length, int time_step)
{
    for (int i = 0; i < NUM_VEHICLES; i++)
    {
        vehicles[i] = (vehicles[i] + (speeds[i] * time_step) / 1000) % road_length; // Update position
    }
}

// Function to calculate traffic flow
int calculate_traffic_flow(int vehicles[], int prev_vehicles[], int road_length)
{
    int flow = 0;
    int fixed_point = road_length / 2; // Fixed point in the middle of the road

    for (int i = 0; i < NUM_VEHICLES; i++)
    {
        // Check if a vehicle has crossed the fixed point
        if (prev_vehicles[i] < fixed_point && vehicles[i] >= fixed_point)
        {
            flow++;
        }
    }

    return flow;
}

#include <iostream>
using namespace std;

// Function to calculate turnaround time, waiting time, and display average times
void calculate_times(int p[], int AT[], int BT[], int n);

// Function to find the next process with the shortest burst time
int find_next_process(int AT[], int BT[], bool completed[], int time, int n);

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    int p[n], AT[n], BT[n];

    // Input for process details
    for (int i = 0; i < n; i++)
    {
        cout << "Enter process no, arrival time and burst time: ";
        cin >> p[i] >> AT[i] >> BT[i];
    }

    // Calculate turnaround time and waiting time using SJF
    calculate_times(p, AT, BT, n);
    return 0;
}

// Function to find the next process with the shortest burst time
int find_next_process(int AT[], int BT[], bool completed[], int time, int n)
{
    int shortest_process = -1;
    int min_burst = 99999; // Manually set a large value to simulate infinity

    for (int i = 0; i < n; i++)
    {
        // Check if the process has arrived and is not yet completed
        if (AT[i] <= time && !completed[i])
        {
            // Check for the shortest job
            if (BT[i] < min_burst)
            {
                min_burst = BT[i];
                shortest_process = i;
            }
            // If burst times are equal, select the process with the earlier arrival time
            else if (BT[i] == min_burst)
            {
                if (AT[i] < AT[shortest_process]) // Prioritize by earlier arrival time
                {
                    shortest_process = i;
                }
            }
        }
    }
    return shortest_process;
}

// Calculate turnaround time, waiting time, and display average times
void calculate_times(int p[], int AT[], int BT[], int n)
{
    int WTime[n], TATime[n], exitTime[n], currentTime = 0;
    bool completed[n] = {0}; // Array to mark completed processes
    int completed_processes = 0, sumTAT = 0, sumWT = 0;

    cout << "\nGantt Chart: ";

    // Execute until all processes are completed
    while (completed_processes < n)
    {
        int process_index = find_next_process(AT, BT, completed, currentTime, n);

        // If no process is available at the current time, increment time
        if (process_index == -1)
        {
            currentTime++;
            continue;
        }

        // Execute the shortest job
        currentTime += BT[process_index];
        exitTime[process_index] = currentTime;

        TATime[process_index] = exitTime[process_index] - AT[process_index]; // Turnaround Time
        WTime[process_index] = TATime[process_index] - BT[process_index];    // Waiting Time

        // Mark the process as completed
        completed[process_index] = true;
        completed_processes++;

        // Display Gantt Chart
        cout << "p" << p[process_index] << " ";

        // Sum up turnaround and waiting times
        sumTAT += TATime[process_index];
        sumWT += WTime[process_index];
    }

    // Calculate and display the average times
    double avg_TAT = (double)sumTAT / n;
    double avg_WT = (double)sumWT / n;

    cout << "\n\nProcess-wise Turnaround and Waiting Times:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << p[i] << ": Turnaround Time = " << TATime[i]
             << ", Waiting Time = " << WTime[i] << endl;
    }

    cout << "\nAverage Turnaround Time: " << avg_TAT << endl;
    cout << "Average Waiting Time: " << avg_WT << endl;
}

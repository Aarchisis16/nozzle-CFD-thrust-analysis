#include <iostream>
using namespace std;
#include <fstream> 


int main(){
    double fuel_mass; // FUEL MASS: Total amount of fuel available to burn.
    double burn_time; // BURN TIME: How long the engine is firing.
    double exit_pressure; // EXIT PRESSURE: Pressure of gas leaving the nozzel.
    double ambient_pressure; // AMBIENT PRESSURE: Pressure of surrounding enviornment (air outside).
    double exit_area;
    double exhaust_velocity;

    ofstream file("data.csv", ios::app);
    //file << "AmbientPressure,Fuel,BurnTime,ExhaustVelocity,Thrust,Isp\n";


    cout<<"=== ROCKET ENGINE==="<<endl;

    cout<<"Enter fuel mass (Kg) : ";
    cin>>fuel_mass;

    cout<<"Enter exit pressure (Pa) : ";
    cin>>exit_pressure;

    cout<<"Enter ambient pressure (Pa) : ";
    cin>>ambient_pressure;

    cout<<"Enter exit area (m^2) : ";
    cin>>exit_area;

    cout << "Enter exhaust velocity from CFD (m/s): ";
    cin >> exhaust_velocity;

        
    cout<<"\n---INPUTS RECORDED---\n";

    cout<<"Fuel Mass : "<<fuel_mass<<" Kg"<<endl;
    cout<<"Exit Pressure : "<<exit_pressure<<" Pa"<<endl;
    cout<<"Ambient Pressure : "<<ambient_pressure<<" Pa"<<endl;
    cout<<"Exit Area : "<<exit_area<<" m^2"<<endl;
    cout << "Exhaust Velocity (CFD): " << exhaust_velocity << " m/s\n";
 

    int choice;
    cout<<"\nSELECT FUEL:\n";
    cout<<"1. RP-1 (Kerosene)\n";
    cout<<"2. LH2 (Hydrogen)\n";
    cout<<"Enter your choice : ";
    cin>>choice;

    string fuel_type;
    if (choice == 1) fuel_type = "RP-1";
    else if (choice == 2) fuel_type = "LH2";
    else fuel_type = "Default";

    double efficiency;

    if(choice == 1) efficiency = 0.9;     // RP-1
    else if(choice == 2) efficiency = 1.2; // LH2
    else efficiency = 1.0;

    cout<<"\n---SIMULATION RUNNING---\n";

    double max_thrust = 0;

    for(int i = 1; i <= 10; i++){
        burn_time = i*20;

        double mass_flow_rate = fuel_mass / burn_time;

        double thrust = efficiency * (mass_flow_rate * exhaust_velocity + (exit_pressure - ambient_pressure) * exit_area);
        
        double isp = exhaust_velocity / 9.81; // F= (m˙)⋅Ve​ => F/(m˙)⋅g = Vex / g ===> Isp = F/(m˙)⋅g = Vex / g

        cout<<"\nBurn Time : "<<burn_time<<" s"<<endl;
        cout<<"\nMass Flow Rate : "<<mass_flow_rate<<" Kg/s"<<endl;
        cout<<"\nThrust : "<<thrust<<" N"<<endl;
        cout<<"\nIsp : "<<isp<<" s"<<endl;


        // Tracking max thrust
        if (thrust > max_thrust) {
            max_thrust = thrust;
        }

        file << ambient_pressure << ","
             << fuel_type << ","
             << burn_time << ","
             << exhaust_velocity << ","
             << thrust << ","
             << isp << "\n";
        }

    file.close();

    cout << "\nMax Thrust Achieved: " << max_thrust << " N" << endl;
    cout<<"\nData exported to data.csv successfully!"<<endl;
    
    return 0;
}
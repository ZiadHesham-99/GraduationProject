# Unity Subsystem

## Introduction

The Unity subsystem of the Fire Inspection Rover project is a critical component that provides an immersive and realistic training environment for firefighters. Through this Unity-based simulator, firefighters can practice and enhance their firefighting skills, making them better equipped to handle various fire scenarios effectively.

## Objectives

The Unity subsystem aims to achieve the following objectives:

- **Realistic Training:** Create a lifelike and interactive simulation environment that closely resembles real-world fire incidents, allowing firefighters to gain practical experience without exposing them to actual danger.

- **Scenario Diversity:** Develop a wide range of simulated fire scenarios, including different building layouts, fire intensities, and environmental challenges, to prepare firefighters for various emergency situations.

- **Skill Evaluation:** Implement data collection mechanisms to record firefighter interactions and decisions during training sessions, enabling detailed performance evaluation and feedback.

- **Multi-Agent:** Simulate Multi-Agent robots communication and Task allocation .

## Class Diagram
![unityClassDiagram](https://github.com/ZiadHesham-99/GraduationProject/assets/76854651/7edafd14-24db-4011-ad53-629b122308cd)

## Environment

The Unity simulator uses the "Industrial Train Station / Train Yard" environment asset from Unity Assets to create a realistic training setting. This environment provides diverse spaces and structures to simulate fire incidents in industrial settings and train yards.

## Results

video of Rover navigatting and mappig the Environemnet on unity : https://drive.google.com/file/d/1FxXOahsNC5wLGMuEZWD99Ber05auFXUF/view?usp=sharing

![unity1](https://github.com/ZiadHesham-99/GraduationProject/assets/76854651/a0368134-bbf1-4665-8b1f-be10646ad9fe)
![unity2](https://github.com/ZiadHesham-99/GraduationProject/assets/76854651/dca4dbb7-3677-41f8-8610-7d4d6eff5981)
![unity3](https://github.com/ZiadHesham-99/GraduationProject/assets/76854651/930f7de7-51aa-49fb-a6a3-510dd644cdce)
![unity4](https://github.com/ZiadHesham-99/GraduationProject/assets/76854651/b6d0714a-415a-4d43-aece-dff577880f4c)
![unity5](https://github.com/ZiadHesham-99/GraduationProject/assets/76854651/bdfe66dd-e7b7-4503-9950-72596c3af2d9)
![unity6](https://github.com/ZiadHesham-99/GraduationProject/assets/76854651/bca0b497-56ee-4fe6-9e72-dd6e9c42a077)



## Used Packages

The Unity subsystem relies on the following Unity packages to enable its functionality:

1. [URDF Importer]([link_to_urdf_importer_package_here](https://github.com/Unity-Technologies/URDF-Importer)) from Unity Robotics Technologies: Allows importing and working with Universal Robot Description Format (URDF) files for robot visualization and interaction.

2. [Unity ROS TCP Connector]([link_to_unity_ros_tcp_connector_package_here](https://github.com/Unity-Technologies/ROS-TCP-Connector)) from Unity Robotics Technologies: Facilitates communication between Unity and the Robot Operating System (ROS) through TCP.

3. [Environment Asset - Industrial Train Station / Train Yard]([link_to_environment_asset_here](https://assetstore.unity.com/packages/3d/environments/industrial/industrial-train-station-train-yard-1934)) from Unity Assets: Provides the realistic environment for simulating fire incidents in industrial settings and train yards.

4. [Realistic Fire VFX v3.6]([link_to_realistic_fire_vfx_package_here](https://assetstore.unity.com/packages/vfx/particles/fire-explosions/realistic-fire-vfx-54494)) from Unity Assets: Adds high-quality and realistic fire visual effects to enhance the simulation's realism.


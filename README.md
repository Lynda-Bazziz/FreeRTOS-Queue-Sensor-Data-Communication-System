# FreeRTOS-Queue-Sensor-Data-Communication-System

Description
This project demonstrates how to use a **FreeRTOS queue** to transfer data between multiple producer tasks (simulated sensors) and a consumer task (monitor).

Key Concepts
- FreeRTOS Tasks
- Queue (xQueueCreate, xQueueSend, xQueueReceive)
- Inter-task communication
- Struct-based messaging

System Architecture

 Producers
- `tacheTemp` → temperature sensor
- `tacheHum` → humidity sensor
- `tacheQual` → air quality sensor

 Consumer
- `tacheMonitor` receives and processes data

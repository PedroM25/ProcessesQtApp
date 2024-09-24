# Processes-Qt-App

### Functional features of this app:
- See the PID, User and command of all running processes in a system
- Kill a process
- Filter processes live, as the user types

### Design features of this app:
- Model View Controller architecture
    - **View**: one implementation featuring Qt5
    - **Model**: one implementation that supports Unix-based systems (no implementation for Windows)
- A seperate thread is in charge of fetching all running processes every 1s.
- To avoid overloading the UI, a diff is performed between currently displayed processes and list of processes provided by the thread.
    - Only new processes are effectively "painted" onto the UI.
- Filter functionality is tightly integrated with the thread that retrieves processes.

### Other info

- Process information for Unix-based implementation is obtained by parsing the /proc folder
- Unit tests using gtest and gmock

### Prerequisites

sudo apt install -y libgrpc++-dev protobuf-compiler-grpc libprotobuf-dev protobuf-compiler qtbase5-dev qtdeclarative5-dev

## Using the app

[app_usage.webm](https://github.com/user-attachments/assets/7f8bada9-9d7e-4e74-abd7-cd5e00198b24)

## Live process kill

[output2.webm](https://github.com/user-attachments/assets/d3056bdf-c66f-4d70-858d-bc04748eae1d)

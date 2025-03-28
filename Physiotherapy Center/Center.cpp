#include "Center.h"

Center::Center() {}

Center::~Center() {}

void Center::AddResource(Resource* res, char type) {
    if (type == 'E') {
        E_Devices.enqueue(res);
    } else if (type == 'U') {
        U_Devices.enqueue(res);
    } else if (type == 'X') {
        X_Rooms.enqueue(res);
    }
}

Resource* Center::GetNextResource(char type) {
    Resource* res = nullptr;
    if (type == 'E' && !E_Devices.isEmpty()) {
        E_Devices.dequeue(res);
    } else if (type == 'U' && !U_Devices.isEmpty()) {
        U_Devices.dequeue(res);
    } else if (type == 'X' && !X_Rooms.isEmpty()) {
        X_Rooms.dequeue(res);
    }
    return res;
}

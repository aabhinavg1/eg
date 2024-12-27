#include <iostream>
#include "Subscriber.h"

int main() {
    Subscriber subscriber("Alice");
    subscriber.subscribe("Tech");
    subscriber.subscribe("Sports");

    std::cout << "Subscriptions for Alice:\n";
    for (const auto& topic : subscriber.getSubscriptions()) {
        std::cout << "- " << topic << "\n";
    }

    return 0;
}

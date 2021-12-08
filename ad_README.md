# TODO
- No "GameThread" anymore, we are switching to single instance persisent world
- make the server authoritative
- Engine: Improve rendering/input backend abtraction, we might move away from sfml at some point
- Server:
    - move into Engine any socket based logic as a framework on its own
    - add support for a mySQL database for world persistence & user accounts

- Client/Server: remove & replace lobby system with a login system

# TODO Engine


# Remarks

# Notes
git submodule update --force --init --remote

cmake build static libraries:
https://cmake.org/cmake/help/latest/guide/tutorial/Selecting%20Static%20or%20Shared%20Libraries.html
https://code.austinmorlan.com/austin/ecs/src/branch/master/Source/Core/Event.hpp

# Server Issues


---
## Thread workers example & mutex
https://en.cppreference.com/w/cpp/thread/mutex

    std::vector<std::thread> workers;

    for (int i = 0; i < 5; i++) {
        workers.push_back(std::thread([]()
        {
            std::cout << "thread function\n";
        }));
    }

    std::for_each(workers.begin(), workers.end(), [](std::thread &t)
    {
        t.join();
    });

# Network spoofing
https://www.netresec.com/index.ashx?page=RawCap

- sequence diagram

# UDP
- Delivery of any given datagram is not guaranteed. Any datagram may be lost at any time.
- Order of delivery is not guaranteed. Datagrams are not necessarily received in the same order in which they were sent.
- Uniqueness of delivery is not guaranteed. Any given datagram may be delivered more than once.

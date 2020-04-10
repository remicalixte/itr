#include <vector>
#include <memory>
#include "ActiveCalc.h"
#include "Client.h"

int main()
{
    ActiveCalc activeCalc;
    std::vector<std::unique_ptr<Client>> clients(10);

    double seed = 2;
    for (auto &client : clients)
    {
        client.reset(new Client(seed, &activeCalc));
        seed *= 2;
    };

    // start active calc
    activeCalc.start();

    // start clients
    for (auto &client : clients)
    {
        client->start();
    }
    for (auto &client : clients)
    {
        client->join();
    }

    return 0;
}

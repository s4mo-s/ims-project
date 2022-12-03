/**
 * IMS project - Theme 1: Electro-energetics
 *
 * Authors:
 *      Samuel Šulo <xsulos00@stud.fit.vutbr.cz>
 *      Samuel Sadlek <xsadle01@stud.fit.vutbr.cz>
 */

#include <iostream>
#include <cstdlib>
#include <getopt.h>
using namespace std;

int main(int argc, char *argv[])
{
    double elePricePerYear = 350; // euro
    int panelPricePer1kWh = 100; // euro
    double emissionProductionPerKWh = 133; // g


    double panels;
    int usage;
    int years = 1;
    double profit = 0;
    double energyWith = 0;
    double energyWithout = 0;
    double energySaved = 0;
    bool energyCrisisChance;
    bool isCrisis = false;
    int numberOfCrisis = 0;
    srand(time(nullptr));

    int opt;
    const char *short_options = "u:p:y:";
    struct option long_options[] = {
            {"usage", required_argument, nullptr, 'u'},
            {"panels", required_argument, nullptr, 'p'},
            {"years", required_argument, nullptr, 'y'},
            {nullptr, 0, nullptr, 0},
    };

    while ((opt = getopt_long(argc, argv, short_options, long_options, nullptr)) != -1)
        switch (opt)
        {
            case 'u':
                usage = stoi(optarg);
                break;

            case 'p':
                panels = stoi(optarg);
                break;

            case 'y':
                years = stoi(optarg);
                break;

            case 'h':
            case '?':
            default :
                cerr << "Arguments: \n"
                     << "\t-u or --usage for average household consumption per year in (MWh)\n"
                     << "\t-p or --panels \n"
                     << "\t-y or --years\n";
                return EXIT_FAILURE;
        }

    cout << "-----------------------------------------------------------------------\n"
         << "SIMULATION START\n"
         << "-----------------------------------------------------------------------\n"
         << "Running with " << usage << "(MWh) average household consumption per year.\n"
         << "Running with " << panels << "(kWh) panels.\n"
         << "Running in range of " << years << " years.\n"
         << "-----------------------------------------------------------------------\n"
         << endl;

    cout << "Panels bought for: " << panels * panelPricePer1kWh << "€" << endl;
    profit -= panelPricePer1kWh * panels;

    for (int i = 1; i <= years; ++i) {
        cout << "------------------------------- YEAR " << i << " -------------------------------\n";

        if (isCrisis){
            elePricePerYear -= abs(0.55*elePricePerYear);
            isCrisis = false;
        }

        energyCrisisChance = (rand() % 100) < 3;
        if(energyCrisisChance){
            elePricePerYear += abs(2.5*elePricePerYear);
            numberOfCrisis++;
            isCrisis = true;
        }
        else {
            profit += abs(elePricePerYear * (panels/1000));
        }
        elePricePerYear += 5;
        energyWithout += usage;
        energyWith += usage - panels/1000;
        energySaved += panels/1000;

        cout << "Spotreba energie:" << endl;
        cout << "\tSpotreba elektrickej energie: " << energyWithout << "(MWh)" << endl;
        cout << "\tSpotreba elektrickej energie so solárnym panelom: " << energyWith << "(MWh)" << endl;
        cout << "\tUšetrená elektrická energia: " << energySaved << "(MWh)" << endl;

        cout << "Emisie:" << endl;
        cout << "\tCO2 vyprodukované bez solárnehoho panelu: " << emissionProductionPerKWh * energyWithout << "(kg)" << endl;
        cout << "\tCO2 vyprodukované so solárnym panelom: " << emissionProductionPerKWh * energyWith << "(kg)" << endl;
        cout << "\tUšetrené škody na životnom prostredí: " << emissionProductionPerKWh * energySaved << "(kg)\n" << endl;

        cout << "Profit: " << profit << "€" << endl;
    }

    cout << "----------------------- Crisis happened " << numberOfCrisis << " times -----------------------\n";
    cout << "-----------------------------------------------------------------------\n"
         << "SIMULATION DONE\n"
         << "-----------------------------------------------------------------------\n";
    return 0;
}

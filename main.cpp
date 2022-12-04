/**
 * IMS project - Theme 1: Electro-energetics
 *
 * Authors:
 *      Samuel Šulo <xsulos00@stud.fit.vutbr.cz>
 *      Samuel Sadlek <xsadle01@stud.fit.vutbr.cz>
 */

#include <iostream>
#include <getopt.h>
using namespace std;

int main(int argc, char *argv[])
{
    double elePriceFor1MWhPerYear = 350; // euro
    double panelPriceFor1kWp = 2000; // euro

    double emissionCoalFiredPowerAndHeatingPlants = 820; // gCo2eq
    double emissionGasPower = 490;
    double emissionBiomassPower = 230;
    double emissionNuclearPower = 12;
    double emissionWaterPower = 24;
    double emissionPhotovoltaicPower = 48;
    double emissionWindPower = 11;
    double emission = 0;

    double panels = 0.0f;
    double usage = 0.0f;
    int years = 1;
    double profit = 0.0f;
    double energyWith = 0.0f;
    double energyWithout = 0.0f;
    double energySaved = 0.0f;
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
                usage = stof(optarg);
                break;

            case 'p':
                panels = stof(optarg);
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

    cout << "Panels bought for: " << panels * panelPriceFor1kWp << "€" << endl;
    profit -= panelPriceFor1kWp * panels;

    for (int i = 1; i <= years; ++i) {
        cout << "------------------------------- YEAR " << i << " -------------------------------\n";

        if (isCrisis){
            elePriceFor1MWhPerYear -= abs(0.55*elePriceFor1MWhPerYear);
            isCrisis = false;
        }

        energyCrisisChance = (rand() % 100) < 3;
        if(energyCrisisChance){
            elePriceFor1MWhPerYear += abs(2.5*elePriceFor1MWhPerYear);
            numberOfCrisis++;
            isCrisis = true;
        }
        profit += abs(elePriceFor1MWhPerYear * (panels));

        elePriceFor1MWhPerYear += 5;
        energyWithout += usage;
        energyWith += usage - panels;
        energySaved += panels;

        emission = emissionBiomassPower+emissionCoalFiredPowerAndHeatingPlants+emissionGasPower
        +emissionNuclearPower+emissionPhotovoltaicPower+emissionWaterPower+emissionWindPower;

        emission = emission/7;

        cout << "Spotreba energie:" << endl;
        printf("\tSpotreba elektrickej energie: %.1f(MWh)\n", energyWithout);
        printf("\tSpotreba elektrickej energie so solárnym panelom: %.1f(MWh)\n", energyWith);
        printf("\tUšetrená elektrická energia: %.1f(MWh)\n", energySaved);


        cout << "Emisie:" << endl;
        printf("\tCO2 vyprodukované bez solárneho panelu: %.1f(kg)\n", emission * energyWithout);
        printf("\tCO2 vyprodukované so solárneho panelu: %.1f(kg)\n", emission * energyWith);
        printf("\tUšetrené škody na životnom prostredí: %.1f(kg)\n", emission * energySaved);

        cout << "Profit: " << profit << "€" << endl;
    }

    cout << "----------------------- Crisis happened " << numberOfCrisis << " times -----------------------\n";
    cout << "-----------------------------------------------------------------------\n"
         << "SIMULATION DONE\n"
         << "-----------------------------------------------------------------------\n";
    return 0;
}

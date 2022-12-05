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

    double emission;
    double emissionWithPV;
    double emissionCoalFiredPowerAndHeatingPlants = 820; // gram
    double emissionGasPower = 490; // gram
    double emissionBiomassPower = 230; // gram
    double emissionPhotovoltaicPower = 48; // gram
    double emissionWaterPower = 24; // gram
    double emissionNuclearPower = 12; // gram
    double emissionWindPower = 11; // gram

    double usage = 0.0f;
    double power = 0.0f;
    int years = 1;
    double profit = 0.0f;
    double energyWith = 0.0f;
    double energyWithout = 0.0f;
    double energySaved = 0.0f;
    bool energyCrisisChance;
    bool isCrisis = false;
    int numberOfCrisis = 0;
    srand(time(nullptr));

    emission = emissionBiomassPower +
               emissionCoalFiredPowerAndHeatingPlants +
               emissionGasPower +
               emissionNuclearPower +
               emissionWaterPower +
               emissionWindPower;

    emissionWithPV = emissionBiomassPower +
               emissionCoalFiredPowerAndHeatingPlants +
               emissionGasPower +
               emissionNuclearPower +
               emissionWaterPower +
               emissionWindPower +
               emissionPhotovoltaicPower;

    emission = emission/6;
    emissionWithPV = emissionWithPV/7;

    int opt;
    const char *short_options = "u:p:y:";
    struct option long_options[] = {
            {"usage", required_argument, nullptr, 'u'},
            {"power", required_argument, nullptr, 'p'},
            {"years", required_argument, nullptr, 'y'},
            {nullptr, 0, nullptr, 0},
    };

    while ((opt = getopt_long(argc, argv, short_options, long_options, nullptr)) != -1)
        switch (opt)
        {
            case 'u':
                try {
                    usage = stof(optarg);
                }
                catch(const invalid_argument)
                {
                    cerr << "Wrong input, usage must be number" << '\n';
                    return EXIT_FAILURE;
                }
                catch(const out_of_range)
                {
                    cerr << "Integer overflow in usage" << '\n';
                    return EXIT_FAILURE;
                }
                if(usage <= 0)
                {
                    cerr << "Usage can't be a negative number" << '\n';
                    return EXIT_FAILURE;
                }
                break;

            case 'p':
                try {
                    power = stof(optarg);
                }
                catch(const invalid_argument)
                {
                    cerr << "Wrong input, power must be number" << '\n';
                    return EXIT_FAILURE;
                }
                catch(const out_of_range)
                {
                    cerr << "Integer overflow in power" << '\n';
                    return EXIT_FAILURE;
                }
                if(power <= 0)
                {
                    cerr << "Power can't be a negative number" << '\n';
                    return EXIT_FAILURE;
                }
                break;

            case 'y':
                try {
                    years = stoi(optarg);
                }
                catch(const invalid_argument)
                {
                    cerr << "Wrong input, years must be number" << '\n';
                    return EXIT_FAILURE;
                }
                catch(const out_of_range)
                {
                    cerr << "Integer overflow in years" << '\n';
                    return EXIT_FAILURE;
                }
                if(years <= 0)
                {
                    cerr << "Years can't be a negative number" << '\n';
                    return EXIT_FAILURE;
                }
                break;

            case 'h':
            case '?':
            default :
                cerr << "Arguments: \n"
                     << "\t-u or --usage for average household consumption per year in (MWh)\n"
                     << "\t-p or --power \n"
                     << "\t-y or --years\n";
                return EXIT_FAILURE;
        }

    cout << "-----------------------------------------------------------------------\n"
         << "SIMULATION START\n"
         << "-----------------------------------------------------------------------\n"
         << "Running with " << usage << "(MWh) average household consumption per year.\n"
         << "Running with " << power << "(kWp) power.\n"
         << "Running in range of " << years << " years.\n"
         << "-----------------------------------------------------------------------\n"
         << endl;

    cout << "Panels bought for: " << power * panelPriceFor1kWp << "€" << endl;
    profit -= panelPriceFor1kWp * power;

    for (int i = 1; i <= years; ++i) {
        cout << "-------------------------------- YEAR " << i << " -------------------------------\n";

        if (isCrisis){
            elePriceFor1MWhPerYear -= abs(0.55*elePriceFor1MWhPerYear);
            isCrisis = false;
        }

        energyCrisisChance = (rand() % 100) < 2;
        if(energyCrisisChance){
            elePriceFor1MWhPerYear += abs(2.5*elePriceFor1MWhPerYear);
            numberOfCrisis++;
            isCrisis = true;
        }
        profit += abs(elePriceFor1MWhPerYear * (power));

        elePriceFor1MWhPerYear += 5;
        energyWithout += usage;
        energyWith += usage - power;
        energySaved += power;

        cout << "Spotreba energie:" << endl;
        printf("\tSpotreba elektrickej energie: %.1f(MWh)\n", energyWithout);
        printf("\tSpotreba elektrickej energie so solárnym panelom: %.1f(MWh)\n", energyWith);
        printf("\tUšetrená elektrická energia: %.1f(MWh)\n", energySaved);


        cout << "Emisie:" << endl;
        printf("\tCO2 vyprodukované bez solárneho panelu: %.1f(kg)\n", emission * energyWithout);
        printf("\tCO2 vyprodukované so solárnym panelom: %.1f(kg)\n", emissionWithPV * energyWith);
        printf("\tUšetrené škody na životnom prostredí: %.1f(kg)\n", emission * energySaved);

        cout << "Profit: " << profit << "€" << endl;
    }

    cout << "----------------------- Crisis happened " << numberOfCrisis << " times -----------------------\n";
    cout << "-----------------------------------------------------------------------\n"
         << "SIMULATION DONE\n"
         << "-----------------------------------------------------------------------\n";
    return 0;
}

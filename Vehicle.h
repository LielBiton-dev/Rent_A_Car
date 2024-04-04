
#pragma once

#define MAX_PLATE 20
#define MIN_MAN_YEAR 1950
#define SEATS_OPT 4
static const int Seats[SEATS_OPT] = { 2,3,4,5 };

typedef enum { ePremium, eStandard, eCompact, eNofCats } eCategory;
static char* Categories[eNofCats] = { "Premium", "Standard", "Compact" };

typedef enum { eNoFeatures, eLuxuryInterior, eEnhancedTech, eAdvancedSafety, eNofOpt } eFeatures;
static char* Features[eNofOpt] = { "No Features", "Luxury Interior", "Enhanced Technology","Advanced Safety" };

typedef enum { eMercedesBenz, eAudi, eLexus, eNumPremiumBrands } ePremiumBrand;
static char* PremiumBrand[eNumPremiumBrands] = { "Mercedes Benz", "Audi", "Lexus" };

typedef enum { eToyota, eHonda, eFord, eNumStandardBrands } eStandardBrand;
static char* StandardBrand[eNumStandardBrands] = { "Toyota", "Honda", "Ford" };

typedef enum { eVolkswagen, eKia, eNissan, eHyundai, eNumCompactBrands } eCompactBrand;
static char* CompactBrand[eNumCompactBrands] = { "Volkswagen", "Kia", "Nissan", "Hyundai" };

typedef struct {
    int isElectric;
    eFeatures feature;
    ePremiumBrand brand;
}Premium;

typedef struct {
    double cargoCapacity;
    eStandardBrand brand;
}Standard;

typedef struct {
    double fuelEfficiency;
    eCompactBrand brand;
}Compact;

typedef struct Vehicle_ {

    void (*print)(const struct Vehicle_*); // Function pointer to print vehicle
   
    int vehicleSN;
    int numSeats;
    int gearBox;
    int isTaken;
    int year;
    double odometer;
    char licensePlate[MAX_PLATE];
    int costPerDay;

    // Union to hold different categories
    union {
        Premium  premium;
        Standard standard;
        Compact compact;
    }category;

}Vehicle;

//polymorphism functions.
void initPremium(Vehicle** vehicleArr, Vehicle* premium, int vehicleCount);
void initStandard(Vehicle** vehicleArr, Vehicle* standard, int vehicleCount);
void initCompact(Vehicle** vehicleArr, Vehicle* compact, int vehicleCount);
void initVehicle(Vehicle** vehicleArr, Vehicle* vehicle, int vehicleCount);
void printVehicle(const Vehicle* vehicle);
void printPremium(const Vehicle* premium);
void printStandard(const Vehicle* standard);
void printCompact(const Vehicle* compact);

void getLicensePlate(Vehicle* vehicle);
int getNumSeats();
int getvehicleYear(int minYear);
int getVehicleSN(Vehicle** vehicleArr, int vehicleCount);
int getVehicleBrand(char** arrName, int numOfOpt);
eFeatures getPremiumFeature();

void updateOdometer(Vehicle* vehicle, int totalDays, int kmPerDay);
int rentVehicle(Vehicle* vehicle); //check again if needed.
int checkUniqueSN(int SN, Vehicle** vehicleArr, int vehicleCount);

int compareByOdometer(const void* v1, const void* v2);
int compareBySN(const void* v1, const void* v2);
int compareByYear(const void* v1, const void* v2);
int compareByLicensePlate(const void* v1, const void* v2); //tomer

//nothing to free

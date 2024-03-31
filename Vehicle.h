#pragma once

#define MAX_PLATE 20
typedef enum { eNoFeatures, eLuxuryInterior, eEnhancedTech, eAdvancedSafety, eNofOpt } eFeatures;
static const char* Features[eNofOpt] = { "No Features", "Luxury Interior", "Enhanced Technology","Advanced Safety" };

typedef enum { eMercedesBenz, eAudi, eLexus, eNumPremiumBrands } ePremiumBrand;
static const char* PremiumBrand[eNumPremiumBrands] = { "Mercedes Benz", "Audi", "Lexus"};

typedef enum { eToyota, eHonda, eFord, eNumStandardBrands } eStandardBrand;
static const char* StandardBrand[eNumStandardBrands] = { "Toyota", "Honda", "Ford" };

typedef enum { eVolkswagen, eKia, eNissan, eHyundai, eNumCompactBrands } eCompactBrand;
static const char* CompactBrand[eNumCompactBrands] = { "Volkswagen", "Kia", "Nissan", "Hyundai"};

typedef struct {
	int isElectric;
    eFeatures feature;
    ePremiumBrand brand;
}Premium;

typedef struct {
	double cargoCapacity;
    int babyChair;
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
    float costPerDay;

    // Union to hold different categories
    union {
        Premium  premium;
        Standard standard;
        Compact compact;
    }category;

}Vehicle;

void printVehicle(const Vehicle* vehicle);
void printPremium(const Vehicle* premium);
void printStandard(const Vehicle* standard);
void printCompact(const Vehicle* compact);
void updateOdometer(Vehicle* vehicle, int totalDays, int kmPerDay);
int rentVehicle(Vehicle* vehicle);
int checkUniqueSN(int SN, Vehicle** vehicleArr, int vehicleCount);

int compareByOdometer(const void* v1, const void* v2);
int compareBySN(const void* v1, const void* v2);
int compareByCost(const void* v1, const void* v2);
int compareByYear(const void* v1, const void* v2);

//nothing to free
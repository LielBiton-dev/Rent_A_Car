#pragma once
typedef enum { eLiability, eCollision, eRoadside, ePersonal, eComprehensive, eNumTypes } eType;
static const char* types[eNumTypes] = { "Liability", "Collision Damage Waiver", "Roadside Assistance", "Personal Accident", "Comprehensive" };
static const int costs[eNumTypes] = { 12,20,18,22,30 };

#define START_SN_INSUR 10000
typedef struct {
    int InsuranceSN;
    eType type;
    int costPerDay;
}Insurance;

Insurance createInsurance();
int generateInsuranceSN();
eType getInsuranceType();
const char* GetTypeStr(int type);
void printInsurance(const Insurance* insurance);

//nothing to free
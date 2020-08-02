#include "provided.h"
#include <vector>
#include <random>       // to create random number generator
#include <set>
using namespace std;
/*
int factorial(int n) {
    // factorial function for delivery optimizer
    if (n == 0 || n == 1)
        return 1;
    return factorial(n - 1) * n;
}

int min(int a, int b) {
    if (a < b)
        return a;
    else return b;
}
*/

int randInt(int min, int max) {
    // generate random integer between min and max (inclusive)
    if (max < min)
        std::swap(max, min);
    static std::random_device rd;
    static std::default_random_engine generator(rd());
    std::uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

// ##################################################################################################################
// DeliveryOptimizerImpl DECLARATION
// ##################################################################################################################

class DeliveryOptimizerImpl {
    public:
        DeliveryOptimizerImpl(const StreetMap* sm);
        ~DeliveryOptimizerImpl();
        void optimizeDeliveryOrder(
            const GeoCoord& depot,
            vector<DeliveryRequest>& deliveries,
            double& oldCrowDistance,
            double& newCrowDistance) const;
    private:
        const   StreetMap* m_map;
        double  findPlanDistance(const GeoCoord& depot, const vector<DeliveryRequest>& plan) const;
        void    simAnnealing(const GeoCoord& depot, vector<DeliveryRequest>& deliveries) const;
        vector<DeliveryRequest> mutateDeliveryPlan(const vector<DeliveryRequest>& plan) const;      
};

// ##################################################################################################################
// DeliveryOptimizerImpl IMPLEMENTATION
// ##################################################################################################################

DeliveryOptimizerImpl::DeliveryOptimizerImpl(const StreetMap* sm) 
    : m_map(sm) {}

DeliveryOptimizerImpl::~DeliveryOptimizerImpl() {
}

void DeliveryOptimizerImpl::optimizeDeliveryOrder(
    const GeoCoord& depot,
    vector<DeliveryRequest>& deliveries,
    double& oldCrowDistance,
    double& newCrowDistance) const {
    
    // trivial case: no deliveries are specified
    if (deliveries.size() == 0) {
        oldCrowDistance = 0;
        newCrowDistance = 0;
        return;
    }

    oldCrowDistance = findPlanDistance(depot, deliveries);
   
    // optimising deliveries
    simAnnealing(depot, deliveries);
    newCrowDistance = findPlanDistance(depot, deliveries);
}

void DeliveryOptimizerImpl::simAnnealing(
    const GeoCoord& depot,
    vector<DeliveryRequest>& deliveries) const {

    vector<DeliveryRequest> currentPlan = deliveries;   // current delivery plan
    
    int TMax = 10000;
    
    // simulating annealing as temperature decreases
    for (int i = TMax; i != 0; i--) {

        double T = (i + 1) / TMax;

        double currentDist = findPlanDistance(depot, currentPlan);
        
        vector<DeliveryRequest> newPlan = mutateDeliveryPlan(currentPlan);
        double newDist = findPlanDistance(depot, newPlan);
        
        double deltaDist = newDist - currentDist;

        // new plan is better than old plan
        if (deltaDist < 0)
            currentPlan = newPlan;

        // new plan isn't better than old plan -> check acceptance probability
        else if (exp(-deltaDist / T ) > randInt(0, 1000) / 1000)
            currentPlan = newPlan;
    }

    deliveries = currentPlan;
}

double DeliveryOptimizerImpl::findPlanDistance(const GeoCoord& depot, const vector<DeliveryRequest>& plan) const {
    // compute and return the total distance along the delivery plan

    // trivial case; plan is empty
    if (plan.size() == 0)
        return 0;
    
    double planDist = 0;    // distance along full plan
    planDist += distanceEarthMiles(depot, plan.front().location);        // distance from depot to first location

    // finding total distance between first and last delivery location
    for (int i = 0; i != plan.size() - 1; i++)
        planDist += distanceEarthMiles(plan[i].location, plan[i + 1].location);
    
    planDist += distanceEarthMiles(depot, plan.back().location);        // distance from last location to depot

    return planDist;
}

vector<DeliveryRequest> DeliveryOptimizerImpl::mutateDeliveryPlan(const vector<DeliveryRequest>& plan) const {
    // returns a shuffled version of the delivery plan

    vector<DeliveryRequest> mutatedPlan = plan;    // the vector which we'll mutate in-place

    // shuffle plan plan (Fisher-Yates)
    for (int i = mutatedPlan.size() - 1; i != 0; i--) {
        int j = randInt(0, i);
        DeliveryRequest requestJ = mutatedPlan[j];
        mutatedPlan[j] = mutatedPlan[i];
        mutatedPlan[i] = requestJ;
    }

    return mutatedPlan;
}

// ##################################################################################################################
// DeliveryOptimizer FUNCTIONS
// ##################################################################################################################
// These functions simply delegate to DeliveryOptimizerImpl's functions.
// You probably don't want to change any of this code.

DeliveryOptimizer::DeliveryOptimizer(const StreetMap* sm)
{
    m_impl = new DeliveryOptimizerImpl(sm);
}

DeliveryOptimizer::~DeliveryOptimizer()
{
    delete m_impl;
}

void DeliveryOptimizer::optimizeDeliveryOrder(
        const GeoCoord& depot,
        vector<DeliveryRequest>& deliveries,
        double& oldCrowDistance,
        double& newCrowDistance) const
{
    return m_impl->optimizeDeliveryOrder(depot, deliveries, oldCrowDistance, newCrowDistance);
}

//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <Windows.h>
#include <vector>
#include <map>
#include <array>
#include <random>
#include <unordered_map>
#include <algorithm>

using namespace omnetpp;
using namespace std;

int z = 0;
int clients = 3;
int servers = 4;
vector<int>data = {1,2,3,4,5,6,7,8,9,10,11,12};
int servers_1 = (servers/2)+1;
int size_data = data.size()/servers;
int value = data.size()-size_data;


/**
 * In the previous model we just created another packet if we needed to
 * retransmit. This is OK because the packet didn't contain much, but
 * in real life it's usually more practical to keep a copy of the original
 * packet so that we can re-send it without the need to build it again.
 */
class Int_arr : public cMessage {
private:
    vector<int> int_array;

public:
    Int_arr(const vector<int>& array) : cMessage(), int_array(array) {}

    // Getter method to access the vector of integers
    const vector<int>& getIntArray() const { return int_array; }
};

class Int_map : public cMessage {
private:
    std::unordered_map<const char*, int> int_map;

public:
    Int_map(const std::unordered_map<const char*, int>& map) : cMessage(), int_map(map) {}

    // Getter method to access the unordered_map
    const std::unordered_map<const char*, int>& getIntMap() const { return int_map; }
};


class Tic9 : public cSimpleModule
{
  private:


    int j = 0;
    int i=0;
    int t = 0;
    int v =0;
    Int_arr *message = nullptr;
    std::vector<int> receivedValues;
    std::vector<int> maxOccurrenceVector;
    unordered_map<const char*,int> map;
    vector<const char*> moduleName;
    int count = 0;
    vector<const char*> selectedModuleNames;
    vector<int> lastCharacterValues;
    int flag = 0;



  public:
    virtual ~Tic9();

  protected:
    virtual Int_arr *generateNewMessage(int i,int j);
    virtual void sendCopyOf(cMessage *msg);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual array<int, 3> generateRandomNumbers(int x,int n);

};

Define_Module(Tic9);

Tic9::~Tic9()
{

//    delete message;
}

void Tic9::initialize()
{
    // Initialize variables.
    message = generateNewMessage(i,i+1);
        sendCopyOf(message);
        i+=size_data;
}


array<int, 3> Tic9::generateRandomNumbers(int x, int n) {
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n - 1);

    // Create a set to store unique random numbers
    std::set<int> uniqueNumbers;

    // Generate and store unique random numbers
    while (uniqueNumbers.size() < x) {
        uniqueNumbers.insert(dis(gen));
    }

    // Convert the set to an array
    array<int, 3> randomNumbers;
    auto it = uniqueNumbers.begin();
    for (int i = 0; i < x; ++i) {
        randomNumbers[i] = *it;
        ++it;
    }

    return randomNumbers;
}



void Tic9::handleMessage(cMessage *msg)
{
    Int_arr *x = dynamic_cast<Int_arr*>(msg);
    Int_map *intmap = dynamic_cast<Int_map*>(msg);

        if (dynamic_cast<Int_arr*>(msg) != nullptr) {
            const vector<int>& data = x->getIntArray();
            j++;
            if (data.size() == 1) {
                // Only one value received, store it
                receivedValues.push_back(data[0]);
                moduleName.push_back(msg->getSenderModule()->getName());
//                auto it = map.find(msg->getSenderModule()->getName());
//                if(it!=map.end()){
//                    map[msg->getSenderModule()->getName()] = 0;
//                }


                if(j==servers_1){
                    j = 0;
                    EV<<"Values received at client,"<< msg->getArrivalModule()->getName()<<": ";
                    for (size_t k = 0; k < receivedValues.size(); ++k) {
                        EV << receivedValues[k] << " ";
                    }
                    EV<<endl;
                    std::map<int, int> occurrenceCount;
                    // Count occurrences of each value in receivedValues
                    for (int val : receivedValues) {
                        occurrenceCount[val]++;
                    }


                    // Find the value with the maximum occurrence
                    int maxOccurrenceValue = 0;
                    int maxOccurrenceCount = 0;
                    for (const auto& entry : occurrenceCount) {
                        if (entry.second > maxOccurrenceCount) {
                            maxOccurrenceCount = entry.second;
                            maxOccurrenceValue = entry.first;
                        }
                    }

                    // Store the value with maximum occurrence in another vector
                    if (maxOccurrenceCount > 0) {
                        maxOccurrenceVector.push_back(maxOccurrenceValue);
                    }

                    for(size_t k=0;k<receivedValues.size();k++){
                         if(receivedValues[k] == maxOccurrenceValue){
                               map[moduleName[k]]++;
                                            }
                                        }

                    receivedValues.clear();
                    moduleName.clear();

                    if(i<=value){
                        initialize();
                    }
                    else{
                        i=0;
                        int maxMaxOccurrenceValue = 0;
                        for (int val : maxOccurrenceVector) {
                            if (val > maxMaxOccurrenceValue) {
                                maxMaxOccurrenceValue = val;
                            }
                        }
                        EV<<"Maximum from client, "<<msg->getArrivalModule()->getName()<<":"<< maxMaxOccurrenceValue;
                        EV<<endl;
                        EV<<"Score of servers at client,"<<msg->getArrivalModule()->getName()<<":"<<endl;
                        for (const auto& entry : map) {
                                           EV << "Server: " << entry.first << ", Count: " << entry.second << endl;
                                       }
                    if(flag==0){

                        for(int k=0;k<clients-1;k++){
                            Int_map *map1 = new Int_map(map);
                            send(map1, "out_c",k);
                        }
//                        Int_map *map1 = new Int_map(map);
//                        Int_map *map2 = new Int_map(map);
//
//                        send(map1, "out_c",0);
//                        send(map2, "out_c",1);
                    }


                    }


                }

            } else {
                EV_ERROR << "Received unexpected number of values: " << data.size() << endl;
            }
            delete msg;
        }
        else if(dynamic_cast<Int_map*>(msg) != nullptr){
            flag = 1;
            count++;
            const unordered_map<const char*, int>& receivedData = intmap->getIntMap();

                // Merge the received map into the existing map
                for (const auto& entry : receivedData) {
                    const char* moduleName = entry.first;
                    int value = entry.second;
                    map[moduleName] += value; // If the key exists, add the value to the existing value
                    // If the key doesn't exist, it will be created and initialized with the received value
                }

                delete msg;
            if(count==clients-1){
                EV<<"After client gossip score of servers : "<<endl;
                for (const auto& entry : map) {
                    EV << "Server: " << entry.first << ", Count: " << entry.second << endl;
                }
                vector<pair<const char*, int>> sortedEntries(map.begin(), map.end());
                            sort(sortedEntries.begin(), sortedEntries.end(),
                                 [](const pair<const char*, int>& a, const pair<const char*, int>& b) {
                                     if (a.second != b.second) {
                                         // Sort in descending order of counts if counts are different
                                         return a.second > b.second;
                                     } else {
                                         // If counts are same, sort based on first value (module name)
                                         return strcmp(a.first, b.first) < 0;
                                     }
                                 });

                            int totalElements = sortedEntries.size();
                            int threshold = (totalElements / 2) + 1;

                            // Store the first value of the top (n/2) + 1 entries
//                            vector<const char*> selectedModuleNames;
                            for (int i = 0; i < threshold; ++i) {
                                selectedModuleNames.push_back(sortedEntries[i].first);
                            }

                            // Store the ASCII value of the last character of each selected module name in an integer array
//                                        vector<int> lastCharacterValues;
                                        for (const char* moduleName : selectedModuleNames) {
                                            // Get the last character of the module name
                                            const char* lastCharPtr = moduleName + strlen(moduleName) - 1;
                                            // Convert the last character to its ASCII value
                                            int lastCharValue = atoi(lastCharPtr);
                                            // Store it in the vector
                                            lastCharacterValues.push_back(lastCharValue);
                                        }

                                        // Do something with the last character values
                                        EV<<"Top (n/2)+1 servers selected : ";
                                        for (int value : lastCharacterValues) {
                                            EV<< value <<" ";
                                            // Store or process each last character value as needed
                                        }// Store or process each last character as needed
                                        EV<<endl;
                                        map.clear();

                          initialize();

            }




        }
        else {
            EV_ERROR << "Received a message of unexpected type: " << msg->getClassName() << endl;
            delete msg;
        }

}

Int_arr *Tic9::generateNewMessage(int i, int j)
{

    vector<int>x;
    int size_data = data.size()/servers;
    for(int k=0;k<size_data;k++){
        x.push_back(data[i+k]);
    }
//    x.push_back(data[i]);
//    x.push_back(data[i+1]);
    Int_arr *msg = new Int_arr(x);
    return msg;
}

void Tic9::sendCopyOf(cMessage *msg)
{
    Int_arr *intMsg = dynamic_cast<Int_arr*>(msg);
    if(count==clients-1){
        if(intMsg){
            const vector<int>& intArray = intMsg->getIntArray();
                   for(int k=0;k<lastCharacterValues.size();k++){
                       Int_arr *copyMsg = new Int_arr(intArray);
                       send(copyMsg,"out",lastCharacterValues[k]);
                       }
        }
                   else{
                       EV_ERROR << "sendCopyOf(): Message is not of type Int_arr." << endl;
                                          delete msg;
                   }

    }
    else{
        if (intMsg) {
                   const vector<int>& intArray = intMsg->getIntArray();
                   array<int,3>randomNumbers = generateRandomNumbers(servers_1,servers);
                   for (int k = 0; k < servers_1; ++k) {
                       Int_arr *copyMsg = new Int_arr(intArray);
                       send(copyMsg,"out",randomNumbers[k]);
                   }
               } else {
                   EV_ERROR << "sendCopyOf(): Message is not of type Int_arr." << endl;
                   delete msg;
               }
    }


}

/**
 * Sends back an acknowledgement -- or not.
 */
class Toc9 : public cSimpleModule
{
private:
    vector<int> max_values;

  protected:
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Toc9);

void Toc9::handleMessage(cMessage *msg)
{
    Int_arr *x = dynamic_cast<Int_arr*>(msg);

    z++;
    if(z%servers==0){

                if (x) {
                    const vector<int>& data = x->getIntArray();
                    int min_value = data[0];
                    for (size_t k = 1; k < data.size(); ++k) {
                        if (data[k] < min_value) {
                            min_value = data[k];
                        }
                    }
                    max_values.push_back(min_value);

                    vector<int> min_value_vector = {min_value};
                    Int_arr *minMsg = new Int_arr(min_value_vector);
                    send(minMsg, "out", msg->getArrivalGate()->getIndex());

                } else {
                    EV_ERROR << "Received a message of unexpected type: " << msg->getClassName() << endl;
                    delete msg;
                }
    }
    else{
        if (x) {
                    const vector<int>& data = x->getIntArray();
                    int max_value = data[0];
                    for (size_t k = 1; k < data.size(); ++k) {
                        if (data[k] > max_value) {
                            max_value = data[k];
                        }
                    }
                    max_values.push_back(max_value);

                    vector<int> max_value_vector = {max_value};
                    Int_arr *maxMsg = new Int_arr(max_value_vector);
                    send(maxMsg, "out", msg->getArrivalGate()->getIndex());

                } else {
                    EV_ERROR << "Received a message of unexpected type: " << msg->getClassName() << endl;
                    delete msg;
                }
    }

//
}


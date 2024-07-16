#pragma once
#pragma once
#include <iostream>

using std::string;

class Record
{
private:
    string id;
    string year;
    string causeName113;
    string causeName;
    string state;
    string deaths;
    string rate;

public:
    Record() {
    }

    Record(string id,
        string year,
        string causeName113,
        string causeName,
        string state,
        string deaths,
        string rate) {
        this->id = id;
        this->year = year;
        this->causeName113 = causeName113;
        this->causeName = causeName;
        this->state = state;
        this->deaths = deaths;
        this->rate = rate;
    }

    void setId(string id) { this->id = id; }
    string getId() { return this->id; }
    void setYear(string year) { this->year = year; }
    string getYear() { return this->year; }
    void setCauseName113(string causeName113) { this->causeName113 = causeName113; }
    string getCauseName113() { return this->causeName113; }
    void setCauseName(string causeName) { this->causeName = causeName; }
    string getCauseName() { return this->causeName; }
    void setState(string state) { this->state = state; }
    string getState() { return this->state; }
    void setDeaths(string deaths) { this->deaths = deaths; }
    string getDeaths() { return this->deaths; }
    void setRate(string rate) { this->rate = rate; }
    string getRate() { return this->rate; }

};

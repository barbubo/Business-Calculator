#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Staff {
protected:
    string nume;
    string rol;
public:
    string dieta;

    virtual double getCostCazare() = 0;

    double getCostAlimentatie() {
        if (dieta == "orice")return 61.2;
        else if (dieta == "vegetariana")return 54.2;
        else if (dieta == "flexitariana")return 67.2;
    }

    string getNume() {
        return this->nume;
    }

    string getRol() {
        return this->rol;
    }

    string getRolEN() {
        if (this->rol == "extins")return "extra";
        else if (this->rol == "actor")return "actor";
        else if (this->rol == "figuratie")return "figuration";
    }

    void setDieta(int x) {
        if (x == 0)this->dieta = "orice";
        else if (x == 1)this->dieta = "vegetariana";
        else if (x == 2)this->dieta = "flexitariana";
    }
};

class Extins : public Staff {
public:
    Extins(string n, string r) {
        this->nume = n;
        this->rol = r;
    }

    double getCostCazare() {
        return 175;
    }
};

class Actor : public Staff {
public:
    string clasaMonstru;

    Actor(string n, string r) {
        this->nume = n;
        this->rol = r;
    }

    double getCostMachiaj() {
        if (this->clasaMonstru == "vampir")return 230;
        else if (this->clasaMonstru == "varcolac")return 555;
        else if (this->clasaMonstru == "sirena")return 345;
        else if (this->clasaMonstru == "clarvazator")return 157;
        else if (this->clasaMonstru == "om")return 55;
    }

    void setClasaMonstru(int x) {
        if (x == 0)this->clasaMonstru = "vampir";
        else if (x == 1)this->clasaMonstru = "varcolac";
        else if (x == 2)this->clasaMonstru = "sirena";
        else if (x == 3)this->clasaMonstru = "clarvazator";
        else if (x == 4)this->clasaMonstru = "om";
    }

    double getCostCazare() {
        return 175;
    }
};

class Figuratie : public Staff {
public:
    string clasaMonstru;

    Figuratie() {
        string prenume[] = {
                "Ada", "Albertina", "Anabela", "Arina", "Bianca", "Beatrice", "Camelia", "Daniela", "Draga",
                "Ecaterina", "Ionela", "Abel", "Benjamin", "Costin", "Darius", "Ionel", "Leonard", "Madalin", "Nelu",
                "Octavian", "Rares"
        };
        string nume[] = {
                "Almasan", "Albu", "Bercea", "Besoiu", "Calinescu", "Cadantu", "Dascalu", "Deac", "Fatu", "Firea",
                "Ganea", "Gaitan", "Hanganu", "Holban", "Lucaciu", "Lucescu", "Margineanu", "Marinescu", "Nastase",
                "Parvu", "Pelea"
        };
        int x = rand() % 19;
        int y = rand() % 19;
        this->nume = prenume[x] + ' ' + nume[y];
        this->rol = "figuratie";
    }

    double getCostCazare() {
        return 140;
    }

    double getCostMachiaj() {
        if (this->clasaMonstru == "vampir")return 230;
        else if (this->clasaMonstru == "varcolac")return 555;
        else if (this->clasaMonstru == "sirena")return 345;
        else if (this->clasaMonstru == "clarvazator")return 157;
        else if (this->clasaMonstru == "om")return 55;
    }

    void setClasaMonstru(int x) {
        if (x == 0)this->clasaMonstru = "vampir";
        else if (x == 1)this->clasaMonstru = "varcolac";
        else if (x == 2)this->clasaMonstru = "sirena";
        else if (x == 3)this->clasaMonstru = "clarvazator";
        else if (x == 4)this->clasaMonstru = "om";
    }

};

void genFiguratie(int n, vector<Figuratie> *figuratii) {
    int i;
    for (i = 0; i < n; i++) {
        Figuratie fig;
        fig.setDieta(rand() % 3);
        fig.setClasaMonstru(rand() % 5);
        figuratii->push_back(fig);
    }
}

void readCast(vector<Extins> *castExtins, vector<Actor> *actori) {
    ifstream castData;
    castData.open("castData.csv");
    string line = "";
    while (getline(castData, line)) {
        string nume, rol;
        stringstream inputString(line);
        getline(inputString, nume, ',');
        getline(inputString, rol, ',');
        if (rol == "extins") {
            Extins extins(nume, rol);
            extins.setDieta(rand() % 3);
            castExtins->push_back(extins);
        } else if (rol == "actor") {
            Actor actor(nume, rol);
            actor.setDieta(rand() % 3);
            actor.setClasaMonstru(rand() % 5);
            actori->push_back(actor);
        }
    }
}

long long costTransport(int numarPersoane) {
    int numarAutocare;
    if (numarPersoane % 50 == 0)numarAutocare = numarPersoane / 50;
    else numarAutocare = numarPersoane / 50 + 1;
    return (long long) numarAutocare * 5680 / 4.68;
}

long long costSpatiu(int numarZile) {
    int costTotal = numarZile / 10 * 98000 + (numarZile % 10) * 10000;
    return costTotal / 4.68;
}

long long costCazare(vector<Extins> castExtins, vector<Actor> actori, vector<Figuratie> figuratii) {
    long long suma = 0;
    for (auto extins: castExtins) {
        suma += extins.getCostCazare();
    }
    for (auto actor: actori) {
        suma += actor.getCostCazare();
    }
    for (auto figuratie: figuratii) {
        suma += figuratie.getCostCazare();
    }
    return suma / 4.68;
}

long long costMachiaj(vector<Actor> actori, vector<Figuratie> figuratii) {
    long long suma = 0;
    for (auto actor: actori) {
        suma += actor.getCostMachiaj();
    }
    for (auto figuratie: figuratii) {
        suma += figuratie.getCostMachiaj();
    }
    return suma / 4.68;
}

long long costAlimentatie(vector<Extins> castExtins, vector<Actor> actori, vector<Figuratie> figuratii) {
    long long suma = 0;
    for (auto extins: castExtins) {
        suma += extins.getCostAlimentatie();
    }
    for (auto actor: actori) {
        suma += actor.getCostAlimentatie();
    }
    for (auto figuratie: figuratii) {
        suma += figuratie.getCostAlimentatie();
    }
    return suma / 4.68;
}

void createAllCastDataRO(vector<Extins> castExtins, vector<Actor> actori, vector<Figuratie> figuratii) {
    ofstream allCastData;
    allCastData.open("allCastDataRO.csv");
    for (auto extins: castExtins) {
        allCastData << extins.getNume() << ',' << extins.getRol() << endl;
    }
    for (auto actor: actori) {
        allCastData << actor.getNume() << ',' << actor.getRol() << endl;
    }
    for (auto figuratie: figuratii) {
        allCastData << figuratie.getNume() << ',' << figuratie.getRol() << endl;
    }
}

void createAllCastDataEN(vector<Extins> castExtins, vector<Actor> actori, vector<Figuratie> figuratii) {
    ofstream allCastData;
    allCastData.open("allCastDataEN.csv");
    for (auto extins: castExtins) {
        allCastData << extins.getNume() << ',' << extins.getRolEN() << endl;
    }
    for (auto actor: actori) {
        allCastData << actor.getNume() << ',' << actor.getRolEN() << endl;
    }
    for (auto figuratie: figuratii) {
        allCastData << figuratie.getNume() << ',' << figuratie.getRolEN() << endl;
    }
}

void createCostData(vector<Extins> castExtins, vector<Actor> actori, vector<Figuratie> figuratii) {
    int v[] = {30, 45, 60, 100};
    ofstream costData;
    costData.open("costData.csv");
    int nrPersoane = castExtins.size() + actori.size() + figuratii.size();
    for (int i = 0; i <= 3; i++) {
        costData << v[i] << ",$" << costTransport(nrPersoane) * 2 << ",$"
                 << costCazare(castExtins, actori, figuratii) * v[i] << ",$" << costMachiaj(actori, figuratii) * v[i]
                 << ",$" << costAlimentatie(castExtins, actori, figuratii) * v[i] << ",$" << costSpatiu(v[i]) << endl;
    }
}

void createMenuDataRO() {
    ofstream menuData;
    menuData.open("menuDataRO.csv");
    menuData << "1,orice,Ciorba de perisoare, Piept de pui cu cartofi prajiti, Clatite cu Nutella" << endl;
    menuData << "1,vegetariana,Supa crema de pastarnac, Conopida la cuptor, Salata de fructe" << endl;
    menuData << "1,flexitariana,Supa crema de legume, Burger cu somon, Clatite cu miere" << endl;
    menuData << endl << endl;
    menuData << "2,orice,Ciorba de burta, Puple de pui cu cartofi copti, Budinca de orez cu vanilie" << endl;
    menuData << "2,vegetariana,Supa de dovleac, Crochete cu spanac, Budinca de chia" << endl;
    menuData << "2,flexitariana,Ciorba de peste, Paste cu ton, Prajitura de portocale" << endl;
    menuData << endl << endl;
    menuData << "3,orice,Ciorba de vita, Ceafa de porc cu piure, Placinta de mere" << endl;
    menuData << "3,vegetariana,Supa crema de cartofi, Falafel, Prajitura cu banane" << endl;
    menuData << "3,flexitariana,Supa crema de spanac, Orez cu fructe de mare, Briose cu afine" << endl;
}

void createMenuDataEN() {
    ofstream menuData;
    menuData.open("menuDataEN.csv");
    menuData << "1,anything,Perisore soup,Chicken breast with fried potatoes,Pancakes with Nutella" << endl;
    menuData << "1,vegetarian,parsnip cream soup,baked cauliflower,fruit salad" << endl;
    menuData << "1,flexitarian,Vegetable cream soup,Salmon burger,Pancakes with honey" << endl;
    menuData << endl << endl;
    menuData << "2,anything,Belly soup,Chicken breasts with baked potatoes,Rice pudding with vanilla" << endl;
    menuData << "2,vegetarian,Pumpkin soup,Croquettes with spinach,Chia pudding" << endl;
    menuData << "2,flexitarian,Fish soup,Pasta with tuna,Orange cake" << endl;
    menuData << endl << endl;
    menuData << "3,anything,Beef soup,Pork neck with mashed potatoes,Apple pie" << endl;
    menuData << "3,vegetarian,Potato cream soup,Falafel,Banana cake" << endl;
    menuData << "3,flexitarian,Cream of spinach soup,Rice with seafood,Muffins with blueberries" << endl;
}

template<typename T>
void afisare(T x, vector<Extins> castExtins, vector<Actor> actori, vector<Figuratie> figuratii) {
    if (x == 1) {
        createAllCastDataRO(castExtins, actori, figuratii);
        createCostData(castExtins, actori, figuratii);
        createMenuDataRO();
        cout << "Fisierele au fost create in limba romana!" << endl;
    } else if (x == 2) {
        createAllCastDataEN(castExtins, actori, figuratii);
        createCostData(castExtins, actori, figuratii);
        createMenuDataEN();
        cout << "The files were created in English!" << endl;
    } else throw "Limba invalida! Incercati 1 sau 2.";
}

void afisare(string x, vector<Extins> castExtins, vector<Actor> actori, vector<Figuratie> figuratii) {
    if (x == "ro" || x == "RO") {
        createAllCastDataRO(castExtins, actori, figuratii);
        createCostData(castExtins, actori, figuratii);
        createMenuDataRO();
    } else if (x == "en" || x == "EN") {
        createAllCastDataEN(castExtins, actori, figuratii);
        createCostData(castExtins, actori, figuratii);
        createMenuDataEN();
    } else throw "Limba invalida! Incercati RO sau EN.";
}

int main() {
    vector<Extins> castExtins;
    vector<Actor> actori;
    vector<Figuratie> figuratii;
    readCast(&castExtins, &actori);
    genFiguratie(132, &figuratii);
    cout << "[1]Limba romana                [2]Limba engleza" << endl;
    int x;
    cin >> x;
    try {
        afisare(x, castExtins, actori, figuratii);
    }
    catch (const char *msg) {
        cerr << msg << endl;
    }
    return 0;
}

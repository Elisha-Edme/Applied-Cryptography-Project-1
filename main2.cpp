#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <cmath>
#include <ctime>
using namespace std;

vector<char> SET = {' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
double PROB_OF_RANDOM_CIPHERTEXT = 0.05;
vector<double> EXPECTED_FREQUENCIES = {0.180, 0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070, 0.040, 0.008, 0.040, 0.024, 0.067, 0.075, 0.019, 0.010, 0.060, 0.063, 0.091, 0.028, 0.010, 0.024, 0.002, 0.020, 0.001};
vector<string> DICTIONARY2 = {"proofed", "earthwork", "sandmen", "foaled", "scapegoats", "yappers", "havened", "vexedly", "prizefighting", "goddess", "coverall", "assassinated", "retransferring", "alleviate", "perpetrators", "prearmed", "dovetailed", "reinsert", "suiciding", "awfullest", "loquaciously", "pathfinders", "dialers", "outfight", "desalt", "outspell", "bikers", "translucently", "liquidize", "ablatives", "savourers", "messenger", "lagunas", "gayness", "gainable", "spouting", "discolored", "lathing", "stampedes", "menarches", "gentling", "craftily", "oolite", "antisepsis", "alchemical", "ignominious", "blackmailers", "eccl", "award", "freakier", "joyriders", "deputized", "million", "spry", "screwiest", "spectaculars", "footsoreness", "uncivilized", "radiometric", "argentine"};
const string Candidate_Plaintext_1 = "autarchy muggiest capabilities snowier collect undivided superpower aspca tektites neuritis turtledoves miriest nonsectarian featherbrained confiscators glimpse domesticator dater houston bassoon antipathy lowdown hallucinative noses drowse wordlessly remembering lessening escargot intersects horace unroofs smokable wirepuller exteriorized auctioned cavils uprose sobbing preannouncements pests noodled minter symbiot rocketlike oops unalike readableness vivo affirmativeness plumier spaciously miseducating recessionals herbaceous recipient evanesce tightrope rester deleteriousness undiscriminati";

const string Candidate_Plaintext_2 = "wanning objectively bicyclers footmark unbutton clockworks yanks distinctively miosis headed reinduction enchanters colleges smirkiest disobliges pageant nubbier victualler beastly teazling indigens demon parser treasurable phrenological flaxseeds interdepartmental filibustered selvedges trode helplessly woefuller ridder redigesting runtish swirling naught corselet pathogeny excommunicates lappets hug basing disassociating rajah pontificator shenanigans glowworm eels halfbacks bonder psychoanalysts methamphetamine rabidly eleven fabulously apprizer lifeway peccadilloes saltatory cetera damnit";

const string Candidate_Plaintext_3 = "mettle bribe dignified topsoil groundmass sorrowfully mondays veneris provender surveyance metallurgy bowl telecasting blandest admonisher desexualization putters admen snaillike tableaux around candlewick oncogenic splintered comp anxiously overdrives misalignments condemns bars referenced sixty contritely astrally dehumidify voile frumenties vile trifles pronghorns huskies marketeers entirely spence incarnations straiten ate abetter blower decreer kayoes ungraciously quarry buttoners bumbles banjos gabbing reoccupation tanbarks brushier tycoons sixtieth motioning unsymmetrically woald stippl";

const string Candidate_Paintext_4 = "charlatans aphoristically commixt oxidise vigilante antisocial blip reinserting slicer crescent fructuary sanctioning quintains configurative yogin overbuying xylan likeness amicability yammered medicates succeeder knackeries keepings finagle ghoulish cretaceous shellers fellable dedicatee microanalytical coalitions hijackers preallotting representatives capitally fosters passives individualizes affrayers tactlessly throes reintrenched fivefold pensioned seville expectorator outleap impedance proconsul suburb valiancy crowbars basso gibbeting documents errant positive dustman alveoli stylebook";

const string Candidate_Plaintext_5 = "smile splintered propitiously sudser looter tunnies bummers kinematical jubilant shushes railings suffrage precedence sheepskins insularity regainer tallowed jaggedly legacy requiting stumblers chiaroscuros dislodged raining biceps skirtings detacher anthropoidea reliquary suits shovelhead billet saturable guiding transvestites scowler preparatory pencils vomit encouraged mustering reincarnate steers burrowers eeliest compulsion jeopardies abstractionists time jugular sagacity intangibles vitalist noncombatants mesentery legends ham larruped bummer aryan abstract weatherbound chrisms qursh qui";

vector<string> plaintexts = {Candidate_Plaintext_1, Candidate_Plaintext_2, Candidate_Plaintext_3, Candidate_Paintext_4, Candidate_Plaintext_5};

// Chooses a random value between 0 and 1
double coinGenerationAlgortithm() {
    double coinVal = ((double) rand() / (RAND_MAX));
    return coinVal;
}

// Chooses a random index in the key
size_t keyCharacterSchedulingAlgorithm(size_t key_len) {
    size_t ind = rand() % key_len;
    return ind;
}

//encrypts plaintext string, produces candidate strings for test2
string encryptString(vector<int>& key, const string& plaintext) {
    int messagePointer = 0;
    int numRandCharacters = 0;
    string c = "";
    while (messagePointer < plaintext.size()) {
        double coinValue = coinGenerationAlgortithm();
        if (PROB_OF_RANDOM_CIPHERTEXT < coinValue) {
            int ind = keyCharacterSchedulingAlgorithm(key.size());
            auto it = find(SET.begin(), SET.end(), plaintext[messagePointer]);
            int index = it - SET.begin();
            c += SET[(index+key[ind]) % 27];
        }
        else {
            if (coinValue <= PROB_OF_RANDOM_CIPHERTEXT) {
                c += SET[rand() % 27];
                numRandCharacters++;
            }
            c += ' ';
        }
        messagePointer++;
    }
    return c;
}

// create a random key of random size
void generate_key(size_t max_len, vector<int>& key)
{
    unordered_set<int> used; ;
    size_t len =  7 + (rand() % max_len);
    while(key.size() != len)
    {
        int number = rand() % 27;
        if(used.count(number) == 0 && number <= 27)
        {
            used.insert(number);
            key.push_back(number);
        }
    }
}

//generates 100 candidate strings using ciphertext
vector<string> generateCandidates(string& ciphertext) {
    vector<string> candidates;
    int maxT = 24;
    int minT = 4;
    int candidatesPerKey = 5;
    for (int i=minT; i < maxT; i++) {
        for (int j = 0; j < candidatesPerKey; j++) {
            vector<int> key;
            generate_key(i, key);
            string candidate = encryptString(key, ciphertext);
            candidates.push_back(candidate);
        }
    }
    return candidates;
}

//fills vector with maps of characters and the number of times they occur in a candidate text
vector<map<char, int>> fillOccurrences(vector<string>& candidates) {
    //initializes counts to 0
    vector<map<char, int>> allOccurrences;
    for (int i=0; i < candidates.size(); i++) {
        map<char, int> occurrences;
        for (int j=0; j < SET.size(); j++) {
            occurrences[SET[j]] = 0;
        }
        allOccurrences.push_back(occurrences);
    }

    //counts up all occurrences of characters in candidate texts
    for (int i = 0; i < candidates.size(); i++) {
        for (int j = 0; j < candidates[i].size(); j++) {
            if (allOccurrences[i].count(candidates[i][j]) > 0) {
                allOccurrences[i][candidates[i][j]]++;
            } else {
                allOccurrences[i][candidates[i][j]] = 1;
            }
        }
    }
    return allOccurrences;
}



//finds lowest chi square value from candidates and prints out best guess among candidates
void guess(vector<double>& distributions, vector<string>& candidates) {
    vector<double> *copy = new vector<double>(distributions);
    sort(distributions.begin(), distributions.end());
    for (int i = 0; i < distributions.size(); i++) {
        cout << distributions[i] << " " << distributions[i] << endl;
            cout << "My guess is " << candidates[i] << endl;
            break;
    }
}

//produces a guess for test 2
void test2Guess( string& ciphertext) {
    vector<string> candidates = generateCandidates(ciphertext);
    vector<double> distributions;
    vector<map<char, int>> allOccurrences = fillOccurrences(candidates);

    for (int i = 0; i < allOccurrences.size(); i++) {
        double x_i = 0;
        int j = 0;
        for (auto it_o = allOccurrences[i].begin(), end_o = allOccurrences[i].end();
             it_o != end_o;) {
            //chi squared calculation
            double exp = ciphertext.size() * EXPECTED_FREQUENCIES[j];
            double obs_exp = (it_o->second - exp);
            double obs_exp2 = pow(obs_exp, 2);
            x_i += obs_exp2 / (double) exp;
            it_o++;
            j++;
        }
        distributions.push_back(x_i);
    }
    guess(distributions, candidates);

}

void test1Guess(vector<string> plaintexts, string ciphertext) {
    //fills vector with maps, each map has letter and the amount of times it occurs in the plain text and the ciphertext
    plaintexts.push_back(ciphertext);
    vector<map<char, int>> allOccurrences;
    for (int i=0; i < plaintexts.size(); i++) {
        map<char, int> occurrences;
        for (int j=0; j < SET.size(); j++) {
            occurrences[SET[j]] = 0;
        }
        allOccurrences.push_back(occurrences);
    }

    //fills vector
    for (int i = 0; i < plaintexts.size(); i++) {
        for (int j = 0; j < plaintexts[i].size(); j++) {
            if (allOccurrences[i].count(plaintexts[i][j]) > 0) {
                allOccurrences[i][plaintexts[i][j]]++;
            } else {
                allOccurrences[i][plaintexts[i][j]] = 1;
            }
        }
    }


    vector<double> distributions;
    //calculates the chi squared values
    for (int i=0; i < allOccurrences.size()-1; i++) {
        double x_i = 0;
        //int j = 0;
        for (auto it_o = allOccurrences[i].begin(), it_e = allOccurrences[5].begin(), end_e = allOccurrences[5].begin(), end_o = allOccurrences[i].end();
             it_o != end_o;)
        {
            double e = it_e->second;
            double o_e = (it_o->second-e);
            double o_e2 = pow(o_e, 2);
            //displays steps of chi square calculation
            //cout << it_o->first << ": (" << it_o->second << " - " << e << ")^2 / " << e << " = " << o_e2/(double)e << " ";
            //cout << x_i << " + " << o_e2/(double)e;
            x_i += o_e2 /(double)e;
            it_o++;
            it_e++;
            //j++;
        }
        //cout << "push back " << x_i << endl;
        distributions.push_back(x_i);
    }
    guess(distributions, plaintexts);

}

int main() {
    srand((unsigned int )time(NULL));
    string ciphertext2;
    cout << "Enter the ciphertext for ";
    cin.ignore();
    getline(cin, ciphertext2);
    vector<int> key;
    generate_key(10, key);

    test1Guess(plaintexts, ciphertext2);
    test2guess(ciphertext2);
    return 0;
}

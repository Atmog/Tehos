#ifndef SCORE_HPP
#define SCORE_HPP

#include "../Application/SettingsParser.hpp"
#include "../Application/IO.hpp"

#include "../Application/System.hpp"

#include <SFML/Network/Http.hpp>
#include <vector>
#include <sstream>

class Score
{
    public:
        Score();

        void load();

        std::string getBestScoreStr(int best = 1);
        int getBestScore(int best = 1);

        bool newScore(int score);

        void submit(std::string user);

        void save();

        std::pair<int,std::string> getWorldBestScore();

    private:
        std::vector<int> mScore;
        app::SettingsParser mFile;
};

#endif // SCORE_HPP

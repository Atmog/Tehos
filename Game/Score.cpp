#include "Score.hpp"

Score::Score()
{
    load();
}

void Score::load()
{
    mFile.loadFromFile("Assets/Data/score.dat");
    for (int i = 1; i < 6; i++)
    {
        int value = 0;
        mFile.get<int>(app::IO::toString(i),value);
        mScore.push_back(value);
    }
}

std::string Score::getBestScoreStr(int best)
{
    return app::IO::toString(mScore[best-1]);
}

int Score::getBestScore(int best)
{
    return mScore[best-1];
}

bool Score::newScore(int score)
{
    mScore.push_back(score);
    std::sort(mScore.begin(), mScore.end(), std::greater<int>());
    if (mScore.back() == score)
    {
        mScore.pop_back();
        return false;
    }
    else
    {
        mScore.pop_back();
        return true;
    }
}

void Score::submit(std::string user)
{
    if (!mScore.empty())
    {
        sf::Http::Request request("/Tehos/score.php", sf::Http::Request::Post);

        std::ostringstream stream;
        stream << "name=" << user << "&score=" << mScore[0];
        request.setBody(stream.str());

        sf::Http http("http://atmog.altervista.org/");
        sf::Http::Response response = http.sendRequest(request);

        if (response.getStatus() != sf::Http::Response::Ok)
        {
            app::System::getLog() << "Failed to submit score";
        }
    }
}

void Score::save()
{
    for (unsigned int i = 0; i < mScore.size(); i++)
    {
        mFile.set<int>(app::IO::toString(i+1),mScore[i]);
    }
    mFile.saveToFile();
}

std::pair<int,std::string> Score::getWorldBestScore()
{
    return std::pair<int,std::string>(0,"");
}
